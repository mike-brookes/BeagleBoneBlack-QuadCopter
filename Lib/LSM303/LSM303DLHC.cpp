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

#include <bitset>
#include "./LSM303DLHC.h"

using namespace abI2C;

void LSM303DLHC::LoadRecommendedFlightSettings( ) {
    if( this->DeviceAddress == ACCEL_ADDRESS ) {
        this->PowerSettings =
                this->CommitSetting(
                        CTRL_REG1_A,
                        SET_CTRL_REG1_A(
                                ODR_1344KHZ,
                                LP_LOW_POWER_DISABLED,
                                Z_AXIS_ENABLED,
                                Y_AXIS_ENABLED,
                                X_AXIS_ENABLED
                        )
                );

        this->HighPassSettings =
                this->CommitSetting(
                        CTRL_REG2_A,
                        SET_CTRL_REG2_A(
                                HIGHPASS_MODE_NORMAL_WITH_RESET,
                                HIGHPASS_FDS_INTERNAL_BYPASSED_DISABLED,
                                HIGHPASS_FILTER_DISABLED_FOR_CLICK,
                                HIGHPASS_FILTER_DISABLED_AOI_INT2,
                                HIGHPASS_FILTER_DISABLED_AOI_INT1
                        )
                );

        this->Int1Settings =
                this->CommitSetting(
                        CTRL_REG3_A,
                        SET_CTRL_REG3_A(
                                CLICK_INTERRUPT_ON_INT1_DISABLED,
                                AOI1_INTERRUPT_ON_INT1_DISABLED,
                                AOI2_INTERRUPT_ON_INT1_DISABLED,
                                DRDY1_INTERRUPT_ON_INT1_DISABLED,
                                DRDY2_INTERRUPT_ON_INT1_DISABLED,
                                FIFO_WTM_INTERRUPT_ON_INT1_DISABLED,
                                FIFO_OVERRUN_INTERRUPT_ON_INT1_DISABLED
                        )
                );

        this->DataSettings =
                this->CommitSetting(
                        CTRL_REG4_A,
                        SET_CTRL_REG4_A(
                                BDU_UPDATE_REGISTERS_CONTINUOUSLY,
                                BLE_DATA_LSB_AT_LOWER_ADDRESS,
                                FS_SCALE_AT_PLUS_MINUS_16G,
                                HR_HI_RES_ENABLED,
                                SIM_SERIAL_INTERFACE_4_WIRE
                        )
                );


        this->MemorySettings =
                this->CommitSetting(
                        CTRL_REG5_A,
                        SET_CTRL_REG5_A(
                                BOOT_REBOOT_MEM_CONTENT_DISABLED,
                                FIFO_DISABLED,
                                LIR_INT1_NOT_LATCHED,
                                D4D_INT1_4D_DISABLED,
                                LIR_INT2_NOT_LATCHED,
                                D4D_INT2_4D_DISABLED
                        )
                );
        this->InterruptSettings =
                this->CommitSetting(
                        CTRL_REG6_A,
                        SET_CTRL6_REG_A(
                                I2_CLICK_INTERRUPT_ON_PAD2_DISABLED,
                                I2_INTERRUPT_1_DISABLED,
                                I2_INTERRUPT_2_DISABLED,
                                BOOT_I1_REBOOT_MEMORY_DISABLED,
                                P2_ACT_ACTIVE_FUNCTION_ON_PAD2_DISABLED,
                                H_LACTIVE_INTERRUPT_ACTIVE_HIGH
                        )
                );

        this->FIFOSettings =
                this->CommitSetting(
                        FIFO_CTRL_REG_A,
                        SET_FIFO_CTRL_REG_A(
                                FM_BYPASS_MODE,
                                TR_TRIGGER_LINKED_TO_INTERRUPT2
                        )
                );

        this->Interrupt1CFGSettings =
                this->CommitSetting(
                        INT1_CFG_A,
                        SET_INT1_CFG_A(
                                AOI_OR_COMBINATION,
                                ZHIE_INTERRUPT_ON_Z_HIGH_DISABLED,
                                ZLIE_INTERRUPT_ON_Z_LOW_DISABLED,
                                YHIE_INTERRUPT_ON_Y_HIGH_DISABLED,
                                YLIE_INTERRUPT_ON_Y_LOW_DISABLED,
                                XHIE_INTERRUPT_ON_X_HIGH_DISABLED,
                                XLIE_INTERRUPT_ON_X_LOW_DISABLED
                        )
                );

        this->Interrupt2CFGSettings =
                this->CommitSetting(
                        INT2_CFG_A,
                        SET_INT2_CFG_A(
                                AOI_OR_COMBINATION,
                                ZHIE_INTERRUPT_ON_Z_HIGH_DISABLED,
                                ZLIE_INTERRUPT_ON_Z_LOW_DISABLED,
                                YHIE_INTERRUPT_ON_Y_HIGH_DISABLED,
                                YLIE_INTERRUPT_ON_Y_LOW_DISABLED,
                                XHIE_INTERRUPT_ON_X_HIGH_DISABLED,
                                XLIE_INTERRUPT_ON_X_LOW_DISABLED
                        )
                );

        this->ClickCFGSettings =
                this->CommitSetting(
                        CLICK_CFG_A,
                        SET_CLICK_CFG_A(
                                ZD_DOUBLECLICK_ON_Z_AXIS_DISABLED,
                                ZS_SINGLECLICK_ON_Z_AXIS_DISABLED,
                                YD_DOUBLECLICK_ON_Y_AXIS_DISABLED,
                                YS_SINGLECLICK_ON_Y_AXIS_DISABLED,
                                XD_DOUBLECLICK_ON_X_AXIS_DISABLED,
                                XS_SINGLECLICK_ON_X_AXIS_DISABLED
                        )
                );

        this->ClickSRCSettings =
                this->CommitSetting(
                        CLICK_SRC_A,
                        SET_CLICK_SRC_A(
                                DCLICK_DOUBLE_CLICK_DETECTION_DISABLED,
                                SCLICK_SINGLE_CLICK_DETECTION_DISABLED,
                                SIGN_POSITIVE_DETECTION
                        )
                );
    }
    else if( this->DeviceAddress == MAG_ADDRESS ) {

        this->CRARegMSettings =
                this->CommitSetting(
                        CRA_REG_M,
                        SET_CRA_REG_M(
                                TEMP_ENABLED,
                                DO2_220Hz
                        )
                );

        this->MRRegMSettings =
                this->CommitSetting(
                        MR_REG_M,
                        SET_MR_REG_M(
                                MD_CONTINUOUS_CONVERSION_MODE
                        )
                );
    }

}

LSM303DLHC::LSM303DLHC( ) {

}

void LSM303DLHC::Init( ) {
    if( this->DeviceAddress == ACCEL_ADDRESS )
        this->GetOutputDataRate( );
    else if( this->DeviceAddress == MAG_ADDRESS )
        this->GetDataOutputRate( );

    this->SetDataTimer( );
    this->StartRecording( );
}

uint8_t LSM303DLHC::CommitSetting( uint8_t RegisterAddress, uint8_t RegisterValue ){
    this->SetRegisterAddress( RegisterAddress );
    this->SetRegisterValue( RegisterValue );
    this->WriteToDevice( 2 );
    return RegisterValue;
}

short LSM303DLHC::GetX( ) {
    return ( this->GetValueFromRegister( ( unsigned char ) ( ( this->DeviceAddress == ACCEL_ADDRESS ) ? OUT_X_H_A : OUT_X_H_M ) ) << 8 ) |
           this->GetValueFromRegister( ( unsigned char ) ( ( this->DeviceAddress == ACCEL_ADDRESS ) ? OUT_X_L_A : OUT_X_L_M ) );
}

short LSM303DLHC::GetY( ) {
    return (this->GetValueFromRegister( ( unsigned char ) ( ( this->DeviceAddress == ACCEL_ADDRESS ) ? OUT_Y_H_A : OUT_Y_H_M ) ) << 8 ) |
           this->GetValueFromRegister( ( unsigned char ) ( ( this->DeviceAddress == ACCEL_ADDRESS ) ? OUT_Y_L_A : OUT_Y_L_M ) );
}

short LSM303DLHC::GetZ( ) {
    return (this->GetValueFromRegister( ( unsigned char ) ( ( this->DeviceAddress == ACCEL_ADDRESS ) ? OUT_Z_H_A : OUT_Z_H_M ) ) << 8 ) |
           this->GetValueFromRegister( ( unsigned char ) ( ( this->DeviceAddress == ACCEL_ADDRESS ) ? OUT_Z_L_A : OUT_Z_L_M ) );

}

void LSM303DLHC::SetX( ) { this->X = GetX( ); }

void LSM303DLHC::SetY( ) { this->Y = GetY( ); }

void LSM303DLHC::SetZ( ) { this->Z = GetZ( ); }

//bits required `0000`0000 >> 4 = 0000`0000` & 15 (00001111) = val of the 4 bits
uint8_t LSM303DLHC::GetOutputDataRate( ) { return uint8_t( ( this->GetPowerSettings( ) >> 4 ) & 15 ); }

//bits required 0000000`0` & 1 (00000001) = val of the 1 bit
bool LSM303DLHC::XAxisIsEnabled( ) { return uint8_t( this->GetPowerSettings( ) & 1 ); }

//bits required 000000`0`0 >> 1 = 0000000`0` & 1 (00000001) = val of the 1 bit
bool LSM303DLHC::YAxisIsEnabled( ) { return uint8_t( ( this->GetPowerSettings( ) >> 1 ) & 1 ); }

//bits required 00000`0`00 >> 2 = 0000000`0` & 1 (00000001) = val of the 1 bit
bool LSM303DLHC::ZAxisIsEnabled( ) { return uint8_t( ( this->GetPowerSettings( ) >> 2 ) & 1 ); }

//bits required 000`000`00 >> 2 = 00000`000` & 7 (00000111) = val of the 3 bits
uint8_t LSM303DLHC::GetDataOutputRate( ) { return uint8_t ( ( this->GetCRARegMSettings( ) >> 2 ) & 7 ); }

//bits required 000000`00` & 3 (00000011) = val of the 2 bits
uint8_t LSM303DLHC::MagnetometerIsEnabled( ) { return uint8_t ( ( this->GetMRRegMSettings( ) ) & 3 ); }

void LSM303DLHC::SetDataTimer( ) {
    ( this->DeviceAddress == ACCEL_ADDRESS ) ? this->SetAccelerometerTimerBasedOnODR( ) : SetMagnetometerTimerBasedOnDO( );
}

void LSM303DLHC::SetAccelerometerTimerBasedOnODR( ) { //ODR = Output Data Rate
    switch( this->GetOutputDataRate( ) << 4 ) {
        case ODR_10HZ    : this->DataTimer = 1000000 / 10; break; //1Hz = 1000000 Micro Seconds
        case ODR_25HZ    : this->DataTimer = 1000000 / 25; break;
        case ODR_50HZ    : this->DataTimer = 1000000 / 50; break;
        case ODR_100HZ   : this->DataTimer = 1000000 / 100; break;
        case ODR_200HZ   : this->DataTimer = 1000000 / 200; break;
        case ODR_400HZ   : this->DataTimer = 1000000 / 400; break;
        case ODR_1344KHZ : this->DataTimer = 800; break;
        case POWER_OFF   : this->DataTimer = 0; break;
        default : this->DataTimer = 1000000;
    }
}

void LSM303DLHC::SetMagnetometerTimerBasedOnDO( ) { //DO = Data Output
    switch( this->GetDataOutputRate( ) << 2 ) {
        case DO2_0_75Hz : this->DataTimer = 1333333; break; //1.5Hz = 1333333 Micro Seconds
        case DO2_1_5Hz  : this->DataTimer = (unsigned int)(1000000 / 1.5); break;
        case DO2_3_0Hz  : this->DataTimer = 1000000 / 3; break;
        case DO2_7_5Hz  : this->DataTimer = (unsigned int)(1000000 / 7.5); break;
        case DO2_15Hz   : this->DataTimer = 1000000 / 15; break;
        case DO2_30Hz   : this->DataTimer = 1000000 / 30; break;
        case DO2_75Hz   : this->DataTimer = 1000000 / 75; break;
        case DO2_220Hz  : this->DataTimer = 1000000 / 220; break;
        default : this->DataTimer = 1333333;
    }
}

void* LSM303DLHC::RecordAccelerometerValues( void *_LSM303 ) {
    LSM303DLHC* LSM303 = ( LSM303DLHC* ) _LSM303;
    while( LSM303->DataTimer ) { //DataTimer will be 0 if the LSM303 is powered off.
        if( LSM303->XAxisIsEnabled( ) ) LSM303->SetX( );
        if( LSM303->YAxisIsEnabled( ) ) LSM303->SetY( );
        if( LSM303->ZAxisIsEnabled( ) ) LSM303->SetZ( );
        usleep( LSM303->DataTimer );
    }
    return 0;
}

void* LSM303DLHC::RecordMagnetometerValues( void *_LSM303 ) {
    LSM303DLHC* LSM303 = ( LSM303DLHC* ) _LSM303;
    while( LSM303->MagnetometerIsEnabled( ) == 0 ) { //"1 = Singe Conversion Mode", "Sleep Mode" with values of 2 or 3
        LSM303->SetX( );
        LSM303->SetY( );
        LSM303->SetZ( );
        usleep( LSM303->DataTimer );
    }
    return 0;
}

void LSM303DLHC::StartRecording( ) {
    if( this->DeviceAddress == ACCEL_ADDRESS )
        pthread_create( &this->LSM303AccelThread, NULL, LSM303DLHC::RecordAccelerometerValues, this );
    else
        pthread_create( &this->LSM303MagThread, NULL, LSM303DLHC::RecordMagnetometerValues, this );
}