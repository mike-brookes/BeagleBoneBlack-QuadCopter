//
// Created by Michael Brookes on 05/05/2016.
//

#include "LSM303Accelerometer.h"

using namespace quadro::i2c;

LSM303Accelerometer::LSM303Accelerometer( unsigned char _deviceAddress, int _busId )
{
    this->setDeviceAddress( _deviceAddress );
    this->setBusId( _busId );
    this->initDevice();
    this->loadRecommendedFlightSettings();
    this->init();
    this->startRecordingPitchAndRoll();
}

float LSM303Accelerometer::roll()
{
    return (float) ( ( atan2( ( double ) this->x, sqrt( double( this->y * this->y + this->z * this->z ))) * 180.0 ) / M_PI );
}

float LSM303Accelerometer::pitch()
{
    return (float) ( ( atan2( ( double ) this->y, ( double ) this->z ) * 180.0 ) / M_PI );
}

void LSM303Accelerometer::startRecordingPitchAndRoll()
{
    pthread_create( &this->updateValuesThread, NULL, LSM303Accelerometer::getAccelerometerValues, this );
}

void* LSM303Accelerometer::getAccelerometerValues( void* _ACCEL )
{
    LSM303Accelerometer* accel = ( LSM303Accelerometer* ) _ACCEL;
    while ( 1 ) {
        accel->pitch();
        accel->roll();
        usleep( accel->dataTimer );
    }
}