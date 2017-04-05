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

#include "LSM303Magnetometer.h"

using namespace quadro::i2c;

LSM303Magnetometer::LSM303Magnetometer( unsigned char _deviceAddress, int _busId )
{
    setDeviceAddress( _deviceAddress );
    setBusId( _busId );
    initDevice();
    loadRecommendedFlightSettings();
    startSensorThread();
}

double LSM303Magnetometer::calcHeading()
{
    double x2 = 0, y2 = 0;

    double t_roll = x * x + z * z;
    float rollRadians = ( float ) atan2(( double ) y, sqrt( t_roll ));

    double t_pitch = y * y + z * z;
    float pitchRadians = ( float ) atan2(( double ) x, sqrt( t_pitch ));

    float cosRoll = ( float ) cos( rollRadians );
    float sinRoll = ( float ) sin( rollRadians );

    float cosPitch = ( float ) cos( -1 * pitchRadians );
    float sinPitch = ( float ) sin( -1 * pitchRadians );

    x2 = ( x ) * cosPitch + ( z ) * sinPitch;
    y2 = ( x ) * sinRoll * sinPitch + ( y ) * cosRoll - ( z ) * sinRoll * cosPitch;

    return ( atan2( x2, y2 ) * 180 ) / M_PI;
}

void* LSM303Magnetometer::runMainSensorUpdateThread( void* static_inst )
{
    LSM303Magnetometer* mag = ( LSM303Magnetometer* ) static_inst;
    while ( mag->currentStatus == deviceStatus::On ) {
        mag->heading = mag->calcHeading();
        usleep( mag->dataTimer );
    }
    return 0;
}

int LSM303Magnetometer::start()
{
    //pthread_create doesn't throw an exception, only returns error codes - these are handled below.
    threadRet = pthread_create( &threadHandle, NULL, LSM303Magnetometer::runMainSensorUpdateThread, this );

    //Thread returned 0 (Success Code)
    if ( threadRet != 0 ) {
        //The sonic sensor thread failed, set the status to "Error" and throw an appropriate exception.
        setStatus( deviceStatus::Error );
        if ( threadRet == EAGAIN ) {
            //Failed because of resource unavailability, try once more and then throw an exception on failure
            threadRet = pthread_create( &threadHandle, NULL, LSM303Magnetometer::runMainSensorUpdateThread, this );
            if ( threadRet != 0 ) {
                throw new i2cSetupException(
                        "(LVMaxSonarEZ) " + i2c::THREAD_FATAL + " : errorNumber = "
                                + to_string( threadRet ) );
            }
        }
        else if ( threadRet == EPERM ) {
            //Thread creation failed because of invalid permissions on the system to create threads.
            throw new i2cSetupException(
                    "(LVMaxSonarEZ) " + i2c::THREAD_PERMISSIONS + " : errorNumber = " + to_string( threadRet ) );
        }
        else if ( threadRet == EINVAL ) {
            //Thread creation failed because the argument used is invalid.
            throw new i2cSetupException(
                    "(LVMaxSonarEZ) " + i2c::THREAD_INVALID_ARG + " : errorNumber = " + to_string( threadRet ) );
        }
        else {
            //An unknown error occurred - unknown error code.
            throw new i2cSetupException(
                    "(LVMaxSonarEZ) " + i2c::THREAD_UNKNOWN + " : errorNumber = " + to_string( threadRet ) );
        }
    }

    //The thread started correctly, so set the status of the Sonic Sensor to "On".
    setStatus( deviceStatus::On );

    //return the device status - realistically it should always be "On" if we get this far...
    return getStatus();

}