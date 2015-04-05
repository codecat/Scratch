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

#ifndef SCRATCH_CDICTIONARY_CPP_INCLUDED
#define SCRATCH_CDICTIONARY_CPP_INCLUDED

#include "CDictionary.h"

SCRATCH_NAMESPACE_BEGIN;

template<class TKey, class TValue>
CDictionaryPair<TKey, TValue>::CDictionaryPair()
{
  key = 0;
  value = 0;
}

template<class TKey, class TValue>
CDictionaryPair<TKey, TValue>::~CDictionaryPair()
{
}

template<class TKey, class TValue>
void CDictionaryPair<TKey, TValue>::Delete()
{
  if(key != 0) {
    delete key;
    key = 0;
  }
  if(value != 0) {
    delete value;
    value = 0;
  }
}

template<class TKey, class TValue>
CDictionary<TKey, TValue>::CDictionary(void)
{
  dic_bAllowDuplicateKeys = FALSE;
}

template<class TKey, class TValue>
CDictionary<TKey, TValue>::CDictionary(const CDictionary<TKey, TValue> &copy)
  : dic_saKeys(copy.dic_saKeys),
    dic_saValues(copy.dic_saValues)
{
  dic_bAllowDuplicateKeys = copy.dic_bAllowDuplicateKeys;
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
  if(!dic_bAllowDuplicateKeys && HasKey(key)) {
    ASSERT(FALSE);
    return;
  }

  // add it
  dic_saKeys.Push() = key;
  dic_saValues.Push() = value;
}

/// Push to the dictionary
template<class TKey, class TValue>
CDictionaryPair<TKey, TValue> CDictionary<TKey, TValue>::Push(const TKey &key)
{
  CDictionaryPair<TKey, TValue> ret;
  ret.key = &(dic_saKeys.Push());
  (*ret.key) = key;
  ret.value = &(dic_saValues.Push());
  return ret;
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
  delete dic_saKeys.PopAt(iIndex);
  delete dic_saValues.PopAt(iIndex);
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

/// Pop a value by its index
template<class TKey, class TValue>
CDictionaryPair<TKey, TValue> CDictionary<TKey, TValue>::PopByIndex(const INDEX iIndex)
{
  CDictionaryPair<TKey, TValue> ret;
  ret.key = dic_saKeys.PopAt(iIndex);
  ret.value = dic_saValues.PopAt(iIndex);
  return ret;
}

/// Pop a value from the dictionary by key
template<class TKey, class TValue>
CDictionaryPair<TKey, TValue> CDictionary<TKey, TValue>::PopByKey(const TKey &key)
{
  return PopByIndex(IndexByKey(key));
}

/// Pop a value from the dictionary
template<class TKey, class TValue>
CDictionaryPair<TKey, TValue> CDictionary<TKey, TValue>::PopByValue(const TValue &value)
{
  return PopByIndex(IndexByValue(value));
}

/// Clear all items
template<class TKey, class TValue>
void CDictionary<TKey, TValue>::Clear(void)
{
  // clear keys and values
  dic_saKeys.Clear();
  dic_saValues.Clear();
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

/// Get a pair from the dictionary using an index
template<class TKey, class TValue>
CDictionaryPair<TKey, TValue> CDictionary<TKey, TValue>::GetPair(const INDEX iIndex)
{
  CDictionaryPair<TKey, TValue> pair;
  pair.key = &dic_saKeys[iIndex];
  pair.value = &dic_saValues[iIndex];
  return pair;
}

/// Get a key from the dictionary using an index
template<class TKey, class TValue>
TKey& CDictionary<TKey, TValue>::GetKeyByIndex(const INDEX iIndex)
{
  // return the value
  return dic_saKeys[iIndex];
}

/// Return value by index
template<class TKey, class TValue>
TValue& CDictionary<TKey, TValue>::GetValueByIndex(const INDEX iIndex)
{
  // return the value
  return dic_saValues[iIndex];
}

SCRATCH_NAMESPACE_END;

#endif
