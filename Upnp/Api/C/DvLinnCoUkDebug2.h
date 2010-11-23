/**
 * Provider for the linn.co.uk:Debug:2 UPnP service
 */
#ifndef HEADER_DVLINNCOUKDEBUG2_C
#define HEADER_DVLINNCOUKDEBUG2_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback which runs when the SetDebugLevel action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDebug2EnableActionSetDebugLevel
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaDebugLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDebug2SetDebugLevel)(void* aPtr, uint32_t aVersion, uint32_t aaDebugLevel);
/**
 * Callback which runs when the DebugLevel action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDebug2EnableActionDebugLevel
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaDebugLevel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDebug2DebugLevel)(void* aPtr, uint32_t aVersion, uint32_t* aaDebugLevel);
/**
 * Callback which runs when the MemWrite action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkDebug2EnableActionMemWrite
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaMemAddress
 * @param[in]  aaMemData
 * @param[in]  aaMemDataLen
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackDebug2MemWrite)(void* aPtr, uint32_t aVersion, uint32_t aaMemAddress, const char* aaMemData, uint32_t aaMemDataLen);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkDebug2Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDebug2Create
 */
DllExport void DvProviderLinnCoUkDebug2Destroy(THandle aProvider);

/**
 * Register a callback for the action SetDebugLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDebug2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDebug2EnableActionSetDebugLevel(THandle aProvider, CallbackDebug2SetDebugLevel aCallback, void* aPtr);
/**
 * Register a callback for the action DebugLevel
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDebug2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDebug2EnableActionDebugLevel(THandle aProvider, CallbackDebug2DebugLevel aCallback, void* aPtr);
/**
 * Register a callback for the action MemWrite
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkDebug2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkDebug2EnableActionMemWrite(THandle aProvider, CallbackDebug2MemWrite aCallback, void* aPtr);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKDEBUG2_C

