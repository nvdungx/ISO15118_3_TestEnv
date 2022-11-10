#include "behaviorfunction/secc_cmvalidate.hpp"
// import from Timer_15118_3 all;
// import from Pics_15118_3 all;
// import from Templates_CMN_CmValidate all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from Templates_CMN_CmSlacParm all;
// import from Templates_SECC_CmAttenCharInd all;
// import from Templates_CMN_CmStartAttenCharInd all;
// import from Templates_CMN_CmMnbcSoundInd all;
// import from ComponentsAndPorts all;
// import from DataStructure_SLAC all;
// import from TestBehavior_SECC_AttenuationCharacterization all;
// import from LibFunctions_15118_3 all;
// import from Services_HAL_61851 all;
// import from Templates_CMN_CmAttenCharRsp all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from Services_PLCLinkStatus all;
// import from Pics_15118 all;
// import from Timer_15118 all;

namespace TestLib {
// SECC Tester
function f_SECC_CMN_TB_VTB_CmValidate_001(in HAL_61851_Listener v_HAL_61851_Listener,
in verdicttype v_vct)
runs on SECC_Tester return verdicttype {
var boolean v_repetition = true;
var integer v_count1 = 0;
var MME v_responseMessage;
if(f_checkValidToggleConfig()) {
while(v_repetition){
tc_TT_match_response.start(par_TT_match_response);
v_count1 = v_count1 + 1;
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001()))
to vc_sut_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(?)))
-> value v_responseMessage {
tc_TT_match_response.stop;
var hexstring v_result = v_responseMessage.mme_payload.
payload.cm_validate_cnf.vcVarField.result;
v_repetition = f_checkResultFieldStep1(v_result,
v_repetition,
v_vct);
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
if(v_count1 mod (par_C_EV_match_retry+1) == 0){
setverdict(v_vct,"The repetition limit is reached. " &
"The Matching process is considered as FAILED.");
v_repetition = false;
} else {
log("The repetition limit is not reached, " &
"a new CM_VALIDATE.REQ message will be send.");
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
if(getverdict() == pass){
// encoding vald toggle time
var hexstring v_pilotTimer = int2hex(float2int((
par_TP_EV_vald_toggle * 10.0) - 1.0),2);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
md_CMN_CMN_CmValidateReq_002(v_pilotTimer)))
to vc_sut_mac;
tc_TP_EV_vald_toggle.start(par_TP_EV_vald_toggle + par_CMN_Transmission_Delay);
// start BCB toggle sequence
for (var integer i=0; i<C_vald_nb_toggles; i=i + 1) {
// B toggle
tc_TP_EV_vald_state_duration.start(par_TP_EV_vald_state_duration);
f_SECC_setState(B,v_HAL_61851_Listener);
tc_TP_EV_vald_state_duration.timeout;
// C toggle
tc_TP_EV_vald_state_duration.start(par_TP_EV_vald_state_duration);
f_SECC_changeValidStateCondition(C);
f_SECC_setState(C,v_HAL_61851_Listener);
tc_TP_EV_vald_state_duration.timeout;
// B toggle
tc_TP_EV_vald_state_duration.start(par_TP_EV_vald_state_duration);
f
_SECC_changeValidStateCondition(B);
f_SECC_setState(B,v_HAL_61851_Listener);
tc_TP_EV_vald_state_duration.timeout;
}
alt {
[] tc_TP_EV_vald_toggle.timeout {
tc_TT_match_response.start(par_TT_match_response);
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_002(?,?)))
-> value v_responseMessage {
tc_TT_match_response.stop;
var hexstring v_result = v_responseMessage.mme_payload.
payload.cm_validate_cnf.vcVarField.
result;
var ToggleNum_TYPE v_toggle_num = v_responseMessage.mme_payload.
payload.cm_validate_cnf.
vcVarField.toggle_num;
f_checkResultFieldStep2(v_result, v_vct);
if(getverdict() == pass){
if(hex2int(v_toggle_num) == C_vald_nb_toggles) {
setverdict(pass,"EVSE_FOUND, the number of detected " &
"BCB toggles is correct.");
}
else {
setverdict(v_vct,"The number of detected BCB " &
"toggles is not correct.");
}
}
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(v_vct, "Invalid message type or content " &
"was received.");
}
[] tc_TT_match_response.timeout {
setverdict(v_vct,"TT_match_response timeout. " &
"The Validation process will be stopped.");
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
}
else {
setverdict(inconc,"Invalid BCB toggle configuration. Check module parameter.");
}
return getverdict;
}
function f_SECC_CMN_TB_VTB_CmValidate_002() runs on SECC_Tester return verdicttype {
var boolean v_repetition = true;
var integer v_count1 = 0;
var MME v_responseMessage;
if(f_checkValidToggleConfig()) {
while(v_repetition){
tc_TT_match_response.start(par_TT_match_response);
v_count1 = v_count1 + 1;
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001()))
to vc_sut_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(?)))
-> value v_responseMessage {
tc_TT_match_response.stop;
var hexstring v_result = v_responseMessage.mme_payload.payload.
cm_validate_cnf.vcVarField.result;
v_repetition = f_checkResultFieldStep1(v_result, v_repetition,
fail);
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
v_repetition = false;
}
[] tc_TT_match_response.timeout {
log("TT_match_response timeout.");
if(v_count1 mod (par_C_EV_match_retry+1) == 0){
setverdict(fail,"The repetition limit is reached. " &
"The Matching process is considered as FAILED.");
v_repetition = false;
} else {
log("The repetition limit is not reached, " &
"a new CM_VALIDATE.REQ message will be send.");
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
if(getverdict() == pass){
var hexstring v_pilotTimer = int2hex(float2int(par_TP_EV_vald_toggle * 10.0),2);
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
md_CMN_CMN_CmValidateReq_002("00")))
to vc_sut_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(?))) {
setverdict(pass,"Step 1 CM_VALIDATE.CNF message was repeated.");
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_response.timeout {
setverdict(fail,"TT_match_response timeout. " &
"Step 1 CM_VALIDATE.CNF message was not repeated.");
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
else {
setverdict(inconc,"Invalid BCB toggle configuration. Check module parameter.");
}
return getverdict;
}
function f_SECC_CMN_TB_VTB_CmValidate_003(in HAL_61851_Listener v_HAL_61851_Listener)
runs on SECC_Tester return verdicttype {
var MME v_responseMessage;
var MACAddress_TYPE v_address;
var integer v_count = 0;
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001()))
to vc_sut_mac;
alt{
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(?)))
-> value v_responseMessage {
tc_TT_match_response.stop;
if(v_count > 0){
setverdict(pass,"CM_VALIDATE.CNF message was repeated.",v_count);
}
v_count = v_count + 1;
tc_TT_match_sequence.start(par_TT_match_sequence + par_CMN_Transmission_Delay);
if(v_count > par_C_EV_match_retry) {
alt{
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(?)))
-> value v_responseMessage {
  setverdict(fail,"CM_VALIDATE.CNF message was repeated, but v_count > " &
"par_C_EV_match_retry.");
}
[] tc_TT_match_sequence.timeout {
setverdict(pass,"TT_match_sequence timeout. " &
"The total number of retries is reached, the Validation " &
"process shall be considered as FAILED");
// encoding vald toggle time
var hexstring v_pilotTimer = int2hex(float2int((
par_TP_EV_vald_toggle * 10.0) - 1.0),2);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
md_CMN_CMN_CmValidateReq_002(v_pilotTimer)))
to vc_sut_mac;
tc_TP_EV_vald_toggle.start(par_TP_EV_vald_toggle + par_CMN_Transmission_Delay);
// start BCB toggle sequence
for (var integer i=0; i<C_vald_nb_toggles; i=i + 1) {
// B toggle
tc_TP_EV_vald_state_duration.start(par_TP_EV_vald_state_duration);
f_SECC_setState(B,v_HAL_61851_Listener);
tc_TP_EV_vald_state_duration.timeout;
// C toggle
tc_TP_EV_vald_state_duration.start(par_TP_EV_vald_state_duration);
f_SECC_changeValidStateCondition(C);
f_SECC_setState(C,v_HAL_61851_Listener);
tc_TP_EV_vald_state_duration.timeout;
// B toggle
tc_TP_EV_vald_state_duration.start(par_TP_EV_vald_state_duration);
f
_SECC_changeValidStateCondition(B);
f_SECC_setState(B,v_HAL_61851_Listener);
tc_TP_EV_vald_state_duration.timeout;
}
alt {
[] tc_TP_EV_vald_toggle.timeout {
tc_TT_match_response.start(par_TT_match_response);
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_002(?,?))) {
tc_TT_match_response.stop;
setverdict(fail,"CM_VALIDATE.CNF message " &
"was not expected, the Matching" &
" process shall be considered " &
"as FAILED.");
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content " &
"was received.");
}
[] tc_TT_match_response.timeout {
setverdict(pass,"TT_match_response timeout. " &
"Matching process is considered " &
"as FAILED.");
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
}
}
else{
repeat;
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({
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
setverdict(fail,"TT_match_response timer timeout. " &
"No CM_VALIDATE.CNF message was received.");
}
[] tc_TT_match_sequence.timeout {
setverdict(fail,"TT_match_sequence timeout. " &
"CM_VALIDATE.CNF message was not repeated.");
}
[] tc_TT_matching_repetition.timeout {
log("TT_matching_repetition timeout - No new matching process can be started, " &
"if the current matching process fails.");
repeat;
}
}
return getverdict;
}
function f_SECC_CMN_TB_VTB_CmValidate_004(in HAL_61851_Listener v_HAL_61851_Listener,
in template(present) MME_Payload mmePayload)
runs on SECC_Tester return verdicttype {
var MME v_responseMessage;
var MACAddress_TYPE v_address;
var integer v_count = 0;
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001()))
to vc_sut_mac;
alt{
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(?)))
-> value v_responseMessage {
tc_TT_match_response.stop;
if(v_count > 0){
setverdict(pass,"CM_VALIDATE.CNF message was repeated.",v_count);
}
v_count = v_count + 1;
tc_TT_match_sequence.start(par_TT_match_sequence + par_CMN_Transmission_Delay);
// send invalid step 2 CM_VALIDATE.REQ message
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
mmePayload)) to vc_sut_mac;
if(v_count > par_C_EV_match_retry) {
alt{
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(?)))
-> value v_responseMessage {
setverdict(fail,"CM_VALIDATE.CNF message was repeated, but v_count > " &
"par_C_EV_match_retry.");
}
[] tc_TT_match_sequence.timeout {
setverdict(pass,"TT_match_sequence timeout. " &
"The total number of retries is reached, the Validation " &
"process shall be considered as FAILED.");
// encoding vald toggle time
var hexstring v_pilotTimer = int2hex(float2int((
par_TP_EV_vald_toggle * 10.0) - 1.0),2);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
md_CMN_CMN_CmValidateReq_002(v_pilotTimer)))
to vc_sut_mac;
tc_TP_EV_vald_toggle.start(par_TP_EV_vald_toggle + par_CMN_Transmission_Delay);
// start BCB toggle sequence
for (var integer i=0; i<C_vald_nb_toggles; i=i + 1) {
// B toggle
tc_TP_EV_vald_state_duration.start(par_TP_EV_vald_state_duration);
f_SECC_setState(B,v_HAL_61851_Listener);
tc_TP_EV_vald_state_duration.timeout;
// C toggle
tc_TP_EV_vald_state_duration.start(par_TP_EV_vald_state_duration);
f_SECC_changeValidStateCondition(C);
f_SECC_setState(C,v_HAL_61851_Listener);
tc_TP_EV_vald_state_duration.timeout;
// B toggle
tc_TP_EV_vald_state_duration.start(par_TP_EV_vald_state_duration);
f
_SECC_changeValidStateCondition(B);
f_SECC_setState(B,v_HAL_61851_Listener);
tc_TP_EV_vald_state_duration.timeout;
}
alt {
[] tc_TP_EV_vald_toggle.timeout {
tc_TT_match_response.start(par_TT_match_response);
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_002(?,?))) {
tc_TT_match_response.stop;
setverdict(fail,"CM_VALIDATE.CNF message " &
"was not expected, the Matching " &
"process shall be considered as FAILED.");
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content " &
"was received.");
}
[] tc_TT_match_response.timeout {
setverdict(pass,"TT_match_response timeout. " &
"Matching process was " &
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
}
}
else{
repeat;
}
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
setverdict(fail,"TT_match_response timeout. " &
"CM_VALIDATE.CNF message was not repeated.");
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
function f_SECC_CMN_TB_VTB_CmValidate_005(in template(present) MME_Payload mmePayload)
runs on SECC_Tester return verdicttype {
var MME v_responseMessage;
var MACAddress_TYPE v_address;
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001()))
to vc_sut_mac;
alt{
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(?)))
-> value v_responseMessage {
tc_TT_match_response.stop;
setverdict(pass,"CM_VALIDATE.CNF message was successful.");
tc_TT_match_sequence.start(par_TT_match_sequence + par_CMN_Transmission_Delay);
// send step 2 CM_VALIDATE.REQ message with a result field unequal than 'ready'
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
mmePayload)) to vc_sut_mac;
alt{
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(?)))
-> value v_responseMessage {
setverdict(fail,"CM_VALIDATE.CNF message was repeated, " &
"but Validation process " &"shall be considered as FAILED.");
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_sequence.timeout {
setverdict(pass,"TT_match_sequence timeout. " &
"The Validation process is considered as FAILED.");
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
setverdict(fail,"TT_match_response timeout. " &
"CM_VALIDATE.CNF message was not repeated.");
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

function f_SECC_CMN_TB_VTB_CmValidate_006() runs on SECC_Tester return verdicttype {
var boolean v_repetition = true;
var integer v_count1 = 0;
var MME v_responseMessage;
if(f_checkValidToggleConfig()) {
if(tc_TP_EVSE_match_session.running) {
tc_TP_EVSE_match_session.stop;
while(v_repetition){
tc_TT_match_response.start(par_TT_match_response);
v_count1 = v_count1 + 1;
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001()))
to vc_sut_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(?)))
-> value v_responseMessage {
tc_TT_match_response.stop;
var hexstring v_result = v_responseMessage.mme_payload.
payload.cm_validate_cnf.
vcVarField.result;
v_repetition = f_checkResultFieldStep1(v_result, v_repetition,
fail);
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
v_repetition = false;
}
[] tc_TT_match_response.timeout {
log("TT_match_response timeout.");
if(v_count1 mod (par_C_EV_match_retry+1) == 0){
setverdict(fail,"The repetition limit is reached. " &
"The Matching process is considered as FAILED.");
v_repetition = false;
} else {
log("The repetition limit is not reached, " &
"a new CM_VALIDATE.REQ message will be send.");
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
}
else {
setverdict(inconc, "The tc_TP_EVSE_match_session timer has expired. " &
"The validation process can not be continued.");
}
}
else {
setverdict(inconc,"Invalid BCB toggle configuration. Check module parameter.");
}
return getverdict;
}
function f_SECC_CMN_TB_VTB_CmValidate_007(in HAL_61851_Listener v_HAL_61851_Listener)
runs on SECC_Tester return verdicttype {
var MME v_responseMessage;
// encoding vald toggle time
var hexstring v_pilotTimer = int2hex(float2int((
par_TP_EV_vald_toggle * 10.0) - 1.0),2);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
md_CMN_CMN_CmValidateReq_002(v_pilotTimer)))
to vc_sut_mac;
tc_TP_EV_vald_toggle.start(par_TP_EV_vald_toggle + par_CMN_Transmission_Delay);
// start BCB toggle sequence
for (var integer i=0; i<C_vald_nb_toggles; i=i + 1) {
// B toggle
tc_TP_EV_vald_state_duration.start(par_TP_EV_vald_state_duration);
f_SECC_setState(B,v_HAL_61851_Listener);
tc_TP_EV_vald_state_duration.timeout;
// C toggle
tc_TP_EV_vald_state_duration.start(par_TP_EV_vald_state_duration);
f_SECC_changeValidStateCondition(C);
f_SECC_setState(C,v_HAL_61851_Listener);
tc_TP_EV_vald_state_duration.timeout;
// B toggle
tc_TP_EV_vald_state_duration.start(par_TP_EV_vald_state_duration);
f_SECC_changeValidStateCondition(B);
f_SECC_setState(B,v_HAL_61851_Listener);
tc_TP_EV_vald_state_duration.timeout;
}
alt {
[] tc_TP_EV_vald_toggle.timeout {
tc_TT_match_response.start(par_TT_match_response);
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_002(?,?)))
-> value v_responseMessage {
tc_TT_match_response.stop;
var hexstring v_result = v_responseMessage.mme_payload.
payload.cm_validate_cnf.vcVarField.
result;
var ToggleNum_TYPE v_toggle_num = v_responseMessage.mme_payload.
payload.cm_validate_cnf.
vcVarField.toggle_num;
f_checkResultFieldStep2(v_result, fail);
if(getverdict() == pass){
if(hex2int(v_toggle_num) == C_vald_nb_toggles) {
setverdict(pass,"EVSE_FOUND, the number of detected " &
"BCB toggles is correct.");
}
else {
setverdict(fail,"The number of detected BCB " &
"toggles is not correct.");
}
}
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_response.timeout {
setverdict(fail,"TT_match_response timeout. " &
"Validation process will be stopped.");
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
function f_SECC_CMN_TB_VTB_CmValidate_008(in Result_TYPE p_result)
runs on SECC_Tester
return verdicttype {
var boolean v_repetition = true;
var integer v_count1 = 0;
var MME v_responseMessage;
while(v_repetition){
tc_TT_match_response.start(par_TT_match_response);
v_count1 = v_count1 + 1;
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001()))
to vc_sut_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(
p_result))) {
tc_TT_match_response.stop;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({
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
v_repetition = false;
}
[] tc_TT_match_response.timeout {
log("TT_match_response timeout.");
if(v_count1 mod (par_C_EV_match_retry+1) == 0){
setverdict(fail,"The repetition limit is reached. " &
"The Matching process is considered as FAILED.");
v_repetition = false;
} else {
log("The repetition limit is not reached, " &
"a new CM_VALIDATE.REQ message will be send.");
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
// SLAC Tester
function f_SECC_CMN_TB_VTB_CmValidate_009() runs on SLAC_Tester return verdicttype {
var boolean v_repetition = true;
var integer v_count1 = 0;
var MME v_responseMessage;
while(v_repetition){
tc_TT_match_response.start(par_TT_match_response);
v_count1 = v_count1 + 1;
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001()))
to vc_sut_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(
par_cmValidate_result_notReady))) {
setverdict(pass,"CM_VALIDATE.CNF message with 'notReady' is correct. " &
"SUT has indicated that it is temporary busy.");
tc_TT_match_response.stop;
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
v_repetition = false;
}
[] tc_TT_match_response.timeout {
log("TT_match_response timeout.");
if(v_count1 mod (par_C_EV_match_retry+1) == 0){
setverdict(fail,"The repetition limit is reached. " &
"The Matching process is considered as FAILED.");
v_repetition = false;
} else {
log("The repetition limit is not reached, " &
"a new CM_VALIDATE.REQ message will be send.");
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
function f_SECC_CMN_TB_VTB_CmValidate_010(in HAL_61851_Listener v_HAL_61851_Listener)
runs on SECC_Tester return verdicttype {
f_SECC_changeValidStateCondition(invalid);
f_SECC_changeValidFrequencyRange(0,0);
f_SECC_changeValidDutyCycleRange(100,100);
deactivate(vc_Default_IEC_61851_ListenerBehavior);
f_SECC_setState(A,v_HAL_61851_Listener);
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001()))
to vc_sut_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(?))) {
setverdict(fail,"CM_VALIDATE.CNF message was not expected." &
"CP State A should be detected before.");
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
function f_SECC_CMN_TB_VTB_CmValidatePreCondition_001() runs on SLAC_Tester
return verdicttype {
var MME v_responseMessage;
var boolean v_repetition = true;
var MACAddress_TYPE v_sut_mac;
var integer v_count1 = 0;
var integer v_count2 = 0;
var SourceRnd_Type v_source_rnd = f_randomHexStringGen(32);
vc_LowestAverageAttenuation = 0.0;
vc_macAddresList = m_CMN_CMN_EmptyMacAddressList();
vc_RunID = f_randomHexStringGen(16);
while(v_repetition){
tc_TT_match_response.start(par_TT_match_response);
v_count1 = v_count1 + 1;
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID)))
to cc_eth_broadcast;
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),
md_CMN_CMN_CmSlacParmCnf_001(par_testSystem_mac,
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID)))
-> value v_responseMessage sender v_sut_mac {
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
if(sizeof(vc_macAddresList.macAddressList) > 0){
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
function f_checkResultFieldStep1(hexstring v_result,
boolean v_repetition,
in verdicttype v_vct)
runs on SECC_Tester
return boolean {
if (v_result == par_cmValidate_result_notReady) {
sleep(0.5);
}
else if (v_result == par_cmValidate_result_ready) {
setverdict(pass,"CM_VALIDATE.CNF is correct. The EV will " &
"send the step 2 CM_VALIDATE.REQ " &
"with a Timer value which covers the whole " &
"BCB toggle sequence.");
v_repetition = false;
}
else if((v_result == par_cmValidate_result_success) or
(v_result == par_cmValidate_result_failure)) {
setverdict(v_vct,"Invalid result code, the EV will stop " &
"the Validation process with " &
"the current EVSE.");
v_repetition = false;
}
else if (v_result == par_cmValidate_result_notRequired) {
setverdict(inconc,"The validation process is not required.");
v_repetition = false;
}
else {
setverdict(v_vct,"Unkwnown result format.");
v_repetition = false;
}
return v_repetition;
}
function f_checkResultFieldStep2(hexstring v_result,
in verdicttype v_vct)
runs on SECC_Tester {
if (v_result == par_cmValidate_result_success) {
setverdict(pass,"CM_VALIDATE.CNF is correct. The EV will compare " &
"the ToggleNum field of the CM_VALIDATE.CNF message " &
"with the number of BCB toggles executed.");
}
else if((v_result == par_cmValidate_result_notReady) or
(v_result == par_cmValidate_result_ready) or
(v_result == par_cmValidate_result_failure) or
(v_result == par_cmValidate_result_notRequired)) {
setverdict(v_vct,"Invalid result code, the EV will stop " &
"the Validation process with " &
"the current EVSE.");
}
else {
setverdict(v_vct,"Unkwnown result format.");
}
}
function f_checkValidToggleConfig() return boolean {
if((int2float(C_vald_nb_toggles) * par_TP_EV_vald_state_duration * 3.0) <
par_TP_EV_vald_toggle) {
return true;
}
return false;
}
}