#include "ads1115.h"

spartan::ADS1115::ADS1115(int bus, uint8_t address)
    : Sensor(bus, address), m_i2c(bus, true) 
{}

const char* spartan::ADS1115::name() const 
{ 
    const char * str = "ADS1115";
    return str;
};

void spartan::ADS1115::printSensorInfo() {}

int spartan::ADS1115::powerOn() { return 0; }

int spartan::ADS1115::powerOff() { return 0; }

int spartan::ADS1115::pollData(MasterDataPacket &dp) { return 0; }

int spartan::ADS1115::printValues() const {}
