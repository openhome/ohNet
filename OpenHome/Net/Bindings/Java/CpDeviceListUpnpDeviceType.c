#include <jni.h>
#include <malloc.h>
#include <stdlib.h>
#include "CpDeviceListUpnpDeviceType.h"
#include "CpDeviceListCallback.h"
#include "OpenHome/Net/C/CpDeviceUpnp.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_CpDeviceListUpnpDeviceType
 * Method:    CpDeviceListCreateUpnpDeviceType
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_CpDeviceListUpnpDeviceType_CpDeviceListCreateUpnpDeviceType
  (JNIEnv *aEnv, jobject aObject, jstring aDomainName, jstring aDeviceType, jint aVersion)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = &deviceRemovedCallback;
	JniObjRef* ref = (JniObjRef*) malloc(sizeof(JniObjRef));
	const char* domainName = (*aEnv)->GetStringUTFChars(aEnv, aDomainName, NULL);
	const char* deviceType = (*aEnv)->GetStringUTFChars(aEnv, aDeviceType, NULL);

	InitialiseCpDeviceListReferences(aEnv, aObject, &ref);
	
	devList = CpDeviceListCreateUpnpDeviceType(domainName, deviceType, aVersion, callbackAdded, ref, callbackRemoved, ref);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aDomainName, domainName);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aDeviceType, deviceType);
	
	return (jlong) devList;
}

#ifdef __cplusplus
}
#endif
