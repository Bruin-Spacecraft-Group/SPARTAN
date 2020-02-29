// Note: doesn't represent all types from <mraa/types.hpp>, only selected

namespace mraa 
{
    /**
     * MRAA return codes
     */
    typedef enum {
        SUCCESS = 0,                             /**< Expected response */
        ERROR_FEATURE_NOT_IMPLEMENTED = 1,       /**< Feature TODO */
        ERROR_FEATURE_NOT_SUPPORTED = 2,         /**< Feature not supported by HW */
        ERROR_INVALID_VERBOSITY_LEVEL = 3,       /**< Verbosity level wrong */
        ERROR_INVALID_PARAMETER = 4,             /**< Parameter invalid */
        ERROR_INVALID_HANDLE = 5,                /**< Handle invalid */
        ERROR_NO_RESOURCES = 6,                  /**< No resource of that type avail */
        ERROR_INVALID_RESOURCE = 7,              /**< Resource invalid */
        ERROR_INVALID_QUEUE_TYPE = 8,            /**< Queue type incorrect */
        ERROR_NO_DATA_AVAILABLE = 9,             /**< No data available */
        ERROR_INVALID_PLATFORM = 10,             /**< Platform not recognised */
        ERROR_PLATFORM_NOT_INITIALISED = 11,     /**< Board information not initialised */
        ERROR_UART_OW_SHORTED = 12,              /**< UART OW Short Circuit Detected*/
        ERROR_UART_OW_NO_DEVICES = 13,           /**< UART OW No devices detected */
        ERROR_UART_OW_DATA_ERROR = 14,           /**< UART OW Data/Bus error detected */

        ERROR_UNSPECIFIED = 99 /**< Unknown Error */
    } Result;

    /**
     * Enum representing different i2c speeds/modes
     */
    typedef enum {
        I2C_STD = 0,  /**< up to 100Khz */
        I2C_FAST = 1, /**< up to 400Khz */
        I2C_HIGH = 2  /**< up to 3.4Mhz */
    } I2cMode;

    /**
     * MRAA SPI Modes
     */
    typedef enum {
        SPI_MODE0 = 0, /**< CPOL = 0, CPHA = 0, Clock idle low, data is clocked in on rising edge,
                        output data (change) on falling edge */
        SPI_MODE1 = 1, /**< CPOL = 0, CPHA = 1, Clock idle low, data is clocked in on falling edge,
                        output data (change) on rising edge */
        SPI_MODE2 = 2, /**< CPOL = 1, CPHA = 0, Clock idle low, data is clocked in on falling edge,
                        output data (change) on rising edge */
        SPI_MODE3 = 3, /**< CPOL = 1, CPHA = 1, Clock idle low, data is clocked in on rising, edge
                        output data (change) on falling edge */
    } Spi_Mode;

    /**
     * Enum representing different uart parity states
     */
    typedef enum {
        UART_PARITY_NONE = 0,
        UART_PARITY_EVEN = 1,
        UART_PARITY_ODD = 2,
        UART_PARITY_MARK = 3,
        UART_PARITY_SPACE = 4
    } UartParity;
} // namespace mraa
