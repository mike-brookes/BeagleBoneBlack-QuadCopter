//
// Created by Michael Brookes on 10/02/2017.
//

#ifndef QUADRO_OVERLAYSETUPEXCEPTION_H
#define QUADRO_OVERLAYSETUPEXCEPTION_H

#include "../../exceptions/setupException.h"

using namespace quadro::exceptions;

namespace quadro {

    namespace overlays {

        using namespace std;

        class overlaySetupException : public setupException {
        public:
            /**
             * Public access point to throw overlaySetupException
             * @param _errMsg
             */
            explicit overlaySetupException( const string& _errMsg ) { }
        };

    }

}

#endif //QUADRO_OVERLAYSETUPEXCEPTION_H
