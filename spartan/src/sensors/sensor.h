#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

#include <data/datapacket.h>

namespace spartan {
    class Sensor {
    public:
        Sensor() {}
        virtual bool pollData(DataPacket &dp) = 0;
        virtual void printValues() = 0;
    };
} // namespace spartan

#endif // SENSOR_H_INCLUDED