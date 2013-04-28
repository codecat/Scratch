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

#include "CNetworkStream.h"

#pragma comment(lib, "wsock32.lib")

SCRATCH_NAMESPACE_BEGIN;

static BOOL _bWinsockInitialized = FALSE;

CNetworkStream::CNetworkStream(void)
{
  ns_pWSAData = new WSADATA;
  ns_socket = NULL;
  ns_psin = new sockaddr_in;

  ns_bEOF = FALSE;

  if(!_bWinsockInitialized) {
    if(WSAStartup(MAKEWORD(2, 2), ns_pWSAData) != 0) {
      throw "Couldn't initialize winsock";
    }
    _bWinsockInitialized = TRUE;
  }
}

CNetworkStream::~CNetworkStream(void)
{
  if(ns_socket != NULL) {
    closesocket(ns_socket);
  }

  delete ns_pWSAData;
  delete ns_psin;
}

ULONG CNetworkStream::Size()
{
  throw "Function not supported in Network Stream";
}

ULONG CNetworkStream::Location()
{
  throw "Function not supported in Network Stream";
}

void CNetworkStream::Seek(ULONG ulPos, INDEX iOrigin)
{
  throw "Function not supported in Network Stream";
}

BOOL CNetworkStream::AtEOF()
{
  return ns_bEOF;
}

BOOL CNetworkStream::Connect(const char* szAddress, USHORT iPort)
{
  hostent* phe = gethostbyname(szAddress);
  if(phe == NULL) {
    return FALSE;
  }

  ns_psin->sin_family = AF_INET;
  ns_psin->sin_addr.s_addr = *(ULONG*)phe->h_addr_list[0];
  ns_psin->sin_port = htons(iPort);

  ns_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(connect(ns_socket, (sockaddr*)ns_psin, sizeof(sockaddr_in)) == 0) {
    return TRUE;
  }

  return FALSE;
}

void CNetworkStream::Close()
{
  closesocket(ns_socket);
  ns_socket = NULL;
}

void CNetworkStream::Write(const void* p, ULONG iLen)
{
  send(ns_socket, (const char*)p, iLen, 0);
}

void CNetworkStream::Read(void* pDest, ULONG iLen)
{
  int iRet = recv(ns_socket, (char*)pDest, iLen, 0);
  ns_bEOF = (iRet == 0) || (iRet < iLen);
}

BOOL CNetworkStream::IsConnected()
{
  fd_set fds;
  fds.fd_array[0] = ns_socket;
  fds.fd_count = 1;
  return select(0, &fds, &fds, &fds, NULL) == 1;
}

void CNetworkStream::Cleanup(void)
{
  if(_bWinsockInitialized) {
    WSACleanup();
    _bWinsockInitialized = false;
  }
}

SCRATCH_NAMESPACE_END;
