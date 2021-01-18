#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

#include <iostream>

#include <datapacket/mdp.h>
#include <globals.h>

namespace spartan {
    class Sensor {
    public:
        // Constructor that takes in pin number that sensor is connected to; this pin number would be used for all
        // member functions
        Sensor(int busID, int instance);

        // Identification, standard max length is 15 characters
        virtual const char * name() const = 0;
        virtual void printSensorInfo() = 0;

        // Standard sensor implementation
        virtual int powerOn() = 0;
        virtual int powerOff() = 0;
        virtual int pollData(MasterDataPacket &dp) = 0;

        // Debug options
        virtual int printValues() const = 0;
        void printEscapedValues(bool normalize) const;

        // Data getters
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
