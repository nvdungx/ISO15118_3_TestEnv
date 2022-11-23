#include "behaviorfunction/evcc_attenuationcharacterization.hpp"
#include "template/template.hpp"
#include "datatype.hpp"
#include "slac_type.hpp"

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
#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)
namespace TestLib
{
AttenProfile_TYPE averageCalc(const ResponseMessageList_TYPE &resMessagelist, integer vcount)
{
  AttenProfile_TYPE attenuation_list;
  integer avg = 0;
  for (integer i = 0; i < 58; i = i + 1)
  {
    for (integer j = 0; j < vcount; j = j + 1)
    {
      avg = avg + hex2int(resMessagelist[j].mme_payload.payload.cm_atten_profile_ind.attenuation_list.attenuation[i]);
    }
    avg = avg / vcount;
    attenuation_list.attenuation[i] = int2hex(avg, 2);
  }
  return attenuation_list;
}
VerdictValue f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(VerdictValue v_vct) {


  MME v_responseMessage;
  integer v_Num_soundsInt;
  ResponseMessageList_TYPE reponseMessageList;
  hexstring v_variable;
  integer v_count = 0;
  boolean v_isRunning = true;
  boolean v_repetition = true;
  AttenProfile_TYPE v_attenuation_list;
  integer v_count2 = 0;
  integer v_countDecrement = -1;
  integer v_countStart = -1;
  integer v_countStop = -1;
  boolean v_firstSound = true;
  EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
  EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
      md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
      md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac, m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))); // to vc_sut_mac;
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
      md_CMN_CMN_SlacMmeCmnHeader_001({CM_START_ATTEN_CHAR_IND = "606A"}),
      md_CMN_CMN_CmStartAttenCharInd_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY, MATCH_ANY, "01", MATCH_ANY, vc_RunID))))
    {
      if (v_count2 == 0)
      {
        EVCC_Tester::tc_TT_EVSE_match_MNBC->start(par_TT_EVSE_match_MNBC);
        EVCC_Tester::tc_TT_match_sequence->stop();
        vc_Num_sounds = v_responseMessage.mme_payload.payload.cm_start_atten_char_ind.num_sounds;
        v_Num_soundsInt = hex2int(vc_Num_sounds);
      }
      setverdict(pass, "CM_START_ATTEN_CHAR.IND is correct.");
      v_count2 = v_count2 + 1;
      if (v_count2 < cc_numberOfStartAtten)
      {
        // repeat;
      }
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
            md_CMN_CMN_CmSlacParmReq_001(
                m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    {
      EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
      EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
          md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac,
                                        m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))); // to vc_sut_mac;
      SLOGI("A further CM_SLAC_PARM.REQ message was received. A new CM_SLAC_PARM.CNF has to be send.");
      // repeat;
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(v_vct, "Invalid message type or content was received.");
      if (v_count2 < cc_numberOfStartAtten)
      {
        setverdict(v_vct, "A wrong number of CM_START_ATTEN_CHAR.IND message was received.");
      }
    }
    if (EVCC_Tester::tc_TT_match_sequence->timeout())
    {
      setverdict(v_vct, "TT_match_sequence timeout. No CM_START_ATTEN_CHAR.IND message was received. Matching process shall be considered as FAILED.");
      break;
    }
    if (EVCC_Tester::tc_TT_EVSE_match_MNBC->timeout())
    {
      setverdict(v_vct, "TT_EVSE_match_MNBC timeout. A wrong number of CM_START_ATTEN_CHAR.IND message was received. Matching process shall be considered as FAILED.");
    }
  }
  if (getverdict == pass)
  {
    while (v_isRunning)
    {
      while (true)
      {
        if (v_firstSound)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}),
                  md_CMN_CMN_CmMnbcSoundInd_001(m_CMN_CMN_SlacPayloadHeader_001(),
                      MATCH_ANY, vc_RunID, MATCH_ANY))))
          {
          // -> value v_responseMessage
            v_countStart = hex2int(v_responseMessage.mme_payload.payload.cm_mnbc_sound_ind.count);
            v_firstSound = false;
            if (v_countStart == cc_numberOfSoundings)
            {
              v_countDecrement = v_countStart - 1;
              v_countStop = 1;
            }
            else if (v_countStart == cc_numberOfSoundings - 1)
            {
              v_countDecrement = v_countStart - 1;
              v_countStop = 0;
            }
            else
            {
              setverdict(v_vct, "The field 'count' has an invalid value.");
              v_isRunning = false;
              break;
            }
            // repeat;
          }
        }
        if (not v_firstSound)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}),
                  md_CMN_CMN_CmMnbcSoundInd_001(
                      m_CMN_CMN_SlacPayloadHeader_001(),
                      int2hex(v_countDecrement, 2),
                      vc_RunID, MATCH_ANY))))
          {
            v_countDecrement = v_countDecrement - 1;
            // repeat;
          }
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_PROFILE_IND = "6086"}),
                md_EVCC_CMN_CmAttenProfileInd_001(
                    vc_sut_mac, MATCH_ANY, MATCH_SKIP))))
        //-> value v_responseMessage
        {
          if (ispresent(v_responseMessage.mme_payload.payload.cm_atten_profile_ind.attenuation_list))
          {
            if (v_responseMessage.mme_payload.payload.cm_atten_profile_ind.num_groups != "3A")
            {
              setverdict(v_vct, "Invalid numGroups value detected.");
              v_isRunning = false;
              break;
            }
            reponseMessageList[v_count] = v_responseMessage;
            v_count = v_count + 1;
          }
          else
          {
            SLOGI("Attenuation list was empty, the received message could not be considered for attenuation calculation.");
          }
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
                md_CMN_CMN_CmSlacParmReq_001(
                    m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
        {
          setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
          v_isRunning = false;
        }
        if (EVCC_Tester::pt_SLAC_Port->receive())
        {
          setverdict(v_vct, "Invalid message type or content was received.");
          v_isRunning = false;
        }
        if (EVCC_Tester::tc_TT_EVSE_match_MNBC->timeout())
        {
          v_isRunning = false;
        }
      }
      if (v_count == v_Num_soundsInt)
      {
        EVCC_Tester::tc_TT_EVSE_match_MNBC->stop();
        v_isRunning = false;
      }
    }
  }
  if (v_count > 0)
  {
    if (v_countDecrement != (v_countStop - 1))
    {
      setverdict(v_vct, "A wrong number of CM_MNBC_SOUND.IND messages was received.");
    }
    else
    {
      vc_Num_sounds = int2hex(v_count, 2);
      setverdict(pass, "CM_MNBC_SOUND.IND is correct.");
      setverdict(pass, "CM_ATTEN_PROFILE.IND is correct.");
      if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
      {
        v_attenuation_list = m_EVCC_CMN_atten_list_002();
      }
      else
      {
        v_attenuation_list = averageCalc(reponseMessageList, v_count);
      }
    }
  }
  else
  {
    setverdict(v_vct, "No Atten Profile messages received.");
  }
  if (getverdict == pass)
  {
    v_count = 0;
    while (v_repetition)
    {
      EVCC_Tester::tc_TT_match_response->start(par_TT_match_response);
      v_count = v_count + 1;
      EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_IND = "606E"}),
          md_EVCC_CMN_CmAttenCharInd_001(m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac, vc_RunID, vc_Num_sounds, v_attenuation_list))); // to vc_sut_mac;
      while (true)
      {
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}),
                md_CMN_CMN_CmAttenCharRsp_001(
                    m_CMN_CMN_SlacPayloadHeader_001(),
                    md_CMN_CMN_Acvarfield_001(vc_sut_mac, vc_RunID)))))
        {
          setverdict(pass, "CM_ATTEN_CHAR.RSP is correct.");
          v_repetition = false;
          EVCC_Tester::tc_TT_match_response->stop();
          EVCC_Tester::tc_TT_EVSE_match_session->start(par_TT_EVSE_match_session);
        }
        if (v_gracefulHandling)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(
                  md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}), MATCH_ANY)))
          {
            SLOGI("The CM_ATTEN_CHAR.RSP message content is not conform but graceful message handling is enabled.");
            v_repetition = false;
            EVCC_Tester::tc_TT_match_response->stop();
            EVCC_Tester::tc_TT_EVSE_match_session->start(par_TT_EVSE_match_session);
          }
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
                md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
        {
          setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
          v_repetition = false;
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}), MATCH_ANY)))
        {
          // CM_ATTEN_PROFILE.IND messages will be ignored!
          // repeat;
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_PROFILE_IND = "6086"}), MATCH_ANY)))
        {
          // CM_ATTEN_PROFILE.IND messages will be ignored!
          // repeat;
        }
        if (EVCC_Tester::pt_SLAC_Port->receive())
        {
          setverdict(v_vct, "Invalid message type or content was received.");
          v_repetition = false;
        }
        if (EVCC_Tester::tc_TT_match_response->timeout())
        {
          SLOGI("TT_match_response timeout.");
          if (v_count mod(par_C_EV_match_retry + 1) == 0)
          {
            setverdict(v_vct, "The repetition limit is reached. The Matching process is considered as FAILED.");
            v_repetition = false;
          }
          else
          {
            SLOGI("The repetition limit is not reached, a new CM_ATTEN_CHAR.IND message will be send.");
          }
        }
      }
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_AttenuationCharacterization_002() {
 // runs on SLAC_Tester

  MME v_responseMessage;
  integer v_Num_soundsInt;
  ResponseMessageList_TYPE reponseMessageList;
  hexstring v_variable;
  integer v_count = 0;
  boolean v_isRunning = true;
  boolean v_repetition = true;
  AttenProfile_TYPE v_attenuation_list;
  integer v_count2 = 0;
  integer v_countDecrement;
  integer v_countStart;
  integer v_countStop;
  boolean v_firstSound = true;
  EVCC_Tester::tc_TT_EVSE_SLAC_init->start(par_TT_EVSE_SLAC_init_min);
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
            md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    //-> value v_responseMessage sender vc_sut_mac
    {
      setverdict(pass, "CM_SLAC_PARM.REQ is correct.");
      vc_RunID = v_responseMessage.mme_payload.payload.cm_slac_parm_req.runid;
      // repeat;
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_START_ATTEN_CHAR_IND = "606A"}),
            md_CMN_CMN_CmStartAttenCharInd_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY, MATCH_ANY,
                                                "01", MATCH_ANY, vc_RunID))))
    {
    // -> value v_responseMessage
      if (v_count2 == 0)
      {
        EVCC_Tester::tc_TT_EVSE_match_MNBC->start(par_TT_EVSE_match_MNBC);
        EVCC_Tester::tc_TT_match_sequence->stop();
        vc_Num_sounds = v_responseMessage.mme_payload.payload.cm_start_atten_char_ind.num_sounds;
        v_Num_soundsInt = hex2int(vc_Num_sounds);
      }
      setverdict(pass, "CM_START_ATTEN_CHAR.IND is correct.");
      v_count2 = v_count2 + 1;
      if (v_count2 < cc_numberOfStartAtten)
      {
        // repeat;
      }
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
            md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    {
      EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
      EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
          md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac, m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))); // to vc_sut_mac;
      SLOGI("A further CM_SLAC_PARM.REQ message was received. A new CM_SLAC_PARM.CNF has to be send.");
      // repeat;
    }
    if (a_EVCC_processPLCLinkNotifications_002())
    {
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
      if (v_count2 < cc_numberOfStartAtten)
      {
        setverdict(fail, "A wrong number of CM_START_ATTEN_CHAR.IND message was received.");
      }
    }
    if (EVCC_Tester::tc_TT_match_sequence->timeout())
    {
      setverdict(fail, "TT_match_sequence timeout. No CM_START_ATTEN_CHAR.IND message was received. Matching process shall be considered as FAILED.");
      break;
    }
    if (EVCC_Tester::tc_TT_EVSE_match_MNBC->timeout())
    {
      setverdict(fail, "TT_EVSE_match_MNBC timeout. A wrong number of CM_START_ATTEN_CHAR.IND message was received. Matching process shall be considered as FAILED.");
    }
    if (EVCC_Tester::tc_TT_EVSE_SLAC_init->timeout())
    {
      setverdict(fail, "TT_EVSE_SLAC_init timeout. SECC assumes that no SLAC will be performed.");
    }
  }
  if (getverdict == pass)
  {
    while (v_isRunning)
    {
      while (true)
      {
        if (v_firstSound)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}),
                  md_CMN_CMN_CmMnbcSoundInd_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY, vc_RunID, MATCH_ANY))))
          {
          // -> value v_responseMessage
            v_countStart = hex2int(v_responseMessage.mme_payload.payload.cm_mnbc_sound_ind.count);
            v_firstSound = false;
            if (v_countStart == cc_numberOfSoundings)
            {
              v_countDecrement = v_countStart - 1;
              v_countStop = 1;
            }
            else if (v_countStart == cc_numberOfSoundings - 1)
            {
              v_countDecrement = v_countStart - 1;
              v_countStop = 0;
            }
            else
            {
              setverdict(fail, "The field 'count' has an invalid value.");
              v_isRunning = false;
              break;
            }
            // repeat;
          }
        }
        if (not v_firstSound)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}), md_CMN_CMN_CmMnbcSoundInd_001(m_CMN_CMN_SlacPayloadHeader_001(),
                                                                                                                int2hex(v_countDecrement, 2), vc_RunID, MATCH_ANY))))
          {
            v_countDecrement = v_countDecrement - 1;
            // repeat;
          }
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_PROFILE_IND = "6086"}),
                md_EVCC_CMN_CmAttenProfileInd_001(vc_sut_mac, MATCH_ANY, MATCH_SKIP))))
        {
        // -> value v_responseMessage
          if (ispresent(v_responseMessage.mme_payload.payload.cm_atten_profile_ind.attenuation_list))
          {
            if (v_responseMessage.mme_payload.payload.cm_atten_profile_ind.num_groups != "3A")
            {
              setverdict(fail, "Invalid numGroups value detected.");
              v_isRunning = false;
              break;
            }
            reponseMessageList[v_count] = v_responseMessage;
            v_count = v_count + 1;
          }
          else
          {
            SLOGI("Attenuation list was empty, the received message could not be considered for attenuation calculation.");
          }
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
                md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
        {
          setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
          v_isRunning = false;
        }
        if (EVCC_Tester::pt_SLAC_Port->receive())
        {
          setverdict(fail, "Invalid message type or content was received.");
          v_isRunning = false;
        }
        if (EVCC_Tester::tc_TT_EVSE_match_MNBC->timeout())
        {
          v_isRunning = false;
        }
      }
      if (v_count == v_Num_soundsInt)
      {
        EVCC_Tester::tc_TT_EVSE_match_MNBC->stop();
        v_isRunning = false;
      }
    }
  }
  if (v_count > 0)
  {
    if (v_countDecrement != (v_countStop - 1))
    {
      setverdict(fail, "A wrong number of CM_MNBC_SOUND.IND messages was received.");
    }
    else
    {
      vc_Num_sounds = int2hex(v_count, 2);
      setverdict(pass, "CM_MNBC_SOUND.IND is correct.");
      setverdict(pass, "CM_ATTEN_PROFILE.IND is correct.");
      v_attenuation_list = averageCalc(reponseMessageList, v_count);
    }
  }
  else
  {
    setverdict(fail, "No Atten Profile messages received.");
  }
  if (getverdict == pass)
  {
    v_count = 0;
    while (v_repetition)
    {
      EVCC_Tester::tc_TT_match_response->start(par_TT_match_response);
      v_count = v_count + 1;
      EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_IND = "606E"}),
          md_EVCC_CMN_CmAttenCharInd_001(m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac, vc_RunID, vc_Num_sounds, v_attenuation_list))); // to vc_sut_mac;
      while (true)
      {
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}),
                md_CMN_CMN_CmAttenCharRsp_001(m_CMN_CMN_SlacPayloadHeader_001(), md_CMN_CMN_Acvarfield_001(vc_sut_mac, vc_RunID)))))
        {
          setverdict(pass, "CM_ATTEN_CHAR.RSP is correct.");
          v_repetition = false;
          EVCC_Tester::tc_TT_EVSE_match_session->start(par_TT_EVSE_match_session);
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
                md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
        {
          setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
          setverdict(fail, "SUT did not send a CM_ATTEN_CHAR.RSP message to the second EVSE.");
          v_repetition = false;
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}), MATCH_ANY)))
        {
          // CM_ATTEN_PROFILE.IND messages will be ignored!
          // repeat;
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_PROFILE_IND = "6086"}), MATCH_ANY)))
        {
          // CM_ATTEN_PROFILE.IND messages will be ignored!
          // repeat;
        }
        if (EVCC_Tester::pt_SLAC_Port->receive())
        {
          setverdict(fail, "Invalid message type or content was received.");
          v_repetition = false;
        }
        if (EVCC_Tester::tc_TT_match_response->timeout())
        {
          SLOGI("TT_match_response timeout.");
          if (v_count mod(par_C_EV_match_retry + 1) == 0)
          {
            setverdict(fail, "The repetition limit is reached. The Matching process is considered as FAILED.");
            v_repetition = false;
          }
          else
          {
            SLOGI("The repetition limit is not reached, a new CM_ATTEN_CHAR.IND message will be send.");
          }
        }
      }
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_AttenuationCharacterization_003() {
 // runs on SLAC_Tester

  MME v_responseMessage;
  integer v_Num_soundsInt;
  ResponseMessageList_TYPE reponseMessageList;
  hexstring v_variable;
  integer v_count = 0;
  boolean v_isRunning = true;
  boolean v_repetition = true;
  AttenProfile_TYPE v_attenuation_list;
  timer t_TT_EVSE_SLAC_init;
  integer v_count2 = 0;
  integer v_countDecrement;
  integer v_countStart;
  integer v_countStop;
  boolean v_firstSound = true;
  t_TT_EVSE_SLAC_init.start(par_TT_EVSE_SLAC_init_min);
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    //-> value v_responseMessage sender vc_sut_mac
    {
      setverdict(pass, "CM_SLAC_PARM.REQ is correct.");
      vc_RunID = v_responseMessage.mme_payload.payload.cm_slac_parm_req.runid;
      EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
      EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
          md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac, m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))); // to vc_sut_mac;
    }
    if (a_EVCC_processPLCLinkNotifications_002())
    {
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
    if (t_TT_EVSE_SLAC_init.timeout())
    {
      setverdict(fail, "TT_EVSE_SLAC_init timeout. SECC assumes that no SLAC will be performed.");
    }
  }
  if (getverdict == pass)
  {
    while (true)
    {
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_START_ATTEN_CHAR_IND = "606A"}),
              md_CMN_CMN_CmStartAttenCharInd_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY, MATCH_ANY, "01", MATCH_ANY, vc_RunID))))
      {
      // -> value v_responseMessage
        if (v_count2 == 0)
        {
          EVCC_Tester::tc_TT_EVSE_match_MNBC->start(par_TT_EVSE_match_MNBC);
          EVCC_Tester::tc_TT_match_sequence->stop();
          vc_Num_sounds = v_responseMessage.mme_payload.payload.cm_start_atten_char_ind.num_sounds;
          v_Num_soundsInt = hex2int(vc_Num_sounds);
        }
        setverdict(pass, "CM_START_ATTEN_CHAR.IND is correct.");
        v_count2 = v_count2 + 1;
        if (v_count2 < cc_numberOfStartAtten)
        {
          // repeat;
        }
      }
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
              md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
      {
        EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
        EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
            md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac, m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))); // to vc_sut_mac;
        SLOGI("A further CM_SLAC_PARM.REQ message was received. A new CM_SLAC_PARM.CNF has to be send.");
        // repeat;
      }
      if (EVCC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
        if (v_count2 < cc_numberOfStartAtten)
        {
          setverdict(fail, "A wrong number of CM_START_ATTEN_CHAR.IND message was received.");
        }
      }
      if (EVCC_Tester::tc_TT_match_sequence->timeout())
      {
        setverdict(fail, "TT_match_sequence timeout. No CM_START_ATTEN_CHAR.IND message was received. Matching process shall be considered as FAILED.");
        break;
      }
      if (EVCC_Tester::tc_TT_EVSE_match_MNBC->timeout())
      {
        setverdict(fail, "TT_EVSE_match_MNBC timeout. A wrong number of CM_START_ATTEN_CHAR.IND message was received. Matching process shall be considered as FAILED.");
      }
    }
    if (getverdict == pass)
    {
      while (v_isRunning)
      {
        while (true)
        {
          if (v_firstSound)
          {
            if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                    md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}),
                    md_CMN_CMN_CmMnbcSoundInd_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY, vc_RunID, MATCH_ANY))))
            {
            // -> value v_responseMessage
              v_countStart = hex2int(v_responseMessage.mme_payload.payload.cm_mnbc_sound_ind.count);
              v_firstSound = false;
              if (v_countStart == cc_numberOfSoundings)
              {
                v_countDecrement = v_countStart - 1;
                v_countStop = 1;
              }
              else if (v_countStart == cc_numberOfSoundings - 1)
              {
                v_countDecrement = v_countStart - 1;
                v_countStop = 0;
              }
              else
              {
                setverdict(fail, "The field 'count' has an invalid value.");
                v_isRunning = false;
                break;
              }
              // repeat;
            }
          }
          if (not v_firstSound)
          {
            if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                    md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}),
                    md_CMN_CMN_CmMnbcSoundInd_001(m_CMN_CMN_SlacPayloadHeader_001(), int2hex(v_countDecrement, 2), vc_RunID, MATCH_ANY))))
            {
              v_countDecrement = v_countDecrement - 1;
              // repeat;
            }
          }
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_PROFILE_IND = "6086"}),
                  md_EVCC_CMN_CmAttenProfileInd_001(vc_sut_mac, MATCH_ANY, MATCH_SKIP))))
          {
          // -> value v_responseMessage
            if (ispresent(v_responseMessage.mme_payload.payload.cm_atten_profile_ind.attenuation_list))
            {
              if (v_responseMessage.mme_payload.payload.cm_atten_profile_ind.num_groups != "3A")
              {
                setverdict(fail, "Invalid numGroups value detected.");
                v_isRunning = false;
                break;
              }
              reponseMessageList[v_count] = v_responseMessage;
              v_count = v_count + 1;
            }
            else
            {
              SLOGI("Attenuation list was empty, the received message could not be considered for attenuation calculation.");
            }
          }
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
                  md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
          {
            setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
            v_isRunning = false;
          }
          if (EVCC_Tester::pt_SLAC_Port->receive())
          {
            setverdict(fail, "Invalid message type or content was received.");
            v_isRunning = false;
          }
          if (EVCC_Tester::tc_TT_EVSE_match_MNBC->timeout())
          {
            v_isRunning = false;
          }
        }
        if (v_count == v_Num_soundsInt)
        {
          EVCC_Tester::tc_TT_EVSE_match_MNBC->stop();
          v_isRunning = false;
        }
      }
    }
    if (v_count > 0)
    {
      if (v_countDecrement != (v_countStop - 1))
      {
        setverdict(fail, "A wrong number of CM_MNBC_SOUND.IND messages was received.");
      }
      else
      {
        vc_Num_sounds = int2hex(v_count, 2);
        setverdict(pass, "CM_MNBC_SOUND.IND is correct.");
        setverdict(pass, "CM_ATTEN_PROFILE.IND is correct.");
        v_attenuation_list = averageCalc(reponseMessageList, v_count);
      }
    }
    else
    {
      setverdict(fail, "No Atten Profile messages received.");
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_AttenuationCharacterization_004() {
 // runs on EVCC_Tester

  MME v_responseMessage;
  integer v_Num_soundsInt;
  ResponseMessageList_TYPE reponseMessageList;
  hexstring v_variable;
  integer v_count = 0;
  boolean v_isRunning = true;
  AttenProfile_TYPE v_attenuation_list;
  integer v_count2 = 0;
  integer v_countDecrement;
  integer v_countStart;
  integer v_countStop;
  boolean v_firstSound = true;
  EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
  EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
      md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
      md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac, m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))); // to vc_sut_mac;
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_START_ATTEN_CHAR_IND = "606A"}),
            md_CMN_CMN_CmStartAttenCharInd_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY, MATCH_ANY, "01", MATCH_ANY, vc_RunID))))
    {
    // -> value v_responseMessage
      if (v_count2 == 0)
      {
        EVCC_Tester::tc_TT_EVSE_match_MNBC->start(par_TT_EVSE_match_MNBC);
        EVCC_Tester::tc_TT_match_sequence->stop();
        EVCC_Tester::tc_TP_EVSE_atten_results->start(par_TT_EV_atten_results);
        vc_Num_sounds = v_responseMessage.mme_payload.payload.cm_start_atten_char_ind.num_sounds;
        v_Num_soundsInt = hex2int(vc_Num_sounds);
      }
      setverdict(pass, "CM_START_ATTEN_CHAR.IND is correct.");
      v_count2 = v_count2 + 1;
      if (v_count2 < cc_numberOfStartAtten)
      {
        // repeat;
      }
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
            md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    {
      EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
      EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
          md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac, m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))); // to vc_sut_mac;
      SLOGI("A further CM_SLAC_PARM.REQ message was received. A new CM_SLAC_PARM.CNF has to be send.");
      // repeat;
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
      if (v_count2 < cc_numberOfStartAtten)
      {
        setverdict(fail, "A wrong number of CM_START_ATTEN_CHAR.IND message was received.");
      }
    }
    if (EVCC_Tester::tc_TT_match_sequence->timeout())
    {
      setverdict(fail, "TT_match_sequence timeout. No CM_START_ATTEN_CHAR.IND message was received. Matching process shall be considered as FAILED.");
      break;
    }
    if (EVCC_Tester::tc_TT_EVSE_match_MNBC->timeout())
    {
      setverdict(fail, "TT_EVSE_match_MNBC timeout. A wrong number of CM_START_ATTEN_CHAR.IND message was received. Matching process shall be considered as FAILED.");
    }
  }
  if (getverdict == pass)
  {
    while (v_isRunning)
    {
      while (true)
      {
        if (v_firstSound)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}),
                  md_CMN_CMN_CmMnbcSoundInd_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY, vc_RunID, MATCH_ANY))))
          {
          // -> value v_responseMessage
            v_countStart = hex2int(v_responseMessage.mme_payload.payload.cm_mnbc_sound_ind.count);
            v_firstSound = false;
            if (v_countStart == cc_numberOfSoundings)
            {
              v_countDecrement = v_countStart - 1;
              v_countStop = 1;
            }
            else if (v_countStart == cc_numberOfSoundings - 1)
            {
              v_countDecrement = v_countStart - 1;
              v_countStop = 0;
            }
            else
            {
              setverdict(fail, "The field 'count' has an invalid value.");
              v_isRunning = false;
              break;
            }
            // repeat;
          }
        }
        if (not v_firstSound)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}),
                  md_CMN_CMN_CmMnbcSoundInd_001(m_CMN_CMN_SlacPayloadHeader_001(), int2hex(v_countDecrement, 2), vc_RunID, MATCH_ANY))))
          {
            v_countDecrement = v_countDecrement - 1;
            // repeat;
          }
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_PROFILE_IND = "6086"}),
                md_EVCC_CMN_CmAttenProfileInd_001(vc_sut_mac, MATCH_ANY, MATCH_SKIP))))
        {
        // -> value v_responseMessage
          if (ispresent(v_responseMessage.mme_payload.payload.cm_atten_profile_ind.attenuation_list))
          {
            if (v_responseMessage.mme_payload.payload.cm_atten_profile_ind.num_groups != "3A")
            {
              setverdict(fail, "Invalid numGroups value detected.");
              v_isRunning = false;
              break;
            }
            reponseMessageList[v_count] = v_responseMessage;
            v_count = v_count + 1;
          }
          else
          {
            SLOGI("Attenuation list was empty, the received message could not be considered for attenuation calculation.");
          }
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
                md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
        {
          setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
          v_isRunning = false;
        }
        if (EVCC_Tester::pt_SLAC_Port->receive())
        {
          setverdict(fail, "Invalid message type or content was received.");
          v_isRunning = false;
        }
        if (EVCC_Tester::tc_TT_EVSE_match_MNBC->timeout())
        {
          v_isRunning = false;
        }
      }
      if (v_count == v_Num_soundsInt)
      {
        EVCC_Tester::tc_TT_EVSE_match_MNBC->stop();
        v_isRunning = false;
      }
    }
  }
  if (v_count > 0)
  {
    if (v_countDecrement != (v_countStop - 1))
    {
      setverdict(fail, "A wrong number of CM_MNBC_SOUND.IND messages was received.");
    }
    else
    {
      vc_Num_sounds = int2hex(v_count, 2);
      setverdict(pass, "CM_MNBC_SOUND.IND is correct.");
      setverdict(pass, "CM_ATTEN_PROFILE.IND is correct.");
      v_attenuation_list = averageCalc(reponseMessageList, v_count);
    }
  }
  else
  {
    setverdict(fail, "No Atten Profile messages received.");
  }
  if (getverdict == pass)
  {
    // wait until tc_TP_EVSE_atten_results timer expires
    while (true)
    {
      if (EVCC_Tester::tc_TP_EVSE_atten_results->timeout())
      {
      }
      if (EVCC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
      }
    }
    EVCC_Tester::tc_TT_match_response->start(par_TT_match_response);
    EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
        md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_IND = "606E"}),
        md_EVCC_CMN_CmAttenCharInd_001(m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac, vc_RunID, vc_Num_sounds, v_attenuation_list))); // to vc_sut_mac;
    while (true)
    {
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}),
              md_CMN_CMN_CmAttenCharRsp_001(m_CMN_CMN_SlacPayloadHeader_001(), md_CMN_CMN_Acvarfield_001(vc_sut_mac, vc_RunID)))))
      {
        setverdict(fail, "CM_ATTEN_CHAR.RSP message was not expected.");
      }
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
              md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
      {
        setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
      }
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}), MATCH_ANY)))
      {
        // CM_ATTEN_PROFILE.IND messages will be ignored!
        // repeat;
      }
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_PROFILE_IND = "6086"}), MATCH_ANY)))
      {
        // CM_ATTEN_PROFILE.IND messages will be ignored!
        // repeat;
      }
      if (EVCC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
      }
      if (EVCC_Tester::tc_TT_match_response->timeout())
      {
        setverdict(pass, "TT_match_response timeout. No CM_ATTEN_CHAR.RSP message was received from the SUT.");
      }
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_AttenuationCharacterization_005(MME_Payload v_payload) {
 // runs on EVCC_Tester

  MME v_responseMessage;
  integer v_Num_soundsInt;
  ResponseMessageList_TYPE reponseMessageList;
  hexstring v_variable;
  integer v_count = 0;
  boolean v_isRunning = true;
  AttenProfile_TYPE v_attenuation_list;
  integer v_count2 = 0;
  integer v_countDecrement;
  integer v_countStart;
  integer v_countStop;
  boolean v_firstSound = true;
  EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
  EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
      md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
      md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac, m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))); // to vc_sut_mac;
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_START_ATTEN_CHAR_IND = "606A"}),
            md_CMN_CMN_CmStartAttenCharInd_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY, MATCH_ANY, "01", MATCH_ANY, vc_RunID))))
    {
    // -> value v_responseMessage
      if (v_count2 == 0)
      {
        EVCC_Tester::tc_TT_EVSE_match_MNBC->start(par_TT_EVSE_match_MNBC);
        EVCC_Tester::tc_TT_match_sequence->stop();
        EVCC_Tester::tc_TP_EVSE_atten_results->start(par_TT_EV_atten_results);
        vc_Num_sounds = v_responseMessage.mme_payload.payload.cm_start_atten_char_ind.num_sounds;
        if (not(ispresent(v_payload.payload.cm_atten_char_ind.num_sounds)))
        {
          v_payload.payload.cm_atten_char_ind.num_sounds = vc_Num_sounds;
        }
        v_Num_soundsInt = hex2int(vc_Num_sounds);
      }
      setverdict(pass, "CM_START_ATTEN_CHAR.IND is correct.");
      v_count2 = v_count2 + 1;
      if (v_count2 < cc_numberOfStartAtten)
      {
        // repeat;
      }
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
            md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    {
      EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
      EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
          md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac, m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))); // to vc_sut_mac;
      SLOGI("A further CM_SLAC_PARM.REQ message was received. A new CM_SLAC_PARM.CNF has to be send.");
      // repeat;
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
      if (v_count2 < cc_numberOfStartAtten)
      {
        setverdict(fail, "A wrong number of CM_START_ATTEN_CHAR.IND message was received.");
      }
    }
    if (EVCC_Tester::tc_TT_match_sequence->timeout())
    {
      setverdict(fail, "TT_match_sequence timeout. No CM_START_ATTEN_CHAR.IND message was received. Matching process shall be considered as FAILED.");
      break;
    }
    if (EVCC_Tester::tc_TT_EVSE_match_MNBC->timeout())
    {
      setverdict(fail, "TT_EVSE_match_MNBC timeout. A wrong number of CM_START_ATTEN_CHAR.IND message was received. Matching process shall be considered as FAILED.");
    }
  }
  if (getverdict == pass)
  {
    while (v_isRunning)
    {
      while (true)
      {
        if (v_firstSound)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}),
                  md_CMN_CMN_CmMnbcSoundInd_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY, vc_RunID, MATCH_ANY))))
          {
          // -> value v_responseMessage
            v_countStart = hex2int(v_responseMessage.mme_payload.payload.cm_mnbc_sound_ind.count);
            v_firstSound = false;
            if (v_countStart == cc_numberOfSoundings)
            {
              v_countDecrement = v_countStart - 1;
              v_countStop = 1;
            }
            else if (v_countStart == cc_numberOfSoundings - 1)
            {
              v_countDecrement = v_countStart - 1;
              v_countStop = 0;
            }
            else
            {
              setverdict(fail, "The field 'count' has an invalid value.");
              v_isRunning = false;
              break;
            }
            // repeat;
          }
        }
        if (not v_firstSound)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}),
                  md_CMN_CMN_CmMnbcSoundInd_001(m_CMN_CMN_SlacPayloadHeader_001(), int2hex(v_countDecrement, 2), vc_RunID, MATCH_ANY))))
          {
            v_countDecrement = v_countDecrement - 1;
            // repeat;
          }
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_PROFILE_IND = "6086"}),
                md_EVCC_CMN_CmAttenProfileInd_001(vc_sut_mac, MATCH_ANY, MATCH_SKIP))))
        {
        // -> value v_responseMessage
          if (ispresent(v_responseMessage.mme_payload.payload.cm_atten_profile_ind.attenuation_list))
          {
            if (v_responseMessage.mme_payload.payload.cm_atten_profile_ind.num_groups != "3A")
            {
              setverdict(fail, "Invalid numGroups value detected.");
              v_isRunning = false;
              break;
            }
            reponseMessageList[v_count] = v_responseMessage;
            v_count = v_count + 1;
          }
          else
          {
            SLOGI("Attenuation list was empty, the received message could not be considered for attenuation calculation.");
          }
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
                md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
        {
          setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
          v_isRunning = false;
        }
        if (EVCC_Tester::pt_SLAC_Port->receive())
        {
          setverdict(fail, "Invalid message type or content was received.");
          v_isRunning = false;
        }
        if (EVCC_Tester::tc_TT_EVSE_match_MNBC->timeout())
        {
          v_isRunning = false;
        }
      }
      if (v_count == v_Num_soundsInt)
      {
        EVCC_Tester::tc_TT_EVSE_match_MNBC->stop();
        v_isRunning = false;
      }
    }
  }
  if (v_count > 0)
  {
    if (v_countDecrement != (v_countStop - 1))
    {
      setverdict(fail, "A wrong number of CM_MNBC_SOUND.IND messages was received.");
    }
    else
    {
      vc_Num_sounds = int2hex(v_count, 2);
      setverdict(pass, "CM_MNBC_SOUND.IND is correct.");
      setverdict(pass, "CM_ATTEN_PROFILE.IND is correct.");
      v_attenuation_list = averageCalc(reponseMessageList, v_count);
    }
  }
  else
  {
    setverdict(fail, "No Atten Profile messages received.");
  }
  if (getverdict == pass)
  {
    // send invalid CM_ATTEN_CHAR.IND message
    EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_IND = "606E"}), v_payload)); // to vc_sut_mac;
    while (true)
    {
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}), MATCH_ANY)))
      {
        setverdict(fail, "Invalid CM_ATTEN_CHAR.IND messages shall be ignored.");
      }
      if (EVCC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
      }
      if (EVCC_Tester::tc_TP_EVSE_atten_results->timeout())
      {
        EVCC_Tester::tc_TT_match_response->start(par_TT_match_response);
        EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_IND = "606E"}),
            md_EVCC_CMN_CmAttenCharInd_001(m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac,
                                            vc_RunID, vc_Num_sounds, v_attenuation_list))); // to vc_sut_mac;
        while (true)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}),
                  md_CMN_CMN_CmAttenCharRsp_001(m_CMN_CMN_SlacPayloadHeader_001(),
                                                md_CMN_CMN_Acvarfield_001(vc_sut_mac, vc_RunID)))))
          {
            setverdict(fail, "CM_ATTEN_CHAR.RSP message was not expected.");
          }
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
                  md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
          {
            setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
          }
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}), MATCH_ANY)))
          {
            // CM_ATTEN_PROFILE.IND messages will be ignored!
            // repeat;
          }
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_PROFILE_IND = "6086"}), MATCH_ANY)))
          {
            // CM_ATTEN_PROFILE.IND messages will be ignored!
            // repeat;
          }
          if (EVCC_Tester::pt_SLAC_Port->receive())
          {
            setverdict(fail, "Invalid message type or content was received.");
          }
          if (EVCC_Tester::tc_TT_match_response->timeout())
          {
            setverdict(pass, "TT_match_response timeout. No CM_ATTEN_CHAR.RSP message was received from the SUT.");
          }
        }
      }
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_AttenuationCharacterization_006(HAL_61851_PwmMode_Type pwmMode) {
 // runs on EVCC_Tester

  // set error state
  f_EVCC_changeValidStateCondition(E, E);
  f_EVCC_setPwmMode(pwmMode);
  EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
  EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
                                                          md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac, m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))); // to vc_sut_mac;
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_START_ATTEN_CHAR_IND = "606A"}), MATCH_ANY)))
    {
      setverdict(fail, "CM_START_ATTEN_CHAR.IND message was not expected. CP State E/F should be detected before.");
      EVCC_Tester::tc_TT_match_sequence->stop();
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
            md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    {
      EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
      EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}), md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac, m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))); // to vc_sut_mac;
      SLOGI("A further CM_SLAC_PARM.REQ message was received. A new CM_SLAC_PARM.CNF has to be send.");
      // repeat;
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
    if (EVCC_Tester::tc_TT_match_sequence->timeout())
    {
      setverdict(pass, "TT_match_sequence timer has expired, the Matching process was terminated by the SUT.");
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_AC_TB_VTB_AttenuationCharacterization_001(integer v_dutcCycle) {
 // runs on EVCC_Tester

  MME v_responseMessage;
  integer v_Num_soundsInt;
  ResponseMessageList_TYPE reponseMessageList;
  hexstring v_variable;
  integer v_count = 0;
  boolean v_isRunning = true;
  boolean v_repetition = true;
  AttenProfile_TYPE v_attenuation_list;
  integer v_count2 = 0;
  integer v_countDecrement;
  integer v_countStart;
  integer v_countStop;
  boolean v_firstSound = true;
  f_EVCC_setDutyCycle(v_dutcCycle);
  EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
  EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
      md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
      md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac, m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))); // to vc_sut_mac;
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_START_ATTEN_CHAR_IND = "606A"}),
            md_CMN_CMN_CmStartAttenCharInd_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY, MATCH_ANY, "01", MATCH_ANY, vc_RunID))))
    //-> value v_responseMessage
    {
      if (v_count2 == 0)
      {
        EVCC_Tester::tc_TT_EVSE_match_MNBC->start(par_TT_EVSE_match_MNBC);
        EVCC_Tester::tc_TT_match_sequence->stop();
        vc_Num_sounds = v_responseMessage.mme_payload.payload.cm_start_atten_char_ind.num_sounds;
        v_Num_soundsInt = hex2int(vc_Num_sounds);
      }
      setverdict(pass, "CM_START_ATTEN_CHAR.IND is correct.");
      v_count2 = v_count2 + 1;
      if (v_count2 < cc_numberOfStartAtten)
      {
        // repeat;
      }
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
            md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    {
      EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
      EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
                                                              md_CMN_CMN_CmSlacParmCnf_001(vc_sut_mac, m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))); // to vc_sut_mac;
      SLOGI("A further CM_SLAC_PARM.REQ message was received. A new CM_SLAC_PARM.CNF has to be send.");
      // repeat;
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
      if (v_count2 < cc_numberOfStartAtten)
      {
        setverdict(fail, "A wrong number of CM_START_ATTEN_CHAR.IND message was received.");
      }
    }
    if (EVCC_Tester::tc_TT_match_sequence->timeout())
    {
      setverdict(fail, "TT_match_sequence timeout. No CM_START_ATTEN_CHAR.IND message was received. Matching process shall be considered as FAILED.");
      break;
    }
    if (EVCC_Tester::tc_TT_EVSE_match_MNBC->timeout())
    {
      setverdict(fail, "TT_EVSE_match_MNBC timeout. A wrong number of CM_START_ATTEN_CHAR.IND message was received. Matching process shall be considered as FAILED.");
    }
  }
  if (getverdict == pass)
  {
    while (v_isRunning)
    {
      while (true)
      {
        if (v_firstSound)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}),
                  md_CMN_CMN_CmMnbcSoundInd_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY, vc_RunID, MATCH_ANY))))
          {
          // -> value v_responseMessage
            v_countStart = hex2int(v_responseMessage.mme_payload.payload.cm_mnbc_sound_ind.count);
            v_firstSound = false;
            if (v_countStart == cc_numberOfSoundings)
            {
              v_countDecrement = v_countStart - 1;
              v_countStop = 1;
            }
            else if (v_countStart == cc_numberOfSoundings - 1)
            {
              v_countDecrement = v_countStart - 1;
              v_countStop = 0;
            }
            else
            {
              setverdict(fail, "The field 'count' has an invalid value.");
              v_isRunning = false;
              break;
            }
            // repeat;
          }
        }
        if (not v_firstSound)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}),
                  md_CMN_CMN_CmMnbcSoundInd_001(m_CMN_CMN_SlacPayloadHeader_001(), int2hex(v_countDecrement, 2), vc_RunID, MATCH_ANY))))
          {
            v_countDecrement = v_countDecrement - 1;
            // repeat;
          }
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_PROFILE_IND = "6086"}),
                md_EVCC_CMN_CmAttenProfileInd_001(vc_sut_mac, MATCH_ANY, MATCH_SKIP))))
        {
        // -> value v_responseMessage
          if (ispresent(v_responseMessage.mme_payload.payload.cm_atten_profile_ind.attenuation_list))
          {
            if (v_responseMessage.mme_payload.payload.cm_atten_profile_ind.num_groups != "3A")
            {
              setverdict(fail, "Invalid numGroups value detected.");
              v_isRunning = false;
              break;
            }
            reponseMessageList[v_count] = v_responseMessage;
            v_count = v_count + 1;
          }
          else
          {
            SLOGI("Attenuation list was empty, the received message could not be considered for attenuation calculation.");
          }
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
                md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
        {
          setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
          v_isRunning = false;
        }
        if (EVCC_Tester::pt_SLAC_Port->receive())
        {
          setverdict(fail, "Invalid message type or content was received.");
          v_isRunning = false;
        }
        if (EVCC_Tester::tc_TT_EVSE_match_MNBC->timeout())
        {
          v_isRunning = false;
        }
      }
      if (v_count == v_Num_soundsInt)
      {
        EVCC_Tester::tc_TT_EVSE_match_MNBC->stop();
        v_isRunning = false;
      }
    }
  }
  if (v_count > 0)
  {
    if (v_countDecrement != (v_countStop - 1))
    {
      setverdict(fail, "A wrong number of CM_MNBC_SOUND.IND messages was received.");
    }
    else
    {
      vc_Num_sounds = int2hex(v_count, 2);
      setverdict(pass, "CM_MNBC_SOUND.IND is correct.");
      setverdict(pass, "CM_ATTEN_PROFILE.IND is correct.");
      v_attenuation_list = averageCalc(reponseMessageList, v_count);
    }
  }
  else
  {
    setverdict(fail, "No Atten Profile messages received.");
  }
  if (getverdict == pass)
  {
    v_count = 0;
    while (v_repetition)
    {
      EVCC_Tester::tc_TT_match_response->start(par_TT_match_response);
      v_count = v_count + 1;
      EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_IND = "606E"}),
          md_EVCC_CMN_CmAttenCharInd_001(m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac,
                                          vc_RunID, vc_Num_sounds, v_attenuation_list))); // to vc_sut_mac;
      while (true)
      {
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}),
                md_CMN_CMN_CmAttenCharRsp_001(m_CMN_CMN_SlacPayloadHeader_001(), md_CMN_CMN_Acvarfield_001(vc_sut_mac, vc_RunID)))))
        {
          setverdict(pass, "CM_ATTEN_CHAR.RSP is correct. The change of the duty cycle should not influence the EVCC Matching process.");
          v_repetition = false;
          EVCC_Tester::tc_TT_EVSE_match_session->start(par_TT_EVSE_match_session);
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
                md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
        {
          setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
          v_repetition = false;
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}), MATCH_ANY)))
        {
          // CM_ATTEN_PROFILE.IND messages will be ignored!
          // repeat;
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_PROFILE_IND = "6086"}), MATCH_ANY)))
        {
          // CM_ATTEN_PROFILE.IND messages will be ignored!
          // repeat;
        }
        if (EVCC_Tester::pt_SLAC_Port->receive())
        {
          setverdict(fail, "Invalid message type or content was received.");
          v_repetition = false;
        }
        if (EVCC_Tester::tc_TT_match_response->timeout())
        {
          SLOGI("TT_match_response timeout.");
          if (v_count mod(par_C_EV_match_retry + 1) == 0)
          {
            setverdict(fail, "The repetition limit is reached. The Matching process is considered as FAILED.");
            v_repetition = false;
          }
          else
          {
            SLOGI("The repetition limit is not reached, a new CM_ATTEN_CHAR.IND message will be send.");
          }
        }
      }
    }
  }
  return EVCC_Tester::getverdict();
}
}