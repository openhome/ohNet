#include <jni.h>
#include "NetworkAdapter.h"
#include "C/OhNet.h"

JNIEXPORT jint JNICALL Java_ohnet_NetworkAdapter_OhNetNetworkAdapterAddress
  (JNIEnv *env, jobject obj, jlong ptr)
{
	TIpAddress ipAddr;

	ipAddr = OhNetNetworkAdapterAddress((OhNetHandleNetworkAdapter) ptr);
	
	return (jint) ipAddr;
}

JNIEXPORT jint JNICALL Java_ohnet_NetworkAdapter_OhNetNetworkAdapterSubnet
  (JNIEnv *env, jobject obj, jlong ptr)
{
	TIpAddress ipAddr;

	ipAddr = OhNetNetworkAdapterSubnet((OhNetHandleNetworkAdapter) ptr);
	
	return (jint) ipAddr;
}

JNIEXPORT jstring JNICALL Java_ohnet_NetworkAdapter_OhNetNetworkAdapterName
  (JNIEnv *env, jobject obj, jlong ptr)
{
	const char* name = OhNetNetworkAdapterName((OhNetHandleNetworkAdapter) ptr);
	
	return ((*env)->NewStringUTF(env, name));
}

JNIEXPORT jstring JNICALL Java_ohnet_NetworkAdapter_OhNetNetworkAdapterFullName
  (JNIEnv *env, jobject obj, jlong ptr)
{
	const char* name = OhNetNetworkAdapterFullName((OhNetHandleNetworkAdapter) ptr);
	
	return ((*env)->NewStringUTF(env, name));
}