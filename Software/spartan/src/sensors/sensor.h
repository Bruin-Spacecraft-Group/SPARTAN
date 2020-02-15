#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

#include <data/datapacket.h>
#include <mraa/i2c.hpp>

namespace spartan {
    class Sensor {
    public:
        Sensor(int busID, int instance) {}

        // Standard sensor implementation

        virtual int powerOn() = 0;
	    virtual int powerOff() = 0;

        // Data getters
        virtual bool pollData(PacketType & dp) const = 0;
        virtual void printValues() const = 0;
    };
} // namespace spartan

#endif // SENSOR_H_INCLUDED