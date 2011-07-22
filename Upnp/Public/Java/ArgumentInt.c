#include <jni.h>
#include "ArgumentInt.h"
#include "C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     openhome_net_controlpoint_ArgumentInt
 * Method:    ActionArgumentCreateIntInput
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_ArgumentInt_ActionArgumentCreateIntInput
  (JNIEnv *env, jobject obj, jlong paramPtr, jint value)
{
	ServiceParameter param = (ServiceParameter) paramPtr;
	
	return (jlong) ActionArgumentCreateIntInput(param, value);
}

/*
 * Class:     openhome_net_controlpoint_ArgumentInt
 * Method:    ActionArgumentCreateIntOutput
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_ArgumentInt_ActionArgumentCreateIntOutput
  (JNIEnv *env, jobject obj, jlong paramPtr)
{
	ServiceParameter param = (ServiceParameter) paramPtr;
	
	return (jlong) ActionArgumentCreateIntOutput(param);
}

/*
 * Class:     openhome_net_controlpoint_ArgumentInt
 * Method:    ActionArgumentValueInt
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_openhome_net_controlpoint_ArgumentInt_ActionArgumentValueInt
  (JNIEnv *env, jobject obj, jlong argPtr)
{
	ActionArgument arg = (ActionArgument) argPtr;
	
	return ActionArgumentValueInt(arg);
}

#ifdef __cplusplus
}
#endif
