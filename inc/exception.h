/*
* PtMemContextExample - Memory Context draw example for QNX4.25/Photon
* Copyright (C) 2020 Roman Serov <roman@serov.co>
*
* This file is part of PtMemContextExample for QNX4.25/Photon.
* 
* PtMemContextExample for QNX4.25/Photon is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* PtMemContextExample for QNX4.25/Photon is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with PtMemContextExample for QNX4.25/Photon. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdio.h>
#include <stdarg.h>
#include <String.h>

//Вещества были забористые
class BaseException {
    public:
        BaseException(String msg) {
            this->msg = msg;
        }

        BaseException(const char *fmt, va_list args) {
            memset(buffer, 0x0, 1024);

            _vbprintf(buffer, 1024, fmt, args);

            this->msg = String(buffer);

        }

        String what() {
            return this->msg;
        }

        const char * what_c() {
            return (const char *) this->msg;
        }

    private:
        String  msg;
        char    buffer[1024];
        va_list args_;
};

#endif
