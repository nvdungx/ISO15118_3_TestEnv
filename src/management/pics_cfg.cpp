#include "management/pics_cfg.hpp"

namespace TestLib
{
  namespace Pics_15118
  {
    using namespace DataStructure_PICS_15118;
    namespace PICS_15118
    {
      namespace PICS_CMN
      {
        boolean PICS_CMN_CMN_CombinedTesting = false;
        ChargingMode PICS_CMN_CMN_ChargingMode = ChargingMode::aC;
        IdentificationMode PICS_CMN_CMN_IdentificationMode = IdentificationMode::eIM;
        PlugType PICS_CMN_CMN_PlugType = PlugType::type2;
        CableCapabilityACType PICS_CMN_AC_CableCapability = CableCapabilityACType::capability32A;
        float PICS_CMN_CMN_WakeUp = 300.0;
      }
      namespace PICS_SECC_Tester
      {
        boolean PICS_SECC_CMN_Pause = false;
        EIMDone PICS_SECC_CMN_EIMDone = EIMDone::v2gAuthorization;
      }
      namespace PICS_EVCC_Tester
      {
        ZeroPow PICS_EVCC_CMN_PmaxSchedulewithZeroPow = ZeroPow::none_;
      }
    }
  }
  namespace Pics_15118_3
  {
    namespace PICS_15118_3
    {
      namespace PICS_CMN
      {
        boolean PICS_CMN_CMN_InitiateCmAmpMap = true;
        boolean PICS_CMN_CMN_SlacTimeouts = true;
        boolean PICS_CMN_CMN_InvalidSlacDataFieldsAndMessages = true;
        boolean PICS_CMN_CMN_InvalidStatesAndDutyCycles = true;
      }
    }
  }
}