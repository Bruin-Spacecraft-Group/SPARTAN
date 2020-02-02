#ifndef DATAPACKET_H_INCLUDED
#define DATAPACKET_H_INCLUDED

namespace spartan {
    struct DataPacket {
        unsigned long timestamp;

        float accel_y;
        float accel_z;
        float gyro_x;
        float gyro_y;
        float gyro_z;
        float temp;
        float pressure;
        float baro_altitude;
        float latitude;
        float longitude;
        float gps_altitude;

        float voltage_AVN;
        float IMU1_current;
        float IMU2_current;
        float IMU3_current;
        float GPS_current;
        float altimeter_current;
        float FC_voltage;
        float FC_current;
        float radio_voltage;
        float radio_current;
        float payload_voltage;
        float payload_current;
    };


    // Protocol (abstract base class) to which all datapackets conform to
    class PacketType {
    public:
        virtual void populate(const DataPacket &dp) = 0;
    protected:
        unsigned long m_timestamp;
    };

    class IMUDataPacket : public PacketType {
    public:
        virtual void populate(const DataPacket &dp);
    private:
        float m_accel_y;
        float m_accel_z;
        float m_gyro_x;
        float m_gyro_y;
        float m_gyro_z;
        float m_temp;
    };

    class AltimeterDataPacket : public PacketType {
    public:
        virtual void populate(const DataPacket &dp);
    private:
        float m_pressure;
        float m_baro_altitude;
    };
    
    class GPSDataPacket : public PacketType {
    public:
        virtual void populate(const DataPacket &dp);
    private:
        float m_latitude;
        float m_longitude;
        float m_gps_altitude;
    };

    class AVNHealthPacket : public PacketType {
    public:
        virtual void populate(const DataPacket &dp);
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
        virtual void populate(const DataPacket &dp);
    private:
        float m_FC_voltage;
        float m_FC_current;
    };

    class RadioHealthPacket : public PacketType {
    public:
        virtual void populate(const DataPacket &dp);
    private:
        float m_radio_voltage;
        float m_radio_current;
    };

    class PayloadHealthPacket : public PacketType {
    public:
        virtual void populate(const DataPacket &dp);
    private:
        float m_payload_voltage;
        float m_payload_current;
    };

    class PayloadDataPacket {};

} // namespace spartan

#endif // DATAPACKET_H_INCLUDED