add_library(
    spartanflightlib

    ./src/data/datapacket.h
    ./src/data/datapacket.cpp
    ./src/sensors/sensor.h

    ./src/sensors/ads1115.h
    ./src/sensors/ads1115.cpp
)

target_include_directories(spartanflightlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")