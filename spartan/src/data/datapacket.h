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
} // namespace spartan

#endif // DATAPACKET_H_INCLUDED