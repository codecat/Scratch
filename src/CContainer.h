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
