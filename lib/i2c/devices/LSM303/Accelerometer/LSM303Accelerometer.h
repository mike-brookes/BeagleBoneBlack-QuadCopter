//
// Created by Michael Brookes on 05/05/2016.
//

#ifndef LSM303_ACCELEROMETER_LSM303ACCELEROMETER_H
#define LSM303_ACCELEROMETER_LSM303ACCELEROMETER_H
#define EMERGENCY_ROLL 25
#define EMERGENCY_PITCH 25

#include "../LSM303DLHC.h"
#include <bitset>
#include <math.h>

namespace quadro {

    namespace i2c {

        using namespace std;

        class LSM303Accelerometer : public LSM303DLHC {

        public:

            LSM303Accelerometer( unsigned char _deviceAddress = ACCEL_ADDRESS, int _busId = 1 );

            float roll();

            float pitch();

        private:

            void startRecordingPitchAndRoll();

            static void* getAccelerometerValues( void* _ACCEL );

            pthread_t updateValuesThread;
        };

    }
}

#endif //LSM303_ACCELEROMETER_LSM303ACCELEROMETER_H
