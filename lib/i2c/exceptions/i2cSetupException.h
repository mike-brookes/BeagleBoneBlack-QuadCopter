//
// Created by Michael Brookes on 10/02/2017.
//

#ifndef QUADRO_I2CSETUPEXCEPTION_H
#define QUADRO_I2CSETUPEXCEPTION_H

#include "../../exceptions/setupException.h"

using namespace quadro::exceptions;

namespace quadro {

    namespace i2c {

        using namespace std;

        static const string STARTUP_FAILURE = "Unable to start the I2C device.";
        static const string THREAD_UNKNOWN = "Unable to create thread : Unknown Error Occurred.";
        static const string THREAD_FATAL = "Unable to create thread : Fatal Error Occurred.";
        static const string THREAD_PERMISSIONS = "Unable to create thread : Operation not permitted.";
        static const string THREAD_INVALID_ARG = "Unable to create thread : Invalid Argument.";

        class i2cSetupException : public setupException {
        public:
            /**
             * Public access point to throw i2cSetupExceptions
             * @param _errMsg
             */
            explicit i2cSetupException( const string& _errMsg ) { }
        };

    }

}

#endif //QUADRO_I2CSETUPEXCEPTION_H
