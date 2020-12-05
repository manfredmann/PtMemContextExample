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

#include "memcontext.h"

MemContextExample::MemContextExample() {
    window      = NULL;
    label       = NULL;
    mc          = NULL;
    buf_draw    = NULL;
    timer       = NULL;
    is_attached = 0;
// ============================

    PhChannelParms_t    parms       = {0, 0, Ph_DYNAMIC_BUFFER};

    if (!PhAttach(NULL, &parms)) {
        return;
    }

    is_attached = 1;

    PtInit(NULL);
    PgSetDrawBufferSize(0xFFFF);

    PtArg_t     args_win[20];
    PtArg_t     args_lbl[6];
    int         arg_i = 0;

    win_area.pos.x = 0;
    win_area.pos.y = 0;
    win_area.size.w = 800;
    win_area.size.h = 800;

// ============================

    PtSetArg(&args_win[arg_i++], Pt_ARG_MIN_WIDTH,      win_area.size.w, 0);
    PtSetArg(&args_win[arg_i++], Pt_ARG_MIN_HEIGHT,     win_area.size.h, 0);
    PtSetArg(&args_win[arg_i++], Pt_ARG_MAX_HEIGHT,     win_area.size.w, 0);
    PtSetArg(&args_win[arg_i++], Pt_ARG_MAX_WIDTH,      win_area.size.h, 0);
    PtSetArg(&args_win[arg_i++], Pt_ARG_WINDOW_TITLE,   "Memory context example", 0);
    PtSetArg(&args_win[arg_i++], Pt_ARG_WINDOW_RENDER_FLAGS,
        Ph_WM_RENDER_ASAPP |
        Ph_WM_RENDER_CLOSE |
        Ph_WM_RENDER_TITLE |
        Ph_WM_RENDER_MIN,
        Pt_TRUE);

    PtSetArg(&args_win[arg_i++], Pt_ARG_WINDOW_CURSOR_OVERRIDE, Pt_TRUE, 0);
    PtSetArg(&args_win[arg_i++], Pt_ARG_WINDOW_STATE,           Ph_WM_STATE_ISFRONT, 0);
    PtSetArg(&args_win[arg_i++], Pt_ARG_CURSOR_TYPE,            Ph_CURSOR_NONE, 0);

    PtSetParentWidget(NULL);

    window = PtCreateWidget(PtWindow, NULL, arg_i, args_win);

// ============================

    lbl_area.pos.x  = 0;
    lbl_area.pos.y  = 0;
    lbl_area.size   = win_area.size;

    buf_draw        = new PhImage_t;
    buf_draw->type  = Pg_IMAGE_DIRECT_888;
    buf_draw->size  = lbl_area.size;
    buf_draw->image = new char[lbl_area.size.w * lbl_area.size.h * 3];
    arg_i           = 0;

    PtSetArg(&args_lbl[arg_i++], Pt_ARG_LABEL_TYPE,     Pt_IMAGE, 0 );
    PtSetArg(&args_lbl[arg_i++], Pt_ARG_AREA,           &lbl_area, 0 );
    PtSetArg(&args_lbl[arg_i++], Pt_ARG_LABEL_DATA,     buf_draw, sizeof(*buf_draw));
    PtSetArg(&args_lbl[arg_i++], Pt_ARG_MARGIN_HEIGHT,  0, 0);
    PtSetArg(&args_lbl[arg_i++], Pt_ARG_MARGIN_WIDTH,   0, 0);
    PtSetArg(&args_lbl[arg_i++], Pt_ARG_BORDER_WIDTH,   0, 0);

    label = PtCreateWidget(PtLabel, window, arg_i, args_lbl);

// ============================

    PhPoint_t translation = { 0, 0 };
    mc = PmMemCreateMC(buf_draw, &win_area.size, &translation);

    PtRealizeWidget(window);
    PtWindowToFront(window);
    PtWindowFocus(window);

    app = PtDefaultAppContext();

    PtAppAddInput(app, 0, MemContextExample::input_callback, NULL);

    timer = new Timer(0, 25 * 1000 * 1000);

    ya_label = new YaLabel;

    PhPoint_t ya_pos;
    
    ya_label->set_text("Ya Metko!");
    ya_label->set_color(0x5555FF);

    ya_pos.x = (lbl_area.size.w / 2) - ya_label->get_size().w / 2;
    ya_pos.y = 0;

    ya_label->set_pos(ya_pos);

    dir = DIR_DOWN_RIGHT;

}

MemContextExample::~MemContextExample() {
    if (mc != NULL) {
        PmMemReleaseMC(mc);

        mc = NULL;
    }

    if (buf_draw != NULL) {
        delete buf_draw;
    }

    if (timer != NULL) {
        delete timer;
    }
}

void MemContextExample::run() {
    if (is_attached == 0) {
        throw MemContextException("Couldn't attach to Photon manager");
    }

    draw();
    
    PtMainLoop();
}

int MemContextExample::input_callback(void *data, pid_t rcv_id, void *message, size_t size) {
    MemContextExample &mem_ctx = MemContextExample::get_instance();

    if (mem_ctx.timer == NULL) {
        return Pt_CONTINUE;
    }

    if (mem_ctx.timer->get_proxy() == rcv_id) {
        mem_ctx.move();
        mem_ctx.draw();
    }

    return Pt_CONTINUE;
}

void MemContextExample::draw() {
    PmMemStart(mc);

    PgSetFillColor(0x000000);
    PgDrawIRect(lbl_area.pos.x, lbl_area.pos.y, lbl_area.size.w, lbl_area.size.h, Pg_DRAW_FILL );

    ya_label->draw();

    PmMemFlush(mc, buf_draw);
    PmMemStop(mc);

    PtArg_t args[1];
    PtSetArg(&args[0], Pt_ARG_LABEL_DATA, buf_draw, sizeof(*buf_draw));
    PtSetResources(label, 1, args);
}

void MemContextExample::move() {
    PhPoint_t   pos     = ya_label->get_pos();
    PhDim_t     size    = ya_label->get_size();

    switch(dir) {
        case DIR_DOWN_RIGHT: {
            pos.x++;
            pos.y++;

            if ((pos.x + (size.w / 2) + 1) == lbl_area.size.w) {
                dir = DIR_DOWN_LEFT;
            }
            break;
        }
        case DIR_DOWN_LEFT: {
            pos.x--;
            pos.y++;

            if (pos.y == lbl_area.size.h) {
                dir = DIR_UP_LEFT;
            }
            break;
        }
        case DIR_UP_LEFT: {
            pos.y--;
            pos.x--;

            if (pos.x == -(size.w / 2) - 1  ) {
                dir = DIR_UP_RIGHT;
            }
            break;
        }
        case DIR_UP_RIGHT: {
            pos.y--;
            pos.x++;

            if (pos.y == 0) {
                dir = DIR_DOWN_RIGHT;
            }
            break;
        }
    }

    ya_label->set_pos(pos);
}