add_library(
    spartanflightlib

    ./src/data/datapacket.h
    ./src/data/datapacket.cpp
    ./src/sensors/sensor.h

    ./src/sensors/ads1115.h
    ./src/sensors/ads1115.cpp

    ./src/sensors/mtk3339.h
    ./src/sensors/mtk3339.cpp
)

target_include_directories(spartanflightlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")