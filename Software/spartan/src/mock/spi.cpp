#include "spi.h"

mraa::Spi::Spi(int bus) {
    m_spi = mraa_spi_init(bus);

    if (m_spi == NULL) {
        throw std::invalid_argument("Error initialising SPI bus");
    }
}

mraa::Spi::Spi(int bus, int cs) {
    m_spi = mraa_spi_init_raw(bus, cs);

    if (m_spi == NULL) {
        throw std::invalid_argument("Error initialising SPI bus");
    }
}

mraa::Spi::Spi(void* spi_context) {
    m_spi = (mraa_spi_context) spi_context;
    if (m_spi == NULL) {
        throw std::invalid_argument("Invalid SPI context");
    }
}

mraa::Spi::~Spi(){
    mraa_spi_stop(m_spi);
}

mraa::Result mraa::Spi::mode(Spi_Mode mode) {
    return (Result) mraa_spi_mode(m_spi, (mraa_spi_mode_t) mode);
}

mraa::Result mraa::Spi::frequency(int hz) {
    return (Result) mraa_spi_frequency(m_spi, hz);
}

int mraa::Spi::writeByte(uint8_t data) {
    return mraa_spi_write(m_spi, (uint8_t) data);
}

int mraa::Spi::writeWord(uint16_t data) {
    return mraa_spi_write_word(m_spi, (uint16_t) data);
}

uint8_t* mraa::Spi::write(uint8_t* txBuf, int length) {
    return mraa_spi_write_buf(m_spi, txBuf, length);
}

uint16_t* mraa::Spi::writeWord(uint16_t* txBuf, int length) {
    return mraa_spi_write_buf_word(m_spi, txBuf, length);
}

mraa::Result mraa::Spi::transfer(uint8_t* txBuf, uint8_t* rxBuf, int length) {
    return (Result) mraa_spi_transfer_buf(m_spi, txBuf, rxBuf, length);
}

mraa::Result mraa::Spi::transfer_word(uint16_t* txBuf, uint16_t* rxBuf, int length) {
    return (Result) mraa_spi_transfer_buf_word(m_spi, txBuf, rxBuf, length);
}

mraa::Result mraa::Spi::lsbmode(bool lsb) {
    return (Result) mraa_spi_lsbmode(m_spi, (mraa_boolean_t) lsb);
}

mraa::Result mraa::Spi::bitPerWord(unsigned int bits) {
    return (Result) mraa_spi_bit_per_word(m_spi, bits);
}
