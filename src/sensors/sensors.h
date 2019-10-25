#ifndef SENSORS_H

#define SENSORS_H

#include <mraa/i2c.hpp>
#include "globals.h"

//rawData pollAll() {/*...*/}
//test mode function; will call construct datapacket function (abstracted function)
//switch statment, with each value corresponding to a series of if statements with global constants of "ACCEL1_IN_USE" and such (as described in "construct" function for datapacket)
//maybe return as a pointer to a dynamic array

//THIS ONE IS IN THE WORKS; IMPLEMENTATION STILL FIGURING OUT
//rawData pollType(int typeMapping)
//polls all sensors of a certain type as indicated by inputted mapped values (find in globals.h file)
//switch statment, with each value corresponding to a series of if statements with global constants of "ACCEL1_IN_USE" and such (as described in "construct" function for datapacket)
//maybe return as a pointer to a dynamic array

//rawData longPollAll() {/*...*/}
//takes pollAll over a longer period of time and averages out the values
//can potentially have a time input for customization purposes
//maybe return as a pointer to a dynamic array

//rawData longPollType() {/*...*/}
//takes pollType over a longer period of time and averages out the values
//can potentially have a time input for customization purposes
//maybe return as a pointer to a dynamic array

//===================================================================================================================

//bool getStatusAll() {/*...*/}
//test mode function; will call construct datapacket function (abstracted function)
//switch statment, with each value corresponding to a series of if statements with global constants of "ACCEL1_IN_USE" and such (as described in "construct" function for datapacket)
//return type can always be changed to an int to allow for more error returns (status constants described in systems.h or in globals.h files)
//maybe return a pointer to a dynamic array with all of the status? or just print to screen because this is an abstracted function?

//THIS ONE IS IN THE WORKS; IMPLEMENTATION STILL FIGURING OUT
//bool getStatusType(int typeMapping) {/*...*/}
//polls all sensors of a certain type as indicated by inputted mapped values (find in globals.h file)
//switch statment, with each value corresponding to a series of if statements with global constants of "ACCEL1_IN_USE" and such (as described in "construct" function for datapacket)
//return type can always be changed to an int to allow for more error returns (status constants described in systems.h or in globals.h files)
//maybe return a pointer to a dynamic array with all of the status? or just print to screen because this is an abstracted function?

//===================================================================================================================

//bool calibrateAll() {/*...*/}
//calls calibrate function of all active sensors
//returns true if successfull; false if otherwise (if one fails)
//return type can always be changed to an int to allow for more error returns (status constants described in systems.h or in globals.h files)

//bool calibrateType() {/*...*/}
//calls calibrate function of all active sensors of one type
//returns true if successfull; false if otherwise (if one fails)
//return type can always be changed to an int to allow for more error returns (status constants described in systems.h or in globals.h files)

//===================================================================================================================

//EACH SENSOR WILL HAVE THEIR OWN CLASSES; THIS IS JUST TO INDICATE THAT EACH SENSOR WILL HAVE THESE GENERAL FUNCTIONS BUT MODIFIED IN SOME WAY (sensor is an abstract base class)
//i.e. ADXL345 accel1(I2C_BUS_ID);
class Sensor
{
public:
	Sensor(int busID, int instance) : m_i2c(busID), m_busID(busID), m_status(STATUS_OFF), m_instance(instance) {/*...*/ }
	//constructor that takes in pin number that sensor is connected to; this pin number would be used for all member functions

	virtual int powerOn() = 0;
	virtual int powerOff() = 0;

	//virtual bool calibrate() { /* ... */ };
	//zeros sensor to current reading (different sensors will have slightly different implementations)
	//returns true if successfully calibrated; false otherwise
	//return type can always be changed to an int to allow for more error returns (status constants described in systems.h or in globals.h files)

	virtual bool poll() = 0;
	//"poll","read","get"; reads raw data from sensor and places it into sensor's respective member variable; maybe into a file? or an input stream? or a member variable of the class/struct? and then preprocess function can pull from that?
	//rawData type is a placeholder for now; will return raw sensor data
	//will preprocess the information within function call

	//virtual bool longPoll() = 0; 
	//call poll() over a longer period of time, averaging out the values (maybe allow time input functionality)
	//"poll","read","get"; reads raw data from sensor and returns it; maybe into a file? or an input stream? or a member variable of the class/struct? and then preprocess function can pull from that?
	//rawData type is a placeholder for now; will return raw sensor data

	//virtual float preprocess() { /* ... */ };
	//converts raw sensor data into relevant values

	virtual void printSensorInfo() = 0;

	virtual void printValues() { /* ... */ };

	int getBusID() const
	{
		return m_busID;
	}

 	virtual int getStatus() const
 	{
 		return m_status;
	}
	// //return status (operate with interfaced constants described in globals.h)

	int getInstance() const
	{
		return m_instance;
	}

	mraa::I2c getI2C() const
	{
		return m_i2c;
	}

	//status functionality temporarily removed, as may not be needed
	/*bool updateStatus(int statusValue)
	{
		//checking if status is a valid status value
		if (statusValue >= 0 && statusValue <= 3)
		{
			m_status = statusValue;
			return true;
		}
		else
			return false;
	}
	//return true if status was updated successfully (statusValue input was a valid status); false if otherwise
	*/
 protected:
 	int m_status;
private:
	mraa::I2c m_i2c; //bus that sensor is connected to
	int m_busID;
	int m_instance; //support for multiple sensors of same type
};

#endif
