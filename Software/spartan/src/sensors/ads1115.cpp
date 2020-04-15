#include "ads1115.h"

// TODO: change instanceID when these are updated
spartan::ADS1115::ADS1115(int bus, uint8_t address) : Sensor(bus, 0), m_i2c(bus, true) {
    for (int i = 0; i < 4; ++i) {
        m_readings[i] = 0;
    }
}

bool spartan::ADS1115::pollData(spartan::DataPacket &dp) {
    uint8_t writeBuf[3];
    uint8_t readBuf[2];

    // Set the slave to talk to
    if (m_i2c.address(0x48) != mraa::SUCCESS) {
        std::cerr << "ADC Failed to set address\n";
        return 0;
    }

    for (int channel = 0; channel < 4; ++channel) {
        writeBuf[0] = 0x01; // Write to config register
        writeBuf[1] = 0xD3;
        writeBuf[2] = 0x03;
        if (m_i2c.write(writeBuf, 3) != mraa::SUCCESS) {
            std::cerr << "ADC Failed to write config register (24 bits)\n";
            return 0;
        }

        readBuf[0] = 0;
        readBuf[1] = 0;

        while ((readBuf[0] & 0x80) == 0) {
            m_i2c.read(readBuf, 2); // Read the config register into readBuf
        }

        writeBuf[0] = 0;					// Set pointer register to 0 to read from the conversion register
        if (m_i2c.write(writeBuf, 1) != mraa::SUCCESS) {
            std::cerr << "Failed to write to pointer register\n";
        }

        m_i2c.read(readBuf, 2);

        int16_t val = readBuf[0] << 8 | readBuf[1];	// Combine the two bytes of readBuf into a single 16 bit result 
        m_readings[channel] = (float)val*4.096/32767.0;

        printf("A0 Voltage Reading %f (V) \n", (float)val*4.096/32767.0);
    }

    // TODO: Integrate datapacket

    return 0; 
}

int spartan::ADS1115::printValues() const {
    for (int i = 0; i < 4; ++i) {
        printf("A%d Voltage Reading %f (V) \n", i, m_readings[i]);
    }
}
