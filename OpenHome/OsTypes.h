#ifndef HEADER_OS_TYPES
#define HEADER_OS_TYPES

#define __STDC_LIMIT_MACROS
#include <stdint.h>

/**
 * Opaque handle to an OS resource
 */
typedef void* THandle;

/**
 * IpV4 address as network order uint32
 */

#define kFamilyV4 0
#define kFamilyV6 1

typedef struct TIpAddress
{
    uint8_t iFamily;
    uint32_t iV4;
    uint8_t iV6[16];
} TIpAddress;

static const TIpAddress kIpAddressV4AllAdapters = {0};

/**
 * Opaque handle to a singleton, setup before other Os functions are called
 */
typedef struct OsContext OsContext;

/* Doxygen groups */
/**
 * @defgroup Core          Core Services
 * @defgroup ControlPoint  Control Point Stack
 * @defgroup Device        Device Stack
 */
/**
 * @defgroup Callbacks     Callbacks
 * @ingroup  Core
 */
/**
 * @defgroup Proxies       Service Proxies
 * @ingroup ControlPoint
 */
/**
 * @defgroup Providers     Service Providers
 * @ingroup Device
 */

#endif // HEADER_OS_TYPES
