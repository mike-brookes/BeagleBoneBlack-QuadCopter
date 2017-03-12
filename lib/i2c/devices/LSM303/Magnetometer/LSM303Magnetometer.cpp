/*
Copyright (C) 2016 Michael Brookes

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
    this->setDeviceAddress( _deviceAddress );
    this->setBusId( _busId );
    this->initDevice();
    this->loadRecommendedFlightSettings();
    this->init();
    this->startRecordingHeading();
}

double LSM303Magnetometer::heading()
{
    double x2 = 0, y2 = 0;

    double t_roll = this->x * this->x + this->z * this->z;
    float rollRadians = ( float ) atan2(( double ) this->y, sqrt( t_roll ));

    double t_pitch = this->y * this->y + this->z * this->z;
    float pitchRadians = ( float ) atan2(( double ) this->x, sqrt( t_pitch ));

    float cosRoll = ( float ) cos( rollRadians );
    float sinRoll = ( float ) sin( rollRadians );

    float cosPitch = ( float ) cos( -1 * pitchRadians );
    float sinPitch = ( float ) sin( -1 * pitchRadians );

    x2 = ( this->x ) * cosPitch + ( this->z ) * sinPitch;
    y2 = ( this->x ) * sinRoll * sinPitch + ( this->y ) * cosRoll - ( this->z ) * sinRoll * cosPitch;

    return ( atan2( x2, y2 ) * 180 ) / M_PI;
}

void LSM303Magnetometer::setHeadingAverages( int iterations )
{
    int i = 0, _totalHeading = 0;
    while ( i < iterations ) {
        _totalHeading += this->heading();
        usleep( this->dataTimer );
        i++;
    }
    this->avgHeading = _totalHeading / iterations;
}

void LSM303Magnetometer::addToHeadingDataStore()
{
    for ( int i = 0; i < ( MAX_DATASTORE - 1 ); i++ ) {
        int NextIndex = ( i + 1 );
        this->headingDataStoredValues[ i ] = this->headingDataStoredValues[ NextIndex ];
    }
    this->headingDataStoredValues[ ( MAX_DATASTORE - 1 ) ] = this->heading();
}

void LSM303Magnetometer::startRecordingHeading()
{
    pthread_create( &this->LSM303UpdateValuesThread, NULL, LSM303Magnetometer::getMagnetometerValues, this );
}

void* LSM303Magnetometer::getMagnetometerValues( void* _ACCEL )
{
    LSM303Magnetometer* accel = ( LSM303Magnetometer* ) _ACCEL;
    while ( 1 ) {
        accel->addToHeadingDataStore();
        usleep( accel->dataTimer );
    }
}