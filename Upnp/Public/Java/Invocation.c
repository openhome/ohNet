#include <jni.h>
#include <malloc.h>
#include <stdlib.h>
#include "Invocation.h"
#include "JniCallbackList.h"
#include "OhNetDefines.h"
#include "C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif

void STDCALL AsyncComplete(void* aPtr, OhNetHandleAsync aAsync) {

	JniObjRef* ref = (JniObjRef*) aPtr;
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
	(*env)->DeleteWeakGlobalRef(env, ref->callbackObj);
	(*(ref->vm))->DetachCurrentThread(ref->vm);
	
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
	(*ref)->callbackObj = (*aEnv)->NewWeakGlobalRef(aEnv, aObject);
	if ((*ref)->callbackObj == NULL) {
		printf("InvocationJNI: Callback object not stored.\n");
		fflush(stdout);
	}
}

/*
 * Class:     openhome_net_controlpoint_Invocation
 * Method:    CpServiceInvocation
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_Invocation_CpServiceInvocation
  (JNIEnv *env, jobject obj, jlong servicePtr, jlong actionPtr)
{
	CpService service = (CpService) (size_t)servicePtr;
	ServiceAction action = (ServiceAction) (size_t)actionPtr;
	OhNetCallbackAsync callback = &AsyncComplete;
	JniObjRef *ref;

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
	CpInvocationC invocation = (CpInvocationC) (size_t)invocationPtr;
	ActionArgument arg = (ActionArgument) (size_t)argPtr;
	env = env;
	obj = obj;
	
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
	CpInvocationC invocation = (CpInvocationC) (size_t)invocationPtr;
	ActionArgument arg = (ActionArgument) (size_t)argPtr;
	env = env;
	obj = obj;
	
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
	CpInvocationC invocation = (CpInvocationC) (size_t)invocationPtr;
	env = env;
	cls = cls;
	
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
	CpInvocationC invocation = (CpInvocationC) (size_t)invocationPtr;
	env = env;
	cls = cls;
	
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
	CpInvocationC invocation = (CpInvocationC) (size_t)invocationPtr;
	env = env;
	cls = cls;
	
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
	CpInvocationC invocation = (CpInvocationC) (size_t)invocationPtr;
	env = env;
	cls = cls;
	
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
	CpInvocationC invocation = (CpInvocationC) (size_t)invocationPtr;
	char *output = CpInvocationOutputString(invocation, index);
	cls = cls;
	
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
	CpInvocationC invocation = (CpInvocationC) (size_t)invocationPtr;
	char* data;
	uint32_t len;
	jbyteArray array;
	cls = cls;
	
	CpInvocationGetOutputBinary(invocation, index, &data, &len);
	
	array = (*env)->NewByteArray(env, len);
	(*env)->SetByteArrayRegion(env, array, 0, len, (jbyte *) data);
	
	return array;
}

#ifdef __cplusplus
}
#endif
