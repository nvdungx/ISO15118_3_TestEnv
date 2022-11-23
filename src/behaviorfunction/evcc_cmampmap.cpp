#include "behaviorfunction/evcc_cmampmap.hpp"
#include "template/template.hpp"
#include "datatype.hpp"
#include "slac_type.hpp"

// import from Timer_15118_3 all;
// import from Pics_15118_3 all;
// import from Templates_CMN_CmAmpMap all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from Templates_CMN_CmSlacMatch all;
// import from ComponentsAndPorts all;
// import from DataStructure_SLAC all;
// import from Services_HAL_61851 all;
// import from DataStructure_HAL_61851 all;
// import from Templates_CMN_CmSlacParm all;
// import from TTlibrary_Logging all;
// import from TestBehavior_EVCC_SDP all;
#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)
namespace TestLib
{
VerdictValue f_EVCC_CMN_TB_VTB_CmAmpMap_001(VerdictValue v_vct)
{
  // runs on EVCC_Tester
  // return VerdictValue
  boolean v_repetition = true;
  integer v_counter = 0;
  while (v_repetition)
  {
    EVCC_Tester::tc_TT_match_response->start(par_TT_match_response);
    v_counter = v_counter + 1;
    EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
        md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_REQ = "601C"}),
        m_CMN_CMN_CmAmpMapReq_001())); // to vc_sut_mac;
    while (true)
    {
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_CNF = "601D"}),
              md_CMN_CMN_CmAmpMapCnf_001("00"))))
      {
        setverdict(pass, "CM_AMP_MAP.CNF is correct.");
        v_repetition = false;
        EVCC_Tester::tc_TT_match_response->stop();
      }
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_CNF = "601D"}),
              md_CMN_CMN_CmAmpMapCnf_001("01"))))
      {
        setverdict(v_vct, "The SUT could not perform the Amplitude map exchange.");
        v_repetition = false;
        EVCC_Tester::tc_TT_match_response->stop();
      }
      if (EVCC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(v_vct, "Invalid message type or content was received.");
        v_repetition = false;
        EVCC_Tester::tc_TT_match_response->stop();
      }
      if (EVCC_Tester::tc_TT_match_response->timeout())
      {
        SLOGI("TT_match_response timeout.");
        if (v_counter mod(par_C_EV_match_retry + 1) == 0)
        {
          setverdict(v_vct, "The SUT did not response to the CM_AMP_MAP.REQ message.");
          v_repetition = false;
        }
        else
        {
          SLOGI("A new CM_AMP_MAP.REQ message will be sent.");
        }
      }
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmAmpMap_002(VerdictValue v_vct)
{
  // runs on EVCC_Tester
  // return VerdictValue
  MME v_requestMessage;
  EVCC_Tester::tc_TT_amp_map_exchange->start(par_TT_amp_map_exchange);
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_REQ = "601C"}),
            md_CMN_CMN_CmAmpMapReq_002(MATCH_ANY, MATCH_ANY))))
    {
      //-> value v_requestMessage
      EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_CNF = "601D"}),
          md_CMN_CMN_CmAmpMapCnf_001("00"))); // to vc_sut_mac;
      Amlen_TYPE v_amlen = v_requestMessage.mme_payload.payload.cm_amp_map_req.amlen;
      ListofAmdata_TYPE v_listAmdata = v_requestMessage.mme_payload.payload.cm_amp_map_req.listAmdata;
      setverdict(pass, "CM_AMP_MAP.REQ is correct.");
      EVCC_Tester::tc_TT_amp_map_exchange->stop();
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(v_vct, "Invalid message type or content was received.");
    }
    if (EVCC_Tester::tc_TT_amp_map_exchange->timeout())
    {
      setverdict(v_vct, "No Amplitude Map exchange was performed by the SUT.");
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmAmpMap_003()
{
  // runs on EVCC_Tester return VerdictValue
  integer v_count = 0;
  EVCC_Tester::tc_TT_amp_map_exchange->start(par_TT_amp_map_exchange);
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_REQ = "601C"}),
            md_CMN_CMN_CmAmpMapReq_002(MATCH_ANY, MATCH_ANY))))
    {
      if (v_count > 0)
      {
        setverdict(pass, "CM_AMP_MAP.REQ message was repeated.", v_count);
      }
      else
      {
        EVCC_Tester::tc_TT_amp_map_exchange->stop();
      }
      v_count = v_count + 1;
      EVCC_Tester::tc_TT_match_response->start(par_TT_match_response);
      if (v_count > par_C_EV_match_retry)
      {
        while (true)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_REQ = "601C"}),
                  md_CMN_CMN_CmAmpMapReq_002(MATCH_ANY, MATCH_ANY))))
          {
            setverdict(fail, "CM_AMP_MAP.REQ message was repeated, but v_count > par_C_EV_match_retry.");
          }
          if (EVCC_Tester::pt_SLAC_Port->receive())
          {
            setverdict(fail, "Invalid message type or content was received.");
          }
          if (EVCC_Tester::tc_TT_match_response->timeout())
          {
            setverdict(pass, "TT_match_response timeout. The total number of retries is reached, the Matching process shall be considered as FAILED.");
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
    if (EVCC_Tester::tc_TT_amp_map_exchange->timeout())
    {
      setverdict(fail, "No Amplitude Map exchange was performed by the SUT.");
    }
    if (EVCC_Tester::tc_TT_match_response->timeout())
    {
      setverdict(fail, "The SUT did not retransmit the CM_AMP_MAP.REQ message.");
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmAmpMap_004()
{
  // runs on EVCC_Tester return VerdictValue
  integer v_count = 0;
  EVCC_Tester::tc_TT_amp_map_exchange->start(par_TT_amp_map_exchange);
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_REQ = "601C"}),
            md_CMN_CMN_CmAmpMapReq_002(MATCH_ANY, MATCH_ANY))))
    {
      if (v_count > 0)
      {
        setverdict(pass, "CM_AMP_MAP.REQ message was repeated.", v_count);
      }
      else
      {
        EVCC_Tester::tc_TT_amp_map_exchange->stop();
      }
      v_count = v_count + 1;
      EVCC_Tester::tc_TT_match_response->start(par_TT_match_response);
      // send invalid CM_AMP_MAP.CNF message
      EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
          md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_CNF = "601D"}),
          md_CMN_CMN_CmAmpMapCnf_001("FF"))); // to vc_sut_mac;
      if (v_count > par_C_EV_match_retry)
      {
        while (true)
        {
          if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
                  md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_REQ = "601C"}),
                  md_CMN_CMN_CmAmpMapReq_002(MATCH_ANY, MATCH_ANY))))
          {
            setverdict(fail, "CM_AMP_MAP.REQ message was repeated, but v_count > par_C_EV_match_retry.");
          }
          if (EVCC_Tester::pt_SLAC_Port->receive())
          {
            setverdict(fail, "Invalid message type or content was received.");
          }
          if (EVCC_Tester::tc_TT_match_response->timeout())
          {
            setverdict(pass, "TT_match_response timeout. The total number of retries is reached, the Matching process shall be considered as FAILED.");
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
    if (EVCC_Tester::tc_TT_amp_map_exchange->timeout())
    {
      setverdict(fail, "No Amplitude Map exchange was performed by the SUT.");
    }
    if (EVCC_Tester::tc_TT_match_response->timeout())
    {
      setverdict(fail, "The SUT did not retransmit the CM_AMP_MAP.REQ message.");
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmAmpMap_005()
{
  // runs on EVCC_Tester return VerdictValue
  boolean v_repetition = true;
  integer v_counter = 0;
  while (v_repetition)
  {
    EVCC_Tester::tc_TT_match_response->start(par_TT_match_response);
    v_counter = v_counter + 1;
    // send invalid CM_AMP_MAP.REQ message
    EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
        md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_REQ = "601C"}),
        md_CMN_CMN_CmAmpMapReq_003("0000"))); // to vc_sut_mac;
    while (true)
    {
if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_CNF = "601D"}),
md_CMN_CMN_CmAmpMapCnf_001(MATCH_ANY))))
{
setverdict(fail, "Received CM_AMP_MAP.CNF message was not expected.");
v_repetition = false;
EVCC_Tester::tc_TT_match_response->stop();
}
if (EVCC_Tester::pt_SLAC_Port->receive())
{
setverdict(fail, "Invalid message type or content was received.");
v_repetition = false;
EVCC_Tester::tc_TT_match_response->stop();
}
if (EVCC_Tester::tc_TT_match_response->timeout())
{
SLOGI("TT_match_response timeout.");
setverdict(pass, "The SUT did not response to the invalid CM_AMP_MAP.REQ message.");
if (v_counter mod(par_C_EV_match_retry + 1) == 0)
{
  v_repetition = false;
}
else
{
  SLOGI("A new invalid CM_AMP_MAP.REQ message will be sent.");
}
}
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmAmpMap_006()
{
  // runs on EVCC_Tester return VerdictValue
  boolean v_repetition = true;
  integer v_counter = 0;
  while (v_repetition)
  {
    EVCC_Tester::tc_TT_match_response->start(par_TT_match_response);
    v_counter = v_counter + 1;
    EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
        md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_REQ = "601C"}),
        m_CMN_CMN_CmAmpMapReq_001())); // to vc_sut_mac;
    while (true)
    {
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_CNF = "601D"}),
              md_CMN_CMN_CmAmpMapCnf_001("00"))))
      {
        setverdict(pass, "CM_AMP_MAP.CNF is correct.");
        EVCC_Tester::tc_TT_match_response->stop();
        if (v_counter > 1)
        {
          v_repetition = false;
        }
      }
      if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
              md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_CNF = "601D"}),
              md_CMN_CMN_CmAmpMapCnf_001("01"))))
      {
        setverdict(fail, "The SUT could not perform the Amplitude map exchange.");
        v_repetition = false;
        EVCC_Tester::tc_TT_match_response->stop();
      }
      if (EVCC_Tester::pt_SLAC_Port->receive())
      {
        setverdict(fail, "Invalid message type or content was received.");
        v_repetition = false;
        EVCC_Tester::tc_TT_match_response->stop();
      }
      if (EVCC_Tester::tc_TT_match_response->timeout())
      {
        setverdict(fail, "The SUT did not response to the CM_AMP_MAP.REQ message.");
        v_repetition = false;
      }
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmAmpMap_007()
{
  // runs on EVCC_Tester return VerdictValue
  integer v_counter = 0;
  EVCC_Tester::tc_TT_match_response->start(par_TT_match_response);
  for (integer i = 0; i < 3; i = i + 1)
  {
    EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
        md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_REQ = "601C"}),
        m_CMN_CMN_CmAmpMapReq_001())); // to vc_sut_mac;
  }
  while (true)
  {
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_CNF = "601D"}),
            md_CMN_CMN_CmAmpMapCnf_001("00"))))
    {
      setverdict(pass, "CM_AMP_MAP.CNF is correct.");
      v_counter = v_counter + 1;
      EVCC_Tester::tc_TT_match_response->stop();
      EVCC_Tester::tc_TT_match_response->start(par_TT_match_response);
      if (v_counter < 3)
      {
        // repeat;
      }
    }
    if (EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_AMP_MAP_CNF = "601D"}),
            md_CMN_CMN_CmAmpMapCnf_001("01"))))
    {
      setverdict(fail, "The SUT could not perform the Amplitude map exchange.");
      EVCC_Tester::tc_TT_match_response->stop();
    }
    if (EVCC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(fail, "Invalid message type or content was received.");
      EVCC_Tester::tc_TT_match_response->stop();
    }
    if (EVCC_Tester::tc_TT_match_response->timeout())
    {
      setverdict(fail, "The SUT did not response to the CM_AMP_MAP.REQ message.");
    }
  }
  return EVCC_Tester::getverdict();
}
VerdictValue f_EVCC_CMN_TB_VTB_CmAmpMap_008()
{
  // runs on EVCC_Tester return VerdictValue
  EVCC_Tester::tc_V2G_SECC_CommunicationSetup_Timer->start;
  f_EVCC_CMN_TB_VTB_SDP_001(MATCH_ANY, fail);
  return EVCC_Tester::getverdict();
}
}