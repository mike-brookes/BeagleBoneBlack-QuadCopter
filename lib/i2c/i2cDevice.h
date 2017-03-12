//
// Created by Michael Brookes on 09/04/2016.
//

#ifndef I2CDEVICE_H
#define I2CDEVICE_H

#include "../Interfaces/IDevice.h"
#include "exceptions/i2cSetupException.h"

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/stat.h>

#define I2C_BUS_COUNT   1               //!< How many I2C buses are available. Add paths below as required.
#define I2C_1           "/dev/i2c-1"    //!< File Path for the i2c-1 bus.

#define ONE_BYTE        1               //!< Used for specifying how many bytes to read
#define TWO_BYTES       2               //!< Used for specifying how many bytes to write
#define MAX_BUFF        1024            //!< Used to store fatal error.

namespace quadro {

    namespace i2c {

        class i2cDevice : public IDevice {

        public:
            /**
             \fn Public Destructor
             */
            ~i2cDevice();

            /**
             \fn Public Constructor
             */
            i2cDevice();

            /*i2c Specific Members*/

            /**
             \fn Public initDevice
             \brief Requires the device address and bus id to be configured.
             */
            void initDevice() throw( i2cSetupException& );

            /**
             \fn Public getValueFromRegister
             \param unsigned char _registerValue
             \brief Writes the register that you want to read, then performs a read on that register.
             */
            short getValueFromRegister( unsigned char _registerAddress );

            /**
             \fn Public setRegisterValue
             \param unsigned char _registerValue
             \brief Set the value that will next be written to the I2C device.
             */
            void setRegisterValue( unsigned char _registerValue );

            /**
             \fn Public setRegisterAddress
             \param unsigned char _registerAddress
             \brief Set the Register address that the _RegisterValue will be written to.
             */
            void setRegisterAddress( unsigned char _registerAddress );

            /**
             \fn Public writeToDevice
             \param size_t _bufferSize
             \brief Perform the write request. The _bufferSize is used to differentiate between a read or write request.
             */
            int writeToDevice( size_t _bufferSize ) throw( i2cSetupException& );

        private:

            /**
             \fn Private Struct I2CBus
             \brief used to store Bus Paths for ease of access.
             */
            struct I2CBus {
                const char* busPath;
            } _bus[I2C_BUS_COUNT];

            /**
             \fn Private Struct stat
             \brief used to check file paths.
             */
            struct stat buffer;

        protected:

            /**
             \fn Protected getDeviceHandle
             \param none
             \brief Returns the current fileHandle for reading and writing to the I2C device.
             */
            int getDeviceFileHandle();

            /**
             \fn Protected getFilePath
             \param none
             \brief Returns then filePath for accessing the I2C device.
             */
            const char* getFilePath();

            /**
             \fn Protected setBusPaths
             \param none
             \brief Set Path to all the available buses. As set with I2CBus (struct) and Defines.
             */
            void setBusPaths();

            /**
             \fn Protected validateBusId
             \param int _busId
             \brief Make sure the BusId being used is valid.
             */
            int validateBusId() throw( i2cSetupException& );

            /**
             \fn Protected validateBusPath
             \param I2CBus _busId
             \brief Make sure the busPath exists.
             */
            char* validateBusPath( char* _busProposedPath ) throw( i2cSetupException& );

            /**
             \fn Protected selectABusPath
             \param none
             \brief Select which Bus Path we can find your I2C device at.
             */
            void selectABusPath();

            /**
             \fn Protected setDeviceAddress
             \param int _deviceAddress
             \brief Used to store the device address (Hex)
             */
            virtual void setDeviceAddress( unsigned char _deviceAddress ) = 0;

            /**
             \fn Protected setBusId
             \param int _busId
             \brief Used to store the bus id (int)
             */
            virtual void setBusId( int _busId ) = 0;

            /* From IDevice Interface*/

            /**
             \fn Protected connectToDevice
             \param none
             \brief Sets up an IOCTL connection to the I2C device as a Slave for Linux.
             */
            int connectToDevice() { return ioctl( this->fileHandle, I2C_SLAVE, this->deviceAddress ); };

            /**
             \fn Protected openDevice
             \param none
             \brief Attempt to open the fileHandle.
             */
            int openDevice() throw( i2cSetupException& );

            /**
             \fn Protected readDevice
             \param size_t _bufferSize
             \brief Reads the current buffer from the I2C device - first writes the register address that will be read.
             */
            short readDevice( size_t _bufferSize ) throw( i2cSetupException& );

            const char* deviceBusPath;

            unsigned char deviceAddress;
            unsigned char registerValue;
            unsigned char registerAddress;

            char readAndWriteBuffer[TWO_BYTES];
            char writeBufferOnly[ONE_BYTE];

            char errMessage[MAX_BUFF];
            int fileHandle;
            int busId;

            bool deviceInitialised;

        };

    }

}

#endif //I2CDEVICE_H
