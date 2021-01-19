cmake_minimum_required(VERSION 3.12)
project(SPARTAN_Flight_Software)

set (CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -Werror)

# TODO: When Apple releases an ARM Macbook, fix this again
if ((${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "x86_64")
    OR (${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "AMD64"))
    set (mraa_INCLUDE_DIRS "")
    set (mraa_LIBRARIES mraamocklib)
else()
    set (mraa_INCLUDE_DIRS "/usr/local/include/mraa")
    set (mraa_LIBRARIES "/usr/local/lib/libmraa.so")
endif()

add_subdirectory(mock)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(main)