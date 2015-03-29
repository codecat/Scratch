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

typedef           long INDEX;
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
