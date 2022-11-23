#ifndef __EVCC_CMVALIDATE_H__
#define __EVCC_CMVALIDATE_H__
#include "datatype.hpp"
#include "slac_type.hpp"

namespace TestLib {
namespace TestBehavior_EVCC_CmValidate
{
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_001(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, boolean v_changeDC, integer v_dutyCycle, VerdictValue v_vct);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_002(void);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_003(const MME_Payload &v_validateCnf);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_004(hexstring v_resultCode, boolean v_isRepeat);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_005(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_006(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, hexstring v_resultCode);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_007(void);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_008(void);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_009(void);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_010(hexstring v_resultCode);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_011(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_012(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, hexstring v_resultCode);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_013(HAL_61851_PwmMode_Type pwmMode);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmValidatePreCondition_001(void);
} // namespace TestBehavior_EVCC_CmValidate
}
#endif // __EVCC_CMVALIDATE_H__