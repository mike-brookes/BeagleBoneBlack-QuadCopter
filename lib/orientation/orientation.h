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

#define STORE_DATA 1;

#include <cstdio>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include "../external/Kalman.h"
#include "../Timer/Timer.h"
#include "../i2c/devices/L3GD20H/L3GD20H.h"
#include "../i2c/devices/LSM303/Accelerometer/LSM303Accelerometer.h"
#include "../analog/devices/LVMaxSonarEZ/LVMaxSonarEZ.h"
#include "../i2c/devices/LSM303/Magnetometer/LSM303Magnetometer.h"
#include "../external/PID.h"

namespace quadro {
    using namespace analog;
    using namespace i2c;

    /**
     * @package quadro::orientation
     */
    class orientation {

    public:

        /**
        * DATA_RATE is the speed that data is being refreshed.
        */
        const float DATA_RATE = 0.01;

        /**
         * Store the location for accelerometer data log file
         */
        string const dataStorageFileName = "/root/robotics/QuadCopter/Data/accelData.dat";

        /**
         * COMPLIMENTARY_FILTER_TUNING is the percentage of the first value used in the filter, it is offset by
         * subtracting it from 1 and using the remainder percentage in the filters algorithm.
         */
        const float COMPLIMENTARY_FILTER_TUNING = 0.98;

        /**
         * Orientation constructor - This class initiates a thread that activates sensors and constantly updates/reads all values.
         * From within this class I should have access to everything orientation related : e.g Accelerometer, Magnetometer, Gyroscope, Barometer and Sonic Sensor.
         *
         * @params none
         * @throws setupException
         */
        orientation();

        /**
         * Destructor : Kills all threads.
         */
        ~orientation() noexcept;

        /**
         * Select a Data Filter from the selection found in dataFilter
         *
         * @param int dataFilter type : 1 = Kalman Filter, 2 = Complimentary Filter.
         */
        void setDataFilterSelection( int );

        float roll; //!< Filtered roll value stored as a float
        float pitch; //!< Filtered pitch value stored as a float
        float yaw; //!< Filtered yaw value stored as a float
        float baroHeight; //!< Filtered baroHeight value stored as a float
        float sonicHeight; //!< Filtered sonicHeight value stored as a float
        float height; //!< Filtered height value stored as a float
        float heading;//!< Filtered heading value stored as a float

        int dataFilterSelection; //!< Contains the currently selected data filter algorithm.

        /**
         * select a Filter type
         */
        enum dataFilter {
            KALMAN = 1, //!< Kalman Filter algorithm.
            COMPLIMENTARY = 2 //!< Complimentary Filter algorithm
        };

        /**
         * Pointer for a new PID (Proportional–Integral–Derivative) object for pitch values
         */
        PID* pitchPID;

        /**
         * Pointer for a new PID (Proportional–Integral–Derivative) object for roll values
         */
        PID* rollPID;

    private:

        /**
         * setValues is a static method that runs in it's own thread assigning values from all assigned orientation sensors.
         *
         * @params *this - a pointer to this object
         */
        static void* setValues( void* orientationInst );

        pthread_t orientationNotifyer; //!< Thread Handle

        Kalman kalmanPitch; //!< kalmanPitch - Create a Kalman filter object for pitch

        Kalman kalmanRoll; //!< kalmanRoll - Create a Kalman filter object for roll

        LVMaxSonarEZ* sonicSensor; //!< sonicSensor - Create a container for the LVMaxSonarEZ object

        LSM303Accelerometer* accelerometer; //!< accelerometer - Create a container for the LSM303Accelerometer object

        LSM303Magnetometer* magnetometer; //!< magnetometer - Create a container for the LSM303Magnetometer object

        L3GD20H* gyroscope; //!< gyroscope - Create a container for the L3GD20H object

        /**
         * runKalmanCalculations run all the sensor data through the Kalman filter and assign orientation values.
         */
        void runKalmanCalculations();

        /**
         * runComplimentaryCalculations run all the sensor data through the Complimentary filter and assign orientation values.
         */
        void runComplimentaryCalculations();

        ofstream dataStorageFile;

    };

}

#endif //QUADRO_ORIENTATION_H
