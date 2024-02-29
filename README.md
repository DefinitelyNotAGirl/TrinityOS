# **GEOS**
The Gaming Evolved Operating System, or for short "GEOS" is intended to become a next generation operating system made for gaming.

This project was started as a result of MS windows (read: MS garbage) being the bane of my existense.

# **Hardware Requirements**
## Recommended
    A 64-bit capable CPU, the more cores the better but dont sacrifice too much single core perfomance.

    16GB of ram

    256GB of disk space (can't ever have enough disk space tho)

    any compatible GPU should do

## Minimum
    A 64-bit capable dual core CPU
    1GB of ram
    16GB of disk space

    please dont expect to be playing any games with these specs tho
    
    any compatible GPU should do
<br><br>
# CPU features
| Feature       | Required  | Supported | Support planned   |
|---------------|-----------|-----------|-------------------|
|PML5           |no         |no         | yes               |
|52 bit PMAW    |yes        |yes        | yes               |
|57 bit PMAW    |no         |no         | yes               |

PMAW = physical memory address width
<br><br>
# **Current Features**
*insert picture of desert*

<br><br>
# **Planned Features**

<br><br>
# **Known issues**
everything

<br><br>
# **Compatibility with Applications written for Microsoft windows**
## C/C++, rust, Assembly, etc.
I plan on creating a set of tools that would allow for the vast majority of "windows applications" written in C/C++,Rust or Assembly (or any other language that compiles down to machine instructions for that matter) to simply be ported to GEOS with little to no effort(mainly through the use of a cross-compiler).
For anyone unfarmiliar, this would mean that porting unreal engine games should require little to no effort so long the Developers of the individual game are willing to cooperate.
(The Unreal Engine, for the most part just spits out machine instructions which have little todo with the operating system and everything todo with the CPU at hand)
## Java
I intend on making sure that GEOS will ship with a fully functional JVM (Java Virtual Machine), therefore applications written in Java ***should*** pose no issues in terms of portability.

## Python
I intend on shipping with a fully functional python executable, therefore python applications ***should*** pose no issues either

## .NET, C#
I, at the time of writing this, am not 100% sure as to how these 2 operate, that said, i know both of them are managed by Microsoft and as you may know if you have read this readme until this point, I am not exactly the biggest fan of Microsoft, long story short i can't promise anything regarding either of these.
(yes i do know that unity is very dependant on C#)

## Any languages not mentioned here
for any languages i didnt mention, just assume they wont be supported.

# **Q&A**
    Q: Will [insert application/game] run on GEOS?

    A: It depends.
    As I mentioned earlier in this readme, I will try my very best to built tools that would allow porting of applications from Microsoft Windows to GEOS to be as easy and handsoff as possible, but wether a given company will actually put in the effort is outside of my control, in general it would be best to not assume any applications that are highly dependant upon features uniqe to Windows (of which i can't spontianously name a single one) to be supported.
<br>

    Q: Will wallpaper engine be supported?

    A: I Hope so.
    As with any other application, i cant promise anything since this is simply outside of my control, but I will make sure GEOS offers all the required features for an application like wallpaper engine
<br>

    Q: Will my 15 year old Hardware be supported?
    
    A: Most propably not.
    GEOS is a very modern Operating System and is only intended to support modern Hardware.
    For reference, at the time of writing this i am developing and testing on my AMD FX8350 straight out of 2012 (which, considering it's age is one beast of a CPU btw) and this is propably about the oldest CPU that will actually run this Operating System.
    
# **Credits**

# **Rant**
## **Nvidia**
Not offering any documentation on their hardware to the general public.
to qoute Linus Torvalds, "Fuck you, nvidia"
## **UEFI**
Honestly, everyone who's got anything to do with EFI/UEFI can go to hell and stay there, BIOS was just fine.

# **LICENSE**

Copyright (c) 2022 DefinitelyNotAGirl@github

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
