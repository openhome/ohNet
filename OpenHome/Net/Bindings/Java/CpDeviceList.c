#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "CpDeviceList.h"
#include "CpDeviceListCallback.h"
#include "JniCallbackList.h"
#include "OpenHome/Defines.h"
#include "OpenHome/Net/C/CpDevice.h"
#include "OpenHome/Net/C/CpDeviceUpnp.h"

#ifdef __cplusplus
extern "C" {
#endif

void STDCALL deviceAddedCallback(void* aPtr, CpDeviceC aDevice) {
	JniObjRef* ref = (JniObjRef*) aPtr;
	JavaVM *vm = ref->vm;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	jint ret;
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
			printf("CpDeviceListJNI: Unable to attach thread to JVM.\n");
			fflush(stdout);
			return;
		}
	}
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "deviceAdded", "(J)V");
    (*env)->DeleteLocalRef(env, cls);
	if (mid == 0) {
		printf("CpDeviceListJNI: Method ID \"deviceAdded()\" not found.\n");
		fflush(stdout);
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackObj, mid, (jlong)(size_t)aDevice);
	// leave daemon thread attached to the VM
}

void STDCALL deviceRemovedCallback(void* aPtr, CpDeviceC aDevice) {

	JniObjRef* ref = (JniObjRef*) aPtr;
	JavaVM *vm = ref->vm;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	jint ret;
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
			printf("CpDeviceListJNI: Unable to attach thread to JVM.\n");
			fflush(stdout);
			return;
		}
	}
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "deviceRemoved", "(J)V");
    (*env)->DeleteLocalRef(env, cls);
	if (mid == 0) {
		printf("CpDeviceListJNI: Method ID \"deviceRemoved()\" not found.\n");
		fflush(stdout);
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackObj, mid, (jlong)(size_t)aDevice);
	// leave daemon thread attached to the VM
}

void InitialiseCpDeviceListReferences(JNIEnv *aEnv, jobject aObject, JniObjRef **aRef)
{
	jint ret;

	*aRef = (JniObjRef*) malloc(sizeof(JniObjRef));
	ret = (*aEnv)->GetJavaVM(aEnv, &(*aRef)->vm);
	if (ret < 0) {
		printf("CpDeviceListJNI: Unable to get reference to the current Java VM.\n");
		fflush(stdout);
	}
	(*aRef)->callbackObj = (*aEnv)->NewGlobalRef(aEnv, aObject);
	if ((*aRef)->callbackObj == NULL) {
		printf("CpDeviceListJNI: Callback object not stored.\n");
		fflush(stdout);
	}
}

/*
 * Class:     org_openhome_net_controlpoint_CpDeviceList
 * Method:    CpDeviceListDestroy
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_controlpoint_CpDeviceList_CpDeviceListDestroy
  (JNIEnv *aEnv, jclass aClass, jlong aList, jlong aCallback)
{
	HandleCpDeviceList list = (HandleCpDeviceList) (size_t)aList;
	JniObjRef *ref = (JniObjRef*) (size_t)aCallback;
	aClass = aClass;

	(*aEnv)->DeleteGlobalRef(aEnv, ref->callbackObj);
	free(ref);
	CpDeviceListDestroy(list);
}

/*
 * Class:     org_openhome_net_controlpoint_CpDeviceList
 * Method:    CpDeviceListRefresh
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_controlpoint_CpDeviceList_CpDeviceListRefresh
  (JNIEnv *aEnv, jclass aClass, jlong aList)
{
	HandleCpDeviceList list = (HandleCpDeviceList) (size_t)aList;
	aEnv = aEnv;
	aClass = aClass;

	CpDeviceListRefresh(list);
}

#ifdef __cplusplus
}
#endif
