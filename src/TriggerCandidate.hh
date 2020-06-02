#pragma once
#include "CommonDef.hh"
#include "TriggerPrimitive.hh"

#include <bitset>
#include <cstdint>
#include <vector>

namespace DuneTriggers {
  struct TriggerCandidate {
    int64_t time_start = {0};
    int64_t time_end = {0};
    int64_t time_peak = {0};
    int channel_start = {0};
    int channel_end = {0};
    int channel_peak = {0};
    std::bitset<DuneTriggers::n_apa> apa = {};
    int adc_integral = {0};
    int adc_peak = {0};
  };
    
    // TriggerCandidate(std::vector<TriggerPrimitive>& prims):
    //   time_start   (std::numeric_limits<int>::max()),
    //   time_end     (0),
    //   time_peak    (0),
    //   channel_start(std::numeric_limits<int>::max()),
    //   channel_end  (0),
    //   channel_peak (0),
    //   apa          (),
    //   adc_integral (0),
    //   adc_peak     (0) {
    
    //   if (prims.empty()) {
    //     return;
    //   }
    
    //   for (auto const& it: prims) {
      
    //     if(it.channel<channel_start) {
    //       channel_start = it.channel;
    //     }
      
    //     if(it.channel>channel_end) {
    //       channel_end = it.channel;
    //     }
      
    //     if(it.time_start<time_start) {
    //       time_start = it.time_start;
    //     }

    //     if(it.time_start+it.time_over_threshold>time_end) {
    //       time_end = it.time_start+it.time_over_threshold;
    //     }

    //     if(it.adc_peak>adc_peak) {
    //       adc_peak = it.adc_peak;
    //       time_peak = it.time_peak;
    //       channel_peak = it.channel;
    //     }

    //     adc_integral += it.adc_integral;

    //     apa.set(it.apa);
    //   }

    // }

}