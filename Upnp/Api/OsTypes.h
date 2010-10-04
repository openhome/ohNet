#ifndef HEADER_OS_TYPES
#define HEADER_OS_TYPES

#ifndef _WIN32
# define __STDC_LIMIT_MACROS
# include <stdint.h>
#else

// MSVC only includes stdint.h from v10
// define the small subset of stdint types Zapp cares about here

typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;

# define INT8_MIN	(-128)
# define INT16_MIN	(-32767-1)
# define INT32_MIN	(-2147483647-1)
# define INT8_MAX	0x7f
# define INT16_MAX	0x7fff
# define INT32_MAX	0x7fffffff
# define UINT8_MAX	0xff
# define UINT16_MAX	0xffff
# define UINT32_MAX	0xffffffff

#endif // !_WIN32

/**
 * Opaque handle to an OS resource
 */
typedef int32_t THandle;

/**
 * IpV4 address as network order uint32
 */
typedef uint32_t TIpAddress;

#endif // HEADER_OS_TYPES
