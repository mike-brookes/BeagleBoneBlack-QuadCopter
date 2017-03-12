//
// Created by Michael Brookes on 06/02/2017.
//

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

    class orientation {
    public:
        orientation();

        LVMaxSonarEZ* sonicSensor;
        LSM303Accelerometer* accelerometer;
        LSM303Magnetometer* magnetometer;
        L3GD20H* gyroscope;

        static void* setValues( void* orientationInst );

        int getEmergencyHeight();

        pthread_t orientationNotifyer;

        float roll, pitch, yaw, baroHeight, sonicHeight, height, heading;

        Kalman kalmanPitch;
        Kalman kalmanRoll;
    };

}

#endif //QUADRO_ORIENTATION_H
