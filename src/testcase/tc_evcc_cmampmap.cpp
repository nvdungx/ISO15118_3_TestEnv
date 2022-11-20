#include "testcase/tc_evcc_cmampmap.hpp"

module TestCases_EVCC_CmAmpMap
{
import from DataStructure_SLAC all;
import from TestBehavior_EVCC_CmAmpMap all;
import from TestBehavior_EVCC_PLCLinkStatus all;
import from ComponentsAndPorts all;
import from Configurations_15118_3 all;
import from PreConditions_EVCC_15118_3 all;
import from Timer_15118_3 all;
import from PostConditions_EVCC_15118_3 all;
import from Services_TXPowerLimitation all;
  testcase TC_EVCC_CMN_VTB_CmAmpMap_001() runs on EVCC_Tester system SystemEVCC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmAmpMap_001(fail);
      if (getverdict == pass)
      {
        f_EVCC_CMN_checkTXPowerLimitation();
      }
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmAmpMap_002() runs on EVCC_Tester system SystemEVCC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmAmpMap_002(fail);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmAmpMap_003() runs on EVCC_Tester system SystemEVCC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmAmpMap_003();
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmAmpMap_004() runs on EVCC_Tester system SystemEVCC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmAmpMap_004();
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmAmpMap_005() runs on EVCC_Tester system SystemEVCC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmAmpMap_005();
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmAmpMap_006() runs on EVCC_Tester system SystemEVCC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmAmpMap_006();
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmAmpMap_007() runs on EVCC_Tester system SystemEVCC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmAmpMap_007();
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmAmpMap_008() runs on EVCC_Tester system SystemEVCC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_CmAmpMap_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmAmpMap_008();
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
}