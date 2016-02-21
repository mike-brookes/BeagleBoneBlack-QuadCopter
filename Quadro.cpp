/*
 * BBBQuadro.cpp
 *
 *  Created on: 6 Dec 2015
 *      Author: michaelbrookes
 */

#include "include/Quadro.h"

Quadro::Quadro() {

}

int Quadro::AddI2CDevices() {
    return 1;
}

int Quadro::AddAnalogDevices() {
    for (int i = 0; i < ANALOG_SENSOR_COUNT; i++) {
        try {
            if (AnalogSensor[i].Analog_SetPort(Config.Analog_Sensor[i].Port) != 0) {
                cerr << "Error adding Analog Device (" << Config.Analog_Sensor[i].Name << ") On Port #" <<
                Config.Analog_Sensor[i].Port << endl;
                return -1;
            }
        }
        catch (exception &e) {
            cerr << "Error adding Analog Device (" << Config.Analog_Sensor[i].Name << ") On Port #" <<
            Config.Analog_Sensor[i].Port << " | Error = " << e.what() << endl;
            return -1;
        }
    }
    return 1;
}

int Quadro::AddMotors() {
    for (int i = 0; i < PROPELLOR_COUNT; i++) {
        PropellorMotor[i].PWM_SetBlockNum(Config.Motors[i].Block);
        PropellorMotor[i].PWM_SetPinNum(Config.Motors[i].Pin);
        PropellorMotor[i].PWM_Init();
        PropellorMotor[i].PWM_SetPeriodVal(BBBPWMDevice::PWM_PeriodValues::ACTIVE);
    }
    return 1;
}

void Quadro::SetAllMotorsSpeed(int motor_speed) {
    for (int i = 0; i < PROPELLOR_COUNT; i++) {
        this->SetMotorSpeed(i, motor_speed);
        pthread_join(PropellorMotor[i].PWM_Thread, &status);
    }
}

void Quadro::SetMotorSpeed(int motor_index, int motor_speed) {
    Config.Motors[motor_index].TargetSpeed = motor_speed;
    PropellorMotor[motor_index].PWM_SetTargetSpeed(motor_speed);
}

void Quadro::SetAllMotorsPower(BBBPWMDevice::PWM_RunValues val) {
    for (int i = 0; i < PROPELLOR_COUNT; i++) {
        Config.Motors[i].RunState = val;
        PropellorMotor[i].PWM_SetRunVal(Config.Motors[i].RunState);
    }
}

void Quadro::SetMotorPower(int motor_index, BBBPWMDevice::PWM_RunValues val) {
    Config.Motors[motor_index].RunState = val;
    PropellorMotor[motor_index].PWM_SetRunVal(Config.Motors[motor_index].RunState);
}

void Quadro::SetDefaultTargetValuesBasedOnStaticAverages() {
    Config.General.TargetValues.Pitch = Accelerometer.avgPitch;
    Config.General.TargetValues.Roll = Accelerometer.avgRoll;
    Config.General.TargetValues.GyroX = Gyroscope.avgX;
    Config.General.TargetValues.GyroY = Gyroscope.avgY;
    Config.General.TargetValues.GyroZ = Gyroscope.avgZ;
    Config.General.TargetValues.Heading = Magnetometer.avgHeading;
    Config.General.TargetValues.Altitude = ConvertAnalogReadingToAltitude(AnalogSensor[0].avgReading);
    cout << "Defaults : " << endl;
    cout << "Default Pitch = " << Config.General.TargetValues.Pitch;
    cout << "Default Roll = " << Config.General.TargetValues.Roll;
    cout << "Default Heading = " << Config.General.TargetValues.Heading;
    cout << "Default Gyro X = " << Config.General.TargetValues.GyroX;
    cout << "Default Gyro Y = " << Config.General.TargetValues.GyroY;
    cout << "Default Gyro Z = " << Config.General.TargetValues.GyroZ;
    cout << "Default Altitude = " << Config.General.TargetValues.Altitude << endl;
}

int Quadro::AnalyseData(int DataArray[MAX_DATASTORE], int TargetValue, int AllowedErrorValue) {
    if (abs(DataArray[(MAX_DATASTORE - 1)] - TargetValue) > abs(AllowedErrorValue)) {
        for (int i = 0; i < MAX_DATASTORE; i++) {
            if (abs(DataArray[i] - TargetValue) <= abs(AllowedErrorValue))
                return 0;
            else if (i == (MAX_DATASTORE - 1)) {
                return abs(DataArray[MAX_DATASTORE - 1] - TargetValue);
            }
        }
        return 0;
    }
    else
        return 0;
}

void Quadro::CheckSensorsForSense() {
    int DataDiff;

    DataDiff = this->AnalyseData(this->Accelerometer.PitchDataStoredValues, Config.General.TargetValues.Pitch,
                                 Config.General.AllowedErrorValues.dPitch);

    if (DataDiff > 0)
        cout << "Pitch value has changed by " << DataDiff << "!" << endl;

    DataDiff = this->AnalyseData(this->Accelerometer.RollDataStoredValues, Config.General.TargetValues.Roll,
                                 Config.General.AllowedErrorValues.dRoll);

    if (DataDiff > 0)
        cout << "Roll value has changed by " << DataDiff << "!" << endl;

    DataDiff = this->AnalyseData(this->Magnetometer.HeadingDataStoredValues, Config.General.TargetValues.Heading,
                                 Config.General.AllowedErrorValues.dHeading);

    if (DataDiff > 0)
        cout << "Heading value has changed by " << DataDiff << "!" << endl;

    DataDiff = this->AnalyseData(this->Gyroscope.GyroXDataStoredValues, Config.General.TargetValues.GyroX,
                                 Config.General.AllowedErrorValues.dGyroX);
    if (DataDiff > 0)
        cout << "GyroX value has changed by " << DataDiff << "!" << endl;

    DataDiff = this->AnalyseData(this->Gyroscope.GyroYDataStoredValues, Config.General.TargetValues.GyroY,
                                 Config.General.AllowedErrorValues.dGyroY);

    if (DataDiff > 0)
        cout << "GyroY value has changed by " << DataDiff << "!" << endl;

    DataDiff = this->AnalyseData(this->Gyroscope.GyroZDataStoredValues, Config.General.TargetValues.GyroZ,
                                 Config.General.AllowedErrorValues.dGyroZ);

    if (DataDiff > 0)
        cout << "GyroZ value has changed by " << DataDiff << "!" << endl;

    DataDiff = this->AnalyseData(this->AnalogSensor[0].DataStoredValues, Config.General.TargetValues.Altitude,
                                 Config.General.AllowedErrorValues.dAltitude);

    if (DataDiff > 0)
        cout << "Altitude value has changed by " << DataDiff << "!" << endl;

}

int Quadro::ConvertAnalogReadingToAltitude(int AReading) {
    return AReading / SONIC_MODIFYER;
}
