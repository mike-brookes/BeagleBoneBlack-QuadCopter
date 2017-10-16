cmake_minimum_required(VERSION 3.4)

project(Quadro)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -Wall -Wextra -Wno-unused-parameter -Wno-unknown-pragmas -static-libasan -ggdb")

SET(CMAKE_BUILD_TYPE Debug)

#set(CMAKE_SYSROOT /Volumes/xtools/arm-none-linux-gnueabi/arm-none-linux-gnueabi/sysroot/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ~/Documents/Remote-File-Mount/QuadCopter/Debug/)

set(SOURCE_FILES
        quadroCopter.h
        quadroCopter.cpp
        main.cpp
        lib/analog/analogBase.cpp
        lib/analog/analogBase.h
        lib/interfaces/IDevice.h
        lib/i2c/i2cDevice.cpp
        lib/i2c/i2cDevice.h
        lib/Timer/Timer.cpp
        lib/Timer/Timer.h
        lib/i2c/devices/L3GD20H/L3GD20H.cpp
        lib/i2c/devices/L3GD20H/L3GD20H.h
        lib/i2c/devices/LSM303/LSM303DLHC.cpp
        lib/i2c/devices/LSM303/LSM303DLHC.h
        lib/i2c/devices/LSM303/Accelerometer/LSM303Accelerometer.cpp
        lib/i2c/devices/LSM303/Accelerometer/LSM303Accelerometer.h
        lib/i2c/devices/LSM303/Magnetometer/LSM303Magnetometer.cpp
        lib/i2c/devices/LSM303/Magnetometer/LSM303Magnetometer.h
        lib/analog/devices/LVMaxSonarEZ/LVMaxSonarEZ.cpp
        lib/analog/devices/LVMaxSonarEZ/LVMaxSonarEZ.h
        lib/pwm/motors/motors.cpp
        lib/pwm/motors/motors.h
        lib/pwm/motors/dji_2212/dji_2212.cpp
        lib/pwm/motors/dji_2212/dji_2212.h
        lib/overlays/overlayBase.cpp
        lib/overlays/overlayBase.h
        lib/analog/overlays/analogOverlay.cpp
        lib/analog/overlays/analogOverlay.h
        lib/pwm/overlays/pwmOverlay.cpp
        lib/pwm/overlays/pwmOverlay.h
        lib/overlays/pinOverlay.cpp
        lib/overlays/pinOverlay.h
        lib/pwm/pwmDevice.cpp
        lib/pwm/pwmDevice.h
        lib/orientation/orientation.cpp
        lib/orientation/orientation.h
        lib/external/Kalman.h
        lib/external/PID.cpp
        lib/external/PID.h
        lib/analog/exceptions/analogSetupException.h
        lib/exceptions/setupException.h
        lib/i2c/exceptions/i2cSetupException.h
        lib/pwm/exceptions/pwmSetupException.h
        lib/overlays/exceptions/overlaySetupException.h
        lib/analog/exceptions/analogRuntimeException.h
        lib/exceptions/runtimeException.h
        lib/aeronautics/aeronautics.cpp
        lib/aeronautics/aeronautics.h)

add_executable(Quadro ${SOURCE_FILES})