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

#ifndef _MSC_VER
#include <pthread.h>
#endif

#include <errno.h>

#include "CMutex.h"

SCRATCH_NAMESPACE_BEGIN;

Mutex::Mutex()
{
#ifndef _MSC_VER
  m_pMutex = (void*)new pthread_mutex_t;
  pthread_mutex_init((pthread_mutex_t*)m_pMutex, NULL);
#else
  m_pMutex = CreateMutex(0, false, 0);
#endif
  m_bIsLocked = false;
}

Mutex::Mutex(const Mutex &copy)
{
  operator=(copy);
}

Mutex &Mutex::operator=(const Mutex &copy)
{
  ASSERT(!copy.m_bIsLocked);
#ifndef _MSC_VER
  m_pMutex = (void*)new pthread_mutex_t;
  pthread_mutex_init((pthread_mutex_t*)m_pMutex, NULL);
#else
  m_pMutex = CreateMutex(0, false, 0);
#endif
  m_bIsLocked = false;
  return *this;
}

Mutex::~Mutex()
{
  ASSERT(!m_bIsLocked);

#ifndef _MSC_VER
  pthread_mutex_destroy((pthread_mutex_t*)m_pMutex);
  delete (pthread_mutex_t*)m_pMutex;
#else
  CloseHandle(m_pMutex);
#endif
}

void Mutex::Lock()
{
#ifndef _MSC_VER
  pthread_mutex_lock((pthread_mutex_t*)m_pMutex);
#else
  WaitForSingleObject(m_pMutex, INFINITE);
#endif

  m_bIsLocked = true;
}

bool Mutex::TryLock()
{
  bool worked;

#ifndef _MSC_VER
  worked = pthread_mutex_trylock((pthread_mutex_t*)m_pMutex) != EBUSY;
#else
  worked = WaitForSingleObject(m_pMutex, 1) == WAIT_OBJECT_0;
  if (m_bIsLocked) return false;
#endif

  if (worked) {
    m_bIsLocked = true;
  }

  return worked;
}

void Mutex::Unlock()
{
  ASSERT(m_bIsLocked);

#ifndef _MSC_VER
  pthread_mutex_unlock((pthread_mutex_t*)m_pMutex);
#else
  ReleaseMutex(m_pMutex);
#endif

  m_bIsLocked = false;
}

MutexWait::MutexWait(const Mutex &mutex)
{
  m_pMutex = &const_cast<Mutex&>(mutex);
  m_pMutex->Lock();
}

MutexWait::~MutexWait()
{
  m_pMutex->Unlock();
}

SCRATCH_NAMESPACE_END;
