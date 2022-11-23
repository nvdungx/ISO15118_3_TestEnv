#ifndef __SECC_CMSLACPARM_H__
#define __SECC_CMSLACPARM_H__
#include "datatype.hpp"
#include "slac_type.hpp"

namespace TestLib {
namespace TestBehavior_SECC_CmSlacParm
{
  extern VerdictValue f_SECC_CMN_TB_VTB_CmSlacParm_001(VerdictValue v_vct);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmSlacParm_002(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, const SLAC_Header &v_slac_Header, boolean v_sendInvalid);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmSlacParm_003(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmSlacParm_004(void);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmSlacParm_005(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  extern VerdictValue f_SECC_AC_TB_VTB_CmSlacParm_001(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  extern VerdictValue f_SECC_AC_TB_VTB_CmSlacParm_002(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  extern VerdictValue f_SECC_AC_TB_VTB_CmSlacParm_003(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
} // namespace TestBehavior_SECC_CmSlacParm
}
#endif // __SECC_CMSLACPARM_H__