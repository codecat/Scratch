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

#ifdef SCRATCH_IMPL
#include <cstdio> // for vsprintf
#include <cstdarg> // for va_list
#include <cstring> // for strlen and strcmp
#include <ctype.h>
#endif

#include "StackArray.hpp"

#ifndef SCRATCH_NO_THREADSAFE
#include "Mutex.hpp"
#endif

#ifndef STRING_FORMAT_BUFFER_SIZE
#define STRING_FORMAT_BUFFER_SIZE 1024
#endif

SCRATCH_NAMESPACE_BEGIN;

class SCRATCH_EXPORT String
{
	friend class Filename;
protected:
	char* str_szBuffer;
#ifndef SCRATCH_NO_THREADSAFE
	Mutex str_mutex;
#endif

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
	void Split(const String &strNeedle, StackArray<String> &astrResult, bool bTrimAll) const;
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
	String& operator+=(const String &strSrc);

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

#ifdef SCRATCH_IMPL

int String::str_iInstances = 0;
char* String::str_szEmpty = (char*)"";

void String::CopyToBuffer(const char* szSrc)
{
	// Validate the source string
	if (szSrc == nullptr) {
		return;
	}

	int iLen = strlen(szSrc);
	if (iLen == 0) {
		// Clean up
		if (this->str_szBuffer != String::str_szEmpty) {
			delete[] this->str_szBuffer;
		}

		// Set to empty char*
		this->str_szBuffer = String::str_szEmpty;
		return;
	}

	// Find the current size and the required size for the string.
	int iBufLen = strlen(this->str_szBuffer) + 1;
	int iReqLen = iLen + 1;

	// Check if we need to make more room.
	if (iReqLen > iBufLen) {
		// Get rid of the previously allocated space and allocate new memory.
		if (this->str_szBuffer != String::str_szEmpty) {
			delete[] this->str_szBuffer;
		}
		this->str_szBuffer = new char[iReqLen];
	}

	// Copy data to the buffer.
	int i = 0;
	for (; i < iLen; i++) {
		this->str_szBuffer[i] = szSrc[i];
	}

	// Always end with a null terminator.
	this->str_szBuffer[i] = '\0';
}

void String::AppendToBuffer(const char* szSrc)
{
	this->AppendToBuffer(szSrc, strlen(szSrc));
}

void String::AppendToBuffer(const char* szSrc, int iCount)
{
	// Validate source string
	if (szSrc == nullptr) {
		return;
	}

	if (iCount <= 0) {
		return;
	}

	// Keep track of our previous buffer pointer so we can use it later for appending.
	char* szOldBuffer = this->str_szBuffer;

	// Find the current size and the required size for the string.
	int iBufLen = strlen(this->str_szBuffer);

	// Get ourselves a new buffer
	this->str_szBuffer = new char[iBufLen + iCount + 1];

	// Copy the buffers
	int iOffset = 0;

	for (int i = 0; i < iBufLen; i++) {
		this->str_szBuffer[iOffset++] = szOldBuffer[i];
	}

	for (int i = 0; i < iCount; i++) {
		this->str_szBuffer[iOffset++] = szSrc[i];
	}

	// Always end with a null terminator.
	this->str_szBuffer[iOffset] = '\0';

	// Clean up
	if (szOldBuffer != String::str_szEmpty) {
		delete[] szOldBuffer;
	}
}

void String::AppendToBuffer(const char cSrc)
{
	// Validate source string
	if (cSrc == 0) {
		return;
	}

	// Keep track of our previous buffer pointer so we can use it later for appending.
	char* szOldBuffer = this->str_szBuffer;

	// Find the current size and the required size for the string.
	int iBufLen = strlen(this->str_szBuffer);

	// Get ourselves a new buffer
	this->str_szBuffer = new char[iBufLen + 2];

	// Copy the buffer
	int iOffset = 0;

	for (int i = 0; i < iBufLen; i++) {
		this->str_szBuffer[iOffset++] = szOldBuffer[i];
	}

	// Append the new character
	this->str_szBuffer[iOffset++] = cSrc;

	// Always end with a null terminator.
	this->str_szBuffer[iOffset] = '\0';

	// Clean up
	if (szOldBuffer != String::str_szEmpty) {
		delete[] szOldBuffer;
	}
}

String::String()
{
	str_iInstances++;
	// Create a new empty buffer
	this->str_szBuffer = String::str_szEmpty;
}

String::String(const char* szStr)
{
	str_iInstances++;
	// Create a new buffer and copy data into it.
	this->str_szBuffer = String::str_szEmpty;
	this->CopyToBuffer(szStr);
}

String::String(const char* szValue, int iStart, int iLength)
{
	str_iInstances++;
	// Create a new buffer and copy data into it.
	this->str_szBuffer = String::str_szEmpty;
	this->AppendToBuffer(szValue + iStart, iLength);
}

String::String(const String &copy)
{
	str_iInstances++;
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(copy.str_mutex);
#endif
	// Create a new buffer and copy data into it.
	this->str_szBuffer = String::str_szEmpty;
	this->CopyToBuffer(copy);
}

String::~String()
{
	str_iInstances--;
	// Clean up
	if (this->str_szBuffer != String::str_szEmpty) {
		delete[] this->str_szBuffer;
	}
}

int String::Length() const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	return strlen(this->str_szBuffer);
}

void String::SetF(const char* szFormat, ...)
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif

	int iSize = STRING_FORMAT_BUFFER_SIZE;
	char* szBuffer = new char[iSize];

	// Get the args list and do a vsprintf to get the right format.
	va_list vL;
	va_start(vL, szFormat);

	// Make sure we don't overflow the buffer by checking against result length
	int iPrintSize = vsnprintf(szBuffer, iSize, szFormat, vL);
	if (iSize <= iPrintSize) {
		// Fail delete buffer and try again
		delete[] szBuffer;
		szBuffer = new char[iPrintSize + 1]; // +1 for \0
		vsnprintf(szBuffer, iPrintSize + 1, szFormat, vL);
	}
	va_end(vL);

	// Copy the just-created buffer to the main buffer
	this->CopyToBuffer(szBuffer);

	// Clean up
	delete[] szBuffer;
}

void String::AppendF(const char* szFormat, ...)
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif

	int iSize = STRING_FORMAT_BUFFER_SIZE;
	char* szBuffer = new char[iSize];

	// Get the args list and do a vsprintf to get the right format.
	va_list vL;
	va_start(vL, szFormat);

	// Make sure we don't overflow the buffer by checking against result length
	int iPrintSize = vsnprintf(szBuffer, iSize, szFormat, vL);
	if (iSize <= iPrintSize) {
		// Fail delete buffer and try again
		delete[] szBuffer;
		szBuffer = new char[iPrintSize + 1]; // +1 for \0
		vsnprintf(szBuffer, iPrintSize + 1, szFormat, vL);
	}
	va_end(vL);

	// Copy the just-created buffer to the main buffer
	this->AppendToBuffer(szBuffer);

	// Clean up
	delete[] szBuffer;
}

void String::Split(const String &strNeedle, StackArray<String> &astrResult) const
{
	Split(strNeedle, astrResult, FALSE);
}

void String::Split(const String &strNeedle, StackArray<String> &astrResult, bool bTrimAll) const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
	MutexWait wait2(strNeedle.str_mutex);
#endif

	// Keep a pointer to the current offset and a "previous offset"
	char* szOffset = str_szBuffer;
	char* szOffsetPrev = szOffset;
	int iCount = 1;

	do {
		// Find the needle from the string in the current offset pointer
		szOffset = strstr(szOffset, strNeedle);

		// If the needle is found
		if (szOffset != nullptr) {
			// Get the length for the string
			int iLen = szOffset - szOffsetPrev;

			// And get a buffer started
			char* szPart = new char[iLen + 1];

			// Copy over the characters to the part buffer
			int i = 0;
			for (; i < iLen; i++) {
				szPart[i] = *(szOffset - (iLen - i));
			}
			szPart[i] = '\0';

			// Add it to the return array
			astrResult.Push() = szPart;
			delete[] szPart;

			// Keep a seperate count
			iCount++;

			// Increase the offset pointer by the needle length
			szOffset += strlen(strNeedle);

			// Keep track of the pointer
			szOffsetPrev = szOffset;
		} else {
			// Get the length for the string
			int iLen = strlen(szOffsetPrev);

			// And get a buffer started
			char* szPart = new char[iLen + 1];

			// Copy over the characters to the part buffer
			int i = 0;
			for (; i < iLen; i++) {
				szPart[i] = szOffsetPrev[i];
			}
			szPart[i] = '\0';

			// Add it to the return vector
			String &strAdd = astrResult.Push();
			strAdd = szPart;
			if (bTrimAll) {
				strAdd = strAdd.Trim();
			}
			delete[] szPart;
		}
	} while (szOffset != nullptr);
}

void String::CommandLineSplit(StackArray<String> &astrResult) const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif

	char* sz = str_szBuffer;
	bool bInString = false;
	String strBuffer;

	do {
		char c = *sz;
		char cn = *(sz + 1);

		if (c == '\\') {
			strBuffer += *(++sz);
			continue;
		}

		if (bInString) {
			if (c == '"' && (cn == ' ' || cn == '\0')) {
				bInString = false;
				continue;
			}
		} else {
			if (c == '"' && strBuffer.Length() == 0) {
				bInString = true;
				continue;
			}
			if (c == ' ' && strBuffer.Length() != 0) {
				astrResult.Push() = strBuffer;
				strBuffer = "";
				continue;
			}
		}

		strBuffer += c;
	} while (*(++sz) != '\0');

	if (strBuffer.Length() != 0) {
		astrResult.Push() = strBuffer;
	}
}

String String::InternalTrim(bool bLeft, bool bRight, char c) const
{
	// Copy ourselves into a new buffer
	int len = strlen(this->str_szBuffer);
	char* szBuffer = new char[len + 1];
#if WINDOWS
	strcpy_s(szBuffer, len + 1, this->str_szBuffer);
#else
	strcpy(szBuffer, this->str_szBuffer);
#endif

	// Keep a pointer to the current offset
	char* szOffset = szBuffer;

	if (bLeft) {
		// While there's a space, keep incrementing the offset
		while (*szOffset == c) {
			// This way, we'll trim all the spaces on the left
			szOffset++;
		}
	}

	if (bRight) {
		// Loop from right to left in the string
		for (int i = strlen(szOffset) - 1; i >= 0; i--) {
			// When we find something other than a space
			if (szOffset[i] != c) {
				// Put a null terminator to trim the right part
				szOffset[i + 1] = '\0';

				// Stop reading
				break;
			}
		}
	}

	// Return
	String ret(szOffset);
	delete[] szBuffer;
	return ret;
}

String String::Trim() const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	return InternalTrim(true, true);
}

String String::Trim(char c) const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	return InternalTrim(true, true, c);
}

String String::TrimLeft() const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	return InternalTrim(true, false);
}

String String::TrimLeft(char c) const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	return InternalTrim(true, false, c);
}

String String::TrimRight() const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	return InternalTrim(false, true);
}

String String::TrimRight(char c) const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	return InternalTrim(false, true, c);
}

String String::Replace(const String &strNeedle, const String &strReplace) const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
	MutexWait wait2(strNeedle.str_mutex);
	MutexWait wait3(strReplace.str_mutex);
#endif

	String strRet("");

	// Keep a pointer to the current offset and a "previous offset"
	char* szOffset = this->str_szBuffer;
	char* szOffsetPrev = szOffset;

	do {
		// Find the offset of the needle
		szOffset = strstr(szOffset, strNeedle);

		// If it's found
		if (szOffset != nullptr) {
			// Append everything before the needle of the original characters to the return value
			strRet.AppendToBuffer(szOffsetPrev, szOffset - szOffsetPrev);

			// Append the replace value
			strRet.AppendToBuffer(strReplace);

			// Increase the offset pointer by the needle length
			szOffset += strlen(strNeedle);

			// Keep track of the pointer
			szOffsetPrev = szOffset;
		} else {
			// Append the remaining part of the source string
			strRet.AppendToBuffer(szOffsetPrev, strlen(szOffsetPrev));
		}
	} while (szOffset != nullptr);

	return strRet;
}

String String::SubString(int iStart) const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	return String(this->str_szBuffer + iStart);
}

String String::SubString(int iStart, int iLen) const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif

	// Empty strings
	if (iStart < 0 || iLen <= 0) {
		return "";
	}

	// Get the first offset
	String strRet(this->str_szBuffer + iStart);

	// Check for stupid developers
	if ((uint32_t)iLen > strlen(strRet)) {
		return strRet;
	}

	// Then set the null terminator at the length the user wants
	strRet[iLen] = '\0';

	// Return
	return strRet;
}

#if !WINDOWS
void strlwr(char* sz)
{
	int len = strlen(sz);
	for (int i = 0; i < len; i++) {
		sz[i] = tolower(sz[i]);
	}
}

void strupr(char* sz)
{
	int len = strlen(sz);
	for (int i = 0; i < len; i++) {
		sz[i] = toupper(sz[i]);
	}
}
#endif

String String::ToLower() const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	String strRet(this->str_szBuffer);
#if WINDOWS
	int len = strlen(this->str_szBuffer);
	_strlwr_s(strRet.str_szBuffer, len + 1);
#else
	strlwr(strRet.str_szBuffer);
#endif
	return strRet;
}

String String::ToUpper() const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	String strRet(this->str_szBuffer);
#if WINDOWS
	int len = strlen(this->str_szBuffer);
	_strupr_s(strRet.str_szBuffer, len + 1);
#else
	strupr(strRet.str_szBuffer);
#endif
	return strRet;
}

int String::IndexOf(char c) const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	const char* sz = strchr(this->str_szBuffer, c);
	if (sz != nullptr) {
		return sz - this->str_szBuffer;
	}
	return -1;
}

int String::IndexOf(const String &strNeedle) const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	const char* sz = strstr(this->str_szBuffer, strNeedle);
	if (sz != nullptr) {
		return sz - this->str_szBuffer;
	}
	return -1;
}

int String::IndexOfLast(char c) const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	const char* sz = strrchr(this->str_szBuffer, c);
	if (sz != nullptr) {
		return sz - this->str_szBuffer;
	}
	return -1;
}

// strrstr taken from: http://stuff.mit.edu/afs/sipb/user/cordelia/Diplomacy/mapit/strrstr.c
static char* strrstr(const char* s1, const char* s2)
{
	const char *sc2, *psc1, *ps1;

	if (*s2 == '\0') {
		return (char*)s1;
	}

	ps1 = s1 + strlen(s1);

	while (ps1 != s1) {
		--ps1;
		for (psc1 = ps1, sc2 = s2; ; ) {
			if (*(psc1++) != *(sc2++)) {
				break;
			} else if (*sc2 == '\0') {
				return (char*)ps1;
			}
		}
	}
	return nullptr;
}

int String::IndexOfLast(const String &strNeedle) const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	const char* sz = strrstr(this->str_szBuffer, strNeedle);
	if (sz != nullptr) {
		return sz - this->str_szBuffer;
	}
	return -1;
}

void String::Fill(char c, int ct)
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	char* szBuffer = new char[ct + 1];
	memset(szBuffer, c, ct);
	szBuffer[ct] = '\0';
	CopyToBuffer(szBuffer);
}

bool String::Contains(const String &strNeedle)
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
	MutexWait wait2(strNeedle.str_mutex);
#endif
	return strstr(this->str_szBuffer, strNeedle) != nullptr;
}

bool String::Contains(char c) const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	int iLen = strlen(str_szBuffer);
	for (int i = 0; i < iLen; i++) {
		if (str_szBuffer[i] == c) {
			return true;
		}
	}
	return false;
}

bool String::StartsWith(const String &strNeedle)
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
	MutexWait wait2(strNeedle.str_mutex);
#endif
	return strstr(this->str_szBuffer, strNeedle) == this->str_szBuffer;
}

bool String::EndsWith(const String &strNeedle)
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
	MutexWait wait2(strNeedle.str_mutex);
#endif

	// Get the offset
	const char* szTemp = strstr(this->str_szBuffer, strNeedle);

	// Make sure the needle is found
	if (szTemp == nullptr) {
		return false;
	}

	// Then compare the offset with our needle
	return !strcmp(strNeedle, szTemp);
}

String::operator const char *()
{
	return this->str_szBuffer;
}

String::operator const char *() const
{
	return this->str_szBuffer;
}

String& String::operator=(char* src)
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	// Copy the right hand side to the buffer.
	this->CopyToBuffer(src);
	return *this;
}

String& String::operator=(const char* src)
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	// Copy the right hand side to the buffer.
	this->CopyToBuffer(src);
	return *this;
}

String& String::operator=(const String &strSrc)
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
	MutexWait wait2(strSrc.str_mutex);
#endif
	// If the right hand side is not the left hand side...
	if (this != &strSrc) {
		// Copy the right hand side to the buffer.
		this->CopyToBuffer(strSrc);
	}
	return *this;
}

String& String::operator+=(const char* szSrc)
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	// Append the right hand side to the buffer.
	this->AppendToBuffer(szSrc);
	return *this;
}

String& String::operator+=(const char cSrc)
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	// Append the right hand side to the buffer.
	this->AppendToBuffer(cSrc);
	return *this;
}

String& String::operator+=(const String &strSrc)
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
	MutexWait wait2(strSrc.str_mutex);
#endif
	// Append the right hand side to the buffer.
	this->AppendToBuffer(strSrc.str_szBuffer);
	return *this;
}

String& String::operator*=(int ctRepeat)
{
	String strOriginal = *this;
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	for (int i = 1; i < ctRepeat; i++) {
		this->AppendToBuffer(strOriginal);
	}
	return *this;
}

bool String::operator==(const char* szSrc) const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	return !strcmp(this->str_szBuffer, szSrc);
}

bool String::operator!=(const char* szSrc) const
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	return strcmp(this->str_szBuffer, szSrc) != 0;
}

char& String::operator[](int iIndex)
{
#ifndef SCRATCH_NO_THREADSAFE
	MutexWait wait(str_mutex);
#endif
	return this->str_szBuffer[iIndex];
}

String operator+(const String &strLHS, const char* szRHS)
{
	return String(strLHS) += szRHS;
}

String operator+(const String &strLHS, const char cRHS)
{
	return String(strLHS) += cRHS;
}

String operator+(const char* szLHS, String &strRHS)
{
	return String(szLHS) += strRHS;
}

String operator+(const char cLHS, String &strRHS)
{
	return String(strRHS) += cLHS;
}

String operator*(const String &strLHS, int ctRepeat)
{
	return String(strLHS) *= ctRepeat;
}

String operator*(int ctRepeat, const String &strRHS)
{
	return String(strRHS) *= ctRepeat;
}

String strPrintF(const char* szFormat, ...)
{
	int iSize = STRING_FORMAT_BUFFER_SIZE;
	char* szBuffer = new char[iSize];

	// Get the args list and do a vsprintf to get the right format.
	va_list vL;
	va_start(vL, szFormat);

	// Make sure we don't overflow the buffer by checking against result length
	int iPrintSize = vsnprintf(szBuffer, iSize, szFormat, vL);
	if (iSize <= iPrintSize) {
		// Fail delete buffer and try again
		delete[] szBuffer;
		szBuffer = new char[iPrintSize + 1]; // +1 for \0
		vsnprintf(szBuffer, iPrintSize + 1, szFormat, vL);
	}
	va_end(vL);

	// Copy the just-created buffer to the main buffer
	String ret(szBuffer);

	// Clean up
	delete[] szBuffer;

	return ret;
}

#endif // include once check

SCRATCH_NAMESPACE_END;
