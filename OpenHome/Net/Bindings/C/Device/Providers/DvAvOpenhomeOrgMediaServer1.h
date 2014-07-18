/**
 * Provider for the av.openhome.org:MediaServer:1 UPnP service
 */
#ifndef HEADER_DVAVOPENHOMEORGMEDIASERVER1_C
#define HEADER_DVAVOPENHOMEORGMEDIASERVER1_C

#include <OpenHome/Defines.h>
#include <OpenHome/OsTypes.h>
#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/C/DvInvocation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DvProviderAvOpenhomeOrgMediaServer1
 * @ingroup Providers
 * @{
 */

/**
 * Callback which runs when the Manufacturer action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgMediaServer1EnableActionManufacturer
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
typedef int32_t (STDCALL *CallbackMediaServer1Manufacturer)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aName, char** aInfo, char** aUrl, char** aImageUri);
/**
 * Callback which runs when the Model action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgMediaServer1EnableActionModel
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
typedef int32_t (STDCALL *CallbackMediaServer1Model)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aName, char** aInfo, char** aUrl, char** aImageUri);
/**
 * Callback which runs when the Product action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgMediaServer1EnableActionProduct
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
typedef int32_t (STDCALL *CallbackMediaServer1Product)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aName, char** aInfo, char** aUrl, char** aImageUri);
/**
 * Callback which runs when the Attributes action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgMediaServer1EnableActionAttributes
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackMediaServer1Attributes)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, char** aValue);
/**
 * Callback which runs when the QueryPort action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgMediaServer1EnableActionQueryPort
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackMediaServer1QueryPort)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);
/**
 * Callback which runs when the BrowsePort action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgMediaServer1EnableActionBrowsePort
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackMediaServer1BrowsePort)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);
/**
 * Callback which runs when the UpdateCount action is invoked
 *
 * @param[in]  aPtr           Opaque data passed to DvProviderAvOpenhomeOrgMediaServer1EnableActionUpdateCount
 * @param[in]  aInvocation    Table of function pointers allowing access to the version of the service being used
 *                            and other queries.
 * @param[in] aInvocationPtr  aPtr argument to all functions contained in aInvocation.
 * @param[out] aValue
 *
 * @return  0 if the action succeeded; non-zero if the action failed
 */
typedef int32_t (STDCALL *CallbackMediaServer1UpdateCount)(void* aPtr, IDvInvocationC* aInvocation, void* aInvocationPtr, uint32_t* aValue);

/**
 * Provider constructor
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  Handle to this provider
 */
DllExport THandle STDCALL DvProviderAvOpenhomeOrgMediaServer1Create(DvDeviceC aDevice);

/**
 * Provider destructor
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1Destroy(THandle aProvider);

/**
 * Enable the ManufacturerName property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerName(THandle aProvider);
/**
 * Enable the ManufacturerInfo property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerInfo(THandle aProvider);
/**
 * Enable the ManufacturerUrl property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerUrl(THandle aProvider);
/**
 * Enable the ManufacturerImageUri property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerImageUri(THandle aProvider);
/**
 * Enable the ModelName property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelName(THandle aProvider);
/**
 * Enable the ModelInfo property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelInfo(THandle aProvider);
/**
 * Enable the ModelUrl property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelUrl(THandle aProvider);
/**
 * Enable the ModelImageUri property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelImageUri(THandle aProvider);
/**
 * Enable the ProductName property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductName(THandle aProvider);
/**
 * Enable the ProductInfo property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductInfo(THandle aProvider);
/**
 * Enable the ProductUrl property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductUrl(THandle aProvider);
/**
 * Enable the ProductImageUri property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductImageUri(THandle aProvider);
/**
 * Enable the Attributes property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyAttributes(THandle aProvider);
/**
 * Enable the QueryPort property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyQueryPort(THandle aProvider);
/**
 * Enable the BrowsePort property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyBrowsePort(THandle aProvider);
/**
 * Enable the UpdateCount property.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnablePropertyUpdateCount(THandle aProvider);

/**
 * Register a callback for the action Manufacturer
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnableActionManufacturer(THandle aProvider, CallbackMediaServer1Manufacturer aCallback, void* aPtr);
/**
 * Register a callback for the action Model
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnableActionModel(THandle aProvider, CallbackMediaServer1Model aCallback, void* aPtr);
/**
 * Register a callback for the action Product
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnableActionProduct(THandle aProvider, CallbackMediaServer1Product aCallback, void* aPtr);
/**
 * Register a callback for the action Attributes
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnableActionAttributes(THandle aProvider, CallbackMediaServer1Attributes aCallback, void* aPtr);
/**
 * Register a callback for the action QueryPort
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnableActionQueryPort(THandle aProvider, CallbackMediaServer1QueryPort aCallback, void* aPtr);
/**
 * Register a callback for the action BrowsePort
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnableActionBrowsePort(THandle aProvider, CallbackMediaServer1BrowsePort aCallback, void* aPtr);
/**
 * Register a callback for the action UpdateCount
 *
 * If this is called, the action's availability will be published in the device's service.xml.
 * If this is not called, any attempt to invoke the action on a control point will fail.
 *
 * @param[in] aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in] aCallback  Callback which will be run when the action is invoked
 * @param[in] aPtr       Client-specified data which will be passed to the callback
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1EnableActionUpdateCount(THandle aProvider, CallbackMediaServer1UpdateCount aCallback, void* aPtr);

/**
 * Set the value of the ManufacturerName property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyManufacturerName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ManufacturerName property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyManufacturerName(THandle aProvider, char** aValue);
/**
 * Set the value of the ManufacturerInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyManufacturerInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ManufacturerInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyManufacturerInfo(THandle aProvider, char** aValue);
/**
 * Set the value of the ManufacturerUrl property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerUrl has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyManufacturerUrl(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ManufacturerUrl property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerUrl has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyManufacturerUrl(THandle aProvider, char** aValue);
/**
 * Set the value of the ManufacturerImageUri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerImageUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyManufacturerImageUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ManufacturerImageUri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyManufacturerImageUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyManufacturerImageUri(THandle aProvider, char** aValue);
/**
 * Set the value of the ModelName property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyModelName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ModelName property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyModelName(THandle aProvider, char** aValue);
/**
 * Set the value of the ModelInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyModelInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ModelInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyModelInfo(THandle aProvider, char** aValue);
/**
 * Set the value of the ModelUrl property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelUrl has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyModelUrl(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ModelUrl property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelUrl has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyModelUrl(THandle aProvider, char** aValue);
/**
 * Set the value of the ModelImageUri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelImageUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyModelImageUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ModelImageUri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyModelImageUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyModelImageUri(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductName property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyProductName(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductName property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductName has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyProductName(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyProductInfo(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductInfo property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductInfo has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyProductInfo(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductUrl property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductUrl has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyProductUrl(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductUrl property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductUrl has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyProductUrl(THandle aProvider, char** aValue);
/**
 * Set the value of the ProductImageUri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductImageUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyProductImageUri(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the ProductImageUri property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyProductImageUri has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyProductImageUri(THandle aProvider, char** aValue);
/**
 * Set the value of the Attributes property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyAttributes has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property (will be copied)
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyAttributes(THandle aProvider, const char* aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the Attributes property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyAttributes has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property.  Caller is responsible for freeing this.
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyAttributes(THandle aProvider, char** aValue);
/**
 * Set the value of the QueryPort property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyQueryPort has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyQueryPort(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the QueryPort property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyQueryPort has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyQueryPort(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the BrowsePort property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyBrowsePort has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyBrowsePort(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the BrowsePort property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyBrowsePort has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyBrowsePort(THandle aProvider, uint32_t* aValue);
/**
 * Set the value of the UpdateCount property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyUpdateCount has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[in]  aValue     New value for the property
 * @param[out] aChanged   1 if the value has been updated; 0 if it was the same as the previous value
 *
 * @return  0 if the property was successfully set; non-zero if there was an error (including
 *          an attempt to set a property to a value not in its allowed range/set)
 */
DllExport int32_t STDCALL DvProviderAvOpenhomeOrgMediaServer1SetPropertyUpdateCount(THandle aProvider, uint32_t aValue, uint32_t* aChanged);
/**
 * Get a copy of the value of the UpdateCount property
 *
 * Can only be called if DvProviderAvOpenhomeOrgMediaServer1EnablePropertyUpdateCount has previously been called.
 *
 * @param[in]  aProvider  Handle returned by DvProviderAvOpenhomeOrgMediaServer1Create
 * @param[out] aValue     Value for the property
 */
DllExport void STDCALL DvProviderAvOpenhomeOrgMediaServer1GetPropertyUpdateCount(THandle aProvider, uint32_t* aValue);

/* @} */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVAVOPENHOMEORGMEDIASERVER1_C

