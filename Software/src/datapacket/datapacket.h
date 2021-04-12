#ifndef DATAPACKET_H_INCLUDED
#define DATAPACKET_H_INCLUDED

#include <string>

#include "../sensors/lsm6ds33.h"

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

    class IMUPacket : public DecodedPacket {
    public:
        IMUPacket(ulong timestamp, const float *data);

    private:
        float m_accel_x;
        float m_accel_y;
        float m_accel_z;
        float m_gyro_x;
        float m_gyro_y;
        float m_gyro_z;
        float m_temp;
    };

//    class AltimeterPacket : public DecodedPacket {
//    public:
//        AltimeterPacket(ulong timestamp, const float *data);
//
//    private:
//        float m_pressure;
//        float m_baro_altitude;
//    };
//
//    class GPSPacket : public DecodedPacket {
//    public:
//        GPSPacket(ulong timestamp, const float *data);
//
//    private:
//        float m_latitude;
//        float m_longitude;
//        float m_gps_altitude;
//    };
//
//    class AVNHealthPacket : public DecodedPacket {
//    public:
//        AVNHealthPacket(ulong timestamp, const float *data);
//
//    private:
//        float m_voltage_AVN;
//        float m_IMU1_current;
//        float m_IMU2_current;
//        float m_IMU3_current;
//        float m_GPS_current;
//        float m_altimeter_current;
//    };
//
//    class FCHealthPacket : public DecodedPacket {
//    public:
//        FCHealthPacket(ulong timestamp, const float *data);
//
//    private:
//        float m_FC_voltage;
//        float m_FC_current;
//    };
//
//    class RadioHealthPacket : public DecodedPacket {
//    public:
//        RadioHealthPacket(ulong timestamp, const float *data);
//
//    private:
//        float m_radio_voltage;
//        float m_radio_current;
//    };
//
//    class PayloadHealthPacket : public DecodedPacket {
//    public:
//        PayloadHealthPacket(ulong timestamp, const float *data);
//
//    private:
//        float m_payload_voltage;
//        float m_payload_current;
//    };
//
//    class PayloadDataPacket {};

} // namespace spartan

#endif // DATAPACKET_H_INCLUDED


