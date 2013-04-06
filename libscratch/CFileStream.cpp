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

void CFileStream::Open(const char* szFileName, const char* szMode)
{
  // must not already have a handle open
  ASSERT(fs_pfh == NULL);

  // open file
  FILE* pfh = fopen(szFileName, szMode);

  // it might not exist
  ASSERT(pfh != NULL);

  // remember info
  fs_strFileName = szFileName;
  fs_pfh = pfh;
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

void CFileStream::Read(void* pDest, ULONG iLen)
{
  fread(pDest, 1, iLen, fs_pfh);
}

SCRATCH_NAMESPACE_END;
