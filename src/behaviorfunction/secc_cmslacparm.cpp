#include "behaviorfunction/secc_cmslacparm.hpp"
#include "management/pics_cfg.hpp"
#include "management/pixit_cfg.hpp"
#include "management/timer_cfg.hpp"
#include "supported/libfunctions.hpp"
#include "datatype.hpp"
#include "slac_type.hpp"

// module TestBehavior_SECC_CmSlacParm {
// import from Templates_CMN_CmSlacParm all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from ComponentsAndPorts all;
// import from Services_HAL_61851 all;
// import from Services_PLCLinkStatus all;
namespace TestLib {

using namespace Pics_15118;
using namespace Pics_15118_3;
using namespace Pixit_15118_3;
using namespace DataStructure_SLAC;
using namespace DataStructure_HAL_61851;
using namespace Timer_15118::Timer_par_15118;
using namespace Timer_15118_3::Timer_par_15118_3;
using namespace LibFunctions_15118_3::generalFunctions;

VerdictValue f_SECC_CMN_TB_VTB_CmSlacParm_001(VerdictValue v_vct) {


  MME v_responseMessage;
  boolean v_repetition = true;
  integer v_count1 = 0;
  integer v_count2 = 0;
  MACAddress_TYPE v_sut_mac;
  SECC_Tester::vc_macAddresList = m_CMN_CMN_EmptyMacAddressList();
  SECC_Tester::vc_RunID = f_randomHexStringGen(16);
  while (v_repetition)
  {
    SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
    v_count1 = v_count1 + 1;
    SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
                                             md_CMN_CMN_CmSlacParmReq_001(
                                                 m_CMN_CMN_SlacPayloadHeader_001(), SECC_Tester::vc_RunID)), cc_eth_broadcast)
    while (true)
    {
      if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
              md_CMN_CMN_CmSlacParmCnf_001(par_testSystem_mac,
                                           m_CMN_CMN_SlacPayloadHeader_001(), SECC_Tester::vc_RunID))))
      {
        SECC_Tester::setverdict(pass, "CM_SLAC_PARM is correct.");
        SECC_Tester::vc_macAddresList.macAddressList[v_count2] = v_sut_mac;
        v_count2 = v_count2 + 1;
        SECC_Tester::vc_Num_sounds = v_responseMessage.mme_payload.payload.cm_slac_parm_cnf.num_sounds;
        SECC_Tester::vc_Time_out = v_responseMessage.mme_payload.payload.cm_slac_parm_cnf.time_out;
        repeat;
      }
      if (a_SECC_processPLCLinkNotifications_001())
      {
        break;
      }
      if (SECC_Tester::pt_SLAC_Port->receive())
      {
        SECC_Tester::setverdict(v_vct, "Invalid message type or content was received.");
        v_repetition = false;
      }
      if (SECC_Tester::tc_TT_match_response->timeout)
      {
        if (sizeof(SECC_Tester::vc_macAddresList.macAddressList) > 0)
        {
          SECC_Tester::tc_TP_match_sequence->start(par_TP_match_sequence);
          v_repetition = false;
        }
        else if (v_count1 mod(par_C_EV_match_retry + 1) == 0)
        {
          log("The Matching process is considered as FAILED.");
          if (tc_TT_matching_repetition.running)
          {
            log("TT_matching_repetition is still running. "
                "A new Matching process is started.");
            v_count1 = 0;
          }
          else
          {
            SECC_Tester::setverdict(v_vct, "TT_matching_repetition has expired. "
                                           "No new Matching process will be started.");
            v_repetition = false;
          }
        }
      }
    }
  }
  return SECC_Tester::getverdict();
}

VerdictValue f_SECC_CMN_TB_VTB_CmSlacParm_002(
    std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener,
    SLAC_Header &v_slac_Header, boolean v_sendInvalid)
{
  MME v_responseMessage;
  boolean v_repetition = true;
  SECC_Tester::vc_RunID = f_randomHexStringGen(16);
  SECC_Tester::tc_TT_EVSE_SLAC_init->start(par_TT_EVSE_SLAC_init_min);
  if (v_sendInvalid)
  {
    SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
        md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
        md_CMN_CMN_CmSlacParmReq_001(v_slac_Header, SECC_Tester::vc_RunID)), cc_eth_broadcast)
  }
  while (true)
  {
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
            md_CMN_CMN_CmSlacParmCnf_001(par_testSystem_mac,
                                         m_CMN_CMN_SlacPayloadHeader_001(), SECC_Tester::vc_RunID))))
    {
      SECC_Tester::setverdict(fail, "Invalid CM_SLAC_PARM.REQ message was not ignored.");
      SECC_Tester::tc_TT_EVSE_SLAC_init->stop();
    }
    if (a_SECC_processPLCLinkNotifications_001())
    {
      break;
    }
    if (SECC_Tester::pt_SLAC_Port->receive())
    {
      SECC_Tester::setverdict(fail, "Invalid message type or content was received.");
    }
    if (SECC_Tester::tc_TT_EVSE_SLAC_init->timeout)
    {
      v_HAL_61851_Listener.stop;
      v_HAL_61851_Listener.start(f_SECC_HAL61851Listener(false));
      f_SECC_changeValidStateCondition(valid_Matching);
      f_SECC_changeValidFrequencyRange(0, 0);
      f_SECC_changeValidDutyCycleRange(100, 100);
      SECC_Tester::tc_TT_EVSE_SLAC_init->start(par_TT_EVSE_SLAC_init_max - par_TT_EVSE_SLAC_init_min);
      while (true)
      {
        if (SECC_Tester::tc_TT_EVSE_SLAC_init->timeout)
        {
          break;
        }
      }
      SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
      SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
          md_CMN_CMN_CmSlacParmReq_001(
              m_CMN_CMN_SlacPayloadHeader_001(), SECC_Tester::vc_RunID)), cc_eth_broadcast)
      while (true)
      {
        if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),MATCH_ANY)))
        {
          SECC_Tester::setverdict(fail, "CM_SLAC_PARM.CNF was sent from the SUT although "
                                        "the timer TT_EVSE_SLAC_init should have "
                                        "been expired.");
          SECC_Tester::tc_TT_match_response->stop();
        }
        if (a_SECC_processPLCLinkNotifications_001())
        {
          break;
        }
        if (SECC_Tester::pt_SLAC_Port->receive())
        {
          SECC_Tester::setverdict(fail, "Invalid message type or content was received.");
        }
        if (SECC_Tester::tc_TT_match_response->timeout)
        {
          SECC_Tester::setverdict(pass, "TT_match_response timeout. "
                                        "CM_SLAC_PARM.CNF was not sent from the SUT "
                                        "because the timer TT_EVSE_SLAC_init is expired.");
        }
      }
    }
  }
  return SECC_Tester::getverdict();
}

VerdictValue f_SECC_CMN_TB_VTB_CmSlacParm_003(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener) {


  SECC_Tester::vc_RunID = f_randomHexStringGen(16);
  sleep(1.0);
  f_SECC_changeValidStateCondition(invalid);
  f_SECC_changeValidFrequencyRange(0, 0);
  f_SECC_changeValidDutyCycleRange(100, 100);
  deactivate(SECC_Tester::vc_Default_IEC_61851_ListenerBehavior);
  f_SECC_setState(A, v_HAL_61851_Listener);
  SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
  SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
                                           md_CMN_CMN_CmSlacParmReq_001(
                                               m_CMN_CMN_SlacPayloadHeader_001(), SECC_Tester::vc_RunID)), cc_eth_broadcast)
  while (true)
  {
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
            md_CMN_CMN_CmSlacParmCnf_001(par_testSystem_mac,
                                         m_CMN_CMN_SlacPayloadHeader_001(), SECC_Tester::vc_RunID))))
    {
      SECC_Tester::setverdict(fail, "CM_SLAC_PARM.CNF message was not expected."
                                    "CP State A should be detected before.");
    }
    if (a_SECC_processPLCLinkNotifications_001())
    {
      break;
    }
    if (SECC_Tester::pt_SLAC_Port->receive())
    {
      SECC_Tester::setverdict(fail, "Invalid message type or content was received.");
    }
    if (SECC_Tester::tc_TT_match_response->timeout)
    {
      SECC_Tester::setverdict(pass, "TT_match_response timer has expired, "
                                    "the Matching process was terminated by the SUT.");
    }
  }
  return SECC_Tester::getverdict();
}

VerdictValue f_SECC_CMN_TB_VTB_CmSlacParm_004(void) {


  MME v_responseMessage;
  boolean v_repetition = true;
  integer v_count1 = 0;
  integer v_count2 = 0;
  MACAddress_TYPE v_sut_mac;
  SECC_Tester::tc_T_conn_max_comm->start;
  SECC_Tester::vc_macAddresList = m_CMN_CMN_EmptyMacAddressList();
  SECC_Tester::vc_RunID = f_randomHexStringGen(16);
  while (v_repetition)
  {
    SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
    v_count1 = v_count1 + 1;
    SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
                                             md_CMN_CMN_CmSlacParmReq_001(
                                                 m_CMN_CMN_SlacPayloadHeader_001(), SECC_Tester::vc_RunID)), cc_eth_broadcast)
    while (true)
    {
      if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
              md_CMN_CMN_CmSlacParmCnf_001(par_testSystem_mac,
                                           m_CMN_CMN_SlacPayloadHeader_001(), SECC_Tester::vc_RunID))))
      {
        SECC_Tester::setverdict(pass, "CM_SLAC_PARM is correct.");
        SECC_Tester::vc_macAddresList.macAddressList[v_count2] = v_sut_mac;
        v_count2 = v_count2 + 1;
        SECC_Tester::vc_Num_sounds = v_responseMessage.mme_payload.payload.cm_slac_parm_cnf.num_sounds;
        SECC_Tester::vc_Time_out = v_responseMessage.mme_payload.payload.cm_slac_parm_cnf.time_out;
        repeat;
      }
      if (a_SECC_processPLCLinkNotifications_001())
      {
        break;
      }
      if (SECC_Tester::pt_SLAC_Port->receive())
      {
        SECC_Tester::setverdict(fail, "Invalid message type or content was received.");
        v_repetition = false;
      }
      if (SECC_Tester::tc_TT_match_response->timeout)
      {
        if (sizeof(SECC_Tester::vc_macAddresList.macAddressList) > 0)
        {
          SECC_Tester::tc_TP_match_sequence->start(par_TP_match_sequence);
          v_repetition = false;
        }
        else if (v_count1 mod(par_C_EV_match_retry + 1) == 0)
        {
          log("The Matching process is considered as FAILED.");
          if (tc_TT_matching_repetition.running)
          {
            log("TT_matching_repetition is still running. "
                "A new Matching process is started.");
            v_count1 = 0;
          }
          else
          {
            SECC_Tester::setverdict(fail, "TT_matching_repetition has expired. "
                                          "No new Matching process will be started.");
            v_repetition = false;
          }
        }
      }
      if (SECC_Tester::tc_T_conn_max_comm->timeout)
      {
        SECC_Tester::setverdict(fail, "T_conn_max_comm has expired. "
                                      "The SUT was not ready for communication "
                                      "within 'T_conn_max_comm' after wakeup by plug-in");
      }
    }
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_CmSlacParm_005(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener) {


  MME v_responseMessage;
  MACAddress_TYPE v_sut_mac;
  f_SECC_setIsConfirmationFlagDC();
  f_SECC_confirmDutyCycle(v_HAL_61851_Listener, par_T_conn_max_comm, fail);
  SECC_Tester::vc_macAddresList = m_CMN_CMN_EmptyMacAddressList();
  SECC_Tester::vc_RunID = f_randomHexStringGen(16);
  SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
  SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
                                           md_CMN_CMN_CmSlacParmReq_001(
                                               m_CMN_CMN_SlacPayloadHeader_001(), SECC_Tester::vc_RunID)), cc_eth_broadcast)
  while (true)
  {
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
            md_CMN_CMN_CmSlacParmCnf_001(par_testSystem_mac,
                                         m_CMN_CMN_SlacPayloadHeader_001(), SECC_Tester::vc_RunID))))
    {
      SECC_Tester::setverdict(pass, "CM_SLAC_PARM is correct.");
    }
    if (a_SECC_processPLCLinkNotifications_001())
    {
      break;
    }
    if (SECC_Tester::pt_SLAC_Port->receive())
    {
      SECC_Tester::setverdict(fail, "Invalid message type or content was received.");
    }
    if (SECC_Tester::tc_TT_match_response->timeout)
    {
      SECC_Tester::setverdict(fail, "TT_match_response timeout. "
                                    "The SUT did not respond to CM_SLAC_PARM.REQ message "
                                    "after 5% duty cycle detection.");
    }
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_AC_TB_VTB_CmSlacParm_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener) {


  if (!SECC_Tester::vc_confirmState)
  {
    timer statetimer = par_CMN_HAL_Timeout;
    f_SECC_confirmState(EorF, v_HAL_61851_Listener, statetimer);
    if (SECC_Tester::getverdict() == pass)
    {
      SECC_Tester::tc_T_step_EF->start(par_T_step_EF_min - cc_offset);
    }
  }
  if (SECC_Tester::getverdict() != pass)
  {
    SECC_Tester::setverdict(fail, "The SUT did not apply CP State E or F.");
  }
  else
  {
    while (true)
    {
      if (SECC_Tester::tc_T_step_EF->timeout)
      {
        break;
      }
      if (a_SECC_processPLCLinkNotifications_001())
      {
        break;
      }
      if (SECC_Tester::pt_SLAC_Port->receive())
      {
        SECC_Tester::setverdict(fail, "Invalid message type or content was received.");
      }
    }
    f_SECC_changeValidStateCondition(B);
    f_SECC_changeValidFrequencyRange(980, 1020);
    f_SECC_changeValidDutyCycleRange(10, 96);
    SECC_Tester::vc_validDutyCycleLowerBound1 = 10;
    SECC_Tester::vc_validDutyCycleUpperBound1 = 96;
    SECC_Tester::vc_validDutyCycleLowerBound2 = 10;
    SECC_Tester::vc_validDutyCycleUpperBound2 = 96;
    f_SECC_setIsConfirmationFlagDC();
    SECC_Tester::tc_T_step_EF->start(par_T_step_EF_max - (par_T_step_EF_min - cc_offset));
    while (true)
    {
      if (SECC_Tester::tc_T_step_EF->timeout)
      {
        break;
      }
      if (a_SECC_DCDetection(SECC_Tester::pt_HAL_61851_Internal_Port,
                             SECC_Tester::vc_validDutyCycleLowerBound1,
                             SECC_Tester::vc_validDutyCycleUpperBound1,
                             SECC_Tester::vc_validDutyCycleLowerBound2,
                             SECC_Tester::vc_validDutyCycleUpperBound2))
      {
        SECC_Tester::vc_confirmDC = true;
      }
      if (a_SECC_processPLCLinkNotifications_001())
      {
        break;
      }
      if (SECC_Tester::pt_SLAC_Port->receive())
      {
        SECC_Tester::setverdict(fail, "Invalid message type or content was received.");
      }
    }
    if (!SECC_Tester::vc_confirmDC)
    {
      f_SECC_confirmDutyCycle(v_HAL_61851_Listener, par_T_conn_max_comm, fail);
    }
    if (SECC_Tester::getverdict() == pass)
    {
      SECC_Tester::setverdict(pass, "The EVSE could signal a nominal duty cycle.");
    }
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_AC_TB_VTB_CmSlacParm_002(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener) {


  integer v_count = 1;
  SECC_Tester::tc_TP_EVSE_SLAC_init->start(par_TT_EVSE_SLAC_init_min - cc_offset);
  while (true)
  {
    if (SECC_Tester::tc_TP_EVSE_SLAC_init->timeout)
    {
      break;
    }
    if (a_SECC_processPLCLinkNotifications_001())
    {
      break;
    }
    if (SECC_Tester::pt_SLAC_Port->receive())
    {
      SECC_Tester::setverdict(fail, "Invalid message type or content was received.");
    }
  }
  f_SECC_changeValidStateCondition(EorF);
  f_SECC_changeValidFrequencyRange(0, 0);
  f_SECC_changeValidDutyCycleRange(0, 0);
  f_SECC_setIsConfirmationFlagVoltage();
  SECC_Tester::tc_TP_EVSE_SLAC_init->start(par_TT_EVSE_SLAC_init_max -
                             (par_TT_EVSE_SLAC_init_min - cc_offset));
  while (true)
  {
    if (SECC_Tester::tc_TP_EVSE_SLAC_init->timeout)
    {
      break;
    }
    if (a_SECC_EFDetection(SECC_Tester::pt_HAL_61851_Internal_Port, EorF))
    {
      SECC_Tester::vc_confirmState = true;
      SECC_Tester::tc_T_step_EF->start(par_T_step_EF_min - cc_offset);
    }
    if (a_SECC_processPLCLinkNotifications_001())
    {
      break;
    }
    if (SECC_Tester::pt_SLAC_Port->receive())
    {
      SECC_Tester::setverdict(fail, "Invalid message type or content was received.");
    }
  }
  while ((v_count <= par_C_sequ_retry) and (SECC_Tester::getverdict() == pass))
  {
    if (!SECC_Tester::vc_confirmState)
    {
      timer statetimer = par_CMN_HAL_Timeout;
      f_SECC_confirmState(EorF, v_HAL_61851_Listener, statetimer);
      SECC_Tester::tc_T_step_EF->start(par_T_step_EF_min - cc_offset);
    }
    SECC_Tester::vc_confirmState = false;
    if (SECC_Tester::getverdict() == pass)
    {
      while (true)
      {
        if (SECC_Tester::tc_T_step_EF->timeout)
        {
          break;
        }
        if (a_SECC_processPLCLinkNotifications_001())
        {
          break;
        }
        if (SECC_Tester::pt_SLAC_Port->receive())
        {
          SECC_Tester::setverdict(fail, "Invalid message type or content was received.");
        }
      }
      f_SECC_changeValidStateCondition(B);
      f_SECC_changeValidFrequencyRange(980, 1020);
      f_SECC_changeValidDutyCycleRange(3, 7);
      SECC_Tester::tc_T_step_EF->start(par_T_step_EF_max - (par_T_step_EF_min - cc_offset));
      while (true)
      {
        if (SECC_Tester::tc_T_step_EF->timeout)
        {
          break;
        }
        if (a_SECC_EFDetection(SECC_Tester::pt_HAL_61851_Internal_Port, EorF))
        {
          SECC_Tester::vc_confirmState = true;
          SECC_Tester::tc_TP_EVSE_SLAC_init->start(par_TT_EVSE_SLAC_init_min - cc_offset);
        }
        if (a_SECC_processPLCLinkNotifications_001())
        {
          break;
        }
        if (SECC_Tester::pt_SLAC_Port->receive())
        {
          SECC_Tester::setverdict(fail, "Invalid message type or content was received.");
        }
      }
      if (!SECC_Tester::vc_confirmState)
      {
        f_SECC_setIsConfirmationFlagDC();
        f_SECC_confirmDutyCycle(v_HAL_61851_Listener, par_T_conn_max_comm, fail);
        SECC_Tester::tc_TP_EVSE_SLAC_init->start(par_TT_EVSE_SLAC_init_min - cc_offset);
      }
      SECC_Tester::vc_confirmState = false;
      v_count = v_count + 1;
      while (true)
      {
        if (SECC_Tester::tc_TP_EVSE_SLAC_init->timeout)
        {
          break;
        }
        if (a_SECC_processPLCLinkNotifications_001())
        {
          break;
        }
        if (SECC_Tester::pt_SLAC_Port->receive())
        {
          SECC_Tester::setverdict(fail, "Invalid message type or content was received.");
        }
      }
      f_SECC_changeValidFrequencyRange(0, 0);
      if (v_count == par_C_sequ_retry)
      {
        f_SECC_changeValidDutyCycleRange(100, 100);
        SECC_Tester::vc_validDutyCycleLowerBound1 = 100;
        SECC_Tester::vc_validDutyCycleUpperBound1 = 100;
        SECC_Tester::vc_validDutyCycleLowerBound2 = 100;
        SECC_Tester::vc_validDutyCycleUpperBound2 = 100;
        f_SECC_setIsConfirmationFlagDC();
      }
      else
      {
        f_SECC_changeValidDutyCycleRange(0, 0);
        f_SECC_changeValidStateCondition(EorF);
        f_SECC_setIsConfirmationFlagVoltage();
      }
      SECC_Tester::tc_TP_EVSE_SLAC_init->start(par_TT_EVSE_SLAC_init_max -
                                 (par_TT_EVSE_SLAC_init_min - cc_offset));
      while (true)
      {
        if (SECC_Tester::tc_TP_EVSE_SLAC_init->timeout)
        {
          break;
        }
        if (a_SECC_EFDetection(SECC_Tester::pt_HAL_61851_Internal_Port, EorF))
        {
          SECC_Tester::vc_confirmState = true;
          SECC_Tester::tc_T_step_EF->start(par_T_step_EF_min - cc_offset);
        }
        if (a_SECC_processPLCLinkNotifications_001())
        {
          break;
        }
        if (SECC_Tester::pt_SLAC_Port->receive())
        {
          SECC_Tester::setverdict(fail, "Invalid message type or content was received.");
        }
      }
    }
  }
  if (!SECC_Tester::vc_confirmState)
  {
    f_SECC_confirmDutyCycle(v_HAL_61851_Listener, par_T_conn_max_comm, fail);
  }
  if (SECC_Tester::getverdict() == pass)
  {
    SECC_Tester::setverdict(pass, "The SUT has initiated an oscillator shutdown "
                                  "after the repetition of 2 fallback sequences (5%).");
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_AC_TB_VTB_CmSlacParm_003(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener) {


  f_SECC_changeValidStateCondition(valid_Matching);
  f_SECC_changeValidDutyCycleRange(10, 96);
  SECC_Tester::vc_validDutyCycleLowerBound1 = 10;
  SECC_Tester::vc_validDutyCycleUpperBound1 = 96;
  SECC_Tester::vc_validDutyCycleLowerBound2 = 10;
  SECC_Tester::vc_validDutyCycleUpperBound2 = 96;
  f_SECC_setState(B, v_HAL_61851_Listener);
  SECC_Tester::tc_TT_matching_repetition->start(par_TT_matching_repetition);
  f_SECC_setIsConfirmationFlagDC();
  f_SECC_confirmDutyCycle(v_HAL_61851_Listener, par_T_conn_max_comm, fail);
  if (SECC_Tester::getverdict() != pass)
  {
    SECC_Tester::setverdict(fail, "No nominal duty cycle could be detected.");
  }
  return SECC_Tester::getverdict();
}
}