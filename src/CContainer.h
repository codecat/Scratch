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

#ifndef SCRATCH_CCONTAINER_H_INCLUDED
#define SCRATCH_CCONTAINER_H_INCLUDED

#include "Common.h"

SCRATCH_NAMESPACE_BEGIN;

template<class Type>
class SCRATCH_EXPORT CContainer
{
public:
  Type** con_pItems;
  INDEX con_ctSlots;
  INDEX con_ctUsed;

public:
  CContainer();
  ~CContainer();

  /// Add an item to the container
  void Add(Type* pItem);

  /// Find the index of the given pointer
  INDEX Find(Type* pItem);

  /// Remove a pointer from the container
  void Remove(Type* pItem);
  /// Remove a pointer from the container by index
  void Remove(INDEX iIndex);

  Type& operator[](INDEX iIndex);

private:
  void AllocateSlots(INDEX ctSlots);
};

SCRATCH_NAMESPACE_END;

#include "CContainer.cpp"

#endif // include once check
