#include "lsm6ds33.h"

// Constructors
LSM6DS33(int busID, int lsm6ID, lsm6Settings settings)
    : Sensor(busID, lsm6ID), m_settings(settings) { // raw=true, disable pinmapper for board
    if (lsm6ID)
        lsm6Address = HIGH_ADDRESS;
    else
        lsm6Address = LOW_ADDRESS;
    setMultipliers();
}

LSM6DS33(int busID, int lsm6ID): Sensor(busID, lsm6ID) {
    if (lsm6ID)
        lsm6Address = HIGH_ADDRESS;
    else
        lsm6Address = LOW_ADDRESS;
    setMultipliers();
}

// Write functions

bool spartan::LSM6DS33::writeReg(uint8_t* buffer, unsigned short size) {
    mraa::Result msg = m_i2c.write(buffer, size);

    // Error handling
    if (msg == mraa::SUCCESS)
        return true;
    else if (msg == mraa::ERROR_INVALID_PARAMETER)
        std::cerr << "Invalid parameter." << std::endl;
    else if (msg == mraa::ERROR_INVALID_HANDLE)
        std::cerr << "ERROR_INVALID_HANDLE" << std::endl;
    else if (msg == mraa::ERROR_NO_RESOURCES)
        std::cerr << "ERROR_NO_RESOURCES" << std::endl;
    else if (msg == mraa::ERROR_INVALID_RESOURCE)
        std::cerr << "ERROR_INVALID_RESOURCE" << std::endl;
    else if (msg == mraa::ERROR_INVALID_QUEUE_TYPE)
        std::cerr << "ERROR_INVALID_QUEUE_TYPE" << std::endl;
    else if (msg == mraa::ERROR_NO_DATA_AVAILABLE)
        std::cerr << "ERROR_NO_DATA_AVAILABLE" << std::endl;
    else if (msg == mraa::ERROR_INVALID_PLATFORM)
        std::cerr << "ERROR_INVALID_PLATFORM" << std::endl;
    else if (msg == mraa::ERROR_PLATFORM_NOT_INITIALISED)
        std::cerr << "ERROR_PLATFORM_NOT_INITIALISED" << std::endl;
    else if (msg == mraa::ERROR_UNSPECIFIED)
        std::cerr << "ERROR_UNSPECIFIED" << std::endl;

    return false;
}

// Device settings

void spartan::LSM6DS33::setMultipliers() {
    switch (m_settings.accelRange) {
        case _2g: _accel_multiplier = accel_multiplier[0]; break;
        case _4g: _accel_multiplier = accel_multiplier[1]; break;
        case _8g: _accel_multiplier = accel_multiplier[2]; break;
        case _16g: _accel_multiplier = accel_multiplier[3]; break;
    }

    switch (m_settings.gyroRange) {
        case _125dps: _gyro_multiplier = gyro_multiplier[0]; break;
        case _250dps: _gyro_multiplier = gyro_multiplier[1]; break;
        case _500dps: _gyro_multiplier = gyro_multiplier[2]; break;
        case _1000dps: _gyro_multiplier = gyro_multiplier[3]; break;
        case _2000dps: _gyro_multiplier = gyro_multiplier[3]; break;
    }
}

bool spartan::LSM6DS33::updateSettings() {
    // Update multiplier constant
    setMultipliers();

    // Accelerometer settings
    m_buffer[0] = CTRL1_XL;
    m_buffer[1] = (m_settings.accel_odr << 4) | m_settings.accelRange | m_settings.accelAAFreq;

    if (!writeReg(m_buffer, 2))
        return false;

    m_buffer[0] = CTRL2_G;
    m_buffer[1] = (m_settings.gyro_odr << 4) | m_settings.gyroRange;

    if (!writeReg(m_buffer, 2))
        return false;
    return true;
}

bool spartan::LSM6DS33::updateSettings(lsm6Settings settings) {
    m_settings = settings;
    return updateSettings();
}

// Power functions

int spartan::LSM6DS33::powerOn() {
    if (m_status == STATUS_IDLE)
        return RESULT_SUCCESS;

    // set I2C address
    if (m_i2c.address(lsm6Address) != mraa::SUCCESS) {
        std::cerr << "Unable to set I2C address." << std::endl;
        return ERROR_ADDR;
    }

    // Update settings for accelerometer and gyroscope
    if (!updateSettings()) {
        std::cerr << "Update setting failed" << std::endl;
        return ERROR_ADDR;
    }

    // CTRL3_C has default 1 on IF_INC page 49 in datasheet
    m_buffer[0] = CTRL3_C;
    m_buffer[1] = 0x04;
    if (!writeReg(m_buffer, 2)) {
        std::cerr << "Unable to write GYRO_POWER_ON to LSM6DS33." << std::endl;
        return ERROR_POWER;
    }

    //run first update of sensor
    if (poll() == false) {
        std::cerr << "Unable to initial poll LSM6DS33." << std::endl;
        return ERROR_POLL;
    }

    m_status = STATUS_IDLE;
    return RESULT_SUCCESS;
}

int spartan::LSM6DS33::powerOff() {
    if (m_status == STATUS_OFF)
        return RESULT_SUCCESS;

    //set I2C address
    if (m_i2c.address(lsm6Address) != mraa::SUCCESS) {
        std::cerr << "Unable to set I2C address." << std::endl;
        return ERROR_ADDR;
    }

    //send "Power Off" command for accelerometer
    m_buffer[0] = CTRL1_XL;
    m_buffer[1] = POWER_OFF;

    if (!writeReg(m_buffer, 2)) {
        std::cerr << "Unable to write POWER_OFF to LSM6DS33's Accelerometer." << std::endl;
        return ERROR_POWER;
    }

    //send "Power Off" command for gyroscope
    m_buffer[0] = CTRL2_G;
    m_buffer[1] = POWER_OFF;

    if (!writeReg(m_buffer, 2)) {
        std::cerr << "Unable to write POWER_OFF to LSM6DS33's Gyroscope." << std::endl;
        return ERROR_POWER;
    }

    m_status = STATUS_OFF;
    return RESULT_SUCCESS;
}

bool spartan::LSM6DS33::poll() {
    if (m_status == STATUS_OFF)
        return ERROR_INVALID_STATUS;

    if (hasNewData() == RESULT_FALSE)
        //std::cerr << "No new data" << std::endl;
        return false;

    // set I2C address
    if (m_i2c.address(lsm6Address) != mraa::SUCCESS) {
        std::cerr << "Unable to set I2C address." << std::endl;
        return false;
    }

    // read temp,x,y,z (14 bytes) into buffer
    if (m_i2c.readBytesReg(OUT_TEMP_L, m_buffer, BUFFER_SIZE) == -1) {
        std::cerr << "Unable to read data bytes starting from LSM6DS33_OUT_TEMP_L." << std::endl;
        return false;
    }

    //record rawacceleration values using data reads for x,y,z respectively
    //DATAx0 is the least significant byte, and DATAx1 is the most significant byte
    //conversion of raw sensor data into relevant values based on constant offset values
    m_temp = ((m_buffer[1] << 8) | m_buffer[0]);

    m_gyro.x = ((m_buffer[3] << 8) | m_buffer[2]);
    m_gyro.y = ((m_buffer[5] << 8) | m_buffer[4]);
    m_gyro.z = ((m_buffer[7] << 8) | m_buffer[6]);

    m_accel.x = ((m_buffer[9] << 8) | m_buffer[8]);
    m_accel.y = ((m_buffer[11] << 8) | m_buffer[10]);
    m_accel.z = ((m_buffer[13] << 8) | m_buffer[12]);

    return true;
}

int spartan::LSM6DS33::hasNewData() {
    // NOTE: STATUS_REG on lSM6DS33 used to check if data is available for temp/gyro/accel
    if (m_status == STATUS_OFF)
        return RESULT_FALSE;

    // set I2C address
    if (m_i2c.address(lsm6Address) != mraa::SUCCESS) {
        std::cerr << "Unable to set I2C address." << std::endl;
        return ERROR_ADDR;
    }
    if (m_i2c.readBytesReg(STATUS_REG,m_buffer,1) == -1)
        return ERROR_READ;

    uint8_t temp = 0;

    if ((m_buffer[0] & 0x7) > temp) {
        return RESULT_SUCCESS;
    } else {
        std::cout << "Status Read " << m_buffer[0] << std::endl;
        return RESULT_FALSE;
    }
}

void spartan::LSM6DS33::printSensorInfo() {
    std::cout << "======================================" << std::endl;
    std::cout << "Type: LSM6DS33" << std::endl;
    std::cout << "Number: " << getInstance() << std::endl;
    std::cout << "Status:     " << getStatus() << std::endl;
    std::cout << "I2C BusID: " << getBusID() << std::endl;
    std::cout << "======================================" << std::endl;
}

void spartan::LSM6DS33::printRawValues() {
    std::cout << "======================================" << std::endl;
    std::cout << "Temp: " << std::setw(6) << m_temp << std::endl;
    std::cout << "AccelX: " <<  std::setw(6) << m_accel.x << std::endl;
    std::cout << "AccelY: " <<  std::setw(6) << m_accel.y << std::endl;
    std::cout << "AccelZ: " <<  std::setw(6) << m_accel.z << std::endl;
    std::cout << "GyroX: " <<  std::setw(6) << m_gyro.x << std::endl;
    std::cout << "GyroY: " <<  std::setw(6) << m_gyro.y << std::endl;
    std::cout << "GyroZ: " <<  std::setw(6) << m_gyro.z << std::endl;
    std::cout << "======================================" << std::endl;
}

bool spartan::LSM6DS33::pollData(DataPacket * & dp) {
    if (!poll())
        return false;
    // Initalize an data array
    float * arr = new float[7];
    arr[0] = (float) ((m_temp / 16) + m_offsets._temp_offset);
    arr[1] = (float) ((m_accel.x*_accel_multiplier) + m_offsets._accel_offsets.x);
    arr[2] = (float) ((m_accel.y*_accel_multiplier) + m_offsets._accel_offsets.y);
    arr[3] = (float) ((m_accel.z*_accel_multiplier) + m_offsets._accel_offsets.z);
    arr[4] = (float) ((m_gyro.x*_gyro_multiplier) + m_offsets._gyro_offsets.x);
    arr[5] = (float) ((m_gyro.y*_gyro_multiplier) + m_offsets._gyro_offsets.y);
    arr[6] = (float) ((m_gyro.z*_gyro_multiplier) + m_offsets._gyro_offsets.z);

    dp = new IMUDataPacket(getTime(), arr);
    return true;
}

int spartan::LSM6DS33::printValues() const {
    std::cout << "======================================" << std::endl;
    std::cout << "Temp: " << ((m_temp / 16) + m_offsets._temp_offset) << "degrees celcius" << std::endl;
    std::cout << "AccelX: " << (float) ((m_accel.x*_accel_multiplier) + m_offsets._accel_offsets.x) << std::endl;
    std::cout << "AccelY: " << (float) ((m_accel.y*_accel_multiplier) + m_offsets._accel_offsets.y) << std::endl;
    std::cout << "AccelZ: " << (float) ((m_accel.z*_accel_multiplier) + m_offsets._accel_offsets.z) << std::endl;
    std::cout << "GyroX: " << (float) ((m_gyro.x*_gyro_multiplier) + m_offsets._gyro_offsets.x) << std::endl;
    std::cout << "GyroY: " << (float) ((m_gyro.y*_gyro_multiplier) + m_offsets._gyro_offsets.y) << std::endl;
    std::cout << "GyroZ: " << (float) ((m_gyro.z*_gyro_multiplier) + m_offsets._gyro_offsets.z)<< std::endl;
    std::cout << "======================================" << std::endl;
    return 9; // # of lines
}

const char *spartan::LSM6DS33::name() const {
    const char * str = "LSM6DS33";
    return str;
}
