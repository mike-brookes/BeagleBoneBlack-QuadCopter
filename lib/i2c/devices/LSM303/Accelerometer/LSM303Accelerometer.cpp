//
// Created by Michael Brookes on 05/05/2016.
//

#include "LSM303Accelerometer.h"

using namespace quadro::i2c;

LSM303Accelerometer::LSM303Accelerometer( unsigned char _deviceAddress, int _busId )
{
    setDeviceAddress( _deviceAddress );
    setBusId( _busId );
    initDevice();
    loadRecommendedFlightSettings();
    startSensorThread();
}

float LSM303Accelerometer::calcRoll()
{
    return (float) ( ( atan2( ( double ) x, sqrt( double( y * y + z * z ))) * 180.0 ) / M_PI );
}

float LSM303Accelerometer::calcPitch()
{
    return (float) ( ( atan2( ( double ) y, ( double ) z ) * 180.0 ) / M_PI );
}

int LSM303Accelerometer::start()
{
    //pthread_create doesn't throw an exception, only returns error codes - these are handled below.
    threadRet = pthread_create( &threadHandle, NULL, LSM303Accelerometer::runMainSensorUpdateThread, this );

    //Thread returned 0 (Success Code)
    if ( threadRet != 0 ) {
        //The sonic sensor thread failed, set the status to "Error" and throw an appropriate exception.
        setStatus( deviceStatus::Error );
        if ( threadRet == EAGAIN ) {
            //Failed because of resource unavailability, try once more and then throw an exception on failure
            threadRet = pthread_create( &threadHandle, NULL, LSM303Accelerometer::runMainSensorUpdateThread, this );
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

void* LSM303Accelerometer::runMainSensorUpdateThread( void* static_inst )
{
    LSM303Accelerometer* accel = ( LSM303Accelerometer* ) static_inst;
    while ( accel->currentStatus == deviceStatus::On ) {
        accel->pitch = accel->calcPitch();
        accel->roll = accel->calcRoll();
        usleep( accel->dataTimer );
    }

    return 0;
}