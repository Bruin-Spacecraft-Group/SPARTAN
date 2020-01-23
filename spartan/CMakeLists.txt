add_library(
    spartanflightlib
    ./src/sensors/test.h
    ./src/sensors/test.cpp
)

target_include_directories(spartanflightlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")