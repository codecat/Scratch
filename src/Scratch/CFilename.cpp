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

#include "CFilename.h"

#if WINDOWS
#include <ShlObj.h>
#endif

SCRATCH_NAMESPACE_BEGIN;

CFilename::CFilename()
{
  str_iInstances++;
  // Create a new empty buffer
  this->str_szBuffer = CString::str_szEmpty;
}

CFilename::CFilename(const CFilename &copy)
{
  str_iInstances++;
  // Create a new buffer and copy data into it.
  this->str_szBuffer = CString::str_szEmpty;
  this->CopyToBuffer(copy);
}

CFilename::CFilename(const char* szStr)
{
  str_iInstances++;
  // Create a new buffer and copy data into it.
  this->str_szBuffer = CString::str_szEmpty;
  this->CopyToBuffer(szStr);
}

CFilename::CFilename(const CString &str)
{
  str_iInstances++;
  // Create a new buffer and copy data into it.
  this->str_szBuffer = CString::str_szEmpty;
  this->CopyToBuffer(str.str_szBuffer);
}

CString CFilename::Extension() const
{
  return CString(strrchr(str_szBuffer, '.') + 1);
}

CString CFilename::Path() const
{
  return CString(str_szBuffer, 0, strrchr(str_szBuffer, '/') - str_szBuffer);
}

CString CFilename::Filename() const
{
  return CString(strrchr(str_szBuffer, '/') + 1);
}

void CFilename::FromHome(const CString &strPath)
{
#if WINDOWS
  char szPath[MAX_PATH];
  if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0, szPath))) {
    this->CopyToBuffer(szPath);
    this->AppendToBuffer("\\" + strPath);
  }
#else
  this->CopyToBuffer("~/" + strPath);
#endif
}

SCRATCH_NAMESPACE_END;
