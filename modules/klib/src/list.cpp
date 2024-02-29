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

#pragma once

#include <exception>
#include <stdint>
#include <misc>
#include <functions>
#include <list>

namespace klib
{
    template<typename T>
    list<T>::list(list<T>& obj)
    {
        this->data = (T*)malloc(sizeof(T)*obj.size);
        memcpy((u64)obj.data,(u64)this->data,obj.size*sizeof(T));
        this->size = obj.size;
    }

    template<typename T>
    list<T>::list()
    {
        this->size = 0;
        this->data = (T*)0;
    }

    template<typename T>
    T& list<T>::operator[](u64 index) const
    {
        if(index >= this->size)
            exception::INDEX_OUT_OF_BOUNDS();
        return this->data[index];
    }

    template<typename T>
    void list<T>::operator<<(T& obj)
    {
        this->push_back(obj);
    }

    template<typename T>
    bool list<T>::operator==(T& obj) const
    {
        if(this == &obj)
            return 1;

        if(this->size != obj.size)
            return 0;

        for(u64 I = 0;I<this->size;I++)
        {
            if(this->data[I] != obj[I])
                return 0;
        }

        return 1;
    }

    template<typename T>
    void list<T>::push_front(T& obj)
    {
        T* tmpd = this->data;
        this->data = (T*)malloc(this->size+1);
        memcpy((u64)tmpd,(u64)this->data+sizeof(T),this->size*sizeof(T));
        free(tmpd);
        this->data[0] = obj;
        this->size++;
    }

    template<typename T>
    void list<T>::push_back(T& obj)
    {
        T* tmpd = this->data;
        this->data = (T*)malloc(this->size+1);
        memcpy((u64)tmpd,(u64)this->data,this->size*sizeof(T));
        free(tmpd);
        this->data[this->size] = obj;
        this->size++;
    }

    template<typename T>
    void list<T>::pop_back()
    {
        if(this->size == 0)
            return;
        this->size--;
        free(this->data+this->size*sizeof(T));
    }

    template<typename T>
    void list<T>::pop_front()
    {
        if(this->size == 0)
            return;
        this->size--;
        free(this->data);
        this->data+=sizeof(T);
    }
    
    template<typename T>
    T& list<T>::front() const
    {
        if(this->size == 0)
            exception::INDEX_OUT_OF_BOUNDS();
        return this->data[0];
    }

    template<typename T>
    T& list<T>::back() const
    {
        if(this->size == 0)
            exception::INDEX_OUT_OF_BOUNDS();
        return this->data[this->size-1];
    }

    template<typename T>
    u64 list<T>::length() const
    {
        return this->size;
    }

    template<typename T>
    T* list<T>::begin() const
    {
        return this->data;
    }

    template<typename T>
    T* list<T>::end() const
    {
        return this->data+this->size;
    }

    template<typename T>
    void list<T>::clear()
    {
        free(this->data);
        this->size = 0;
    }

    template<typename T>
    T* list<T>::dataAddress() const
    {
        return this->data;
    }

    //
    // destructor
    //
    template<typename T>
    list<T>::~list()
    {
        free(this->data);
    }
}