#include <jni.h>
#include "CpService.h"
#include "OpenHome/Net/C/CpDevice.h"
#include "OpenHome/Net/C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_CpService
 * Method:    CpServiceCreate
 * Signature: (Ljava/lang/String;Ljava/lang/String;IJ)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_CpService_CpServiceCreate
  (JNIEnv *aEnv, jclass aClass, jstring aDomain, jstring aName, jint aVersion, jlong aDevice)
{
	CpDeviceC device = (CpDeviceC) (size_t)aDevice;
	CpService service;
	const char* domain = (*aEnv)->GetStringUTFChars(aEnv, aDomain, NULL);
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	aClass = aClass;
	
	service = CpServiceCreate(domain, name, aVersion, device);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aDomain, domain);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return (jlong) (size_t)service;
}

/*
 * Class:     org_openhome_net_controlpoint_CpService
 * Method:    CpServiceDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_controlpoint_CpService_CpServiceDestroy
  (JNIEnv *aEnv, jclass aClass, jlong aService)
{
	CpService service = (CpService) (size_t)aService;
	aEnv = aEnv;
	aClass = aClass;

	CpServiceDestroy(service);
}

/*
 * Class:     org_openhome_net_controlpoint_CpService
 * Method:    CpServiceInvokeAction
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_controlpoint_CpService_CpServiceInvokeAction
  (JNIEnv *aEnv, jclass aClass, jlong aService, jlong aInvocation)
{
	CpService service = (CpService) (size_t)aService;
	CpInvocationC invocation = (CpInvocationC) (size_t)aInvocation;
	aEnv = aEnv;
	aClass = aClass;
	
	CpServiceInvokeAction(service, invocation);
}

#ifdef __cplusplus
}
#endif
