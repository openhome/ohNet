/**
 * Provider for the av.openhome.org:Sender:1 UPnP service
 */
#ifndef HEADER_DVAVOPENHOMEORGSENDER1_C
#define HEADER_DVAVOPENHOMEORGSENDER1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

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
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgSender1EnableActionPresentationUrl
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackSender1PresentationUrl)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValue);
/**
 * Callback which runs when the Metadata action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgSender1EnableActionMetadata
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackSender1Metadata)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValue);
/**
 * Callback which runs when the Audio action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgSender1EnableActionAudio
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackSender1Audio)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);
/**
 * Callback which runs when the Status action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgSender1EnableActionStatus
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackSender1Status)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValue);
/**
 * Callback which runs when the Attributes action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgSender1EnableActionAttributes
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackSender1Attributes)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderAvOpenhomeOrgSender1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1Destroy(THandle aProvider);

/**
 * Enable the PresentationUrl property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1EnablePropertyPresentationUrl(THandle aProvider);
/**
 * Enable the Metadata property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1EnablePropertyMetadata(THandle aProvider);
/**
 * Enable the Audio property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1EnablePropertyAudio(THandle aProvider);
/**
 * Enable the Status property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1EnablePropertyStatus(THandle aProvider);
/**
 * Enable the Attributes property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1EnablePropertyAttributes(THandle aProvider);

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
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1EnableActionPresentationUrl(THandle aProvider, CallbackSender1PresentationUrl aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1EnableActionMetadata(THandle aProvider, CallbackSender1Metadata aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1EnableActionAudio(THandle aProvider, CallbackSender1Audio aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1EnableActionStatus(THandle aProvider, CallbackSender1Status aCallback, void* aPtr);
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
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1EnableActionAttributes(THandle aProvider, CallbackSender1Attributes aCallback, void* aPtr);

/**
 * Set the value of the PresentationUrl property
 *
 * Can only be called if DvProviderAvOpenhomeOrgSender1EnablePropertyPresentationUrl has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgSender1SetPropertyPresentationUrl(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the PresentationUrl property
 *
 * Can only be called if DvProviderAvOpenhomeOrgSender1EnablePropertyPresentationUrl has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1GetPropertyPresentationUrl(THandle aProvider, char** aValue);
/**
 * Set the value of the Metadata property
 *
 * Can only be called if DvProviderAvOpenhomeOrgSender1EnablePropertyMetadata has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgSender1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Metadata property
 *
 * Can only be called if DvProviderAvOpenhomeOrgSender1EnablePropertyMetadata has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1GetPropertyMetadata(THandle aProvider, char** aValue);
/**
 * Set the value of the Audio property
 *
 * Can only be called if DvProviderAvOpenhomeOrgSender1EnablePropertyAudio has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgSender1SetPropertyAudio(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Audio property
 *
 * Can only be called if DvProviderAvOpenhomeOrgSender1EnablePropertyAudio has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1GetPropertyAudio(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the Status property
 *
 * Can only be called if DvProviderAvOpenhomeOrgSender1EnablePropertyStatus has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgSender1SetPropertyStatus(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Status property
 *
 * Can only be called if DvProviderAvOpenhomeOrgSender1EnablePropertyStatus has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1GetPropertyStatus(THandle aProvider, char** aValue);
/**
 * Set the value of the Attributes property
 *
 * Can only be called if DvProviderAvOpenhomeOrgSender1EnablePropertyAttributes has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgSender1SetPropertyAttributes(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Attributes property
 *
 * Can only be called if DvProviderAvOpenhomeOrgSender1EnablePropertyAttributes has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgSender1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgSender1GetPropertyAttributes(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVAVOPENHOMEORGSENDER1_C

