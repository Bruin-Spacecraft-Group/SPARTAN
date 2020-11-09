# include_directories(/home/pi/mraa)

add_executable(flight_software main.cpp)

# find_library(MRAA_LIB mraa)
# target_include_directories(flight_software PUBLIC ${mraa_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/src")
# target_link_libraries(flight_software PUBLIC ${mraa_LIBRARIES} spartanflightlib)

target_link_libraries(flight_software PUBLIC spartanflightlib)
