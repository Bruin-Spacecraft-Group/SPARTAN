#include "uart.h"

mraa::Uart::Uart(int uart) {
    m_uart = mraa_uart_init(uart);

    if (m_uart == NULL) {
        throw std::invalid_argument("Error initialising UART");
    }
}

mraa::Uart::Uart(std::string path) {
    m_uart = mraa_uart_init_raw(path.c_str());

    if (m_uart == NULL) {
        throw std::invalid_argument("Error initialising UART");
    }
}

mraa::Uart::Uart(void* uart_context) {
    m_uart = (mraa_uart_context) uart_context;

    if (m_uart == NULL) {
        throw std::invalid_argument("Invalid UART context");
    }
}

mraa::Uart::~Uart() {
    mraa_uart_stop(m_uart);
}

std::string mraa::Uart::getDevicePath() {
    std::string ret_val(mraa_uart_get_dev_path(m_uart));
    return ret_val;
}

int mraa::Uart::read(char* data, int length) {
    return mraa_uart_read(m_uart, data, (size_t) length);
}

int mraa::Uart::write(const char* data, int length) {
    return mraa_uart_write(m_uart, data, (size_t) length);
}

std::string mraa::Uart::readStr(int length) {
    char* data = (char*) malloc(sizeof(char) * length);
    if (data == NULL) {
        throw std::bad_alloc();
    }

    int v = mraa_uart_read(m_uart, data, (size_t) length);
    std::string ret(data, v);
    free(data);
    return ret;
}

int mraa::Uart::writeStr(std::string data) {
    // this is data.length() not +1 because we want to avoid the '\0' char
    return mraa_uart_write(m_uart, data.c_str(), (data.length()));
}

bool mraa::Uart::dataAvailable(unsigned int millis = 0) {
    if (mraa_uart_data_available(m_uart, millis))
        return true;
    else
        return false;
}

mraa::Result mraa::Uart::flush() {
    return (Result) mraa_uart_flush(m_uart);
}

mraa::Result mraa::Uart::sendBreak(int duration) {
    return (Result) mraa_uart_sendbreak(m_uart, duration);
}

mraa::Result mraa::Uart::setBaudRate(unsigned int baud) {
    return (Result) mraa_uart_set_baudrate(m_uart, baud);
}

mraa::Result mraa::Uart::setMode(int bytesize, UartParity parity, int stopbits) {
    return (Result) mraa_uart_set_mode(m_uart, bytesize, (mraa_uart_parity_t) parity, stopbits);
}

mraa::Result mraa::Uart::setFlowcontrol(bool xonxoff, bool rtscts) {
    return (Result) mraa_uart_set_flowcontrol(m_uart, xonxoff, rtscts);
}

mraa::Result mraa::Uart::setTimeout(int read, int write, int interchar) {
    return (Result) mraa_uart_set_timeout(m_uart, read, write, interchar);
}

mraa::Result mraa::Uart::setNonBlocking(bool nonblock) {
    return (Result) mraa_uart_set_non_blocking(m_uart, nonblock);
}