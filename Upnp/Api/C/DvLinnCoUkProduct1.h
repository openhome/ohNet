/**
 * Provider for the linn.co.uk:Product:1 UPnP service
 */
#ifndef HEADER_DVLINNCOUKPRODUCT1_C
#define HEADER_DVLINNCOUKPRODUCT1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback which runs when the Room action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct1EnableActionRoom
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaRoom
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct1Room)(void* aPtr, uint32_t aVersion, char** aaRoom);
/**
 * Callback which runs when the SetRoom action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct1EnableActionSetRoom
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaRoom
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct1SetRoom)(void* aPtr, uint32_t aVersion, const char* aaRoom);
/**
 * Callback which runs when the Standby action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct1EnableActionStandby
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaStandby
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct1Standby)(void* aPtr, uint32_t aVersion, uint32_t* aaStandby);
/**
 * Callback which runs when the SetStandby action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct1EnableActionSetStandby
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaStandby
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct1SetStandby)(void* aPtr, uint32_t aVersion, uint32_t aaStandby);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkProduct1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct1Create
 */
DllExport void DvProviderLinnCoUkProduct1Destroy(THandle aProvider);

/**
 * Register a callback for the action Room
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct1EnableActionRoom(THandle aProvider, CallbackProduct1Room aCallback, void* aPtr);
/**
 * Register a callback for the action SetRoom
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct1EnableActionSetRoom(THandle aProvider, CallbackProduct1SetRoom aCallback, void* aPtr);
/**
 * Register a callback for the action Standby
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct1EnableActionStandby(THandle aProvider, CallbackProduct1Standby aCallback, void* aPtr);
/**
 * Register a callback for the action SetStandby
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct1EnableActionSetStandby(THandle aProvider, CallbackProduct1SetStandby aCallback, void* aPtr);

/**
 * Set the value of the Room property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct1SetPropertyRoom(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Room property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkProduct1GetPropertyRoom(THandle aProvider, char** aValue);
/**
 * Set the value of the Standby property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct1SetPropertyStandby(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Standby property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkProduct1GetPropertyStandby(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPRODUCT1_C

