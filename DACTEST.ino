static int testsig[] = {
//insert test signal in decimal form here 
}



void setup()
{
  //ADC->ADC_MR = 0x103D0200;
  analogWriteResolution(12);
  //analogReadResolution(12);
  //Serial.begin(9600);
}

void loop()
{
  int i = 0;
  for(i=0;i<59000;i++)//59000 is the length of a sample signal, which can be changed according to the test signal. 
  {
    //test[i]=map(test[i],min,max,0,4095)//minium and maxium value of the test signal can be found by some methods.
    analogWrite(DAC1,testsig[i]); 
    delayMicroseconds(195);
  } 
   //int a=analogRead(0);
   // Serial.println(a);
}
