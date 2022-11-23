#include "testcase/tc_evcc_cmslacparm.hpp"

#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)
namespace TestCases_EVCC_CmSlacParm
{
// import from DataStructure_SLAC all;
// import from TestBehavior_EVCC_CmSlacParm all;
// import from ComponentsAndPorts all;
// import from Configurations_15118_3 all;
// import from Timer_15118_3 all;
// import from PreConditions_EVCC_15118_3 all;
// import from PostConditions_EVCC_15118_3 all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from Templates_CMN_CmSlacParm all;
// import from LibFunctions_15118_3 { group generalFunctions;}
VerdictValue TC_EVCC_CMN_VTB_CmSlacParm_001(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmSlacParm_002(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmSlacParm_002();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmSlacParm_003(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmSlacParm_003(md_CMN_CMN_CmSlacParmCnf_002("000000000000",
                                                                  "0A", "06", "01", vc_sut_mac,
                                                                  m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmSlacParm_004(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmSlacParm_003(md_CMN_CMN_CmSlacParmCnf_002("FFFFFFFFFFFF",
                                                                  "0A", "00", "01", vc_sut_mac,
                                                                  m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmSlacParm_005(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmSlacParm_003(md_CMN_CMN_CmSlacParmCnf_002("FFFFFFFFFFFF",
                                                                  "0A", "06", "00", vc_sut_mac,
                                                                  m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmSlacParm_006(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmSlacParm_003(md_CMN_CMN_CmSlacParmCnf_002("FFFFFFFFFFFF",
                                                                  "0A", "06", "01", vc_sut_mac,
                                                                  m_CMN_CMN_SlacPayloadHeaderInvalid_001(), vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmSlacParm_007(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmSlacParm_003(md_CMN_CMN_CmSlacParmCnf_002("FFFFFFFFFFFF",
                                                                  "0A", "06", "01", vc_sut_mac,
                                                                  m_CMN_CMN_SlacPayloadHeaderInvalid_002(), vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmSlacParm_008(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    RunID_TYPE v_RunID = f_randomHexStringGen(16);
    if (v_RunID != vc_RunID)
    {
      f_EVCC_CMN_TB_VTB_CmSlacParm_003(md_CMN_CMN_CmSlacParmCnf_002("FFFFFFFFFFFF",
                                                                    "0A", "06", "01", vc_sut_mac,
                                                                    m_CMN_CMN_SlacPayloadHeader_001(), v_RunID));
    }
    else
    {
      setverdict(inconc, "Invalid runID is equal to current runID.")
    };
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmSlacParm_009(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmSlacParm_004();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmSlacParm_010(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmSlacParm_005();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmSlacParm_011(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmSlacParm_003(md_CMN_CMN_CmSlacParmCnf_002("FFFFFFFFFFFF", "0A", "06", "01", "000000000000",
                                                                  m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmSlacParm_012(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  vc_errorState = e_NegVolt12;
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmSlacParm_013(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  vc_DutyCycle = 100;
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_CMN_VTB_CmSlacParm_014(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  vc_errorState = e_NegVolt12;
  vc_DutyCycle = 100;
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_AC_VTB_CmSlacParm_001(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  vc_DutyCycle = cc_dutyCycle_32A;
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_EVCC_AC_VTB_CmSlacParm_002(void) // runs on EVCC_Tester system SystemEVCC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  vc_DutyCycle = cc_dutyCycle_32A;
  vc_errorState = e_NegVolt12;
  preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
} // namespace TestCases_EVCC_CmSlacParm