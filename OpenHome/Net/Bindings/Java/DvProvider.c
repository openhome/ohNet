#include <jni.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "DvProvider.h"
#include "JniCallbackList.h"
#include "OpenHome/Net/C/DvProvider.h"

#ifdef __cplusplus
extern "C" {
#endif

static void STDCALL CallbackDvInvocation(void* aPtr, DvInvocationC aInvocation)
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
            printf("Unable to attach thread to JVM.\n");
            return;
        }
    }
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "actionInvoked", "(J)V");
    (*env)->DeleteLocalRef(env, cls);
	if (mid == 0) {
		printf("Method ID actionInvoked() not found.\n");
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackObj, mid, (jlong)(size_t)aInvocation);
	// leave daemon thread attached to the VM
}

/*
 * Class:     org_openhome_net_device_DvProvider
 * Method:    DvProviderCreate
 * Signature: (JLjava/lang/String;Ljava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_device_DvProvider_DvProviderCreate
  (JNIEnv *aEnv, jclass aClass, jlong aDevice, jstring aDomain, jstring aType, jint aVersion)
{
	DvDeviceC device = (DvDeviceC) (size_t)aDevice;
	const char* domain = (*aEnv)->GetStringUTFChars(aEnv, aDomain, NULL);
	const char* type = (*aEnv)->GetStringUTFChars(aEnv, aType, NULL);
	DvProviderC provider;
	aClass = aClass;
	
	provider = DvProviderCreate(device, domain, type, aVersion);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aType, type);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aDomain, domain);
	
	return (jlong) (size_t)provider;
}

/*
 * Class:     org_openhome_net_device_DvProvider
 * Method:    DvProviderDestroy
 * Signature: (J[JI)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_DvProvider_DvProviderDestroy
  (JNIEnv *aEnv, jclass aClass, jlong aProvider, jlongArray aCallbacks, jint aLen)
{
	DvProviderC provider = (DvProviderC) (size_t)aProvider;
	jlong *callbacks;
	int i;
	aEnv = aEnv;
	aClass = aClass;
	
	callbacks = (*aEnv)->GetLongArrayElements(aEnv, aCallbacks, NULL);
	for (i = 0; i < aLen; i++)
	{
		JniObjRef *ref = (JniObjRef*) (size_t)callbacks[i];
		(*aEnv)->DeleteGlobalRef(aEnv, ref->callbackObj);
		free(ref);
	}
	(*aEnv)->ReleaseLongArrayElements(aEnv, aCallbacks, callbacks, 0);
	
	DvProviderDestroy(provider);
}

/*
 * Class:     org_openhome_net_device_DvProvider
 * Method:    DvProviderAddAction
 * Signature: (JJLorg/openhome/net/device/IDvInvocationListener;)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_device_DvProvider_DvProviderAddAction
  (JNIEnv *aEnv, jclass aClass, jlong aProvider, jlong aAction, jobject aCallback)
{
	DvProviderC provider = (DvProviderC) (size_t)aProvider;
	ServiceAction action = (ServiceAction) (size_t)aAction;
	OhNetCallbackDvInvocation callback = &CallbackDvInvocation;
	JniObjRef *ref = (JniObjRef*) malloc(sizeof(JniObjRef));
	int ret;
	aClass = aClass;

	ret = (*aEnv)->GetJavaVM(aEnv, &ref->vm);
	if (ret < 0)
	{
		printf("DvProviderJNI: Unable to get reference to the current Java VM.\n");
		fflush(stdout);
	}
	ref->callbackObj = (*aEnv)->NewGlobalRef(aEnv, aCallback);
	if (ref->callbackObj == NULL)
	{
		printf("DvProviderJNI: Callback object not stored.\n");
		fflush(stdout);
	}

	DvProviderAddAction(provider, action, callback, ref);
	
	return (jlong) (size_t)ref;
}

/*
 * Class:     org_openhome_net_device_DvProvider
 * Method:    DvProviderPropertiesLock
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_DvProvider_DvProviderPropertiesLock
  (JNIEnv *aEnv, jclass aClass, jlong aProvider)
{
	DvProviderC provider = (DvProviderC) (size_t)aProvider;
	aEnv = aEnv;
	aClass = aClass;
	
	DvProviderPropertiesLock(provider);
}

/*
 * Class:     org_openhome_net_device_DvProvider
 * Method:    DvProviderPropertiesUnlock
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_DvProvider_DvProviderPropertiesUnlock
  (JNIEnv *aEnv, jclass aClass, jlong aProvider)
{
	DvProviderC provider = (DvProviderC) (size_t)aProvider;
	aEnv = aEnv;
	aClass = aClass;
	
	DvProviderPropertiesUnlock(provider);
}

/*
 * Class:     org_openhome_net_device_DvProvider
 * Method:    DvProviderAddProperty
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_DvProvider_DvProviderAddProperty
  (JNIEnv *aEnv, jclass aClass, jlong aProvider, jlong aProperty)
{
	DvProviderC provider = (DvProviderC) (size_t)aProvider;
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
	aEnv = aEnv;
	aClass = aClass;
	
	DvProviderAddProperty(provider, property);
}

/*
 * Class:     org_openhome_net_device_DvProvider
 * Method:    DvProviderSetPropertyInt
 * Signature: (JJI)Lorg/openhome/net/device/DvProvider/PropertySetStatus;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_device_DvProvider_DvProviderSetPropertyInt
  (JNIEnv *aEnv, jclass aObject, jlong aProvider, jlong aProperty, jint aValue)
{
	jclass statusClass;
	jmethodID cid;
	jobject status;
	uint32_t changed;
	int result;
	DvProviderC provider = (DvProviderC) (size_t)aProvider;
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
	aEnv = aEnv;
	
	statusClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/device/DvProvider$PropertySetStatus");
	if (statusClass == NULL)
	{
		printf("Unable to find class org/openhome/net/device/DvProvider$PropertySetStatus\n");
		return NULL;
	}
	cid = (*aEnv)->GetMethodID(aEnv, statusClass, "<init>", "(Lorg/openhome/net/device/DvProvider;II)V");
	if (cid == NULL) {
		printf("Unable to find constructor for class org/openhome/net/device/DvProvider$PropertySetStatus\n");
        return NULL;
	}
	result = DvProviderSetPropertyInt(provider, property, aValue, &changed);
	status = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, changed, result);
	(*aEnv)->DeleteLocalRef(aEnv, statusClass);
	
	return status;
}

/*
 * Class:     org_openhome_net_device_DvProvider
 * Method:    DvProviderSetPropertyUint
 * Signature: (JJJ)Lorg/openhome/net/device/DvProvider/PropertySetStatus;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_device_DvProvider_DvProviderSetPropertyUint
  (JNIEnv *aEnv, jobject aObject, jlong aProvider, jlong aProperty, jlong aValue)
{
	jclass statusClass;
	jmethodID cid;
	jobject status;
	uint32_t changed;
	uint32_t value = (uint32_t) aValue;
	int result;
	DvProviderC provider = (DvProviderC) (size_t)aProvider;
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
	aEnv = aEnv;
	
	statusClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/device/DvProvider$PropertySetStatus");
	if (statusClass == NULL)
	{
		printf("Unable to find class org/openhome/net/device/DvProvider$PropertySetStatus\n");
		return NULL;
	}
	cid = (*aEnv)->GetMethodID(aEnv, statusClass, "<init>", "(Lorg/openhome/net/device/DvProvider;II)V");
	if (cid == NULL) {
		printf("Unable to find constructor for class org/openhome/net/device/DvProvider$PropertySetStatus\n");
        return NULL;
	}
	result = DvProviderSetPropertyUint(provider, property, value, &changed);
	status = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, changed, result);
	(*aEnv)->DeleteLocalRef(aEnv, statusClass);
	
	return status;
}

/*
 * Class:     org_openhome_net_device_DvProvider
 * Method:    DvProviderSetPropertyBool
 * Signature: (JJI)Lorg/openhome/net/device/DvProvider/PropertySetStatus;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_device_DvProvider_DvProviderSetPropertyBool
  (JNIEnv *aEnv, jclass aObject, jlong aProvider, jlong aProperty, jint aValue)
{
	jclass statusClass;
	jmethodID cid;
	jobject status;
	uint32_t changed;
	int result;
	DvProviderC provider = (DvProviderC) (size_t)aProvider;
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
	aEnv = aEnv;
	
	statusClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/device/DvProvider$PropertySetStatus");
	if (statusClass == NULL)
	{
		printf("Unable to find class org/openhome/net/device/DvProvider$PropertySetStatus\n");
		return NULL;
	}
	cid = (*aEnv)->GetMethodID(aEnv, statusClass, "<init>", "(Lorg/openhome/net/device/DvProvider;II)V");
	if (cid == NULL) {
		printf("Unable to find constructor for class org/openhome/net/device/DvProvider$PropertySetStatus\n");
        return NULL;
	}
	result = DvProviderSetPropertyBool(provider, property, aValue, &changed);
	status = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, changed, result);
	(*aEnv)->DeleteLocalRef(aEnv, statusClass);
	
	return status;
}

/*
 * Class:     org_openhome_net_device_DvProvider
 * Method:    DvProviderSetPropertyString
 * Signature: (JJLjava/lang/String;)Lorg/openhome/net/device/DvProvider/PropertySetStatus;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_device_DvProvider_DvProviderSetPropertyString
  (JNIEnv *aEnv, jclass aObject, jlong aProvider, jlong aProperty, jstring aValue)
{
	jclass statusClass;
	jmethodID cid;
	jobject status;
	uint32_t changed;
	const char* value = (*aEnv)->GetStringUTFChars(aEnv, aValue, NULL);
	int result;
	DvProviderC provider = (DvProviderC) (size_t)aProvider;
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
	aEnv = aEnv;
	
	statusClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/device/DvProvider$PropertySetStatus");
	if (statusClass == NULL)
	{
		printf("Unable to find class org/openhome/net/device/DvProvider$PropertySetStatus\n");
		return NULL;
	}
	cid = (*aEnv)->GetMethodID(aEnv, statusClass, "<init>", "(Lorg/openhome/net/device/DvProvider;II)V");
	if (cid == NULL) {
		printf("Unable to find constructor for class org/openhome/net/device/DvProvider$PropertySetStatus\n");
        return NULL;
	}
	result = DvProviderSetPropertyString(provider, property, value, &changed);
	status = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, changed, result);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aValue, value);
	(*aEnv)->DeleteLocalRef(aEnv, statusClass);
	
	return status;
}

/*
 * Class:     org_openhome_net_device_DvProvider
 * Method:    DvProviderSetPropertyBinary
 * Signature: (JJ[BI)Lorg/openhome/net/device/DvProvider/PropertySetStatus;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_device_DvProvider_DvProviderSetPropertyBinary
  (JNIEnv *aEnv, jclass aObject, jlong aProvider, jlong aProperty, jbyteArray aData, jint aLen)
{
	jclass statusClass;
	jmethodID cid;
	jobject status;
	uint8_t *data = (uint8_t*)malloc(sizeof(uint8_t)*aLen);
	uint32_t changed;
	int result;
	DvProviderC provider = (DvProviderC) (size_t)aProvider;
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
	aEnv = aEnv;
	
	statusClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/device/DvProvider$PropertySetStatus");
	if (statusClass == NULL)
	{
		printf("Unable to find class org/openhome/net/device/DvProvider$PropertySetStatus\n");
		return NULL;
	}
	cid = (*aEnv)->GetMethodID(aEnv, statusClass, "<init>", "(Lorg/openhome/net/device/DvProvider;II)V");
	if (cid == NULL) {
		printf("Unable to find constructor for class org/openhome/net/device/DvProvider$PropertySetStatus\n");
        return NULL;
	}
	(*aEnv)->GetByteArrayRegion(aEnv, aData, 0, aLen, (jbyte *)data);
	result = DvProviderSetPropertyBinary(provider, property, data, aLen, &changed);
	status = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, changed, result);
	(*aEnv)->DeleteLocalRef(aEnv, statusClass);
	
	return status;
}

#ifdef __cplusplus
}
#endif
