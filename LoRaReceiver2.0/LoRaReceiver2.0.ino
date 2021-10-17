#include <SPI.h>
#include <LoRa.h>
#include <U8x8lib.h>

U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

// uncomment the section corresponding to your board
// BSFrance 2017 contact@bsrance.fr 

//  //LoR32u4 433MHz V1.0 (white board)
//  #define SCK     15
//  #define MISO    14
//  #define MOSI    16
//  #define SS      1
//  #define RST     4
//  #define DI0     7
//  #define BAND    433E6 
//  #define PABOOST true

//  //LoR32u4 433MHz V1.2 (white board)
//  #define SCK     15
//  #define MISO    14
//  #define MOSI    16
//  #define SS      8
//  #define RST     4
//  #define DI0     7
//  #define BAND    433E6 
//  #define PABOOST true 

  //LoR32u4II 868MHz or 915MHz (black board)
  #define SCK     15
  #define MISO    14
  #define MOSI    16
  #define SS      8
  #define RST     4
  #define DI0     7
  #define BAND    915E6
  #define PABOOST true 




void setup() {
  Serial1.begin(9600);
  Serial1.println("LoRa Receiver");
  LoRa.setPins(SS,RST,DI0);
  LoRa.begin(BAND,PABOOST );
  LoRa.setSpreadingFactor(10);           // ranges from 6-12,default 7 see API docs
  LoRa.enableCrc();

  u8x8.begin();
  u8x8.setFlipMode(3); // set number from 1 to 3, the screen word will rotary 180
}




void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    while (LoRa.available()) {
      u8x8
      .print((char)LoRa.read());
    }
    // print RSSI of packet
    Serial1.print("' with RSSI ");
    Serial1.println(LoRa.packetRssi());
  }

 
//User Display Output Begins
  u8x8.setFont(u8x8_font_chroma48medium8_r); //Max 15 Char
  u8x8.setCursor(0, 0); // char row, col - not pixel
  u8x8.print("RSSI ");
  u8x8.print(LoRa.packetRssi());
  u8x8.println((char)LoRa.read());


  
}
