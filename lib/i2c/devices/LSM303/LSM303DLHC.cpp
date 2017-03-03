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

#include "./LSM303DLHC.h"

using namespace quadro::i2c;

void LSM303DLHC::loadRecommendedFlightSettings()
{
    if ( this->deviceAddress == ACCEL_ADDRESS ) {
        this->powerSettings =
                this->commitSetting(
                        CTRL_REG1_A,
                        SET_CTRL_REG1_A(
                                ODR_1344KHZ,
                                LP_LOW_POWER_DISABLED,
                                Z_AXIS_ENABLED,
                                Y_AXIS_ENABLED,
                                X_AXIS_ENABLED
                        )
                );

        this->highPassSettings =
                this->commitSetting(
                        CTRL_REG2_A,
                        SET_CTRL_REG2_A (
                                HIGHPASS_MODE_NORMAL_WITH_RESET,
                                HIGHPASS_FDS_INTERNAL_BYPASSED_DISABLED,
                                HIGHPASS_FILTER_DISABLED_FOR_CLICK,
                                HIGHPASS_FILTER_DISABLED_AOI_INT2,
                                HIGHPASS_FILTER_DISABLED_AOI_INT1
                        )
                );

        this->int1Settings =
                this->commitSetting(
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

        this->dataSettings =
                this->commitSetting(
                        CTRL_REG4_A,
                        SET_CTRL_REG4_A(
                                BDU_UPDATE_REGISTERS_CONTINUOUSLY,
                                BLE_DATA_LSB_AT_LOWER_ADDRESS,
                                FS_SCALE_AT_PLUS_MINUS_16G,
                                HR_HI_RES_ENABLED,
                                SIM_SERIAL_INTERFACE_4_WIRE
                        )
                );

        this->memorySettings =
                this->commitSetting(
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
        this->interruptSettings =
                this->commitSetting(
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
                this->commitSetting(
                        FIFO_CTRL_REG_A,
                        SET_FIFO_CTRL_REG_A(
                                FM_BYPASS_MODE,
                                TR_TRIGGER_LINKED_TO_INTERRUPT2
                        )
                );

        this->interrupt1CFGSettings =
                this->commitSetting(
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

        this->interrupt2CFGSettings =
                this->commitSetting(
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

        this->clickCFGSettings =
                this->commitSetting(
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

        this->clickSRCSettings =
                this->commitSetting(
                        CLICK_SRC_A,
                        SET_CLICK_SRC_A(
                                DCLICK_DOUBLE_CLICK_DETECTION_DISABLED,
                                SCLICK_SINGLE_CLICK_DETECTION_DISABLED,
                                SIGN_POSITIVE_DETECTION
                        )
                );
    }
    else if ( this->deviceAddress == MAG_ADDRESS ) {

        this->CRARegMSettings =
                this->commitSetting(
                        CRA_REG_M,
                        SET_CRA_REG_M(
                                TEMP_ENABLED,
                                DO2_220Hz
                        )
                );

        this->MRRegMSettings =
                this->commitSetting(
                        MR_REG_M,
                        SET_MR_REG_M(
                                MD_CONTINUOUS_CONVERSION_MODE
                        )
                );
    }

}

LSM303DLHC::LSM303DLHC()
{

}

void LSM303DLHC::init()
{
    if ( this->deviceAddress == ACCEL_ADDRESS )
        this->getOutputDataRate();
    else if ( this->deviceAddress == MAG_ADDRESS )
        this->getDataOutputRate();

    this->setDataTimer();
    this->startRecording();
}

uint8_t LSM303DLHC::commitSetting( uint8_t registerAddress, uint8_t registerValue )
{
    this->setRegisterAddress( registerAddress );
    this->setRegisterValue( registerValue );
    this->writeToDevice( 2 );
    return registerValue;
}

short LSM303DLHC::getX()
{
    return ( this->getValueFromRegister(
            ( unsigned char ) (( this->deviceAddress == ACCEL_ADDRESS ) ? OUT_X_H_A : OUT_X_H_M )) << 8 ) |
            this->getValueFromRegister(
                    ( unsigned char ) (( this->deviceAddress == ACCEL_ADDRESS ) ? OUT_X_L_A : OUT_X_L_M ));
}

short LSM303DLHC::getY()
{
    return ( this->getValueFromRegister(
            ( unsigned char ) (( this->deviceAddress == ACCEL_ADDRESS ) ? OUT_Y_H_A : OUT_Y_H_M )) << 8 ) |
            this->getValueFromRegister(
                    ( unsigned char ) (( this->deviceAddress == ACCEL_ADDRESS ) ? OUT_Y_L_A : OUT_Y_L_M ));
}

short LSM303DLHC::getZ()
{
    return ( this->getValueFromRegister(
            ( unsigned char ) (( this->deviceAddress == ACCEL_ADDRESS ) ? OUT_Z_H_A : OUT_Z_H_M )) << 8 ) |
            this->getValueFromRegister(
                    ( unsigned char ) (( this->deviceAddress == ACCEL_ADDRESS ) ? OUT_Z_L_A : OUT_Z_L_M ));

}

void LSM303DLHC::setX() { this->x = getX(); }

void LSM303DLHC::setY() { this->y = getY(); }

void LSM303DLHC::setZ() { this->z = getZ(); }

//bits required `0000`0000 >> 4 = 0000`0000` & 15 (00001111) = val of the 4 bits
uint8_t LSM303DLHC::getOutputDataRate() { return uint8_t(( this->getPowerSettings() >> 4 ) & 15 ); }

//bits required 0000000`0` & 1 (00000001) = val of the 1 bit
bool LSM303DLHC::XAxisIsEnabled() { return uint8_t( this->getPowerSettings() & 1 ); }

//bits required 000000`0`0 >> 1 = 0000000`0` & 1 (00000001) = val of the 1 bit
bool LSM303DLHC::YAxisIsEnabled() { return uint8_t(( this->getPowerSettings() >> 1 ) & 1 ); }

//bits required 00000`0`00 >> 2 = 0000000`0` & 1 (00000001) = val of the 1 bit
bool LSM303DLHC::ZAxisIsEnabled() { return uint8_t(( this->getPowerSettings() >> 2 ) & 1 ); }

//bits required 000`000`00 >> 2 = 00000`000` & 7 (00000111) = val of the 3 bits
uint8_t LSM303DLHC::getDataOutputRate() { return uint8_t(( this->getCRARegMSettings() >> 2 ) & 7 ); }

//bits required 000000`00` & 3 (00000011) = val of the 2 bits
uint8_t LSM303DLHC::magnetometerIsEnabled() { return uint8_t(( this->getMRRegMSettings()) & 3 ); }

void LSM303DLHC::setDataTimer()
{
    ( this->deviceAddress == ACCEL_ADDRESS ) ? this->setAccelerometerTimerBasedOnODR()
                                             : setMagnetometerTimerBasedOnDO();
}

void LSM303DLHC::setAccelerometerTimerBasedOnODR()
{ //ODR = Output Data Rate
    switch ( this->getOutputDataRate() << 4 ) {
    case ODR_10HZ    :
        this->dataTimer = 1000000 / 10;
        break; //1Hz = 1000000 Micro Seconds
    case ODR_25HZ    :
        this->dataTimer = 1000000 / 25;
        break;
    case ODR_50HZ    :
        this->dataTimer = 1000000 / 50;
        break;
    case ODR_100HZ   :
        this->dataTimer = 1000000 / 100;
        break;
    case ODR_200HZ   :
        this->dataTimer = 1000000 / 200;
        break;
    case ODR_400HZ   :
        this->dataTimer = 1000000 / 400;
        break;
    case ODR_1344KHZ :
        this->dataTimer = 800;
        break;
    case POWER_OFF   :
        this->dataTimer = 0;
        break;
    default :
        this->dataTimer = 1000000;
    }
}

void LSM303DLHC::setMagnetometerTimerBasedOnDO()
{ //DO = Data Output
    switch ( this->getDataOutputRate() << 2 ) {
    case DO2_0_75Hz :
        this->dataTimer = 1333333;
        break; //1.5Hz = 1333333 Micro Seconds
    case DO2_1_5Hz  :
        this->dataTimer = ( unsigned int ) ( 1000000 / 1.5 );
        break;
    case DO2_3_0Hz  :
        this->dataTimer = 1000000 / 3;
        break;
    case DO2_7_5Hz  :
        this->dataTimer = ( unsigned int ) ( 1000000 / 7.5 );
        break;
    case DO2_15Hz   :
        this->dataTimer = 1000000 / 15;
        break;
    case DO2_30Hz   :
        this->dataTimer = 1000000 / 30;
        break;
    case DO2_75Hz   :
        this->dataTimer = 1000000 / 75;
        break;
    case DO2_220Hz  :
        this->dataTimer = 1000000 / 220;
        break;
    default :
        this->dataTimer = 1333333;
    }
}

void* LSM303DLHC::recordAccelerometerValues( void* _LSM303 )
{
    LSM303DLHC* LSM303 = ( LSM303DLHC* ) _LSM303;
    while ( LSM303->dataTimer ) { //dataTimer will be 0 if the LSM303 is powered off.
        if ( LSM303->XAxisIsEnabled()) LSM303->setX();
        if ( LSM303->YAxisIsEnabled()) LSM303->setY();
        if ( LSM303->ZAxisIsEnabled()) LSM303->setZ();
        usleep( LSM303->dataTimer );
    }
    return 0;
}

void* LSM303DLHC::recordMagnetometerValues( void* _LSM303 )
{
    LSM303DLHC* LSM303 = ( LSM303DLHC* ) _LSM303;
    while ( LSM303->magnetometerIsEnabled() == 0 ) { //"1 = Singe Conversion Mode", "Sleep Mode" with values of 2 or 3
        LSM303->setX();
        LSM303->setY();
        LSM303->setZ();
        usleep( LSM303->dataTimer );
    }
    return 0;
}

void LSM303DLHC::startRecording()
{
    if ( this->deviceAddress == ACCEL_ADDRESS )
        pthread_create( &this->LSM303AccelThread, NULL, LSM303DLHC::recordAccelerometerValues, this );
    else
        pthread_create( &this->LSM303MagThread, NULL, LSM303DLHC::recordMagnetometerValues, this );
}