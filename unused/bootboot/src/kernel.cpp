/*
 * mykernel/cpp/kernel.cpp
 *
 * Copyright (C) 2017 - 2021 bzt (bztsrc@gitlab)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This file is part of the BOOTBOOT Protocol package.
 * @brief A sample BOOTBOOT compatible kernel
 *
 */
#pragma once

///* we don't assume cstdint exists */
#include "GEOS/master.h"
#include "bootboot.h"

/* imported virtual addresses, see linker script */
extern BOOTBOOT bootboot;               // see bootboot.h
extern unsigned char environment[4096]; // configuration, UTF-8 text key=value pairs
extern uint8_t fb;                      // linear framebuffer mapped

/******************************************
 * Entry point, called by BOOTBOOT Loader *
 ******************************************/
void colorScreen(uint32_t c)
{
    uint32_t* framebuffer = bootboot.fb_ptr;
    for(uint64_t pixel = 0;pixel<bootboot.fb_width*bootboot.fb_height;pixel++)
        framebuffer[pixel] = c;
}

int main()
{
    //setup to enter geos_main
    geos::video::screenWidth  = bootboot.fb_width ;
    geos::video::screenHeight = bootboot.fb_height;
    geos::video::framebuffer  = bootboot.fb_ptr   ;
    colorScreen(0x00050505);
    geos_main();

    //hang up (this could should never be reached in a release build)
    while(1);
}

