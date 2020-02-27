add_library(
    spartanflightlib

    ./src/data/datapacket.h
    ./src/data/datapacket.cpp
    ./src/sensors/sensor.h
    ./src/sensors/sensor.cpp

    ./src/sensors/ads1115.h
    ./src/sensors/ads1115.cpp
    ./src/sensors/lsm6ds33.h
    ./src/sensors/lsm6ds33.cpp
    ./src/constants.h
    ./src/globals.h
)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    target_include_directories(spartanflightlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src" "/usr/local/include")
else()
    target_include_directories(spartanflightlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
endif()
