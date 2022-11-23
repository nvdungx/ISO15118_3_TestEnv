namespace DC_EVCC_SLAC_Error_Control
{
// import from TestCases_EVCC_CmSlacParm all;
// import from TestCases_EVCC_AttenuationCharacterization all;
// import from TestCases_EVCC_CmValidate all;
// import from TestCases_EVCC_CmSlacMatch all;
// import from TestCases_EVCC_PLCLinkStatus all;
// import from TestCases_EVCC_CmAmpMap all;
// import from Pics_15118 all;
// import from Pics_15118_3 all;
// import from Pixit_15118_3 all;
// import from ComponentsAndPorts all;
void control()
{
  /** Test Group 1: SLAC timeouts **/
  if (PICS_CMN_CMN_SlacTimeouts)
  {
    // CmSlacParm ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacParm_002())
    }
    if (PIXIT_EVCC_CMN_TTMatchingRepetitionConfig)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacParm_010())
    }
    // AttenuationCharacterization ++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_AttenuationCharacterization_003())
    }
    // CmValidate ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_004())
    }
    if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_007())
    }
    if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_009())
    }
    // CmSlacMatch +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacMatch_003())
    }
    // CmAmpMap +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (not PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_EVCC_CMN_VTB_CmAmpMap_003())
    }
  }
  /** Test Group 2: Invalid SLAC data fields && messages **/
  if (PICS_CMN_CMN_InvalidSlacDataFieldsAndMessages)
  {
    // CmSlacParm ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacParm_003())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacParm_004())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacParm_005())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacParm_006())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacParm_007())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacParm_008())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacParm_009())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacParm_011())
    }
    // AttenuationCharacterization ++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_AttenuationCharacterization_004())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_AttenuationCharacterization_005())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_AttenuationCharacterization_006())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_AttenuationCharacterization_007())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_AttenuationCharacterization_008())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_AttenuationCharacterization_009())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_AttenuationCharacterization_010())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_AttenuationCharacterization_011())
    }
    // CmValidate ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_005())
    }
    if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_006())
    }
    if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_008())
    }
    if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_010())
    }
    if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_011())
    }
    if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_012())
    }
    if ((PIXIT_EVCC_CMN_CmValidate == cmValidate) &&
        (PIXIT_EVCC_CMN_FallbackValidationFailed == continue_))
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_013())
    }
    if ((PIXIT_EVCC_CMN_CmValidate == cmValidate) &&
        (PIXIT_EVCC_CMN_FallbackValidationFailed == terminate))
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_014())
    }
    if ((PIXIT_EVCC_CMN_CmValidate == cmValidate) &&
        (PIXIT_EVCC_CMN_ConcurrentValidation == iterate))
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_019())
    }
    // CmSlacMatch +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacMatch_004())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacMatch_005())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacMatch_006())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacMatch_007())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacMatch_008())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacMatch_009())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacMatch_010())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_CmSlacMatch_011())
    }
    // CmAmpMap +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (not PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_EVCC_CMN_VTB_CmAmpMap_004())
    }
    if (PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_EVCC_CMN_VTB_CmAmpMap_005())
    }
  }
  /** Test Group 3: Invalid states && duty cycles **/
  if (PICS_CMN_CMN_InvalidStatesAndDutyCycles)
  {
    // AttenuationCharacterization ++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_AttenuationCharacterization_012())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_AttenuationCharacterization_013())
    }
    // CmValidate ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_020())
    }
    if (PIXIT_EVCC_CMN_CmValidate == cmValidate)
    {
      execute(TC_EVCC_CMN_VTB_CmValidate_021())
    }
    // PLCLinkStatus +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_PLCLinkStatus_002())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_PLCLinkStatus_003())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_PLCLinkStatus_004())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_PLCLinkStatus_006())
    }
    if (true)
    {
      execute(TC_EVCC_CMN_VTB_PLCLinkStatus_007())
    }
  }
}
}