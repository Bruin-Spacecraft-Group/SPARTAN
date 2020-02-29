# include_directories(/home/pi/mraa)

include_directories(${mraa_INCLUDE_DIRS})

add_executable(flight_software main.cpp)

find_library(MRAA_LIB mraa)

target_link_libraries(flight_software ${mraa_LIBRARIES} spartanflightlib)

#target_link_libraries(flight_software PRIVATE spartanflightlib)
