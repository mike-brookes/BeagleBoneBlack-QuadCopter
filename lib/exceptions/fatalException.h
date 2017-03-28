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

#ifndef QUADRO_AFATALEXCEPTION_H
#define QUADRO_AFATALEXCEPTION_H

#include <cstdio>
#include <exception>
#include <string>

namespace quadro {

    namespace exceptions {

        using namespace std;

        /**
         * TODO: add logging.
         */
        class fatalException : public exception {
        public:

            fatalException() { }

            fatalException( string errMessage )
                    :errMessage_( errMessage ) { }

            const char* what() const throw() { return errMessage_.c_str(); }

            string errMessage_;
        };

    }

}

#endif //QUADRO_AFATALEXCEPTION_H