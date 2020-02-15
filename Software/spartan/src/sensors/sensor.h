#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

#include <data/datapacket.h>
#include <mraa/i2c.hpp>
#include "../globals.h"

namespace spartan {
    class Sensor {
    public:
        Sensor(int busID, int instance) : m_i2c(busID,true), m_busID(busID), m_status(STATUS_OFF), m_instance(instance) {/*...*/ }
        //constructor that takes in pin number that sensor is connected to; this pin number would be used for all member functions

        virtual int powerOn() = 0;
        virtual int powerOff() = 0;

        virtual bool poll() = 0;

        virtual void printSensorInfo() = 0;

        virtual void printValues() { /* ... */ };

        int getBusID() const
        {
            return m_busID;
        }

        virtual int getStatus() const
        {
            return m_status;
        }
        // //return status (operate with interfaced constants described in globals.h)

        int getInstance() const
        {
            return m_instance;
        }

        mraa::I2c getI2C() const
        {
            return m_i2c;
        }
        // Standard sensor implementation

        virtual int powerOn() = 0;
	    virtual int powerOff() = 0;

        // Data getters
        virtual bool pollData(PacketType & dp) const = 0;
        virtual void printValues() const = 0;
    };

    protected:
 	    int m_status;
    private:
	    mraa::I2c m_i2c; //bus that sensor is connected to
	    int m_busID;
	    int m_instance; //support for multiple sensors of same type
};
} // namespace spartan

#endif // SENSOR_H_INCLUDED