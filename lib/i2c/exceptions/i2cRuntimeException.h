//
// Created by Michael Brookes on 26/03/2017.
//

#ifndef QUADRO_ANALOGRUNTIMEEXCEPTION_H
#define QUADRO_ANALOGRUNTIMEEXCEPTION_H

#include "../../exceptions/runtimeException.h"

namespace quadro {

    namespace i2c {

        using namespace std;

        const string THREAD_CANCELLATION_FAILURE = "Unable to cancel thread : Unable to locate process.";
        const string THREAD_CANCELLATION_UNKNOWN = "Unable to cancel thread : Unknown error, not a known error code.";
        /**
        * This class will handle any I2C Device RunTime Errors
        */
        class i2cRuntimeException : public runtimeException {
        public:
            /**
             * Public access point to throw I2C Runtime Exceptions
             * @param _errMsg
             */
            i2cRuntimeException( string _errMsg ) { }
        };

    }
}

#endif //QUADRO_ANALOGRUNTIMEEXCEPTION_H
