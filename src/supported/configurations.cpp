#include "configurations.hpp"
#include <spdlog/spdlog.h>
#include "slac_type.hpp"
#include "component.hpp"
#include "port.hpp"

namespace TestLib
{

/* In addition to the MTC and PTC and their corresponding port type definitions, a test configuration also
consists of respective Test System Interfaces (TSI). An abstract Test System Interface (TSI) is specified
as a collection of ports. A TSI has no local timers, constants or variables. Only ports are assigned to it.
During the test  case execution test  components ports  can be mapped dynamically to the TSI ports to
establish communication channel to the real test system interface. In the test configuration the TSI uses
the type System_EVCC or System_SECC depending on the type of the SUT */

void Configurations_15118_3::map()
{

}

void Configurations_15118_3::connect()
{

}

void Configurations_15118_3::activate()
{

}

void Configurations_15118_3::unmap()
{

}

void Configurations_15118_3::disconnect()
{

}

void Configurations_15118_3::all_component_kill()
{

}

// ::::::::::::::::::::::: Config Functions :::::::::::::::::::::::::
// :::::::::::::::::::::::::: SECC Tester :::::::::::::::::::::::::::
void Configurations_15118_3::f_SECC_CMN_PR_InitConfiguration_SLAC_001(
    std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener,
    std::shared_ptr<SystemSECC> &v_SystemSECC)
{

  map(mtc_secc->pt_SLAC_Port, v_SystemSECC->pt_SLAC_Port);
  v_HAL_61851_Listener = HAL_61851_Listener::create("IEC 61851 Listener");
  map(mtc_secc->pt_HAL_61851_Port, v_SystemSECC->pt_HAL_61851_Port);
  map(v_HAL_61851_Listener->pt_HAL_61851_Listener_Port, v_SystemSECC->pt_HAL_61851_Listener_Port);
  connect(mtc_secc->pt_HAL_61851_Internal_Port, v_HAL_61851_Listener->pt_HAL_61851_Internal_Port);
  v_HAL_61851_Listener->start(f_SECC_HAL61851Listener(false));
  activate(a_CMN_IEC61851ListenerBehavior(mtc_secc->pt_HAL_61851_Internal_Port));
}

void Configurations_15118_3::f_SECC_CMN_PR_InitConfiguration_SLAC_002(
    std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener,
    std::shared_ptr<SLAC_Tester> &v_SLAC_Tester2,
    std::shared_ptr<SLAC_Tester> &v_SLAC_Tester3,
    std::shared_ptr<SLAC_Tester> &v_SLAC_Tester4,
    std::shared_ptr<SLAC_Tester> &v_SLAC_Tester5,
    std::shared_ptr<SystemSECC> &systemSECC)
{
  hexstring(6) emptyMacAddress{0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  map(mtc_secc->pt_SLAC_Port, systemSECC->pt_SLAC_Port);
  if (par_slac_node2_mac != emptyMacAddress)
  {
    v_SLAC_Tester2 = SLAC_Tester::create("Slac Tester 2", par_slac_node2_mac);
    map(v_SLAC_Tester2->pt_SLAC_Port, systemSECC->pt_SLAC_Port);
  }
  else
  {
    spdlog::info("MAC address of Slac node 2 is empty.");
  }
  if (par_slac_node3_mac != emptyMacAddress)
  {
    v_SLAC_Tester3 = SLAC_Tester::create("Slac Tester 3", par_slac_node3_mac);
    map(v_SLAC_Tester3->pt_SLAC_Port, systemSECC->pt_SLAC_Port);
  }
  else
  {
    spdlog::info("MAC address of Slac node 3 is empty.");
  }
  if (par_slac_node4_mac != emptyMacAddress)
  {
    v_SLAC_Tester4 = SLAC_Tester::create("Slac Tester 4", par_slac_node4_mac);
    map(v_SLAC_Tester4->pt_SLAC_Port, systemSECC->pt_SLAC_Port);
  }
  else
  {
    spdlog::info("MAC address of Slac node 4 is empty.");
  }
  if (par_slac_node5_mac != emptyMacAddress)
  {
    v_SLAC_Tester5 = SLAC_Tester::create("Slac Tester 5", par_slac_node5_mac);
    map(v_SLAC_Tester5->pt_SLAC_Port, systemSECC->pt_SLAC_Port);
  }
  else
  {
    spdlog::info("MAC address of Slac node 5 is empty.");
  }
  v_HAL_61851_Listener = HAL_61851_Listener::create("IEC 61851 Listener");
  map(mtc_secc->pt_HAL_61851_Port, systemSECC->pt_HAL_61851_Port);
  map(v_HAL_61851_Listener->pt_HAL_61851_Listener_Port, systemSECC->pt_HAL_61851_Listener_Port);
  connect(mtc_secc->pt_HAL_61851_Internal_Port, v_HAL_61851_Listener->pt_HAL_61851_Internal_Port);
  v_HAL_61851_Listener->start(f_SECC_HAL61851Listener(false));
  vc_Default_IEC_61851_ListenerBehavior = activate(a_CMN_IEC61851ListenerBehavior(mtc_secc->pt_HAL_61851_Internal_Port));
}

void Configurations_15118_3::f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(
    std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener,
    std::shared_ptr<SystemSECC> &v_SystemSECC)
{
  unmap(mtc_secc->pt_HAL_61851_Port, v_SystemSECC->pt_HAL_61851_Port);
  unmap(v_HAL_61851_Listener->pt_HAL_61851_Listener_Port, v_SystemSECC->pt_HAL_61851_Listener_Port);
  disconnect(mtc_secc->pt_HAL_61851_Internal_Port, v_HAL_61851_Listener->pt_HAL_61851_Internal_Port);
  v_HAL_61851_Listener->kill();
  unmap(mtc_secc->pt_SLAC_Port, v_SystemSECC->pt_SLAC_Port);
}

void Configurations_15118_3::f_SECC_CMN_PO_ShutdownConfiguration_SLAC_002(
    std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener,
    std::shared_ptr<SLAC_Tester2> &v_SLAC_Tester2,
    std::shared_ptr<SLAC_Tester3> &v_SLAC_Tester3,
    std::shared_ptr<SLAC_Tester4> &v_SLAC_Tester4,
    std::shared_ptr<SLAC_Tester5> &v_SLAC_Tester5,
    std::shared_ptr<SystemSECC> &v_SystemSECC)
{
  unmap(mtc_secc->pt_HAL_61851_Port, v_SystemSECC->pt_HAL_61851_Port);
  unmap(v_HAL_61851_Listener->pt_HAL_61851_Listener_Port, v_SystemSECC->pt_HAL_61851_Listener_Port);
  disconnect(mtc_secc->pt_HAL_61851_Internal_Port, v_HAL_61851_Listener->pt_HAL_61851_Internal_Port);
  unmap(mtc_secc->pt_SLAC_Port, v_SystemSECC->pt_SLAC_Port);
  if (v_SLAC_Tester2->running())
  {
    unmap(v_SLAC_Tester2->pt_SLAC_Port, v_SystemSECC->pt_SLAC_Port);
  }
  if (v_SLAC_Tester3->running())
  {
    unmap(v_SLAC_Tester3->pt_SLAC_Port, v_SystemSECC->pt_SLAC_Port);
  }
  if (v_SLAC_Tester4->running())
  {
    unmap(v_SLAC_Tester4->pt_SLAC_Port, v_SystemSECC->pt_SLAC_Port);
  }
  if (v_SLAC_Tester5->running())
  {
    unmap(v_SLAC_Tester5->pt_SLAC_Port, v_SystemSECC->pt_SLAC_Port);
  }
  all_component_kill();
}


// ::::::::::::::::::::::: Config Functions :::::::::::::::::::::::::
// :::::::::::::::::::::::::: EVCC Tester :::::::::::::::::::::::::::
void Configurations_15118_3::f_EVCC_CMN_PR_InitConfiguration_SLAC_001(
    std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener,
    std::shared_ptr<SystemEVCC> &v_SystemEVCC)
{
  map(mtc_evcc->pt_SLAC_Port, v_SystemEVCC->pt_SLAC_Port);
  v_HAL_61851_Listener = HAL_61851_Listener::create("IEC 61851 Listener");
  map(mtc_evcc->pt_HAL_61851_Port, v_SystemEVCC->pt_HAL_61851_Port);
  map(v_HAL_61851_Listener->pt_HAL_61851_Listener_Port, v_SystemEVCC->pt_HAL_61851_Listener_Port);
  connect(mtc_evcc->pt_HAL_61851_Internal_Port, v_HAL_61851_Listener->pt_HAL_61851_Internal_Port);
  v_HAL_61851_Listener->start(f_EVCC_HAL61851Listener(false));
  activate(a_CMN_IEC61851ListenerBehavior(mtc_evcc->pt_HAL_61851_Internal_Port));
}
void Configurations_15118_3::f_EVCC_CMN_PR_InitConfiguration_SLAC_002(
    std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener,
    std::shared_ptr<SLAC_Tester> &v_SLAC_Tester2,
    std::shared_ptr<SystemEVCC> &systemEVCC)
{
  hexstring(6) emptyMacAddress{0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  map(mtc_evcc->pt_SLAC_Port, systemEVCC->pt_SLAC_Port);
  if ((par_slac_node2_mac != emptyMacAddress) || isbound(v_SLAC_Tester2))
  {
    v_SLAC_Tester2 = SLAC_Tester::create("Slac Tester 2", par_slac_node2_mac);
    map(v_SLAC_Tester2->pt_SLAC_Port, systemEVCC->pt_SLAC_Port);
  }
  else
  {
    spdlog::info("MAC address of Slac node 2 is empty.");
  }
  v_HAL_61851_Listener = HAL_61851_Listener::create("IEC 61851 Listener");
  map(mtc_evcc->pt_HAL_61851_Port, systemEVCC->pt_HAL_61851_Port);
  map(v_HAL_61851_Listener->pt_HAL_61851_Listener_Port, systemEVCC->pt_HAL_61851_Listener_Port);
  connect(mtc_evcc->pt_HAL_61851_Internal_Port, v_HAL_61851_Listener->pt_HAL_61851_Internal_Port);
  v_HAL_61851_Listener->start(f_EVCC_HAL61851Listener(false));
  vc_Default_IEC_61851_ListenerBehavior = activate(a_CMN_IEC61851ListenerBehavior(mtc_evcc->pt_HAL_61851_Internal_Port));
}
void Configurations_15118_3::f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_001(
    std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener,
    std::shared_ptr<SystemEVCC> &v_SystemEVCC)
{
  unmap(mtc_evcc->pt_HAL_61851_Port, v_SystemEVCC->pt_HAL_61851_Port);
  unmap(v_HAL_61851_Listener->pt_HAL_61851_Listener_Port, v_SystemEVCC->pt_HAL_61851_Listener_Port);
  disconnect(mtc_evcc->pt_HAL_61851_Internal_Port, v_HAL_61851_Listener->pt_HAL_61851_Internal_Port);
  v_HAL_61851_Listener->kill();
  unmap(mtc_evcc->pt_SLAC_Port, v_SystemEVCC->pt_SLAC_Port);
}
void Configurations_15118_3::f_EVCC_CMN_PO_ShutdownConfiguration_SLAC_002(
    std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener,
    std::shared_ptr<SLAC_Tester> &v_SLAC_Tester2,
    std::shared_ptr<SystemEVCC> &v_SystemEVCC)
{
  unmap(mtc_evcc->pt_HAL_61851_Port, v_SystemEVCC->pt_HAL_61851_Port);
  unmap(v_HAL_61851_Listener->pt_HAL_61851_Listener_Port, v_SystemEVCC->pt_HAL_61851_Listener_Port);
  disconnect(mtc_evcc->pt_HAL_61851_Internal_Port, v_HAL_61851_Listener->pt_HAL_61851_Internal_Port);
  unmap(mtc_evcc->pt_SLAC_Port, v_SystemEVCC->pt_SLAC_Port);
  unmap(v_SLAC_Tester2->pt_SLAC_Port, v_SystemEVCC->pt_SLAC_Port);
  all_component_kill();
}

}