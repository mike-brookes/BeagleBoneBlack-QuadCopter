/*
Copyright (C) 2017 Michael Brookes

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
    if ( deviceAddress == ACCEL_ADDRESS ) {
        powerSettings =
                commitSetting(
                        CTRL_REG1_A,
                        SET_CTRL_REG1_A(
                                ODR_1344KHZ,
                                LP_LOW_POWER_DISABLED,
                                Z_AXIS_ENABLED,
                                Y_AXIS_ENABLED,
                                X_AXIS_ENABLED
                        )
                );

        highPassSettings =
                commitSetting(
                        CTRL_REG2_A,
                        SET_CTRL_REG2_A (
                                HIGHPASS_MODE_NORMAL_WITH_RESET,
                                HIGHPASS_FDS_INTERNAL_BYPASSED_DISABLED,
                                HIGHPASS_FILTER_DISABLED_FOR_CLICK,
                                HIGHPASS_FILTER_DISABLED_AOI_INT2,
                                HIGHPASS_FILTER_DISABLED_AOI_INT1
                        )
                );

        int1Settings =
                commitSetting(
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

        dataSettings =
                commitSetting(
                        CTRL_REG4_A,
                        SET_CTRL_REG4_A(
                                BDU_UPDATE_REGISTERS_CONTINUOUSLY,
                                BLE_DATA_LSB_AT_LOWER_ADDRESS,
                                FS_SCALE_AT_PLUS_MINUS_16G,
                                HR_HI_RES_ENABLED,
                                SIM_SERIAL_INTERFACE_4_WIRE
                        )
                );

        memorySettings =
                commitSetting(
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
        interruptSettings =
                commitSetting(
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

        FIFOSettings =
                commitSetting(
                        FIFO_CTRL_REG_A,
                        SET_FIFO_CTRL_REG_A(
                                FM_BYPASS_MODE,
                                TR_TRIGGER_LINKED_TO_INTERRUPT2
                        )
                );

        interrupt1CFGSettings =
                commitSetting(
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

        interrupt2CFGSettings =
                commitSetting(
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

        clickCFGSettings =
                commitSetting(
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

        clickSRCSettings =
                commitSetting(
                        CLICK_SRC_A,
                        SET_CLICK_SRC_A(
                                DCLICK_DOUBLE_CLICK_DETECTION_DISABLED,
                                SCLICK_SINGLE_CLICK_DETECTION_DISABLED,
                                SIGN_POSITIVE_DETECTION
                        )
                );
    }
    else if ( deviceAddress == MAG_ADDRESS ) {

        CRARegMSettings =
                commitSetting(
                        CRA_REG_M,
                        SET_CRA_REG_M(
                                TEMP_ENABLED,
                                DO2_220Hz
                        )
                );

        MRRegMSettings =
                commitSetting(
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

LSM303DLHC::~LSM303DLHC()
{
    stopRecording();
}

void LSM303DLHC::startSensorThread()
{
    if ( deviceAddress == ACCEL_ADDRESS ) {
        getOutputDataRate();
    }
    else if ( deviceAddress == MAG_ADDRESS ) {
        getDataOutputRate();
    }

    setDataTimer();
    startRecording();
}

uint8_t LSM303DLHC::commitSetting( uint8_t registerAddress, uint8_t registerValue )
{
    setRegisterAddress( registerAddress );
    setRegisterValue( registerValue );
    writeToDevice( 2 );
    return registerValue;
}

short LSM303DLHC::getX()
{
    return ( getValueFromRegister(
            ( unsigned char ) (( deviceAddress == ACCEL_ADDRESS ) ? OUT_X_H_A : OUT_X_H_M )) << 8 ) |
            getValueFromRegister(
                    ( unsigned char ) (( deviceAddress == ACCEL_ADDRESS ) ? OUT_X_L_A : OUT_X_L_M ));
}

short LSM303DLHC::getY()
{
    return ( getValueFromRegister(
            ( unsigned char ) (( deviceAddress == ACCEL_ADDRESS ) ? OUT_Y_H_A : OUT_Y_H_M )) << 8 ) |
            getValueFromRegister(
                    ( unsigned char ) (( deviceAddress == ACCEL_ADDRESS ) ? OUT_Y_L_A : OUT_Y_L_M ));
}

short LSM303DLHC::getZ()
{
    return ( getValueFromRegister(
            ( unsigned char ) (( deviceAddress == ACCEL_ADDRESS ) ? OUT_Z_H_A : OUT_Z_H_M )) << 8 ) |
            getValueFromRegister(
                    ( unsigned char ) (( deviceAddress == ACCEL_ADDRESS ) ? OUT_Z_L_A : OUT_Z_L_M ));

}

void LSM303DLHC::setX() { x = getX(); }

void LSM303DLHC::setY() { y = getY(); }

void LSM303DLHC::setZ() { z = getZ(); }

//bits required `0000`0000 >> 4 = 0000`0000` & 15 (00001111) = val of the 4 bits
uint8_t LSM303DLHC::getOutputDataRate() { return uint8_t(( getPowerSettings() >> 4 ) & 15 ); }

//bits required 0000000`0` & 1 (00000001) = val of the 1 bit
bool LSM303DLHC::XAxisIsEnabled() { return uint8_t( getPowerSettings() & 1 ); }

//bits required 000000`0`0 >> 1 = 0000000`0` & 1 (00000001) = val of the 1 bit
bool LSM303DLHC::YAxisIsEnabled() { return uint8_t(( getPowerSettings() >> 1 ) & 1 ); }

//bits required 00000`0`00 >> 2 = 0000000`0` & 1 (00000001) = val of the 1 bit
bool LSM303DLHC::ZAxisIsEnabled() { return uint8_t(( getPowerSettings() >> 2 ) & 1 ); }

//bits required 000`000`00 >> 2 = 00000`000` & 7 (00000111) = val of the 3 bits
uint8_t LSM303DLHC::getDataOutputRate() { return uint8_t(( getCRARegMSettings() >> 2 ) & 7 ); }

//bits required 000000`00` & 3 (00000011) = val of the 2 bits
uint8_t LSM303DLHC::magnetometerIsEnabled() { return uint8_t(( getMRRegMSettings()) & 3 ); }

void LSM303DLHC::setDataTimer()
{
    ( deviceAddress == ACCEL_ADDRESS ) ? setAccelerometerTimerBasedOnODR()
                                       : setMagnetometerTimerBasedOnDO();
}

void LSM303DLHC::setAccelerometerTimerBasedOnODR()
{ //ODR = Output Data Rate
    switch ( getOutputDataRate() << 4 ) {
    case ODR_10HZ    :
        dataTimer = 1000000 / 10;
        break; //1Hz = 1000000 Micro Seconds
    case ODR_25HZ    :
        dataTimer = 1000000 / 25;
        break;
    case ODR_50HZ    :
        dataTimer = 1000000 / 50;
        break;
    case ODR_100HZ   :
        dataTimer = 1000000 / 100;
        break;
    case ODR_200HZ   :
        dataTimer = 1000000 / 200;
        break;
    case ODR_400HZ   :
        dataTimer = 1000000 / 400;
        break;
    case ODR_1344KHZ :
        dataTimer = 800;
        break;
    case POWER_OFF   :
        dataTimer = 0;
        break;
    default :
        dataTimer = 1000000;
    }
}

void LSM303DLHC::setMagnetometerTimerBasedOnDO()
{ //DO = Data Output
    switch ( getDataOutputRate() << 2 ) {
    case DO2_0_75Hz :
        dataTimer = 1333333;
        break; //1.5Hz = 1333333 Micro Seconds
    case DO2_1_5Hz  :
        dataTimer = ( unsigned int ) ( 1000000 / 1.5 );
        break;
    case DO2_3_0Hz  :
        dataTimer = 1000000 / 3;
        break;
    case DO2_7_5Hz  :
        dataTimer = ( unsigned int ) ( 1000000 / 7.5 );
        break;
    case DO2_15Hz   :
        dataTimer = 1000000 / 15;
        break;
    case DO2_30Hz   :
        dataTimer = 1000000 / 30;
        break;
    case DO2_75Hz   :
        dataTimer = 1000000 / 75;
        break;
    case DO2_220Hz  :
        dataTimer = 1000000 / 220;
        break;
    default :
        dataTimer = 1333333;
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
    while ( LSM303->magnetometerIsEnabled() == 0 ) { //0 = continuous mode, 1 = "Singe Conversion Mode", "Sleep Mode" with values of 2 or 3
        LSM303->setX();
        LSM303->setY();
        LSM303->setZ();
        usleep( LSM303->dataTimer );
    }
    return 0;
}

void LSM303DLHC::startRecording()
{
    if ( deviceAddress == ACCEL_ADDRESS ) {
        threadRet = pthread_create( &LSM303AccelThread, NULL, LSM303DLHC::recordAccelerometerValues, this );
        if ( threadRet == EAGAIN ) {
            //Failed because of resource unavailability, try once more and then throw an exception on failure
            threadRet = pthread_create( &LSM303AccelThread, NULL, LSM303DLHC::recordAccelerometerValues, this );
            if ( threadRet != 0 ) {
                throw new i2cSetupException(
                        "(LVMaxSonarEZ) " + i2c::THREAD_FATAL + " : errorNumber = "
                                + to_string( threadRet ));
            }
        }
    }
    else {
        threadRet = pthread_create( &LSM303MagThread, NULL, LSM303DLHC::recordMagnetometerValues, this );
        if ( threadRet == EAGAIN ) {
            //Failed because of resource unavailability, try once more and then throw an exception on failure
            threadRet = pthread_create( &LSM303MagThread, NULL, LSM303DLHC::recordMagnetometerValues, this );
            if ( threadRet != 0 ) {
                throw new i2cSetupException(
                        "(LVMaxSonarEZ) " + i2c::THREAD_FATAL + " : errorNumber = "
                                + to_string( threadRet ) );
            }
        }
    }

    //Thread returned 0 (Success Code)
    if ( threadRet != 0 ) {
        //The sonic sensor thread failed, throw an appropriate exception.
        if ( threadRet == EPERM ) {
            //Thread creation failed because of invalid permissions on the system to create threads.
            throw new i2cSetupException(
                    "(LVMaxSonarEZ) " + i2c::THREAD_PERMISSIONS + " : errorNumber = " + to_string( threadRet ) );
        }
        else if ( threadRet == EINVAL ) {
            //Thread creation failed because the argument used is invalid.
            throw new i2cSetupException(
                    "(LVMaxSonarEZ) " + i2c::THREAD_INVALID_ARG + " : errorNumber = " + to_string( threadRet ) );
        }
        else {
            //An unknown error occurred - unknown error code.
            throw new i2cSetupException(
                    "(LVMaxSonarEZ) " + i2c::THREAD_UNKNOWN + " : errorNumber = " + to_string( threadRet ) );
        }
    }
}

void LSM303DLHC::stopRecording()
{
    if ( deviceAddress == ACCEL_ADDRESS ) {
        powerSettings =
                commitSetting(
                        CTRL_REG1_A,
                        SET_CTRL_REG1_A(
                                POWER_OFF,
                                LP_LOW_POWER_DISABLED,
                                Z_AXIS_DISABLED,
                                Y_AXIS_DISABLED,
                                X_AXIS_DISABLED
                        )
                );
        setDataTimer();
        stop( LSM303AccelThread );
    }
    else {
        MRRegMSettings =
                commitSetting(
                        MR_REG_M,
                        SET_MR_REG_M(
                                MD_SLEEP_MODE_1
                        )
                );
        stop( LSM303MagThread );
    }
}