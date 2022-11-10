#include "testcase/tc_evcc_attenuationcharacterization.hpp"

module TestCases_EVCC_AttenuationCharacterization
{
import from DataStructure_SLAC all;
import from PreConditions_EVCC_15118_3 all;
import from TestBehavior_EVCC_AttenuationCharacterization all;
import from ComponentsAndPorts all;
import from Configurations_15118_3 all;
import from PostConditions_EVCC_15118_3 all;
import from Timer_15118_3 all;
import from Templates_EVCC_CmAttenCharInd all;
import from Templates_CMN_SlacPayloadHeader all;
import from TestBehavior_EVCC_CmSlacParm all;
import from LibFunctions_15118_3 { group generalFunctions;
}
testcase TC_EVCC_CMN_VTB_AttenuationCharacterization_001() runs on EVCC_Tester
    system SystemEVCC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_AttenuationCharacterization_002() runs on EVCC_Tester
    system SystemEVCC
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
    v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_AttenuationCharacterization_002());
    var verdicttype testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
    if (testbehaviorVerdict == pass)
    {
      f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
    }
    v_SLAC_Tester2.done;
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
}
testcase TC_EVCC_CMN_VTB_AttenuationCharacterization_003() runs on EVCC_Tester
    system SystemEVCC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_AttenuationCharacterization_004();
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_AttenuationCharacterization_004() runs on EVCC_Tester
    system SystemEVCC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_AttenuationCharacterization_005(md_EVCC_CMN_CmAttenCharInd_002(
        m_CMN_CMN_SlacPayloadHeaderInvalid_001(),
        vc_sut_mac, vc_RunID, vc_Num_sounds,
        '0000000000000000000000000000000000' H,
        '0000000000000000000000000000000000' H,
        '3A' H, m_EVCC_CMN_atten_list_001()));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_AttenuationCharacterization_005() runs on EVCC_Tester
    system SystemEVCC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_AttenuationCharacterization_005(md_EVCC_CMN_CmAttenCharInd_002(
        m_CMN_CMN_SlacPayloadHeaderInvalid_002(),
        vc_sut_mac, vc_RunID, vc_Num_sounds,
        '0000000000000000000000000000000000' H,
        '0000000000000000000000000000000000' H,
        '3A' H, m_EVCC_CMN_atten_list_001()));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_AttenuationCharacterization_006() runs on EVCC_Tester
    system SystemEVCC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_AttenuationCharacterization_005(md_EVCC_CMN_CmAttenCharInd_002(
        m_CMN_CMN_SlacPayloadHeader_001(),
        '000000000000' H, vc_RunID,
        vc_Num_sounds,
        '0000000000000000000000000000000000' H,
        '0000000000000000000000000000000000' H,
        '3A' H, m_EVCC_CMN_atten_list_001()));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_AttenuationCharacterization_007() runs on EVCC_Tester
    system SystemEVCC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    var RunID_TYPE v_RunID = f_randomHexStringGen(16);
    if (v_RunID != vc_RunID)
    {
      f_EVCC_CMN_TB_VTB_AttenuationCharacterization_005(md_EVCC_CMN_CmAttenCharInd_002(
          m_CMN_CMN_SlacPayloadHeader_001(),
          vc_sut_mac, v_RunID, vc_Num_sounds,
          '0000000000000000000000000000000000' H,
          '0000000000000000000000000000000000' H,
          '3A' H, m_EVCC_CMN_atten_list_001()));
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
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_AttenuationCharacterization_008() runs on EVCC_Tester
    system SystemEVCC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_AttenuationCharacterization_005(md_EVCC_CMN_CmAttenCharInd_002(
        m_CMN_CMN_SlacPayloadHeader_001(),
        vc_sut_mac, vc_RunID, vc_Num_sounds,
        '0000000000000000000000000000000001' H,
        '0000000000000000000000000000000000' H,
        '3A' H, m_EVCC_CMN_atten_list_001()));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_AttenuationCharacterization_009() runs on EVCC_Tester
    system SystemEVCC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_AttenuationCharacterization_005(md_EVCC_CMN_CmAttenCharInd_002(
        m_CMN_CMN_SlacPayloadHeader_001(),
        vc_sut_mac, vc_RunID, vc_Num_sounds,
        '0000000000000000000000000000000000' H,
        '0000000000000000000000000000000001' H,
        '3A' H, m_EVCC_CMN_atten_list_001()));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_AttenuationCharacterization_010() runs on EVCC_Tester
    system SystemEVCC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_AttenuationCharacterization_005(md_EVCC_CMN_CmAttenCharInd_002(
        m_CMN_CMN_SlacPayloadHeader_001(),
        vc_sut_mac, vc_RunID, vc_Num_sounds,
        '0000000000000000000000000000000000' H,
        '0000000000000000000000000000000000' H,
        '00' H, m_EVCC_CMN_atten_list_001()));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_AttenuationCharacterization_011() runs on EVCC_Tester
    system SystemEVCC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_AttenuationCharacterization_005(md_EVCC_CMN_CmAttenCharInd_002(
        m_CMN_CMN_SlacPayloadHeader_001(),
        vc_sut_mac, vc_RunID, '00' H,
        '0000000000000000000000000000000000' H,
        '0000000000000000000000000000000000' H,
        '3A' H, m_EVCC_CMN_atten_list_001()));
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_AttenuationCharacterization_012() runs on EVCC_Tester
    system SystemEVCC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_AttenuationCharacterization_006(e_OscOff);
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_AttenuationCharacterization_013() runs on EVCC_Tester
    system SystemEVCC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_CMN_TB_VTB_AttenuationCharacterization_006(e_NegVolt12);
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_AC_VTB_AttenuationCharacterization_001() runs on EVCC_Tester
    system SystemEVCC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_AC_TB_VTB_AttenuationCharacterization_001(10);
  }
  else
  {
    log("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_AC_VTB_AttenuationCharacterization_002() runs on EVCC_Tester
    system SystemEVCC
{
  var HAL_61851_Listener v_HAL_61851_Listener;
  var verdicttype preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_EVCC_AC_TB_VTB_AttenuationCharacterization_001(96);
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