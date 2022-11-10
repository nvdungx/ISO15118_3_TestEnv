#include "behaviorfunction/evcc_cmampmap.hpp"

// import from Timer_15118_3 all;
// import from Pics_15118_3 all;
// import from Templates_CMN_CmAmpMap all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from Templates_CMN_CmSlacMatch all;
// import from ComponentsAndPorts all;
// import from DataStructure_SLAC all;
// import from Services_HAL_61851 all;
// import from DataStructure_HAL_61851 all;
// import from Templates_CMN_CmSlacParm all;
// import from TTlibrary_Logging all;
// import from TestBehavior_EVCC_SDP all;
namespace TestLib {
function f_EVCC_CMN_TB_VTB_CmAmpMap_001(in verdicttype v_vct)
runs on EVCC_Tester
return verdicttype {
var boolean v_repetition = true;
var integer v_counter = 0;
while(v_repetition){
tc_TT_match_response.start(par_TT_match_response);
v_counter = v_counter + 1;
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_REQ = '601C'H}),
m_CMN_CMN_CmAmpMapReq_001()))
to vc_sut_mac;
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_CNF = '601D'H}),
md_CMN_CMN_CmAmpMapCnf_001("00"))) {
setverdict(pass,"CM_AMP_MAP.CNF is correct.");
v_repetition = false;
tc_TT_match_response.stop;
}
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_CNF = '601D'H}),
md_CMN_CMN_CmAmpMapCnf_001("01"))) {
setverdict(v_vct,"The SUT could not perform the " &
"Amplitude map exchange.");
v_repetition = false;
tc_TT_match_response.stop;
}
[] pt_SLAC_Port.receive {
setverdict(v_vct, "Invalid message type or content " &
"was received.");
v_repetition = false;
tc_TT_match_response.stop;
}
[] tc_TT_match_response.timeout {
log("TT_match_response timeout.");
if(v_counter mod (par_C_EV_match_retry+1) == 0){
setverdict(v_vct,"The SUT did not response to the " &
"CM_AMP_MAP.REQ message.");
v_repetition = false;
} else {
log("A new CM_AMP_MAP.REQ message will be sent.");
}
}
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmAmpMap_002(in verdicttype v_vct)
runs on EVCC_Tester
return verdicttype {
var MME v_requestMessage;
tc_TT_amp_map_exchange.start(par_TT_amp_map_exchange);
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_REQ = '601C'H}),
md_CMN_CMN_CmAmpMapReq_002(?,?)))
-> value v_requestMessage {
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_CNF = '601D'H}),
md_CMN_CMN_CmAmpMapCnf_001("00")))
to vc_sut_mac;
var Amlen_TYPE v_amlen = v_requestMessage.mme_payload.
payload.cm_amp_map_req.amlen;
var ListofAmdata_TYPE v_listAmdata = v_requestMessage.mme_payload.
payload.cm_amp_map_req.listAmdata;
setverdict(pass,"CM_AMP_MAP.REQ is correct.");
tc_TT_amp_map_exchange.stop;
}
[] pt_SLAC_Port.receive {
setverdict(v_vct, "Invalid message type or content was received.");
}
[] tc_TT_amp_map_exchange.timeout {
setverdict(v_vct,"No Amplitude Map exchange was performed by the SUT.");
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmAmpMap_003() runs on EVCC_Tester return verdicttype {
var integer v_count = 0;
tc_TT_amp_map_exchange.start(par_TT_amp_map_exchange);
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_REQ = '601C'H}),
md_CMN_CMN_CmAmpMapReq_002(?,?))) {
if(v_count > 0){
setverdict(pass,"CM_AMP_MAP.REQ message was repeated.",v_count);
} else { tc_TT_amp_map_exchange.stop;}
v_count = v_count + 1;
tc_TT_match_response.start(par_TT_match_response);
if(v_count > par_C_EV_match_retry) {
alt{
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_REQ = '601C'H}),
md_CMN_CMN_CmAmpMapReq_002(?,?))) {
setverdict(fail,"CM_AMP_MAP.REQ message was repeated, " &
"but v_count > par_C_EV_match_retry.");
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content " &
"was received.");
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
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_amp_map_exchange.timeout {
setverdict(fail,"No Amplitude Map exchange was performed by the SUT.");
}
[] tc_TT_match_response.timeout {
setverdict(fail,"The SUT did not retransmit the " &
"CM_AMP_MAP.REQ message.");
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmAmpMap_004() runs on EVCC_Tester return verdicttype {
var integer v_count = 0;
tc_TT_amp_map_exchange.start(par_TT_amp_map_exchange);
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_REQ = '601C'H}),
md_CMN_CMN_CmAmpMapReq_002(?,?))) {
if(v_count > 0){
setverdict(pass,"CM_AMP_MAP.REQ message was repeated.",v_count);
} else { tc_TT_amp_map_exchange.stop;}
v_count = v_count + 1;
tc_TT_match_response.start(par_TT_match_response);
// send invalid CM_AMP_MAP.CNF message
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_CNF = '601D'H}),
md_CMN_CMN_CmAmpMapCnf_001('FF'H)))
to vc_sut_mac;
if(v_count > par_C_EV_match_retry) {
alt{
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_REQ = '601C'H}),
md_CMN_CMN_CmAmpMapReq_002(?,?))) {
setverdict(fail,"CM_AMP_MAP.REQ message was repeated, " &
"but v_count > par_C_EV_match_retry.");
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content " &
"was received.");
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
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TT_amp_map_exchange.timeout {
setverdict(fail,"No Amplitude Map exchange was performed by the SUT.");
}
[] tc_TT_match_response.timeout {
setverdict(fail,"The SUT did not retransmit the " &
"CM_AMP_MAP.REQ message.");
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmAmpMap_005() runs on EVCC_Tester return verdicttype {
var boolean v_repetition = true;
var integer v_counter = 0;
while(v_repetition){
tc_TT_match_response.start(par_TT_match_response);
v_counter = v_counter + 1;
// send invalid CM_AMP_MAP.REQ message
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_REQ = '601C'H}),
md_CMN_CMN_CmAmpMapReq_003("0000")))
to vc_sut_mac;
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_CNF = '601D'H}),
md_CMN_CMN_CmAmpMapCnf_001(?))) {
setverdict(fail,"Received CM_AMP_MAP.CNF message " &
"was not expected.");
v_repetition = false;
tc_TT_match_response.stop;
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content " &
"was received.");
v_repetition = false;
tc_TT_match_response.stop;
}
[] tc_TT_match_response.timeout {
log("TT_match_response timeout.");
setverdict(pass,"The SUT did not response to the " &
"invalid CM_AMP_MAP.REQ message.");
if(v_counter mod (par_C_EV_match_retry+1) == 0){
v_repetition = false;
} else {
log("A new invalid CM_AMP_MAP.REQ message will be sent.");
}
}
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmAmpMap_006() runs on EVCC_Tester return verdicttype {
var boolean v_repetition = true;
var integer v_counter = 0;
while(v_repetition){
tc_TT_match_response.start(par_TT_match_response);
v_counter = v_counter + 1;
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_REQ = '601C'H}),
m_CMN_CMN_CmAmpMapReq_001()))
to vc_sut_mac;
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_CNF = '601D'H}),
md_CMN_CMN_CmAmpMapCnf_001("00"))) {
setverdict(pass,"CM_AMP_MAP.CNF is correct.");
tc_TT_match_response.stop;
if(v_counter > 1) {
v_repetition = false;
}
}
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_CNF = '601D'H}),
md_CMN_CMN_CmAmpMapCnf_001("01"))) {
setverdict(fail,"The SUT could not perform the " &
"Amplitude map exchange.");
v_repetition = false;
tc_TT_match_response.stop;
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content " &
"was received.");
v_repetition = false;
tc_TT_match_response.stop;
}
[] tc_TT_match_response.timeout {
setverdict(fail,"The SUT did not response to the " &
"CM_AMP_MAP.REQ message.");
v_repetition = false;
}
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmAmpMap_007() runs on EVCC_Tester return verdicttype {
var integer v_counter = 0;
tc_TT_match_response.start(par_TT_match_response);
for (var integer i=0; i<3; i=i + 1) {
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_REQ = '601C'H}),
m_CMN_CMN_CmAmpMapReq_001()))
to vc_sut_mac;
}
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_CNF = '601D'H}),
md_CMN_CMN_CmAmpMapCnf_001("00"))) {
setverdict(pass,"CM_AMP_MAP.CNF is correct.");
v_counter = v_counter + 1;
tc_TT_match_response.stop;
tc_TT_match_response.start(par_TT_match_response);
if(v_counter < 3) {
repeat;
}
}
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_AMP_MAP_CNF = '601D'H}),
md_CMN_CMN_CmAmpMapCnf_001("01"))) {
setverdict(fail,"The SUT could not perform the " &
"Amplitude map exchange.");
tc_TT_match_response.stop;
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content " &
"was received.");
tc_TT_match_response.stop;
}
[] tc_TT_match_response.timeout {
setverdict(fail,"The SUT did not response to the " &
"CM_AMP_MAP.REQ message.");
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_CmAmpMap_008() runs on EVCC_Tester return verdicttype {
tc_V2G_SECC_CommunicationSetup_Timer.start;
f_EVCC_CMN_TB_VTB_SDP_001(?, fail);
return getverdict;
}
}