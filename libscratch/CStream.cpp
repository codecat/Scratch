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

#include "CStream.h"

CStream::CStream(void)
{
  strm_nlmNewLineMode = ENLM_LF;
}

CStream::~CStream(void)
{
  Close();
}

void CStream::Close(void)
{
}

void CStream::WriteString(const CString &str)
{
  Write((const char*)str, strlen(str) + 1);
}

void CStream::WriteStream(CStream &strm)
{
  ULONG ulPos = strm.Location();
  const void* pBuffer = strm.ReadToEnd();
  Write(pBuffer, strm.Size() - ulPos);
}

void* CStream::ReadToEnd(void)
{
  return Read(Size() - Location());
}

CString CStream::ReadString(void)
{
  CString strRet;
  char c;
  do {
    // read 1 character
    c = *(char*)Read(sizeof(char));

    // if it's not the terminator
    if(c != '\0') {
      // he'll be back
      strRet += c;
    }
  } while(c != '\0');

  // done, return
  return strRet;
}

void CStream::WriteLine(const CString &str)
{
  // write text
  Write((const char*)str, strlen(str));

  // write newline
  switch(strm_nlmNewLineMode) {
  case ENLM_CRLF: Write("\r\n", 2); break;
  case ENLM_LF: Write("\n", 1); break;
  case ENLM_CR: Write("\r", 1); break;
  }
}

CString CStream::ReadLine(void)
{
  CString strRet;
  char c;
  do {
    // read 1 character
    c = *(char*)Read(sizeof(char));

    // skip \r
    if(c == '\r') {
      //WARNING: This can potentially cause problems on certain operating systems
      //         that work with \r _only_ as a newline character. We should incorporate
      //         strm_nlmNewLineMode with this in a future version.
      continue;
    }

    // if it's not the terminator
    if(c != '\n') {
      // he'll be back
      strRet += c;
    }
  } while(c != '\n');

  // done, return
  return strRet;
}