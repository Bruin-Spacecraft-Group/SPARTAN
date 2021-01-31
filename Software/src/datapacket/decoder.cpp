#include "decoder.h"

void spartan::Decoder::decode(const EncodedPacket &packet) {
    switch (packet.id) {
        case spartan::data_id::LSM6DS33_DATA:
            m_decoded_packets.push_back(decode_lsm6ds33(packet));
            break;
        case spartan::data_id::LSM6DS33_SET:
            set_lsm6ds33();
            break;
        default:
            break;
    }
}

spartan::DecodedPacket* spartan::Decoder::decode_lsm6ds33(const EncodedPacket &packet) const {
    //record raw acceleration values using data reads for x,y,z respectively
    //DATAx0 is the least significant byte, and DATAx1 is the most significant byte
    //conversion of raw sensor data into relevant values based on constant offset values
    int32_t temp = ((packet.data[1] << 8) | packet.data[0]);

    int32_t gyro_x = ((packet.data[3] << 8) | packet.data[2]);
    int32_t gyro_y = ((packet.data[5] << 8) | packet.data[4]);
    int32_t gyro_z = ((packet.data[7] << 8) | packet.data[6]);

    int32_t accel_x = ((packet.data[9] << 8) | packet.data[8]);
    int32_t accel_y = ((packet.data[11] << 8) | packet.data[10]);
    int32_t accel_z = ((packet.data[13] << 8) | packet.data[12]);

    float decoded_data[7] = {
        (float) ((temp / 16.0) + m_lsm6ds33_settings.temp_offset),
        (float) ((accel_x * m_lsm6ds33_settings.accel_multiplier) + m_lsm6ds33_settings.accel_offset_x),
        (float) ((accel_y * m_lsm6ds33_settings.accel_multiplier) + m_lsm6ds33_settings.accel_offset_y),
        (float) ((accel_z * m_lsm6ds33_settings.accel_multiplier) + m_lsm6ds33_settings.accel_offset_z),
        (float) ((gyro_x * m_lsm6ds33_settings.gyro_multiplier) + m_lsm6ds33_settings.gyro_offset_x),
        (float) ((gyro_y * m_lsm6ds33_settings.gyro_multiplier) + m_lsm6ds33_settings.gyro_offset_y),
        (float) ((gyro_z * m_lsm6ds33_settings.gyro_multiplier) + m_lsm6ds33_settings.gyro_offset_z)
    };

    return new IMUDecodedPacket(packet.timestamp, decoded_data);
}

void spartan::Decoder::set_lsm6ds33() {
    // TODO
}