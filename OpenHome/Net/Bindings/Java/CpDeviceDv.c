#include <jni.h>
#include "CpDeviceDv.h"
#include "OpenHome/Net/C/CpDeviceDv.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_CpDeviceDv
 * Method:    CpDeviceDvCreate
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_CpDeviceDv_CpDeviceDvCreate
  (JNIEnv *aEnv, jclass aClass, jlong aDevice)
{
	DvDeviceC device = (DvDeviceC) (size_t)aDevice;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) (size_t)CpDeviceDvCreate(device);
}

#ifdef __cplusplus
}
#endif
