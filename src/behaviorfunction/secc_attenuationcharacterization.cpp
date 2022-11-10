#include "behaviorfunction/secc_attenuationcharacterization.hpp"
#include "management/pics_cfg.hpp"
#include "management/pixit_cfg.hpp"
#include "management/timer_cfg.hpp"
#include "supported/libfunctions.hpp"
#include "datatype.hpp"
#include "slac_type.hpp"
// import from Timer_15118_3 all;
// import from Pics_15118_3 all;
// import from Pics_15118 all;
// import from Templates_CMN_CmSlacParm all;
// import from Templates_SECC_CmAttenCharInd all;
// import from Templates_CMN_CmAttenCharRsp all;
// import from Templates_CMN_CmStartAttenCharInd all;
// import from Templates_CMN_CmMnbcSoundInd all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from Templates_CMN_CmSlacMatch all;
// import from ComponentsAndPorts all;
// import from Services_HAL_61851 all;
// import from DataStructure_SLAC all;
// import from LibFunctions_15118_3 { group generalFunctions; }
// import from Services_PLCLinkStatus all;
// import from Timer_15118 all;
// import from Services_TXPowerLimitation all;
// import from Services_HAL_61851 all;
namespace TestLib {

function f_SECC_CMN_TB_VTB_AttenuationCharacterization_001(in verdicttype v_vct)
runs on SECC_Tester
return verdicttype {
var MME v_responseMessage;
var SourceRnd_Type v_source_rnd = f_randomHexStringGen(32);
vc_LowestAverageAttenuation = 0.0;
var MACAddress_TYPE v_sut_mac;
tc_TP_match_sequence.timeout;
tc_TT_EV_atten_results.start(par_TT_EV_atten_results);
for (var integer i=0; i<3; i=i+1) {
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_START_ATTEN_CHAR_IND = '606A'H}),
md_CMN_CMN_CmStartAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_Num_sounds,
vc_Time_out, "01", par_testSystem_mac, vc_RunID)))
to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
var integer v_cnt = par_C_EV_match_MNBC;
for (var integer i=0; i<par_C_EV_match_MNBC; i=i+1) {
v_cnt = v_cnt -1;
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_MNBC_SOUND_IND = "6076"}),
md_CMN_CMN_CmMnbcSoundInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), int2hex(v_cnt,2),
vc_RunID, v_source_rnd))) to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
var integer v_cnt_pot_evse = 0;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),
mdw_SECC_CMN_CmAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_RunID, ?)))
-> value v_responseMessage sender v_sut_mac {
setverdict(pass,"CM_ATTEN_CHAR.IND is correct.");
v_cnt_pot_evse = v_cnt_pot_evse + 1;
vc_attenuation_list = v_responseMessage.mme_payload.payload.
cm_atten_char_ind.attenuation_list;
tc_TP_match_sequence.start(par_TP_match_sequence);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(par_testSystem_mac, vc_RunID))))
to v_sut_mac;
tc_TP_match_sequence.stop;
f_SECC_CMN_setMac(v_responseMessage, v_sut_mac);
if(sizeof(vc_macAddresList.macAddressList) == v_cnt_pot_evse) {
log("CM_ATTEN_CHAR.IND messages from all EVSEs are received.");
}
else{repeat;}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),?)) {
// CM_SLAC_PARM.CNF messages will be ignored!
repeat;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_PROFILE_IND = "6086"}),?)) {
// CM_ATTEN_PROFILE.IND messages will be ignored!
repeat;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(v_vct, "Invalid message type or content was received.");
}
[] tc_TT_EV_atten_results.timeout {
if(v_cnt_pot_evse == 0){
setverdict(v_vct,"TT_EV_atten_results timeout and " &
"no CM_ATTEN_CHAR.IND " &
"received - EVSE_NOT_FOUND.");
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
function f_SECC_CMN_TB_VTB_AttenuationCharacterization_002() runs on SECC_Tester
return verdicttype {
var MME v_responseMessage;
var SourceRnd_Type v_source_rnd = f_randomHexStringGen(32);
vc_LowestAverageAttenuation = 0.0;
tc_TP_match_sequence.timeout;
tc_TT_EV_atten_results.start(par_TT_EV_atten_results);
for (var integer i=0; i<3; i=i+1) {
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_START_ATTEN_CHAR_IND = '606A'H}),
md_CMN_CMN_CmStartAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_Num_sounds,
vc_Time_out, "01", par_testSystem_mac, vc_RunID)))
to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
var integer v_cnt = par_C_EV_match_MNBC;
for (var integer i=0; i<par_C_EV_match_MNBC; i=i+1) {
v_cnt = v_cnt -1;
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_MNBC_SOUND_IND = "6076"}),
md_CMN_CMN_CmMnbcSoundInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), int2hex(v_cnt,2),
vc_RunID, v_source_rnd))) to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),
mdw_SECC_CMN_CmAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_RunID, ?)))
-> value v_responseMessage {
setverdict(pass,"CM_ATTEN_CHAR.IND is correct.");
tc_TT_EV_atten_results.stop;
vc_RunID = f_randomHexStringGen(16);
tc_TP_match_sequence.start(par_TP_match_sequence);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID)))
to cc_eth_broadcast;
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),
md_CMN_CMN_CmSlacParmCnf_001(
par_testSystem_mac ,
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))) {
setverdict(pass,"CM_SLAC_PARM.CNF is correct.");
tc_TP_match_sequence.stop;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_response.timeout {
setverdict(fail,"TT_match_response timeout. " &
"The SECC did not reply to CM_SLAC_PARM " &
"request message.");
}
[] tc_TT_matching_repetition.timeout {
log("TT_matching_repetition timeout - " &
"No new matching process can be started, " &
"if the current matching process fails.");
repeat;
}
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),?)) {
// CM_SLAC_PARM.CNF messages will be ignored!
repeat;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_PROFILE_IND = "6086"}),?)) {
// CM_ATTEN_PROFILE.IND messages will be ignored!
repeat;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EV_atten_results.timeout {
setverdict(fail,"TT_EV_atten_results timeout and no CM_ATTEN_CHAR.IND " &
"received - EVSE_NOT_FOUND.");
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
function f_SECC_CMN_TB_VTB_AttenuationCharacterization_003(in integer n) runs on SECC_Tester
return verdicttype {
var MME v_responseMessage;
var SourceRnd_Type v_source_rnd = f_randomHexStringGen(32);
tc_TP_match_sequence.timeout;
tc_TT_EV_atten_results.start(par_TT_EV_atten_results);
for (var integer i=0; i<3; i=i+1) {
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_START_ATTEN_CHAR_IND = '606A'H}),
md_CMN_CMN_CmStartAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_Num_sounds,
vc_Time_out, "01", par_testSystem_mac, vc_RunID)))
to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
var integer v_cnt = par_C_EV_match_MNBC;
// send (par_C_EV_match_MNBC-n) CM_MNBC_SOUND.IND messages
for (var integer i=0; i<par_C_EV_match_MNBC-n; i=i+1) {
v_cnt = v_cnt -1;
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_MNBC_SOUND_IND = "6076"}),
md_CMN_CMN_CmMnbcSoundInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
int2hex(v_cnt,2), vc_RunID, v_source_rnd)))
to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),
mdw_SECC_CMN_CmAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_RunID, ?)))
-> value v_responseMessage {
setverdict(pass,"Anticipated number of CM_MNBC_SOUND.IND " &
"messages was not sent, " &
"but CM_ATTEN_CHAR.IND is correct.");
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),?)) {
// CM_SLAC_PARM.CNF messages will be ignored!
repeat;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_PROFILE_IND = "6086"}),?)) {
// CM_ATTEN_PROFILE.IND messages will be ignored!
repeat;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EV_atten_results.timeout {
setverdict(fail,"TT_EV_atten_results timeout and no CM_ATTEN_CHAR.IND " &
"received - EVSE_NOT_FOUND.");
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
function f_SECC_CMN_TB_VTB_AttenuationCharacterization_004() runs on SECC_Tester
return verdicttype {
var MME v_responseMessage;
var SourceRnd_Type v_source_rnd = f_randomHexStringGen(32);
vc_LowestAverageAttenuation = 0.0;
var integer v_count = 0;
var MACAddress_TYPE v_sut_mac;
tc_TP_match_sequence.timeout;
tc_TT_EV_atten_results.start(par_TT_EV_atten_results);
for (var integer i=0; i<3; i=i+1) {
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_START_ATTEN_CHAR_IND = '606A'H}),
md_CMN_CMN_CmStartAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_Num_sounds,
vc_Time_out, "01", par_testSystem_mac, vc_RunID)))
to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
var integer v_cnt = par_C_EV_match_MNBC;
for (var integer i=0; i<par_C_EV_match_MNBC; i=i+1) {
v_cnt = v_cnt -1;
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_MNBC_SOUND_IND = "6076"}),
md_CMN_CMN_CmMnbcSoundInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
int2hex(v_cnt,2), vc_RunID, v_source_rnd)))
to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),
mdw_SECC_CMN_CmAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_RunID, ?)))
-> sender v_sut_mac {
if(v_count > 0){
setverdict(pass,"CM_ATTEN_CHAR.IND message was repeated.",v_count);
}
v_count = v_count + 1;
tc_TT_match_response.start(par_TT_match_response +
par_CMN_Transmission_Delay);
if(v_count > par_C_EV_match_retry) {
alt{
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),
mdw_SECC_CMN_CmAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_RunID, ?)))
-> sender v_sut_mac {
setverdict(fail,"CM_ATTEN_CHAR.IND message was " &
"repeated, but v_count > " &
"par_C_EV_match_retry.");
}
[] tc_TT_match_response.timeout {
setverdict(pass,"TT_match_response timeout. " &
"The total number of retries is reached, " &
"the Matching process " &
"shall be considered as FAILED");
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(
par_testSystem_mac, vc_RunID))))
to v_sut_mac;
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_REQ = '607C'H}),
md_CMN_CMN_CmSlacMatchReq_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, v_sut_mac, vc_RunID)))
to v_sut_mac;
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_CNF = '607D'H}),
md_CMN_CMN_CmSlacMatchCnf_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, v_sut_mac,
vc_RunID, ?, ?))) {
setverdict(fail,"CM_SLAC_MATCH.CNF message " &
"was not expected. " &
"Repetition limit was reached.");
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
setverdict(fail, "Invalid message type or content " &
"was received.");
}
[] tc_TT_match_response.timeout {
setverdict(pass,"TT_match_response timeout. " &
"Matching process is " &
"considered as FAILED.");
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
}
else{
repeat;
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),?)) {
// CM_SLAC_PARM.CNF messages will be ignored!
repeat;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_PROFILE_IND = "6086"}),?)) {
// CM_ATTEN_PROFILE.IND messages will be ignored!
repeat;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EV_atten_results.timeout {
setverdict(fail,"TT_EV_atten_results timeout and no CM_ATTEN_CHAR.IND " &
"received - EVSE_NOT_FOUND.");
}
[] tc_TT_match_response.timeout {
setverdict(fail,"TT_match_response timeout. " &
"CM_ATTEN_CHAR.IND message was not repeated.");
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
function f_SECC_CMN_TB_VTB_AttenuationCharacterization_005(in template(present)
SLAC_Header payloadHeader,
in template(present)
Acvarfield_Type acvarfield)
runs on SECC_Tester
return verdicttype {
var MME v_responseMessage;
var SourceRnd_Type v_source_rnd = f_randomHexStringGen(32);
vc_LowestAverageAttenuation = 0.0;
var integer v_count = 0;
var MACAddress_TYPE v_sut_mac;
tc_TP_match_sequence.timeout;
tc_TT_EV_atten_results.start(par_TT_EV_atten_results);
for (var integer i=0; i<3; i=i+1) {
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_START_ATTEN_CHAR_IND = '606A'H}),
md_CMN_CMN_CmStartAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_Num_sounds, vc_Time_out,
"01", par_testSystem_mac, vc_RunID))) to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
var integer v_cnt = par_C_EV_match_MNBC;
for (var integer i=0; i<par_C_EV_match_MNBC; i=i+1) {
v_cnt = v_cnt -1;
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_MNBC_SOUND_IND = "6076"}),
md_CMN_CMN_CmMnbcSoundInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), int2hex(v_cnt,2),
vc_RunID, v_source_rnd))) to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),
mdw_SECC_CMN_CmAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_RunID, ?)))
-> sender v_sut_mac {
if(v_count > 0){
setverdict(pass,"CM_ATTEN_CHAR.IND message was repeated.",v_count);
}
v_count = v_count + 1;
tc_TT_match_response.start(par_TT_match_response +
par_CMN_Transmission_Delay);
// send invalid CM_ATTEN_CHAR.RSP message
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
payloadHeader, acvarfield))) to v_sut_mac;
if(v_count > par_C_EV_match_retry) {
alt{
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),
mdw_SECC_CMN_CmAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_RunID, ?)))
-> sender v_sut_mac {
setverdict(fail,"CM_ATTEN_CHAR.IND message was repeated, but " &
"v_count > par_C_EV_match_retry.");
}
[] tc_TT_match_response.timeout {
setverdict(pass,"TT_match_response timeout. " &
"The total number of retries is reached, " &
"the Matching process shall " &
"be considered as FAILED");
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(
par_testSystem_mac, vc_RunID))))
to v_sut_mac;
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
setverdict(fail,"CM_SLAC_MATCH.CNF message " &
"was not expected. " &
"Repetition limit was reached.");
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
setverdict(fail, "Invalid message type or content " &
"was received.");
}
[] tc_TT_match_response.timeout {
setverdict(pass,"TT_match_response timeout. " &
"Matching process is " &
"considered as FAILED.");
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
}
else{
repeat;
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),?)) {
// CM_SLAC_PARM.CNF messages will be ignored!
repeat;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_PROFILE_IND = "6086"}),?)) {
// CM_ATTEN_PROFILE.IND messages will be ignored!
repeat;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EV_atten_results.timeout {
setverdict(fail,"TT_EV_atten_results timeout and no CM_ATTEN_CHAR.IND " &
"received - EVSE_NOT_FOUND.");
}
[] tc_TT_match_response.timeout {
setverdict(fail,"TT_match_response timeout. " &
"CM_ATTEN_CHAR.IND message was not repeated.");
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
function f_SECC_CMN_TB_VTB_AttenuationCharacterization_006() runs on SECC_Tester
return verdicttype {
var MME v_responseMessage;
var SourceRnd_Type v_source_rnd = f_randomHexStringGen(32);
vc_LowestAverageAttenuation = 0.0;
tc_TT_match_sequence.start(par_TT_match_sequence);
// wait until tc_TT_match_sequence timer expires
tc_TT_match_sequence.timeout;
tc_TT_EV_atten_results.start(par_TT_EV_atten_results);
for (var integer i=0; i<3; i=i+1) {
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_START_ATTEN_CHAR_IND = '606A'H}),
md_CMN_CMN_CmStartAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_Num_sounds,
vc_Time_out, "01", par_testSystem_mac, vc_RunID)))
to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
var integer v_cnt = par_C_EV_match_MNBC;
for (var integer i=0; i<par_C_EV_match_MNBC; i=i+1) {
v_cnt = v_cnt -1;
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_MNBC_SOUND_IND = "6076"}),
md_CMN_CMN_CmMnbcSoundInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
int2hex(v_cnt,2), vc_RunID, v_source_rnd)))
to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),
mdw_SECC_CMN_CmAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_RunID, ?)))
-> value v_responseMessage {
setverdict(fail,"CM_ATTEN_CHAR.IND message was not expected. " &
"TT_EV_atten_results timer should have expired.");
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),?)) {
// CM_SLAC_PARM.CNF messages will be ignored!
repeat;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_PROFILE_IND = "6086"}),?)) {
// CM_ATTEN_PROFILE.IND messages will be ignored!
repeat;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EV_atten_results.timeout {
setverdict(pass,"TT_EV_atten_results timeout, Matching process is " &
"considered as FAILED.");
}
[] tc_TT_matching_repetition.timeout {
log("TT_matching_repetition timeout - No new matching process can be started, " &
"if the current matching process fails.");
repeat;
}
}
return getverdict;
}
function f_SECC_CMN_TB_VTB_AttenuationCharacterization_007(in template MME_Payload v_payload)
runs on SECC_Tester
return verdicttype {
var MME v_responseMessage;
var SourceRnd_Type v_source_rnd = f_randomHexStringGen(32);
vc_LowestAverageAttenuation = 0.0;
tc_TP_match_sequence.timeout;
tc_TT_EV_atten_results.start(par_TT_EV_atten_results);
for (var integer i=0; i<3; i=i+1) {
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
// send invalid CM_START_ATTEN_CHAR.IND message
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_START_ATTEN_CHAR_IND = '606A'H}), v_payload))
to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
var integer v_cnt = par_C_EV_match_MNBC;
for (var integer i=0; i<par_C_EV_match_MNBC; i=i+1) {
v_cnt = v_cnt -1;
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_MNBC_SOUND_IND = "6076"}),
md_CMN_CMN_CmMnbcSoundInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
int2hex(v_cnt,2), vc_RunID, v_source_rnd)))
to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),
mdw_SECC_CMN_CmAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_RunID, ?)))
-> value v_responseMessage {
setverdict(fail,"CM_ATTEN_CHAR.IND message was not expected. " &
"Invalid CM_START_ATTEN_CHAR.IND " &
"message was sent before.");
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),?)) {
// CM_SLAC_PARM.CNF messages will be ignored!
repeat;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_PROFILE_IND = "6086"}),?)) {
// CM_ATTEN_PROFILE.IND messages will be ignored!
repeat;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EV_atten_results.timeout {
setverdict(pass,"TT_EV_atten_results timeout. " &
"No valid CM_START_ATTEN_CHAR.IND " &
"message was received before.");
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
function f_SECC_CMN_TB_VTB_AttenuationCharacterization_008(in HAL_61851_Listener
v_HAL_61851_Listener)
runs on SECC_Tester
return verdicttype {
var MME v_responseMessage;
var SourceRnd_Type v_source_rnd = f_randomHexStringGen(32);
vc_LowestAverageAttenuation = 0.0;
f_SECC_changeValidStateCondition(invalid);
f_SECC_changeValidFrequencyRange(0,0);
f_SECC_changeValidDutyCycleRange(100,100);
deactivate(vc_Default_IEC_61851_ListenerBehavior);
f_SECC_setState(A,v_HAL_61851_Listener);
tc_TP_match_sequence.timeout;
tc_TT_EV_atten_results.start(par_TT_EV_atten_results);
for (var integer i=0; i<3; i=i+1) {
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_START_ATTEN_CHAR_IND = '606A'H}),
md_CMN_CMN_CmStartAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_Num_sounds,
vc_Time_out, "01", par_testSystem_mac, vc_RunID)))
to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
var integer v_cnt = par_C_EV_match_MNBC;
for (var integer i=0; i<par_C_EV_match_MNBC; i=i+1) {
v_cnt = v_cnt -1;
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_MNBC_SOUND_IND = "6076"}),
md_CMN_CMN_CmMnbcSoundInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), int2hex(v_cnt,2),
vc_RunID, v_source_rnd))) to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),
mdw_SECC_CMN_CmAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
par_testSystem_mac, vc_RunID, ?)))
-> value v_responseMessage {
setverdict(fail,"CM_ATTEN_CHAR.IND message was not expected." &
"CP State A should be detected before.");
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),?)) {
// CM_SLAC_PARM.CNF messages will be ignored!
repeat;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_PROFILE_IND = "6086"}),?)) {
// CM_ATTEN_PROFILE.IND messages will be ignored!
repeat;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EV_atten_results.timeout {
setverdict(pass,"TT_EV_atten_results timer has expired, " &
"the Matching process was terminated by the SUT.");
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
function f_SECC_CMN_TB_VTB_AttenuationCharacterization_009(in MACAddress_TYPE
v_macAddress)
runs on SLAC_Tester
return verdicttype {
var MME v_responseMessage;
var boolean v_repetition = true;
var integer v_count1 = 0;
var integer v_count2 = 0;
var MACAddress_TYPE v_sut_mac;
var SourceRnd_Type v_source_rnd = f_randomHexStringGen(32);
vc_LowestAverageAttenuation = 0.0;
vc_macAddresList = m_CMN_CMN_EmptyMacAddressList();
vc_RunID = f_randomHexStringGen(16);
tc_TT_matching_repetition.start(par_TT_matching_repetition);
while(v_repetition){
tc_TT_match_response.start(par_TT_match_response);
v_count1 = v_count1 + 1;
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID)))
to cc_eth_broadcast;
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),
md_CMN_CMN_CmSlacParmCnf_001(
v_macAddress ,m_CMN_CMN_SlacPayloadHeader_001(),
vc_RunID)))
-> value v_responseMessage sender v_sut_mac{
setverdict(pass,"CM_SLAC_PARM is correct.");
vc_macAddresList.macAddressList[v_count2] = v_sut_mac;
v_count2 = v_count2 + 1;
vc_Num_sounds = v_responseMessage.mme_payload.payload.
cm_slac_parm_cnf.num_sounds;
vc_Time_out = v_responseMessage.mme_payload.payload.
cm_slac_parm_cnf.time_out;
repeat;
}
[] a_SECC_processPLCLinkNotifications_002();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
v_repetition = false;
}
[] tc_TT_match_response.timeout {
if(isbound(vc_macAddresList.macAddressList)){
tc_TP_match_sequence.start(par_TP_match_sequence);
v_repetition = false;
}
else if(v_count1 mod (par_C_EV_match_retry+1) == 0){
log("The Matching process is considered as FAILED.");
if(tc_TT_matching_repetition.running){
log("TT_matching_repetition is still running. " &
"A new Matching process is started.");
v_count1 = 0;
}
else {
setverdict(fail, "TT_matching_repetition has expired. " &
"No new Matching process will be started.");
v_repetition = false;
}
}
}
}
}
if(getverdict == pass) {
tc_TP_match_sequence.timeout;
tc_TT_EV_atten_results.start(par_TT_EV_atten_results);
for (var integer i=0; i<3; i=i+1) {
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_START_ATTEN_CHAR_IND = '606A'H}),
md_CMN_CMN_CmStartAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_Num_sounds,
vc_Time_out, "01", v_macAddress, vc_RunID)))
to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
var integer v_cnt = par_C_EV_match_MNBC;
for (var integer i=0; i<par_C_EV_match_MNBC; i=i+1) {
v_cnt = v_cnt -1;
tc_TP_EV_batch_msg_interval.start(par_TP_EV_batch_msg_interval);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_MNBC_SOUND_IND = "6076"}),
md_CMN_CMN_CmMnbcSoundInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), int2hex(v_cnt,2),
vc_RunID, v_source_rnd))) to cc_eth_broadcast;
tc_TP_EV_batch_msg_interval.timeout;
};
var integer v_cnt_pot_evse = 0;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),
mdw_SECC_CMN_CmAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
v_macAddress, vc_RunID, ?)))
-> value v_responseMessage sender v_sut_mac {
setverdict(pass,"CM_ATTEN_CHAR.IND is correct.");
v_cnt_pot_evse = v_cnt_pot_evse + 1;
tc_TP_match_sequence.start(par_TP_match_sequence);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(v_macAddress, vc_RunID))))
to v_sut_mac;
tc_TP_match_sequence.stop;
f_SECC_CMN_setMac(v_responseMessage, v_sut_mac);
if(sizeof(vc_macAddresList.macAddressList) == v_cnt_pot_evse) {
log("CM_ATTEN_CHAR.IND messages from all EVSEs are received.");
}
else{repeat;}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),?)) {
// CM_SLAC_PARM.CNF messages will be ignored!
repeat;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_PROFILE_IND = "6086"}),?)) {
// CM_ATTEN_PROFILE.IND messages will be ignored!
repeat;
}
[] a_SECC_processPLCLinkNotifications_002();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EV_atten_results.timeout {
if(v_cnt_pot_evse == 0){
setverdict(fail,"TT_EV_atten_results timeout and no CM_ATTEN_CHAR.IND " &
"received - EVSE_NOT_FOUND.");
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
function f_SECC_CMN_setMac(MME v_responseMessage, MACAddress_TYPE v_sut_mac_temp) runs on
SLAC_Tester {
var AttenProfile_TYPE v_attenuation_list = v_responseMessage.mme_payload.
payload.cm_atten_char_ind.attenuation_list;
var float averageAttenuation = f_SECC_CMN_calculateAttenuation(v_attenuation_list);
log("SUT MAC address: ", v_sut_mac_temp, "Average attenuation: ", averageAttenuation);
if((averageAttenuation < vc_LowestAverageAttenuation) or
(vc_LowestAverageAttenuation == 0.0)){
vc_LowestAverageAttenuation = averageAttenuation;
vc_sut_mac = v_sut_mac_temp;
log("An SECC with a lower attenuation could be detected.");
}
}
function f_SECC_CMN_calculateAttenuation(AttenProfile_TYPE v_attenuation_list) runs on
SLAC_Tester
return float {
var integer v_attenuationAdded = 0;
for (var integer i=0; i<sizeof(v_attenuation_list); i=i + 1) {
v_attenuationAdded = v_attenuationAdded + hex2int(v_attenuation_list.attenuation[i]);
}
var float v_averageAttenuation = (int2float(v_attenuationAdded)/
int2float(sizeof(v_attenuation_list)));
return v_averageAttenuation;
}
function f_SECC_CMN_Reset_001(in HAL_61851_Listener v_HAL_61851_Listener) runs on SECC_Tester {
// initiate restart of the matching process
all timer.stop;
v_HAL_61851_Listener.stop;
v_HAL_61851_Listener.start(f_SECC_HAL61851Listener(false));
f_SECC_changeValidStateCondition(A);
f_SECC_changeValidFrequencyRange(0,0);
f_SECC_changeValidDutyCycleRange(100,100);
f_SECC_setState(A,v_HAL_61851_Listener);
f_SECC_setProximity(0);
f_SECC_CMN_setTXPower(10);
v_HAL_61851_Listener.stop;
v_HAL_61851_Listener.start(f_SECC_HAL61851Listener(true));
if(PICS_CMN_CMN_ChargingMode == aC){
f_SECC_changeValidFrequencyRange(0,0);
f_SECC_changeValidDutyCycleRange(100,100);
vc_validDutyCycleLowerBound2 = 100;
vc_validDutyCycleUpperBound2 = 100;
}
if(PICS_CMN_CMN_PlugType == type1) {
f_SECC_setProximity(cc_proximity_type1);
} else {
if(PICS_CMN_CMN_ChargingMode == aC){
var integer v_proximity_type2_AC;
if(PICS_CMN_AC_CableCapability == capability13A) {
  v_proximity_type2_AC = cc_proximity_type2_AC_13A;
} else if(PICS_CMN_AC_CableCapability == capability20A) {
v_proximity_type2_AC = cc_proximity_type2_AC_20A;
} else if(PICS_CMN_AC_CableCapability == capability32A) {
v_proximity_type2_AC = cc_proximity_type2_AC_32A;
} else {
v_proximity_type2_AC = cc_proximity_type2_AC_63A;
}
f_SECC_setProximity(v_proximity_type2_AC);
} else {
f_SECC_setProximity(cc_proximity_type2_DC);
}
}
sleep((par_CMN_waitForNextHAL));
f_SECC_changeValidStateCondition(valid_Matching);
f_SECC_setState(vc_state,v_HAL_61851_Listener);
tc_TT_matching_repetition.start(par_TT_matching_repetition);
}
function f_SECC_CMN_compareAttenuationValues_001(in AttenProfile_TYPE
v_attenuation_list1,
in AttenProfile_TYPE
v_attenuation_list2) {
var integer v_meanAttenuation1;
var integer v_meanAttenuation2;
v_meanAttenuation1 = f_SECC_CMN_calculateMeanOfAttenuationValues_001(
v_attenuation_list1);
v_meanAttenuation2 = f_SECC_CMN_calculateMeanOfAttenuationValues_001(
v_attenuation_list2);
if((v_meanAttenuation2 - v_meanAttenuation1) < par_SECC_attenuationDeviation) {
setverdict(fail, "Invalid attenuation values were detected. The deviation " &
"was smaller than 'par_SECC_attenuationDeviation'.");
} else {
setverdict(pass, "Valid attenuation values were detected. The deviation " &
"was greater or equal than 'par_SECC_attenuationDeviation'.");
}
}
function f_SECC_CMN_calculateMeanOfAttenuationValues_001(in AttenProfile_TYPE
v_attenuation_list)
return integer{
var integer v_result = 0;
for (var integer i=0; i<sizeof(v_attenuation_list); i=i + 1) {
v_result = v_result + hex2int(v_attenuation_list.attenuation[i]);
}
v_result = v_result/sizeof(v_attenuation_list);
return v_result;
}
}