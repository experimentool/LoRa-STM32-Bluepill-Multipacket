This project uses LoRa RFM95 transceiver modules operating at 915 MHz. STM32 Bluepill microcontrollers are used for both the Sender and Receiver.  Both Sender and Receiver modules are described in this project. The RFM95 modules utilize SPI communication with the STM Bluepill controllers.
The Sender transmits multiple packets of data from a solar panel.  The first packet sends the voltage, current and watts from the panel utilizing an I2C INA219 power monitor sensor module.  The next packet sends temperature, relative humidity and atmospheric pressure utilizing an I2C BME280 sensor module.  The data is formatted before transmission so the characters sent to the LoRa receiver will be displayed correctly on the 2004 LCD. The Code is written in C++ and the Aruino IDE was used for programming.  The STM32 Bluepill modules were programmed for USB operation prior to using the Arduino IDE.  
The C++ code has been supplied for both the Sender and Receiver.  The Adafruit library for the INA219 has been modified to use a 75 millivolt external shunt so that current up to 30 Amps can be measured.  You must remove the 100 milliohm resistor from the INA219 module to get corrrect readings.
The LoRa Sender schematic has been included.  The LoRa Receiver is a much simpler schematic.  Connections from the RFM95 module via SPI  to the STM32 Bluepill just like the Sender.  The INA219 and the BME280 modules are obviously not used in the Receiver.  The LCD module 2004 connects to the STM32 Bluepill I2C bus. Two jpg pics of the receiver display text are included.
If you should decide to utilize this project, the user assumes all responsibility for the results and personal safety.
