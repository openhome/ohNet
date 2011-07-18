/**
 * Provider for the av.openhome.org:Sender:1 UPnP service
 */
#ifndef HEADER_DVAVOPENHOMEORGSENDER1_C
#define HEADER_DVAVOPENHOMEORGSENDER1_C

#include <OhNetDefines.h>
#include <OsTypes.h>
#include <C/DvDevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderAvOpenhomeOrgSender1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the PresentationUrl action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgSender1EnableActionPresentationUrl
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackSender1PresentationUrl)(void* aPtr, uint32_t aVersion, char** aValue);
/**
 * Callback which runs when the Metadata action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgSender1EnableActionMetadata
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackSender1Metadata)(void* aPtr, uint32_t aVersion, char** aValue);
/**
 * Callback which runs when the Audio action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgSender1EnableActionAudio
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackSender1Audio)(void* aPtr, uint32_t aVersion, uint32_t* aValue);
/**
 * Callback which runs when the Status action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgSender1EnableActionStatus
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackSender1Status)(void* aPtr, uint32_t aVersion, char** aValue);
/**
 * Callback which runs when the Attributes action is invoked
 *
 * @param[in]  aPtr      Opaque data passed to DvProviderAvOpenhomeOrgSender1EnableActionAttributes
 * @param[in]  aVersion  Version of the service being used.  Will be <= the version advertised by the provider
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (*CallbackSender1Attributes)(void* aPtr, uint32_t aVersion, char** aValue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle DvProviderAvOpenhomeOrgSender1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 */
DllExport void DvProviderAvOpenhomeOrgSender1Destroy(THandle aProvider);

/**
 * Register a callback for the action PresentationUrl
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgSender1EnableActionPresentationUrl(THandle aProvider, CallbackSender1PresentationUrl aCallback, void* aPtr);
/**
 * Register a callback for the action Metadata
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgSender1EnableActionMetadata(THandle aProvider, CallbackSender1Metadata aCallback, void* aPtr);
/**
 * Register a callback for the action Audio
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgSender1EnableActionAudio(THandle aProvider, CallbackSender1Audio aCallback, void* aPtr);
/**
 * Register a callback for the action Status
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgSender1EnableActionStatus(THandle aProvider, CallbackSender1Status aCallback, void* aPtr);
/**
 * Register a callback for the action Attributes
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void DvProviderAvOpenhomeOrgSender1EnableActionAttributes(THandle aProvider, CallbackSender1Attributes aCallback, void* aPtr);

/**
 * Set the value of the PresentationUrl property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgSender1SetPropertyPresentationUrl(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the PresentationUrl property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderAvOpenhomeOrgSender1GetPropertyPresentationUrl(THandle aProvider, char** aValue);
/**
 * Set the value of the Metadata property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgSender1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Metadata property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderAvOpenhomeOrgSender1GetPropertyMetadata(THandle aProvider, char** aValue);
/**
 * Set the value of the Audio property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgSender1SetPropertyAudio(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Audio property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[out] aValue     Value for the property
 */
DllExport void DvProviderAvOpenhomeOrgSender1GetPropertyAudio(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Status property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgSender1SetPropertyStatus(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Status property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderAvOpenhomeOrgSender1GetPropertyStatus(THandle aProvider, char** aValue);
/**
 * Set the value of the Attributes property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t DvProviderAvOpenhomeOrgSender1SetPropertyAttributes(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Attributes property
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void DvProviderAvOpenhomeOrgSender1GetPropertyAttributes(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVAVOPENHOMEORGSENDER1_C

