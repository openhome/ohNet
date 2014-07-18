/**
 * Provider for the av.openhome.org:Product:1 UPnP service
 */
#ifndef HEADER_DVAVOPENHOMEORGPRODUCT1_C
#define HEADER_DVAVOPENHOMEORGPRODUCT1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderAvOpenhomeOrgProduct1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Manufacturer action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionManufacturer
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aName
 * @param[out] aInfo
 * @param[out] aUrl
 * @param[out] aImageUri
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1Manufacturer)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aName, char** aInfo, char** aUrl, char** aImageUri);
/**
 * Callback which runs when the Model action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionModel
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aName
 * @param[out] aInfo
 * @param[out] aUrl
 * @param[out] aImageUri
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1Model)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aName, char** aInfo, char** aUrl, char** aImageUri);
/**
 * Callback which runs when the Product action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionProduct
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aRoom
 * @param[out] aName
 * @param[out] aInfo
 * @param[out] aUrl
 * @param[out] aImageUri
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1Product)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aRoom, char** aName, char** aInfo, char** aUrl, char** aImageUri);
/**
 * Callback which runs when the Standby action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionStandby
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1Standby)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);
/**
 * Callback which runs when the SetStandby action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSetStandby
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1SetStandby)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValue);
/**
 * Callback which runs when the SourceCount action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSourceCount
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1SourceCount)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);
/**
 * Callback which runs when the SourceXml action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSourceXml
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1SourceXml)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValue);
/**
 * Callback which runs when the SourceIndex action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSourceIndex
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1SourceIndex)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);
/**
 * Callback which runs when the SetSourceIndex action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSetSourceIndex
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1SetSourceIndex)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aValue);
/**
 * Callback which runs when the SetSourceIndexByName action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSetSourceIndexByName
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1SetSourceIndexByName)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, const char* aValue);
/**
 * Callback which runs when the Source action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSource
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[in]  aIndex
 * @param[out] aSystemName
 * @param[out] aType
 * @param[out] aName
 * @param[out] aVisible
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1Source)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t aIndex, char** aSystemName, char** aType, char** aName, uint32_t* aVisible);
/**
 * Callback which runs when the Attributes action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionAttributes
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1Attributes)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValue);
/**
 * Callback which runs when the SourceXmlChangeCount action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgProduct1EnableActionSourceXmlChangeCount
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackProduct1SourceXmlChangeCount)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderAvOpenhomeOrgProduct1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1Destroy(THandle aProvider);

/**
 * Enable the ManufacturerName property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerName(THandle aProvider);
/**
 * Enable the ManufacturerInfo property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerInfo(THandle aProvider);
/**
 * Enable the ManufacturerUrl property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerUrl(THandle aProvider);
/**
 * Enable the ManufacturerImageUri property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerImageUri(THandle aProvider);
/**
 * Enable the ModelName property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyModelName(THandle aProvider);
/**
 * Enable the ModelInfo property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyModelInfo(THandle aProvider);
/**
 * Enable the ModelUrl property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyModelUrl(THandle aProvider);
/**
 * Enable the ModelImageUri property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyModelImageUri(THandle aProvider);
/**
 * Enable the ProductRoom property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyProductRoom(THandle aProvider);
/**
 * Enable the ProductName property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyProductName(THandle aProvider);
/**
 * Enable the ProductInfo property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyProductInfo(THandle aProvider);
/**
 * Enable the ProductUrl property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyProductUrl(THandle aProvider);
/**
 * Enable the ProductImageUri property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyProductImageUri(THandle aProvider);
/**
 * Enable the Standby property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyStandby(THandle aProvider);
/**
 * Enable the SourceIndex property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertySourceIndex(THandle aProvider);
/**
 * Enable the SourceCount property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertySourceCount(THandle aProvider);
/**
 * Enable the SourceXml property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertySourceXml(THandle aProvider);
/**
 * Enable the Attributes property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnablePropertyAttributes(THandle aProvider);

/**
 * Register a callback for the action Manufacturer
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionManufacturer(THandle aProvider, CallbackProduct1Manufacturer aCallback, void* aPtr);
/**
 * Register a callback for the action Model
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionModel(THandle aProvider, CallbackProduct1Model aCallback, void* aPtr);
/**
 * Register a callback for the action Product
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionProduct(THandle aProvider, CallbackProduct1Product aCallback, void* aPtr);
/**
 * Register a callback for the action Standby
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionStandby(THandle aProvider, CallbackProduct1Standby aCallback, void* aPtr);
/**
 * Register a callback for the action SetStandby
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSetStandby(THandle aProvider, CallbackProduct1SetStandby aCallback, void* aPtr);
/**
 * Register a callback for the action SourceCount
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSourceCount(THandle aProvider, CallbackProduct1SourceCount aCallback, void* aPtr);
/**
 * Register a callback for the action SourceXml
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSourceXml(THandle aProvider, CallbackProduct1SourceXml aCallback, void* aPtr);
/**
 * Register a callback for the action SourceIndex
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSourceIndex(THandle aProvider, CallbackProduct1SourceIndex aCallback, void* aPtr);
/**
 * Register a callback for the action SetSourceIndex
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSetSourceIndex(THandle aProvider, CallbackProduct1SetSourceIndex aCallback, void* aPtr);
/**
 * Register a callback for the action SetSourceIndexByName
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSetSourceIndexByName(THandle aProvider, CallbackProduct1SetSourceIndexByName aCallback, void* aPtr);
/**
 * Register a callback for the action Source
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSource(THandle aProvider, CallbackProduct1Source aCallback, void* aPtr);
/**
 * Register a callback for the action Attributes
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionAttributes(THandle aProvider, CallbackProduct1Attributes aCallback, void* aPtr);
/**
 * Register a callback for the action SourceXmlChangeCount
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1EnableActionSourceXmlChangeCount(THandle aProvider, CallbackProduct1SourceXmlChangeCount aCallback, void* aPtr);

/**
 * Set the value of the ManufacturerName property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyManufacturerName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ManufacturerName property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyManufacturerName(THandle aProvider, char** aValue);
/**
 * Set the value of the ManufacturerInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyManufacturerInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ManufacturerInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyManufacturerInfo(THandle aProvider, char** aValue);
/**
 * Set the value of the ManufacturerUrl property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerUrl has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyManufacturerUrl(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ManufacturerUrl property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerUrl has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyManufacturerUrl(THandle aProvider, char** aValue);
/**
 * Set the value of the ManufacturerImageUri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerImageUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyManufacturerImageUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ManufacturerImageUri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyManufacturerImageUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyManufacturerImageUri(THandle aProvider, char** aValue);
/**
 * Set the value of the ModelName property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyModelName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyModelName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ModelName property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyModelName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyModelName(THandle aProvider, char** aValue);
/**
 * Set the value of the ModelInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyModelInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyModelInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ModelInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyModelInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyModelInfo(THandle aProvider, char** aValue);
/**
 * Set the value of the ModelUrl property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyModelUrl has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyModelUrl(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ModelUrl property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyModelUrl has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyModelUrl(THandle aProvider, char** aValue);
/**
 * Set the value of the ModelImageUri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyModelImageUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyModelImageUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ModelImageUri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyModelImageUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyModelImageUri(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductRoom property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyProductRoom has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyProductRoom(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductRoom property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyProductRoom has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyProductRoom(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductName property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyProductName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyProductName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductName property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyProductName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyProductName(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyProductInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyProductInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyProductInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyProductInfo(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductUrl property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyProductUrl has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyProductUrl(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductUrl property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyProductUrl has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyProductUrl(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductImageUri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyProductImageUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyProductImageUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductImageUri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyProductImageUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyProductImageUri(THandle aProvider, char** aValue);
/**
 * Set the value of the Standby property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyStandby has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyStandby(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Standby property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyStandby has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyStandby(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the SourceIndex property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertySourceIndex has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertySourceIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SourceIndex property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertySourceIndex has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertySourceIndex(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the SourceCount property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertySourceCount has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertySourceCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SourceCount property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertySourceCount has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertySourceCount(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the SourceXml property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertySourceXml has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertySourceXml(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the SourceXml property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertySourceXml has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertySourceXml(THandle aProvider, char** aValue);
/**
 * Set the value of the Attributes property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyAttributes has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgProduct1SetPropertyAttributes(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Attributes property
 *
 * Can only be called if DvProviderAvOpenhomeOrgProduct1EnablePropertyAttributes has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgProduct1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgProduct1GetPropertyAttributes(THandle aProvider, char** aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVAVOPENHOMEORGPRODUCT1_C

