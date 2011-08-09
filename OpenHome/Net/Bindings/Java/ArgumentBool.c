#include <jni.h>
#include "ArgumentBool.h"
#include "OpenHome/Net/C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_ArgumentBool
 * Method:    ActionArgumentCreateBoolInput
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_ArgumentBool_ActionArgumentCreateBoolInput
  (JNIEnv *aEnv, jclass aClass, jlong aParameter, jint aValue)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) (size_t)ActionArgumentCreateBoolInput(param, aValue);
}

/*
 * Class:     org_openhome_net_controlpoint_ArgumentBool
 * Method:    ActionArgumentCreateBoolOutput
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_ArgumentBool_ActionArgumentCreateBoolOutput
  (JNIEnv *aEnv, jclass aClass, jlong aParameter)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) (size_t)ActionArgumentCreateBoolOutput(param);
}

/*
 * Class:     org_openhome_net_controlpoint_ArgumentBool
 * Method:    ActionArgumentValueBool
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_controlpoint_ArgumentBool_ActionArgumentValueBool
  (JNIEnv *aEnv, jclass aClass, jlong aArgument)
{
	ActionArgument arg = (ActionArgument) (size_t)aArgument;
	aEnv = aEnv;
	aClass = aClass;
	
	return ActionArgumentValueBool(arg);
}

#ifdef __cplusplus
}
#endif
