/**
 * Created Date: Monday February 20th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Monday February 20th 2023 3:58:41 am
 * Modified By: DefinitelyNotAGirl@github (definitelynotagirl115199@gmail.com)
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
#pragma once

constexpr uint64_t operator""PByte(unsigned long long const x);
constexpr uint64_t operator""TByte(unsigned long long const x);
constexpr uint64_t operator""GByte(unsigned long long const x);
constexpr uint64_t operator""MByte(unsigned long long const x);
constexpr uint64_t operator""KByte(unsigned long long const x);

constexpr uint64_t operator""PiB(unsigned long long const x);
constexpr uint64_t operator""TiB(unsigned long long const x);
constexpr uint64_t operator""GiB(unsigned long long const x);
constexpr uint64_t operator""MiB(unsigned long long const x);
constexpr uint64_t operator""KiB(unsigned long long const x);

constexpr uint64_t operator""PBit(unsigned long long const x);
constexpr uint64_t operator""TBit(unsigned long long const x);
constexpr uint64_t operator""GBit(unsigned long long const x);
constexpr uint64_t operator""MBit(unsigned long long const x);
constexpr uint64_t operator""KBit(unsigned long long const x);

constexpr uint64_t operator""P(unsigned long long const x);
constexpr uint64_t operator""T(unsigned long long const x);
constexpr uint64_t operator""G(unsigned long long const x);
constexpr uint64_t operator""M(unsigned long long const x);
constexpr uint64_t operator""K(unsigned long long const x);

#define KILO 1000
#define MEGA 1000000
#define GIGA 1000000000
#define TERA 1000000000000
#define PETA 1000000000000000


