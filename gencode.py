#!/usr/bin/env python3
# -*- coding:utf-8 -*-
###
# Created Date: Wednesday March 22nd 2023
# Author: DefinitelyNotAGirl@github
# -----
# Last Modified: Wednesday May 24th 2023 7:20:27 am
# Modified By: DefinitelyNotAGirl@github (definitelynotagirl115169@gmail.com)
# -----
# Copyright (c) 2023 DefinitelyNotAGirl@github
# 
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use, copy,
# modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
###

#0b0000000000000000000000000000000000000000000000000000000000000000
all0 = "0000000000000000000000000000000000000000000000000000000000000000"
all1 = "1111111111111111111111111111111111111111111111111111111111111111"

#setbit
print("//setbit")
for I in range(0,64):
    II=63-I
    bstr = all0[:II] + "1" + all0[II + 1:]
    if(I<10):
        print("#define SETBIT_0"+str(I)+"(t) "+"t |= 0b"+bstr)
    else:
        print("#define SETBIT_"+str(I)+"(t) "+"t |= 0b"+bstr)

#clearbit
print("\n//clearbit")
for I in range(0,64):
    II=63-I
    bstr = all1[:II] + "0" + all1[II + 1:]
    if(I<10):
        print("#define CLEARBIT_0"+str(I)+"(t) "+"t &= 0b"+bstr)
    else:
        print("#define CLEARBIT_"+str(I)+"(t) "+"t &= 0b"+bstr)

#SCbit
print("\n//scbit")
for I in range(0,64):
    if(I<10):
        print("#define SCBIT_0"+str(I)+"(t,v) "+"if(v){SETBIT_0"+str(I)+"(t)}else{CLEARBIT_0"+str(I)+"(t)}")
    else:
        print("#define SCBIT_"+str(I)+"(t,v) "+"if(v){SETBIT_"+str(I)+"(t)}else{CLEARBIT_"+str(I)+"(t)}")
        
#getbit
print("\n//getbit")
for I in range(0,64):
    II=63-I
    bstr = all0[:II] + "1" + all0[II + 1:]
    if(I<10):
        print("#define GETBIT_0"+str(I)+"(r,w) "+"w = (r & 0b"+bstr+")")
    else:
        print("#define GETBIT_"+str(I)+"(r,w) "+"w = (r & 0b"+bstr+")")
        
#exprgetbit
print("\n//getbit")
for I in range(0,64):
    II=63-I
    bstr = all0[:II] + "1" + all0[II + 1:]
    if(I<10):
        print("#define EXPR_GETBIT_0"+str(I)+"(r) "+"(r & 0b"+bstr+")")
    else:
        print("#define EXPR_GETBIT_"+str(I)+"(r) "+"(r & 0b"+bstr+")")
        
#flipbit
print("//flipbit")
for I in range(0,64):
    II=63-I
    bstr = all0[:II] + "1" + all0[II + 1:]
    if(I<10):
        print("#define FLIPBIT_0"+str(I)+"(t) "+"t ^ 0b"+bstr)
    else:
        print("#define FLIPBIT_"+str(I)+"(t) "+"t ^ 0b"+bstr)

