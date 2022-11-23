#ifndef __EVCC_CMSLACPARM_H__
#define __EVCC_CMSLACPARM_H__
#include "datatype.hpp"
#include "slac_type.hpp"

namespace TestLib {
namespace TestBehavior_EVCC_CmSlacParm
{
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmSlacParm_001(VerdictValue v_vct);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmSlacParm_002(void);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmSlacParm_003(const MME_Payload &invalidPayload);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmSlacParm_004(void);
  extern VerdictValue f_EVCC_CMN_TB_VTB_CmSlacParm_005(void);
} // namespace TestBehavior_EVCC_CmSlacParm
}
#endif // __EVCC_CMSLACPARM_H__