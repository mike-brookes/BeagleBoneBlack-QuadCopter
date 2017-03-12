#include "L3GD20H.h"

using namespace quadro::i2c;

/**
 \brief BBBLSM303DLHC : A class that provides control of the accelerometer LSM303DLHC and extends I2C devices on the Beaglebone Black.
  BBBI2CDevice : A low level control of I2C devices on the Beaglebone Black.
 */
L3GD20H::L3GD20H( unsigned char _deviceAddress, int _busId )
{
    this->setDeviceAddress( _deviceAddress );
    this->setBusId( _busId );
    this->initDevice();

    if ( this->setPower( _switch::ON ) < 0 ) {
        cerr << "Critical Error 1 : LSM303DLHC - Attempted to set the Accelerometers Power state to : "
             << this->gyroSwitch << " | This action failed." << endl;
        exit( 1 );
    }

    this->start();
}

int L3GD20H::setPower( _switch gyroSwitch )
{
    this->gyroSwitch = gyroSwitch;
    this->setRegisterAddress( CTRL1 );
    this->setRegisterValue( gyroSwitch );
    this->writeToDevice( 2 );
    return gyroSwitch;
}

void* L3GD20H::getValues( void* gyroInst )
{
    L3GD20H* gyro = ( L3GD20H* ) gyroInst;
    int startTime;
    while ( 1 ) {
        startTime = Timer::milliTimer();
        gyro->setX();
        gyro->setY();
        gyro->setZ();
        while ( Timer::milliTimer() - startTime < ( DT * 1000 )) {
            usleep( 100 );
        }
    }
}

void L3GD20H::start()
{
    pthread_create( &this->gyroNotifyer, NULL, L3GD20H::getValues, this );
}

/*!
 @function SetX
 - Set this->g.X to the current X reading from the sensor
 @returns <void>
 */
void L3GD20H::setX( void )
{
    this->rad.x = ( int16_t ) ( this->getValueFromRegister( OUT_X_L ) | ( this->getValueFromRegister( OUT_X_H ) << 8 ));
    this->rad.x *= 0.00875F;
    this->angle.x = float( this->rad.x * DT );
}

/*!
 @function SetY
 - Set this->g.Y to the current Y reading from the sensor
 @returns <void>
 */
void L3GD20H::setY( void )
{
    this->rad.y = ( int16_t ) ( this->getValueFromRegister( OUT_Y_L ) | ( this->getValueFromRegister( OUT_Y_H ) << 8 ));
    this->rad.y *= 0.00875F;
    this->angle.y = float( this->rad.y * DT );
}

/*!
 @function SetZ
 - Set this->g.Z to the current Z reading from the sensor
 @returns <void>
 */
void L3GD20H::setZ( void )
{
    this->rad.z = -( int16_t ) ( this->getValueFromRegister( OUT_Z_L )
            | ( this->getValueFromRegister( OUT_Z_H ) << 8 ));
    this->rad.z *= 0.00875F;
    this->angle.z = float( this->rad.z * DT );
}
