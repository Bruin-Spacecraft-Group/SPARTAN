#ifndef I2C_H_INCLUDED
#define I2C_H_INCLUDED

#include "types.h"
#include <stdexcept>

namespace mraa
{
    class I2c
    {
    public:
        /**
         * Instantiates an i2c bus. Multiple instances of the same bus can
         * exist and the bus is not guaranteed to be on the correct address
         * before read/write.
         *
         * @param bus The i2c bus to use
         * @param raw Whether to disable pinmapper for your board
         */
        I2c(int bus, bool raw = false);

        /**
         * I2C constructor, takes a pointer to a I2C context and initialises the I2C class
         *
         * @param i2c_context void * to an I2C context
         */
        I2c(void* i2c_context);

        /**
         * Closes the I2c Bus used. This does not guarantee the bus will not
         * be usable by anyone else or communicates this disconnect to any
         * slaves.
         */
        ~I2c();

        /**
         * Sets the i2c Frequency for communication. Your board may not support
         * the set frequency. Anyone can change this at any time and this will
         * affect every slave on the bus
         *
         * @param mode Frequency to set the bus to
         * @return Result of operation
         */
        Result frequency(I2cMode mode);

        /**
         * Set the slave to talk to, typically called before every read/write
         * operation
         *
         * @param address Communicate to the i2c slave on this address
         * @return Result of operation
         */
        Result address(uint8_t address);

        /**
         * Read exactly one byte from the bus
         *
         * @throws std::invalid_argument in case of error
         * @return char read from the bus
         */
        uint8_t readByte();

        /**
         * Read length bytes from the bus into *data pointer
         *
         * @param data Data to read into
         * @param length Size of read in bytes to make
         * @return length of read, should match length
         */
        int read(uint8_t* data, int length);

        /**
         * Read byte from an i2c register
         *
         * @param reg Register to read from
         *
         * @throws std::invalid_argument in case of error
         * @return char read from register
         */
        uint8_t readReg(uint8_t reg);

        /**
         * Read word from an i2c register
         *
         * @param reg Register to read from
         *
         * @throws std::invalid_argument in case of error
         * @return char read from register
         */
        uint16_t readWordReg(uint8_t reg);

        /**
         * Read length bytes from the bus into *data pointer starting from
         * an i2c register
         *
         * @param reg Register to read from
         * @param data pointer to the byte array to read data in to
         * @param length max number of bytes to read
         * @return length passed to the function or -1
         */
        int readBytesReg(uint8_t reg, uint8_t* data, int length);

        /**
         * Write a byte on the bus
         *
         * @param data The byte to send on the bus
         * @return Result of operation
         */
        Result writeByte(uint8_t data);

        /**
         * Write length bytes to the bus, the first byte in the array is the
         * command/register to write
         *
         * @param data Buffer to send on the bus, first byte is i2c command
         * @param length Size of buffer to send
         * @return Result of operation
         */
        Result write(const uint8_t* data, int length);

        /**
         * Write a byte to an i2c register
         *
         * @param reg Register to write to
         * @param data Value to write to register
         * @return Result of operation
         */
        Result writeReg(uint8_t reg, uint8_t data);

        /**
         * Write a word to an i2c register
         *
         * @param reg Register to write to
         * @param data Value to write to register
         * @return Result of operation
         */
        Result writeWordReg(uint8_t reg, uint16_t data);
    };
}

#endif // I2C_H_INCLUDED
