#include "management/timer_cfg.hpp"

namespace TestLib
{
  namespace Timer_15118
  {
    namespace Timer_par_15118
    {
      // ------------------ Non-standardised CMN Processing timeouts -------
      float par_CMN_Transmission_Delay = 0.25;
      float par_CMN_HAL_Timeout = 2.0;
      float par_CMN_waitForNextHAL = 0.5;
      float par_CMN_Intern_PTC_Timeout = 0.4;
      float par_CMN_setKey = 3.0;
      // ------------------ Non-standardised EVCC Processing timeouts -------
      float par_EVCC_waitForNextTC = 2.0;
      // ------------------ Non-standardised SECC Processing timeouts -------
      float par_SECC_waitForNextTC = 20.0;
      float par_SECC_T_step_X1 = 3.0;
      float par_SECC_Pmax0W = 200.0;
    }
  }
  namespace Timer_15118_3
  {
    // using namespace DataStructure_SLAC;
    namespace Timer_par_15118_3
    {
      // ------------------ SLAC timeout ------------------------------
      float par_TT_match_response = 0.2;
      float par_TP_match_sequence = 0.1;
      float par_TP_EV_batch_msg_interval = 0.03;
      float par_TT_EV_atten_results = 1.2;
      float par_TT_EVSE_SLAC_init_min = 20.0;
      float par_TT_EVSE_SLAC_init_max = 50.0;
      float par_TT_EVSE_match_MNBC = 0.6;
      float par_TT_EVSE_match_session = 10.0;
      float par_TT_match_sequence = 0.4;
      float par_TT_match_join = 12.0;
      float par_TT_link_status_response = 5.0;
      float par_TT_matching_rate = 0.4;
      float par_TT_matching_repetition = 10.0;
      float par_TP_match_response = 0.1;
      float par_T_step_EF_min = 4.0;
      float par_T_step_EF_max = 8.0;
      float par_T_conn_max_comm = 8.0;
      float par_TT_polling_pause = 0.25;
      float par_TP_match_leave = 1.0;
      float par_TP_EV_vald_state_duration = 0.3;
      float par_T_vald_state_duration_max = 0.4;
      float par_TP_EV_vald_toggle = 2.0;
      float par_TT_amp_map_exchange = 0.2;
      float par_T_conn_resume = 6.0;
      // ------------------ Non-standardised CMN Processing timeouts --------
      float par_CMN_waitForKeyReset = 20.0;
      float par_CMN_waitForConnectionLoss = 5.0;
      // ------------------ Non-standardised SECC Processing timeouts --------
      float par_SECC_change_to_Nominal = 3.0;
      float par_SECC_EIM_Timeout = 10.0;
      float par_SECC_PLCNodeReady_delay = 1.0;
      float par_SECC_waitForEIMAuthorization = 10.0;
      float par_SECC_waitForPlugin = 600.0;
      // ------------------ Non-standardised EVCC Processing timeouts --------
      float par_EVCC_PLCNodeReady_delay = 15.0;
      float par_EVCC_setDC_delay = 1.0;
    }
  }
}