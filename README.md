# MHZ19
Arduino IDE library for operating the MH-Z19 and MH-Z19B CO2 sensor 
on ESP-WROOM-02/32(ESP8266/ESP32) or Arduino  
version 0.5

Main work was done by crisap94

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

* The Sensor through PWM can only implement getPpmPwm(), so in order to use all the functionalities use UART protocol.

# MHZ19 library function

## Constructor

* MHZ19  
  normal constructor. if you use this constructor, you must execute begin() function after this constructor.

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
  
* measurement_t getMeasurement()  
  receive a struct with members co2_ppm, temperature (MH-Z19 hidden function? not mentioned in the datasheet) and state (same as temperature, but seems not to be present in MH-Z19B). If the sensor is connected state = 0.
  
* int getPpmPwm()  
  get co2 ppm.

* int getStatus()  
  get ths MH-Z19 sensor status value (MH-Z19 hidden function? not mentioned in the datasheet)

* bool isWarming()  
  check the MH-Z19 sensor is warming up. (MH-Z19 hidden function? not mentioned in the datasheet, but seems not to be present in MH-Z19B)

# link
* MH-Z19 Data sheet  
  http://www.winsen-sensor.com/d/files/PDF/Infrared%20Gas%20Sensor/NDIR%20CO2%20SENSOR/MH-Z19%20CO2%20Ver1.0.pdf

* MH-Z19B Data sheet  
  http://www.winsen-sensor.com/d/files/infrared-gas-sensor/mh-z19b-co2-ver1_0.pdf
  
* A newer datasheet is available here
  https://www.winsen-sensor.com/d/files/MH-Z19B.pdf

# history
* ver. 0.1: closed version. - crisap94
* ver. 0.2: first release version. - crisap94
* ver. 0.3: support ESP-WROOM-32(ESP32) - crisap94
* ver. 0.4: Implementing PWM readings and refactor library use. - crisap94
* ver. 0.5: Refactored library to take advantage of all uart measurements per read - sebastianbergt

# todo

* SoftwareSerial uart communication is not always working well in version 0.4 and 0.5. Potentially due to instantiating it only when it is needed.

# Example Code

```c++
/*----------------------------------------------------------
    MH-Z19 CO2 sensor  SAMPLE
  ----------------------------------------------------------*/

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
    delay(3000); // Issue #14
    Serial.print("MH-Z19 now warming up...  status:");
    Serial.println(mhz19_uart->getStatus());
    delay(1000);
}

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
  ----------------------------------------------------------*/
void loop()
{
    measurement_t m = mhz19_uart->getMeasurement();

    Serial.print("co2: ");
    Serial.println(m.co2_ppm);
    Serial.print("temp: ");
    Serial.println(m.temperature);

    int co2ppm = mhz19_pwm->getPpmPwm();
    Serial.print("co2: ");
    Serial.println(co2ppm);
    
    delay(5000);
}
```
