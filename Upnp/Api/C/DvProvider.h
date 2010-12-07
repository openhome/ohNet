#ifndef HEADER_DVPROVIDER_C
#define HEADER_DVPROVIDER_C

#include <OsTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProvider
 * @ingroup Device
 * @{
 */

/**
 * Lock the provider's properties, blocking publication of updates.
 *
 * This is not necessary when updating a single property but is used by providers that have
 * >1 properties whose values are related.  Without locking, updates to some properties may
 * be published, leaving related properties in their old (now incompatible) states.
 *
 * Every call to this must be followed by (exactly) one call to DvProviderPropertiesUnlock().
 *
 * @param[in] aProvider   Handle to a provider
 */
DllExport void DvProviderPropertiesLock(THandle aProvider);

/**
 * Unlock the provider's properties, allowing publication of updates.
 *
 * Any pending updates will automatically be scheduled.
 * This must only be called following a call to DvProviderPropertiesLock().
 *
 * @param[in] aProvider   Handle to a provider
 */
DllExport void DvProviderPropertiesUnlock(THandle aProvider);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVPROVIDER_C
