/**
 * Created Date: Friday April 28th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Thursday May 25th 2023 2:26:50 am
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
#include <litop>

constexpr u64 operator""PByte(unsigned long long const x){return x*PETA;}
constexpr u64 operator""TByte(unsigned long long const x){return x*TERA;}
constexpr u64 operator""GByte(unsigned long long const x){return x*GIGA;}
constexpr u64 operator""MByte(unsigned long long const x){return x*MEGA;}
constexpr u64 operator""KByte(unsigned long long const x){return x*KILO;}

constexpr u64 operator""PB(unsigned long long const x){return x*PETA;}
constexpr u64 operator""TB(unsigned long long const x){return x*TERA;}
constexpr u64 operator""GB(unsigned long long const x){return x*GIGA;}
constexpr u64 operator""MB(unsigned long long const x){return x*MEGA;}
constexpr u64 operator""KB(unsigned long long const x){return x*KILO;}

constexpr u64 operator""PiB(unsigned long long const x){return x*0x4000000000000;}
constexpr u64 operator""TiB(unsigned long long const x){return x*0x10000000000  ;}
constexpr u64 operator""GiB(unsigned long long const x){return x*0x40000000     ;}
constexpr u64 operator""MiB(unsigned long long const x){return x*0x100000       ;}
constexpr u64 operator""KiB(unsigned long long const x){return x*1024           ;}

constexpr u64 operator""P(unsigned long long const x){return x*PETA;}
constexpr u64 operator""T(unsigned long long const x){return x*TERA;}
constexpr u64 operator""G(unsigned long long const x){return x*GIGA;}
constexpr u64 operator""M(unsigned long long const x){return x*MEGA;}
constexpr u64 operator""K(unsigned long long const x){return x*KILO;}

