#include <jni.h>
#include "SubnetList.h"
#include "OpenHome/Net/C/OhNet.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_SubnetList
 * Method:    OhNetSubnetListCreate
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_SubnetList_OhNetSubnetListCreate
  (JNIEnv *aEnv, jclass aClass)
{
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) (size_t)OhNetSubnetListCreate();
}

/*
 * Class:     org_openhome_net_core_SubnetList
 * Method:    OhNetSubnetListSize
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_SubnetList_OhNetSubnetListSize
  (JNIEnv *aEnv, jclass aClass, jlong aList)
{
	OhNetHandleNetworkAdapterList list = (OhNetHandleNetworkAdapterList) (size_t)aList;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) OhNetSubnetListSize(list);
}

/*
 * Class:     org_openhome_net_core_SubnetList
 * Method:    OhNetSubnetAt
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_SubnetList_OhNetSubnetAt
  (JNIEnv *aEnv, jclass aClass, jlong aList, jint aIndex)
{
	OhNetHandleNetworkAdapterList list = (OhNetHandleNetworkAdapterList) (size_t)aList;
	aEnv = aEnv;
	aClass = aClass;
    
    return (jlong) (size_t)OhNetSubnetAt(list, aIndex);
}

/*
 * Class:     org_openhome_net_core_SubnetList
 * Method:    OhNetSubnetListDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_SubnetList_OhNetSubnetListDestroy
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
