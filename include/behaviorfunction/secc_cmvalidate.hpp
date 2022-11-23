#ifndef __SECC_CMVALIDATE_H__
#define __SECC_CMVALIDATE_H__
#include "datatype.hpp"
#include "slac_type.hpp"

namespace TestLib {
namespace TestBehavior_SECC_CmValidate
{
  extern VerdictValue f_SECC_CMN_TB_VTB_CmValidate_001(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener, VerdictValue v_vct);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmValidate_002(void);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmValidate_003(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmValidate_004(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener, const MME_Payload &mmePayload);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmValidate_005(const MME_Payload &mmePayload);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmValidate_006(void);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmValidate_007(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmValidate_008(Result_TYPE p_result);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmValidate_009(void);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmValidate_010(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmValidatePreCondition_001(void);
} // namespace TestBehavior_SECC_CmValidate
}
#endif // __SECC_CMVALIDATE_H__