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

#ifndef QUADRO_RUNTIMEEXCEPTIONS_H
#define QUADRO_RUNTIMEEXCEPTIONS_H

#include <cstdio>
#include <exception>
#include <string>
#include <utility>
#include <utility>

namespace quadro {

    namespace exceptions {

        using namespace std;

        /**
         * TODO: add logging.
         */
        class runtimeException : public exception {
        public:

            runtimeException() = default;

            explicit runtimeException( string errMessage )
                    :errMessage_( std::move( std::move( errMessage ))) { }

            const char* what() const throw() override { return errMessage_.c_str(); }

            string errMessage_;
        };

    }

}

#endif //QUADRO_RUNTIMEEXCEPTIONS_H
