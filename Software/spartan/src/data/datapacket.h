#ifndef DATAPACKET_H_INCLUDED
#define DATAPACKET_H_INCLUDED

#include <fstream>
#include <data/mdp.h>

namespace spartan {
    // Protocol (abstract base class) to which all datapackets conform to
    /*
     * Pattern of output
     * 1. Timestamp
     * 2. Data packet array size
     * 3. dp.data[0]
     * ...
     */
    class DataPacket {
    public:
        DataPacket(unsigned long timestamp);

        virtual void populate(const MasterDataPacket & dp) = 0;

        // Each sensor packet would implement this to vary data array size
        virtual int getSize() const = 0;

        // Read and write PacketType data through file stream
        friend std::ostream &operator<<(std::ostream &out, const DataPacket &dp);
        friend std::istream &operator>>(std::istream &in, DataPacket &dp);

    protected:
        unsigned long m_timestamp;
        float *m_data;
    }; // class DataPacket

    /* (timestamp, 
     *  [0: accel.x, 1: .y, 2: .z,
     *  3: gyro.x, 4: .y, 5: .z,
     *  6: temp] )
     */
    class IMUDataPacket : public DataPacket {
    public:
        IMUDataPacket(unsigned long timestamp);
        IMUDataPacket(unsigned long timestamp, MasterDataPacket &dp);
        ~IMUDataPacket();

        virtual void populate(const MasterDataPacket &dp);

        // Size of data array
        int getSize() const;
    }; // class IMUDataPacket
} // namespace spartan

#endif // DATAPACKET_H_INCLUDED
