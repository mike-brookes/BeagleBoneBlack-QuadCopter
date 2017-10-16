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

#include "pwmDevice.h"

using namespace quadro::pwm;

pwmDevice::pwmDevice( pinBlocks _block, PWMPins _pin ) throw( pwmSetupException& )
{

    setBlockNum( _block );
    setPinNum( _pin );

    if ( settings.overlayLoaded ) {
        _pinOverlay = new pinOverlay( blockNum, pinNum );

        if ( _pinOverlay->settings.overlayLoaded )
            setFilePaths();
    }

}

void pwmDevice::readDevice( valType _vt )
{
    setValType( _vt );
    readDevice( 1024 );
}

short pwmDevice::readDevice( size_t _bufferSize )
{
    if ( !PWMFile.is_open()) {
        if ( openDevice()) {
            try {
                getline( PWMFile, currentReading );
                PWMFile.close();
            }
            catch ( ifstream::failure& e ) {
                cout << "Exception caught handling binary file : " << e.what() << endl;
            }
        }
        return 1;
    }
    else
        return -1;
}

void pwmDevice::initDevice() throw( pwmSetupException& )
{
    if ( !settings.overlayLoaded ) {
        snprintf( errMessage, sizeof( errMessage ),
                "Fatal pwm Error - Unable to set up your pwm device : %s",
                settings.overlay );
        throw pwmSetupException( errMessage );
    }
}

void pwmDevice::writeToDevice( valType _vt, long _val ) throw( pwmSetupException& )
{
    setValType( _vt );
    setWriteVal( _val );
    writeToDevice( 1024 );
}

int pwmDevice::writeToDevice( size_t _bufferSize ) throw( pwmSetupException& )
{
    try {

        ofstream PWMWriteFile;
        PWMWriteFile.open( getFilePath());
        if ( PWMWriteFile.is_open()) {
            PWMWriteFile << val2Write;
            PWMWriteFile.close();
            return 1;
        }
        else {
            return 0;
        }

    }
    catch ( exception& e ) {
        cout << "Exception Occurred" << e.what() << endl;
        return 0;
    }
}

int pwmDevice::openDevice() throw( pwmSetupException& )
{
    try {
        PWMFile.open( getFilePath(), ios::binary );
        return 1;
    }
    catch ( exception& e ) {
        snprintf( errMessage, sizeof( errMessage ),
                "Fatal pwm Error - Unable to create fileHandle : %s - %s",
                _pinOverlay->pinOverlayDir, e.what());
        throw pwmSetupException( errMessage );
    }
}

long pwmDevice::get( valType _vt ) { return getCurrentReading( _vt ); }

void pwmDevice::set( valType _vt, long _val ) { writeToDevice( _vt, _val ); }

long pwmDevice::getCurrentReading( valType _vt )
{
    readDevice( _vt );
    if ( !currentReading.empty()) {
        if ( _vt == Run )
            return ( currentReading == "1" );
        else if ( _vt == Power_Control ) {
            powerControlStr = currentReading;
            return 1;
        }
        else
            return stoi( currentReading );
    }
    else {
        return 0;
    }
}

char* pwmDevice::getFilePath()
{
    switch ( VT ) {
    case Run :
        return runPath;
    case Duty :
        return dutyPath;
    case Period :
        return periodPath;
    case Polarity :
        return polarityPath;
    case Power_Control :
        return powerControlPath;
    case Power_RunTime_Active :
        return powerRunTime_ActivePath;
    case Power_RunTime_Suspended :
        return powerRunTime_SuspendedPath;
    default:
        return dutyPath;
    }
}

void pwmDevice::setFilePaths()
{
    snprintf( runPath, sizeof( runPath ), "%s/%s", _pinOverlay->pinOverlayDir, "run" );
    snprintf( dutyPath, sizeof( dutyPath ), "%s/%s", _pinOverlay->pinOverlayDir, "duty" );
    snprintf( periodPath, sizeof( periodPath ), "%s/%s", _pinOverlay->pinOverlayDir, "period" );
    snprintf( polarityPath, sizeof( polarityPath ), "%s/%s", _pinOverlay->pinOverlayDir,
            "polarity" );
    snprintf( powerControlPath, sizeof( powerControlPath ), "%s/%s", _pinOverlay->pinOverlayDir,
            "power/control" );
    snprintf( powerRunTime_ActivePath, sizeof( powerRunTime_ActivePath ), "%s/%s",
            _pinOverlay->pinOverlayDir, "power/runtime_active_time" );
    snprintf( powerRunTime_SuspendedPath, sizeof( powerRunTime_SuspendedPath ), "%s/%s",
            _pinOverlay->pinOverlayDir, "power/runtime_suspended_time" );
}

void pwmDevice::setPinNum( PWMPins _pin ) { pinNum = _pin; }

void pwmDevice::setBlockNum( pinBlocks _block ) { blockNum = _block; }

void pwmDevice::setValType( valType _vt ) { VT = _vt; }

void pwmDevice::setWriteVal( long _val ) { val2Write = _val; }