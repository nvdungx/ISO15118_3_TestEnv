// # required libgpiod-dev libgpiod
#include "boost/asio.hpp"
#include "basic_signal.hpp"
#include "spdlog/spdlog.h"
#include "datatype.hpp"

using namespace TestLib;
using namespace TestLib::DataStructure_HAL_61851;

class ISRCallback: public BasicSignalCallback
{
public:
  ISRCallback():BasicSignalCallback(CallbackType::ISR) {};
  ~ISRCallback() {};
  void operator()() override
  {
    spdlog::info("isr callback");
  }
};
class StateCallback: public BasicSignalCallback
{
public:
  StateCallback():BasicSignalCallback(CallbackType::STATE) {};
  ~StateCallback() {};
  void operator()(IEC_61851_States new_state) override
  {
    (void)new_state;
    spdlog::info("state callback");
  }
};
std::shared_ptr<StateCallback> cb2 = std::make_shared<StateCallback>();
std::shared_ptr<ISRCallback> cb = std::make_shared<ISRCallback>();
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  spdlog::set_level(spdlog::level::level_enum::debug);
  auto io = std::make_shared<boost::asio::io_service>();
  BasicSignalling bc(io, SUTType::SECC);
  bc.start();
  if (bc.is_started())
    spdlog::info("started");
  bc.set_event_notification(cb);
  bc.set_event_notification(cb2);
  bc.clear_event_notification(CallbackType::ISR);
  bc.clear_event_notification(cb2);
  bc.get_freq();
  bc.get_proximity();
  bc.get_pwm();
  bc.get_state();
  bc.set_error(IEC_61851_ErrStates::LOST_CP);
  bc.set_freq(10);
  bc.set_proximity(1);
  bc.set_pwm(1);
  bc.set_state(IEC_61851_States::B);
  bc.stop();
  std::cin.get();
  return 0;
}