include_directories(${mraa_INCLUDE_DIRS})

add_executable(lsm6ds33_test lsm6ds33_test.cpp)

find_library(MRAA_LIB mraa)

target_link_libraries(lsm6ds33_test ${mraa_LIBRARIES} spartanflightlib)
