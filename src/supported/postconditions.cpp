module PostConditions_SECC_15118_3 {
import from ComponentsAndPorts all;
import from Services_HAL_61851 all;
import from LibFunctions_15118_3 { group generalFunctions; }
import from Pics_15118 all;
import from Pixit_15118 all;
import from Timer_15118_3 all;
import from Timer_15118 all;
function f_SECC_CMN_PO_InitialState_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on SECC_Tester {
v_HAL_61851_Listener.stop;
v_HAL_61851_Listener.start(f_SECC_HAL61851Listener(false));
pt_HAL_61851_Port.clear;
pt_HAL_61851_Internal_Port.clear;
f_SECC_changeValidStateCondition(A);
f_SECC_changeValidFrequencyRange(0,0);
f_SECC_changeValidDutyCycleRange(100,100);
f_SECC_setState(A,v_HAL_61851_Listener);
pt_HAL_61851_Port.clear;
sleep((par_CMN_waitForNextHAL));
f_SECC_setProximity(0);
v_HAL_61851_Listener.stop;
all timer.stop;
log(par_SECC_waitForNextTC, " Sec timer started");
sleep(par_SECC_waitForNextTC);
log(par_SECC_waitForNextTC, " Sec timer stopped");
}
}
module PostConditions_EVCC_15118_3 {
import from ComponentsAndPorts all;
import from Services_HAL_61851 all;
import from LibFunctions_15118_3 all;
import from Pics_15118 all;
import from Timer_15118_3 all;
import from Pixit_15118 all;
import from Timer_15118 all;
function f_EVCC_CMN_PO_InitialState_001(out HAL_61851_Listener v_HAL_61851_Listener)
runs on EVCC_Tester {
v_HAL_61851_Listener.stop;
v_HAL_61851_Listener.start(f_EVCC_HAL61851Listener(false));
pt_HAL_61851_Port.clear;
f_EVCC_setPwmMode(e_OscOff);
pt_HAL_61851_Port.clear;
sleep((par_CMN_waitForNextHAL));
f_EVCC_setProximity(0);
v_HAL_61851_Listener.stop;
all timer.stop;
log((par_EVCC_waitForNextTC)," Sec timer started");
sleep((par_EVCC_waitForNextTC));
log((par_EVCC_waitForNextTC)," Sec timer stopped");
}
}