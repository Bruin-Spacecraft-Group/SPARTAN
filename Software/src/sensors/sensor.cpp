#include "sensor.h"
#include "utils/utils.h"

// Constructor
spartan::Sensor::Sensor(int busID, int instance, int data_len)
    : m_busID(busID), m_status(STATUS_OFF), m_instance(instance) {
    m_data = new float[data_len];
}

// Destructor
spartan::Sensor::~Sensor() {
    delete[] m_data;
}

// Set timestamp
void spartan::Sensor::setTimestamp(unsigned long timestamp) {
    m_timestamp = spartan::getTimeMillis();
}

// Get timestamp
unsigned long spartan::Sensor::getTimestamp() const {
    return m_timestamp;
}

// Debug output
void spartan::Sensor::printEscapedValues(bool normalize) const {
    int lines = printValues();
    std::cout << "\033[100D" << std::flush;
    std::cout << "\033[" << lines << "A" << std::flush;
    if (normalize) {
        std::cout << "\033[" << lines << "B" << std::flush;
    }
}

void spartan::Sensor::printPollingError() const {
    std::cerr << "Sensor name: " << this->name() << " instance; " << this->getInstance()
              << " poll data error!" << std::endl;
}

// Generic function implementation for the sensor class
int spartan::Sensor::getBusID() const { return m_busID; }
int spartan::Sensor::getStatus() const { return m_status; }
int spartan::Sensor::getInstance() const { return m_instance; }
float* spartan::Sensor::getData() const { return m_data; }
