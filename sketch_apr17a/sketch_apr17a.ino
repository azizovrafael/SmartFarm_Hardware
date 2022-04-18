#include "DHT.h"
#define DHTPIN A2     // Digital pin connected to the DHT sensor
#include <String.h>

#include <SoftwareSerial.h>

SoftwareSerial sim800l(2, 3); // RX,TX for Arduino and for the module it's TXD RXD, they should be inverted

#define button1 7 //Button pin, on the other pin it's wired with GND

bool button_State; //Button state
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

int sensorPin = A0; 
int sensorValue;  
int limit = 300; 


void setup()
{
 
  pinMode(button1, INPUT_PULLUP); //The button is always on HIGH level, when pressed it goes LOW
  sim800l.begin(9600);   //Module baude rate, this is on max, it depends on the version
  Serial.begin(9600);   
   dht.begin();
  delay(1000);
}
 
void loop()
{
  String cumle = ""; 
  int a = moniture();
  int t = temprature();
  String stringOne = String(a);
  String stringtu = String(t);
  cumle = "Nemislik: "+ stringOne + " Temprature: "+stringtu+"\n";
  Serial.print(cumle);

  delay(25000);
  
   SendSMS(cumle,"AT+CMGS=\"+994553366046\"\r");
   

   delay(28800000);

}
 
void SendSMS(String Cumle,String nomre)
{
  String cumle="aaaa";
  Serial.println("Sending SMS...");               //Show this message on serial monitor
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  sim800l.print(nomre);  //Your phone number don't forget to include your country code, example +212123456789"
  delay(500);
  sim800l.print(Cumle);       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(500);
  sim800l.print((char)26);// (required according to the datasheet)
  delay(500);
  sim800l.println();
  Serial.println("Text Sent.");
  delay(500);


}


int moniture(){
  sensorValue = analogRead(sensorPin); 
  sensorValue = map(sensorValue,680,0,0,100);

 return sensorValue+25;
  }

 
int temprature(){
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  return t;
  
}
 
