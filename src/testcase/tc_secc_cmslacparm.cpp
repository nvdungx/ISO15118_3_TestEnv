#include "testcase/tc_secc_cmslacparm.hpp"

module TestCases_SECC_CmSlacParm
{
import from DataStructure_SLAC all;
import from TestBehavior_SECC_CmSlacParm all;
import from TestBehavior_SECC_AttenuationCharacterization all;
import from TestBehavior_SECC_CmSlacMatch all;
import from TestBehavior_SECC_CmSetKey all;
import from TestBehavior_SECC_PLCLinkStatus all;
import from TestBehavior_SECC_CmValidate all;
import from ComponentsAndPorts all;
import from Configurations_15118_3 all;
import from PreConditions_SECC_15118_3 all;
import from PostConditions_SECC_15118_3 all;
import from Timer_15118_3 all;
import from Pixit_15118_3 all;
import from Templates_CMN_SlacPayloadHeader all;
  testcase TC_SECC_CMN_VTB_CmSlacParm_001() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmSlacParm_001(fail);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmSlacParm_002() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    vc_state = C;
    preConVerdict = f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmSlacParm_001(fail);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmSlacParm_003() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    vc_state = D;
    preConVerdict = f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmSlacParm_001(fail);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmSlacParm_004() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmSlacParm_002(v_HAL_61851_Listener, omit, false);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmSlacParm_005() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmSlacParm_002(v_HAL_61851_Listener,
                                       m_CMN_CMN_SlacPayloadHeaderInvalid_001(), true);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmSlacParm_006() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmSlacParm_002(v_HAL_61851_Listener,
                                       m_CMN_CMN_SlacPayloadHeaderInvalid_002(), true);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmSlacParm_007() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmSlacParm_003(v_HAL_61851_Listener);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmSlacParm_008() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    vc_sleepAfterPlugOut = true;
    preConVerdict = f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmSlacParm_004();
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmSlacParm_009() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    vc_sleepAfterPlugOut = true;
    preConVerdict = f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmSlacParm_005(v_HAL_61851_Listener);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_AC_VTB_CmSlacParm_001() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    verdicttype verdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    vc_activateNominal = false;
    vc_testCaseSpecific = true;
    preConVerdict = f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      verdict = f_SECC_AC_TB_VTB_CmSlacParm_001(v_HAL_61851_Listener);
      if (verdict == pass)
      {
        verdict = f_SECC_CMN_TB_VTB_CmSlacParm_001(fail);
      }
      if (verdict == pass)
      {
        verdict = f_SECC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
      }
      if (PIXIT_SECC_CMN_CmValidate == cmValidate)
      {
        verdict = f_SECC_CMN_TB_VTB_CmValidate_001(v_HAL_61851_Listener, fail);
      }
      if (verdict == pass)
      {
        verdict = f_SECC_CMN_TB_VTB_CmSlacMatch_001(fail);
      }
      if (verdict == pass)
      {
        tc_TT_match_join.start(par_TT_match_join);
        verdict = f_SECC_CMN_TB_VTB_CmSetKey_001(false);
      }
      if (verdict == pass)
      {
        verdict = f_SECC_CMN_TB_VTB_PLCLinkStatus_001(fail);
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
  testcase TC_SECC_AC_VTB_CmSlacParm_002() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    vc_activateNominal = false;
    preConVerdict = f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_AC_TB_VTB_CmSlacParm_002(v_HAL_61851_Listener);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_AC_VTB_CmSlacParm_003() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    verdicttype verdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    vc_testCaseSpecific = true;
    preConVerdict = f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      verdict = f_SECC_AC_TB_VTB_CmSlacParm_001(v_HAL_61851_Listener);
      if (verdict == pass)
      {
        verdict = f_SECC_CMN_TB_VTB_CmSlacParm_001(fail);
      }
      if (verdict == pass)
      {
        verdict = f_SECC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
      }
      if (PIXIT_SECC_CMN_CmValidate == cmValidate)
      {
        verdict = f_SECC_CMN_TB_VTB_CmValidate_001(v_HAL_61851_Listener, fail);
      }
      if (verdict == pass)
      {
        verdict = f_SECC_CMN_TB_VTB_CmSlacMatch_001(fail);
      }
      if (verdict == pass)
      {
        tc_TT_match_join.start(par_TT_match_join);
        verdict = f_SECC_CMN_TB_VTB_CmSetKey_001(false);
      }
      if (verdict == pass)
      {
        verdict = f_SECC_CMN_TB_VTB_PLCLinkStatus_001(fail);
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
  testcase TC_SECC_AC_VTB_CmSlacParm_004() runs on SECC_Tester system SystemSECC
  {
    HAL_61851_Listener v_HAL_61851_Listener;
    verdicttype preConVerdict;
    verdicttype verdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    vc_testCaseSpecific = true;
    preConVerdict = f_SECC_CMN_PR_SetProximityPilot_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      verdict = f_SECC_AC_TB_VTB_CmSlacParm_003(v_HAL_61851_Listener);
      if (verdict == pass)
      {
        verdict = f_SECC_CMN_TB_VTB_CmSlacParm_001(fail);
      }
      if (verdict == pass)
      {
        verdict = f_SECC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
      }
      if (PIXIT_SECC_CMN_CmValidate == cmValidate)
      {
        verdict = f_SECC_CMN_TB_VTB_CmValidate_001(v_HAL_61851_Listener, fail);
      }
      if (verdict == pass)
      {
        verdict = f_SECC_CMN_TB_VTB_CmSlacMatch_001(fail);
      }
      if (verdict == pass)
      {
        tc_TT_match_join.start(par_TT_match_join);
        verdict = f_SECC_CMN_TB_VTB_CmSetKey_001(false);
      }
      if (verdict == pass)
      {
        verdict = f_SECC_CMN_TB_VTB_PLCLinkStatus_001(fail);
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
}