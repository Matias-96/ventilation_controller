/*
 * SDP600.cpp
 *
 *  Created on: 25.9.2023
 *      Author: jpj1
 */

#include "SDP610.h"
#include <cstdint>

uint8_t SDP610::TRIGGER_MEASUREMENT = 0xF1;
uint8_t SDP610::SOFT_RESET = 0xFE;

SDP610::SDP610(
		LPC_I2C_T *i2c_peripheral,
		int _scl_port,
		int _scl_pin,
		int _scd_port,
		int _scd_pin,
		int altitude,
		uint8_t _address) :
		i2c(i2c_peripheral), address(_address){

	if(i2c != nullptr){
		Chip_IOCON_PinMuxSet(LPC_IOCON, _scl_port, _scl_pin, IOCON_DIGMODE_EN | I2C_MODE);
		Chip_IOCON_PinMuxSet(LPC_IOCON, _scd_port, _scd_pin, IOCON_DIGMODE_EN | I2C_MODE);
		Chip_SWM_EnableFixedPin(SWM_FIXED_I2C0_SCL);
		Chip_SWM_EnableFixedPin(SWM_FIXED_I2C0_SDA);

		/* Enable I2C clock and reset I2C peripheral - the boot ROM does not do this */
		Chip_I2C_Init(i2c);

		/* Setup clock rate for I2C */
		Chip_I2C_SetClockDiv(i2c, I2C_CLK_DIVIDER);

		/* Setup I2CM transfer rate */
		Chip_I2CM_SetBusSpeed(i2c, I2C_BITRATE);

		/* Enable Master Mode */
		Chip_I2CM_Enable(i2c);
	}
	set_altitude(altitude);
}

void SDP610::SetupXferRecAndExecute(uint8_t *txBuffPtr,
								   uint16_t txSize,
								   uint8_t *rxBuffPtr,
								   uint16_t rxSize)
{
	/* Setup I2C transfer record */
	i2cmXferRec.slaveAddr = address;
	i2cmXferRec.status = 0;
	i2cmXferRec.txSz = txSize;
	i2cmXferRec.rxSz = rxSize;
	i2cmXferRec.txBuff = txBuffPtr;
	i2cmXferRec.rxBuff = rxBuffPtr;

	Chip_I2CM_XferBlocking(i2c, &i2cmXferRec);
}

int SDP610::read(int &i2c_error) {
	if(i2c == nullptr){
		i2c_error = -1;
		return 0;
	}

	int pressure = 0;
	uint8_t read_data[2] = {0};
	SetupXferRecAndExecute(&TRIGGER_MEASUREMENT, 1, read_data, 2);
	if (i2cmXferRec.status == I2CM_STATUS_OK) {
		// Sensor sends MSB first, construct correct measurement
		int sensor_output = (((int)read_data[0]) << 8) | read_data[1];
		if(read_data[0] & (1 << 7)){
			sensor_output |= 0xFFFF0000;
		}
		pressure = (sensor_output / SCALE_FACTOR) * altitude_correction_factor;
	}

	i2c_error = i2cmXferRec.status;
	return pressure;
}

void SDP610::soft_reset(int &i2c_error){
	if(i2c == nullptr){
		i2c_error = -1;
		return;
	}
	SetupXferRecAndExecute(&SOFT_RESET, 1, nullptr, 0);
	i2c_error = i2cmXferRec.status;
	// After reset, do one dummy read because sensor's first
	//measurement after reset is not valid
	if(i2cmXferRec.status == I2CM_STATUS_OK){
		read(i2c_error);
	}
}

void SDP610::set_altitude(int altitude){

	if(altitude < 250) altitude_correction_factor = 0.95;
	else if(altitude < 425) altitude_correction_factor = 0.98;
	else if(altitude < 500) altitude_correction_factor = 1.00;
	else if(altitude < 750) altitude_correction_factor = 1.01;
	else if(altitude < 1500) altitude_correction_factor = 1.04;
	else if(altitude < 2250) altitude_correction_factor = 1.15;
	else if(altitude < 3000) altitude_correction_factor = 1.26;
	else altitude_correction_factor = 1.38;
}


