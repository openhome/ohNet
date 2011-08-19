#include <jni.h>
#include <stdio.h>
#include "CpDeviceListUpnpUuid.h"
#include "CpDeviceListCallback.h"
#include "OpenHome/Net/C/CpDeviceUpnp.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_CpDeviceListUpnpUuid
 * Method:    CpDeviceListCreateUpnpUuid
 * Signature: (Ljava/lang/String;)Lorg/openhome/net/controlpoint/CpDeviceList/CpDeviceListInitialised;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_controlpoint_CpDeviceListUpnpUuid_CpDeviceListCreateUpnpUuid
  (JNIEnv *aEnv, jobject aObject, jstring aUuid)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = &deviceRemovedCallback;
	JniObjRef* ref = (JniObjRef*) malloc(sizeof(JniObjRef));
	const char* uuid = (*aEnv)->GetStringUTFChars(aEnv, aUuid, NULL);
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
	
	devList = CpDeviceListCreateUpnpUuid(uuid, callbackAdded, ref, callbackRemoved, ref);
	devListInit = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, (jlong)(size_t)devList, (jlong)(size_t)ref);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aUuid, uuid);
	
	return devListInit;	
}

#ifdef __cplusplus
}
#endif
