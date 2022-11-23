#include "testcase/tc_evcc_plclinkstatus.hpp"

#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)
namespace TestCases_EVCC_PLCLinkStatus
{
// import from DataStructure_SLAC all;
// import from TestBehavior_EVCC_PLCLinkStatus all;
// import from ComponentsAndPorts all;
// import from Configurations_15118_3 all;
// import from PreConditions_EVCC_15118_3 all;
// import from Timer_15118_3 all;
// import from Pixit_15118_3 all;
// import from PostConditions_EVCC_15118_3 all;
// import from PreConditions_EVCC_15118_2{
//       function f_EVCC_AC_PR_SessionStop_002,
//       f_EVCC_DC_PR_WeldingDetectionOrSessionStop_002,
//       f_EVCC_AC_PR_SessionStop_003,
//       f_EVCC_DC_PR_WeldingDetectionOrSessionStop_003 };
// import from Configurations_15118_2 all;
// import from LibFunctions_15118_3 all;
// import from Services_HAL_61851 all;
// import from TestBehavior_EVCC_CommonBehavior all;
// import from Timer_15118 all;
// import from Pixit_15118 all;
// import from Pics_15118 all;
// import from Timer_15118_2 all;

VerdictValue TC_EVCC_CMN_VTB_PLCLinkStatus_001(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_001(fail);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_PLCLinkStatus_002(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_002();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_PLCLinkStatus_003(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_003(e_OscOff);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_PLCLinkStatus_004(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_003(e_NegVolt12);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_PLCLinkStatus_005(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  vc_DutyCycleDelay = 7.5;
  preConVerdict = f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_001(fail);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  if (getverdict == pass)
  {
    SLOGI("A SECC delay of 7,5 s for signaling a 5% duty cycle did not " &
        "influence the SLAC Matching process.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_PLCLinkStatus_006(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_006(v_HAL_61851_Listener, 5, E);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_PLCLinkStatus_007(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_006(v_HAL_61851_Listener, 5, F);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_PLCLinkStatus_008(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_008(v_HAL_61851_Listener);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_AC_VTB_PLCLinkStatus_001(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_AC_PR_SessionStop_002(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    preConVerdict = f_EVCC_setPwmMode(e_PosVolt12);
  }
  if (preConVerdict == pass)
  {
    map(mtc
        : pt_SLAC_Port, system
        : pt_SLAC_Port);
    f_EVCC_startSleepingPhase(PICS_CMN_CMN_WakeUp);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_004(v_HAL_61851_Listener);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_AC_VTB_PLCLinkStatus_002(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_AC_PR_SessionStop_002(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    preConVerdict = f_EVCC_setPwmMode(e_PosVolt12);
  }
  if (preConVerdict == pass)
  {
    map(mtc
        : pt_SLAC_Port, system
        : pt_SLAC_Port);
    f_EVCC_startSleepingPhase(PIXIT_CMN_CMN_WakeUp - 5.0);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_005(v_HAL_61851_Listener, PIXIT_CMN_CMN_WakeUp);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_AC_VTB_PLCLinkStatus_003(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_006(v_HAL_61851_Listener,
                                        par_EVSENominalDutyCycle, E);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_AC_VTB_PLCLinkStatus_004(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_AC_TB_VTB_PLCLinkStatus_001();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_AC_VTB_PLCLinkStatus_005(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_AC_TB_VTB_PLCLinkStatus_002(v_HAL_61851_Listener, E);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_AC_VTB_PLCLinkStatus_006(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_AC_PR_SessionStop_003(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    map(mtc
        : pt_SLAC_Port, system
        : pt_SLAC_Port);
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_007();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_AC_VTB_PLCLinkStatus_007(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_006(v_HAL_61851_Listener,
                                        par_EVSENominalDutyCycle, F);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_AC_VTB_PLCLinkStatus_008(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_AC_TB_VTB_PLCLinkStatus_002(v_HAL_61851_Listener, F);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_AC_VTB_PLCLinkStatus_009(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_AC_PR_SessionStop_002(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    preConVerdict = f_EVCC_setPwmMode(e_PosVolt12);
  }
  if (preConVerdict == pass)
  {
    map(mtc
        : pt_SLAC_Port, system
        : pt_SLAC_Port);
    f_EVCC_startSleepingPhase(par_SECC_Pmax0W - 5.0);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_005(v_HAL_61851_Listener, par_SECC_Pmax0W);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_AC_VTB_PLCLinkStatus_010(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_AC_PR_SessionStop_002(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    preConVerdict = f_EVCC_setPwmMode(e_PosVolt12);
  }
  if (preConVerdict == pass)
  {
    map(mtc
        : pt_SLAC_Port, system
        : pt_SLAC_Port);
    f_EVCC_startSleepingPhase(par_SECC_Pmax0W - 5.0);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_005(v_HAL_61851_Listener, par_SECC_Pmax0W);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_DC_VTB_PLCLinkStatus_001(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_DC_PR_WeldingDetectionOrSessionStop_002(
      v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    preConVerdict = f_EVCC_setPwmMode(e_PosVolt12);
  }
  if (preConVerdict == pass)
  {
    map(mtc
        : pt_SLAC_Port, system
        : pt_SLAC_Port);
    f_EVCC_startSleepingPhase(PICS_CMN_CMN_WakeUp);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_004(v_HAL_61851_Listener);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_DC_VTB_PLCLinkStatus_002(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_DC_PR_WeldingDetectionOrSessionStop_002(
      v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    preConVerdict = f_EVCC_setPwmMode(e_PosVolt12);
  }
  if (preConVerdict == pass)
  {
    map(mtc
        : pt_SLAC_Port, system
        : pt_SLAC_Port);
    f_EVCC_startSleepingPhase(PIXIT_CMN_CMN_WakeUp - 5.0);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_005(v_HAL_61851_Listener, PIXIT_CMN_CMN_WakeUp);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_DC_VTB_PLCLinkStatus_003(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_DC_PR_WeldingDetectionOrSessionStop_003(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    map(mtc
        : pt_SLAC_Port, system
        : pt_SLAC_Port);
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_007();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_DC_VTB_PLCLinkStatus_004(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_DC_PR_WeldingDetectionOrSessionStop_002(
      v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    preConVerdict = f_EVCC_setPwmMode(e_PosVolt12);
  }
  if (preConVerdict == pass)
  {
    map(mtc
        : pt_SLAC_Port, system
        : pt_SLAC_Port);
    f_EVCC_startSleepingPhase(par_SECC_Pmax0W - 5.0);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_005(v_HAL_61851_Listener, par_SECC_Pmax0W);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_DC_VTB_PLCLinkStatus_005(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_DC_PR_WeldingDetectionOrSessionStop_002(
      v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    preConVerdict = f_EVCC_setPwmMode(e_PosVolt12);
  }
  if (preConVerdict == pass)
  {
    map(mtc
        : pt_SLAC_Port, system
        : pt_SLAC_Port);
    f_EVCC_startSleepingPhase(par_SECC_Pmax0W - 5.0);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_PLCLinkStatus_005(v_HAL_61851_Listener, par_SECC_Pmax0W);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, system);
}
} // namespace TestCases_EVCC_PLCLinkStatus