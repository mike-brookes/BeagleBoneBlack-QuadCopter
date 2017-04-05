/*
Copyright (C) 2017 Michael Brookes

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SRC_H_L3GD20H_H_
#define SRC_H_L3GD20H_H_

#include "../../i2cDevice.h"
#include <pthread.h>
#include <unistd.h>
#include <functional>
#include <iostream>
#include <sys/types.h>
#include "../../../Timer/Timer.h"

using namespace std;

//From Table 17. of the L3GD20H Data sheet ( /lib/docs/L3GD20H.pdf )
#define GYRO_ADDRESS    0x6B
#define CTRL1           0x20
#define OUT_X_L         0x28
#define OUT_X_H         0x29
#define OUT_Y_L         0x2A
#define OUT_Y_H         0x2B
#define OUT_Z_L         0x2C
#define OUT_Z_H         0x2D

#define DT              0.02
#define AA              0.97

namespace quadro {

    namespace i2c {

        /**
         * L3GD20H : A class that provides control of the L3GD20H which contains : gyroscope.
         */
        class L3GD20H : public i2cDevice {

        public:

            /*!
             * L3GD20H Constructor, initialises the device - writes default settings to the sensor
             *
             * @see start() to start reading the device and updating X, Y and Z values.
             * @param _deviceAddress
             * @param _busId
             */
            L3GD20H( unsigned char _deviceAddress = GYRO_ADDRESS, int _busId = 1 );

            /**
             * start() - Allows the independent control to start the thread that updates the Accelerometer readings.
             *
             * @param none
             * @throws i2cSetupException
             * @returns int deviceStatus : 1 = on, 0 = off or 2 = error
             */
            int start();

            /**
             * Please refer to the documentation provided for your L3GD20H for further details (CTRL1 pg 36 point 7.2)
             */
            enum _switch {
                ON = 0x7F,        //!< 0x7F 200 Hz Data Rate, Power On and X, Y, Z enabled
                OFF = 0x00        //!< 0x00 Off
            };

            /**
             *Creates the template for vector, used by the gyroscope.
             */
            template<typename T>
            struct vector {
                T x, y, z;
            };

            vector<int> rad; //!< Gyroscope Radian vector (X, Y, Z)
            vector<float> angle; //!< Gyroscope Angle Vector (X, Y, Z)

            pthread_t threadHandle;//!< @var Thread Handle

        protected:

            /**
             * Sets the devices I2C device address - to satisfy the interface
             *
             * @param _deviceAddress
             */
            void setDeviceAddress( unsigned char _deviceAddress ) { this->deviceAddress = _deviceAddress; }

            /**
             * Sets the devices I2C Bus Id - to satisfy the interface
             *
             * @param _busId
             */
            void setBusId( int _busId ) { this->busId = _busId; }

            _switch gyroSwitch; //!< enum value for the Gyroscope power status.

            /**
             * Set the power status on the Gyroscope
             *
             * @param gyroSwitch
             * @return int
             */
            int setPower( _switch gyroSwitch );

            /**
             * Calculate the Gyro X angular rate of change using the equation :
             * X = SensorRawValue * 0.00875 * 0.02
             * sets the angle vector x value.
             */
            void calcX( void );

            /**
             * Calculate the Gyro Y angular rate of change using the equation :
             * Y = SensorRawValue * 0.00875 * 0.02
             * sets the angle vector y value.
             */
            void calcY( void );

            /**
             * Calculate the Gyro Z angular rate of change using the equation :
             * Z = SensorRawValue * 0.00875 * 0.02
             * sets the angle vector z value.
             */
            void calcZ( void );

            /*!
             * runMainSensorUpdateThread starts a continuous thread updating the programs values from the sensors values.
             *
             * @see start() to start this thread running
             * @see stop() to stop this thread running
             * @param static_inst
             * @return 0
             */
            static void* runMainSensorUpdateThread( void* static_inst );

            int threadRet; //!< @var thread return value

        };

    }
}

#endif /* SRC_H_L3GD20H_H_ */
