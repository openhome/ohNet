#include <jni.h>
#include <stdlib.h>
#include "CpDevice.h"
#include "OpenHome/Net/C/CpDevice.h"
#include "OpenHome/Net/C/CpDeviceUpnp.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_CpDevice
 * Method:    CpDeviceCUdn
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_openhome_net_controlpoint_CpDevice_CpDeviceCUdn
  (JNIEnv *aEnv, jclass aClass, jlong aDevice)
{
	CpDeviceC device = (CpDeviceC) (size_t)aDevice;
	const char* devUdn = CpDeviceCUdn(device);
	aClass = aClass;
	
	return ((*aEnv)->NewStringUTF(aEnv, devUdn));
}

/*
 * Class:     org_openhome_net_controlpoint_CpDevice
 * Method:    CpDeviceCAddRef
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_controlpoint_CpDevice_CpDeviceCAddRef
  (JNIEnv *aEnv, jclass aClass, jlong aDevice)
{
	CpDeviceC device = (CpDeviceC) (size_t)aDevice;
	aEnv = aEnv;
	aClass = aClass;

	CpDeviceCAddRef(device);
}

/*
 * Class:     org_openhome_net_controlpoint_CpDevice
 * Method:    CpDeviceCRemoveRef
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_controlpoint_CpDevice_CpDeviceCRemoveRef
  (JNIEnv *aEnv, jclass aClass, jlong aDevice)
{
	CpDeviceC device = (CpDeviceC) (size_t)aDevice;
	aEnv = aEnv;
	aClass = aClass;
	
	CpDeviceCRemoveRef(device);
}

/*
 * Class:     org_openhome_net_controlpoint_CpDevice
 * Method:    CpDeviceCGetAttribute
 * Signature: (JLjava/lang/String;[Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_controlpoint_CpDevice_CpDeviceCGetAttribute
  (JNIEnv *aEnv, jclass aClass, jlong aDevice, jstring aKey, jobjectArray aValue)
{
	CpDeviceC device = (CpDeviceC) (size_t)aDevice;
	int result;
	char* value;
	const char* key = (*aEnv)->GetStringUTFChars(aEnv, aKey, NULL);
	aClass = aClass;
	
	result = CpDeviceCGetAttribute(device, key, &value);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aKey, key);
	(*aEnv)->SetObjectArrayElement(aEnv, aValue, 0, (*aEnv)->NewStringUTF(aEnv,value));
	
	return result;
}

#ifdef __cplusplus
}
#endif


