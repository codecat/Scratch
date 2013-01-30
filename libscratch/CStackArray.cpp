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

#ifndef SCRATCH_CSTACKARRAY_CPP_INCLUDED
#define SCRATCH_CSTACKARRAY_CPP_INCLUDED 1

#ifdef USE_PRAGMAONCE
  #pragma once
#endif

#include "CStackArray.h"

#include <cstdlib>
#include <cstring>

template<class Type>
CStackArray<Type>::CStackArray()
{
  sa_pItems = NULL;
  sa_ctSlots = 0;
  sa_ctUsed = 0;
  AllocateSlots(256);
}

template<class Type>
CStackArray<Type>::CStackArray(const CStackArray& copy)
{
  sa_ctSlots = copy.sa_ctSlots;
  sa_ctUsed = copy.sa_ctUsed;

  // allocate new memory
  sa_pItems = (Type**)malloc(sizeof(Type*) * sa_ctSlots);

  // copy memory from the to-copy instance
  memcpy(sa_pItems, copy.sa_pItems, sizeof(Type*) * sa_ctSlots);
}

template<class Type>
CStackArray<Type>::~CStackArray()
{
  PopAll();
}

template<class Type>
void CStackArray<Type>::AllocateSlots(INDEX ctSlots)
{
  // allocate some memory
  sa_ctSlots += ctSlots;
  Type** pNewMem = (Type**)malloc(sizeof(Type*) * sa_ctSlots);

  // if we allocated memory before
  if(sa_pItems != NULL) {
    // copy data to the new memory
    memcpy(pNewMem, sa_pItems, sizeof(Type*) * (sa_ctSlots - ctSlots));
    // free previously allocated memory
    free(sa_pItems);
  }

  // update the pointer
  sa_pItems = pNewMem;
}

/// Push to the stack, return a reference to the newly made object
template<class Type>
Type& CStackArray<Type>::Push(void)
{
  // if we need more slots
  if(sa_ctUsed >= sa_ctSlots) {
    // allocate some more
    AllocateSlots(256);
  }

  // create the new object
  Type* tNewObject = new Type;

  // push it onto the stack
  sa_pItems[sa_ctUsed] = tNewObject;

  // increase iterator
  sa_ctUsed++;

  // return new object
  return *tNewObject;
}

/// Push existing object to the stack
template<class Type>
void CStackArray<Type>::Push(Type& tObject)
{
  // if we need more slots
  if(sa_ctUsed >= sa_ctSlots) {
    // allocate some more
    AllocateSlots(256);
  }

  // push it onto the stack
  sa_pItems[sa_ctUsed] = &tObject;

  // increase iterator
  sa_ctUsed++;
}

/// Pop top object from the stack
template<class Type>
Type& CStackArray<Type>::Pop(void)
{
  ASSERT(sa_ctUsed > 0);

  // decrease iterator
  sa_ctUsed--;

  // get the item on top of the stack
  Type* tObject = sa_pItems[sa_ctUsed];

  // set the remaining pointer to NULL (just to be sure)
  sa_pItems[sa_ctUsed] = NULL;

  // return the object
  return *tObject;
}

/// Pop all objects from the stack
template<class Type>
void CStackArray<Type>::PopAll(void)
{
  // for every object
  for(INDEX i=0; i<sa_ctUsed; i++) {
    // set remaining pointer to NULL (just to be sure)
    sa_pItems[i] = NULL;
  }

  // reset iterator to 0
  sa_ctUsed = 0;
}

/// Clear all objects in the stack
template<class Type>
void CStackArray<Type>::Clear(void)
{
  // for every object
  for(INDEX i=0; i<sa_ctUsed; i++) {
    // delete it
    delete sa_pItems[i];
    // set remaining pointer to NULL (just to be sure)
    sa_pItems[i] = NULL;
  }

  // reset iterator to 0
  sa_ctUsed = 0;
}

/// Return how many objects there currently are in the stack
template<class Type>
INDEX CStackArray<Type>::Count(void)
{
  return sa_ctUsed;
}

template<class Type>
Type& CStackArray<Type>::operator[](int iIndex)
{
  ASSERT(iIndex >= 0 && iIndex < sa_ctUsed);
  return *sa_pItems[iIndex];
}

#endif
