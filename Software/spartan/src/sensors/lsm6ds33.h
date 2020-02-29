#ifndef LSM6DS33_H
#define LSM6DS33_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <chrono>

#ifdef __linux__
#include <mraa/i2c.hpp>
#else
#include <mock/i2c.h>
#endif

#include <sensors/sensor.h>
#include <globals.h>
#include <constants.h>

// Data sheet and other info about sensor can be referenced here: https://www.st.com/resource/en/datasheet/lsm6ds33.pdf

namespace spartan {
    // Available settings

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
            AccelRange accelRange = _4g;
            AccelAAFreq accelAAFreq = _400hz;
            GyroRange gyroRange = _500dps;
            ODR accel_odr = odr_1660Hz;
            ODR gyro_odr = odr_1660Hz;
        } m_settings;

        offsets m_offsets = {0, {.x=0, .y=0, .z=0}, {.x=0, .y=0, .z=0}};

        uint8_t lsm6Address;

        LSM6DS33(	int busID, 
                    int lsm6ID,		//  Either 0 or 1 (can only connect 2 lsm6ds33 modules)
                    lsm6Settings settings
                );
        LSM6DS33(	int busID, 
                    int lsm6ID		//  Either 0 or 1 (can only connect 2 lsm6ds33 modules)
                );

        virtual int powerOn();
        virtual int powerOff();

        // returns RESULT_FALSE if no new data, RESULT_SUCCESS if member data was updated with latest reading,
        // ERROR in the case of an error
        virtual bool poll();
        int hasNewData();

        bool writeReg(uint8_t* buffer, unsigned short size);

        void setMultipliers();
        bool updateSettings();
        bool updateSettings(lsm6Settings settings);

        //virtual bool longPoll() { return false; /*dummy*/}
        // call poll() over a longer period of time, averaging out the values (maybe allow time input functionality, or
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

        virtual bool pollData(MasterDataPacket &dp);
        virtual int printValues() const;
        virtual const char * name() const;

    private:
        short m_temp;
        vector<short> m_accel;
        // using short because 16-byte data output. c++ translate the raw binary output according to two's complement. 
        vector<short> m_gyro;
        uint8_t m_buffer[BUFFER_SIZE];
        mraa::I2c m_i2c;
    };
} // namespace spartan

#endif // LSM6DS33_H
