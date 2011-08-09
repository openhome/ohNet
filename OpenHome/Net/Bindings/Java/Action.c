#include <jni.h>
#include "Action.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_Action
 * Method:    ServiceActionCreate
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_Action_ServiceActionCreate
  (JNIEnv *aEnv, jclass aClass, jstring aName)
{
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	ServiceAction action = ServiceActionCreate(name);
	aClass = aClass;
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return (jlong) (size_t)action;
}

/*
 * Class:     org_openhome_net_core_Action
 * Method:    ServiceActionDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_Action_ServiceActionDestroy
  (JNIEnv *aEnv, jclass aClass, jlong aAction)
{
	ServiceAction action = (ServiceAction) (size_t)aAction;
	aEnv = aEnv;
	aClass = aClass;
	
	ServiceActionDestroy(action);
}

/*
 * Class:     org_openhome_net_core_Action
 * Method:    ServiceActionAddInputParameter
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_Action_ServiceActionAddInputParameter
  (JNIEnv *aEnv, jclass aClass, jlong aAction, jlong aParameter)
{
	ServiceAction action = (ServiceAction) (size_t)aAction;
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	aEnv = aEnv;
	aClass = aClass;
	
	ServiceActionAddInputParameter(action, param);
}

/*
 * Class:     org_openhome_net_core_Action
 * Method:    ServiceActionAddOutputParameter
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_Action_ServiceActionAddOutputParameter
  (JNIEnv *aEnv, jclass aClass, jlong aAction, jlong aParameter)
{
	ServiceAction action = (ServiceAction) (size_t)aAction;
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	aEnv = aEnv;
	aClass = aClass;
	
	ServiceActionAddOutputParameter(action, param);
}

/*
 * Class:     org_openhome_net_core_Action
 * Method:    ServiceActionName
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_openhome_net_core_Action_ServiceActionName
  (JNIEnv *aEnv, jclass aClass, jlong aAction)
{
	ServiceAction action = (ServiceAction) (size_t)aAction;
	const char* name = ServiceActionName(action);
	aClass = aClass;
	
	return (*aEnv)->NewStringUTF(aEnv, name);
}

#ifdef __cplusplus
}
#endif
