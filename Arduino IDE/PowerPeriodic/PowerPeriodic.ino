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
    val = map(val,681,3413,0,4095); //Solve DAC output limitation.(1/6~5/6 Vref)
    val = int(val);
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
  //delay(10);
  float k=0;
  float x=0;
  float y;
  Serial.println("The power sequence is:");
  for (int i = 10; i < j; i++)
  {
  Serial.println(buf[i]);
  k+=buf[i];
  }
  k=k/(j-10);
  //Serial.print("The Mean value is ");
  //Serial.println(k);
  for (int i = 10; i < j; i++)
  {
    x+= (buf[i]-k)*(buf[i]-k);
  }
  x=sqrt(x/(j-10));
  //Serial.print("The SD value is ");
  //Serial.println(x);
  y=k+6*x;
  //Serial.print("The Therhold value is ");
  //Serial.print(y);
  Serial.println("The pulse sequence is:");
  for (int i = 10; i < j; i++)
  {
    if(buf[i]<y)
      buf[i]=0;
    else
      buf[i]=150;
    Serial.println(buf[i]);
  }
  Serial.println("The therhold value is:");
  Serial.print(y);
}
