#ifndef ADS1115_H_INCLUDED
#define ADS1115_H_INCLUDED

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
    class ADS1115 : public Sensor {
    public:
        ADS1115(int bus, uint8_t address);
        int pollData(spartan::MasterDataPacket &dp) override;
        int printValues() const override;
    };
} // namespace spartan

#endif // ADS1115_H_INCLUDED