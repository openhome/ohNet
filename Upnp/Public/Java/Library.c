#include <jni.h>
#include "Library.h"
#include "C/OhNet.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     openhome_net_core_Library
 * Method:    OhNetLibraryInitialise
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_core_Library_OhNetLibraryInitialise
  (JNIEnv *env, jobject obj, jlong paramPtr)
{
	OhNetHandleInitParams param = (OhNetHandleInitParams) paramPtr;
	
    return (jlong) OhNetLibraryInitialise(param);
}

/*
 * Class:     openhome_net_core_Library
 * Method:    OhNetSubnetListCreate
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_core_Library_OhNetSubnetListCreate
  (JNIEnv *env, jobject obj)
{
    return (jlong) OhNetSubnetListCreate();
}

/*
 * Class:     openhome_net_core_Library
 * Method:    OhNetSubnetAt
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_openhome_net_core_Library_OhNetSubnetAt
  (JNIEnv *env, jobject obj, jlong listPtr, jint index)
{
    OhNetHandleNetworkAdapterList list = (OhNetHandleNetworkAdapterList) listPtr;
    
    return (jlong) OhNetSubnetAt(list, index);
}

/*
 * Class:     openhome_net_core_Library
 * Method:    OhNetNetworkAdapterAddress
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_openhome_net_core_Library_OhNetNetworkAdapterAddress
  (JNIEnv *env,  jobject obj, jlong netAdptrPtr)
{
	OhNetHandleNetworkAdapter netAdapter = (OhNetHandleNetworkAdapter) netAdptrPtr;
    TIpAddress ipAddr;

    ipAddr = OhNetNetworkAdapterAddress(netAdapter);
    
    return (jint) ipAddr;
}

/*
 * Class:     openhome_net_core_Library
 * Method:    OhNetNetworkAdapterSubnet
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_openhome_net_core_Library_OhNetNetworkAdapterSubnet
  (JNIEnv *env, jobject obj, jlong netAdptrPtr)
{
	OhNetHandleNetworkAdapter netAdapter = (OhNetHandleNetworkAdapter) netAdptrPtr;
    TIpAddress ipAddr;

    ipAddr = OhNetNetworkAdapterSubnet(netAdapter);
	
	return (jint) ipAddr;
}
/*
 * Class:     openhome_net_core_Library
 * Method:    OhNetCurrentSubnetAdapter
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_core_Library_OhNetCurrentSubnetAdapter
  (JNIEnv *env, jobject obj)
{
	return (jlong) OhNetCurrentSubnetAdapter();
}
/*
 * Class:     openhome_net_core_Library
 * Method:    OhNetSubnetListDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_openhome_net_core_Library_OhNetSubnetListDestroy
  (JNIEnv *env,  jobject obj, jlong listPtr)
{
    OhNetHandleNetworkAdapterList list = (OhNetHandleNetworkAdapterList) listPtr;
    
    OhNetSubnetListDestroy(list);
}

/*
 * Class:     openhome_net_core_Library
 * Method:    OhNetLibraryStartCp
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_openhome_net_core_Library_OhNetLibraryStartCp
  (JNIEnv *env, jobject obj, jint ipAddr)
{
	OhNetLibraryStartCp((TIpAddress) ipAddr);
}

/*
 * Class:     openhome_net_core_Library
 * Method:    OhNetLibraryClose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_openhome_net_core_Library_OhNetLibraryClose
  (JNIEnv *env, jobject obj)
{
	OhNetLibraryClose();
}

#ifdef __cplusplus
}
#endif
