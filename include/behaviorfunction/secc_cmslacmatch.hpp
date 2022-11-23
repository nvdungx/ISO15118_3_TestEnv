#ifndef __SECC_CMSLACMATCH_H__
#define __SECC_CMSLACMATCH_H__
#include "datatype.hpp"
#include "slac_type.hpp"

namespace TestLib {
namespace TestBehavior_SECC_CmSlacMatch
{
  extern VerdictValue f_SECC_CMN_TB_VTB_CmSlacMatch_001(VerdictValue v_vct);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmSlacMatch_002(void);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmSlacMatch_003(void);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmSlacMatch_004(const MME_Payload &v_payload);
  extern VerdictValue f_SECC_CMN_TB_VTB_CmSlacMatch_005(const std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
} // namespace TestBehavior_SECC_CmSlacMatch
}
#endif // __SECC_CMSLACMATCH_H__