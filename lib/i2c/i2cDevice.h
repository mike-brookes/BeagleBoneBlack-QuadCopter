//
// Created by Michael Brookes on 09/04/2016.
//

#ifndef I2CDEVICE_H
#define I2CDEVICE_H

#include "../Interfaces/IDevice.h"
#include "exceptions/i2cSetupException.h"
#include "exceptions/i2cRuntimeException.h"

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

        /**
         * A base class for I2C devices, handles a lot of the lower level aspects like setting up the slave device, reading and writing to the device etc.
         */
        class i2cDevice : public IDevice {

        public:
            /**
             * Public Destructor
             */
            ~i2cDevice() override;

            /**
             * Public Constructor
             */
            i2cDevice();

            /*i2c Specific Members*/

            /**
             * Public initDevice - Requires the device address and bus id to be configured.
             */
            void initDevice() throw( i2cSetupException& ) override;

            /**
             * Public getValueFromRegister - Writes the register that you want to read, then performs a read on that register.
             *
             * @param unsigned char _registerValue
             * @return short
             */
            short getValueFromRegister( unsigned char _registerAddress );

            /**
             * Public setRegisterValue - Set the value that will next be written to the I2C device.
             *
             * @param unsigned char _registerValue
             */
            void setRegisterValue( unsigned char _registerValue );

            /**
             * Public setRegisterAddress - Set the Register address that the _RegisterValue will be written to.
             *
             * @param unsigned char _registerAddress
             */
            void setRegisterAddress( unsigned char _registerAddress );

            /**
             * Public writeToDevice - Perform the write request. The _bufferSize is used to differentiate between a read or write request.
             *
             * @param size_t _bufferSize
             * @throws i2cSetupException
             * @return int
             */
            int writeToDevice( size_t _bufferSize ) throw( i2cSetupException& ) override;

            /**
             * stop() - Allows the independent control to stop the specified thread.
             *
             * @param pthread_t threadHandle
             * @throws i2cRuntimeException
             * @returns enum deviceStatus : 1 = on, 0 = off or 2 = error
             */
            int stop( pthread_t threadHandle );

        private:

            /**
             Private Struct I2CBus - used to store Bus Paths for ease of access.
             */
            struct I2CBus {
                const char* busPath; //!< @var contains the path to the select I2C bus
            } _bus[I2C_BUS_COUNT];

            struct stat buffer; //!< @var Private Struct stat used to check file paths.

        protected:

            /*!
             * Stores the current deviceStatus for easy reference fro other objects
             */
            enum deviceStatus {
                On = 1, //!< Status On (thread is active)
                Off = 0, //!< Status Off (thread is disabled)
                Error = 2 //!< Status Error (thread is disabled)
            };

            /*!
             * getStatus returns the current status of the sensor
             *
             * @return int
             */
            int getStatus();

            /*!
             * setStatus allows the status of the sensor to be changed to one of the values set in deviceStatus
             *
             * @param _status
             */
            void setStatus( deviceStatus _status );

            deviceStatus currentStatus; //!< @var currentStatus holds a deviceStatus value

            /**
             * Protected getDeviceHandle - Returns the current fileHandle for reading and writing to the I2C device.
             *
             * @param none
             * @return int : The current fileHandle for reading and writing to the I2C device.
             */
            int getDeviceFileHandle();

            /**
             * Protected getFilePath - Returns then filePath for accessing the I2C device.
             *
             * @param none
             * @return char
             */
            const char* getFilePath();

            /**
             * Protected setBusPaths - Set Path to all the available buses. As set with I2CBus (struct) and Defines.
             *
             * @param none
             */
            void setBusPaths();

            /**
             * Protected validateBusId - Make sure the BusId being used is valid.
             *
             * @param int _busId
             * @throws i2cSetupException
             * @return int
             */
            int validateBusId() throw( i2cSetupException& );

            /**
             * Protected validateBusPath - Make sure the busPath exists.
             *
             * @param I2CBus _busId
             * @throws i2cSetupException
             * @return char
             */
            char* validateBusPath( char* _busProposedPath ) throw( i2cSetupException& );

            /**
             * Protected selectABusPath - Select which Bus Path we can find your I2C device at.
             *
             * @param none
             */
            void selectABusPath();

            /**
             * Protected setDeviceAddress - Used to store the device address (Hex)
             *
             * @param int _deviceAddress
             */
            virtual void setDeviceAddress( unsigned char _deviceAddress ) = 0;

            /**
             * Protected setBusId - Used to store the bus id (int)
             * @param int _busId
             */
            virtual void setBusId( int _busId ) = 0;

            /* From IDevice Interface*/

            /**
             * Protected connectToDevice - Sets up an IOCTL connection to the I2C device as a Slave for Linux.
             *
             * @param none
             * @return int
             */
            int connectToDevice() override { return ioctl( this->fileHandle, I2C_SLAVE, this->deviceAddress ); };

            /**
             * Protected openDevice - Attempts to open the fileHandle.
             *
             * @param none
             * @throws i2cSetupException
             * @return int
             */
            int openDevice() throw( i2cSetupException& ) override;

            /**
             * Protected readDevice - Reads the current buffer from the I2C device; first writes the register address that will be read.
             *
             * @param size_t _bufferSize
             * @throws i2cSetupException
             * @return short
             */
            short readDevice( size_t _bufferSize ) throw( i2cSetupException& ) override;

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
