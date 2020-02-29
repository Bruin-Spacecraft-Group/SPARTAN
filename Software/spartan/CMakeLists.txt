add_library(
    spartanflightlib

    ./src/mock/types.h
    ./src/mock/i2c.h
    ./src/mock/i2c.cpp
    ./src/mock/spi.h
    ./src/mock/spi.cpp
    ./src/mock/uart.h
    ./src/mock/uart.cpp

    ./src/data/datapacket.h
    ./src/data/datapacket.cpp
    ./src/sensors/sensor.h

    ./src/sensors/ads1115.h
    ./src/sensors/ads1115.cpp
)

target_include_directories(spartanflightlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")