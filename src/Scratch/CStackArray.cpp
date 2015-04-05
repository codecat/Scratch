/*  libscratch - Multipurpose objective C++ library.
    
    Copyright (c) 2015 Angelo Geels <spansjh@gmail.com>
    
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

#ifndef SCRATCH_CSTACKARRAY_CPP_INCLUDED
#define SCRATCH_CSTACKARRAY_CPP_INCLUDED

#include "CStackArray.h"

#include <cstdlib>
#include <cstring>

SCRATCH_NAMESPACE_BEGIN;

template<class Type>
CStackArray<Type>::CStackArray()
{
  sa_pItems = NULL;
  sa_ctSlots = 0;
  sa_ctUsed = 0;
  sa_bOnlyPop = FALSE;
  AllocateSlots(256);
}

template<class Type>
CStackArray<Type>::CStackArray(const CStackArray<Type> &copy)
{
  sa_pItems = NULL;
  sa_ctSlots = 0;
  sa_ctUsed = 0;
  sa_bOnlyPop = copy.sa_bOnlyPop;

  AllocateSlots(copy.sa_ctSlots);

  // copy meta information
  sa_ctUsed = copy.sa_ctUsed;

  // copy data to other slots
  for(INDEX i=0; i<sa_ctUsed; i++) {
    // allocate memory for it
    sa_pItems[i] = new Type;

    // this should call the copy constructor
    *sa_pItems[i] = *copy.sa_pItems[i];
  }
}

template<class Type>
CStackArray<Type>::~CStackArray()
{
  if(sa_bOnlyPop) {
    PopAll();
  } else {
    Clear();
  }

  // free allocated memory for data
  if(sa_pItems != NULL) {
    free(sa_pItems);
  }
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

/// Push to the beginning of the stack, return a reference to the newly made object
template<class Type>
Type& CStackArray<Type>::PushBegin(void)
{
  // PushBegin() in combination with sa_bOnlyPop will cause memory leaking if not manually Clear()'d
  ASSERT(!sa_bOnlyPop);

  // if we need more slots
  if(sa_ctUsed >= sa_ctSlots) {
    // allocate some more
    AllocateSlots(256);
  }

  // create the new object
  Type* tNewObject = new Type;

  // make some room
  for(int i=sa_ctUsed; i>0; i--) {
    sa_pItems[i] = sa_pItems[i-1];
  }

  // push it onto the beginning of the stack
  sa_pItems[0] = tNewObject;

  // increase iterator
  sa_ctUsed++;

  // return new object
  return *tNewObject;
}

/// Push to the stack, return a reference to the newly made object
template<class Type>
Type& CStackArray<Type>::Push(void)
{
  // Push() in combination with sa_bOnlyPop will cause memory leaking if not manually Clear()'d
  ASSERT(!sa_bOnlyPop);

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

/// Push a pointer to the stack
template<class Type>
void CStackArray<Type>::Push(Type* pObj)
{
  // if we need more slots
  if(sa_ctUsed >= sa_ctSlots) {
    // allocate some more
    AllocateSlots(256);
  }

  // push it onto the stack
  sa_pItems[sa_ctUsed] = pObj;

  // increase iterator
  sa_ctUsed++;
}

/// Pop top object from the stack
template<class Type>
Type* CStackArray<Type>::Pop(void)
{
  ASSERT(sa_ctUsed > 0);

  // decrease iterator
  sa_ctUsed--;

  // get the item on top of the stack
  Type* tObject = sa_pItems[sa_ctUsed];

  // set the remaining pointer to NULL (just to be sure)
  sa_pItems[sa_ctUsed] = NULL;

  // return the object
  return tObject;
}

/// Pop a certain index from the stack
template<class Type>
Type* CStackArray<Type>::PopAt(INDEX iIndex)
{
  ASSERT(iIndex < Count());

  // decrease iterator
  sa_ctUsed--;

  // get the item in the stack
  Type* tObject = sa_pItems[iIndex];

  // move pointers at the right one point to the left
  for(INDEX i=iIndex; i<sa_ctUsed; i++) {
    // set pointer to next one in stack
    sa_pItems[i] = sa_pItems[i + 1];
  }

  // set last pointer to NULL (just in case)
  sa_pItems[sa_ctUsed] = NULL;

  // return the object
  return tObject;
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

/// Find the index of the given object in the stack
template<class Type>
INDEX CStackArray<Type>::Find(const Type &obj)
{
  // for every object
  for(INDEX i=0; i<sa_ctUsed; i++) {
    // test if it's the given one
    if(obj == *sa_pItems[i]) {
      return i;
    }
  }

  return -1;
}

/// Find the index of the given pointer in the stack
template<class Type>
INDEX CStackArray<Type>::FindPointer(const Type* pObj)
{
  // for every object
  for(INDEX i=0; i<sa_ctUsed; i++) {
    // test if it's the given one
    if(pObj == sa_pItems[i]) {
      return i;
    }
  }

  return -1;
}

/// Find the index of the given condition in the stack
template<class Type>
template<typename Func>
INDEX CStackArray<Type>::FindAny(Func f)
{
  // for every object
  for(INDEX i=0; i<sa_ctUsed; i++) {
    // test with function
    if(f(*sa_pItems[i])) {
      return i;
    }
  }
  return -1;
}

/// Returns whether the given object is currently in the stack
template<class Type>
BOOL CStackArray<Type>::Contains(const Type &obj)
{
  return Find(obj) != -1;
}

/// Returns whether the given pointer is currently in the stack
template<class Type>
BOOL CStackArray<Type>::ContainsPointer(const Type* pObj)
{
  return FindPointer(pObj) != -1;
}

/// Returns whether the given condition exists on any of the objects currently in the stack
template<class Type>
template<typename Func>
BOOL CStackArray<Type>::ContainsAny(Func f)
{
  return FindAny(f) != -1;
}

template<class Type>
Type& CStackArray<Type>::operator[](INDEX iIndex)
{
  ASSERT(iIndex >= 0 && iIndex < sa_ctUsed);
  return *sa_pItems[iIndex];
}

SCRATCH_NAMESPACE_END;

#endif
