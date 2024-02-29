/**
 * Created Date: Sunday April 16th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Thursday May 25th 2023 2:27:13 am
 * Modified By: DefinitelyNotAGirl@github (definitelynotagirl115169@gmail.com)
 * -----
 * Copyright (c) 2023 DefinitelyNotAGirl@github
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
#include <misc>
#include <exception>
#include <string>

namespace klib
{
    void stringUTF8::replace(stringUTF8 target, stringUTF8 replacement)
    {
        list<stringUTF8> pieces = this->split(target);
        this->clear();
        for(stringUTF8 I : pieces)
        {
            for(char II : I)
                *this << II;
            for(char II : replacement)
                *this << II;
        }
    }

    list<stringUTF8> stringUTF8::split(stringUTF8 delimiter,u64 limit)
    {
        u64 dPOS = 0;

        list<stringUTF8> result;
        stringUTF8 working;

        for(char I : *this)
        {
            if(I != delimiter[dPOS])
                working << I;
            else
                dPOS++;
            if(dPOS == delimiter.size)
            {
                result << working;
                working.clear();
                dPOS = 0;
            }
        }
        if(working.size > 0)
            result << working;

        return result;
    }

    stringUTF8::stringUTF8(const char* str)
    {
        if(this->size != 0)
            this->clear();
        for(u64 I = 0;I<strlen((u64)str);I++)
            *this << str[I];
    }

    stringUTF8::stringUTF8(const stringUTF8& str)
    {
        this->size = str.size;
        this->data = str.data;
    }

    stringUTF8::stringUTF8(u64 x)
    {
        exception::FUNCTION_NOT_IMPLEMENTED();
    }
    stringUTF8::stringUTF8(u32 x)
    {
        exception::FUNCTION_NOT_IMPLEMENTED();
    }
    stringUTF8::stringUTF8(u16 x)
    {
        exception::FUNCTION_NOT_IMPLEMENTED();
    }
    stringUTF8::stringUTF8(u8 x)
    {
        exception::FUNCTION_NOT_IMPLEMENTED();
    }
    stringUTF8::stringUTF8(i64 x)
    {
        exception::FUNCTION_NOT_IMPLEMENTED();
    }
    stringUTF8::stringUTF8(i32 x)
    {
        exception::FUNCTION_NOT_IMPLEMENTED();
    }
    stringUTF8::stringUTF8(i16 x)
    {
        exception::FUNCTION_NOT_IMPLEMENTED();
    }
    stringUTF8::stringUTF8(i8 x)
    {
        exception::FUNCTION_NOT_IMPLEMENTED();
    }
    stringUTF8::stringUTF8(f32 x)
    {
        exception::FUNCTION_NOT_IMPLEMENTED();
    }
    stringUTF8::stringUTF8(f64 x)
    {
        exception::FUNCTION_NOT_IMPLEMENTED();
    }

    stringUTF8::stringUTF8(){}

    void stringUTF8::operator<<(stringUTF8 s)
    {
        klib::exception::FUNCTION_NOT_IMPLEMENTED();
    }
    void stringUTF8::operator<<(char* s)
    {
        klib::exception::FUNCTION_NOT_IMPLEMENTED();
    }
    void stringUTF8::operator<<(const char* s)
    {
        klib::exception::FUNCTION_NOT_IMPLEMENTED();
    }
    void stringUTF8::operator<<(char c)
    {
        klib::exception::FUNCTION_NOT_IMPLEMENTED();
    }
    void stringUTF8::operator<<(u64 i)
    {
        klib::exception::FUNCTION_NOT_IMPLEMENTED();
    }
    void stringUTF8::operator<<(i64 i)
    {
        klib::exception::FUNCTION_NOT_IMPLEMENTED();
    }
    void stringUTF8::operator<<(f64 d)
    {
        klib::exception::FUNCTION_NOT_IMPLEMENTED();
    }
    void stringUTF8::operator<<(f32 f)
    {
    klib::exception::FUNCTION_NOT_IMPLEMENTED();}
    stringUTF8::operator u64() const
    {
    klib::exception::FUNCTION_NOT_IMPLEMENTED();}
    stringUTF8::operator u32() const
    {
    klib::exception::FUNCTION_NOT_IMPLEMENTED();}
    stringUTF8::operator u16() const
    {
    klib::exception::FUNCTION_NOT_IMPLEMENTED();}
    stringUTF8::operator u8() const
    {
    klib::exception::FUNCTION_NOT_IMPLEMENTED();}
    stringUTF8::operator i64() const
    {
    klib::exception::FUNCTION_NOT_IMPLEMENTED();}
    stringUTF8::operator i32() const
    {
    klib::exception::FUNCTION_NOT_IMPLEMENTED();}
    stringUTF8::operator i16() const
    {
    klib::exception::FUNCTION_NOT_IMPLEMENTED();}
    stringUTF8::operator i8() const
    {
    klib::exception::FUNCTION_NOT_IMPLEMENTED();}
    stringUTF8::operator f32() const
    {
    klib::exception::FUNCTION_NOT_IMPLEMENTED();}
    stringUTF8::operator f64() const
    {
    klib::exception::FUNCTION_NOT_IMPLEMENTED();}
}