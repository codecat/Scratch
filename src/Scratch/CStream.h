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

#ifndef SCRATCH_CSTREAM_H_INCLUDED
#define SCRATCH_CSTREAM_H_INCLUDED

#include "Common.h"
#include "CString.h"

SCRATCH_NAMESPACE_BEGIN;

enum SCRATCH_EXPORT ENewLineMode
{
  ENLM_CRLF,
  ENLM_LF,
  ENLM_CR,
};

class SCRATCH_EXPORT CStream
{
public:
  ENewLineMode strm_nlmNewLineMode;

public:
  CStream(void);
  ~CStream(void);

  virtual ULONG Size() = 0;
  virtual ULONG Location() = 0;
  virtual void Seek(ULONG ulPos, INDEX iOrigin) = 0;
  virtual BOOL AtEOF() = 0;

  virtual void Close();

  virtual void Write(const void* p, ULONG iLen) = 0;
  inline void WriteIndex(const INDEX &i)   { Write(&i, sizeof(INDEX)); }
  inline void WriteLong(const LONG &l)     { Write(&l, sizeof(LONG)); }
  inline void WriteFloat(const FLOAT &f)   { Write(&f, sizeof(FLOAT)); }
  inline void WriteDouble(const DOUBLE &d) { Write(&d, sizeof(DOUBLE)); }
  void WriteString(const CString &str);
  void WriteStream(CStream &strm);

  virtual void Read(void* pDest, ULONG iLen) = 0;
  void ReadToEnd(void* pDest);
  inline INDEX  ReadIndex(void)  { INDEX  i; Read(&i, sizeof(INDEX)); return i; }
  inline LONG   ReadLong(void)   { LONG   l; Read(&l, sizeof(LONG)); return l; }
  inline FLOAT  ReadFloat(void)  { FLOAT  f; Read(&f, sizeof(FLOAT)); return f; }
  inline DOUBLE ReadDouble(void) { DOUBLE d; Read(&d, sizeof(DOUBLE)); return d; }
  CString ReadString(void);

  inline char ReadChar(void) { char c; Read(&c, 1); return c; }
  inline char PeekChar(void) { char c; Read(&c, 1); Seek(-1, 1/*SEEK_CUR*/); return c; }

  bool Expect(const CString &str);
  char ReadUntil(CString &strOut, const CString &strCharacters);

  void WriteText(const CString &str);
  void WriteLine(const CString &str);
  void WriteLine(void);
  CString ReadLine(void);

  inline CStream& operator <<(INDEX i)       { WriteIndex(i); return *this; }
  inline CStream& operator <<(FLOAT f)       { WriteFloat(f); return *this; }
  inline CStream& operator <<(DOUBLE d)      { WriteDouble(d); return *this; }
  inline CStream& operator <<(CString str)   { WriteString(str); return *this; }
  inline CStream& operator <<(CStream &strm) { WriteStream(strm); return *this; }

  inline CStream& operator >>(INDEX &i)      { i = ReadIndex(); return *this; }
  inline CStream& operator >>(FLOAT &f)      { f = ReadFloat(); return *this; }
  inline CStream& operator >>(DOUBLE &d)     { d = ReadDouble(); return *this; }
  inline CStream& operator >>(CString &str)  { str = ReadString(); return *this; }
};

SCRATCH_NAMESPACE_END;

#endif
