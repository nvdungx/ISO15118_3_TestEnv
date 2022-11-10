#include "behaviorfunction/secc_cmsetkey.hpp"
// import from Timer_15118_3 all;
// import from Pics_15118_3 all;
// import from Templates_CMN_CmSetKey all;
// import from Templates_CMN_SlacManagementMessageEntry all;
// import from ComponentsAndPorts all;
// import from DataStructure_SLAC all;
// import from Timer_15118 all;
// import from Services_PLCLinkStatus all;
namespace TestLib {
function f_SECC_CMN_TB_VTB_CmSetKey_001(in boolean useTimer) runs on SECC_Tester
return verdicttype {
timer t1 = par_CMN_setKey;
if(useTimer) {
t1.start;
}
pt_SLAC_Port.send(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SET_KEY_REQ = "6008"}),
md_CMN_CMN_CmSetKeyReq_001(vc_Nid, vc_Nmk)))
to par_testSystem_plc_node_mac;
alt {
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SET_KEY_CNF = "6009"}),
mdw_CMN_CMN_CmSetKeyCnf_001("01"))) {
setverdict(pass,"CM_SET_KEY is correct.");
}
[] pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SLAC_MATCH_CNF = '607D'H}),?)) {
repeat;
}
[]pt_SLAC_Port.receive(md_CMN_CMN_SlacMme_001(
md_CMN_CMN_SlacMmeCmnHeader_001({
CM_SET_KEY_CNF = "6009"}),
mdw_CMN_CMN_CmSetKeyCnf_001("00"))) {
setverdict(inconc,"CM_SET_KEY is incorrect. " &
"The PLC node could not set the key.");
}
[] a_SECC_processPLCLinkNotifications_001();
[] pt_SLAC_Port.receive {
setverdict(inconc, "Invalid message type or content was received.");
}
[] tc_TT_match_join.timeout {
setverdict(inconc,"CM_SET_KEY timeout.");
}
[useTimer == true] t1.timeout {
setverdict(inconc,"CM_SET_KEY timeout.");
}
}
return getverdict;
}
}