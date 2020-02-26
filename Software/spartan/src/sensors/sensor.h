#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

#include <chrono>
#include <iostream>
#include <mraa/i2c.hpp>

#include <data/datapacket.h>
#include <globals.h>

namespace spartan {
    class Sensor {
    public:
        Sensor(int busID, int instance);
        // Constructor that takes in pin number that sensor is connected to; this pin number would be used for all
        // member functions

        // Identification, standard max length is 15 characters
        virtual const char * name() const = 0;
        virtual void printSensorInfo() = 0;

        // Standard sensor implementation
        virtual int powerOn() = 0;
        virtual int powerOff() = 0;
        virtual bool poll() = 0;

        // Data getters
        virtual bool pollData(DataPacket * & dp) = 0;

        // Debug options
        virtual int printValues() const = 0;
        void printEscapedValues(bool normalize) const;

        // Standard getter for timestamp
        unsigned long getTime() const;

        int getBusID() const;
        int getInstance() const;
        // Return status (operate with interfaced constants described in globals.h)
        virtual int getStatus() const;

    protected:
 	    int m_status;
	    int m_busID;
	    int m_instance; // support for multiple sensors of same type
    };
} // namespace spartan

#endif // SENSOR_H_INCLUDED
