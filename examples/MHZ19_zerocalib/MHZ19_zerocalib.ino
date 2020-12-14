/*----------------------------------------------------------
    MH-Z19 CO2 sensor  Zero calibration SAMPLE
  ----------------------------------------------------------*/

#include <MHZ19.h>

const int rx_pin = 4;  //Serial rx pin no
const int tx_pin = 5;  //Serial tx pin no

const int waitingMinutes = 30;  //waiting 30 minutes

MHZ19 mhz19(rx_pin,tx_pin); 

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  setup
  ----------------------------------------------------------*/
void setup() {
  Serial.begin(9600);
  mhz19.begin(rx_pin, tx_pin);
  mhz19.setAutoCalibration(false);
  delay(3000);
  Serial.println();
}

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
  ----------------------------------------------------------*/
long cnt = 0;
const long waitingSeconds = waitingMinutes * 60L;
void loop() {
  if ( ++cnt % 60 == 0) {
    Serial.print(cnt / 60); Serial.println("min.");
    Serial.print("co2: "); Serial.print(mhz19.getPPM()); Serial.println("ppm now.");
  } else {
    Serial.print(".");
  }
  delay(1000);

  if (cnt > waitingSeconds) {
    Serial.println("");
    mhz19.calibrateZero();
    Serial.println("1st zero calibration now .");

    delay(60000);
    mhz19.calibrateZero();  // Just in case
    Serial.println("2nd zero calibration now .");

    for ( int i = 0; i < 10; i++) {
      measurement_t m = mhz19.getMeasurement();
      Serial.print("co2: "); Serial.print(m.co2_ppm); Serial.println("ppm now.");
      delay(10000);
    }
    cnt = 0;
    return;
  }

}

