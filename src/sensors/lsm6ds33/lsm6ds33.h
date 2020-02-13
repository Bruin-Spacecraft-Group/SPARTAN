//another found GPIO interface library for the raspberry pi: http://wiringpi.com/reference/i2c-library/
//data sheet and other info about sensor can be referenced here: https://www.st.com/resource/en/datasheet/lsm6ds33.pdf

#ifndef LSM6DS33_H

#define LSM6DS33_H

#include <iostream>
#include <cstdlib>
#include "../sensors.h"
#include "../../globals.h"
#include "../mdp.h"
#include "lsm6add.h"

//buffer size for writing values to registers
#define BUFFER_SIZE 14
#define DATA_REG_SIZE 14

//address
#define LSM6DS33_I2C_ADDR 0x6A //7-bit address form; default in 'write' state; implies connection to supply voltage; 0xD4 for connection to ground; general form: 110101xb

/*
The Slave ADdress (SAD) associated to the LSM6DS33 is 110101xb. The SDO/SA0 pin
can be used to modify the less significant bit of the device address. If the SDO/SA0 pin is
connected to the supply voltage, LSb is ‘1’ (address 1101011b); else if the SDO/SA0 pin is
connected to ground, the LSb value is ‘0’ (address 1101010b). This solution permits to
connect and address two different inertial modules to the same I2C bus.

LSB is 1 (8th bit in address) for read
LSB is 0 (8th bit in address) for write
*/

//useful values
#define LSM6DS33_POWER_OFF 			0x00

// Setting the I2C slave address
#define LSM6DS33_SA0_HIGH_ADDRESS 0b1101011
#define LSM6DS33_SA0_LOW_ADDRESS  0b1101010

// Available settings

enum AccelRange { _2g=0b0000, _4g=0b1000, _8g=0b1100, _16g=0b0100}; 	// (00: ±2 g; 01: ±16 g; 10: ±4 g; 11: ±8 g)
enum AccelAAFreq { _400hz=0b00, _200hz=0b01, _100hz=0b10, _50hz=0b11 }	// (00: 400 Hz; 01: 200 Hz; 10: 100 Hz; 11: 50 Hz)
enum GyroRange { _125dps=0b0010, _250dps=0b0000, _500dps=0b0100, _1000dps=0b1000, _2000dps=0b1100}; 	
// first two digits(00: 250 dps; 01: 500 dps; 10: 1000 dps; 11: 2000 dps)  third: 125 dps. Default value: 0 (0: disabled; 1: enabled) fourth: 0
enum ODR { odr_12hz=0b0001, odr_26Hz=0b0010, odr_52Hz=0b0011, 
odr_104Hz=0b0100, 
odr_208Hz=0b0101, 
odr_416Hz=0b0110, 
odr_833Hz=0b0111, 
odr_1660Hz=0b1000, // Gyro ODR only up to 1660, Accel has the following two.
odr_3330Hz=0b1001, 
odr_6660Hz=0b1010};

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

	offsets m_offsets = {0, {.x=1, .y=1, .z=1}, {.x=1, .y=1, .z=1}};
	

	bool writeReg(uint8_t* buffer, unsigned short size);

	bool updateSettings() {

		// Update multiplier constant

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

		// Accelerometer settings
		m_buffer[0] = CTRL1_XL;
		m_buffer[1] = (m_settings.accel_odr << 8) | m_settings.accelRange | m_settings.accelAAFreq;

		if (!writeReg(m_buffer, 2))
			return false;

		m_buffer[0] = CTRL2_G;
		m_buffer[1] = (m_settings.gyro_odr << 8) | m_settings.gyroRange;

		if (!writeReg(m_buffer, 2))
			return false;

		
		return true;
	}

	bool updateSettings(lsm6Settings settings) {
		m_settings = settings;
		updateSettings();
	}

	uint8_t lsm6Address;

	LSM6DS33(	int busID, 
				int instance, 
				lsm6Settings settings,
				lsm6ID		//  Either 0 or 1 (can only connect 2 lsm6ds33 modules)
			): Sensor(busID, instance), 
				m_i2c(busID,true), 
				m_settings(settings)  // raw=true, disable pinmapper for board
	{
		if (lsm6ID)
			lsm6Address = HIGH_ADDRESS;
		else 
			lsm6Address = LOW_ADDRESS;
		
	}

	bool writeReg(uint8_t* buffer, unsigned short size) {
		mraa::Result msg = m_i2c.write(buffer, 2);

		// Error handling
		if (msg == mraa::SUCESS) 
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
		if (!updateSettings(settings)) {
			std::cerr << "Update setting failed" << std::endl;
			return ERROR_ADDR;
		}

		/* CTRL3_C has default 1 on IF_INC page 49 in datasheet
		m_buffer[0] = CTRL3_C;
		m_buffer[1] = 0x04;
		if (!writeReg(m_buffer, 2))
		{
			std::cerr << "Unable to write GYRO_POWER_ON to LSM6DS33." << std::endl;
			return ERROR_POWER;
		}
		*/
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
			return RESULT_FALSE;

		//set I2C address
		if (m_i2c.address(LSM6DS33_I2C_ADDR) != mraa::SUCCESS)
		{
			std::cerr << "Unable to set I2C address." << std::endl;
			return ERROR_ADDR;
		}

		//read temp,x,y,z (14 bytes) into buffer
		if (m_i2c.readBytesReg(LSM6DS33_OUT_TEMP_L, m_buffer, DATA_REG_SIZE) == -1)
		{
			std::cerr << "Unable to read data bytes starting from LSM6DS33_OUT_TEMP_L." << std::endl;
			return ERROR_POLL;
		}

		//record rawacceleration values using data reads for x,y,z respectively
		//DATAx0 is the least significant byte, and DATAx1 is the most significant byte
		//conversion of raw sensor data into relevant values based on constant offset values
		m_temp = ((m_buffer[1] << 8) | m_buffer[0]) + m_offsets._temp_offset;

		m_gyro[0] = ((m_buffer[3] << 8) | m_buffer[2]) * _accel_multiplier;
		m_gyro[1] = ((m_buffer[5] << 8) | m_buffer[4]) * _accel_multiplier;
		m_gyro[2] = ((m_buffer[7] << 8) | m_buffer[6]) * _accel_multiplier;

		m_accel[0] = ((m_buffer[9] << 8) | m_buffer[8]) * _gyro_multiplier;
		m_accel[1] = ((m_buffer[11] << 8) | m_buffer[10]) * _gyro_multiplier;
		m_accel[2] = ((m_buffer[13] << 8) | m_buffer[12]) * _gyro_multiplier;

		return RESULT_SUCCESS;
	}

	virtual bool poll(MDP mdp) {

		//mdp.set_accel(m_accel);

		return RESULT_SUCCESS;
	}

	int hasNewData()
	{
		//NOTE: STATUS_REG on lSM6DS33 used to check if data is available for temp/gyro/accel
		if (m_status == STATUS_OFF)
			return RESULT_FALSE;

		//set I2C address
		if (m_i2c.address(LSM6DS33_I2C_ADDR) != mraa::SUCCESS)
		{
			std::cerr << "Unable to set I2C address." << std::endl;
			return ERROR_ADDR;
		}

		if (m_i2c.readBytesReg(LSM6DS33_STATUS_REG,m_buffer,1) == -1)
			return ERROR_READ;

		uint8_t temp = 0;

		if ((m_buffer[0] & 0x7) > temp)
			return RESULT_SUCCESS;
		else
			return RESULT_FALSE;
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
		std::cout << "Temp: " << m_temp << std::endl;
		std::cout << "AccelX: " << m_accel[0] << std::endl;
		std::cout << "AccelY: " << m_accel[1] << std::endl;
		std::cout << "AccelZ: " << m_accel[2] << std::endl;
		std::cout << "GyroX: " << m_gyro[0] << std::endl;
		std::cout << "GyroY: " << m_gyro[1] << std::endl;
		std::cout << "GyroZ: " << m_gyro[2] << std::endl;
		std::cout << "======================================" << std::endl;
	}

	void printEscapedRawValues() {
		printRawValues();
		std::cout << "\033[100D" << std::flush;
		std::cout << "\033[9A" << std::flush;
	}

    const float accel_multiplier[4] = {0.061, 0.122, 0.244, 0.488};
	const float _accel_multiplier;
    const float gyro_multiplier[5] = {4.375, 8.75, 17.5, 35, 70};
	const float _gyro_multiplier;
    
    virtual void printValues() {
        std::cout << "======================================" << std::endl;
        std::cout << "Temp: " << (int) (m_temp / 16) << "degrees celcius" << std::endl;
		std::cout << "AccelX: " << (float) (m_accel[0]*accel_offset[0]) << std::endl;
		std::cout << "AccelY: " << (float) (m_accel[1]*accel_offset[0]) << std::endl;
		std::cout << "AccelZ: " << (float) (m_accel[2]*accel_offset[0]) << std::endl;
		std::cout << "GyroX: " << (float) (m_gyro[0]*gyro_offset[0]) << std::endl;
		std::cout << "GyroY: " << (float) (m_gyro[1]*gyro_offset[0]) << std::endl;
		std::cout << "GyroZ: " << (float) (m_gyro[2]*gyro_offset[0]) << std::endl;
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



private:
	mraa::I2c m_i2c;
	short m_temp;
	vector<short> m_accel; // using short because 16-byte data output. c++ translate the raw binary output according to two's complement. 
	vector<short> m_gyro;

	uint8_t m_buffer[BUFFER_SIZE];
};

#endif
