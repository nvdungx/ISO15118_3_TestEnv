#include "testcase/tc_secc_plclinkstatus.hpp"

module TestCases_SECC_CmAmpMap
{
import from DataStructure_SLAC all;
import from TestBehavior_SECC_CmAmpMap all;
import from TestBehavior_SECC_PLCLinkStatus all;
import from ComponentsAndPorts all;
import from Configurations_15118_3 all;
import from PreConditions_SECC_15118_3 all;
import from Timer_15118_3 all;
import from PostConditions_SECC_15118_3 all;
import from Services_TXPowerLimitation all;
  testcase TC_SECC_CMN_VTB_CmAmpMap_001() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
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
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmAmpMap_002() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
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
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmAmpMap_003() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
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
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmAmpMap_004() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
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
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmAmpMap_005() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
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
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmAmpMap_006() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
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
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmAmpMap_007() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
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
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmAmpMap_008() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
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
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
}