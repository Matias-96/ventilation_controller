/*
 * SDP600.h
 *
 *  Created on: 25.9.2023
 *      Author: jpj1
 */

#ifndef SDP610_H_
#define SDP610_H_

#include "board.h"


class SDP610 {
public:
	static const int MAX_PRESSURE_Pa = 125;
	SDP610(LPC_I2C_T *i2c_peripheral,
			int _scl_port = 0,
			int _scl_pin = 22,
			int _scd_port = 0,
			int _scd_pin = 23,
			int altitude = 0,
			uint8_t _address = 64);
	int read(int &i2c_error);
	void soft_reset(int &i2c_error);
	void set_altitude(int altitude);


private:
	LPC_I2C_T *i2c;
	I2CM_XFER_T i2cmXferRec;
	uint8_t address;
	float altitude_correction_factor;
	static const int I2C_CLK_DIVIDER = 40; 	/* I2C clock is set to 1.8MHz */
	static const int I2C_BITRATE = 100000; 	/* 100KHz I2C bit-rate */
	static const int I2C_MODE = 0; 			/* Standard I2C mode */
	static const int SCALE_FACTOR = 240;
	void SetupXferRecAndExecute(uint8_t *txBuffPtr,
							    uint16_t txSize,
							    uint8_t *rxBuffPtr,
							    uint16_t rxSize);

	// Command codes from datasheet
	static uint8_t TRIGGER_MEASUREMENT;
	static uint8_t SOFT_RESET;

};




#endif /* SDP610_H_ */
