add_executable(flight_software main.cpp)

find_library(MRAA_LIB mraa)
target_link_libraries(flight_software "${MRAA_LIB}")

target_link_libraries(flight_software PRIVATE spartanflightlib)