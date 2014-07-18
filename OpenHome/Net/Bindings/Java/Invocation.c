#include <jni.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "Invocation.h"
#include "JniCallbackList.h"
#include "OpenHome/Defines.h"
#include "OpenHome/Net/C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif

void STDCALL AsyncComplete(void* aPtr, OhNetHandleAsync aAsync) {

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
            printf("Unable to attach thread to JVM.\n");
            fflush(stdout);
            return;
        }
    }

	
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "asyncComplete", "(JJ)V");
    (*env)->DeleteLocalRef(env, cls);
	if (mid == 0)
	{
		printf("Method ID not found.\n");
		fflush(stdout);
		return;
	}
	
	(*env)->CallVoidMethod(env, ref->callbackObj, mid, (jlong)(size_t)NULL, (jlong)(size_t)aAsync);
	(*env)->DeleteGlobalRef(env, ref->callbackObj);
    // leave daemon thread attached to the VM
	
	free(ref);
}

static void STDCALL InitialiseReferences(JNIEnv *aEnv, jobject aObject, JniObjRef **ref)
{
	jint ret;
	*ref = (JniObjRef *)malloc(sizeof(JniObjRef));

	ret = (*aEnv)->GetJavaVM(aEnv, &(*ref)->vm);
	if (ret < 0) {
		printf("InvocationJNI: Unable to get reference to the current Java VM.\n");
		fflush(stdout);
	}
	(*ref)->callbackObj = (*aEnv)->NewGlobalRef(aEnv, aObject);
	if ((*ref)->callbackObj == NULL) {
		printf("InvocationJNI: Callback object not stored.\n");
		fflush(stdout);
	}
}

/*
 * Class:     org_openhome_net_controlpoint_Invocation
 * Method:    CpServiceInvocation
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_Invocation_CpServiceInvocation
  (JNIEnv *aEnv, jobject aObject, jlong aService, jlong aAction)
{
	CpService service = (CpService) (size_t)aService;
	ServiceAction action = (ServiceAction) (size_t)aAction;
	OhNetCallbackAsync callback = &AsyncComplete;
	JniObjRef *ref;

	InitialiseReferences(aEnv, aObject, &ref);
	
	return (jlong) (size_t)CpServiceInvocation(service, action, callback, ref);
}

/*
 * Class:     org_openhome_net_controlpoint_Invocation
 * Method:    CpInvocationAddInput
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_controlpoint_Invocation_CpInvocationAddInput
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jlong aArgument)
{
	CpInvocationC invocation = (CpInvocationC) (size_t)aInvocation;
	ActionArgument arg = (ActionArgument) (size_t)aArgument;
	aEnv = aEnv;
	aClass = aClass;
	
	CpInvocationAddInput(invocation, arg);
}

/*
 * Class:     org_openhome_net_controlpoint_Invocation
 * Method:    CpInvocationAddOutput
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_controlpoint_Invocation_CpInvocationAddOutput
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jlong aArgument)
{
	CpInvocationC invocation = (CpInvocationC) (size_t)aInvocation;
	ActionArgument arg = (ActionArgument) (size_t)aArgument;
	aEnv = aEnv;
	aClass = aClass;
	
	CpInvocationAddOutput(invocation, arg);
}

/*
 * Class:     org_openhome_net_controlpoint_Invocation
 * Method:    CpInvocationError
 * Signature: (J)I
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_controlpoint_Invocation_CpInvocationError
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation)
{
	CpInvocationC invocation = (CpInvocationC) (size_t)aInvocation;
    uint32_t code = 0;
    const char* desc = NULL;
    jclass proxyErrorClass;
    jmethodID mid;
    jstring descString;
    jobject proxyError;
	aClass = aClass;

	if (CpInvocationError(invocation, &code, &desc) == 0) {
        return NULL;
    }
    proxyErrorClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/controlpoint/ProxyError");
    if (proxyErrorClass == NULL)
    {
        printf("Unable to find class org/openhome/net/controlpoint/ProxyError\n");
        fflush(stdout);
        return NULL;
    }
    mid = (*aEnv)->GetMethodID(aEnv, proxyErrorClass, "<init>", "(ILjava/lang/String;)V");
    if (mid == NULL) {
        printf("Unable to find constructor for class org/openhome/net/controlpoint/ProxyError\n");
        fflush(stdout);
        return NULL;
    }
    descString = desc == NULL ? NULL : (*aEnv)->NewStringUTF(aEnv, desc);
    proxyError = (*aEnv)->NewObject(aEnv, proxyErrorClass, mid, (jint)code, descString);
    (*aEnv)->DeleteLocalRef(aEnv, proxyErrorClass);
    
    return proxyError;
}

/*
 * Class:     org_openhome_net_controlpoint_Invocation
 * Method:    CpInvocationOutputInt
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_controlpoint_Invocation_CpInvocationOutputInt
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jint aIndex)
{
	CpInvocationC invocation = (CpInvocationC) (size_t)aInvocation;
	aEnv = aEnv;
	aClass = aClass;
	
	return CpInvocationOutputInt(invocation, aIndex);
}

/*
 * Class:     org_openhome_net_controlpoint_Invocation
 * Method:    CpInvocationOutputUint
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_Invocation_CpInvocationOutputUint
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jint aIndex)
{
	CpInvocationC invocation = (CpInvocationC) (size_t)aInvocation;
	aEnv = aEnv;
	aClass = aClass;
	
	return CpInvocationOutputUint(invocation, aIndex);
}

/*
 * Class:     org_openhome_net_controlpoint_Invocation
 * Method:    CpInvocationOutputBool
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_controlpoint_Invocation_CpInvocationOutputBool
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jint aIndex)
{
	CpInvocationC invocation = (CpInvocationC) (size_t)aInvocation;
	aEnv = aEnv;
	aClass = aClass;
	
	return CpInvocationOutputBool(invocation, aIndex);
}

/*
 * Class:     org_openhome_net_controlpoint_Invocation
 * Method:    CpInvocationOutputString
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_openhome_net_controlpoint_Invocation_CpInvocationOutputString
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jint aIndex)
{
	CpInvocationC invocation = (CpInvocationC) (size_t)aInvocation;
	char *output = CpInvocationOutputString(invocation, aIndex);
	aClass = aClass;
	
	return (*aEnv)->NewStringUTF(aEnv, output);
}

/*
 * Class:     org_openhome_net_controlpoint_Invocation
 * Method:    CpInvocationGetOutputBinary
 * Signature: (JI)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_openhome_net_controlpoint_Invocation_CpInvocationGetOutputBinary
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jint aIndex)
{
	CpInvocationC invocation = (CpInvocationC) (size_t)aInvocation;
	char* data;
	uint32_t len;
	jbyteArray array;
	aClass = aClass;
	
	CpInvocationGetOutputBinary(invocation, aIndex, &data, &len);
	
	array = (*aEnv)->NewByteArray(aEnv, len);
	(*aEnv)->SetByteArrayRegion(aEnv, array, 0, len, (jbyte *) data);
	
	return array;
}

#ifdef __cplusplus
}
#endif
