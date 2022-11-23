
#include "behaviorfunction/evcc_cmvalidate.hpp"
#include "template/template.hpp"

// import from Timer_15118_3 all;
// import from Pixit_15118_3 all;
// import from Pics_15118_3 all;
// import from Templates_CMN_CmValidate all;
// import from Templates_CMN_CmStartAttenCharInd all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from Templates_CMN_CmMnbcSoundInd all;
// import from Templates_CMN_CmAttenCharRsp all;
// import from Templates_EVCC_CmAttenCharInd all;
// import from Templates_EVCC_CmAttenProfileInd all;
// import from Templates_CMN_CmSlacParm all;
// import from ComponentsAndPorts all;
// import from DataStructure_SLAC all;
// import from TestBehavior_EVCC_AttenuationCharacterization all;
// import from LibFunctions_15118_3 { group generalFunctions; }
// import from Services_HAL_61851 all;
// import from Templates_CMN_CmSlacParm all;
// import from Templates_CMN_HAL61851 all;
// import from DataStructure_HAL_61851 all;
// import from Templates_CMN_CmSlacMatch all;
// import from Services_PLCLinkStatus all;
// import from Pics_15118 all;
// import from DataStructure_HAL_61851 all;
// import from Timer_15118 all;
#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)
namespace TestLib
{
namespace TestBehavior_EVCC_CmValidate
{
float decodeValdToggleTime(PilotTimer_TYPE v_pilotTimer)
{
  return (int2float((hex2int(v_pilotTimer) + 1)) * 0.1);
}
// EVCC Tester
VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_001(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, boolean v_changeDC, integer v_dutyCycle, VerdictValue v_vct)
{
  // runs on EVCC_Tester return VerdictValue {
  MME v_requestMessage;
  integer cnt = 0;
  boolean isStep2 = false;
  float v_TT_EVSE_vald_toggle;
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            md_CMN_CMN_CmValidateReq_004(MATCH_ANY, MATCH_ANY, MATCH_ANY))))
    {
      //-> value v_requestMessage
      PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.cm_validate_req.vrVarField.pilot_timer;
      SignalType_TYPE p_signalType = v_requestMessage.mme_payload.payload.cm_validate_req.signalType;
      if ((p_signalType != "00"))
      {
        setverdict(v_vct, "Step 1 CM_VALIDATE.REQ is not correct. Invalid signalType was detected.");
      }
      EVCC_Tester::tc_TT_EVSE_match_session->stop();
      if (v_pilotTimer == "00")
      {
        if (not isStep2)
        {
          setverdict(pass, "Step 1 CM_VALIDATE.REQ is correct.");
          isStep2 = true;
          if (v_changeDC)
          {
            // change current duty cycle
            f_EVCC_setDutyCycle(v_dutyCycle);
          }
        }
        else
        {
          SLOGI("Step 2 CM_VALIDATE.REQ message contains timer field equal to zero. Step 1 CM_VALIDATE.CNF will be resent.");
        }
        EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
            md_CMN_CMN_CmValidateCnf_001(
                par_cmValidate_result_ready))); // to vc_sut_mac;
        EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
        // repeat;
      }
      else if (decodeValdToggleTime(v_pilotTimer) >= par_TP_EV_vald_toggle_min and
               decodeValdToggleTime(v_pilotTimer) <= par_TP_EV_vald_toggle_max and
               isStep2)
      {
        setverdict(pass, "Step 2 CM_VALIDATE.REQ is correct.");
        EVCC_Tester::tc_TT_match_sequence->stop();
        v_TT_EVSE_vald_toggle = decodeValdToggleTime(v_pilotTimer);
      }
      else
      {
        setverdict(v_vct, "Invalid message content was received from the SUT.");
      }
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            mw_CMN_CMN_CmValidateReq_003())))
    {
      setverdict(v_vct, "Result field is not set to 'Ready'. Matching process is considered as FAILED.");
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
            md_CMN_CMN_CmSlacParmReq_001(
                m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    {
      setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}), MATCH_ANY)))
    {
      // CM_ATTEN_CHAR.RSP messages will be ignored!
      // repeat;
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(v_vct, "Invalid message type or content was received.");
    }
    if (EVCC_Tester::tc_TT_match_sequence->timeout())
    {
      cnt = cnt + 1;
      SLOGI("TT_match_sequence timeout.");
      if (cnt > par_C_EV_match_retry)
      {
        setverdict(v_vct, "Repetition limit is reached. Matching process is considered as FAILED.");
      }
      else
      {
        SLOGI("A new CM_VALIDATE.CNF message will be sent.");
        EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
            md_CMN_CMN_CmValidateCnf_001(
                par_cmValidate_result_ready))); // to vc_sut_mac;
        EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
        // repeat;
      }
    }
    if (EVCC_Tester::tc_TT_EVSE_match_session->timeout())
    {
      setverdict(v_vct, "TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
    }
  }
  if (getverdict == pass)
  {
    // BCB toggle sequence detection
    EVCC_Tester::tc_TT_EVSE_vald_toggle->start(v_TT_EVSE_vald_toggle);
    f_EVCC_changeValidStateCondition(B, C);
    timer statetimer = (par_T_vald_state_duration_max + par_CMN_Transmission_Delay);
    statetimer.start();
    integer toggleCnt = 0;
    while (true)
    {
      if (a_EVCC_BCBToggleDetection(EVCC_Tester::pt_HAL_61851_Internal_Port, B))
      {
        statetimer.stop;
        toggleCnt = toggleCnt + 1;
        f_EVCC_changeValidStateCondition(B, C);
        // repeat;
      }
      if (a_EVCC_BCBToggleDetection(EVCC_Tester::pt_HAL_61851_Internal_Port, C))
      {
        statetimer.stop;
        f_EVCC_changeValidStateCondition(C, B);
        statetimer.start(par_T_vald_state_duration_max);
        // repeat;
      }
      if (EVCC_Tester::pt_HAL_61851_Internal_Port.receive())
      {
        setverdict(v_vct, "Received state has an invalid value.");
      }
      if (statetimer.timeout())
      {
        setverdict(v_vct, "The EVSE could not detect the corresponding toggle value within the maximal valid state duration.");
      }
      if (EVCC_Tester::tc_TT_EVSE_vald_toggle->timeout())
      {
        if (toggleCnt > 0 and toggleCnt <= 3)
        {
          setverdict(pass, "Valid BCB toggle sequence could be detected.");
          EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
              md_CMN_CMN_CmValidateCnf_002(
                  int2hex(toggleCnt, 2),
                  par_cmValidate_result_success))); // to vc_sut_mac;
          f_EVCC_changeValidStateCondition(C, B);
          EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
        }
        else
        {
          setverdict(v_vct, "Invalid BCB toggle sequence was detected.");
        }
      }
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_002(void)
{
  // runs on EVCC_Tester
  // return VerdictValue
  MME v_responseMessage;
  integer v_count = 0;
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            m_CMN_CMN_CmValidateReq_001())))
    {
      //-> value v_responseMessage
      if (v_count > 0)
      {
        setverdict(pass, "CM_VALIDATE.REQ message was repeated.", v_count);
      }
      else
      {
        EVCC_Tester::tc_TT_EVSE_match_session->stop();
      }
      v_count = v_count + 1;
      EVCC_Tester::tc_TT_match_response->start(par_TT_match_response + par_CMN_Transmission_Delay);
      if (v_count > par_C_EV_match_retry)
      {
        while (true)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
                  m_CMN_CMN_CmValidateReq_001())))
          {
            setverdict(fail, "CM_VALIDATE.REQ message was repeated, but v_count > par_C_EV_match_retry.");
          }
          if (EVCC_Tester::tc_TT_match_response->timeout())
          {
            setverdict(pass, "TT_match_response timeout. The total number of retries is reached, the Validation process shall be considered as FAILED.");
          }
        }
      }
      else
      {
        // repeat;
      }
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
    if (EVCC_Tester::tc_TT_EVSE_match_session->timeout())
    {
      setverdict(fail, "TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_003(const MME_Payload &v_validateCnf)
{
  // runs on EVCC_Tester return VerdictValue
  MME v_responseMessage;
  integer v_count = 0;
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            m_CMN_CMN_CmValidateReq_001())))
    {
      //-> value v_responseMessage
      if (v_count > 0)
      {
        setverdict(pass, "CM_VALIDATE.REQ message was repeated.", v_count);
      }
      else
      {
        EVCC_Tester::tc_TT_EVSE_match_session->stop();
      }
      v_count = v_count + 1;
      EVCC_Tester::tc_TT_match_response->start(par_TT_match_response + par_CMN_Transmission_Delay);
      // send invalid CM_VALIDATE.CNF message
      EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}), v_validateCnf)); // to vc_sut_mac;
      if (v_count > par_C_EV_match_retry)
      {
        while (true)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
                  m_CMN_CMN_CmValidateReq_001())))
          {
            setverdict(fail, "CM_VALIDATE.REQ message was repeated, but v_count > par_C_EV_match_retry.");
          }
          if (EVCC_Tester::tc_TT_match_response->timeout())
          {
            setverdict(pass, "TT_match_response timeout. The total number of retries is reached, the Validation process shall be considered as FAILED.");
          }
        }
      }
      else
      {
        // repeat;
      }
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
    if (EVCC_Tester::tc_TT_EVSE_match_session->timeout())
    {
      setverdict(fail, "TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_004(hexstring v_resultCode, boolean v_isRepeat)
{
  // runs on EVCC_Tester return VerdictValue
  MME v_requestMessage;
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            md_CMN_CMN_CmValidateReq_002(MATCH_ANY))))
    {
      //-> value v_requestMessage
      PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.cm_validate_req.vrVarField.pilot_timer;
      EVCC_Tester::tc_TT_EVSE_match_session->stop();
      if (v_pilotTimer == "00")
      {
        setverdict(pass, "Step 1 CM_VALIDATE.REQ is correct.");
        EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
        EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
            md_CMN_CMN_CmValidateCnf_001(v_resultCode))); // to vc_sut_mac;
        if (v_isRepeat)
        {
          // repeat;
        }
      }
      else
      {
        EVCC_Tester::tc_TT_match_sequence->stop();
        setverdict(fail, "Step 2 CM_VALIDATE.REQ was received. The validation process with the current EVSE has to be stopped by the SUT before.");
      }
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            mw_CMN_CMN_CmValidateReq_003())))
    {
      setverdict(fail, "Result field is not set to 'Ready'. Matching process is considered as FAILED.");
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
            md_CMN_CMN_CmSlacParmReq_001(
                m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    {
      setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}), MATCH_ANY)))
    {
      // CM_ATTEN_CHAR.RSP messages will be ignored!
      // repeat;
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
    if (EVCC_Tester::tc_TT_match_sequence->timeout())
    {
      setverdict(pass, "TT_match_sequence timeout. The SUT has stopped the validation process with the current EVSE.");
    }
    if (EVCC_Tester::tc_TT_EVSE_match_session->timeout())
    {
      setverdict(fail, "TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_005(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  // runs on EVCC_Tester return VerdictValue
  MME v_requestMessage;
  integer cnt = 0;
  boolean isStep2 = false;
  float v_TT_EVSE_vald_toggle;
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            md_CMN_CMN_CmValidateReq_002(MATCH_ANY))))
    {
      //-> value v_requestMessage
      PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.cm_validate_req.vrVarField.pilot_timer;
      EVCC_Tester::tc_TT_EVSE_match_session->stop();
      if (v_pilotTimer == "00")
      {
        if (not isStep2)
        {
          setverdict(pass, "Step 1 CM_VALIDATE.REQ is correct.");
          isStep2 = true;
        }
        else
        {
          SLOGI("Step 2 CM_VALIDATE.REQ message contains timer field equal to zero. Step 1 CM_VALIDATE.CNF will be resent.");
        }
        EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
            md_CMN_CMN_CmValidateCnf_001(par_cmValidate_result_ready))); // to vc_sut_mac;
        EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
        // repeat;
      }
      else if (decodeValdToggleTime(v_pilotTimer) >= par_TP_EV_vald_toggle_min and
               decodeValdToggleTime(v_pilotTimer) <= par_TP_EV_vald_toggle_max and
               isStep2)
      {
        setverdict(pass, "Step 2 CM_VALIDATE.REQ is correct.");
        EVCC_Tester::tc_TT_match_sequence->stop();
        v_TT_EVSE_vald_toggle = decodeValdToggleTime(v_pilotTimer);
      }
      else
      {
        setverdict(fail, "Invalid message content was received from the SUT.");
      }
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            mw_CMN_CMN_CmValidateReq_003())))
    {
      setverdict(fail, "Result field is not set to 'Ready'. Matching process is considered as FAILED.");
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
            md_CMN_CMN_CmSlacParmReq_001(
                m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    {
      setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}), MATCH_ANY)))
    {
      // CM_ATTEN_CHAR.RSP messages will be ignored!
      // repeat;
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
    if (EVCC_Tester::tc_TT_match_sequence->timeout())
    {
      cnt = cnt + 1;
      SLOGI("TT_match_sequence timeout.");
      if (cnt > par_C_EV_match_retry)
      {
        setverdict(fail, "Repetition limit is reached. Matching process is considered as FAILED.");
      }
      else
      {
        SLOGI("A new CM_VALIDATE.CNF message will be sent.");
        EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
            md_CMN_CMN_CmValidateCnf_001(
                par_cmValidate_result_ready))); // to vc_sut_mac;
        EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
        // repeat;
      }
    }
    if (EVCC_Tester::tc_TT_EVSE_match_session->timeout())
    {
      setverdict(fail, "TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
    }
  }
  if (getverdict == pass)
  {
    // BCB toggle sequence detection
    EVCC_Tester::tc_TT_EVSE_vald_toggle->start(v_TT_EVSE_vald_toggle);
    f_EVCC_changeValidStateCondition(B, C);
    timer statetimer = (par_T_vald_state_duration_max + par_CMN_Transmission_Delay);
    statetimer.start();
    integer toggleCnt = 0;
    while (true)
    {
      if (a_EVCC_BCBToggleDetection(EVCC_Tester::pt_HAL_61851_Internal_Port, B))
      {
        statetimer.stop;
        toggleCnt = toggleCnt + 1;
        f_EVCC_changeValidStateCondition(B, C);
        // repeat;
      }
      if (a_EVCC_BCBToggleDetection(EVCC_Tester::pt_HAL_61851_Internal_Port, C))
      {
        statetimer.stop;
        f_EVCC_changeValidStateCondition(C, B);
        statetimer.start(par_T_vald_state_duration_max);
        // repeat;
      }
      if (EVCC_Tester::pt_HAL_61851_Internal_Port.receive())
      {
        setverdict(fail, "Received state has an invalid value.");
      }
      if (statetimer.timeout())
      {
        setverdict(fail, "The EVSE could not detect the corresponding toggle value within the maximal valid state duration.");
      }
      if (EVCC_Tester::tc_TT_EVSE_vald_toggle->timeout())
      {
        EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
        while (true)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive())
          {
            setverdict(fail, "The SUT did not stop the validation process with the current EVSE.");
          }
          if (EVCC_Tester::tc_TT_match_sequence->timeout())
          {
            setverdict(pass, "TT_match_sequence timeout. The SUT has stopped the validation process with the current EVSE.");
          }
        }
      }
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_006(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, hexstring v_resultCode)
{
  // runs on EVCC_Tester return VerdictValue
  MME v_requestMessage;
  integer cnt = 0;
  boolean isStep2 = false;
  float v_TT_EVSE_vald_toggle;
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            md_CMN_CMN_CmValidateReq_002(MATCH_ANY))))
    {
      //-> value v_requestMessage
      PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.cm_validate_req.vrVarField.pilot_timer;
      EVCC_Tester::tc_TT_EVSE_match_session->stop();
      if (v_pilotTimer == "00")
      {
        if (not isStep2)
        {
          setverdict(pass, "Step 1 CM_VALIDATE.REQ is correct.");
          isStep2 = true;
        }
        else
        {
          SLOGI("Step 2 CM_VALIDATE.REQ message contains timer field equal to zero. Step 1 CM_VALIDATE.CNF will be resent.");
        }
        EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
            md_CMN_CMN_CmValidateCnf_001(par_cmValidate_result_ready))); // to vc_sut_mac;
        EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
        // repeat;
      }
      else if (decodeValdToggleTime(v_pilotTimer) >= par_TP_EV_vald_toggle_min and
               decodeValdToggleTime(v_pilotTimer) <= par_TP_EV_vald_toggle_max and
               isStep2)
      {
        setverdict(pass, "Step 2 CM_VALIDATE.REQ is correct.");
        EVCC_Tester::tc_TT_match_sequence->stop();
        v_TT_EVSE_vald_toggle = decodeValdToggleTime(v_pilotTimer);
      }
      else
      {
        setverdict(fail, "Invalid message content was received from the SUT.");
      }
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            mw_CMN_CMN_CmValidateReq_003())))
    {
      setverdict(fail, "Result field is not set to 'Ready'. Matching process is considered as FAILED.");
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
            md_CMN_CMN_CmSlacParmReq_001(
                m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    {
      setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}), MATCH_ANY)))
    {
      // CM_ATTEN_CHAR.RSP messages will be ignored!
      // repeat;
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
    if (EVCC_Tester::tc_TT_match_sequence->timeout())
    {
      cnt = cnt + 1;
      SLOGI("TT_match_sequence timeout.");
      if (cnt > par_C_EV_match_retry)
      {
        setverdict(fail, "Repetition limit is reached. Matching process is considered as FAILED.");
      }
      else
      {
        SLOGI("A new CM_VALIDATE.CNF message will be sent.");
        EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
            md_CMN_CMN_CmValidateCnf_001(par_cmValidate_result_ready))); // to vc_sut_mac;
        EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
        // repeat;
      }
    }
    if (EVCC_Tester::tc_TT_EVSE_match_session->timeout())
    {
      setverdict(fail, "TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
    }
  }
  if (getverdict == pass)
  {
    // BCB toggle sequence detection
    EVCC_Tester::tc_TT_EVSE_vald_toggle->start(v_TT_EVSE_vald_toggle);
    f_EVCC_changeValidStateCondition(B, C);
    timer statetimer = (par_T_vald_state_duration_max + par_CMN_Transmission_Delay);
    statetimer.start();
    integer toggleCnt = 0;
    while (true)
    {
      if (a_EVCC_BCBToggleDetection(EVCC_Tester::pt_HAL_61851_Internal_Port, B))
      {
        statetimer.stop;
        toggleCnt = toggleCnt + 1;
        f_EVCC_changeValidStateCondition(B, C);
        // repeat;
      }
      if (a_EVCC_BCBToggleDetection(EVCC_Tester::pt_HAL_61851_Internal_Port, C))
      {
        statetimer.stop;
        f_EVCC_changeValidStateCondition(C, B);
        statetimer.start(par_T_vald_state_duration_max);
        // repeat;
      }
      if (EVCC_Tester::pt_HAL_61851_Internal_Port.receive())
      {
        setverdict(fail, "Received state has an invalid value.");
      }
      if (statetimer.timeout())
      {
        setverdict(fail, "The EVSE could not detect the corresponding toggle value within the maximal valid state duration.");
      }
      if (EVCC_Tester::tc_TT_EVSE_vald_toggle->timeout())
      {
        EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
            md_CMN_CMN_CmValidateCnf_002(int2hex(toggleCnt, 2), v_resultCode))); // to vc_sut_mac;
        EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
        while (true)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive())
          {
            setverdict(fail, "The SUT did not stop the validation process with the current EVSE.");
          }
          if (EVCC_Tester::tc_TT_match_sequence->timeout())
          {
            setverdict(pass, "TT_match_sequence timeout. The SUT has stopped the validation process with the current EVSE.");
          }
        }
      }
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_007(void)
{
  // runs on EVCC_Tester return VerdictValue
  MME v_requestMessage;
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            md_CMN_CMN_CmValidateReq_002(MATCH_ANY))))
    {
      //-> value v_requestMessage
      PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.cm_validate_req.vrVarField.pilot_timer;
      EVCC_Tester::tc_TT_EVSE_match_session->stop();
      if (v_pilotTimer == "00")
      {
        setverdict(pass, "Step 1 CM_VALIDATE.REQ is correct.");
        EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
        EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
            md_CMN_CMN_CmValidateCnf_001(
                par_cmValidate_result_notRequired))); // to vc_sut_mac;
        // repeat;
      }
      else
      {
        EVCC_Tester::tc_TT_match_sequence->stop();
        setverdict(pass, "Step 2 CM_VALIDATE.REQ was received. SUT has continued the validation process.");
      }
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            mw_CMN_CMN_CmValidateReq_003())))
    {
      setverdict(fail, "Result field is not set to 'Ready'. Matching process is considered as FAILED.");
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
            md_CMN_CMN_CmSlacParmReq_001(
                m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    {
      setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}), MATCH_ANY)))
    {
      // CM_ATTEN_CHAR.RSP messages will be ignored!
      // repeat;
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
    if (EVCC_Tester::tc_TT_match_sequence->timeout())
    {
      setverdict(fail, "TT_match_sequence timeout. The SUT has stopped the validation process.");
    }
    if (EVCC_Tester::tc_TT_EVSE_match_session->timeout())
    {
      setverdict(fail, "TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_008(void)
{
  // runs on EVCC_Tester return VerdictValue
  MME v_requestMessage;
  boolean v_isFirst = true;
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            md_CMN_CMN_CmValidateReq_002("00"))))
    {
      //-> value v_requestMessage
      if (v_isFirst)
      {
        EVCC_Tester::tc_TT_EVSE_match_session->stop();
        setverdict(pass, "Step 1 CM_VALIDATE.REQ is correct.");
        EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
            md_CMN_CMN_CmValidateCnf_001(
                par_cmValidate_result_notReady))); // to vc_sut_mac;
      }
      else
      {
        EVCC_Tester::tc_EVCC_ValidationRetry->stop();
        setverdict(pass, "Step 1 CM_VALIDATE.REQ is correct. SUT has retried the SLAC validation process after waiting for PIXIT_EVCC_CMN_ValidationRetry seconds.");
      }
      if (v_isFirst)
      {
        EVCC_Tester::tc_EVCC_ValidationRetry->start(PIXIT_EVCC_CMN_ValidationRetry +
                                                    (2.0 * par_CMN_Transmission_Delay));
        v_isFirst = false;
        // repeat;
      }
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            mw_CMN_CMN_CmValidateReq_003())))
    {
      setverdict(fail, "Result field is not set to 'Ready'. Matching process is considered as FAILED.");
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
            md_CMN_CMN_CmSlacParmReq_001(
                m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    {
      setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}), MATCH_ANY)))
    {
      // CM_ATTEN_CHAR.RSP messages will be ignored!
      // repeat;
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
    if (EVCC_Tester::tc_TT_EVSE_match_session->timeout())
    {
      setverdict(fail, "TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
    }
    if (EVCC_Tester::tc_EVCC_ValidationRetry->timeout())
    {
      setverdict(fail, "EVCC_ValidationRetry timeout. SUT has not retried the SLAC validation process after waiting for 'PIXIT_EVCC_CMN_ValidationRetry' seconds.");
    }
  }
  return EVCC_Tester::getverdict();
}
// SLAC Tester
VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_009(void)
{
  //  runs on SLAC_Tester return VerdictValue
  MME v_responseMessage;
  integer v_count;
  VerdictValue v_verdict;
  v_verdict = f_EVCC_CMN_TB_VTB_CmValidatePreCondition_001();
  if (v_verdict == pass)
  {
    v_count = 0;
    while (true)
    {
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
              m_CMN_CMN_CmValidateReq_001())))
      {
        //-> value v_responseMessage
        if (v_count > 0)
        {
          setverdict(pass, "CM_VALIDATE.REQ message was repeated.", v_count);
        }
        else
        {
          EVCC_Tester::tc_TT_EVSE_match_session->stop();
        }
        v_count = v_count + 1;
        EVCC_Tester::tc_TT_match_response->start(par_TT_match_response +
                                                 par_CMN_Transmission_Delay);
        if (v_count > par_C_EV_match_retry)
        {
          while (true)
          {
            if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                    md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
                    m_CMN_CMN_CmValidateReq_001())))
            {
              setverdict(fail, "CM_VALIDATE.REQ message was repeated, but v_count > par_C_EV_match_retry.");
            }
            if (EVCC_Tester::tc_TT_match_response->timeout())
            {
              setverdict(pass, "TT_match_response timeout. The total number of retries is reached, the Validation process shall be considered as FAILED.");
            }
          }
        }
        else
        {
          // repeat;
        }
      }
      if (EVCC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
      }
      if (EVCC_Tester::tc_TT_EVSE_match_session->timeout())
      {
        setverdict(fail, "TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
      }
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_010(hexstring v_resultCode)
{
  // runs on SLAC_Tester return VerdictValue
  MME v_requestMessage;
  VerdictValue v_verdict;
  v_verdict = f_EVCC_CMN_TB_VTB_CmValidatePreCondition_001();
  if (v_verdict == pass)
  {
    while (true)
    {
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
              md_CMN_CMN_CmValidateReq_002(MATCH_ANY))))
      {
        //-> value v_requestMessage
        PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.cm_validate_req.vrVarField.pilot_timer;
        EVCC_Tester::tc_TT_EVSE_match_session->stop();
        if (v_pilotTimer == "00")
        {
          setverdict(pass, "Step 1 CM_VALIDATE.REQ is correct.");
          EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
              md_CMN_CMN_CmValidateCnf_001(v_resultCode))); // to vc_sut_mac;
          EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
          // repeat;
        }
        else
        {
          EVCC_Tester::tc_TT_match_sequence->stop();
          setverdict(fail, "Step 2 CM_VALIDATE.REQ was received. The validation process with the current EVSE has to be stopped by the SUT before.");
        }
      }
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
              mw_CMN_CMN_CmValidateReq_003())))
      {
        setverdict(fail, "Result field is not set to 'Ready'. Matching process is considered as FAILED.");
      }
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
              md_CMN_CMN_CmSlacParmReq_001(
                  m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
      {
        setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
      }
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}), MATCH_ANY)))
      {
        // CM_ATTEN_CHAR.RSP messages will be ignored!
        // repeat;
      }
      if (EVCC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
      }
      if (EVCC_Tester::tc_TT_match_sequence->timeout())
      {
        setverdict(pass, "TT_match_sequence timeout. The SUT has stopped the validation process with the current EVSE.");
      }
      if (EVCC_Tester::tc_TT_EVSE_match_session->timeout())
      {
        setverdict(fail, "TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
      }
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_011(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  // runs on SLAC_Tester return VerdictValue
  MME v_requestMessage;
  integer cnt = 0;
  boolean isStep2 = false;
  float v_TT_EVSE_vald_toggle;
  VerdictValue v_verdict;
  v_verdict = f_EVCC_CMN_TB_VTB_CmValidatePreCondition_001();
  if (v_verdict == pass)
  {
    while (true)
    {
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
              md_CMN_CMN_CmValidateReq_002(MATCH_ANY))))
      {
        //-> value v_requestMessage
        PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.cm_validate_req.vrVarField.pilot_timer;
        EVCC_Tester::tc_TT_EVSE_match_session->stop();
        if (v_pilotTimer == "00")
        {
          if (not isStep2)
          {
            setverdict(pass, "Step 1 CM_VALIDATE.REQ is correct.");
            isStep2 = true;
          }
          else
          {
            SLOGI("Step 2 CM_VALIDATE.REQ message contains timer field equal to zero. Step 1 CM_VALIDATE.CNF will be resent.");
          }
          EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
              md_CMN_CMN_CmValidateCnf_001(
                  par_cmValidate_result_ready))); // to vc_sut_mac;
          EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
          // repeat;
        }
        else if (decodeValdToggleTime(v_pilotTimer) >= par_TP_EV_vald_toggle_min and
                 decodeValdToggleTime(v_pilotTimer) <= par_TP_EV_vald_toggle_max and
                 isStep2)
        {
          setverdict(pass, "Step 2 CM_VALIDATE.REQ is correct.");
          EVCC_Tester::tc_TT_match_sequence->stop();
          v_TT_EVSE_vald_toggle = decodeValdToggleTime(v_pilotTimer);
        }
        else
        {
          setverdict(fail, "Invalid message content was received from the SUT.");
        }
      }
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
              mw_CMN_CMN_CmValidateReq_003())))
      {
        setverdict(fail, "Result field is not set to 'Ready'. Matching process is considered as FAILED.");
      }
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
              md_CMN_CMN_CmSlacParmReq_001(
                  m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
      {
        setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
      }
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}), MATCH_ANY)))
      {
        // CM_ATTEN_CHAR.RSP messages will be ignored!
        // repeat;
      }
      if (EVCC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
      }
      if (EVCC_Tester::tc_TT_match_sequence->timeout())
      {
        cnt = cnt + 1;
        SLOGI("TT_match_sequence timeout.");
        if (cnt > par_C_EV_match_retry)
        {
          setverdict(fail, "Repetition limit is reached. Matching process is considered as FAILED.");
        }
        else
        {
          SLOGI("A new CM_VALIDATE.CNF message will be sent.");
          EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
              md_CMN_CMN_CmValidateCnf_001(
                  par_cmValidate_result_ready))); // to vc_sut_mac;
          EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
          // repeat;
        }
      }
      if (EVCC_Tester::tc_TT_EVSE_match_session->timeout())
      {
        setverdict(fail, "TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
      }
    }
    if (getverdict == pass)
    {
      // BCB toggle sequence detection
      EVCC_Tester::tc_TT_EVSE_vald_toggle->start(v_TT_EVSE_vald_toggle);
      f_EVCC_changeValidStateCondition(B, C);
      timer statetimer = (par_T_vald_state_duration_max +
                          par_CMN_Transmission_Delay);
      statetimer.start();
      integer toggleCnt = 0;
      while (true)
      {
        if (a_EVCC_BCBToggleDetection(EVCC_Tester::pt_HAL_61851_Internal_Port, B))
        {
          statetimer.stop;
          toggleCnt = toggleCnt + 1;
          f_EVCC_changeValidStateCondition(B, C);
          // repeat;
        }
        if (a_EVCC_BCBToggleDetection(EVCC_Tester::pt_HAL_61851_Internal_Port, C))
        {
          statetimer.stop;
          f_EVCC_changeValidStateCondition(C, B);
          statetimer.start(par_T_vald_state_duration_max);
          // repeat;
        }
        if (EVCC_Tester::pt_HAL_61851_Internal_Port.receive())
        {
          setverdict(fail, "Received state has an invalid value.");
        }
        if (statetimer.timeout())
        {
          setverdict(fail, "The EVSE could not detect the corresponding toggle value within the maximal valid state duration.");
        }
        if (EVCC_Tester::tc_TT_EVSE_vald_toggle->timeout())
        {
          EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
          while (true)
          {
            if (EVCC_Tester::pt_SLAC_Port->receive())
            {
              setverdict(fail, "The SUT did not stop the validation process with the current EVSE.");
            }
            if (EVCC_Tester::tc_TT_match_sequence->timeout())
            {
              setverdict(pass, "TT_match_sequence timeout. The SUT has stopped the validation process with the current EVSE.");
            }
          }
        }
      }
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_012(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, hexstring v_resultCode)
{
  // runs on SLAC_Tester return VerdictValue
  MME v_requestMessage;
  integer cnt = 0;
  boolean isStep2 = false;
  float v_TT_EVSE_vald_toggle;
  VerdictValue v_verdict;
  v_verdict = f_EVCC_CMN_TB_VTB_CmValidatePreCondition_001();
  if (v_verdict == pass)
  {
    while (true)
    {
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
              md_CMN_CMN_CmValidateReq_002(MATCH_ANY))))
      {
        //-> value v_requestMessage
        PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.cm_validate_req.vrVarField.pilot_timer;
        EVCC_Tester::tc_TT_EVSE_match_session->stop();
        if (v_pilotTimer == "00")
        {
          if (not isStep2)
          {
            setverdict(pass, "Step 1 CM_VALIDATE.REQ is correct.");
            isStep2 = true;
          }
          else
          {
            SLOGI("Step 2 CM_VALIDATE.REQ message contains timer field equal to zero. Step 1 CM_VALIDATE.CNF will be resent.");
          }
          EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
              md_CMN_CMN_CmValidateCnf_001(
                  par_cmValidate_result_ready))); // to vc_sut_mac;
          EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
          // repeat;
        }
        else if (decodeValdToggleTime(v_pilotTimer) >= par_TP_EV_vald_toggle_min and
                 decodeValdToggleTime(v_pilotTimer) <= par_TP_EV_vald_toggle_max and
                 isStep2)
        {
          setverdict(pass, "Step 2 CM_VALIDATE.REQ is correct.");
          EVCC_Tester::tc_TT_match_sequence->stop();
          v_TT_EVSE_vald_toggle = decodeValdToggleTime(v_pilotTimer);
        }
        else
        {
          setverdict(fail, "Invalid message content was received from the SUT.");
        }
      }
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
              mw_CMN_CMN_CmValidateReq_003())))
      {
        setverdict(fail, "Result field is not set to 'Ready'. Matching process is considered as FAILED.");
      }
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
              md_CMN_CMN_CmSlacParmReq_001(
                  m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
      {
        setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
      }
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}), MATCH_ANY)))
      {
        // CM_ATTEN_CHAR.RSP messages will be ignored!
        // repeat;
      }
      if (EVCC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
      }
      if (EVCC_Tester::tc_TT_match_sequence->timeout())
      {
        cnt = cnt + 1;
        SLOGI("TT_match_sequence timeout.");
        if (cnt > par_C_EV_match_retry)
        {
          setverdict(fail, "Repetition limit is reached. Matching process is considered as FAILED.");
        }
        else
        {
          SLOGI("A new CM_VALIDATE.CNF message will be sent.");
          EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
              md_CMN_CMN_CmValidateCnf_001(
                  par_cmValidate_result_ready))); // to vc_sut_mac;
          EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
          // repeat;
        }
      }
      if (EVCC_Tester::tc_TT_EVSE_match_session->timeout())
      {
        setverdict(fail, "TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
      }
    }
    if (getverdict == pass)
    {
      // BCB toggle sequence detection
      EVCC_Tester::tc_TT_EVSE_vald_toggle->start(v_TT_EVSE_vald_toggle);
      f_EVCC_changeValidStateCondition(B, C);
      timer statetimer = (par_T_vald_state_duration_max + par_CMN_Transmission_Delay);
      statetimer.start();
      integer toggleCnt = 0;
      while (true)
      {
        if (a_EVCC_BCBToggleDetection(EVCC_Tester::pt_HAL_61851_Internal_Port, B))
        {
          statetimer.stop;
          toggleCnt = toggleCnt + 1;
          f_EVCC_changeValidStateCondition(B, C);
          // repeat;
        }
        if (a_EVCC_BCBToggleDetection(EVCC_Tester::pt_HAL_61851_Internal_Port, C))
        {
          statetimer.stop;
          f_EVCC_changeValidStateCondition(C, B);
          statetimer.start(par_T_vald_state_duration_max);
          // repeat;
        }
        if (EVCC_Tester::pt_HAL_61851_Internal_Port.receive())
        {
          setverdict(fail, "Received state has an invalid value.");
        }
        if (statetimer.timeout())
        {
          setverdict(fail, "The EVSE could not detect the corresponding toggle value within the maximal valid state duration.");
        }
        if (EVCC_Tester::tc_TT_EVSE_vald_toggle->timeout())
        {
          EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
              md_CMN_CMN_CmValidateCnf_002(
                  int2hex(toggleCnt, 2),
                  v_resultCode))); // to vc_sut_mac;
          EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
          while (true)
          {
            if (EVCC_Tester::pt_SLAC_Port->receive())
            {
              setverdict(fail, "The SUT did not stop the validation process with the current EVSE.");
            }
            if (EVCC_Tester::tc_TT_match_sequence->timeout())
            {
              setverdict(pass, "TT_match_sequence timeout. The SUT has stopped the validation process with the current EVSE.");
            }
          }
        }
      }
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmValidate_013(HAL_61851_PwmMode_Type pwmMode)
{
  // runs on EVCC_Tester return VerdictValue
  MME v_requestMessage;
  boolean isStep2 = false;
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            md_CMN_CMN_CmValidateReq_002(MATCH_ANY))))
    {
      //-> value v_requestMessage
      PilotTimer_TYPE v_pilotTimer = v_requestMessage.mme_payload.payload.cm_validate_req.vrVarField.pilot_timer;
      EVCC_Tester::tc_TT_EVSE_match_session->stop();
      if (v_pilotTimer == "00")
      {
        if (not isStep2)
        {
          setverdict(pass, "Step 1 CM_VALIDATE.REQ is correct.");
          isStep2 = true;
        }
        else
        {
          setverdict(fail, "Step 2 CM_VALIDATE.REQ message contains timer field equal to zero and was not expected. CP State E/F should be detected before.");
          break;
        }
        // set error state
        f_EVCC_changeValidStateCondition(E, E);
        f_EVCC_setPwmMode(pwmMode);
        EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_CNF = "6079"}),
            md_CMN_CMN_CmValidateCnf_001(par_cmValidate_result_ready))); // to vc_sut_mac;
        EVCC_Tester::tc_TT_match_sequence->start(par_TT_match_sequence);
        // repeat;
      }
      else
      {
        setverdict(fail, "Step 2 CM_VALIDATE.REQ message was not expected. CP State E/F should be detected before.");
      }
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_VALIDATE_REQ = "6078"}),
            mw_CMN_CMN_CmValidateReq_003())))
    {
      setverdict(fail, "Result field is not set to 'Ready'. Matching process is considered as FAILED.");
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
            md_CMN_CMN_CmSlacParmReq_001(m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    {
      setverdict(inconc, "CM_SLAC_PARM.REQ message was received. New Matching process is started.");
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}), MATCH_ANY)))
    {
      // CM_ATTEN_CHAR.RSP messages will be ignored!
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
    if (EVCC_Tester::tc_TT_EVSE_match_session->timeout())
    {
      setverdict(fail, "TT_EVSE_match_session timeout. Matching process shall be considered as FAILED.");
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmValidatePreCondition_001(void)
{
  //  runs on SLAC_Tester
  // return VerdictValue
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
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
            md_CMN_CMN_CmSlacParmReq_001(
                m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
    {
      //-> value v_responseMessage
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
    if (EVCC_Tester::tc_TT_EVSE_SLAC_init->timeout())
    {
      setverdict(fail, "TT_EVSE_SLAC_init timeout. SECC assumes that no SLAC will be performed.");
    }
  }
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_START_ATTEN_CHAR_IND = "606A"}),
            md_CMN_CMN_CmStartAttenCharInd_001(
                m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY, MATCH_ANY,
                "01", MATCH_ANY, vc_RunID))))
    {
      //-> value v_responseMessage
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
        if (!v_firstSound)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_MNBC_SOUND_IND = "6076"}),
                  md_CMN_CMN_CmMnbcSoundInd_001(m_CMN_CMN_SlacPayloadHeader_001(),
                                                int2hex(v_countDecrement, 2), vc_RunID, MATCH_ANY))))
          {
            v_countDecrement = v_countDecrement - 1;
            // repeat;
          }
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_PROFILE_IND = "6086"}),
                md_EVCC_CMN_CmAttenProfileInd_001(
                    vc_sut_mac, MATCH_ANY, MATCH_SKIP))))
        {
          //-> value v_responseMessage
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
                md_CMN_CMN_CmSlacParmReq_001(
                    m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
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
      v_attenuation_list = m_EVCC_CMN_atten_list_002();
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
          md_EVCC_CMN_CmAttenCharInd_001(
              m_CMN_CMN_SlacPayloadHeader_001(), vc_sut_mac,
              vc_RunID, vc_Num_sounds, v_attenuation_list)))
          to vc
              _sut_mac;
      while (true)
      {
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_ATTEN_CHAR_RSP = "606F"}),
                                                                      md_CMN_CMN_CmAttenCharRsp_001(
                                                                          m_CMN_CMN_SlacPayloadHeader_001(),
                                                                          md_CMN_CMN_Acvarfield_001(
                                                                              vc_sut_mac, vc_RunID)))))
        {
          setverdict(pass, "CM_ATTEN_CHAR.RSP is correct.");
          v_repetition = false;
          EVCC_Tester::tc_TT_match_response->stop();
          EVCC_Tester::tc_TT_EVSE_match_session->start(par_TT_EVSE_match_session);
        }
        if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
                md_CMN_CMN_CmSlacParmReq_001(
                    m_CMN_CMN_SlacPayloadHeader_001(), MATCH_ANY))))
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
}