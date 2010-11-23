/**
 * Provider for the linn.co.uk:ProxyManager:1 UPnP service
 */
#ifndef HEADER_DVLINNCOUKPROXYMANAGER1_C
#define HEADER_DVLINNCOUKPROXYMANAGER1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback which runs when the KontrolProductConnected action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProxyManager1EnableActionKontrolProductConnected
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaConnected
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProxyManager1KontrolProductConnected)(void* aPtr, uint32_t aVersion, char** aaConnected);
/**
 * Callback which runs when the SetKontrolProductConnected action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProxyManager1EnableActionSetKontrolProductConnected
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaConnected
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProxyManager1SetKontrolProductConnected)(void* aPtr, uint32_t aVersion, const char* aaConnected);
/**
 * Callback which runs when the KontrolProductComPort action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProxyManager1EnableActionKontrolProductComPort
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaPort
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProxyManager1KontrolProductComPort)(void* aPtr, uint32_t aVersion, uint32_t* aaPort);
/**
 * Callback which runs when the SetKontrolProductComPort action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProxyManager1EnableActionSetKontrolProductComPort
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaConnected
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProxyManager1SetKontrolProductComPort)(void* aPtr, uint32_t aVersion, uint32_t aaConnected);
/**
 * Callback which runs when the DiscPlayerConnected action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProxyManager1EnableActionDiscPlayerConnected
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaConnected
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProxyManager1DiscPlayerConnected)(void* aPtr, uint32_t aVersion, char** aaConnected);
/**
 * Callback which runs when the SetDiscPlayerConnected action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProxyManager1EnableActionSetDiscPlayerConnected
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaConnected
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProxyManager1SetDiscPlayerConnected)(void* aPtr, uint32_t aVersion, const char* aaConnected);
/**
 * Callback which runs when the DiscPlayerComPort action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProxyManager1EnableActionDiscPlayerComPort
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaPort
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProxyManager1DiscPlayerComPort)(void* aPtr, uint32_t aVersion, uint32_t* aaPort);
/**
 * Callback which runs when the SetDiscPlayerComPort action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProxyManager1EnableActionSetDiscPlayerComPort
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaConnected
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProxyManager1SetDiscPlayerComPort)(void* aPtr, uint32_t aVersion, uint32_t aaConnected);
/**
 * Callback which runs when the TestKontrolProductConnection action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProxyManager1EnableActionTestKontrolProductConnection
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaResult
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProxyManager1TestKontrolProductConnection)(void* aPtr, uint32_t aVersion, uint32_t* aaResult);
/**
 * Callback which runs when the TestDiscPlayerConnection action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProxyManager1EnableActionTestDiscPlayerConnection
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaResult
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProxyManager1TestDiscPlayerConnection)(void* aPtr, uint32_t aVersion, uint32_t* aaResult);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkProxyManager1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 */
DllExport void DvProviderLinnCoUkProxyManager1Destroy(THandle aProvider);

/**
 * Register a callback for the action KontrolProductConnected
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProxyManager1EnableActionKontrolProductConnected(THandle aProvider, CallbackProxyManager1KontrolProductConnected aCallback, void* aPtr);
/**
 * Register a callback for the action SetKontrolProductConnected
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProxyManager1EnableActionSetKontrolProductConnected(THandle aProvider, CallbackProxyManager1SetKontrolProductConnected aCallback, void* aPtr);
/**
 * Register a callback for the action KontrolProductComPort
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProxyManager1EnableActionKontrolProductComPort(THandle aProvider, CallbackProxyManager1KontrolProductComPort aCallback, void* aPtr);
/**
 * Register a callback for the action SetKontrolProductComPort
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProxyManager1EnableActionSetKontrolProductComPort(THandle aProvider, CallbackProxyManager1SetKontrolProductComPort aCallback, void* aPtr);
/**
 * Register a callback for the action DiscPlayerConnected
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProxyManager1EnableActionDiscPlayerConnected(THandle aProvider, CallbackProxyManager1DiscPlayerConnected aCallback, void* aPtr);
/**
 * Register a callback for the action SetDiscPlayerConnected
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProxyManager1EnableActionSetDiscPlayerConnected(THandle aProvider, CallbackProxyManager1SetDiscPlayerConnected aCallback, void* aPtr);
/**
 * Register a callback for the action DiscPlayerComPort
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProxyManager1EnableActionDiscPlayerComPort(THandle aProvider, CallbackProxyManager1DiscPlayerComPort aCallback, void* aPtr);
/**
 * Register a callback for the action SetDiscPlayerComPort
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProxyManager1EnableActionSetDiscPlayerComPort(THandle aProvider, CallbackProxyManager1SetDiscPlayerComPort aCallback, void* aPtr);
/**
 * Register a callback for the action TestKontrolProductConnection
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProxyManager1EnableActionTestKontrolProductConnection(THandle aProvider, CallbackProxyManager1TestKontrolProductConnection aCallback, void* aPtr);
/**
 * Register a callback for the action TestDiscPlayerConnection
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProxyManager1EnableActionTestDiscPlayerConnection(THandle aProvider, CallbackProxyManager1TestDiscPlayerConnection aCallback, void* aPtr);

/**
 * Set the value of the KontrolProductConnected property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProxyManager1SetPropertyKontrolProductConnected(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the KontrolProductConnected property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkProxyManager1GetPropertyKontrolProductConnected(THandle aProvider, char** aValue);
/**
 * Set the value of the KontrolProductComPort property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProxyManager1SetPropertyKontrolProductComPort(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the KontrolProductComPort property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkProxyManager1GetPropertyKontrolProductComPort(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the DiscPlayerConnected property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProxyManager1SetPropertyDiscPlayerConnected(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the DiscPlayerConnected property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkProxyManager1GetPropertyDiscPlayerConnected(THandle aProvider, char** aValue);
/**
 * Set the value of the DiscPlayerComPort property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProxyManager1SetPropertyDiscPlayerComPort(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the DiscPlayerComPort property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProxyManager1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkProxyManager1GetPropertyDiscPlayerComPort(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPROXYMANAGER1_C

