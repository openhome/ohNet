#include <jni.h>
#include "ArgumentUint.h"
#include "C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     openhome_net_controlpoint_ArgumentUint
 * Method:    ActionArgumentCreateUintInput
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_ArgumentUint_ActionArgumentCreateUintInput
  (JNIEnv *env, jobject obj, jlong paramPtr, jlong val)
{
	ServiceParameter param = (ServiceParameter) (size_t)paramPtr;
	env = env;
	obj = obj;
	
	return (jlong) ActionArgumentCreateUintInput(param, (uint32_t)val);
}

/*
 * Class:     openhome_net_controlpoint_ArgumentUint
 * Method:    ActionArgumentCreateUintOutput
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_ArgumentUint_ActionArgumentCreateUintOutput
  (JNIEnv *env, jobject obj, jlong paramPtr)
{
	ServiceParameter param = (ServiceParameter) (size_t)paramPtr;
	env = env;
	obj = obj;
	
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
	ActionArgument arg = (ActionArgument) (size_t)argPtr;
	env = env;
	obj = obj;
	
	return ActionArgumentValueUint(arg);
}

#ifdef __cplusplus
}
#endif
