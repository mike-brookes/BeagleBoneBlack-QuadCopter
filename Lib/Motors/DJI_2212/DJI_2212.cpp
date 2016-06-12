//
// Created by Michael Brookes on 12/06/2016.
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

#include "DJI_2212.h"

DJI_2212::DJI_2212( abIDevice::iDeviceOverlay::PinBlocks _block,
                    abIDevice::iDeviceOverlay::PWMPins _pin
) : Motors( _block, _pin ) {

    this->SetMaxSpeed( MAX_DUTY );
    this->SetMinSpeed( MIN_DUTY );
    this->SetSpeedStep( DEFAULT_SPEED_STEP );
    this->SetDuty( this->GetMinSpeed( ) );
    this->SetPeriod( DEFAULT_PERIOD );
    this->SetPolarity( 1 );

}

void DJI_2212::Init( ){
    this->SetPeriod( ACTIVATE_PERIOD );
    this->SetTargetSpeed( SPIN_SLOWSPEED );
    this->SetRun( 1 );
    this->Start( );
}

void DJI_2212::SetDuty( long _duty ) {
    this->CurrentDuty = _duty;
    this->Set( Duty, this->CurrentDuty );
}

void DJI_2212::SetPeriod( long _period ) {
    this->CurrentPeriod = _period;
    this->Set( Period, this->CurrentPeriod );
}

void DJI_2212::SetRun( int _run ) {
    this->CurrentRun = _run;
    this->Set( Run, this->CurrentRun );
}

void DJI_2212::SetPolarity( int _polarity ) {
    this->CurrentPolarity = _polarity;
    this->Set( Polarity, this->CurrentPolarity );
}