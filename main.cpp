//
// Created by Michael Brookes on 12/06/2016.
//

#include "Quadro.h"

int main(){

    using namespace abIDevice;
    DJI_2212 *Motor1, *Motor2, *Motor3, *Motor4;
    Motor1 = new DJI_2212( iDeviceOverlay::PinBlocks::BLOCK_P9, iDeviceOverlay::PWMPins::PIN_42 );
    Motor2 = new DJI_2212( iDeviceOverlay::PinBlocks::BLOCK_P8, iDeviceOverlay::PWMPins::PIN_19 );
    Motor3 = new DJI_2212( iDeviceOverlay::PinBlocks::BLOCK_P9, iDeviceOverlay::PWMPins::PIN_14 );
    Motor4 = new DJI_2212( iDeviceOverlay::PinBlocks::BLOCK_P9, iDeviceOverlay::PWMPins::PIN_22 );

    Motor1->Init( );
    Motor2->Init( );
    Motor3->Init( );
    Motor4->Init( );

    using namespace abAnalog;
    LVMaxSonarEZ SonicSensor;
    SonicSensor.Start( );
    sleep( 1 );
    SonicSensor.SetMode( LVMaxSonarEZ::DeviceMode::Cm );

    using namespace abI2C;
    LSM303Accelerometer *Accelerometer;
    LSM303Magnetometer *Magnetometer;
    Accelerometer = new LSM303Accelerometer( );
    Magnetometer = new LSM303Magnetometer( );
    Accelerometer->SetPitchAndRollAverages( 50 );
    Magnetometer->SetHeadingAverages( 50 );

    while(1){
        cout << "Current Distance In Cm : " << SonicSensor.Distance( ) << endl;
        cout << "Heading = " << Magnetometer->Heading( ) << endl;
        cout << "Roll = " << Accelerometer->Roll( ) << endl;
        cout << "Pitch = " << Accelerometer->Pitch( ) << endl;
    }
}