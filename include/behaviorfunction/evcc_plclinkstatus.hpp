#ifndef __EVCC_PLCLINKSTATUS_H__
#define __EVCC_PLCLINKSTATUS_H__
#include "datatype.hpp"

namespace TestLib {
namespace TestBehavior_EVCC_PLCLinkStatus
{
  extern VerdictValue f_EVCC_CMN_TB_VTB_PLCLinkStatus_001(VerdictValue v_vct);
  extern VerdictValue f_EVCC_CMN_TB_VTB_PLCLinkStatus_002(void);
  extern VerdictValue f_EVCC_CMN_TB_VTB_PLCLinkStatus_003(HAL_61851_PwmMode_Type pwmMode);
  extern VerdictValue f_EVCC_CMN_TB_VTB_PLCLinkStatus_004(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener);
  extern VerdictValue f_EVCC_CMN_TB_VTB_PLCLinkStatus_005(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener, float v_time);
  extern VerdictValue f_EVCC_CMN_TB_VTB_PLCLinkStatus_006(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener, integer v_dutyCycle, IEC_61851_States v_state);
  extern VerdictValue f_EVCC_CMN_TB_VTB_PLCLinkStatus_007(void);
  extern VerdictValue f_EVCC_CMN_TB_VTB_PLCLinkStatus_008(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener);
  extern VerdictValue f_EVCC_AC_TB_VTB_PLCLinkStatus_001(void);
  extern VerdictValue f_EVCC_AC_TB_VTB_PLCLinkStatus_002(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener, IEC_61851_States v_state);
} // namespace TestBehavior_EVCC_PLCLinkStatus
}
#endif // __EVCC_PLCLINKSTATUS_H__