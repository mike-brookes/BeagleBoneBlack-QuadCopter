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

            /*!
             * LSM303Accelerometer Constructor, initialises the device - writes default settings to the sensor
             *
             * @see start() to start reading the device and updating roll and pitch values.
             * @param _deviceAddress
             * @param _busId
             */
            LSM303Accelerometer( unsigned char _deviceAddress = ACCEL_ADDRESS, int _busId = 1 );

            /*!
             * Calculates roll using the following equation :
             * atan2( X, sqrt( Y * Y + Z * Z )) * 180.0 ) / 3.14159265358979323846 )
             *
             * @return float Current roll calculation
             */
            float calcRoll();

            /*!
             * Calculates pitch using the following equation :
             * atan2( Y, Z ) * 180.0 ) / 3.14159265358979323846
             *
             * @return float Current pitch calculation.
             */
            float calcPitch();

            /**
             * start() - Allows the independent control to start the thread that updates the Accelerometer readings.
             *
             * @param none
             * @throws i2cSetupException
             * @returns int deviceStatus : 1 = on, 0 = off or 2 = error
             */
            int start();

            float pitch; //!< Stores the calculated Pitch value

            float roll; //!< Stores the calculated Roll value

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

#endif //LSM303_ACCELEROMETER_LSM303ACCELEROMETER_H
