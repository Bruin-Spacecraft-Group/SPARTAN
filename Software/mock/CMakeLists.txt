add_library(
    mraamocklib

    i2c.cpp
    spi.cpp
    uart.cpp
)

target_include_directories(
    mraamocklib

    PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)