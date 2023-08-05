//Final IOT Code by Deepak
#define BLYNK_TEMPLATE_ID "TMPL3a9o5JEko"
#define BLYNK_TEMPLATE_NAME "Voltage Detection"
#define BLYNK_AUTH_TOKEN "Ra6l2YbEX9K6l3T1IGQSGla5Ko-9C05R"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
float correctionfactor = 3.5;
int analogueInput = 34;
float vout = 0.0;
float vin =0.0;

float R1=10000;
float R2=65757;
int value = 0;

 
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "IOT";  // type your wifi name
char pass[] = "12345678";  // type your wifi password
 
#define RAIN_SENSOR  4
BlynkTimer timer;
int flag=0;
void DetectVoltage()
{
  // int isButtonPressed = digitalRead(RAIN_SENSOR);
   value = analogRead(analogueInput);
  vout = (value*5.0) /1023.0;
  vin = abs(vout / (R2/(R1+R2)));

  vin = vin - correctionfactor;
  Serial.print("INPUT V =");
  Serial.println(vin,4);
 
  if (vin<10 && flag==0) {
 digitalWrite(2,LOW);
    Serial.println("Voltage is Suitable for the device");
     Blynk.logEvent("Highvoltage_alert","High Voltage detected!Power switced!");
    flag=1;
  }
  else if (vin>10)
  {
    flag=0;
     digitalWrite(2,LOW);
    Serial.println("HIGH VOLTAGE DETECTED! VOLTAGE SWITCED!");
  }
}

void setup(){
  
   pinMode(analogueInput,INPUT);
  Serial.begin(115200);
  Serial.print("Dc volt meter");
  pinMode(2,OUTPUT);

  Blynk.begin(auth, ssid, pass);
  //dht.begin();
  timer.setInterval(2500L, DetectVoltage);
}

void loop(){
  Blynk.run();
  timer.run();
}