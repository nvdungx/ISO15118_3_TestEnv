module Templates_CMN_SlacPayloadHeader {
import from DataStructure_SLAC all;
template SLAC_Header m_CMN_CMN_SlacPayloadHeader_001() := {
application_type := '00'H,
security_type := '00'H
}
template SLAC_Header m_CMN_CMN_SlacPayloadHeaderInvalid_001() := {
application_type := 'FF'H,
security_type := '00'H
}
template SLAC_Header m_CMN_CMN_SlacPayloadHeaderInvalid_002() := {
application_type := '00'H,
security_type := 'FF'H
}
}
module Templates_CMN_SlacManagementMessageEntry {
import from DataStructure_SLAC all;
template MME md_CMN_CMN_SlacMme_001(
template(present) MME_Header p_mme_header,
template(present) MME_Payload p_mme_payload) := {
mme_header := p_mme_header,
mme_payload := p_mme_payload
}
template MME_Header md_CMN_CMN_SlacMmeCmnHeader_001(
template(present) MMTYPE p_mmtype) := {
mmv := '01'H,
mmtype := p_mmtype,
fmi := '00'H,
fmsn := '00'H
}
template MME_Header md_CMN_CMN_SlacMmeOuiHeader_001(
template(present) MMTYPE p_mmtype) := {
mmv := '00'H,
mmtype := p_mmtype,
fmi := omit,
fmsn := omit
}
}
module Templates_CMN_CmSlacParm {
import from DataStructure_SLAC all;
template MME_Payload md_CMN_CMN_CmSlacParmReq_001 (
template(present) SLAC_Header v_slac_header,
template(present) RunID_TYPE v_runid) := {
payload := {
cm_slac_parm_req := {
slac_header := v_slac_header,
runid := v_runid
}
}
}
template MME_Payload md_CMN_CMN_CmSlacParmCnf_001 (
template(present) MACAddress_TYPE p_forwarding_sta,
template(present) SLAC_Header p_appheader,
template(present) RunID_TYPE p_runid) := {
payload := {
cm_slac_parm_cnf := {
msound_target := 'FFFFFFFFFFFF'H,
num_sounds := '0A'H,
time_out := '06'H,
resp_type := '01'H,
forwarding_sta := p_forwarding_sta,
appheader := p_appheader,
runid := p_runid
}
}
}
template MME_Payload md_CMN_CMN_CmSlacParmCnf_002 (
template(present) MACAddress_TYPE p_msound_target,
template(present) NumSounds_TYPE p_num_sounds,
template(present) TimeOut_TYPE p_time_out,
template(present) RespType_TYPE p_resp_type,
template(present) MACAddress_TYPE p_forwarding_sta,
template(present) SLAC_Header p_appheader,
template(present) RunID_TYPE p_runid) := {
payload := {
cm_slac_parm_cnf := {
msound_target := p_msound_target,
num_sounds := p_num_sounds,
time_out := p_time_out,
resp_type := p_resp_type,
forwarding_sta := p_forwarding_sta,
appheader := p_appheader,
runid := p_runid
}
}
}
template MACAddressList_TYPE m_CMN_CMN_EmptyMacAddresList() := {
macAddressList := omit
}
}
module Templates_CMN_CmStartAttenCharInd {
import from DataStructure_SLAC all;
template MME_Payload md_CMN_CMN_CmStartAttenCharInd_001(
template(present) SLAC_Header v_slac_header,
template(present) NumSounds_TYPE v_num_sounds,
template(present) TimeOut_TYPE v_time_out,
template(present) RespType_TYPE v_resp_type,
template(present) MACAddress_TYPE v_forwarding_sta,
template(present) RunID_TYPE v_runid) := {
payload:= {
cm_start_atten_char_ind := {
slac_header := v_slac_header,
num_sounds := v_num_sounds,
time_out := v_time_out,
resp_type := v_resp_type,
forwarding_sta := v_forwarding_sta,
runid := v_runid
}
}
}
}
module Templates_CMN_CmMnbcSoundInd {
import from DataStructure_SLAC all;
template MME_Payload md_CMN_CMN_CmMnbcSoundInd_001(
template(present) SLAC_Header v_slac_header,
template(present) Count_TYPE v_count,
template(present) RunID_TYPE v_runid,
template(present) SourceRnd_Type v_source_rnd):= {
payload:= {
cm_mnbc_sound_ind := {
slac_header := v_slac_header,
source_id := '0000000000000000000000000000000000'H,
count := v_count,
runid := v_runid,
res0 := '0000000000000000'H,
source_rnd := v_source_rnd }
}
}
}
module Templates_CMN_CmAttenCharRsp {
import from DataStructure_SLAC all;
template Acvarfield_Type md_CMN_CMN_Acvarfield_001 (
template(present) MACAddress_TYPE v_source_address,
template(present) RunID_TYPE v_runid):= {
source_address := v_source_address,
runid := v_runid,
source_id := '0000000000000000000000000000000000'H,
resp_id := '0000000000000000000000000000000000'H,
result := '00'H
}
template Acvarfield_Type md_CMN_CMN_Acvarfield_002 (
template(present) MACAddress_TYPE p_source_address,
template(present) RunID_TYPE p_runid,
template(present) StationID_TYPE p_source_id,
template(present) StationID_TYPE p_resp_id,
template(present) Result_TYPE p_result):= {
source_address := p_source_address,
runid := p_runid,
source_id := p_source_id,
resp_id := p_resp_id,
result := p_result
}
template MME_Payload md_CMN_CMN_CmAttenCharRsp_001(
template(present) SLAC_Header v_slac_header,
template(present) Acvarfield_Type v_acvarfield):= {
payload:= {
cm_atten_char_rsp := {
slac_header := v_slac_header,
acvarfield := v_acvarfield}
}
}
}
module Templates_CMN_CmValidate {
import from DataStructure_SLAC all;
template MME_Payload m_CMN_CMN_CmValidateReq_001() := {
{
cm_validate_req := {
signalType := '00'H,
vrVarField := {
pilot_timer := '00'H,
result := '01'H
}
}
}
}
template MME_Payload md_CMN_CMN_CmValidateReq_002(
in template(present) PilotTimer_TYPE p_pilot_timer) := {
{
cm_validate_req := {
signalType := '00'H,
vrVarField := {
pilot_timer := p_pilot_timer,
result := '01'H
}
}
}
}
template MME_Payload mw_CMN_CMN_CmValidateReq_003() := {
{
cm_validate_req := {
signalType := '00'H,
vrVarField := {
pilot_timer := ?,
result := ?
}
}
}
}
template MME_Payload md_CMN_CMN_CmValidateReq_004(
in template(present) SignalType_TYPE p_signalType,
in template(present) PilotTimer_TYPE p_pilot_timer,
in template(present) Result_TYPE p_result) := {
{
cm_validate_req := {
signalType := p_signalType,
vrVarField := {
pilot_timer := p_pilot_timer,
result := p_result
}
}
}
}
template MME_Payload md_CMN_CMN_CmValidateCnf_001(
in template(present) Result_TYPE p_result) := {
{
cm_validate_cnf := {
signalType := '00'H,
vcVarField := {
toggle_num := '00'H,
result := p_result
}
}
}
}
template MME_Payload md_CMN_CMN_CmValidateCnf_002(
in template(present) ToggleNum_TYPE p_toggle_num,
in template(present) Result_TYPE p_result) := {
{
cm_validate_cnf := {
signalType := '00'H,
vcVarField := {
toggle_num := p_toggle_num,
result := p_result
}
}
}
}
template MME_Payload md_CMN_CMN_CmValidateCnf_003(
in template(present) SignalType_TYPE p_signalType,
in template(present) ToggleNum_TYPE p_toggle_num,
in template(present) Result_TYPE p_result) := {
{
cm_validate_cnf := {
signalType := p_signalType,
vcVarField := {
toggle_num := p_toggle_num,
result := p_result
}
}
}
}
}
module Templates_CMN_CmSlacMatch {
import from DataStructure_SLAC all;
template MME_Payload md_CMN_CMN_CmSlacMatchReq_001 (
template(present) SLAC_Header v_slac_header,
template(present) MACAddress_TYPE v_pevmac,
template(present) MACAddress_TYPE v_evsemac,
template(present) RunID_TYPE v_runid) := {
payload := {
cm_slac_match_req := {
slac_header := v_slac_header,
mvflength := '003E'H,
pevid := '0000000000000000000000000000000000'H,
pevmac := v_pevmac,
evseid := '0000000000000000000000000000000000'H,
evsemac := v_evsemac,
runid := v_runid,
res0 := '0000000000000000'H
}
}
}
template MME_Payload md_CMN_CMN_CmSlacMatchReq_002 (
template(present) SLAC_Header v_slac_header,
template(present) Mvflength_TYPE v_mvflength,
template(present) StationID_TYPE v_pevid,
template(present) MACAddress_TYPE v_pevmac,
template(present) StationID_TYPE v_evseid,
template(present) MACAddress_TYPE v_evsemac,
template(present) RunID_TYPE v_runid) := {
payload := {
cm_slac_match_req := {
slac_header := v_slac_header,
mvflength := v_mvflength,
pevid := v_pevid,
pevmac := v_pevmac,
evseid := v_evseid,
evsemac := v_evsemac,
runid := v_runid,
res0 := '0000000000000000'H
}
}
}
template MME_Payload md_CMN_CMN_CmSlacMatchCnf_001 (
template(present) SLAC_Header v_slac_header,
template(present) MACAddress_TYPE v_pevmac,
template(present) MACAddress_TYPE v_evsemac,
template(present) RunID_TYPE v_runid,
template(present) NID_TYPE v_nid,
template(present) NMK_TYPE v_nmk) := {
payload := {
cm_slac_match_cnf := {
slac_header := v_slac_header,
mvflength := '0056'H,
pevid := '0000000000000000000000000000000000'H,
pevmac := v_pevmac,
evseid := '0000000000000000000000000000000000'H,
evsemac := v_evsemac,
runid := v_runid,
res0 := '0000000000000000'H,
nid := v_nid,
res1 := '00'H,
nmk := v_nmk
}
}
}
template MME_Payload md_CMN_CMN_CmSlacMatchCnf_001 (
template(present) SLAC_Header v_slac_header,
template(present) MACAddress_TYPE v_pevmac,
template(present) MACAddress_TYPE v_evsemac,
template(present) RunID_TYPE v_runid,
template(present) NID_TYPE v_nid,
template(present) NMK_TYPE v_nmk) := {
payload := {
cm_slac_match_cnf := {
slac_header := v_slac_header,
mvflength := '0056'H,
pevid := '0000000000000000000000000000000000'H,
pevmac := v_pevmac,
evseid := '0000000000000000000000000000000000'H,
evsemac := v_evsemac,
runid := v_runid,
res0 := '0000000000000000'H,
nid := v_nid,
res1 := '00'H,
nmk := v_nmk
}
}
}
module Templates_CMN_CmSetKey {
import from DataStructure_SLAC all;
template MME_Payload md_CMN_CMN_CmSetKeyReq_001 (
template(present) NID_TYPE v_nid,
template(present) NewKey_TYPE v_neykey) := {
payload := {
cm_set_key_req := {
keytype := '01'H,
mynonce := '00000000'H,
yournonce := '00000000'H,
pid := '04'H,
prn := '0000'H,
pmn := '00'H,
ccocapability := '00'H,
nid := v_nid,
neweks := '01'H,
neykey := v_neykey
}
}
}
template MME_Payload mdw_CMN_CMN_CmSetKeyCnf_001(
in template(present) Result_TYPE p_result) := {
payload := {
cm_set_key_cnf := {
result := p_result,
mynonce := ?,
yournonce := ?,
pid := ?,
prn := ?,
pmn := ?,
ccocapability := ?
}
}
}
}
module Templates_CMN_CmAmpMap {
import from DataStructure_SLAC all;
template MME_Payload m_CMN_CMN_CmAmpMapReq_001() := {
{
cm_amp_map_req := {
amlen := '0395'H,
listAmdata := {
amdata := {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H}
}
}
}
}
template MME_Payload md_CMN_CMN_CmAmpMapReq_002(
in template(present) Amlen_TYPE p_amlen,
in template(present) ListofAmdata_TYPE p_listAmdata) := {
{
cm_amp_map_req := {
amlen := p_amlen,
listAmdata := p_listAmdata
}
}
}
template MME_Payload md_CMN_CMN_CmAmpMapReq_003(
in template (present) Amlen_TYPE p_amlen) := {
{
cm_amp_map_req := {
amlen := p_amlen,
listAmdata := {
amdata := {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & { 'C0'H} & {
'BC'H} & { 'BC'H} & { 'AA'H} & { 'AA'H} & { '8F'H} & {
'8F'H} & { '8F'H} & { '8F'H} & { 'A1'H} & { 'A1'H} & {
'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & { 'A1'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H} & { '00'H} & {
'00'H} & { '00'H} & { '00'H} & { '00'H}
}
}
}
}
template MME_Payload md_CMN_CMN_CmAmpMapCnf_001(
in template (present) Result_TYPE p_result) := {
{
cm_amp_map_cnf := {
result := p_result
}
}
}
}
module Templates_CMN_CmNwStats {
import from DataStructure_SLAC all;
template MME_Payload md_CMN_CMN_CmNwStatsReq_001() := {
{
cm_nw_stats_req := {}
}
}
template MME_Payload md_CMN_CMN_CmNwStatsCnf_001() := {
{
cm_nw_stats_cnf := {
numStas := ?,
listOfStas := ?
}
}
}
template MME_Payload md_CMN_CMN_CmNwStatsCnf_002() := {
{
cm_nw_stats_cnf := {
numStas := '00'H,
listOfStas := omit
}
}
}
}
module Templates_EVCC_CmAttenProfileInd {
import from DataStructure_SLAC all;
template MME_Payload md_EVCC_CMN_CmAttenProfileInd_001(
template(present) MACAddress_TYPE v_pev_address,
template(present) NumGroups_TYPE v_num_groups,
template AttenProfile_TYPE v_attenuation_list):= {
payload:= {
cm_atten_profile_ind := {
pev_address := v_pev_address,
num_groups := v_num_groups,
res1 := '00'H,
attenuation_list := v_attenuation_list}
}
}
template AttenProfile_TYPE mw_EVCC_CMN_AttenProfile_001() := {
attenuation :={
?, ?, ?, ?, ?, ?, ?, ? ,?, ?, ?, ?, ?, ?, ?, ?,
?, ?, ?, ?, ?, ?, ?, ? ,?, ?, ?, ?, ?, ?, ?, ?,
?, ?, ?, ?, ?, ?, ?, ? ,?, ?, ?, ?, ?, ?, ?, ?,
?, ?, ?, ?, ?, ?, ?, ? ,?, ?}
}
}
module Templates_EVCC_CmAttenCharInd {
import from DataStructure_SLAC all;
template MME_Payload md_EVCC_CMN_CmAttenCharInd_001(
  template(present) SLAC_Header v_slac_header,
template(present) MACAddress_TYPE v_source_address,
template(present) RunID_TYPE v_runid,
template(present) NumSounds_TYPE v_num_sounds,
template(present) AttenProfile_TYPE v_atten_list):= {
payload:= {
cm_atten_char_ind := {
slac_header := v_slac_header,
source_address := v_source_address,
runid := v_runid,
source_id := '0000000000000000000000000000000000'H,
resp_id := '0000000000000000000000000000000000'H,
num_sounds := v_num_sounds,
num_groups :='3A'H,
attenuation_list := v_atten_list
}
}
}
template MME_Payload md_EVCC_CMN_CmAttenCharInd_002(
template(present) SLAC_Header v_slac_header,
template(present) MACAddress_TYPE v_source_address,
template(present) RunID_TYPE v_runid,
template(present) NumSounds_TYPE v_num_sounds,
template(present) StationID_TYPE v_source_id,
template(present) StationID_TYPE v_resp_id,
template(present) NumGroups_TYPE v_num_groups,
template(present) AttenProfile_TYPE v_atten_list) := {
payload:= {
cm_atten_char_ind := {
slac_header := v_slac_header,
source_address := v_source_address,
runid := v_runid,
source_id := v_source_id,
resp_id := v_resp_id,
num_sounds := v_num_sounds,
num_groups := v_num_groups,
attenuation_list := v_atten_list
}
}
}
template AttenProfile_TYPE m_EVCC_CMN_atten_list_001() := {
attenuation := {
'1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H,
'1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H,
'1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H,
'1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H,
'1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H,
'1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H,
'1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H, '1E'H,
'1E'H, '1E'H
}
}
template AttenProfile_TYPE m_EVCC_CMN_atten_list_002() := {
attenuation := {
'28'H, '28'H, '28'H, '28'H, '28'H, '28'H, '28'H, '28'H,
'28'H, '28'H, '28'H, '28'H, '28'H, '28'H, '28'H, '28'H,
'28'H, '28'H, '28'H, '28'H, '28'H, '28'H, '28'H, '28'H,
'28'H, '28'H, '28'H, '28'H, '28'H, '28'H, '28'H, '28'H,
'28'H, '28'H, '28'H, '28'H, '28'H, '28'H, '28'H, '28'H,
'28'H, '28'H, '28'H, '28'H, '28'H, '28'H, '28'H, '28'H,
'28'H, '28'H, '28'H, '28'H, '28'H, '28'H, '28'H, '28'H,
'28'H, '28'H
}
}
}