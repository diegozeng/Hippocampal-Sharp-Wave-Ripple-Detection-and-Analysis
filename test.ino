#include "BandPassFilter.h"
#include "BandPassFilter.c"

//The number of samples to buffer before analyzing them
int samplesN = 1000;
int micPin = 0;

BandPassFilter* filter;

void setup(){
  analogReadResolution(12);
  ADC->ADC_MR |= 0x800;
  Serial.begin(115200);
  filter = new BandPassFilter();
  BandPassFilter_init(filter);
}

void loop(){
  long pow = 0;
  long filtpow = 0;
  int peak = 0;
  long start = millis();
  for(int k=0; k<samplesN; k++){
    int val = analogRead(micPin);
    BandPassFilter_put(filter, val);

    int filtered = BandPassFilter_get(filter);

    pow += ((long)val*(long)val)/samplesN;
    filtpow += ((long)filtered*(long)filtered)/samplesN;
    peak = max(peak, filtered);
  }
  long end = millis(); 
  float freq = ((float)samplesN * (float)1000) / ((float)end - (float)start);

  Serial.print(freq);
  Serial.print(" ");
  Serial.print(pow);
  Serial.print(" ");
  Serial.print(filtpow);
  Serial.print(" ");
  Serial.println(peak);
}
