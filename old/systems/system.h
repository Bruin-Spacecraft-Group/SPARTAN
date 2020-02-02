#ifndef SYSTEM_H

#define SYSTEM_H

#include 

//MRAA I2C modes for data tranmission rates (up to 100kHz/400kHz/3.4MHz)
#define I2C_STD	mraa::I2cMode::I2C_STD
#define I2C_FAST mraa::I2cMode::I2C_FAST
#define I2C_HIGH mraa::I2cMode::I2C_HIGH

//EACH SYSTEM WILL HAVE THEIR OWN CLASSES; THIS IS JUST TO INDICATE THAT EACH SYSTEM WILL HAVE THESE GENERAL FUNCTIONS BUT MODIFIED IN SOME WAY
//have classes for each system type (maybe class inheritence with an overall "system" class, and have constructor that takes in what port connected to when declared in "main")
class System
{
public:
	System(char* connectionType) {/*...*/}
	//connection type parameter currently set to a string input, but probably easier to simply map to global constant
	//dataRate of connection; do not currently know exact connection types, and therefore might not be needed

	virtual int getStatus() const = 0;
	//returns value depending on status; as determined by global constants
	//i.e. 	0: not connected/powered off
	//		1: idle, waiting for command
	//		2: ready to recieve data
	//		3: ready to send data

	bool isConnected() const {/*...*/}
	//less abstracted "getStatus" function, specifically implements the check for being connected via wire

	char* getConnectionType() const {/*...*/}
	//accessor function for c-string of connection type

	//int getDataRate() const {/*...*/}
		//returns the current set data rate

	//bool setDataRate() {/*...*/}
		//returns true if successfully set datarate; false otherwise

private:
	//int m_datarate;
	char* connectionType;
};

#endif