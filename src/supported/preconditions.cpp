#include "supported/preconditions.hpp"
#include "supported/libfunctions.hpp"

namespace TestLib
{

using namespace LibFunctions_15118_3::generalFunctions;

VerdictValue PreConditions_SECC_15118_3::f_SECC_CMN_PR_StateA_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = pass;
  f_SECC_changeValidStateCondition(A);
  verdict = f_SECC_setState(A, v_HAL_61851_Listener);
  SECC_Tester::pt_HAL_61851_Port->clear();
  sleep(par_CMN_waitForNextHAL);
  verdict = f_SECC_setProximity(0);
  if ((PICS_SECC_CMN_EIMDone == beforePlugin) && vc_testCaseSpecific)
  {
    boolean v_result = f_SECC_CMN_EIMIdentification();
    if (v_result)
    {
      f_SECC_setEimStatus(v_result);
    }
  }
  return verdict;
}

// SECC
VerdictValue PreConditions_SECC_15118_3::f_SECC_CMN_PR_DisconnectDataLink_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_SECC_CMN_PR_StateA_001(v_HAL_61851_Listener);
  // generate Nid and Nmk
  vc_Nmk = f_randomHexStringGen(16);
  vc_Nid = fx_generateNID(vc_Nmk);
  verdict = f_SECC_CMN_TB_VTB_CmSetKey_001(true);
  return verdict;
}
VerdictValue PreConditions_SECC_15118_3::f_SECC_CMN_PR_SetProximityPilot_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_SECC_CMN_PR_DisconnectDataLink_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    if (vc_sleepAfterPlugOut)
    {
      sleep(par_SECC_waitForPlugin);
    }
    v_HAL_61851_Listener->stop();
    v_HAL_61851_Listener->start(f_SECC_HAL61851Listener(true));
    if (vc_activateNominal)
    {
      f_SECC_changeValidFrequencyRange(0, 0);
      f_SECC_changeValidDutyCycleRange(100, 100);
      vc_validDutyCycleLowerBound2 = 100;
      vc_validDutyCycleUpperBound2 = 100;
    }
    if (PICS_CMN_CMN_PlugType == type1)
    {
      verdict = f_SECC_setProximity(cc_proximity_type1);
    }
    else
    {
      if (PICS_CMN_CMN_ChargingMode == aC)
      {
        integer v_proximity_type2_AC;
        if (PICS_CMN_AC_CableCapability == capability13A)
        {
          v_proximity_type2_AC = cc_proximity_type2_AC_13A;
        }
        else if (PICS_CMN_AC_CableCapability == capability20A)
        {
          v_proximity_type2_AC = cc_proximity_type2_AC_20A;
        }
        else if (PICS_CMN_AC_CableCapability == capability32A)
        {
          v_proximity_type2_AC = cc_proximity_type2_AC_32A;
        }
        else
        {
          v_proximity_type2_AC = cc_proximity_type2_AC_63A;
        }
        verdict = f_SECC_setProximity(v_proximity_type2_AC);
      }
      else
      {
        verdict = f_SECC_setProximity(cc_proximity_type2_DC);
      }
    }
  }
  return verdict;
}

VerdictValue PreConditions_SECC_15118_3::f_SECC_CMN_PR_StateB_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_SECC_CMN_PR_SetProximityPilot_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    sleep(par_CMN_waitForNextHAL);
    f_SECC_changeValidStateCondition(valid);
    f_SECC_setState(vc_state, v_HAL_61851_Listener);
    if ((PICS_SECC_CMN_EIMDone == afterPlugin) && vc_testCaseSpecific)
    {
      f_SECC_setIsConfirmationFlagDC();
      verdict = f_SECC_confirmDutyCycle(v_HAL_61851_Listener, par_T_conn_max_comm, inconc);
      f_SECC_changeValidStateCondition(EorF);
      f_SECC_changeValidFrequencyRange(0, 0);
      f_SECC_changeValidDutyCycleRange(0, 0);
      f_SECC_setIsConfirmationFlagVoltage();
      boolean v_result = f_SECC_CMN_EIMIdentification();
      if (v_result)
      {
        f_SECC_setEimStatus(v_result);
      }
    }
    else if ((PICS_SECC_CMN_EIMDone == duringSlac) && vc_testCaseSpecific)
    {
      f_SECC_setIsConfirmationFlagDC();
      verdict = f_SECC_confirmDutyCycle(v_HAL_61851_Listener, par_T_conn_max_comm, inconc);
      if (verdict == pass)
      {
        if (PIXIT_SECC_AC_InitialDutyCyle == dc5)
        {
          f_SECC_changeValidDutyCycleRange(100, 100);
          vc_validDutyCycleLowerBound2 = 100;
          vc_validDutyCycleUpperBound2 = 100;
        }
        boolean v_result = f_SECC_CMN_EIMIdentification();
      }
    }
  }
  tc_TT_matching_repetition.start(par_TT_matching_repetition);
  return verdict;
}
VerdictValue PreConditions_SECC_15118_3::f_SECC_CMN_PR_CmSlacParm_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    verdict = f_SECC_CMN_TB_VTB_CmSlacParm_001(inconc);
  }
  return verdict;
}
VerdictValue PreConditions_SECC_15118_3::f_SECC_CMN_PR_AttenuationCharacterization_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_SECC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  // SECC_AttenuationCharacterization Behavior
  if (verdict == pass)
  {
    verdict = f_SECC_CMN_TB_VTB_AttenuationCharacterization_001(inconc);
  }
  return verdict;
}
VerdictValue PreConditions_SECC_15118_3::f_SECC_CMN_PR_CmValidate_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  // SECC_CmSlacMatch Behavior
  if (verdict == pass)
  {
    verdict = f_SECC_CMN_TB_VTB_CmValidate_001(v_HAL_61851_Listener, inconc);
  }
  return verdict;
}
VerdictValue PreConditions_SECC_15118_3::f_SECC_CMN_PR_CmSlacMatch_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict;
  if (PIXIT_SECC_CMN_CmValidate == cmValidate)
  {
    verdict = f_SECC_CMN_PR_CmValidate_001(v_HAL_61851_Listener);
  }
  else
  {
    verdict = f_SECC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  }
  // SECC_CmSlacMatch Behavior
  if (verdict == pass)
  {
    verdict = f_SECC_CMN_TB_VTB_CmSlacMatch_001(inconc);
  }
  return verdict;
}
VerdictValue PreConditions_SECC_15118_3::f_SECC_CMN_PR_CmSetKey_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_SECC_CMN_PR_CmSlacMatch_001(v_HAL_61851_Listener);
  // SECC_CmSetKey Behavior
  if (verdict == pass)
  {
    tc_TT_match_join.start(par_TT_match_join);
    verdict = f_SECC_CMN_TB_VTB_CmSetKey_001(false);
  }
  return verdict;
}
VerdictValue PreConditions_SECC_15118_3::f_SECC_CMN_PR_PLCLinkStatus_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_SECC_CMN_PR_CmSetKey_001(v_HAL_61851_Listener);
  // SECC_PLCLinkStatus Behavior
  if (verdict == pass)
  {
    verdict = f_SECC_CMN_TB_VTB_PLCLinkStatus_001(inconc);
    tc_TT_matching_repetition.stop();
  }
  return verdict;
}
VerdictValue PreConditions_SECC_15118_3::f_SECC_CMN_PR_CmAmpMap_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_SECC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  // EVCC_CmAmpMap Behavior
  if (verdict == pass)
  {
    if (PICS_CMN_CMN_InitiateCmAmpMap)
    {
      verdict = f_SECC_CMN_TB_VTB_CmAmpMap_001(inconc);
      if (getverdict == pass)
      {
        f_SECC_CMN_checkTXPowerLimitation();
      }
    }
    else
    {
      verdict = f_SECC_CMN_TB_VTB_CmAmpMap_002(inconc);
    }
  }
  return verdict;
}

using namespace LibFunctions_15118_3::generalFunctions;
// EVCC
VerdictValue PreConditions_EVCC_15118_3::f_EVCC_CMN_PR_SetPowerFlowConfiguration_001(void)
{
  VerdictValue verdict = pass;
  return verdict;
}
VerdictValue PreConditions_EVCC_15118_3::f_EVCC_CMN_PR_DisableControlPilot_001(void)
{
  VerdictValue verdict = f_EVCC_CMN_PR_SetPowerFlowConfiguration_001();
  verdict = f_EVCC_setPwmMode(vc_errorState);
  sleep(par_CMN_waitForNextHAL);
  verdict = f_EVCC_setProximity(0);
  return verdict;
}
VerdictValue PreConditions_EVCC_15118_3::f_EVCC_CMN_PR_CmSetKey_001(void)
{
  VerdictValue verdict = f_EVCC_CMN_PR_DisableControlPilot_001();
  // generate Nid and Nmk
  if (verdict == pass)
  {
    vc_Nmk = f_randomHexStringGen(32);
    vc_Nid = fx_generateNID(vc_Nmk);
    verdict = f_EVCC_CMN_TB_VTB_CmSetKey_001();
    f_EVCC_PLCNodeIsReadyForCommunication();
    sleep(par_EVCC_PLCNodeReady_delay);
  }
  return verdict;
}
VerdictValue PreConditions_EVCC_15118_3::f_EVCC_CMN_PR_SetProximityPilot_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_EVCC_CMN_PR_CmSetKey_001();
  if (verdict == pass)
  {
    v_HAL_61851_Listener->stop();
    v_HAL_61851_Listener->start(f_EVCC_HAL61851Listener(true));
    if (PICS_CMN_CMN_PlugType == type1)
    {
      verdict = f_EVCC_setProximity(cc_proximity_type1);
    }
    else
    {
      if (PICS_CMN_CMN_ChargingMode == aC)
      {
        integer v_proximity_type2_AC;
        if (PICS_CMN_AC_CableCapability == capability13A)
        {
          v_proximity_type2_AC = cc_proximity_type2_AC_13A;
        }
        else if (PICS_CMN_AC_CableCapability == capability20A)
        {
          v_proximity_type2_AC = cc_proximity_type2_AC_20A;
        }
        else if (PICS_CMN_AC_CableCapability == capability32A)
        {
          v_proximity_type2_AC = cc_proximity_type2_AC_32A;
        }
        else
        {
          v_proximity_type2_AC = cc_proximity_type2_AC_63A;
        }
        verdict = f_EVCC_setProximity(v_proximity_type2_AC);
      }
      else
      {
        verdict = f_EVCC_setProximity(cc_proximity_type2_DC);
      }
    }
  }
  return verdict;
}
VerdictValue PreConditions_EVCC_15118_3::f_EVCC_CMN_PR_EnableControlPilot_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_EVCC_CMN_PR_SetProximityPilot_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    sleep(par_CMN_waitForNextHAL);
    f_EVCC_changeValidStateCondition(E, valid);
    verdict = f_EVCC_setPwmMode(e_PosVolt12);
  }
  return verdict;
}
VerdictValue PreConditions_EVCC_15118_3::f_EVCC_CMN_PR_StateB_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_EVCC_CMN_PR_EnableControlPilot_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    timer statetimer = par_CMN_HAL_Timeout;
    verdict = f_EVCC_confirmState(valid, v_HAL_61851_Listener, statetimer, inconc);
  }
  tc_TT_EVSE_SLAC_init.start(par_TT_EVSE_SLAC_init_min);
  return verdict;
}
VerdictValue PreConditions_EVCC_15118_3::f_EVCC_CMN_PR_DutyCycle_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  integer v_oscOff = 100;
  VerdictValue verdict = f_EVCC_CMN_PR_StateB_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    sleep(vc_DutyCycleDelay);
    if (PICS_CMN_CMN_ChargingMode == aC)
    {
      if (vc_DutyCycle != v_oscOff)
      {
        verdict = f_EVCC_setDutyCycle(vc_DutyCycle);
        verdict = f_EVCC_setPwmMode(e_OscOn);
      }
    }
    else
    {
      verdict = f_EVCC_setDutyCycle(5);
      verdict = f_EVCC_setPwmMode(e_OscOn);
    }
    EVCC_Tester::pt_SLAC_Port->clear();
  }
  return verdict;
}
VerdictValue PreConditions_EVCC_15118_3::f_EVCC_CMN_PR_CmSlacParm_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_EVCC_CMN_PR_DutyCycle_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    verdict = f_EVCC_CMN_TB_VTB_CmSlacParm_001(inconc);
  }
  return verdict;
}
VerdictValue PreConditions_EVCC_15118_3::f_EVCC_CMN_PR_AttenuationCharacterization_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_EVCC_CMN_PR_CmSlacParm_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    verdict = f_EVCC_CMN_TB_VTB_AttenuationCharacterization_001(inconc);
  }
  return verdict;
}
VerdictValue PreConditions_EVCC_15118_3::f_EVCC_CMN_PR_CmValidate_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  if (verdict == passand PIXIT_EVCC_CMN_CmValidate == cmValidate)
  {
    verdict = f_EVCC_CMN_TB_VTB_CmValidate_001(v_HAL_61851_Listener, false, vc_DutyCycle, inconc);
  }
  return verdict;
}
VerdictValue PreConditions_EVCC_15118_3::f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_EVCC_CMN_PR_AttenuationCharacterization_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    verdict = f_EVCC_CMN_TB_VTB_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener, inconc);
  }
  return verdict;
}
VerdictValue PreConditions_EVCC_15118_3::f_EVCC_CMN_PR_PLCLinkStatus_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_EVCC_CMN_PR_CmValidateOrCmSlacMatch_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    verdict = f_EVCC_CMN_TB_VTB_PLCLinkStatus_001(inconc);
  }
  return verdict;
}
VerdictValue PreConditions_EVCC_15118_3::f_EVCC_CMN_PR_CmAmpMap_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  VerdictValue verdict = f_EVCC_CMN_PR_PLCLinkStatus_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    if (PICS_CMN_CMN_InitiateCmAmpMap)
    {
      verdict = f_EVCC_CMN_TB_VTB_CmAmpMap_001(inconc);
      if (getverdict == pass)
      {
        f_EVCC_CMN_checkTXPowerLimitation();
      }
    }
    else
    {
      verdict = f_EVCC_CMN_TB_VTB_CmAmpMap_002(inconc);
    }
  }
  return verdict;
}
}