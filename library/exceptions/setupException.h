//
// Created by Michael Brookes on 08/02/2017.
//

#ifndef QUADRO_ASETUPEXCEPTION_H
#define QUADRO_ASETUPEXCEPTION_H

#include <cstdio>
#include <exception>
#include <string>

namespace quadro {

    namespace exceptions {

        using namespace std;

        class setupException : public exception {
        public:

            setupException() { }

            setupException( string errMessage )
                    :errMessage_( errMessage ) { }

            const char* what() const throw() { return errMessage_.c_str(); }

            string errMessage_;
        };

    }

}

#endif //QUADRO_ASETUPEXCEPTION_H