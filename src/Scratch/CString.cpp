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

void CString::SetF(const char* szFormat, ...)
{
  char* szBuffer = new char[CSTRING_FORMAT_BUFFER_SIZE];

  // Get the args list and do a vsprintf to get the right format.
  va_list vL;
  va_start(vL, szFormat);
  vsprintf(szBuffer, szFormat, vL);
  va_end(vL);

  // Copy the just-created buffer to the main buffer
  this->CopyToBuffer(szBuffer);

  // Clean up
  delete[] szBuffer;
}

void CString::AppendF(const char* szFormat, ...)
{
  char* szBuffer = new char[CSTRING_FORMAT_BUFFER_SIZE];

  // Get the args list and do a vsprintf to get the right format.
  va_list vL;
  va_start(vL, szFormat);
  vsprintf(szBuffer, szFormat, vL);
  va_end(vL);

  // Copy the just-created buffer to the main buffer
  this->AppendToBuffer(szBuffer);

  // Clean up
  delete[] szBuffer;
}

void CString::Split(const CString &strNeedle, CStackArray<CString> &astrResult) const
{
  Split(strNeedle, astrResult, FALSE, -1);
}

void CString::Split(const CString &strNeedle, CStackArray<CString> &astrResult, BOOL bTrimAll) const
{
  Split(strNeedle, astrResult, bTrimAll, -1);
}

void CString::Split(const CString &strNeedle, CStackArray<CString> &astrResult, BOOL bTrimAll, int iMax) const
{
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
      delete szPart;

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
      delete szPart;
    }
  } while(szOffset != NULL);
}

CString CString::Trim()
{
  // Keep a pointer to the current offset
  char* szOffset = this->str_szBuffer;

  // While there's a space, keep incrementing the offset
  while(*szOffset == ' ') {
    // This way, we'll trim all the spaces on the left
    szOffset++;
  }

  // Loop from right to left in the string
  for(int i=strlen(szOffset)-1; i>=0; i--) {
    // When we find something other than a space
    if(szOffset[i] != ' ') {
      // Put a null terminator to trim the right part
      szOffset[i + 1] = '\0';

      // Stop reading
      break;
    }
  }

  // Return
  return CString(szOffset);
}

CString CString::Replace(const CString &strNeedle, const CString &strReplace) const
{
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

CString CString::SubString(int iStart, int iLen) const
{
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
  CString strRet(this->str_szBuffer);
  strlwr(strRet.str_szBuffer);
  return strRet;
}

CString CString::ToUpper() const
{
  CString strRet(this->str_szBuffer);
  strupr(strRet.str_szBuffer);
  return strRet;
}

bool CString::Contains(const CString &strNeedle)
{
  return strstr(this->str_szBuffer, strNeedle) != NULL;
}

bool CString::Contains(char c) const
{
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
  return strstr(this->str_szBuffer, strNeedle) == this->str_szBuffer;
}

bool CString::EndsWith(const CString &strNeedle)
{
  // Locate the needle in the buffer
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
  // Copy the right hand side to the buffer.
  this->CopyToBuffer(src);
  return *this;
}

CString& CString::operator=(const char* src)
{
  // Copy the right hand side to the buffer.
  this->CopyToBuffer(src);
  return *this;
}

CString& CString::operator=(const CString &strSrc)
{
  // If the right hand side is not the left hand side...
  if(this != &strSrc) {
    // Copy the right hand side to the buffer.
    this->CopyToBuffer(strSrc);
  }
  return *this;
}

CString& CString::operator+=(const char* szSrc)
{
  // Append the right hand side to the buffer.
  this->AppendToBuffer(szSrc);
  return *this;
}

CString& CString::operator+=(const char cSrc)
{
  // Append the right hand side to the buffer.
  this->AppendToBuffer(cSrc);
  return *this;
}

bool CString::operator==(const char* szSrc) const
{
  return !strcmp(this->str_szBuffer, szSrc);
}

bool CString::operator!=(const char* szSrc) const
{
  return strcmp(this->str_szBuffer, szSrc) != 0;
}

char& CString::operator[](int iIndex)
{
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

CString strPrintF(const char* szFormat, ...)
{
  char* szBuffer = new char[CSTRING_FORMAT_BUFFER_SIZE];

  // Get the args list and do a vsprintf to get the right format.
  va_list vL;
  va_start(vL, szFormat);
  vsprintf(szBuffer, szFormat, vL);
  va_end(vL);

  // Copy the just-created buffer to the main buffer
  CString ret(szBuffer);

  // Clean up
  delete[] szBuffer;

  return ret;
}

SCRATCH_NAMESPACE_END;
