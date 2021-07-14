module AC_SECC_SLAC_Control
{
import from TestCases_SECC_CmSlacParm all;
import from TestCases_SECC_AttenuationCharacterization all;
import from TestCases_SECC_CmValidate all;
import from TestCases_SECC_CmSlacMatch all;
import from TestCases_SECC_CmAmpMap all;
import from TestCases_SECC_PLCLinkStatus all;
import from Pics_15118 all;
import from Pics_15118_3 all;
import from Pixit_15118_3 all;
import from ComponentsAndPorts all;
import from Timer_15118_3 all;
import from Timer_15118 all;
import from Pixit_15118 all;
  control
  {
    // CmSlacParm ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_SECC_CMN_VTB_CmSlacParm_001())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_CmSlacParm_002())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_CmSlacParm_003())
    }
    if ((PIXIT_SECC_AC_InitialDutyCyle == dc5) && (PICS_CMN_CMN_IdentificationMode == eIM) && (PICS_SECC_CMN_EIMDone == afterPlugin))
    {
      execute(TC_SECC_AC_VTB_CmSlacParm_001())
    }
    if ((PIXIT_SECC_AC_InitialDutyCyle == dc100) && (PICS_CMN_CMN_IdentificationMode == eIM) && (PICS_SECC_CMN_EIMDone == afterPlugin))
    {
      execute(TC_SECC_AC_VTB_CmSlacParm_003())
    }
    if ((PICS_CMN_CMN_IdentificationMode == eIM) && (PICS_SECC_CMN_EIMDone == beforePlugin))
    {
      execute(TC_SECC_AC_VTB_CmSlacParm_004())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_CmSlacParm_008())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_CmSlacParm_009())
    }
    // AttenuationCharacterization +++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_001())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_002())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_003())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_020())
    }
    // CmValidate ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmValidate_001())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmValidate_002())
    }
    if ((PIXIT_SECC_CMN_CmValidate == cmValidate) && PIXIT_SECC_CMN_ArchitectureValidationNotRequired)
    {
      execute(TC_SECC_CMN_VTB_CmValidate_011())
    }
    if ((PIXIT_SECC_CMN_CmValidate == cmValidate) && PIXIT_SECC_CMN_ArchitectureValidationNotRequired)
    {
      execute(TC_SECC_CMN_VTB_CmValidate_012())
    }
    // CmSlacMatch +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (PIXIT_SECC_CMN_CmValidate == none_)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_001())
    }
    if (PIXIT_SECC_CMN_CmValidate == none_)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_003())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_002())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_004())
    }
    // PLCLinkStatus ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (not PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_SECC_CMN_VTB_PLCLinkStatus_001())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_PLCLinkStatus_003())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_PLCLinkStatus_004())
    }
    if ((PIXIT_SECC_AC_InitialDutyCyle == dc5) && (PICS_CMN_CMN_IdentificationMode == eIM) && (PICS_SECC_CMN_EIMDone == duringSlac))
    {
      execute(TC_SECC_AC_VTB_PLCLinkStatus_001())
    }
    if (PICS_SECC_CMN_Pause && PICS_CMN_CMN_CombinedTesting && PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp)
    {
      execute(TC_SECC_AC_VTB_PLCLinkStatus_002())
    }
    if (PICS_SECC_CMN_Pause && PICS_CMN_CMN_CombinedTesting && PIXIT_CMN_CMN_WakeUp < PICS_CMN_CMN_WakeUp)
    {
      execute(TC_SECC_AC_VTB_PLCLinkStatus_003())
    }
    if (not PICS_SECC_CMN_Pause && PICS_CMN_CMN_CombinedTesting)
    {
      execute(TC_SECC_AC_VTB_PLCLinkStatus_008())
    }
    if ((PIXIT_SECC_AC_InitialDutyCyle == dc100) && (PICS_CMN_CMN_IdentificationMode == eIM) && (PICS_SECC_CMN_EIMDone == duringSlac))
    {
      execute(TC_SECC_AC_VTB_PLCLinkStatus_009())
    }
    if (PICS_SECC_CMN_Pause && PICS_CMN_CMN_CombinedTesting && PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp)
    {
      execute(TC_SECC_AC_VTB_PLCLinkStatus_010())
    }
    if (PICS_SECC_CMN_Pause && PICS_CMN_CMN_CombinedTesting && PICS_CMN_CMN_WakeUp < par_SECC_T_step_X1 && PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp)
    {
      execute(TC_SECC_AC_VTB_PLCLinkStatus_012())
    }
    // CmAmpMap +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_SECC_CMN_VTB_CmAmpMap_001())
    }
    if (not PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_SECC_CMN_VTB_CmAmpMap_002())
    }
    if (PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_SECC_CMN_VTB_CmAmpMap_006())
    }
    if (not PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_SECC_CMN_VTB_CmAmpMap_007())
    }
    if (not PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_SECC_CMN_VTB_CmAmpMap_008())
    }
  }
}