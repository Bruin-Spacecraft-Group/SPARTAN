//data sheet and other info about sensor can be referenced here: https://www.st.com/resource/en/datasheet/lsm6ds33.pdf

#ifndef LSM6DS33_H

#define LSM6DS33_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include "sensor.h"
#include "../globals.h"
#include "../constants.h"

namespace spartan {
// Available settings


enum AccelRange { _2g=0b0000, _4g=0b1000, _8g=0b1100, _16g=0b0100}; 	// (00: ±2 g; 01: ±16 g; 10: ±4 g; 11: ±8 g)
enum AccelAAFreq { _400hz=0b00, _200hz=0b01, _100hz=0b10, _50hz=0b11 };	// (00: 400 Hz; 01: 200 Hz; 10: 100 Hz; 11: 50 Hz)
enum GyroRange { _125dps=0b0010, _250dps=0b0000, _500dps=0b0100, _1000dps=0b1000, _2000dps=0b1100}; 	
// first two digits(00: 250 dps; 01: 500 dps; 10: 1000 dps; 11: 2000 dps)  third: 125 dps. Default value: 0 (0: disabled; 1: enabled) fourth: 0
enum ODR { odr_12hz=0b0001, odr_26Hz=0b0010, odr_52Hz=0b0011, odr_104Hz=0b0100, odr_208Hz=0b0101, odr_416Hz=0b0110, odr_833Hz=0b0111, odr_1660Hz=0b1000, // Gyro ODR only up to 1660, Accel has the following two
odr_3330Hz=0b1001, odr_6660Hz=0b1010};

class LSM6DS33 : public Sensor
{
public:
	// vector template 
	template<typename T> struct vector {
		T x, y, z;
	};

	struct offsets {
		float _temp_offset = 0;
		vector<float> _accel_offsets; // 1, 2, 3 are offsets that are added to the value, 4 is a scale factor applied.
		vector<float> _gyro_offsets;  // Same as above
	};
	
	// IMU settings
	// Change defaults here

	struct lsm6Settings {
		AccelRange accelRange = _4g;
		AccelAAFreq accelAAFreq = _400hz;
		GyroRange gyroRange = _500dps;
		ODR accel_odr = odr_1660Hz;
		ODR gyro_odr = odr_1660Hz;
	} m_settings;

	offsets m_offsets = {0, {.x=0, .y=0, .z=0}, {.x=0, .y=0, .z=0}};
	


	bool writeReg(uint8_t* buffer, unsigned short size) {
		mraa::Result msg = m_i2c.write(buffer, size);

		// Error handling
		if (msg == mraa::SUCCESS) 
			return true;
		else if (msg == mraa::ERROR_INVALID_PARAMETER)
			std::cerr << "Invalid parameter." << std::endl;
		else if (msg == mraa::ERROR_INVALID_HANDLE)
			std::cerr << "ERROR_INVALID_HANDLE" << std::endl;
		else if (msg == mraa::ERROR_NO_RESOURCES)
			std::cerr << "ERROR_NO_RESOURCES" << std::endl;
		else if (msg == mraa::ERROR_INVALID_RESOURCE)
			std::cerr << "ERROR_INVALID_RESOURCE" << std::endl;
		else if (msg == mraa::ERROR_INVALID_QUEUE_TYPE)
			std::cerr << "ERROR_INVALID_QUEUE_TYPE" << std::endl;
		else if (msg == mraa::ERROR_NO_DATA_AVAILABLE)
			std::cerr << "ERROR_NO_DATA_AVAILABLE" << std::endl;
		else if (msg == mraa::ERROR_INVALID_PLATFORM)
			std::cerr << "ERROR_INVALID_PLATFORM" << std::endl;
		else if (msg == mraa::ERROR_PLATFORM_NOT_INITIALISED)
			std::cerr << "ERROR_PLATFORM_NOT_INITIALISED" << std::endl;
		else if (msg == mraa::ERROR_UNSPECIFIED)
			std::cerr << "ERROR_UNSPECIFIED" << std::endl;
		
		return false;
	}

	void setMultipliers() {
		switch (m_settings.accelRange) {
			case _2g: _accel_multiplier = accel_multiplier[0]; break;
			case _4g: _accel_multiplier = accel_multiplier[1]; break;
			case _8g: _accel_multiplier = accel_multiplier[2]; break;
			case _16g: _accel_multiplier = accel_multiplier[3]; break;
		}

		switch (m_settings.gyroRange) {
			case _125dps: _gyro_multiplier = gyro_multiplier[0]; break;
			case _250dps: _gyro_multiplier = gyro_multiplier[1]; break;
			case _500dps: _gyro_multiplier = gyro_multiplier[2]; break;
			case _1000dps: _gyro_multiplier = gyro_multiplier[3]; break;
			case _2000dps: _gyro_multiplier = gyro_multiplier[3]; break;
		}
	}

	bool updateSettings() {

		// Update multiplier constant

		setMultipliers();

		// Accelerometer settings
		m_buffer[0] = CTRL1_XL;
		m_buffer[1] = (m_settings.accel_odr << 4) | m_settings.accelRange | m_settings.accelAAFreq;

		if (!writeReg(m_buffer, 2))
			return false;

		m_buffer[0] = CTRL2_G;
		m_buffer[1] = (m_settings.gyro_odr << 4) | m_settings.gyroRange;

		if (!writeReg(m_buffer, 2))
			return false;

		
		return true;
	}

	bool updateSettings(lsm6Settings settings) {
		m_settings = settings;
		return updateSettings();
	}

	uint8_t lsm6Address;

	
	LSM6DS33(	int busID, 
				int lsm6ID,		//  Either 0 or 1 (can only connect 2 lsm6ds33 modules)
				lsm6Settings settings
			): Sensor(busID, lsm6ID), 
				m_i2c(busID,true), 
				m_settings(settings)  // raw=true, disable pinmapper for board
	{
		if (lsm6ID)
			lsm6Address = HIGH_ADDRESS;
		else 
			lsm6Address = LOW_ADDRESS;
		setMultipliers();
	}

	LSM6DS33(	int busID, 
				int lsm6ID		//  Either 0 or 1 (can only connect 2 lsm6ds33 modules)
			): Sensor(busID, lsm6ID), 
				m_i2c(busID,true)
	{
		if (lsm6ID)
			lsm6Address = HIGH_ADDRESS;
		else 
			lsm6Address = LOW_ADDRESS;
		setMultipliers();
	}


	virtual int powerOn()
	{
		if (m_status == STATUS_IDLE)
			return RESULT_SUCCESS;

		//set I2C address
		
		if (m_i2c.address(lsm6Address) != mraa::SUCCESS)
		{
			std::cerr << "Unable to set I2C address." << std::endl;
			return ERROR_ADDR;
		}

		// Update settings for accelerometer and gyroscope
		if (!updateSettings()) {
			std::cerr << "Update setting failed" << std::endl;
			return ERROR_ADDR;
		}

		// CTRL3_C has default 1 on IF_INC page 49 in datasheet
		m_buffer[0] = CTRL3_C;
		m_buffer[1] = 0x04;
		if (!writeReg(m_buffer, 2))
		{
			std::cerr << "Unable to write GYRO_POWER_ON to LSM6DS33." << std::endl;
			return ERROR_POWER;
		}
		
		//run first update of sensor
		if (poll() == false)
		{
			std::cerr << "Unable to initial poll LSM6DS33." << std::endl;
			return ERROR_POLL;
		}

		m_status = STATUS_IDLE;

		return RESULT_SUCCESS;
	}

	virtual int powerOff()
	{
		if (m_status == STATUS_OFF)
			return RESULT_SUCCESS;

		//set I2C address
		if (m_i2c.address(lsm6Address) != mraa::SUCCESS)
		{
			std::cerr << "Unable to set I2C address." << std::endl;
			return ERROR_ADDR;
		}

		//send "Power Off" command for accelerometer
		m_buffer[0] = CTRL1_XL;
		m_buffer[1] = POWER_OFF;

		if (!writeReg(m_buffer, 2))
		{
			std::cerr << "Unable to write POWER_OFF to LSM6DS33's Accelerometer." << std::endl;
			return ERROR_POWER;
		}

		//send "Power Off" command for gyroscope
		m_buffer[0] = CTRL2_G;
		m_buffer[1] = POWER_OFF;

		if (!writeReg(m_buffer, 2))
		{
			std::cerr << "Unable to write POWER_OFF to LSM6DS33's Gyroscope." << std::endl;
			return ERROR_POWER;
		}

		m_status = STATUS_OFF;

		return RESULT_SUCCESS;
	}

	//returns RESULT_FALSE if no new data, RESULT_SUCCESS if member data was updated with latest reading, ERROR in the case of an error
	
	
	virtual bool poll()
	{
		if (m_status == STATUS_OFF)
			return ERROR_INVALID_STATUS;

		if (hasNewData() == RESULT_FALSE)
			//std::cerr << "No new data" << std::endl;
			return RESULT_FALSE;

		//set I2C address
		if (m_i2c.address(lsm6Address) != mraa::SUCCESS)
		{
			std::cerr << "Unable to set I2C address." << std::endl;
			return ERROR_ADDR;
		}

		//read temp,x,y,z (14 bytes) into buffer
		if (m_i2c.readBytesReg(OUT_TEMP_L, m_buffer, BUFFER_SIZE) == -1)
		{
			std::cerr << "Unable to read data bytes starting from LSM6DS33_OUT_TEMP_L." << std::endl;
			return ERROR_POLL;
		}

		//record rawacceleration values using data reads for x,y,z respectively
		//DATAx0 is the least significant byte, and DATAx1 is the most significant byte
		//conversion of raw sensor data into relevant values based on constant offset values
		m_temp = ((m_buffer[1] << 8) | m_buffer[0]);
		
		m_gyro.x = ((m_buffer[3] << 8) | m_buffer[2]);
		m_gyro.y = ((m_buffer[5] << 8) | m_buffer[4]);
		m_gyro.z = ((m_buffer[7] << 8) | m_buffer[6]);

		m_accel.x = ((m_buffer[9] << 8) | m_buffer[8]); 
		m_accel.y = ((m_buffer[11] << 8) | m_buffer[10]);
		m_accel.z = ((m_buffer[13] << 8) | m_buffer[12]);

		return RESULT_SUCCESS;
	}

	
	int hasNewData()
	{
		//NOTE: STATUS_REG on lSM6DS33 used to check if data is available for temp/gyro/accel
		if (m_status == STATUS_OFF)
			return RESULT_FALSE;

		//set I2C address 
		if (m_i2c.address(lsm6Address) != mraa::SUCCESS)
		{
			std::cerr << "Unable to set I2C address." << std::endl;
			return ERROR_ADDR;
		}
		if (m_i2c.readBytesReg(STATUS_REG,m_buffer,1) == -1)
			return ERROR_READ;

		uint8_t temp = 0;

		if ((m_buffer[0] & 0x7) > temp)
			return RESULT_SUCCESS;
		else {
			std::cout << "Status Read " << m_buffer[0] << std::endl;
			return RESULT_FALSE;
		}
			
	}

	//virtual bool longPoll() { return false; /*dummy*/}
	//call poll() over a longer period of time, averaging out the values (maybe allow time input functionality, or just do poll 10 times and average out the values, storing result into rawAccel array)
	//"poll","read","get"; reads raw data from sensor and returns it; maybe into a file? or an input stream? or a member variable of the class/struct? and then preprocess function can pull from that?
	//rawData type is a placeholder for now; will return raw sensor data

	virtual void printSensorInfo()
	{
		std::cout << "======================================" << std::endl;
		std::cout << "Type: LSM6DS33" << std::endl;
		std::cout << "Number: " << getInstance() << std::endl;
		std::cout << "Status:     " << getStatus() << std::endl;
		std::cout << "I2C BusID: " << getBusID() << std::endl;
		std::cout << "======================================" << std::endl;
	}

	void printRawValues()
	{
		std::cout << "======================================" << std::endl;
		std::cout << "Temp: " << std::setw(6) << m_temp << std::endl;
		std::cout << "AccelX: " <<  std::setw(6) << m_accel.x << std::endl;
		std::cout << "AccelY: " <<  std::setw(6) << m_accel.y << std::endl;
		std::cout << "AccelZ: " <<  std::setw(6) << m_accel.z << std::endl;
		std::cout << "GyroX: " <<  std::setw(6) << m_gyro.x << std::endl;
		std::cout << "GyroY: " <<  std::setw(6) << m_gyro.y << std::endl;
		std::cout << "GyroZ: " <<  std::setw(6) << m_gyro.z << std::endl;
		std::cout << "======================================" << std::endl;
	}
	
	void printEscapedRawValues(int lines) {
		printRawValues();
		std::cout << "\033[100D" << std::flush;
		std::cout << "\033[" << lines << "A" << std::flush;
	
	}

    const float accel_multiplier[4] = {0.061, 0.122, 0.244, 0.488};
	float _accel_multiplier;
    const float gyro_multiplier[5] = {4.375, 8.75, 17.5, 35, 70};
	float _gyro_multiplier;

	virtual bool pollData(DataPacket * dp) const {
		if (poll() != RESULT_SUCCESS) 
			return false;
		// Initalize an data array
		float * arr = new float[7];
		arr[0] = (float) ((m_temp / 16) + m_offsets._temp_offset);
		arr[1] = (float) ((m_accel.x*_accel_multiplier) * m_offsets._accel_offsets.x);
		arr[2] = (float) ((m_accel.y*_accel_multiplier) * m_offsets._accel_offsets.y);
		arr[3] = (float) ((m_accel.z*_accel_multiplier) * m_offsets._accel_offsets.z);
		arr[4] = (float) ((m_gyro.x*_gyro_multiplier) * m_offsets._gyro_offsets.x);
		arr[5] = (float) ((m_gyro.y*_gyro_multiplier) * m_offsets._gyro_offsets.y);
		arr[6] = (float) ((m_gyro.z*_gyro_multiplier) * m_offsets._gyro_offsets.z);

		dp = new IMUDataPacket(getTime(), arr);

		return true;
	}
    
    virtual void printValues() const {
        std::cout << "======================================" << std::endl;
        std::cout << "Temp: " << ((m_temp / 16) + m_offsets._temp_offset << "degrees celcius" << std::endl;
		std::cout << "AccelX: " << (float) ((m_accel.x*_accel_multiplier) * m_offsets._accel_offsets.x) << std::endl;
		std::cout << "AccelY: " << (float) ((m_accel.y*_accel_multiplier) * m_offsets._accel_offsets.y)  < std::endl;
		std::cout << "AccelZ: " << (float) ((m_accel.z*_accel_multiplier) * m_offsets._accel_offsets.z) << std::endl;
		std::cout << "GyroX: " << (float) ((m_gyro.x*_gyro_multiplier) * m_offsets._gyro_offsets.x) << std::endl;
		std::cout << "GyroY: " << (float) ((m_gyro.y*_gyro_multiplier) * m_offsets._gyro_offsets.y) << std::endl;
		std::cout << "GyroZ: " << (float) ((m_gyro.z*_gyro_multiplier) * m_offsets._gyro_offsets.z)<< std::endl;
		std::cout << "======================================" << std::endl;
    }
   /*
    virtual float * getValues() {
		float val[7];
        for (int i=0; i<3; i++) {
            val[1+i] = (m_accel[i] + m_accel_offsets[i]) * m_accel_offsets[4];
            val[4+i] = (m_gyro[i] + m_gyro_offsets[i]) * m_gyro_offsets[4] ;
        }
        val[0] = (m_temp / 16) + m_temp_offset;
		return val;
    } */
/*
    double avg[6]= {
		0, 0, 0, 0, 0, 0
	};
	double * calibrate(int count) {

		for (int i=0; i<count; i++) {
			poll();
            for (int i=0; i<3; i++) {
                avg[i] += m_accel[i];
                avg[i+3] += m_gyro[i];
            }

		}

        for (int i=0; i<6; i++) {
            avg[i] /= count;
        }
        
        return avg;
		
	}
*/


private:
	mraa::I2c m_i2c;
	short m_temp;
	vector<short> m_accel; // using short because 16-byte data output. c++ translate the raw binary output according to two's complement. 
	vector<short> m_gyro;

	uint8_t m_buffer[BUFFER_SIZE];
};

}

#endif
