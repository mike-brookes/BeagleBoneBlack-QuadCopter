//
// Created by Michael Brookes on 10/02/2017.
//

#ifndef QUADRO_PWMSETUPEXCEPTION_H
#define QUADRO_PWMSETUPEXCEPTION_H

#include "../../exceptions/setupException.h"

using namespace quadro::exceptions;
using namespace std;

namespace quadro {

    namespace pwm {

        class pwmSetupException : public setupException {
        public:
            /**
             * Public access point to throw i2cSetupExceptions
             * @param _errMsg
             */
            explicit pwmSetupException( string _errMsg ) { }
        };

    }

}

#endif //QUADRO_PWMSETUPEXCEPTION_H
