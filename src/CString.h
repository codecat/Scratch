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

#ifndef SCRATCH_CSTRING_H_INCLUDED
#define SCRATCH_CSTRING_H_INCLUDED

#include "CStackArray.h"

#ifndef CSTRING_FORMAT_BUFFER_SIZE
#define CSTRING_FORMAT_BUFFER_SIZE 1024
#endif

SCRATCH_NAMESPACE_BEGIN;

class SCRATCH_EXPORT CString
{
private:
  char* str_szBuffer;

  void CopyToBuffer(const char* szSrc);
  void AppendToBuffer(const char* szSrc);
  void AppendToBuffer(const char* szSrc, int iCount);
  void AppendToBuffer(const char cSrc);

public:
  static char* str_szEmpty;
  static int str_iInstances;

  CString();
  CString(const char* szValue);
  CString(const CString &strCopy);
  ~CString();

  void SetF(const char* szFormat, ...);
  void AppendF(const char* szFormat, ...);

  void Split(const CString &strNeedle, CStackArray<CString> &astrResult) const;
  void Split(const CString &strNeedle, CStackArray<CString> &astrResult, BOOL bTrimAll) const ;
  void Split(const CString &strNeedle, CStackArray<CString> &astrResult, BOOL bTrimAll, int iMax) const;
  CString Trim();
  CString Replace(const CString &strNeedle, const CString &strReplace) const;
  CString SubString(int iStart, int iLen) const;
  CString ToLower() const;
  CString ToUpper() const;

  bool Contains(const CString &strNeedle);
  bool Contains(char c) const;
  bool StartsWith(const CString &strNeedle);
  bool EndsWith(const CString &strNeedle);

  operator const char*();
  operator const char*() const;

  CString& operator=(char* szSrc);
  CString& operator=(const char* szSrc);
  CString& operator=(const CString &strSrc);

  CString& operator+=(const char* szSrc);
  CString& operator+=(const char cSrc);

  bool operator==(const char* szSrc) const;
  bool operator!=(const char* szSrc) const;

  char& operator[](int iIndex);
};

CString SCRATCH_EXPORT operator+(const CString &strLHS, const char* szRHS);
CString SCRATCH_EXPORT operator+(const CString &strLHS, const char cRHS);

CString SCRATCH_EXPORT operator+(const char* szLHS, CString &strRHS);
CString SCRATCH_EXPORT operator+(const char cLHS, CString &strRHS);

CString SCRATCH_EXPORT strPrintF(const char* szFormat, ...);

SCRATCH_NAMESPACE_END;

#endif // include once check
