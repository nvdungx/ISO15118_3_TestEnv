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
namespace Configurations_15118_3
{
  void f_SECC_CMN_PR_InitConfiguration_SLAC_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SystemSECC> &v_SystemSECC);
  void f_SECC_CMN_PR_InitConfiguration_SLAC_002(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester2, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester3, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester4, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester5, std::shared_ptr<SystemSECC> &systemSECC);
  void f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SystemSECC> &v_SystemSECC);
  void f_SECC_CMN_PO_ShutdownConfiguration_SLAC_002(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester2, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester3, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester4, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester5, std::shared_ptr<SystemSECC> &v_SystemSECC);
  void f_EVCC_CMN_PR_InitConfiguration_SLAC_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SystemEVCC> &v_SystemEVCC);
  void f_EVCC_CMN_PR_InitConfiguration_SLAC_002(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester2, std::shared_ptr<SystemEVCC> &systemEVCC);
  void f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SystemEVCC> &v_SystemEVCC);
  void f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<SLAC_Tester> &v_SLAC_Tester2, std::shared_ptr<SystemEVCC> &v_SystemEVCC);
} // namespace Configurations_15118_3
} // namespace TestLib

#endif // __CONFIGURATIONS_H__