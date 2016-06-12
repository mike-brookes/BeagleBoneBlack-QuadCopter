//
// Created by Michael Brookes on 05/05/2016.
//

#include "LSM303Accelerometer.h"

LSM303Accelerometer::LSM303Accelerometer( unsigned char _DeviceAddress, int _BusId ) {
    this->SetDeviceAddress( _DeviceAddress );
    this->SetBusId( _BusId );
    this->InitDevice( );
    this->LoadRecommendedFlightSettings( );
    this->Init( );
    this->StartRecordingPitchAndRoll( );
}

double LSM303Accelerometer::Roll( ) {
    return ( ( atan2 ( ( double )this->X, sqrt( double( this->Y * this->Y + this->Z * this->Z ) ) ) * 180.0 ) / M_PI );
    //return (( atan2 ( ( double ) this->X, sqrt( ( double ) this->Y * ( double ) this->Y + ( double ) this->Z * ( double ) this->Z ) ) * 180.0 ) / M_PI);
}

double LSM303Accelerometer::Pitch( ) {
    return ( atan2 ( ( double )this->Y, ( double )this->Z ) * 180.0 ) / M_PI;
    //return ( atan2 ( ( double ) this->Y, ( double ) this->Z ) * 180.0 ) / M_PI;
}

void LSM303Accelerometer::SetPitchAndRollAverages( int iterations ) {
    int i = 0, total_roll = 0, total_pitch = 0;
    while (i < iterations) {
        total_roll += this->Roll( );
        total_pitch += this->Pitch( );
        usleep( this->DataTimer );
        i++;
    }
    this->avgRoll = total_roll / iterations;
    this->avgPitch = total_pitch / iterations;
}

void LSM303Accelerometer::AddToPitchAndRollDataStore( ) {
    for( int i = 0; i < ( MAX_DATASTORE - 1 ); i++ ) {
        int NextIndex = (i + 1);
        this->PitchDataStoredValues[ i ] = this->PitchDataStoredValues[ NextIndex ];
        this->RollDataStoredValues[ i ] = this->RollDataStoredValues[ NextIndex ];
    }
    this->PitchDataStoredValues[ ( MAX_DATASTORE - 1 ) ] = this->Pitch( );
    this->RollDataStoredValues[ ( MAX_DATASTORE - 1 ) ] = this->Roll( );
}

void LSM303Accelerometer::StartRecordingPitchAndRoll( ) {
    pthread_create( &this->LSM303UpdateValuesThread, NULL, LSM303Accelerometer::GetAccelerometerValues, this );
}

void* LSM303Accelerometer::GetAccelerometerValues(  void *_ACCEL  ){
    LSM303Accelerometer* accel = (LSM303Accelerometer*)_ACCEL;
    while( 1 ) {
        accel->AddToPitchAndRollDataStore( );
        usleep( accel->DataTimer );
    }
}