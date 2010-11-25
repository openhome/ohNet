/**
 * Device
 *
 * Has a universally unique name and operates on 0..n protocols.
 * Services are added by constructing DvProvider* instances, passing a handle to a
 * DvDeviceC during construction
 */

#ifndef HEADER_DVDEVICEC
#define HEADER_DVDEVICEC

#include <OsTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Opaque handle to a device
 */
typedef THandle DvDeviceC;

typedef void (*ZappCallback)(void* aPtr);

/**
 * Callback which is run before serving a file begins
 *
 * @param[in] aWriterData  Opaque pointer passed to ZappCallbackResourceManager
 * @param[in] aTotalBytes  Size in bytes of the file.  Can be 0 if size is unknown.
 * @param[in] aMimeType    MIME type of the file.  May be NULL if this is unknown.
 */
typedef void (*ZappCallbackWriteResourceBegin)(void* aWriterData, uint32_t aTotalBytes, const char* aMimeType);

/**
 * Callback which runs to serve a chunk of a file
 *
 * Will be called 0..n times after ZappCallbackWriteResourceBegin and before ZappCallbackWriteResourceEnd
 *
 * @param[in] aWriterData  Opaque pointer passed to ZappCallbackResourceManager
 * @param[in] aData        File data to write
 * @param[in] aBytes       Size in bytes of aData
 */
typedef void (*ZappCallbackWriteResource)(void* aWriterData, const uint8_t* aData, uint32_t aBytes);

/**
 * Called when serving of a file is complete
 *
 * Will only be called after a call to ZappCallbackWriteResourceBegin.
 * An error writing the file can be inferred if ZappCallbackWriteResource has not been called or
 * if aTotalBytes was non-zero in the Begin callback and the sum of aBytes values in the Write
 * callbacks does not match aTotalBytes.
 *
 * @param[in] aWriterData  Opaque pointer passed to ZappCallbackResourceManager
 */
typedef void (*ZappCallbackWriteResourceEnd)(void* aWriterData);

/**
 * Callback which runs when a device is asked to serve an unknown file
 *
 * @param[in] aUserData       'aPtr' passed to DvDeviceCreate
 * @param[in] aUriTail        File being requested
 * @param[in] aInterface      Network interface the file request was made on
 * @param[in] aWriterData     Opaque pointer to be passed to all 3 ZappCallbackWriteResource* callbacks
 * @param[in] aWriteBegin     Callback to run at the start of serving the file.
 *                            Should not be run if the file cannot be supplied.
 * @param[in] aWriteResource  Callback to run to write file data.  Must be called at least once to
 *                            successfully serve a file.  Can be called repeatedly to allow the file
 *                            to be written in chunks (avoiding the need to read a large file fully
 *                            into memory).
 * @param[in] aWriteEnd       Callback to be run at the end of serving a file.
 *                            Must be called if aWriteBegin is called.
 */
typedef void (*ZappCallbackResourceManager)(void* aUserData, const char* aUriTail, TIpAddress aInterface, void* aWriterData,
	                                        ZappCallbackWriteResourceBegin aWriteBegin,
                                            ZappCallbackWriteResource aWriteResource,
                                            ZappCallbackWriteResourceEnd aWriteEnd);


/**
 * Constructor.  Creates a device capable of operating on any of the protocols the device
 * stack supports but with no services or attributes as yet
 *
 * @param[in] aUdn    Universally unique identifier.  The caller is responsible for
 *                    calculating/assigning this
 *
 * @return  Handle to the new device
 */
DllExport DvDeviceC DvDeviceCreateNoResources(const char* aUdn);

/**
 * Constructor.  Creates a device capable of serving UI files an of operating on any of the
 * protocols the device stack supports but with no services or attributes as yet
 *
 * @param[in] aUdn    Universally unique identifier.  The caller is responsible for
 *                    calculating/assigning this
 * @param[in] aResourceManager  Callback which will be run when a client requests a file the
 *                              device itself cannot deliver
 * @param[in] aPtr    Data to be passed to the aResourceManager callback
 *
 * @return  Handle to the new device
 */
DllExport DvDeviceC DvDeviceCreate(const char* aUdn, ZappCallbackResourceManager aResourceManager, void* aPtr);

/**
 * Destroy a device.
 * Must be called once for each successful call to DvDeviceCreate[NoResources]
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 */
DllExport void DvDeviceDestroy(DvDeviceC aDevice);

/**
 * Query the (client-specified) unique device name
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  The name passed to the c'tor
 */
DllExport const char* DvDeviceUdn(DvDeviceC aDevice);

/**
 * Query whether a device is enabled
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 *
 * @return  1 if the device is enabled; 0 otherwise
 */
DllExport int32_t DvDeviceEnabled(DvDeviceC aDevice);

/**
 * Set the device ready for external use
 *
 * When this returns, the device will be available for use using any of the protocols
 * the device stack supports.  Services must not be added (DvProvider-derived classes
 * created using this device) and attributes must not be set while a device is enabled.
 * If these need to change in future, the device must first be disabled.
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 */
DllExport void DvDeviceSetEnabled(DvDeviceC aDevice);

/**
 * Disable the device, withdrawing its availability for external use
 *
 * Services can be added and attributes can be set once a device is disabled.  The device
 * will not be available for use again until SetEnabled() is called again.
 * This call is asynchronous so returns before the device is fully disabled.  Wait for the
 * aCompleted callback before adding services or setting attributes.
 *
 * @param[in] aDevice     Handle returned by DvDeviceCreate[NoResources]
 * @param[in] aCompleted  Callback which runs when the device is fully disabled.
 *                        Until this runs, the device should be considered to still be enabled.
 * @param[in] aPtr        Data to be passed to the aCompleted callback
 */
DllExport void DvDeviceSetDisabled(DvDeviceC aDevice, ZappCallback aCompleted, void* aPtr);

/**
 * Query the value of an atrribute
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 * @param[in]  aKey    string of the form protocol_name.protocol_specific_key
 *                     Commonly used keys are published ... (!!!! where?)
 * @param[out] aValue  const pointer to the attribute or NULL if the attribute has not been set.
 */
DllExport void DvDeviceGetAttribute(DvDeviceC aDevice, const char* aKey, const char** aValue);

/**
 * Set the value of an attribute
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 * @param[in] aKey     string of the form protocol_name.protocol_specific_key
 * @param[in] aValue   attribute will be set to a copy of this string
 */
DllExport void DvDeviceSetAttribute(DvDeviceC aDevice, const char* aKey, const char* aValue);

/**
 * Add a block of xml which will be returned as part of the device description
 *
 * Use is limited to UPnP for now.  Xml is returned with device xml inside the <device>
 * tag (at the same level as most attributes)
 *
 * @param[in] aDevice  Handle returned by DvDeviceCreate[NoResources]
 * @param[in] aXml     One or more tag+value blocks
 */
DllExport void DvDeviceSetXmlExtension(DvDeviceC aDevice, const char* aXml);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_DVDEVICEC
