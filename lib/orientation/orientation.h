/*
Copyright (C) 2016 Michael Brookes

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

#ifndef QUADRO_ORIENTATION_H
#define QUADRO_ORIENTATION_H

#define DATA_RATE       0.02
#define FILTER_TUNING   0.98

#include <cstdio>
#include <pthread.h>
#include "../External/Kalman.h"
#include "../Timer/Timer.h"
#include "../I2C/Devices/L3GD20H/L3GD20H.h"
#include "../I2C/Devices/LSM303/Accelerometer/LSM303Accelerometer.h"
#include "../analog/devices/LVMaxSonarEZ/LVMaxSonarEZ.h"
#include "../I2C/Devices/LSM303/Magnetometer/LSM303Magnetometer.h"

namespace quadro {
    using namespace analog;
    using namespace i2c;

    /**
     * @package quadro
     * Class orientation : this class initiates a thread that updates all current values
     * From within this class I should have access to everything orientation related
     * e.g Accelerometer, Magnetometer, Gyroscope, Barometer and Sonic Sensor.
     */
    class orientation {
    public:

        /**
         * orientation constructor
         * Sets up objects for each orientation sensor and starts the thread.
         * @params none
         */
        orientation();

        /**
         * Create a pointer for the sonicSensor
         */
        LVMaxSonarEZ* sonicSensor;

        /**
         * Create a pointer for the accelerometer
         */
        LSM303Accelerometer* accelerometer;

        /**
         * Create a pointer for the magnetometer
         */
        LSM303Magnetometer* magnetometer;

        /**
         * Create a pointer for the gyroscope
         */
        L3GD20H* gyroscope;

        /**
         * setValues is a static method that runs in it's own thread assigning values from all assigned orientation sensors.
         * @params *this
         */
        static void* setValues( void* orientationInst );

        /**
         * The method is used for determining urgency of movements, attempting to give some kind of priority to avoid crashes.
         * @return int (a value of cm or inches depending on sensor setting)
         */
        int getEmergencyHeight();

        /**
         * Thread notifyer
         */
        pthread_t orientationNotifyer;

        /**
         * Value storage as float.
         */
        float roll, pitch, yaw, baroHeight, sonicHeight, height, heading;

        /**
         * Create a Kalman filter object for pitch
         */
        Kalman kalmanPitch;

        /**
         * Create a Kalman filter object for pitch
         */
        Kalman kalmanRoll;
    };

}

#endif //QUADRO_ORIENTATION_H
