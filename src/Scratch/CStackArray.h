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

#ifndef SCRATCH_CSTACKARRAY_H_INCLUDED
#define SCRATCH_CSTACKARRAY_H_INCLUDED

#include "Common.h"

SCRATCH_NAMESPACE_BEGIN;

template<class Type>
class SCRATCH_EXPORT CStackArray
{
public:
  Type** sa_pItems;
  INDEX sa_ctSlots;
  INDEX sa_ctUsed;
  BOOL sa_bOnlyPop;

public:
  CStackArray(void);
  CStackArray(const CStackArray<Type> &copy); // Note: If this ever gets called, you're most likely writing bad code.
  ~CStackArray(void);

  /// Push to the beginning of the stack, return a reference to the newly made object
  Type& PushBegin(void);
  /// Push to the stack, return a reference to the newly made object
  Type& Push(void);
  /// Push a pointer to the stack
  void Push(Type* pObj);
  /// Pop top object from the stack
  Type* Pop(void);
  /// Pop a certain index from the stack
  Type* PopAt(INDEX iIndex);

  /// Pop all objects from the stack
  void PopAll(void);
  /// Clear all objects in the stack
  void Clear(void);

  /// Return how many objects there currently are in the stack
  INDEX Count(void);

  /// Find the index of the given object in the stack
  INDEX Find(const Type &obj);
  /// Find the index of the given pointer in the stack
  INDEX FindPointer(const Type* pObj);
  /// Find the index of the given condition in the stack
  template<typename Func>
  INDEX FindAny(Func f);

  /// Returns whether the given object is currently in the stack
  BOOL Contains(const Type &obj);
  /// Returns whether the given pointer is currently in the stack
  BOOL ContainsPointer(const Type* pObj);
  /// Returns whether the given condition is currently in the stack
  template<typename Func>
  BOOL ContainsAny(Func f);

  Type& operator[](INDEX iIndex);

private:
  void AllocateSlots(INDEX ctSlots);
};

SCRATCH_NAMESPACE_END;

#include "CStackArray.cpp"

#endif // include once check
