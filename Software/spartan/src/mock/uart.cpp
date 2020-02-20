#include "uart.h"

// Constructors/destructors

mraa::Uart::Uart(int uart) {}
mraa::Uart::Uart(std::string path) {}
mraa::Uart::Uart(void* uart_context) {}
mraa::Uart::~Uart() {}

// UART interface settings

std::string mraa::Uart::getDevicePath() {
    return "/dev/does/not/exist";
}

// Read/write functions

int mraa::Uart::read(char* data, int length) {
    return std::rand();
}

int mraa::Uart::write(const char* data, int length) {
    return length;
}

std::string mraa::Uart::readStr(int length) {
    char* data = (char*) std::malloc(sizeof(char) * length);
    if (data == NULL) {
        throw std::bad_alloc();
    }

    for (int i = 0; i < length; i++) {
        data[i] = (char) std::rand();
    }
    std::string ret(data, length);
    std::free(data);
    return ret;
}

int mraa::Uart::writeStr(std::string data) {
    // this is data.length() not +1 because we want to avoid the '\0' char
    return data.length();
}

// Miscellaneous data functions

bool mraa::Uart::dataAvailable(unsigned int millis = 0) {
    return true;
}

mraa::Result mraa::Uart::flush() {
    return mraa::SUCCESS;
}

mraa::Result mraa::Uart::sendBreak(int duration) {
    return mraa::SUCCESS;
}

mraa::Result mraa::Uart::setBaudRate(unsigned int baud) {
    return mraa::SUCCESS;
}

mraa::Result mraa::Uart::setMode(int bytesize, UartParity parity, int stopbits) {
    return mraa::SUCCESS;
}

mraa::Result mraa::Uart::setFlowcontrol(bool xonxoff, bool rtscts) {
    return mraa::SUCCESS;
}

mraa::Result mraa::Uart::setTimeout(int read, int write, int interchar) {
    return mraa::SUCCESS;
}

mraa::Result mraa::Uart::setNonBlocking(bool nonblock) {
    return mraa::SUCCESS;
}