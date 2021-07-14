#include "basic_signal.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>
#include <stdexcept>
#include <pigpiod_if2.h>
#include <boost/bind/bind.hpp>

#define SLOGW(msg) spdlog::warn("BS> {}", msg)
#define SLOGI(msg) spdlog::info("BS> {}", msg)
#define SLOGE(msg) spdlog::error("BS> {}", msg)
#define SLOGD(msg) spdlog::debug("BS> {}", msg)
static void debounce_filter(const boost::system::error_code &ec, std::atomic<bool> *execute_flag, int pull_type, int pi, uint32_t gpio, BasicSignalling *self, boost::asio::steady_timer *t);

BasicSignalling::BasicSignalling(
    const std::shared_ptr<boost::asio::io_service> &io_service, const SUTType &SUT)
    : _sut_type(SUT), _io_service(io_service), _strand(*_io_service),
      _strand_required(false),
      _started(false)
{
  if (io_service == nullptr)
  {
    throw std::invalid_argument("Asio io_service is invalid!");
  }
}
BasicSignalling::~BasicSignalling()
{
  callback_cancel(this->gpiod_callback_id);
  pigpio_stop(this->gpiod_pid);
}

bool BasicSignalling::start(void)
{
  assert(!is_started() && "Basic Signalling module is already started!");
  if (is_started())
    return false;
  this->gpiod_pid = pigpio_start(NULL, NULL);
  if (0 > this->gpiod_pid)
  {
    SLOGE("Failed to get gpio id from pigpio daemon");
    return false;
  }
  int result = 0;
  for (auto &relay : this->RELAYS)
  {
    int temp = 0;
    temp += set_mode(this->gpiod_pid, relay, PI_OUTPUT);
    temp += set_pull_up_down(this->gpiod_pid, relay, PI_PUD_DOWN);
    temp += gpio_write(this->gpiod_pid, relay, OFF);
    if (0 > temp)
    {
      SLOGE(fmt::format("Failed to initialize GPIO {}", relay));
      result++;
    }
  }
  int temp = 0;
  temp += set_mode(this->gpiod_pid, INPUT_BUTTON_PIN, PI_INPUT);
  temp += set_pull_up_down(this->gpiod_pid, INPUT_BUTTON_PIN, PI_PUD_DOWN);
  this->gpiod_callback_id = callback_ex(this->gpiod_pid, INPUT_BUTTON_PIN, RISING_EDGE, &BasicSignalling::btn_isr, this);
  if ((0 > temp) || (0 > this->gpiod_callback_id))
  {
    SLOGE(fmt::format("Failed to initialize GPIO {}", INPUT_BUTTON_PIN));
    result++;
  }
  if (0 == result)
  {
    _started = true;
  }
  else
  {
    _started = false;
  }
  return _started;
}

void BasicSignalling::stop(void)
{
}

bool BasicSignalling::is_started(void)
{
  return _started;
}

void BasicSignalling::set_event_notification(const std::shared_ptr<BasicSignalCallback> &cb)
{
  // cast shared_ptr of CallbackObject to reference weak ptr > push to list
  this->_event_noti[cb->get_type()].push_back(std::weak_ptr<BasicSignalCallback>(cb));
}

bool BasicSignalling::set_state(IEC_61851_States state)
{
  (void)state;
  return false;
}

IEC_61851_States BasicSignalling::get_state(void)
{
  return A;
}

bool BasicSignalling::verify_state(IEC_61851_States state)
{
  (void)state;
  return false;
}

bool BasicSignalling::set_error(IEC_61851_ErrStates error_state)
{
  (void)error_state;
  return false;
}

void BasicSignalling::set_proximity(uint32_t value)
{
  SLOGW("not support proximity operation");
  (void)value;
}

uint32_t BasicSignalling::get_proximity(void)
{
  SLOGW("not support proximity operation");
  return 0;
}

void BasicSignalling::set_pwm(uint32_t duty)
{
  SLOGW("not support pwm operation");
  (void)duty;
}

uint32_t BasicSignalling::get_pwm(void)
{
  SLOGW("not support pwm operation");
  return 0;
}

void BasicSignalling::set_freq(uint32_t freq)
{
  SLOGW("not support frequency operation");
  (void)freq;
}

uint32_t BasicSignalling::get_freq(void)
{
  SLOGW("not support frequency operation");
  return 0;
}

void BasicSignalling::temp_call()
{
  // loop through all callback register for STATE event
  for (auto cb = this->_event_noti[CallbackType::STATE].begin();
       cb != this->_event_noti[CallbackType::STATE].end();)
  {
    // check if callback is valid(i.e. register object is still exist)
    if (auto obj_cb = cb->lock())
    // if (check_valid_callback(this->_event_noti[CallbackType::STATE], cb))
    {
      (*obj_cb)(A);
      cb++;
    }
    else
    {
      cb = this->_event_noti[CallbackType::STATE].erase(cb);
    }
  }
  // same for other
  for (auto cb = this->_event_noti[CallbackType::DUTY].begin();
       cb != this->_event_noti[CallbackType::DUTY].end();)
  {
    if (auto obj_cb = cb->lock())
    {
      (*obj_cb)(100.0);
      cb++;
    }
    else
    {
      cb = this->_event_noti[CallbackType::DUTY].erase(cb);
    }
  }
}
void BasicSignalling::_notify_btn_isr(void)
{
  for (auto cb = this->_event_noti[CallbackType::ISR].begin();
       cb != this->_event_noti[CallbackType::ISR].end();)
  {
    if (auto obj_cb = cb->lock())
    {
      (*obj_cb)();
      cb++;
    }
    else
    {
      cb = this->_event_noti[CallbackType::ISR].erase(cb);
    }
  }
}
static void debounce_filter(const boost::system::error_code &ec, std::atomic<bool> *execute_flag, int pull_type, int pi, uint32_t gpio, BasicSignalling *self, boost::asio::steady_timer *t)
{
  static uint32_t press_state = 0x00000001;
  if (ec != boost::asio::error::operation_aborted)
  {
    // a stream of 1 high and 31 low -> button pressed (default high, pressed low, falling edge)
    // 32*5us -> 160us minimum(low state hold) to detect button pressed
    int val;
    if (pull_type == PI_PUD_DOWN)
      val = !gpio_read(pi, gpio);
    else
      val = gpio_read(pi, gpio);
    press_state = (press_state << 1) | val | 0xE0000000;
    SLOGD(fmt::format("read value {0} - {1:0X}", val, press_state));
    if (press_state == 0xF0000000)
    {
      self->_notify_btn_isr();
      *execute_flag = false;
      press_state = 0x00000001;
      SLOGD("button pressed");
    }
    else
    {
      // if 32bit high detect (button in default state) or low(pressed hold) stop reload timer else reload timer
      if ((press_state != 0xFFFFFFFF) && (press_state != 0xE0000000))
      {
        SLOGD("wait next poll");
        t->async_wait(boost::bind(debounce_filter, boost::placeholders::_1, execute_flag, pull_type, pi, gpio, self, t));
      }
      else
      {
        SLOGD("debounce timer reset");
        *execute_flag = false;
        press_state = 0x00000001;
      }
    }
  }
  else
  {
    SLOGD("debounce timer cancel");
    // reset
  }
}
void BasicSignalling::btn_isr(int pi, uint32_t gpio, uint32_t level, uint32_t tick, void *self)
{
  // timer poll the gpio value each 10us
  static boost::asio::steady_timer debounce_timer((*((BasicSignalling *)self)->_io_service), std::chrono::microseconds{5});
  static std::atomic<bool> execute_flag = false;
  // register falling_edge signal of input button pin and timer is not in execution
  if ((gpio == INPUT_BUTTON_PIN) && (execute_flag == false))
  {
    SLOGD(fmt::format("await timer {}", level));
    execute_flag = true;
    debounce_timer.async_wait(boost::bind(debounce_filter, boost::placeholders::_1, &execute_flag, PI_PUD_DOWN, pi, gpio, (BasicSignalling *)self, &debounce_timer));
  }
}