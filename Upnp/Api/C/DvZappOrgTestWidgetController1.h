/**
 * Provider for the zapp.org:TestWidgetController:1 UPnP service
 */
#ifndef HEADER_DVZAPPORGTESTWIDGETCONTROLLER1_C
#define HEADER_DVZAPPORGTESTWIDGETCONTROLLER1_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback which runs when the CreateWidget action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestWidgetController1EnableActionCreateWidget
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aWidgetUdn
 * @param[in]  aWidgetClass
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestWidgetController1CreateWidget)(void* aPtr, uint32_t aVersion, const char* aWidgetUdn, uint32_t aWidgetClass);
/**
 * Callback which runs when the RemoveWidget action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestWidgetController1EnableActionRemoveWidget
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aWidgetUdn
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestWidgetController1RemoveWidget)(void* aPtr, uint32_t aVersion, const char* aWidgetUdn);
/**
 * Callback which runs when the SetWidgetRegister action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestWidgetController1EnableActionSetWidgetRegister
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aWidgetUdn
 * @param[in]  aRegisterIndex
 * @param[in]  aRegisterValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestWidgetController1SetWidgetRegister)(void* aPtr, uint32_t aVersion, const char* aWidgetUdn, uint32_t aRegisterIndex, uint32_t aRegisterValue);
/**
 * Callback which runs when the GetWidgetRegister action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderZappOrgTestWidgetController1EnableActionGetWidgetRegister
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aWidgetUdn
 * @param[in]  aRegisterIndex
 * @param[out] aRegisterValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackTestWidgetController1GetWidgetRegister)(void* aPtr, uint32_t aVersion, const char* aWidgetUdn, uint32_t aRegisterIndex, uint32_t* aRegisterValue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderZappOrgTestWidgetController1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestWidgetController1Create
 */
DllExport void DvProviderZappOrgTestWidgetController1Destroy(THandle aProvider);

/**
 * Register a callback for the action CreateWidget
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestWidgetController1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestWidgetController1EnableActionCreateWidget(THandle aProvider, CallbackTestWidgetController1CreateWidget aCallback, void* aPtr);
/**
 * Register a callback for the action RemoveWidget
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestWidgetController1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestWidgetController1EnableActionRemoveWidget(THandle aProvider, CallbackTestWidgetController1RemoveWidget aCallback, void* aPtr);
/**
 * Register a callback for the action SetWidgetRegister
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestWidgetController1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestWidgetController1EnableActionSetWidgetRegister(THandle aProvider, CallbackTestWidgetController1SetWidgetRegister aCallback, void* aPtr);
/**
 * Register a callback for the action GetWidgetRegister
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderZappOrgTestWidgetController1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderZappOrgTestWidgetController1EnableActionGetWidgetRegister(THandle aProvider, CallbackTestWidgetController1GetWidgetRegister aCallback, void* aPtr);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVZAPPORGTESTWIDGETCONTROLLER1_C

