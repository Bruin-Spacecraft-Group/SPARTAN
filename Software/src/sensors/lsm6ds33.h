#ifndef LSM6DS33_H
#define LSM6DS33_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <chrono>

// TODO: When Apple releases an ARM Macbook, fix this again
#if !defined(__x86_64__) && !defined(_WIN32)
#include <mraa/i2c.hpp>
#else
#include <mock/i2c.h>
#endif

#include "datapacket.h"
#include <sensors/sensor.h>
#include <globals.h>

// Data sheet and other info about sensor can be referenced here: https://www.st.com/resource/en/datasheet/lsm6ds33.pdf

namespace spartan {
    class EncodedPacket;

    // Available settings
    namespace lsm6ds33 {
        enum AccelRange {
            _2g=0b0000,
            _4g=0b1000,
            _8g=0b1100,
            _16g=0b0100
        }; 	// (00: ±2 g; 01: ±16 g; 10: ±4 g; 11: ±8 g)

        enum AccelAAFreq {
            _400hz=0b00,
            _200hz=0b01,
            _100hz=0b10,
            _50hz=0b11
        };	// (00: 400 Hz; 01: 200 Hz; 10: 100 Hz; 11: 50 Hz)

        enum GyroRange {
            _125dps=0b0010,
            _250dps=0b0000,
            _500dps=0b0100,
            _1000dps=0b1000,
            _2000dps=0b1100
        };
        // first two digits(00: 250 dps; 01: 500 dps; 10: 1000 dps; 11: 2000 dps)
        // third: 125 dps. Default value: 0 (0: disabled; 1: enabled) fourth: 0

        enum ODR {
            odr_12hz=0b0001,
            odr_26Hz=0b0010,
            odr_52Hz=0b0011,
            odr_104Hz=0b0100,
            odr_208Hz=0b0101,
            odr_416Hz=0b0110,
            odr_833Hz=0b0111,
            odr_1660Hz=0b1000, // Gyro ODR only up to 1660, Accel has the following two
            odr_3330Hz=0b1001,
            odr_6660Hz=0b1010
        };

        enum utils {
            BUFFER_SIZE       = 14
        };

        enum regAddr {
            POWER_OFF         = 0x00,
            HIGH_ADDRESS      = 0x6B,
            LOW_ADDRESS       = 0x6A,
            FUNC_CFG_ACCESS   = 0x01,

            FIFO_CTRL1        = 0x06,
            FIFO_CTRL2        = 0x07,
            FIFO_CTRL3        = 0x08,
            FIFO_CTRL4        = 0x09,
            FIFO_CTRL5        = 0x0A,
            ORIENT_CFG_G      = 0x0B,

            INT1_CTRL         = 0x0D,
            INT2_CTRL         = 0x0E,
            WHO_AM_I          = 0x0F,
            CTRL1_XL          = 0x10,
            CTRL2_G           = 0x11,
            CTRL3_C           = 0x12,
            CTRL4_C           = 0x13,
            CTRL5_C           = 0x14,
            CTRL6_C           = 0x15,
            CTRL7_G           = 0x16,
            CTRL8_XL          = 0x17,
            CTRL9_XL          = 0x18,
            CTRL10_C          = 0x19,

            WAKE_UP_SRC       = 0x1B,
            TAP_SRC           = 0x1C,
            D6D_SRC           = 0x1D,
            STATUS_REG        = 0x1E,

            OUT_TEMP_L        = 0x20,
            OUT_TEMP_H        = 0x21,
            OUTX_L_G          = 0x22,
            OUTX_H_G          = 0x23,
            OUTY_L_G          = 0x24,
            OUTY_H_G          = 0x25,
            OUTZ_L_G          = 0x26,
            OUTZ_H_G          = 0x27,
            OUTX_L_XL         = 0x28,
            OUTX_H_XL         = 0x29,
            OUTY_L_XL         = 0x2A,
            OUTY_H_XL         = 0x2B,
            OUTZ_L_XL         = 0x2C,
            OUTZ_H_XL         = 0x2D,

            FIFO_STATUS1      = 0x3A,
            FIFO_STATUS2      = 0x3B,
            FIFO_STATUS3      = 0x3C,
            FIFO_STATUS4      = 0x3D,
            FIFO_DATA_OUT_L   = 0x3E,
            FIFO_DATA_OUT_H   = 0x3F,
            TIMESTAMP0_REG    = 0x40,
            TIMESTAMP1_REG    = 0x41,
            TIMESTAMP2_REG    = 0x42,

            STEP_TIMESTAMP_L  = 0x49,
            STEP_TIMESTAMP_H  = 0x4A,
            STEP_COUNTER_L    = 0x4B,
            STEP_COUNTER_H    = 0x4C,

            FUNC_SRC          = 0x53,

            TAP_CFG           = 0x58,
            TAP_THS_6D        = 0x59,
            INT_DUR2          = 0x5A,
            WAKE_UP_THS       = 0x5B,
            WAKE_UP_DUR       = 0x5C,
            FREE_FALL         = 0x5D,
            MD1_CFG           = 0x5E,
            MD2_CFG           = 0x5F,
        };
    } // namespace lsm6ds33

    class LSM6DS33 : public Sensor {
    public:
        // vector template 
        template<typename T> struct vector {
            T x, y, z;
        };

        struct offsets {
            float _temp_offset = 0;
            vector<float> _accel_offsets; // 1, 2, 3 are offsets that are added to the value, 4 is a scale factor applied.
            vector<float> _gyro_offsets;  // Same as above
        };
        
        // IMU settings
        // Change defaults here
        struct lsm6Settings {
            lsm6ds33::AccelRange accelRange = lsm6ds33::_4g;
            lsm6ds33::AccelAAFreq accelAAFreq = lsm6ds33::_400hz;
            lsm6ds33::GyroRange gyroRange = lsm6ds33::_500dps;
            lsm6ds33::ODR accel_odr = lsm6ds33::odr_1660Hz;
            lsm6ds33::ODR gyro_odr = lsm6ds33::odr_1660Hz;
        } m_settings;

        offsets m_offsets = {0, {.x=0, .y=0, .z=0}, {.x=0, .y=0, .z=0}};

        uint8_t lsm6Address;

        // Note: busID can be either 0 or 1 (can only connect 2 lsm6ds33 modules)
        LSM6DS33(int busID, int lsm6ID, lsm6Settings settings);
        LSM6DS33(int busID, int lsm6ID);

        virtual int powerOn();
        virtual int powerOff();

        int pollData(std::vector<EncodedPacket> &packets) override;
        // returns RESULT_FALSE if no new data, RESULT_SUCCESS if member data was updated with latest reading,
        // ERROR in the case of an error
        int hasNewData();
        bool update();

        bool writeReg(uint8_t* buffer, unsigned short size);

        void setMultipliers();
        bool updateSettings();
        bool updateSettings(lsm6Settings settings);

        //virtual bool longPoll() { return false; /*dummy*/}
        // call pollData() over a longer period of time, averaging out the values (maybe allow time input functionality, or
        // just do poll 10 times and average out the values, storing result into rawAccel array)
        // "poll","read","get"; reads raw data from sensor and returns it; maybe into a file? or an input stream? or a
        // member variable of the class/struct? and then preprocess function can pull from that?
        // rawData type is a placeholder for now; will return raw sensor data

        virtual void printSensorInfo();
        void printRawValues();

        const float accel_multiplier[4] = {0.061, 0.122, 0.244, 0.488};
        float _accel_multiplier;
        const float gyro_multiplier[5] = {4.375, 8.75, 17.5, 35, 70};
        float _gyro_multiplier;

        virtual int printValues() const;
        virtual const char * name() const;

    private:
        short m_temp;
        vector<short> m_accel;
        // using short because 16-byte data output. c++ translate the raw binary output according to two's complement. 
        vector<short> m_gyro;
        uint8_t m_buffer[lsm6ds33::BUFFER_SIZE];
        mraa::I2c m_i2c;
    };
} // namespace spartan

#endif // LSM6DS33_H
