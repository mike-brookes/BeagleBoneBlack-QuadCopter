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

#include "i2cDevice.h"

using namespace quadro::i2c;

i2cDevice::i2cDevice()
{
    deviceAddress = 0x00;
    busId = 0;
    deviceInitialised = false;
}

i2cDevice::~i2cDevice()
{
    close( fileHandle );
}

void i2cDevice::initDevice() throw( i2cSetupException& )
{
    if ( !deviceAddress )
        throw i2cSetupException( "i2c Device Not Configured ( try : 'obj->setDeviceAddress([hex address])' )" );
    if ( !busId )
        throw i2cSetupException( "i2c Device Not Configured ( try : 'obj->setBusId([bus number])' )" );
    /*
     * ** ## -- Setup Stage -- ## ** *
     * setBusPaths : Saves the file paths to the available buses for ease of access.
     */
    setBusPaths();

    /*
     * ** ## -- Assignment Stage ( based on args ) -- ## ** *
     * validateBusId : Make sure we have a valid bus ID before proceeding.
     * selectABusPath : Used to specify which bus your i2c device is on.
     * setDeviceAddress: Hex value for your specific i2c Device.
     */
    validateBusId();
    selectABusPath();

    /*
     * ** ## -- init Stage -- ## ** *
     * openDevice : Creates a file handle for the device, should it be closed? Probably... :)
     * connectToDevice : Assigns the device as an i2c Slave and checks availability using IOCTL
     *
     * More info on IOCTL : http://man7.org/linux/man-pages/man2/ioctl.2.html
     */
    openDevice();
    connectToDevice();

    deviceInitialised = true;
}

void i2cDevice::setBusPaths()
{
    _bus[ 1 ].busPath = validateBusPath(( char* ) I2C_1 );
}

void i2cDevice::selectABusPath() { deviceBusPath = _bus[ busId ].busPath; }

void i2cDevice::setRegisterAddress( unsigned char _registerAddress ) { registerAddress = _registerAddress; }

void i2cDevice::setRegisterValue( unsigned char _RegisterValue ) { registerValue = _RegisterValue; }

const char* i2cDevice::getFilePath() { return deviceBusPath; }

void i2cDevice::setStatus( deviceStatus _status )
{
    currentStatus = _status;
}

int i2cDevice::getStatus()
{
    return currentStatus;
}

int i2cDevice::getDeviceFileHandle() { return fileHandle; }

int i2cDevice::validateBusId() throw( i2cSetupException& )
{
    if ( busId > I2C_BUS_COUNT || busId < 1 ) {
        snprintf( errMessage, sizeof( errMessage ), "Bus ID : %d  is not a valid BUS for this device.",
                busId );
        throw ( i2cSetupException( errMessage ));
    }
    else
        return EXIT_SUCCESS;
}

char* i2cDevice::validateBusPath( char* _busProposedPath ) throw( i2cSetupException& )
{
    if ( stat( _busProposedPath, &buffer ) == 0 )
        return _busProposedPath;
    else {
        snprintf( errMessage, sizeof( errMessage ),
                "Fatal i2c Error - Unable to locate the i2c Bus file : %s", _busProposedPath );
        throw i2cSetupException( errMessage );
    }
}

short i2cDevice::getValueFromRegister( unsigned char _RegisterAddress )
{
    if ( !deviceInitialised )
        throw i2cSetupException( "i2c Device Not Initialised ( try : 'obj->initDevice()' )" );
    setRegisterAddress( _RegisterAddress );
    writeBufferOnly[ 0 ] = registerAddress;
    if ( write( getDeviceFileHandle(), writeBufferOnly, 1 ) == 1 ) {
        return readDevice( ONE_BYTE );
    }
    else {
        snprintf( errMessage, sizeof( errMessage ), "Fatal i2c Error - Unable to write to file : %s",
                getFilePath());
        throw i2cSetupException( errMessage );
    }
}

short i2cDevice::readDevice( size_t _BufferSize ) throw( i2cSetupException& )
{
    if ( !deviceInitialised )
        throw i2cSetupException( "i2c Device Not Initialised ( try : 'obj->initDevice()' )" );
    unsigned char buff[_BufferSize];
    if ( _BufferSize != read( getDeviceFileHandle(), buff, _BufferSize )) {
        snprintf( errMessage, sizeof( errMessage ), "Fatal i2c Error - Unable to read from file : %s",
                getFilePath());
        throw i2cSetupException( errMessage );
    }
    else
        return buff[ 0 ];
}

int i2cDevice::openDevice() throw( i2cSetupException& )
{
    fileHandle = open( getFilePath(), O_RDWR );
    if ( fileHandle == 0 ) {
        snprintf( errMessage, sizeof( errMessage ), "Fatal i2c Error - Unable to open file : %s",
                getFilePath());
        throw i2cSetupException( errMessage );
    }
    return fileHandle;
}

int i2cDevice::writeToDevice( size_t _bufferSize ) throw( i2cSetupException& )
{
    if ( !deviceInitialised )
        throw i2cSetupException( "i2c Device Not Initialised ( try : 'obj->initDevice()' )" );
    try {
        if ( _bufferSize > ONE_BYTE ) {
            readAndWriteBuffer[ 0 ] = registerAddress;
            readAndWriteBuffer[ 1 ] = registerValue;
            write( getDeviceFileHandle(), readAndWriteBuffer, _bufferSize );
        }
        else {
            writeBufferOnly[ 0 ] = registerAddress;
            write( getDeviceFileHandle(), writeBufferOnly, _bufferSize );
        }
    }
    catch ( exception& e ) {
        snprintf( errMessage, sizeof( errMessage ), "Fatal i2c Error - Unable to write to file : %s",
                getFilePath());
        throw i2cSetupException( errMessage );
    }

    return EXIT_SUCCESS;
}

int i2cDevice::stop( pthread_t threadHandle )
{
    //pthread_cancel doesn't throw an exception, only returns error codes - these are handled below.
    int threadRet = pthread_cancel( threadHandle );

    if ( threadRet != 0 ) {
        //The sonic sensor thread cancellation failed, set the status to "Error" and throw an appropriate exception.
        setStatus( deviceStatus::Error );
        if ( threadRet == ESRCH ) {
            //Unable to locate process to cancel.
            throw i2cRuntimeException( i2c::THREAD_CANCELLATION_FAILURE );
        }
        else {
            //An unknown error occurred - unknown error code.
            throw i2cRuntimeException( i2c::THREAD_CANCELLATION_UNKNOWN );
        }
    }

    //The thread was cancelled successfully - set the device status to "Off".
    setStatus( deviceStatus::Off );

    //return the current device status, should always be Off here.
    return getStatus();

}