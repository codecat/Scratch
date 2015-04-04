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

#ifndef SCRATCH_CDICTIONARY_H_INCLUDED
#define SCRATCH_CDICTIONARY_H_INCLUDED

#include "Common.h"
#include "CStackArray.h"

SCRATCH_NAMESPACE_BEGIN;

template<class TKey, class TValue>
class CDictionary;

template<class TKey, class TValue>
class SCRATCH_EXPORT CDictionaryPair
{
  friend class CDictionary<TKey, TValue>;
public:
  TKey* key;
  TValue* value;

protected:
  BOOL m_bClear;

public:
  CDictionaryPair();
  CDictionaryPair(CDictionaryPair<TKey, TValue> &copy);
  ~CDictionaryPair();
};

template<class TKey, class TValue>
class SCRATCH_EXPORT CDictionary
{
private:
  CStackArray<TKey> dic_saKeys;
  CStackArray<TValue> dic_saValues;

public:
  BOOL dic_bAllowDuplicateKeys;

public:
  CDictionary(void);
  CDictionary(const CDictionary<TKey, TValue> &copy);
  ~CDictionary(void);

  /// Add to the dictionary
  void Add(const TKey &key, const TValue &value);
  /// Push to the dictionary
  CDictionaryPair<TKey, TValue> Push(const TKey &key);

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

  /// Pop a value by its index
  CDictionaryPair<TKey, TValue> PopByIndex(const INDEX iIndex);
  /// Pop a value from the dictionary by key
  CDictionaryPair<TKey, TValue> PopByKey(const TKey &key);
  /// Pop a value from the dictionary
  CDictionaryPair<TKey, TValue> PopByValue(const TValue &value);

  /// Clear all items
  void Clear(void);

  /// Return how many objects there currently are in the dictionary
  INDEX Count(void);

  TValue& operator[](const TKey &key);
  
  /// Get a key from the dictionary using an index
  TKey& GetKeyByIndex(const INDEX iIndex);
  /// Get a value from the dictionary using an index
  TValue& GetValueByIndex(const INDEX iIndex);
};

SCRATCH_NAMESPACE_END;

#include "CDictionary.cpp"

#endif
