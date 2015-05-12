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

#include <pthread.h>
#include <errno.h>

#include "CMutex.h"

SCRATCH_NAMESPACE_BEGIN;

CMutex::CMutex()
{
  m_pMutex = (void*)new pthread_mutex_t;
  pthread_mutex_init((pthread_mutex_t*)m_pMutex, NULL);
}

CMutex::~CMutex()
{
  pthread_mutex_destroy((pthread_mutex_t*)m_pMutex);
  delete (pthread_mutex_t*)m_pMutex;
}

void CMutex::Lock() const
{
  pthread_mutex_lock((pthread_mutex_t*)m_pMutex);
}

bool CMutex::TryLock() const
{
  return pthread_mutex_trylock((pthread_mutex_t*)m_pMutex) != EBUSY;
}

void CMutex::Unlock() const
{
  pthread_mutex_unlock((pthread_mutex_t*)m_pMutex);
}

CMutexWait::CMutexWait(const CMutex &mutex)
{
  m_pMutex = &mutex;
  m_pMutex->Lock();
}

CMutexWait::~CMutexWait()
{
  m_pMutex->Unlock();
}

SCRATCH_NAMESPACE_END;
