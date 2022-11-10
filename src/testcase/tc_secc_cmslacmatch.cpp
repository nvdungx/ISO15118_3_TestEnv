#include "testcase/tc_secc_cmslacmatch.hpp"

module TestCases_SECC_CmSlacMatch
{
import from DataStructure_SLAC all;
import from TestBehavior_SECC_CmSlacMatch all;
import from ComponentsAndPorts all;
import from Configurations_15118_3 all;
import from PreConditions_SECC_15118_3 all;
import from PostConditions_SECC_15118_3 all;
import from Templates_CMN_CmSlacMatch all;
import from Templates_CMN_SlacPayloadHeader all;
import from LibFunctions_15118_3 { group generalFunctions;
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_001() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
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
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_002() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
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
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_003() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
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
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_004() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
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
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_005() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
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
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_006() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
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
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_007() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeaderInvalid_001(), '003E' H,
        '0000000000000000000000000000000000' H,
        par_testSystem_mac,
        '0000000000000000000000000000000000' H,
        vc_sut_mac, vc_RunID));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_008() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeaderInvalid_001(), '003E' H,
        '0000000000000000000000000000000000' H,
        par_testSystem_mac,
        '0000000000000000000000000000000000' H,
        vc_sut_mac, vc_RunID));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_009() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeaderInvalid_002(), '003E' H,
        '0000000000000000000000000000000000' H,
        par_testSystem_mac,
        '0000000000000000000000000000000000' H,
        vc_sut_mac, vc_RunID));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_010() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeaderInvalid_002(), '003E' H,
        '0000000000000000000000000000000000' H,
        par_testSystem_mac,
        '0000000000000000000000000000000000' H,
        vc_sut_mac, vc_RunID));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_011() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), '0000' H,
        '0000000000000000000000000000000000' H,
        par_testSystem_mac,
        '0000000000000000000000000000000000' H,
        vc_sut_mac, vc_RunID));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_012() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), '0000' H,
        '0000000000000000000000000000000000' H,
        par_testSystem_mac,
        '0000000000000000000000000000000000' H,
        vc_sut_mac, vc_RunID));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_013() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), '003E' H,
        '0000000000000000000000000000000001' H,
        par_testSystem_mac,
        '0000000000000000000000000000000000' H,
        vc_sut_mac, vc_RunID));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_014() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), '003E' H,
        '0000000000000000000000000000000001' H,
        par_testSystem_mac,
        '0000000000000000000000000000000000' H,
        vc_sut_mac, vc_RunID));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_015() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), '003E' H,
        '0000000000000000000000000000000000' H,
        '000000000000' H,
        '0000000000000000000000000000000000' H,
        vc_sut_mac, vc_RunID));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_016() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), '003E' H,
        '0000000000000000000000000000000000' H,
        '000000000000' H,
        '0000000000000000000000000000000000' H,
        vc_sut_mac, vc_RunID));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_017() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), '003E' H,
        '0000000000000000000000000000000000' H,
        par_testSystem_mac,
        '0000000000000000000000000000000001' H,
        vc_sut_mac, vc_RunID));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_018() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), '003E' H,
        '0000000000000000000000000000000000' H,
        par_testSystem_mac,
        '0000000000000000000000000000000001' H,
        vc_sut_mac, vc_RunID));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_019() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), '003E' H,
        '0000000000000000000000000000000000' H,
        par_testSystem_mac,
        '0000000000000000000000000000000000' H,
        '000000000000' H, vc_RunID));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_020() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
        m_CMN_CMN_SlacPayloadHeader_001(), '003E' H,
        '0000000000000000000000000000000000' H,
        par_testSystem_mac,
        '0000000000000000000000000000000000' H,
        '000000000000' H, vc_RunID));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_021() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    var RunID_TYPE v_RunID = f_randomHexStringGen(16);
    if (v_RunID != vc_RunID)
    {
      f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
          m_CMN_CMN_SlacPayloadHeader_001(), '003E' H,
          '0000000000000000000000000000000000' H,
          par_testSystem_mac,
          '0000000000000000000000000000000000' H,
          vc_sut_mac, v_RunID));
    }
    else
    {
      setverdict(inconc, "Invalid runID is equal to current runID.")
    };
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_022() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    var RunID_TYPE v_RunID = f_randomHexStringGen(16);
    if (v_RunID != vc_RunID)
    {
      f_SECC_CMN_TB_VTB_CmSlacMatch_004(md_CMN_CMN_CmSlacMatchReq_002(
          m_CMN_CMN_SlacPayloadHeader_001(), '003E' H,
          '0000000000000000000000000000000000' H,
          par_testSystem_mac,
          '0000000000000000000000000000000000' H,
          vc_sut_mac, v_RunID));
    }
    else
    {
      setverdict(inconc, "Invalid runID is equal to current runID.")
    };
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_023() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
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
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_SECC_CMN_VTB_CmSlacMatch_024() runs on SECC_Tester system SystemSECC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
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
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
}