#ifndef HEADER_DVPROVIDER_C
#define HEADER_DVPROVIDER_C

#include <OsTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

DllExport void DvProviderPropertiesLock(THandle aProvider);
DllExport void DvProviderPropertiesUnlock(THandle aProvider);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVPROVIDER_C
