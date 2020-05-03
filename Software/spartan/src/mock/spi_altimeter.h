#ifndef SPI_ALTIMETER_H_INCLUDED
#define SPI_ALTIMETER_H_INCLUDED

#include "spi.h"

namespace mraa {
    // Fake Altimeter over SPI. See spi.h for method descriptions.
    class SpiAltimeter {
    public:
        SpiAltimeter();
        virtual ~SpiAltimeter();

        virtual int writeByte(uint8_t data);
        virtual int writeWord(uint16_t data);
        virtual uint8_t* write(uint8_t* txBuf, int length);

#ifndef SWIG
        virtual uint16_t* writeWord(uint16_t* txBuf, int length);
        virtual Result transfer(uint8_t* txBuf, uint8_t* rxBuf, int length);
        virtual Result transfer_word(uint16_t* txBuf, uint16_t* rxBuf, int length);
#endif
    };
} // namespace mraa

#endif // SPI_ALTIMETER_H_INCLUDED
