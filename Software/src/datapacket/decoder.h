#ifndef SPARTAN_FLIGHT_SOFTWARE_DECODER_H
#define SPARTAN_FLIGHT_SOFTWARE_DECODER_H

#include "datapacket.h"

#include <string>
#include <cstdint>
#include <vector>

using std::string;

namespace spartan {


    class Decoder {
    public:
        // Decodes a string into a DecodedPacket
        void decode(const string &packet);

        // Decoders for each sensor
        DecodedPacket* decode_lsm6ds33(ulong timestamp, const char *data) const;

        // Setters for each sensor's settings
        void set_lsm6ds33();

    private:
        struct lsm6ds33_settings {
            float temp_offset = 0.0;
            float accel_offset_x = 0.0;
            float accel_offset_y = 0.0;
            float accel_offset_z = 0.0;
            float gyro_offset_x = 0.0;
            float gyro_offset_y = 0.0;
            float gyro_offset_z = 0.0;
            float accel_multiplier = 0.0;
            float gyro_multiplier = 0.0;
        } m_lsm6ds33_settings;

        std::vector<spartan::DecodedPacket *> m_decoded_packets;
    };
}

#endif //SPARTAN_FLIGHT_SOFTWARE_DECODER_H
