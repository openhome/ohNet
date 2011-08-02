#include <jni.h>
#include <malloc.h>
#include <stdlib.h>
#include "CpDeviceListUpnpServiceType.h"
#include "CpDeviceListCallback.h"
#include "OpenHome/Net/C/CpDeviceUpnp.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_CpDeviceListUpnpServiceType
 * Method:    CpDeviceListCreateUpnpServiceType
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_CpDeviceListUpnpServiceType_CpDeviceListCreateUpnpServiceType
  (JNIEnv *aEnv, jobject aObject, jstring aDomainName, jstring aServiceType, jint aVersion)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = &deviceRemovedCallback;
	JniObjRef* ref = (JniObjRef*) malloc(sizeof(JniObjRef));
	const char* domainName = (*aEnv)->GetStringUTFChars(aEnv, aDomainName, NULL);
	const char* serviceType = (*aEnv)->GetStringUTFChars(aEnv, aServiceType, NULL);

	InitialiseCpDeviceListReferences(aEnv, aObject, &ref);
	
	devList = CpDeviceListCreateUpnpServiceType(domainName, serviceType, aVersion, callbackAdded, ref, callbackRemoved, ref);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aDomainName, domainName);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aServiceType, serviceType);
	
	return (jlong) devList;
}	

#ifdef __cplusplus
}
#endif
