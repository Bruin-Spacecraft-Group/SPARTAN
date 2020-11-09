# include_directories(${mraa_INCLUDE_DIRS})

add_executable(lsm6ds33_test lsm6ds33_test.cpp)

# find_library(MRAA_LIB mraa)
# target_include_directories(lsm6ds33_test PUBLIC ${mraa_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/src")
# target_link_libraries(lsm6ds33_test PUBLIC ${mraa_LIBRARIES} spartanflightlib)

target_link_libraries(lsm6ds33_test PUBLIC spartanflightlib)
