#include "mtk3339.h"

// Constructor

spartan::MTK3339::MTK3339(int bus, uint8_t address)
    : Sensor(bus, address), m_i2c(bus, true)
{}

// Identification

const char* spartan::MTK3339::name() const 
{
    const char * str = "MTK3339";
    return str;
};

void spartan::MTK3339::printSensorInfo() {}


// Power functions

int spartan::MTK3339::powerOn() { return 0; }
int spartan::MTK3339::powerOff() { return 0; }

// Update sensor data buffer
int spartan::MTK3339::poll(MasterDataPacket &dp) { return 0; }

int spartan::MTK3339::printValues() const { return 0; }
