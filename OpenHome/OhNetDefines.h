#ifndef HEADER_OHNET_DEFINES
#define HEADER_OHNET_DEFINES

#ifdef _WIN32
# ifndef DllExport
#  define DllExport __declspec(dllexport)
# endif
# ifndef DllExportClass
#  define DllExportClass
# endif
# define STDCALL __stdcall
# define INLINE __inline
#else
# ifndef DllExport
#  define DllExport __attribute__ ((visibility("default")))
# endif
# ifndef DllExportClass
#  define DllExportClass __attribute__ ((visibility("default")))
# endif
# define STDCALL
# define INLINE inline
#endif

#endif /* HEADER_OHNET_DEFINES */
