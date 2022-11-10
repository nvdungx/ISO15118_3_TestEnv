#include "testcase/tc_secc_cmvalidate.hpp"

module TestCases_SECC_CmValidate
{
import from TestBehavior_SECC_CmValidate all;
import from TestBehavior_SECC_CmSlacMatch all;
import from ComponentsAndPorts all;
import from Configurations_15118_3 all;
import from PreConditions_SECC_15118_3 all;
import from PostConditions_SECC_15118_3 all;
import from Templates_CMN_CmValidate all;
import from Timer_15118_3 all;
  testcase TC_SECC_CMN_VTB_CmValidate_001() runs on SECC_Tester system SystemSECC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmValidate_001(v_HAL_61851_Listener, fail);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmValidate_002() runs on SECC_Tester system SystemSECC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmValidate_002();
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmValidate_003() runs on SECC_Tester system SystemSECC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmValidate_003(v_HAL_61851_Listener);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmValidate_004() runs on SECC_Tester system SystemSECC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      var hexstring v_pilotTimer = int2hex(float2int((par_TP_EV_vald_toggle * 10.0) - 1.0), 2);
      f_SECC_CMN_TB_VTB_CmValidate_004(v_HAL_61851_Listener,
                                       md_CMN_CMN_CmValidateReq_004(
                                           'FF' H, v_pilotTimer, '01' H));
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmValidate_005() runs on SECC_Tester system SystemSECC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      var hexstring v_pilotTimer = int2hex(float2int((par_TP_EV_vald_toggle * 10.0) - 1.0), 2);
      f_SECC_CMN_TB_VTB_CmValidate_005(md_CMN_CMN_CmValidateReq_004(
          '00' H, v_pilotTimer,
          par_cmValidate_result_notReady));
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmValidate_006() runs on SECC_Tester system SystemSECC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      var hexstring v_pilotTimer = int2hex(float2int((par_TP_EV_vald_toggle * 10.0) - 1.0), 2);
      f_SECC_CMN_TB_VTB_CmValidate_005(md_CMN_CMN_CmValidateReq_004(
          '00' H, v_pilotTimer,
          par_cmValidate_result_success));
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmValidate_007() runs on SECC_Tester system SystemSECC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      var hexstring v_pilotTimer = int2hex(float2int((par_TP_EV_vald_toggle * 10.0) - 1.0), 2);
      f_SECC_CMN_TB_VTB_CmValidate_005(md_CMN_CMN_CmValidateReq_004(
          '00' H, v_pilotTimer,
          par_cmValidate_result_failure));
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmValidate_008() runs on SECC_Tester system SystemSECC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      var hexstring v_pilotTimer = int2hex(float2int((par_TP_EV_vald_toggle * 10.0) - 1.0), 2);
      f_SECC_CMN_TB_VTB_CmValidate_005(md_CMN_CMN_CmValidateReq_004(
          '00' H, v_pilotTimer,
          par_cmValidate_result_notRequired));
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_SECC_CMN_VTB_CmValidate_009() runs on SECC_Tester system SystemSECC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var SLAC_Tester2 v_SLAC_Tester2;
    var SLAC_Tester3 v_SLAC_Tester3;
    var SLAC_Tester4 v_SLAC_Tester4;
    var SLAC_Tester5 v_SLAC_Tester5;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2,
                                             v_SLAC_Tester3, v_SLAC_Tester4,
                                             v_SLAC_Tester5, system);
    preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    if (preConVerdict == pass)
    {
      tc_TP_EVSE_match_session.start(par_TT_EVSE_match_session);
      v_SLAC_Tester2.start(f_SECC_CMN_TB_VTB_CmValidatePreCondition_001());
      v_SLAC_Tester2.done;
    }
    //-------------- Test behavior---------------------------------------------------------
    if (getverdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmValidate_006();
      if (getverdict == pass)
      {
        v_SLAC_Tester2.start(f_SECC_CMN_TB_VTB_CmValidate_009());
        f_SECC_CMN_TB_VTB_CmValidate_007(v_HAL_61851_Listener);
        v_SLAC_Tester2.done;
      }
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_SECC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2,
                                                 v_SLAC_Tester3, v_SLAC_Tester4,
                                                 v_SLAC_Tester5, system);
  }
  testcase TC_SECC_CMN_VTB_CmValidate_010() runs on SECC_Tester system SystemSECC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmValidate_008(par_cmValidate_result_failure);
      if (getverdict == pass)
      {
        setverdict(pass, "CM_VALIDATE.CNF message with 'failure' is correct. " &
                             "SUT is not able to perform any BCB-Toggle.");
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
  testcase TC_SECC_CMN_VTB_CmValidate_011() runs on SECC_Tester system SystemSECC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmValidate_008(par_cmValidate_result_notRequired);
      setverdict(pass, "CM_VALIDATE.CNF message with 'notRequired' is correct. " &
                           "SUT has indicated that a validation is not required.");
      if (getverdict == pass)
      {
        f_SECC_CMN_TB_VTB_CmValidate_007(v_HAL_61851_Listener);
        if (getverdict == pass)
        {
          setverdict(pass, "SUT has finished the validation process.");
        }
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
  testcase TC_SECC_CMN_VTB_CmValidate_012() runs on SECC_Tester system SystemSECC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmValidate_008(par_cmValidate_result_notRequired);
      setverdict(pass, "CM_VALIDATE.CNF message with 'notRequired' is correct. " &
                           "SUT has indicated that a validation is not required.");
      if (getverdict == pass)
      {
        f_SECC_CMN_TB_VTB_CmSlacMatch_001(fail);
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
  testcase TC_SECC_CMN_VTB_CmValidate_013() runs on SECC_Tester system SystemSECC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmValidate_010(v_HAL_61851_Listener);
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