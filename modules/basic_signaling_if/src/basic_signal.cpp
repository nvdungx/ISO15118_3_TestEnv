#include "basic_signal.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>
#include <stdexcept>
#include <pigpiod_if2.h>
#include <boost/bind/bind.hpp>

#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)

namespace TestLib
{

  static void debounce_filter(const boost::system::error_code &ec,
                              std::atomic<bool> *execute_flag, int pull_type, int pi, uint32_t gpio,
                              BasicSignalling *self, boost::asio::steady_timer *t);

  const EnumUnorderedMap GPIOIF_ERROR({{pigif_bad_send, "pigif_bad_send"},
                                       {pigif_bad_recv, "pigif_bad_recv"},
                                       {pigif_bad_getaddrinfo, "pigif_bad_getaddrinfo"},
                                       {pigif_bad_connect, "pigif_bad_connect"},
                                       {pigif_bad_socket, "pigif_bad_socket"},
                                       {pigif_bad_noib, "pigif_bad_noib"},
                                       {pigif_duplicate_callback, "pigif_duplicate_callback"},
                                       {pigif_bad_malloc, "pigif_bad_malloc"},
                                       {pigif_bad_callback, "pigif_bad_callback"},
                                       {pigif_notify_failed, "pigif_notify_failed"},
                                       {pigif_callback_not_found, "pigif_callback_not_found"},
                                       {pigif_unconnected_pi, "pigif_unconnected_pi"},
                                       {pigif_too_many_pis, "pigif_too_many_pis"}});
  const EnumMap STATE_MAP({"A", "B", "C", "D", "E", "F", "NA", "none_"});
  const EnumMap ERROR_MAP({"LOST_CP", "LOST_PE", "LOST_DIODE", "SHORT_CP_PE"});

  BasicSignalling::BasicSignalling(
      const std::shared_ptr<boost::asio::io_service> &io_service, const SUTType &SUT)
      : _sut_type(SUT), _io_service(io_service), _strand(*_io_service),
        _strand_required(false),
        _started(false)
  {
    _state = IEC_61851_States::none_;
    if (io_service == nullptr)
    {
      throw std::invalid_argument("Asio io_service is invalid!");
    }
  }
  BasicSignalling::~BasicSignalling()
  {
    if (0 > callback_cancel(this->gpiod_callback_id))
    {
      SLOGE("Failed to cancel callback");
    }
    pigpio_stop(this->gpiod_pid);
  }

  bool BasicSignalling::start(void)
  {
    // assert(!is_started() && "Basic Signalling module is already started!");
    if (is_started())
    {
      SLOGW("BasicSignal module is already started");
      return false;
    }
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
      this->_started = true;
    }
    else
    {
      this->_started = false;
    }
    return this->_started;
  }

  void BasicSignalling::stop(void)
  {
    if (0 > callback_cancel(this->gpiod_callback_id))
    {
      SLOGE("Failed to cancel calback");
    }
    pigpio_stop(this->gpiod_pid);
    this->_started = false;
  }

  bool BasicSignalling::is_started(void)
  {
    return this->_started;
  }

  void BasicSignalling::set_event_notification(const std::shared_ptr<BasicSignalCallback> &cb)
  {
    // cast shared_ptr of CallbackObject to reference weak ptr > push to list
    this->_event_noti[cb->get_type()].push_back(std::weak_ptr<BasicSignalCallback>(cb));
  }

  void BasicSignalling::clear_event_notification(CallbackType _type)
  {
    this->_event_noti[_type].clear();
  }

  void BasicSignalling::clear_event_notification(const std::shared_ptr<BasicSignalCallback> &cb)
  {
    this->_event_noti[cb->get_type()].remove_if([&cb](std::weak_ptr<BasicSignalCallback> item)
                                                { return (item.lock() == cb); });
  }

  bool BasicSignalling::set_state(IEC_61851_States state)
  {
    bool result = true;
    // State A or the associated voltage level shall be supported, other voltage level is optional
    if (this->_sut_type == SUTType::SECC)
    {
      // State A, B, C and D
      if ((state == A) || (state == B) || (state == C) || (state == D))
      {
        for (size_t i = 0; i < this->RELAYS.size(); i++)
        {
          int value = gpio_write(this->gpiod_pid, this->RELAYS[i], this->STATE_RELAY_MAP[state][i]);
          if (0 > value)
          {
            SLOGE(fmt::format("Failed to write gpio {}", GPIOIF_ERROR[result]));
            result = false;
          }
        }
        this->_state = state;
        SLOGI(fmt::format("Set state {}", STATE_MAP[state]));
      }
      else
      {
        SLOGW("Required state is not supported");
      }
    }
    else
    {
      // State E and F or the associated voltage level shall be supported, other voltage levels are optional.
    }
    return result;
  }

  IEC_61851_States BasicSignalling::get_state(void)
  {
    return this->_state;
  }

  bool BasicSignalling::verify_state(IEC_61851_States state)
  {
    bool result = true;
    // State A or the associated voltage level shall be supported, other voltage level is optional
    if (this->_sut_type == SUTType::SECC)
    {
      // State A, B, C and D
      if ((state == A) || (state == B) || (state == C) || (state == D))
      {
        for (size_t i = 0; i < this->RELAYS.size(); i++)
        {
          int value = gpio_read(this->gpiod_pid, this->RELAYS[i]);
          if (this->STATE_RELAY_MAP[state][i] != value)
          {
            SLOGE(fmt::format("Failed to read gpio {}", GPIOIF_ERROR[result]));
            result = false;
          }
          else
          {
            // nothing
          }
        }
      }
      else
      {
        SLOGW("Required state is not supported");
      }
    }
    else
    {
      // State E and F or the associated voltage level shall be supported, other voltage levels are optional.
    }
    return result;
  }

  bool BasicSignalling::set_error(IEC_61851_ErrStates error_state, bool target_relay_only)
  {
    bool result = true;
    if (!target_relay_only)
    {
      for (size_t i = 0; i < this->RELAYS.size(); i++)
      {
        int value = gpio_write(this->gpiod_pid, this->RELAYS[i], this->ERROR_RELAY_MAP[error_state][i]);
        if (0 > value)
        {
          SLOGE(fmt::format("Failed to write gpio {}", GPIOIF_ERROR[result]));
          result = false;
        }
      }
      SLOGI(fmt::format("Set error state {}", ERROR_MAP[error_state]));
    }
    else
    {
      std::map<IEC_61851_ErrStates, relay_pin_t> target{
          {LOST_CP, RELAY_RES_B},
          {LOST_PE, RELAY_PE_LINE},
          {LOST_DIODE, RELAY_DIODE},
          {SHORT_CP_PE, RELAY_SHORT_CIRCUIT}};
      int value = gpio_write(this->gpiod_pid, target[error_state], relay_val_t::ON);
      if (0 > value)
      {
        SLOGE(fmt::format("Failed to write gpio {}", GPIOIF_ERROR[result]));
        result = false;
      }
    }
    return result;
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

  void BasicSignalling::_notify(CallbackType _type)
  {
    // // loop through all callback register
    for (auto cb = this->_event_noti[_type].begin(); cb != this->_event_noti[_type].end();)
    {
      // check if callback is valid(i.e. register object is still exist)
      if (auto obj_cb = cb->lock())
      {
        (*obj_cb)();
        cb++;
      }
      else
      {
        // clean if callback is not existed
        cb = this->_event_noti[_type].erase(cb);
      }
    }
  }

  static void debounce_filter(const boost::system::error_code &ec,
                              std::atomic<bool> *execute_flag, int pull_type, int pi, uint32_t gpio,
                              BasicSignalling *self, boost::asio::steady_timer *t)
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
        self->_notify(CallbackType::ISR);
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
    (void)tick;
    // timer poll the gpio value each 10us
    // ERROR: could not check self validity > error when BasicSignal object is disposed > self refer to invalid object.
    static boost::asio::steady_timer debounce_timer((*((BasicSignalling *)self)->_io_service), std::chrono::microseconds{5});
    static std::atomic<bool> execute_flag = false;
    // register falling_edge signal of input button pin and timer is not in execution
    if ((gpio == INPUT_BUTTON_PIN) && (execute_flag == false))
    {
      SLOGD(fmt::format("await timer {}", level));
      execute_flag = true;
      debounce_timer.async_wait(boost::bind(debounce_filter, boost::placeholders::_1, &execute_flag, PI_PUD_DOWN, pi, gpio, (BasicSignalling *)self, &debounce_timer));
    }
    else
    {
      // not target gpio
    }
  }

} // namespace TestLib