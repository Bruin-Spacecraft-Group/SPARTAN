# include_directories(/home/pi/mraa)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set (mraa_INCLUDE_DIRS "/usr/local/include/mraa")
    set (mraa_LIBRARIES "/usr/local/lib/libmraa.a" "/usr/local/lib/libjson-c.a")
else()
    set (mraa_INCLUDE_DIRS "/home/pi/mraa/build/src")
    set (mraa_LIBRARIES "/home/pi/mraa/build/src/libmraa.so")
endif()

include_directories(${mraa_INCLUDE_DIRS})

add_executable(flight_software main.cpp)

find_library(MRAA_LIB mraa)

target_link_libraries(flight_software ${mraa_LIBRARIES} spartanflightlib)

#target_link_libraries(flight_software PRIVATE spartanflightlib)
