add_library(
    spartanflightlib

    datapacket/datapacket.cpp
    sensors/sensor.cpp

    sensors/ads1115.cpp
    sensors/lsm6ds33.cpp

    utils/utils.cpp
)

target_include_directories(
    spartanflightlib

    PUBLIC
    ${mraa_INCLUDE_DIRS} 
    ${CMAKE_CURRENT_SOURCE_DIR} # covers `globals.h`
    ${CMAKE_SOURCE_DIR} # covers `mock/*`

    datapacket  # covers `mdp.h`, `datapacket.h`
    sensors  # covers `sensor.h`, sensor-specific headers
    utils  # covers `utils.h`

)

# link with either MRAA .so or `mraamocklib` located in `mock` directory (depending on what system we're building on)
target_link_libraries(
    spartanflightlib

    PUBLIC
    ${mraa_LIBRARIES}
)