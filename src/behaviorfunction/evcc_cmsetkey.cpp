#include "behaviorfunction/evcc_cmsetkey.hpp"

// import from Timer_15118_3 all;
// import from Pics_15118_3 all;
// import from Templates_CMN_CmSetKey all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from ComponentsAndPorts all;
// import from DataStructure_SLAC all;
// import from Services_PLCLinkStatus all;
// import from Timer_15118 all;
namespace TestLib {
VerdictValue f_EVCC_CMN_TB_VTB_CmSetKey_001() runs on EVCC_Tester return VerdictValue {
timer t1 = par_CMN_setKey;
t1.start;
EVCC_Tester::pt_SLAC_Port->send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SET_KEY_REQ = "6008"}),
md_CMN_CMN_CmSetKeyReq_001(vc_Nid, vc_Nmk)))
to par_testSystem_plc_node_mac;
while(true) {
[]EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SET_KEY_CNF = "6009"}),
mdw_CMN_CMN_CmSetKeyCnf_001("01"))) {
setverdict(pass,"CM_SET_KEY is correct.");
}
[]EVCC_Tester::pt_SLAC_Port->receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SET_KEY_CNF = "6009"}),
mdw_CMN_CMN_CmSetKeyCnf_001("00"))) {
setverdict(inconc,"CM_SET_KEY is incorrect. The PLC node could not set the key.");
}
[] a_EVCC_processPLCLinkNotifications_001();
[] EVCC_Tester::pt_SLAC_Port->receive {
setverdict(inconc, "Invalid message type or content was received.");
}
[] t1.timeout {
setverdict(inconc,"CM_SET_KEY timeout.");
}
}
return EVCC_Tester::getverdict();
}
}