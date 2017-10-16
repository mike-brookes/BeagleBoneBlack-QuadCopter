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

#ifndef LSM303_ACCELEROMETER_LSM303Magnetometer_H
#define LSM303_ACCELEROMETER_LSM303Magnetometer_H

#include "../LSM303DLHC.h"
#include <bitset>
#include <cmath>

using namespace std;

namespace quadro {

    namespace i2c {

        class LSM303Magnetometer : public LSM303DLHC {

        public:

            /*!
             * LSM303Magnetometer Constructor, initialises the device - writes default settings to the sensor
             *
             * @see start() to start reading the device and updating heading values.
             * @param _deviceAddress
             * @param _busId
             */
            explicit LSM303Magnetometer( unsigned char _deviceAddress = MAG_ADDRESS, int _busId = 1 );

            /*!
             * Calculates heading using the following equation :
             *
             * x2 = ( x ) * cos( -1 * atan2( X, sqrt( Y * Y + Z * Z )) ) + ( z ) * sin( -1 * atan2( X, sqrt( Y * Y + Z * Z )) );
             * y2 = ( x ) * sin( atan2( Y, sqrt( X * X + Z * Z )) ) * sin( -1 * atan2( X, sqrt( Y * Y + Z * Z )) ) + ( y ) * cos( atan2( Y, sqrt( X * X + Z * Z )) ) - ( z ) * sin( atan2( Y, sqrt( X * X + Z * Z )) ) * cos( -1 * atan2( X, sqrt( Y * Y + Z * Z )) );
             *
             * return ( atan2( x2, y2 ) * 180 ) / 3.14159265358979323846;
             *
             * @return double Current heading calculation
             */
            double calcHeading();

            /**
             * start() - Allows the independent control to start the thread that updates the Magnetometer readings.
             *
             * @param none
             * @throws i2cSetupException
             * @returns int deviceStatus : 1 = on, 0 = off or 2 = error
             */
            int start();

            double heading; //!< Store current calculated heading value;

            pthread_t threadHandle; //!< @var Thread Handle

        private:

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
#endif //LSM303_ACCELEROMETER_LSM303Magnetometer_H
