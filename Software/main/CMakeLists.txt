# include_directories(/home/pi/mraa)

add_executable(spartan main.cpp)

# find_library(MRAA_LIB mraa)
# target_include_directories(spartan PUBLIC ${mraa_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/src")
# target_link_libraries(spartan PUBLIC ${mraa_LIBRARIES} spartanflightlib)

target_link_libraries(spartan PUBLIC spartanflightlib)
