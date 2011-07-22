#include <jni.h>
#include <stdlib.h>
#include "C/CpDevice.h"
#include "C/CpDeviceUpnp.h"
#include "CpDevice.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     openhome_net_controlpoint_CpDevice
 * Method:    CpDeviceCUdn
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_openhome_net_controlpoint_CpDevice_CpDeviceCUdn
  (JNIEnv *env, jobject obj, jlong devPtr)
{
	CpDeviceC device = (CpDeviceC) devPtr;
	const char* devUdn = CpDeviceCUdn(device);

	return ((*env)->NewStringUTF(env, devUdn));
}

/*
 * Class:     openhome_net_controlpoint_CpDevice
 * Method:    CpDeviceCAddRef
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_openhome_net_controlpoint_CpDevice_CpDeviceCAddRef
  (JNIEnv *env, jobject obj, jlong devPtr)
{
	CpDeviceC device = (CpDeviceC) devPtr;

	CpDeviceCAddRef(device);
}

/*
 * Class:     openhome_net_controlpoint_CpDevice
 * Method:    CpDeviceCRemoveRef
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_openhome_net_controlpoint_CpDevice_CpDeviceCRemoveRef
  (JNIEnv *env, jobject obj, jlong devPtr)
{
	CpDeviceC device = (CpDeviceC) devPtr;
	
	CpDeviceCRemoveRef(device);
}

/*
 * Class:     openhome_net_controlpoint_CpDevice
 * Method:    CpDeviceCGetAttribute
 * Signature: (JLjava/lang/String;[Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_openhome_net_controlpoint_CpDevice_CpDeviceCGetAttribute
  (JNIEnv *env, jobject obj, jlong devPtr, jstring key, jobjectArray value)
{
	CpDeviceC device = (CpDeviceC) devPtr;
	int result;
	char* nativeValue;

	const char* nativeKey = (*env)->GetStringUTFChars(env, key, NULL);
	
	result = CpDeviceCGetAttribute(device, nativeKey, &nativeValue);
	
	(*env)->ReleaseStringUTFChars(env, key, nativeKey);
	(*env)->SetObjectArrayElement(env, value, 0, (*env)->NewStringUTF(env, nativeValue));
	
	return result;
}

#ifdef __cplusplus
}
#endif


