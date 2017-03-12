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

#include "i2cDevice.h"

using namespace quadro::i2c;

    i2cDevice::i2cDevice()
    {
        this->deviceAddress = 0x00;
        this->busId = 0;
        this->deviceInitialised = false;
    }

    i2cDevice::~i2cDevice() { close( this->fileHandle ); }

    void i2cDevice::initDevice() throw( i2cSetupException& )
    {
        if ( !this->deviceAddress )
            throw i2cSetupException( "i2c Device Not Configured ( try : 'obj->setDeviceAddress([hex address])' )" );
        if ( !this->busId )
            throw i2cSetupException( "i2c Device Not Configured ( try : 'obj->setBusId([bus number])' )" );
        /*
         * ** ## -- Setup Stage -- ## ** *
         * setBusPaths : Saves the file paths to the available buses for ease of access.
         */
        this->setBusPaths();

        /*
         * ** ## -- Assignment Stage ( based on args ) -- ## ** *
         * validateBusId : Make sure we have a valid bus ID before proceeding.
         * selectABusPath : Used to specify which bus your i2c device is on.
         * setDeviceAddress: Hex value for your specific i2c Device.
         */
        this->validateBusId();
        this->selectABusPath();

        /*
         * ** ## -- init Stage -- ## ** *
         * openDevice : Creates a file handle for the device, should it be closed? Probably... :)
         * connectToDevice : Assigns the device as an i2c Slave and checks availability using IOCTL
         *
         * More info on IOCTL : http://man7.org/linux/man-pages/man2/ioctl.2.html
         */
        this->openDevice();
        this->connectToDevice();

        this->deviceInitialised = true;
    }

    void i2cDevice::setBusPaths()
    {
        this->_bus[ 1 ].busPath = this->validateBusPath(( char* ) I2C_1 );
    }

    void i2cDevice::selectABusPath() { this->deviceBusPath = _bus[ this->busId ].busPath; }

    void i2cDevice::setRegisterAddress( unsigned char _registerAddress ) { this->registerAddress = _registerAddress; }

    void i2cDevice::setRegisterValue( unsigned char _RegisterValue ) { this->registerValue = _RegisterValue; }

    const char* i2cDevice::getFilePath() { return this->deviceBusPath; }

    int i2cDevice::getDeviceFileHandle() { return this->fileHandle; }

    int i2cDevice::validateBusId() throw( i2cSetupException& )
    {
        if ( this->busId > I2C_BUS_COUNT || this->busId < 1 ) {
            snprintf( this->errMessage, sizeof( this->errMessage ), "Bus ID : %d  is not a valid BUS for this device.",
                    this->busId );
            throw ( i2cSetupException( this->errMessage ));
        }
        else
            return EXIT_SUCCESS;
    }

    char* i2cDevice::validateBusPath( char* _busProposedPath ) throw( i2cSetupException& )
    {
        if ( stat( _busProposedPath, &buffer ) == 0 )
            return _busProposedPath;
        else {
            snprintf( this->errMessage, sizeof( this->errMessage ),
                    "Fatal i2c Error - Unable to locate the i2c Bus file : %s", _busProposedPath );
            throw i2cSetupException( this->errMessage );
        }
    }

    short i2cDevice::getValueFromRegister( unsigned char _RegisterAddress )
    {
        if ( !this->deviceInitialised )
            throw i2cSetupException( "i2c Device Not Initialised ( try : 'obj->initDevice()' )" );
        this->setRegisterAddress( _RegisterAddress );
        this->writeBufferOnly[ 0 ] = this->registerAddress;
        if ( write( this->getDeviceFileHandle(), this->writeBufferOnly, 1 ) == 1 ) {
            return this->readDevice( ONE_BYTE );
        }
        else {
            snprintf( this->errMessage, sizeof( this->errMessage ), "Fatal i2c Error - Unable to write to file : %s",
                    this->getFilePath());
            throw i2cSetupException( this->errMessage );
        }
    }

    short i2cDevice::readDevice( size_t _BufferSize ) throw( i2cSetupException& )
    {
        if ( !this->deviceInitialised )
            throw i2cSetupException( "i2c Device Not Initialised ( try : 'obj->initDevice()' )" );
        unsigned char buff[_BufferSize];
        if ( read( this->getDeviceFileHandle(), buff, _BufferSize ) != _BufferSize ) {
            snprintf( this->errMessage, sizeof( this->errMessage ), "Fatal i2c Error - Unable to read from file : %s",
                    this->getFilePath());
            throw i2cSetupException( this->errMessage );
        }
        else
            return buff[ 0 ];
    }

    int i2cDevice::openDevice() throw( i2cSetupException& )
    {
        this->fileHandle = open( this->getFilePath(), O_RDWR );
        if ( this->fileHandle == 0 ) {
            snprintf( this->errMessage, sizeof( this->errMessage ), "Fatal i2c Error - Unable to open file : %s",
                    this->getFilePath());
            throw i2cSetupException( this->errMessage );
        }
        return this->fileHandle;
    }

    int i2cDevice::writeToDevice( size_t _bufferSize ) throw( i2cSetupException& )
    {
        if ( !this->deviceInitialised )
            throw i2cSetupException( "i2c Device Not Initialised ( try : 'obj->initDevice()' )" );
        try {
            if ( _bufferSize > ONE_BYTE ) {
                this->readAndWriteBuffer[ 0 ] = this->registerAddress;
                this->readAndWriteBuffer[ 1 ] = this->registerValue;
                write( this->getDeviceFileHandle(), this->readAndWriteBuffer, _bufferSize );
            }
            else {
                this->writeBufferOnly[ 0 ] = this->registerAddress;
                write( this->getDeviceFileHandle(), this->writeBufferOnly, _bufferSize );
            }
        }
        catch ( exception& e ) {
            snprintf( this->errMessage, sizeof( this->errMessage ), "Fatal i2c Error - Unable to write to file : %s",
                    this->getFilePath());
            throw i2cSetupException( this->errMessage );
        }

        return EXIT_SUCCESS;
    }