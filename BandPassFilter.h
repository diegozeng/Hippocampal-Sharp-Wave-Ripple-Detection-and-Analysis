#ifndef BANDPASSFILTER_H_
#define BANDPASSFILTER_H_

/*

sampling frequency: 5000 Hz

fixed point precision: 32 bits

* 0 Hz - 125 Hz
  gain = 0
  desired attenuation = -60 dB
  actual attenuation = n/a

* 175 Hz - 225 Hz
  gain = 1
  desired ripple = 5 dB
  actual ripple = n/a

* 275 Hz - 2500 Hz
  gain = 0
 desired attenuation = -60 dB
  actual attenuation = n/a

*/

#define BANDPASSFILTER_TAP_NUM 364

typedef struct {
  int history[BANDPASSFILTER_TAP_NUM];
  unsigned int last_index;
} BandPassFilter;

void BandPassFilter_init(BandPassFilter* f);
void BandPassFilter_put(BandPassFilter* f, int input);
int BandPassFilter_get(BandPassFilter* f);

#endif
