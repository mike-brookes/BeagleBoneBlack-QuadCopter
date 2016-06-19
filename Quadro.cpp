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

#include "Quadro.h"

Quadro::Quadro( ) {

    Motor[ 0 ] = new DJI_2212( abIDevice::iDeviceOverlay::PinBlocks::BLOCK_P9, abIDevice::iDeviceOverlay::PWMPins::PIN_42 );
    Motor[ 0 ]->Init( );

    Motor[ 1 ] = new DJI_2212( abIDevice::iDeviceOverlay::PinBlocks::BLOCK_P8, abIDevice::iDeviceOverlay::PWMPins::PIN_19 );
    Motor[ 1 ]->Init( );

    Motor[ 2 ] = new DJI_2212( abIDevice::iDeviceOverlay::PinBlocks::BLOCK_P9, abIDevice::iDeviceOverlay::PWMPins::PIN_14 );
    Motor[ 2 ]->Init( );

    Motor[ 3 ] = new DJI_2212( abIDevice::iDeviceOverlay::PinBlocks::BLOCK_P9, abIDevice::iDeviceOverlay::PWMPins::PIN_22 );
    Motor[ 3 ]->Init( );
    //add additional motors here, specifying Block and Pin accordingly.

    SonicSensor = new LVMaxSonarEZ( );
    SonicSensor->Start( );
    SonicSensor->SetMode( LVMaxSonarEZ::DeviceMode::Cm );

    Accelerometer = new LSM303Accelerometer( );
    Magnetometer = new LSM303Magnetometer( );

    usleep( 100000 ); //wait .1 of a second for readings to be updated.

}

void Quadro::SetStartupTargets( ) {

    this->Height.TargetVal = 25.00;
    this->Height.AllowableError = 1.00;

    this->Pitch.TargetVal = 0.00;
    this->Pitch.AllowableError = 0.50;

    this->Roll.TargetVal = 0.00;
    this->Roll.AllowableError = 0.50;

    this->Heading.TargetVal = this->Magnetometer->Heading( );
    this->Heading.AllowableError = 1.00;

}

void Quadro::MaintainTargets( ) {
    //this->MaintainHeight( );
    //this->MaintainRoll( );
    this->MaintainPitch( );
    this->MaintainHeading( );
}

void Quadro::MaintainHeight( ) {
    int EMERGENCY_HEIGHT = ( this->SonicSensor->CurrentMode == this->SonicSensor->DeviceMode::Cm ) ? EMERGENCY_HEIGHT_CM : EMERGENCY_HEIGHT_INCH;
    double SS_DISTANCE = this->SonicSensor->Distance( );
    this->State = ( SS_DISTANCE < EMERGENCY_HEIGHT ) ? STATE::URGENT : STATE::NORMAL;

    if( this->ActionRequired( this->SonicSensor->DataStoredValues, this->Height ) > 0 ) {

        if( SS_DISTANCE < this->Height.TargetVal )
            SpeedUpMotors( );
        else
            SlowDownMotors( );

    }
}

void Quadro::MaintainRoll( ) {
    double ACC_ROLL = this->Accelerometer->Roll( );
    cout << "Current Roll = " << ACC_ROLL << endl << endl;
    int SPEEDUP_MOTOR_IDS[ 2 ], SLOWDOWN_MOTOR_IDS[ 2 ];
    this->State = ( ACC_ROLL < EMERGENCY_ROLL ) ? STATE::URGENT : STATE::NORMAL;
    double ActionVal = this->ActionRequired( this->Accelerometer->RollDataStoredValues, this->Roll );
    if( ActionVal != 0 ) {
        SPEEDUP_MOTOR_IDS[ 0 ] = ( ActionVal - this->Roll.TargetVal < 0 ) ? 1 : 0;
        SPEEDUP_MOTOR_IDS[ 1 ] = ( ActionVal - this->Roll.TargetVal < 0 ) ? 2 : 3;
        SLOWDOWN_MOTOR_IDS[ 0 ] = ( ActionVal - this->Roll.TargetVal < 0 ) ? 0 : 1;
        SLOWDOWN_MOTOR_IDS[ 1 ] = ( ActionVal - this->Roll.TargetVal < 0 ) ? 3 : 2;
        this->SpeedUpMotors( SPEEDUP_MOTOR_IDS );
        this->SlowDownMotors( SLOWDOWN_MOTOR_IDS );
    }
}

void Quadro::MaintainPitch( ) {
    double ACC_PITCH = this->Accelerometer->Pitch( );
    int SPEEDUP_MOTOR_IDS[ 2 ], SLOWDOWN_MOTOR_IDS[ 2 ];
    cout << "Current Pitch Val = " << ACC_PITCH << endl << endl;
    this->State = ( ACC_PITCH < EMERGENCY_ROLL ) ? STATE::URGENT : STATE::NORMAL;
    if( this->ActionRequired( this->Accelerometer->PitchDataStoredValues, this->Pitch ) != 0 ) {
        SPEEDUP_MOTOR_IDS[ 0 ] = ( ACC_PITCH - this->Pitch.TargetVal < 0 ) ? 3 : 0;
        SPEEDUP_MOTOR_IDS[ 1 ] = ( ACC_PITCH - this->Pitch.TargetVal < 0 ) ? 2 : 1;
        SLOWDOWN_MOTOR_IDS[ 0 ] = ( ACC_PITCH - this->Pitch.TargetVal < 0 ) ? 0 : 3;
        SLOWDOWN_MOTOR_IDS[ 1 ] = ( ACC_PITCH - this->Pitch.TargetVal < 0 ) ? 1 : 2;
        this->SpeedUpMotors( SPEEDUP_MOTOR_IDS );
        this->SlowDownMotors( SLOWDOWN_MOTOR_IDS );
    }
}

void Quadro::MaintainHeading( ) {

}

double Quadro::ActionRequired( double ValArray[ MAX_DATASTORE ], Target _TargetVal ) {

    double TotalVal = 0.00;

    for( int i = 0; i < MAX_DATASTORE; i++ ) {
        TotalVal += ValArray[ i ];

        if( this->ConvertDoubleToPositive( ( ValArray[ i ] - _TargetVal.TargetVal ) ) <= _TargetVal.AllowableError )
            return 0;
        else if( i == ( MAX_DATASTORE - 1 ) ) {
            return ( TotalVal / ( MAX_DATASTORE ) );
        }
    }
    return 0.00;

}

double Quadro::ConvertDoubleToPositive( double _val ) {
    if( _val < 0 ) return _val * -1;
    if( _val >= 0 ) return _val * 1;
}

void Quadro::SpeedUpMotors( int AFFECTED_MOTORS[ 2 ] ) {
    for( int i = 0; i < 2; i++ ) {
        this->Motor[ AFFECTED_MOTORS[ i ] ]->SetTargetSpeed (
                ( this->Motor[ AFFECTED_MOTORS[ i ] ]->CurrentDuty - ( DEFAULT_SPEED_STEP * this->State ) ) );
    }
}

void Quadro::SlowDownMotors( int AFFECTED_MOTORS[ 2 ] ) {
    for( int i = 0; i < 2; i++ ) {
        this->Motor[ AFFECTED_MOTORS[ i ] ]->SetTargetSpeed (
                ( this->Motor[ AFFECTED_MOTORS[ i ] ]->CurrentDuty + ( DEFAULT_SPEED_STEP * this->State ) ) );
    }
}

void Quadro::SpeedUpMotors( ) {
    for( int i = 0; i < MOTOR_COUNT; i++ )
        this->Motor[ i ]->SetTargetSpeed( ( this->Motor[ i ]->CurrentDuty - ( DEFAULT_SPEED_STEP * this->State ) ) );
}

void Quadro::SlowDownMotors( ) {
    for( int i = 0; i < MOTOR_COUNT; i++ )
        this->Motor[ i ]->SetTargetSpeed( ( this->Motor[ i ]->CurrentDuty + ( DEFAULT_SPEED_STEP * this->State ) ) );
}