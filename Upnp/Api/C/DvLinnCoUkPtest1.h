/**
 * Provider for the linn.co.uk:Ptest:1 UPnP service
 */
#ifndef HEADER_DVLINNCOUKPTEST1_C
#define HEADER_DVLINNCOUKPTEST1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback which runs when the TestComPort action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPtest1EnableActionTestComPort
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaPort
 * @param[out] aaResult
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPtest1TestComPort)(void* aPtr, uint32_t aVersion, uint32_t aaPort, uint32_t* aaResult);
/**
 * Callback which runs when the LedsOn action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPtest1EnableActionLedsOn
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPtest1LedsOn)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the LedsOff action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkPtest1EnableActionLedsOff
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackPtest1LedsOff)(void* aPtr, uint32_t aVersion);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkPtest1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPtest1Create
 */
DllExport void DvProviderLinnCoUkPtest1Destroy(THandle aProvider);

/**
 * Register a callback for the action TestComPort
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPtest1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPtest1EnableActionTestComPort(THandle aProvider, CallbackPtest1TestComPort aCallback, void* aPtr);
/**
 * Register a callback for the action LedsOn
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPtest1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPtest1EnableActionLedsOn(THandle aProvider, CallbackPtest1LedsOn aCallback, void* aPtr);
/**
 * Register a callback for the action LedsOff
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkPtest1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkPtest1EnableActionLedsOff(THandle aProvider, CallbackPtest1LedsOff aCallback, void* aPtr);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPTEST1_C

