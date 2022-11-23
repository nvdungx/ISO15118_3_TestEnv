#ifndef __PRECONDITIONS_H__
#define __PRECONDITIONS_H__

#include "datatype.hpp"
#include "execution/paralleltestcomponent.hpp"

namespace TestLib
{
namespace PreConditions_SECC_15118_3
{
  VerdictValue f_SECC_CMN_PR_StateA_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_SECC_CMN_PR_DisconnectDataLink_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_SECC_CMN_PR_SetProximityPilot_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_SECC_CMN_PR_StateB_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_SECC_CMN_PR_CmSlacParm_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_SECC_CMN_PR_AttenuationCharacterization_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_SECC_CMN_PR_CmValidate_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_SECC_CMN_PR_CmSlacMatch_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_SECC_CMN_PR_CmSetKey_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_SECC_CMN_PR_PLCLinkStatus_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_SECC_CMN_PR_CmAmpMap_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
} // namespace PreConditions_SECC_15118_3

namespace PreConditions_EVCC_15118_3
{
  VerdictValue f_EVCC_CMN_PR_SetPowerFlowConfiguration_001(void);
  VerdictValue f_EVCC_CMN_PR_DisableControlPilot_001(void);
  VerdictValue f_EVCC_CMN_PR_CmSetKey_001(void);
  VerdictValue f_EVCC_CMN_PR_SetProximityPilot_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_EVCC_CMN_PR_EnableControlPilot_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_EVCC_CMN_PR_StateB_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_EVCC_CMN_PR_DutyCycle_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_EVCC_CMN_PR_CmSlacParm_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_EVCC_CMN_PR_AttenuationCharacterization_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_EVCC_CMN_PR_CmValidate_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_EVCC_CMN_PR_PLCLinkStatus_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  VerdictValue f_EVCC_CMN_PR_CmAmpMap_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
} // namespace PreConditions_EVCC_15118_3
} // namespace TestLib


#endif // __PRECONDITIONS_H__