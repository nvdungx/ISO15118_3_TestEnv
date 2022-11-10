#include "behaviorfunction/evcc_plclinkstatus.hpp"

// import from Timer_15118_3 all;
// import from Pics_15118 all;
// import from Pixit_15118_3 all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from Templates_CMN_CmSlacMatch all;
// import from ComponentsAndPorts all;
// import from DataStructure_SLAC all;
// import from Services_PLCLinkStatus all;
// import from Services_HAL_61851 all;
// import from DataStructure_HAL_61851 all;
// import from TestBehavior_EVCC_SDP all;
// import from LibFunctions_15118_3 all;
// import from Timer_15118 all;
// import from Pixit_15118 all;
// import from TestBehavior_EVCC_CmSetKey all;
// import from TestBehavior_EVCC_CmSlacParm all;
// import from Templates_CMN_CmNwStats all;
namespace TestLib {
function f_EVCC_CMN_TB_VTB_PLCLinkStatus_001(in verdicttype v_vct)
runs on EVCC_Tester
return verdicttype {
var verdicttype v_verdict;
tc_TT_match_join.start(par_TT_match_join);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_CNF = '607D'H}),
md_CMN_CMN_CmSlacMatchCnf_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac,
par_testSystem_mac, vc_RunID, vc_Nid,vc_Nmk)))
to vc_sut_mac;
v_verdict = f_EVCC_getPLCLinkEstablishment(v_vct);
if(v_verdict == pass) {
setverdict(pass, "The data link was established by the SUT.");
}
else {
setverdict(v_vct, "The data link could not be established by the SUT.");
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_PLCLinkStatus_002() runs on EVCC_Tester return verdicttype {
var verdicttype v_verdict;
// set state E
f_EVCC_changeValidStateCondition(E,E);
f_EVCC_setPwmMode(e_OscOff);
v_verdict = f_EVCC_getPLCLinkTermination(par_TP_match_leave +
par_CMN_Transmission_Delay, fail);
if(v_verdict == pass) {
setverdict(pass, "The data link was terminated by the SUT.");
}
else {
setverdict(fail, "The data link did not terminated by the SUT.");
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_PLCLinkStatus_003(HAL_61851_PwmMode_Type pwmMode)
runs on EVCC_Tester
return verdicttype {
var verdicttype v_verdict;
// set error state
f_EVCC_changeValidStateCondition(E,E);
f_EVCC_setPwmMode(pwmMode);
tc_TT_match_join.start(par_TT_match_join);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_CNF = '607D'H}),
md_CMN_CMN_CmSlacMatchCnf_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac,
par_testSystem_mac, vc_RunID,vc_Nid,vc_Nmk)))
to vc_sut_mac;
v_verdict = f_EVCC_getPLCLinkError();
if(v_verdict == pass) {
setverdict(pass, "The data link was not established by the SUT.");
}
else {
setverdict(fail, "The data link was established by the SUT.");
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_PLCLinkStatus_004(in HAL_61851_Listener
v_HAL_61851_Listener)
runs on EVCC_Tester
return verdicttype {
var verdicttype verdict = pass;
v_HAL_61851_Listener.stop;
v_HAL_61851_Listener.start(f_EVCC_HAL61851Listener(true));
f_EVCC_setPwmMode(e_OscOn);
f_EVCC_setDutyCycle(5);
f_EVCC_getPLCLinkEstablishmentAfterSleepMode(fail);
if(getverdict == pass) {
tc_V2G_SECC_CommunicationSetup_Timer.start;
verdict = f_EVCC_CMN_TB_VTB_SDP_001(?, fail);
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_PLCLinkStatus_005(in HAL_61851_Listener
v_HAL_61851_Listener,
in float v_time)
runs on EVCC_Tester
return verdicttype {
var verdicttype verdict = pass;
v_HAL_61851_Listener.stop;
v_HAL_61851_Listener.start(f_EVCC_HAL61851Listener(true));
// BCB toggle sequence detection
f_EVCC_changeValidStateCondition(B,C);
timer statetimer = (PICS_CMN_CMN_WakeUp -
v_time + 5.0);
statetimer.start;
alt {
[] a_EVCC_BCBToggleDetection(pt_HAL_61851_Internal_Port, B){
statetimer.stop;
}
[] a_EVCC_BCBToggleDetection(pt_HAL_61851_Internal_Port, C){
statetimer.stop;
f_EVCC_changeValidStateCondition(C,B);
statetimer.start(par_T_vald_state_duration_max);
repeat;
}
[] pt_HAL_61851_Internal_Port.receive {
setverdict(fail, "Received state has an invalid value.");
}
[] statetimer.timeout {
setverdict(fail, "The EVSE could not detect the corresponding " &
"toggle value within " &
"the maximal valid state duration.");
}
}
if(getverdict != pass) {
log("The SUT did not initiate a wake-up " &
"within 'PICS_CMN_CMN_WakeUp'.");
}
f_EVCC_getPLCLinkEstablishmentAfterSleepMode(fail);
if(getverdict == pass) {
tc_V2G_SECC_CommunicationSetup_Timer.start;
verdict = f_EVCC_CMN_TB_VTB_SDP_001(?, fail);
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_PLCLinkStatus_006(in HAL_61851_Listener
v_HAL_61851_Listener,
in integer v_dutyCycle,
in IEC_61851_States v_state)
runs on EVCC_Tester
return verdicttype {
var verdicttype v_verdict = pass;
sleep(par_CMN_waitForConnectionLoss);
// generate new Nid and Nmk
vc_Nmk = f_randomHexStringGen(32);
vc_Nid = fx_generateNID(vc_Nmk);
v_verdict = f_EVCC_CMN_TB_VTB_CmSetKey_001();
if (v_verdict == pass) {
v_verdict = f_EVCC_getPLCLinkTermination(par_TP_match_leave, fail);
}
if (v_verdict == pass) {
v_verdict = f_EVCC_setPwmMode(e_PosVolt12);
}
sleep(par_CMN_waitForNextHAL);
if (v_verdict == pass) {
f_EVCC_changeValidStateCondition(E,E);
v_verdict = f_EVCC_setPwmMode(e_OscOff);
}
tc_T_step_EF.start(par_T_step_EF_min);
alt {
[] tc_T_step_EF.timeout {}
[] a_EVCC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or " &
"content was received.");
}
}
if (v_verdict == pass) {
f_EVCC_changeValidStateCondition(v_state,valid);
v_verdict = f_EVCC_setDutyCycle(v_dutyCycle);
}
sleep(par_CMN_waitForNextHAL);
if (v_verdict == pass) {
v_verdict = f_EVCC_setPwmMode(e_OscOn);
}
if (v_verdict == pass) {
timer statetimer = par_CMN_HAL_Timeout;
v_verdict = f_EVCC_confirmState(valid, v_HAL_61851_Listener,
statetimer, fail);
}
if (v_verdict == pass) {
tc_TT_EVSE_SLAC_init.start(par_TT_EVSE_SLAC_init_min);
f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
}
return getverdict;
}

function f_EVCC_CMN_TB_VTB_PLCLinkStatus_007() runs on EVCC_Tester
return verdicttype {
tc_TP_match_leave.start(par_TP_match_leave);
alt {
[] tc_TP_match_leave.timeout {}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or " &
"content was received.");
}
}
tc_TT_link_status_response.start;
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({
CM_NW_STATS_REQ = "6048"}),
md_CMN_CMN_CmNwStatsReq_001()))
to par_testSystem_plc_node_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_NW_STATS_CNF = "6049"}),
md_CMN_CMN_CmNwStatsCnf_001())) {
setverdict(fail,"The SUTs node was detected in the current " &
"logical network.");
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_NW_STATS_CNF = "6049"}),
md_CMN_CMN_CmNwStatsCnf_002())) {
setverdict(pass,"The SUTs node has left the current " &
"logical network.");
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or " &
"content was received.");
}
[] tc_TT_link_status_response.timeout {
setverdict(fail,"CM_NW_STATS timeout.");
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_PLCLinkStatus_008(in HAL_61851_Listener
v_HAL_61851_Listener)
runs on EVCC_Tester
return verdicttype {
var verdicttype v_verdict = pass;
var hexstring v_Nmk_old;
var hexstring v_Nid_old;
v_Nmk_old = vc_Nmk;
v_Nid_old = vc_Nid;
sleep(par_CMN_waitForConnectionLoss);
v_HAL_61851_Listener.stop;
v_HAL_61851_Listener.start(f_EVCC_HAL61851Listener(false));
// generate new Nid and Nmk
vc_Nmk = f_randomHexStringGen(32);
vc_Nid = fx_generateNID(vc_Nmk);
v_verdict = f_EVCC_CMN_TB_VTB_CmSetKey_001();
if (v_verdict == pass) {
v_verdict = f_EVCC_getPLCLinkTermination(par_TP_match_leave, fail);
}
// set old Nid and Nmk
if (v_verdict == pass) {
vc_Nmk = vc_Nmk;
vc_Nid = vc_Nid;
v_verdict = f_EVCC_CMN_TB_VTB_CmSetKey_001();
}
if (v_verdict == pass) {
v_verdict = f_EVCC_checkLeavingLogicalNetwork();
}
return getverdict;
}
function f_EVCC_AC_TB_VTB_PLCLinkStatus_001() runs on EVCC_Tester
return verdicttype {
var verdicttype v_verdict = pass;
sleep(par_CMN_waitForConnectionLoss);
// generate new Nid and Nmk
vc_Nmk = f_randomHexStringGen(32);
vc_Nid = fx_generateNID(vc_Nmk);
v_verdict = f_EVCC_CMN_TB_VTB_CmSetKey_001();
if (v_verdict == pass) {
v_verdict = f_EVCC_getPLCLinkTermination(par_TP_match_leave, fail);
}
tc_TconnResetup.start(PIXIT_EVCC_AC_TconnResetup);
alt {
[] tc_TconnResetup.timeout {}
[] a_EVCC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content " &
"was received.");
}
}
if (v_verdict == pass) {
tc_TT_EVSE_SLAC_init.start(par_TT_EVSE_SLAC_init_min);
v_verdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
}
return getverdict;
}
function f_EVCC_AC_TB_VTB_PLCLinkStatus_002(in HAL_61851_Listener
v_HAL_61851_Listener,
in IEC_61851_States v_state)
runs on EVCC_Tester
return verdicttype {
var verdicttype v_verdict = pass;
sleep(par_CMN_waitForConnectionLoss);
// generate new Nid and Nmk
vc_Nmk = f_randomHexStringGen(32);
vc_Nid = fx_generateNID(vc_Nmk);
v_verdict = f_EVCC_CMN_TB_VTB_CmSetKey_001();
if (v_verdict == pass) {
v_verdict = f_EVCC_getPLCLinkTermination(par_TP_match_leave, fail);
}
tc_TconnResetup.start(PIXIT_EVCC_AC_TconnResetup/2.0);
alt {
[] tc_TconnResetup.timeout {}
[] a_EVCC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content " &
"was received.");
}
}
if (v_verdict == pass) {
v_verdict = f_EVCC_setPwmMode(e_PosVolt12);
}
sleep(par_CMN_waitForNextHAL);
if (v_verdict == pass) {
f_EVCC_changeValidStateCondition(E,E);
v_verdict = f_EVCC_setPwmMode(e_OscOff);
}
tc_T_step_EF.start(par_T_step_EF_min);
alt {
[] tc_T_step_EF.timeout {}
[] a_EVCC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or " &
"content was received.");
}
}
if (v_verdict == pass) {
f_EVCC_changeValidStateCondition(v_state, valid);
v_verdict = f_EVCC_setDutyCycle(par_EVSENominalDutyCycle);
}
sleep(par_CMN_waitForNextHAL);
if (v_verdict == pass) {
v_verdict = f_EVCC_setPwmMode(e_OscOn);
}
if (v_verdict == pass) {
timer statetimer = par_CMN_HAL_Timeout;
v_verdict = f_EVCC_confirmState(valid, v_HAL_61851_Listener,
statetimer, fail);
}
if (v_verdict == pass) {
tc_TT_EVSE_SLAC_init.start(par_TT_EVSE_SLAC_init_min);
f_EVCC_CMN_TB_VTB_CmSlacParm_001(fail);
}
return getverdict;
}
}