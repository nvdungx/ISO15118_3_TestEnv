#include "testcase/tc_evcc_cmslacparm.hpp"

module TestCases_EVCC_CmSlacParm {
import from DataStructure_SLAC all;
import from TestBehavior_EVCC_CmSlacParm all;
import from ComponentsAndPorts all;
import from Configurations_15118_3 all;
import from Timer_15118_3 all;
import from PreConditions_EVCC_15118_3 all;
import from PostConditions_EVCC_15118_3 all;
import from Templates_CMN_SlacPayloadHeader all;
import from Templates_CMN_CmSlacParm all;
import from LibFunctions_15118_3 { group generalFunctions; }
testcase TC_EVCC_CMN_VTB_CmSlacParm_001() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacParm_002() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacParm_002();
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacParm_003() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacParm_003(md_CMN_CMN_CmSlacParmCnf_002("000000000000",
'0A'H, "06", "01", vc_sut_mac,
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID));
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacParm_004() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacParm_003(md_CMN_CMN_CmSlacParmCnf_002('FFFFFFFFFFFF'H,
'0A'H, "00", "01", vc_sut_mac,
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID));
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacParm_005() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacParm_003(md_CMN_CMN_CmSlacParmCnf_002('FFFFFFFFFFFF'H,
'0A'H, "06", "00", vc_sut_mac,
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID));
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacParm_006() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacParm_003(md_CMN_CMN_CmSlacParmCnf_002('FFFFFFFFFFFF'H,
'0A'H, "06", "01", vc_sut_mac,
m_CMN_CMN_SlacPayloadHeaderInvalid_001(), vc_RunID));
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacParm_007() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacParm_003(md_CMN_CMN_CmSlacParmCnf_002('FFFFFFFFFFFF'H,
'0A'H, "06", "01", vc_sut_mac,
m_CMN_CMN_SlacPayloadHeaderInvalid_002(), vc_RunID));
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacParm_008() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
var RunID_TYPE v_RunID := f_randomHexStringGen(16);
if(v_RunID != vc_RunID) {
f_EVCC_CMN_TB_VTB_CmSlacParm_003(md_CMN_CMN_CmSlacParmCnf_002('FFFFFFFFFFFF'H,
'0A'H, "06", "01", vc_sut_mac,
m_CMN_CMN_SlacPayloadHeader_001(), v_RunID));
} else {setverdict(inconc, "Invalid runID is equal to current runID.")};
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacParm_009() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacParm_004();
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacParm_010() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacParm_005();
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacParm_011() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacParm_003(md_CMN_CMN_CmSlacParmCnf_002('FFFFFFFFFFFF'H,'0A'H, "06", "01", "000000000000",
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID));
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacParm_012() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
vc_errorState := e_NegVolt12;
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacParm_013() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
vc_DutyCycle := 100;
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_CMN_VTB_CmSlacParm_014() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
vc_errorState := e_NegVolt12;
vc_DutyCycle := 100;
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_AC_VTB_CmSlacParm_001() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
vc_DutyCycle := cc_dutyCycle_32A;
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
testcase TC_EVCC_AC_VTB_CmSlacParm_002() runs on EVCC_Tester system SystemEVCC {
var HAL_61851_Listener v_HAL_61851_Listener;
var verdicttype preConVerdict;
// -------------- Pre Conditions-------------------------------------------------------
f_EVCC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
vc_DutyCycle := cc_dutyCycle_32A;
vc_errorState := e_NegVolt12;
preConVerdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
//-------------- Test behavior---------------------------------------------------------
if( preConVerdict == pass ) {
f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
} else {
log("PreCondition was unsuccessful.");
}
//------------- Post Conditions--------------------------------------------------------
f_EVCC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
}