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

#ifndef SCRATCH_COMMON_H_INCLUDED
#define SCRATCH_COMMON_H_INCLUDED

#include <cstdio>
#include <cmath>
#include <cassert>

#ifdef _MSC_VER
#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#define WINDOWS 1
#else
#define WINDOWS 0
#endif

#define SCRATCH_NAMESPACE_BEGIN namespace Scratch {
#define SCRATCH_NAMESPACE_END }

#if WINDOWS
#define SCRATCH_EXPORT __declspec(dllexport)
#elif defined(_GCC)
#define SCRATCH_EXPORT __attribute__((visibility("default"))
#else
#define SCRATCH_EXPORT
#endif

#ifdef NULL
#undef NULL
#endif
#define NULL 0

#define TRUE 1
#define FALSE 0

typedef            int INDEX;
typedef          float FLOAT;
typedef         double DOUBLE;
typedef            int BOOL;
typedef  unsigned char UBYTE;
#if !WINDOWS
typedef unsigned short USHORT;
typedef           long LONG;
typedef  unsigned long ULONG;
#endif

#ifndef SCRATCH_NO_GLOBFUNC
template<class T> inline T Max(const T &v1, const T &v2) { return v1 >= v2 ? v1 : v2; }
template<class T> inline T Min(const T &v1, const T &v2) { return v1 <= v2 ? v1 : v2; }
template<class T> inline void Swap(T &v1, T &v2) { T t = v1; v1 = v2; v2 = t; }

template<class T> inline T Abs(const T &v) { return v < 0 ? -v : v; }
#endif

//#ifdef SCRATCH_ALIAS_LEGACY_PREFIX
#define CString String
#define CFilename Filename
#define CStackArray StackArray
#define CDictionary Dictionary
#define CException Exception
#define CStream Stream
#define CMemoryStream MemoryStream
#define CFileStream FileStream
#define CNetworkStream NetworkStream
//#endif

#ifndef ASSERT

#ifdef _MSC_VER
SCRATCH_NAMESPACE_BEGIN;
inline BOOL SCRATCH_EXPORT _scratch_assert(const char* expr, const char* filename, unsigned lineno);
SCRATCH_NAMESPACE_END;
// Windows
#define ASSERT(expr) {             \
  if(!(expr)) {                    \
    static UBYTE bWasHere = 0;     \
    if(!bWasHere) {                \
      if(Scratch::_scratch_assert( \
        #expr,                     \
        __FILE__,                  \
        __LINE__)) {               \
        __asm { int 3 }            \
      }                            \
      bWasHere = 1;                \
    }                              \
  }                                \
}
#else
// Other sensible operating systems
#define ASSERT(expr) assert(expr)
#endif

#endif

#endif // include once check
