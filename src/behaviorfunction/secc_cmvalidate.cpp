#include "behaviorfunction/secc_cmvalidate.hpp"
#include "template/template.hpp"

// import from Timer_15118_3 all;
// import from Pics_15118_3 all;
// import from Templates_CMN_CmValidate all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from Templates_CMN_CmSlacParm all;
// import from Templates_SECC_CmAttenCharInd all;
// import from Templates_CMN_CmStartAttenCharInd all;
// import from Templates_CMN_CmMnbcSoundInd all;
// import from ComponentsAndPorts all;
// import from DataStructure_SLAC all;
// import from TestBehavior_SECC_AttenuationCharacterization all;
// import from LibFunctions_15118_3 all;
// import from Services_HAL_61851 all;
// import from Templates_CMN_CmAttenCharRsp all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from Services_PLCLinkStatus all;
// import from Pics_15118 all;
// import from Timer_15118 all;
#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)
namespace TestLib
{
namespace TestBehavior_SECC_CmValidate
{
boolean f_checkResultFieldStep1(hexstring v_result, boolean v_repetition, VerdictValue v_vct)
{
  // runs on SECC_Tester
  //  return boolean {
  if (v_result == par_cmValidate_result_notReady)
  {
    sleep(0.5);
  }
  else if (v_result == par_cmValidate_result_ready)
  {
    setverdict(pass, "CM_VALIDATE.CNF is correct. The EV will send the step 2 CM_VALIDATE.REQ with a Timer value which covers the whole BCB toggle sequence.");
    v_repetition = false;
  }
  else if ((v_result == par_cmValidate_result_success) or
           (v_result == par_cmValidate_result_failure))
  {
    setverdict(v_vct, "Invalid result code, the EV will stop the Validation process with the current EVSE.");
    v_repetition = false;
  }
  else if (v_result == par_cmValidate_result_notRequired)
  {
    setverdict(inconc, "The validation process is not required.");
    v_repetition = false;
  }
  else
  {
    setverdict(v_vct, "Unkwnown result format.");
    v_repetition = false;
  }
  return v_repetition;
}
void f_checkResultFieldStep2(hexstring v_result, VerdictValue v_vct)
{
  // runs on SECC_Tester
  if (v_result == par_cmValidate_result_success)
  {
    setverdict(pass, "CM_VALIDATE.CNF is correct. The EV will compare the ToggleNum field of the CM_VALIDATE.CNF message with the number of BCB toggles executed.");
  }
  else if ((v_result == par_cmValidate_result_notReady) or
           (v_result == par_cmValidate_result_ready) or
           (v_result == par_cmValidate_result_failure) or
           (v_result == par_cmValidate_result_notRequired))
  {
    setverdict(v_vct, "Invalid result code, the EV will stop the Validation process with the current EVSE.");
  }
  else
  {
    setverdict(v_vct, "Unkwnown result format.");
  }
}
boolean f_checkValidToggleConfig(void)
{
  if ((int2float(C_vald_nb_toggles) * par_TP_EV_vald_state_duration * 3.0) < par_TP_EV_vald_toggle)
  {
    return true;
  }
  return false;
}
// SECC Tester
VerdictValue f_SECC_CMN_TB_VTB_CmValidate_001(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener, VerdictValue v_vct)
{
  // runs on SECC_Tester return VerdictValue {
  boolean v_repetition = true;
  integer v_count1 = 0;
  MME v_responseMessage;
  if (f_checkValidToggleConfig())
  {
    while (v_repetition)
    {
      SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
      v_count1 = v_count1 + 1;
      SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
          m_CMN_CMN_CmValidateReq_001())); // to vc_sut_mac;
      while (true)
      {
        if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
                md_CMN_CMN_CmValidateCnf_001(MATCH_ANY))))
        {
          //-> value v_responseMessage
          SECC_Tester::tc_TT_match_response->stop();
          hexstring v_result = v_responseMessage.mme_payload.payload.cm_validate_cnf.vcVarField.result;
          v_repetition = f_checkResultFieldStep1(v_result, v_repetition, v_vct);
        }
        if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_IND = "606E"}), MATCH_ANY)))
        {
          SECC_Tester::tc_TT_match_response->stop();
          SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
          SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}),
              md_CMN_CMN_CmAttenCharRsp_001(
                  m_CMN_CMN_SlacPayloadHeader_001(),
                  md_CMN_CMN_Acvarfield_001(
                      par_testSystem_mac, vc_RunID)))); // to vc_sut_mac;
          SLOGI("A further CM_ATTEN_CHAR.IND message was received. A new CM_ATTEN_CHAR.RSP has to be send.");
          // repeat;
        }
        if (a_SECC_processPLCLinkNotifications_001())
        {
        }
        if (SECC_Tester::pt_SLAC_Port->receive())
        {
          setverdict(v_vct, "Invalid message type or content was received.");
          v_repetition = false;
        }
        if (SECC_Tester::tc_TT_match_response->timeout())
        {
          SLOGI("TT_match_response timeout.");
          if (v_count1 mod(par_C_EV_match_retry + 1) == 0)
          {
            setverdict(v_vct, "The repetition limit is reached. The Matching process is considered as FAILED.");
            v_repetition = false;
          }
          else
          {
            SLOGI("The repetition limit is not reached, a new CM_VALIDATE.REQ message will be send.");
          }
        }
        if (SECC_Tester::tc_TT_matching_repetition->timeout())
        {
          SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
          // repeat;
        }
      }
    }
    if (getverdict() == pass)
    {
      // encoding vald toggle time
      hexstring v_pilotTimer = int2hex(float2int((par_TP_EV_vald_toggle * 10.0) - 1.0), 2);
      SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
          md_CMN_CMN_CmValidateReq_002(v_pilotTimer))); // to vc_sut_mac;
      SECC_Tester::tc_TP_EV_vald_toggle->start(par_TP_EV_vald_toggle + par_CMN_Transmission_Delay);
      // start BCB toggle sequence
      for (integer i = 0; i < C_vald_nb_toggles; i = i + 1)
      {
        // B toggle
        SECC_Tester::tc_TP_EV_vald_state_duration->start(par_TP_EV_vald_state_duration);
        f_SECC_setState(B, v_HAL_61851_Listener);
        SECC_Tester::tc_TP_EV_vald_state_duration->timeout;
        // C toggle
        SECC_Tester::tc_TP_EV_vald_state_duration->start(par_TP_EV_vald_state_duration);
        f_SECC_changeValidStateCondition(C);
        f_SECC_setState(C, v_HAL_61851_Listener);
        SECC_Tester::tc_TP_EV_vald_state_duration->timeout;
        // B toggle
        SECC_Tester::tc_TP_EV_vald_state_duration->start(par_TP_EV_vald_state_duration);
        f
            _SECC_changeValidStateCondition(B);
        f_SECC_setState(B, v_HAL_61851_Listener);
        SECC_Tester::tc_TP_EV_vald_state_duration->timeout;
      }
      while (true)
      {
        if (SECC_Tester::tc_TP_EV_vald_toggle->timeout())
        {
          SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
          while (true)
          {
            if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                    md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
                    md_CMN_CMN_CmValidateCnf_002(MATCH_ANY, MATCH_ANY))))
            {
              //-> value v_responseMessage
              SECC_Tester::tc_TT_match_response->stop();
              hexstring v_result = v_responseMessage.mme_payload.payload.cm_validate_cnf.vcVarField.result;
              ToggleNum_TYPE v_toggle_num = v_responseMessage.mme_payload.payload.cm_validate_cnf.vcVarField.toggle_num;
              f_checkResultFieldStep2(v_result, v_vct);
              if (getverdict() == pass)
              {
                if (hex2int(v_toggle_num) == C_vald_nb_toggles)
                {
                  setverdict(pass, "EVSE_FOUND, the number of detected BCB toggles is correct.");
                }
                else
                {
                  setverdict(v_vct, "The number of detected BCB toggles is not correct.");
                }
              }
            }
            if (a_SECC_processPLCLinkNotifications_001())
            {
            }
            if (SECC_Tester::pt_SLAC_Port->receive())
            {
              setverdict(v_vct, "Invalid message type or content was received.");
            }
            if (SECC_Tester::tc_TT_match_response->timeout())
            {
              setverdict(v_vct, "TT_match_response timeout. The Validation process will be stopped.");
            }
            if (SECC_Tester::tc_TT_matching_repetition->timeout())
            {
              SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
              // repeat;
            }
          }
        }
      }
    }
  }
  else
  {
    setverdict(inconc, "Invalid BCB toggle configuration. Check module parameter.");
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_CmValidate_002(void)
{
  // runs on SECC_Tester return VerdictValue
  boolean v_repetition = true;
  integer v_count1 = 0;
  MME v_responseMessage;
  if (f_checkValidToggleConfig())
  {
    while (v_repetition)
    {
      SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
      v_count1 = v_count1 + 1;
      SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
          m_CMN_CMN_CmValidateReq_001())); // to vc_sut_mac;
      while (true)
      {
        if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
                md_CMN_CMN_CmValidateCnf_001(MATCH_ANY))))
        {
          //-> value v_responseMessage
          SECC_Tester::tc_TT_match_response->stop();
          hexstring v_result = v_responseMessage.mme_payload.payload.cm_validate_cnf.vcVarField.result;
          v_repetition = f_checkResultFieldStep1(v_result, v_repetition, fail);
        }
        if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_IND = "606E"}), MATCH_ANY)))
        {
          SECC_Tester::tc_TT_match_response->stop();
          SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
          SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}),
              md_CMN_CMN_CmAttenCharRsp_001(m_CMN_CMN_SlacPayloadHeader_001(), md_CMN_CMN_Acvarfield_001(par_testSystem_mac, vc_RunID)))); // to vc_sut_mac;
          SLOGI("A further CM_ATTEN_CHAR.IND message was received. A new CM_ATTEN_CHAR.RSP has to be send.");
          // repeat;
        }
        if (a_SECC_processPLCLinkNotifications_001())
        {
        }
        if (SECC_Tester::pt_SLAC_Port->receive())
        {
          setverdict(fail, "Invalid message type or content was received.");
          v_repetition = false;
        }
        if (SECC_Tester::tc_TT_match_response->timeout())
        {
          SLOGI("TT_match_response timeout.");
          if (v_count1 mod(par_C_EV_match_retry + 1) == 0)
          {
            setverdict(fail, "The repetition limit is reached. The Matching process is considered as FAILED.");
            v_repetition = false;
          }
          else
          {
            SLOGI("The repetition limit is not reached, a new CM_VALIDATE.REQ message will be send.");
          }
        }
        if (SECC_Tester::tc_TT_matching_repetition->timeout())
        {
          SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
          // repeat;
        }
      }
    }
    if (getverdict() == pass)
    {
      hexstring v_pilotTimer = int2hex(float2int(par_TP_EV_vald_toggle * 10.0), 2);
      SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
      SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
          md_CMN_CMN_CmValidateReq_002("00"))); // to vc_sut_mac;
      while (true)
      {
        if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
                md_CMN_CMN_CmValidateCnf_001(MATCH_ANY))))
        {
          setverdict(pass, "Step 1 CM_VALIDATE.CNF message was repeated.");
        }
        if (a_SECC_processPLCLinkNotifications_001())
        {
        }
        if (SECC_Tester::pt_SLAC_Port->receive())
        {
          setverdict(fail, "Invalid message type or content was received.");
        }
        if (SECC_Tester::tc_TT_match_response->timeout())
        {
          setverdict(fail, "TT_match_response timeout. Step 1 CM_VALIDATE.CNF message was not repeated.");
        }
        if (SECC_Tester::tc_TT_matching_repetition->timeout())
        {
          SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
          // repeat;
        }
      }
    }
  }
  else
  {
    setverdict(inconc, "Invalid BCB toggle configuration. Check module parameter.");
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_CmValidate_003(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener)
{
  // runs on SECC_Tester return VerdictValue
  MME v_responseMessage;
  MACAddress_TYPE v_address;
  integer v_count = 0;
  SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
  SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
      md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
      m_CMN_CMN_CmValidateReq_001())); // to vc_sut_mac;
  while (true)
  {
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
            md_CMN_CMN_CmValidateCnf_001(MATCH_ANY))))
    {
      //-> value v_responseMessage
      SECC_Tester::tc_TT_match_response->stop();
      if (v_count > 0)
      {
        setverdict(pass, "CM_VALIDATE.CNF message was repeated.", v_count);
      }
      v_count = v_count + 1;
      SECC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence + par_CMN_Transmission_Delay);
      if (v_count > par_C_EV_match_retry)
      {
        while (true)
        {
          if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
                  md_CMN_CMN_CmValidateCnf_001(MATCH_ANY))))
          {
            //-> value v_responseMessage
            setverdict(fail, "CM_VALIDATE.CNF message was repeated, but v_count > par_C_EV_match_retry.");
          }
          if (SECC_Tester::tc_TT_match_sequence->timeout())
          {
            setverdict(pass, "TT_match_sequence timeout. The total number of retries is reached, the Validation process shall be considered as FAILED");
            // encoding vald toggle time
            hexstring v_pilotTimer = int2hex(float2int((par_TP_EV_vald_toggle * 10.0) - 1.0), 2);
            SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
                md_CMN_CMN_CmValidateReq_002(v_pilotTimer))); // to vc_sut_mac;
            SECC_Tester::tc_TP_EV_vald_toggle->start(par_TP_EV_vald_toggle + par_CMN_Transmission_Delay);
            // start BCB toggle sequence
            for (integer i = 0; i < C_vald_nb_toggles; i = i + 1)
            {
              // B toggle
              SECC_Tester::tc_TP_EV_vald_state_duration->start(par_TP_EV_vald_state_duration);
              f_SECC_setState(B, v_HAL_61851_Listener);
              SECC_Tester::tc_TP_EV_vald_state_duration->timeout;
              // C toggle
              SECC_Tester::tc_TP_EV_vald_state_duration->start(par_TP_EV_vald_state_duration);
              f_SECC_changeValidStateCondition(C);
              f_SECC_setState(C, v_HAL_61851_Listener);
              SECC_Tester::tc_TP_EV_vald_state_duration->timeout;
              // B toggle
              SECC_Tester::tc_TP_EV_vald_state_duration->start(par_TP_EV_vald_state_duration);
              f_SECC_changeValidStateCondition(B);
              f_SECC_setState(B, v_HAL_61851_Listener);
              SECC_Tester::tc_TP_EV_vald_state_duration->timeout;
            }
            while (true)
            {
              if (SECC_Tester::tc_TP_EV_vald_toggle->timeout())
              {
                SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
                while (true)
                {
                  if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                          md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
                          md_CMN_CMN_CmValidateCnf_002(MATCH_ANY, MATCH_ANY))))
                  {
                    SECC_Tester::tc_TT_match_response->stop();
                    setverdict(fail, "CM_VALIDATE.CNF message was not expected, the Matching process shall be considered as FAILED.");
                  }
                  if (a_SECC_processPLCLinkNotifications_001())
                  {
                  }
                  if (SECC_Tester::pt_SLAC_Port->receive())
                  {
                    setverdict(fail, "Invalid message type or content was received.");
                  }
                  if (SECC_Tester::tc_TT_match_response->timeout())
                  {
                    setverdict(pass, "TT_match_response timeout. Matching process is considered as FAILED.");
                  }
                  if (SECC_Tester::tc_TT_matching_repetition->timeout())
                  {
                    SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
                    // repeat;
                  }
                }
              }
            }
          }
        }
      }
      else
      {
        // repeat;
      }
    }
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_IND = "606E"}), MATCH_ANY)))
    {
      SECC_Tester::tc_TT_match_response->stop();
      SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
      SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}),
          md_CMN_CMN_CmAttenCharRsp_001(m_CMN_CMN_SlacPayloadHeader_001(), md_CMN_CMN_Acvarfield_001(par_testSystem_mac, vc_RunID)))); // to vc_sut_mac;
      SLOGI("A further CM_ATTEN_CHAR.IND message was received. A new CM_ATTEN_CHAR.RSP has to be send.");
      // repeat;
    }
    if (a_SECC_processPLCLinkNotifications_001())
    {
    }
    if (SECC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
    if (SECC_Tester::tc_TT_match_response->timeout())
    {
      setverdict(fail, "TT_match_response timer timeout. No CM_VALIDATE.CNF message was received.");
    }
    if (SECC_Tester::tc_TT_match_sequence->timeout())
    {
      setverdict(fail, "TT_match_sequence timeout. CM_VALIDATE.CNF message was not repeated.");
    }
    if (SECC_Tester::tc_TT_matching_repetition->timeout())
    {
      SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
      // repeat;
    }
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_CmValidate_004(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener, const MME_Payload &mmePayload)
{
  // runs on SECC_Tester return VerdictValue {
  MME v_responseMessage;
  MACAddress_TYPE v_address;
  integer v_count = 0;
  SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
  SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}), m_CMN_CMN_CmValidateReq_001())); // to vc_sut_mac;
  while (true)
  {
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
            md_CMN_CMN_CmValidateCnf_001(MATCH_ANY))))
    {
      //-> value v_responseMessage
      SECC_Tester::tc_TT_match_response->stop();
      if (v_count > 0)
      {
        setverdict(pass, "CM_VALIDATE.CNF message was repeated.", v_count);
      }
      v_count = v_count + 1;
      SECC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence + par_CMN_Transmission_Delay);
      // send invalid step 2 CM_VALIDATE.REQ message
      SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}), mmePayload)); // to vc_sut_mac;
      if (v_count > par_C_EV_match_retry)
      {
        while (true)
        {
          if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
                  md_CMN_CMN_CmValidateCnf_001(MATCH_ANY))))
          {
            //-> value v_responseMessage
            setverdict(fail, "CM_VALIDATE.CNF message was repeated, but v_count > par_C_EV_match_retry.");
          }
          if (SECC_Tester::tc_TT_match_sequence->timeout())
          {
            setverdict(pass, "TT_match_sequence timeout. The total number of retries is reached, the Validation process shall be considered as FAILED.");
            // encoding vald toggle time
            hexstring v_pilotTimer = int2hex(float2int((par_TP_EV_vald_toggle * 10.0) - 1.0), 2);
            SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
                md_CMN_CMN_CmValidateReq_002(v_pilotTimer))); // to vc_sut_mac;
            SECC_Tester::tc_TP_EV_vald_toggle->start(par_TP_EV_vald_toggle + par_CMN_Transmission_Delay);
            // start BCB toggle sequence
            for (integer i = 0; i < C_vald_nb_toggles; i = i + 1)
            {
              // B toggle
              SECC_Tester::tc_TP_EV_vald_state_duration->start(par_TP_EV_vald_state_duration);
              f_SECC_setState(B, v_HAL_61851_Listener);
              SECC_Tester::tc_TP_EV_vald_state_duration->timeout;
              // C toggle
              SECC_Tester::tc_TP_EV_vald_state_duration->start(par_TP_EV_vald_state_duration);
              f_SECC_changeValidStateCondition(C);
              f_SECC_setState(C, v_HAL_61851_Listener);
              SECC_Tester::tc_TP_EV_vald_state_duration->timeout;
              // B toggle
              SECC_Tester::tc_TP_EV_vald_state_duration->start(par_TP_EV_vald_state_duration);
              f_SECC_changeValidStateCondition(B);
              f_SECC_setState(B, v_HAL_61851_Listener);
              SECC_Tester::tc_TP_EV_vald_state_duration->timeout;
            }
            while (true)
            {
              if (SECC_Tester::tc_TP_EV_vald_toggle->timeout())
              {
                SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
                while (true)
                {
                  if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                          md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
                          md_CMN_CMN_CmValidateCnf_002(MATCH_ANY, MATCH_ANY))))
                  {
                    SECC_Tester::tc_TT_match_response->stop();
                    setverdict(fail, "CM_VALIDATE.CNF message was not expected, the Matching process shall be considered as FAILED.");
                  }
                  if (a_SECC_processPLCLinkNotifications_001())
                  {
                  }
                  if (SECC_Tester::pt_SLAC_Port->receive())
                  {
                    setverdict(fail, "Invalid message type or content was received.");
                  }
                  if (SECC_Tester::tc_TT_match_response->timeout())
                  {
                    setverdict(pass, "TT_match_response timeout. Matching process was considered as FAILED.");
                  }
                  if (SECC_Tester::tc_TT_matching_repetition->timeout())
                  {
                    SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
                    // repeat;
                  }
                }
              }
            }
          }
        }
      }
      else
      {
        // repeat;
      }
    }
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_IND = "606E"}), MATCH_ANY)))
    {
      SECC_Tester::tc_TT_match_response->stop();
      SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
      SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}),
          md_CMN_CMN_CmAttenCharRsp_001(
              m_CMN_CMN_SlacPayloadHeader_001(),
              md_CMN_CMN_Acvarfield_001(
                  par_testSystem_mac, vc_RunID)))); // to vc_sut_mac;
      SLOGI("A further CM_ATTEN_CHAR.IND message was received. A new CM_ATTEN_CHAR.RSP has to be send.");
      // repeat;
    }
    if (a_SECC_processPLCLinkNotifications_001())
    {
    }
    if (SECC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
    if (SECC_Tester::tc_TT_match_response->timeout())
    {
      setverdict(fail, "TT_match_response timeout. CM_VALIDATE.CNF message was not repeated.");
    }
    if (SECC_Tester::tc_TT_matching_repetition->timeout())
    {
      SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
      // repeat;
    }
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_CmValidate_005(const MME_Payload &mmePayload)
{
  // runs on SECC_Tester return VerdictValue
  MME v_responseMessage;
  MACAddress_TYPE v_address;
  SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
  SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
      md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
      m_CMN_CMN_CmValidateReq_001())); // to vc_sut_mac;
  while (true)
  {
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
            md_CMN_CMN_CmValidateCnf_001(MATCH_ANY))))
    {
      //-> value v_responseMessage
      SECC_Tester::tc_TT_match_response->stop();
      setverdict(pass, "CM_VALIDATE.CNF message was successful.");
      SECC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence + par_CMN_Transmission_Delay);
      // send step 2 CM_VALIDATE.REQ message with a result field unequal than 'ready'
      SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}), mmePayload)); // to vc_sut_mac;
      while (true)
      {
        if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
                md_CMN_CMN_CmValidateCnf_001(MATCH_ANY))))
        {
          //-> value v_responseMessage
          setverdict(fail, "CM_VALIDATE.CNF message was repeated, but Validation process shall be considered as FAILED.");
        }
        if (a_SECC_processPLCLinkNotifications_001())
        {
        }
        if (SECC_Tester::pt_SLAC_Port->receive())
        {
          setverdict(fail, "Invalid message type or content was received.");
        }
        if (SECC_Tester::tc_TT_match_sequence->timeout())
        {
          setverdict(pass, "TT_match_sequence timeout. The Validation process is considered as FAILED.");
        }
        if (SECC_Tester::tc_TT_matching_repetition->timeout())
        {
          SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
          // repeat;
        }
      }
    }
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_IND = "606E"}), MATCH_ANY)))
    {
      SECC_Tester::tc_TT_match_response->stop();
      SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
      SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}),
          md_CMN_CMN_CmAttenCharRsp_001(m_CMN_CMN_SlacPayloadHeader_001(), md_CMN_CMN_Acvarfield_001(par_testSystem_mac, vc_RunID)))); // to vc_sut_mac;
      SLOGI("A further CM_ATTEN_CHAR.IND message was received. A new CM_ATTEN_CHAR.RSP has to be send.");
      // repeat;
    }
    if (a_SECC_processPLCLinkNotifications_001())
    {
    }
    if (SECC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
    if (SECC_Tester::tc_TT_match_response->timeout())
    {
      setverdict(fail, "TT_match_response timeout. CM_VALIDATE.CNF message was not repeated.");
    }
    if (SECC_Tester::tc_TT_matching_repetition->timeout())
    {
      SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
      // repeat;
    }
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_CmValidate_006(void)
{
  // runs on SECC_Tester return VerdictValue
  boolean v_repetition = true;
  integer v_count1 = 0;
  MME v_responseMessage;
  if (f_checkValidToggleConfig())
  {
    if (tc_TP_EVSE_match_session.running())
    {
      SECC_Tester::tc_TP_EVSE_match_session->stop();
      while (v_repetition)
      {
        SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
        v_count1 = v_count1 + 1;
        SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            m_CMN_CMN_CmValidateReq_001())); // to vc_sut_mac;
        while (true)
        {
          if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
                  md_CMN_CMN_CmValidateCnf_001(MATCH_ANY))))
          {
            //-> value v_responseMessage
            SECC_Tester::tc_TT_match_response->stop();
            hexstring v_result = v_responseMessage.mme_payload.payload.cm_validate_cnf.vcVarField.result;
            v_repetition = f_checkResultFieldStep1(v_result, v_repetition,
                                                   fail);
          }
          if (a_SECC_processPLCLinkNotifications_001())
          {
          }
          if (SECC_Tester::pt_SLAC_Port->receive())
          {
            setverdict(fail, "Invalid message type or content was received.");
            v_repetition = false;
          }
          if (SECC_Tester::tc_TT_match_response->timeout())
          {
            SLOGI("TT_match_response timeout.");
            if (v_count1 mod(par_C_EV_match_retry + 1) == 0)
            {
              setverdict(fail, "The repetition limit is reached. The Matching process is considered as FAILED.");
              v_repetition = false;
            }
            else
            {
              SLOGI("The repetition limit is not reached, a new CM_VALIDATE.REQ message will be send.");
            }
          }
          if (SECC_Tester::tc_TT_matching_repetition->timeout())
          {
            SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
            // repeat;
          }
        }
      }
    }
    else
    {
      setverdict(inconc, "The tc_TP_EVSE_match_session timer has expired. The validation process can not be continued.");
    }
  }
  else
  {
    setverdict(inconc, "Invalid BCB toggle configuration. Check module parameter.");
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_CmValidate_007(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener)
{
  // runs on SECC_Tester return VerdictValue
  MME v_responseMessage;
  // encoding vald toggle time
  hexstring v_pilotTimer = int2hex(float2int((
                                                 par_TP_EV_vald_toggle * 10.0) -
                                             1.0),
                                   2);
  SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
      md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
      md_CMN_CMN_CmValidateReq_002(v_pilotTimer))); // to vc_sut_mac;
  SECC_Tester::tc_TP_EV_vald_toggle->start(par_TP_EV_vald_toggle + par_CMN_Transmission_Delay);
  // start BCB toggle sequence
  for (integer i = 0; i < C_vald_nb_toggles; i = i + 1)
  {
    // B toggle
    SECC_Tester::tc_TP_EV_vald_state_duration->start(par_TP_EV_vald_state_duration);
    f_SECC_setState(B, v_HAL_61851_Listener);
    SECC_Tester::tc_TP_EV_vald_state_duration->timeout;
    // C toggle
    SECC_Tester::tc_TP_EV_vald_state_duration->start(par_TP_EV_vald_state_duration);
    f_SECC_changeValidStateCondition(C);
    f_SECC_setState(C, v_HAL_61851_Listener);
    SECC_Tester::tc_TP_EV_vald_state_duration->timeout;
    // B toggle
    SECC_Tester::tc_TP_EV_vald_state_duration->start(par_TP_EV_vald_state_duration);
    f_SECC_changeValidStateCondition(B);
    f_SECC_setState(B, v_HAL_61851_Listener);
    SECC_Tester::tc_TP_EV_vald_state_duration->timeout;
  }
  while (true)
  {
    if (SECC_Tester::tc_TP_EV_vald_toggle->timeout())
    {
      SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
      while (true)
      {
        if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
                md_CMN_CMN_CmValidateCnf_002(MATCH_ANY, MATCH_ANY))))
        {
          //-> value v_responseMessage
          SECC_Tester::tc_TT_match_response->stop();
          hexstring v_result = v_responseMessage.mme_payload.payload.cm_validate_cnf.vcVarField.result;
          ToggleNum_TYPE v_toggle_num = v_responseMessage.mme_payload.payload.cm_validate_cnf.vcVarField.toggle_num;
          f_checkResultFieldStep2(v_result, fail);
          if (getverdict() == pass)
          {
            if (hex2int(v_toggle_num) == C_vald_nb_toggles)
            {
              setverdict(pass, "EVSE_FOUND, the number of detected BCB toggles is correct.");
            }
            else
            {
              setverdict(fail, "The number of detected BCB toggles is not correct.");
            }
          }
        }
        if (a_SECC_processPLCLinkNotifications_001())
        {
        }
        if (SECC_Tester::pt_SLAC_Port->receive())
        {
          setverdict(fail, "Invalid message type or content was received.");
        }
        if (SECC_Tester::tc_TT_match_response->timeout())
        {
          setverdict(fail, "TT_match_response timeout. Validation process will be stopped.");
        }
        if (SECC_Tester::tc_TT_matching_repetition->timeout())
        {
          SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
          // repeat;
        }
      }
    }
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_CmValidate_008(Result_TYPE p_result)
{
  // runs on SECC_Tester
  // return VerdictValue
  boolean v_repetition = true;
  integer v_count1 = 0;
  MME v_responseMessage;
  while (v_repetition)
  {
    SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
    v_count1 = v_count1 + 1;
    SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
        md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
        m_CMN_CMN_CmValidateReq_001())); // to vc_sut_mac;
    while (true)
    {
      if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
              md_CMN_CMN_CmValidateCnf_001(
                  p_result))))
      {
        SECC_Tester::tc_TT_match_response->stop();
      }
      if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_IND = "606E"}), MATCH_ANY)))
      {
        SECC_Tester::tc_TT_match_response->stop();
        SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
        SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}),
            md_CMN_CMN_CmAttenCharRsp_001(m_CMN_CMN_SlacPayloadHeader_001(), md_CMN_CMN_Acvarfield_001(par_testSystem_mac, vc_RunID)))); // to vc_sut_mac;
        SLOGI("A further CM_ATTEN_CHAR.IND message was received. A new CM_ATTEN_CHAR.RSP has to be send.");
        // repeat;
      }
      if (a_SECC_processPLCLinkNotifications_001())
      {
      }
      if (SECC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
        v_repetition = false;
      }
      if (SECC_Tester::tc_TT_match_response->timeout())
      {
        SLOGI("TT_match_response timeout.");
        if (v_count1 mod(par_C_EV_match_retry + 1) == 0)
        {
          setverdict(fail, "The repetition limit is reached. The Matching process is considered as FAILED.");
          v_repetition = false;
        }
        else
        {
          SLOGI("The repetition limit is not reached, a new CM_VALIDATE.REQ message will be send.");
        }
      }
      if (SECC_Tester::tc_TT_matching_repetition->timeout())
      {
        SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
        // repeat;
      }
    }
  }
  return SECC_Tester::getverdict();
}
// SLAC Tester
VerdictValue f_SECC_CMN_TB_VTB_CmValidate_009(void)
{
  //  runs on SLAC_Tester return VerdictValue
  boolean v_repetition = true;
  integer v_count1 = 0;
  MME v_responseMessage;
  while (v_repetition)
  {
    SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
    v_count1 = v_count1 + 1;
    SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
        md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
        m_CMN_CMN_CmValidateReq_001())); // to vc_sut_mac;
    while (true)
    {
      if (SECC_Tester::pt_SLAC_Port->receive(
        md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
          md_CMN_CMN_CmValidateCnf_001(par_cmValidate_result_notReady))))
      {
        setverdict(pass, "CM_VALIDATE.CNF message with 'notReady' is correct. SUT has indicated that it is temporary busy.");
        SECC_Tester::tc_TT_match_response->stop();
      }
      if (a_SECC_processPLCLinkNotifications_001())
      {
      }
      if (SECC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
        v_repetition = false;
      }
      if (SECC_Tester::tc_TT_match_response->timeout())
      {
        SLOGI("TT_match_response timeout.");
        if (v_count1 mod(par_C_EV_match_retry + 1) == 0)
        {
          setverdict(fail, "The repetition limit is reached. The Matching process is considered as FAILED.");
          v_repetition = false;
        }
        else
        {
          SLOGI("The repetition limit is not reached, a new CM_VALIDATE.REQ message will be send.");
        }
      }
      if (SECC_Tester::tc_TT_matching_repetition->timeout())
      {
        SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
        // repeat;
      }
    }
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_CmValidate_010(const std::shared_ptr<HAL_61851_Listener > &v_HAL_61851_Listener)
{
  // runs on SECC_Tester return VerdictValue
  f_SECC_changeValidStateCondition(invalid);
  f_SECC_changeValidFrequencyRange(0, 0);
  f_SECC_changeValidDutyCycleRange(100, 100);
  deactivate(vc_Default_IEC_61851_ListenerBehavior);
  f_SECC_setState(A, v_HAL_61851_Listener);
  SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
  SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
      md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
      m_CMN_CMN_CmValidateReq_001())); // to vc_sut_mac;
  while (true)
  {
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
            md_CMN_CMN_CmValidateCnf_001(MATCH_ANY))))
    {
      setverdict(fail, "CM_VALIDATE.CNF message was not expected.CP State A should be detected before.");
    }
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_IND = "606E"}), MATCH_ANY)))
    {
      SECC_Tester::tc_TT_match_response->stop();
      SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
      SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}),
          md_CMN_CMN_CmAttenCharRsp_001(m_CMN_CMN_SlacPayloadHeader_001(), md_CMN_CMN_Acvarfield_001(par_testSystem_mac, vc_RunID)))); // to vc_sut_mac;
      SLOGI("A further CM_ATTEN_CHAR.IND message was received. A new CM_ATTEN_CHAR.RSP has to be send.");
      // repeat;
    }
    if (a_SECC_processPLCLinkNotifications_001())
    {
    }
    if (SECC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
    if (SECC_Tester::tc_TT_match_response->timeout())
    {
      setverdict(pass, "TT_match_response timer has expired, the Matching process was terminated by the SUT.");
    }
    if (SECC_Tester::tc_TT_matching_repetition->timeout())
    {
      SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
      // repeat;
    }
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_CmValidatePreCondition_001(void)
{
  //  runs on SLAC_Tester
  // return VerdictValue
  MME v_responseMessage;
  boolean v_repetition = true;
  MACAddress_TYPE v_sut_mac;
  integer v_count1 = 0;
  integer v_count2 = 0;
  SourceRnd_Type v_source_rnd = f_randomHexStringGen(32);
  vc_LowestAverageAttenuation = 0.0;
  vc_macAddresList = m_CMN_CMN_EmptyMacAddressList();
  vc_RunID = f_randomHexStringGen(16);
  while (v_repetition)
  {
    SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
    v_count1 = v_count1 + 1;
    SECC_Tester::pt_SLAC_Port->send(
      md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
        md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))); // to cc_eth_broadcast;
    while (true)
    {
      if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
        md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
        md_CMN_CMN_CmSlacParmCnf_001(par_testSystem_mac, m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))))
      {
        //-> value v_responseMessage sender v_sut_mac
        setverdict(pass, "CM_SLAC_PARM is correct.");
        vc_macAddresList.macAddressList[v_count2] = v_sut_mac;
        v_count2 = v_count2 + 1;
        vc_Num_sounds = v_responseMessage.mme_payload.payload.cm_slac_parm_cnf.num_sounds;
        vc_Time_out = v_responseMessage.mme_payload.payload.cm_slac_parm_cnf.time_out;
        // repeat;
      }
      if (a_SECC_processPLCLinkNotifications_002())
      {
      }
      if (SECC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
        v_repetition = false;
      }
      if (SECC_Tester::tc_TT_match_response->timeout())
      {
        if (sizeof(vc_macAddresList.macAddressList) > 0)
        {
          SECC_Tester::tc_TP_match_sequence->start(par_TP_match_sequence);
          v_repetition = false;
        }
        else if (v_count1 mod(par_C_EV_match_retry + 1) == 0)
        {
          SLOGI("The Matching process is considered as FAILED.");
          if (tc_TT_matching_repetition.running())
          {
            SLOGI("TT_matching_repetition is still running. A new Matching process is started.");
            v_count1 = 0;
          }
          else
          {
            setverdict(fail, "TT_matching_repetition has expired. No new Matching process will be started.");
            v_repetition = false;
          }
        }
      }
    }
  }
  if (getverdict == pass)
  {
    SECC_Tester::tc_TP_match_sequence->timeout;
    SECC_Tester::tc_TT_EV_atten_results->start(par_TT_EV_atten_results);
    for (integer i = 0; i < 3; i = i + 1)
    {
      SECC_Tester::tc_TP_EV_batch_msg_interval->start(par_TP_EV_batch_msg_interval);
      SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_START_ATTEN_CHAR_IND = "606A"}),
          md_CMN_CMN_CmStartAttenCharInd_001(m_CMN_CMN_SlacPayloadHeader_001(), vc_Num_sounds, vc_Time_out, "01", par_testSystem_mac, vc_RunID))); // to cc_eth_broadcast;
      SECC_Tester::tc_TP_EV_batch_msg_interval->timeout;
    }
    integer v_cnt = par_C_EV_match_MNBC;
    for (integer i = 0; i < par_C_EV_match_MNBC; i = i + 1)
    {
      v_cnt = v_cnt - 1;
      SECC_Tester::tc_TP_EV_batch_msg_interval->start(par_TP_EV_batch_msg_interval);
      SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}),
          md_CMN_CMN_CmMnbcSoundInd_001(
              m_CMN_CMN_SlacPayloadHeader_001(), int2hex(v_cnt, 2),
              vc_RunID, v_source_rnd))); // to cc_eth_broadcast;
      SECC_Tester::tc_TP_EV_batch_msg_interval->timeout;
    }
    integer v_cnt_pot_evse = 0;
    while (true)
    {
      if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_IND = "606E"}),
              mdw_SECC_CMN_CmAttenCharInd_001(
                  m_CMN_CMN_SlacPayloadHeader_001(),
                  par_testSystem_mac, vc_RunID, MATCH_ANY))))
      {
        //-> value v_responseMessage sender v_sut_mac
        setverdict(pass, "CM_ATTEN_CHAR.IND is correct.");
        v_cnt_pot_evse = v_cnt_pot_evse + 1;
        SECC_Tester::tc_TP_match_sequence->start(par_TP_match_sequence);
        SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}),
            md_CMN_CMN_CmAttenCharRsp_001(
                m_CMN_CMN_SlacPayloadHeader_001(),
                md_CMN_CMN_Acvarfield_001(par_testSystem_mac, vc_RunID))))
            to v_sut_mac;
        SECC_Tester::tc_TP_match_sequence->stop();
        f_SECC_CMN_setMac(v_responseMessage, v_sut_mac);
        if (sizeof(vc_macAddresList.macAddressList) == v_cnt_pot_evse)
        {
          SLOGI("CM_ATTEN_CHAR.IND messages from all EVSEs are received.");
        }
        else
        {
          // repeat;
        }
      }
      if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}), MATCH_ANY)))
      {
        // CM_SLAC_PARM.CNF messages will be ignored!
        // repeat;
      }
      if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_PROFILE_IND = "6086"}), MATCH_ANY)))
      {
        // CM_ATTEN_PROFILE.IND messages will be ignored!
        // repeat;
      }
      if (a_SECC_processPLCLinkNotifications_002())
      {
      }
      if (SECC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
      }
      if (SECC_Tester::tc_TT_EV_atten_results->timeout())
      {
        if (v_cnt_pot_evse == 0)
        {
          setverdict(fail, "TT_EV_atten_results timeout and no CM_ATTEN_CHAR.IND received - EVSE_NOT_FOUND.");
        }
      }
      if (SECC_Tester::tc_TT_matching_repetition->timeout())
      {
        SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
        // repeat;
      }
    }
  }
  return SECC_Tester::getverdict();
}
}
}