#include "behaviorfunction/secc_cmsetkey.hpp"
#include "template/template.hpp"

// import from Timer_15118_3 all;
// import from Pics_15118_3 all;
// import from Templates_CMN_CmSetKey all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from ComponentsAndPorts all;
// import from DataStructure_SLAC all;
// import from Timer_15118 all;
// import from Services_PLCLinkStatus all;
#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)
namespace TestLib
{
namespace TestBehavior_SECC_CmSetKey
{
VerdictValue f_SECC_CMN_TB_VTB_CmSetKey_001(boolean useTimer)
{
  // runs on SECC_Tester
  // return VerdictValue
  timer t1 = par_CMN_setKey;
  if (useTimer)
  {
    t1.start();
  }
  SECC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
      md_CMN_CMN_SlacMmeCmnHeader_001({CM_SET_KEY_REQ = "6008"}),
      md_CMN_CMN_CmSetKeyReq_001(vc_Nid, vc_Nmk))); // to par_testSystem_plc_node_mac;
  while (true)
  {
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SET_KEY_CNF = "6009"}),
            mdw_CMN_CMN_CmSetKeyCnf_001("01"))))
    {
      setverdict(pass, "CM_SET_KEY is correct.");
    }
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SLAC_MATCH_CNF = "607D"}), MATCH_ANY)))
    {
      // repeat;
    }
    if (SECC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
            md_CMN_CMN_SlacMmeCmnHeader_001({CM_SET_KEY_CNF = "6009"}),
            mdw_CMN_CMN_CmSetKeyCnf_001("00"))))
    {
      setverdict(inconc, "CM_SET_KEY is incorrect. The PLC node could not set the key.");
    }
    if (a_SECC_processPLCLinkNotifications_001())
    {
    }
    if (SECC_Tester::pt_SLAC_Port->receive())
    {
      setverdict(inconc, "Invalid message type or content was received.");
    }
    if (SECC_Tester::tc_TT_match_join->timeout())
    {
      setverdict(inconc, "CM_SET_KEY timeout.");
    }
    if (useTimer == true)
    {
      if (t1.timeout())
      {
        setverdict(inconc, "CM_SET_KEY timeout.");
      }
    }
  }
  return SECC_Tester::getverdict();
}
}
}