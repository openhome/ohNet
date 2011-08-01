#include <jni.h>
#include "CpDeviceListUpnpRoot.h"
#include "CpDeviceListCallback.h"
#include "OpenHome/Net/C/CpDeviceUpnp.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_CpDeviceListUpnpRoot
 * Method:    CpDeviceListCreateUpnpRoot
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_CpDeviceListUpnpRoot_CpDeviceListCreateUpnpRoot
  (JNIEnv *aEnv, jobject aObject)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = &deviceRemovedCallback;
	JniObjRef* ref = (JniObjRef*) malloc(sizeof(JniObjRef));

	InitialiseCpDeviceListReferences(aEnv, aObject, &ref);
									  
	devList = CpDeviceListCreateUpnpRoot(callbackAdded, ref, callbackRemoved, ref);
	
	return (jlong) devList;
}

#ifdef __cplusplus
}
#endif
