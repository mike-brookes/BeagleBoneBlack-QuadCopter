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
using namespace std;

LVMaxSonarEZ::LVMaxSonarEZ()
{
    //Set device startup settings
    setMode( deviceMode::Cm );
    setStatus( deviceStatus::Off );
}

int LVMaxSonarEZ::start()
{

    //pthread_create doesn't throw an exception, only returns error codes - these are handled below.
    threadRet = pthread_create( &threadHandle, nullptr, LVMaxSonarEZ::runMainSensorUpdateThread, this );

    //Thread returned 0 (Success Code)
    if ( threadRet != 0 ) {
        //The sonic sensor thread failed, set the status to "Error" and throw an appropriate exception.
        setStatus( deviceStatus::Error );
        if ( threadRet == EAGAIN ) {
            //Failed because of resource unavailability, try once more and then throw an exception on failure
            threadRet = pthread_create( &threadHandle, nullptr, LVMaxSonarEZ::runMainSensorUpdateThread, this );
            if ( threadRet != 0 ) {
                throw analogSetupException(
                        "(LVMaxSonarEZ) " + analog::THREAD_FATAL + " : errorNumber = "
                                + to_string( threadRet ));
            }
        }
        else if ( threadRet == EPERM ) {
            //Thread creation failed because of invalid permissions on the system to create threads.
            throw analogSetupException(
                    "(LVMaxSonarEZ) " + analog::THREAD_PERMISSIONS + " : errorNumber = " + to_string( threadRet ));
        }
        else if ( threadRet == EINVAL ) {
            //Thread creation failed because the argument used is invalid.
            throw analogSetupException(
                    "(LVMaxSonarEZ) " + analog::THREAD_INVALID_ARG + " : errorNumber = " + to_string( threadRet ));
        }
        else {
            //An unknown error occurred - unknown error code.
            throw analogSetupException(
                    "(LVMaxSonarEZ) " + analog::THREAD_UNKNOWN + " : errorNumber = " + to_string( threadRet ));
        }
    }

    //The thread started correctly, so set the status of the Sonic Sensor to "On".
    setStatus( deviceStatus::On );

    //return the device status - realistically it should always be "On" if we get this far...
    return getStatus();

}

int LVMaxSonarEZ::stop()
{
    //pthread_cancel doesn't throw an exception, only returns error codes - these are handled below.
    threadRet = pthread_cancel( threadHandle );

    if ( threadRet != 0 ) {
        //The sonic sensor thread cancellation failed, set the status to "Error" and throw an appropriate exception.
        setStatus( deviceStatus::Error );
        if ( threadRet == ESRCH ) {
            //Unable to locate process to cancel.
            throw analogRuntimeException( THREAD_CANCELLATION_FAILURE );
        }
        else {
            //An unknown error occurred - unknown error code.
            throw analogRuntimeException( THREAD_CANCELLATION_UNKNOWN );
        }
    }

    //The thread was cancelled successfully - set the device status to "Off".
    setStatus( deviceStatus::Off );

    return getStatus();

}

void* LVMaxSonarEZ::runMainSensorUpdateThread( void* static_inst )
{
    auto* SonicInst = ( LVMaxSonarEZ* ) static_inst;
    while ( SonicInst->currentStatus == deviceStatus::On ) {
        SonicInst->reading = SonicInst->getCurrentReading();
        usleep( SonicInst->dataTimer );
    }
    return nullptr;
}

double LVMaxSonarEZ::convertReadingToDistance( int _reading )
{
    switch ( currentMode ) {
    case deviceMode::Inches :
        return _reading / SONIC_INCH_MODIFIER;
    case deviceMode::Cm :
        return ( _reading / SONIC_INCH_MODIFIER ) * SONIC_CM_MODIFIER;
    default:
        return _reading / SONIC_INCH_MODIFIER;
    }
}

void LVMaxSonarEZ::setMode( deviceMode _mode )
{
    currentMode = _mode;
}

void LVMaxSonarEZ::setStatus( deviceStatus _status )
{
    currentStatus = _status;
}

int LVMaxSonarEZ::getStatus()
{
    return currentStatus;
}

double LVMaxSonarEZ::getDistance()
{
    return convertReadingToDistance( reading );
}