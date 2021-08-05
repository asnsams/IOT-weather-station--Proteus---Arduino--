
#include<Wire.h>
#include <BlynkSimpleStream.h>

#include <DHT.h>
#define kpa2atm 0.00986923267
BlynkTimer timer;
char auth[]="BmvLmGz6n9ttWSyOYk12pvKhUS8u6NAx";
DHT dht1(2,DHT11);


// pin defs
int pressurePin = 0;
int rainPin=3;
int ldrPin=1;

// variables
int val;
float pkPa; // pressure in kPa
float pAtm; // pressure in Atm
int ldr;
float light;

void sendToBlynk(){
  int t4=dht1.readTemperature();
  int h4=dht1.readHumidity();
  int hic4=dht1.computeHeatIndex(t4,h4,false);
  
   /* get the pressure */
  val = analogRead(pressurePin);
  pkPa = ((float)val/(float)1023+0.095)/0.009;
  pAtm = kpa2atm*pkPa;
  int rain=digitalRead(rainPin);
  ldr = analogRead(ldrPin);
  Blynk.virtualWrite(V1,t4);
  Blynk.virtualWrite(V2,h4);
  Blynk.virtualWrite(V3,pkPa);
  Blynk.virtualWrite(V4,rain);
  Blynk.virtualWrite(V5,ldr);
  delay(500);
}
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Blynk.begin(Serial,auth);
dht1.begin();
pinMode(rainPin,OUTPUT);

timer.setInterval(1000L, sendToBlynk);
}
void loop() {
  // put your main code here, to run repeatedly:
Blynk.run();
timer.run();
delay(1000);
}
