//
//  L3GD20H.h
//  L3GD20H
//
//  Created by Michael Brookes on 14/11/2015.
//  Copyright © 2015 Michael Brookes. All rights reserved.
//

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

//From Table 17. of the L3GD20H Data sheet ( http://www.adafruit.com/datasheets/L3GD20H.pdf )
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

/**
 \brief L3GD20H : A class that provides control of the L3GD20H which contains : gyroscope.
 \author    Michael Brookes
 \version   1.0
 \date      Nov-2015
 \copyright GNU Public License.
 */

namespace quadro {

    namespace i2c {

        class L3GD20H : public i2cDevice {

        public:

            /**
             \brief Please refer to the documention provided for your L3GD20H for further details (CTRL1 pg 36 point 7.2)
             */
            enum _switch {
                ON = 0x7F,        //!< 0x7F 200 Hz Data Rate, Power On and X, Y, Z enabled
                OFF = 0x00        //!< 0x00 Off
            };

            void start();

            /**
             \brief Creates the template for vector, used by the gyroscope.
             */
            template<typename T>
            struct vector {
                T x, y, z;
            };

            vector<int> rad; //!< Gyroscope Radian vector (X, Y, Z)
            vector<float> angle; //!< Gyroscope Angle Vector (X, Y, Z)

            L3GD20H( unsigned char _deviceAddress = GYRO_ADDRESS, int _busId = 1 );

        protected:

            void setDeviceAddress( unsigned char _deviceAddress ) { this->deviceAddress = _deviceAddress; }

            void setBusId( int _busId ) { this->busId = _busId; }

            _switch gyroSwitch;                    //!< enum value for the Gyroscope power status.

            int setPower( _switch gyroSwitch );

            void setX( void );

            void setY( void );

            void setZ( void );

            static void* getValues( void* gyroInst );

            pthread_t gyroNotifyer;

        };

    }
}

#endif /* SRC_H_L3GD20H_H_ */
