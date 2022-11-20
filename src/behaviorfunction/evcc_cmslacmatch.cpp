#include "behaviorfunction/evcc_cmslacmatch.hpp"

// import from Templates_CMN_CmSlacMatch all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from ComponentsAndPorts all;
// import from Timer_15118_3 all;
// import from Pics_15118_3 all;
// import from DataStructure_SLAC all;
// import from Templates_CMN_CmSlacParm all;
// import from Timer_15118 all;
namespace TestLib {
VerdictValue f_EVCC_CMN_TB_VTB_CmSlacMatch_001() runs on EVCC_Tester return VerdictValue {
while(true) {
[] EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = "607C"}),
md_CMN_CMN_CmSlacMatchReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac,
par_testSystem_mac, vc_RunID))) {
setverdict(pass,"CM_SLAC_MATCH.REQ is correct.");
if(tc_TT_EVSE_match_session.running) {
EVCC_Tester::tc_TT_EVSE_match_session->stop();
}
else {
EVCC_Tester::tc_TT_match_sequence->stop();
}
}
[] EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),MATCH_ANY))) {
setverdict(inconc,"CM_SLAC_PARM.REQ message was received. New Matching process is started.");
}
[] EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP = "606F"}),MATCH_ANY)) {
// CM_ATTEN_CHAR.RSP messages will be ignored!
repeat;
}
[] EVCC_Tester::pt_SLAC_Port->receive {
setverdict(fail, "Invalid message type or content was received.");
}
if (EVCC_Tester::tc_TT_EVSE_match_session->timeout()) {
setverdict(fail,"TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
}
if (EVCC_Tester::tc_TT_match_sequence->timeout()) {
setverdict(fail,"TT_match_sequence timeout. Matching process shall be considered as FAILED.");
}
}
return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmSlacMatch_002() runs on EVCC_Tester return VerdictValue {
MME v_responseMessage;
MACAddress_TYPE v_address;
integer v_count = 0;
boolean v_stopLnkStatus = false;
v_count = v_count + 1;
EVCC_Tester::tc_TT_match_response->start(par_TT_match_response + par_CMN_Transmission_Delay);
while(true){
[]EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = "607C"}),
md_CMN_CMN_CmSlacMatchReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac,
par_testSystem_mac, vc_RunID))) {
v_count = v_count + 1;
EVCC_Tester::tc_TT_match_response->start(par_TT_match_response + par_CMN_Transmission_Delay);
if(v_count > par_C_EV_match_retry) {
while(true){
[] EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = "607C"}),
md_CMN_CMN_CmSlacMatchReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac,
par_testSystem_mac, vc_RunID))) {
setverdict(fail,"CM_SLAC_MATCH.REQ message was repeated, but v_count > par_C_EV_match_retry.");
}
if (EVCC_Tester::tc_TT_match_response->timeout()) {
setverdict(pass,"TT_match_response timeout. The total number of retries is reached, the Matching process shall be considered as FAILED.");
}
}
}
else{
repeat;
}
}
[] EVCC_Tester::pt_SLAC_Port->receive {
setverdict(fail, "Invalid message type or content was received.");
}
if (EVCC_Tester::tc_TT_EVSE_match_session->timeout()) {
setverdict(fail,"TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
}
if (EVCC_Tester::tc_TT_match_response->timeout()) {
setverdict(fail,"TT_match_response timeout. CM_SLAC_MATCH.REQ message was not repeated.");
}
}
return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmSlacMatch_003(in template(present) MME_Payload mmePayload)
runs on EVCC_Tester return VerdictValue {
MME v_responseMessage;
MACAddress_TYPE v_address;
integer v_count = 0;
boolean v_stopLnkStatus = false;
v_count = v_count + 1;
EVCC_Tester::tc_TT_match_response->start(par_TT_match_response + par_CMN_Transmission_Delay);
// send invalid CM_SLAC_MATCH.CNF message
EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_CNF = "607D"}),
mmePayload)) to vc_sut_mac;
while(true){
[]EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = "607C"}),
md_CMN_CMN_CmSlacMatchReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac,
par_testSystem_mac, vc_RunID))) {
v_count = v_count + 1;
EVCC_Tester::tc_TT_match_response->start(par_TT_match_response + par_CMN_Transmission_Delay);
// send invalid CM_SLAC_MATCH.CNF message
EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_CNF = "607D"}),
mmePayload)) to vc_sut_mac;
if(v_count > par_C_EV_match_retry) {
while(true){
[]EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = "607C"}),
md_CMN_CMN_CmSlacMatchReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac,
par_testSystem_mac, vc_RunID))) {
setverdict(fail,"CM_SLAC_MATCH.REQ message was repeated, but v_count > par_C_EV_match_retry.");
}
if (EVCC_Tester::tc_TT_match_response->timeout()) {
setverdict(pass,"TT_match_response timeout. The total number of retries is reached, the Matching process shall be considered as FAILED");
}
}
}
else{
repeat;
}
}
[] EVCC_Tester::pt_SLAC_Port->receive {
setverdict(fail, "Invalid message type or content was received.");
}
if (EVCC_Tester::tc_TT_EVSE_match_session->timeout()) {
setverdict(fail,"TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
}
if (EVCC_Tester::tc_TT_match_response->timeout()) {
setverdict(fail,"TT_match_response timeout. CM_SLAC_MATCH.REQ message was not repeated.");
}
}
return EVCC_Tester::getverdict();
}
}