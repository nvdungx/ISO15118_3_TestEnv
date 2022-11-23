#include "behaviorfunction/secc_plclinkstatus.hpp"
#include "template/template.hpp"

// import from Timer_15118_3 all;
// import from Pics_15118_3 all;
// import from Pixit_15118_3 all;
// import from Pics_15118 all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from Templates_CMN_CmSlacMatch all;
// import from ComponentsAndPorts all;
// import from DataStructure_SLAC all;
// import from Services_PLCLinkStatus all;
// import from Services_HAL_61851 all;
// import from Templates_CMN_CmSlacParm all;
// import from TestBehavior_SECC_CmSlacParm all;
// import from TestBehavior_SECC_CmSetKey all;
// import from LibFunctions_15118_3 all;
// import from Timer_15118 all;
// import from Pixit_15118 all;
// import from DataStructure_SDP all;
// import from Pixit_15118_2 all;
// import from TestBehavior_SECC_SDP all;
// import from Templates_CMN_CmNwStats all;
#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)
namespace TestLib
{
namespace TestBehavior_SECC_PLCLinkStatus
{
VerdictValue f_SECC_CMN_TB_VTB_PLCLinkStatus_001(VerdictValue v_vct)
{
  // runs on SECC_Tester
  // return VerdictValue
  VerdictValue v_verdict;
  v_verdict = f_SECC_getPLCLinkEstablishment(v_vct);
  if (v_verdict == pass)
  {
    setverdict(pass, "The data link was established by the SUT.");
  }
  else
  {
    setverdict(v_vct, "The data link could not be established by the SUT.");
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_PLCLinkStatus_002(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  // return VerdictValue
  // runs on SECC_Tester
  VerdictValue v_verdict;
  // set state A
  f_SECC_changeValidStateCondition(invalid);
  f_SECC_changeValidFrequencyRange(0, 0);
  f_SECC_changeValidDutyCycleRange(100, 100);
  deactivate(vc_Default_IEC_61851_ListenerBehavior);
  f_SECC_setState(A, v_HAL_61851_Listener);
  v_verdict = f_SECC_getPLCLinkTermination(par_TP_match_leave + par_CMN_Transmission_Delay, fail);
  if (v_verdict == pass)
  {
    setverdict(pass, "The data link was terminated by the SUT.");
  }
  else
  {
    setverdict(fail, "The data link did not terminated by the SUT.");
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_PLCLinkStatus_003(void)
{
  //  runs on SECC_Tester
  // return VerdictValue
  vc_RunID = f_randomHexStringGen(16);
  SECC_Tester::tc_TT_match_response->start(par_TT_match_response);
  SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
      md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_REQ = "6064"}),
      md_CMN_CMN_CmSlacParmReq_001(
          m_CMN_CMN_SlacPayloadHeader_001(),
          vc_RunID))); // to cc_eth_broadcast;
  while (true)
  {
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_PARM_CNF = "6065"}),
            md_CMN_CMN_CmSlacParmCnf_001(par_testSystem_mac, m_CMN_CMN_SlacPayloadHeader_001(), vc_RunID))))
    {
      setverdict(fail, "CM_SLAC_PARM message was not expected, no SLAC messages should be send in state 'Matched'.");
    }
    if (SECC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
    if (SECC_Tester::tc_TT_match_response->timeout())
    {
      setverdict(pass, "TT_match_response timeout. SUT did not respond to a CM_SLAC_PARM.REQ message, if it is in state 'Matched'.");
    }
    if (SECC_Tester::tc_TT_matching_repetition->timeout())
    {
      SLOGI("TT_matching_repetition timeout - No new matching process can be started, if the current matching process fails.");
      // repeat;
    }
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_PLCLinkStatus_004(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  // runs on SECC_Tester
  // return VerdictValue
  VerdictValue v_verdict = pass;
  v_HAL_61851_Listener.stop;
  v_HAL_61851_Listener.start(f_SECC_HAL61851Listener(true));
  if (PICS_CMN_CMN_ChargingMode == aC)
  {
    f_SECC_changeValidDutyCycleRange(10, 96);
    vc_validDutyCycleLowerBound2 = 10;
    vc_validDutyCycleUpperBound2 = 96;
  }
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
  f_SECC_getPLCLinkEstablishmentAfterSleepMode(pass, fail, fail);
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_PLCLinkStatus_005(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  // runs on SECC_Tester
  // return VerdictValue
  VerdictValue v_verdict = pass;
  v_HAL_61851_Listener.stop;
  v_HAL_61851_Listener.start(f_SECC_HAL61851Listener(true));
  f_SECC_setIsConfirmationFlagDC();
  if (PICS_CMN_CMN_ChargingMode == aC)
  {
    f_SECC_changeValidDutyCycleRange(10, 96);
    vc_validDutyCycleLowerBound2 = 10;
    vc_validDutyCycleUpperBound2 = 96;
  }
  v_verdict = f_SECC_confirmDutyCycle(v_HAL_61851_Listener, (PICS_CMN_CMN_WakeUp - PIXIT_CMN_CMN_WakeUp + 5.0), fail);
  if (getverdict != pass)
  {
    SLOGI("The SUT did not initiate a wake-up within 'PICS_CMN_CMN_WakeUp'.");
  }
  f_SECC_getPLCLinkEstablishmentAfterSleepMode(pass, fail, fail);
  if (getverdict == pass)
  {
    Security_TYPE v_security = cc_hexTls;
    if (PICS_CMN_CMN_IdentificationMode == eIM and
        PIXIT_SECC_CMN_TLS == false)
    {
      v_security = cc_hexTcp;
    }
    v_verdict = f_SECC_CMN_TB_VTB_SDP_001(v_security, fail);
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_PLCLinkStatus_006(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  // runs on SECC_Tester
  // return VerdictValue
  VerdictValue v_verdict = pass;
  v_HAL_61851_Listener.stop;
  v_HAL_61851_Listener.start(f_SECC_HAL61851Listener(true));
  if (v_verdict == pass)
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
    SECC_Tester::tc_T_conn_max_comm->start(par_T_conn_max_comm);
    f_SECC_changeValidStateCondition(EorF);
    f_SECC_changeValidFrequencyRange(0, 0);
    f_SECC_changeValidDutyCycleRange(0, 0);
    f_SECC_setIsConfirmationFlagVoltage();
    f_SECC_getPLCLinkEstablishmentAfterSleepMode(fail, pass, fail);
    timer statetimer = (par_T_conn_max_comm - tc_T_conn_max_comm.read) + par_CMN_HAL_Timeout;
    f_SECC_confirmState(EorF, v_HAL_61851_Listener, statetimer);
    if (getverdict != pass)
    {
      setverdict(fail, "The SUT did not apply CP State E or F.");
    }
    else
    {
      SECC_Tester::tc_T_step_EF->start(par_T_step_EF_min - cc_offset);
      while (true)
      {
        if (SECC_Tester::tc_T_step_EF->timeout())
        {
        }
        if (SECC_Tester::pt_SLAC_Port->receive())
        {
          setverdict(fail, "Invalid message type or content was received.");
        }
      }
      f_SECC_changeValidStateCondition(B);
      f_SECC_setIsConfirmationFlagDC();
      f_SECC_changeValidFrequencyRange(980, 1020);
      if (PICS_CMN_CMN_ChargingMode == aC)
      {
        f_SECC_changeValidDutyCycleRange(10, 96);
        vc_validDutyCycleLowerBound1 = 3;
        vc_validDutyCycleUpperBound1 = 7;
        vc_validDutyCycleLowerBound2 = 10;
        vc_validDutyCycleUpperBound2 = 96;
      }
      SECC_Tester::tc_T_step_EF->start(par_T_step_EF_max -
                                        (par_T_step_EF_min - cc_offset));
      while (true)
      {
        if (SECC_Tester::tc_T_step_EF->timeout())
        {
        }
        if (a_SECC_DCDetection(SECC_Tester::pt_HAL_61851_Internal_Port,
                                vc_validDutyCycleLowerBound1,
                                vc_validDutyCycleUpperBound1,
                                vc_validDutyCycleLowerBound2,
                                vc_validDutyCycleUpperBound2))
        {
          vc_confirmDC = true;
        }
        if (SECC_Tester::pt_SLAC_Port->receive())
        {
          setverdict(fail, "Invalid message type or content was received.");
        }
      }
      if (not vc_confirmDC)
      {
        v_verdict = f_SECC_confirmDutyCycle(v_HAL_61851_Listener, par_T_conn_max_comm, fail);
      }
    }
  }
  if (getverdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacParm_001(fail);
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_PLCLinkStatus_007(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  // runs on SECC_Tester
  // return VerdictValue
  VerdictValue v_verdict = pass;
  sleep(par_CMN_waitForConnectionLoss);
  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(0, 0);
  f_SECC_changeValidDutyCycleRange(100, 100);
  // generate new Nid and Nmk
  vc_Nmk = f_randomHexStringGen(32);
  vc_Nid = fx_generateNID(vc_Nmk);
  v_verdict = f_SECC_CMN_TB_VTB_CmSetKey_001(true);
  if (v_verdict == pass)
  {
    v_verdict = f_SECC_getPLCLinkTermination(par_TP_match_leave, fail);
  }
  if (v_verdict == pass)
  {
    v_verdict = f_SECC_confirmDutyCycle(v_HAL_61851_Listener, par_T_conn_max_comm, fail);
    f_SECC_changeValidStateCondition(EorF);
    f_SECC_changeValidDutyCycleRange(0, 0);
    f_SECC_setIsConfirmationFlagVoltage();
  }
  if (v_verdict == pass)
  {
    timer statetimer = par_CMN_HAL_Timeout;
    v_verdict = f_SECC_confirmState(EorF, v_HAL_61851_Listener, statetimer);
  }
  if (getverdict != pass)
  {
    setverdict(fail, "The SUT did not apply CP State E or F.");
  }
  else
  {
    SECC_Tester::tc_T_step_EF->start(par_T_step_EF_min - cc_offset);
    while (true)
    {
      if (SECC_Tester::tc_T_step_EF->timeout())
      {
      }
      if (a_SECC_processPLCLinkNotifications_001())
      {
      }
      if (SECC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
      }
    }
    f_SECC_changeValidStateCondition(B);
    f_SECC_setIsConfirmationFlagDC();
    vc_validDutyCycleLowerBound1 = 3;
    vc_validDutyCycleUpperBound1 = 7;
    if (PICS_CMN_CMN_ChargingMode == aC)
    {
      f_SECC_changeValidDutyCycleRange(10, 100);
      vc_validDutyCycleLowerBound2 = 10;
      vc_validDutyCycleUpperBound2 = 100;
    }
    else
    {
      f_SECC_changeValidDutyCycleRange(100, 100);
      vc_validDutyCycleLowerBound2 = 100;
      vc_validDutyCycleUpperBound2 = 100;
    }
    SECC_Tester::tc_T_step_EF->start(par_T_step_EF_max - (par_T_step_EF_min - cc_offset));
    while (true)
    {
      if (SECC_Tester::tc_T_step_EF->timeout())
        ;
      if (a_SECC_DCDetection(SECC_Tester::pt_HAL_61851_Internal_Port,
                              vc_validDutyCycleLowerBound1,
                              vc_validDutyCycleUpperBound1,
                              vc_validDutyCycleLowerBound2,
                              vc_validDutyCycleUpperBound2))
      {
        vc_confirmDC = true;
      }
      if (SECC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
      }
    }
    if (not vc_confirmDC)
    {
      v_verdict = f_SECC_confirmDutyCycle(v_HAL_61851_Listener, par_T_conn_max_comm, fail);
    }
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_PLCLinkStatus_008(void)
{
  // runs on SECC_Tester
  // return VerdictValue
  SECC_Tester::tc_TP_match_leave->start(par_TP_match_leave);
  while (true)
  {
    if (SECC_Tester::tc_TP_match_leave->timeout())
    {
    }
    if (SECC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
  }
  SECC_Tester::tc_TT_link_status_response->start;
  SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(md_CMN_CMN_SlacMmeCmnHeader_001({CM_NW_STATS_REQ = "6048"}),
                                                          md_CMN_CMN_CmNwStatsReq_001())); // to par_testSystem_plc_node_mac;
  while (true)
  {
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_NW_STATS_CNF = "6049"}),
            md_CMN_CMN_CmNwStatsCnf_001())))
    {
      setverdict(fail, "The SUTs node was detected in the current logical network.");
    }
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_NW_STATS_CNF = "6049"}),
            md_CMN_CMN_CmNwStatsCnf_002())))
    {
      setverdict(pass, "The SUTs node has left the current logical network.");
    }
    if (SECC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
    }
    if (SECC_Tester::tc_TT_link_status_response->timeout())
    {
      setverdict(fail, "CM_NW_STATS timeout.");
    }
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_PLCLinkStatus_009(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  // runs on SECC_Tester
  // return VerdictValue
  VerdictValue v_verdict = pass;
  hexstring v_Nmk_old;
  hexstring v_Nid_old;
  v_Nmk_old = vc_Nmk;
  v_Nid_old = vc_Nid;
  sleep(par_CMN_waitForConnectionLoss);
  v_HAL_61851_Listener.stop;
  v_HAL_61851_Listener.start(f_SECC_HAL61851Listener(false));
  // generate new Nid and Nmk
  vc_Nmk = f_randomHexStringGen(32);
  vc_Nid = fx_generateNID(vc_Nmk);
  v_verdict = f_SECC_CMN_TB_VTB_CmSetKey_001(true);
  if (v_verdict == pass)
  {
    v_verdict = f_SECC_getPLCLinkTermination(par_TP_match_leave, fail);
  }
  // set old Nid and Nmk
  if (v_verdict == pass)
  {
    vc_Nmk = vc_Nmk;
    vc_Nid = vc_Nid;
    v_verdict = f_SECC_CMN_TB_VTB_CmSetKey_001(true);
  }
  if (v_verdict == pass)
  {
    f_SECC_checkLeavingLogicalNetwork();
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_PLCLinkStatus_010(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  // runs on SECC_Tester
  // return VerdictValue
  VerdictValue v_verdict = pass;
  v_HAL_61851_Listener.stop;
  v_HAL_61851_Listener.start(f_SECC_HAL61851Listener(true));
  f_SECC_setIsConfirmationFlagDC();
  if (PICS_CMN_CMN_ChargingMode == aC)
  {
    f_SECC_changeValidDutyCycleRange(10, 96);
    vc_validDutyCycleLowerBound2 = 10;
    vc_validDutyCycleUpperBound2 = 96;
  }
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
  SECC_Tester::tc_T_conn_max_comm->start(par_T_conn_max_comm);
  if (getverdict == pass)
  {
    v_verdict = f_SECC_confirmDutyCycle(v_HAL_61851_Listener, (par_T_conn_max_comm - tc_T_conn_max_comm.read), fail);
  }
  if (getverdict == pass)
  {
    Security_TYPE v_security = cc_hexTls;
    if (PICS_CMN_CMN_IdentificationMode == eIM and PIXIT_SECC_CMN_TLS == false)
    {
      v_security = cc_hexTcp;
    }
    v_verdict = f_SECC_CMN_TB_VTB_SDP_001(v_security, fail);
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_PLCLinkStatus_011(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  // runs on SECC_Tester
  // return VerdictValue
  VerdictValue v_verdict = pass;
  sleep(par_CMN_waitForConnectionLoss);
  f_SECC_changeValidStateCondition(EorF);
  f_SECC_changeValidDutyCycleRange(0, 0);
  f_SECC_setIsConfirmationFlagVoltage();
  // generate new Nid and Nmk
  vc_Nmk = f_randomHexStringGen(32);
  vc_Nid = fx_generateNID(vc_Nmk);
  v_verdict = f_SECC_CMN_TB_VTB_CmSetKey_001(true);
  if (v_verdict == pass)
  {
    v_verdict = f_SECC_getPLCLinkTermination(par_TP_match_leave, fail);
  }
  if (v_verdict == pass)
  {
    timer statetimer = par_CMN_HAL_Timeout;
    v_verdict = f_SECC_confirmState(EorF, v_HAL_61851_Listener, statetimer);
  }
  if (getverdict != pass)
  {
    setverdict(fail, "The SUT did not apply CP State E or F.");
  }
  else
  {
    SECC_Tester::tc_T_step_EF->start(par_T_step_EF_min - cc_offset);
    while (true)
    {
      if (SECC_Tester::tc_T_step_EF->timeout())
      {
      }
      if (a_SECC_processPLCLinkNotifications_001())
      {
      }
      if (SECC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
      }
    }
    f_SECC_changeValidStateCondition(B);
    f_SECC_setIsConfirmationFlagDC();
    vc_validDutyCycleLowerBound1 = 3;
    vc_validDutyCycleUpperBound1 = 7;
    if (PICS_CMN_CMN_ChargingMode == aC)
    {
      f_SECC_changeValidDutyCycleRange(10, 100);
      vc_validDutyCycleLowerBound2 = 10;
      vc_validDutyCycleUpperBound2 = 100;
    }
    else
    {
      f_SECC_changeValidDutyCycleRange(100, 100);
      vc_validDutyCycleLowerBound2 = 100;
      vc_validDutyCycleUpperBound2 = 100;
    }
    SECC_Tester::tc_T_step_EF->start(par_T_step_EF_max -
                                      (par_T_step_EF_min - cc_offset));
    while (true)
    {
      if (SECC_Tester::tc_T_step_EF->timeout())
        ;
      if (a_SECC_DCDetection(SECC_Tester::pt_HAL_61851_Internal_Port,
                              vc_validDutyCycleLowerBound1,
                              vc_validDutyCycleUpperBound1,
                              vc_validDutyCycleLowerBound2,
                              vc_validDutyCycleUpperBound2))
      {
        vc_confirmDC = true;
      }
      if (SECC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
      }
    }
    if (not vc_confirmDC)
    {
      v_verdict = f_SECC_confirmDutyCycle(v_HAL_61851_Listener, par_T_conn_max_comm, fail);
    }
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_CMN_TB_VTB_PLCLinkStatus_012(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  // runs on SECC_Tester
  // return VerdictValue
  VerdictValue v_verdict = pass;
  v_HAL_61851_Listener.stop;
  v_HAL_61851_Listener.start(f_SECC_HAL61851Listener(true));
  f_SECC_setIsConfirmationFlagDC();
  if (PICS_CMN_CMN_ChargingMode == aC)
  {
    f_SECC_changeValidDutyCycleRange(10, 96);
    vc_validDutyCycleLowerBound2 = 10;
    vc_validDutyCycleUpperBound2 = 96;
  }
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
  SECC_Tester::tc_T_conn_max_comm->start(par_T_conn_max_comm);
  if (getverdict == pass)
  {
    while (true)
    {
      if (SECC_Tester::tc_T_step_X1->timeout())
      {
        SLOGI("The SUT did not signal B1/B2 transition earlier than 'par_SECC_T_step_X1'.");
        // repeat;
      }
      if (a_SECC_DCDetection(SECC_Tester::pt_HAL_61851_Internal_Port,
                              vc_validDutyCycleLowerBound1,
                              vc_validDutyCycleUpperBound1,
                              vc_validDutyCycleLowerBound2,
                              vc_validDutyCycleUpperBound2))
      {
        if (tc_T_step_X1.running())
        {
          setverdict(fail, "The SUT has signaled B1/B2 transition earlier than 'par_SECC_T_step_X1'.");
        }
      }
      if (SECC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
      }
      if (SECC_Tester::tc_T_conn_max_comm->timeout())
      {
        setverdict(fail, "The SUT could not signal the corresponding duty cycle.");
      }
    }
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_AC_TB_VTB_PLCLinkStatus_001(void)
{
  // runs on SECC_Tester
  // return VerdictValue
  timer t1;
  float v_waitForEim = 1.0;
  while (not vc_eimDone and getverdict == pass)
  {
    SLOGI("Wait for user interaction.");
    t1.start(v_waitForEim);
    while (true)
    {
      if (t1.timeout())
      {
      }
    }
  }
  if (getverdict == pass)
  {
    sleep(par_SECC_change_to_Nominal);
    f_SECC_getDcNominalStatus();
  }
  return SECC_Tester::getverdict();
}
VerdictValue f_SECC_AC_TB_VTB_PLCLinkStatus_002(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  // runs on SECC_Tester
  // return VerdictValue
  VerdictValue v_verdict = pass;
  sleep(par_CMN_waitForConnectionLoss);
  // generate new Nid and Nmk
  vc_Nmk = f_randomHexStringGen(32);
  vc_Nid = fx_generateNID(vc_Nmk);
  v_verdict = f_SECC_CMN_TB_VTB_CmSetKey_001(true);
  if (v_verdict == pass)
  {
    v_verdict = f_SECC_getPLCLinkTermination(par_TP_match_leave,
                                              fail);
  }
  if (getverdict == pass)
  {
    f_SECC_CMN_TB_VTB_CmSlacParm_001(fail);
  }
  return SECC_Tester::getverdict();
}
}
}