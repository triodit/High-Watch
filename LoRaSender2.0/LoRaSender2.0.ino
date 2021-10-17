//#include <OneWire.h>
//#include <DallasTemperature.h>
#include <SPI.h>
#include <LoRa.h>

  //LoR32u4II 868MHz or 915MHz (black board)
  #define SCK     15
  #define MISO    14
  #define MOSI    16
  #define SS      8
  #define RST     4
  #define DI0     7
  #define BAND    915E6
  #define PABOOST true 

//  #define ONE_WIRE_BUS 10
//  OneWire oneWire(ONE_WIRE_BUS);  
//  DallasTemperature sensors(&oneWire);

int counter = 0;
int voltage_read = A0;
float voltage = 0;
const float VOLTAGE_FACTOR = 1.681759379042690815006468305304; //13v = 733 for USB  13v = 773 for junker


void setup() {
  LoRa.setPins(SS,RST,DI0);
  LoRa.begin(BAND,PABOOST);
  LoRa.setSpreadingFactor(10);           // ranges from 6-12,default 7 see API docs
  LoRa.enableCrc();
  //sensors.begin();
  Serial.begin(9600);

  pinMode(voltage, INPUT);
}

void loop() {
  
  //sensors.requestTemperatures(); 
  voltage = (analogRead(voltage_read) * VOLTAGE_FACTOR)/100;
  //Serial.println(voltage);
  
  
  // send packet
  LoRa.beginPacket();
  LoRa.print("Msg ");
  LoRa.print(counter);
  LoRa.print("   ");
  //LoRa.print(analogRead(voltage_read));
  LoRa.print(voltage);
  LoRa.print("V");
/*  LoRa.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  LoRa.print((char)176);//shows degrees character
  LoRa.println("F");
*/

  LoRa.endPacket();
  counter++;
  delay(1500);











  
}
