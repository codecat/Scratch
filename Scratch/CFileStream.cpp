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

#include "CFileStream.h"

SCRATCH_NAMESPACE_BEGIN;

CFileStream::CFileStream(void)
{
  fs_pfh = NULL;
}

CFileStream::~CFileStream(void)
{
  Close();
}

ULONG CFileStream::Size()
{
  ULONG ulPos = Location();
  Seek(0, SEEK_END);
  ULONG ulSize = Location();
  Seek(ulPos, SEEK_SET);
  return ulSize;
}

ULONG CFileStream::Location()
{
  return ftell(fs_pfh);
}

void CFileStream::Seek(ULONG ulPos, INDEX iOrigin)
{
  fseek(fs_pfh, ulPos, iOrigin);
}

BOOL CFileStream::AtEOF()
{
  return feof(fs_pfh) > 0;
}

BOOL CFileStream::Open(const char* szFileName, const char* szMode)
{
  // must not already have a handle open
  ASSERT(fs_pfh == NULL);

  // open file
  FILE* pfh = fopen(szFileName, szMode);

  // it might not exist
  if(pfh == NULL) {
    return FALSE;
  }

  // remember info
  fs_strFileName = szFileName;
  fs_pfh = pfh;

  // success
  return TRUE;
}

void CFileStream::OpenStdout()
{
  fs_strFileName = "stdout";
  fs_pfh = stdout;
}

void CFileStream::OpenStdin()
{
  fs_strFileName = "stdin";
  fs_pfh = stdin;
}

void CFileStream::OpenStderr()
{
  fs_strFileName = "stderr";
  fs_pfh = stderr;
}

void CFileStream::Close(void)
{
  // close the file handle
  if(fs_pfh != NULL) {
    fclose(fs_pfh);
    fs_pfh = NULL;
  }
}

void CFileStream::Write(const void* p, ULONG iLen)
{
  fwrite(p, 1, iLen, fs_pfh);
}

int CFileStream::Read(void* pDest, ULONG iLen)
{
  return fread(pDest, 1, iLen, fs_pfh);
}

SCRATCH_NAMESPACE_END;
