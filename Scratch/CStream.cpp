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

#include "CStream.h"

SCRATCH_NAMESPACE_BEGIN;

Stream::Stream(void)
{
  strm_nlmNewLineMode = ENLM_LF;
}

Stream::~Stream(void)
{
  Close();
}

void Stream::Close(void)
{
}

void Stream::WriteString(const String &str)
{
  Write((const char*)str, strlen(str) + 1);
}

void Stream::WriteStream(Stream &strm)
{
  // get buffer size
  ULONG ulBufferSize = strm.Size() - strm.Location();
  ULONG ulBytesLeft = ulBufferSize;

  // allocate memory for chunks
  ULONG ulChunkSize = 1024;
  void* pBuffer = malloc(ulChunkSize);

  // loop through chunks required to write
  while(ulBytesLeft > 0) {
    // check for end of stream
    if(ulBytesLeft < ulChunkSize) {
      ulChunkSize = ulBytesLeft;
    }
    // read chunk from other stream
    strm.Read(pBuffer, ulChunkSize);
    // write chunk into our stream
    Write(pBuffer, ulChunkSize);
  }

  // we're done, deallocate buffer
  free(pBuffer);
}

void Stream::ReadToEnd(void* pDest)
{
  Read(pDest, Size() - Location());
}

String Stream::ReadString(void)
{
  String strRet;
  char c;
  do {
    // read 1 character
    Read(&c, sizeof(char));

    // if it's not the terminator
    if(c != '\0') {
      // he'll be back
      strRet += c;
    }
  } while(c != '\0');

  // done, return
  return strRet;
}

bool Stream::Expect(const String &str)
{
  int iLen = strlen(str);

  char* szBuffer = new char[iLen+1];
  szBuffer[iLen] = '\0';

  Read(szBuffer, iLen);
  bool ret = (str == szBuffer);

  if(!ret) {
    Seek(-iLen, SEEK_CUR);
  }

  delete[] szBuffer;
  return ret;
}

char Stream::ReadUntil(String &strOut, const String &strCharacters)
{
  String ret;
  char ccc = '\0';
  while(!AtEOF()) {
    char cc = ReadChar();
    if(strCharacters.Contains(cc)) {
      ccc = cc;
      break;
    }
    ret += cc;
  }
  strOut = ret;
  return ccc;
}

void Stream::WriteText(const String &str)
{
  // write text
  Write((const char*)str, strlen(str));
}

void Stream::WriteLine(const String &str)
{
  // write text
  WriteText(str);
  // write newline
  WriteLine();
}

void Stream::WriteLine(void)
{
  // write newline
  switch(strm_nlmNewLineMode) {
  case ENLM_CRLF: Write("\r\n", 2); break;
  case ENLM_LF: Write("\n", 1); break;
  case ENLM_CR: Write("\r", 1); break;
  }
}

String Stream::ReadLine(void)
{
  String strRet;
  char c;
  do {
    // read 1 character
    Read(&c, sizeof(char));

    // if at EOF
    if(AtEOF()) {
      // we're done here
      break;
    }

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

SCRATCH_NAMESPACE_END;
