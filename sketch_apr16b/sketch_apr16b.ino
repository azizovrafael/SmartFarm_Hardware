#include "DHT.h"
#define DHTPIN A2     // Digital pin connected to the DHT sensor
#include <String.h>
#include <SoftwareSerial.h>
SoftwareSerial sim800l(2, 3);

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

int sensorPin = A0; 
int sensorValue;  
int limit = 300; 

void setup() {
  sim800l.begin(9600);
 Serial.begin(9600);
 dht.begin();
 Serial.println("Starting ...");

 delay(3000);
//  ReceiveMode();
//  Send_Starter();
 
}

void loop() {

  String cumle = ""; 
  int a = moniture();
  int t = temprature();
  String stringOne = String(a);
  String stringtu = String(t);
  cumle = "Nemislik: "+ stringOne + " Temprature: "+stringtu+"\n";
  
  Serial.print(cumle);
  ReceiveMode();
  Send_Starter();
 

 
 delay(3600000); 
}



int moniture(){
  sensorValue = analogRead(sensorPin); 
  sensorValue = map(sensorValue,680,0,0,100);

 return sensorValue;
  }

 
int temprature(){
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  return t;
  
}


void Serialcom() //This is used with ReceiveMode function, it's okay to use for tests with Serial monitor
{
  delay(500);
  while (Serial.available())
  {
    sim800l.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (sim800l.available())
  {
    Serial.write(sim800l.read());//Forward what Software Serial received to Serial Port
  }
}


void ReceiveMode() {      //Set the SIM800L Receive mode

  sim800l.println("AT"); //If everything is Okay it will show "OK" on the serial monitor
  Serialcom();
  sim800l.println("AT+CMGF=1"); // Configuring TEXT mode
  Serialcom();

  sim800l.print("AT+CSCS=UCS2\r");
  Serialcom();
  sim800l.println("AT+CNMI=2,2,0,0,0"); //Configure the SIM800L on how to manage the Received SMS... Check the SIM800L AT commands manual
  Serialcom();
  sim800l.print("AT+CMGD=1,4");
  Serialcom();
  delay(200);
}


void Send_Starter()
{
  Serial.println("Sending starter message...");     //Displays on the serial monitor...Optional
  sim800l.print("AT+CMGF=1\r");          //Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+994553366046\"\r");  //Your phone number don't forget to include your country code example +212xxxxxxxxx"
  delay(500);
  sim800l.print("Sistem Basladi");  //This string is sent as SMS        delay(500);
  sim800l.print((char)26);//Required to tell the module that it can send the SMS
  delay(500);
  sim800l.println();
  Serial.println("Starter Sent.");
  delay(500);
}
