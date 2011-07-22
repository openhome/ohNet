#include <jni.h>
#include "ArgumentString.h"
#include "C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     openhome_net_controlpoint_ArgumentString
 * Method:    ActionArgumentCreateStringInput
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_ArgumentString_ActionArgumentCreateStringInput
  (JNIEnv *env, jobject obj, jlong paramPtr, jstring val)
{
	ServiceParameter param = (ServiceParameter) paramPtr;
	ActionArgument arg;
	const char* nativeValue = (*env)->GetStringUTFChars(env, val, NULL);
	
	arg = ActionArgumentCreateStringInput(param, nativeValue);
	
	(*env)->ReleaseStringUTFChars(env, val, nativeValue);
	
	return (jlong) arg;
}

/*
 * Class:     openhome_net_controlpoint_ArgumentString
 * Method:    ActionArgumentCreateStringOutput
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_ArgumentString_ActionArgumentCreateStringOutput
  (JNIEnv *env, jobject obj, jlong paramPtr)
{
	ServiceParameter param = (ServiceParameter) paramPtr;
	
	return (jlong) ActionArgumentCreateStringOutput(param);
}

/*
 * Class:     openhome_net_controlpoint_ArgumentString
 * Method:    ActionArgumentValueString
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_openhome_net_controlpoint_ArgumentString_ActionArgumentValueString
  (JNIEnv *env, jobject obj, jlong argPtr)
{
	ActionArgument arg = (ActionArgument) argPtr;
	
	const char* val = ActionArgumentValueString(arg);
	
	return ((*env)->NewStringUTF(env, val));
}

#ifdef __cplusplus
}
#endif
