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

#include "orientation.h"

using namespace quadro;

/**
 * orientation constructor
 * Sets up objects for each orientation sensor and starts the thread.
 * @params none
 */
orientation::orientation( )
{
    sonicSensor = new LVMaxSonarEZ();
    sonicSensor->start();
    sonicSensor->setMode( LVMaxSonarEZ::deviceMode::Cm );

    accelerometer = new LSM303Accelerometer();

    magnetometer = new LSM303Magnetometer();

    gyroscope = new L3GD20H();
    pthread_create( &this->orientationNotifyer, NULL, orientation::setValues, this );
}

/**
 * setValues is a static method that runs in it's own thread assigning values from all assigned orientation sensors.
 * @params *this
 */
void* orientation::setValues( void* orientationInst )
{

    int startTime;

    orientation* position = ( orientation* ) orientationInst;

    while ( 1 ) {

        startTime = Timer::milliTimer();

        //Complimentary filter method
        //float CFANGLEX = 0;
        //float CFANGLEY = 0;
        //position->pitch = FILTER_TUNING * ( CFANGLEX + position->gyroscope->angle.x * DATA_RATE ) + ( 1 - FILTER_TUNING ) * position->accelerometer->pitch();
        //position->roll = FILTER_TUNING * ( CFANGLEY + position->gyroscope->angle.y * DATA_RATE ) + ( 1 - FILTER_TUNING ) * position->accelerometer->roll();

        //Kalman Filter Method.
        position->pitch = float( position->kalmanPitch.getAngle( position->accelerometer->pitch(), position->gyroscope->angle.x, DATA_RATE ) );
        position->roll = float( position->kalmanRoll.getAngle( position->accelerometer->roll(), position->gyroscope->angle.y, DATA_RATE ) );

        position->yaw = 0;
        position->height = 0;
        position->baroHeight = 0;
        position->sonicHeight = 0;
        position->heading = 0;
        /*
         * printf( "   GyroX  %7.3f \t AccXangle \e[m %7.3f \t \033[22;31mCFangleX %7.3f\033[0m\t GyroY  %7.3f \t AccYangle %7.3f \t \033[22;36mCFangleY %7.3f\t\033[0m\n",
                position->gyroscope->angle.x, position->accelerometer->pitch(), CFANGLEX,
                position->gyroscope->angle.y, position->accelerometer->roll(), CFANGLEY );
        */
        while ( Timer::milliTimer() - startTime < ( DATA_RATE * 1000 )) {
            usleep( 100 );
        }

    }
}

/**
 * This method is used for determining urgency of movements, attempting to give some kind of priority to avoid crashes.
 * @return int (a value of cm or inches depending on sensor setting)
 */
int orientation::getEmergencyHeight()
{
    return ( this->sonicSensor->currentMode == this->sonicSensor->deviceMode::Cm ) ? EMERGENCY_HEIGHT_CM
                                                                                   : EMERGENCY_HEIGHT_INCH;
}