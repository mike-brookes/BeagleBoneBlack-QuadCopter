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

#include "L3GD20H.h"

using namespace quadro::i2c;

L3GD20H::L3GD20H( unsigned char _deviceAddress, int _busId )
{
    setDeviceAddress( _deviceAddress );
    setBusId( _busId );
    initDevice();

    if ( setPower( _switch::ON ) < 0 ) {
        throw i2cSetupException( "Critical Error : L3GD20H - Attempted to set the Gyroscopes Power state but this action failed." );
    }
}

int L3GD20H::setPower( _switch gyroSwitch )
{
    setEnabled( gyroSwitch == _switch::ON );
    setRegisterAddress( CTRL1 );
    setRegisterValue( gyroSwitch );
    writeToDevice( 2 );
    return gyroSwitch;
}

void L3GD20H::setEnabled( bool _enabled )
{
    enabled = _enabled;
}

bool L3GD20H::isEnabled(){
    return enabled;
}

void* L3GD20H::runMainSensorUpdateThread( void* static_inst )
{
    auto* gyro = ( L3GD20H* ) static_inst;
    int startTime;
    while ( gyro->isEnabled() ) {
        startTime = Timer::milliTimer();
        gyro->calcX();
        gyro->calcY();
        gyro->calcZ();
        while ( Timer::milliTimer() - startTime < ( DT * 1000 )) {
            usleep( 100 );
        }
    }
    return nullptr;
}

int L3GD20H::start()
{
    //pthread_create doesn't throw an exception, only returns error codes - these are handled below.
    threadRet = pthread_create( &threadHandle, nullptr, L3GD20H::runMainSensorUpdateThread, this );

    //Thread returned 0 (Success Code)
    if ( threadRet != 0 ) {
        //The sonic sensor thread failed, set the status to "Error" and throw an appropriate exception.
        setStatus( deviceStatus::Error );
        if ( threadRet == EAGAIN ) {
            //Failed because of resource unavailability, try once more and then throw an exception on failure
            threadRet = pthread_create( &threadHandle, nullptr, L3GD20H::runMainSensorUpdateThread, this );
            if ( threadRet != 0 ) {
                throw i2cSetupException(
                        "(LVMaxSonarEZ) " + i2c::THREAD_FATAL + " : errorNumber = "
                                + to_string( threadRet ) );
            }
        }
        else if ( threadRet == EPERM ) {
            //Thread creation failed because of invalid permissions on the system to create threads.
            throw i2cSetupException(
                    "(LVMaxSonarEZ) " + i2c::THREAD_PERMISSIONS + " : errorNumber = " + to_string( threadRet ) );
        }
        else if ( threadRet == EINVAL ) {
            //Thread creation failed because the argument used is invalid.
            throw i2cSetupException(
                    "(LVMaxSonarEZ) " + i2c::THREAD_INVALID_ARG + " : errorNumber = " + to_string( threadRet ) );
        }
        else {
            //An unknown error occurred - unknown error code.
            throw i2cSetupException(
                    "(LVMaxSonarEZ) " + i2c::THREAD_UNKNOWN + " : errorNumber = " + to_string( threadRet ) );
        }
    }

    //The thread started correctly, so set the status of the Sonic Sensor to "On".
    setStatus( deviceStatus::On );

    //return the device status - realistically it should always be "On" if we get this far...
    return getStatus();

}

void L3GD20H::calcX( )
{
    rad.x = ( int16_t ) ( getValueFromRegister( OUT_X_L ) | ( getValueFromRegister( OUT_X_H ) << 8 ));
    rad.x *= 0.00875F;
    angle.x = float( rad.x * DT );
}

void L3GD20H::calcY( )
{
    rad.y = ( int16_t ) ( getValueFromRegister( OUT_Y_L ) | ( getValueFromRegister( OUT_Y_H ) << 8 ));
    rad.y *= 0.00875F;
    angle.y = float( rad.y * DT );
}

void L3GD20H::calcZ( )
{
    rad.z = -( int16_t ) ( getValueFromRegister( OUT_Z_L )
            | ( getValueFromRegister( OUT_Z_H ) << 8 ));
    rad.z *= 0.00875F;
    angle.z = float( rad.z * DT );
}

void L3GD20H::setBusId( int _busId ) { busId = _busId; }

void L3GD20H::setDeviceAddress( unsigned char _deviceAddress ) { deviceAddress = _deviceAddress; }
