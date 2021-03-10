#include <jni.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <OpenHome/Os.h>
#include "DvDeviceStandard.h"
#include "JniCallbackList.h"
#include "OpenHome/Net/C/DvDevice.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t STDCALL CallbackResourceManager(void* aUserData, const char* aUriTail, TIpAddress aInterface, THandle aLanguageList, void* aWriterData,
	                         OhNetCallbackWriteResourceBegin aWriteBegin,
                             OhNetCallbackWriteResource aWriteResource,
                             OhNetCallbackWriteResourceEnd aWriteEnd)
{
	JniObjRef* ref = (JniObjRef*) aUserData;
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
			printf("DvDeviceStandardJNI: Unable to attach thread to JVM.\n");
			fflush(stdout);
			return 0;
		}
	}
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "writeResource", "(JLjava/lang/String;IJJJJJ)V");
    (*env)->DeleteLocalRef(env, cls);
	if (mid == 0) {
		printf("Method ID writeResource() not found.\n");
		fflush(stdout);
		return 0;
	}

	if (aInterface.iFamily == kFamilyV6) {
		printf("Attempted to WriteResource to IPv6 Address\n");
		fflush(stdout);
		return 0;
	}

	(*env)->CallVoidMethod(env, ref->callbackObj, mid,
			(jlong) (size_t)aUserData,
			(jstring) (*env)->NewStringUTF(env, aUriTail),
#ifdef DEFINE_LITTLE_ENDIAN
            (jint) SwapEndian32(aInterface.iV4),
#elif defined DEFINE_BIG_ENDIAN
			(jint) aInterface.iV4,
#else
# error Endianness not defined
#endif
            (jlong) (size_t)aLanguageList,
			(jlong) (size_t)aWriterData,
			(jlong) (size_t)aWriteBegin,
			(jlong) (size_t)aWriteResource,
			(jlong) (size_t)aWriteEnd);
	
	// leave daemon thread attached to the VM
    return 0;
}

/*
 * Class:     org_openhome_net_device_DvDeviceStandard
 * Method:    DvDeviceStandardCreateNoResources
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_device_DvDeviceStandard_DvDeviceStandardCreateNoResources
  (JNIEnv *aEnv, jclass aClass, jstring aUdn)
{
	const char* udn = (*aEnv)->GetStringUTFChars(aEnv, aUdn, NULL);
	DvDeviceC device;
	aClass = aClass;
	
	device = DvDeviceStandardCreateNoResources(udn);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aUdn, udn);
	
	return (jlong) (size_t)device;
}

/*
 * Class:     org_openhome_net_device_DvDeviceStandard
 * Method:    DvDeviceStandardCreate
 * Signature: (Ljava/lang/String;)Lorg/openhome/net/device/DvDeviceStandard/DvDeviceStandardInitialised;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_device_DvDeviceStandard_DvDeviceStandardCreate
  (JNIEnv *aEnv, jobject aObject, jstring aUdn)
{
	const char* udn = (*aEnv)->GetStringUTFChars(aEnv, aUdn, NULL);
	OhNetCallbackResourceManager callback = (OhNetCallbackResourceManager) &CallbackResourceManager;
	JniObjRef *ref = (JniObjRef*) malloc(sizeof(JniObjRef));
	DvDeviceC device;
	int ret;
	jclass statusClass;
	jmethodID cid;
	jobject devInit;

	ret = (*aEnv)->GetJavaVM(aEnv, &ref->vm);
	if (ret < 0) {
		printf("Unable to get reference to the current Java VM.\n");
	}
	ref->callbackObj = (*aEnv)->NewGlobalRef(aEnv, aObject);
	
	statusClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/device/DvDeviceStandard$DvDeviceStandardInitialised");
	if (statusClass == NULL)
	{
		printf("Unable to find class org/openhome/net/device/DvDeviceStandard$DvDeviceStandardInitialised\n");
		return NULL;
	}
	cid = (*aEnv)->GetMethodID(aEnv, statusClass, "<init>", "(Lorg/openhome/net/device/DvDeviceStandard;JJ)V");
	if (cid == NULL)
	{
		printf("Unable to find constructor for class org/openhome/net/device/DvDeviceStandard$DvDeviceStandardInitialised\n");
        return NULL;
	}
	
	device = DvDeviceStandardCreate(udn, callback, ref);
	devInit = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, (jlong)(size_t)device, (jlong)(size_t)ref);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aUdn, udn);
	
	return devInit;
}

/*
 * Class:     org_openhome_net_device_DvDeviceStandard
 * Method:    DvDeviceDestroy
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_DvDeviceStandard_DvDeviceDestroy
  (JNIEnv *aEnv, jclass aClass, jlong aDevice, jlong aCallback)
{
	JniObjRef *ref = (JniObjRef*) (size_t)aCallback;
	DvDeviceC device = (DvDeviceC) (size_t)aDevice;
	aEnv = aEnv;
	aClass = aClass;

	if (ref != NULL)
	{
		(*aEnv)->DeleteGlobalRef(aEnv, ref->callbackObj);
		free(ref);
	}
	DvDeviceDestroy(device);
}

/*
 * Class:     org_openhome_net_device_DvDeviceStandard
 * Method:    DvResourceWriterLanguageCount
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvDeviceStandard_DvResourceWriterLanguageCount
  (JNIEnv *aEnv, jclass aClass, jlong aLanguageList)
{
	THandle languageList = (THandle) (void*)(size_t)aLanguageList;
	uint32_t count = DvResourceWriterLanguageCount(languageList);
	aEnv = aEnv;
	aClass = aClass;
	
	return (jint) count;
}

/*
 * Class:     org_openhome_net_device_DvDeviceStandard
 * Method:    DvResourceWriterLanguage
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_openhome_net_device_DvDeviceStandard_DvResourceWriterLanguage
  (JNIEnv *aEnv, jclass aClass, jlong aLanguageList, jint aIndex)
{
	THandle languageList = (THandle) (void*)(size_t)aLanguageList;
	const char* language = DvResourceWriterLanguage(languageList, aIndex);
	aEnv = aEnv;
	aClass = aClass;
	
	return (*aEnv)->NewStringUTF(aEnv, language);
}

#ifdef __cplusplus
}
#endif
