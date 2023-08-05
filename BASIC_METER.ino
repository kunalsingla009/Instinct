float correctionfactor = 1;
int analogueInput = A0;
float vout = 0.0;
float vin =0.0;

float R1=30000;
float R2=7500;
int value = 0; 
void setup(){
  pinMode(analogueInput,INPUT);
  Serial.begin(9600);
  Serial.print("Dc volt meter");
  pinMode(7,OUTPUT);
}
void loop(){
  value = analogRead(analogueInput);
  vout = (value*5.0) /1023.0;
  vin = abs(vout / (R2/(R1+R2)));

  vin = vin - correctionfactor;
  Serial.print("INPUT V =");
  Serial.println(vin,4);
  if(vin<10){
    digitalWrite(7,HIGH);
    Serial.println("Voltage is Suitable for the device");
    
  }
  else if(vin>10){
    digitalWrite(7,LOW);
    Serial.println("HIGH VOLTAGE DETECTED! VOLTAGE SWITCED!");
}
  delay(500);
  
}