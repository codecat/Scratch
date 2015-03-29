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

#include "CNetworkStream.h"

#if WINDOWS
#pragma comment(lib, "wsock32.lib")
#endif

SCRATCH_NAMESPACE_BEGIN;

#if WINDOWS
static BOOL _bWinsockInitialized = FALSE;
#endif

CNetworkStream::CNetworkStream(void)
{
#if WINDOWS
  ns_pWSAData = new WSADATA;
  ns_socket = NULL;
#else
  ns_socket = 0;
#endif
  ns_psin = new sockaddr_in;

  ns_bEOF = FALSE;

#if WINDOWS
  if(!_bWinsockInitialized) {
    if(WSAStartup(MAKEWORD(2, 2), ns_pWSAData) != 0) {
      throw "Couldn't initialize winsock";
    }
    _bWinsockInitialized = TRUE;
  }
#endif
}

CNetworkStream::~CNetworkStream(void)
{
  if(ns_socket != NULL) {
#if WINDOWS
    closesocket(ns_socket);
#else
    close(ns_socket);
#endif
  }

#if WINDOWS
  delete ns_pWSAData;
#endif
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
#if WINDOWS
  closesocket(ns_socket);
#else
  close(ns_socket);
#endif
  ns_socket = NULL;
}

void CNetworkStream::Write(const void* p, ULONG iLen)
{
  send(ns_socket, (const char*)p, iLen, 0);
}

void CNetworkStream::Read(void* pDest, ULONG iLen)
{
  int iRet = recv(ns_socket, (char*)pDest, iLen, 0);
  ns_bEOF = (iRet == 0) || ((ULONG)iRet < iLen);
}

BOOL CNetworkStream::IsConnected()
{
#if WINDOWS
  fd_set fds;
  fds.fd_array[0] = ns_socket;
  fds.fd_count = 1;
  return select(0, &fds, &fds, &fds, NULL) == 1;
#else
  return TRUE; //TODO: FIXME
#endif
}

void CNetworkStream::Cleanup(void)
{
#if WINDOWS
  if(_bWinsockInitialized) {
    WSACleanup();
    _bWinsockInitialized = false;
  }
#endif
}

SCRATCH_NAMESPACE_END;
