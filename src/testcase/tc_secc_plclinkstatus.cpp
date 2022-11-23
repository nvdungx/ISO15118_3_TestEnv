#include "testcase/tc_secc_plclinkstatus.hpp"

#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)
namespace TestCases_SECC_CmAmpMap
{
// import from DataStructure_SLAC all;
// import from TestBehavior_SECC_CmAmpMap all;
// import from TestBehavior_SECC_PLCLinkStatus all;
// import from ComponentsAndPorts all;
// import from Configurations_15118_3 all;
// import from PreConditions_SECC_15118_3 all;
// import from Timer_15118_3 all;
// import from PostConditions_SECC_15118_3 all;
// import from Services_TXPowerLimitation all;
VerdictValue TC_SECC_CMN_VTB_CmAmpMap_001(void); // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmAmpMap_001(fail);
    if (getverdict == pass)
    {
      f_SECC_CMN_checkTXPowerLimitation();
    }
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmAmpMap_002(void); // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmAmpMap_002(fail);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmAmpMap_003(void); // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmAmpMap_003();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmAmpMap_004(void); // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmAmpMap_004();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmAmpMap_005(void); // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmAmpMap_005();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmAmpMap_006(void); // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmAmpMap_006();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmAmpMap_007(void); // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmAmpMap_007();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmAmpMap_008(void); // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmAmpMap_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmAmpMap_008();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
} // namespace TestCases_SECC_CmAmpMap