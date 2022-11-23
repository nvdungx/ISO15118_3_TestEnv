#ifndef __EVCC_ATTENUATIONCHARACTERIZATION_H__
#define __EVCC_ATTENUATIONCHARACTERIZATION_H__
#include "datatype.hpp"
#include "slac_type.hpp"

namespace TestLib
{
namespace TestBehavior_EVCC_AttenuationCharacterization
{
  extern VerdictValue f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(VerdictValue v_vct);
  extern VerdictValue f_EVCC_CMN_TB_VTB_AttenuationCharacterization_002(void);
  extern VerdictValue f_EVCC_CMN_TB_VTB_AttenuationCharacterization_003(void);
  extern VerdictValue f_EVCC_CMN_TB_VTB_AttenuationCharacterization_004(void);
  extern VerdictValue f_EVCC_CMN_TB_VTB_AttenuationCharacterization_005(const MME_Payload &v_payload);
  extern VerdictValue f_EVCC_CMN_TB_VTB_AttenuationCharacterization_006(HAL_61851_PwmMode_Type pwmMode);
  extern VerdictValue f_EVCC_AC_TB_VTB_AttenuationCharacterization_001(integer v_dutcCycle);
} // namespace TestBehavior_EVCC_AttenuationCharacterization
}
#endif // __EVCC_ATTENUATIONCHARACTERIZATION_H__