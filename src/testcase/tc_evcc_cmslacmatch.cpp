#include "testcase/tc_evcc_cmslacmatch.hpp"

module TestCases_EVCC_CmSlacMatch {
import from DataStructure_SLAC all;
import from TestBehavior_EVCC_CmSlacMatch all;
import from TestBehavior_EVCC_CmValidateOrCmSlacMatch all;
import from ComponentsAndPorts all;
import from Configurations_15118_3 all;
import from Timer_15118_3 all;
import from PreConditions_EVCC_15118_3 all;
import from PostConditions_EVCC_15118_3 all;
import from Templates_CMN_CmSlacMatch all;
import from Templates_CMN_SlacPayloadHeader all;
import from TestBehavior_EVCC_AttenuationCharacterization all;
import from TestBehavior_EVCC_CmSlacParm all;
import from LibFunctions_15118_3 { group generalFunctions; }
testcase TC_EVCC_CMN_VTB_CmSlacMatch_001() runs on EVCC_Tester system SystemEVCC {
HAL_61851_Listener v_HAL_61851_Listener;
verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict = f_EVCC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacMatch_001();
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacMatch_002() runs on EVCC_Tester system SystemEVCC {
HAL_61851_Listener v_HAL_61851_Listener;
verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacMatch_001();
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacMatch_003() runs on EVCC_Tester system SystemEVCC {
HAL_61851_Listener v_HAL_61851_Listener;
verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict = f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacMatch_002();
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacMatch_004() runs on EVCC_Tester system SystemEVCC {
HAL_61851_Listener v_HAL_61851_Listener;
verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict = f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacMatch_003(md_CMN_CMN_CmSlacMatchCnf_002(
m_CMN_CMN_SlacPayloadHeaderInvalid_001(),
"0056",
"0000000000000000000000000000000000",
vc_sut_mac,
"0000000000000000000000000000000000",
par_testSystem_mac,
vc_RunID, vc_Nid, vc_Nmk));
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacMatch_005() runs on EVCC_Tester system SystemEVCC {
HAL_61851_Listener v_HAL_61851_Listener;
verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict = f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacMatch_003(md_CMN_CMN_CmSlacMatchCnf_002(
m_CMN_CMN_SlacPayloadHeaderInvalid_002(),
"0056",
"0000000000000000000000000000000000",
vc_sut_mac,
"0000000000000000000000000000000000",
par_testSystem_mac,
vc_RunID, vc_Nid, vc_Nmk));
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacMatch_006() runs on EVCC_Tester system SystemEVCC {
HAL_61851_Listener v_HAL_61851_Listener;
verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict = f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacMatch_003(md_CMN_CMN_CmSlacMatchCnf_002(
m_CMN_CMN_SlacPayloadHeader_001(),
"0000",
"0000000000000000000000000000000000",
vc_sut_mac,
"0000000000000000000000000000000000",
par_testSystem_mac,
vc_RunID, vc_Nid, vc_Nmk));
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacMatch_007() runs on EVCC_Tester system SystemEVCC {
HAL_61851_Listener v_HAL_61851_Listener;
verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict = f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacMatch_003(md_CMN_CMN_CmSlacMatchCnf_002(
m_CMN_CMN_SlacPayloadHeader_001(),
"0056",
"0000000000000000000000000000000001",
vc_sut_mac,
"0000000000000000000000000000000000",
par_testSystem_mac,
vc_RunID, vc_Nid, vc_Nmk));
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacMatch_008() runs on EVCC_Tester system SystemEVCC {
HAL_61851_Listener v_HAL_61851_Listener;
verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict = f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacMatch_003(md_CMN_CMN_CmSlacMatchCnf_002(
m_CMN_CMN_SlacPayloadHeader_001(),
"0056",
"0000000000000000000000000000000000",
"000000000000",
"0000000000000000000000000000000000",
par_testSystem_mac,
vc_RunID, vc_Nid, vc_Nmk));
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacMatch_009() runs on EVCC_Tester system SystemEVCC {
HAL_61851_Listener v_HAL_61851_Listener;
verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict = f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacMatch_003(md_CMN_CMN_CmSlacMatchCnf_002(
m_CMN_CMN_SlacPayloadHeader_001(),
"0056",
"0000000000000000000000000000000000",
vc_sut_mac,
"0000000000000000000000000000000001",
par_testSystem_mac,
vc_RunID, vc_Nid, vc_Nmk));
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacMatch_010() runs on EVCC_Tester system SystemEVCC {
HAL_61851_Listener v_HAL_61851_Listener;
verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict = f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacMatch_003(md_CMN_CMN_CmSlacMatchCnf_002(
m_CMN_CMN_SlacPayloadHeader_001(),
"0056",
"0000000000000000000000000000000000",
vc_sut_mac,
"0000000000000000000000000000000000",
"000000000000",
vc_RunID, vc_Nid, vc_Nmk));
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacMatch_011() runs on EVCC_Tester system SystemEVCC {
HAL_61851_Listener v_HAL_61851_Listener;
verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict = f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
RunID_TYPE v_RunID = f_randomHexStringGen(16);
if(v_RunID != vc_RunID) {
f_EVCC_CMN_TB_VTB_CmSlacMatch_003(md_CMN_CMN_CmSlacMatchCnf_002(
m_CMN_CMN_SlacPayloadHeader_001(),
"0056",
"0000000000000000000000000000000000",
vc_sut_mac,
"0000000000000000000000000000000000",
par_testSystem_mac,
v_RunID, vc_Nid, vc_Nmk));
} else {setverdict(inconc, "Invalid runID is equal to current runID.")};
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacMatch_012() runs on EVCC_Tester system SystemEVCC {
HAL_61851_Listener v_HAL_61851_Listener;
SLAC_Tester2 v_SLAC_Tester2;
verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
preConVerdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
v_SLAC_Tester2.start(f_EVCC_CMN_TB_VTB_AttenuationCharacterization_003());
verdicttype testbehaviorVerdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
if(testbehaviorVerdict == pass) {
testbehaviorVerdict = f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
}
if(testbehaviorVerdict == pass) {
f_EVCC_CMN_TB_VTB_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener, fail);
}
v_SLAC_Tester2.done;
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(v_HAL_61851_Listener, v_SLAC_Tester2, system);
}
}