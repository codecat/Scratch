/*  libscratch - Multipurpose objective C++ library.
    Copyright (C) 2012 - 2013  Angelo Geels

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

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
