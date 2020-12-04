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

#include <string.h>

#include "yalabel.h"

static const char *yalabel_font = "pcterm20";

static unsigned int get_string_width(const char *font, const char *str) {
    PhRect_t rect;

    PfExtentText(&rect, NULL, font, str, strlen(str));

    return rect.lr.x - rect.ul.x + 1;
}

static unsigned int get_string_height(const char *font, const char *str) {
    PhRect_t rect;

    PfExtentText(&rect, NULL, font, str, strlen(str));

    return rect.lr.y - rect.ul.y + 1;
}

static void draw_string(PhPoint_t p, const char *str, const char *font, unsigned int color) {
    PgSetFont(font);
    PgSetTextColor(color);
    PgDrawText(str, strlen(str), &p, 0);
}

YaLabel::YaLabel() {

}

void YaLabel::draw() {
    PhRect_t  rect;
    
    rect.ul.x = pos.x;
    rect.ul.y = pos.y;
    rect.lr.x = pos.x + size.w;
    rect.lr.y = pos.y + size.h;

    PgSetUserClip(&rect);

    PhPoint_t draw_pos = {pos.x, pos.y + size.h};

    draw_string(draw_pos, (const char *) text, yalabel_font, color);

    PtClipRemove();

}

void YaLabel::set_text(String text) {
    this->size.w    = get_string_width(yalabel_font, (const char *) text);
    this->size.h    = get_string_height(yalabel_font, (const char *) text);
    this->text      = text;
}

void YaLabel::set_pos(PhPoint_t pos) {
    this->pos = pos;
}

void YaLabel::set_color(PgColor_t color) {
    this->color = color;
}

PhPoint_t YaLabel::get_pos() {
    return pos;
}

PhDim_t YaLabel::get_size() {
    return size;
}
