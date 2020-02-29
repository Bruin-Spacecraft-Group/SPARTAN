

// The Slave ADdress (SAD) associated to the LSM6DS33 is 110101xb. The SDO/SA0 pin
// can be used to modify the less significant bit of the device address. If the SDO/SA0 pin is
// connected to the supply voltage, LSb is ‘1’ (address 1101011b); else if the SDO/SA0 pin is
// connected to ground, the LSb value is ‘0’ (address 1101010b). This solution permits to
// connect and address two different inertial modules to the same I2C bus.

// LSB is 1 (8th bit in address) for read
// LSB is 0 (8th bit in address) for write


enum utils {
    BUFFER_SIZE       = 14
};

enum regAddr
{
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