#include "BandPassFilter.h"

static int filter_taps[BANDPASSFILTER_TAP_NUM] = {
  165039187,
  0,
  -379115666,
  0,
  651217292,
  0,
  -876974897,
  0,
  964886615,
  0,
  -876974897,
  0,
  651217292,
  0,
  -379115666,
  0,
  165039187
};

void BandPassFilter_init(BandPassFilter* f) {
  int i;
  for(i = 0; i < BANDPASSFILTER_TAP_NUM; ++i)
    f->history[i] = 0;
  f->last_index = 0;
}

void BandPassFilter_put(BandPassFilter* f, int input) {
  f->history[f->last_index++] = input;
  if(f->last_index == BANDPASSFILTER_TAP_NUM)
    f->last_index = 0;
}

int LowPassFilter_get(LowPassFilter* f) {
  long long acc = 0;
  int index = f->last_index, i;
  for(i = 0; i < BANDPASSFILTER_TAP_NUM; ++i) {
    index = index != 0 ? index-1 : BANDPASSFILTER_TAP_NUM-1;
    acc += (long long)f->history[index] * filter_taps[i];
  };
  return acc >> 32;
}
