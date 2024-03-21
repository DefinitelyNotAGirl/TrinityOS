/**
Created Date: Sunday March 17th 2024
Author: Lilith (definitelynotagirl115169@gmail.com)
-----
Last Modified: Sunday March 17th 2024 1:28:51 am
Modified By: Lilith (definitelynotagirl115169@gmail.com)
-----
Copyright (c) 2024 Lilith Nitschke-Höfer (lilithnitschkehoefer@gmail.com)

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
*/
#pragma once
#include "stdint.hxx"
#include "FixedSizeList.hxx"
#include "initializer_list.hxx"

//+ ██████  ██████  ██ ███    ██ ████████
//+ ██   ██ ██   ██ ██ ████   ██    ██
//+ ██████  ██████  ██ ██ ██  ██    ██
//+ ██      ██   ██ ██ ██  ██ ██    ██
//+ ██      ██   ██ ██ ██   ████    ██
class printStream {
	//*
	//* Members
	//*
	protected:
	public:
		void (*printConstStr)(const char* str);
		void (*printStr)	 (char* str);
		void (*printChar)	 (char c);
		void (*printInteger) (uint64_t n);
		void (*printFloat)	 (double d);
		char* linePrefix = nullptr;
	//!
	//! Functions
	//!
	protected:
	public:
		inline printStream(
			void (*printConstStr)(const char* 	str	),
			void (*printStr		)(char* 		str	),
			void (*printChar	)(char 			c	),
			void (*printInteger	)(uint64_t 		n	),
			void (*printFloat	)(double 		d	),
			char* linePrefix = nullptr
		)
			:
			printConstStr(printConstStr),
			printStr(printStr),
			printChar(printChar),
			printInteger(printInteger),
			printFloat(printFloat),
			linePrefix(linePrefix)
		{}
		inline printStream& operator<<(const char* str)	{this->printConstStr(str)	;return *this;}
		inline printStream& operator<<(char* str)		{this->printStr(str)		;return *this;}
		inline printStream& operator<<(char c)			{this->printChar(c)			;return *this;}
		inline printStream& operator<<(uint64_t n)		{this->printInteger(n)		;return *this;}
		inline printStream& operator<<(double d)		{this->printFloat(d)		;return *this;}
};

extern printStream info;
extern printStream warn;
extern printStream error;
extern printStream debug;

constexpr char endl = '\n';


//, ███████ ██ ███████ ██      ██████      ███    ███  █████  ██████
//, ██      ██ ██      ██      ██   ██     ████  ████ ██   ██ ██   ██
//, █████   ██ █████   ██      ██   ██     ██ ████ ██ ███████ ██████
//, ██      ██ ██      ██      ██   ██     ██  ██  ██ ██   ██ ██
//, ██      ██ ███████ ███████ ██████      ██      ██ ██   ██ ██

enum class FieldType : uint8_t {
	Boolean,
	Integer,
	String
};

template<typename T>
class Field {
	//*
	//* Members
	//*
	protected:
		uint64_t mask;
		FieldType type;
		uint8_t StringSize; //. size for string fields, ignored when type!=FieldType::String
		char* name;
	public:
	//!
	//! Functions
	//!
	protected:
	public:
		Field(uint64_t mask,FieldType type,char* name,uint8_t StringSize = 0)
			:mask(mask),type(type),name(name),StringSize(StringSize){}
		Field(){}
		void print(T* data,printStream& stream)
		{
			switch(this->type)
			{
				case(FieldType::Boolean):
				{
					if((*data & this->mask) != 0)
					{
						stream << "\033[38:5:10m[" << this->name << "]\033[0m";
					}
					else
					{
						stream << "\033[38:5:255m[" << this->name << "]\033[0m";
					}
					break;
				}
			}
		}
};

template<typename T,int FieldCount>
class FieldMap {
	//*
	//* Members
	//*
	protected:
		void (*customPrint)(FieldMap<T,FieldCount>* fm);
		FixedList<Field<T>,FieldCount> Fields;
	public:
	//!
	//! Functions
	//!
	protected:
	public:
		FieldMap(std::initializer_list<Field<T>> fl,void(*customPrintFunction)(FieldMap<T,FieldCount>* fm))
		{
			this->customPrint = customPrintFunction;
			for(const Field<T>& f : fl)
				this->Fields << f;
		}
		void print(T* data,printStream& stream)
		{
			if(this->customPrint != nullptr)
				return this->customPrint(this);
			stream << "field map print..." << endl;
			for(Field<T>& field : this->Fields)
				field.print(data,stream);
		}
};
