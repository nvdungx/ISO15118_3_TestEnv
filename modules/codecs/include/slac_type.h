#ifndef __SLAC_TYPE_H__
#define __SLAC_TYPE_H__

#include <array>
#include <vector>

#define hexstring(A) std::array<uint8_t, A>
// template<typename s>
// using hexstring = std::array<uint8_t, s>;

namespace DataStructure_SLAC
{
  typedef struct SLAC_Header
  {
    hexstring(2) application_type;
    hexstring(2) security_type;
  } SLAC_Header_st;
  typedef hexstring(2) MMV_TYPE;
  typedef hexstring(2) Fmi_TYPE;
  typedef hexstring(2) Fmsn_TYPE;
  typedef hexstring(6) OUI_TYPE;         // with{variant "byteOrder=big-endian"};
  typedef hexstring(32) NMK_TYPE;        // with{variant "byteOrder=big-endian"};
  typedef hexstring(14) NID_TYPE;        // with{variant "byteOrder=big-endian"};
  typedef hexstring(12) MACAddress_TYPE; // with{variant "byteOrder=big-endian"};
  typedef hexstring(34) StationID_TYPE;
  typedef hexstring(16) RunID_TYPE;
  typedef hexstring(2) TimeOut_TYPE;
  typedef hexstring(2) NumSounds_TYPE;
  typedef hexstring(2) NumGroups_TYPE;
  typedef hexstring(2) ToggleNum_TYPE;
  typedef hexstring(2) RespType_TYPE;
  typedef hexstring(2) Aag_TYPE;
  typedef hexstring(2) Result_TYPE;
  typedef hexstring(4) Mvflength_TYPE;
  typedef hexstring(16) Res0_TYPE;
  typedef hexstring(2) Res1_TYPE;
  typedef hexstring(2) Count_TYPE;
  typedef hexstring(32) SourceRnd_Type;
  typedef hexstring(2) Attenuation_TYPE;
  typedef hexstring(2) SignalType_TYPE;
  typedef hexstring(2) PilotTimer_TYPE;
  typedef hexstring(2) KeyType_TYPE;
  typedef hexstring(8) MyNonce_TYPE;
  typedef hexstring(8) YourNonce_TYPE;
  typedef hexstring(2) PID_TYPE;
  typedef hexstring(4) PRN_TYPE;
  typedef hexstring(2) PMN_TYPE;
  typedef hexstring(2) CCoCapability_TYPE;
  typedef hexstring(2) NewEKS_TYPE;
  typedef hexstring(32) NewKey_TYPE; // with{variant "byteOrder=big-endian"};
  typedef hexstring(2) LnkStatus_TYPE;
  typedef hexstring(2) NumStas_TYPE;
  typedef hexstring(2) DataRate_TYPE;
  typedef hexstring(4) Amlen_TYPE;
  typedef hexstring(2) Amdata_TYPE;
  typedef hexstring(2) HostActionReq_TYPE;
  typedef hexstring(2) SessionId_TYPE;
  typedef hexstring(4) OutstandingRetries_TYPE;
  typedef hexstring(4) RetryTimer10ms_TYPE;
  typedef hexstring(2) MStatus_TYPE;

  #define MME_CM_SLAC_PARM_REQ        ((uint16_t)0x6064)
  #define MME_CM_SLAC_PARM_CNF        ((uint16_t)0x6065)
  #define MME_CM_START_ATTEN_CHAR_IND ((uint16_t)0x606A)
  #define MME_CM_ATTEN_CHAR_IND       ((uint16_t)0x606E)
  #define MME_CM_ATTEN_CHAR_RSP       ((uint16_t)0x606F)
  #define MME_CM_MNBC_SOUND_IND       ((uint16_t)0x6076)
  #define MME_CM_VALIDATE_REQ         ((uint16_t)0x6078)
  #define MME_CM_VALIDATE_CNF         ((uint16_t)0x6079)
  #define MME_CM_SLAC_MATCH_REQ       ((uint16_t)0x607C)
  #define MME_CM_SLAC_MATCH_CNF       ((uint16_t)0x607D)
  #define MME_CM_ATTEN_PROFILE_IND    ((uint16_t)0x6086)
  #define MME_CM_SET_KEY_REQ          ((uint16_t)0x6008)
  #define MME_CM_SET_KEY_CNF          ((uint16_t)0x6009)
  #define MME_VS_PL_LNK_STATUS_REQ    ((uint16_t)0xA0B8)
  #define MME_VS_PL_LNK_STATUS_CNF    ((uint16_t)0xA0B9)
  #define MME_CM_AMP_MAP_REQ          ((uint16_t)0x601C)
  #define MME_CM_AMP_MAP_CNF          ((uint16_t)0x601D)
  #define MME_VS_HST_ACTION_REQ       ((uint16_t)0xA062)
  #define MME_VS_HST_ACTION_RSP       ((uint16_t)0xA063)
  #define MME_CM_NW_STATS_REQ         ((uint16_t)0x6048)
  #define MME_CM_NW_STATS_CNF         ((uint16_t)0x6049)
  typedef union MM_TYPE
  {
    hexstring(2) value;
    uint16_t CM_SLAC_PARM_REQ;
    uint16_t CM_SLAC_PARM_CNF;
    uint16_t CM_START_ATTEN_CHAR_IND;
    uint16_t CM_ATTEN_CHAR_IND;
    uint16_t CM_ATTEN_CHAR_RSP;
    uint16_t CM_MNBC_SOUND_IND;
    uint16_t CM_VALIDATE_REQ;
    uint16_t CM_VALIDATE_CNF;
    uint16_t CM_SLAC_MATCH_REQ;
    uint16_t CM_SLAC_MATCH_CNF;
    uint16_t CM_ATTEN_PROFILE_IND;
    uint16_t CM_SET_KEY_REQ;
    uint16_t CM_SET_KEY_CNF;
    uint16_t VS_PL_LNK_STATUS_REQ;
    uint16_t VS_PL_LNK_STATUS_CNF;
    uint16_t CM_AMP_MAP_REQ;
    uint16_t CM_AMP_MAP_CNF;
    uint16_t VS_HST_ACTION_REQ;
    uint16_t VS_HST_ACTION_RSP;
    uint16_t CM_NW_STATS_REQ;
    uint16_t CM_NW_STATS_CNF;
  } MM_TYPE_st;
  typedef struct AttenProfile_TYPE
  {
    std::vector<Attenuation_TYPE> attenuation;
    const uint8_t min_size = 1;
    const uint8_t max_size = 58;
  } AttenProfile_TYPE_st;
  typedef struct ACVarField_TYPE
  {
    MACAddress_TYPE source_address;
    RunID_TYPE runid;
    StationID_TYPE source_id;
    StationID_TYPE resp_id;
    Result_TYPE result;
  } ACVarField_TYPE_st;
  typedef struct VRVarField_TYPE
  {
    PilotTimer_TYPE pilot_timer;
    Result_TYPE result;
  } VRVarField_TYPE_st;
  typedef struct VCVarField_TYPE
  {
    ToggleNum_TYPE toggle_num;
    Result_TYPE result;
  } VCVarField_TYPE_st;

  typedef struct CM_SLAC_PARM_REQ
  {
    SLAC_Header_st slac_header;
    RunID_TYPE runid;
  } CM_SLAC_PARM_REQ_st;
  typedef struct CM_SLAC_PARM_CNF
  {
    MACAddress_TYPE msound_target;
    NumSounds_TYPE num_sounds;
    TimeOut_TYPE time_out;
    RespType_TYPE resp_type;
    MACAddress_TYPE forwarding_sta;
    SLAC_Header_st appheader;
    RunID_TYPE runid;
  } CM_SLAC_PARM_CNF_st;
  typedef struct CM_START_ATTEN_CHAR_IND
  {
    SLAC_Header_st slac_header;
    NumSounds_TYPE num_sounds;
    TimeOut_TYPE time_out;
    RespType_TYPE resp_type;
    MACAddress_TYPE forwarding_sta;
    RunID_TYPE runid;
  } CM_START_ATTEN_CHAR_IND_st;
  typedef struct CM_ATTEN_CHAR_IND
  {
    SLAC_Header_st slac_header;
    MACAddress_TYPE source_address;
    RunID_TYPE runid;
    StationID_TYPE source_id;
    StationID_TYPE resp_id;
    NumSounds_TYPE num_sounds;
    NumGroups_TYPE num_groups;
    AttenProfile_TYPE_st attenuation_list;
  } CM_ATTEN_CHAR_IND_st;
  typedef struct CM_ATTEN_CHAR_RSP
  {
    SLAC_Header_st slac_header;
    ACVarField_TYPE_st acvarfield;
  } CM_ATTEN_CHAR_RSP_st;
  typedef struct CM_MNBC_SOUND_IND
  {
    SLAC_Header_st slac_header;
    StationID_TYPE source_id;
    Count_TYPE count;
    RunID_TYPE runid;
    Res0_TYPE res0;
    SourceRnd_Type source_rnd;
  } CM_MNBC_SOUND_IND_st;
  typedef struct CM_ATTEN_PROFILE_IND
  {
    MACAddress_TYPE pev_address;
    NumGroups_TYPE num_groups;
    Res1_TYPE res1;
    AttenProfile_TYPE_st attenuation_list;
    bool attenuation_list_isUsed;
  } CM_ATTEN_PROFILE_IND_st;

  typedef struct CM_VALIDATE_REQ
  {
    SignalType_TYPE signalType;
    VRVarField_TYPE_st vrVarField;
  } CM_VALIDATE_REQ_st;
  typedef struct CM_VALIDATE_CNF
  {
    SignalType_TYPE signalType;
    VCVarField_TYPE_st vcVarField;
  } CM_VALIDATE_CNF_st;
  typedef struct CM_SLAC_MATCH_REQ
  {
    SLAC_Header_st slac_header;
    Mvflength_TYPE mvflength;
    StationID_TYPE pevid;
    MACAddress_TYPE pevmac;
    StationID_TYPE evseid;
    MACAddress_TYPE evsemac;
    RunID_TYPE runid;
    Res0_TYPE res0;
  } CM_SLAC_MATCH_REQ_st;
  typedef struct CM_SLAC_MATCH_CNF
  {
    SLAC_Header_st slac_header;
    Mvflength_TYPE mvflength;
    StationID_TYPE pevid;
    MACAddress_TYPE pevmac;
    StationID_TYPE evseid;
    MACAddress_TYPE evsemac;
    RunID_TYPE runid;
    Res0_TYPE res0;
    NID_TYPE nid;
    Res1_TYPE res1;
    NMK_TYPE nmk;
  } CM_SLAC_MATCH_CNF_st;
  typedef struct CM_SET_KEY_REQ
  {
    KeyType_TYPE keytype;
    MyNonce_TYPE mynonce;
    YourNonce_TYPE yournonce;
    PID_TYPE pid;
    PRN_TYPE prn;
    PMN_TYPE pmn;
    CCoCapability_TYPE ccocapability;
    NID_TYPE nid;
    NewEKS_TYPE neweks;
    NewKey_TYPE neykey;
  } CM_SET_KEY_REQ_st;
  typedef struct CM_SET_KEY_CNF
  {
    Result_TYPE result;
    MyNonce_TYPE mynonce;
    YourNonce_TYPE yournonce;
    PID_TYPE pid;
    PRN_TYPE prn;
    PMN_TYPE pmn;
    CCoCapability_TYPE ccocapability;
  } CM_SET_KEY_CNF_st;
  typedef struct VS_PL_LNK_STATUS_REQ
  {
    OUI_TYPE oui;
  } VS_PL_LNK_STATUS_REQ_st; // with{variant "FMI=false"}
  typedef struct VS_PL_LNK_STATUS_CNF
  {
    OUI_TYPE oui;
    Result_TYPE result;
    LnkStatus_TYPE lnkStatus;
  } VS_PL_LNK_STATUS_CNF_st; //with{variant "FMI=false"}
  // typedef struct of MME ResponseMessageList_TYPE;
  typedef struct MACAddressList_TYPE
  {
    std::vector<MACAddress_TYPE> macAddressList;
    bool macAddressList_isUsed;
    const uint8_t min_size = 0;
    const uint8_t max_size = 10; // length(0..10) optional
  } MACAddressList_TYPE_st;
  typedef float T_conn_comm_TYPE; //(0.0..8.0);
  typedef struct ListofAmdata_TYPE
  {
    std::vector<Amdata_TYPE> amdata; // length(0..1155)
    const uint16_t min_size = 0;
    const uint16_t max_size = 1155;
  } ListofAmdata_TYPE_st;
  typedef struct CM_AMP_MAP_REQ
  {
    Amlen_TYPE amlen;
    ListofAmdata_TYPE_st listAmdata;
  } CM_AMP_MAP_REQ_st;
  typedef struct CM_AMP_MAP_CNF
  {
    Result_TYPE result;
  } CM_AMP_MAP_CNF_st;
  typedef struct VS_HST_ACTION_REQ
  {
    OUI_TYPE oui;
    HostActionReq_TYPE hostActionReq;
    SessionId_TYPE sessionId;
    OutstandingRetries_TYPE outstandingRetries;
    RetryTimer10ms_TYPE retryTimer10ms;
  } VS_HST_ACTION_REQ_st; // with{variant "FMI=false"}
  typedef struct VS_HST_ACTION_RSP
  {
    OUI_TYPE oui;
    MStatus_TYPE mStatus;
    HostActionReq_TYPE hostActionReq;
    SessionId_TYPE sessionId;
    OutstandingRetries_TYPE outstandingRetries;
  } VS_HST_ACTION_RSP_st; // with{variant "FMI=false"}
  typedef struct CM_NW_STATS_REQ
  {
  } CM_NW_STATS_REQ_st;
  typedef struct Stas_TYPE
  {
    MACAddress_TYPE macAddress;
    DataRate_TYPE avgPHYDR_tx;
    DataRate_TYPE avgPHYDR_rx;
  } Stas_TYPE_st;
  typedef struct ListofStas_TYPE
  {
    std::vector<Stas_TYPE_st> stas; // length(1..8)
    const uint8_t min_size = 1;
    const uint8_t max_size = 8;
  } ListofStas_TYPE_st;
  typedef struct CM_NW_STATS_CNF
  {
    NumStas_TYPE numStas;
    ListofStas_TYPE_st listOfStas;
    bool listOfStas_isUsed; // optional
  } CM_NW_STATS_CNF_st;

  typedef struct MME_Header
  {
    MMV_TYPE mmv;
    MM_TYPE_st mmtype;
    Fmi_TYPE fmi;
    bool fmi_isUsed;
    Fmsn_TYPE fmsn;
    bool fmsn_iUsed;
  } MME_Header_st;
  typedef struct MME_Payload
  {
    union
    {
      CM_SLAC_PARM_REQ_st cm_slac_parm_req;
      CM_SLAC_PARM_CNF_st cm_slac_parm_cnf;
      CM_START_ATTEN_CHAR_IND_st cm_start_atten_char_ind;
      CM_ATTEN_CHAR_IND_st cm_atten_char_ind;
      CM_ATTEN_CHAR_RSP_st cm_atten_char_rsp;
      CM_MNBC_SOUND_IND_st cm_mnbc_sound_ind;
      CM_ATTEN_PROFILE_IND_st cm_atten_profile_ind;
      CM_VALIDATE_REQ_st cm_validate_req;
      CM_VALIDATE_CNF_st cm_validate_cnf;
      CM_SLAC_MATCH_REQ_st cm_slac_match_req;
      CM_SLAC_MATCH_CNF_st cm_slac_match_cnf;
      CM_SET_KEY_REQ_st cm_set_key_req;
      CM_SET_KEY_CNF_st cm_set_key_cnf;
      VS_PL_LNK_STATUS_REQ_st vs_pl_lnk_status_req;
      VS_PL_LNK_STATUS_CNF_st vs_pl_lnk_status_cnf;
      CM_AMP_MAP_REQ_st cm_amp_map_req;
      CM_AMP_MAP_CNF_st cm_amp_map_cnf;
      VS_HST_ACTION_REQ_st vs_hst_action_req;
      VS_HST_ACTION_RSP_st vs_hst_action_rsp;
      CM_NW_STATS_REQ_st cm_nw_stats_req;
      CM_NW_STATS_CNF_st cm_nw_stats_cnf;
    } payload;
  } MME_Payload_st;
  typedef struct MME
  {
    MME_Header_st mme_header;
    MME_Payload_st mme_payload;
  } MME_st;
}
// with
// {
//   encode "SLAC";
// }

#endif // __SLAC_TYPE_H__