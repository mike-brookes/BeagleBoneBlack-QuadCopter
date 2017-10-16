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

#include "analogBase.h"

using namespace quadro::analog;

analogBase::analogBase()
        :devicePort{ analogPort::PORT0 }
{

    setDevicePort( analogPort::PORT0 );
    initDevice();
    if ( analogOverlay_.settings.overlayLoaded ) {
        setDeviceFilePath();
    }
    else {
        snprintf( analogOverlay_.errMessage, sizeof( analogOverlay_.errMessage ),
                "Fatal analogBase Error - Unable to initialise the analogBase Device." );
        throw analogSetupException( analogOverlay_.errMessage );
    }
}

analogBase::~analogBase() = default;

void analogBase::initDevice() throw( analogSetupException& )
{
    if ( !analogOverlay_.settings.overlayLoaded ) {
        snprintf( analogOverlay_.errMessage, sizeof( analogOverlay_.errMessage ),
                "Fatal analogBase Error - Unable to load overlays : %s",
                analogOverlay_.settings.overlay );
        throw analogSetupException( analogOverlay_.errMessage );
    }
}

int analogBase::getCurrentReading()
{
    readDevice( 1024 );
    if ( currentReading.length() > 0 ) {
        return stoi( currentReading );
    }
    else {
        return 1;
    }
}

short analogBase::readDevice( size_t bufferSize_ )
{
    if ( !deviceFile.is_open()) {
        if ( openDevice()) {
            try {
                getline( deviceFile, currentReading );
                deviceFile.close();
            }
            catch ( ifstream::failure& e ) {
                throw analogSetupException( e.what());
            }
        }
        return 0;
    } else {
        return -1;
    }
}

int analogBase::openDevice() throw( analogSetupException& )
{
    try {
        deviceFile.open( deviceFilePath.c_str(), ios::binary | ios::in );
        return 1;
    }
    catch ( exception& e ) {
        snprintf( analogOverlay_.errMessage, sizeof( analogOverlay_.errMessage ),
                "Fatal analogBase Error - Unable to create fileHandle : %s",
                deviceFilePath.c_str());
        throw analogSetupException( analogOverlay_.errMessage );
    }
}

void analogBase::setDevicePort( analogPort DevicePort )
{
    devicePort = DevicePort;
}

void analogBase::setDeviceFilePath()
{
    ostringstream oss;
    deviceFilePath = analogOverlay_.settings.helperPath;
    deviceFilePath.append( analogOverlay_.settings.fileType );
    oss << devicePort;
    deviceFilePath.append( oss.str());
}