#ifndef UART_GPS_H_INCLUDED
#define UART_GPS_H_INCLUDED

#include "uart.h"

namespace mraa {
    // Fake GPS over UART. See uart.h for method descriptions.
    class UartGps {
    public:
        UartGps();
        virtual ~UartGps();

        virtual std::string getDevicePath();

        virtual int read(char* data, int length);
        virtual int write(const char* data, int length);

        virtual std::string readStr(int length);
        virtual int writeStr(std::string data);

        virtual bool dataAvailable(unsigned int millis = 0);
    };
} // namespace mraa

#endif // UART_GPS_H_INCLUDED
