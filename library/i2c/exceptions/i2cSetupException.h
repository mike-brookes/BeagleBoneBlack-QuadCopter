//
// Created by Michael Brookes on 10/02/2017.
//

#ifndef QUADRO_I2CSETUPEXCEPTION_H
#define QUADRO_I2CSETUPEXCEPTION_H

#include "../../Exceptions/setupException.h"

using namespace quadro::exceptions;

namespace quadro {

    namespace i2c {

        using namespace std;

        class i2cSetupException : public setupException {
        public:
            /**
             * Public access point to throw i2cSetupExceptions
             * @param _errMsg
             */
            i2cSetupException( string _errMsg ) { }
        };

    }

}

#endif //QUADRO_I2CSETUPEXCEPTION_H
