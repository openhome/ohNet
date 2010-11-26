/**
 * Provider for the linn.co.uk:Product:3 UPnP service
 */
#ifndef HEADER_DVLINNCOUKPRODUCT3_C
#define HEADER_DVLINNCOUKPRODUCT3_C

#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderLinnCoUkProduct3
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Type action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionType
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaType
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3Type)(void* aPtr, uint32_t aVersion, char** aaType);
/**
 * Callback which runs when the Model action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionModel
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaModel
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3Model)(void* aPtr, uint32_t aVersion, char** aaModel);
/**
 * Callback which runs when the Name action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3Name)(void* aPtr, uint32_t aVersion, char** aaName);
/**
 * Callback which runs when the SetName action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSetName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SetName)(void* aPtr, uint32_t aVersion, const char* aaName);
/**
 * Callback which runs when the Room action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionRoom
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaRoom
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3Room)(void* aPtr, uint32_t aVersion, char** aaRoom);
/**
 * Callback which runs when the SetRoom action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSetRoom
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaRoom
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SetRoom)(void* aPtr, uint32_t aVersion, const char* aaRoom);
/**
 * Callback which runs when the Standby action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionStandby
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaStandby
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3Standby)(void* aPtr, uint32_t aVersion, uint32_t* aaStandby);
/**
 * Callback which runs when the SetStandby action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSetStandby
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaStandby
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SetStandby)(void* aPtr, uint32_t aVersion, uint32_t aaStandby);
/**
 * Callback which runs when the SourceCount action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSourceCount
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaSourceCount
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SourceCount)(void* aPtr, uint32_t aVersion, uint32_t* aaSourceCount);
/**
 * Callback which runs when the SourceXml action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSourceXml
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaSourceXml
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SourceXml)(void* aPtr, uint32_t aVersion, char** aaSourceXml);
/**
 * Callback which runs when the SourceIndex action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSourceIndex
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaSourceIndex
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SourceIndex)(void* aPtr, uint32_t aVersion, uint32_t* aaSourceIndex);
/**
 * Callback which runs when the SetSourceIndex action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSetSourceIndex
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaSourceIndex
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SetSourceIndex)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex);
/**
 * Callback which runs when the SetSourceIndexByName action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSetSourceIndexByName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaSourceName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SetSourceIndexByName)(void* aPtr, uint32_t aVersion, const char* aaSourceName);
/**
 * Callback which runs when the SetStartupSourceIndexByName action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSetStartupSourceIndexByName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaSourceName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SetStartupSourceIndexByName)(void* aPtr, uint32_t aVersion, const char* aaSourceName);
/**
 * Callback which runs when the StartupSourceIndex action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionStartupSourceIndex
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaSourceIndex
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3StartupSourceIndex)(void* aPtr, uint32_t aVersion, uint32_t* aaSourceIndex);
/**
 * Callback which runs when the SetStartupSourceIndex action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSetStartupSourceIndex
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaSourceIndex
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SetStartupSourceIndex)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex);
/**
 * Callback which runs when the StartupSourceEnabled action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionStartupSourceEnabled
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aaStartupSourceEnabled
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3StartupSourceEnabled)(void* aPtr, uint32_t aVersion, uint32_t* aaStartupSourceEnabled);
/**
 * Callback which runs when the SetStartupSourceEnabled action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSetStartupSourceEnabled
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaStartupSourceEnabled
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SetStartupSourceEnabled)(void* aPtr, uint32_t aVersion, uint32_t aaStartupSourceEnabled);
/**
 * Callback which runs when the SourceSystemName action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSourceSystemName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaSourceIndex
 * @param[out] aaSourceName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SourceSystemName)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex, char** aaSourceName);
/**
 * Callback which runs when the SourceName action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSourceName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaSourceIndex
 * @param[out] aaSourceName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SourceName)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex, char** aaSourceName);
/**
 * Callback which runs when the SetSourceName action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSetSourceName
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaSourceIndex
 * @param[in]  aaSourceName
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SetSourceName)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex, const char* aaSourceName);
/**
 * Callback which runs when the SourceType action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSourceType
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaSourceIndex
 * @param[out] aaSourceType
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SourceType)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex, char** aaSourceType);
/**
 * Callback which runs when the SourceVisible action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSourceVisible
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaSourceIndex
 * @param[out] aaSourceVisible
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SourceVisible)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex, uint32_t* aaSourceVisible);
/**
 * Callback which runs when the SetSourceVisible action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderLinnCoUkProduct3EnableActionSetSourceVisible
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[in]  aaSourceIndex
 * @param[in]  aaSourceVisible
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackProduct3SetSourceVisible)(void* aPtr, uint32_t aVersion, uint32_t aaSourceIndex, uint32_t aaSourceVisible);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderLinnCoUkProduct3Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 */
DllExport void DvProviderLinnCoUkProduct3Destroy(THandle aProvider);

/**
 * Register a callback for the action Type
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionType(THandle aProvider, CallbackProduct3Type aCallback, void* aPtr);
/**
 * Register a callback for the action Model
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionModel(THandle aProvider, CallbackProduct3Model aCallback, void* aPtr);
/**
 * Register a callback for the action Name
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionName(THandle aProvider, CallbackProduct3Name aCallback, void* aPtr);
/**
 * Register a callback for the action SetName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSetName(THandle aProvider, CallbackProduct3SetName aCallback, void* aPtr);
/**
 * Register a callback for the action Room
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionRoom(THandle aProvider, CallbackProduct3Room aCallback, void* aPtr);
/**
 * Register a callback for the action SetRoom
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSetRoom(THandle aProvider, CallbackProduct3SetRoom aCallback, void* aPtr);
/**
 * Register a callback for the action Standby
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionStandby(THandle aProvider, CallbackProduct3Standby aCallback, void* aPtr);
/**
 * Register a callback for the action SetStandby
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSetStandby(THandle aProvider, CallbackProduct3SetStandby aCallback, void* aPtr);
/**
 * Register a callback for the action SourceCount
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSourceCount(THandle aProvider, CallbackProduct3SourceCount aCallback, void* aPtr);
/**
 * Register a callback for the action SourceXml
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSourceXml(THandle aProvider, CallbackProduct3SourceXml aCallback, void* aPtr);
/**
 * Register a callback for the action SourceIndex
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSourceIndex(THandle aProvider, CallbackProduct3SourceIndex aCallback, void* aPtr);
/**
 * Register a callback for the action SetSourceIndex
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSetSourceIndex(THandle aProvider, CallbackProduct3SetSourceIndex aCallback, void* aPtr);
/**
 * Register a callback for the action SetSourceIndexByName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSetSourceIndexByName(THandle aProvider, CallbackProduct3SetSourceIndexByName aCallback, void* aPtr);
/**
 * Register a callback for the action SetStartupSourceIndexByName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSetStartupSourceIndexByName(THandle aProvider, CallbackProduct3SetStartupSourceIndexByName aCallback, void* aPtr);
/**
 * Register a callback for the action StartupSourceIndex
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionStartupSourceIndex(THandle aProvider, CallbackProduct3StartupSourceIndex aCallback, void* aPtr);
/**
 * Register a callback for the action SetStartupSourceIndex
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSetStartupSourceIndex(THandle aProvider, CallbackProduct3SetStartupSourceIndex aCallback, void* aPtr);
/**
 * Register a callback for the action StartupSourceEnabled
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionStartupSourceEnabled(THandle aProvider, CallbackProduct3StartupSourceEnabled aCallback, void* aPtr);
/**
 * Register a callback for the action SetStartupSourceEnabled
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSetStartupSourceEnabled(THandle aProvider, CallbackProduct3SetStartupSourceEnabled aCallback, void* aPtr);
/**
 * Register a callback for the action SourceSystemName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSourceSystemName(THandle aProvider, CallbackProduct3SourceSystemName aCallback, void* aPtr);
/**
 * Register a callback for the action SourceName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSourceName(THandle aProvider, CallbackProduct3SourceName aCallback, void* aPtr);
/**
 * Register a callback for the action SetSourceName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSetSourceName(THandle aProvider, CallbackProduct3SetSourceName aCallback, void* aPtr);
/**
 * Register a callback for the action SourceType
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSourceType(THandle aProvider, CallbackProduct3SourceType aCallback, void* aPtr);
/**
 * Register a callback for the action SourceVisible
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSourceVisible(THandle aProvider, CallbackProduct3SourceVisible aCallback, void* aPtr);
/**
 * Register a callback for the action SetSourceVisible
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderLinnCoUkProduct3EnableActionSetSourceVisible(THandle aProvider, CallbackProduct3SetSourceVisible aCallback, void* aPtr);

/**
 * Set the value of the ProductType property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductType(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductType property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductType(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductModel property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductModel(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductModel property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductModel(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductName(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductRoom property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductRoom(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductRoom property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductRoom(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductStandby property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductStandby(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductStandby property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductStandby(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ProductSourceIndex property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductSourceIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductSourceIndex property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductSourceIndex(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ProductSourceCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductSourceCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductSourceCount property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductSourceCount(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ProductSourceXml property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductSourceXml(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductSourceXml property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductSourceXml(THandle aProvider, char** aValue);
/**
 * Set the value of the StartupSourceIndex property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyStartupSourceIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the StartupSourceIndex property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkProduct3GetPropertyStartupSourceIndex(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the StartupSourceEnabled property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyStartupSourceEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the StartupSourceEnabled property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkProduct3GetPropertyStartupSourceEnabled(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ProductAnySourceName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductAnySourceName(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductAnySourceName property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductAnySourceName(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ProductAnySourceVisible property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductAnySourceVisible(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductAnySourceVisible property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductAnySourceVisible(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the ProductAnySourceType property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderLinnCoUkProduct3SetPropertyProductAnySourceType(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductAnySourceType property
 *
 * @param[in]  aProvider  Handle returned by DvProviderLinnCoUkProduct3Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderLinnCoUkProduct3GetPropertyProductAnySourceType(THandle aProvider, uint32_t* aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVLINNCOUKPRODUCT3_C

