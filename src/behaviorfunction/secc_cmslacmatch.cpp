#include "behaviorfunction/secc_cmslacmatch.hpp"
// import from Timer_15118_3 all;
// import from Pics_15118 all;
// import from Pics_15118_3 all;
// import from Pixit_15118_3 all;
// import from Templates_CMN_CmSlacMatch all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from ComponentsAndPorts all;
// import from DataStructure_SLAC all;
// import from DataStructure_HAL_61851 all;
// import from Services_HAL_61851 all;
// import from Templates_CMN_CmAttenCharRsp all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from Services_PLCLinkStatus all;
// import from Timer_15118 all;
namespace TestLib {

function f_SECC_CMN_TB_VTB_CmSlacMatch_001(in verdicttype v_vct)
runs on SECC_Tester
return verdicttype {
var MME v_responseMessage;
var boolean v_repetition = true;
var integer v_counter = 0;
while(v_repetition){
tc_TT_match_response.start(par_TT_match_response);
v_counter = v_counter + 1;
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = '607C'H}),
md_CMN_CMN_CmSlacMatchReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_sut_mac, vc_RunID)))
to vc_sut_mac;
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_CNF = '607D'H}),
md_CMN_CMN_CmSlacMatchCnf_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_sut_mac, vc_RunID, ?, ?)))
-> value v_responseMessage {
setverdict(pass,"CM_SLAC_MATCH is correct.");
vc_Nid = v_responseMessage.mme_payload.payload.cm_slac_match_cnf.nid;
vc_Nmk = v_responseMessage.mme_payload.payload.cm_slac_match_cnf.nmk;
v_repetition = false;
tc_TT_match_response.stop;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),?)) {
tc_TT_match_response.stop;
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(
par_testSystem_mac, vc_RunID))))
to vc_sut_mac;
log("A further CM_ATTEN_CHAR.IND message was received. " &
"A new CM_ATTEN_CHAR.RSP has to be send.");
repeat;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(v_vct, "Invalid message type or content was received.");
v_repetition = false;
}
[] tc_TT_match_response.timeout {
log("TT_match_response timeout.");
if(v_counter mod (par_C_EV_match_retry+1) == 0){
setverdict(v_vct,"The repetition limit is reached. " &
"The Matching process is considered " &
"as FAILED.");
v_repetition = false;
} else {
log("The repetition limit is not reached, " &
"a new CM_SLAC_MATCH.REQ message will be send.");
}
}
[] tc_TT_matching_repetition.timeout {
log("TT_matching_repetition timeout - " &
"No new matching process can be started, " &
"if the current matching process fails.");
repeat;
}
}
}
return getverdict;
}
function f_SECC_CMN_TB_VTB_CmSlacMatch_002() runs on SECC_Tester return verdicttype {
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = '607C'H}),
md_CMN_CMN_CmSlacMatchReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_sut_mac, vc_RunID)))
to vc_sut_mac;
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_CNF = '607D'H}),
md_CMN_CMN_CmSlacMatchCnf_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_sut_mac, vc_RunID, ?, ?))) {
repeat;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),?)) {
tc_TT_match_response.stop;
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(
par_testSystem_mac, vc_RunID))))
to vc_sut_mac;
log("A further CM_ATTEN_CHAR.IND message was received. " &
"A new CM_ATTEN_CHAR.RSP has to be send.");
repeat;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_response.timeout {
// retransmitting CM_SLAC_MATCH.REQ message
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = '607C'H}),
md_CMN_CMN_CmSlacMatchReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_sut_mac, vc_RunID)))
to vc_sut_mac;
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_CNF = '607D'H}),
md_CMN_CMN_CmSlacMatchCnf_001(
m_CMN_CMN_SlacPayloadHeader_001(), par_testSystem_mac,
vc_sut_mac, vc_RunID, ?, ?))) {
tc_TT_match_response.stop;
setverdict(pass,"TT_match_response timeout. " &
"CM_SLAC_MATCH.CNF was retransmitted.");
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_response.timeout {
setverdict(fail,"TT_match_response timeout. " &
"CM_SLAC_MATCH.CNF was not retransmitted.");
}
}
}
[] tc_TT_matching_repetition.timeout {
log("TT_matching_repetition timeout - " &
"No new matching process can be started, " &
"if the current matching process fails.");
repeat;
}
}
return getverdict;
}
function f_SECC_CMN_TB_VTB_CmSlacMatch_003() runs on SECC_Tester return verdicttype {
var charstring v_timer_name;
if(PIXIT_SECC_CMN_CmValidate == cmValidate) {
v_timer_name = "TT_match_sequence";
tc_TT_match_sequence.start(par_TT_match_sequence +
par_CMN_Transmission_Delay);
// wait until TT_match_sequence timer expires
alt {
[] tc_TT_match_sequence.timeout;
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_matching_repetition.timeout {
log("TT_matching_repetition timeout - " &
"No new matching process can be started, " &
"if the current matching process fails.");
repeat;
}
}
}
else {
v_timer_name = "TT_EVSE_match_session";
tc_TT_EVSE_match_session.start(par_TT_EVSE_match_session +
par_CMN_Transmission_Delay);
// wait until TT_EVSE_match_session timer expires
alt {
[] tc_TT_EVSE_match_session.timeout;
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_matching_repetition.timeout {
log("TT_matching_repetition timeout - " &
"No new matching process can be started, " &
"if the current matching process fails.");
repeat;
}
}
}
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = '607C'H}),
md_CMN_CMN_CmSlacMatchReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_sut_mac, vc_RunID)))
to vc_sut_mac;
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_CNF = '607D'H}),
md_CMN_CMN_CmSlacMatchCnf_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_sut_mac, vc_RunID, ?, ?))) {
setverdict(fail,"CM_SLAC_MATCH.CNF was not expected, " & v_timer_name &
" timer has been expired.");
tc_TT_match_response.stop;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),?)) {
tc_TT_match_response.stop;
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(
par_testSystem_mac, vc_RunID))))
to vc_sut_mac;
log("A further CM_ATTEN_CHAR.IND message was received. " &
"A new CM_ATTEN_CHAR.RSP has to be send.");
repeat;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_response.timeout {
setverdict(pass,"TT_match_response timeout. " &
"Matching process is considered as FAILED.");
}
[] tc_TT_matching_repetition.timeout {
log("TT_matching_repetition timeout - " &
"No new matching process can be started, " &
"if the current matching process fails.");
repeat;
}
}
return getverdict;
}
function f_SECC_CMN_TB_VTB_CmSlacMatch_004(in template MME_Payload v_payload)
runs on SECC_Tester return verdicttype {
timer v_timer;
var charstring v_timer_name;
if(PIXIT_SECC_CMN_CmValidate == cmValidate) {
v_timer_name = "TT_match_sequence";
v_timer.start(par_TT_match_sequence + par_CMN_Transmission_Delay);
}
else {
v_timer_name = "TT_EVSE_match_session";
v_timer.start(par_TT_EVSE_match_session + par_CMN_Transmission_Delay);
}
// send invalid CM_SLAC_MATCH.REQ message
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = '607C'H}), v_payload))
to vc_sut_mac;
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_CNF = '607D'H}),?)) {
setverdict(fail,"Invalid CM_SLAC_MATCH.REQ messages shall be ignored.");
tc_TT_EVSE_match_session.stop;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),?)) {
tc_TT_match_response.stop;
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(
par_testSystem_mac, vc_RunID))))
to vc_sut_mac;
log("A further CM_ATTEN_CHAR.IND message was received. " &
"A new CM_ATTEN_CHAR.RSP has to be send.");
repeat;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] v_timer.timeout {
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = '607C'H}),
md_CMN_CMN_CmSlacMatchReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_sut_mac, vc_RunID)))
to vc_sut_mac;
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_CNF = '607D'H}),
md_CMN_CMN_CmSlacMatchCnf_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_sut_mac, vc_RunID, ?, ?))) {
setverdict(fail,"CM_SLAC_MATCH.CNF was not expected, "
& v_timer_name & " has been expired.");
tc_TT_match_response.stop;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),?)) {
// CM_ATTEN_CHAR.IND messages will be ignored!
repeat;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_response.timeout {
setverdict(pass,"TT_match_response timeout. " &
"Matching process is considered as FAILED.");
}
[] tc_TT_matching_repetition.timeout {
log("TT_matching_repetition timeout - " &
"No new matching process can be started, " &
"if the current matching process fails.");
repeat;
}
}
}
}
return getverdict;
}
function f_SECC_CMN_TB_VTB_CmSlacMatch_005(in HAL_61851_Listener v_HAL_61851_Listener)
runs on SECC_Tester return verdicttype {
f_SECC_changeValidStateCondition(invalid);
f_SECC_changeValidFrequencyRange(0,0);
f_SECC_changeValidDutyCycleRange(100,100);
deactivate(vc_Default_IEC_61851_ListenerBehavior);
f_SECC_setState(A,v_HAL_61851_Listener);
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = '607C'H}),
md_CMN_CMN_CmSlacMatchReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_sut_mac, vc_RunID)))
to vc_sut_mac;
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_CNF = '607D'H}),
md_CMN_CMN_CmSlacMatchCnf_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_sut_mac,
vc_RunID, ?, ?))) {
setverdict(fail,"CM_SLAC_MATCH.CNF message was not expected." &
"CP State A should be detected before.");
tc_TT_match_response.stop;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),?)) {
tc_TT_match_response.stop;
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(
par_testSystem_mac, vc_RunID))))
to vc_sut_mac;
log("A further CM_ATTEN_CHAR.IND message was received. " &
"A new CM_ATTEN_CHAR.RSP has to be send.");
repeat;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_response.timeout {
setverdict(pass,"TT_match_response timer has expired, " &
"the Matching process was terminated " &
"by the SUT.");
}
[] tc_TT_matching_repetition.timeout {
log("TT_matching_repetition timeout - " &
"No new matching process can be started, " &
"if the current matching process fails.");
repeat;
}
}
return getverdict;
}
}