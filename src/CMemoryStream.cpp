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

BOOL CMemoryStream::AtEOF()
{
  return Size() - Location() > 0;
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

void CMemoryStream::Read(void* pDest, ULONG iLen)
{
  // copy data to destination
  memcpy(pDest, strm_pubBuffer + strm_ulPosition, iLen);
  
  // increase position
  strm_ulPosition += iLen;
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
