#include "behaviorfunction/evcc_attenuationcharacterization.hpp"

// import from Templates_CMN_CmStartAttenCharInd all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from Templates_CMN_CmMnbcSoundInd all;
// import from Templates_CMN_CmAttenCharRsp all;
// import from Templates_EVCC_CmAttenCharInd all;
// import from Templates_EVCC_CmAttenProfileInd all;
// import from Templates_CMN_CmSlacParm all;
// import from ComponentsAndPorts all;
// import from Pics_15118 all;
// import from Pics_15118_3 all;
// import from Pixit_15118_3 all;
// import from Timer_15118_3 all;
// import from Services_HAL_61851 all;
// import from DataStructure_SLAC all;
// import from LibFunctions_15118_3 { group generalFunctions; }
// import from Services_PLCLinkStatus all;
// import from DataStructure_HAL_61851 all;
namespace TestLib {
function averageCalc(in ResponseMessageList_TYPE resMessagelist, in integer vcount)
return AttenProfile_TYPE {
var AttenProfile_TYPE attenuation_list;
var integer avg =0;
for (var integer i=0; i<58; i=i+1)
{
for (var integer j=0;j<vcount;j=j+1)
{
avg=avg+hex2int(resMessagelist[j].mme_payload.payload.cm_atten_profile_ind.
attenuation_list.attenuation[i]);
}
avg=avg/vcount;
attenuation_list.attenuation[i]=int2hex(avg,2);
}
return attenuation_list;
}
function f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(in verdicttype v_vct)
runs on EVCC_Tester
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
var integer v_countDecrement = -1;
var integer v_countStart = -1;
var integer v_countStop = -1;
var boolean v_firstSound = true;
tc_TT_match_sequence.start(par_TT_match_sequence);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),
md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac,
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID)))
to vc_sut_mac;
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
setverdict(v_vct, "Invalid message type or content was received.");
if(v_count2 < cc_numberOfStartAtten) {
setverdict(v_vct, "A wrong number of CM_START_ATTEN_CHAR.IND " &
"message was received.");
}
}
[] tc_TT_match_sequence.timeout {
setverdict(v_vct,"TT_match_sequence timeout. " &
"No CM_START_ATTEN_CHAR.IND " &
"message was received. Matching process shall be " &
"considered as FAILED.");
break;
}
[] tc_TT_EVSE_match_MNBC.timeout {
setverdict(v_vct,"TT_EVSE_match_MNBC timeout. A wrong number of " &
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
else {
setverdict(v_vct, "The field 'count' has an " &
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
setverdict(v_vct,"Invalid numGroups value detected.");
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
setverdict(v_vct, "Invalid message type or " &
"content was received.");
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
setverdict(v_vct,"A wrong number of CM_MNBC_SOUND.IND messages " &
"was received.");
} else {
vc_Num_sounds = int2hex(v_count,2);
setverdict(pass,"CM_MNBC_SOUND.IND is correct.");
setverdict(pass,"CM_ATTEN_PROFILE.IND is correct.");
if(PIXIT_EVCC_CMN_CmValidate == cmValidate) {
v_attenuation_list = m_EVCC_CMN_atten_list_002();
} else {
v_attenuation_list = averageCalc(reponseMessageList, v_count);
}
}
}
else {
setverdict(v_vct,"No Atten Profile messages received.");
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
to vc_sut_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(vc_sut_mac, vc_RunID)))) {
setverdict(pass,"CM_ATTEN_CHAR.RSP is correct.");
v_repetition = false;
tc_TT_match_response.stop;
tc_TT_EVSE_match_session.start(par_TT_EVSE_match_session);
}
[v_gracefulHandling] pt_SLAC_Port.receive(
md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),?)) {
log("The CM_ATTEN_CHAR.RSP message content is " &
"not conform but graceful message handling " &
"is enabled.");
v_repetition = false;
tc_TT_match_response.stop;
tc_TT_EVSE_match_session.start(par_TT_EVSE_match_session);
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?))){
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
setverdict(v_vct, "Invalid message type or content was received.");
v_repetition = false;
}
[] tc_TT_match_response.timeout {
log("TT_match_response timeout.");
if(v_count mod (par_C_EV_match_retry+1) == 0){
setverdict(v_vct,"The repetition limit is reached. " &
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
function f_EVCC_CMN_TB_VTB_AttenuationCharacterization_002() runs on SLAC_Tester
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
tc_TT_EVSE_SLAC_init.start(par_TT_EVSE_SLAC_init_min);
alt {
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?)))
-> value v_responseMessage sender vc_sut_mac
{
setverdict(pass,"CM_SLAC_PARM.REQ is correct.");
vc_RunID = v_responseMessage.mme_payload.payload.cm_slac_parm_req.runid;
repeat;
}
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
m_CMN_CMN_SlacPayloadHeader_001(),
vc_RunID)))
to vc_sut_mac;
log("A further CM_SLAC_PARM.REQ message was received. " &
"A new CM_SLAC_PARM.CNF has to be send.");
repeat;
}
[] a_EVCC_processPLCLinkNotifications_002();
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
[] tc_TT_EVSE_SLAC_init.timeout {
setverdict(fail,"TT_EVSE_SLAC_init timeout. SECC assumes that " &
"no SLAC will be performed.");
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
m_CMN_CMN_SlacPayloadHeader_001(), ?))){
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
v_attenuation_list = averageCalc(reponseMessageList, v_count);
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
to vc_sut_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(
vc_sut_mac, vc_RunID)))) {
setverdict(pass,"CM_ATTEN_CHAR.RSP is correct.");
v_repetition = false;
tc_TT_EVSE_match_session.start(par_TT_EVSE_match_session);
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?))){
setverdict(inconc,"CM_SLAC_PARM.REQ message was received. " &
"New Matching process is started.");
setverdict(fail, "SUT did not send a CM_ATTEN_CHAR.RSP " &
"message to the second EVSE.");
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
function f_EVCC_CMN_TB_VTB_AttenuationCharacterization_003() runs on SLAC_Tester
return verdicttype {
var MME v_responseMessage;
var integer v_Num_soundsInt;
var ResponseMessageList_TYPE reponseMessageList;
var hexstring v_variable;
var integer v_count = 0;
var boolean v_isRunning = true;
var boolean v_repetition = true;
var AttenProfile_TYPE v_attenuation_list;
timer t_TT_EVSE_SLAC_init;
var integer v_count2 = 0;
var integer v_countDecrement;
var integer v_countStart;
var integer v_countStop;
var boolean v_firstSound = true;
t_TT_EVSE_SLAC_init.start(par_TT_EVSE_SLAC_init_min);
alt{
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?)))
-> value v_responseMessage sender vc_sut_mac {
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
[] t_TT_EVSE_SLAC_init.timeout {
setverdict(fail,"TT_EVSE_SLAC_init timeout. SECC assumes that no SLAC " &
"will be performed.");
}
}
if(getverdict == pass) {
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
m_CMN_CMN_SlacPayloadHeader_001(), ?))){
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
log("Attenuation list was empty, the received message " &
"could not be considered for attenuation calculation.");
}
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?))){
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
v_attenuation_list = averageCalc(reponseMessageList, v_count);
}
}
else {
setverdict(fail,"No Atten Profile messages received.");
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_AttenuationCharacterization_004() runs on EVCC_Tester
return verdicttype {
var MME v_responseMessage;
var integer v_Num_soundsInt;
var ResponseMessageList_TYPE reponseMessageList;
var hexstring v_variable;
var integer v_count = 0;
var boolean v_isRunning = true;
var AttenProfile_TYPE v_attenuation_list;
var integer v_count2 = 0;
var integer v_countDecrement;
var integer v_countStart;
var integer v_countStop;
var boolean v_firstSound = true;
tc_TT_match_sequence.start(par_TT_match_sequence);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),
md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac,
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID)))
to vc_sut_mac;
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
tc_TP_EVSE_atten_results.start(par_TT_EV_atten_results);
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
m_CMN_CMN_SlacPayloadHeader_001(), ?))){
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
m_CMN_CMN_SlacPayloadHeader_001(), ?))){
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
v_attenuation_list = averageCalc(reponseMessageList, v_count);
}
}
else {
setverdict(fail,"No Atten Profile messages received.");
}
if(getverdict == pass) {
// wait until tc_TP_EVSE_atten_results timer expires
alt {
[] tc_TP_EVSE_atten_results.timeout;
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content " &
"was received.");
}
}
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),
md_EVCC_CMN_CmAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac,
vc_RunID, vc_Num_sounds, v_attenuation_list)))
to vc
_sut_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(
vc_sut_mac, vc_RunID)))) {
setverdict(fail,"CM_ATTEN_CHAR.RSP message was not expected.");
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
}
[] tc_TT_match_response.timeout {
setverdict(pass, "TT_match_response timeout. " &
"No CM_ATTEN_CHAR.RSP message was " &
"received from the SUT.");
}
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_AttenuationCharacterization_005(in template MME_Payload v_payload)
runs on EVCC_Tester
return verdicttype{
var MME v_responseMessage;
var integer v_Num_soundsInt;
var ResponseMessageList_TYPE reponseMessageList;
var hexstring v_variable;
var integer v_count = 0;
var boolean v_isRunning = true;
var AttenProfile_TYPE v_attenuation_list;
var integer v_count2 = 0;
var integer v_countDecrement;
var integer v_countStart;
var integer v_countStop;
var boolean v_firstSound = true;
tc_TT_match_sequence.start(par_TT_match_sequence);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),
md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac,
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID)))
to vc_sut_mac;
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
tc_TP_EVSE_atten_results.start(par_TT_EV_atten_results);
vc_Num_sounds = v_responseMessage.mme_payload.payload.
cm_start_atten_char_ind.num_sounds;
if(not(ispresent(v_payload.payload.cm_atten_char_ind.num_sounds))) {
v_payload.payload.cm_atten_char_ind.num_sounds = vc_Num_sounds;
}
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
m_CMN_CMN_SlacPayloadHeader_001(), ?))){
tc_TT_match_sequence.start(par_TT_match_sequence);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),
md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac,
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))) to vc_sut_mac;
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
m_CMN_CMN_SlacPayloadHeader_001(), ?))){
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
v_attenuation_list = averageCalc(reponseMessageList, v_count);
}
}
else {
setverdict(fail,"No Atten Profile messages received.");
}
if(getverdict == pass) {
// send invalid CM_ATTEN_CHAR.IND message
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}), v_payload))
to vc_sut_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),?)) {
setverdict(fail,"Invalid CM_ATTEN_CHAR.IND messages shall be ignored.");
}
[] pt_SLAC_Port.receive {
setverdict(fail, "Invalid message type or content was received.");
}
[] tc_TP_EVSE_atten_results.timeout {
tc_TT_match_response.start(par_TT_match_response);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_IND = '606E'H}),
md_EVCC_CMN_CmAttenCharInd_001(
m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac,
vc_RunID, vc_Num_sounds, v_attenuation_list)))
to vc_sut_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(
vc_sut_mac, vc_RunID)))) {
setverdict(fail,"CM_ATTEN_CHAR.RSP message was not expected.");
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
}
[] tc_TT_match_response.timeout {
setverdict(pass, "TT_match_response timeout. " &
"No CM_ATTEN_CHAR.RSP message was " &
"received from the SUT.");
}
}
}
}
}
return getverdict;
}
function f_EVCC_CMN_TB_VTB_AttenuationCharacterization_006(HAL_61851_PwmMode_Type pwmMode)
runs on EVCC_Tester
return verdicttype {
// set error state
f_EVCC_changeValidStateCondition(E,E);
f_EVCC_setPwmMode(pwmMode);
tc_TT_match_sequence.start(par_TT_match_sequence);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),
md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac,
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID)))
to vc_sut_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_START_ATTEN_CHAR_IND = '606A'H}),?)) {
setverdict(fail,"CM_START_ATTEN_CHAR.IND message " &
"was not expected. CP State E/F " &
"should be detected before.");
tc_TT_match_sequence.stop;
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_REQ = "6064"}),
md_CMN_CMN_CmSlacParmReq_001(
m_CMN_CMN_SlacPayloadHeader_001(), ?))){
tc_TT_match_sequence.start(par_TT_match_sequence);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({
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
}
[] tc_TT_match_sequence.timeout {
setverdict(pass,"TT_match_sequence timer has expired, " &
"the Matching process was terminated " &
"by the SUT.");
}
}
return getverdict;
}
function f_EVCC_AC_TB_VTB_AttenuationCharacterization_001(in integer v_dutcCycle)
runs on EVCC_Tester
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
f_EVCC_setDutyCycle(v_dutcCycle);
tc_TT_match_sequence.start(par_TT_match_sequence);
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_PARM_CNF = "6065"}),
md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac,
m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID)))
to vc_sut_mac;
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
m_CMN_CMN_SlacPayloadHeader_001(), ?))){
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
m_CMN_CMN_SlacPayloadHeader_001(), ?))){
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
v_attenuation_list = averageCalc(reponseMessageList, v_count);
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
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_ATTEN_CHAR_RSP ='606F'H}),
md_CMN_CMN_CmAttenCharRsp_001(
m_CMN_CMN_SlacPayloadHeader_001(),
md_CMN_CMN_Acvarfield_001(
vc_sut_mac, vc_RunID)))) {
  setverdict(pass,"CM_ATTEN_CHAR.RSP is correct. " &
"The change of the duty cycle " &
"should not influence the EVCC Matching process.");
v_repetition = false;
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
}