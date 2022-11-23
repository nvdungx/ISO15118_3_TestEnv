#include "testcase/tc_secc_cmvalidate.hpp"

#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)
namespace TestCases_SECC_CmValidate
{
// import from TestBehavior_SECC_CmValidate all;
// import from TestBehavior_SECC_CmSlacMatch all;
// import from ComponentsAndPorts all;
// import from Configurations_15118_3 all;
// import from PreConditions_SECC_15118_3 all;
// import from PostConditions_SECC_15118_3 all;
// import from Templates_CMN_CmValidate all;
// import from Timer_15118_3 all;
VerdictValue TC_SECC_CMN_VTB_CmValidate_001(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmValidate_002(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmValidate_003(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmValidate_004(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    hexstring v_pilotTimer = int2hex(float2int((par_TP_EV_vald_toggle * 10.0) - 1.0), 2);
    f_SECC_CMN_TB_VTB_CmValidate_004(v_HAL_61851_Listener,
                                      md_CMN_CMN_CmValidateReq_004(
                                          "FF", v_pilotTimer, "01"));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmValidate_005(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    hexstring v_pilotTimer = int2hex(float2int((par_TP_EV_vald_toggle * 10.0) - 1.0), 2);
    f_SECC_CMN_TB_VTB_CmValidate_005(md_CMN_CMN_CmValidateReq_004(
        "00", v_pilotTimer,
        par_cmValidate_result_notReady));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmValidate_006(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    hexstring v_pilotTimer = int2hex(float2int((par_TP_EV_vald_toggle * 10.0) - 1.0), 2);
    f_SECC_CMN_TB_VTB_CmValidate_005(md_CMN_CMN_CmValidateReq_004(
        "00", v_pilotTimer,
        par_cmValidate_result_success));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmValidate_007(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    hexstring v_pilotTimer = int2hex(float2int((par_TP_EV_vald_toggle * 10.0) - 1.0), 2);
    f_SECC_CMN_TB_VTB_CmValidate_005(md_CMN_CMN_CmValidateReq_004(
        "00", v_pilotTimer,
        par_cmValidate_result_failure));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmValidate_008(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    hexstring v_pilotTimer = int2hex(float2int((par_TP_EV_vald_toggle * 10.0) - 1.0), 2);
    f_SECC_CMN_TB_VTB_CmValidate_005(md_CMN_CMN_CmValidateReq_004(
        "00", v_pilotTimer,
        par_cmValidate_result_notRequired));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmValidate_009(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  SLAC_Tester2 v_SLAC_Tester2;
  SLAC_Tester3 v_SLAC_Tester3;
  SLAC_Tester4 v_SLAC_Tester4;
  SLAC_Tester5 v_SLAC_Tester5;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2,
                                                v_SLAC_Tester3, v_SLAC_Tester4,
                                                v_SLAC_Tester5, system);
}
VerdictValue TC_SECC_CMN_VTB_CmValidate_010(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmValidate_011(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmValidate_012(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmValidate_013(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
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
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
} // namespace TestCases_SECC_CmValidate