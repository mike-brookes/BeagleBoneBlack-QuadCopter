cmake_minimum_required(VERSION 3.3)
project(Quadro)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g")

set(CMAKE_SYSROOT /Volumes/xtools/arm-none-linux-gnueabi/arm-none-linux-gnueabi/sysroot/)

set(CMAKE_CXX_COMPILER /Volumes/xtools/arm-none-linux-gnueabi/bin/arm-none-linux-gnueabi-g++)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(CMAKE_SYSROOT /Volumes/xtools/arm-none-linux-gnueabi/arm-none-linux-gnueabi/sysroot/)

file(GLOB SOURCES "*.cpp")

add_executable(Quadro
        ${SOURCES}
        ${PROJECT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/BBBAnalogDevice.cpp.o
        ${PROJECT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/BBBI2CDevice.cpp.o
        ${PROJECT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/BBBL3GD20H.cpp.o
        ${PROJECT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/BBBLSM303DLHC.cpp.o
        ${PROJECT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/BBBPWMDevice.cpp.o
        )