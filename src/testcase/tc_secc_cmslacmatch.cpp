#include "testcase/tc_secc_cmslacmatch.hpp"

#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)
namespace TestCases_SECC_CmSlacMatch
{
// import from DataStructure_SLAC all;
// import from TestBehavior_SECC_CmSlacMatch all;
// import from ComponentsAndPorts all;
// import from Configurations_15118_3 all;
// import from PreConditions_SECC_15118_3 all;
// import from PostConditions_SECC_15118_3 all;
// import from Templates_CMN_CmSlacMatch all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from LibFunctions_15118_3 { group generalFunctions;}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_001(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_001(fail);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_002(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_001(fail);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_003(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_002();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_004(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_002();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_005(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_003();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_006(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_003();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_007(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeaderInvalid_001(), "003E",
        "0000000000000000000000000000000000",
        par_testSystem_mac,
        "0000000000000000000000000000000000",
        vc_sut_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_008(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeaderInvalid_001(), "003E",
        "0000000000000000000000000000000000",
        par_testSystem_mac,
        "0000000000000000000000000000000000",
        vc_sut_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_009(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeaderInvalid_002(), "003E",
        "0000000000000000000000000000000000",
        par_testSystem_mac,
        "0000000000000000000000000000000000",
        vc_sut_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_010(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeaderInvalid_002(), "003E",
        "0000000000000000000000000000000000",
        par_testSystem_mac,
        "0000000000000000000000000000000000",
        vc_sut_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_011(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), "0000",
        "0000000000000000000000000000000000",
        par_testSystem_mac,
        "0000000000000000000000000000000000",
        vc_sut_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_012(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), "0000",
        "0000000000000000000000000000000000",
        par_testSystem_mac,
        "0000000000000000000000000000000000",
        vc_sut_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_013(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), "003E",
        "0000000000000000000000000000000001",
        par_testSystem_mac,
        "0000000000000000000000000000000000",
        vc_sut_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_014(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), "003E",
        "0000000000000000000000000000000001",
        par_testSystem_mac,
        "0000000000000000000000000000000000",
        vc_sut_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_015(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), "003E",
        "0000000000000000000000000000000000",
        "000000000000",
        "0000000000000000000000000000000000",
        vc_sut_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_016(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), "003E",
        "0000000000000000000000000000000000",
        "000000000000",
        "0000000000000000000000000000000000",
        vc_sut_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_017(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), "003E",
        "0000000000000000000000000000000000",
        par_testSystem_mac,
        "0000000000000000000000000000000001",
        vc_sut_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_018(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), "003E",
        "0000000000000000000000000000000000",
        par_testSystem_mac,
        "0000000000000000000000000000000001",
        vc_sut_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_019(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), "003E",
        "0000000000000000000000000000000000",
        par_testSystem_mac,
        "0000000000000000000000000000000000",
        "000000000000", vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_020(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), "003E",
        "0000000000000000000000000000000000",
        par_testSystem_mac,
        "0000000000000000000000000000000000",
        "000000000000", vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_021(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    RunID_TYPE v_RunID = f_randomHexStringGen(16);
    if (v_RunID != vc_RunID)
    {
      f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
          m_CMN_CMN_SlacPayloadHeader_001(), "003E",
          "0000000000000000000000000000000000",
          par_testSystem_mac,
          "0000000000000000000000000000000000",
          vc_sut_mac, v_RunID));
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
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_022(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    RunID_TYPE v_RunID = f_randomHexStringGen(16);
    if (v_RunID != vc_RunID)
    {
      f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
          m_CMN_CMN_SlacPayloadHeader_001(), "003E",
          "0000000000000000000000000000000000",
          par_testSystem_mac,
          "0000000000000000000000000000000000",
          vc_sut_mac, v_RunID));
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
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_023(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_005(v_HAL_61851_Listener);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_CmSlacMatch_024(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_005(v_HAL_61851_Listener);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
} // namespace TestCases_SECC_CmSlacMatch