/*
  MHZ19.h - MH-Z19 CO2 sensor library for ESP-WROOM-02/32(ESP8266/ESP32) or Arduino
  version 1.0
  
  License MIT
*/

#ifndef _MHZ19
#define _MHZ19

#include "Arduino.h"
#include "SoftwareSerial.h"

enum MHZ19_UART_DATA
{
	PPM,
	TEMPERATURE,
	STAT
};

enum MHZ19_PWM_DATA
{
	CALC_2000_PPM,
	CALC_5000_PPM
};

enum MHZ19_POTOCOL
{
	UART,
	PWM
};

typedef struct measurement {
	int co2_ppm;
	int temperature;
	int state;
} measurement_t;


class MHZ19
{
  public:
	MHZ19();
	MHZ19(int rx, int tx);
	MHZ19(int pwm);
	virtual ~MHZ19();

	void begin(int rx, int tx);
	void begin(int pwm);
	void setAutoCalibration(boolean autocalib);
	void calibrateZero();
	void calibrateSpan(int ppm);
	int getStatus();
	measurement_t getMeasurement();
	int getPpmPwm();

	boolean isWarming();

  protected:
	void writeCommand(uint8_t com[]);
	void writeCommand(uint8_t com[], uint8_t response[]);

  private:
	uint8_t mhz19_checksum(uint8_t com[]);
	measurement_t getSerialData();
	void setPwmData(MHZ19_PWM_DATA type);

	static const int REQUEST_CNT = 8;
	static const int RESPONSE_CNT = 9;

	// serial command
	uint8_t getppm[REQUEST_CNT] = {0xff, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t zerocalib[REQUEST_CNT] = {0xff, 0x01, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t spancalib[REQUEST_CNT] = {0xff, 0x01, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t autocalib_on[REQUEST_CNT] = {0xff, 0x01, 0x79, 0xA0, 0x00, 0x00, 0x00, 0x00};
	uint8_t autocalib_off[REQUEST_CNT] = {0xff, 0x01, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00};
	
	// Serial Pins
	int _rx_pin = -1;
	int _tx_pin = -1;

	// Pwm Pin
	int _pwm_pin;

	// Pwm Data Flag
	uint8_t PWM_DATA_SELECT = MHZ19_PWM_DATA::CALC_2000_PPM;
};

#endif
