#include "datapacket.h"

#include <string>

std::string spartan::format_encoded_packet(EncodedPacket &packet) {
    std::string formatted = std::to_string(packet.length) + std::to_string(packet.timestamp) + ","
            + std::to_string(packet.length);

    for (int i = 0; i < packet.length; i++) {
        formatted += std::to_string(packet.data[i]);
    }

    return formatted;
}

spartan::DecodedPacket::DecodedPacket(ulong timestamp) : m_timestamp(timestamp) {}

ulong spartan::DecodedPacket::get_timestamp() const {
    return m_timestamp;
}

spartan::IMUDecodedPacket::IMUDecodedPacket(ulong timestamp, const float *data) : DecodedPacket(timestamp) {
    m_temp = data[0];
    m_accel_x = data[1];
    m_accel_y = data[2];
    m_accel_z = data[3];
    m_gyro_x = data[4];
    m_gyro_y = data[5];
    m_gyro_z = data[6];
}

void spartan::PacketType::setTimestamp(unsigned long timestamp) {
    m_timestamp = timestamp;
}

unsigned long spartan::PacketType::getTimestamp() const {
    return m_timestamp;
}

spartan::IMUDataPacket::IMUDataPacket(Sensor *lsm6ds33)
    : m_lsm6ds33(dynamic_cast<spartan::LSM6DS33*>(lsm6ds33)) {}

int spartan::IMUDataPacket::getSize() const { return 7; }

void spartan::IMUDataPacket::update() {
    unsigned long timestamp = m_lsm6ds33->getTimestamp();

    if (timestamp == getTimestamp()) {
        // Sensor data has not changed, so no need to update data
        return;
    }

    // Set timestamp
    setTimestamp(timestamp);

    // Populate data fields
    float *data = m_lsm6ds33->getData();
    m_temp = data[0];
    m_accel_x = data[1];
    m_accel_y = data[2];
    m_accel_z = data[3];
    m_gyro_x = data[4];
    m_gyro_y = data[5];
    m_gyro_z = data[6];
}

std::string spartan::IMUDataPacket::format() const { 
    return "\ttimestamp: " + std::to_string(m_timestamp)
           + "\n\taccel_y: " + std::to_string(m_accel_y) 
           + "\n\taccel_z: " + std::to_string(m_accel_z) 
           + "\n\tgyro_x: " + std::to_string(m_gyro_x) 
           + "\n\tgyro_y: " + std::to_string(m_gyro_y) 
           + "\n\tgyro_z: " + std::to_string(m_gyro_z) 
           + "\n\ttemperature: " + std::to_string(m_temp);
};

int spartan::AltimeterDataPacket::getSize() const { return 3; }

int spartan::GPSDataPacket::getSize() const { return 4; }

int spartan::AVNHealthPacket::getSize() const { return 7; }

int spartan::FCHealthPacket::getSize() const { return 3; }

int spartan::RadioHealthPacket::getSize() const { return 3; }

int spartan::PayloadHealthPacket::getSize() const { return 3; }