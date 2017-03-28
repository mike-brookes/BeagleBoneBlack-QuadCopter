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

#ifndef QUADRO_ORIENTATION_H
#define QUADRO_ORIENTATION_H

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
    * @var DATA_RATE is the speed that data is being refreshed.
    */
    const float DATA_RATE = 0.02;

    /**
     * @var COMPLIMENTARY_FILTER_TUNING is the percentage of the first value used in the filter, it is offset by
     * subtracting it from 1 and using that percentage of the second value used in the filters algorithm.
     */
    const float COMPLIMENTARY_FILTER_TUNING = 0.98;

    /*!
     * @package quadro::orientation
     */
    class orientation {

    public:

        /*!
         * Orientation constructor - This class initiates a thread that activates sensors and constantly updates/reads all values.
         * From within this class I should have access to everything orientation related : e.g Accelerometer, Magnetometer, Gyroscope, Barometer and Sonic Sensor.
         * @params none
         * @throws setupException
         * @TODO Allow selection of filter type : e.g Kalman, Complimentary.
         */
        orientation( );

        /*!
         * This method is used for determining urgency of movements, attempting to give some kind of priority to actions.
         * @return int (a value of cm or inches depending on sensor setting)
         */
        int getEmergencyHeight();

        /*!
         * @param int dataFilter type : 1 = Kalman Filter, 2 = Complimentary Filter.
         */
        void setDataFilterSelection( int );

        /*!
         * @var Converted sensor reading storage as float.
         */
        float roll, pitch, yaw, baroHeight, sonicHeight, height, heading;

        /*!
         * @var contains the currently selected data filter algorithm.
         */
        int dataFilterSelection;

    private:

        enum dataFilter {
            KALMAN = 1,
            COMPLIMENTARY = 2
        };

        /*!
         * setValues is a static method that runs in it's own thread assigning values from all assigned orientation sensors.
         * @params *this - a pointer to this object
         */
        static void* setValues( void* orientationInst );

        /*!
         * @var orientationNotifyer - Thread notifyer
         */
        pthread_t orientationNotifyer;

        /*!
         * @var kalmanPitch - Create a Kalman filter object for pitch
         */
        Kalman kalmanPitch;

        /*!
         * @var kalmanRoll - Create a Kalman filter object for roll
         */
        Kalman kalmanRoll;

        /*!
         * @var sonicSensor - Create a container for the LVMaxSonarEZ object
         */
        LVMaxSonarEZ* sonicSensor;

        /*!
         * @var accelerometer - Create a container for the LSM303Accelerometer object
         */
        LSM303Accelerometer* accelerometer;

        /*!
         * @var magnetometer - Create a container for the LSM303Magnetometer object
         */
        LSM303Magnetometer* magnetometer;

        /*!
         * @var gyroscope - Create a container for the L3GD20H object
         */
        L3GD20H* gyroscope;

        /*!
         * runKalmanCalculations run all the sensor data through the Kalman filter and assign orientation values.
         */
        void runKalmanCalculations();

        /*!
         * runComplimentaryCalculations run all the sensor data through the Complimentary filter and assign orientation values.
         */
        void runComplimentaryCalculations();

    };

}

#endif //QUADRO_ORIENTATION_H
