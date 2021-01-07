#ifndef MTK3339_H_INCLUDED
#define MTK3339_H_INCLUDED

// TODO: When Apple releases an ARM Macbook, fix this again
#if !defined(__x86_64__) && !defined(_WIN32)
#include <mraa/i2c.hpp>
#else
#include <mock/i2c.h>
#endif

#include <stdint.h>
#include <sensors/sensor.h>

namespace spartan
{
    class MTK3339 : public Sensor {
    public:
        MTK3339(int bus, uint8_t address);

        // Identification
        virtual const char * name() const;
        virtual void printSensorInfo();

        // Sensor control
        virtual int powerOn();
        virtual int powerOff();
        virtual int poll(MasterDataPacket &dp);

        // Debugging & printing
        virtual int printValues() const;
    private:
        mraa::I2c m_i2c;
    };
} // namespace spartan

#endif // MTK3339_H_INCLUDED