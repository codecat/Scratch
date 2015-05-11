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

#include <cstdio> // for vsprintf
#include <cstdarg> // for va_list
#include <cstring> // for strlen and strcmp
#include <ctype.h>

#include "CString.h"

SCRATCH_NAMESPACE_BEGIN;

int CString::str_iInstances = 0;
char* CString::str_szEmpty = (char*)"";

void CString::CopyToBuffer(const char* szSrc)
{
  // Validate the source string
  if(szSrc == NULL) {
    return;
  }

  int iLen = strlen(szSrc);
  if(iLen == 0) {
    // Clean up
    if(this->str_szBuffer != CString::str_szEmpty) {
      delete[] this->str_szBuffer;
    }

    // Set to empty char*
    this->str_szBuffer = CString::str_szEmpty;
    return;
  }

  // Find the current size and the required size for the string.
  int iBufLen = strlen(this->str_szBuffer) + 1;
  int iReqLen = iLen + 1;

  // Check if we need to make more room.
  if(iReqLen > iBufLen) {
    // Get rid of the previously allocated space and allocate new memory.
    if(this->str_szBuffer != CString::str_szEmpty) {
      delete[] this->str_szBuffer;
    }
    this->str_szBuffer = new char[iReqLen];
  }

  // Copy data to the buffer.
  int i = 0;
  for(; i<iLen; i++) {
    this->str_szBuffer[i] = szSrc[i];
  }

  // Always end with a null terminator.
  this->str_szBuffer[i] = '\0';
}

void CString::AppendToBuffer(const char* szSrc)
{
  this->AppendToBuffer(szSrc, strlen(szSrc));
}

void CString::AppendToBuffer(const char* szSrc, int iCount)
{
  // Validate source string
  if(szSrc == NULL) {
    return;
  }

  if(iCount <= 0) {
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

  for(int i=0; i<iBufLen; i++) {
    this->str_szBuffer[iOffset++] = szOldBuffer[i];
  }

  for(int i=0; i<iCount; i++) {
    this->str_szBuffer[iOffset++] = szSrc[i];
  }

  // Always end with a null terminator.
  this->str_szBuffer[iOffset] = '\0';

  // Clean up
  if(szOldBuffer != CString::str_szEmpty) {
    delete[] szOldBuffer;
  }
}

void CString::AppendToBuffer(const char cSrc)
{
  // Validate source string
  if(cSrc == 0) {
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

  for(int i=0; i<iBufLen; i++) {
    this->str_szBuffer[iOffset++] = szOldBuffer[i];
  }

  // Append the new character
  this->str_szBuffer[iOffset++] = cSrc;

  // Always end with a null terminator.
  this->str_szBuffer[iOffset] = '\0';

  // Clean up
  if(szOldBuffer != CString::str_szEmpty) {
    delete[] szOldBuffer;
  }
}

CString::CString()
{
  str_iInstances++;
  // Create a new empty buffer
  this->str_szBuffer = CString::str_szEmpty;
}

CString::CString(const char* szStr)
{
  str_iInstances++;
  // Create a new buffer and copy data into it.
  this->str_szBuffer = CString::str_szEmpty;
  this->CopyToBuffer(szStr);
}

CString::CString(const char* szValue, int iStart, int iLength)
{
  str_iInstances++;
  // Create a new buffer and copy data into it.
  this->str_szBuffer = CString::str_szEmpty;
  this->AppendToBuffer(szValue + iStart, iLength);
}

CString::CString(const CString &copy)
{
  str_iInstances++;
  CMutexWait wait(copy.str_mutex);
  // Create a new buffer and copy data into it.
  this->str_szBuffer = CString::str_szEmpty;
  this->CopyToBuffer(copy);
}

CString::~CString()
{
  str_iInstances--;
  // Clean up
  if(this->str_szBuffer != CString::str_szEmpty) {
    delete[] this->str_szBuffer;
  }
}

int CString::Length() const
{
  CMutexWait wait(str_mutex);
  return strlen(this->str_szBuffer);
}

void CString::SetF(const char* szFormat, ...)
{
  CMutexWait wait(str_mutex);

  int iSize = CSTRING_FORMAT_BUFFER_SIZE;
  char* szBuffer = new char[iSize];

  // Get the args list and do a vsprintf to get the right format.
  va_list vL;
  va_start(vL, szFormat);

  // Make sure we don't overflow the buffer by checking against result length
  int iPrintSize = vsnprintf(szBuffer, iSize, szFormat, vL);
  if(iSize <= iPrintSize) {
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

void CString::AppendF(const char* szFormat, ...)
{
  CMutexWait wait(str_mutex);

  int iSize = CSTRING_FORMAT_BUFFER_SIZE;
  char* szBuffer = new char[iSize];

  // Get the args list and do a vsprintf to get the right format.
  va_list vL;
  va_start(vL, szFormat);

  // Make sure we don't overflow the buffer by checking against result length
  int iPrintSize = vsnprintf(szBuffer, iSize, szFormat, vL);
  if(iSize <= iPrintSize) {
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

void CString::Split(const CString &strNeedle, CStackArray<CString> &astrResult) const
{
  Split(strNeedle, astrResult, FALSE);
}

void CString::Split(const CString &strNeedle, CStackArray<CString> &astrResult, BOOL bTrimAll) const
{
  CMutexWait wait(str_mutex);
  CMutexWait wait2(strNeedle.str_mutex);

  // Keep a pointer to the current offset and a "previous offset"
  char* szOffset = str_szBuffer;
  char* szOffsetPrev = szOffset;
  int iCount = 1;

  do {
    // Find the needle from the string in the current offset pointer
    szOffset = strstr(szOffset, strNeedle);

    // If the needle is found
    if(szOffset != NULL) {
      // Get the length for the string
      int iLen = szOffset - szOffsetPrev;

      // And get a buffer started
      char* szPart = new char[iLen + 1];

      // Copy over the characters to the part buffer
      int i = 0;
      for(; i<iLen; i++) {
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
      for(; i<iLen; i++) {
        szPart[i] = szOffsetPrev[i];
      }
      szPart[i] = '\0';

      // Add it to the return vector
      CString &strAdd = astrResult.Push();
      strAdd = szPart;
      if(bTrimAll) {
        strAdd = strAdd.Trim();
      }
      delete[] szPart;
    }
  } while(szOffset != NULL);
}

void CString::CommandLineSplit(CStackArray<CString> &astrResult) const
{
  CMutexWait wait(str_mutex);

  char* sz = str_szBuffer;
  bool bInString = false;
  CString strBuffer;

  do {
    char c = *sz;
    char cn = *(sz + 1);

    if(c == '\\') {
      strBuffer += *(++sz);
      continue;
    }

    if(bInString) {
      if(c == '"' && (cn == ' ' || cn == '\0')) {
        bInString = false;
        continue;
      }
    } else {
      if(c == '"' && strBuffer.Length() == 0) {
        bInString = true;
        continue;
      }
      if(c == ' ' && strBuffer.Length() != 0) {
        astrResult.Push() = strBuffer;
        strBuffer = "";
        continue;
      }
    }

    strBuffer += c;
  } while(*(++sz) != '\0');

  if(strBuffer.Length() != 0) {
    astrResult.Push() = strBuffer;
  }
}

CString CString::InternalTrim(bool bLeft, bool bRight, char c) const
{
  // Copy ourselves into a new buffer
  char* szBuffer = new char[strlen(this->str_szBuffer) + 1];
  strcpy(szBuffer, this->str_szBuffer);

  // Keep a pointer to the current offset
  char* szOffset = szBuffer;

  if(bLeft) {
    // While there's a space, keep incrementing the offset
    while(*szOffset == c) {
      // This way, we'll trim all the spaces on the left
      szOffset++;
    }
  }

  if(bRight) {
    // Loop from right to left in the string
    for(int i=strlen(szOffset)-1; i>=0; i--) {
      // When we find something other than a space
      if(szOffset[i] != c) {
        // Put a null terminator to trim the right part
        szOffset[i + 1] = '\0';

        // Stop reading
        break;
      }
    }
  }

  // Return
  CString ret(szOffset);
  delete[] szBuffer;
  return ret;
}

CString CString::Trim() const
{
  CMutexWait wait(str_mutex);
  return InternalTrim(true, true);
}

CString CString::Trim(char c) const
{
  CMutexWait wait(str_mutex);
  return InternalTrim(true, true, c);
}

CString CString::TrimLeft() const
{
  CMutexWait wait(str_mutex);
  return InternalTrim(true, false);
}

CString CString::TrimLeft(char c) const
{
  CMutexWait wait(str_mutex);
  return InternalTrim(true, false, c);
}

CString CString::TrimRight() const
{
  CMutexWait wait(str_mutex);
  return InternalTrim(false, true);
}

CString CString::TrimRight(char c) const
{
  CMutexWait wait(str_mutex);
  return InternalTrim(false, true, c);
}

CString CString::Replace(const CString &strNeedle, const CString &strReplace) const
{
  CMutexWait wait(str_mutex);
  CMutexWait wait2(strNeedle.str_mutex);
  CMutexWait wait3(strReplace.str_mutex);

  CString strRet("");

  // Keep a pointer to the current offset and a "previous offset"
  char* szOffset = this->str_szBuffer;
  char* szOffsetPrev = szOffset;

  do {
    // Find the offset of the needle
    szOffset = strstr(szOffset, strNeedle);

    // If it's found
    if(szOffset != NULL) {
      // Append everything before the needle of the original characters to the return value
      strRet.AppendToBuffer(szOffsetPrev, szOffset - szOffsetPrev);

      // Append the replace value
      strRet += strReplace;

      // Increase the offset pointer by the needle length
      szOffset += strlen(strNeedle);

      // Keep track of the pointer
      szOffsetPrev = szOffset;
    } else {
      // Append the remaining part of the source string
      strRet.AppendToBuffer(szOffsetPrev, strlen(szOffsetPrev));
    }
  } while(szOffset != NULL);

  return strRet;
}

CString CString::SubString(int iStart) const
{
  CMutexWait wait(str_mutex);
  return CString(this->str_szBuffer + iStart);
}

CString CString::SubString(int iStart, int iLen) const
{
  CMutexWait wait(str_mutex);

  // Empty strings
  if(iStart < 0 || iLen <= 0) {
    return "";
  }

  // Get the first offset
  CString strRet(this->str_szBuffer + iStart);

  // Check for stupid developers
  if((ULONG)iLen > strlen(strRet)) {
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
  for(int i=0; i<len; i++) {
    sz[i] = tolower(sz[i]);
  }
}

void strupr(char* sz)
{
  int len = strlen(sz);
  for(int i=0; i<len; i++) {
    sz[i] = toupper(sz[i]);
  }
}
#endif

CString CString::ToLower() const
{
  CMutexWait wait(str_mutex);
  CString strRet(this->str_szBuffer);
  strlwr(strRet.str_szBuffer);
  return strRet;
}

CString CString::ToUpper() const
{
  CMutexWait wait(str_mutex);
  CString strRet(this->str_szBuffer);
  strupr(strRet.str_szBuffer);
  return strRet;
}

int CString::IndexOf(char c) const
{
  CMutexWait wait(str_mutex);
  const char* sz = strchr(this->str_szBuffer, c);
  if(sz != NULL) {
    return sz - this->str_szBuffer;
  }
  return -1;
}

int CString::IndexOf(const CString &strNeedle) const
{
  CMutexWait wait(str_mutex);
  const char* sz = strstr(this->str_szBuffer, strNeedle);
  if(sz != NULL) {
    return sz - this->str_szBuffer;
  }
  return -1;
}

int CString::IndexOfLast(char c) const
{
  CMutexWait wait(str_mutex);
  const char* sz = strrchr(this->str_szBuffer, c);
  if(sz != NULL) {
    return sz - this->str_szBuffer;
  }
  return -1;
}

// strrstr taken from: http://stuff.mit.edu/afs/sipb/user/cordelia/Diplomacy/mapit/strrstr.c
static char* strrstr(const char* s1, const char* s2)
{
  const char *sc2, *psc1, *ps1;

  if(*s2 == '\0') {
    return (char*)s1;
  }

  ps1 = s1 + strlen(s1);

  while(ps1 != s1) {
    --ps1;
    for(psc1 = ps1, sc2 = s2; ; ) {
      if(*(psc1++) != *(sc2++)) {
        break;
      } else if(*sc2 == '\0') {
        return (char*)ps1;
      }
    }
  }
  return NULL;
}

int CString::IndexOfLast(const CString &strNeedle) const
{
  CMutexWait wait(str_mutex);
  const char* sz = strrstr(this->str_szBuffer, strNeedle);
  if(sz != NULL) {
    return sz - this->str_szBuffer;
  }
  return -1;
}

void CString::Fill(char c, int ct)
{
  CMutexWait wait(str_mutex);
  char* szBuffer = new char[ct + 1];
  memset(szBuffer, c, ct);
  szBuffer[ct] = '\0';
  CopyToBuffer(szBuffer);
}

bool CString::Contains(const CString &strNeedle)
{
  CMutexWait wait(str_mutex);
  CMutexWait wait2(strNeedle.str_mutex);
  return strstr(this->str_szBuffer, strNeedle) != NULL;
}

bool CString::Contains(char c) const
{
  CMutexWait wait(str_mutex);
  int iLen = strlen(str_szBuffer);
  for(int i=0; i<iLen; i++) {
    if(str_szBuffer[i] == c) {
      return true;
    }
  }
  return false;
}

bool CString::StartsWith(const CString &strNeedle)
{
  CMutexWait wait(str_mutex);
  CMutexWait wait2(strNeedle.str_mutex);
  return strstr(this->str_szBuffer, strNeedle) == this->str_szBuffer;
}

bool CString::EndsWith(const CString &strNeedle)
{
  CMutexWait wait(str_mutex);
  CMutexWait wait2(strNeedle.str_mutex);

  // Get the offset
  const char* szTemp = strstr(this->str_szBuffer, strNeedle);

  // Make sure the needle is found
  if(szTemp == NULL) {
    return false;
  }

  // Then compare the offset with our needle
  return !strcmp(strNeedle, szTemp);
}

CString::operator const char *()
{
  return this->str_szBuffer;
}

CString::operator const char *() const
{
  return this->str_szBuffer;
}

CString& CString::operator=(char* src)
{
  CMutexWait wait(str_mutex);
  // Copy the right hand side to the buffer.
  this->CopyToBuffer(src);
  return *this;
}

CString& CString::operator=(const char* src)
{
  CMutexWait wait(str_mutex);
  // Copy the right hand side to the buffer.
  this->CopyToBuffer(src);
  return *this;
}

CString& CString::operator=(const CString &strSrc)
{
  CMutexWait wait(str_mutex);
  CMutexWait wait2(strSrc.str_mutex);
  // If the right hand side is not the left hand side...
  if(this != &strSrc) {
    // Copy the right hand side to the buffer.
    this->CopyToBuffer(strSrc);
  }
  return *this;
}

CString& CString::operator+=(const char* szSrc)
{
  CMutexWait wait(str_mutex);
  // Append the right hand side to the buffer.
  this->AppendToBuffer(szSrc);
  return *this;
}

CString& CString::operator+=(const char cSrc)
{
  CMutexWait wait(str_mutex);
  // Append the right hand side to the buffer.
  this->AppendToBuffer(cSrc);
  return *this;
}

CString& CString::operator*=(int ctRepeat)
{
  CString strOriginal = *this;
  CMutexWait wait(str_mutex);
  for(int i=1; i<ctRepeat; i++) {
    this->AppendToBuffer(strOriginal);
  }
  return *this;
}

bool CString::operator==(const char* szSrc) const
{
  CMutexWait wait(str_mutex);
  return !strcmp(this->str_szBuffer, szSrc);
}

bool CString::operator!=(const char* szSrc) const
{
  CMutexWait wait(str_mutex);
  return strcmp(this->str_szBuffer, szSrc) != 0;
}

char& CString::operator[](int iIndex)
{
  CMutexWait wait(str_mutex);
  return this->str_szBuffer[iIndex];
}

CString operator+(const CString &strLHS, const char* szRHS)
{
  return CString(strLHS) += szRHS;
}

CString operator+(const CString &strLHS, const char cRHS)
{
  return CString(strLHS) += cRHS;
}

CString operator+(const char* szLHS, CString &strRHS)
{
  return CString(szLHS) += strRHS;
}

CString operator+(const char cLHS, CString &strRHS)
{
  return CString(strRHS) += cLHS;
}

CString operator*(const CString &strLHS, int ctRepeat)
{
  return CString(strLHS) *= ctRepeat;
}

CString operator*(int ctRepeat, const CString &strRHS)
{
  return CString(strRHS) *= ctRepeat;
}

CString strPrintF(const char* szFormat, ...)
{
  int iSize = CSTRING_FORMAT_BUFFER_SIZE;
  char* szBuffer = new char[iSize];

  // Get the args list and do a vsprintf to get the right format.
  va_list vL;
  va_start(vL, szFormat);

  // Make sure we don't overflow the buffer by checking against result length
  int iPrintSize = vsnprintf(szBuffer, iSize, szFormat, vL);
  if(iSize <= iPrintSize) {
    // Fail delete buffer and try again
    delete[] szBuffer;
    szBuffer = new char[iPrintSize + 1]; // +1 for \0
    vsnprintf(szBuffer, iPrintSize + 1, szFormat, vL);
  }
  va_end(vL);

  // Copy the just-created buffer to the main buffer
  CString ret(szBuffer);

  // Clean up
  delete[] szBuffer;

  return ret;
}

SCRATCH_NAMESPACE_END;
