#include "template/template.hpp"

namespace TestLib
{
using namespace std::literals;
const int MATCH_ANY = 0xFF;  // ? any value
const int MATCH_SKIP = 0xFF; // *, any value or none

namespace Templates_CMN_SlacPayloadHeader
{
using namespace DataStructure_SLAC;

SLAC_Header m_CMN_CMN_SlacPayloadHeader_001()
{
  return (SLAC_Header){.application_type = 0x00, .security_type = 0x00};
}
SLAC_Header m_CMN_CMN_SlacPayloadHeaderInvalid_001()
{
  return (SLAC_Header){.application_type = 0xFF, .security_type = 0x00};
}
SLAC_Header m_CMN_CMN_SlacPayloadHeaderInvalid_002()
{
  return (SLAC_Header){.application_type = 0x00, .security_type = 0xFF};
}
}

namespace Templates_CMN_SlacManagementMessageEntry
{
using namespace DataStructure_SLAC;

MME md_CMN_CMN_SlacMme_001(const MME_Header &p_mme_header, const MME_Payload &p_mme_payload)
{
  return (MME){.mme_header = p_mme_header, .mme_payload = p_mme_payload};
}
MME_Header md_CMN_CMN_SlacMmeCmnHeader_001(const MM_TYPE &p_mmtype)
{
  return (MME_Header){
      .mmv = 0x01,
      .mmtype = p_mmtype,
      .fmi = 0x00,
      .fmi_isUsed = true,
      .fmsn = 0x00,
      .fmsn_isUsed = true};
}
MME_Header md_CMN_CMN_SlacMmeOuiHeader_001(const MM_TYPE &p_mmtype)
{
  return (MME_Header){
      .mmv = 0x00,
      .mmtype = p_mmtype,
      .fmi_isUsed = false,
      .fmsn_isUsed = false};
}
}

namespace Templates_CMN_CmSlacParm
{
using namespace DataStructure_SLAC;

MME_Payload md_CMN_CMN_CmSlacParmReq_001(const SLAC_Header &v_slac_header, const RunID_TYPE &v_runid)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_slac_parm_req = {
      .slac_header = v_slac_header,
      .runid = v_runid};
  return tmplPayload;
}
MME_Payload md_CMN_CMN_CmSlacParmCnf_001(const MACAddress_TYPE &p_forwarding_sta,
  const SLAC_Header &p_appheader, const RunID_TYPE &p_runid)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_slac_parm_cnf = {
      .msound_target = "FFFFFFFFFFFF"sv,
      .num_sounds = 0x0A,
      .time_out = 0x06,
      .resp_type = 0x01,
      .forwarding_sta = p_forwarding_sta,
      .appheader = p_appheader,
      .runid = p_runid};
  return tmplPayload;
}
MME_Payload md_CMN_CMN_CmSlacParmCnf_002(const MACAddress_TYPE &p_msound_target,
  const NumSounds_TYPE &p_num_sounds, const TimeOut_TYPE &p_time_out,
  const RespType_TYPE &p_resp_type, const MACAddress_TYPE &p_forwarding_sta,
  const SLAC_Header &p_appheader, const RunID_TYPE &p_runid)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_slac_parm_cnf = {
      .msound_target = p_msound_target,
      .num_sounds = p_num_sounds,
      .time_out = p_time_out,
      .resp_type = p_resp_type,
      .forwarding_sta = p_forwarding_sta,
      .appheader = p_appheader,
      .runid = p_runid};
  return tmplPayload;
}
MACAddressList_TYPE m_CMN_CMN_EmptyMacAddressList()
{
  return (MACAddressList_TYPE){.macAddressList_isUsed = false};
}
}

namespace Templates_CMN_CmStartAttenCharInd
{
using namespace DataStructure_SLAC;

MME_Payload md_CMN_CMN_CmStartAttenCharInd_001(const SLAC_Header &v_slac_header,
  const NumSounds_TYPE &v_num_sounds, const TimeOut_TYPE &v_time_out,
  const RespType_TYPE &v_resp_type, const MACAddress_TYPE &v_forwarding_sta,
  const RunID_TYPE &v_runid)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_start_atten_char_ind = {
      .slac_header = v_slac_header,
      .num_sounds = v_num_sounds,
      .time_out = v_time_out,
      .resp_type = v_resp_type,
      .forwarding_sta = v_forwarding_sta,
      .runid = v_runid};
  return tmplPayload;
}
}

namespace Templates_CMN_CmMnbcSoundInd
{
using namespace DataStructure_SLAC;

MME_Payload md_CMN_CMN_CmMnbcSoundInd_001(const SLAC_Header &v_slac_header,
  const Count_TYPE &v_count, const RunID_TYPE &v_runid, const SourceRnd_Type &v_source_rnd)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_mnbc_sound_ind = {
      .slac_header = v_slac_header,
      .source_id = "0000000000000000000000000000000000"sv,
      .count = v_count,
      .runid = v_runid,
      .res0 = "0000000000000000"sv,
      .source_rnd = v_source_rnd};
  return tmplPayload;
}
}

namespace Templates_CMN_CmAttenCharRsp
{
using namespace DataStructure_SLAC;

ACVarField_TYPE md_CMN_CMN_Acvarfield_001(const MACAddress_TYPE &v_source_address,
  const RunID_TYPE &v_runid)
{
  return (ACVarField_TYPE){
      .source_address = v_source_address,
      .runid = v_runid,
      .source_id = "0000000000000000000000000000000000"sv,
      .resp_id = "0000000000000000000000000000000000"sv,
      .result = 0x00};
}
ACVarField_TYPE md_CMN_CMN_Acvarfield_002(const MACAddress_TYPE &p_source_address,
  const RunID_TYPE &p_runid, const StationID_TYPE &p_source_id,
  const StationID_TYPE &p_resp_id, const Result_TYPE &p_result)
{
  return (ACVarField_TYPE){
      .source_address = p_source_address,
      .runid = p_runid,
      .source_id = p_source_id,
      .resp_id = p_resp_id,
      .result = p_result};
}
MME_Payload md_CMN_CMN_CmAttenCharRsp_001(const SLAC_Header &v_slac_header,
                                          const ACVarField_TYPE &v_acvarfield)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_atten_char_rsp = {
      .slac_header = v_slac_header,
      .acvarfield = v_acvarfield};
  return tmplPayload;
}
}

namespace Templates_CMN_CmValidate
{
using namespace DataStructure_SLAC;

MME_Payload m_CMN_CMN_CmValidateReq_001()
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_validate_req = {
      .signalType = 0x00,
      .vrVarField = {.pilot_timer = 0x00, .result = 0x01}};
  return tmplPayload;
}
MME_Payload md_CMN_CMN_CmValidateReq_002(const PilotTimer_TYPE &p_pilot_timer)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_validate_req = {
      .signalType = 0x00,
      .vrVarField = {.pilot_timer = p_pilot_timer, .result = 0x01}};
  return tmplPayload;
}
MME_Payload mw_CMN_CMN_CmValidateReq_003()
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_validate_req = {
      .signalType = 0x00,
      .vrVarField = {.pilot_timer = MATCH_ANY, .result = MATCH_ANY}};
  return tmplPayload;
}
MME_Payload md_CMN_CMN_CmValidateReq_004(const SignalType_TYPE &p_signalType,
  const PilotTimer_TYPE &p_pilot_timer, const Result_TYPE &p_result)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_validate_req = {
      .signalType = p_signalType,
      .vrVarField = {.pilot_timer = p_pilot_timer, .result = p_result}};
  return tmplPayload;
}
MME_Payload md_CMN_CMN_CmValidateCnf_001(const Result_TYPE &p_result)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_validate_cnf = {
      .signalType = 0x00,
      .vcVarField = {.toggle_num = 0x00, .result = p_result}};
  return tmplPayload;
}
MME_Payload md_CMN_CMN_CmValidateCnf_002(const ToggleNum_TYPE &p_toggle_num,
    const Result_TYPE &p_result)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_validate_cnf = {
      .signalType = 0x00,
      .vcVarField = {.toggle_num = p_toggle_num, .result = p_result}};
  return tmplPayload;
}
MME_Payload md_CMN_CMN_CmValidateCnf_003(const SignalType_TYPE &p_signalType,
  const ToggleNum_TYPE &p_toggle_num, const Result_TYPE &p_result)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_validate_cnf = {
      .signalType = p_signalType,
      .vcVarField = {.toggle_num = p_toggle_num, .result = p_result}};
  return tmplPayload;
}
}

namespace Templates_CMN_CmSlacMatch
{
using namespace DataStructure_SLAC;

MME_Payload md_CMN_CMN_CmSlacMatchReq_001(const SLAC_Header &v_slac_header,
  const MACAddress_TYPE &v_pevmac, const MACAddress_TYPE &v_evsemac,
  const RunID_TYPE &v_runid)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_slac_match_req = {
      .slac_header = v_slac_header,
      .mvflength = 0x003E,
      .pevid = "0000000000000000000000000000000000"sv,
      .pevmac = v_pevmac,
      .evseid = "0000000000000000000000000000000000"sv,
      .evsemac = v_evsemac,
      .runid = v_runid,
      .res0 = "0000000000000000"sv};
  return tmplPayload;
}
MME_Payload md_CMN_CMN_CmSlacMatchReq_002(const SLAC_Header &v_slac_header,
  const Mvflength_TYPE &v_mvflength, const StationID_TYPE &v_pevid,
  const MACAddress_TYPE &v_pevmac, const StationID_TYPE &v_evseid,
  const MACAddress_TYPE &v_evsemac, const RunID_TYPE &v_runid)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_slac_match_req = {
      .slac_header = v_slac_header,
      .mvflength = v_mvflength,
      .pevid = v_pevid,
      .pevmac = v_pevmac,
      .evseid = v_evseid,
      .evsemac = v_evsemac,
      .runid = v_runid,
      .res0 = "0000000000000000"sv};
  return tmplPayload;
}
MME_Payload md_CMN_CMN_CmSlacMatchCnf_001(const SLAC_Header &v_slac_header,
  const MACAddress_TYPE &v_pevmac, const MACAddress_TYPE &v_evsemac,
  const RunID_TYPE &v_runid, const NID_TYPE &v_nid, const NMK_TYPE &v_nmk)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_slac_match_cnf = {
      .slac_header = v_slac_header,
      .mvflength = 0x0056,
      .pevid = "0000000000000000000000000000000000"sv,
      .pevmac = v_pevmac,
      .evseid = "0000000000000000000000000000000000"sv,
      .evsemac = v_evsemac,
      .runid = v_runid,
      .res0 = "0000000000000000"sv,
      .nid = v_nid,
      .res1 = 0x00,
      .nmk = v_nmk};
  return tmplPayload;
}
MME_Payload md_CMN_CMN_CmSlacMatchCnf_002(const SLAC_Header &v_slac_header,
  const Mvflength_TYPE &v_mvflength, const StationID_TYPE &v_pevid,
  const MACAddress_TYPE &v_pevmac, const StationID_TYPE &v_evseid,
  const MACAddress_TYPE &v_evsemac, const RunID_TYPE &v_runid,
  const NID_TYPE &v_nid, const NMK_TYPE &v_nmk)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_slac_match_cnf = {
      .slac_header = v_slac_header,
      .mvflength = v_mvflength,
      .pevid = v_pevid,
      .pevmac = v_pevmac,
      .evseid = v_evseid,
      .evsemac = v_evsemac,
      .runid = v_runid,
      .res0 = "0000000000000000"sv,
      .nid = v_nid,
      .res1 = 0x00,
      .nmk = v_nmk};
  return tmplPayload;
}
}

namespace Templates_CMN_CmSetKey
{
using namespace DataStructure_SLAC;

MME_Payload md_CMN_CMN_CmSetKeyReq_001(const NID_TYPE &v_nid, const NewKey_TYPE &v_neykey)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_set_key_req = {
      .keytype = 0x01,
      .mynonce = 0x00000000,
      .yournonce = 0x00000000,
      .pid = 0x04,
      .prn = 0x0000,
      .pmn = 0x00,
      .ccocapability = 0x00,
      .nid = v_nid,
      .neweks = 0x01,
      .neykey = v_neykey};
  return tmplPayload;
}
MME_Payload mdw_CMN_CMN_CmSetKeyCnf_001(const Result_TYPE &p_result)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_set_key_cnf = {
      .result = p_result,
      .mynonce = MATCH_ANY,
      .yournonce = MATCH_ANY,
      .pid = MATCH_ANY,
      .prn = MATCH_ANY,
      .pmn = MATCH_ANY,
      .ccocapability = MATCH_ANY};
  return tmplPayload;
}
}

namespace Templates_CMN_CmAmpMap
{
using namespace DataStructure_SLAC;

MME_Payload m_CMN_CMN_CmAmpMapReq_001()
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_amp_map_req.amlen = 0x0395;
  tmplPayload.payload.cm_amp_map_req.listAmdata.amdata = {
      0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xBC, 0xBC, 0xAA, 0xAA, 0x8F, 0x8F, 0x8F,
      0x8F, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xC0, 0xC0, 0xC0, 0xC0,
      0xC0, 0xBC, 0xBC, 0xAA, 0xAA, 0x8F, 0x8F, 0x8F, 0x8F, 0xA1, 0xA1, 0xA1,
      0xA1, 0xA1, 0xA1, 0xA1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xBC, 0xBC, 0xAA,
      0xAA, 0x8F, 0x8F, 0x8F, 0x8F, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1,
      0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xBC, 0xBC, 0xAA, 0xAA, 0x8F, 0x8F, 0x8F,
      0x8F, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xC0, 0xC0, 0xC0, 0xC0,
      0xC0, 0xBC, 0xBC, 0xAA, 0xAA, 0x8F, 0x8F, 0x8F, 0x8F, 0xA1, 0xA1, 0xA1,
      0xA1, 0xA1, 0xA1, 0xA1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xBC, 0xBC, 0xAA,
      0xAA, 0x8F, 0x8F, 0x8F, 0x8F, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1,
      0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xBC, 0xBC, 0xAA, 0xAA, 0x8F, 0x8F, 0x8F,
      0x8F, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xC0, 0xC0, 0xC0, 0xC0,
      0xC0, 0xBC, 0xBC, 0xAA, 0xAA, 0x8F, 0x8F, 0x8F, 0x8F, 0xA1, 0xA1, 0xA1,
      0xA1, 0xA1, 0xA1, 0xA1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xBC, 0xBC, 0xAA,
      0xAA, 0x8F, 0x8F, 0x8F, 0x8F, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1,
      0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xBC, 0xBC, 0xAA, 0xAA, 0x8F, 0x8F, 0x8F,
      0x8F, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00};
  return tmplPayload;
}
MME_Payload md_CMN_CMN_CmAmpMapReq_002(
    const Amlen_TYPE &p_amlen,
    const ListofAmdata_TYPE &p_listAmdata)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_amp_map_req.amlen = p_amlen;
  tmplPayload.payload.cm_amp_map_req.listAmdata.amdata = p_listAmdata.amdata;
  return tmplPayload;
}
MME_Payload md_CMN_CMN_CmAmpMapReq_003(
    const Amlen_TYPE &p_amlen)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_amp_map_req.amlen = p_amlen;
  tmplPayload.payload.cm_amp_map_req.listAmdata.amdata = {
      0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xBC, 0xBC, 0xAA, 0xAA, 0x8F, 0x8F, 0x8F, 0x8F, 0xA1, 0xA1,
      0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xBC, 0xBC, 0xAA, 0xAA, 0x8F,
      0x8F, 0x8F, 0x8F, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
      0xBC, 0xBC, 0xAA, 0xAA, 0x8F, 0x8F, 0x8F, 0x8F, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1,
      0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xBC, 0xBC, 0xAA, 0xAA, 0x8F, 0x8F, 0x8F, 0x8F, 0xA1, 0xA1,
      0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xBC, 0xBC, 0xAA, 0xAA, 0x8F,
      0x8F, 0x8F, 0x8F, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
      0xBC, 0xBC, 0xAA, 0xAA, 0x8F, 0x8F, 0x8F, 0x8F, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1,
      0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xBC, 0xBC, 0xAA, 0xAA, 0x8F, 0x8F, 0x8F, 0x8F, 0xA1, 0xA1,
      0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xBC, 0xBC, 0xAA, 0xAA, 0x8F,
      0x8F, 0x8F, 0x8F, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
      0xBC, 0xBC, 0xAA, 0xAA, 0x8F, 0x8F, 0x8F, 0x8F, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1,
      0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xBC, 0xBC, 0xAA, 0xAA, 0x8F, 0x8F, 0x8F, 0x8F, 0xA1, 0xA1,
      0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  return tmplPayload;
}
MME_Payload md_CMN_CMN_CmAmpMapCnf_001(const Result_TYPE &p_result)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_amp_map_cnf.result = p_result;
  return tmplPayload;
}
}

namespace Templates_CMN_CmNwStats
{
using namespace DataStructure_SLAC;

MME_Payload md_CMN_CMN_CmNwStatsReq_001()
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_nw_stats_req = {}; // any
  return tmplPayload;
}
MME_Payload md_CMN_CMN_CmNwStatsCnf_001()
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_nw_stats_cnf.numStas = MATCH_ANY;
  tmplPayload.payload.cm_nw_stats_cnf.listOfStas_isUsed = true;
  tmplPayload.payload.cm_nw_stats_cnf.listOfStas.stas = {}; // any
  return tmplPayload;
}
MME_Payload md_CMN_CMN_CmNwStatsCnf_002()
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_nw_stats_cnf.numStas = 0x00;
  tmplPayload.payload.cm_nw_stats_cnf.listOfStas_isUsed = false; // omit
  tmplPayload.payload.cm_nw_stats_cnf.listOfStas.stas = {};
  return tmplPayload;
}
}

namespace Templates_SECC_CmAttenCharInd {
using namespace DataStructure_SLAC;
MME_Payload mdw_SECC_CMN_CmAttenCharInd_001(const SLAC_Header &v_slac_header,
  const MACAddress_TYPE &v_source_address, const RunID_TYPE &v_runid,
  const NumSounds_TYPE &v_num_sounds)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_atten_char_ind = {
    .slac_header = v_slac_header,
    .source_address = v_source_address,
    .runid = v_runid,
    .source_id = "0000000000000000000000000000000000"sv,
    .resp_id = "0000000000000000000000000000000000"sv,
    .num_sounds = v_num_sounds,
    .num_groups = 0x3A,
    .attenuation_list.attenuation = {
        MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
        MATCH_ANY ,MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
        MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
        MATCH_ANY, MATCH_ANY, MATCH_ANY ,MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
        MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
        MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY ,MATCH_ANY, MATCH_ANY,
        MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
        MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
        MATCH_ANY, MATCH_ANY}
  };
  return tmplPayload;
}
}

namespace Templates_EVCC_CmAttenProfileInd
{
using namespace DataStructure_SLAC;

MME_Payload md_EVCC_CMN_CmAttenProfileInd_001(const MACAddress_TYPE &v_pev_address,
  const NumGroups_TYPE &v_num_groups, const AttenProfile_TYPE &v_attenuation_list)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_atten_profile_ind = {
      .pev_address = v_pev_address,
      .num_groups = v_num_groups,
      .res1 = 0x00,
      .attenuation_list = v_attenuation_list,
      .attenuation_list_isUsed = true};
  return tmplPayload;
}
AttenProfile_TYPE mw_EVCC_CMN_AttenProfile_001()
{
  return (AttenProfile_TYPE)std::vector<Attenuation_TYPE>{
      MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
      MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
      MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
      MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
      MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
      MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
      MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
      MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
      MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY,
      MATCH_ANY, MATCH_ANY, MATCH_ANY, MATCH_ANY};
};
}

namespace Templates_EVCC_CmAttenCharInd
{
using namespace DataStructure_SLAC;

MME_Payload md_EVCC_CMN_CmAttenCharInd_001(const SLAC_Header &v_slac_header,
  const MACAddress_TYPE &v_source_address, const RunID_TYPE &v_runid,
  const NumSounds_TYPE &v_num_sounds, const AttenProfile_TYPE &v_atten_list)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_atten_char_ind = {
      .slac_header = v_slac_header,
      .source_address = v_source_address,
      .runid = v_runid,
      .source_id = "0000000000000000000000000000000000"sv,
      .resp_id = "0000000000000000000000000000000000"sv,
      .num_sounds = v_num_sounds,
      .num_groups = 0x3A,
      .attenuation_list = v_atten_list};
  return tmplPayload;
}
MME_Payload md_EVCC_CMN_CmAttenCharInd_002(const SLAC_Header &v_slac_header,
  const MACAddress_TYPE &v_source_address, const RunID_TYPE &v_runid,
  const NumSounds_TYPE &v_num_sounds, const StationID_TYPE &v_source_id,
  const StationID_TYPE &v_resp_id, const NumGroups_TYPE &v_num_groups,
  const AttenProfile_TYPE &v_atten_list)
{
  MME_Payload tmplPayload;
  tmplPayload.payload.cm_atten_char_ind = {
      .slac_header = v_slac_header,
      .source_address = v_source_address,
      .runid = v_runid,
      .source_id = v_source_id,
      .resp_id = v_resp_id,
      .num_sounds = v_num_sounds,
      .num_groups = v_num_groups,
      .attenuation_list = v_atten_list};
  return tmplPayload;
}
AttenProfile_TYPE m_EVCC_CMN_atten_list_001()
{
  return (AttenProfile_TYPE)std::vector<Attenuation_TYPE>{
      0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E,
      0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E,
      0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E,
      0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E,
      0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E,
      0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E,
      0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E,
      0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E,
      0x1E, 0x1E};
}
AttenProfile_TYPE m_EVCC_CMN_atten_list_002()
{
  return (AttenProfile_TYPE)std::vector<Attenuation_TYPE>{
      0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
      0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
      0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
      0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
      0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
      0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
      0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
      0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
      0x28, 0x28};
}
}
} // namespace TestLib