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

#include "PWMDevice.h"

namespace abPWM {

    PWMDevice::PWMDevice( PinBlocks _block, PWMPins _pin ) throw( PWMSetupException& ) {

        this->SetBlockNum( _block );
        this->SetPinNum( _pin );

        if( this->Settings.OverlayLoaded ) {
            this->_PinOverlay = new PinOverlay( this->BlockNum, this->PinNum );

            if( this->_PinOverlay->Settings.OverlayLoaded )
                this->SetFilePaths( );
        }

    }

    void PWMDevice::ReadDevice( ValType _vt ) {
        this->SetValType( _vt );
        this->ReadDevice( 1024 );
    }

    short PWMDevice::ReadDevice( size_t _BufferSize ) {
        if( !this->PWMFile.is_open( ) ) {
            if( this->OpenDevice( ) ) {
                try {
                    getline( this->PWMFile, this->CurrentReading );
                    this->PWMFile.close( );
                }
                catch( ifstream::failure e ) {
                    cout << "Exception caught handling binary file : " << e.what( ) << endl;
                }
            }
            return 1;
        }
        else
            return -1;
    }

    void PWMDevice::InitDevice( ) throw( PWMSetupException& ) {
        if( !this->Settings.OverlayLoaded ) {
            snprintf( this->ErrMessage, sizeof( this->ErrMessage ),
                      "Fatal PWM Error - Unable to set up your PWM device : %s",
                      this->Settings.Overlay );
            throw PWMSetupException( this->ErrMessage );
        }
    }

    void PWMDevice::WriteToDevice( ValType _vt, long int _val ) throw( PWMSetupException& ) {
        this->SetValType( _vt );
        this->SetWriteVal( _val );
        this->WriteToDevice( 1024 );
    }

    int PWMDevice::WriteToDevice( size_t _BufferSize ) throw( PWMSetupException& ) {
        ofstream PWMWriteFile;
        PWMWriteFile.open( this->GetFilePath( ) );
        if( PWMWriteFile.is_open( ) ) {
            PWMWriteFile << this->Val2Write;
            PWMWriteFile.close( );
        }
    }

    int PWMDevice::OpenDevice( ) throw( PWMSetupException& ) {
        try {
            this->PWMFile.open( this->GetFilePath( ), ios::binary );
            return 1;
        } catch ( exception& e ) {
            snprintf( this->ErrMessage, sizeof( this->ErrMessage ),
                      "Fatal PWM Error - Unable to create FileHandle : %s - %s",
                      this->_PinOverlay->PinOverlayDir, e.what( ) );
            throw PWMSetupException( this->ErrMessage );
        }
    }

    long PWMDevice::Get( ValType _vt ) { return this->GetCurrentReading ( _vt ); }

    void PWMDevice::Set( ValType _vt, long _val ) { this->WriteToDevice( _vt, _val ); }

    long PWMDevice::GetCurrentReading( ValType _vt ) {
        this->ReadDevice( _vt );
        if( this->CurrentReading != "" ) {
            if( _vt == Run )
                return ( this->CurrentReading.compare( "1" ) == 0 ) ? true : false;
            else if( _vt == Power_Control ) {
                this->Power_ControlStr = this->CurrentReading;
                return 1;
            }
            else
                return stoi( this->CurrentReading );
        }
    }

    char* PWMDevice::GetFilePath( ){
        switch( this->VT ) {
            case Run : return this->RunPath;
            case Duty : return this->DutyPath;
            case Period : return this->PeriodPath;
            case Polarity : return this->PolarityPath;
            case Power_Control : return this->PowerControlPath;
            case Power_RunTime_Active : return this->PowerRunTime_ActivePath;
            case Power_RunTime_Suspended : return this->PowerRunTime_SuspendedPath;
            default: return this->DutyPath;
        }
    }

    void PWMDevice::SetFilePaths( ) {
        snprintf( this->RunPath, sizeof( this->RunPath ), "%s/%s", this->_PinOverlay->PinOverlayDir, "run" );
        snprintf( this->DutyPath, sizeof( this->DutyPath ), "%s/%s", this->_PinOverlay->PinOverlayDir, "duty" );
        snprintf( this->PeriodPath, sizeof( this->PeriodPath ), "%s/%s", this->_PinOverlay->PinOverlayDir, "period" );
        snprintf( this->PolarityPath, sizeof( this->PolarityPath ), "%s/%s", this->_PinOverlay->PinOverlayDir, "polarity" );
        snprintf( this->PowerControlPath, sizeof( this->PowerControlPath ), "%s/%s", this->_PinOverlay->PinOverlayDir, "power/control" );
        snprintf( this->PowerRunTime_ActivePath, sizeof( this->PowerRunTime_ActivePath ), "%s/%s", this->_PinOverlay->PinOverlayDir, "power/runtime_active_time" );
        snprintf( this->PowerRunTime_SuspendedPath, sizeof( this->PowerRunTime_SuspendedPath ), "%s/%s", this->_PinOverlay->PinOverlayDir, "power/runtime_suspended_time" );
    }

    void PWMDevice::SetPinNum( PWMPins _pin ) { this->PinNum = _pin; }

    void PWMDevice::SetBlockNum( PinBlocks _block ) { this->BlockNum = _block; }

    void PWMDevice::SetValType( ValType _vt ) { this->VT = _vt; }

    void PWMDevice::SetWriteVal( long _val ) { this->Val2Write = _val; }

}