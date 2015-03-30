/*  libscratch - Multipurpose objective C++ library.
    
    Copyright (c) 2013-2015 Angelo Geels <spansjh@gmail.com>
    
    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:
    
    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef SCRATCH_CCONTAINER_CPP_INCLUDED
#define SCRATCH_CCONTAINER_CPP_INCLUDED

#include "CContainer.h"

SCRATCH_NAMESPACE_BEGIN;

template<class Type>
CContainer<Type>::CContainer()
{

}

template<class Type>
CContainer<Type>::~CContainer()
{

}

/// Add an item to the container
template<class Type>
void CContainer<Type>::Add(Type* pItem)
{

}

/// Find the index of the given pointer
template<class Type>
INDEX CContainer<Type>::Find(Type* pItem)
{

}

/// Remove a pointer from the container
template<class Type>
void CContainer<Type>::Remove(Type* pItem)
{

}

/// Remove a pointer from the container by index
template<class Type>
void CContainer<Type>::Remove(INDEX iIndex)
{

}

template<class Type>
void CContainer<Type>::AllocateSlots(INDEX ctSlots)
{

}

SCRATCH_NAMESPACE_END;

#endif
