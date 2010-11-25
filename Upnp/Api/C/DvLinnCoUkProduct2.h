/**
 * Provider for the linn.co.uk:Product:2 UPnP service
 */
#ifndef HEADER_DVLINNCOUKPRODUCT2_C
#define HEADER_DVLINNCOUKPRODUCT2_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback which runs when the Type action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct2EnableActionType
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaType
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct2Type)(void* aPtr, uint32_t aVersion, char** aaType);
/**
 * Callback which runs when the Model action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct2EnableActionModel
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaModel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct2Model)(void* aPtr, uint32_t aVersion, char** aaModel);
/**
 * Callback which runs when the Name action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct2EnableActionName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct2Name)(void* aPtr, uint32_t aVersion, char** aaName);
/**
 * Callback which runs when the SetName action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct2EnableActionSetName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct2SetName)(void* aPtr, uint32_t aVersion, const char* aaName);
/**
 * Callback which runs when the Room action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct2EnableActionRoom
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaRoom
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct2Room)(void* aPtr, uint32_t aVersion, char** aaRoom);
/**
 * Callback which runs when the SetRoom action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct2EnableActionSetRoom
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaRoom
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct2SetRoom)(void* aPtr, uint32_t aVersion, const char* aaRoom);
/**
 * Callback which runs when the Standby action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct2EnableActionStandby
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaStandby
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct2Standby)(void* aPtr, uint32_t aVersion, uint32_t* aaStandby);
/**
 * Callback which runs when the SetStandby action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct2EnableActionSetStandby
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaStandby
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct2SetStandby)(void* aPtr, uint32_t aVersion, uint32_t aaStandby);
/**
 * Callback which runs when the SourceCount action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct2EnableActionSourceCount
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaSourceCount
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct2SourceCount)(void* aPtr, uint32_t aVersion, uint32_t* aaSourceCount);
/**
 * Callback which runs when the SourceIndex action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct2EnableActionSourceIndex
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaSourceIndex
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct2SourceIndex)(void* aPtr, uint32_t aVersion, uint32_t* aaSourceIndex);
/**
 * Callback which runs when the SetSourceIndex action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct2EnableActionSetSourceIndex
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaSourceIndex
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct2SetSourceIndex)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex);
/**
 * Callback which runs when the SourceType action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct2EnableActionSourceType
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaSourceIndex
 * @param[out] aaSourceType
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct2SourceType)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex, char** aaSourceType);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkProduct2Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 */
DllExport void DvProviderLinnCoUkProduct2Destroy(THandle aProvider);

/**
 * Register a callback for the action Type
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct2EnableActionType(THandle aProvider, CallbackProduct2Type aCallback, void* aPtr);
/**
 * Register a callback for the action Model
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct2EnableActionModel(THandle aProvider, CallbackProduct2Model aCallback, void* aPtr);
/**
 * Register a callback for the action Name
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct2EnableActionName(THandle aProvider, CallbackProduct2Name aCallback, void* aPtr);
/**
 * Register a callback for the action SetName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct2EnableActionSetName(THandle aProvider, CallbackProduct2SetName aCallback, void* aPtr);
/**
 * Register a callback for the action Room
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct2EnableActionRoom(THandle aProvider, CallbackProduct2Room aCallback, void* aPtr);
/**
 * Register a callback for the action SetRoom
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct2EnableActionSetRoom(THandle aProvider, CallbackProduct2SetRoom aCallback, void* aPtr);
/**
 * Register a callback for the action Standby
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct2EnableActionStandby(THandle aProvider, CallbackProduct2Standby aCallback, void* aPtr);
/**
 * Register a callback for the action SetStandby
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct2EnableActionSetStandby(THandle aProvider, CallbackProduct2SetStandby aCallback, void* aPtr);
/**
 * Register a callback for the action SourceCount
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct2EnableActionSourceCount(THandle aProvider, CallbackProduct2SourceCount aCallback, void* aPtr);
/**
 * Register a callback for the action SourceIndex
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct2EnableActionSourceIndex(THandle aProvider, CallbackProduct2SourceIndex aCallback, void* aPtr);
/**
 * Register a callback for the action SetSourceIndex
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct2EnableActionSetSourceIndex(THandle aProvider, CallbackProduct2SetSourceIndex aCallback, void* aPtr);
/**
 * Register a callback for the action SourceType
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct2EnableActionSourceType(THandle aProvider, CallbackProduct2SourceType aCallback, void* aPtr);

/**
 * Set the value of the ProductName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct2SetPropertyProductName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkProduct2GetPropertyProductName(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductRoom property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct2SetPropertyProductRoom(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductRoom property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkProduct2GetPropertyProductRoom(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductStandby property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct2SetPropertyProductStandby(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductStandby property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkProduct2GetPropertyProductStandby(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ProductSourceIndex property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct2SetPropertyProductSourceIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductSourceIndex property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct2Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkProduct2GetPropertyProductSourceIndex(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPRODUCT2_C

