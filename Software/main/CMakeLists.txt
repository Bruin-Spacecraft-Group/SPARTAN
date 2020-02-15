# include_directories(/home/pi/mraa)
set (mraa_INCLUDE_DIRS "/home/pi/mraa/build/src")
set (mraa_LIBRARIES "/home/pi/mraa/build/src/libmraa.so")
include_directories(${mraa_INCLUDE_DIRS})

add_executable(flight_software main.cpp)

find_library(MRAA_LIB mraa)

target_link_libraries(flight_software ${mraa_LIBRARIES} spartanflightlib)

#target_link_libraries(flight_software PRIVATE spartanflightlib)
