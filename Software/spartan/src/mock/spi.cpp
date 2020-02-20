#include "spi.h"

// Constructors/destructors

mraa::Spi::Spi(int bus) {}
mraa::Spi::Spi(int bus, int cs) {}
mraa::Spi::Spi(void* spi_context) {}
mraa::Spi::~Spi(){}

// SPI interface settings

mraa::Result mraa::Spi::mode(Spi_Mode mode) {}
mraa::Result mraa::Spi::frequency(int hz) {}
mraa::Result mraa::Spi::lsbmode(bool lsb) {}
mraa::Result mraa::Spi::bitPerWord(unsigned int bits) {}

// Read/write functions

int mraa::Spi::writeByte(uint8_t data) {
    return std::rand();
}

int mraa::Spi::writeWord(uint16_t data) {
    return std::rand();
}

uint8_t* mraa::Spi::write(uint8_t* txBuf, int length) {
    uint8_t *buf = (uint8_t *)std::malloc(length * sizeof(uint8_t));
    if (buf == NULL) {
        throw std::bad_alloc();
    }

    for (int i = 0; i < length; i++) {
        buf[i] = (uint8_t) std::rand();
    }
    return buf; // free using std::free
}

uint16_t* mraa::Spi::writeWord(uint16_t* txBuf, int length) {
    uint16_t *buf = (uint16_t *)std::malloc(length * sizeof(uint16_t));
    if (buf == NULL) {
        throw std::bad_alloc();
    }

    for (int i = 0; i < length; i++) {
        buf[i] = (uint16_t) std::rand();
    }
    return buf; // free using std::free
}

mraa::Result mraa::Spi::transfer(uint8_t* txBuf, uint8_t* rxBuf, int length) {
    for (int i = 0; i < length; i++) {
        rxBuf[i] = (uint8_t) std::rand();
    }
    return mraa::SUCCESS;
}

mraa::Result mraa::Spi::transfer_word(uint16_t* txBuf, uint16_t* rxBuf, int length) {
    for (int i = 0; i < length; i++) {
        rxBuf[i] = (uint16_t) std::rand();
    }
    return mraa::SUCCESS;
}
