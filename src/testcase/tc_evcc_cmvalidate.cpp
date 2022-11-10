#include "testcase/tc_evcc_cmvalidate.hpp"

module TestCases_EVCC_CmValidate
{
import from TestBehavior_EVCC_CmValidate all;
import from TestBehavior_EVCC_CmSlacParm all;
import from TestBehavior_EVCC_CmSlacMatch all;
import from TestBehavior_EVCC_AttenuationCharacterization all;
import from ComponentsAndPorts all;
import from Configurations_15118_3 all;
import from PreConditions_EVCC_15118_3 all;
import from PostConditions_EVCC_15118_3 all;
import from Templates_CMN_CmValidate all;
import from Timer_15118_3 all;
  testcase TC_EVCC_CMN_VTB_CmValidate_001() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmValidate_001(v_HAL_61851_Listener, false,
                                       vc_DutyCycle, fail);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_002() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmValidate_001(v_HAL_61851_Listener, true,
                                       10, fail);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_003() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmValidate_001(v_HAL_61851_Listener, true,
                                       96, fail);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_004() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmValidate_002();
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_005() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmValidate_003(md_CMN_CMN_CmValidateCnf_003('FF' H, '00' H, '01' H));
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_006() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmValidate_003(md_CMN_CMN_CmValidateCnf_003('00' H, 'FF' H, '01' H));
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_007() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var SLAC_Tester2 v_SLAC_Tester2;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
    preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_009());
      var verdicttype testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
      if (testbehaviorVerdict == pass)
      {
        testbehaviorVerdict = f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
      }
      if (testbehaviorVerdict == pass)
      {
        f_EVCC_CMN_TB_VTB_CmValidate_002();
      }
      v_SLAC_Tester2.done;
      if (getverdict == pass)
      {
        setverdict(pass, "SUT has continued the SLAC validation process " &
                             "with the next potential EVSE");
      }
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_008() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var SLAC_Tester2 v_SLAC_Tester2;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
    preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_010(par_cmValidate_result_success));
      var verdicttype testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
      if (testbehaviorVerdict == pass)
      {
        testbehaviorVerdict = f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
      }
      if (testbehaviorVerdict == pass)
      {
        f_EVCC_CMN_TB_VTB_CmValidate_004(par_cmValidate_result_success, true);
      }
      v_SLAC_Tester2.done;
      if (getverdict == pass)
      {
        setverdict(pass, "SUT has continued the SLAC validation process " &
                             "with the next potential EVSE");
      }
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_009() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var SLAC_Tester2 v_SLAC_Tester2;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
    preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_011(v_HAL_61851_Listener));
      var verdicttype testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
      if (testbehaviorVerdict == pass)
      {
        testbehaviorVerdict = f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
      }
      if (testbehaviorVerdict == pass)
      {
        f_EVCC_CMN_TB_VTB_CmValidate_005(v_HAL_61851_Listener);
      }
      v_SLAC_Tester2.done;
      if (getverdict == pass)
      {
        setverdict(pass, "SUT has continued the SLAC validation process " &
                             "with the next potential EVSE");
      }
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_010() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var SLAC_Tester2 v_SLAC_Tester2;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
    preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_012(v_HAL_61851_Listener,
                                                            par_cmValidate_result_failure));
      var verdicttype testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
      if (testbehaviorVerdict == pass)
      {
        testbehaviorVerdict = f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
      }
      if (testbehaviorVerdict == pass)
      {
        f_EVCC_CMN_TB_VTB_CmValidate_006(v_HAL_61851_Listener,
                                         par_cmValidate_result_failure);
      }
      v_SLAC_Tester2.done;
      if (getverdict == pass)
      {
        setverdict(pass, "SUT has continued the SLAC validation process " &
                             "with the next potential EVSE");
      }
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_011() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var SLAC_Tester2 v_SLAC_Tester2;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
    preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_012(v_HAL_61851_Listener,
                                                            par_cmValidate_result_notReady));
      var verdicttype testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
      if (testbehaviorVerdict == pass)
      {
        testbehaviorVerdict = f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
      }
      if (testbehaviorVerdict == pass)
      {
        f_EVCC_CMN_TB_VTB_CmValidate_006(v_HAL_61851_Listener,
                                         par_cmValidate_result_notReady);
      }
      v_SLAC_Tester2.done;
      if (getverdict == pass)
      {
        setverdict(pass, "SUT has continued the SLAC validation process " &
                             "with the next potential EVSE");
      }
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_012() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var SLAC_Tester2 v_SLAC_Tester2;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
    preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_012(v_HAL_61851_Listener,
                                                            par_cmValidate_result_notRequired));
      var verdicttype testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
      if (testbehaviorVerdict == pass)
      {
        testbehaviorVerdict = f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
      }
      if (testbehaviorVerdict == pass)
      {
        f_EVCC_CMN_TB_VTB_CmValidate_006(v_HAL_61851_Listener,
                                         par_cmValidate_result_notRequired);
      }
      v_SLAC_Tester2.done;
      if (getverdict == pass)
      {
        setverdict(pass, "SUT has continued the SLAC validation process " &
                             "with the next potential EVSE");
      }
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_013() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var SLAC_Tester2 v_SLAC_Tester2;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
    preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_010(par_cmValidate_result_failure));
      var verdicttype testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
      if (testbehaviorVerdict == pass)
      {
        testbehaviorVerdict = f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
      }
      if (testbehaviorVerdict == pass)
      {
        f_EVCC_CMN_TB_VTB_CmValidate_004(par_cmValidate_result_failure, true);
      }
      v_SLAC_Tester2.done;
      if (getverdict == pass)
      {
        setverdict(pass, "SUT has continued the SLAC validation process " &
                             "with the next potential EVSE");
      }
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_014() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmValidate_004(par_cmValidate_result_failure, true);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_015() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmValidate_004(par_cmValidate_result_failure, false);
      if (getverdict == pass)
      {
        f_EVCC_CMN_TB_VTB_CmSlacMatch_001();
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
  testcase TC_EVCC_CMN_VTB_CmValidate_016() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmValidate_007();
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_017() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmValidate_004(par_cmValidate_result_notRequired, false);
      if (getverdict == pass)
      {
        f_EVCC_CMN_TB_VTB_CmSlacMatch_001();
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
  testcase TC_EVCC_CMN_VTB_CmValidate_018() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmValidate_008();
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_019() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var SLAC_Tester2 v_SLAC_Tester2;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
    preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_010(par_cmValidate_result_notReady));
      var verdicttype testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
      if (testbehaviorVerdict == pass)
      {
        testbehaviorVerdict = f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
      }
      if (testbehaviorVerdict == pass)
      {
        f_EVCC_CMN_TB_VTB_CmValidate_004(par_cmValidate_result_notReady, true);
      }
      v_SLAC_Tester2.done;
      if (getverdict == pass)
      {
        setverdict(pass, "SUT has continued the SLAC validation process " &
                             "with the next potential EVSE");
      }
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_020() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmValidate_013(e_OscOff);
    }
    else
    {
      log("PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  }
  testcase TC_EVCC_CMN_VTB_CmValidate_021() runs on EVCC_Tester system SystemEVCC
  {
    var HAL_61851_Listener v_HAL_61851_Listener;
    var verdicttype preConVerdict;
    // -------------- Pre Conditions-------------------------------------------------------
    f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
    preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_CmValidate_013(e_NegVolt12);
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