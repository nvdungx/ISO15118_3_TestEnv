#include "template/template.hpp"
#include "datatype.hpp"
#include "slac_type.hpp"

namespace TestLib
{

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
    /* MME md_CMN_CMN_SlacMme_001(const MME_Header &p_mme_header,const  MME_Payload &p_mme_payload)
    {
      return (MME){.mme_header = p_mme_header, .mme_payload = p_mme_payload};
    } */
    /* MME_Header md_CMN_CMN_SlacMmeCmnHeader_001(MMTYPE p_mmtype)
    {
      mmv = 0x01;
      mmtype = p_mmtype;
      fmi = 0x00;
      fmsn = 0x00;
    }
    MME_Header md_CMN_CMN_SlacMmeOuiHeader_001(MMTYPE p_mmtype)
    {
      mmv = 0x00;
      mmtype = p_mmtype;
      fmi = omit;
      fmsn = omit;
    } */
  }
  /* namespace Templates_CMN_CmSlacParm
  {
    using namespace DataStructure_SLAC;
    MME_Payload md_CMN_CMN_CmSlacParmReq_001(
        SLAC_Header v_slac_header,
        RunID_TYPE v_runid)
    {
      payload = { cm_slac_parm_req = {
                      slac_header = v_slac_header,
                      runid = v_runid} }
    }
    MME_Payload md_CMN_CMN_CmSlacParmCnf_001(
        MACAddress_TYPE p_forwarding_sta,
        SLAC_Header p_appheader,
        RunID_TYPE p_runid)
    {
      payload = { cm_slac_parm_cnf = {
                      msound_target = 0xFFFFFFFFFFFF,
                      num_sounds = 0x0A,
                      time_out = 0x06,
                      resp_type = 0x01,
                      forwarding_sta = p_forwarding_sta,
                      appheader = p_appheader,
                      runid = p_runid} }
    }
    MME_Payload md_CMN_CMN_CmSlacParmCnf_002(
        MACAddress_TYPE p_msound_target,
        NumSounds_TYPE p_num_sounds,
        TimeOut_TYPE p_time_out,
        RespType_TYPE p_resp_type,
        MACAddress_TYPE p_forwarding_sta,
        SLAC_Header p_appheader,
        RunID_TYPE p_runid)
    {
      payload = { cm_slac_parm_cnf = {
                      msound_target = p_msound_target,
                      num_sounds = p_num_sounds,
                      time_out = p_time_out,
                      resp_type = p_resp_type,
                      forwarding_sta = p_forwarding_sta,
                      appheader = p_appheader,
                      runid = p_runid} }
    }
    MACAddressList_TYPE m_CMN_CMN_EmptyMacAddresList()
    {
      macAddressList = omit
    }
  }
  namespace Templates_CMN_CmStartAttenCharInd
  {
    using namespace DataStructure_SLAC;
    MME_Payload md_CMN_CMN_CmStartAttenCharInd_001(
        SLAC_Header v_slac_header,
        NumSounds_TYPE v_num_sounds,
        TimeOut_TYPE v_time_out,
        RespType_TYPE v_resp_type,
        MACAddress_TYPE v_forwarding_sta,
        RunID_TYPE v_runid)
    {
      payload = { cm_start_atten_char_ind = {
                      slac_header = v_slac_header,
                      num_sounds = v_num_sounds,
                      time_out = v_time_out,
                      resp_type = v_resp_type,
                      forwarding_sta = v_forwarding_sta,
                      runid = v_runid} }
    }
  }
  namespace Templates_CMN_CmMnbcSoundInd
  {
    using namespace DataStructure_SLAC;
    MME_Payload md_CMN_CMN_CmMnbcSoundInd_001(
        SLAC_Header v_slac_header,
        Count_TYPE v_count,
        RunID_TYPE v_runid,
        SourceRnd_Type v_source_rnd)
    {
      payload = { cm_mnbc_sound_ind = {
                      slac_header = v_slac_header,
                      source_id = 0x0000000000000000000000000000000000,
                      count = v_count,
                      runid = v_runid,
                      res0 = 0x0000000000000000,
                      source_rnd = v_source_rnd} }
    }
  }
  namespace Templates_CMN_CmAttenCharRsp
  {
    using namespace DataStructure_SLAC;
    Acvarfield_Type md_CMN_CMN_Acvarfield_001(
        MACAddress_TYPE v_source_address,
        RunID_TYPE v_runid){
        source_address = v_source_address,
        runid = v_runid,
        source_id = 0x0000000000000000000000000000000000,
        resp_id = 0x0000000000000000000000000000000000,
        result = 0x00} Acvarfield_Type md_CMN_CMN_Acvarfield_002(MACAddress_TYPE p_source_address,
                                                                 RunID_TYPE p_runid,
                                                                 StationID_TYPE p_source_id,
                                                                 StationID_TYPE p_resp_id,
                                                                 Result_TYPE p_result){
        source_address = p_source_address,
        runid = p_runid,
        source_id = p_source_id,
        resp_id = p_resp_id,
        result = p_result} MME_Payload md_CMN_CMN_CmAttenCharRsp_001(SLAC_Header v_slac_header,
                                                                     Acvarfield_Type v_acvarfield)
    {
      payload = { cm_atten_char_rsp = {
                      slac_header = v_slac_header,
                      acvarfield = v_acvarfield} }
    }
  }
  namespace Templates_CMN_CmValidate
  {
    using namespace DataStructure_SLAC;
    MME_Payload m_CMN_CMN_CmValidateReq_001()
    {
      {
        cm_validate_req = { signalType = 0x00,
                            vrVarField = {
                                pilot_timer = 0x00,
                                result = 0x01} }
      }
    }
    MME_Payload md_CMN_CMN_CmValidateReq_002(
        PilotTimer_TYPE p_pilot_timer)
    {
      {
        cm_validate_req = { signalType = 0x00,
                            vrVarField = {
                                pilot_timer = p_pilot_timer,
                                result = 0x01} }
      }
    }
    MME_Payload mw_CMN_CMN_CmValidateReq_003()
    {
      {
        cm_validate_req = { signalType = 0x00,
                            vrVarField = {
                                pilot_timer = ?,
                                result =      ? } }
      }
    }
    MME_Payload md_CMN_CMN_CmValidateReq_004(
        SignalType_TYPE p_signalType,
        PilotTimer_TYPE p_pilot_timer,
        Result_TYPE p_result)
    {
      {
        cm_validate_req = { signalType = p_signalType,
                            vrVarField = {
                                pilot_timer = p_pilot_timer,
                                result = p_result} }
      }
    }
    MME_Payload md_CMN_CMN_CmValidateCnf_001(
        Result_TYPE p_result)
    {
      {
        cm_validate_cnf = { signalType = 0x00,
                            vcVarField = {
                                toggle_num = 0x00,
                                result = p_result} }
      }
    }
    MME_Payload md_CMN_CMN_CmValidateCnf_002(
        ToggleNum_TYPE p_toggle_num,
        Result_TYPE p_result)
    {
      {
        cm_validate_cnf = { signalType = 0x00,
                            vcVarField = {
                                toggle_num = p_toggle_num,
                                result = p_result} }
      }
    }
    MME_Payload md_CMN_CMN_CmValidateCnf_003(
        SignalType_TYPE p_signalType,
        ToggleNum_TYPE p_toggle_num,
        Result_TYPE p_result)
    {
      {
        cm_validate_cnf = { signalType = p_signalType,
                            vcVarField = {
                                toggle_num = p_toggle_num,
                                result = p_result} }
      }
    }
  }
  namespace Templates_CMN_CmSlacMatch
  {
    using namespace DataStructure_SLAC;
    MME_Payload md_CMN_CMN_CmSlacMatchReq_001(
        SLAC_Header v_slac_header,
        MACAddress_TYPE v_pevmac,
        MACAddress_TYPE v_evsemac,
        RunID_TYPE v_runid)
    {
      payload = { cm_slac_match_req = {
                      slac_header = v_slac_header,
                      mvflength = 0x003E,
                      pevid = 0x0000000000000000000000000000000000,
                      pevmac = v_pevmac,
                      evseid = 0x0000000000000000000000000000000000,
                      evsemac = v_evsemac,
                      runid = v_runid,
                      res0 = 0x0000000000000000} }
    }
    MME_Payload md_CMN_CMN_CmSlacMatchReq_002(
        SLAC_Header v_slac_header,
        Mvflength_TYPE v_mvflength,
        StationID_TYPE v_pevid,
        MACAddress_TYPE v_pevmac,
        StationID_TYPE v_evseid,
        MACAddress_TYPE v_evsemac,
        RunID_TYPE v_runid)
    {
      payload = { cm_slac_match_req = {
                      slac_header = v_slac_header,
                      mvflength = v_mvflength,
                      pevid = v_pevid,
                      pevmac = v_pevmac,
                      evseid = v_evseid,
                      evsemac = v_evsemac,
                      runid = v_runid,
                      res0 = 0x0000000000000000} }
    }
    MME_Payload md_CMN_CMN_CmSlacMatchCnf_001(
        SLAC_Header v_slac_header,
        MACAddress_TYPE v_pevmac,
        MACAddress_TYPE v_evsemac,
        RunID_TYPE v_runid,
        NID_TYPE v_nid,
        NMK_TYPE v_nmk)
    {
      payload = { cm_slac_match_cnf = {
                      slac_header = v_slac_header,
                      mvflength = 0x0056,
                      pevid = 0x0000000000000000000000000000000000,
                      pevmac = v_pevmac,
                      evseid = 0x0000000000000000000000000000000000,
                      evsemac = v_evsemac,
                      runid = v_runid,
                      res0 = 0x0000000000000000,
                      nid = v_nid,
                      res1 = 0x00,
                      nmk = v_nmk} }
    }
    MME_Payload md_CMN_CMN_CmSlacMatchCnf_001(
        SLAC_Header v_slac_header,
        MACAddress_TYPE v_pevmac,
        MACAddress_TYPE v_evsemac,
        RunID_TYPE v_runid,
        NID_TYPE v_nid,
        NMK_TYPE v_nmk)
    {
      payload = { cm_slac_match_cnf = {
                      slac_header = v_slac_header,
                      mvflength = 0x0056,
                      pevid = 0x0000000000000000000000000000000000,
                      pevmac = v_pevmac,
                      evseid = 0x0000000000000000000000000000000000,
                      evsemac = v_evsemac,
                      runid = v_runid,
                      res0 = 0x0000000000000000,
                      nid = v_nid,
                      res1 = 0x00,
                      nmk = v_nmk} }
    }
    namespace Templates_CMN_CmSetKey
    {
      using namespace DataStructure_SLAC;
      MME_Payload md_CMN_CMN_CmSetKeyReq_001(
          NID_TYPE v_nid,
          NewKey_TYPE v_neykey)
      {
        payload = { cm_set_key_req = {
                        keytype = 0x01,
                        mynonce = 0x00000000,
                        yournonce = 0x00000000,
                        pid = 0x04,
                        prn = 0x0000,
                        pmn = 0x00,
                        ccocapability = 0x00,
                        nid = v_nid,
                        neweks = 0x01,
                        neykey = v_neykey} }
      }
      MME_Payload mdw_CMN_CMN_CmSetKeyCnf_001(
          Result_TYPE p_result)
      {
        payload = { cm_set_key_cnf = {
                        result = p_result,
                        mynonce =       ?,
                        yournonce =     ?,
                        pid =           ?,
                        prn =           ?,
                        pmn =           ?,
                        ccocapability = ? } }
      }
    }
    namespace Templates_CMN_CmAmpMap
    {
      using namespace DataStructure_SLAC;
      MME_Payload m_CMN_CMN_CmAmpMapReq_001()
      {
        {
          cm_amp_map_req = { amlen = 0x0395,
                             listAmdata = {
                                 amdata = {
                                              0xC0} &
                                          {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00}} }
        }
      }
      MME_Payload md_CMN_CMN_CmAmpMapReq_002(
          Amlen_TYPE p_amlen,
          ListofAmdata_TYPE p_listAmdata)
      {
        {
          cm_amp_map_req = { amlen = p_amlen,
                             listAmdata = p_listAmdata
          }
        }
      }
      MME_Payload md_CMN_CMN_CmAmpMapReq_003(
          Amlen_TYPE p_amlen)
      {
        {
          cm_amp_map_req = { amlen = p_amlen,
                             listAmdata = {
                                 amdata = {
                                              0xC0} &
                                          {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xC0} & {0xBC} & {0xBC} & {0xAA} & {0xAA} & {0x8F} & {0x8F} & {0x8F} & {0x8F} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0xA1} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00} & {0x00}} }
        }
      }
      MME_Payload md_CMN_CMN_CmAmpMapCnf_001(
          Result_TYPE p_result)
      {
        {
          cm_amp_map_cnf = { result = p_result
          }
        }
      }
    }
    namespace Templates_CMN_CmNwStats
    {
      using namespace DataStructure_SLAC;
      MME_Payload md_CMN_CMN_CmNwStatsReq_001()
      {
        {
          cm_nw_stats_req = {}
        }
      }
      MME_Payload md_CMN_CMN_CmNwStatsCnf_001()
      {
        {
          cm_nw_stats_cnf = { numStas =    ?,
                              listOfStas = ? }
        }
      }
      MME_Payload md_CMN_CMN_CmNwStatsCnf_002()
      {
        {
          cm_nw_stats_cnf = { numStas = 0x00,
                              listOfStas = omit
          }
        }
      }
    }
    namespace Templates_EVCC_CmAttenProfileInd
    {
      using namespace DataStructure_SLAC;
      MME_Payload md_EVCC_CMN_CmAttenProfileInd_001(
          MACAddress_TYPE v_pev_address,
          NumGroups_TYPE v_num_groups,
          AttenProfile_TYPE v_attenuation_list)
      {
        payload = { cm_atten_profile_ind = {
                        pev_address = v_pev_address,
                        num_groups = v_num_groups,
                        res1 = 0x00,
                        attenuation_list = v_attenuation_list} }
      }
      AttenProfile_TYPE mw_EVCC_CMN_AttenProfile_001()
      {
        attenuation = {
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ?,
          ? }
      }
    }
    namespace Templates_EVCC_CmAttenCharInd
    {
      using namespace DataStructure_SLAC all;
      MME_Payload md_EVCC_CMN_CmAttenCharInd_001(
          SLAC_Header v_slac_header,
          MACAddress_TYPE v_source_address,
          RunID_TYPE v_runid,
          NumSounds_TYPE v_num_sounds,
          AttenProfile_TYPE v_atten_list)
      {
        payload = { cm_atten_char_ind = {
                        slac_header = v_slac_header,
                        source_address = v_source_address,
                        runid = v_runid,
                        source_id = 0x0000000000000000000000000000000000,
                        resp_id = 0x0000000000000000000000000000000000,
                        num_sounds = v_num_sounds,
                        num_groups = 0x3A,
                        attenuation_list = v_atten_list} }
      }
      MME_Payload md_EVCC_CMN_CmAttenCharInd_002(
          SLAC_Header v_slac_header,
          MACAddress_TYPE v_source_address,
          RunID_TYPE v_runid,
          NumSounds_TYPE v_num_sounds,
          StationID_TYPE v_source_id,
          StationID_TYPE v_resp_id,
          NumGroups_TYPE v_num_groups,
          AttenProfile_TYPE v_atten_list)
      {
        payload = { cm_atten_char_ind = {
                        slac_header = v_slac_header,
                        source_address = v_source_address,
                        runid = v_runid,
                        source_id = v_source_id,
                        resp_id = v_resp_id,
                        num_sounds = v_num_sounds,
                        num_groups = v_num_groups,
                        attenuation_list = v_atten_list} }
      }
      AttenProfile_TYPE m_EVCC_CMN_atten_list_001()
      {
        attenuation = { 0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E,
                        0x1E
        }
      }
      AttenProfile_TYPE m_EVCC_CMN_atten_list_002()
      {
        attenuation = { 0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28,
                        0x28
        }
      }
    } */

  } // namespace TestLib