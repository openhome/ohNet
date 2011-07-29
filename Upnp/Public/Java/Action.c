#include <jni.h>
#include "Action.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     ohnet_Action
 * Method:    ServiceActionCreate
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_ohnet_Action_ServiceActionCreate
  (JNIEnv *env, jobject obj, jstring name)
{
	const char* nativeName = (*env)->GetStringUTFChars(env, name, NULL);
	ServiceAction action = ServiceActionCreate(nativeName);
	obj = obj;
	
	(*env)->ReleaseStringUTFChars(env, name, nativeName);
	
	return (jlong) action;
}

/*
 * Class:     ohnet_Action
 * Method:    ServiceActionDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ohnet_Action_ServiceActionDestroy
  (JNIEnv *env, jobject obj, jlong actionPtr)
{
	ServiceAction action = (ServiceAction) (size_t)actionPtr;
	env = env;
	obj = obj;
	
	ServiceActionDestroy(action);
}

/*
 * Class:     ohnet_Action
 * Method:    ServiceActionAddInputParameter
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_ohnet_Action_ServiceActionAddInputParameter
  (JNIEnv *env, jobject obj, jlong actionPtr, jlong paramPtr)
{
	ServiceAction action = (ServiceAction) (size_t)actionPtr;
	ServiceParameter param = (ServiceParameter) (size_t)paramPtr;
	env = env;
	obj = obj;
	
	ServiceActionAddInputParameter(action, param);
}

/*
 * Class:     ohnet_Action
 * Method:    ServiceActionAddOutputParameter
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_ohnet_Action_ServiceActionAddOutputParameter
  (JNIEnv *env, jobject obj, jlong actionPtr, jlong paramPtr)
{
	ServiceAction action = (ServiceAction) (size_t)actionPtr;
	ServiceParameter param = (ServiceParameter) (size_t)paramPtr;
	env = env;
	obj = obj;
	
	ServiceActionAddOutputParameter(action, param);
}

/*
 * Class:     ohnet_Action
 * Method:    ServiceActionName
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ohnet_Action_ServiceActionName
  (JNIEnv *env, jobject obj, jlong actionPtr)
{
	ServiceAction action = (ServiceAction) (size_t)actionPtr;
	const char* nativeName = ServiceActionName(action);
	obj = obj;
	
	return (*env)->NewStringUTF(env, nativeName);
}

#ifdef __cplusplus
}
#endif
