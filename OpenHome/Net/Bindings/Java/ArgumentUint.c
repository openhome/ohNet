#include <jni.h>
#include "ArgumentUint.h"
#include "OpenHome/Net/C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_ArgumentUint
 * Method:    ActionArgumentCreateUintInput
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_ArgumentUint_ActionArgumentCreateUintInput
  (JNIEnv *aEnv, jclass aClass, jlong aParameter, jlong aValue)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) (size_t)ActionArgumentCreateUintInput(param, (uint32_t)aValue);
}

/*
 * Class:     org_openhome_net_controlpoint_ArgumentUint
 * Method:    ActionArgumentCreateUintOutput
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_ArgumentUint_ActionArgumentCreateUintOutput
  (JNIEnv *aEnv, jclass aClass, jlong aParameter)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) (size_t)ActionArgumentCreateUintOutput(param);
}

/*
 * Class:     org_openhome_net_controlpoint_ArgumentUint
 * Method:    ActionArgumentValueUint
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_ArgumentUint_ActionArgumentValueUint
  (JNIEnv *aEnv, jclass aClass, jlong aArgument)
{
	ActionArgument arg = (ActionArgument) (size_t)aArgument;
	aEnv = aEnv;
	aClass = aClass;
	
	return ActionArgumentValueUint(arg);
}

#ifdef __cplusplus
}
#endif
