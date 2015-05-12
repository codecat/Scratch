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

#include "CException.h"

SCRATCH_NAMESPACE_BEGIN;

CException::CException()
{
}

CException::CException(const char* format, ...)
{
  int iSize = 256;
  char* szBuffer = new char[iSize];

  // Get the args list and do a vsprintf to get the right format.
  va_list vL;
  va_start(vL, format);

  // Make sure we don't overflow the buffer by checking against result length
  int iPrintSize = vsnprintf(szBuffer, iSize, format, vL);
  if(iSize <= iPrintSize) {
    // Fail delete buffer and try again
    delete[] szBuffer;
    szBuffer = new char[iPrintSize + 1]; // +1 for \0
    vsnprintf(szBuffer, iPrintSize + 1, format, vL);
  }
  va_end(vL);

  // Copy the just-created buffer to the main buffer
  Message = szBuffer;

  // Clean up
  delete[] szBuffer;
}

CException::~CException()
{
}

SCRATCH_NAMESPACE_END;

