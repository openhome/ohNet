#include <jni.h>
#include <malloc.h>
#include <stdlib.h>
#include "CpProxy.h"
#include "JniCallbackList.h"
#include "C/CpProxy.h"

#ifdef __cplusplus
extern "C" {
#endif

static JniCallbackList *iList = NULL;

static void STDCALL CallbackChange(void* aPtr)
{
	JniObjRef* ref = (JniObjRef*) aPtr;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	jint ret;
	
	ret = (*(ref->vm))->AttachCurrentThread(ref->vm, (void **) &env, NULL);
	if (ret < 0)
		printf("Unable to attach thread to JVM.\n");
	
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "notifyChange", "()V");
	if (mid == 0) {
		printf("Method ID notifyChange() not found.\n");
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackObj, mid);
	
	(*(ref->vm))->DetachCurrentThread(ref->vm);
}

static void STDCALL CallbackInitial(void* aPtr)
{
	JniObjRef* ref = (JniObjRef*) aPtr;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	jint ret;

	ret = (*(ref)->vm)->AttachCurrentThread(ref->vm, (void **) &env, NULL);
	if (ret < 0)
		printf("Unable to attach thread to JVM.\n");
	
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "notifyChange", "()V");
	if (mid == 0) {
		printf("Method ID notifyChange() not found.\n");
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackObj, mid);
	
	(*(ref->vm))->DetachCurrentThread(ref->vm);
}

static void STDCALL InitialiseReferences(JNIEnv *aEnv, jobject aObject, JniObjRef **aRef)
{
	jint ret;
	*aRef = (JniObjRef *)malloc(sizeof(JniObjRef));
	if (iList == NULL)
	{
		iList = JniCallbackListCreate();
	}

	ret = (*aEnv)->GetJavaVM(aEnv, &(*aRef)->vm);
	if (ret < 0) {
		printf("CpProxyJNI: Unable to get reference to the current Java VM.\n");
		fflush(stdout);
	}
	(*aRef)->callbackObj = (*aEnv)->NewWeakGlobalRef(aEnv, aObject);
	if ((*aRef)->callbackObj == NULL) {
		printf("CpProxyJNI: Callback object not stored.\n");
		fflush(stdout);
	}
	JniCallbackListAddElement(&iList, *aRef);
}

/*
 * Class:     openhome_net_controlpoint_CpProxy
 * Method:    CpProxyCreate
 * Signature: (Ljava/lang/String;Ljava/lang/String;IJ)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_CpProxy_CpProxyCreate
  (JNIEnv *env, jobject obj, jstring domain, jstring name, jint version, jlong devPtr)
{
	CpDeviceC device = (CpDeviceC) (size_t)devPtr;
	const char* nativeDomain = (*env)->GetStringUTFChars(env, domain, NULL);
	const char* nativeName = (*env)->GetStringUTFChars(env, name, NULL);
	THandle proxy = CpProxyCreate(nativeDomain, nativeName, version, device);
	obj = obj;
	
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
	THandle proxy = (THandle) (size_t)proxyPtr;
	obj = obj;
	
	JniCallbackListDestroy(env, &iList);
	iList = NULL;
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
	THandle proxy = (THandle) (size_t)proxyPtr;
	env = env;
	obj = obj;
	
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
	THandle proxy = (THandle) (size_t)proxyPtr;
	env = env;
	obj = obj;

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
	THandle proxy = (THandle) (size_t)proxyPtr;
	env = env;
	obj = obj;
	
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
	THandle proxy = (THandle) (size_t)proxyPtr;
	OhNetCallback callback = &CallbackChange;
	JniObjRef *ref;
	obj = obj;
	
	InitialiseReferences(env, callbackObj, &ref);
	
	CpProxySetPropertyChanged(proxy, callback, ref);
}

/*
 * Class:     openhome_net_controlpoint_CpProxy
 * Method:    CpProxySetPropertyInitialEvent
 * Signature: (JLohnet/IPropertyChangeListener;)V
 */
JNIEXPORT void JNICALL Java_openhome_net_controlpoint_CpProxy_CpProxySetPropertyInitialEvent
  (JNIEnv *env, jobject obj, jlong proxyPtr, jobject callbackObj)
{
	THandle proxy = (THandle) (size_t)proxyPtr;
	OhNetCallback callback = (OhNetCallback) &CallbackInitial;
	JniObjRef *ref;
	obj = obj;
	
	InitialiseReferences(env, callbackObj, &ref);
	
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
	THandle proxy = (THandle) (size_t)proxyPtr;
	env = env;
	obj = obj;
	
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
	THandle proxy = (THandle) (size_t)proxyPtr;
	env = env;
	obj = obj;
	
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
	THandle proxy = (THandle) (size_t)proxyPtr;
	ServiceProperty property = (ServiceProperty) (size_t)propertyPtr;
	env = env;
	obj = obj;
	
	CpProxyAddProperty(proxy, property);
}

#ifdef __cplusplus
}
#endif
