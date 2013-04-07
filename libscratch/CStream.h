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

#ifndef SCRATCH_CSTREAM_H_INCLUDED
#define SCRATCH_CSTREAM_H_INCLUDED 1

#ifdef USE_PRAGMAONCE
  #pragma once
#endif

#include "Common.h"
#include "CString.h"

SCRATCH_NAMESPACE_BEGIN;

enum ENewLineMode
{
  ENLM_CRLF,
  ENLM_LF,
  ENLM_CR,
};

class CStream
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
