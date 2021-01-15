#include "dps422xtsa1.h"

spartan::DPS422XTSA1::DPS422XTSA1(int bus, uint8_t address) 
	: Sensor(bus, address), m_i2c(bus, true)
{
	// Implementation
}

const char* spartan::DPS422XTSA1::name() const
{
	// Implementation
	const char* sensor_name = "DPS422XTSA1";
	return sensor_name;
}
void spartan::DPS422XTSA1::printSensorInfo()
{
	// Implementation
}

int spartan::DPS422XTSA1::powerOn()
{ 
	// Implementation
	return 0;
}
int spartan::DPS422XTSA1::powerOff()
{ 
	// Implementation
	return 0;
}

int spartan::DPS422XTSA1::poll(spartan::MasterDataPacket &dp)
{
	// Implementation
	return 0;
}

int spartan::DPS422XTSA1::printValues() const
{
	// Implementation
	return 0;
}
