/**
 * Provider for the zapp.org:TestWidget:1 UPnP service
 */
#ifndef HEADER_DVZAPPORGTESTWIDGET1_C
#define HEADER_DVZAPPORGTESTWIDGET1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback which runs when the SetReadWriteRegister action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestWidget1EnableActionSetReadWriteRegister
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aRegisterIndex
 * @param[in]  aRegisterValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestWidget1SetReadWriteRegister)(void* aPtr, uint32_t aVersion, uint32_t aRegisterIndex, uint32_t aRegisterValue);
/**
 * Callback which runs when the GetWidgetClass action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestWidget1EnableActionGetWidgetClass
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aWidgetClass
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestWidget1GetWidgetClass)(void* aPtr, uint32_t aVersion, uint32_t* aWidgetClass);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderZappOrgTestWidget1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 */
DllExport void DvProviderZappOrgTestWidget1Destroy(THandle aProvider);

/**
 * Register a callback for the action SetReadWriteRegister
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestWidget1EnableActionSetReadWriteRegister(THandle aProvider, CallbackTestWidget1SetReadWriteRegister aCallback, void* aPtr);
/**
 * Register a callback for the action GetWidgetClass
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestWidget1EnableActionGetWidgetClass(THandle aProvider, CallbackTestWidget1GetWidgetClass aCallback, void* aPtr);

/**
 * Set the value of the ReadWriteRegister0 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister0(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ReadWriteRegister0 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister0(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ReadWriteRegister1 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister1(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ReadWriteRegister1 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister1(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ReadWriteRegister2 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister2(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ReadWriteRegister2 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister2(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ReadWriteRegister3 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadWriteRegister3(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ReadWriteRegister3 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadWriteRegister3(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ReadOnlyRegister4 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister4(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ReadOnlyRegister4 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister4(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ReadOnlyRegister5 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister5(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ReadOnlyRegister5 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister5(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ReadOnlyRegister6 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister6(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ReadOnlyRegister6 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister6(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ReadOnlyRegister7 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderZappOrgTestWidget1SetPropertyReadOnlyRegister7(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ReadOnlyRegister7 property
 *
 * @param[in]  aProvider  Handle returned by DvProviderZappOrgTestWidget1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderZappOrgTestWidget1GetPropertyReadOnlyRegister7(THandle aProvider, uint32_t* aValue);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVZAPPORGTESTWIDGET1_C

