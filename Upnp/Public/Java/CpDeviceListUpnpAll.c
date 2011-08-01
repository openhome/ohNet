#include <jni.h>
#include "CpDeviceListUpnpAll.h"
#include "CpDeviceListCallback.h"
#include "OpenHome/Net/C/CpDeviceUpnp.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_CpDeviceListUpnpAll
 * Method:    CpDeviceListCreateUpnpAll
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_CpDeviceListUpnpAll_CpDeviceListCreateUpnpAll
  (JNIEnv *aEnv, jobject aObject)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = &deviceRemovedCallback;
	JniObjRef* ref = (JniObjRef*) malloc(sizeof(JniObjRef));

	InitialiseCpDeviceListReferences(aEnv, aObject, &ref);
									  
	devList = CpDeviceListCreateUpnpAll(callbackAdded, ref, callbackRemoved, ref);
	
	return (jlong) devList;
}

#ifdef __cplusplus
}
#endif
