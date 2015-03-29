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

#ifndef SCRATCH_CNETWORKSTREAM_H_INCLUDED
#define SCRATCH_CNETWORKSTREAM_H_INCLUDED

#include "Common.h"
#include "CStream.h"

#if WINDOWS
#include <WinSock2.h>
#else
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#endif

SCRATCH_NAMESPACE_BEGIN;

class SCRATCH_EXPORT CNetworkStream : public CStream
{
public:
#if WINDOWS
  WSADATA* ns_pWSAData;
  SOCKET ns_socket;
#else
  int ns_socket;
#endif
  sockaddr_in* ns_psin;

  BOOL ns_bEOF;

public:
  CNetworkStream(void);
  ~CNetworkStream(void);

  ULONG Size();
  ULONG Location();
  void Seek(ULONG ulPos, INDEX iOrigin);
  BOOL AtEOF();

  BOOL Connect(const char* szAddress, USHORT iPort);
  void Close();
  void Write(const void* p, ULONG iLen);
  void Read(void* pDest, ULONG iLen);

  BOOL IsConnected();

  static void Cleanup(void);
};

SCRATCH_NAMESPACE_END;

#endif