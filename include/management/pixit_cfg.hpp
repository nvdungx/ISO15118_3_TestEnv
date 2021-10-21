#ifndef __PIXIT_CFG_H__
#define __PIXIT_CFG_H__

#include "datatype.hpp"

namespace TestLib
{
  namespace Pixit_15118
  {
    using namespace DataStructure_PIXIT_15118;
    namespace PIXIT_15118
    {
      namespace PIXIT_CMN
      {
        /* Indication for the wake‐up time (SUT) within a paused session */
        float PIXIT_CMN_CMN_WakeUp;
      }
      namespace PIXIT_EVCC_Tester
      {
        /* Indication for enabling a charging pause Choice: i) pause, ii) unknown, iii) none_ */
        Pause PIXIT_EVCC_CMN_Pause;
      }
    }
  }
  namespace Pixit_15118_3
  {
    using namespace DataStructure_PIXIT_15118_3;
    namespace PIXIT_15118_3
    {
      namespace PIXIT_CMN_Tester
      {
        /* Indication for explicit testing of Amplitude map process */
        boolean PIXIT_CMN_CMN_CmAmpMap;
      }
      namespace PIXIT_SECC_Tester
      {
        /* Indication for explicit testing of SECC Validation process Choice: i) none_, ii) cmValidate */
        CmValidateSECC PIXIT_SECC_CMN_CmValidate;
        /* Indication for starting with initial duty cycle of 5 % or 100 % */
        DutyCycle PIXIT_SECC_AC_InitialDutyCyle;
        /* Indication for SECC grid architecture which not requires a validation process */
        boolean PIXIT_SECC_CMN_ArchitectureValidationNotRequired;
        /* Indication for the implemented handling after connection loss (
          Option A: EVSE shall leave the logical network and shall switch to
          state E/F after connection loss,
          Option B: EVSE shall leave the logical network, shall stay in X2 state
          and waits for a new matching process) */
        CLHandling PIXIT_SECC_AC_ConnectionLossHandling;
      }
      namespace PIXIT_EVCC_Tester
      {
        /* Indication for explicit testing of EVCC Validation process. If
          PIXIT_EVCC_CMN_CmValidate := cmValidate, test system sends a
          manipulated attenuation profile (attenuation was increased) to
          trigger a validation process
          Choice: i) cmValidate, ii) unknown, iii) none_ */
        CmValidateEVCC PIXIT_EVCC_CMN_CmValidate;
        /* Indication for validation fallback handling if the SUT does not have
          implemented the validation process feature (failed)
          Choice: i) continue_, ii) skip, iii) terminate iv) unknown */
        ValidationFallbackHandling PIXIT_EVCC_CMN_FallbackValidationFailed;
        /* Indication for validation fallback if the SECC grid architecture not
          requires a validation process (notRequired)
          Choice: i) continue_, ii) skip, iii) unknown */
        ValidationFallbackHandling PIXIT_EVCC_CMN_FallbackValidationNotRequired;
        /* Indication for handling if an SECC is occupied by another running
          validation process Choice: i) retry, ii) iterate, iii) unknown */
        ConcurrentValidationHandling PIXIT_EVCC_CMN_ConcurrentValidation;
        /* Indication for the knowledge of the configuration parameter
          PIXIT_EVCC_CMN_TTMatchingRepetition and PIXIT_EVCC_CMN_TTMatchingRate */
        boolean PIXIT_EVCC_CMN_TTMatchingRepetitionConfig;
        /* Predefined SUT value for the parameter TT_matching_repetition */
        float PIXIT_EVCC_CMN_TTMatchingRepetition;
        /* Predefined SUT value for the parameter TT_matching_rate */
        float PIXIT_EVCC_CMN_TTMatchingRate;
        /* Predefined SUT value for time to wait for a retry of the validation
          process if a SECC is occupied by another running validation process */
        float PIXIT_EVCC_CMN_ValidationRetry;
        /* Indication for the implemented handling after connection loss (
          Option A: EV shall leave the logical network and shall wait for a new
          incoming matching trigger (control pilot X1 or X2 state),
          Option B: EV shall leave the logical network and shall restart the
          matching process after 'T_conn_resetup'. */
        CLHandling PIXIT_EVCC_AC_ConnectionLossHandling;
        /* Predefined SUT value for the parameter T_conn_resetup */
        float PIXIT_EVCC_AC_TconnResetup;
      }
    }
  }
}
#endif // __PIXIT_CFG_H__