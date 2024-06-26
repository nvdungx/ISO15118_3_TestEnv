#include "testcase/tc_evcc_cmvalidateorcmslacmatch.hpp"

#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)
namespace TestCases_EVCC_CmValidateOrCmSlacMatch
{
// import from DataStructure_SLAC all;
// import from TestBehavior_EVCC_AttenuationCharacterization all;
// import from TestBehavior_EVCC_CmValidateOrCmSlacMatch all;
// import from ComponentsAndPorts all;
// import from Configurations_15118_3 all;
// import from Timer_15118_3 all;
// import from PreConditions_EVCC_15118_3 all;
// import from PostConditions_EVCC_15118_3 all;
// import from Templates_CMN_CmSlacMatch all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from TestBehavior_EVCC_AttenuationCharacterization all;
// import from TestBehavior_EVCC_CmSlacParm all;

VerdictValue TC_EVCC_CMN_VTB_CmValidateOrCmSlacMatch_001(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener, fail);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
} // namespace TestCases_EVCC_CmValidateOrCmSlacMatch