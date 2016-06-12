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

#ifndef SRC_LSM303DLHC_H_
#define SRC_LSM303DLHC_H_

#include "../I2C/I2CDevice.h"

#define MICRO_SECOND = 1000000
/*
 * REGISTER ADDRESS
 */
//From Table 17. of the LSM303 Data sheet ( Lib/Docs/LSM303DLHC.PDF )
#define ACCEL_ADDRESS                               0x19    //!< I2C Address of the accelerometer device.
#define CTRL_REG1_A                                 0x20    //!< Read/Write (power control) : Default - 00111
#define CTRL_REG2_A                                 0x21    //!< Read/Write (filter selection) : Default - 0
#define CTRL_REG3_A                                 0x22    //!< Read/Write (interrupt settings) : Default - 0
#define CTRL_REG4_A                                 0x23    //!< Read/Write (range/resolution settings) : Default - 0
#define CTRL_REG5_A                                 0x24    //!< Read/Write (FIFO setting | internal memory) : Default - 0
#define CTRL_REG6_A                                 0x25    //!< Read/Write (CLICK interrupt setting) : Default - 0
#define REFERENCE_A                                 0x26    //!< Read/Write (Reference value for interrupt generation) : Default - 0
#define STATUS_REG_A                                0x27    //!< Read Only  (Overrun trigger) : Default - 0
#define OUT_X_L_A                                   0x28    //!< Read Only  (X-axis acceleration data. The value is expressed in 2’s complement)
#define OUT_X_H_A                                   0x29    //!< Read Only  (X-axis acceleration data. The value is expressed in 2’s complement)
#define OUT_Y_L_A                                   0x2A    //!< Read Only  (Y-axis acceleration data. The value is expressed in 2’s complement)
#define OUT_Y_H_A                                   0x2B    //!< Read Only  (Y-axis acceleration data. The value is expressed in 2’s complement)
#define OUT_Z_L_A                                   0x2C    //!< Read Only  (Z-axis acceleration data. The value is expressed in 2’s complement)
#define OUT_Z_H_A                                   0x2D    //!< Read Only  (Z-axis acceleration data. The value is expressed in 2’s complement)
#define FIFO_CTRL_REG_A                             0x2E    //!< Read/Write (FIFO mode selection) : Default - 0
#define FIFO_SRC_REG_A                              0x2F    //!< Read Only  (FIFO register)
#define INT1_CFG_A                                  0x30    //!< Read/Write (interrupt 1 settings)
#define INT1_SOURCE_A                               0x31    //!< Read Only  (interrupt 1 settings)
#define INT1_THS_A                                  0x32    //!< Read/Write (interrupt 1 settings)
#define INT1_DURATION_A                             0x33    //!< Read/Write (interrupt 1 settings)
#define INT2_CFG_A                                  0x34    //!< Read/Write (interrupt 2 settings)
#define INT2_SOURCE_A                               0x35    //!< Read 		(interrupt 2 settings)
#define INT2_THS_A                                  0x36    //!< Read/Write (interrupt 2 settings)
#define INT2_DURATION_A                             0x37    //!< Read/Write (interrupt 2 settings)
#define CLICK_CFG_A                                 0x38    //!< Read/Write (interrupt double CLICK on Z axis) : Default - 0
#define CLICK_SRC_A                                 0x39    //!< Read/Write (interrupt double CLICK settings)
#define CLICK_THS_A                                 0x3A    //!< Read/Write (interrupt double CLICK settings)
#define TIME_LIMIT_A                                0x3B    //!< Read/Write (interrupt double CLICK settings)
#define TIME_LATENCY_A                              0x3C    //!< Read/Write (interrupt double CLICK settings)
#define TIME_WINDOW_A                               0x3D    //!< Read/Write (interrupt double CLICK settings)

#define MAG_ADDRESS                                 0x1E    //!< I2C Address of the magnetometer device.
#define CRA_REG_M                                   0x00    //!< Read/Write (0x94 or 10010100 Temp sensor on and 30 hz refresh rate.)
#define CRB_REG_M                                   0x01    //!< Read/Write
#define MR_REG_M                                    0x02    //!< Read/Write (0x00 or 00000000 Continuous conversion mode.)
#define OUT_X_H_M                                   0x03    //!< Read Only  (X-axis magnetometer data. The value is expressed in 2’s complement)
#define OUT_X_L_M                                   0x04    //!< Read Only  (X-axis magnetometer data. The value is expressed in 2’s complement)
#define OUT_Z_H_M                                   0x05    //!< Read Only  (Z-axis magnetometer data. The value is expressed in 2’s complement)
#define OUT_Z_L_M                                   0x06    //!< Read Only  (Z-axis magnetometer data. The value is expressed in 2’s complement)
#define OUT_Y_H_M                                   0x07    //!< Read Only  (Y-axis magnetometer data. The value is expressed in 2’s complement)
#define OUT_Y_L_M                                   0x08    //!< Read Only  (Y-axis magnetometer data. The value is expressed in 2’s complement)
#define SR_REG_Mg                                   0x09    //!< Read Only
#define IRA_REG_M                                   0x0A    //!< Read Only
#define IRB_REG_M                                   0x0B    //!< Read Only
#define IRC_REG_M                                   0x0C    //!< Read Only
#define TEMP_OUT_H_M                                0x31    //!< Read Only  (Temp sensor data. The value is expressed in 2’s complement)
#define TEMP_OUT_L_M                                0x32    //!< Read Only  (Temp sensor data. The value is expressed in 2’s complement)
/*
 * END OF REGISTER ADDRESSES
 */

/*
 * POWER SETTINGS - REGISTER TO WRITE TO : CTRL_REG1_A 0x20
 */
#define POWER_OFF                                   0b00000000
#define ODR_1HZ                                     0b00010000
#define ODR_10HZ                                    0b00100000
#define ODR_25HZ                                    0b00110000
#define ODR_50HZ                                    0b01000000
#define ODR_100HZ                                   0b01010000
#define ODR_200HZ                                   0b01100000
#define ODR_400HZ                                   0b01110000
#define ODR_1344KHZ                                 0b10010000
#define LP_LOW_POWER_DISABLED                       0b00000000
#define LP_LOW_POWER_ENABLED                        0b00001000
#define Z_AXIS_ENABLED                              0b00000100
#define Z_AXIS_DISABLED                             0b00000000
#define Y_AXIS_ENABLED                              0b00000010
#define Y_AXIS_DISABLED                             0b00000000
#define X_AXIS_ENABLED                              0b00000001
#define X_AXIS_DISABLED                             0b00000000

#define SET_CTRL_REG1_A( ODR, LPEN, ZEN, YEN, XEN ) ODR | LPEN | ZEN | YEN | XEN
/*
 * END OF POWER SETTINGS
 */

/*
 * HIGH PASS FILTER SETTINGS - REGISTER : CTRL_REG2_A 0x21
 */
#define HIGHPASS_MODE_NORMAL_WITH_RESET             0b00000000
#define HIGHPASS_MODE_REFERENCE_SIGNAL              0b01000000
#define HIGHPASS_MODE_NORMAL                        0b10000000
#define HIGHPASS_MODE_AUTO_RESET_ON_INTERRUPT       0b11000000
/*
 \brief FDS = Filtered Data Selection
 */
#define HIGHPASS_FDS_INTERNAL_BYPASSED_ENABLED      0b00001000
#define HIGHPASS_FDS_INTERNAL_BYPASSED_DISABLED     0b00000000
#define HIGHPASS_FILTER_ENABLED_FOR_CLICK           0b00000100
#define HIGHPASS_FILTER_DISABLED_FOR_CLICK          0b00000000
#define HIGHPASS_FILTER_DISABLED_AOI_INT2           0b00000000
#define HIGHPASS_FILTER_ENABLED_AOI_INT2            0b00000010
#define HIGHPASS_FILTER_ENABLED_AOI_INT1            0b00000001
#define HIGHPASS_FILTER_DISABLED_AOI_INT1           0b00000000

#define SET_CTRL_REG2_A( HIGHPASS_MODE, HIGHPASS_FDS, HIGHPASS_CLICK_FILTER, HIGHPASS_AOI_INT2, HIGHPASS_AOI_INT1 ) HIGHPASS_MODE | HIGHPASS_FDS | HIGHPASS_CLICK_FILTER | HIGHPASS_AOI_INT2 | HIGHPASS_AOI_INT1
/*
 * END OF HIGH PASS FILTER SETTINGS
 */

/*
 * INTERRUPT SETTINGS - REGISTER : CTRL_REG3_A 0x22
 */
#define CLICK_INTERRUPT_ON_INT1_ENABLED             0b10000000
#define CLICK_INTERRUPT_ON_INT1_DISABLED            0b00000000
#define AOI1_INTERRUPT_ON_INT1_ENABLED              0b01000000
#define AOI1_INTERRUPT_ON_INT1_DISABLED             0b00000000
#define AOI2_INTERRUPT_ON_INT1_ENABLED              0b00100000
#define AOI2_INTERRUPT_ON_INT1_DISABLED             0b00000000
#define DRDY1_INTERRUPT_ON_INT1_ENABLED             0b00010000
#define DRDY1_INTERRUPT_ON_INT1_DISABLED            0b00000000
#define DRDY2_INTERRUPT_ON_INT1_ENABLED             0b00001000
#define DRDY2_INTERRUPT_ON_INT1_DISABLED            0b00000000
#define FIFO_WTM_INTERRUPT_ON_INT1_ENABLED          0b00000100
#define FIFO_WTM_INTERRUPT_ON_INT1_DISABLED         0b00000000
#define FIFO_OVERRUN_INTERRUPT_ON_INT1_ENABLED      0b00000010
#define FIFO_OVERRUN_INTERRUPT_ON_INT1_DISABLED     0b00000000

#define SET_CTRL_REG3_A(CLICK, AOI1, AOI2, DRDY1, DRDY2, WTM, OVERRUN) CLICK | AOI1 | AOI2 | DRDY1 | DRDY2 | WTM | OVERRUN
/*
 * END OF INTERRUPT SETTINGS
 */

/*
 * RESOLUTION AND SCALE SETTINGS - REGISTER : CTRL_REG4_A 0x23
 */
#define BDU_UPDATE_REGISTERS_CONTINUOUSLY           0b00000000
#define BDU_WAIT_UNTIL_REGISTERS_ARE_READ           0b10000000
#define BLE_DATA_LSB_AT_LOWER_ADDRESS               0b00000000
#define BLE_DATA_MSB_AT_LOWER_ADDRESS               0b01000000
#define FS_SCALE_AT_PLUS_MINUS_2G                   0b00000000
#define FS_SCALE_AT_PLUS_MINUS_4G                   0b00010000
#define FS_SCALE_AT_PLUS_MINUS_8G                   0b00100000
#define FS_SCALE_AT_PLUS_MINUS_16G                  0b00110000
#define HR_HI_RES_ENABLED                           0b00001000
#define HR_HI_RES_DISABLED                          0b00000000
#define SIM_SERIAL_INTERFACE_4_WIRE                 0b00000000
#define SIM_SERIAL_INTERFACE_3_WIRE                 0b00000001

#define SET_CTRL_REG4_A( BDU, BLE, FS, HR, SIM ) BDU | BLE | FS | HR | SIM
/*
 * END OF RESOLUTION AND SCALE SETTINGS
 */

/*
 * REGISTER : CTRL_REG5_A 0x24
 */
#define BOOT_REBOOT_MEM_CONTENT_ENABLED             0b10000000
#define BOOT_REBOOT_MEM_CONTENT_DISABLED            0b00000000
#define FIFO_ENABLED                                0b01000000
#define FIFO_DISABLED                               0b00000000
#define LIR_INT1_LATCHED                            0b00001000
#define LIR_INT1_NOT_LATCHED                        0b00000000
#define D4D_INT1_4D_ENABLED                         0b00000100
#define D4D_INT1_4D_DISABLED                        0b00000000
#define LIR_INT2_LATCHED                            0b00000010
#define LIR_INT2_NOT_LATCHED                        0b00000000
#define D4D_INT2_4D_ENABLED                         0b00000001
#define D4D_INT2_4D_DISABLED                        0b00000000

#define SET_CTRL_REG5_A( BOOT, FIFO_EN, LIR_INT1, D4D_INT1, LIR_INT2, D4D_INT2 ) BOOT | FIFO_EN | LIR_INT1 | D4D_INT1 | LIR_INT2 | D4D_INT2
/*
 * END OF REGISTER
 */

/*
 * REGISTER : CTRL_REG6_A 0x25
 */
#define I2_CLICK_INTERRUPT_ON_PAD2_ENABLED          0b10000000
#define I2_CLICK_INTERRUPT_ON_PAD2_DISABLED         0b00000000
#define I2_INTERRUPT_1_ENABLED                      0b01000000
#define I2_INTERRUPT_1_DISABLED                     0b00000000
#define I2_INTERRUPT_2_ENABLED                      0b00100000
#define I2_INTERRUPT_2_DISABLED                     0b00000000
#define BOOT_I1_REBOOT_MEMORY_ENABLED               0b00010000
#define BOOT_I1_REBOOT_MEMORY_DISABLED              0b00000000
#define P2_ACT_ACTIVE_FUNCTION_ON_PAD2_ENABLED      0b00001000
#define P2_ACT_ACTIVE_FUNCTION_ON_PAD2_DISABLED     0b00000000
#define H_LACTIVE_INTERRUPT_ACTIVE_HIGH             0b00000000
#define H_LACTIVE_INTERRUPT_ACTIVE_LOW              0b00000010

#define SET_CTRL6_REG_A( I2_CLICK, I2_INT1, I2_INT2, BOOT_I1, P2_ACT, H_LACTIVE ) I2_CLICK | I2_INT1 | I2_INT2 | BOOT_I1 | P2_ACT | H_LACTIVE
/*
 * END OF REGISTER
 */

/*
 * REGISTER : FIFO_CTRL_REG_A 0x2E
 */
#define FM_BYPASS_MODE                              0b00000000
#define FM_FIFO_MODE                                0b01000000
#define FM_STREAM_MODE                              0b10000000
#define FM_TRIGGER_MODE                             0b11000000
#define TR_TRIGGER_LINKED_TO_INTERRUPT1             0b00000000
#define TR_TRIGGER_LINKED_TO_INTERRUPT2             0b00100000

#define SET_FIFO_CTRL_REG_A( FM, TR ) FM | TR
/*
 * END OF REGISTER
 */

/*
* REGISTER INT1_CFG_A 0x30 & INT2_CFG_A 0x31
*/
#define AOI_OR_COMBINATION                          0b00000000
#define AOI_6D_MOVEMENT_RECOGNITION_ENABLED         0b01000000
#define AOI_AND_COMBINATION                         0b10000000
#define AOI_6D_POSITION_RECOGNITION_ENABLED         0b11000000
#define ZHIE_INTERRUPT_ON_Z_HIGH_ENABLED            0b00100000
#define ZHIE_INTERRUPT_ON_Z_HIGH_DISABLED           0b00000000
#define ZLIE_INTERRUPT_ON_Z_LOW_ENABLED             0b00010000
#define ZLIE_INTERRUPT_ON_Z_LOW_DISABLED            0b00000000
#define YHIE_INTERRUPT_ON_Y_HIGH_ENABLED            0b00001000
#define YHIE_INTERRUPT_ON_Y_HIGH_DISABLED           0b00000000
#define YLIE_INTERRUPT_ON_Y_LOW_ENABLED             0b00000100
#define YLIE_INTERRUPT_ON_Y_LOW_DISABLED            0b00000000
#define XHIE_INTERRUPT_ON_X_HIGH_ENABLED            0b00000010
#define XHIE_INTERRUPT_ON_X_HIGH_DISABLED           0b00000000
#define XLIE_INTERRUPT_ON_X_LOW_ENABLED             0b00000001
#define XLIE_INTERRUPT_ON_X_LOW_DISABLED            0b00000000

#define SET_INT1_CFG_A( AOI, ZHIE, ZLIE, YHIE, YLIE, XHIE, XLIE ) AOI | ZHIE | ZLIE | YHIE | YLIE | XHIE | XLIE
#define SET_INT2_CFG_A( AOI, ZHIE, ZLIE, YHIE, YLIE, XHIE, XLIE ) AOI | ZHIE | ZLIE | YHIE | YLIE | XHIE | XLIE
/*
 * END OF REGISTER
 */

/*
 * CLICK_CFG_A 0x38
 */
#define ZD_DOUBLECLICK_ON_Z_AXIS_ENABLED            0b00100000
#define ZD_DOUBLECLICK_ON_Z_AXIS_DISABLED           0b00000000
#define ZS_SINGLECLICK_ON_Z_AXIS_ENABLED            0b00010000
#define ZS_SINGLECLICK_ON_Z_AXIS_DISABLED           0b00000000
#define YD_DOUBLECLICK_ON_Y_AXIS_ENABLED            0b00001000
#define YD_DOUBLECLICK_ON_Y_AXIS_DISABLED           0b00000000
#define YS_SINGLECLICK_ON_Y_AXIS_ENABLED            0b00000100
#define YS_SINGLECLICK_ON_Y_AXIS_DISABLED           0b00000000
#define XD_DOUBLECLICK_ON_X_AXIS_ENABLED            0b00000010
#define XD_DOUBLECLICK_ON_X_AXIS_DISABLED           0b00000000
#define XS_SINGLECLICK_ON_X_AXIS_ENABLED            0b00000001
#define XS_SINGLECLICK_ON_X_AXIS_DISABLED           0b00000000

#define SET_CLICK_CFG_A( ZD, ZS, YD, YS, XD, XS ) ZD | ZS | YD | YS | XD | XS
/*
 * END OF CLICK_CFG_A
 */

/*
 * CLICK_SRC_A 0x39
 */
#define IA_INTERRUPT_ACTIVE_NO_INTERRUPTS           0b00000000
#define IA_INTERRUPT_ACTIVE_1_OR_MORE_INTERRUPTS    0b01000000
#define DCLICK_DOUBLE_CLICK_DETECTION_ENABLED       0b00000000
#define DCLICK_DOUBLE_CLICK_DETECTION_DISABLED      0b00100000
#define SCLICK_SINGLE_CLICK_DETECTION_ENABLED       0b00000000
#define SCLICK_SINGLE_CLICK_DETECTION_DISABLED      0b00010000
#define SIGN_POSITIVE_DETECTION                     0b00000000
#define SIGN_NEGATIVE_DETECTION                     0b00001000

#define SET_CLICK_SRC_A( DCLICK, SCLICK, SIGN ) DCLICK | SCLICK | SIGN
/*
 * END OF CLICK_SRC_A
 */

/*
 * CRA_REG_M 0x00
 */
#define TEMP_ENABLED                                0b10000000
#define TEMP_DISABLED                               0b00000000
#define DO2_0_75Hz                                  0b00000000
#define DO2_1_5Hz                                   0b00000100
#define DO2_3_0Hz                                   0b00001000
#define DO2_7_5Hz                                   0b00001100
#define DO2_15Hz                                    0b00010000
#define DO2_30Hz                                    0b00010100
#define DO2_75Hz                                    0b00011000
#define DO2_220Hz                                   0b00011100

#define SET_CRA_REG_M( TEMP_EN, DO2 ) TEMP_EN | DO2
/*
 * END OF CRA_REG_M
 */

/*
 * CRB_REG_M 0x01
 */
#define GAIN_RANGE_1_3_GAIN_X_Y_Z_1100_GAIN_Z_980   0b00100000
#define GAIN_RANGE_1_9_GAIN_X_Y_Z_855_GAIN_Z_760    0b01000000
#define GAIN_RANGE_2_5_GAIN_X_Y_Z_670_GAIN_Z_600    0b01100000
#define GAIN_RANGE_4_0_GAIN_X_Y_Z_450_GAIN_Z_400    0b10000000
#define GAIN_RANGE_4_7_GAIN_X_Y_Z_400_GAIN_Z_355    0b10100000
#define GAIN_RANGE_5_6_GAIN_X_Y_Z_330_GAIN_Z_295    0b11000000
#define GAIN_RANGE_8_1_GAIN_X_Y_Z_230_GAIN_Z_205    0b11100000

#define SET_CRB_REG_M( GAIN ) GAIN
/*
 * END OF CRB_REG_M
 */

/*
 * MR_REG_M 0x02
 */
#define MD_CONTINUOUS_CONVERSION_MODE               0b00000000
#define MD_SINGLE_CONVERSION_MODE                   0b00000001
#define MD_SLEEP_MODE_1                             0b00000010
#define MD_SLEEP_MODE_2                             0b00000011

#define SET_MR_REG_M( MD ) MD
/*
 * END OF MR_REG_M
 */

/**
 \brief LSM303DLHC : Base class that provides control of the BBBLSM303DLHC, inherits I2C methods.
 \version   2.3
 \date      Oct-2015
 \copyright GNU Public License.
 */
using namespace abI2C;

class LSM303DLHC : public I2CDevice {

public:

    /**
     \brief BBBLSM303DLHC : A class that provides control of the BBBLSM303DLHC's accelerometer, magnetometer, temp and gyro.
     */
    LSM303DLHC( );

    void LoadRecommendedFlightSettings( );

    uint8_t GetPowerSettings( ){ return this->PowerSettings; }

    uint8_t GetHighPassSettings( ){ return this->HighPassSettings; }

    uint8_t GetInt1Settings( ){ return this->Int1Settings; }

    uint8_t GetDataSettings( ){ return this->DataSettings; }

    uint8_t GetMemorySettings( ){ return this->MemorySettings; }

    uint8_t GetInterruptSettings( ){ return this->InterruptSettings; }

    uint8_t GetFIFOSettings( ){ return this->FIFOSettings; }

    uint8_t GetInterrupt1CFGSettings( ){ return this->Interrupt1CFGSettings; }

    uint8_t GetInterrupt2CFGSettings( ){ return this->Interrupt2CFGSettings; }

    uint8_t GetClickCFGSettings( ){ return this->ClickCFGSettings; }

    uint8_t GetClickSRCSettings( ){ return this->ClickSRCSettings; }

    uint8_t GetCRARegMSettings( ){ return this->CRARegMSettings; }

    uint8_t GetMRRegMSettings( ){ return this->MRRegMSettings; }

    void Init( );

    short X, Y, Z;

    unsigned int DataTimer;

protected:

    void SetDeviceAddress( unsigned char _DeviceAddress ) { this->DeviceAddress = _DeviceAddress; }

    void SetBusId( int _BusId ) { this->BusId = _BusId; }

private:

    uint8_t CommitSetting( uint8_t RegisterAddress, uint8_t RegisterValue );
    uint8_t PowerSettings;
    uint8_t HighPassSettings;
    uint8_t Int1Settings;
    uint8_t DataSettings;
    uint8_t MemorySettings;
    uint8_t InterruptSettings;
    uint8_t FIFOSettings;
    uint8_t Interrupt1CFGSettings;
    uint8_t Interrupt2CFGSettings;
    uint8_t ClickCFGSettings;
    uint8_t ClickSRCSettings;
    uint8_t CRARegMSettings;
    uint8_t MRRegMSettings;

    static void* RecordAccelerometerValues(  void *_LSM303  );

    static void* RecordMagnetometerValues(  void *_LSM303  );

    void SetAccelerometerTimerBasedOnODR( );

    void SetMagnetometerTimerBasedOnDO( );

    void StartRecording( );

    void SetDataTimer( );

    short GetX( );

    short GetY( );

    short GetZ( );

    void SetX( );

    void SetY( );

    void SetZ( );

    uint8_t MagnetometerIsEnabled( );

    uint8_t GetOutputDataRate( );

    uint8_t GetDataOutputRate( );

    bool XAxisIsEnabled( );

    bool YAxisIsEnabled( );

    bool ZAxisIsEnabled( );

    pthread_t LSM303AccelThread, LSM303MagThread;

};

#endif /* SRC_LSM303DLHC_H_ */
