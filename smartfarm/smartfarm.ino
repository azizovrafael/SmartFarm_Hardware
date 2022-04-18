#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT");
  updateSerial();
  delay(1000);

  mySerial.println("AT+CSCS=UCS2\r");
  updateSerial();
  delay(1000);


  mySerial.println("AT+CMGS=\"+994553366046\"\r"); // 1)
  updateSerial();
  mySerial.print("https://Shool"); // 2) text content 
  updateSerial();
  mySerial.write(30); // 3)
}

void loop() {
  updateSerial();
}

// For data transmission from Serial to Software Serial port & vice versa
void updateSerial() {
  delay(500);
  while (Serial.available()) {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }

  while (mySerial.available()) {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}




//#include "DHT.h"
//#define DHTPIN A2     // Digital pin connected to the DHT sensor
//
//#define DHTTYPE DHT11   // DHT 11
//
//DHT dht(DHTPIN, DHTTYPE);
//
//void setup() {
//  Serial.begin(9600);
//  Serial.println(F("DHTxx test!"));
//
//  dht.begin();
//}
//
//void loop() {
//  // Wait a few seconds between measurements.
//  delay(2000);
//
//  int t = temprature();
//  Serial.print(F("Temperature: "));
//  Serial.print(t);
//  Serial.print(F("C \n"));
//  
//}
//
//int temprature(){
//  
//  float h = dht.readHumidity();
//  float t = dht.readTemperature();
//  float f = dht.readTemperature(true);
//
//  float hif = dht.computeHeatIndex(f, h);
//  float hic = dht.computeHeatIndex(t, h, false);
//
//  return t;
//  
//}




















//int sensorPin = A0; 
//int sensorValue;  
//int limit = 300; 
//
//void setup() {
// Serial.begin(9600);
// 
//}
//
//void loop() {
//
// int a = moniture();
// Serial.println(a);
// 
// 
// 
// delay(1000); 
//}
//
//
//
//int moniture(){
//  sensorValue = analogRead(sensorPin); 
//  sensorValue = map(sensorValue,680,0,0,100);
//
// return sensorValue;
//  }
