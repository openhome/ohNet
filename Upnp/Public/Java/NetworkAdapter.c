#include <jni.h>
#include "NetworkAdapter.h"
#include "OpenHome/Net/C/OhNet.h"

JNIEXPORT jint JNICALL Java_ohnet_NetworkAdapter_OhNetNetworkAdapterAddress
  (JNIEnv *env, jobject obj, jlong ptr)
{
	TIpAddress ipAddr;
	OhNetHandleNetworkAdapter adapter = (OhNetHandleNetworkAdapter) (size_t)ptr;
	env = env;
	obj = obj;

	ipAddr = OhNetNetworkAdapterAddress(adapter);
	
	return (jint) ipAddr;
}

JNIEXPORT jint JNICALL Java_ohnet_NetworkAdapter_OhNetNetworkAdapterSubnet
  (JNIEnv *env, jobject obj, jlong ptr)
{
	TIpAddress ipAddr;
	OhNetHandleNetworkAdapter adapter = (OhNetHandleNetworkAdapter) (size_t)ptr;
	env = env;
	obj = obj;

	ipAddr = OhNetNetworkAdapterSubnet(adapter);
	
	return (jint) ipAddr;
}

JNIEXPORT jstring JNICALL Java_ohnet_NetworkAdapter_OhNetNetworkAdapterName
  (JNIEnv *env, jobject obj, jlong ptr)
{
	OhNetHandleNetworkAdapter adapter = (OhNetHandleNetworkAdapter) (size_t)ptr;
	const char* name = OhNetNetworkAdapterName(adapter);
	obj = obj;
	
	return ((*env)->NewStringUTF(env, name));
}

JNIEXPORT jstring JNICALL Java_ohnet_NetworkAdapter_OhNetNetworkAdapterFullName
  (JNIEnv *env, jobject obj, jlong ptr)
{
	OhNetHandleNetworkAdapter adapter = (OhNetHandleNetworkAdapter) (size_t)ptr;
	const char* name = OhNetNetworkAdapterFullName(adapter);
	obj = obj;
	
	return ((*env)->NewStringUTF(env, name));
}