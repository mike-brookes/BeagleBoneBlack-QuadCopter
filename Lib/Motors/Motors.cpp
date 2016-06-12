// Created by Michael Brookes on 06/06/2016.
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

#include "Motors.h"

namespace abPWM {

    Motors::Motors(
        abIDevice::iDeviceOverlay::PinBlocks _block,
        abIDevice::iDeviceOverlay::PWMPins _pin
    ) : PWMDevice( _block, _pin ) {
        this->TargetSpeed = this->GetMinSpeed( );
    };

    void Motors::SetTargetSpeed( long _TargetSpeed ) throw( long ){
        this->TargetSpeed = _TargetSpeed;
        try{
            if( this->TargetSpeed < this->GetMaxSpeed( ) )
                throw ( this->GetMaxSpeed( ) );
            else if( this->TargetSpeed > this->GetMinSpeed( ) )
                throw ( this->GetMinSpeed( ) );
        }
        catch( long &e ) {
            this->SetTargetSpeed( e );
        }
    }

    void Motors::IncreaseSpeed( unsigned short _SpeedMod ) {
        this->CurrentDuty -= _SpeedMod;
        this->Set( Duty, ( this->CurrentDuty ) );
    }

    void Motors::DecreaseSpeed( unsigned short _SpeedMod ) {
        this->CurrentDuty += _SpeedMod;
        this->Set( Duty, ( this->CurrentDuty ) );
    }

    void Motors::ReversePolarity( ) {
        this->CurrentPolarity = ( this->CurrentPolarity == polarity::Positive ) ? polarity::Negative : polarity::Positive;
        this->Set( Polarity,  this->CurrentPolarity);
    }

    void Motors::SetStatus( status _status ){
        this->Status = _status;
        this->Set( Run, ( this->Status != 3 ) ? _status : 0 );
    }

    void *Motors::MaintainTargetSpeed( void *_inst ) {
        Motors* MotorInst = (Motors*)_inst;
        cout << "Thread : MotorInst -> Run == " << MotorInst->CurrentRun << endl;
        while( MotorInst->CurrentRun == status::On ) {
            if( MotorInst->CurrentDuty > MotorInst->TargetSpeed )
                MotorInst->IncreaseSpeed( );
            else
                MotorInst->DecreaseSpeed( );
        }
        MotorInst->Stop( );
    }

    void Motors::Start( ) {
        if( this->Status == status::Off ) {
            this->ThreadRet = pthread_create( &this->MotorSpeedThread, NULL, Motors::MaintainTargetSpeed, this );

            if( this->ThreadRet == 0 )
                this->SetStatus( status::On );
            else {
                this->SetStatus( status::Error );
                if( this->ThreadRet == EAGAIN )
                    throw ( "Unable to create thread : Resource Limit Reached." );
                else
                    throw ( "Unable to create thread : Unknown Error Occurred." );
            }
        }
    }

    void Motors::Stop( ) {
        cout << "Stopping Motor" << endl;
        if( this->Status != status::Off ) {
            this->SetStatus( status::Off );
            pthread_exit( &this->MotorSpeedThread );
        }
    }

    long Motors::GetMaxSpeed( ) {
        return this->MaxSpeed;
    }

    long Motors::GetMinSpeed( ) {
        return this->MinSpeed;
    }

    int Motors::GetSpeedStep( ) {
        return this->SpeedStep;
    }

    void Motors::SetMinSpeed( long _MinSpeed ) {
        this->MinSpeed = _MinSpeed;
    }

    void Motors::SetMaxSpeed( long _MaxSpeed ) {
        this->MaxSpeed = _MaxSpeed;
    }

    void Motors::SetSpeedStep( int _SpeedStep ) {
        this->SpeedStep = _SpeedStep;
    }
}