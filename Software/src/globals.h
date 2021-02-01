#ifndef GLOBALS_H
#define GLOBALS_H

// I2C bus ID
#define I2C_BUS 0;

//pin mapping to MRAA numbers for Raspberry Pi Model 2 and B+ (https://iotdk.intel.com/docs/master/mraa/rasppi.html)
//shows abstraction level outright; makes apparent that MRAA abstraction is being used (not some magic numbers)
#define MRAA_1 1  //P1-01, 3V3 VCC
#define MRAA_2 2  //P1-02, 5V VCC
#define MRAA_3 3  //P1-03, 12C SDA
#define MRAA_4 4  //P1-04, 5V VCC
#define MRAA_5 5  //P1-05, 12C SCL
#define MRAA_6 6  //P1-06, GND
#define MRAA_7 7  //P1-07, GPIO(4)
#define MRAA_8 8  //P1-08, UART TX
#define MRAA_9 9  //P1-09, GND
#define MRAA_10 10  //P1-10, UART RX
#define MRAA_11 11  //P1-11, GPIO(17)
#define MRAA_12 12  //P1-12, GPIO(18)
#define MRAA_13 13  //P1-13, GPIO(27)
#define MRAA_14 14  //P1-14, GND
#define MRAA_15 15  //P1-15, GPIO(22)
#define MRAA_16 16  //P1-16, GPIO(23)
#define MRAA_17 17  //P1-17, 3V3 VCC
#define MRAA_18 18  //P1-18, GPIO(24)
#define MRAA_19 19  //P1-19, SPI MOSI
#define MRAA_20 20  //P1-20, GND
#define MRAA_21 21  //P1-21, SPI MISO
#define MRAA_22 22  //P1-22, GPIO(25)
#define MRAA_23 23  //P1-23, SPI SCL
#define MRAA_24 24  //P1-24, SPI CS0
#define MRAA_25 25  //P1-25, GND
#define MRAA_26 26  //P1-26, SPI CS1
#define MRAA_27 27  //P1-27, I2C SDA1
#define MRAA_28 28  //P1-28, I2C SCL1
#define MRAA_29 29  //P1-29, GPIO(5)
#define MRAA_30 30  //P1-30, GND
#define MRAA_31 31  //P1-31, GPIO(6)
#define MRAA_32 32  //P1-32, GPIO(12)
#define MRAA_33 33  //P1-33, GPIO(13)
#define MRAA_34 34  //P1-34, GND
#define MRAA_35 35  //P1-35, SPI MISO1
#define MRAA_36 36  //P1-36, GPIO(16)
#define MRAA_37 37  //P1-37, GPIO(26)
#define MRAA_38 38  //P1-38, SPI MOSI1
#define MRAA_39 39  //P1-39, GND
#define MRAA_40 40  //P1-40, SPI SCL1

namespace spartan {
    // arbritary mapping for function implementations in sensors.h and more
    enum sensor_type {
        ACCEL,
        GYRO,
        TEMP,
        BARO,
        CURRENT,
        MAG
    };

    enum flight_state {
        // status constants (as currently used in systems.h)
        DISCONNECTED,
        // maybe this as a general status for being mission ready before launch? (this would be right after turn-on)
        IDLE,
        READY_TO_RECIEVE,
        READY_TO_SEND
    };

    // return codes (success and error types)
    enum result_type {
        RESULT_SUCCESS,
        RESULT_FALSE,
        ERROR_ADDR,
        ERROR_POWER,
        ERROR_DATAFORMAT,
        ERROR_READ,
        ERROR_POLL,
        ERROR_INVALID_STATUS,
        ERROR_WRITE,
        ERROR_UPDATE_SETTING
    };

    // sensor status types
    enum sensor_status_type {
        STATUS_IDLE,
        STATUS_OFF,
        STATUS_ERROR
    };
}

#endif
