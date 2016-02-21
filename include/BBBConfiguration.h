/*
 * BBBConfiguration.h
 *
 *  Created on: 6 Dec 2015
 *      Author: michaelbrookes
 */

#ifndef SRC_H_BBBCONFIGURATION_H_
#define SRC_H_BBBCONFIGURATION_H_
#include "BBBPWMDevice.h"
#include "BBBAnalogDevice.h"
#include <string>
#include <queue>

using namespace std;

//<!--START OF CUSTOMISATIONS

#define MAX_DATASTORE					15				//<!-- How large the array of stored data is to compare for changes.

#define PROPELLOR_COUNT 				4 				//<!-- How many Propellors are there?
#define ANALOG_SENSOR_COUNT 			1 				//<!-- How many of the sensors are connected to analog ports?
#define I2C_SENSOR_COUNT 				3 				//<!-- How many of the sensors are connected to I2C ports?

#define GENERAL_NAME					"Quadro"

#define MOTOR_DEFAULTPERIODVAL			1900000			//<!-- Default value for the period value (pulse timing)
#define MOTOR_DEFAULTRUNVAL				0				//<!-- Default value for the run status (0 = Off)
#define MOTOR_MAXSPEED 					150000			//<!-- Default Max Speed for the motors.
#define MOTOR_TAKEOFFSPEED 				250000			//<!-- Default Take Off Speed for the motors.
#define MOTOR_SLOWSPEED 				700000			//<!-- Default Slow Speed for the motors.
#define MOTOR_STOPSPEED 				780000			//<!-- Default Stop Speed for the motors without turning the power off.

#define ROLL_ALLOWABLE_ERROR			1				//<!-- Allowable error for the Roll Value in degrees.
#define PITCH_ALLOWABLE_ERROR			1				//<!-- Allowable error for the Pitch Value in degrees.
#define HEADING_ALLOWABLE_ERROR			2				//<!-- Allowable error for the Heading Value in degrees.
#define ALTITUDE_ALLOWABLE_ERROR		1				//<!-- Allowable error for the Altitude Value in cm.
#define GYROX_ALLOWABLE_ERROR			0				//<!-- Allowable error for the Gyro X Value in degrees per second.
#define GYROY_ALLOWABLE_ERROR			0				//<!-- Allowable error for the Gyro Y Value in degrees per second.
#define GYROZ_ALLOWABLE_ERROR			0				//<!-- Allowable error for the Gyro Z Value in degrees per second.

#define MOTOR_1_BLOCK					9
#define MOTOR_1_PIN						42

#define MOTOR_2_BLOCK					8
#define MOTOR_2_PIN						19

#define MOTOR_3_BLOCK					9
#define MOTOR_3_PIN						14

#define MOTOR_4_BLOCK					9
#define MOTOR_4_PIN						22

#define ANALOG_1_PORT					0
#define ANALOG_1_NAME					"Sonic Sensor"

#define I2C_DEVICE_1_ADDRESS			0x19
#define I2C_DEVICE_1_NAME				"Accelerometer"

#define I2C_DEVICE_2_ADDRESS			0x1E
#define I2C_DEVICE_2_NAME				"Magnetometer"

#define I2C_DEVICE_3_ADDRESS			0x6B
#define I2C_DEVICE_3_NAME				"Gyroscope"

//<!--END OF CUSTOMISATIONS ###---DO NOT EDIT BELOW--###

class BBBConfiguration {

public:

    struct GENERAL_SETTINGS {
        string Name = GENERAL_NAME;
        struct TargetsVector { double Pitch, Roll, Heading;
            int GyroX, GyroY, GyroZ;
            int Altitude; } TargetValues;
        struct AllowableError {
            double dPitch = PITCH_ALLOWABLE_ERROR;
            double dRoll = ROLL_ALLOWABLE_ERROR;
            double dHeading = HEADING_ALLOWABLE_ERROR;
            int dGyroX = GYROX_ALLOWABLE_ERROR;
            int dGyroY = GYROY_ALLOWABLE_ERROR;
            int dGyroZ = GYROZ_ALLOWABLE_ERROR;
            int dAltitude = ALTITUDE_ALLOWABLE_ERROR;
        } AllowedErrorValues;
    } General;

    struct MOTOR_SETTINGS {
        int ID;
        string Name;
        BBBPWMDevice::PWM_BlockNum Block;
        BBBPWMDevice::PWM_PinNum Pin;
        BBBPWMDevice::PWM_RunValues RunState;
        int Period = MOTOR_DEFAULTPERIODVAL;
        int TargetSpeed = MOTOR_SLOWSPEED;
        int MaxSpeed = MOTOR_MAXSPEED;
        int TakeOffSpeed = MOTOR_TAKEOFFSPEED;
        int SlowSpeed = MOTOR_SLOWSPEED;
        int StopSpeed = MOTOR_STOPSPEED;
    } Motors[ PROPELLOR_COUNT ];

    struct ANALOG_SENSOR_SETTINGS {
        int ID;
        string Name;
        int AlertValue;
        BBBAnalogDevice::AnalogPort Port;
    } Analog_Sensor[ ANALOG_SENSOR_COUNT ];

    struct I2C_SENSOR_SETTINGS {
        int ID;
        string Name;
        int AlertValue;
        int AllowableDifference;
        int DeviceAddress;
    } I2C_Sensor[ I2C_SENSOR_COUNT ];

    BBBConfiguration(){

        //<!-- Propellor 1 info --!>//
        Motors[0].ID = 1; 																		//<!--Propellor 1 ID
        Motors[0].Name = "FL"; 																	//<!--Propellor 1 Name
        Motors[0].Block = ( BBBPWMDevice::PWM_BlockNum ) MOTOR_1_BLOCK;							//<!--Propellor 1 Block Location
        Motors[0].Pin = ( BBBPWMDevice::PWM_PinNum ) MOTOR_1_PIN;								//<!--Propellor 1 Pin Location
        //<!-- End of Propellor 1 info --!>//

        //<!-- Propellor 2 info --!>//
        Motors[1].ID = 2; 																		//<!--Propellor 2 ID
        Motors[1].Name = "FR"; 																	//<!--Propellor 2 Name
        Motors[1].Block = ( BBBPWMDevice::PWM_BlockNum ) MOTOR_2_BLOCK;							//<!--Propellor 2 Block Location
        Motors[1].Pin = ( BBBPWMDevice::PWM_PinNum ) MOTOR_2_PIN;								//<!--Propellor 2 Pin Location
        //<!-- End of Propellor 2 info --!>//

        //<!-- Propellor 3 info --!>//
        Motors[2].ID = 3; 																		//<!--Propellor 3 ID
        Motors[2].Name = "BL"; 																	//<!--Propellor 3 Name
        Motors[2].Block = ( BBBPWMDevice::PWM_BlockNum ) MOTOR_3_BLOCK;							//<!--Propellor 3 Block Location
        Motors[2].Pin = ( BBBPWMDevice::PWM_PinNum ) MOTOR_3_PIN;								//<!--Propellor 3 Pin Location
        //<!-- End of Propellor 3 info --!>//

        //<!-- Propellor 4 info --!>//
        Motors[3].ID = 4; 																		//<!--Propellor 4 ID
        Motors[3].Name = "BR"; 																	//<!--Propellor 4 Name
        Motors[3].Block = ( BBBPWMDevice::PWM_BlockNum ) MOTOR_4_BLOCK;							//<!--Propellor 4 Block Location
        Motors[3].Pin = ( BBBPWMDevice::PWM_PinNum ) MOTOR_4_PIN;								//<!--Propellor 4 Pin Location
        //<!-- End of Propellor 4 info --!>//

        //<!-- Analog Sensor 1 info --!>//
        Analog_Sensor[0].ID = 1;																//<!--Analog Sensor Device 1 ID
        Analog_Sensor[0].Name = ANALOG_1_NAME;													//<!--Analog Sensor Device 1 Name
        Analog_Sensor[0].Port = ( BBBAnalogDevice::AnalogPort ) ANALOG_1_PORT;					//<!--Analog Sensor Device 1 Address(int)
        //<!-- End of Sensor 1 info --!>//

        //<!-- I2C Sensor 1 info --!>//
        I2C_Sensor[0].ID = 1;																	//<!--I2C Sensor Device 1 ID
        I2C_Sensor[0].Name = I2C_DEVICE_1_NAME;													//<!--I2C Sensor Device 1 Name
        I2C_Sensor[0].DeviceAddress = I2C_DEVICE_1_ADDRESS;										//<!--I2C Sensor Device 1 Address(hex)
        //<!-- End of I2C Sensor 1 info --!>//

        //<!-- I2C Sensor 2 info --!>//
        I2C_Sensor[1].ID = 2;																	//<!--I2C Sensor Device 2 ID
        I2C_Sensor[1].Name = I2C_DEVICE_2_NAME;													//<!--I2C Sensor Device 2 Name
        I2C_Sensor[1].DeviceAddress = I2C_DEVICE_2_ADDRESS;										//<!--I2C Sensor Device 2 Address(hex)
        //<!-- End of I2C Sensor 2 info --!>//

        //<!-- I2C Sensor 3 info --!>//
        I2C_Sensor[2].ID = 3;																	//<!--I2C Sensor Device 3 ID
        I2C_Sensor[2].Name = I2C_DEVICE_3_NAME;													//<!--I2C Sensor Device 3 Name
        I2C_Sensor[2].DeviceAddress = I2C_DEVICE_3_ADDRESS;										//<!--I2C Sensor Device 3 Address(hex)
        //<!-- End of I2C Sensor 3 info --!>//

    }

};

#endif /* SRC_H_BBBCONFIGURATION_H_ */
