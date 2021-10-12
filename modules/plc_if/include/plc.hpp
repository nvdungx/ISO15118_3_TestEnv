#ifndef __PLC_H__
#define __PLC_H__

#include <boost/asio.hpp>
#include <string>
#include "datatype.hpp"
namespace TestLib {

/* raw socket on qca7000 interface(OSI Layer 2) */
class Channel {
  #define ETHER_ADDR_LEN 6
  boost::asio::generic::raw_protocol::socket socket;
  std::string ifname;
  uint8_t mac[ETHER_ADDR_LEN];

  bool init(void);
  bool open(void);
  bool close(void);

};


/* HomePlug GreenPHY PowerLineCommunication
The data link control ServiceAccessPoint provides link status information, error information,
control functionality and is located between the connection coordination and higher layers. */
class HPGPSta
{
private:
  /* data */
public:
  HPGPSta() {}
  ~HPGPSta() {}


  /* [V2G5-031] The service function for data link status control shall
  provide a mean to check if the PLC link can be established within TT_match_join. */
  /* EV, EVSE: D-LINK_READY.indication shall inform higher layers about a change of communication link status.*/
  DLinkStatusType dlink_get_status(void);

  /* [V2G5-032] The service function for data link status control shall provide
  a mean to check if the PLC link will be terminated within TP_match_leave. */
  /* EV, EVSE: D-LINK_TERMINATE.request requests lower layers to terminate the data link. */
  bool dlink_terminate(void);

  /* EVSE: D-LINK_ERROR.request requests lower layers to terminate the data link and restart the matching
  process by a control pilot transition through state E. */
  bool dlink_get_error(void);

  /* EV, EVSE: D-LINK_PAUSE.request requests lower layers to enter a power saving mode.
  While being in this   mode, the state will be kept to “Matched”. */
  bool dlink_pause(void);

  /* [V2G5-037] The service function for attenuator injection shall provide a mean
  to inject an RF attenuator on the control pilot, effective for the frequency band 2 MHz to 30 MHz.*/
  // attenuator injection for SECC testing

  /* [V2G5-036] The service function for transmission power limitation shall
  provide a mean to check notched carriers in the frequency band
  2 MHz to 30 MHz after a requested amplitude map exchange. */
  // transmission power limitation for EVCC or SECC testing
};

} // namespace TestLib
#endif // __PLC_H__