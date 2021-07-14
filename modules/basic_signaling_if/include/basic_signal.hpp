#ifndef __BASIC_SIGNAL_H__
#define __BASIC_SIGNAL_H__

#include <unordered_map>
#include <list>
#include <memory>
#include <boost/asio.hpp>
#include "datatype.hpp"

using namespace DataStructure_HAL_61851;

// The parallel test component (PTC) for IEC 61851‐1 signaling continuously observes
// positive voltage (state), frequency, duty cycle and the proximity resistor value

// call‐back function which reports change events of the current PWM state

class BasicSignalling : public std::enable_shared_from_this<BasicSignalling>
{
private:
  int gpiod_pid;
  int gpiod_callback_id;
  // type of SUT (corresponding control state available)
  SUTType _sut_type;
  // map of callback type and registed callback list from upper layer (weak_ptr)
  std::unordered_map<CallbackType, std::list<std::weak_ptr<BasicSignalCallback>>> _event_noti;
  // Asio IO service
  std::shared_ptr<boost::asio::io_service> _io_service;
  // Asio service strand for serialized handler execution
  boost::asio::io_service::strand _strand;
  bool _strand_required;
  std::atomic<bool> _started;
public:
  BasicSignalling(const std::shared_ptr<boost::asio::io_service> &io_service, const SUTType &SUT);
  ~BasicSignalling();
  // common
  bool start(void);
  // common
  void stop(void);
  // common
  bool is_started(void);

  void set_event_notification(const std::shared_ptr<BasicSignalCallback>& cb);

  // set the current PWM state or associated voltage level.
  // SECC SUT: State B, C and D or the associated voltage level shall be supported, other voltage level are optional
  // EVCC SUT: State E and F or the associated voltage level shall be supported, other voltage levels are optional.
  // EVCC SUT: switch on/off the ControlPilot Line to simulate an un‐plug or plug‐in for the SUT.
  //            State A or the associated voltage level shall be supported, other voltage level is optional
  bool set_state(IEC_61851_States state);
  // CMN: get the current PWM state or associated voltage level.
  IEC_61851_States get_state(void);
  // CMN: call‐back function which reports change events of the current PWM state or associated voltage level.

  bool set_error(IEC_61851_ErrStates error_state);

  // CMN: set the proximity on SUT side.
  void set_proximity(uint32_t value);
  // CMN: get the proximity resistor value from SUT side
  uint32_t get_proximity(void);
  // CMN: call‐back function which reports change events of the resistor value for the proximity from SUT side.

  // EVCC SUT: set the current duty cycle in [%]. The values 5 %, and 7 %‐98 % shall be supported, other values are optional.
  void set_pwm(uint32_t duty);
  // CMN: get the duty cycle in [%].
  uint32_t get_pwm(void);
  // CMN: call‐back function which reports changes of the duty cycle in [%].

  // EVCC SUT: set current frequency in [Hz]. A value of 1 000 Hz +/‐ 5 % shall be supported, other values are optional.
  void set_freq(uint32_t freq);
  // CMN: get the frequency in [Hz].
  uint32_t get_freq(void);
  // CMN: call‐back function which reports change events of the frequency in [Hz]

  void _notify_btn_isr(void);
private:
  bool verify_state(IEC_61851_States state);
  void temp_call();
  static void btn_isr(int pi, uint32_t gpio, uint32_t level, uint32_t tick, void *self);

private:
  typedef enum en_relay_pin_t
  {
    RELAY_PE_LINE = 26,      // PE line, ON = connect/ OFF = disconnect
    RELAY_SHORT_CIRCUIT = 0, // short circuit, ON = no short/ OFF short
    RELAY_DIODE = 5,         // diode line, ON = has diode/ OFF no diode
    RELAY_RES_B = 6,         // resistor value to state B
    RELAY_RES_C = 13,        // resistor value to state C (need RES_B connect)
    RELAY_RES_D = 19         // resistor  value to state D (need RES_B and RES_C)
  } relay_pin_t;
  typedef enum en_relay_val_t
  {
    OFF = 0,
    ON
  } relay_val_t;
#define INPUT_BUTTON_PIN 21
#define NUM_STATE 6
#define NUM_RELAY 6
  const std::vector<uint32_t> RELAYS{RELAY_PE_LINE, RELAY_RES_B, RELAY_RES_C, RELAY_RES_D, RELAY_DIODE, RELAY_SHORT_CIRCUIT};
  const relay_val_t STATE_RELAY_MAP[NUM_STATE][NUM_RELAY] = {
          // PE    B     C    D     DIODE  SH
      [A] = {OFF,  OFF,  OFF, OFF,  OFF,   OFF},
      [B] = {ON,   ON,   OFF, OFF,  OFF,   OFF},
      [C] = {ON,   ON,   ON,  OFF,  OFF,   OFF},
      [D] = {ON,   ON,   OFF, ON,   OFF,   OFF},
      [E] = {ON,   ON,   OFF, OFF,  OFF,   ON },
      [F] = {OFF,  OFF,  OFF, OFF,  OFF,   OFF}
    };
};

#endif // __BASIC_SIGNAL_H__
