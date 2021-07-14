module PreConditions_SECC_15118_3 {
import from TestBehavior_SECC_CmSlacParm all;
import from TestBehavior_SECC_AttenuationCharacterization all;
import from TestBehavior_SECC_CmSlacMatch all;
import from TestBehavior_SECC_CmSetKey all;
import from TestBehavior_SECC_PLCLinkStatus all;
import from TestBehavior_SECC_CmValidate all;
import from TestBehavior_SECC_CmAmpMap all;
import from Timer_15118_3 all;
import from ComponentsAndPorts all
import from LibFunctions_15118_3 all;
import from Services_HAL_61851 all;
import from Pics_15118_3 all;
import from Pixit_15118_3 all;
import from Pics_15118 all;
import from Services_PLCLinkStatus all;
import from Timer_15118 all;
import from Services_EIMIdentification all;
import from Services_TXPowerLimitation all;
function f_SECC_CMN_PR_StateA_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on SECC_Tester return verdicttype {
var verdicttype verdict := pass;
f_SECC_changeValidStateCondition(A);
verdict := f_SECC_setState(A,v_HAL_61851_Listener);
pt_HAL_61851_Port.clear;
sleep((par_CMN_waitForNextHAL));
verdict := f_SECC_setProximity(0);
if(PICS_SECC_CMN_EIMDone == beforePlugin and vc_testCaseSpecific) {
var boolean v_result := f_SECC_CMN_EIMIdentification();
if(v_result) {
f_SECC_setEimStatus(v_result);
}
}
return verdict;
}
// SECC
function f_SECC_CMN_PR_DisconnectDataLink_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on SECC_Tester return verdicttype {
var verdicttype verdict := f_SECC_CMN_PR_StateA_001(v_HAL_61851_Listener);
// generate Nid and Nmk
vc_Nmk := f_randomHexStringGen(32);
vc_Nid := fx_generateNID(vc_Nmk);
verdict := f_SECC_CMN_TB_VTB_CmSetKey_001(true);
return verdict;
}
function f_SECC_CMN_PR_SetProximityPilot_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on SECC_Tester return verdicttype {
var verdicttype verdict := f_SECC_CMN_PR_DisconnectDataLink_001(v_HAL_61851_Listener);
if ( verdict == pass ) {
if(vc_sleepAfterPlugOut) {
sleep((par_SECC_waitForPlugin));
}
v_HAL_61851_Listener.stop;
v_HAL_61851_Listener.start(f_SECC_HAL61851Listener(true));
if(vc_activateNominal){
f_SECC_changeValidFrequencyRange(0,0);
f_SECC_changeValidDutyCycleRange(100,100);
vc_validDutyCycleLowerBound2 := 100;
vc_validDutyCycleUpperBound2 := 100;
}
if(PICS_CMN_CMN_PlugType == type1) {
verdict := f_SECC_setProximity(cc_proximity_type1);
} else {
if(PICS_CMN_CMN_ChargingMode == aC){
var integer v_proximity_type2_AC;
if(PICS_CMN_AC_CableCapability == capability13A) {
v_proximity_type2_AC := cc_proximity_type2_AC_13A;
} else if(PICS_CMN_AC_CableCapability == capability20A) {
v_proximity_type2_AC := cc_proximity_type2_AC_20A;
} else if(PICS_CMN_AC_CableCapability == capability32A) {
v_proximity_type2_AC := cc_proximity_type2_AC_32A;
} else {
v_proximity_type2_AC := cc_proximity_type2_AC_63A;
}
verdict := f_SECC_setProximity(v_proximity_type2_AC);
} else {
verdict := f_SECC_setProximity(cc_proximity_type2_DC);
}
}
}
return verdict;
}
function f_SECC_CMN_PR_StateB_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on SECC_Tester return verdicttype {
var verdicttype verdict := f_SECC_CMN_PR_SetProximityPilot_001(v_HAL_61851_Listener);
if ( verdict == pass ) {
sleep((par_CMN_waitForNextHAL));
f_SECC_changeValidStateCondition(valid);
f_SECC_setState(vc_state,v_HAL_61851_Listener);
if(PICS_SECC_CMN_EIMDone == afterPlugin and vc_testCaseSpecific) {
f_SECC_setIsConfirmationFlagDC();
verdict := f_SECC_confirmDutyCycle(v_HAL_61851_Listener,
par_T_conn_max_comm,
inconc);
f_SECC_changeValidStateCondition(EorF);
f_SECC_changeValidFrequencyRange(0,0);
f_SECC_changeValidDutyCycleRange(0,0);
f_SECC_setIsConfirmationFlagVoltage();
var boolean v_result := f_SECC_CMN_EIMIdentification();
if(v_result) {
f_SECC_setEimStatus(v_result);
}
} else if(PICS_SECC_CMN_EIMDone == duringSlac and vc_testCaseSpecific) {
f_SECC_setIsConfirmationFlagDC();
verdict := f_SECC_confirmDutyCycle(v_HAL_61851_Listener,
par_T_conn_max_comm,
inconc);
if(verdict == pass) {
if(PIXIT_SECC_AC_InitialDutyCyle == dc5) {
f_SECC_changeValidDutyCycleRange(100,100);
vc_validDutyCycleLowerBound2 := 100;
vc_validDutyCycleUpperBound2 := 100;
}
var boolean v_result := f_SECC_CMN_EIMIdentification();
}
}
}
tc_TT_matching_repetition.start(par_TT_matching_repetition);
return verdict;
}
function f_SECC_CMN_PR_CmSlacParm_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on SECC_Tester return verdicttype {
var verdicttype verdict := f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
if ( verdict == pass ) {
verdict := f_SECC_CMN_TB_VTB_CmSlacParm_001(inconc);
}
return verdict;
}
function f_SECC_CMN_PR_AttenuationCharacterization_001(out HAL_61851_Listener
v_HAL_61851_Listener)
runs on SECC_Tester
return verdicttype {
var verdicttype verdict := f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
// SECC_AttenuationCharacterization Behavior
if ( verdict == pass ) {
verdict := f_SECC_CMN_TB_VTB_AttenuationCharacterization_001(inconc);
}
return verdict;
}
function f_SECC_CMN_PR_CmValidate_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on SECC_Tester return verdicttype {
var verdicttype verdict := f_SECC_CMN_PR_AttenuationCharacterization_001(
v_HAL_61851_Listener);
// SECC_CmSlacMatch Behavior
if ( verdict == pass) {
verdict := f_SECC_CMN_TB_VTB_CmValidate_001(v_HAL_61851_Listener, inconc);
}
return verdict;
}
function f_SECC_CMN_PR_CmSlacMatch_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on SECC_Tester return verdicttype {
var verdicttype verdict;
if(PIXIT_SECC_CMN_CmValidate == cmValidate) {
verdict := f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
}
else {
verdict := f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
}
// SECC_CmSlacMatch Behavior
if (verdict == pass ) {
verdict := f_SECC_CMN_TB_VTB_CmSlacMatch_001(inconc);
}
return verdict;
}
function f_SECC_CMN_PR_CmSetKey_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on SECC_Tester return verdicttype {
var verdicttype verdict := f_SECC_CMN_PR_CmSlacMatch_001(v_HAL_61851_Listener);
// SECC_CmSetKey Behavior
if ( verdict == pass ) {
tc_TT_match_join.start(par_TT_match_join);
verdict := f_SECC_CMN_TB_VTB_CmSetKey_001(false);
}
return verdict;
}
function f_SECC_CMN_PR_PLCLinkStatus_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on SECC_Tester return verdicttype {
var verdicttype verdict := f_SECC_CMN_PR_CmSetKey_001(v_HAL_61851_Listener);
// SECC_PLCLinkStatus Behavior
if ( verdict == pass ) {
verdict := f_SECC_CMN_TB_VTB_PLCLinkStatus_001(inconc);
tc_TT_matching_repetition.stop;
}
return verdict;
}
function f_SECC_CMN_PR_CmAmpMap_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on SECC_Tester return verdicttype {
var verdicttype verdict := f_SECC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
// EVCC_CmAmpMap Behavior
if ( verdict == pass ) {
if(PICS_CMN_CMN_InitiateCmAmpMap) {
verdict := f_SECC_CMN_TB_VTB_CmAmpMap_001(inconc);
if(getverdict == pass) {
f_SECC_CMN_checkTXPowerLimitation();
}
}
else {
verdict := f_SECC_CMN_TB_VTB_CmAmpMap_002(inconc);
}
}
return verdict;
}
}

module PreConditions_EVCC_15118_3 {
import from TestBehavior_EVCC_CmSetKey all;
import from TestBehavior_EVCC_CmSlacParm all;
import from TestBehavior_EVCC_PLCLinkStatus all;
import from TestBehavior_EVCC_AttenuationCharacterization all;
import from TestBehavior_EVCC_CmSlacMatch all;
import from TestBehavior_EVCC_CmValidate all;
import from TestBehavior_EVCC_CmAmpMap all;
import from TestBehavior_EVCC_CmValidateOrCmSlacMatch all;
import from Timer_15118_3 all;
import from ComponentsAndPorts all;
import from LibFunctions_15118_3 { group generalFunctions; }
import from Services_HAL_61851 all;
import from Pics_15118_3 all;
import from Pics_15118 all;
import from Pixit_15118_3 all;
import from Services_PLCLinkStatus all;
import from Pixit_15118 all;
import from Timer_15118 all;
import from Services_TXPowerLimitation all;
import from TTlibrary_Logging all;
import from LibFunctions_15118_2 {function f_CMN_PhysicalValue_GetValue};
function f_EVCC_CMN_PR_SetPowerFlowConfiguration_001() runs on EVCC_Tester return verdicttype{
var verdicttype verdict := pass;
return verdict;
}
function f_EVCC_CMN_PR_DisableControlPilot_001() runs on EVCC_Tester return verdicttype {
var verdicttype verdict := f_EVCC_CMN_PR_SetPowerFlowConfiguration_001();
verdict := f_EVCC_setPwmMode(vc_errorState);
sleep((par_CMN_waitForNextHAL));
verdict := f_EVCC_setProximity(0);
return verdict;
}
function f_EVCC_CMN_PR_CmSetKey_001() runs on EVCC_Tester return verdicttype {
var verdicttype verdict := f_EVCC_CMN_PR_DisableControlPilot_001();
// generate Nid and Nmk
if ( verdict == pass ) {
vc_Nmk := f_randomHexStringGen(32);
vc_Nid := fx_generateNID(vc_Nmk);
verdict := f_EVCC_CMN_TB_VTB_CmSetKey_001();
f_EVCC_PLCNodeIsReadyForCommunication();
sleep(par_EVCC_PLCNodeReady_delay);
}
return verdict;
}
function f_EVCC_CMN_PR_SetProximityPilot_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on EVCC_Tester return verdicttype {
var verdicttype verdict := f_EVCC_CMN_PR_CmSetKey_001();
if ( verdict == pass ) {
v_HAL_61851_Listener.stop;
v_HAL_61851_Listener.start(f_EVCC_HAL61851Listener(true));
if(PICS_CMN_CMN_PlugType == type1) {
verdict := f_EVCC_setProximity(cc_proximity_type1);
} else {
if(PICS_CMN_CMN_ChargingMode == aC){
var integer v_proximity_type2_AC;
if(PICS_CMN_AC_CableCapability == capability13A) {
v_proximity_type2_AC := cc_proximity_type2_AC_13A;
} else if(PICS_CMN_AC_CableCapability == capability20A) {
v_proximity_type2_AC := cc_proximity_type2_AC_20A;
} else if(PICS_CMN_AC_CableCapability == capability32A) {
v_proximity_type2_AC := cc_proximity_type2_AC_32A;
} else {
v_proximity_type2_AC := cc_proximity_type2_AC_63A;
}
verdict := f_EVCC_setProximity(v_proximity_type2_AC);
} else {
verdict := f_EVCC_setProximity(cc_proximity_type2_DC);
}
}
}
return verdict;
}
function f_EVCC_CMN_PR_EnableControlPilot_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on EVCC_Tester return verdicttype {
var verdicttype verdict := f_EVCC_CMN_PR_SetProximityPilot_001(v_HAL_61851_Listener);
if ( verdict == pass ) {
sleep((par_CMN_waitForNextHAL));
f_EVCC_changeValidStateCondition(E,valid);
verdict := f_EVCC_setPwmMode(e_PosVolt12);
}
return verdict;
}
function f_EVCC_CMN_PR_StateB_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on EVCC_Tester return verdicttype {
var verdicttype verdict := f_EVCC_CMN_PR_EnableControlPilot_001(v_HAL_61851_Listener);
if ( verdict == pass ) {
timer statetimer := par_CMN_HAL_Timeout;
verdict := f_EVCC_confirmState(valid, v_HAL_61851_Listener,
statetimer, inconc);
}
tc_TT_EVSE_SLAC_init.start(par_TT_EVSE_SLAC_init_min);
return verdict;
}
function f_EVCC_CMN_PR_DutyCycle_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on EVCC_Tester return verdicttype {
var integer v_oscOff := 100;
var verdicttype verdict := f_EVCC_CMN_PR_StateB_001(v_HAL_61851_Listener);
if ( verdict == pass ) {
sleep((vc_DutyCycleDelay));
if(PICS_CMN_CMN_ChargingMode == aC){
if(vc_DutyCycle != v_oscOff) {
verdict := f_EVCC_setDutyCycle(vc_DutyCycle);
verdict := f_EVCC_setPwmMode(e_OscOn);
}
}
else {
verdict := f_EVCC_setDutyCycle(5);
verdict := f_EVCC_setPwmMode(e_OscOn);
}
pt_SLAC_Port.clear;
}
return verdict;
}
function f_EVCC_CMN_PR_CmSlacParm_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on EVCC_Tester return verdicttype {
var verdicttype verdict := f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
if ( verdict == pass ) {
verdict := f_EVCC_CMN_TB_VTB_CmSlacParm_001(inconc);
}
return verdict;
}
function f_EVCC_CMN_PR_AttenuationCharacterization_001(out HAL_61851_Listener
v_HAL_61851_Listener)
runs on EVCC_Tester
return verdicttype {
var verdicttype verdict := f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
if ( verdict == pass ) {
  verdict := f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(inconc);
}
return verdict;
}
function f_EVCC_CMN_PR_CmValidate_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on EVCC_Tester return verdicttype {
var verdicttype verdict := f_EVCC_CMN_PR_AttenuationCharacterization_001(
v_HAL_61851_Listener);
if ( verdict == passand PIXIT_EVCC_CMN_CmValidate == cmValidate) {
verdict := f_EVCC_CMN_TB_VTB_CmValidate_001(v_HAL_61851_Listener, false,
vc_DutyCycle, inconc);
}
return verdict;
}
function f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on EVCC_Tester return verdicttype {
var verdicttype verdict := f_EVCC_CMN_PR_AttenuationCharacterization_001(
v_HAL_61851_Listener);
if ( verdict == pass) {
verdict := f_EVCC_CMN_TB_VTB_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener,
inconc);
}
return verdict;
}
function f_EVCC_CMN_PR_PLCLinkStatus_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on EVCC_Tester return verdicttype {
var verdicttype verdict := f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener);
if ( verdict == pass ) {
verdict := f_EVCC_CMN_TB_VTB_PLCLinkStatus_001(inconc);
}
return verdict;
}
function f_EVCC_CMN_PR_CmAmpMap_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on EVCC_Tester return verdicttype {
var verdicttype verdict := f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
if ( verdict == pass ) {
if(PICS_CMN_CMN_InitiateCmAmpMap) {
verdict := f_EVCC_CMN_TB_VTB_CmAmpMap_001(inconc);
if(getverdict == pass) {
f_EVCC_CMN_checkTXPowerLimitation();
}
}
else {
verdict := f_EVCC_CMN_TB_VTB_CmAmpMap_002(inconc);
}
}
return verdict;
}
}