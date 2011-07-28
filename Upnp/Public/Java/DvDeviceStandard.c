#include <jni.h>
#include <malloc.h>
#include <stdlib.h>
#include "DvDeviceStandard.h"
#include "JniCallbackList.h"
#include "C/DvDevice.h"

#ifdef __cplusplus
extern "C" {
#endif

static JniCallbackList *iList = NULL;

void CallbackResourceManager(void* aUserData, const char* aUriTail, TIpAddress aInterface, THandle aLanguageList, void* aWriterData,
	                         OhNetCallbackWriteResourceBegin aWriteBegin,
                             OhNetCallbackWriteResource aWriteResource,
                             OhNetCallbackWriteResourceEnd aWriteEnd)
{
	JniObjRef* ref = (JniObjRef*) aUserData;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	jint ret;
	
	ret = (*(ref->vm))->AttachCurrentThread(ref->vm, (void **) &env, NULL);
	if (ret < 0)
		printf("Unable to attach thread to JVM.\n");
	
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "writeResource", "(Jjava/lang/StringIJJJJJ)V");
	if (mid == 0) {
		printf("Method ID writeResource() not found.\n");
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackObj, mid,
			(jlong) aUserData,
			(*env)->NewStringUTF(env, aUriTail),
			(jint) aInterface,
			(jlong) aLanguageList,
			(jlong) aWriterData,
			(jlong) aWriteBegin,
			(jlong) aWriteResource,
			(jlong) aWriteEnd);
	
	(*(ref->vm))->DetachCurrentThread(ref->vm);
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
	
	return (jlong) device;
}

/*
 * Class:     org_openhome_net_device_DvDeviceStandard
 * Method:    DvDeviceStandardCreate
 * Signature: (Ljava/lang/String;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_device_DvDeviceStandard_DvDeviceStandardCreate
  (JNIEnv *aEnv, jobject aObject, jstring aUdn)
{
	const char* udn = (*aEnv)->GetStringUTFChars(aEnv, aUdn, NULL);
	OhNetCallbackResourceManager callback = (OhNetCallbackResourceManager) &CallbackResourceManager;
	JniObjRef *ref = (JniObjRef*) malloc(sizeof(JniObjRef));
	int ret;

	if (!iList)
	{
		iList = JniCallbackListCreate();
	}
	ret = (*aEnv)->GetJavaVM(aEnv, &ref->vm);
	if (ret < 0) {
		printf("Unable to get reference to the current Java VM.\n");
	}
	ref->callbackObj = (*aEnv)->NewWeakGlobalRef(aEnv, aObject);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aUdn, udn);
	JniCallbackListAddElement(&iList, ref);
	
	return (jlong) DvDeviceStandardCreate(udn, callback, &ref);
}

/*
 * Class:     org_openhome_net_device_DvDeviceStandard
 * Method:    DvDeviceDestroy
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_DvDeviceStandard_DvDeviceDestroy
  (JNIEnv *aEnv, jclass aClass, jlong aDevice, jlong aUserData)
{
	void* userData = (void*) (size_t)aUserData;
	DvDeviceC device = (DvDeviceC) (size_t)aDevice;
	aEnv = aEnv;
	aClass = aClass;
	
	if (userData != NULL)
	{
		free(userData);
	}
	JniCallbackListDestroy(aEnv, &iList);
	iList = NULL;
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
	THandle languageList = (THandle) (void*)&aLanguageList;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jint) DvResourceWriterLanguageCount(languageList);
}

/*
 * Class:     org_openhome_net_device_DvDeviceStandard
 * Method:    DvResourceWriterLanguage
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_openhome_net_device_DvDeviceStandard_DvResourceWriterLanguage
  (JNIEnv *aEnv, jclass aClass, jlong aLanguageList, jint aIndex)
{
	THandle languageList = (THandle) (void*)&aLanguageList;
	const char* language = DvResourceWriterLanguage(languageList, aIndex);
	aEnv = aEnv;
	aClass = aClass;
	
	return (*aEnv)->NewStringUTF(aEnv, language);
}

#ifdef __cplusplus
}
#endif
