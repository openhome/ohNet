#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
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
 * Signature: (JLjava/lang/String;)Lorg/openhome/net/controlpoint/CpAttribute;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_controlpoint_CpDevice_CpDeviceCGetAttribute
  (JNIEnv *aEnv, jclass aClass, jlong aDevice, jstring aKey)
{
	CpDeviceC device = (CpDeviceC) (size_t)aDevice;
	jclass attributeClass;
	jmethodID mid;
	jobject attribute;
	jboolean resultBool;
	jstring valueString;
	int result;
	char* value;
	const char* key = (*aEnv)->GetStringUTFChars(aEnv, aKey, NULL);
	aClass = aClass;

	attributeClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/controlpoint/CpAttribute");
	if (attributeClass == NULL)
	{
		printf("Unable to find class org/openhome/net/controlpoint/CpAttribute\n");
		fflush(stdout);
		return NULL;
	}
	mid = (*aEnv)->GetMethodID(aEnv, attributeClass, "<init>", "(Ljava/lang/String;ZLjava/lang/String;)V");
	if (mid == NULL) {
		printf("Unable to find constructor for class org/openhome/net/controlpoint/CpAttribute\n");
		fflush(stdout);
        return NULL;
	}
	result = CpDeviceCGetAttribute(device, key, &value);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aKey, key);

	if (result == 0)
	{
		value = NULL;
	}
	valueString = (*aEnv)->NewStringUTF(aEnv, value);
	resultBool = (result ? JNI_TRUE : JNI_FALSE);
	attribute = (*aEnv)->NewObject(aEnv, attributeClass, mid, aKey, resultBool, valueString);
	(*aEnv)->DeleteLocalRef(aEnv, attributeClass);
	
	return attribute;
}

#ifdef __cplusplus
}
#endif


