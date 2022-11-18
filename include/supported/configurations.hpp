#ifndef __CONFIGURATIONS_H__
#define __CONFIGURATIONS_H__

#include "slac_type.hpp"
#include "supported/configurations.hpp"
#include "execution/maintestcomponent.hpp"
#include "execution/paralleltestcomponent.hpp"
#include "execution/testsysteminterface.hpp"
#include "execution/port.hpp"

namespace TestLib
{
  class Configurations_15118_3
  {
  private:
  public:
    Configurations_15118_3() = delete;
    Configurations_15118_3(Configurations_15118_3 &) = delete;
    Configurations_15118_3 &operator=(const Configurations_15118_3 &) = delete;
    ~Configurations_15118_3(){};
    static void map();
    static void connect();
    static void activate();
    static void unmap();
    static void disconnect();
    static void all_component_kill();
    static void f_SECC_CMN_PR_InitConfiguration_SLAC_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SystemSECC> &v_SystemSECC);
    static void f_SECC_CMN_PR_InitConfiguration_SLAC_002(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester2, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester3, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester4, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester5, std::shared_ptr<SystemSECC> &systemSECC);
    static void f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SystemSECC> &v_SystemSECC);
    static void f_SECC_CMN_PO_ShutdownConfiguration_SLAC_002(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester2, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester3, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester4, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester5, std::shared_ptr<SystemSECC> &v_SystemSECC);
    static void f_EVCC_CMN_PR_InitConfiguration_SLAC_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SystemEVCC> &v_SystemEVCC);
    static void f_EVCC_CMN_PR_InitConfiguration_SLAC_002(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester2, std::shared_ptr<SystemEVCC> &systemEVCC);
    static void f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SystemEVCC> &v_SystemEVCC);
    static void f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester2, std::shared_ptr<SystemEVCC> &v_SystemEVCC);
  };
} // namespace TestLib

#endif // __CONFIGURATIONS_H__