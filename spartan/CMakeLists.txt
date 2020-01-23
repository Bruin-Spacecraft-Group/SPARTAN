add_library(
    spartanflightlib
    ./src/data/datapacket.h
    ./src/data/datapacket.cpp
    ./src/sensors/test.h
    ./src/sensors/test.cpp
    ./src/sensors/sensor.h
)

target_include_directories(spartanflightlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")