#include "i2c.h"

// Contructors/destructors

mraa::I2c::I2c(int bus, bool raw = false) {}
mraa::I2c::I2c(void* i2c_context) {}
mraa::I2c::~I2c() {}

// I2C interface settings

mraa::Result mraa::I2c::frequency(mraa::I2cMode mode) {
    return mraa::SUCCESS;
}

mraa::Result mraa::I2c::address(uint8_t address) {
    return mraa::SUCCESS;
}

// Read functions

uint8_t mraa::I2c::readByte() {
    return (uint8_t) std::rand();
}

int mraa::I2c::read(uint8_t* data, int length) {
    for (int i = 0; i < length; i++) {
        data[i] = (uint8_t) std::rand();
    }
    return length;
}

uint8_t mraa::I2c::readReg(uint8_t reg) {
    return (uint8_t) std::rand();
}

uint16_t mraa::I2c::readWordReg(uint8_t reg) {
    return (uint16_t) std::rand();
}

int mraa::I2c::readBytesReg(uint8_t reg, uint8_t* data, int length) {
    for (int i = 0; i < length; i++) {
        data[i] = (uint8_t) std::rand();
    }
    return length;
}

// Write functions

mraa::Result mraa::I2c::writeByte(uint8_t data) {
    return mraa::SUCCESS;
}

mraa::Result mraa::I2c::write(const uint8_t* data, int length) {
    return mraa::SUCCESS;
}

mraa::Result mraa::I2c::writeReg(uint8_t reg, uint8_t data) {
    return mraa::SUCCESS;
}

mraa::Result mraa::I2c::writeWordReg(uint8_t reg, uint16_t data) {
    return mraa::SUCCESS;
}
