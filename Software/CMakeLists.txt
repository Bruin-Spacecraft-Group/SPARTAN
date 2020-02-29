cmake_minimum_required(VERSION 3.12)
project(SPARTAN_Flight_Software)

set (CMAKE_CXX_STANDARD 17)

set (mraa_INCLUDE_DIRS "/usr/local/include/mraa")
if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set (mraa_LIBRARIES "/usr/local/lib/libmraa.a" "/usr/local/lib/libjson-c.a")
else()
    set (mraa_LIBRARIES "/usr/local/lib/libmraa.so")
endif()

add_subdirectory(spartan)
add_subdirectory(tests)
add_subdirectory(main)
