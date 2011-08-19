#include <jni.h>
#include "ArgumentString.h"
#include "OpenHome/Net/C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_ArgumentString
 * Method:    ActionArgumentCreateStringInput
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_ArgumentString_ActionArgumentCreateStringInput
  (JNIEnv *aEnv, jclass aClass, jlong aParameter, jstring aValue)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	ActionArgument arg;
	const char* value = (*aEnv)->GetStringUTFChars(aEnv, aValue, NULL);
	aClass = aClass;
	
	arg = ActionArgumentCreateStringInput(param, value);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aValue, value);
	
	return (jlong) (size_t)arg;
}

/*
 * Class:     org_openhome_net_controlpoint_ArgumentString
 * Method:    ActionArgumentCreateStringOutput
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_ArgumentString_ActionArgumentCreateStringOutput
  (JNIEnv *aEnv, jclass aClass, jlong aParameter)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) (size_t)ActionArgumentCreateStringOutput(param);
}

/*
 * Class:     org_openhome_net_controlpoint_ArgumentString
 * Method:    ActionArgumentValueString
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_openhome_net_controlpoint_ArgumentString_ActionArgumentValueString
  (JNIEnv *aEnv, jclass aClass, jlong aArgument)
{
	ActionArgument arg = (ActionArgument) (size_t)aArgument;
	const char* val = ActionArgumentValueString(arg);
	aClass = aClass;
	
	return ((*aEnv)->NewStringUTF(aEnv, val));
}

#ifdef __cplusplus
}
#endif
