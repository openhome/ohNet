#include <jni.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "DvDevice.h"
#include "JniCallbackList.h"
#include "OpenHome/Net/C/DvDevice.h"

#ifdef __cplusplus
extern "C" {
#endif

static void STDCALL CallbackDeviceDisabled(void* aPtr)
{
	JniObjRef *ref = (JniObjRef*) aPtr;
	JavaVM *vm = ref->vm;
	jint ret;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	jint attached;

	attached = (*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_4);
	if (attached < 0)
	{
#ifdef __ANDROID__
		ret = (*vm)->AttachCurrentThreadAsDaemon(vm, &env, NULL);
#else
		ret = (*vm)->AttachCurrentThreadAsDaemon(vm, (void **)&env, NULL);
#endif
		if (ret < 0)
		{
			printf("DvDeviceJNI: Unable to attach thread to JVM.\n");
			fflush(stdout);
			return;
		}
	}
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "deviceDisabled", "()V");
    (*env)->DeleteLocalRef(env, cls);
	if (mid == 0) {
		printf("Method ID deviceDisabled() not found.\n");
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackObj, mid);
	
	(*env)->DeleteGlobalRef(env, ref->callbackObj);
	// leave daemon thread attached to the VM
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
	
	return (jlong) (size_t)device;
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
	ref->callbackObj = (*aEnv)->NewGlobalRef(aEnv, aCompleted);
	
	DvDeviceSetDisabled(device, callback, ref);
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

#ifdef __cplusplus
}
#endif
