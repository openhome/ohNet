#include <jni.h>
#include "NetworkAdapterList.h"
#include "OpenHome/Net/C/OhNet.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_NetworkAdapterList
 * Method:    OhNetSubnetListCreate
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_NetworkAdapterList_OhNetSubnetListCreate
  (JNIEnv *aEnv, jclass aClass)
{
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) OhNetSubnetListCreate();
}

/*
 * Class:     org_openhome_net_core_NetworkAdapterList
 * Method:    OhNetSubnetListSize
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_NetworkAdapterList_OhNetSubnetListSize
  (JNIEnv *aEnv, jclass aClass, jlong aList)
{
	OhNetHandleNetworkAdapterList list = (OhNetHandleNetworkAdapterList) (size_t)aList;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) OhNetSubnetListSize(list);
}

/*
 * Class:     org_openhome_net_core_NetworkAdapterList
 * Method:    OhNetSubnetAt
 * Signature: (JI)I
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_NetworkAdapterList_OhNetSubnetAt
  (JNIEnv *aEnv, jclass aClass, jlong aList, jint aIndex)
{
	OhNetHandleNetworkAdapterList list = (OhNetHandleNetworkAdapterList) (size_t)aList;
	aEnv = aEnv;
	aClass = aClass;
    
    return (jlong) OhNetSubnetAt(list, aIndex);
}

/*
 * Class:     org_openhome_net_core_NetworkAdapterList
 * Method:    OhNetSubnetListDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_NetworkAdapterList_OhNetSubnetListDestroy
  (JNIEnv *aEnv, jclass aClass, jlong aList)
{
	OhNetHandleNetworkAdapterList list = (OhNetHandleNetworkAdapterList) (size_t)aList;
	aEnv = aEnv;
	aClass = aClass;
    
	OhNetSubnetListDestroy(list);
}

#ifdef __cplusplus
}
#endif
