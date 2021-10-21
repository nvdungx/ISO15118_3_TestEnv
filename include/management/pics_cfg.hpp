#ifndef __PICS_CFG_H__
#define __PICS_CFG_H__
#include "datatype.hpp"

namespace TestLib
{
  namespace Pics_15118
  {
    using namespace DataStructure_PICS_15118;
    namespace PICS_15118
    {
      namespace PICS_CMN
      {
        /* Indication for enabling combined testing including SLAC association and V2G messaging*/
        extern boolean PICS_CMN_CMN_CombinedTesting;
        /* Indication for testing either AC or DC charging mode  */
        extern ChargingMode PICS_CMN_CMN_ChargingMode;
        /* Indication for testing either EIM or PnC identification mode */
        extern IdentificationMode PICS_CMN_CMN_IdentificationMode;
        /* Indication for testing either type1 or type2 plug type  */
        extern PlugType PICS_CMN_CMN_PlugType;
        /* Indication for used AC cable type Choice: i) capability13A, ii) capability20A, iii) capability32A, iv) capability63A, v) capability70A  */
        extern CableCapabilityACType PICS_CMN_AC_CableCapability;
        /* Indication for the sleep time within a paused session  */
        extern float PICS_CMN_CMN_WakeUp;
      }
      namespace PICS_SECC_Tester
      {
        /* Indication for enabling a charging pause  */
        extern boolean PICS_SECC_CMN_Pause;
        /* Indication for initiating EIM Authorization process Choice: i) beforePlugin, ii) afterPlugin, iii) duringSlac, iv) v2gAuthorization  */
        extern EIMDone PICS_SECC_CMN_EIMDone;
      }
      namespace PICS_EVCC_Tester
      {
        /* Indication for enabling a PmaxScheduleList with a list element pMax = 0W (triggering pause) Choice: i) sleepWithoutCharge, ii) sleepAfterCharge, iii) none_ */
        extern ZeroPow PICS_EVCC_CMN_PmaxSchedulewithZeroPow;
      }
    }
  }
  namespace Pics_15118_3
  {
    using namespace DataStructure_PICS_15118_3;
    namespace PICS_15118_3
    {
      namespace PICS_CMN
      {
        /* Indication for initiating the Amplitude map process  */
        extern boolean PICS_CMN_CMN_InitiateCmAmpMap;
        /* Indication for enabling Test Group: SLAC timeouts  */
        extern boolean PICS_CMN_CMN_SlacTimeouts;
        /* Indication for enabling Test Group: Invalid SLAC data fields and messages  */
        extern boolean PICS_CMN_CMN_InvalidSlacDataFieldsAndMessages;
        /* Indication for enabling Test Group: Invalid states and duty cycles  */
        extern boolean PICS_CMN_CMN_InvalidStatesAndDutyCycles;
      }
    }
  }
}
#endif // __PICS_CFG_H__