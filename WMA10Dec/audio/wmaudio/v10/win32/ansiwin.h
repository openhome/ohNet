//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

// This file contains cut-and-pasted definitions from the various windows
// include files. This file can be included by an ANSI-C compiler, and
// the target should be able to run on a windows machine.

#ifndef _ANSIWIN_H_
#define _ANSIWIN_H_

//-----------------------------------------------
// Defines
//-----------------------------------------------
#define INFINITE            0xFFFFFFFF  // From winbase.h
#define CreateEvent  CreateEventA       // From winbase.h
#define NOERROR             0           // From winerror.h
#define STATUS_WAIT_0                    ((DWORD   )0x00000000L)    // From winnt.h
#define WAIT_OBJECT_0       ((STATUS_WAIT_0 ) + 0 )                 // From winbase.h7

#define WINAPI      __stdcall                   // From windef.h
#define DECLSPEC_IMPORT __declspec(dllimport)   // From winnt.h
#define WINBASEAPI DECLSPEC_IMPORT              // From winbase.h
#define WINUSERAPI DECLSPEC_IMPORT              // From winuser.h
#define VER_PLATFORM_WIN32_NT           2       // From winnt.h

#ifdef UNICODE
typedef unsigned short  TCHAR;                  // From winnt.h and stdio.h
#define OutputDebugString  OutputDebugStringW   // From winbase.h
#define TEXT(quote)     L##quote                // From winnt.h
#else
typedef char            TCHAR;                  // From winnt.h
#define OutputDebugString  OutputDebugStringA   // From winbase.h
#define TEXT(quote)     quote                   // From winnt.h
#endif  // UNICODE

//-----------------------------------------------
// Typedefs
//-----------------------------------------------
typedef U32 DWORD, *LPDWORD;    // Stolen from windef.h
typedef U16 WORD;               // Stolen from windef.h
typedef int BOOL;               // Stolen from windef.h
typedef void *LPVOID;           // Stolen from windef.h
typedef void *HANDLE;           // Stolen from winnt.h
#define VOID void               // Stolen from winnt.h
typedef unsigned __int64 ULONG_PTR; // Stolen from basetsd.h
typedef ULONG_PTR DWORD_PTR;

typedef const char *LPCSTR, *PCSTR;             // Stolen from winnt.h
typedef const unsigned short *LPCWSTR, *PCWSTR; // Stolen from winnt.h
typedef const TCHAR *LPCTSTR, *PCTSTR;

typedef char CHAR;                              // From ntdef.h
typedef unsigned short WCHAR;                   // From ntdef.h

// From winbase.h
typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

// From winbase.h
typedef DWORD (WINAPI *PTHREAD_START_ROUTINE)(
    LPVOID lpThreadParameter
    );
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

// From winnt.h
typedef union _LARGE_INTEGER {
    struct {
        U32 LowPart;
        I32 HighPart;
    };
    struct {
        U32 LowPart;
        I32 HighPart;
    } u;
    I64 QuadPart;
} LARGE_INTEGER;

// From winnt.h
typedef union _ULARGE_INTEGER {
    struct {
        U32 LowPart;
        U32 HighPart;
    };
    struct {
        U32 LowPart;
        U32 HighPart;
    } u;
    U64 QuadPart;
} ULARGE_INTEGER;

// From winnt.h
typedef struct _OSVERSIONINFOA {
    DWORD dwOSVersionInfoSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformId;
    CHAR  szCSDVersion[ 128 ];     // Maintenance string for PSS usage
} OSVERSIONINFOA, *POSVERSIONINFOA, *LPOSVERSIONINFOA;
typedef struct _OSVERSIONINFOW {
    DWORD dwOSVersionInfoSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformId;
    WCHAR  szCSDVersion[ 128 ];     // Maintenance string for PSS usage
} OSVERSIONINFOW, *POSVERSIONINFOW, *LPOSVERSIONINFOW, RTL_OSVERSIONINFOW, *PRTL_OSVERSIONINFOW;

// From winbase.h
typedef struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

// From winbase.h
//#if defined(_WIN64)
//#error We assumed DWORD_PTR == U32 for SYSTEM_INFO::dwActiveProcessorMask. Must fix!
//#endif  // _WIN64

typedef struct _SYSTEM_INFO {
    union {
        DWORD dwOemId;          // Obsolete field...do not use
        struct {
            WORD wProcessorArchitecture;
            WORD wReserved;
        };
    };
    DWORD dwPageSize;
    LPVOID lpMinimumApplicationAddress;
    LPVOID lpMaximumApplicationAddress;
    DWORD dwActiveProcessorMask; // Defined as DWORD_PTR in Whistler SDK but is U32 for Win32
    DWORD_PTR dwNumberOfProcessors;
    DWORD dwProcessorType;
    DWORD dwAllocationGranularity;
    WORD wProcessorLevel;
    WORD wProcessorRevision;
} SYSTEM_INFO, *LPSYSTEM_INFO;


//-----------------------------------------------
// Function Prototypes
//-----------------------------------------------

// Winbase.h Functions
WINBASEAPI BOOL WINAPI SetEvent(HANDLE hEvent);
WINBASEAPI DWORD WINAPI WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);
WINBASEAPI BOOL WINAPI CloseHandle(HANDLE hObject);

WINBASEAPI HANDLE WINAPI CreateEventA(LPSECURITY_ATTRIBUTES lpEventAttributes,
    BOOL bManualReset, BOOL bInitialState, LPCSTR lpName);
WINBASEAPI HANDLE WINAPI CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes,
    DWORD dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter,
    DWORD dwCreationFlags, LPDWORD lpThreadId);


WINBASEAPI BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);
WINBASEAPI BOOL WINAPI QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);

WINBASEAPI VOID WINAPI OutputDebugStringA(LPCSTR lpOutputString);
WINBASEAPI VOID WINAPI OutputDebugStringW(LPCWSTR lpOutputString);
WINBASEAPI BOOL WINAPI GetVersionExA(LPOSVERSIONINFOA lpVersionInformation);
WINBASEAPI BOOL WINAPI GetVersionExW(LPOSVERSIONINFOW lpVersionInformation);
WINBASEAPI HANDLE WINAPI GetCurrentProcess(VOID);
WINBASEAPI BOOL WINAPI GetProcessTimes(
    HANDLE hProcess,
    LPFILETIME lpCreationTime,
    LPFILETIME lpExitTime,
    LPFILETIME lpKernelTime,
    LPFILETIME lpUserTime
    );
WINBASEAPI VOID WINAPI GetSystemInfo(LPSYSTEM_INFO lpSystemInfo);
WINBASEAPI BOOL WINAPI SetThreadPriority(HANDLE hThread, int nPriority);
WINBASEAPI int WINAPI GetThreadPriority(HANDLE hThread);
WINBASEAPI HANDLE WINAPI GetCurrentThread(VOID);

// from objidl.h
typedef struct IStream IStream;
// from unknwn.h
typedef struct IUnknown IUnknown;
// WinUser.h Functions
#include <stdarg.h> // For va_list
//WINUSERAPI int WINAPI wvsprintf(LPSTR, LPCSTR, va_list);
//Handle unicode and non-unicode in ANSI as well.
WINUSERAPI int WINAPI wvsprintfA(__out LPSTR, LPCSTR, va_list);
WINUSERAPI int WINAPI wvsprintfW(__out LPWSTR, LPCWSTR, va_list);

#ifdef UNICODE
#define wvsprintf  wvsprintfW
#define GetVersionEx  GetVersionExW
typedef OSVERSIONINFOW OSVERSIONINFO;
#else
#define wvsprintf  wvsprintfA
#define GetVersionEx  GetVersionExA
typedef OSVERSIONINFOA OSVERSIONINFO;
#endif // !UNICODE


#endif // _ANSIWIN_H_
