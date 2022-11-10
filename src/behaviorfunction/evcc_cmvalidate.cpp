
#include "behaviorfunction/evcc_cmvalidate.hpp"
// import from Timer_15118_3 all;
// import from Pixit_15118_3 all;
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
// import from LibFunctions_15118_3 { group generalFunctions; }
// import from Services_HAL_61851 all;
// import from Templates_CMN_CmSlacParm all;
// import from Templates_CMN_HAL61851 all;
// import from DataStructure_HAL_61851 all;
// import from Templates_CMN_CmSlacMatch all;
// import from Services_PLCLinkStatus all;
// import from Pics_15118 all;
// import from DataStructure_HAL_61851 all;
// import from Timer_15118 all;
namespace TestLib {
// EVCC Tester
function f_EVCC_CMN_TB_VTB_CmValidate_001(in HAL_61851_Listener v_HAL_61851_Listener,
in boolean v_changeDC, in integer v_dutyCycle,
in verdicttype v_vct)
runs on EVCC_Tester return verdicttype {
var MME v_requestMessage;
var integer cnt = 0;
var boolean isStep2 = false;
var float v_TT_EVSE_vald_toggle;
alt {
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
setverdict(v_vct,"Step 1 CM_VALIDATE.REQ is not correct. " &
"Invalid signalType was detected.");
}
tc_TT_EVSE_match_session.stop;
if(v_pilotTimer == "00") {
if(not isStep2) {
setverdict(pass,"Step 1 CM_VALIDATE.REQ is correct.");
isStep2 = true;
if(v_changeDC) {
// change current duty cycle
f_EVCC_setDutyCycle(v_dutyCycle);
}
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
m_CMN_CMN_SlacPayloadHeader_001(), ?))){
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
[] tc_TT_EVSE_match_session.timeout {
setverdict(v_vct,"TT_EVSE_match_session timeout. " &
"Matching process shall " &
"be considered as FAILED.");
}
}
if(getverdict == pass) {
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
"toggle value within " &
"the maximal valid state duration.");
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
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmValidate_002() runs on EVCC_Tester
return verdicttype {
var MME v_responseMessage;
var integer v_count = 0;
alt{
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001()))
-> value v_responseMessage {
if(v_count > 0){
setverdict(pass,"CM_VALIDATE.REQ message was repeated.",v_count);
}
else {
tc_TT_EVSE_match_session.stop;
}
v_count = v_count + 1;
tc_TT_match_response.start(par_TT_match_response + par_CMN_Transmission_Delay);
if(v_count > par_C_EV_match_retry) {
alt{
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001())) {
setverdict(fail,"CM_VALIDATE.REQ message was repeated, but v_count > " &
"par_C_EV_match_retry.");
}
[] tc_TT_match_response.timeout {
setverdict(pass,"TT_match_response timeout. " &
"The total number of retries is reached, " &
"the Validation process " &
"shall be considered as FAILED.");
}
}
}
else{
repeat;
}
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EVSE_match_session.timeout {
setverdict(fail,"TT_EVSE_match_session timeout. Matching process shall be " &
"considered as FAILED.");
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmValidate_003(in template(present) MME_Payload v_validateCnf)
runs on EVCC_Tester return verdicttype {
var MME v_responseMessage;
var integer v_count = 0;
alt{
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001()))
-> value v_responseMessage {
if(v_count > 0){
setverdict(pass,"CM_VALIDATE.REQ message was repeated.",v_count);
}
else {
tc_TT_EVSE_match_session.stop;
}
v_count = v_count + 1;
tc_TT_match_response.start(par_TT_match_response + par_CMN_Transmission_Delay);
// send invalid CM_VALIDATE.CNF message
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}), v_validateCnf))
to vc_sut_mac;
if(v_count > par_C_EV_match_retry) {
alt{
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001())) {
setverdict(fail,"CM_VALIDATE.REQ message was repeated, but v_count > " &
"par_C_EV_match_retry.");
}
[] tc_TT_match_response.timeout {
setverdict(pass,"TT_match_response timeout. " &
"The total number of retries is reached, " &
"the Validation process " &
"shall be considered as FAILED.");
}
}
}
else{
repeat;
}
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EVSE_match_session.timeout {
setverdict(fail,"TT_EVSE_match_session timeout. " &
"Matching process shall be " &
"considered as FAILED.");
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmValidate_004(in hexstring v_resultCode, in boolean v_isRepeat)
runs on EVCC_Tester return verdicttype {
var MME v_requestMessage;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
md_CMN_CMN_CmValidateReq_002(?)))
-> value v_requestMessage {
var PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.
cm_validate_req.vrVarField.pilot_timer;
tc_TT_EVSE_match_session.stop;
if(v_pilotTimer == "00") {
setverdict(pass,"Step 1 CM_VALIDATE.REQ is correct.");
tc_TT_match_sequence.start(par_TT_match_sequence);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(v_resultCode)))
to vc_sut_mac;
if(v_isRepeat) {
repeat;
}
}
else {
tc_TT_match_sequence.stop;
setverdict(fail,"Step 2 CM_VALIDATE.REQ was received. The validation " &
"process with the current EVSE has to be stopped by " &
"the SUT before.");
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
mw_CMN_CMN_CmValidateReq_003())) {
setverdict(fail,"Result field is not set to 'Ready'. Matching process is " &
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
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_sequence.timeout {
setverdict(pass,"TT_match_sequence timeout. " &
"The SUT has stopped the validation process " &
"with the current EVSE.");
}
[] tc_TT_EVSE_match_session.timeout {
setverdict(fail,"TT_EVSE_match_session timeout. Matching process " &
"shall be considered as FAILED.");
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmValidate_005(in HAL_61851_Listener v_HAL_61851_Listener)
runs on EVCC_Tester return verdicttype {
var MME v_requestMessage;
var integer cnt = 0;
var boolean isStep2 = false;
var float v_TT_EVSE_vald_toggle;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
md_CMN_CMN_CmValidateReq_002(?)))
-> value v_requestMessage {
var PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.
cm_validate_req.vrVarField.pilot_timer;
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
md_CMN_CMN_CmValidateCnf_001(par_cmValidate_result_ready)))
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
}
else {
setverdict(fail, "Invalid message content was " &
"received from the SUT.");
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
mw_CMN_CMN_CmValidateReq_003())) {
setverdict(fail,"Result field is not set to 'Ready'. Matching process is " &
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
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_sequence.timeout {
cnt = cnt +1;
log("TT_match_sequence timeout.");
if (cnt > par_C_EV_match_retry) {
setverdict(fail,"Repetition limit is reached. Matching process is " &
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
[] tc_TT_EVSE_match_session.timeout {
setverdict(fail,"TT_EVSE_match_session timeout. Matching process shall be " &
"considered as FAILED.");
}
}
if(getverdict == pass) {
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
setverdict(fail, "Received state has an invalid value.");
}
[] statetimer.timeout {
setverdict(fail, "The EVSE could not detect the corresponding " &
"toggle value within " &
"the maximal valid state duration.");
}
[] tc_TT_EVSE_vald_toggle.timeout {
tc_TT_match_sequence.start(par_TT_match_sequence);
alt {
[] pt_SLAC_Port.receive {
setverdict(fail,"The SUT did not stop the validation " &
"process with the current EVSE.");
}
[] tc_TT_match_sequence.timeout {
setverdict(pass,"TT_match_sequence timeout. " &
"The SUT has stopped the validation " &
"process with the current EVSE.");
}
}
}
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmValidate_006(in HAL_61851_Listener v_HAL_61851_Listener,
in hexstring v_resultCode) runs on EVCC_Tester return verdicttype {
var MME v_requestMessage;
var integer cnt = 0;
var boolean isStep2 = false;
var float v_TT_EVSE_vald_toggle;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
md_CMN_CMN_CmValidateReq_002(?)))
-> value v_requestMessage {
var PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.
cm_validate_req.vrVarField.pilot_timer;
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
}
else {
setverdict(fail, "Invalid message content was " &
"received from the SUT.");
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
mw_CMN_CMN_CmValidateReq_003())) {
setverdict(fail,"Result field is not set to 'Ready'. Matching process is " &
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
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_sequence.timeout {
cnt = cnt +1;
log("TT_match_sequence timeout.");
if (cnt > par_C_EV_match_retry) {
setverdict(fail,"Repetition limit is reached. Matching process " &
"is considered as FAILED.");
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
[] tc_TT_EVSE_match_session.timeout {
setverdict(fail,"TT_EVSE_match_session timeout. Matching process shall " &
"be considered as FAILED.");
}
}
if(getverdict == pass) {
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
setverdict(fail, "Received state has an invalid value.");
}
[] statetimer.timeout {
setverdict(fail, "The EVSE could not detect the corresponding " &
"toggle value within the " &
"maximal valid state duration.");
}
[] tc_TT_EVSE_vald_toggle.timeout {
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_002(
int2hex(toggleCnt,2),
v_resultCode)))
to vc_sut_mac;
tc_TT_match_sequence.start(par_TT_match_sequence);
alt {
[] pt_SLAC_Port.receive {
setverdict(fail,"The SUT did not stop the validation " &
"process with the current EVSE.");
}
[] tc_TT_match_sequence.timeout {
setverdict(pass,"TT_match_sequence timeout. " &
"The SUT has stopped the validation " &
"process with the current EVSE.");
}
}
}
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmValidate_007() runs on EVCC_Tester return verdicttype {
var MME v_requestMessage;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
md_CMN_CMN_CmValidateReq_002(?)))
-> value v_requestMessage {
var PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.
cm_validate_req.vrVarField.pilot_timer;
tc_TT_EVSE_match_session.stop;
if(v_pilotTimer == "00") {
setverdict(pass,"Step 1 CM_VALIDATE.REQ is correct.");
tc_TT_match_sequence.start(par_TT_match_sequence);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(
par_cmValidate_result_notRequired)))
to vc_sut_mac;
repeat;
}
else {
tc_TT_match_sequence.stop;
setverdict(pass,"Step 2 CM_VALIDATE.REQ was received. SUT has " &
"continued the validation process.");
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
mw_CMN_CMN_CmValidateReq_003())) {
setverdict(fail,"Result field is not set to 'Ready'. Matching process is " &
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
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_sequence.timeout {
setverdict(fail,"TT_match_sequence timeout. The SUT has stopped " &
"the validation process.");
}
[] tc_TT_EVSE_match_session.timeout {
setverdict(fail,"TT_EVSE_match_session timeout. Matching process " &
"shall be considered as FAILED.");
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmValidate_008() runs on EVCC_Tester return verdicttype {
  var MME v_requestMessage;
var boolean v_isFirst = true;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
md_CMN_CMN_CmValidateReq_002("00")))
-> value v_requestMessage {
if(v_isFirst) {
tc_TT_EVSE_match_session.stop;
setverdict(pass,"Step 1 CM_VALIDATE.REQ is correct.");
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(
par_cmValidate_result_notReady)))
to vc_sut_mac;
}
else {
tc_EVCC_ValidationRetry.stop;
setverdict(pass,"Step 1 CM_VALIDATE.REQ is correct. SUT has retried " &
"the SLAC validation process after waiting for " &
"PIXIT_EVCC_CMN_ValidationRetry seconds.");
}
if(v_isFirst) {
tc_EVCC_ValidationRetry.start(PIXIT_EVCC_CMN_ValidationRetry +
(2.0 * par_CMN_Transmission_Delay));
v_isFirst = false;
repeat;
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
mw_CMN_CMN_CmValidateReq_003())) {
setverdict(fail,"Result field is not set to 'Ready'. Matching process is " &
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
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EVSE_match_session.timeout {
setverdict(fail,"TT_EVSE_match_session timeout. Matching process " &
"shall be considered as FAILED.");
}
[] tc_EVCC_ValidationRetry.timeout {
setverdict(fail,"EVCC_ValidationRetry timeout. SUT has not retried " &
"the SLAC validation process after waiting for " &
"'PIXIT_EVCC_CMN_ValidationRetry' seconds.");
}
}
return getverdict;
}
// SLAC Tester
function f_EVCC_CMN_TB_VTB_CmValidate_009() runs on SLAC_Tester return verdicttype {
var MME v
_responseMessage;
var integer v_count;
var verdicttype v_verdict;
v_verdict = f_EVCC_CMN_TB_VTB_CmValidatePreCondition_001();
if(v_verdict == pass) {
v
_count = 0;
alt{
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001()))
-> value v_responseMessage {
if(v_count > 0){
setverdict(pass,"CM_VALIDATE.REQ message was repeated.",v_count);
}
else {
tc_TT_EVSE_match_session.stop;
}
v_count = v_count + 1;
tc_TT_match_response.start(par_TT_match_response +
par_CMN_Transmission_Delay);
if(v_count > par_C_EV_match_retry) {
alt{
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
m_CMN_CMN_CmValidateReq_001())) {
setverdict(fail,"CM_VALIDATE.REQ message " &
"was repeated, but v_count > " &
"par_C_EV_match_retry.");
}
[] tc_TT_match_response.timeout {
setverdict(pass,"TT_match_response timeout. " &
"The total number of retries is reached, " &
"the Validation process " &
"shall be considered as FAILED.");
}
}
}
else{
repeat;
}
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EVSE_match_session.timeout {
setverdict(fail,"TT_EVSE_match_session timeout. " &
"Matching process shall be " &
"considered as FAILED.");
}
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmValidate_010(in hexstring v_resultCode)
runs on SLAC_Tester return verdicttype {
var MME v_requestMessage;
var verdicttype v_verdict;
v_verdict = f_EVCC_CMN_TB_VTB_CmValidatePreCondition_001();
if(v_verdict == pass) {
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
md_CMN_CMN_CmValidateReq_002(?)))
-> value v_requestMessage {
var PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.
cm_validate_req.vrVarField.pilot_timer;
tc_TT_EVSE_match_session.stop;
if(v_pilotTimer == "00") {
setverdict(pass,"Step 1 CM_VALIDATE.REQ is correct.");
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(v_resultCode)))
to vc_sut_mac;
tc_TT_match_sequence.start(par_TT_match_sequence);
repeat;
}
else {
tc_TT_match_sequence.stop;
setverdict(fail,"Step 2 CM_VALIDATE.REQ was received. The validation " &
"process with the current EVSE has to be stopped by " &
"the SUT before.");
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
mw_CMN_CMN_CmValidateReq_003())) {
setverdict(fail,"Result field is not set to 'Ready'. Matching process is " &
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
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_sequence.timeout {
setverdict(pass,"TT_match_sequence timeout. " &
"The SUT has stopped the validation process " &
"with the current EVSE.");
}
[] tc_TT_EVSE_match_session.timeout {
setverdict(fail,"TT_EVSE_match_session timeout. Matching process " &
"shall be considered as FAILED.");
}
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmValidate_011(in HAL_61851_Listener v_HAL_61851_Listener)
runs on SLAC_Tester return verdicttype {
var MME v_requestMessage;
var integer cnt = 0;
var boolean isStep2 = false;
var float v_TT_EVSE_vald_toggle;
var verdicttype v_verdict;
v_verdict = f_EVCC_CMN_TB_VTB_CmValidatePreCondition_001();
if(v_verdict == pass) {
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
md_CMN_CMN_CmValidateReq_002(?)))
-> value v_requestMessage {
var PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.
cm_validate_req.vrVarField.pilot_timer;
tc_TT_EVSE_match_session.stop;
if(v_pilotTimer == "00") {
if(not isStep2) {
setverdict(pass,"Step 1 CM_VALIDATE.REQ is correct.");
isStep2 = true;
}
else {
log("Step 2 CM_VALIDATE.REQ message contains " &
"timer field equal to zero. " &
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
}
else {
setverdict(fail, "Invalid message content was " &
"received from the SUT.");
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
mw_CMN_CMN_CmValidateReq_003())) {
setverdict(fail,"Result field is not set to 'Ready'. " &
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
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_sequence.timeout {
cnt = cnt +1;
log("TT_match_sequence timeout.");
if (cnt > par_C_EV_match_retry) {
setverdict(fail,"Repetition limit is reached. " &
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
[] tc_TT_EVSE_match_session.timeout {
setverdict(fail,"TT_EVSE_match_session timeout. " &
"Matching process shall be " &
"considered as FAILED.");
}
}
if(getverdict == pass) {
// BCB toggle sequence detection
tc_TT_EVSE_vald_toggle.start(v_TT_EVSE_vald_toggle);
f_EVCC_changeValidStateCondition(B,C);
timer statetimer = (par_T_vald_state_duration_max +
par_CMN_Transmission_Delay);
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
setverdict(fail, "Received state has an invalid value.");
}
[] statetimer.timeout {
setverdict(fail, "The EVSE could not detect the corresponding " &
"toggle value within " &
"the maximal valid state duration.");
}
[] tc_TT_EVSE_vald_toggle.timeout {
tc_TT_match_sequence.start(par_TT_match_sequence);
alt {
[] pt_SLAC_Port.receive {
setverdict(fail,"The SUT did not stop the validation " &
"process with the current EVSE.");
}
[] tc_TT_match_sequence.timeout {
setverdict(pass,"TT_match_sequence timeout. " &
"The SUT has stopped the validation " &
"process with the current EVSE.");
}
}
}
}
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmValidate_012(in HAL_61851_Listener v_HAL_61851_Listener,
in hexstring v_resultCode)
runs on SLAC_Tester return verdicttype {
var MME v_requestMessage;
var integer cnt = 0;
var boolean isStep2 = false;
var float v_TT_EVSE_vald_toggle;
var verdicttype v_verdict;
v_verdict = f_EVCC_CMN_TB_VTB_CmValidatePreCondition_001();
if(v_verdict == pass) {
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
md_CMN_CMN_CmValidateReq_002(?)))
-> value v_requestMessage {
var PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.
cm_validate_req.vrVarField.pilot_timer;
tc_TT_EVSE_match_session.stop;
if(v_pilotTimer == "00") {
if(not isStep2) {
setverdict(pass,"Step 1 CM_VALIDATE.REQ is correct.");
isStep2 = true;
}
else {
log("Step 2 CM_VALIDATE.REQ message contains " &
"timer field equal to zero. " &
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
}
else {
setverdict(fail, "Invalid message content was " &
"received from the SUT.");
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
mw_CMN_CMN_CmValidateReq_003())) {
setverdict(fail,"Result field is not set to 'Ready'. " &
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
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_sequence.timeout {
cnt = cnt +1;
log("TT_match_sequence timeout.");
if (cnt > par_C_EV_match_retry) {
setverdict(fail,"Repetition limit is reached. " &
"Matching process " &
"is considered as FAILED.");
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
[] tc_TT_EVSE_match_session.timeout {
setverdict(fail,"TT_EVSE_match_session timeout. " &
"Matching process shall " &
"be considered as FAILED.");
}
}
if(getverdict == pass) {
// BCB toggle sequence detection
tc_TT_EVSE_vald_toggle.start(v_TT_EVSE_vald_toggle);
f_EVCC_changeValidStateCondition(B,C);
timer statetimer = (par_T_vald_state_duration_max +
par_CMN_Transmission_Delay);
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
setverdict(fail, "Received state has an invalid value.");
}
[] statetimer.timeout {
setverdict(fail, "The EVSE could not detect the corresponding " &
"toggle value within the " &
"maximal valid state duration.");
}
[] tc_TT_EVSE_vald_toggle.timeout {
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_002(
int2hex(toggleCnt,2),
v_resultCode)))
to vc_sut_mac;
tc_TT_match_sequence.start(par_TT_match_sequence);
alt {
[] pt_SLAC_Port.receive {
setverdict(fail,"The SUT did not stop the validation " &
"process with the current EVSE.");
}
[] tc_TT_match_sequence.timeout {
setverdict(pass,"TT_match_sequence timeout. " &
"The SUT has stopped the validation " &
"process with the current EVSE.");
}
}
}
}
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmValidate_013(in HAL_61851_PwmMode_Type pwmMode)
runs on EVCC_Tester return verdicttype {
var MME v_requestMessage;
var boolean isStep2 = false;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
md_CMN_CMN_CmValidateReq_002(?)))
-> value v_requestMessage {
var PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.
cm_validate_req.vrVarField.pilot_timer;
tc_TT_EVSE_match_session.stop;
if(v_pilotTimer == "00") {
if(not isStep2) {
setverdict(pass,"Step 1 CM_VALIDATE.REQ is correct.");
isStep2 = true;
}
else {
setverdict(fail,"Step 2 CM_VALIDATE.REQ message contains " &
"timer field equal to zero and was not expected. " &
"CP State E/F should be detected before.");
break;
}
// set error state
f_EVCC_changeValidStateCondition(E,E);
f_EVCC_setPwmMode(pwmMode);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_CNF = "6079"}),
md_CMN_CMN_CmValidateCnf_001(
par_cmValidate_result_ready)))
to vc_sut_mac;
tc_TT_match_sequence.start(par_TT_match_sequence);
repeat;
}
else {
setverdict(fail,"Step 2 CM_VALIDATE.REQ message was not expected. " &
"CP State E/F should be detected before.");
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_VALIDATE_REQ = "6078"}),
mw_CMN_CMN_CmValidateReq_003())) {
setverdict(fail,"Result field is not set to 'Ready'. Matching process is " &
"considered as FAILED.");
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?))){
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
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_match_sequence.timeout {
setverdict(pass,"TT_match_sequence timer has expired, " &
"the Matching process was terminated " &
"by the SUT.");
}
[] tc_TT_EVSE_match_session.timeout {
setverdict(fail,"TT_EVSE_match_session timeout. Matching process shall " &
"be considered as FAILED.");
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmValidatePreCondition_001() runs on SLAC_Tester
return verdicttype {
var MME v_responseMessage;
var integer v_Num_soundsInt;
var ResponseMessageList_TYPE reponseMessageList;
var hexstring v_variable;
var integer v_count = 0;
var boolean v_isRunning = true;
var boolean v_repetition = true;
var AttenProfile_TYPE v_attenuation_list;
var integer v_count2 = 0;
var integer v_countDecrement;
var integer v_countStart;
var integer v_countStop;
var boolean v_firstSound = true;
alt{
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?)))
-> value v_responseMessage {
setverdict(pass,"CM_SLAC_PARM.REQ is correct.");
vc_RunID = v_responseMessage.mme_payload.payload.cm_slac_parm_req.runid;
tc_TT_match_sequence.start(par_TT_match_sequence);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),
md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac,
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID)))
to vc_sut_mac;
}
[] a_EVCC_processPLCLinkNotifications_002();
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_EVSE_SLAC_init.timeout {
setverdict(fail,"TT_EVSE_SLAC_init timeout. SECC assumes that no " &
"SLAC will be performed.");
}
}
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_START_ATTEN_CHAR_IND = '606A'H}),
md_CMN_CMN_CmStartAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?, ?,
"01", ?, vc_RunID)))
-> value v_responseMessage {
if(v_count2 == 0) {
tc_TT_EVSE_match_MNBC.start(par_TT_EVSE_match_MNBC);
tc_TT_match_sequence.stop;
vc_Num_sounds = v_responseMessage.mme_payload.payload.
cm_start_atten_char_ind.num_sounds;
v_Num_soundsInt = hex2int(vc_Num_sounds);
}
setverdict(pass,"CM_START_ATTEN_CHAR.IND is correct.");
v_count2 = v_count2 + 1;
if(v_count2 < cc_numberOfStartAtten) {
repeat;
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?))) {
tc_TT_match_sequence.start(par_TT_match_sequence);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),
md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac,
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID)))
to vc_sut_mac;
log("A further CM_SLAC_PARM.REQ message was received. " &
"A new CM_SLAC_PARM.CNF has to be send.");
repeat;
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
if(v_count2 < cc_numberOfStartAtten) {
setverdict(fail, "A wrong number of CM_START_ATTEN_CHAR.IND " &
"message was received.");
}
}
[] tc_TT_match_sequence.timeout {
setverdict(fail,"TT_match_sequence timeout. " &
"No CM_START_ATTEN_CHAR.IND " &
"message was received. Matching process shall be " &
"considered as FAILED.");
break;
}
[] tc_TT_EVSE_match_MNBC.timeout {
setverdict(fail,"TT_EVSE_match_MNBC timeout. A wrong number of " &
"CM_START_ATTEN_CHAR.IND message was received. " &
"Matching process shall be considered as FAILED.");
}
}
if(getverdict == pass) {
while (v_isRunning) {
alt {
[v_firstSound] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_MNBC_SOUND_IND = "6076"}),
md_CMN_CMN_CmMnbcSoundInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
?, vc_RunID, ?)))
-> value v_responseMessage {
v_countStart = hex2int(v_responseMessage.
mme_payload.payload.
cm_mnbc_sound_ind.count);
v_firstSound = false;
if(v_countStart == cc_numberOfSoundings) {
v_countDecrement = v_countStart - 1;
v_countStop = 1;
} else if(v_countStart == cc_numberOfSoundings - 1){
v_countDecrement = v_countStart - 1;
v_countStop = 0;
}
else {setverdict(fail, "The field 'count' has an " &
"invalid value.");
v_isRunning = false;
break;
}
repeat;
}
[not v_firstSound] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_MNBC_SOUND_IND = "6076"}),
md_CMN_CMN_CmMnbcSoundInd_001(
m_CMN_CMN_SlacPayloadHeader_001(),
int2hex(v_countDecrement,2),
vc_RunID, ?))) {
v_countDecrement = v_countDecrement - 1;
repeat;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_PROFILE_IND = "6086"}),
md_EVCC_CMN_CmAttenProfileInd_001(
vc_sut_mac, ?, *)))
-> value v_responseMessage {
if(ispresent(v_responseMessage.mme_payload.payload.
cm_atten_profile_ind.attenuation_list)) {
if(v_responseMessage.mme_payload.payload.
cm_atten_profile_ind.num_groups != '3A'H) {
setverdict(fail,"Invalid numGroups value detected.");
v_isRunning = false;
break;
}
reponseMessageList[v_count] = v_responseMessage;
v_count = v_count + 1;
}
else {
log("Attenuation list was empty, the received message could not " &
"be considered for attenuation calculation.");
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?))) {
setverdict(inconc,"CM_SLAC_PARM.REQ message was received. " &
"New Matching process is started.");
v_isRunning = false;
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
v_isRunning = false;
}
[] tc_TT_EVSE_match_MNBC.timeout {
v_isRunning = false;
}
}
if(v_count == v_Num_soundsInt){
tc_TT_EVSE_match_MNBC.stop;
v_isRunning = false;
}
}
}
if (v_count>0){
if(v_countDecrement != (v_countStop - 1)) {
setverdict(fail,"A wrong number of CM_MNBC_SOUND.IND messages " &
"was received.");
} else {
vc_Num_sounds = int2hex(v_count,2);
setverdict(pass,"CM_MNBC_SOUND.IND is correct.");
setverdict(pass,"CM_ATTEN_PROFILE.IND is correct.");
v_attenuation_list = m_EVCC_CMN_atten_list_002();
}
}
else {
setverdict(fail,"No Atten Profile messages received.");
}
if(getverdict == pass) {
v_count = 0;
while(v_repetition){
tc_TT_match_response.start(par_TT_match_response);
v_count = v_count + 1;
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),
md_EVCC_CMN_CmAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac,
vc_RunID, vc_Num_sounds, v_attenuation_list)))
to vc
_sut_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(
vc_sut_mac, vc_RunID)))) {
setverdict(pass,"CM_ATTEN_CHAR.RSP is correct.");
v_repetition = false;
tc_TT_match_response.stop;
tc_TT_EVSE_match_session.start(par_TT_EVSE_match_session);
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?))) {
setverdict(inconc,"CM_SLAC_PARM.REQ message was received. " &
"New Matching process is started.");
v_repetition = false;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_MNBC_SOUND_IND = "6076"}),?)) {
// CM_ATTEN_PROFILE.IND messages will be ignored!
repeat;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_PROFILE_IND = "6086"}),?)) {
// CM_ATTEN_PROFILE.IND messages will be ignored!
repeat;
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
v_repetition = false;
}
[] tc_TT_match_response.timeout {
log("TT_match_response timeout.");
if(v_count mod (par_C_EV_match_retry+1) == 0){
setverdict(fail,"The repetition limit is reached. " &
"The Matching process is considered " &
"as FAILED.");
v_repetition = false;
} else {
log("The repetition limit is not reached, " &
"a new CM_ATTEN_CHAR.IND message will be send.");
}
}
}
}
}
return getverdict;
}
function decodeValdToggleTime(in PilotTimer_TYPE v_pilotTimer) return float {
return (int2float((hex2int(v_pilotTimer) + 1)) * 0.1);
}
}