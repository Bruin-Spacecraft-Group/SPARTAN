#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

#include "types.h"
#include <stdlib.h>
#include <stdexcept>
#include <string>

namespace mraa
{
    /**
     * @brief API to UART (enabling only)
     *
     * This file defines the UART interface for libmraa
     *
     * @snippet uart.cpp Interesting
     */
    class Uart
    {
    public:
        /**
         * Uart Constructor, takes a pin number which will map directly to the
         * linux uart number, this 'enables' the uart, nothing more
         *
         * @param uart the index of the uart set to use
         */
        Uart(int uart);

        /**
         * Uart Constructor, takes a string to the path of the serial
         * interface that is needed.
         *
         * @param path the index of the uart set to use
         */
        Uart(std::string path);

        /**
         * Uart Constructor, takes a pointer to the UART context and initialises
         * the UART class
         *
         * @param uart_context void * to a UART context
         */
        Uart(void* uart_context);

        /**
         * Uart destructor
         */
        ~Uart();

        /**
         * Get string with tty device path within Linux
         * For example. Could point to "/dev/ttyS0"
         *
         * @return char pointer of device path
         */
        std::string getDevicePath();

        /**
         * Read bytes from the device into char* buffer
         *
         * @param data buffer pointer
         * @param length maximum size of buffer
         * @return numbers of bytes read
         */
        int read(char* data, int length);

        /**
         * Write bytes in char* buffer to a device
         *
         * @param data buffer pointer
         * @param length maximum size of buffer
         * @return the number of bytes written, or -1 if an error occurred
         */
        int write(const char* data, int length);

        /**
         * Read bytes from the device into a String object
         *
         * @param length to read
         * @throws std::bad_alloc If there is no space left for read.
         * @return string of data
         */
        std::string readStr(int length);

        /**
         * Write bytes in String object to a device
         *
         * @param data string to write
         * @return the number of bytes written, or -1 if an error occurred
         */
        int writeStr(std::string data);

        /**
         * Check to see if data is available on the device for reading
         *
         * @param millis number of milliseconds to wait, or 0 to return immediately
         * @return true if there is data available to read, false otherwise
         */
        bool dataAvailable(unsigned int millis = 0);

        /**
         * Flush the outbound data.
         * Blocks until complete.
         *
         * @return Result of operation
         */
        Result flush();

        /**
         * Send a break to the device.
         * Blocks until complete.
         *
         * @param duration When 0, send a break lasting at least 250
         * milliseconds, and not more than 500 milliseconds.  When non zero,
         * the break duration is implementation specific.
         * @return Result of operation
         */
        Result sendBreak(int duration);

        /**
         * Set the baudrate.
         * Takes an int and will attempt to decide what baudrate  is
         * to be used on the UART hardware.
         *
         * @param baud unsigned int of baudrate i.e. 9600
         * @return Result of operation
         */
        Result setBaudRate(unsigned int baud);

        /**
         * Set the transfer mode
         * For example setting the mode to 8N1 would be
         * "dev.setMode(8,UART_PARITY_NONE , 1)"
         *
         * @param bytesize data bits
         * @param parity Parity bit setting
         * @param stopbits stop bits
         * @return Result of operation
         */
        Result setMode(int bytesize, UartParity parity, int stopbits);

        /**
         * Set the flowcontrol
         *
         * @param xonxoff XON/XOFF Software flow control.
         * @param rtscts RTS/CTS out of band hardware flow control
         * @return Result of operation
         */
        Result setFlowcontrol(bool xonxoff, bool rtscts);

        /**
         * Set the timeout for read and write operations
         * <= 0 will disable that timeout
         *
         * @param read read timeout
         * @param write write timeout
         * @param interchar inbetween char timeout
         * @return Result of operation
         */
        Result setTimeout(int read, int write, int interchar);

        /**
         * Set the blocking state for write operations
         *
         * @param nonblock new nonblocking state
         * @return Result of operation
         */
        Result setNonBlocking(bool nonblock);
    };
} // namespace mraa

#endif // UART_H_INCLUDED
