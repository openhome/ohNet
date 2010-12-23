/**
 * Provider for the linn.co.uk:Volkano:1 UPnP service
 */
#ifndef HEADER_DVLINNCOUKVOLKANO1_C
#define HEADER_DVLINNCOUKVOLKANO1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderLinnCoUkVolkano1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Reboot action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkVolkano1EnableActionReboot
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolkano1Reboot)(void* aPtr, uint32_t aVersion);
/**
 * Callback which runs when the BootMode action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkVolkano1EnableActionBootMode
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaMode
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolkano1BootMode)(void* aPtr, uint32_t aVersion, char** aaMode);
/**
 * Callback which runs when the SetBootMode action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkVolkano1EnableActionSetBootMode
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaMode
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolkano1SetBootMode)(void* aPtr, uint32_t aVersion, const char* aaMode);
/**
 * Callback which runs when the BspType action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkVolkano1EnableActionBspType
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaBspType
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolkano1BspType)(void* aPtr, uint32_t aVersion, char** aaBspType);
/**
 * Callback which runs when the UglyName action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkVolkano1EnableActionUglyName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaUglyName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolkano1UglyName)(void* aPtr, uint32_t aVersion, char** aaUglyName);
/**
 * Callback which runs when the MacAddress action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkVolkano1EnableActionMacAddress
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaMacAddress
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolkano1MacAddress)(void* aPtr, uint32_t aVersion, char** aaMacAddress);
/**
 * Callback which runs when the ProductId action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkVolkano1EnableActionProductId
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaProductNumber
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolkano1ProductId)(void* aPtr, uint32_t aVersion, char** aaProductNumber);
/**
 * Callback which runs when the BoardId action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkVolkano1EnableActionBoardId
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaIndex
 * @param[out] aaBoardNumber
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolkano1BoardId)(void* aPtr, uint32_t aVersion, uint32_t aaIndex, char** aaBoardNumber);
/**
 * Callback which runs when the BoardType action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkVolkano1EnableActionBoardType
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaIndex
 * @param[out] aaBoardNumber
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolkano1BoardType)(void* aPtr, uint32_t aVersion, uint32_t aaIndex, char** aaBoardNumber);
/**
 * Callback which runs when the MaxBoards action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkVolkano1EnableActionMaxBoards
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaMaxBoards
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolkano1MaxBoards)(void* aPtr, uint32_t aVersion, uint32_t* aaMaxBoards);
/**
 * Callback which runs when the SoftwareVersion action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkVolkano1EnableActionSoftwareVersion
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaSoftwareVersion
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackVolkano1SoftwareVersion)(void* aPtr, uint32_t aVersion, char** aaSoftwareVersion);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkVolkano1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkVolkano1Create
 */
DllExport void DvProviderLinnCoUkVolkano1Destroy(THandle aProvider);

/**
 * Register a callback for the action Reboot
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkVolkano1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkVolkano1EnableActionReboot(THandle aProvider, CallbackVolkano1Reboot aCallback, void* aPtr);
/**
 * Register a callback for the action BootMode
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkVolkano1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkVolkano1EnableActionBootMode(THandle aProvider, CallbackVolkano1BootMode aCallback, void* aPtr);
/**
 * Register a callback for the action SetBootMode
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkVolkano1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkVolkano1EnableActionSetBootMode(THandle aProvider, CallbackVolkano1SetBootMode aCallback, void* aPtr);
/**
 * Register a callback for the action BspType
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkVolkano1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkVolkano1EnableActionBspType(THandle aProvider, CallbackVolkano1BspType aCallback, void* aPtr);
/**
 * Register a callback for the action UglyName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkVolkano1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkVolkano1EnableActionUglyName(THandle aProvider, CallbackVolkano1UglyName aCallback, void* aPtr);
/**
 * Register a callback for the action MacAddress
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkVolkano1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkVolkano1EnableActionMacAddress(THandle aProvider, CallbackVolkano1MacAddress aCallback, void* aPtr);
/**
 * Register a callback for the action ProductId
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkVolkano1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkVolkano1EnableActionProductId(THandle aProvider, CallbackVolkano1ProductId aCallback, void* aPtr);
/**
 * Register a callback for the action BoardId
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkVolkano1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkVolkano1EnableActionBoardId(THandle aProvider, CallbackVolkano1BoardId aCallback, void* aPtr);
/**
 * Register a callback for the action BoardType
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkVolkano1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkVolkano1EnableActionBoardType(THandle aProvider, CallbackVolkano1BoardType aCallback, void* aPtr);
/**
 * Register a callback for the action MaxBoards
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkVolkano1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkVolkano1EnableActionMaxBoards(THandle aProvider, CallbackVolkano1MaxBoards aCallback, void* aPtr);
/**
 * Register a callback for the action SoftwareVersion
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkVolkano1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkVolkano1EnableActionSoftwareVersion(THandle aProvider, CallbackVolkano1SoftwareVersion aCallback, void* aPtr);


/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKVOLKANO1_C

