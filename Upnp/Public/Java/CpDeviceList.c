#include <jni.h>
#include <stdlib.h>
#include <malloc.h>
#include "CpDeviceList.h"
#include "JniCallbackList.h"
#include "OhNetDefines.h"
#include "C/CpDevice.h"
#include "C/CpDeviceUpnp.h"

static JniCallbackList *iList = NULL;

static void STDCALL deviceAddedCallback(void* aPtr, CpDeviceC aDevice) {

	JniObjRef* ref = (JniObjRef*) aPtr;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	jint ret;

	ret = (*(ref->vm))->AttachCurrentThread(ref->vm, (void **) &env, NULL);
	if (ret < 0)
		printf("CpDeviceListJNI: Unable to attach thread to JVM.\n");
	
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "deviceAdded", "(J)V");
	if (mid == 0) {
		printf("CpDeviceListJNI: Method ID \"deviceAdded()\" not found.\n");
		fflush(stdout);
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackObj, mid, aDevice);
	(*(ref->vm))->DetachCurrentThread(ref->vm);
}

static void STDCALL deviceRemovedCallback(void* aPtr, CpDeviceC aDevice) {

	JniObjRef* ref = (JniObjRef*) aPtr;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	jint ret;

	ret = (*(ref->vm))->AttachCurrentThread(ref->vm, (void **) &env, NULL);
	if (ret < 0)
		printf("CpDeviceListJNI: Unable to attach thread to JVM.\n");
	
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "deviceRemoved", "(J)V");
	if (mid == 0) {
		printf("CpDeviceListJNI: Method ID \"deviceRemoved()\" not found.\n");
		fflush(stdout);
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackObj, mid, aDevice);
	(*(ref->vm))->DetachCurrentThread(ref->vm);
}

static void InitialiseReferences(JNIEnv *aEnv, jobject aObject, JniObjRef **aRef)
{
	jint ret;

	if (!iList)
	{
		iList = JniCallbackListCreate();
	}
	*aRef = (JniObjRef*) malloc(sizeof(JniObjRef));
	ret = (*aEnv)->GetJavaVM(aEnv, &(*aRef)->vm);
	if (ret < 0) {
		printf("CpDeviceListJNI: Unable to get reference to the current Java VM.\n");
		fflush(stdout);
	}
	(*aRef)->callbackObj = (*aEnv)->NewWeakGlobalRef(aEnv, aObject);
	if ((*aRef)->callbackObj == NULL) {
		printf("CpDeviceListJNI: Callback object not stored.\n");
		fflush(stdout);
	}
	JniCallbackListAddElement(&iList, *aRef);
}

JNIEXPORT void JNICALL Java_ohnet_CpDeviceList_CpDeviceListDestroy
  (JNIEnv *env, jobject obj, jlong ptr)
{
	HandleCpDeviceList list = (HandleCpDeviceList) (size_t)ptr;
	obj = obj;
	
	JniCallbackListDestroy(env, &iList);
	iList = NULL;
	CpDeviceListDestroy(list);
}

JNIEXPORT void JNICALL Java_ohnet_CpDeviceList_CpDeviceListRefresh
  (JNIEnv *env, jobject obj, jlong ptr)
{
	HandleCpDeviceList list = (HandleCpDeviceList) (size_t)ptr;
	env = env;
	obj = obj;
	
	CpDeviceListRefresh(list);
}

JNIEXPORT jlong JNICALL Java_ohnet_CpDeviceList_CpDeviceListCreateUpnpAll
  (JNIEnv *env, jobject obj)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = (OhNetCallbackDevice) &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = (OhNetCallbackDevice) &deviceRemovedCallback;
	JniObjRef* ref = (JniObjRef*) malloc(sizeof(JniObjRef));

	InitialiseReferences(env, obj, &ref);
									  
	devList = CpDeviceListCreateUpnpAll(callbackAdded, ref, callbackRemoved, ref);
	
	return (jlong) devList;
}

JNIEXPORT jlong JNICALL Java_ohnet_CpDeviceList_CpDeviceListCreateUpnpRoot
  (JNIEnv *env, jobject obj)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = (OhNetCallbackDevice) &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = (OhNetCallbackDevice) &deviceRemovedCallback;
	JniObjRef* ref = (JniObjRef*) malloc(sizeof(JniObjRef));

	InitialiseReferences(env, obj, &ref);
									  
	devList = CpDeviceListCreateUpnpRoot(callbackAdded, ref, callbackRemoved, ref);
	
	return (jlong) devList;
}

JNIEXPORT jlong JNICALL Java_ohnet_CpDeviceList_CpDeviceListCreateUpnpUuid
  (JNIEnv *env, jobject obj, jstring uuid)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = (OhNetCallbackDevice) &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = (OhNetCallbackDevice) &deviceRemovedCallback;
	JniObjRef* ref = (JniObjRef*) malloc(sizeof(JniObjRef));
	const char* nativeUuid = (*env)->GetStringUTFChars(env, uuid, NULL);

	InitialiseReferences(env, obj, &ref);
	
	devList = CpDeviceListCreateUpnpUuid(nativeUuid, callbackAdded, ref, callbackRemoved, ref);
	
	(*env)->ReleaseStringUTFChars(env, uuid, nativeUuid);
	
	return (jlong) devList;	
}

JNIEXPORT jlong JNICALL Java_ohnet_CpDeviceList_CpDeviceListCreateUpnpDeviceType
  (JNIEnv *env, jobject obj, jstring dom, jstring dev, jint version)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = (OhNetCallbackDevice) &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = (OhNetCallbackDevice) &deviceRemovedCallback;
	JniObjRef* ref = (JniObjRef*) malloc(sizeof(JniObjRef));
	const char* domName = (*env)->GetStringUTFChars(env, dom, NULL);
	const char* devType = (*env)->GetStringUTFChars(env, dev, NULL);

	InitialiseReferences(env, obj, &ref);
	
	devList = CpDeviceListCreateUpnpDeviceType(domName, devType, version, callbackAdded, ref, callbackRemoved, ref);
	
	(*env)->ReleaseStringUTFChars(env, dom, domName);
	(*env)->ReleaseStringUTFChars(env, dev, devType);
	
	return (jlong) devList;
}

JNIEXPORT jlong JNICALL Java_ohnet_CpDeviceList_CpDeviceListCreateUpnpServiceType
  (JNIEnv *env, jobject obj, jstring dom, jstring service, jint version)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = (OhNetCallbackDevice) &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = (OhNetCallbackDevice) &deviceRemovedCallback;
	JniObjRef* ref = (JniObjRef*) malloc(sizeof(JniObjRef));
	const char* domName = (*env)->GetStringUTFChars(env, dom, NULL);
	const char* serviceType = (*env)->GetStringUTFChars(env, service, NULL);

	InitialiseReferences(env, obj, &ref);
	
	devList = CpDeviceListCreateUpnpServiceType(domName, serviceType, version, callbackAdded, ref, callbackRemoved, ref);
	
	(*env)->ReleaseStringUTFChars(env, dom, domName);
	(*env)->ReleaseStringUTFChars(env, service, serviceType);
	
	return (jlong) devList;
}
