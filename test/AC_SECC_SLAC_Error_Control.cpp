namespace AC_SECC_SLAC_Error_Control
{
// import from TestCases_SECC_CmSlacParm all;
// import from TestCases_SECC_AttenuationCharacterization all;
// import from TestCases_SECC_CmValidate all;
// import from TestCases_SECC_CmSlacMatch all;
// import from TestCases_SECC_PLCLinkStatus all;
// import from TestCases_SECC_CmAmpMap all;
// import from Pics_15118 all;
// import from Pics_15118_3 all;
// import from Pixit_15118_3 all;
// import from Timer_15118 all;
// import from ComponentsAndPorts all;
void control()
{
  /** Test Group 1: SLAC timeouts **/
  if (PICS_CMN_CMN_SlacTimeouts)
  {
    // CmSlacParm ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_SECC_CMN_VTB_CmSlacParm_004())
    }
    if ((PIXIT_SECC_AC_InitialDutyCyle == dc5) &&
        (PICS_CMN_CMN_IdentificationMode == eIM))
    {
      execute(TC_SECC_AC_VTB_CmSlacParm_002())
    }
    // AttenuationCharacterization ++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_004())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_012())
    }
    // CmValidate ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmValidate_003())
    }
    // CmSlacMatch +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (PIXIT_SECC_CMN_CmValidate == none_)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_005())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_006())
    }
    // CmAmpMap +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (not PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_SECC_CMN_VTB_CmAmpMap_003())
    }
  }
  /** Test Group 2: Invalid SLAC data fields && messages **/
  if (PICS_CMN_CMN_InvalidSlacDataFieldsAndMessages)
  {
    // CmSlacParm ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_SECC_CMN_VTB_CmSlacParm_005())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_CmSlacParm_006())
    }
    // AttenuationCharacterization ++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_005())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_006())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_007())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_008())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_009())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_010())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_011())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_013())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_014())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_015())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_016())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_017())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_018())
    }
    // CmValidate ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmValidate_004())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmValidate_005())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmValidate_006())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmValidate_007())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmValidate_008())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmValidate_009())
    }
    if (PIXIT_SECC_CMN_CmValidate == none_)
    {
      execute(TC_SECC_CMN_VTB_CmValidate_010())
    }
    // CmSlacMatch +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (PIXIT_SECC_CMN_CmValidate == none_)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_007())
    }
    if (PIXIT_SECC_CMN_CmValidate == none_)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_009())
    }
    if (PIXIT_SECC_CMN_CmValidate == none_)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_011())
    }
    if (PIXIT_SECC_CMN_CmValidate == none_)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_013())
    }
    if (PIXIT_SECC_CMN_CmValidate == none_)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_015())
    }
    if (PIXIT_SECC_CMN_CmValidate == none_)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_017())
    }
    if (PIXIT_SECC_CMN_CmValidate == none_)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_019())
    }
    if (PIXIT_SECC_CMN_CmValidate == none_)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_021())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_008())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_010())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_012())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_014())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_016())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_018())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_020())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_022())
    }
    // CmAmpMap +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (not PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_SECC_CMN_VTB_CmAmpMap_004())
    }
    if (PICS_CMN_CMN_InitiateCmAmpMap && PIXIT_CMN_CMN_CmAmpMap)
    {
      execute(TC_SECC_CMN_VTB_CmAmpMap_005())
    }
  }
  /** Test Group 3: Invalid states && duty cycles **/
  if (PICS_CMN_CMN_InvalidStatesAndDutyCycles)
  {
    // CmSlacParm ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_SECC_CMN_VTB_CmSlacParm_007())
    }
    // AttenuationCharacterization ++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_SECC_CMN_VTB_AttenuationCharacterization_019())
    }
    // CmValidate ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmValidate_013())
    }
    // CmSlacMatch +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (PIXIT_SECC_CMN_CmValidate == none_)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_023())
    }
    if (PIXIT_SECC_CMN_CmValidate == cmValidate)
    {
      execute(TC_SECC_CMN_VTB_CmSlacMatch_024())
    }
    // PLCLinkStatus +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    if (true)
    {
      execute(TC_SECC_CMN_VTB_PLCLinkStatus_002())
    }
    if (true)
    {
      execute(TC_SECC_CMN_VTB_PLCLinkStatus_005())
    }
    if (PICS_SECC_CMN_Pause && PICS_CMN_CMN_CombinedTesting &&
        (PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp))
    {
      execute(TC_SECC_AC_VTB_PLCLinkStatus_004())
    }
    if (PIXIT_SECC_AC_InitialDutyCyle == dc5)
    {
      execute(TC_SECC_AC_VTB_PLCLinkStatus_005())
    }
    if ((PIXIT_SECC_AC_InitialDutyCyle == dc5) &&
        (PIXIT_SECC_AC_ConnectionLossHandling == optionA) &&
        (PICS_CMN_CMN_IdentificationMode == eIM) &&
        (PICS_SECC_CMN_EIMDone == afterPlugin))
    {
      execute(TC_SECC_AC_VTB_PLCLinkStatus_006())
    }
    if ((PIXIT_SECC_AC_InitialDutyCyle == dc5) &&
        (PIXIT_SECC_AC_ConnectionLossHandling == optionB) &&
        (PICS_CMN_CMN_IdentificationMode == eIM) &&
        (PICS_SECC_CMN_EIMDone == afterPlugin))
    {
      execute(TC_SECC_AC_VTB_PLCLinkStatus_007())
    }
    if (PIXIT_SECC_AC_InitialDutyCyle == dc100)
    {
      execute(TC_SECC_AC_VTB_PLCLinkStatus_011())
    }
  }
}
}
// import from Pixit_15118 all;