#include "BandPassFilter.h"
#include "BandPassFilter.c"

int samplesN = 50;
int micPin = 0;
int j = 0;
BandPassFilter* filter;

void setup()
{
  analogReadResolution(12);
  analogWriteResolution(12);
  ADC->ADC_MR = 0x10380400;
  Serial.begin(115200);
  filter = new BandPassFilter();
  BandPassFilter_init(filter);
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
    //buf[k]=buf[k+1]
    filtpow += ((long)filtered*(long)filtered)/samplesN;

    }
  //long end = millis();
  filtpow = (int)sqrt(filtpow);
  analogWrite(DAC1,filtpow); 
  buf[j] = filtpow;
  j=j+1;
}

void interr()
{
  for (int i = 0; i < j; i++)
  Serial.println(buf[i])
}
