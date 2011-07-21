#include <jni.h>
#include <malloc.h>
#include <stdlib.h>
#include "Invocation.h"
#include "C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
	JavaVM *vm;
	jweak callbackObj;
} jniObjRef;

//jniObjRef *ref = NULL;

void AsyncComplete(void* aPtr, OhNetHandleAsync aAsync) {

	jniObjRef* ref = (jniObjRef*) aPtr;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	jint ret;

	ret = (*(ref->vm))->AttachCurrentThread(ref->vm, (void **) &env, NULL);
	if (ret < 0)
	{
		printf("Unable to attach thread to JVM.\n");
		fflush(stdout);
		return;
	}
	
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "asyncComplete", "(JJ)V");
	if (mid == 0)
	{
		printf("Method ID not found.\n");
		fflush(stdout);
		return;
	}
	
	(*env)->CallVoidMethod(env, ref->callbackObj, mid, (jlong) NULL, (jlong) aAsync);
	
	(*(ref->vm))->DetachCurrentThread(ref->vm);
	
	free(ref);
}

void InitialiseReferences(JNIEnv *env, jobject obj, jniObjRef **ref)
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
	(*ref)->callbackObj = (*env)->NewWeakGlobalRef(env, obj);

	/*if (callbackObj == NULL) {
		printf("Callback object not stored.\n");
	} else {
		printf("Callback object successfully stored.\n");
	}*/
}

/*
 * Class:     openhome_net_controlpoint_Invocation
 * Method:    CpServiceInvocation
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_Invocation_CpServiceInvocation
  (JNIEnv *env, jobject obj, jlong servicePtr, jlong actionPtr)
{
	CpService service = (CpService) servicePtr;
	ServiceAction action = (ServiceAction) actionPtr;
	OhNetCallbackAsync callback = &AsyncComplete;
	
	jniObjRef *ref;
	jclass cls;
	jmethodID mid;
	jint ret;
	
	InitialiseReferences(env, obj, &ref);
	
	return (jlong) CpServiceInvocation(service, action, callback, ref);
}

/*
 * Class:     openhome_net_controlpoint_Invocation
 * Method:    CpInvocationAddInput
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_openhome_net_controlpoint_Invocation_CpInvocationAddInput
  (JNIEnv *env, jobject obj, jlong invocationPtr, jlong argPtr)
{
	CpInvocationC invocation = (CpInvocationC) invocationPtr;
	ActionArgument arg = (ActionArgument) argPtr;
	
	CpInvocationAddInput(invocation, arg);
}

/*
 * Class:     openhome_net_controlpoint_Invocation
 * Method:    CpInvocationAddOutput
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_openhome_net_controlpoint_Invocation_CpInvocationAddOutput
  (JNIEnv *env, jobject obj, jlong invocationPtr, jlong argPtr)
{
	CpInvocationC invocation = (CpInvocationC) invocationPtr;
	ActionArgument arg = (ActionArgument) argPtr;
	
	CpInvocationAddOutput(invocation, arg);
}

/*
 * Class:     openhome_net_controlpoint_Invocation
 * Method:    CpInvocationError
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_openhome_net_controlpoint_Invocation_CpInvocationError
  (JNIEnv *env, jclass cls, jlong invocationPtr)
{
	CpInvocationC invocation = (CpInvocationC) invocationPtr;
	
	return CpInvocationError(invocation);
}

/*
 * Class:     openhome_net_controlpoint_Invocation
 * Method:    CpInvocationOutputInt
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_openhome_net_controlpoint_Invocation_CpInvocationOutputInt
  (JNIEnv *env, jclass cls, jlong invocationPtr, jint index)
{
	CpInvocationC invocation = (CpInvocationC) invocationPtr;
	
	return CpInvocationOutputInt(invocation, index);
}

/*
 * Class:     openhome_net_controlpoint_Invocation
 * Method:    CpInvocationOutputUint
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_Invocation_CpInvocationOutputUint
  (JNIEnv *env, jclass cls, jlong invocationPtr, jint index)
{
	CpInvocationC invocation = (CpInvocationC) invocationPtr;
	
	return CpInvocationOutputUint(invocation, index);
}

/*
 * Class:     openhome_net_controlpoint_Invocation
 * Method:    CpInvocationOutputBool
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_openhome_net_controlpoint_Invocation_CpInvocationOutputBool
  (JNIEnv *env, jclass cls, jlong invocationPtr, jint index)
{
	CpInvocationC invocation = (CpInvocationC) invocationPtr;
	
	return CpInvocationOutputBool(invocation, index);
}

/*
 * Class:     openhome_net_controlpoint_Invocation
 * Method:    CpInvocationOutputString
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_openhome_net_controlpoint_Invocation_CpInvocationOutputString
  (JNIEnv *env, jclass cls, jlong invocationPtr, jint index)
{
	CpInvocationC invocation = (CpInvocationC) invocationPtr;
	char *output = CpInvocationOutputString(invocation, index);
	
	return (*env)->NewStringUTF(env, output);
}

/*
 * Class:     openhome_net_controlpoint_Invocation
 * Method:    CpInvocationGetOutputBinary
 * Signature: (JI)[B
 */
JNIEXPORT jbyteArray JNICALL Java_openhome_net_controlpoint_Invocation_CpInvocationGetOutputBinary
  (JNIEnv *env, jclass cls, jlong invocationPtr, jint index)
{
	CpInvocationC invocation = (CpInvocationC) invocationPtr;
	uint8_t* data;
	uint32_t len;
	jbyteArray array;
	
	CpInvocationGetOutputBinary(invocation, index, &data, &len);
	
	array = (*env)->NewByteArray(env, len);
	(*env)->SetByteArrayRegion(env, array, 0, len, (jbyte *) data);
	
	return array;
}

#ifdef __cplusplus
}
#endif
