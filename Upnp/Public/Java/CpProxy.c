#include <jni.h>
#include <malloc.h>
#include <stdlib.h>
#include "CpProxy.h"
#include "C/CpProxy.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
	JavaVM *vm;
	jweak callbackChangeObj;
	jweak callbackInitialObj;
} jniObjRef;

//jniObjRef *ref = NULL; // IF not using this MUST free other pointers at some point!

void CallbackChange(void *aPtr)
{

	jniObjRef* ref = (jniObjRef*) aPtr;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	jint ret;
	
	ret = (*(ref->vm))->AttachCurrentThread(ref->vm, (void **) &env, NULL);
	if (ret < 0)
		printf("Unable to attach thread to JVM.\n");
	
	cls = (*env)->GetObjectClass(env, ref->callbackChangeObj);
	mid = (*env)->GetMethodID(env, cls, "notifyChange", "()V");
	if (mid == 0) {
		printf("Method ID notifyChange() not found.\n");
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackChangeObj, mid);
	
	(*(ref->vm))->DetachCurrentThread(ref->vm);
}

void CallbackInitial(void *aPtr)
{
	jniObjRef* ref = (jniObjRef*) aPtr;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	jint ret;

	ret = (*(ref)->vm)->AttachCurrentThread(ref->vm, (void **) &env, NULL);
	if (ret < 0)
		printf("Unable to attach thread to JVM.\n");
	
	cls = (*env)->GetObjectClass(env, ref->callbackInitialObj);
	mid = (*env)->GetMethodID(env, cls, "notifyChange", "()V");
	if (mid == 0) {
		printf("Method ID notifyChange() not found.\n");
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackInitialObj, mid);
	
	(*(ref->vm))->DetachCurrentThread(ref->vm);
}

void InitialiseJvmRef(JNIEnv *env, jniObjRef **ref)
{
	jint vmCount;
	jint ret;

	/*ret = (*env)->GetJavaVM(env, &(ref->vm));
	if (ret < 0) {
		printf("Unable to get reference to the current Java VM.\n");
	}*/
	*ref = (jniObjRef*) malloc(sizeof(jniObjRef));

	ret = JNI_GetCreatedJavaVMs(&((*ref)->vm), 1, &vmCount);
//	printf("Number of virtual machines found: %d\n", vmCount);
	/*if (callbackObj == NULL) {
		printf("Callback object not stored.\n");
	} else {
		printf("Callback object successfully stored.\n");
	}*/
	
}

/*
 * Class:     openhome_net_controlpoint_CpProxy
 * Method:    CpProxyCreate
 * Signature: (Ljava/lang/String;Ljava/lang/String;IJ)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_CpProxy_CpProxyCreate
  (JNIEnv *env, jobject obj, jstring domain, jstring name, jint version, jlong devPtr)
{
	CpDeviceC device = (CpDeviceC) devPtr;
	const char* nativeDomain = (*env)->GetStringUTFChars(env, domain, NULL);
	const char* nativeName = (*env)->GetStringUTFChars(env, name, NULL);
	
	THandle proxy = CpProxyCreate(nativeDomain, nativeName, version, device);
	
	(*env)->ReleaseStringUTFChars(env, domain, nativeName);
	(*env)->ReleaseStringUTFChars(env, name, nativeName);
	
	return (jlong) proxy;
}

/*
 * Class:     openhome_net_controlpoint_CpProxy
 * Method:    CpProxyDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_openhome_net_controlpoint_CpProxy_CpProxyDestroy
  (JNIEnv *env, jobject obj, jlong proxyPtr)
{
	THandle proxy = (THandle) proxyPtr;
	
//	free(ref);
	CpProxyDestroy(proxy);
}

/*
 * Class:     openhome_net_controlpoint_CpProxy
 * Method:    CpProxyService
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_CpProxy_CpProxyService
  (JNIEnv *env, jobject obj, jlong proxyPtr)
{
	THandle proxy = (THandle) proxyPtr;
	
	return (jlong) CpProxyService(proxy);
}

/*
 * Class:     openhome_net_controlpoint_CpProxy
 * Method:    CpProxySubscribe
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_openhome_net_controlpoint_CpProxy_CpProxySubscribe
  (JNIEnv *env, jobject obj, jlong proxyPtr)
{
	THandle proxy = (THandle) proxyPtr;
	
	CpProxySubscribe(proxy);
}

/*
 * Class:     openhome_net_controlpoint_CpProxy
 * Method:    CpProxyUnsubscribe
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_openhome_net_controlpoint_CpProxy_CpProxyUnsubscribe
  (JNIEnv *env, jobject obj, jlong proxyPtr)
{
	THandle proxy = (THandle) proxyPtr;
	
	CpProxyUnsubscribe(proxy);
}

/*
 * Class:     openhome_net_controlpoint_CpProxy
 * Method:    CpProxySetPropertyChanged
 * Signature: (JLohnet/IPropertyChangeListener;)V
 */
JNIEXPORT void JNICALL Java_openhome_net_controlpoint_CpProxy_CpProxySetPropertyChanged
  (JNIEnv *env, jobject obj, jlong proxyPtr, jobject callbackObj)
{
	THandle proxy = (THandle) proxyPtr;
	OhNetCallback callback = &CallbackChange;
	jniObjRef *ref;
	
	InitialiseJvmRef(env, &ref);
	ref->callbackChangeObj = (*env)->NewWeakGlobalRef(env, callbackObj);
	
	CpProxySetPropertyChanged(proxy, callback, ref);

//	printf("SetPropertyChanged->ref: %p\n", ref);
//	printf("SetPropertyChanged->ref->callbackObj: %p\n", ref->callbackChangeObj);
//	fflush(stdout);
}

/*
 * Class:     openhome_net_controlpoint_CpProxy
 * Method:    CpProxySetPropertyInitialEvent
 * Signature: (JLohnet/IPropertyChangeListener;)V
 */
JNIEXPORT void JNICALL Java_openhome_net_controlpoint_CpProxy_CpProxySetPropertyInitialEvent
  (JNIEnv *env, jobject obj, jlong proxyPtr, jobject callbackObj)
{
	THandle proxy = (THandle) proxyPtr;
	OhNetCallback callback = &CallbackInitial;
	jniObjRef *ref;
	
	InitialiseJvmRef(env, &ref);
	ref->callbackInitialObj = (*env)->NewWeakGlobalRef(env, callbackObj);
	
	CpProxySetPropertyChanged(proxy, callback, NULL);
}

/*
 * Class:     openhome_net_controlpoint_CpProxy
 * Method:    CpProxyPropertyReadLock
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_openhome_net_controlpoint_CpProxy_CpProxyPropertyReadLock
  (JNIEnv *env, jobject obj, jlong proxyPtr)
{
	THandle proxy = (THandle) proxyPtr;
	
	CpProxyPropertyReadLock(proxy);
}

/*
 * Class:     openhome_net_controlpoint_CpProxy
 * Method:    CpProxyPropertyReadUnlock
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_openhome_net_controlpoint_CpProxy_CpProxyPropertyReadUnlock
  (JNIEnv *env, jobject obj, jlong proxyPtr)
{
	THandle proxy = (THandle) proxyPtr;
	
	CpProxyPropertyReadUnlock(proxy);
}

/*
 * Class:     openhome_net_controlpoint_CpProxy
 * Method:    CpProxyAddProperty
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_openhome_net_controlpoint_CpProxy_CpProxyAddProperty
  (JNIEnv *env, jobject obj, jlong proxyPtr, jlong propertyPtr)
{
	THandle proxy = (THandle) proxyPtr;
	ServiceProperty property = (ServiceProperty) propertyPtr;
	
	CpProxyAddProperty(proxy, property);
}

#ifdef __cplusplus
}
#endif
