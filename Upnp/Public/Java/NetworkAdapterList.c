#include <jni.h>
#include "NetworkAdapterList.h"
#include "C/OhNet.h"

JNIEXPORT jint JNICALL Java_ohnet_NetworkAdapterList_OhNetSubnetListSize
  (JNIEnv *env, jobject obj, jlong ptr)
{
	OhNetHandleNetworkAdapterList list = (OhNetHandleNetworkAdapterList) ptr;
	
	return (jint) OhNetSubnetListSize(list);
}

JNIEXPORT jint JNICALL Java_ohnet_NetworkAdapterList_OhNetSubnetAt
  (JNIEnv *env, jobject obj, jlong ptr, jint i)
{
	OhNetHandleNetworkAdapterList list = (OhNetHandleNetworkAdapterList) ptr;
    
    return (jint) OhNetSubnetAt(list, i);
}