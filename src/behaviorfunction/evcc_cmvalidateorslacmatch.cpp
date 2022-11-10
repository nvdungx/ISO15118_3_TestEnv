#include "behaviorfunction/evcc_cmvalidateorslacmatch.hpp"

// import from Timer_15118_3 all;
// import from Pics_15118_3 all;
// import from Templates_CMN_CmValidate all;
// import from Templates_CMN_CmStartAttenCharInd all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from Templates_CMN_CmMnbcSoundInd all;
// import from Templates_CMN_CmAttenCharRsp all;
// import from Templates_EVCC_CmAttenCharInd all;
// import from Templates_EVCC_CmAttenProfileInd all;
// import from Templates_CMN_CmSlacParm all;
// import from ComponentsAndPorts all;
// import from DataStructure_SLAC all;
// import from TestBehavior_EVCC_AttenuationCharacterization all;
// import from TestBehavior_EVCC_CmValidate all;
// import from LibFunctions_15118_3 { group generalFunctions; }
// import from Services_HAL_61851 all;
// import from Templates_CMN_CmSlacParm all;
// import from Templates_CMN_HAL61851 all;
// import from DataStructure_HAL_61851 all;
// import from Templates_CMN_CmSlacMatch all;
// import from Timer_15118 all;
namespace TestLib {
function f_EVCC_CMN_TB_VTB_CmValidateOrCmSlacMatch_001(in HAL_61851_Listener
v_HAL_61851_Listener,
in verdicttype v_vct)
runs on EVCC_Tester
return verdicttype {
var MME v_requestMessage;
var integer cnt = 0;
var boolean isStep2 = false;
var float v_TT_EVSE_vald_toggle;
var boolean isCmValidate = false;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = '607C'H}),
md_CMN_CMN_CmSlacMatchReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),
vc_sut_mac, par_testSystem_mac,
vc_RunID))) {
setverdict(pass,"CM_SLAC_MATCH.REQ is correct.");
tc_TT_EVSE_match_session.stop;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
md_CMN_CMN_CmValidateReq_004(?,?,?)))
-> value v_requestMessage {
var PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.
cm_validate_req.vrVarField.pilot_timer;
var SignalType_TYPE p_signalType = v_requestMessage.mme_payload.payload.
cm_validate_req.signalType;
if((p_signalType != "00")) {
setverdict(v_vct,"Step 1 CM_VALIDATE.REQ is not correct. Invalid " &
"signalType was detected.");
}
tc_TT_EVSE_match_session.stop;
if(v_pilotTimer == "00") {
if(not isStep2) {
setverdict(pass,"Step 1 CM_VALIDATE.REQ is correct.");
isStep2 = true;
}
else {
log("Step 2 CM_VALIDATE.REQ message contains timer field equal to zero. " &
"Step 1 CM_VALIDATE.CNF will be resent.");
}
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(
par_cmValidate_result_ready)))
to vc_sut_mac;
tc_TT_match_sequence.start(par_TT_match_sequence);
repeat;
}
else if(decodeValdToggleTime(v_pilotTimer) >= par_TP_EV_vald_toggle_min and
decodeValdToggleTime(v_pilotTimer) <= par_TP_EV_vald_toggle_max and
isStep2) {
setverdict(pass,"Step 2 CM_VALIDATE.REQ is correct.");
tc_TT_match_sequence.stop;
v_TT_EVSE_vald_toggle = decodeValdToggleTime(v_pilotTimer);
// BCB toggle sequence detection
tc_TT_EVSE_vald_toggle.start(v_TT_EVSE_vald_toggle);
f_EVCC_changeValidStateCondition(B,C);
timer statetimer = (par_T_vald_state_duration_max + par_CMN_Transmission_Delay);
statetimer.start;
var integer toggleCnt = 0;
alt {
[] a_EVCC_BCBToggleDetection(pt_HAL_61851_Internal_Port, B){
statetimer.stop;
toggleCnt = toggleCnt + 1;
f_EVCC_changeValidStateCondition(B,C);
repeat;
}
[] a_EVCC_BCBToggleDetection(pt_HAL_61851_Internal_Port, C){
statetimer.stop;
f_EVCC_changeValidStateCondition(C,B);
statetimer.start(par_T_vald_state_duration_max);
repeat;
}
[] pt_HAL_61851_Internal_Port.receive {
setverdict(v_vct, "Received state has an invalid value.");
}
[] statetimer.timeout {
setverdict(v_vct, "The EVSE could not detect the corresponding " &
"toggle value within the " &
"maximal valid state duration.");
}
[] tc_TT_EVSE_vald_toggle.timeout {
if(toggleCnt > 0 and toggleCnt <= 3) {
setverdict(pass,"Valid BCB toggle sequence could be detected.");
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_002(
int2hex(toggleCnt,2),
par_cmValidate_result_success)))
to vc_sut_mac;
f_EVCC_changeValidStateCondition(C,B);
tc_TT_match_sequence.start(par_TT_match_sequence);
}
else {
setverdict(v_vct,"Invalid BCB toggle sequence was detected.");
}
}
}
if(getverdict == pass) {
repeat;
}
}
else {
setverdict(v_vct, "Invalid message content was " &
"received from the SUT.");
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
mw_CMN_CMN_CmValidateReq_003())) {
setverdict(v_vct,"Result field is not set to 'Ready'. " &
"Matching process is " &
"considered as FAILED.");
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?))) {
setverdict(inconc,"CM_SLAC_PARM.REQ message was received. " &
"New Matching process is started.");
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
  md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP = '606F'H}),?)) {
// CM_ATTEN_CHAR.RSP messages will be ignored!
repeat;
}
[] pt_SLAC_Port.receive {
setverdict(v_vct, "Invalid message type or content was received.");
}
[] tc_TT_match_sequence.timeout {
if(isCmValidate) {
cnt = cnt +1;
log("TT_match_sequence timeout.");
if (cnt > par_C_EV_match_retry) {
setverdict(v_vct,"Repetition limit is reached. " &
"Matching process is " &
"considered as FAILED.");
}
else {
log("A new CM_VALIDATE.CNF message will be sent.");
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(
par_cmValidate_result_ready)))
to vc_sut_mac;
tc_TT_match_sequence.start(par_TT_match_sequence);
repeat;
}
}
else {
setverdict(v_vct,"TT_match_sequence timeout. Matching process " &
"shall be considered as FAILED.");
}
}
[] tc_TT_EVSE_match_session.timeout {
setverdict(v_vct,"TT_EVSE_match_session timeout. Matching process " &
"shall be considered as FAILED.");
}
}
return getverdict;
}
}