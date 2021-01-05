#ifndef DPS422XTSA1_H_INCLUDED
#define DPS422XTSA1_H_INCLUDED

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
    class DPS422XTSA1 : public Sensor {
    public:
        DPS422XTSA1(int bus, uint8_t address);

        virtual const char* name() const;
        virtual void printSensorInfo();

        virtual int powerOn();
        virtual int powerOff();
        virtual int poll(MasterDataPacket& dp);

        virtual int printValues() const;

    private:
        mraa::I2c m_i2c;
};
} // namespace spartan

#endif // DPS422XTSA1_H_INCLUDED