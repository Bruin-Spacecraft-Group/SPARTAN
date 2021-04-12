#include "datapacket.h"

#include <string>

std::string spartan::format_encoded_packet(EncodedPacket &packet) {
    std::string formatted = std::to_string(packet.timestamp) + ',';
    formatted += packet.id;
    formatted += packet.length;

    for (int i = 0; i < packet.length; i++) {
        formatted += packet.data[i];
    }

    return formatted;
}

spartan::DecodedPacket::DecodedPacket(ulong timestamp) : m_timestamp(timestamp) {}

ulong spartan::DecodedPacket::get_timestamp() const {
    return m_timestamp;
}

spartan::IMUPacket::IMUPacket(ulong timestamp, const float *data) : DecodedPacket(timestamp) {
    m_temp = data[0];
    m_accel_x = data[1];
    m_accel_y = data[2];
    m_accel_z = data[3];
    m_gyro_x = data[4];
    m_gyro_y = data[5];
    m_gyro_z = data[6];
}