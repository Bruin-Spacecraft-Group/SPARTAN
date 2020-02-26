#include "sensor.h"

// Constructor
spartan::Sensor::Sensor(int busID, int instance)
    : m_busID(busID), m_status(STATUS_OFF), m_instance(instance) {}

// Debug output
void spartan::Sensor::printEscapedValues(bool normalize) const {
    int lines = printValues();
    std::cout << "\033[100D" << std::flush;
    std::cout << "\033[" << lines << "A" << std::flush;
    if (normalize) {
        std::cout << "\033[" << lines << "B" << std::flush;
    }
}

// Generic function implementation for the sensor class
unsigned long spartan::Sensor::getTime() const {
    return (unsigned long) std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
}
int spartan::Sensor::getBusID() const { return m_busID; }
int spartan::Sensor::getStatus() const { return m_status; }
int spartan::Sensor::getInstance() const { return m_instance; }
