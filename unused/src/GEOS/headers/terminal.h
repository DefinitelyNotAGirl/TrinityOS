/**
 * Created Date: Wednesday October 26th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Wednesday October 26th 2022 6:10:46 pm
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

uint32_t rainbowColors[6] = {0x00E50000,0x00FF8D00,0x00FFEE00,0x00028121,0x00004CFF,0x00760088};
class terminal
{
private:
    u32 pixelWidth = 0;
    u32 pixelHeight = 0;
    u16 rows = 0;
    u16 columns = 0;
    u32** screen = 0;
    u16 lineSpacing = 1;

    u32 currentLine = 0;
    u32 currentCol = 0;
    u16 height = 8;
    u16 width = 8;

    u16 rainbowIndex = 0;

public:
    terminal();
    terminal(uint32_t px,uint32_t ph);
    ~terminal();

    u32 textColor = 0x00999999;
    u32 backColor = 0x00000000;

    bool rainbowText = 0;

    void write(const char* str);
    void write(const char* str, u64 len);
    void write(char c);
    void clear();
    void scroll();
    void setFrameBufferAddr(uint32_t* fb);
    uint32_t* getFrameBufferAddr();
};
terminal* lterm;
