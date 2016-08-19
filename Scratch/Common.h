/*	libscratch - Multipurpose objective C++ library.

		Copyright (c) 2013 - 2016 Angelo Geels <spansjh@gmail.com>

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

#pragma once

#include <cstdio>
#include <cmath>
#include <cassert>
#include <cstdint>

#ifdef _MSC_VER
	#include <WinSock2.h>
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <Windows.h>
	#define WINDOWS 1
#else
	#define WINDOWS 0
#endif

#ifdef __APPLE__
	#define MACOSX 1
#else
	#define MACOSX 0
#endif

#ifndef SCRATCH_NAMESPACE
	#define SCRATCH_NAMESPACE Scratch
#endif

#define SCRATCH_NAMESPACE_BEGIN namespace SCRATCH_NAMESPACE {
#define SCRATCH_NAMESPACE_END }

#ifndef SCRATCH_NO_GLOBFUNC
template<class T> inline T Max(const T &v1, const T &v2) { return v1 >= v2 ? v1 : v2; }
template<class T> inline T Min(const T &v1, const T &v2) { return v1 <= v2 ? v1 : v2; }
template<class T> inline void Swap(T &v1, T &v2) { T t = v1; v1 = v2; v2 = t; }

template<class T> inline T Abs(const T &v) { return v < 0 ? -v : v; }
#endif

#ifndef ASSERT
#define ASSERT assert
#endif
