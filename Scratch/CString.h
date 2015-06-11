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
#include "CMutex.h"

#ifndef CSTRING_FORMAT_BUFFER_SIZE
#define CSTRING_FORMAT_BUFFER_SIZE 1024
#endif

SCRATCH_NAMESPACE_BEGIN;

class SCRATCH_EXPORT String
{
	friend class Filename;
protected:
  char* str_szBuffer;
  Mutex str_mutex;

  void CopyToBuffer(const char* szSrc);
  void AppendToBuffer(const char* szSrc);
  void AppendToBuffer(const char* szSrc, int iCount);
  void AppendToBuffer(const char cSrc);

public:
  static char* str_szEmpty;
  static int str_iInstances;

	String();
	String(const char* szValue);
	String(const char* szValue, int iStart, int iLength);
	String(const String &strCopy);
	virtual ~String();

  int Length() const;

  void SetF(const char* szFormat, ...);
  void AppendF(const char* szFormat, ...);

	void Split(const String &strNeedle, StackArray<String> &astrResult) const;
	void Split(const String &strNeedle, StackArray<String> &astrResult, BOOL bTrimAll) const;
	void CommandLineSplit(StackArray<String> &astrResult) const;
private:
	String InternalTrim(bool bLeft, bool bRight, char c = ' ') const;
public:
	String Trim() const;
	String Trim(char c) const;
	String TrimLeft() const;
	String TrimLeft(char c) const;
	String TrimRight() const;
	String TrimRight(char c) const;
	String Replace(const String &strNeedle, const String &strReplace) const;
	String SubString(int iStart) const;
	String SubString(int iStart, int iLen) const;
	String ToLower() const;
	String ToUpper() const;

  int IndexOf(char c) const;
	int IndexOf(const String &strNeedle) const;

  int IndexOfLast(char c) const;
	int IndexOfLast(const String &strNeedle) const;

  void Fill(char c, int ct);

	bool Contains(const String &strNeedle);
  bool Contains(char c) const;
	bool StartsWith(const String &strNeedle);
	bool EndsWith(const String &strNeedle);

  operator const char*();
  operator const char*() const;

	String& operator=(char* szSrc);
	String& operator=(const char* szSrc);
	String& operator=(const String &strSrc);

	String& operator+=(const char* szSrc);
	String& operator+=(const char cSrc);

	String& operator*=(int ctRepeat);

  bool operator==(const char* szSrc) const;
  bool operator!=(const char* szSrc) const;

  char& operator[](int iIndex);
};

String SCRATCH_EXPORT operator+(const String &strLHS, const char* szRHS);
String SCRATCH_EXPORT operator+(const String &strLHS, const char cRHS);

String SCRATCH_EXPORT operator+(const char* szLHS, String &strRHS);
String SCRATCH_EXPORT operator+(const char cLHS, String &strRHS);

String SCRATCH_EXPORT operator*(const String &strLHS, int ctRepeat);
String SCRATCH_EXPORT operator*(int ctRepeat, const String &strRHS);

String SCRATCH_EXPORT strPrintF(const char* szFormat, ...);

SCRATCH_NAMESPACE_END;

#endif // include once check
