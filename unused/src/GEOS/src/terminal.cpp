/**
 * Created Date: Wednesday October 26th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Saturday November 19th 2022 8:05:57 pm
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

terminal::terminal(){}

terminal::terminal(uint32_t px,uint32_t ph)
    :pixelWidth(px),pixelHeight(ph){}
    
terminal::~terminal(){}

void terminal::clear()
{
    memset<u32>(this->getFrameBufferAddr(),this->pixelHeight*this->pixelWidth,this->backColor);
    this->currentCol = 0;
    this->currentLine = 0;
}

void terminal::setFrameBufferAddr(uint32_t* fb)
{
    u32 line = 0;
    for(u32 pixel = 0;pixel<geos::video::screenWidth*(geos::video::screenHeight-1);pixel+=geos::video::screenWidth)
        screen[line++] = fb+pixel;
}

uint32_t* terminal::getFrameBufferAddr()
{
    return this->screen[0];
}

void terminal::write(const char* str, u64 len)
{
    for(u64 I = 0;I<len;I++)
        this->write(str[I]);
}
    
void terminal::write(const char* str)
{
    for(u32 I = 0;str[I]!=0x00;I++)
    {
        switch(str[I])
        {
            default:
                this->write(str[I]); 
                break;
        }
    }
}

void terminal::scroll()
{
    memcpy(this->screen[this->lineSpacing+height],this->screen[0],this->pixelWidth*(this->pixelHeight-height-this->lineSpacing));
    memzero(this->screen[0]+this->pixelWidth*(this->pixelHeight-height-this->lineSpacing),this->pixelWidth*(this->pixelHeight+height+this->lineSpacing));
}

void terminal::write(char c)
{
    //FIXME: no scrolling, trying to scroll reboots the system
    if(c == 0x00){return;}
    else if(c == '\n')
    {
        this->currentLine++;
        this->currentCol = 0;
        return;
    }
    else if(c == '\b')
    {
        this->currentCol--;
        return;
    }
    else if(c == ' ')
    {
        if(this->rainbowText)
        {
            this->rainbowIndex++;
            this->rainbowIndex%=6;
            this->textColor = rainbowColors[this->rainbowIndex];
        }
    }

    unsigned char* glyph = geos::font::font8x8_basic[c];

    u32 maxCol = this->pixelWidth/(width);
    u32 maxLine = this->pixelWidth/(height+this->lineSpacing);
    for(u16 h = 0;h<height;h++)
    {
        for(u16 w = 0;w<width;w++)
        {
            //if(((currentLine+currentLine*lineSpacing)*height)+h >= maxLine && (currentCol*width)+w >= maxCol)
            //    this->scroll();

            if(getBit(glyph+h,w))
                screen[((currentLine+currentLine*lineSpacing)*height)+h][(currentCol*width)+w] = this->textColor;
            else
                screen[((currentLine+currentLine*lineSpacing)*height)+h][(currentCol*width)+w] = this->backColor;
        }
    }
    this->currentCol++;
    if(this->currentCol*width >= this->pixelWidth)
    {
        this->currentCol %= this->pixelWidth/width;
        this->currentLine++;
    }
}
