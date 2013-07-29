#include "BandPassFilter.h"
#include "BandPassFilter.c"

BandPassFilter* filter;

void setup()
{
analogReadResolution(12);
analogWriteResolution(12);
ADC->ADC_MR = 0x103D0200;
//Serial.begin(115200);
filter = new BandPassFilter();
BandPassFilter_init(filter);
}

void loop()
{
int val = analogRead(0);
BandPassFilter_put(filter, val);
int filtered = BandPassFilter_get(filter);
filtered = filtered + 1400;
filtered = constrain(filtered,0,4095);
analogWrite(DAC1,filtered);

//Serial.println(filtered);
}
