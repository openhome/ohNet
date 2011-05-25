/**
 * Provider for the openhome.org:TestDimmableLight:1 UPnP service
 */
#ifndef HEADER_DVOPENHOMEORGTESTDIMMABLELIGHT1_C
#define HEADER_DVOPENHOMEORGTESTDIMMABLELIGHT1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderOpenhomeOrgTestDimmableLight1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the GetLevel action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderOpenhomeOrgTestDimmableLight1EnableActionGetLevel
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestDimmableLight1GetLevel)(void* aPtr, uint32_t aVersion, uint32_t* aLevel);
/**
 * Callback which runs when the SetLevel action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderOpenhomeOrgTestDimmableLight1EnableActionSetLevel
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestDimmableLight1SetLevel)(void* aPtr, uint32_t aVersion, uint32_t aLevel);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderOpenhomeOrgTestDimmableLight1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestDimmableLight1Create
 */
DllExport void DvProviderOpenhomeOrgTestDimmableLight1Destroy(THandle aProvider);

/**
 * Register a callback for the action GetLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestDimmableLight1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderOpenhomeOrgTestDimmableLight1EnableActionGetLevel(THandle aProvider, CallbackTestDimmableLight1GetLevel aCallback, void* aPtr);
/**
 * Register a callback for the action SetLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderOpenhomeOrgTestDimmableLight1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderOpenhomeOrgTestDimmableLight1EnableActionSetLevel(THandle aProvider, CallbackTestDimmableLight1SetLevel aCallback, void* aPtr);

/**
 * Set the value of the A_ARG_Level property
 *
 * @param[in]  aProvider  Handle returned by DvProviderOpenhomeOrgTestDimmableLight1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderOpenhomeOrgTestDimmableLight1SetPropertyA_ARG_Level(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the A_ARG_Level property
 *
 * @param[in]  aProvider  Handle returned by DvProviderOpenhomeOrgTestDimmableLight1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderOpenhomeOrgTestDimmableLight1GetPropertyA_ARG_Level(THandle aProvider, uint32_t* aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVOPENHOMEORGTESTDIMMABLELIGHT1_C

