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

#ifndef SCRATCH_CDICTIONARY_H_INCLUDED
#define SCRATCH_CDICTIONARY_H_INCLUDED 1

#ifdef USE_PRAGMAONCE
  #pragma once
#endif

#include "Common.h"
#include "CStackArray.h"

SCRATCH_NAMESPACE_BEGIN;

template<class TKey, class TValue>
class CDictionary
{
private:
  CStackArray<TKey> dic_saKeys;
  CStackArray<TValue> dic_saValues;

public:
  CDictionary(void);
  ~CDictionary(void);

  /// Add to the dictionary
  void Add(const TKey &key, const TValue &value);

  /// Get the index of the given key
  INDEX IndexByKey(const TKey &key);
  /// Get the index of the given value
  INDEX IndexByValue(const TValue &value);

  /// Does this dictionary have the given key?
  BOOL HasKey(const TKey &key);
  /// Does this dictionary have the given value?
  BOOL HasValue(const TValue &value);

  /// Remove a value by its index
  void RemoveByIndex(const INDEX iIndex);
  /// Remove a value from the dictionary by key
  void RemoveByKey(const TKey &key);
  /// Remove a value from the dictionary
  void RemoveByValue(const TValue &value);

  /// Return how many objects there currently are in the dictionary
  INDEX Count(void);

  TValue& operator[](const TKey &key);
};

SCRATCH_NAMESPACE_END;

#include "CDictionary.cpp"

#endif
