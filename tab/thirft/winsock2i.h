#ifndef WINSOCK2I_H
#define WINSOCK2I_H

//For sovle winsock2 problem
#ifdef _WINSOCK2API_

#if !defined(WIN32_LEAN_AND_MEAN) && (_WIN32_WINNT >= 0x0400) && !defined(USING_WIN_PSDK)
#include <windows.h>
#else
#include <WinSock2.h>
#endif


#endif // WINSOCK2I_H
