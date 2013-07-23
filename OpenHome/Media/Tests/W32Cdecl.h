#ifndef HEADER_W32CDECL
#define HEADER_W32CDECL

#ifndef CDECL
# ifdef _WIN32
#  define CDECL __cdecl
# else
#  define CDECL
# endif
#endif

#endif // HEADER_W32CDECL
