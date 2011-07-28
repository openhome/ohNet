#include <jni.h>
#include <malloc.h>
#include <stdlib.h>
#include "DvDevice.h"
#include "JniCallbackList.h"
#include "C/DvDevice.h"

#ifdef __cplusplus
extern "C" {
#endif

void CallbackDeviceDisabled(void* aPtr)
{
	JniObjRef *ref = (JniObjRef*) aPtr;
	jint ret;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	
	ret = (*(ref->vm))->AttachCurrentThread(ref->vm, (void **) &env, NULL);
	if (ret < 0)
	{
		printf("Unable to attach thread to JVM.\n");
		return;
	}
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "deviceDisabled", "()V");
	if (mid == 0) {
		printf("Method ID deviceDisabled() not found.\n");
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackObj, mid);
	
	(*(ref->vm))->DetachCurrentThread(ref->vm);
	(*env)->DeleteWeakGlobalRef(env, ref->callbackObj);
	free(ref);
}

/*
 * Class:     org_openhome_net_device_DvDevice
 * Method:    DvDeviceCreate
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_device_DvDevice_DvDeviceCreate
  (JNIEnv *aEnv, jclass aClass, jstring aUdn)
{
	const char* udn = (*aEnv)->GetStringUTFChars(aEnv, aUdn, NULL);
	DvDeviceC device = DvDeviceCreate(udn);
	aClass = aClass;

	(*aEnv)->ReleaseStringUTFChars(aEnv, aUdn, udn);
	
	return (jlong) device;
}

/*
 * Class:     org_openhome_net_device_DvDevice
 * Method:    DvDeviceDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_DvDevice_DvDeviceDestroy
  (JNIEnv *aEnv, jclass aClass, jlong aDevice)
{
	DvDeviceC device = (DvDeviceC) (size_t)aDevice;
	aEnv = aEnv;
	aClass = aClass;
	
	DvDeviceDestroy(device);
}

/*
 * Class:     org_openhome_net_device_DvDevice
 * Method:    DvDeviceUdn
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_openhome_net_device_DvDevice_DvDeviceUdn
  (JNIEnv *aEnv, jclass aClass, jlong aDevice)
{
	DvDeviceC device = (DvDeviceC) (size_t)aDevice;
	const char* udn = DvDeviceUdn(device);
	aClass = aClass;
	
	return (*aEnv)->NewStringUTF(aEnv, udn);
}

/*
 * Class:     org_openhome_net_device_DvDevice
 * Method:    DvDeviceEnabled
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvDevice_DvDeviceEnabled
  (JNIEnv *aEnv, jclass aClass, jlong aDevice)
{
	DvDeviceC device = (DvDeviceC) (size_t)aDevice;
	aEnv = aEnv;
	aClass = aClass;
	
	return DvDeviceEnabled(device);
}

/*
 * Class:     org_openhome_net_device_DvDevice
 * Method:    DvDeviceSetEnabled
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_DvDevice_DvDeviceSetEnabled
  (JNIEnv *aEnv, jclass aClass, jlong aDevice)
{
	DvDeviceC device = (DvDeviceC) (size_t)aDevice;
	aEnv = aEnv;
	aClass = aClass;
	
	DvDeviceSetEnabled(device);
}

/*
 * Class:     org_openhome_net_device_DvDevice
 * Method:    DvDeviceSetDisabled
 * Signature: (JLorg/openhome/net/device/IDvDeviceListener;)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_DvDevice_DvDeviceSetDisabled
  (JNIEnv *aEnv, jclass aClass, jlong aDevice, jobject aCompleted)
{
	DvDeviceC device = (DvDeviceC) (size_t)aDevice;
	OhNetCallback callback = (OhNetCallback) &CallbackDeviceDisabled;
	JniObjRef *ref = (JniObjRef*) malloc(sizeof(JniObjRef));
	int ret;
	aClass = aClass;

	ret = (*aEnv)->GetJavaVM(aEnv, &ref->vm);
	if (ret < 0) {
		printf("Unable to get reference to the current Java VM.\n");
	}
	ref->callbackObj = (*aEnv)->NewWeakGlobalRef(aEnv, aCompleted);
	
	DvDeviceSetDisabled(device, callback, &ref);
}

/*
 * Class:     org_openhome_net_device_DvDevice
 * Method:    DvDeviceGetAttribute
 * Signature: (JLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_openhome_net_device_DvDevice_DvDeviceGetAttribute
  (JNIEnv *aEnv, jclass aClass, jlong aDevice, jstring aKey)
{
	DvDeviceC device = (DvDeviceC) (size_t)aDevice;
	const char* key = (*aEnv)->GetStringUTFChars(aEnv, aKey, NULL);
	const char* value;
	aClass = aClass;
	
	DvDeviceGetAttribute(device, key, &value);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aKey, key);
	
	return (*aEnv)->NewStringUTF(aEnv, value);
}

/*
 * Class:     org_openhome_net_device_DvDevice
 * Method:    DvDeviceSetAttribute
 * Signature: (JLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_DvDevice_DvDeviceSetAttribute
  (JNIEnv *aEnv, jclass aClass, jlong aDevice, jstring aKey, jstring aValue)
{
	DvDeviceC device = (DvDeviceC) (size_t)aDevice;
	const char* key = (*aEnv)->GetStringUTFChars(aEnv, aKey, NULL);
	const char* value = (*aEnv)->GetStringUTFChars(aEnv, aValue, NULL);
	aClass = aClass;
	
	DvDeviceSetAttribute(device, key, value);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aKey, key);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aValue, value);
}

/*
 * Class:     org_openhome_net_device_DvDevice
 * Method:    DvDeviceSetXmlExtension
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_DvDevice_DvDeviceSetXmlExtension
  (JNIEnv *aEnv, jclass aClass, jlong aDevice, jstring aXml)
{
	DvDeviceC device = (DvDeviceC) (size_t)aDevice;
	const char* xml = (*aEnv)->GetStringUTFChars(aEnv, aXml, NULL);
	aClass = aClass;
	
	DvDeviceSetXmlExtension(device, xml);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aXml, xml);
}

#ifdef __cplusplus
}
#endif
