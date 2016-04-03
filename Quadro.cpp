/*
 * BBBQuadro.cpp
 *
 *  Created on: 6 Dec 2015
 *      Author: michaelbrookes
 */

#include "include/Quadro.h"

Quadro::Quadro( ) {

}

Quadro::~Quadro( ) {
    cout << "--####---Destructing---###--" << endl;

    for( int i = 0; i < PROPELLER_COUNT; i++ )
        propellerMotor[ i ].PWM_SetRunVal( BBBPWMDevice::PWM_RunValues::OFF );
}

int Quadro::AddI2CDevices( ) {
    return 1;
}

int Quadro::AddAnalogDevices( ) {
    for( int i = 0; i < ANALOG_SENSOR_COUNT; i++ ) {
        try {
            if( AnalogSensor[ i ].Analog_SetPort( Config.Analog_Sensor[ i ].Port ) != 0 ) {
                cerr << "Error adding Analog Device (" << Config.Analog_Sensor[ i ].Name << ") On Port #" <<
                Config.Analog_Sensor[ i ].Port << endl;
                return -1;
            }
            else {
                AnalogSensor[ i ].Analog_SetType( BBBAnalogDevice::SONIC );
            }
        }
        catch( exception &e ) {
            cerr << "Error adding Analog Device (" << Config.Analog_Sensor[ i ].Name << ") On Port #" <<
            Config.Analog_Sensor[ i ].Port << " | Error = " << e.what( ) << endl;
            return -1;
        }
    }
    return 1;
}

int Quadro::AddMotors( ) {
    for( int i = 0; i < PROPELLER_COUNT; i++ ) {
        propellerMotor[ i ].PWM_SetBlockNum( Config.Motors[ i ].Block );
        propellerMotor[ i ].PWM_SetPinNum( Config.Motors[ i ].Pin );
        propellerMotor[ i ].PWM_SetTargetSpeed( Config.Motors[ i ].TargetSpeed );
        propellerMotor[ i ].PWM_Init( );
        propellerMotor[ i ].PWM_SetPeriodVal( BBBPWMDevice::PWM_PeriodValues::STARTUP );
        propellerMotor[ i ].PWM_SetRunVal( BBBPWMDevice::PWM_RunValues::ON );
    }
    sleep(1);
    for( int i = 0; i < PROPELLER_COUNT; i++ ){
        propellerMotor[ i ].PWM_SetTargetSpeed( MOTOR_SLOWSPEED );
        propellerMotor[ i ].PWM_SetPeriodVal( BBBPWMDevice::PWM_PeriodValues::ACTIVE );
    }
    return 1;
}

void Quadro::SetAllMotorsSpeed( int motor_speed ) {
    for( int i = 0; i < PROPELLER_COUNT; i++ ) {
        this->SetMotorSpeed( i, motor_speed );
    }
}

void Quadro::SetMotorSpeed( int motor_index, int motor_speed ) {
    Config.Motors[ motor_index ].TargetSpeed = motor_speed;
    propellerMotor[ motor_index ].PWM_SetTargetSpeed( motor_speed );
}

void Quadro::SetAllMotorsPower( BBBPWMDevice::PWM_RunValues val ) {
    for( int i = 0; i < PROPELLER_COUNT; i++ ) {
        Config.Motors[ i ].RunState = val;
        propellerMotor[ i ].PWM_SetRunVal( Config.Motors[ i ].RunState );
    }
}

void Quadro::SetMotorPower( int motor_index, BBBPWMDevice::PWM_RunValues val ) {
    Config.Motors[ motor_index ].RunState = val;
    propellerMotor[ motor_index ].PWM_SetRunVal( Config.Motors[ motor_index ].RunState );
}

void Quadro::SetDefaultTargetValuesBasedOnStaticAverages( ) {
    Config.General.TargetValues.Pitch = 0;//Accelerometer.avgPitch;
    Config.General.TargetValues.Roll = 0;//Accelerometer.avgRoll;
    Config.General.TargetValues.GyroX = 0;//Gyroscope.avgX;
    Config.General.TargetValues.GyroY = 0;//Gyroscope.avgY;
    Config.General.TargetValues.GyroZ = 0;//Gyroscope.avgZ;
    Config.General.TargetValues.Heading = Magnetometer.avgHeading;
    Config.General.TargetValues.Altitude = AnalogSensor[ 0 ].avgReading;
}

int Quadro::SpeedUpMotor( int motor_index ) {
    propellerMotor[ motor_index ].PWM_TargetSpeed -= MOTOR_SPEED_OFFSET;
    if( propellerMotor[ motor_index ].PWM_TargetSpeed < 420000 )
        propellerMotor[ motor_index ].PWM_TargetSpeed = 420000;
    if( propellerMotor[ motor_index ].PWM_TargetSpeed > MIN_DUTY )
        propellerMotor[ motor_index ].PWM_TargetSpeed = MIN_DUTY;
    return propellerMotor[ motor_index ].PWM_TargetSpeed;
}

int Quadro::SlowDownMotor( int motor_index ) {
    propellerMotor[ motor_index ].PWM_TargetSpeed += MOTOR_SPEED_OFFSET;
    if( propellerMotor[ motor_index ].PWM_TargetSpeed < 420000 )
        propellerMotor[ motor_index ].PWM_TargetSpeed = 420000;
    if( propellerMotor[ motor_index ].PWM_TargetSpeed > MIN_DUTY )
        propellerMotor[ motor_index ].PWM_TargetSpeed = MIN_DUTY;
    return propellerMotor[ motor_index ].PWM_TargetSpeed;
}

void Quadro::ControlPitch( double DataDiff ) {
                                                                                                                        /*   xxxxx                   xxxxx                      */
    if( this->Accelerometer.Pitch - Config.General.TargetValues.Pitch  > 0 ) {                                          /*   x 3 x                   x 2 x                      */
        propellerMotor[ 0 ].PWM_SetTargetSpeed( this->SlowDownMotor( 3 ) );                                //FL         /*   xxxxx                   xxxxx                      */
        propellerMotor[ 1 ].PWM_SetTargetSpeed( this->SlowDownMotor( 2 ) );                                //FR         /*     \\                     //                        */
        propellerMotor[ 2 ].PWM_SetTargetSpeed( this->SpeedUpMotor( 1 ) );                                 //BL         /*      \\ (white arm)       // (white arm)             */
        propellerMotor[ 3 ].PWM_SetTargetSpeed( this->SpeedUpMotor( 0 ) );                                 //BR         /*       \\                 //                          */
    }                                                                                                                   /*        \\               //     -                     */
    else {                                                                                                              /*         \\    BACK     //       <--. _               */
        propellerMotor[ 0 ].PWM_SetTargetSpeed( this->SpeedUpMotor( 3 ) );                                 //FL         /*           -------------               `.             */
        propellerMotor[ 1 ].PWM_SetTargetSpeed( this->SpeedUpMotor( 2 ) );                                 //FR         /*          |L          R |             P  \            */
        propellerMotor[ 2 ].PWM_SetTargetSpeed( this->SlowDownMotor( 1 ) );                                //BL         /*          |E          I |             I   |           */
        propellerMotor[ 3 ].PWM_SetTargetSpeed( this->SlowDownMotor( 0 ) );                                //BR         /*          |F          G |             T   |           */
    }                                                                                                                   /*          |T          H |             C   |           */
}                                                                                                                       /*          |           T |             H  /            */
                                                                                                                        /*           -------------              _.'             */
void Quadro::ControlRoll( double DataDiff ) {                                                                           /*         //    FRONT    \\       <--'                 */
                                                                                                                        /*        //               \\     +                     */
    if( this->Accelerometer.Roll - Config.General.TargetValues.Roll  > 0 ) {                                            /*       //                 \\                          */
        propellerMotor[ 0 ].PWM_SetTargetSpeed( this->SpeedUpMotor( 0 ) );                                  //FL        /*      // (red arm)         \\ (red arm)               */
        propellerMotor[ 1 ].PWM_SetTargetSpeed( this->SlowDownMotor( 1 ) );                                 //FR        /*     //                     \\                        */
        propellerMotor[ 2 ].PWM_SetTargetSpeed( this->SlowDownMotor( 2 ) );                                 //BL        /*   xxxxx                   xxxxx                      */
        propellerMotor[ 3 ].PWM_SetTargetSpeed( this->SpeedUpMotor( 3 ) );                                  //BR        /*   x 0 x                   x 1 x                      */
    }                                                                                                                   /*   xxxxx                   xxxxx                      */
    else {
        propellerMotor[ 0 ].PWM_SetTargetSpeed( this->SlowDownMotor( 0 ) );                                 //FL        /*             _.-""""-._                               */
        propellerMotor[ 1 ].PWM_SetTargetSpeed( this->SpeedUpMotor( 1 ) );                                  //FR        /*           .'   Roll   `.                             */
        propellerMotor[ 2 ].PWM_SetTargetSpeed( this->SpeedUpMotor( 2 ) );                                  //BL        /*          /              \                            */
        propellerMotor[ 3 ].PWM_SetTargetSpeed( this->SlowDownMotor( 3 ) );                                 //BR        /*         |                |                           */
    }                                                                                                                   /*       + \/               \/ -                        */
}

void Quadro::ControlYaw( double DataDiff ) {

}

void Quadro::CheckSensorsForSense( ) {
    int DataDiffAsInt;
    double DataDiffAsDouble;

    DataDiffAsDouble = AnalyseData( this->Accelerometer.PitchDataStoredValues, Config.General.TargetValues.Pitch,
                                  Config.General.AllowedErrorValues.dPitch );

    if( DataDiffAsDouble > 0 )
        this->ControlPitch( DataDiffAsDouble );

    DataDiffAsDouble = AnalyseData( this->Accelerometer.RollDataStoredValues, Config.General.TargetValues.Roll,
                                  Config.General.AllowedErrorValues.dRoll );

    if( DataDiffAsDouble > 0 )
        this->ControlRoll( DataDiffAsDouble );

    DataDiffAsDouble = AnalyseData( this->Magnetometer.HeadingDataStoredValues, Config.General.TargetValues.Heading,
                                  Config.General.AllowedErrorValues.dHeading );

    if( DataDiffAsDouble > 0 )
        cout << "Heading value has changed by " << DataDiffAsDouble << "!" << endl;

    DataDiffAsInt = AnalyseData( this->Gyroscope.GyroXDataStoredValues, Config.General.TargetValues.GyroX,
                                  Config.General.AllowedErrorValues.dGyroX );
    if( DataDiffAsInt > 0 )
        cout << "GyroX value has changed by " << DataDiffAsInt << "!" << endl;

    DataDiffAsInt = AnalyseData( this->Gyroscope.GyroYDataStoredValues, Config.General.TargetValues.GyroY,
                                  Config.General.AllowedErrorValues.dGyroY );

    if( DataDiffAsInt > 0 )
        cout << "GyroY value has changed by " << DataDiffAsInt << "!" << endl;

    DataDiffAsInt = AnalyseData( this->Gyroscope.GyroZDataStoredValues, Config.General.TargetValues.GyroZ,
                                  Config.General.AllowedErrorValues.dGyroZ );

    if( DataDiffAsInt > 0 )
        cout << "GyroZ value has changed by " << DataDiffAsInt << "!" << endl;

    DataDiffAsInt = AnalyseData( this->AnalogSensor[ 0 ].DataStoredValues, Config.General.TargetValues.Altitude,
                                  Config.General.AllowedErrorValues.dAltitude );

    if( DataDiffAsInt > 0 )
        cout << "Altitude value has changed by " << DataDiffAsDouble << "!" << endl;
}
