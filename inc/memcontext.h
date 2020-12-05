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

#ifndef MEMCTX_H
#define MEMCTX_H

#include <Ap.h>
#include <Ph.h>
#include <Pt.h>

#include <photon/Pf.h>
#include <photon/PhRender.h>
#include <photon/PtLabel.h>

#include <String.h>

#include "timer.h"
#include "yalabel.h"

typedef enum {
    DIR_DOWN_RIGHT,
    DIR_DOWN_LEFT,
    DIR_UP_LEFT,
    DIR_UP_RIGHT,
} direction_t;

class MemContextException : public BaseException {
    public:
        MemContextException(String msg) : BaseException(msg) { } 
        MemContextException(const char *fmt, ...) : BaseException(fmt, (va_start(args_, fmt), args_)) {
            va_end(args_);
        }

    private:
        va_list args_;
};

class MemContextExample {
    public:
        ~MemContextExample();

        static MemContextExample &get_instance() {
            static MemContextExample mem_ctx;

            return mem_ctx;
        }

        void        run();
        void        move();
        static int  input_callback(void *data, pid_t rcv_id, void *message, size_t size);

    private:
        MemContextExample();

        int                 is_attached;

        PtWidget_t *        window;
        PtWidget_t *        label;

        PhArea_t            win_area;
        PhArea_t            lbl_area;

        PtAppContext_t      app;
        PmMemoryContext_t * mc;
        PhImage_t *         buf_draw;

        void                draw();

        Timer *             timer;

        YaLabel *           ya_label;

        direction_t         dir;
};

#endif
