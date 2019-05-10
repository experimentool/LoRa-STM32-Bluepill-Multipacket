// April 2019 Sketch name 'LoRaReceiver_STM32_bluepill.ino'
// The following 3 LoRa sender sketches will work with this receiver sketch.
// 1. Companion Sketch name 'LoRaSender_STM32_bluepill.ino'
// 2. Companion Sketch name 'LoRaSender_STM32_bluepill_BME280.ino'
// 3. Companion Sketch name 'LoRaSender_STM32_bluepill_BME280_INA219.ino'
// RFM95 pins to bluepill pins: SCK-PA5, MISO-PA6, MOSI-PA7, DIO0-PA1, SS-PA4, RESET-PC13
// using modified Sandeep Mistry library 'LoRa.h' to 'LoRa_STM32.h' by Armtronix
// LoRa_STM32.h library is located in Documents/Arduino/libraries/arduino-LoRa-STM32-master
// I2C STM32 pins SCL-PB6, SDA-PB7
// LCD I2C 1602 or 2004 display - 2/4 lines, 16/20 characters per line

#include <SPI.h>
#include <LoRa_STM32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// Set the LCD address to 0x27 OR 0x3F for a 16/20 chars and 2/4 line display
// This LCD will display characters exactly as sent by the LoRa Sender
LiquidCrystal_I2C lcd(0x27, 20, 4);
//LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  Serial.begin(9600);
  //  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(915E6)) {
    delay(500);
    //  Serial.println("Starting LoRa failed!");
    while (1);
  }

  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.clear();
  lcd.print("LoRa receive ");
  lcd.setCursor(0, 1);
  lcd.print("915 MHz");

  delay(5000);

  lcd.clear();
  lcd.setCursor(0, 0);

}

void loop() {
  
  
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    //    Serial.print("Received packet '");
    lcd.clear();
    // read packet
    while (LoRa.available()) {
      //  Serial.print((char)LoRa.read());
      lcd.print((char)LoRa.read());
            
    }

  lcd.setCursor(0, 3);
  lcd.print(LoRa.packetRssi()); lcd.print("  RSSI");
    // print RSSI of packet
   // Serial.print(LoRa.packetRssi());
   // Serial.println(" RSSI");

  }
 
}
