#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

#include <data/datapacket.h>
#include <mraa/i2c.hpp>
#include "../globals.h"
#include <chrono>
#include <iostream>

namespace spartan {
    class Sensor {
    public:
        Sensor(int busID, int instance) : m_i2c(busID,true), m_busID(busID), m_status(STATUS_OFF), m_instance(instance) {/*...*/ }
        //constructor that takes in pin number that sensor is connected to; this pin number would be used for all member functions

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
        void printEscapedValues(bool normalize) const {
            printValues();
            std::cout << "\033[100D" << std::flush;
            std::cout << "\033[" << lines << "A" << std::flush;
            if (normalize) {
                std::cout << "\033[" << lines << "B" << std::flush;
            }
        }

        // Standard getter for timestamp
        unsigned long getTime() {
            return (unsigned long) std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        }

        // Generic function implementation for the sensor class
        int getBusID() const { return m_busID; }
        //return status (operate with interfaced constants described in globals.h)
        virtual int getStatus() const { return m_status; }
        int getInstance() const { return m_instance; }
        mraa::I2c getI2C() const { return m_i2c; }

    protected:
 	    int m_status;
	    mraa::I2c m_i2c; //bus that sensor is connected to
	    int m_busID;
	    int m_instance; //support for multiple sensors of same type
    };

}
 // namespace spartan

#endif // SENSOR_H_INCLUDED
