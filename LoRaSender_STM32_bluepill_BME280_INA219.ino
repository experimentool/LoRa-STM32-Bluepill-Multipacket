// Sketch name 'LoRaSender_STM32_bluepill_BME280_INA219.ino'
// Sketch sends multiple LoRa packets to LoRa receiver 
// Companion Sketch 'LoRaReceiver_STM32_bluepill.ino'
// RFM95 pins to bluepill pins: SCK-PA5, MISO-PA6, MOSI-PA7, DIO0-PA1, SS-PA4, RESET-PC13
// using modified Sandeep Mistry library 'LoRa.h' to 'LoRa_STM32.h' by Armtronix
// LoRa_STM32.h library is located in 'Documents/Arduino/libraries/arduino-LoRa-STM32-master'
// Also JAL modified Adafruit INA219.cpp library for a 75 millivolt shunt 30A.  That is why the INA219 libraries are attached to this sketch.
// I2C STM32 pins SCL-PB6, SDA-PB7
// WARNING: Keep your wiring leads short as the RFM95 module is very sensitive to stray capacity and noise.

#include <SPI.h>
#include <LoRa_STM32.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Wire.h>
#include "Adafruit_INA219.h"  
Adafruit_INA219 ina219; //I2C

Adafruit_BME280 bme; // I2C

int counter = 0;

String temper = String(8); // string used in degrees F
String atmos = String(8);  // string used in inHg
String hum = String(8); //string used in humidity
 
void setup() {
  if (!LoRa.begin(915E6)) {
    delay(500);
    while (1);
  }

Serial.begin(115200);

ina219.begin();

bool status;

  // default settings
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

}

void loop() {

  temper = ((bme.readTemperature() * 9 / 5 + 32)); // Let 'temper' string equal the read/calculated degrees F from the BME 280
  atmos = ((bme.readPressure() / 3389.39 + 0.587)); // Let 'atmos' string equal the read/calculated inHg sea level from BME 280
  hum = (bme.readHumidity());  // Let 'hum' string equal the read 'readHumidity' from the BME 280
   
   if (counter < 1) {
     Packet1();
      
  }

  if (counter == 1) {
    Packet1();
      
  }

  if (counter == 2) {
     Packet2();
      
  }

  if (counter == 3) {
     Packet2();
      
  }
  
  counter++;
  if (counter > 4) {
    counter = 0;
  }
  delay(5000);
}

  void Packet1() {
    
  LoRa.beginPacket();
  LoRa.print(temper);  LoRa.print(" degF          ");
  LoRa.print(atmos);  LoRa.print(" inHg          ");
  LoRa.print(hum);  LoRa.print(" pctRH        ");
  LoRa.endPacket();
  
  }

  void Packet2() {
 float shuntvoltage = 0;
 float busvoltage = 0;
 float current_mA = 0;
 
 float loadvoltage = 0;
 float power = 0;
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  float current_A = (current_mA / 1000);
  loadvoltage = busvoltage + (shuntvoltage / 1000);
//  power = busvoltage * (current_mA / 1000);
  power = busvoltage * current_A ;
  LoRa.beginPacket();
  LoRa.print(busvoltage);  LoRa.print(" V              ");
  LoRa.print(power);  LoRa.print(" W             ");
  // LoRa.print(current_mA); LoRa.print(" mA           ");
  LoRa.print(current_A); LoRa.print(" A         ");
  LoRa.endPacket();
  }
