//
// Created by Michael Brookes on 26/05/2016.
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

#include "LVMaxSonarEZ.h"

using namespace quadro::analog;

LVMaxSonarEZ::LVMaxSonarEZ()
{
    this->setMode( deviceMode::Cm );
    this->setStatus( deviceStatus::Off );
}

void LVMaxSonarEZ::start()
{
    this->threadRet = pthread_create( &this->sonicReaderThread, NULL, LVMaxSonarEZ::getValueAsInt, this );

    if ( this->threadRet == 0 )
        this->setStatus( deviceStatus::On );
    else {
        this->setStatus( deviceStatus::Error );
        if ( this->threadRet == EAGAIN )
            this->currentError = "Unable to create thread : Resource Limit Reached.";
        else
            this->currentError = "Unable to create thread : Unknown Error Occurred.";
    }
}

void LVMaxSonarEZ::stop()
{
    this->threadRet = pthread_cancel( this->sonicReaderThread );

    if ( this->threadRet == 0 )
        this->setStatus( deviceStatus::Off );
    else {
        this->setStatus( deviceStatus::Error );
        if ( this->threadRet == ESRCH )
            this->currentError = "Unable to cancel thread : Unable to locate process.";
        else
            this->currentError = "Unable to cancel thread : Unknown Error Occurred.";
    }

}

void* LVMaxSonarEZ::getValueAsInt( void* static_inst )
{
    LVMaxSonarEZ* SonicInst = ( LVMaxSonarEZ* ) static_inst;
    while ( SonicInst->currentStatus == deviceStatus::On ) {
        SonicInst->reading = SonicInst->getReading();
        SonicInst->addToDataStore();
        usleep( SONIC_DATATIMER );
    }
}

int LVMaxSonarEZ::getReading()
{
    return this->getCurrentReading();
}

double LVMaxSonarEZ::convertReadingToDistance( int _reading )
{
    switch ( this->currentMode ) {
    case deviceMode::Inches :
        return _reading / SONIC_INCH_MODIFYER;
    case deviceMode::Cm :
        return ( _reading / SONIC_INCH_MODIFYER ) * SONIC_CM_MODIFYER;
    default:
        return _reading / SONIC_INCH_MODIFYER;
    }
}

void LVMaxSonarEZ::setAverage( int iterations = 50 )
{
    double total_reading = 0;
    int i = 0;
    while ( i < iterations ) {
        total_reading += this->reading;
        usleep( this->dataTimer );
        i++;
    }
    this->avgReading = total_reading / iterations;
}

void LVMaxSonarEZ::addToDataStore()
{
    for ( int i = 0; i < MAX_DATASTORE; i++ )
        this->dataStoredValues[ i ] = this->dataStoredValues[ i + 1 ];

    this->dataStoredValues[ MAX_DATASTORE - 1 ] = this->convertReadingToDistance( this->reading );
}

void LVMaxSonarEZ::setMode( deviceMode _mode )
{
    this->currentMode = _mode;
}

void LVMaxSonarEZ::setStatus( deviceStatus _status )
{
    this->currentStatus = _status;
}

double LVMaxSonarEZ::distance()
{
    return this->convertReadingToDistance( this->reading );
}

double LVMaxSonarEZ::avgDistance()
{
    this->setAverage( 50 );
    return this->avgReading;
}