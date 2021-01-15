add_library(
    mraamocklib

    ./src/mock/types.h
    ./src/mock/i2c.h
    ./src/mock/i2c.cpp
    ./src/mock/spi.h
    ./src/mock/spi.cpp
    ./src/mock/uart.h
    ./src/mock/uart.cpp
)

add_library(
    spartanflightlib

    ./src/data/mdp.h
    ./src/data/datapacket.h
    ./src/data/datapacket.cpp
    ./src/sensors/sensor.h
    ./src/sensors/sensor.cpp

    ./src/sensors/ads1115.h
    ./src/sensors/ads1115.cpp
    ./src/sensors/lsm6ds33.h
    ./src/sensors/lsm6ds33.cpp
    ./src/sensors/dps422xtsa1.h
    ./src/sensors/dps422xtsa1.cpp
    ./src/globals.h

    ./src/utils/utils.h
    ./src/utils/utils.cpp
)

target_include_directories(spartanflightlib PUBLIC ${mraa_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(spartanflightlib PUBLIC ${mraa_LIBRARIES})
