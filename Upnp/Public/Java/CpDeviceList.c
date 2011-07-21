#include <jni.h>
#include <stdlib.h>
#include <malloc.h>
#include "CpDeviceList.h"
#include "C/CpDevice.h"
#include "C/CpDeviceUpnp.h"

typedef struct{
	JavaVM *vm;
	jweak callbackObj;
} jniObjRef;

jniObjRef *ref = NULL;

void deviceAddedCallback(void* aPtr, CpDeviceC aDevice) {

	jniObjRef* ref = (jniObjRef*) aPtr;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	jint ret;

	ret = (*(ref->vm))->AttachCurrentThread(ref->vm, (void **) &env, NULL);
	if (ret < 0)
		printf("Unable to attach thread to JVM.\n");
	
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "deviceAdded", "(J)V");
	if (mid == 0) {
		printf("Method ID not found.\n");
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackObj, mid, aDevice);
	
	(*(ref->vm))->DetachCurrentThread(ref->vm);
	
	//printf("Device added native test.\n");
}

void deviceRemovedCallback(void* aPtr, CpDeviceC aDevice) {

	jniObjRef* ref = (jniObjRef*) aPtr;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	jint ret;

	ret = (*(ref->vm))->AttachCurrentThread(ref->vm, (void **) &env, NULL);
	if (ret < 0)
		printf("Unable to attach thread to JVM.\n");
	
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "deviceRemoved", "(J)V");
	if (mid == 0) {
		printf("Method ID not found.\n");
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackObj, mid, aDevice);
	
	(*(ref->vm))->DetachCurrentThread(ref->vm);
	
	//printf("Device removed native test.\n");
}

JNIEXPORT void JNICALL Java_ohnet_CpDeviceList_CpDeviceListDestroy
  (JNIEnv *env, jobject obj, jlong ptr)
{
	(*env)->DeleteGlobalRef(env, ref->callbackObj);
	free(ref);
	
	CpDeviceListDestroy((HandleCpDeviceList) ptr);
}

JNIEXPORT void JNICALL Java_ohnet_CpDeviceList_CpDeviceListRefresh
  (JNIEnv *env, jobject obj, jlong ptr)
{
	CpDeviceListRefresh((HandleCpDeviceList) ptr);
}

void initialiseReferences(JNIEnv *env, jobject obj)
{
	jint vmCount;
	jint ret;

	/*ret = (*env)->GetJavaVM(env, &(ref->vm));
	if (ret < 0) {
		printf("Unable to get reference to the current Java VM.\n");
	}*/
	ref = (jniObjRef*) malloc(sizeof(jniObjRef));

	ret = JNI_GetCreatedJavaVMs(&(ref->vm), 1, &vmCount);
//	printf("Number of virtual machines found: %d\n", vmCount);
	ref->callbackObj = (*env)->NewWeakGlobalRef(env, obj);
	/*if (callbackObj == NULL) {
		printf("Callback object not stored.\n");
	} else {
		printf("Callback object successfully stored.\n");
	}*/
}

JNIEXPORT jlong JNICALL Java_ohnet_CpDeviceList_CpDeviceListCreateUpnpAll
  (JNIEnv *env, jobject obj)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = &deviceRemovedCallback;
	//jniObjRef* ref = (jniObjRef*) malloc(sizeof(jniObjRef));

	initialiseReferences(env, obj);
									  
	devList = CpDeviceListCreateUpnpAll(callbackAdded, ref, callbackRemoved, ref);
	
	return (jlong) devList;
}

JNIEXPORT jlong JNICALL Java_ohnet_CpDeviceList_CpDeviceListCreateUpnpRoot
  (JNIEnv *env, jobject obj)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = &deviceRemovedCallback;

	initialiseReferences(env, obj);
									  
	devList = CpDeviceListCreateUpnpRoot(callbackAdded, ref, callbackRemoved, ref);
	
	return (jlong) devList;
}

JNIEXPORT jlong JNICALL Java_ohnet_CpDeviceList_CpDeviceListCreateUpnpUuid
  (JNIEnv *env, jobject obj, jstring uuid)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = &deviceRemovedCallback;
	
	const char* nativeUuid = (*env)->GetStringUTFChars(env, uuid, NULL);

	initialiseReferences(env, obj);
	
	devList = CpDeviceListCreateUpnpUuid(nativeUuid, callbackAdded, ref, callbackRemoved, ref);
	
	(*env)->ReleaseStringUTFChars(env, uuid, nativeUuid);
	
	return (jlong) devList;	
}

JNIEXPORT jlong JNICALL Java_ohnet_CpDeviceList_CpDeviceListCreateUpnpDeviceType
  (JNIEnv *env, jobject obj, jstring dom, jstring dev, jint version)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = &deviceRemovedCallback;

	const char* domName = (*env)->GetStringUTFChars(env, dom, NULL);
	const char* devType = (*env)->GetStringUTFChars(env, dev, NULL);

	initialiseReferences(env, obj);
	
	devList = CpDeviceListCreateUpnpDeviceType(domName, devType, version, callbackAdded, ref, callbackRemoved, ref);
	
	(*env)->ReleaseStringUTFChars(env, dom, domName);
	(*env)->ReleaseStringUTFChars(env, dev, devType);
	
	return (jlong) devList;
}

JNIEXPORT jlong JNICALL Java_ohnet_CpDeviceList_CpDeviceListCreateUpnpServiceType
  (JNIEnv *env, jobject obj, jstring dom, jstring service, jint version)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = &deviceRemovedCallback;

	const char* domName = (*env)->GetStringUTFChars(env, dom, NULL);
	const char* serviceType = (*env)->GetStringUTFChars(env, service, NULL);

	initialiseReferences(env, obj);
	
	devList = CpDeviceListCreateUpnpServiceType(domName, serviceType, version, callbackAdded, ref, callbackRemoved, ref);
	
	(*env)->ReleaseStringUTFChars(env, dom, domName);
	(*env)->ReleaseStringUTFChars(env, service, serviceType);
	
	return (jlong) devList;
}
