#ifndef I2C_IMU_H_INCLUDED
#define I2C_IMU_H_INCLUDED

#include "i2c.h"

namespace mraa {
    // Fake IMU over I2C. See i2c.h for method descriptions.
    class I2cImu {
    public:
        I2cImu();
        virtual ~I2cImu();

        virtual uint8_t readByte();
        virtual int read(uint8_t* data, int length);
        virtual uint8_t readReg(uint8_t reg);
        virtual uint16_t readWordReg(uint8_t reg);
        virtual int readBytesReg(uint8_t reg, uint8_t* data, int length);

        virtual Result writeByte(uint8_t data);
        virtual Result write(const uint8_t* data, int length);
        virtual Result writeReg(uint8_t reg, uint8_t data);
        virtual Result writeWordReg(uint8_t reg, uint16_t data);
    };
} // namespace mraa

#endif // I2C_IMU_H_INCLUDED
