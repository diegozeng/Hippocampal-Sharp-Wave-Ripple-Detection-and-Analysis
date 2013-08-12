#include "BandPassFilter.h"
#include "BandPassFilter.c"

//The length of window to calculate power.
int samplesN = 50;
int micPin = 0;
int j = 0;
int buf[1180] = {0};// array length: determined by the sample length in a cycle.
BandPassFilter* filter;

void setup()
{
  analogReadResolution(12);
  analogWriteResolution(12);
  ADC->ADC_MR = 0x10380400;
  Serial.begin(115200);
  filter = new BandPassFilter();
  BandPassFilter_init(filter);
  attachInterrupt(3,interr,FALLING);
}

void loop()
{
  long filtpow = 0;
  //long start = millis();
  for(int k=0; k<samplesN; k++)
    {
    int val = analogRead(micPin);
    //var=(int)((val*3.3-2252.8)/2.2-1177);
    BandPassFilter_put(filter, val);
    int filtered = BandPassFilter_get(filter);
    filtpow += ((long)filtered*(long)filtered)/samplesN;
    
        //peak = max(peak, filtered);
    }
  //long end = millis();
  filtpow = (int)sqrt(filtpow);
  buf[j] = filtpow;
  analogWrite(DAC1,filtpow); 
  j=j+1;
  if(j==1179) // determined by the sample length in a cycle
  {
    j=0;
  }
  
  //float freq = ((float)samplesN * (float)1000) / ((float)end - (float)start);
  // Serial.println(freq);

}

void interr()
{
  for (int i = 0; i < j; i++)
  Serial.println(buf[i]);
}
