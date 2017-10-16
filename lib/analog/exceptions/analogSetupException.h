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

#ifndef QUADRO_ANALOGSETUPEXCEPTION_H
#define QUADRO_ANALOGSETUPEXCEPTION_H

#include "../../exceptions/setupException.h"

using namespace quadro::exceptions;

namespace quadro {

    namespace analog {

        using namespace std;

        const string STARTUP_FAILURE = "Unable to start the analog device.";
        const string THREAD_UNKNOWN = "Unable to create thread : Unknown Error Occurred.";
        const string THREAD_FATAL = "Unable to create thread : Fatal Error Occurred.";
        const string THREAD_PERMISSIONS = "Unable to create thread : Operation not permitted.";
        const string THREAD_INVALID_ARG = "Unable to create thread : Invalid Argument.";

        /**
        * This class will handle any Analog Device Setup Errors
        */
        class analogSetupException : public setupException {
        public:
            /**
             * Public access point to throw AnalogSetupExceptions
             * @param _errMsg
             */
            explicit analogSetupException( const string& _errMsg ) { }
        };

    }
}

#endif //QUADRO_ANALOGSETUPEXCEPTION_H
