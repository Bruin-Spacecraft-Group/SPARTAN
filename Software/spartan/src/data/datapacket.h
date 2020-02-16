#ifndef DATAPACKET_H_INCLUDED
#define DATAPACKET_H_INCLUDED

#include <fstream>

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
    /*
     * Pattern of output
     * 1. Timestamp
     * 2. Data packet array size
     * 3. dp.data[0]
     * ...
     */
    class PacketType {
    public:
        virtual void populate(const DataPacket & dp) = 0;

        // Each sensor packet would implement this to vary data array size
        virtual int getSize() const = 0;

        // Read and write PacketType data through file stream
        friend std::ostream & operator << (std::ostream & out, const PacketType & dp)
        {
            out << dp.m_timestamp << "\n";
            out << dp.getSize() << "\n";
            for (int i=0; i<dp.getSize(); i++)
                out << dp.data[i] << "\n";
            return out;
        }

        friend std::istream & operator >> (std::istream &in, PacketType & dp)
        {
            in >> dp.m_timestamp;
            in.ignore(256, '\n'); // Don't really need the size
            for (int i = 0; i < dp.getSize(); i++)
                in >> dp.data[i];
            return in;
        }
        
        PacketType(unsigned long timestamp, float * data) {
            m_timestamp = timestamp;
            this->data = data;
        }


    protected:
        unsigned long m_timestamp;
        float * data;
    };

    /* (timestamp, 
     *  [0: accel.x, 1: .y, 2: .z,
     *  3: gyro.x, 4: .y, 5: .z,
     *  6: temp] )
     * */
    class IMUDataPacket : public PacketType {
    public:
        // Size of data array
        int getSize() const {
            return 7;
        }
        virtual void populate(const DataPacket &dp);

        IMUDataPacket(unsigned long timestamp, float * data): DataPacket(timestamp, data) {}
    };



    /* Commented to test new simplified generic structure
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
     */

} // namespace spartan

#endif // DATAPACKET_H_INCLUDED