# include_directories(/home/pi/mraa)

set (mraa_INCLUDE_DIRS "/usr/local/include/mraa")

if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set (mraa_LIBRARIES "/usr/local/lib/libmraa.a" "/usr/local/lib/libjson-c.a")
else()
    set (mraa_LIBRARIES "/usr/local/lib/libmraa.so")
endif()

include_directories(${mraa_INCLUDE_DIRS})

add_executable(flight_software main.cpp)

find_library(MRAA_LIB mraa)

target_link_libraries(flight_software ${mraa_LIBRARIES} spartanflightlib)

#target_link_libraries(flight_software PRIVATE spartanflightlib)
