# MHZ19 
Arduino IDE library for operating the MH-Z19 CO2 sensor in ESP-WROOM-02/32(ESP8266/ESP32) or Arduino  
version 0.3

# Credits and license  
License MIT

# How to use

* Include this library to your Arduino IDE.
* Wiring MH-Z19 sensor to your Arduino or ESP-WROOM-02/32(ESP8266/ESP32).

    MH-Z19 Vout to Arduino Vout(5V)  
    MH-Z19 GND  to Arduino GND  
    MH-Z19 Tx   to Arduino Digital Pin (Serial Rx pin)  
    MH-Z19 Rx   to Arduino Digital Pin (Serial Tx pin)  
    other MH-Z19 pins are not used.  
    
* Wiring the MH-Z19 through PWM use a PWM pin from your Arduino,ESP8266 or ESP32
* Read sample source code. It's very simple !

# caution

* This library is testing only ESP-WROOM-02/32(ESP8266/ESP32) boards. if you can't execute this library on your arduino (or clone) boards, please contact me.

* The Sensor through PWM can only implement getPPM(MHZ19_POTOCOL::PWM), so in order to use all the functionalities use UART protocol.

# MHZ19 library function

## Constractor

* MHZ19  
  normal constractor. if you use this constractor, you must execute begin() function after this constractor execute.

* MHZ19(int rx, int tx)  
  setting rx and tx pin, and initialize Software Serial.
  
* MHZ19(int pwm_pin)
  settings pwm pin.

## public function for UART

* void begin(int rx, int tx)  
  setting rx and tx pin, and initialize Software Serial.
  
* void setAutoCalibration(bool autocalib)  
  MH-Z19 has automatic calibration procedure. the MH-Z19 executing automatic calibration, its do zero point(stable gas environment (400ppm)) judgement.
  The automatic calibration cycle is every 24 hours after powered on.  
  If you use this sensor in door, you execute `setAutoCalibration(false)`.

* void calibrateZero()  
  execute zero point calibration. 
  if you want to execute zero point calibration, the MH-Z19 sensor must work in stable gas environment (400ppm) for over 20 minutes and you execute this function.

* void calibrateSpan(int ppm)  
  execute span point calibration.
  if you want to execute span point calibration, the MH-Z19 sensor must work in between 1000 to 2000ppm level co2 for over 20 minutes and you execute this function.
  
* int getPPM(MHZ19_POTOCOL::UART)  
  get co2 ppm.
  
* int getPPM(MHZ19_POTOCOL::PWM)  
  get co2 ppm.
  
* int getTemperature()  
  get temperature (MH-Z19 hidden function?  this function is not support.)

* int getStatus()  
  get ths MH-Z19 sensor status value (but I don't know what this value is. this function do not support, too.)

* bool isWarming()  
  check the MH-Z19 sensor is warming up.

# link
* MH-Z19 Data sheet  
  http://www.winsen-sensor.com/d/files/PDF/Infrared%20Gas%20Sensor/NDIR%20CO2%20SENSOR/MH-Z19%20CO2%20Ver1.0.pdf

* MH-Z19B Data sheet  
  http://www.winsen-sensor.com/d/files/infrared-gas-sensor/mh-z19b-co2-ver1_0.pdf

# history
* ver. 0.1: closed version.
* ver. 0.2: first release version.
* ver. 0.3: support ESP-WROOM-32(ESP32)
* ver. 0.4: Implementing PWM readings and refactor library use.

# Example Code

```
#include <Arduino.h>
#include "MHZ19.h"

const int rx_pin = 13; //Serial rx pin no
const int tx_pin = 15; //Serial tx pin no
const int pwmpin = 14;
MHZ19 *mhz19_uart = new MHZ19(rx_pin,tx_pin);
MHZ19 *mhz19_pwm = new MHZ19(pwmpin);

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  setup
  ----------------------------------------------------------*/
void setup()
{
    Serial.begin(115200);
    mhz19_uart->begin(rx_pin, tx_pin);
    mhz19_uart->setAutoCalibration(false);
    while (mhz19_uart->isWarming())
    {
        Serial.print("MH-Z19 now warming up...  status:");
        Serial.println(mhz19_uart->getStatus());
        delay(1000);
    }
}

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
  ----------------------------------------------------------*/
void loop()
{
    int co2ppm = mhz19_uart->getPPM(MHZ19_POTOCOL::UART);
    int temp = mhz19_uart->getTemperature();

    Serial.print("co2: ");
    Serial.println(co2ppm);
    Serial.print("temp: ");
    Serial.println(temp);

    co2ppm = mhz19_pwm->getPPM(MHZ19_POTOCOL::PWM);
    Serial.print("co2: ");
    Serial.println(co2ppm);
    

    delay(5000);
}
```
