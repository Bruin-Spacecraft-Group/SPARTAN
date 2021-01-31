#ifndef DATAPACKET_H_INCLUDED
#define DATAPACKET_H_INCLUDED

#include <string>

#include "sensors/lsm6ds33.h"

using ulong = unsigned long;

namespace spartan {
    class Sensor;
    class LSM6DS33;

    struct EncodedPacket {
        uint8_t id;
        ulong timestamp;
        uint8_t length;
        uint8_t *data;
    };

    std::string format_encoded_packet(EncodedPacket &packet);

    class DecodedPacket {
    public:
        explicit DecodedPacket(ulong timestamp);

        ulong get_timestamp() const;

    private:
        ulong m_timestamp;
    };

    class IMUDecodedPacket : public DecodedPacket {
    public:
        IMUDecodedPacket(ulong timestamp, const float *data);

    private:
        float m_accel_x;
        float m_accel_y;
        float m_accel_z;
        float m_gyro_x;
        float m_gyro_y;
        float m_gyro_z;
        float m_temp;
    };

    class PacketType {
    public:
        virtual int getSize() const = 0;
        virtual std::string format() const = 0;

        void setTimestamp(unsigned long timestamp);
        unsigned long getTimestamp() const;

    protected:
        unsigned long m_timestamp;
    };

    class IMUDataPacket : public PacketType {
    public:
        explicit IMUDataPacket(Sensor *lsm6ds33);

        int getSize() const override;
        std::string format() const override;

    private:
        LSM6DS33 *m_lsm6ds33;
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
        virtual int getSize() const;
    private:
        float m_pressure;
        float m_baro_altitude;
    };

    class GPSDataPacket : public PacketType {
    public:
        virtual int getSize() const;
    private:
        float m_latitude;
        float m_longitude;
        float m_gps_altitude;
    };

    class AVNHealthPacket : public PacketType {
    public:
        virtual int getSize() const;
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
        virtual int getSize() const;
    private:
        float m_FC_voltage;
        float m_FC_current;
    };

    class RadioHealthPacket : public PacketType {
    public:
        virtual int getSize() const;
    private:
        float m_radio_voltage;
        float m_radio_current;
    };

    class PayloadHealthPacket : public PacketType {
    public:
        virtual int getSize() const;
    private:
        float m_payload_voltage;
        float m_payload_current;
    };

    class PayloadDataPacket {};

} // namespace spartan

#endif // DATAPACKET_H_INCLUDED


