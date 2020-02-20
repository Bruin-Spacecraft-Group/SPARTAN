#include "i2c.h"

mraa::I2c::I2c(int bus, bool raw = false) {
    if (raw) {
        m_i2c = mraa_i2c_init_raw(bus);
    } else {
        m_i2c = mraa_i2c_init(bus);
    }
    if (m_i2c == NULL) {
        throw std::invalid_argument("Invalid i2c bus");
    }
}

mraa::I2c::I2c(void* i2c_context) {
    m_i2c = (mraa_i2c_context) i2c_context;
    if (m_i2c == NULL) {
        throw std::invalid_argument("Invalid I2C context");
    }
}

mraa::I2c::~I2c() {
    mraa_i2c_stop(m_i2c);
}

mraa::Result mraa::I2c::frequency(mraa::I2cMode mode) {
    return (Result) mraa_i2c_frequency(m_i2c, (mraa_i2c_mode_t) mode);
}

mraa::Result mraa::I2c::address(uint8_t address) {
    return (Result) mraa_i2c_address(m_i2c, address);
}

uint8_t mraa::I2c::readByte() {
    int x = mraa_i2c_read_byte(m_i2c);
    if (x == -1) {
        throw std::invalid_argument("Unknown error in I2c::readByte()");
    }
    return (uint8_t) x;
}

int mraa::I2c::read(uint8_t* data, int length) {
    return mraa_i2c_read(m_i2c, data, length);
}

uint8_t mraa::I2c::readReg(uint8_t reg) {
    int x = mraa_i2c_read_byte_data(m_i2c, reg);
    if (x == -1) {
        throw std::invalid_argument("Unknown error in I2c::readReg()");
    }
    return (uint8_t) x;
}

uint16_t mraa::I2c::readWordReg(uint8_t reg) {
    int x = mraa_i2c_read_word_data(m_i2c, reg);
    if (x == -1) {
        throw std::invalid_argument("Unknown error in I2c::readReg()");
    }
    return (uint16_t) x;
}

int mraa::I2c::readBytesReg(uint8_t reg, uint8_t* data, int length) {
    return mraa_i2c_read_bytes_data(m_i2c, reg, data, length);
}

mraa::Result mraa::I2c::writeByte(uint8_t data) {
    return (Result) mraa_i2c_write_byte(m_i2c, data);
}

mraa::Result mraa::I2c::write(const uint8_t* data, int length) {
    return (Result) mraa_i2c_write(m_i2c, data, length);
}

mraa::Result mraa::I2c::writeReg(uint8_t reg, uint8_t data) {
    return (Result) mraa_i2c_write_byte_data(m_i2c, data, reg);
}

mraa::Result mraa::I2c::writeWordReg(uint8_t reg, uint16_t data) {
    return (Result) mraa_i2c_write_word_data(m_i2c, data, reg);
}