//another found GPIO interface library for the raspberry pi: http://wiringpi.com/reference/i2c-library/
//data sheet and other info about sensor can be referenced here: https://www.st.com/resource/en/datasheet/lsm6ds33.pdf

#ifndef LSM6DS33_H

#define LSM6DS33_H

#include <iostream>
#include <cstdlib>
#include "../sensors.h"
#include "../../globals.h"
#include "../mdp.h"

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

//registers
#define LSM6DS33_FIFO_CTRL1			0x06
#define LSM6DS33_FIFO_CTRL2			0x07
#define LSM6DS33_FIFO_CTRL3			0x08
#define LSM6DS33_FIFO_CTRL4			0x09
#define LSM6DS33_FIFO_CTRL5			0x0A
#define LSM6DS33_ORIENT_CFG_G		0x0B

#define LSM6DS33_INT1_CTRL			0x0D
#define LSM6DS33_INT2_CTRL			0x0E
#define LSM6DS33_WHO_AM_I			0x0F
#define LSM6DS33_CTRL1_XL			0x10
#define LSM6DS33_CTRL2_G			0x11
#define LSM6DS33_CTRL3_C			0x12
#define LSM6DS33_CTRL4_C			0x13
#define LSM6DS33_CTRL5_C			0x14
#define LSM6DS33_CTRL6_C			0x15
#define LSM6DS33_CTRL7_G			0x16

#define LSM6DS33_CTRL8_XL          	0x17
#define LSM6DS33_CTRL9_XL          	0x18
#define LSM6DS33_CTRL10_C          	0x19

#define LSM6DS33_WAKE_UP_SRC       	0x1B
#define LSM6DS33_TAP_SRC           	0x1C
#define LSM6DS33_D6D_SRC           	0x1D
#define LSM6DS33_STATUS_REG       	0x1E

#define LSM6DS33_OUT_TEMP_L        	0x20 //lower 8-bits of overall 16-bit word in two's complement (applies to all data output registers)
#define LSM6DS33_OUT_TEMP_H       	0x21
#define LSM6DS33_OUTX_L_G          	0x22
#define LSM6DS33_OUTX_H_G          	0x23
#define LSM6DS33_OUTY_L_G          	0x24
#define LSM6DS33_OUTY_H_G          	0x25
#define LSM6DS33_OUTZ_L_G          	0x26
#define LSM6DS33_OUTZ_H_G          	0x27
#define LSM6DS33_OUTX_L_XL         	0x28
#define LSM6DS33_OUTX_H_XL         	0x29
#define LSM6DS33_OUTY_L_XL         	0x2A
#define LSM6DS33_OUTY_H_XL         	0x2B
#define LSM6DS33_OUTZ_L_XL         	0x2C
#define LSM6DS33_OUTZ_H_XL         	0x2D
#define LSM6DS33_FIFO_STATUS1      	0x3A
#define LSM6DS33_FIFO_STATUS2      	0x3B
#define LSM6DS33_FIFO_STATUS3      	0x3C
#define LSM6DS33_FIFO_STATUS4      	0x3D
#define LSM6DS33_FIFO_DATA_OUT_L   	0x3E
#define LSM6DS33_FIFO_DATA_OUT_H   	0x3F
#define LSM6DS33_TIMESTAMP0_REG    	0x40
#define LSM6DS33_TIMESTAMP1_REG    	0x41
#define LSM6DS33_TIMESTAMP2_REG    	0x42

#define LSM6DS33_STEP_TIMESTAMP_L  	0x49
#define LSM6DS33_STEP_TIMESTAMP_H  	0x4A
#define LSM6DS33_STEP_COUNTER_H    	0x4C

#define LSM6DS33_FUNC_SRC          	0x53

#define LSM6DS33_TAP_CFG           	0x58
#define LSM6DS33_TAP_THS_6D        	0x59
#define LSM6DS33_INT_DUR2          	0x5A
#define LSM6DS33_WAKE_UP_THS       	0x5B
#define LSM6DS33_WAKE_UP_DUR       	0x5C
#define LSM6DS33_FREE_FALL         	0x5D
#define LSM6DS33_MD1_CFG           	0x5E
#define LSM6DS33_MD2_CFG           	0x5F

//useful values
#define LSM6DS33_ACCEL_POWER_ON		0xA0 //this is at 6.6kHz (high performance)
#define LSM6DS33_GYRO_POWER_ON		0x80 //this is at 1.66kHz (high performance)
#define LSM6DS33_POWER_OFF 			0x00

// Data interpretation



class LSM6DS33 : public Sensor
{
public:
	LSM6DS33(int busID, int instance): Sensor(busID, instance), m_i2c(busID,true)
	{
		//set offsets
		m_temp_offset = 0;
		m_accel_offsets[0] = 1; //THESE VALUES HAVE NOT BEEN TESTED FOR YET
		m_accel_offsets[1] = 1;
		m_accel_offsets[2] = 1;
		m_gyro_offsets[0] = 1; //THESE VALUES HAVE NOT BEEN TESTED FOR YET
		m_gyro_offsets[1] = 1;
		m_gyro_offsets[2] = 1;
	}

	virtual int powerOn()
	{
		if (m_status == STATUS_IDLE)
			return RESULT_SUCCESS;

		//set I2C address
		if (m_i2c.address(LSM6DS33_I2C_ADDR) != mraa::SUCCESS)
		{
			std::cerr << "Unable to set I2C address." << std::endl;
			return ERROR_ADDR;
		}

		//send "Power On" command for accelerometer
		//change from default accelerometer full-scale selection to +-16g instead of +-2g
		m_buffer[0] = LSM6DS33_CTRL1_XL;
		m_buffer[1] = LSM6DS33_ACCEL_POWER_ON | 0x4;
		
		if (m_i2c.write(m_buffer, 2) == mraa::ERROR_INVALID_PARAMETER)
			std::cerr << "Invalid parameter." << std::endl;
		if (m_i2c.write(m_buffer, 2) == mraa::ERROR_INVALID_HANDLE)
			std::cerr << "ERROR_INVALID_HANDLE" << std::endl;
		if (m_i2c.write(m_buffer, 2) == mraa::ERROR_NO_RESOURCES)
			std::cerr << "ERROR_NO_RESOURCES" << std::endl;
		if (m_i2c.write(m_buffer, 2) == mraa::ERROR_INVALID_RESOURCE)
			std::cerr << "ERROR_INVALID_RESOURCE" << std::endl;
		if (m_i2c.write(m_buffer, 2) == mraa::ERROR_INVALID_QUEUE_TYPE)
			std::cerr << "ERROR_INVALID_QUEUE_TYPE" << std::endl;
		if (m_i2c.write(m_buffer, 2) == mraa::ERROR_NO_DATA_AVAILABLE)
			std::cerr << "ERROR_NO_DATA_AVAILABLE" << std::endl;
		if (m_i2c.write(m_buffer, 2) == mraa::ERROR_INVALID_PLATFORM)
			std::cerr << "ERROR_INVALID_PLATFORM" << std::endl;
		if (m_i2c.write(m_buffer, 2) == mraa::ERROR_PLATFORM_NOT_INITIALISED)
			std::cerr << "ERROR_PLATFORM_NOT_INITIALISED" << std::endl;
		if (m_i2c.write(m_buffer, 2) == mraa::ERROR_UNSPECIFIED)
			std::cerr << "ERROR_UNSPECIFIED" << std::endl;

		if (m_i2c.write(m_buffer, 2) != mraa::SUCCESS)
		{
			std::cerr << "Unable to write ACCEL_POWER_ON to LSM6DS33." << std::endl;
			return ERROR_POWER;
		}

		//send "Power On" command for gyroscope
		//change from default gyroscope full-scale selection to +-, 'OR' value here with LSM6DS33_GYRO_POWER_ON
		m_buffer[0] = LSM6DS33_CTRL2_G;
		m_buffer[1] = LSM6DS33_GYRO_POWER_ON; //MIGHT WANT TO CHANGE THIS 
		
		if (m_i2c.write(m_buffer, 2) != mraa::SUCCESS)
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
		if (m_i2c.address(LSM6DS33_I2C_ADDR) != mraa::SUCCESS)
		{
			std::cerr << "Unable to set I2C address." << std::endl;
			return ERROR_ADDR;
		}

		//send "Power Off" command for accelerometer
		m_buffer[0] = LSM6DS33_CTRL1_XL;
		m_buffer[1] = LSM6DS33_POWER_OFF;

		if (m_i2c.write(m_buffer, 2) != mraa::SUCCESS)
		{
			std::cerr << "Unable to write POWER_OFF to LSM6DS33's Accelerometer." << std::endl;
			return ERROR_POWER;
		}

		//send "Power Off" command for gyroscope
		m_buffer[0] = LSM6DS33_CTRL2_G;
		m_buffer[1] = LSM6DS33_POWER_OFF;

		if (m_i2c.write(m_buffer, 2) != mraa::SUCCESS)
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
		m_temp = ((m_buffer[1] << 8) | m_buffer[0]) + m_temp_offset;

		m_gyro[0] = ((m_buffer[3] << 8) | m_buffer[2]) * m_accel_offsets[0];
		m_gyro[1] = ((m_buffer[5] << 8) | m_buffer[4]) * m_accel_offsets[1];
		m_gyro[2] = ((m_buffer[7] << 8) | m_buffer[6]) * m_accel_offsets[2];

		m_accel[0] = ((m_buffer[9] << 8) | m_buffer[8]) * m_gyro_offsets[0];
		m_accel[1] = ((m_buffer[11] << 8) | m_buffer[10]) * m_gyro_offsets[1];
		m_accel[2] = ((m_buffer[13] << 8) | m_buffer[12]) * m_gyro_offsets[2];

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

	virtual void printRawValues()
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

    const float accel_offset[4] = {0.061, 0.122, 0.244, 0.488};
    const float gyro_offset[5] = {4.375, 8.75, 17.5, 35, 70};
    
    virtual void printValues() {
        std::cout << "======================================" << std::endl;
        std::cout << "Temp: " << (int) (m_temp / 16) << "degrees centigrade" << std::endl;
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
	short m_accel[3];
	short m_gyro[3];
	float m_temp_offset;
	float m_accel_offsets[4]; // 1, 2, 3 are offsets that are added to the value, 4 is a scale factor applied.
	float m_gyro_offsets[4];  // Same as above
	uint8_t m_buffer[BUFFER_SIZE];
};

#endif
