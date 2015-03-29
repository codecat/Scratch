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
  CStackArray(const CStackArray& copy); // Note: If this ever gets called, you're most likely writing bad code.
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
