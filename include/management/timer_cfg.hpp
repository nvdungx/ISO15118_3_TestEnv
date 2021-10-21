#ifndef __TIMER_CFG_H__
#define __TIMER_CFG_H__
namespace TestLib
{
  namespace Timer_15118
  {
    namespace Timer_par_15118
    {
      // ------------------ Non-standardised CMN Processing timeouts -------
      extern float par_CMN_Transmission_Delay;
      extern float par_CMN_HAL_Timeout;
      extern float par_CMN_waitForNextHAL;
      extern float par_CMN_Intern_PTC_Timeout;
      extern float par_CMN_setKey;
      // ------------------ Non-standardised EVCC Processing timeouts -------
      extern float par_EVCC_waitForNextTC;
      // ------------------ Non-standardised SECC Processing timeouts -------
      extern float par_SECC_waitForNextTC;
      extern float par_SECC_T_step_X1;
      extern float par_SECC_Pmax0W;
    }
  }
  namespace Timer_15118_3
  {
    // using namespace DataStructure_SLAC;
    namespace Timer_par_15118_3
    {
      // ------------------ SLAC timeout ------------------------------
      extern float par_TT_match_response;
      extern float par_TP_match_sequence;
      extern float par_TP_EV_batch_msg_interval;
      extern float par_TT_EV_atten_results;
      extern float par_TT_EVSE_SLAC_init_min;
      extern float par_TT_EVSE_SLAC_init_max;
      extern float par_TT_EVSE_match_MNBC;
      extern float par_TT_EVSE_match_session;
      extern float par_TT_match_sequence;
      extern float par_TT_match_join;
      extern float par_TT_link_status_response;
      extern float par_TT_matching_rate;
      extern float par_TT_matching_repetition;
      extern float par_TP_match_response;
      extern float par_T_step_EF_min;
      extern float par_T_step_EF_max;
      extern float par_T_conn_max_comm;
      extern float par_TT_polling_pause;
      extern float par_TP_match_leave;
      extern float par_TP_EV_vald_state_duration;
      extern float par_T_vald_state_duration_max;
      extern float par_TP_EV_vald_toggle;
      extern float par_TT_amp_map_exchange;
      extern float par_T_conn_resume;
      // ------------------ Non-standardised CMN Processing timeouts --------
      extern float par_CMN_waitForKeyReset;
      extern float par_CMN_waitForConnectionLoss;
      // ------------------ Non-standardised SECC Processing timeouts --------
      extern float par_SECC_change_to_Nominal;
      extern float par_SECC_EIM_Timeout;
      extern float par_SECC_PLCNodeReady_delay;
      extern float par_SECC_waitForEIMAuthorization;
      extern float par_SECC_waitForPlugin;
      // ------------------ Non-standardised EVCC Processing timeouts --------
      extern float par_EVCC_PLCNodeReady_delay;
      extern float par_EVCC_setDC_delay;
    }
  }
}
#endif // __TIMER_CFG_H__