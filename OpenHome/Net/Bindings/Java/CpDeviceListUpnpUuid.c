#include <jni.h>
#include "CpDeviceListUpnpUuid.h"
#include "CpDeviceListCallback.h"
#include "OpenHome/Net/C/CpDeviceUpnp.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_CpDeviceListUpnpUuid
 * Method:    CpDeviceListCreateUpnpUuid
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_CpDeviceListUpnpUuid_CpDeviceListCreateUpnpUuid
  (JNIEnv *aEnv, jobject aObject, jstring aUuid)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = &deviceRemovedCallback;
	JniObjRef* ref = (JniObjRef*) malloc(sizeof(JniObjRef));
	const char* uuid = (*aEnv)->GetStringUTFChars(aEnv, aUuid, NULL);

	InitialiseCpDeviceListReferences(aEnv, aObject, &ref);
	
	devList = CpDeviceListCreateUpnpUuid(uuid, callbackAdded, ref, callbackRemoved, ref);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aUuid, uuid);
	
	return (jlong) devList;	
}

#ifdef __cplusplus
}
#endif
