#include <jni.h>
#include "ArgumentUint.h"
#include "C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     openhome_net_controlpoint_ArgumentUint
 * Method:    ActionArgumentCreateUintInput
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_ArgumentUint_ActionArgumentCreateUintInput
  (JNIEnv *env, jobject obj, jlong paramPtr, jint val)
{
	ServiceParameter param = (ServiceParameter) paramPtr;
	
	return (jlong) ActionArgumentCreateUintInput(param, val);
}

/*
 * Class:     openhome_net_controlpoint_ArgumentUint
 * Method:    ActionArgumentCreateUintOutput
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_ArgumentUint_ActionArgumentCreateUintOutput
  (JNIEnv *env, jobject obj, jlong paramPtr)
{
	ServiceParameter param = (ServiceParameter) paramPtr;
	
	return (jlong) ActionArgumentCreateUintOutput(param);
}

/*
 * Class:     openhome_net_controlpoint_ArgumentUint
 * Method:    ActionArgumentValueUint
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_ArgumentUint_ActionArgumentValueUint
  (JNIEnv *env, jobject obj, jlong argPtr)
{
	ActionArgument arg = (ActionArgument) argPtr;
	
	return ActionArgumentValueUint(arg);
}

#ifdef __cplusplus
}
#endif
