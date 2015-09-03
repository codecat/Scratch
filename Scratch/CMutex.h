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

#ifndef SCRATCH_CMUTEX_H_INCLUDED
#define SCRATCH_CMUTEX_H_INCLUDED

#include "Common.h"

SCRATCH_NAMESPACE_BEGIN;

class SCRATCH_EXPORT Mutex
{
private:
  void* m_pMutex;
  bool m_bIsLocked;

public:
  Mutex();
  Mutex(const Mutex &copy); // copy constructor actually does the same as regular constructor.
  ~Mutex();

  void Lock();
  bool TryLock();
  void Unlock();
};

class SCRATCH_EXPORT MutexWait
{
public:
  Mutex* m_pMutex;

public:
  MutexWait(const Mutex &mutex);
  ~MutexWait();
};

SCRATCH_NAMESPACE_END;

#endif
