//
// Created by Michael Brookes on 08/02/2017.
//

#ifndef QUADRO_ANALOGSETUPEXCEPTION_H
#define QUADRO_ANALOGSETUPEXCEPTION_H

#include "../../Exceptions/setupException.h"

using namespace quadro::exceptions;

namespace quadro {

    namespace analog {

        using namespace std;

        /**
        * This class will handle any Analog Device Setup Errors
        */
        class analogSetupException : public setupException {
        public:
            /**
             * Public access point to throw AnalogSetupExceptions
             * @param _errMsg
             */
            analogSetupException( string _errMsg ) { }
        };

    }
}

#endif //QUADRO_ANALOGSETUPEXCEPTION_H
