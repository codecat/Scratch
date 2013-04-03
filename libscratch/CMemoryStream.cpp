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

#include "CMemoryStream.h"

SCRATCH_NAMESPACE_BEGIN;

CMemoryStream::CMemoryStream(void)
{
  strm_pubBuffer = NULL;
  strm_ulPosition = 0;
  strm_ulSize = 0;
  strm_ulUsed = 0;
  AllocateMoreMemory(1024);
}

CMemoryStream::~CMemoryStream(void)
{
  delete[] strm_pubBuffer;
}

ULONG CMemoryStream::Size()
{
  return strm_ulUsed;
}

ULONG CMemoryStream::Location()
{
  return strm_ulPosition;
}

void CMemoryStream::Seek(ULONG ulPos, INDEX iOrigin)
{
  switch(iOrigin) {
  case SEEK_CUR: strm_ulPosition += ulPos; break;
  case SEEK_END: strm_ulPosition = Size() + ulPos; break;
  case SEEK_SET: strm_ulPosition = ulPos; break;
  }
}

void CMemoryStream::Write(const void* p, ULONG iLen)
{
  // check if we need a larger buffer
  if(strm_ulPosition + iLen >= strm_ulSize) {
    AllocateMoreMemory(Max<INDEX>(iLen, 1024));
  }

  // copy over memory
  memcpy(strm_pubBuffer + strm_ulPosition, p, iLen);

  // increase position
  strm_ulPosition += iLen;

  // update used counter
  strm_ulUsed = Max<ULONG>(strm_ulPosition, strm_ulUsed);
}

void* CMemoryStream::Read(ULONG iLen)
{
  // create a new buffer
  void* pBuffer = malloc(iLen);
  memcpy(pBuffer, strm_pubBuffer + strm_ulPosition, iLen);
  
  // increase position
  strm_ulPosition += iLen;

  // return pointer to buffer
  return pBuffer;
}

void CMemoryStream::AllocateMoreMemory(INDEX ctBytes)
{
  ASSERT(ctBytes > 0);

  // create new buffer and remember old one
  UBYTE* pubNewBuffer = new UBYTE[strm_ulSize + ctBytes];
  UBYTE* pubOldBuffer = strm_pubBuffer;
  
  // if there's old memory to copy
  if(pubOldBuffer != NULL && strm_ulSize > 0) {
    memcpy(pubNewBuffer, pubOldBuffer, strm_ulSize);
  }

  // increase the size count
  strm_ulSize += ctBytes;

  // set the new buffer pointer
  strm_pubBuffer = pubNewBuffer;

  // delete old memory
  if(pubOldBuffer != NULL) {
    delete[] pubOldBuffer;
  }
}

SCRATCH_NAMESPACE_END;
