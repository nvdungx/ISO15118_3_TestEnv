#ifndef __POSTCONDITIONS_H__
#define __POSTCONDITIONS_H__

#include "datatype.hpp"
#include "execution/paralleltestcomponent.hpp"

namespace TestLib
{
extern void all_timer_stop(void);

namespace PostConditions_SECC_15118_3
{
  void f_SECC_CMN_PO_InitialState_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
} // namespace PostConditions_SECC_15118_3

namespace PostConditions_EVCC_15118_3
{
  void f_EVCC_CMN_PO_InitialState_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
} // namespace PostConditions_EVCC_15118_3
} // namespace TestLib

#endif // __POSTCONDITIONS_H__