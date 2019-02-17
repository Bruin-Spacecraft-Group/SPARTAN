#ifndef ADXL345_H

#define ADXL_345_H

#include <iostream>
#include <cstdlib>
#include "sensors.h"
#include "globals.h"

//buffer size
#define BUFFER_SIZE 6;

//address and ID
#define ADXL345_I2C_ADDR 0x1D //or 0x53 for address IF ALT ADDRESS pin (Pin 12) is grounded
#define ADXL345_ID 0x00 //device ID

//control registers
#define ADXL345_OFSX 0x1E
#define ADXL345_OFSY 0x1F
#define ADXL345_OFSZ 0x20
#define ADXL345_TAP_THRESH 0x1D
#define ADXL345_TAP_DUR 0x21
#define ADXL345_TAP_LATENCY 0x22
#define ADXL345_ACT_THRESH 0x24
#define ADXL345_INACT_THRESH 0x25
#define ADXL345_INACT_TIME 0x26
#define ADXL345_INACT_ACT_CTL 0x27
#define ADXL345_FALL_THRESH 0x28
#define ADXL345_FALL_TIME 0x29
#define ADXL345_TAP_AXES 0x2A
#define ADXL345_ACT_TAP_STATUS 0x2B

//interrupt registers
#define ADXL345_INT_ENABLE 0x2E
#define ADXL345_INT_MAP 0x2F
#define ADXL345_INT_SOURCE 0x30

//data registers (read only) (eight bits each)
#define ADXL345_XOUT_L 0x32
#define ADXL345_XOUT_H 0x33
#define ADXL345_YOUT_L 0x34
#define ADXL345_YOUT_H 0x35
#define ADXL345_ZOUT_L 0x36
#define ADXL345_ZOUT_H 0x37
#define DATA_REG_SIZE 6

//data and power management
#define ADXL345_BW_RATE 0x2C
#define ADXL345_POWER_CTL 0x2D
#define ADXL345_DATA_FORMAT 0x31 //setting of 1 in the SELF_TEST bit applies a self-test force to the sensor, causing a shift in the output data. A value of 0 disables the self-test force
#define ADXL345_FIFO_CTL 0x38
#define ADXL345_FIFO_STATUS 0x39

//useful values
#define ADXL345_POWER_ON 0x08
#define ADXL345_AUTO_SLP 0x30
#define ADXL345_STANDBY 0x00

//scales and resolution
#define ADXL345_FULL_RES 0x08
#define ADXL345_10BIT 0x00
#define ADXL345_2G 0x00
#define ADXL345_4G 0x01
#define ADXL345_8G 0x02
#define ADXL345_16G 0x03

//accel
class ADXL345: public Sensor
{
public:
	ADXL345(int busID, int instance):Sensor(busID, instance), m_i2c(busID)
	{
		//set I2C address
		if (m_i2c.address(ADXL345_I2C_ADDR) != mraa::SUCCESS)
		{
			std::cerr << "Unable to set I2C address." << endl;
			exit(ERROR_ADDR);
		}

		//send "Power On" command
		m_buffer[0] = ADXL345_POWER_CTL;
		m_buffer[1] = ADXL345_POWER_ON;
		
		if (m_i2c.write(m_buffer, 2) != mraa::SUCCESS)
		{
			std::cerr << "Unable to write POWER_ON to ADXL345." << endl;
			exit(ERROR_POWER);
		}

		//send "Data Format" command
		m_buffer[0] = ADXL345_DATA_FORMAT;
    	m_buffer[1] = ADXL345_16G | ADXL345_FULL_RES; //device is in full resolution mode, where the output resolution increases with the g range set by the range bits to maintain a 4 mg/LSB scale factor
    	if (m_i2c.write(m_buffer, 2) != mraa::SUCCESS)
		{
			std::cerr << "Unable to write DATA_FORMAT to ADXL345." << endl;
			exit(ERROR_DATAFORMAT);
		}

		//run calibration of sensor
		if (calibrate() == false)
		{
			std::cerr << "Unsuccessful ADXL345 calibration." << endl;
			exit(ERROR_CALIB); //might not be wanted, as calibration could be potentially not required
		}

		//run first update of sensor
		if (poll() == false)
		{
			std::cerr << "Unable to initial poll ADXL345." << endl;
			exit(ERROR_POLL);
		}
	};

	virtual bool calibrate() {/*...*/}
	//zeros sensor to current reading (different sensors will have slightly different implementations)
	//returns true if successfully calibrated; false otherwise
	//return type can always be changed to an int to allow for more error returns (status constants described in systems.h or in globals.h files)

	virtual bool poll() {

		//set I2C address
		if (m_i2c.address(ADXL345_I2C_ADDR) != mraa::SUCCESS)
		{
			std::cerr << "Unable to set I2C address." << endl;
			exit(ERROR_ADDR);
		}

		//write XOUT_L byte
		if (m_i2c.writeByte(ADXL345_XOUT_L) != mraa::SUCCESS) //maybe remove check for success, as ADXL345_XOUT_L register is not supposed to be "writeable"
		{
			std::cerr << "Unable to write ADXL345 XOUT_L byte." << endl;
			exit(ERROR_POLL);
		}

		//read x,y,z data into buffer
		m_i2c.read(m_buffer, DATA_REG_SIZE);

		//record rawacceleration values using data reads for x,y,z respectively
		//DATAx0 is the least significant byte, and DATAx1 is the most significant byte
    	m_rawaccel[0] = ((m_buffer[1] << 8 ) | m_buffer[0]);
    	m_rawaccel[1] = ((m_buffer[3] << 8 ) | m_buffer[2]);
    	m_rawaccel[2] = ((m_buffer[5] << 8 ) | m_buffer[4]);

	}
	//"poll","read","get"; reads raw data from sensor and places it into sensor's respective member variable; maybe into a file as well? or an input stream? and then preprocess function can pull from that?

	virtual bool longPoll() { return false; //dummy}
	//call poll() over a longer period of time, averaging out the values (maybe allow time input functionality, or just do poll 10 times and average out the values, storing result into rawAccel array)
	//"poll","read","get"; reads raw data from sensor and returns it; maybe into a file? or an input stream? or a member variable of the class/struct? and then preprocess function can pull from that?
	//rawData type is a placeholder for now; will return raw sensor data

	virtual float preprocess() { return 1.0; //dummy}
	//converts raw sensor data into relevant values
	//make sure to include offsets in the preprocessing(?)

	//Scale Factor at XOUT, YOUT, ZOUT ±16 g, 10-bit resolution 28.1 31.2 34.3 mg/LSB


	//ADXL345 HAS A SELF-TEST FEATURE THAT HAS INSTRUCTIONS ON HOW TO USE IT ON PAGE 20/21 of DATA SHEET

	virtual void printSensorInfo()
	{
		std::cout << "Type:       ADXL345" << endl;
		std::cout << "Number:     " << getInstance() << endl;
		//std::cout << "Status:     " << getStatus() << endl;
		std::cout << "I2C BusID:  " << getBusID() << endl;

		std::cout << "RawAccelX:  " << m_rawAccel[1] << endl;
		std::cout << "RawAccelY:  " << m_rawAccel[2] << endl;
		std::cout << "RawAccelZ:  " << m_rawAccel[3] << endl;

		std::cout << "ProcessedX: " << m_processedAccel[1] << endl;
		std::cout << "ProcessedY: " << m_processedAccel[2] << endl;
		std::cout << "ProcessedZ: " << m_processedAccel[3] << endl;
	}



private:
	mraa::I2c m_i2c;
	float m_rawAccel[3];
	float m_processedAccel[3];
	//need something for offsets/scaling for preprocessing/calibration
	uint8_t m_buffer[BUFFER_SIZE];
}

#endif