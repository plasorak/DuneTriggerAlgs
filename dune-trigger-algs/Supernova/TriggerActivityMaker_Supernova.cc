#include "dune-trigger-algs/Supernova/TriggerActivityMaker_Supernova.hh"
#include <chrono>

using pd_clock = std::chrono::duration<double, std::ratio<1, 50000000>>;
using namespace triggeralgs;

void TriggerActivityMakerSupernova::operator()(const TriggerPrimitive& input_tp,
                                                std::vector<TriggerActivity>& output_ta) {
  // Time measurement
  auto now = std::chrono::steady_clock::now();
  m_algorithm = (uint32_t)pd_clock(now.time_since_epoch()).count();

  int64_t tend = input_tp.time_start+input_tp.time_over_threshold;
    
  if (m_time_start==0) {
    m_tp_list.erase(m_tp_list.begin(), m_tp_list.end());
    m_tp_list.push_back(input_tp);
    m_time_start    = input_tp.time_start;
    m_time_end      = tend;
    m_time_peak     = input_tp.time_peak;
    m_channel_start = input_tp.channel;
    m_channel_end   = input_tp.channel;
    m_channel_peak  = input_tp.channel;
    m_adc_integral  = input_tp.adc_integral;
    m_adc_peak      = input_tp.adc_peak;
    m_detid         = input_tp.detid;
    return;
  }
    
  bool time_ok = is_time_consistent(input_tp);
  bool channel_ok = is_channel_consistent(input_tp);
    
  if (not time_ok and not channel_ok) {
    output_ta.push_back(MakeTriggerActivity());
    m_tp_list.erase(m_tp_list.begin(), m_tp_list.end());
    m_tp_list.push_back(input_tp);
    m_time_start    = input_tp.time_start;
    m_time_end      = tend;
    m_time_peak     = input_tp.time_peak;
    m_channel_start = input_tp.channel;
    m_channel_end   = input_tp.channel;
    m_channel_peak  = input_tp.channel;
    m_adc_integral  = input_tp.adc_integral;
    m_adc_peak      = input_tp.adc_peak;
    m_detid         = input_tp.detid;
    return;
  }

  if (input_tp.time_start < m_time_start)
    m_time_start = input_tp.time_start;

  if (tend > m_time_end)
    m_time_end = tend;

  if (input_tp.adc_peak > m_adc_peak) {
    m_time_peak    = input_tp.time_peak;
    m_adc_peak     = input_tp.adc_peak;
    m_channel_peak = input_tp.channel;
  }

  if (input_tp.channel > m_channel_end)
    m_channel_end = input_tp.channel;
    
  if (input_tp.channel < m_channel_start)
    m_channel_start = input_tp.channel;
    

  m_tp_list.push_back(input_tp);
  m_adc_integral += input_tp.adc_integral;
  m_detid        |= input_tp.detid;
}
