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

#include <stdio.h>

#include "memcontext.h"

int main() {
    MemContextExample &mem_ctx = MemContextExample::get_instance();

    try {
        mem_ctx.run();
    } catch (TimerException &e) {
        printf("%s\n", e.what_c());
    } catch (MemContextException &e) {
        printf("%s\n", e.what_c());        
    }

    return 0;
}