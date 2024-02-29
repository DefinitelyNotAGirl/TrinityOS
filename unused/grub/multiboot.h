/**
 * Created Date: Friday November 25th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Friday November 25th 2022 12:05:42 pm
 * Modified By: DefinitelyNotAGirl@github (definitelynotagirl115199@gmail.com)
 * -----
 * Copyright (c) 2022 DefinitelyNotAGirl@github
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
 */
#pragma once
#include "../master.h"

struct mutlibootInfo
{
    uint32_t flags                ;
    uint32_t mem_lower            ;
    uint32_t mem_upper            ;
    uint32_t boot_device          ;
    uint32_t cmdline              ;
    uint32_t mods_count           ;
    uint32_t mods_addr            ;
    uint32_t syms             [4] ;
    uint32_t mmap_length          ;
    uint32_t mmap_addr            ;
    uint32_t drives_length        ;
    uint32_t drives_addr          ;
    uint32_t config_table         ;
    uint32_t boot_loader_name     ;
    uint32_t apm_table            ;
    uint32_t vbe_control_info     ;
    uint32_t vbe_mode_info        ;
    uint16_t vbe_mode             ;
    uint16_t vbe_interface_seg    ;
    uint16_t vbe_interface_off    ;
    uint16_t vbe_interface_len    ;
    uint64_t framebuffer_addr     ;
    uint32_t framebuffer_pitch    ;
    uint32_t framebuffer_width    ;
    uint32_t framebuffer_heigh    ;
    uint8_t  framebuffer_bpp      ;
    uint8_t  framebuffer_type     ;
    uint8_t  color_info        [5];

} PACKED ;
