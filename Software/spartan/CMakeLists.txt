add_library(
    spartanflightlib

    ./src/data/datapacket.h
    ./src/data/datapacket.cpp
    ./src/sensors/sensor.h

    ./src/sensors/ads1115.h
    ./src/sensors/ads1115.cpp
    ./src/sensors/lsm6ds33.h
    ./src/constants.h
    ./src/globals.h
)

target_include_directories(spartanflightlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")