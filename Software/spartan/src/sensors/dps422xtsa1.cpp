#include "dps422xtsa1.h"
#include "globals.h"

spartan::DPS422XTSA1::DPS422XTSA1(int bus, uint8_t address) 
	: Sensor(bus, address), m_i2c(bus, true)
{
	// Implementation
}

const char* spartan::DPS422XTSA1::name() const
{
	// Implementation;
	return "DPS422XTSA1";
}
void spartan::DPS422XTSA1::printSensorInfo()
{
	// Implementation
}

int spartan::DPS422XTSA1::powerOn()
{ 
	// Implementation
	return RESULT_SUCCESS;
}
int spartan::DPS422XTSA1::powerOff()
{ 
	// Implementation
	return RESULT_SUCCESS;
}

int spartan::DPS422XTSA1::pollData(spartan::MasterDataPacket &dp)
{
	// Implementation
	return RESULT_SUCCESS;
}

int spartan::DPS422XTSA1::printValues() const
{
	// Implementation
	return RESULT_SUCCESS;
}
