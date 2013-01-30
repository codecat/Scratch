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

#ifndef SCRATCH_CDICTIONARY_CPP_INCLUDED
#define SCRATCH_CDICTIONARY_CPP_INCLUDED 1

#ifdef USE_PRAGMAONCE
  #pragma once
#endif

#include "CDictionary.h"

template<class TKey, class TValue>
CDictionary<TKey, TValue>::CDictionary(void)
{
}

template<class TKey, class TValue>
CDictionary<TKey, TValue>::~CDictionary(void)
{
}

/// Add to the dictionary
template<class TKey, class TValue>
void CDictionary<TKey, TValue>::Add(const TKey &key, const TValue &value)
{
  // if the key has already been added
  if(HasKey(key)) {
    ASSERT(FALSE);
    return;
  }

  // add it
  dic_saKeys.Push() = key;
  dic_saValues.Push() = value;
}

/// Get the index of the given key
template<class TKey, class TValue>
INDEX CDictionary<TKey, TValue>::IndexByKey(const TKey &key)
{
  int ctElements = Count();

  // find the right index
  int iIndex = 0;
  for(; iIndex<ctElements; iIndex++) {
    if(dic_saKeys[iIndex] == key) {
      // this is the item, we found the index
      break;
    }
  }

  // return index, or element count if it doesn't exist
  if(iIndex < ctElements) {
    return iIndex;
  }
  return -1;
}

/// Get the index of the given value
template<class TKey, class TValue>
INDEX CDictionary<TKey, TValue>::IndexByValue(const TValue &value)
{
  int ctElements = Count();

  // find the right index
  int iIndex = 0;
  for(; iIndex<ctElements; iIndex++) {
    if(dic_saValues[iIndex] == value) {
      // this is the item, we found the index
      break;
    }
  }

  // return index, or -1 if it doesn't exist
  if(iIndex < ctElements) {
    return iIndex;
  }
  return -1;
}

/// Does this dictionary have the given key?
template<class TKey, class TValue>
BOOL CDictionary<TKey, TValue>::HasKey(const TKey &key)
{
  return IndexByKey(key) != -1;
}

/// Does this dictionary have the given value?
template<class TKey, class TValue>
BOOL CDictionary<TKey, TValue>::HasValue(const TValue &value)
{
  return IndexByValue(value) != -1;
}

/// Remove a value by its index
template<class TKey, class TValue>
void CDictionary<TKey, TValue>::RemoveByIndex(const INDEX iIndex)
{
  // pop the values at that index
  dic_saKeys.PopAt(iIndex);
  dic_saValues.PopAt(iIndex);
}

/// Remove a value from the dictionary by key
template<class TKey, class TValue>
void CDictionary<TKey, TValue>::RemoveByKey(const TKey &key)
{
  // remove by index
  RemoveByIndex(IndexByKey(key));
}

/// Remove a value from the dictionary
template<class TKey, class TValue>
void CDictionary<TKey, TValue>::RemoveByValue(const TValue &value)
{
  // remove by index
  RemoveByIndex(IndexByValue(value));
}

/// Return how many objects there currently are in the dictionary
template<class TKey, class TValue>
INDEX CDictionary<TKey, TValue>::Count(void)
{
  // return the amount of keys (amount of values is the same)
  return dic_saKeys.Count();
}

template<class TKey, class TValue>
TValue& CDictionary<TKey, TValue>::operator[](const TKey &key)
{
  // get the index
  INDEX iIndex = IndexByKey(key);

  // if the key doesn't exist
  if(iIndex == -1) {
    // make a new key
    dic_saKeys.Push() = key;

    // and make a new value which we'll return
    return dic_saValues.Push();
  }

  // return the value
  return dic_saValues[iIndex];
}

#endif
