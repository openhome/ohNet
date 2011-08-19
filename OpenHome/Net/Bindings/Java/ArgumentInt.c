#include <jni.h>
#include "ArgumentInt.h"
#include "OpenHome/Net/C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_ArgumentInt
 * Method:    ActionArgumentCreateIntInput
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_ArgumentInt_ActionArgumentCreateIntInput
  (JNIEnv *aEnv, jclass aClass, jlong aParameter, jint aValue)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) (size_t)ActionArgumentCreateIntInput(param, aValue);
}

/*
 * Class:     org_openhome_net_controlpoint_ArgumentInt
 * Method:    ActionArgumentCreateIntOutput
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_ArgumentInt_ActionArgumentCreateIntOutput
  (JNIEnv *aEnv, jclass aClass, jlong aParameter)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) (size_t)ActionArgumentCreateIntOutput(param);
}

/*
 * Class:     org_openhome_net_controlpoint_ArgumentInt
 * Method:    ActionArgumentValueInt
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_controlpoint_ArgumentInt_ActionArgumentValueInt
  (JNIEnv *aEnv, jclass aClass, jlong aArgument)
{
	ActionArgument arg = (ActionArgument) (size_t)aArgument;
	aEnv = aEnv;
	aClass = aClass;
	
	return ActionArgumentValueInt(arg);
}

#ifdef __cplusplus
}
#endif
