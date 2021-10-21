#include "configurations.hpp"
#include <spdlog/spdlog.h>
#include "slac_type.hpp"
#include "component.hpp"
#include "port.hpp"
#include "libfunctions.hpp"
#include "timer_cfg.hpp"

namespace TestLib
{
  using namespace LibFunctions_15118_3::generalFunctions;
  using namespace Timer_15118::Timer_15118_3;

  void all_timer_stop(void)
  {

  }

  void PostConditions_SECC_15118_3::f_SECC_CMN_PO_InitialState_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
  {
    v_HAL_61851_Listener->stop();
    v_HAL_61851_Listener->start(f_SECC_HAL61851Listener(false));
    SECC_Tester::pt_HAL_61851_Port->clear();
    SECC_Tester::pt_HAL_61851_Internal_Port->clear();
    f_SECC_changeValidStateCondition(A);
    f_SECC_changeValidFrequencyRange(0, 0);
    f_SECC_changeValidDutyCycleRange(100, 100);
    f_SECC_setState(A, v_HAL_61851_Listener);
    SECC_Tester::pt_HAL_61851_Port->clear();
    sleep(par_CMN_waitForNextHAL);
    f_SECC_setProximity(0);
    v_HAL_61851_Listener->stop();
    all_timer_stop();
    spdlog::info(par_SECC_waitForNextTC, " Sec timer started");
    sleep(par_SECC_waitForNextTC);
    spdlog::info(par_SECC_waitForNextTC, " Sec timer stopped");
  }

  void PostConditions_EVCC_15118_3::f_EVCC_CMN_PO_InitialState_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
  {
    v_HAL_61851_Listener->stop();
    v_HAL_61851_Listener->start(f_EVCC_HAL61851Listener(false));
    EVCC_Tester::pt_HAL_61851_Port->clear();
    f_EVCC_setPwmMode(e_OscOff);
    EVCC_Tester::pt_HAL_61851_Port->clear();
    sleep(par_CMN_waitForNextHAL);
    f_EVCC_setProximity(0);
    v_HAL_61851_Listener->stop();
    all_timer_stop();
    spdlog::info((par_EVCC_waitForNextTC), " Sec timer started");
    sleep(par_EVCC_waitForNextTC);
    spdlog::info((par_EVCC_waitForNextTC), " Sec timer stopped");
  }
}
