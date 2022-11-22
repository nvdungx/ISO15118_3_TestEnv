#include "behaviorfunction/evcc_cmslacparm.hpp"
// import from Templates_CMN_CmSlacParm all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from Templates_CMN_CmStartAttenCharInd all;
// import from Templates_CMN_CmSlacParm all;
// import from Templates_SECC_CmAttenCharInd all;
// import from Templates_CMN_CmAttenCharRsp all;
// import from Templates_CMN_CmMnbcSoundInd all;
// import from Templates_CMN_CmSlacMatch all;
// import from Templates_CMN_CmValidate all;
// import from ComponentsAndPorts all;
// import from Timer_15118_3 all;
// import from Pixit_15118_3 all;
// import from Pics_15118_3 all;
// import from DataStructure_SLAC all;
// import from LibFunctions_15118_3 { group generalFunctions; };
// import from Services_HAL_61851 all;
// import from Services_PLCLinkStatus all;
// import from Timer_15118 all;
namespace TestLib {
VerdictValue f_EVCC_CMN_TB_VTB_CmSlacParm_001(VerdictValue v_vct) {

// runs on EVCC_Tester
//return VerdictValue
MME v_responseMessage;
MACAddress_TYPE v_address;
while(true){
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),MATCH_ANY)))) {
setverdict(pass,"CM_SLAC_PARM.REQ is correct.");
vc_RunID = v_responseMessage.mme_payload.payload.cm_slac_parm_req.runid;
}
if (a_EVCC_processPLCLinkNotifications_001()) {}
if (EVCC_Tester::pt_SLAC_Port->receive()) {
setverdict(v_vct, "Invalid message type or content was received.");
}
if (EVCC_Tester::tc_TT_EVSE_SLAC_init->timeout()) {
setverdict(v_vct,"TT_EVSE_SLAC_init timeout. SECC assumes that no SLAC will be performed.");
}
}
return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmSlacParm_002() {
// runs on EVCC_Tester return VerdictValue
MME v_responseMessage;
MACAddress_TYPE v_address;
integer v_count = 0;
while(true){
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),MATCH_ANY)))) {
//-> value v_responseMessage sender vc_sut_mac
vc
_RunID = v_responseMessage.mme_payload.payload.cm_slac_parm_req.runid;
if(v_count > 0){
setverdict(pass,"CM_SLAC_PARM.REQ message was repeated.",v_count);
}
v_count = v_count + 1;
EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
if(v_count > par_C_EV_match_retry) {
EVCC_Tester::tc_TT_match_sequence->stop();
EVCC_Tester::tc_TT_match_response->start(par_TT_match_response +
(2.0MATCH_SKIP par_CMN_Transmission_Delay));
while(true){
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),MATCH_ANY)))) {
//-> value v_responseMessage sender vc_sut_mac
setverdict(fail,"CM_SLAC_PARM.REQ message was repeated, but v_count > par_C_EV_match_retry.");
}
if (EVCC_Tester::pt_SLAC_Port->receive()) {
setverdict(fail, "Invalid message type or content was received.");
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
if (a_EVCC_processPLCLinkNotifications_001()) {}
if (EVCC_Tester::pt_SLAC_Port->receive()) {
setverdict(fail, "Invalid message type or content was received.");
}
if (EVCC_Tester::tc_TT_EVSE_SLAC_init->timeout()) {
setverdict(fail,"TT_EVSE_SLAC_init timeout. SECC assumes that no SLAC will be performed.");
}
if (EVCC_Tester::tc_TT_match_sequence->timeout()) {
setverdict(fail,"TT_match_sequence timeout. CM_SLAC_PARM.REQ message was not repeated.");
}
}
return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmSlacParm_003(template(present) MME_Payload invalidPayload) {

// runs on EVCC_Tester return VerdictValue
MME v_responseMessage;
MACAddress_TYPE v_address;
integer v_count = 0;
while(true){
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),MATCH_ANY)))) {
//-> value v_responseMessage sender vc_sut_mac
vc_RunID = v_responseMessage.mme_payload.payload.cm_slac_parm_req.runid;
if(not(ispresent(invalidPayload.payload.cm_slac_parm_cnf.runid))) {
invalidPayload.payload.cm_slac_parm_cnf.runid = vc_RunID;
}
if(not(ispresent(invalidPayload.payload.cm_slac_parm_cnf.forwarding_sta))) {
invalidPayload.payload.cm_slac_parm_cnf.forwarding_sta = vc_sut_mac;
}
if(v_count > 0){
setverdict(pass,"CM_SLAC_PARM.REQ message was repeated.",v_count);
}
v_count = v_count + 1;
EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
// send invalid CM_SLAC_PARM.CNF message
EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}), invalidPayload)); //to vc_sut_mac;
if(v_count > par_C_EV_match_retry) {
EVCC_Tester::tc_TT_match_sequence->stop();
EVCC_Tester::tc_TT_match_response->start(par_TT_match_response +
(2.0MATCH_SKIP par_CMN_Transmission_Delay));
while(true){
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),MATCH_ANY)))) {
//-> value v_responseMessage sender vc_sut_mac
setverdict(fail,"CM_SLAC_PARM.REQ message was repeated, but v_count > par_C_EV_match_retry.");
}
if (EVCC_Tester::pt_SLAC_Port->receive()) {
setverdict(fail, "Invalid message type or content was received.");
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
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_START_ATTEN_CHAR_IND = "606A"}),
md_CMN_CMN_CmStartAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),MATCH_ANY,MATCH_ANY, "01",MATCH_ANY, vc_RunID)))) {
//-> value v_responseMessage
setverdict(fail,"CM_START_ATTEN_CHAR.IND message was received but not expected.");
}
if (a_EVCC_processPLCLinkNotifications_001()) {}
if (EVCC_Tester::pt_SLAC_Port->receive()) {
setverdict(fail, "Invalid message type or content was received.");
}
if (EVCC_Tester::tc_TT_EVSE_SLAC_init->timeout()) {
setverdict(fail,"TT_EVSE_SLAC_init timeout. SECC assumes that no SLAC will be performed.");
}
if (EVCC_Tester::tc_TT_match_sequence->timeout()) {
setverdict(fail,"TT_match_sequence timeout. CM_SLAC_PARM.REQ message was not repeated.");
}
}
return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmSlacParm_004() {
// runs on EVCC_Tester return VerdictValue
MME v_responseMessage;
MACAddress_TYPE v_address;
boolean v_isInvalidMes = false;
SourceRnd_Type v_source_rnd = f_randomHexStringGen(32);
timer t;
while(true){
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),MATCH_ANY)))) {
//-> value v_responseMessage sender vc_sut_mac
setverdict(pass,"CM_SLAC_PARM.REQ is correct.");
t.start(par_TT_EV_atten_results);
vc_RunID = v_responseMessage.mme_payload.payload.cm_slac_parm_req.runid;
// send CM_SLAC_PARM.REQ message
EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))); //to vc_sut_mac;
// send CM_START_ATTEN_CHAR.IND message
EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_START_ATTEN_CHAR_IND = "606A"}),
md_CMN_CMN_CmStartAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), "0A",
"06", "01", par_testSystem_mac, vc_RunID))); //to vc_sut_mac;
// send CM_MNBC_SOUND.IND message
EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_MNBC_SOUND_IND = "6076"}),
md_CMN_CMN_CmMnbcSoundInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
int2hex(10,2), vc_RunID, v_source_rnd))); //to vc_sut_mac;
// send CM_ATTEN_CHAR.RSP message
EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ="606F"}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(par_testSystem_mac, vc_RunID)))); //to vc_sut_mac;
// send CM_VALIDATE.REQ message
EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001())); //to vc_sut_mac;
// send message
EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = "607C"}),
md_CMN_CMN_CmSlacMatchReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), par_testSystem_mac,
vc_sut_mac, vc_RunID))); //to vc_sut_mac;
while(true) {
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),MATCH_ANY)))) {
repeat;
}
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),MATCH_ANY))) {
v_isInvalidMes = true;
}
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = "606E"}),MATCH_ANY))) {
v_isInvalidMes = true;
}
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),MATCH_ANY))) {
v_isInvalidMes = true;
}
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_CNF = "607D"}),MATCH_ANY))) {
v_isInvalidMes = true;
}
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),MATCH_ANY))) {
v_isInvalidMes = true;
}
if (EVCC_Tester::pt_SLAC_Port->receive()) {
setverdict(fail, "Invalid message type or content was received.");
}
if (t.timeout()) {
setverdict(pass,"The SUT did not respond to the EVCC messages.");
}
}
if (v_isInvalidMes) {
setverdict(fail, "The EVCC shall not respond to the following messages: CM_SLAC_PARM.REQ, CM_START_ATTEN_CHAR.IND, CM_MNBC_SOUND.IND, CM_ATTEN_CHAR.RSP, CM_VALIDATE.REQ, CM_SLAC_MATCH.REQ.");
}
}
if (a_EVCC_processPLCLinkNotifications_001()) {}
if (EVCC_Tester::pt_SLAC_Port->receive()) {
setverdict(fail, "Invalid message type or content was received.");
}
if (EVCC_Tester::tc_TT_EVSE_SLAC_init->timeout()) {
setverdict(fail,"TT_EVSE_SLAC_init timeout. SECC assumes that no SLAC will be performed.");
}
}
return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmSlacParm_005() {
// runs on EVCC_Tester return VerdictValue
MME v_responseMessage;
MACAddress_TYPE v_address;
integer v_count = 0;
EVCC_Tester::tc_TP_matching_repetition->start(par_TT_matching_repetition);
while(true){
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),MATCH_ANY)))) {
//-> value v_responseMessage sender vc_sut_mac
vc_RunID = v_responseMessage.mme_payload.payload.cm_slac_parm_req.runid;
if(v_count > 0){
setverdict(pass,"CM_SLAC_PARM.REQ message was repeated.",v_count);
}
EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
v_count = v_count + 1;
if(v_count > par_C_EV_match_retry) {
EVCC_Tester::tc_TT_match_sequence->stop();
EVCC_Tester::tc_TT_match_response->start(par_TT_match_response +
(2.0MATCH_SKIP par_CMN_Transmission_Delay));
while(true){
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),MATCH_ANY)))) {
//-> value v_responseMessage sender vc_sut_mac
setverdict(fail,"CM_SLAC_PARM.REQ message was repeated, but v_count > par_C_EV_match_retry.");
}
if (EVCC_Tester::pt_SLAC_Port->receive()) {
setverdict(fail, "Invalid message type or content was received.");
}
if (EVCC_Tester::tc_TT_match_response->timeout()) {
setverdict(pass,"TT_match_response timeout. The total number of retries is reached, the Matching process shall be considered as FAILED.");
EVCC_Tester::tc_TP_matching_rate->start(PIXIT_EVCC_CMN_TTMatchingRate +
par_CMN_Transmission_Delay);
if(tc_TP_matching_repetition.running) {
v_count = 0;
repeat;
}
else {
while(true){
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),MATCH_ANY)))) {
//-> value v_responseMessage sender vc_sut_mac
setverdict(fail,"CM_SLAC_PARM.REQ message was repeated, but tc_TP_matching_repetition timer has expired.");
}
if (EVCC_Tester::pt_SLAC_Port->receive()) {
setverdict(fail, "Invalid message type or content was received.");
}
if (EVCC_Tester::tc_TP_matching_rate->timeout()) {
setverdict(pass,"SUT did not start a new matching process aftertc_TP_matching_repetition timeout.");
}
}
}
}
}
}
else{
repeat;
}
}
if (a_EVCC_processPLCLinkNotifications_001()) {}
if (EVCC_Tester::pt_SLAC_Port->receive()) {
setverdict(fail, "Invalid message type or content was received.");
}
if (EVCC_Tester::tc_TT_EVSE_SLAC_init->timeout()) {
setverdict(fail,"TT_EVSE_SLAC_init timeout. SECC assumes that no SLAC will be performed.");
}
if (EVCC_Tester::tc_TT_match_sequence->timeout()) {
setverdict(fail,"TT_match_sequence timeout. CM_SLAC_PARM.REQ message was not repeated.");
}
if (EVCC_Tester::tc_TP_matching_rate->timeout()) {
setverdict(fail,"TP_matching_rate timeout. SUT did not start a new matching process.");
}
}
return EVCC_Tester::getverdict();
}
}