#ifndef __SECC_ATTENUATIONCHARACTERIZATION_H__
#define __SECC_ATTENUATIONCHARACTERIZATION_H__
#include "datatype.hpp"
#include "slac_type.hpp"

namespace TestLib {
namespace TestBehavior_SECC_AttenuationCharacterization
{
  extern VerdictValue f_SECC_CMN_setMac(const MME &v_responseMessage, const MACAddress_TYPE &v_sut_mac_temp);
  extern VerdictValue f_SECC_CMN_TB_VTB_AttenuationCharacterization_001(VerdictValue v_vct);
  extern VerdictValue f_SECC_CMN_TB_VTB_AttenuationCharacterization_002(void);
  extern VerdictValue f_SECC_CMN_TB_VTB_AttenuationCharacterization_003(integer n);
  extern VerdictValue f_SECC_CMN_TB_VTB_AttenuationCharacterization_004(void);
  extern VerdictValue f_SECC_CMN_TB_VTB_AttenuationCharacterization_005(const SLAC_Header &payloadHeader, const Acvarfield_Type &acvarfield);
  extern VerdictValue f_SECC_CMN_TB_VTB_AttenuationCharacterization_006(void);
  extern VerdictValue f_SECC_CMN_TB_VTB_AttenuationCharacterization_007(const MME_Payload &v_payload);
  extern VerdictValue f_SECC_CMN_TB_VTB_AttenuationCharacterization_008(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener);
  extern VerdictValue f_SECC_CMN_TB_VTB_AttenuationCharacterization_009(const MACAddress_TYPE &v_macAddress);
  extern VerdictValue f_SECC_CMN_Reset_001(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener);
  extern VerdictValue f_SECC_CMN_compareAttenuationValues_001(const AttenProfile_TYPE &v_attenuation_list1, const AttenProfile_TYPE &v_attenuation_list2);
} // namespace TestBehavior_SECC_AttenuationCharacterization
}
#endif // __SECC_ATTENUATIONCHARACTERIZATION_H__