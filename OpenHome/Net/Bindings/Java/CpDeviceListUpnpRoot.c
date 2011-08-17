#include <jni.h>
#include <stdio.h>
#include "CpDeviceListUpnpRoot.h"
#include "CpDeviceListCallback.h"
#include "OpenHome/Net/C/CpDeviceUpnp.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_CpDeviceListUpnpRoot
 * Method:    CpDeviceListCreateUpnpRoot
 * Signature: ()Lorg/openhome/net/controlpoint/CpDeviceList/CpDeviceListInitialised;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_controlpoint_CpDeviceListUpnpRoot_CpDeviceListCreateUpnpRoot
  (JNIEnv *aEnv, jobject aObject)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = &deviceRemovedCallback;
	JniObjRef* ref = (JniObjRef*) malloc(sizeof(JniObjRef));
	jclass statusClass;
	jmethodID cid;
	jobject devListInit;

	InitialiseCpDeviceListReferences(aEnv, aObject, &ref);

	statusClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/controlpoint/CpDeviceList$CpDeviceListInitialised");
	if (statusClass == NULL)
	{
		printf("Unable to find class org/openhome/net/controlpoint/CpDeviceList$CpDeviceListInitialised\n");
		return NULL;
	}
	cid = (*aEnv)->GetMethodID(aEnv, statusClass, "<init>", "(Lorg/openhome/net/controlpoint/CpDeviceList;JJ)V");
	if (cid == NULL)
	{
		printf("Unable to find constructor for class org/openhome/net/controlpoint/CpDeviceList$CpDeviceListInitialised\n");
        return NULL;
	}
	
	devList = CpDeviceListCreateUpnpRoot(callbackAdded, ref, callbackRemoved, ref);
	devListInit = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, (jlong)(size_t)devList, (jlong)(size_t)ref);
	
	return devListInit;
}

#ifdef __cplusplus
}
#endif
