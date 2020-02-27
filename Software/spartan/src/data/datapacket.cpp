#include "datapacket.h"

// Generic constructor
spartan::DataPacket::DataPacket(unsigned long timestamp, float * data) {
    m_timestamp = timestamp;
    this->data = data;
}

// Generic write
std::ostream& spartan::operator<<(std::ostream &out, const spartan::DataPacket &dp) {
    out << dp.m_timestamp << "\n";
    out << dp.getSize() << "\n";
    for (int i=0; i<dp.getSize(); i++)
        out << dp.data[i] << "\n";
    return out;
}

// Generic read
std::istream & spartan::operator>>(std::istream &in, spartan::DataPacket &dp) {
    in >> dp.m_timestamp;
    in.ignore(256, '\n'); // Don't really need the size
    for (int i = 0; i < dp.getSize(); i++)
        in >> dp.data[i];
    return in;
}

/* Deprecated. Corresponds to deprecated definitions in `mdp.h`.
void spartan::IMUDataPacket::populate(const MasterDataPacket &dp) {
    m_timestamp = dp.timestamp;
    // m_accel_y = dp.accel_y;
    // m_accel_z = dp.accel_z;
    // m_gyro_x = dp.gyro_x;
    // m_gyro_y = dp.gyro_y;
    // m_gyro_z = dp.gyro_z;
    // m_temp = dp.temp;
}

void spartan::AltimeterDataPacket::populate(const DataPacket &dp) {
    m_timestamp = dp.timestamp;
    m_pressure = dp.pressure;
    m_baro_altitude = dp.baro_altitude;
}

void spartan::GPSDataPacket::populate(const DataPacket &dp) {
    m_timestamp = dp.timestamp;
    m_latitude = dp.latitude;
    m_longitude = dp.longitude;
    m_gps_altitude = dp.gps_altitude;
}

void spartan::AVNHealthPacket::populate(const DataPacket &dp) {
    m_timestamp = dp.timestamp;
    m_voltage_AVN = dp.voltage_AVN;
    m_IMU1_current = dp.IMU1_current;
    m_IMU2_current = dp.IMU2_current;
    m_IMU3_current = dp.IMU3_current;
    m_GPS_current = dp.GPS_current;
    m_altimeter_current = dp.altimeter_current;
}

void spartan::FCHealthPacket::populate(const DataPacket &dp) {
    m_timestamp = dp.timestamp;
    m_FC_voltage = dp.FC_voltage;
    m_FC_current = dp.FC_current;
}

void spartan::RadioHealthPacket::populate(const DataPacket &dp) {
    m_timestamp = dp.timestamp;
    m_radio_voltage = dp.radio_voltage;
    m_radio_current = dp.radio_current;
}

void spartan::PayloadHealthPacket::populate(const DataPacket &dp) {
    m_timestamp = dp.timestamp;
    m_payload_voltage = dp.payload_voltage;
    m_payload_current = dp.payload_current;
}
*/
