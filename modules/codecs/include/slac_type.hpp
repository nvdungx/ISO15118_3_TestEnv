#ifndef __SLAC_TYPE_H__
#define __SLAC_TYPE_H__

#include <array>
#include <vector>
#include <cstdint>
#include <string_view>
#include <cstring>
#include <spdlog/spdlog.h>

namespace TestLib {

template <size_t size>
class hexstring
{
private:
  uint8_t raw_data[size];

  uint8_t get_nibble(const char &c)
  {
    if (('0' <= c) && ('9' >= c))
    {
      return c - '0';
    }
    else if (('A' <= c) && ('F' >= c))
    {
      return (c - 'A' + 0x0A);
    }
    else if (('a' <= c) && ('f' >= c))
    {
      return (c - 'a' + 0x0A);
    }
    else
    {
      spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, "Invalid hex nibble");
      return 0;
    }
  }
public:
  hexstring()
  {
    for (size_t i = 0; i < size; i++)
    {
      raw_data[i] = 0;
    }
  }
  hexstring(const std::array<uint8_t, size> &input)
  {
    for (size_t i = 0; i < size/2; i++)
    {
      raw_data[i] = input[i];
    }
  }
  hexstring(const std::string_view &input)
  {
    /* clear array */
    for (size_t i = 0; i < size; i++)
    {
      raw_data[i] = 0;
    }
    /* go through all char and char index smaller than size*2 */
    for (size_t i = 0; (i < input.size()) && (size > (i/2)); i++)
    {
      if (i%2 == 0)
      {
        /* even index char at high nibble */
        raw_data[i/2] = this->get_nibble(input[i]) << 4;
      }
      else
      {
        /* odd at low nibble of hex */
        raw_data[i/2] |= this->get_nibble(input[i]);
      }
    }
  }
  bool operator!=(const hexstring<size> &rho)
  {
    bool result = true;
    for (size_t i = 0; i < size; i++)
    {
      result &= (rho.raw_data[i] != raw_data[i]);
    }
    return result;
  }
  bool operator==(const hexstring<size> &rho)
  {
    bool result = true;
    for (size_t i = 0; i < size; i++)
    {
      result &= (rho.raw_data[i] == raw_data[i]);
    }
    return result;
  }
};

// ISO15118 hexstring<2> = '00' << 1 byte, TBD: check if required to change to
// template class hexstring<size>
// #define hexstring(A) std::array<uint8_t, A>

extern hexstring<6> par_slac_node2_mac;
extern hexstring<6> par_slac_node3_mac;
extern hexstring<6> par_slac_node4_mac;
extern hexstring<6> par_slac_node5_mac;

namespace DataStructure_SLAC
{
  typedef struct stSLAC_Header
  {
    uint8_t application_type; // hexstring len 2
    uint8_t security_type;    // hexstring len 2
  } SLAC_Header;

  typedef uint8_t MMV_TYPE;   // hexstring len 2
  typedef uint8_t Fmi_TYPE;   // hexstring len 2
  typedef uint8_t Fmsn_TYPE;  // hexstring len 2
  typedef hexstring<3> OUI_TYPE;          // hexstring len 6 with{variant "byteOrder=big-endian"};
  typedef hexstring<16> NMK_TYPE;         // hexstring len 32 with{variant "byteOrder=big-endian"};
  typedef hexstring<7> NID_TYPE;          // hexstring len 14 with{variant "byteOrder=big-endian"};
  typedef hexstring<6> MACAddress_TYPE;   // hexstring len 12 with{variant "byteOrder=big-endian"};
  typedef hexstring<17> StationID_TYPE;   // hexstring len 34
  typedef hexstring<8> RunID_TYPE;        // hexstring len 16
  typedef uint8_t TimeOut_TYPE;   // hexstring len 2
  typedef uint8_t NumSounds_TYPE; // hexstring len 2
  typedef uint8_t NumGroups_TYPE; // hexstring len 2
  typedef uint8_t ToggleNum_TYPE; // hexstring len 2
  typedef uint8_t RespType_TYPE;  // hexstring len 2
  typedef uint8_t Aag_TYPE;       // hexstring len 2
  typedef uint8_t Result_TYPE;    // hexstring len 2
  typedef uint16_t Mvflength_TYPE;  // hexstring len 4
  typedef hexstring<8> Res0_TYPE; // hexstring len 16
  typedef uint8_t Res1_TYPE;  // hexstring len 2
  typedef uint8_t Count_TYPE; // hexstring len 2
  typedef hexstring<16> SourceRnd_Type; // hexstring len 32
  typedef uint8_t Attenuation_TYPE; // hexstring len 2
  typedef uint8_t SignalType_TYPE;  // hexstring len 2
  typedef uint8_t PilotTimer_TYPE;  // hexstring len 2
  typedef uint8_t KeyType_TYPE;     // hexstring len 2
  typedef uint32_t MyNonce_TYPE;  // hexstring len 8
  typedef uint32_t YourNonce_TYPE;  // hexstring len 8
  typedef uint8_t PID_TYPE;       // hexstring len 2
  typedef uint16_t PRN_TYPE;      // hexstring len 4
  typedef uint8_t PMN_TYPE;       // hexstring len 2
  typedef uint8_t CCoCapability_TYPE; // hexstring len 2
  typedef uint8_t NewEKS_TYPE;        // hexstring len 2
  typedef hexstring<16> NewKey_TYPE; // hexstring len 32 with{variant "byteOrder=big-endian"};
  typedef uint8_t LnkStatus_TYPE; // hexstring len 2
  typedef uint8_t NumStas_TYPE; // hexstring len 2
  typedef uint8_t DataRate_TYPE;  // hexstring len 2
  typedef uint16_t Amlen_TYPE;  // hexstring len 4
  typedef uint8_t Amdata_TYPE;  // hexstring len 2
  typedef uint8_t HostActionReq_TYPE; // hexstring len 2
  typedef uint8_t SessionId_TYPE;     // hexstring len 2
  typedef uint16_t OutstandingRetries_TYPE; // hexstring len 4
  typedef uint16_t RetryTimer10ms_TYPE; // hexstring len 4
  typedef uint8_t MStatus_TYPE;     // hexstring len 2

  /* MME Management	Message	Entry */
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
  /* Management message type */
  typedef union stMM_TYPE
  {
    uint16_t value;
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
  } MM_TYPE;

  typedef struct stAttenProfile_TYPE
  {
    std::array<Attenuation_TYPE, 58> attenuation;
  } AttenProfile_TYPE;

  typedef struct stACVarField_TYPE
  {
    MACAddress_TYPE source_address;
    RunID_TYPE runid;
    StationID_TYPE source_id;
    StationID_TYPE resp_id;
    Result_TYPE result;
  } ACVarField_TYPE;

  typedef struct stVRVarField_TYPE
  {
    PilotTimer_TYPE pilot_timer;
    Result_TYPE result;
  } VRVarField_TYPE;

  typedef struct VCVarField_TYPE
  {
    ToggleNum_TYPE toggle_num;
    Result_TYPE result;
  } VCVarField_TYPE;

  // typedef struct of MME ResponseMessageList_TYPE;
  typedef struct stMACAddressList_TYPE
  {
    std::vector<MACAddress_TYPE> macAddressList;
    bool macAddressList_isUsed;
    const uint8_t min_size = 0;
    const uint8_t max_size = 10; // length(0..10) optional
  } MACAddressList_TYPE;

  typedef float T_conn_comm_TYPE; //(0.0..8.0);
  #define T_conn_comm_TYPE_MIN ((float)(0.0F))
  #define T_conn_comm_TYPE_MAX ((float)(8.0F))

  typedef struct stListofAmdata_TYPE
  {
    std::vector<Amdata_TYPE> amdata; // length(0..1155)
    const uint16_t min_size = 0;
    const uint16_t max_size = 1155;
  } ListofAmdata_TYPE;

  typedef struct stStas_TYPE
  {
    MACAddress_TYPE macAddress;
    DataRate_TYPE avgPHYDR_tx;
    DataRate_TYPE avgPHYDR_rx;
  } Stas_TYPE;
  typedef struct stListofStas_TYPE
  {
    std::vector<Stas_TYPE> stas; // length(1..8)
    const uint8_t min_size = 1;
    const uint8_t max_size = 8;
  } ListofStas_TYPE;

  /* specific MME payload - SLAC layer message */
  /* EVCC - SLAC param request - broadcast */
  typedef struct stCM_SLAC_PARM_REQ
  {
    SLAC_Header slac_header;
    RunID_TYPE runid;
  } CM_SLAC_PARM_REQ;

  /* SECC - SLAC param confirm */
  typedef struct stCM_SLAC_PARM_CNF
  {
    MACAddress_TYPE msound_target;
    NumSounds_TYPE num_sounds;
    TimeOut_TYPE time_out;
    RespType_TYPE resp_type;
    MACAddress_TYPE forwarding_sta;
    SLAC_Header appheader;
    RunID_TYPE runid;
  } CM_SLAC_PARM_CNF;

  /* EVCC - SLAC start attenuation char indication - broadcast */
  typedef struct stCM_START_ATTEN_CHAR_IND
  {
    SLAC_Header slac_header;
    NumSounds_TYPE num_sounds;
    TimeOut_TYPE time_out;
    RespType_TYPE resp_type;
    MACAddress_TYPE forwarding_sta;
    RunID_TYPE runid;
  } CM_START_ATTEN_CHAR_IND;

  /* SECC */
  typedef struct stCM_ATTEN_CHAR_IND
  {
    SLAC_Header slac_header;
    MACAddress_TYPE source_address;
    RunID_TYPE runid;
    StationID_TYPE source_id;
    StationID_TYPE resp_id;
    NumSounds_TYPE num_sounds;
    NumGroups_TYPE num_groups;
    AttenProfile_TYPE attenuation_list;
  } CM_ATTEN_CHAR_IND;

  /* EVCC */
  typedef struct stCM_ATTEN_CHAR_RSP
  {
    SLAC_Header slac_header;
    ACVarField_TYPE acvarfield;
  } CM_ATTEN_CHAR_RSP;

  /* EVCC */
  typedef struct stCM_MNBC_SOUND_IND
  {
    SLAC_Header slac_header;
    StationID_TYPE source_id;
    Count_TYPE count;
    RunID_TYPE runid;
    Res0_TYPE res0;
    SourceRnd_Type source_rnd;
  } CM_MNBC_SOUND_IND;

  /* EVCC */
  typedef struct stCM_ATTEN_PROFILE_IND
  {
    MACAddress_TYPE pev_address;
    NumGroups_TYPE num_groups;
    Res1_TYPE res1;
    AttenProfile_TYPE attenuation_list; // optional
    bool attenuation_list_isUsed;
  } CM_ATTEN_PROFILE_IND;

  typedef struct stCM_VALIDATE_REQ
  {
    SignalType_TYPE signalType;
    VRVarField_TYPE vrVarField;
  } CM_VALIDATE_REQ;

  typedef struct stCM_VALIDATE_CNF
  {
    SignalType_TYPE signalType;
    VCVarField_TYPE vcVarField;
  } CM_VALIDATE_CNF;

  typedef struct stCM_SLAC_MATCH_REQ
  {
    SLAC_Header slac_header;
    Mvflength_TYPE mvflength;
    StationID_TYPE pevid;
    MACAddress_TYPE pevmac;
    StationID_TYPE evseid;
    MACAddress_TYPE evsemac;
    RunID_TYPE runid;
    Res0_TYPE res0;
  } CM_SLAC_MATCH_REQ;

  typedef struct stCM_SLAC_MATCH_CNF
  {
    SLAC_Header slac_header;
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
  } CM_SLAC_MATCH_CNF;

  typedef struct stCM_SET_KEY_REQ
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
  } CM_SET_KEY_REQ;

  typedef struct stCM_SET_KEY_CNF
  {
    Result_TYPE result;
    MyNonce_TYPE mynonce;
    YourNonce_TYPE yournonce;
    PID_TYPE pid;
    PRN_TYPE prn;
    PMN_TYPE pmn;
    CCoCapability_TYPE ccocapability;
  } CM_SET_KEY_CNF;

  typedef struct stCM_AMP_MAP_REQ
  {
    Amlen_TYPE amlen;
    ListofAmdata_TYPE listAmdata;
  } CM_AMP_MAP_REQ;

  typedef struct stCM_AMP_MAP_CNF
  {
    Result_TYPE result;
  } CM_AMP_MAP_CNF;

  typedef struct stCM_NW_STATS_REQ
  {
  } CM_NW_STATS_REQ;

  typedef struct stCM_NW_STATS_CNF
  {
    NumStas_TYPE numStas;
    ListofStas_TYPE listOfStas; // optional
    bool listOfStas_isUsed;
  } CM_NW_STATS_CNF;

  typedef struct stVS_PL_LNK_STATUS_REQ
  {
    OUI_TYPE oui;
  } VS_PL_LNK_STATUS_REQ; // with{variant "FMI=false"}

  typedef struct stVS_PL_LNK_STATUS_CNF
  {
    OUI_TYPE oui;
    Result_TYPE result;
    LnkStatus_TYPE lnkStatus;
  } VS_PL_LNK_STATUS_CNF; //with{variant "FMI=false"}

  typedef struct stVS_HST_ACTION_REQ
  {
    OUI_TYPE oui;
    HostActionReq_TYPE hostActionReq;
    SessionId_TYPE sessionId;
    OutstandingRetries_TYPE outstandingRetries;
    RetryTimer10ms_TYPE retryTimer10ms;
  } VS_HST_ACTION_REQ; // with{variant "FMI=false"}

  typedef struct stVS_HST_ACTION_RSP
  {
    OUI_TYPE oui;
    MStatus_TYPE mStatus;
    HostActionReq_TYPE hostActionReq;
    SessionId_TYPE sessionId;
    OutstandingRetries_TYPE outstandingRetries;
  } VS_HST_ACTION_RSP; // with{variant "FMI=false"}

  /* Management Message Entry header */
  typedef struct stMME_Header
  {
    /* Management Message Version */
    MMV_TYPE mmv;
    /* Management Message Type */
    MM_TYPE mmtype;
    /* Fragmentation Management Information */
    Fmi_TYPE fmi; // optional
    bool fmi_isUsed;
    /* Fragmentation Message Sequence Number */
    Fmsn_TYPE fmsn; // optional
    bool fmsn_isUsed;
  } MME_Header;

  typedef struct stMME_Payload
  {
    union unPayload
    {
      CM_SLAC_PARM_REQ cm_slac_parm_req;
      CM_SLAC_PARM_CNF cm_slac_parm_cnf;
      CM_START_ATTEN_CHAR_IND cm_start_atten_char_ind;
      CM_ATTEN_CHAR_IND cm_atten_char_ind;
      CM_ATTEN_CHAR_RSP cm_atten_char_rsp;
      CM_MNBC_SOUND_IND cm_mnbc_sound_ind;
      CM_ATTEN_PROFILE_IND cm_atten_profile_ind;
      CM_VALIDATE_REQ cm_validate_req;
      CM_VALIDATE_CNF cm_validate_cnf;
      CM_SLAC_MATCH_REQ cm_slac_match_req;
      CM_SLAC_MATCH_CNF cm_slac_match_cnf;
      CM_SET_KEY_REQ cm_set_key_req;
      CM_SET_KEY_CNF cm_set_key_cnf;
      VS_PL_LNK_STATUS_REQ vs_pl_lnk_status_req;
      VS_PL_LNK_STATUS_CNF vs_pl_lnk_status_cnf;
      CM_AMP_MAP_REQ cm_amp_map_req;
      CM_AMP_MAP_CNF cm_amp_map_cnf;
      VS_HST_ACTION_REQ vs_hst_action_req;
      VS_HST_ACTION_RSP vs_hst_action_rsp;
      CM_NW_STATS_REQ cm_nw_stats_req;
      CM_NW_STATS_CNF cm_nw_stats_cnf;
      unPayload()
      {
      }
      ~unPayload()
      {
      }
    } payload;
  } MME_Payload;

  /* management message entry: messages exchange between PLC node */
  typedef struct stMME
  {
    MME_Header mme_header;
    MME_Payload mme_payload;
  } MME;
}
// with
// {
//   encode "SLAC";
// }
} // namespace TestLib

#endif // __SLAC_TYPE_H__