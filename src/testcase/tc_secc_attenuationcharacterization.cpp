#include "testcase/tc_secc_attenuationcharacterization.hpp"

#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)
namespace TestCases_SECC_AttenuationCharacterization
{
// import from DataStructure_SLAC all;
// import from TestBehavior_SECC_AttenuationCharacterization all;
// import from ComponentsAndPorts all;
// import from Configurations_15118_3 all;
// import from PreConditions_SECC_15118_3 all;
// import from PostConditions_SECC_15118_3 all;
// import from Templates_CMN_CmAttenCharRsp all;
// import from Templates_CMN_SlacPayloadHeader all;
// import from Templates_CMN_CmStartAttenCharInd all;
// import from LibFunctions_15118_3 { group generalFunctions;}
// import from TestBehavior_SECC_CmSlacParm all;

VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_001(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_002(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_002();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_003(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_003(1);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_004(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_004();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_005(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_005(
        m_CMN_CMN_SlacPayloadHeaderInvalid_001(),
        md_CMN_CMN_Acvarfield_001(
            par_testSystem_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_006(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_005(
        m_CMN_CMN_SlacPayloadHeaderInvalid_002(),
        md_CMN_CMN_Acvarfield_001(
            par_testSystem_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_007(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_005(
        m_CMN_CMN_SlacPayloadHeader_001(), md_CMN_CMN_Acvarfield_002(
                                               "000000000000", vc_RunID,
                                               "0000000000000000000000000000000000",
                                               "0000000000000000000000000000000000",
                                               "00"));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_008(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    RunID_TYPE v_RunID = f_randomHexStringGen(16);
    if (v_RunID != vc_RunID)
    {
      f_SECC_CMN_TB_VTB_AttenuationCharacterization_005(
          m_CMN_CMN_SlacPayloadHeader_001(),
          md_CMN_CMN_Acvarfield_002(
              par_testSystem_mac, v_RunID,
              "0000000000000000000000000000000000",
              "0000000000000000000000000000000000",
              "00"));
    }
    else
    {
      setverdict(inconc, "Invalid runID is equal to current runID.")
    };
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_009(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_005(
        m_CMN_CMN_SlacPayloadHeader_001(),
        md_CMN_CMN_Acvarfield_002(
            par_testSystem_mac, vc_RunID,
            "0000000000000000000000000000000001",
            "0000000000000000000000000000000000",
            "00"));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_010(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_005(
        m_CMN_CMN_SlacPayloadHeader_001(),
        md_CMN_CMN_Acvarfield_002(
            par_testSystem_mac, vc_RunID,
            "0000000000000000000000000000000000",
            "0000000000000000000000000000000001",
            "00"));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_011(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_005(
        m_CMN_CMN_SlacPayloadHeader_001(),
        md_CMN_CMN_Acvarfield_002(
            par_testSystem_mac, vc_RunID,
            "0000000000000000000000000000000000",
            "0000000000000000000000000000000000",
            "FF"));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_012(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_006();
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_013(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_007(
        md_CMN_CMN_CmStartAttenCharInd_001(
            m_CMN_CMN_SlacPayloadHeaderInvalid_001(),
            vc_Num_sounds, vc_Time_out, "01",
            par_testSystem_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_014(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_007(
        md_CMN_CMN_CmStartAttenCharInd_001(
            m_CMN_CMN_SlacPayloadHeaderInvalid_002(),
            vc_Num_sounds, vc_Time_out, "01",
            par_testSystem_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_015(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_007(
        md_CMN_CMN_CmStartAttenCharInd_001(
            m_CMN_CMN_SlacPayloadHeader_001(),
            "00", vc_Time_out, "01",
            par_testSystem_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_016(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_007(
        md_CMN_CMN_CmStartAttenCharInd_001(
            m_CMN_CMN_SlacPayloadHeader_001(),
            vc_Num_sounds, "00", "01",
            par_testSystem_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_017(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_007(
        md_CMN_CMN_CmStartAttenCharInd_001(
            m_CMN_CMN_SlacPayloadHeader_001(),
            vc_Num_sounds, vc_Time_out, "00",
            par_testSystem_mac, vc_RunID));
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_018(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    RunID_TYPE v_RunID = f_randomHexStringGen(16);
    if (v_RunID != vc_RunID)
    {
      f_SECC_CMN_TB_VTB_AttenuationCharacterization_007(
          md_CMN_CMN_CmStartAttenCharInd_001(
              m_CMN_CMN_SlacPayloadHeader_001(),
              vc_Num_sounds, vc_Time_out, "01",
              par_testSystem_mac, v_RunID));
    }
    else
    {
      setverdict(inconc, "Invalid runID is equal to current runID.")
    };
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_019(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_008(v_HAL_61851_Listener);
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
VerdictValue TC_SECC_CMN_VTB_AttenuationCharacterization_020(void) // runs on SECC_Tester system SystemSECC
{
  HAL_61851_Listener v_HAL_61851_Listener;
  VerdictValue preConVerdict;
  VerdictValue verdict;
  AttenProfile_TYPE v_attenuation_list;
  // -------------- Pre Conditions-------------------------------------------------------
  f_SECC_CMN_PR_InitConfiguration_SLAC_001(v_HAL_61851_Listener, system);
  preConVerdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    f_SECC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
    if (getverdict == pass)
    {
      v_attenuation_list = vc_attenuation_list;
      f_SECC_CMN_Reset_001(v_HAL_61851_Listener);
    }
    if (getverdict == pass)
    {
      f_SECC_CMN_TB_VTB_CmSlacParm_001(fail);
    }
    if (getverdict == pass)
    {
      f_SECC_CMN_TB_VTB_AttenuationCharacterization_001(fail);
    }
    if (getverdict == pass)
    {
      f_SECC_CMN_compareAttenuationValues_001(v_attenuation_list,
                                              vc_attenuation_list);
    }
  }
  else
  {
    SLOGI("PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  f_SECC_CMN_PO_ShutdownConfiguration_SLAC_001(v_HAL_61851_Listener, system);
}
} // namespace TestCases_SECC_AttenuationCharacterization