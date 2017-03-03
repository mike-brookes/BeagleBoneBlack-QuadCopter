//
// Created by Michael Brookes on 20/05/2016.
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

#include "analogBase.h"

using namespace quadro::analog;

analogBase::analogBase()
{

    this->setDevicePort( analogPort::PORT0 );
    this->initDevice();
    if ( this->_analogOverlay.settings.overlayLoaded ) {
        this->setDeviceFilePath();
    }
    else {
        snprintf( this->_analogOverlay.errMessage, sizeof( this->_analogOverlay.errMessage ),
                "Fatal analogBase Error - Unable to initialise the analogBase Device." );
        throw analogSetupException( this->_analogOverlay.errMessage );
    }
}

analogBase::~analogBase() { }

void analogBase::initDevice() throw( analogSetupException& )
{
    if ( !this->_analogOverlay.settings.overlayLoaded ) {
        snprintf( this->_analogOverlay.errMessage, sizeof( this->_analogOverlay.errMessage ),
                "Fatal analogBase Error - Unable to load overlays : %s",
                this->_analogOverlay.settings.overlay );
        throw analogSetupException( this->_analogOverlay.errMessage );
    }
}

int analogBase::getCurrentReading()
{
    this->readDevice( 1024 );
    if ( this->currentReading.length() > 0 ) {
        return stoi( this->currentReading );
    }
    else {
        return 1;
    }
}

short analogBase::readDevice( size_t _bufferSize )
{
    if ( !this->deviceFile.is_open()) {
        if ( this->openDevice()) {
            try {
                getline( this->deviceFile, this->currentReading );
                this->deviceFile.close();
            }
            catch ( ifstream::failure e ) {
                throw new analogSetupException( e.what() );
            }
        }
        return 0;
    }
}

int analogBase::openDevice() throw( analogSetupException& )
{
    try {
        this->deviceFile.open( this->deviceFilePath.c_str(), ios::binary | ios::in );
        return 1;
    }
    catch ( exception& e ) {
        snprintf( this->_analogOverlay.errMessage, sizeof( this->_analogOverlay.errMessage ),
                "Fatal analogBase Error - Unable to create fileHandle : %s",
                this->deviceFilePath.c_str());
        throw analogSetupException( this->_analogOverlay.errMessage );
    }
}

void analogBase::setDevicePort( analogPort DevicePort )
{
    this->devicePort = DevicePort;
}

void analogBase::setDeviceFilePath()
{
    ostringstream oss;
    this->deviceFilePath = this->_analogOverlay.settings.helperPath;
    this->deviceFilePath.append( this->_analogOverlay.settings.fileType );
    oss << this->devicePort;
    this->deviceFilePath.append( oss.str());
}