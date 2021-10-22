#include "management/pixit_cfg.hpp"

namespace TestLib
{
  namespace Pixit_15118
  {
    namespace PIXIT_15118
    {
      namespace PIXIT_CMN
      {
        float PIXIT_CMN_CMN_WakeUp = 200.0;
      }
      namespace PIXIT_EVCC_Tester
      {
        using namespace DataStructure_PIXIT_15118;
        Pause PIXIT_EVCC_CMN_Pause = Pause::unknown;
      }
    }
  }
  namespace Pixit_15118_3
  {
    namespace PIXIT_15118_3
    {
      namespace PIXIT_CMN_Tester
      {
        boolean PIXIT_CMN_CMN_CmAmpMap = false;
      }
      namespace PIXIT_SECC_Tester
      {
        using namespace DataStructure_PIXIT_15118_3;
        CmValidateSECC PIXIT_SECC_CMN_CmValidate = CmValidateSECC::none_;
        DutyCycle PIXIT_SECC_AC_InitialDutyCyle = DutyCycle::dc5;
        boolean PIXIT_SECC_CMN_ArchitectureValidationNotRequired = false;
        CLHandling PIXIT_SECC_AC_ConnectionLossHandling = CLHandling::optionA;
      }
      namespace PIXIT_EVCC_Tester
      {
        using namespace DataStructure_PIXIT_15118_3;
        CmValidateEVCC PIXIT_EVCC_CMN_CmValidate = CmValidateEVCC::unknown;
        ValidationFallbackHandling PIXIT_EVCC_CMN_FallbackValidationFailed = ValidationFallbackHandling::unknown;
        ValidationFallbackHandling PIXIT_EVCC_CMN_FallbackValidationNotRequired = ValidationFallbackHandling::unknown;
        ConcurrentValidationHandling PIXIT_EVCC_CMN_ConcurrentValidation = ConcurrentValidationHandling::unknown;
        boolean PIXIT_EVCC_CMN_TTMatchingRepetitionConfig = false;
        float PIXIT_EVCC_CMN_TTMatchingRepetition = 10.0;
        float PIXIT_EVCC_CMN_TTMatchingRate = 0.4;
        float PIXIT_EVCC_CMN_ValidationRetry = 1.0;
        CLHandling PIXIT_EVCC_AC_ConnectionLossHandling = CLHandling::optionA;
        float PIXIT_EVCC_AC_TconnResetup = 15.0;
      }
    }
  }
}