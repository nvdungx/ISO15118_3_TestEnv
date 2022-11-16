#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__

#include "slac_type.hpp"

namespace TestLib
{
namespace Templates_CMN_SlacPayloadHeader
{
using namespace DataStructure_SLAC;
SLAC_Header m_CMN_CMN_SlacPayloadHeader_001();
SLAC_Header m_CMN_CMN_SlacPayloadHeaderInvalid_001();
SLAC_Header m_CMN_CMN_SlacPayloadHeaderInvalid_002();
}

namespace Templates_CMN_SlacManagementMessageEntry
{
using namespace DataStructure_SLAC;
MME md_CMN_CMN_SlacMme_001(const MME_Header &p_mme_header, const MME_Payload &p_mme_payload);
MME_Header md_CMN_CMN_SlacMmeCmnHeader_001(const MM_TYPE &p_mmtype);
MME_Header md_CMN_CMN_SlacMmeOuiHeader_001(const MM_TYPE &p_mmtype);
}

namespace Templates_CMN_CmSlacParm
{
using namespace DataStructure_SLAC;
MME_Payload md_CMN_CMN_CmSlacParmReq_001(const SLAC_Header &v_slac_header, const RunID_TYPE &v_runid);
MME_Payload md_CMN_CMN_CmSlacParmCnf_001(const MACAddress_TYPE &p_forwarding_sta, const SLAC_Header &p_appheader, const RunID_TYPE &p_runid);
MME_Payload md_CMN_CMN_CmSlacParmCnf_002(const MACAddress_TYPE &p_msound_target, const NumSounds_TYPE &p_num_sounds, const TimeOut_TYPE &p_time_out, const RespType_TYPE &p_resp_type, const MACAddress_TYPE &p_forwarding_sta, const SLAC_Header &p_appheader, const RunID_TYPE &p_runid);
MACAddressList_TYPE m_CMN_CMN_EmptyMacAddressList();
}

namespace Templates_CMN_CmStartAttenCharInd
{
using namespace DataStructure_SLAC;
MME_Payload md_CMN_CMN_CmStartAttenCharInd_001(const SLAC_Header &v_slac_header, const NumSounds_TYPE &v_num_sounds, const TimeOut_TYPE &v_time_out, const RespType_TYPE &v_resp_type, const MACAddress_TYPE &v_forwarding_sta, const RunID_TYPE &v_runid);
}

namespace Templates_CMN_CmMnbcSoundInd
{
using namespace DataStructure_SLAC;
MME_Payload md_CMN_CMN_CmMnbcSoundInd_001(const SLAC_Header &v_slac_header, const Count_TYPE &v_count, const RunID_TYPE &v_runid, const SourceRnd_Type &v_source_rnd);
}

namespace Templates_CMN_CmAttenCharRsp
{
using namespace DataStructure_SLAC;
ACVarField_TYPE md_CMN_CMN_Acvarfield_001(const MACAddress_TYPE &v_source_address, const RunID_TYPE &v_runid);
ACVarField_TYPE md_CMN_CMN_Acvarfield_002(const MACAddress_TYPE &p_source_address,const RunID_TYPE &p_runid,const StationID_TYPE &p_source_id,const StationID_TYPE &p_resp_id,const Result_TYPE &p_result);
MME_Payload md_CMN_CMN_CmAttenCharRsp_001(const SLAC_Header &v_slac_header, const ACVarField_TYPE &v_acvarfield);
}

namespace Templates_CMN_CmValidate
{
using namespace DataStructure_SLAC;
MME_Payload m_CMN_CMN_CmValidateReq_001();
MME_Payload md_CMN_CMN_CmValidateReq_002(const PilotTimer_TYPE &p_pilot_timer);
MME_Payload mw_CMN_CMN_CmValidateReq_003();
MME_Payload md_CMN_CMN_CmValidateReq_004(const SignalType_TYPE &p_signalType,const PilotTimer_TYPE &p_pilot_timer,const Result_TYPE &p_result);
MME_Payload md_CMN_CMN_CmValidateCnf_001(const Result_TYPE &p_result);
MME_Payload md_CMN_CMN_CmValidateCnf_002(const ToggleNum_TYPE &p_toggle_num, const Result_TYPE &p_result);
MME_Payload md_CMN_CMN_CmValidateCnf_003(const SignalType_TYPE &p_signalType,const ToggleNum_TYPE &p_toggle_num,const Result_TYPE &p_result);
}

namespace Templates_CMN_CmSlacMatch
{
using namespace DataStructure_SLAC;
MME_Payload md_CMN_CMN_CmSlacMatchReq_001(const SLAC_Header &v_slac_header,const MACAddress_TYPE &v_pevmac,const MACAddress_TYPE &v_evsemac,const RunID_TYPE &v_runid);
MME_Payload md_CMN_CMN_CmSlacMatchReq_002(const SLAC_Header &v_slac_header,const Mvflength_TYPE &v_mvflength,const StationID_TYPE &v_pevid,const MACAddress_TYPE &v_pevmac,const StationID_TYPE &v_evseid,const MACAddress_TYPE &v_evsemac,const RunID_TYPE &v_runid);
MME_Payload md_CMN_CMN_CmSlacMatchCnf_001(const SLAC_Header &v_slac_header,const MACAddress_TYPE &v_pevmac,const MACAddress_TYPE &v_evsemac,const RunID_TYPE &v_runid,const NID_TYPE &v_nid,const NMK_TYPE &v_nmk);
MME_Payload md_CMN_CMN_CmSlacMatchCnf_001(const SLAC_Header &v_slac_header,const MACAddress_TYPE &v_pevmac,const MACAddress_TYPE &v_evsemac,const RunID_TYPE &v_runid,const NID_TYPE &v_nid,const NMK_TYPE &v_nmk);
}

namespace Templates_CMN_CmSetKey
{
using namespace DataStructure_SLAC;
MME_Payload md_CMN_CMN_CmSetKeyReq_001(const NID_TYPE &v_nid,const NewKey_TYPE &v_neykey);
MME_Payload mdw_CMN_CMN_CmSetKeyCnf_001(const Result_TYPE &p_result);
}

namespace Templates_CMN_CmAmpMap
{
using namespace DataStructure_SLAC;

MME_Payload m_CMN_CMN_CmAmpMapReq_001();
MME_Payload md_CMN_CMN_CmAmpMapReq_002(const Amlen_TYPE &p_amlen, const ListofAmdata_TYPE &p_listAmdata);
MME_Payload md_CMN_CMN_CmAmpMapReq_003(const Amlen_TYPE &p_amlen);
MME_Payload md_CMN_CMN_CmAmpMapCnf_001(const Result_TYPE &p_result);
}

namespace Templates_CMN_CmNwStats
{
using namespace DataStructure_SLAC;
MME_Payload md_CMN_CMN_CmNwStatsReq_001();
MME_Payload md_CMN_CMN_CmNwStatsCnf_001();
MME_Payload md_CMN_CMN_CmNwStatsCnf_002();
}

namespace Templates_EVCC_CmAttenProfileInd
{
using namespace DataStructure_SLAC;
MME_Payload md_EVCC_CMN_CmAttenProfileInd_001(const MACAddress_TYPE &v_pev_address,const NumGroups_TYPE &v_num_groups,const AttenProfile_TYPE &v_attenuation_list);
AttenProfile_TYPE mw_EVCC_CMN_AttenProfile_001();
}

namespace Templates_EVCC_CmAttenCharInd
{
using namespace DataStructure_SLAC;
MME_Payload md_EVCC_CMN_CmAttenCharInd_001(const SLAC_Header &v_slac_header,const MACAddress_TYPE &v_source_address,const RunID_TYPE &v_runid,const NumSounds_TYPE &v_num_sounds,const AttenProfile_TYPE &v_atten_list);
MME_Payload md_EVCC_CMN_CmAttenCharInd_002(const SLAC_Header &v_slac_header,const MACAddress_TYPE &v_source_address, const RunID_TYPE &v_runid,const NumSounds_TYPE &v_num_sounds, const StationID_TYPE &v_source_id,const StationID_TYPE &v_resp_id, const NumGroups_TYPE &v_num_groups, const AttenProfile_TYPE &v_atten_list);
AttenProfile_TYPE m_EVCC_CMN_atten_list_001();
AttenProfile_TYPE m_EVCC_CMN_atten_list_002();
}
}

#endif // __TEMPLATE_H__