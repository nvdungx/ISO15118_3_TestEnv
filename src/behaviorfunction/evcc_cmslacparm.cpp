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
function f_EVCC_CMN_TB_VTB_CmSlacParm_001(in verdicttype v_vct)
runs on EVCC_Tester
return verdicttype {
var MME v_responseMessage;
var MACAddress_TYPE v_address;
alt{
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?)))
-> value v_responseMessage
sender vc_sut_mac {
setverdict(pass,"CM_SLAC_PARM.REQ is correct.");
vc_RunID = v_responseMessage.mme_payload.payload.cm_slac_parm_req.runid;
}
[] a_EVCC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(v_vct, "Invalid message type or content was received.");
}
[] tc_TT_EVSE_SLAC_init.timeout {
setverdict(v_vct,"TT_EVSE_SLAC_init timeout. SECC assumes that no SLAC " &
"will be performed.");
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmSlacParm_002() runs on EVCC_Tester return verdicttype {
var MME v_responseMessage;
var MACAddress_TYPE v_address;
var integer v_count = 0;
alt{
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?)))
-> value v_responseMessage sender vc_sut_mac {
vc
_RunID = v_responseMessage.mme_payload.payload.cm_slac_parm_req.runid;
if(v_count > 0){
setverdict(pass,"CM_SLAC_PARM.REQ message was repeated.",v_count);
}
v_count = v_count + 1;
tc_TT_match_sequence.start(par_TT_match_sequence);
if(v_count > par_C_EV_match_retry) {
tc_TT_match_sequence.stop;
tc_TT_match_response.start(par_TT_match_response +
(2.0 * par_CMN_Transmission_Delay));
alt{
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?)))
-> value v_responseMessage sender vc_sut_mac {
setverdict(fail,"CM_SLAC_PARM.REQ message was repeated, but v_count > " &
"par_C_EV_match_retry.");
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_response.timeout {
setverdict(pass,"TT_match_response timeout. " &
"The total number of retries is reached, " &
"the Matching process " &
"shall be considered as FAILED.");
}
}
}
else{
repeat;
}
}
[] a_EVCC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EVSE_SLAC_init.timeout {
setverdict(fail,"TT_EVSE_SLAC_init timeout. SECC assumes " &
"that no SLAC will be performed.");
}
[] tc_TT_match_sequence.timeout {
setverdict(fail,"TT_match_sequence timeout. " &
"CM_SLAC_PARM.REQ message was not repeated.");
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmSlacParm_003(in template(present) MME_Payload invalidPayload)
runs on EVCC_Tester return verdicttype {
var MME v_responseMessage;
var MACAddress_TYPE v_address;
var integer v_count = 0;
alt{
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?)))
-> value v_responseMessage sender vc_sut_mac {
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
tc_TT_match_sequence.start(par_TT_match_sequence);
// send invalid CM_SLAC_PARM.CNF message
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}), invalidPayload))
to vc_sut_mac;
if(v_count > par_C_EV_match_retry) {
tc_TT_match_sequence.stop;
tc_TT_match_response.start(par_TT_match_response +
(2.0 * par_CMN_Transmission_Delay));
alt{
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?)))
-> value v_responseMessage sender vc_sut_mac {
setverdict(fail,"CM_SLAC_PARM.REQ message was repeated, but v_count > " &
"par_C_EV_match_retry.");
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_response.timeout {
setverdict(pass,"TT_match_response timeout. " &
"The total number of retries is reached, " &
"the Matching process " &
"shall be considered as FAILED.");
}
}
}
else{
repeat;
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_START_ATTEN_CHAR_IND = '606A'H}),
md_CMN_CMN_CmStartAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?, ?, "01", ?, vc_RunID)))
-> value v_responseMessage {
setverdict(fail,"CM_START_ATTEN_CHAR.IND message was received but not expected.");
}
[] a_EVCC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EVSE_SLAC_init.timeout {
setverdict(fail,"TT_EVSE_SLAC_init timeout. SECC assumes " &
"that no SLAC will be performed.");
}
[] tc_TT_match_sequence.timeout {
setverdict(fail,"TT_match_sequence timeout. " &
"CM_SLAC_PARM.REQ message was not repeated.");
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmSlacParm_004() runs on EVCC_Tester return verdicttype {
var MME v_responseMessage;
var MACAddress_TYPE v_address;
var boolean v_isInvalidMes = false;
var SourceRnd_Type v_source_rnd = f_randomHexStringGen(32);
timer t;
alt{
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?)))
-> value v_responseMessage sender vc_sut_mac {
setverdict(pass,"CM_SLAC_PARM.REQ is correct.");
t.start(par_TT_EV_atten_results);
vc_RunID = v_responseMessage.mme_payload.payload.cm_slac_parm_req.runid;
// send CM_SLAC_PARM.REQ message
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID)))
to vc_sut_mac;
// send CM_START_ATTEN_CHAR.IND message
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_START_ATTEN_CHAR_IND = '606A'H}),
md_CMN_CMN_CmStartAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), '0A'H,
"06", "01", par_testSystem_mac, vc_RunID)))
to vc_sut_mac;
// send CM_MNBC_SOUND.IND message
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_MNBC_SOUND_IND = "6076"}),
md_CMN_CMN_CmMnbcSoundInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
int2hex(10,2), vc_RunID, v_source_rnd)))
to vc_sut_mac;
// send CM_ATTEN_CHAR.RSP message
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(par_testSystem_mac, vc_RunID))))
to vc_sut_mac;
// send CM_VALIDATE.REQ message
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001()))
to vc_sut_mac;
// send message
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = '607C'H}),
md_CMN_CMN_CmSlacMatchReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), par_testSystem_mac,
vc_sut_mac, vc_RunID)))
to vc_sut_mac;
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?))) {
repeat;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),?)) {
v_isInvalidMes = true;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),?)) {
v_isInvalidMes = true;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),?)) {
v_isInvalidMes = true;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_CNF = '607D'H}),?)) {
v_isInvalidMes = true;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),?)) {
v_isInvalidMes = true;
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] t.timeout {
setverdict(pass,"The SUT did not respond to the EVCC messages.");
}
}
if (v_isInvalidMes) {
setverdict(fail, "The EVCC shall not respond to the following messages: " &
"CM_SLAC_PARM.REQ, CM_START_ATTEN_CHAR.IND, " &
"CM_MNBC_SOUND.IND, CM_ATTEN_CHAR.RSP, CM_VALIDATE.REQ, " &
"CM_SLAC_MATCH.REQ.");
}
}
[] a_EVCC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EVSE_SLAC_init.timeout {
setverdict(fail,"TT_EVSE_SLAC_init timeout. SECC assumes " &
"that no SLAC will be performed.");
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmSlacParm_005() runs on EVCC_Tester return verdicttype {
var MME v_responseMessage;
var MACAddress_TYPE v_address;
var integer v_count = 0;
tc_TP_matching_repetition.start(par_TT_matching_repetition);
alt{
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?)))
-> value v_responseMessage sender vc_sut_mac {
vc_RunID = v_responseMessage.mme_payload.payload.cm_slac_parm_req.runid;
if(v_count > 0){
setverdict(pass,"CM_SLAC_PARM.REQ message was repeated.",v_count);
}
tc_TT_match_sequence.start(par_TT_match_sequence);
v_count = v_count + 1;
if(v_count > par_C_EV_match_retry) {
tc_TT_match_sequence.stop;
tc_TT_match_response.start(par_TT_match_response +
(2.0 * par_CMN_Transmission_Delay));
alt{
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?)))
-> value v_responseMessage sender vc_sut_mac {
setverdict(fail,"CM_SLAC_PARM.REQ message was repeated, but v_count > " &
"par_C_EV_match_retry.");
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_response.timeout {
setverdict(pass,"TT_match_response timeout. " &
"The total number of retries is reached, " &
"the Matching process " &
"shall be considered as FAILED.");
tc_TP_matching_rate.start(PIXIT_EVCC_CMN_TTMatchingRate +
par_CMN_Transmission_Delay);
if(tc_TP_matching_repetition.running) {
v_count = 0;
repeat;
}
else {
alt{
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?)))
-> value v_responseMessage sender vc_sut_mac {
setverdict(fail,"CM_SLAC_PARM.REQ message was repeated, but " &
"tc_TP_matching_repetition timer has expired.");
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TP_matching_rate.timeout {
setverdict(pass,"SUT did not start a new matching process after" &
"tc_TP_matching_repetition timeout.");
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
[] a_EVCC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EVSE_SLAC_init.timeout {
setverdict(fail,"TT_EVSE_SLAC_init timeout. SECC assumes " &
"that no SLAC will be performed.");
}
[] tc_TT_match_sequence.timeout {
setverdict(fail,"TT_match_sequence timeout. " &
"CM_SLAC_PARM.REQ message was not repeated.");
}
[] tc_TP_matching_rate.timeout {
setverdict(fail,"TP_matching_rate timeout. " &
"SUT did not start a new matching process.");
}
}
return getverdict;
}
}