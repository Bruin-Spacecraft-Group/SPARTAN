#ifndef SPI_H_INCLUDED
#define SPI_H_INCLUDED

#include "types.h"
#include <stdexcept>
#include <new>

namespace mraa
{
    /**
    * @brief API to Serial Peripheral Interface
    *
    * This file defines the SPI interface for libmraa
    *
    * @snippet spi.cpp Interesting
    */
    class Spi
    {
    public:
        /**
         * Initialise SPI object using the board mapping to set muxes
         *
         * @param bus to use, as listed in the platform definition, normally 0
         */
        Spi(int bus);

        /**
         * Initialise SPI object using 'raw' mode. Mraa will go and grab the spidev device lablled /dev/spidev[bus].[cs]
         *
         * @param bus to use
         * @param cs to use
         */
        Spi(int bus, int cs);

        /**
         * Spi Constructor, takes a pointer to a SPI context and initialises
         * the SPI class
         *
         * @param spi_context void * to SPI context
         */
        Spi(void* spi_context);

        /**
         * Closes spi bus
         */
        ~Spi();

        /**
         * Set the SPI device mode. see spidev0-3
         *
         * @param mode the mode. See Linux spidev doc
         * @return Result of operation
         */
        Result mode(Spi_Mode mode);

        /**
         * Set the SPI device operating clock frequency
         *
         * @param hz the frequency to set in hz
         * @return Result of operation
         */
        Result frequency(int hz);

        /**
         * Write single byte to the SPI device
         *
         * @param data the byte to send
         * @return data received on the miso line or -1 in case of error
         */
        int writeByte(uint8_t data);

        /**
         * Write single byte to the SPI device
         *
         * @param data the byte to send
         * @return data received on the miso line or -1 in case of error
         */
        int writeWord(uint16_t data);

        /**
         * Write buffer of bytes to SPI device The pointer return has to be
         * free'd by the caller. It will return a NULL pointer in cases of
         * error
         *
         * @param txBuf buffer to send
         * @param length size of buffer to send
         * @return uint8_t* data received on the miso line. Same length as passed in
         */
        uint8_t* write(uint8_t* txBuf, int length);

#ifndef SWIG
        /**
         * Write buffer of bytes to SPI device The pointer return has to be
         * free'd by the caller. It will return a NULL pointer in cases of
         * error
         *
         * @param txBuf buffer to send
         * @param length size of buffer (in bytes) to send
         * @return uint8_t* data received on the miso line. Same length as passed in
         */
        uint16_t* writeWord(uint16_t* txBuf, int length);
#endif

#ifndef SWIG
        /**
         * Transfer data to and from SPI device Receive pointer may be null if
         * return data is not needed.
         *
         * @param txBuf buffer to send
         * @param rxBuf buffer to optionally receive data from spi device
         * @param length size of buffer to send
         * @return Result of operation
         */
        Result transfer(uint8_t* txBuf, uint8_t* rxBuf, int length);

        /**
         * Transfer data to and from SPI device Receive pointer may be null if
         * return data is not needed.
         *
         * @param txBuf buffer to send
         * @param rxBuf buffer to optionally receive data from spi device
         * @param length size of buffer to send
         * @return Result of operation
         */
        Result transfer_word(uint16_t* txBuf, uint16_t* rxBuf, int length);
#endif

        /**
         * Change the SPI lsb mode
         *
         * @param lsb Use least significant bit transmission - 0 for msbi
         * @return Result of operation
         */
        Result lsbmode(bool lsb);

        /**
         * Set bits per mode on transaction, default is 8
         *
         * @param bits bits per word
         * @return Result of operation
         */
        Result bitPerWord(unsigned int bits);
    };
}

#endif // SPI_H_INCLUDED
