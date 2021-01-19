#include "spi.h"

// Constructors/destructors

mraa::Spi::Spi(int bus) {
    (void) bus;
}

mraa::Spi::Spi(int bus, int cs) {
    (void) bus;
    (void) cs;
}

mraa::Spi::Spi(void* spi_context) {
    (void) spi_context;
}

mraa::Spi::~Spi(){}

// SPI interface settings

mraa::Result mraa::Spi::mode(Spi_Mode mode) {
    (void) mode;

    return mraa::SUCCESS;
}

mraa::Result mraa::Spi::frequency(int hz) {
    (void) hz;

    return mraa::SUCCESS;
}

mraa::Result mraa::Spi::lsbmode(bool lsb) {
    (void) lsb;

    return mraa::SUCCESS;
}

mraa::Result mraa::Spi::bitPerWord(unsigned int bits) {
    (void) bits;

    return mraa::SUCCESS;
}

// Read/write functions

int mraa::Spi::writeByte(uint8_t data) {
    (void) data;

    return std::rand();
}

int mraa::Spi::writeWord(uint16_t data) {
    (void) data;

    return std::rand();
}

uint8_t* mraa::Spi::write(uint8_t* txBuf, int length) {
    (void) txBuf;

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
    (void) txBuf;

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
    (void) txBuf;

    for (int i = 0; i < length; i++) {
        rxBuf[i] = (uint8_t) std::rand();
    }
    return mraa::SUCCESS;
}

mraa::Result mraa::Spi::transfer_word(uint16_t* txBuf, uint16_t* rxBuf, int length) {
    (void) txBuf;

    for (int i = 0; i < length; i++) {
        rxBuf[i] = (uint16_t) std::rand();
    }
    return mraa::SUCCESS;
}
