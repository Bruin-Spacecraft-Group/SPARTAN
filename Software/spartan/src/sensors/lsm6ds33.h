
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

        virtual int poll(MasterDataPacket &dp);
        // returns RESULT_FALSE if no new data, RESULT_SUCCESS if member data was updated with latest reading,
        // ERROR in the case of an error
        int hasNewData();
        virtual bool update();

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
