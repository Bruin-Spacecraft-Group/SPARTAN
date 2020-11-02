#include "mdp.h"

#include <string>

// spartan::IMUDataPacket::IMUDataPacket() {}

int spartan::IMUDataPacket::getSize() const { return 7; }

std::string spartan::IMUDataPacket::format() const { 
    return "\ttimestamp: " + std::to_string(m_timestamp)
           + "\n\taccel_y: " + std::to_string(m_accel_y) 
           + "\n\taccel_z: " + std::to_string(m_accel_z) 
           + "\n\tgyro_x: " + std::to_string(m_gyro_x) 
           + "\n\tgyro_y: " + std::to_string(m_gyro_y) 
           + "\n\tgyro_z: " + std::to_string(m_gyro_z) 
           + "\n\ttemperature: " + std::to_string(m_temp);
};

void spartan::IMUDataPacket::populate(const MasterDataPacket &dp) {
    m_timestamp = dp.timestamp;
    m_accel_y = dp.accel_y;
    m_accel_z = dp.accel_z;
    m_gyro_x = dp.gyro_x;
    m_gyro_y = dp.gyro_y;
    m_gyro_z = dp.gyro_z;
    m_temp = dp.temp;
}

int spartan::AltimeterDataPacket::getSize() const { return 3; }

void spartan::AltimeterDataPacket::populate(const MasterDataPacket &dp) {
    m_timestamp = dp.timestamp;
    m_pressure = dp.pressure;
    m_baro_altitude = dp.baro_altitude;
}

int spartan::GPSDataPacket::getSize() const { return 4; }

void spartan::GPSDataPacket::populate(const MasterDataPacket &dp) {
    m_timestamp = dp.timestamp;
    m_latitude = dp.latitude;
    m_longitude = dp.longitude;
    m_gps_altitude = dp.gps_altitude;
}

int spartan::AVNHealthPacket::getSize() const { return 7; }

void spartan::AVNHealthPacket::populate(const MasterDataPacket &dp) {
    m_timestamp = dp.timestamp;
    m_voltage_AVN = dp.voltage_AVN;
    m_IMU1_current = dp.IMU1_current;
    m_IMU2_current = dp.IMU2_current;
    m_IMU3_current = dp.IMU3_current;
    m_GPS_current = dp.GPS_current;
    m_altimeter_current = dp.altimeter_current;
}

int spartan::FCHealthPacket::getSize() const { return 3; }

void spartan::FCHealthPacket::populate(const MasterDataPacket &dp) {
    m_timestamp = dp.timestamp;
    m_FC_voltage = dp.FC_voltage;
    m_FC_current = dp.FC_current;
}

int spartan::RadioHealthPacket::getSize() const { return 3; }

void spartan::RadioHealthPacket::populate(const MasterDataPacket &dp) {
    m_timestamp = dp.timestamp;
    m_radio_voltage = dp.radio_voltage;
    m_radio_current = dp.radio_current;
}

int spartan::PayloadHealthPacket::getSize() const { return 3; }

void spartan::PayloadHealthPacket::populate(const MasterDataPacket &dp) {
    m_timestamp = dp.timestamp;
    m_payload_voltage = dp.payload_voltage;
    m_payload_current = dp.payload_current;
}