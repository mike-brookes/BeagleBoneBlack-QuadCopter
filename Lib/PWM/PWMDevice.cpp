//
// Created by Michael Brookes on 27/05/2016.
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

#include "pwmDevice.h"

using namespace quadro::pwm;

pwmDevice::pwmDevice( pinBlocks _block, PWMPins _pin ) throw( pwmSetupException& )
{

    this->setBlockNum( _block );
    this->setPinNum( _pin );

    if ( this->settings.overlayLoaded ) {
        this->_pinOverlay = new pinOverlay( this->blockNum, this->pinNum );

        if ( this->_pinOverlay->settings.overlayLoaded )
            this->setFilePaths();
    }

}

void pwmDevice::readDevice( valType _vt )
{
    this->setValType( _vt );
    this->readDevice( 1024 );
}

short pwmDevice::readDevice( size_t _bufferSize )
{
    if ( !this->PWMFile.is_open()) {
        if ( this->openDevice()) {
            try {
                getline( this->PWMFile, this->currentReading );
                this->PWMFile.close();
            }
            catch ( ifstream::failure e ) {
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
    if ( !this->settings.overlayLoaded ) {
        snprintf( this->errMessage, sizeof( this->errMessage ),
                "Fatal pwm Error - Unable to set up your pwm device : %s",
                this->settings.overlay );
        throw pwmSetupException( this->errMessage );
    }
}

void pwmDevice::writeToDevice( valType _vt, long _val ) throw( pwmSetupException& )
{
    this->setValType( _vt );
    this->setWriteVal( _val );
    this->writeToDevice( 1024 );
}

int pwmDevice::writeToDevice( size_t _bufferSize ) throw( pwmSetupException& )
{
    try {

        ofstream PWMWriteFile;
        PWMWriteFile.open( this->getFilePath());
        if ( PWMWriteFile.is_open()) {
            PWMWriteFile << this->val2Write;
            PWMWriteFile.close();
        }

    }
    catch( exception& e ){
        cout << "Exception Occurred" << e.what() << endl;
    }
}

int pwmDevice::openDevice() throw( pwmSetupException& )
{
    try {
        this->PWMFile.open( this->getFilePath(), ios::binary );
        return 1;
    }
    catch ( exception& e ) {
        snprintf( this->errMessage, sizeof( this->errMessage ),
                "Fatal pwm Error - Unable to create fileHandle : %s - %s",
                this->_pinOverlay->pinOverlayDir, e.what());
        throw pwmSetupException( this->errMessage );
    }
}

long pwmDevice::get( valType _vt ) { return this->getCurrentReading( _vt ); }

void pwmDevice::set( valType _vt, long _val ) { this->writeToDevice( _vt, _val ); }

long pwmDevice::getCurrentReading( valType _vt )
{
    this->readDevice( _vt );
    if ( this->currentReading != "" ) {
        if ( _vt == Run )
            return ( this->currentReading.compare( "1" ) == 0 );
        else if ( _vt == Power_Control ) {
            this->powerControlStr = this->currentReading;
            return 1;
        }
        else
            return stoi( this->currentReading );
    }
}

char* pwmDevice::getFilePath()
{
    switch ( this->VT ) {
    case Run :
        return this->runPath;
    case Duty :
        return this->dutyPath;
    case Period :
        return this->periodPath;
    case Polarity :
        return this->polarityPath;
    case Power_Control :
        return this->powerControlPath;
    case Power_RunTime_Active :
        return this->powerRunTime_ActivePath;
    case Power_RunTime_Suspended :
        return this->powerRunTime_SuspendedPath;
    default:
        return this->dutyPath;
    }
}

void pwmDevice::setFilePaths()
{
    snprintf( this->runPath, sizeof( this->runPath ), "%s/%s", this->_pinOverlay->pinOverlayDir, "run" );
    snprintf( this->dutyPath, sizeof( this->dutyPath ), "%s/%s", this->_pinOverlay->pinOverlayDir, "duty" );
    snprintf( this->periodPath, sizeof( this->periodPath ), "%s/%s", this->_pinOverlay->pinOverlayDir, "period" );
    snprintf( this->polarityPath, sizeof( this->polarityPath ), "%s/%s", this->_pinOverlay->pinOverlayDir,
            "polarity" );
    snprintf( this->powerControlPath, sizeof( this->powerControlPath ), "%s/%s", this->_pinOverlay->pinOverlayDir,
            "power/control" );
    snprintf( this->powerRunTime_ActivePath, sizeof( this->powerRunTime_ActivePath ), "%s/%s",
            this->_pinOverlay->pinOverlayDir, "power/runtime_active_time" );
    snprintf( this->powerRunTime_SuspendedPath, sizeof( this->powerRunTime_SuspendedPath ), "%s/%s",
            this->_pinOverlay->pinOverlayDir, "power/runtime_suspended_time" );
}

void pwmDevice::setPinNum( PWMPins _pin ) { this->pinNum = _pin; }

void pwmDevice::setBlockNum( pinBlocks _block ) { this->blockNum = _block; }

void pwmDevice::setValType( valType _vt ) { this->VT = _vt; }

void pwmDevice::setWriteVal( long _val ) { this->val2Write = _val; }