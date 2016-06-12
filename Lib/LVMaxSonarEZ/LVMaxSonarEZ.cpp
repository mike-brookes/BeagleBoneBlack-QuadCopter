//
// Created by Michael Brookes on 26/05/2016.
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

#include "LVMaxSonarEZ.h"


LVMaxSonarEZ::LVMaxSonarEZ( ) {
    this->SetMode( DeviceMode::Cm );
    this->SetStatus( DeviceStatus::Off );
}

void LVMaxSonarEZ::Start( ) {
    this->ThreadRet = pthread_create( &this->SonicReaderThread, NULL, LVMaxSonarEZ::GetValueAsInt, this );

    if( this->ThreadRet == 0 )
        this->SetStatus( DeviceStatus::On );
    else {
        this->SetStatus( DeviceStatus::Error );
        if( this->ThreadRet == EAGAIN )
            this->CurrentError = "Unable to create thread : Resource Limit Reached.";
        else
            this->CurrentError = "Unable to create thread : Unknown Error Occurred.";
    }
}

void LVMaxSonarEZ::Stop( ) {
    this->ThreadRet = pthread_cancel( this->SonicReaderThread );

    if( this->ThreadRet == 0 )
        this->SetStatus( DeviceStatus::Off );
    else {
        this->SetStatus( DeviceStatus::Error );
        if( this->ThreadRet == ESRCH )
            this->CurrentError = "Unable to cancel thread : Unable to locate process.";
        else
            this->CurrentError = "Unable to cancel thread : Unknown Error Occurred.";
    }

}

void *LVMaxSonarEZ::GetValueAsInt( void *static_inst ) {
    LVMaxSonarEZ* SonicInst = (LVMaxSonarEZ*)static_inst;
    while( SonicInst->CurrentStatus == DeviceStatus::On ) {
        SonicInst->Reading = SonicInst->GetReading( );
        SonicInst->AddToDataStore( );
        usleep( SONIC_DATATIMER );
    }
}

int LVMaxSonarEZ::GetReading( ) {
    return this->GetCurrentReading( );
}

double LVMaxSonarEZ::ConvertReadingToDistance( int _reading ) {
    switch( this->CurrentMode ) {
        case DeviceMode::Inches :
            return _reading / SONIC_INCH_MODIFYER;
        case DeviceMode::Cm :
            return ( _reading / SONIC_INCH_MODIFYER ) * SONIC_CM_MODIFYER;
        default:
            return _reading / SONIC_INCH_MODIFYER;
    }
}

void LVMaxSonarEZ::SetAverage( int iterations = 50 ) {
    double total_reading = 0;
    int i = 0;
    while (i < iterations) {
        total_reading += this->Reading;
        usleep( this->DataTimer );
        i++;
    }
    this->AvgReading = total_reading / iterations;
}

void LVMaxSonarEZ::AddToDataStore( ) {
    for( int i = 0; i < MAX_DATASTORE; i++ )
        this->DataStoredValues[ i ] = this->DataStoredValues[ i + 1 ];

    this->DataStoredValues[ MAX_DATASTORE -1 ] = this->Reading;
}

void LVMaxSonarEZ::SetMode( DeviceMode _mode ) {
    this->CurrentMode = _mode;
}

void LVMaxSonarEZ::SetStatus( DeviceStatus _status ) {
    this->CurrentStatus = _status;
}

double LVMaxSonarEZ::Distance( ) {
    return this->ConvertReadingToDistance( this->Reading );
}

double LVMaxSonarEZ::AvgDistance( ) {
    this->SetAverage( 50 );
    return this->AvgReading;
}