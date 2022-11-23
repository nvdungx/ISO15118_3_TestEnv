#include "testcase/tc_evcc_cmvalidate.hpp"

#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)
namespace TestCases_EVCC_CmValidate
{
// import from TestBehavior_EVCC_CmValidate all;
// import from TestBehavior_EVCC_CmSlacParm all;
// import from TestBehavior_EVCC_CmSlacMatch all;
// import from TestBehavior_EVCC_AttenuationCharacterization all;
// import from ComponentsAndPorts all;
// import from Configurations_15118_3 all;
// import from PreConditions_EVCC_15118_3 all;
// import from PostConditions_EVCC_15118_3 all;
// import from Templates_CMN_CmValidate all;
// import from Timer_15118_3 all;
VerdictValue TC_EVCC_CMN_VTB_CmValidate_001(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_002(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_003(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_004(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_005(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmValidate_003(md_CMN_CMN_CmValidateCnf_003("FF", "00", "01"));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_006(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmValidate_003(md_CMN_CMN_CmValidateCnf_003("00", "FF", "01"));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_007(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  SLAC_Tester2 v_SLAC_Tester2;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_009());
    VerdictValue testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_008(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  SLAC_Tester2 v_SLAC_Tester2;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_010(par_cmValidate_result_success));
    VerdictValue testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_009(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  SLAC_Tester2 v_SLAC_Tester2;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_011(v_HAL_61851_Listener));
    VerdictValue testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_010(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  SLAC_Tester2 v_SLAC_Tester2;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_012(v_HAL_61851_Listener,
                                                          par_cmValidate_result_failure));
    VerdictValue testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_011(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  SLAC_Tester2 v_SLAC_Tester2;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_012(v_HAL_61851_Listener,
                                                          par_cmValidate_result_notReady));
    VerdictValue testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_012(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  SLAC_Tester2 v_SLAC_Tester2;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_012(v_HAL_61851_Listener,
                                                          par_cmValidate_result_notRequired));
    VerdictValue testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_013(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  SLAC_Tester2 v_SLAC_Tester2;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_010(par_cmValidate_result_failure));
    VerdictValue testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_014(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_015(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_016(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_017(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_018(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_019(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  SLAC_Tester2 v_SLAC_Tester2;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_CmValidate_010(par_cmValidate_result_notReady));
    VerdictValue testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_020(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmValidate_021(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
} // namespace TestCases_EVCC_CmValidate