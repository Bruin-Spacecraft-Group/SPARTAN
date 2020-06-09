#ifndef MDP_H_INCLUDED
#define MDP_H_INCLUDED

namespace spartan {
    struct MasterDataPacket {
        unsigned long timestamp;
        float accel_xArray[NUM_accel_x];
        float accel_yArray[NUM_accel_y];
        float accel_zArray[NUM_accel_z];
        float gyro_xArray[NUM_gyro_x];
        float gyro_yArray[NUM_gyro_y];
        float gyro_zArray[NUM_gyro_z];
        float tempArray[NUM_temp];
        float pressureArray[NUM_pressure];
        float baro_altitudeArray[NUM_baro_altitude];
        float latitudeArray[NUM_latitude];
        float longitudeArray[NUM_longitude];
        float gps_altitudeArray[NUM_gps_altitude];
        float voltage_AVNArray[NUM_voltage_AVN];
        float IMU1_currentArray[NUM_IMU1_current];
        float IMU2_currentArray[NUM_IMU2_current];
        float IMU3_currentArray[NUM_IMU3_current];
        float GPS_currentArray[NUM_GPS_current];
        float altimeter_currentArray[NUM_altimeter_current];
        float FC_voltageArray[NUM_FC_voltage];
        float FC_currentArray[NUM_FC_current];
        float radio_voltageArray[NUM_radio_voltage];
        float radio_currentArray[NUM_radio_current];
        float payload_voltageArray[NUM_payload_voltage];
        float payload_currentArray[NUM_payload_current];
    };

    /* Deprecated. See generic structure in `datapacket.h`.
    class PacketType {
    public:
        virtual void populate(const MasterDataPacket &dp) = 0;
    protected:
        unsigned long m_timestamp;
    };

    class IMUDataPacket : public PacketType {
    public:
        virtual void populate(const MasterDataPacket &dp);
    private:
        float m_accel_x;
        float m_accel_y;
        float m_accel_z;
        float m_gyro_x;
        float m_gyro_y;
        float m_gyro_z;
        float m_temp;
    };

    class AltimeterDataPacket : public PacketType {
    public:
        virtual void populate(const MasterDataPacket &dp);
    private:
        float m_pressure;
        float m_baro_altitude;
    };

    class GPSDataPacket : public PacketType {
    public:
        virtual void populate(const MasterDataPacket &dp);
    private:
        float m_latitude;
        float m_longitude;
        float m_gps_altitude;
    };

    class AVNHealthPacket : public PacketType {
    public:
        virtual void populate(const MasterDataPacket &dp);
    private:
        float m_voltage_AVN;
        float m_IMU1_current;
        float m_IMU2_current;
        float m_IMU3_current;
        float m_GPS_current;
        float m_altimeter_current;
    };

    class FCHealthPacket : public PacketType {
    public:
        virtual void populate(const MasterDataPacket &dp);
    private:
        float m_FC_voltage;
        float m_FC_current;
    };

    class RadioHealthPacket : public PacketType {
    public:
        virtual void populate(const MasterDataPacket &dp);
    private:
        float m_radio_voltage;
        float m_radio_current;
    };

    class PayloadHealthPacket : public PacketType {
    public:
        virtual void populate(const MasterDataPacket &dp);
    private:
        float m_payload_voltage;
        float m_payload_current;
    };

    class PayloadDataPacket {};
     */
} // namespace spartan

#endif // MDP_H_INCLUDED
