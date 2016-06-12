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

#include <vector>
#include "AnalogDevice.h"

namespace abAnalog{

    AnalogDevice::AnalogDevice( ) {

        this->SetDevicePort( AnalogPort::PORT0 );
        this->InitDevice( );
        if( this->_AnalogOverlay.Settings.OverlayLoaded ) {
            this->SetDeviceFilePath( );
        }
        else {
            snprintf( this->_AnalogOverlay.ErrMessage, sizeof( this->_AnalogOverlay.ErrMessage ),
                      "Fatal Analog Error - Unable to initialise the Analog Device." );
            throw AnalogSetupException( this->_AnalogOverlay.ErrMessage );
        }
    }

    AnalogDevice::~AnalogDevice( ) { }

    void AnalogDevice::InitDevice( ) throw( AnalogSetupException& ) {
        if( !this->_AnalogOverlay.Settings.OverlayLoaded ) {
            snprintf( this->_AnalogOverlay.ErrMessage, sizeof( this->_AnalogOverlay.ErrMessage ),
                      "Fatal Analog Error - Unable to load overlay : %s",
                      this->_AnalogOverlay.Settings.Overlay );
            throw AnalogSetupException( this->_AnalogOverlay.ErrMessage );
        }
    }

    int AnalogDevice::GetCurrentReading( ) {
        this->ReadDevice( 1024 );
        if( this->CurrentReading.length() > 0 ){
            return stoi( this->CurrentReading );
        }
        else {
            return 1;
        }
    }

    short AnalogDevice::ReadDevice( size_t _BufferSize ) {
        if( !this->DeviceFile.is_open( ) ) {
            if( this->OpenDevice( ) ) {
                try {
                    getline( this->DeviceFile, this->CurrentReading );
                    this->DeviceFile.close( );
                }
                catch( ifstream::failure e ) {
                    cout << "Exception caught handling binary file : " << e.what( ) << endl;
                }
            }
            return 0;
        }
    }

    int AnalogDevice::OpenDevice( ) throw( AnalogSetupException& ) {
        try {
            this->DeviceFile.open( this->DeviceFilePath.c_str( ), ios::binary | ios::in );
            return 1;
        } catch ( exception& e ) {
            snprintf( this->_AnalogOverlay.ErrMessage, sizeof( this->_AnalogOverlay.ErrMessage ),
                      "Fatal Analog Error - Unable to create FileHandle : %s",
                      this->DeviceFilePath.c_str( ) );
            throw AnalogSetupException( this->_AnalogOverlay.ErrMessage );
        }
    }

    void AnalogDevice::SetDevicePort( AnalogPort DevicePort ) {
        this->DevicePort = DevicePort;
    }

    void AnalogDevice::SetDeviceFilePath( ) {
        ostringstream oss;
        this->DeviceFilePath = this->_AnalogOverlay.Settings.HelperPath;
        this->DeviceFilePath.append( this->_AnalogOverlay.Settings.FileType );
        oss << this->DevicePort;
        this->DeviceFilePath.append( oss.str( ) );
    }

}