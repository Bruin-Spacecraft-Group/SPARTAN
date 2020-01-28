// #include <mraa/i2c.hpp>
#include <stdint.h>
#include <sensors/sensor.h>

namespace spartan
{
    class ADS1115 : public Sensor {
    public:
        ADS1115(int bus, uint8_t address);
        virtual bool pollData(spartan::DataPacket &dp);
        virtual void printValues() const;
    };
} // namespace spartan