/**
 * Created Date: Wednesday October 26th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Wednesday October 26th 2022 9:28:10 pm
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

uint32_t tempColor  = 0x00000000;
uint32_t INFOCOLOR  = 0x000084ff;
uint32_t WARNCOLOR  = 0x00FF5500;
uint32_t ERRORCOLOR = 0x00FF0000;
uint32_t OKCOLOR    = 0x0000FF00;

const char* PRINT_INFO = "[INFO]";
const char* PRINT_WARN = "[WARNING]";
const char* PRINT_ERROR = "[ERROR]";
const char* PRINT_FAILED = " [FAILED]\n";
const char* PRINT_OK = " [OK]\n";

void printINFO(const char* str)
{
    tempColor = lterm->textColor;
    lterm->textColor = INFOCOLOR;
    lterm->write(PRINT_INFO);
    lterm->textColor = tempColor;
    lterm->write(str);
}

void printWARNING(const char* str)
{
    tempColor = lterm->textColor;
    lterm->textColor = WARNCOLOR;
    lterm->write(PRINT_WARN);
    lterm->textColor = tempColor;
    lterm->write(str);
}

void printERROR(const char* str)
{
    tempColor = lterm->textColor;
    lterm->textColor = ERRORCOLOR;
    lterm->write(PRINT_ERROR);
    lterm->textColor = tempColor;
    lterm->write(str);
}

void printOK()
{
    tempColor = lterm->textColor;
    lterm->textColor = OKCOLOR;
    lterm->write(PRINT_OK);
    lterm->textColor = tempColor;
}

void printFAILED()
{
    tempColor = lterm->textColor;
    lterm->textColor = ERRORCOLOR;
    lterm->write(PRINT_FAILED);
    lterm->textColor = tempColor;
}

void printValue(bool b,const char* name)
{
    printINFO(name);
    lterm->write(": ");
    if(b)
        lterm->write("true");
    else
        lterm->write("false");
}

void printValue(uint32_t v,const char* name)
{
    char valueStr[30] = {0x00};
    INTTS(v,10,valueStr);
    printINFO(name);
    lterm->write(": ");
    lterm->write(valueStr);
}


void printValue(int64_t v,const char* name)
{
    printINFO(name);
    char valueStr[30] = {0x00};
    INTTS(v,16,valueStr);
    printINFO(name);
    lterm->write(": 0x");
    lterm->write(valueStr);
}

void printHEXU64(uint64_t v,const char* name)
{
    char pstr[STR_POINTER_LEN] = {0x00};
    PTS(pstr,v);
    printINFO(name);
    lterm->write(": ");
    lterm->write(pstr,STR_POINTER_LEN);
}
