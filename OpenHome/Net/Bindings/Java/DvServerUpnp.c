#include <jni.h>
#include "DvServerUpnp.h"
#include "OpenHome/Net/C/DvServerUpnp.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_device_DvServerUpnp
 * Method:    DvServerUpnpCreate
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_device_DvServerUpnp_DvServerUpnpCreate
  (JNIEnv *aEnv, jclass aClass)
{
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) (size_t)DvServerUpnpCreate();
}

/*
 * Class:     org_openhome_net_device_DvServerUpnp
 * Method:    DvServerUpnpDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_DvServerUpnp_DvServerUpnpDestroy
  (JNIEnv *aEnv, jclass aClass, jlong aServer)
{
	THandle server = (THandle) (size_t)aServer;
	aEnv = aEnv;
	aClass = aClass;
	
	DvServerUpnpDestroy(server);
}

/*
 * Class:     org_openhome_net_device_DvServerUpnp
 * Method:    DvServerUpnpAddDevice
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_DvServerUpnp_DvServerUpnpAddDevice
  (JNIEnv *aEnv, jclass aClass, jlong aServer, jlong aDevice)
{
	THandle server = (THandle) (size_t)aServer;
	DvDeviceC device = (DvDeviceC) (size_t)aDevice;
	aEnv = aEnv;
	aClass = aClass;
	
	DvServerUpnpAddDevice(server, device);
}

#ifdef __cplusplus
}
#endif
