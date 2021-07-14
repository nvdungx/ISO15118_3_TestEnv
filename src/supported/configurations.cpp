module Configurations_15118_3 {
import from Services_HAL_61851 all;
import from ComponentsAndPorts all;
import from LibFunctions_15118_3 { group generalFunctions; }
import from Pics_15118 all;
// ::::::::::::::::::::::: Config Functions :::::::::::::::::::::::::
function f_SECC_CMN_PR_InitConfiguration_SLAC_001(out HAL_61851_Listener v_HAL_61851_Listener,
SystemSECC v_SystemSECC) runs on SECC_Tester {
map(mtc:pt_SLAC_Port, v_SystemSECC:pt_SLAC_Port);
v_HAL_61851_Listener := HAL_61851_Listener.create("IEC 61851 Listener") alive;
map(mtc:pt_HAL_61851_Port, v_SystemSECC:pt_HAL_61851_Port);
map(v_HAL_61851_Listener:pt_HAL_61851_Listener_Port,
v_SystemSECC:pt_HAL_61851_Listener_Port);
connect(mtc:pt_HAL_61851_Internal_Port, v_HAL_61851_Listener:pt_HAL_61851_Internal_Port);
v_HAL_61851_Listener.start(f_SECC_HAL61851Listener(false));
activate(a_CMN_IEC61851ListenerBehavior(pt_HAL_61851_Internal_Port));
}
function f_SECC_CMN_PR_InitConfiguration_SLAC_002(out HAL_61851_Listener v_HAL_61851_Listener,
out SLAC_Tester2 v_SLAC_Tester2,
out SLAC_Tester3 v_SLAC_Tester3,
out SLAC_Tester4 v_SLAC_Tester4,
out SLAC_Tester5 v_SLAC_Tester5,
SystemSECC systemSECC) runs on SECC_Tester {
var hexstring emptyMacAddress := '000000000000'H;
map(mtc:pt_SLAC_Port, systemSECC:pt_SLAC_Port);
if(par_slac_node2_mac != emptyMacAddress) {
v_SLAC_Tester2 := SLAC_Tester2.create("Slac Tester 2") alive;
map(v_SLAC_Tester2:pt_SLAC_Port, systemSECC:pt_SLAC_Port) param (par_slac_node2_mac);
}
else {log("MAC address of Slac node 2 is empty.");}
if(par_slac_node3_mac != emptyMacAddress) {
v_SLAC_Tester3 := SLAC_Tester3.create("Slac Tester 3") alive;
map(v_SLAC_Tester3:pt_SLAC_Port, systemSECC:pt_SLAC_Port) param (par_slac_node3_mac);
}
else {log("MAC address of Slac node 3 is empty.");}
if(par_slac_node4_mac != emptyMacAddress) {
v_SLAC_Tester4 := SLAC_Tester4.create("Slac Tester 4") alive;
map(v_SLAC_Tester4:pt_SLAC_Port, systemSECC:pt_SLAC_Port) param (par_slac_node4_mac);
}
else {log("MAC address of Slac node 4 is empty.");}
if(par_slac_node5_mac != emptyMacAddress) {
v_SLAC_Tester5 := SLAC_Tester5.create("Slac Tester 5") alive;
map(v_SLAC_Tester5:pt_SLAC_Port, systemSECC:pt_SLAC_Port) param (par_slac_node5_mac);
}
else {log("MAC address of Slac node 5 is empty.");}
v_HAL_61851_Listener := HAL_61851_Listener.create("IEC 61851 Listener") alive;
map(mtc:pt_HAL_61851_Port, systemSECC:pt_HAL_61851_Port);
map(v_HAL_61851_Listener:pt_HAL_61851_Listener_Port,
systemSECC:pt_HAL_61851_Listener_Port);
connect(mtc:pt_HAL_61851_Internal_Port,
v_HAL_61851_Listener:pt_HAL_61851_Internal_Port);
v_HAL_61851_Listener.start(f_SECC_HAL61851Listener(false));
vc_Default_IEC_61851_ListenerBehavior := activate(a_CMN_IEC61851ListenerBehavior(
pt_HAL_61851_Internal_Port));
}
function f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(out HAL_61851_Listener
v_HAL_61851_Listener,
SystemSECC v_SystemSECC)
runs on SECC_Tester {
unmap(mtc:pt_HAL_61851_Port, v_SystemSECC:pt_HAL_61851_Port);
unmap(v_HAL_61851_Listener:pt_HAL_61851_Listener_Port,
v_SystemSECC:pt_HAL_61851_Listener_Port);
disconnect(mtc:pt_HAL_61851_Internal_Port,
v_HAL_61851_Listener:pt_HAL_61851_Internal_Port);
v_HAL_61851_Listener.kill;
unmap(mtc:pt_SLAC_Port, v_SystemSECC:pt_SLAC_Port);
}
function f_SECC_CMN_PO_ShutdownConfiguration_SLAC_002(out HAL_61851_Listener
v_HAL_61851_Listener,
out SLAC_Tester2 v_SLAC_Tester2,
out SLAC_Tester3 v_SLAC_Tester3,
out SLAC_Tester4 v_SLAC_Tester4,
out SLAC_Tester5 v_SLAC_Tester5,
SystemSECC v_SystemSECC)
runs on SECC_Tester {
unmap(mtc:pt_HAL_61851_Port, v_SystemSECC:pt_HAL_61851_Port);
unmap(v_HAL_61851_Listener:pt_HAL_61851_Listener_Port,
v_SystemSECC:pt_HAL_61851_Listener_Port);
disconnect(mtc:pt_HAL_61851_Internal_Port,
v_HAL_61851_Listener:pt_HAL_61851_Internal_Port);
unmap(mtc:pt_SLAC_Port, v_SystemSECC:pt_SLAC_Port);
if(v_SLAC_Tester2.running) {
unmap(v_SLAC_Tester2:pt_SLAC_Port, v_SystemSECC:pt_SLAC_Port);
}
if(v_SLAC_Tester3.running) {
unmap(v_SLAC_Tester3:pt_SLAC_Port, v_SystemSECC:pt_SLAC_Port);
}
if(v_SLAC_Tester4.running) {
unmap(v_SLAC_Tester4:pt_SLAC_Port, v_SystemSECC:pt_SLAC_Port);
}
if(v_SLAC_Tester5.running) {
unmap(v_SLAC_Tester5:pt_SLAC_Port, v_SystemSECC:pt_SLAC_Port);
}
all component.kill;
}
// ::::::::::::::::::::::: Config Functions :::::::::::::::::::::::::
function f_EVCC_CMN_PR_InitConfiguration_SLAC_001(out HAL_61851_Listener v_HAL_61851_Listener,
SystemEVCC v_SystemEVCC) runs on EVCC_Tester {
map(mtc:pt_SLAC_Port, v_SystemEVCC:pt_SLAC_Port);
v_HAL_61851_Listener := HAL_61851_Listener.create("IEC 61851 Listener") alive;
map(mtc:pt_HAL_61851_Port, v_SystemEVCC:pt_HAL_61851_Port);
map(v_HAL_61851_Listener:pt_HAL_61851_Listener_Port,
v_SystemEVCC:pt_HAL_61851_Listener_Port);
connect(mtc:pt_HAL_61851_Internal_Port,
v_HAL_61851_Listener:pt_HAL_61851_Internal_Port);
v_HAL_61851_Listener.start(f_EVCC_HAL61851Listener(false));
activate(a_CMN_IEC61851ListenerBehavior(pt_HAL_61851_Internal_Port));
}
function f_EVCC_CMN_PR_InitConfiguration_SLAC_002(out HAL_61851_Listener v_HAL_61851_Listener,
out SLAC_Tester2 v_SLAC_Tester2,
SystemEVCC systemEVCC) runs on EVCC_Tester {
var hexstring emptyMacAddress := '000000000000'H;
map(mtc:pt_SLAC_Port, systemEVCC:pt_SLAC_Port);
if(par_slac_node2_mac != emptyMacAddress or isbound(v_SLAC_Tester2)) {
v_SLAC_Tester2 := SLAC_Tester2.create("Slac Tester 2") alive;
map(v_SLAC_Tester2:pt_SLAC_Port, systemEVCC:pt_SLAC_Port) param (par_slac_node2_mac);
}
else {log("MAC address of Slac node 2 is empty.");}
v_HAL_61851_Listener := HAL_61851_Listener.create("IEC 61851 Listener") alive;
map(mtc:pt_HAL_61851_Port, systemEVCC:pt_HAL_61851_Port);
map(v_HAL_61851_Listener:pt_HAL_61851_Listener_Port,
systemEVCC:pt_HAL_61851_Listener_Port);
connect(mtc:pt_HAL_61851_Internal_Port, v_HAL_61851_Listener:pt_HAL_61851_Internal_Port);
v_HAL_61851_Listener.start(f_EVCC_HAL61851Listener(false));
vc_Default_IEC_61851_ListenerBehavior := activate(a_CMN_IEC61851ListenerBehavior(
pt_HAL_61851_Internal_Port));
}
function f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(out HAL_61851_Listener
v_HAL_61851_Listener,
SystemEVCC v_SystemEVCC)
runs on EVCC_Tester {
unmap(mtc:pt_HAL_61851_Port, v_SystemEVCC:pt_HAL_61851_Port);
unmap(v_HAL_61851_Listener:pt_HAL_61851_Listener_Port,
v_SystemEVCC:pt_HAL_61851_Listener_Port);
disconnect(mtc:pt_HAL_61851_Internal_Port,
v_HAL_61851_Listener:pt_HAL_61851_Internal_Port);
v_HAL_61851_Listener.kill;
unmap(mtc:pt_SLAC_Port, v_SystemEVCC:pt_SLAC_Port);
}
function f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(out HAL_61851_Listener
v_HAL_61851_Listener,
out SLAC_Tester2 v_SLAC_Tester2,
SystemEVCC v_SystemEVCC)
runs on EVCC_Tester {
unmap(mtc:pt_HAL_61851_Port, v_SystemEVCC:pt_HAL_61851_Port);
unmap(v_HAL_61851_Listener:pt_HAL_61851_Listener_Port,
v_SystemEVCC:pt_HAL_61851_Listener_Port);
disconnect(mtc:pt_HAL_61851_Internal_Port,
v_HAL_61851_Listener:pt_HAL_61851_Internal_Port);
unmap(mtc:pt_SLAC_Port, v_SystemEVCC:pt_SLAC_Port);
unmap(v_SLAC_Tester2:pt_SLAC_Port, v_SystemEVCC:pt_SLAC_Port);
all component.kill;
}
}