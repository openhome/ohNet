#include <jni.h>
#include "ArgumentBool.h"
#include "C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     openhome_net_controlpoint_ArgumentBool
 * Method:    ActionArgumentCreateBoolInput
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_ArgumentBool_ActionArgumentCreateBoolInput
  (JNIEnv *env, jobject obj, jlong paramPtr, jint val)
{
	ServiceParameter param = (ServiceParameter) (size_t)paramPtr;
	env = env;
	obj = obj;
	
	return (jlong) ActionArgumentCreateBoolInput(param, val);
}

/*
 * Class:     openhome_net_controlpoint_ArgumentBool
 * Method:    ActionArgumentCreateBoolOutput
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_ArgumentBool_ActionArgumentCreateBoolOutput
  (JNIEnv *env, jobject obj, jlong paramPtr)
{
	ServiceParameter param = (ServiceParameter) (size_t)paramPtr;
	env = env;
	obj = obj;
	
	return (jlong) ActionArgumentCreateBoolOutput(param);
}

/*
 * Class:     openhome_net_controlpoint_ArgumentBool
 * Method:    ActionArgumentValueBool
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_openhome_net_controlpoint_ArgumentBool_ActionArgumentValueBool
  (JNIEnv *env, jobject obj, jlong argPtr)
{
	ActionArgument arg = (ActionArgument) (size_t)argPtr;
	env = env;
	obj = obj;
	
	return ActionArgumentValueBool(arg);
}

#ifdef __cplusplus
}
#endif
