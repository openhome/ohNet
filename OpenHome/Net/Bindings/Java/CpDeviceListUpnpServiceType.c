#include <jni.h>
#include <malloc.h>
#include <stdio.h>
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
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)Lorg/openhome/net/controlpoint/CpDeviceList/CpDeviceListInitialised;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_controlpoint_CpDeviceListUpnpServiceType_CpDeviceListCreateUpnpServiceType
  (JNIEnv *aEnv, jobject aObject, jstring aDomainName, jstring aServiceType, jint aVersion)
{
	HandleCpDeviceList devList;
	OhNetCallbackDevice callbackAdded = &deviceAddedCallback;
	OhNetCallbackDevice callbackRemoved = &deviceRemovedCallback;
	JniObjRef* ref = (JniObjRef*) malloc(sizeof(JniObjRef));
	const char* domainName = (*aEnv)->GetStringUTFChars(aEnv, aDomainName, NULL);
	const char* serviceType = (*aEnv)->GetStringUTFChars(aEnv, aServiceType, NULL);
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
	
	devList = CpDeviceListCreateUpnpServiceType(domainName, serviceType, aVersion, callbackAdded, ref, callbackRemoved, ref);
	devListInit = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, (jlong)(size_t)devList, (jlong)(size_t)ref);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aDomainName, domainName);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aServiceType, serviceType);
	
	return devListInit;
}	

#ifdef __cplusplus
}
#endif
