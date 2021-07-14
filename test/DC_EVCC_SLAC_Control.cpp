module DC_EVCC_SLAC_Control
{
import from TestCases_EVCC_CmSlacParm all;
import from TestCases_EVCC_AttenuationCharacterization all;
import from TestCases_EVCC_CmValidate all;
import from TestCases_EVCC_CmSlacMatch all;
import from TestCases_EVCC_PLCLinkStatus all;
import from TestCases_EVCC_CmAmpMap all;
import from TestCases_EVCC_CmValidateOrCmSlacMatch all;
import from Pics_15118 all;
import from Pics_15118_3 all;
import from Pixit_15118_3 all;
import from Timer_15118_3 all;
import from ComponentsAndPorts all;
import from Timer_15118 all;
import from Pixit_15118 all;
import from Timer_15118_2 all;
  control
  {
    // CmSlacParm ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacParm_001())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacParm_012())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacParm_013())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacParm_014())
    }
    // AttenuationCharacterization +++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_AttenuationCharacterization_001())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_AttenuationCharacterization_002())
    }
    // CmValidate ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_001())
    }
    if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_002())
    }
    if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_003())
    }
    if ((PIXIT_EVCC_CMN_CmValidate == cmValidate) &&
        (PIXIT_EVCC_CMN_FallbackValidationFailed == skip))
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_015())
    }
    if ((PIXIT_EVCC_CMN_CmValidate == cmValidate) &&
        (PIXIT_EVCC_CMN_FallbackValidationNotRequired == continue_))
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_016())
    }
    if ((PIXIT_EVCC_CMN_CmValidate == cmValidate) &&
        (PIXIT_EVCC_CMN_FallbackValidationNotRequired == skip))
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_017())
    }
    if ((PIXIT_EVCC_CMN_CmValidate == cmValidate) &&
        (PIXIT_EVCC_CMN_ConcurrentValidation == retry))
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_018())
    }
    // CmSlacMatch +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacMatch_001())
    }
    if (PIXIT_EVCC_CMN_CmValidate == none_)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacMatch_002())
    }
    if (PIXIT_EVCC_CMN_CmValidate == unknown)
    {
      execute(TC_EVCC_CMN_VTB_CmValidateOrCmSlacMatch_001())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacMatch_012())
    }
    // PLCLinkStatus ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (not PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_EVCC_CMN_VTB_PLCLinkStatus_001())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_PLCLinkStatus_005())
    }
    if ((PIXIT_EVCC_CMN_Pause == pause) && PICS_CMN_CMN_CombinedTesting &&
        (PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp))
    {
      execute(TC_EVCC_DC_VTB_PLCLinkStatus_001())
    }
    if ((PIXIT_EVCC_CMN_Pause == pause) && PICS_CMN_CMN_CombinedTesting &&
        (PIXIT_CMN_CMN_WakeUp < PICS_CMN_CMN_WakeUp))
    {
      execute(TC_EVCC_DC_VTB_PLCLinkStatus_002())
    }
    if ((PIXIT_EVCC_CMN_Pause == none_) && PICS_CMN_CMN_CombinedTesting)
    {
      execute(TC_EVCC_DC_VTB_PLCLinkStatus_003())
    }
    if ((PICS_EVCC_CMN_PmaxSchedulewithZeroPow == sleepWithoutCharge) &&
        PICS_CMN_CMN_CombinedTesting &&
        (par_SECC_Pmax0W < PICS_CMN_CMN_WakeUp))
    {
      execute(TC_EVCC_DC_VTB_PLCLinkStatus_004())
    }
    if ((PICS_EVCC_CMN_PmaxSchedulewithZeroPow == sleepAfterCharge) &&
        PICS_CMN_CMN_CombinedTesting &&
        (par_SECC_Pmax0W < PICS_CMN_CMN_WakeUp))
    {
      execute(TC_EVCC_DC_VTB_PLCLinkStatus_005())
    }
    // CmAmpMap +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_EVCC_CMN_VTB_CmAmpMap_001())
    }
    if (not PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_EVCC_CMN_VTB_CmAmpMap_002())
    }
    if (PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_EVCC_CMN_VTB_CmAmpMap_006())
    }
    if (PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_EVCC_CMN_VTB_CmAmpMap_007())
    }
    if (PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_EVCC_CMN_VTB_CmAmpMap_008())
    }
  }
}