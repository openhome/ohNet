#include <jni.h>
#include "CpService.h"
#include "C/CpDevice.h"
#include "C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     openhome_net_controlpoint_CpService
 * Method:    CpServiceCreate
 * Signature: (Ljava/lang/String;Ljava/lang/String;IJ)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_CpService_CpServiceCreate
  (JNIEnv *env, jobject obj, jstring domain, jstring name, jint version, jlong devPtr)
{
	CpDeviceC device = (CpDeviceC) devPtr;
	CpService service;
	
	const char* nativeDomain = (*env)->GetStringUTFChars(env, domain, NULL);
	const char* nativeName = (*env)->GetStringUTFChars(env, name, NULL);
	
	service = CpServiceCreate(nativeDomain, nativeName, version, device);
	
	(*env)->ReleaseStringUTFChars(env, domain, nativeDomain);
	(*env)->ReleaseStringUTFChars(env, name, nativeName);
	
	return (jlong) service;
}

/*
 * Class:     openhome_net_controlpoint_CpService
 * Method:    CpServiceDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_openhome_net_controlpoint_CpService_CpServiceDestroy
  (JNIEnv *env, jobject obj, jlong servicePtr)
{
	CpService service = (CpService) servicePtr;

	CpServiceDestroy(service);
}

/*
 * Class:     openhome_net_controlpoint_CpService
 * Method:    CpServiceInvokeAction
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_openhome_net_controlpoint_CpService_CpServiceInvokeAction
  (JNIEnv *env, jobject obj, jlong servicePtr, jlong invocationPtr)
{
	CpService service = (CpService) servicePtr;
	CpInvocationC invocation = (CpInvocationC) invocationPtr;
	
	CpServiceInvokeAction(service, invocation);
}

#ifdef __cplusplus
}
#endif
