#include <jni.h>
#include "InitParams.h"
#include "C/OhNet.h"

JNIEXPORT jlong JNICALL Java_openhome_net_core_InitParams_OhNetInitParamsCreate
  (JNIEnv *env, jobject obj)
{
	return (jlong) OhNetInitParamsCreate();
}

JNIEXPORT void JNICALL Java_openhome_net_core_InitParams_OhNetInitParamsDestroy
  (JNIEnv *env, jobject obj, jlong ptr)
{
	OhNetInitParamsDestroy((OhNetHandleInitParams) ptr);
}

JNIEXPORT jint JNICALL Java_openhome_net_core_InitParams_OhNetInitParamsTcpConnectTimeoutMs
  (JNIEnv *env, jobject obj, jlong ptr)
{
	int timeout = OhNetInitParamsTcpConnectTimeoutMs((OhNetHandleInitParams) ptr);
	
	return (jint) timeout;
}

JNIEXPORT jint JNICALL Java_openhome_net_core_InitParams_OhNetInitParamsMsearchTimeSecs
  (JNIEnv *env, jobject obj, jlong ptr)
{
	int searchTime = OhNetInitParamsMsearchTimeSecs((OhNetHandleInitParams) ptr);
	
	return (jint) searchTime;
}

JNIEXPORT jint JNICALL Java_openhome_net_core_InitParams_OhNetInitParamsMsearchTtl
  (JNIEnv *env, jobject obj, jlong ptr)
{
	int searchTime = OhNetInitParamsMsearchTtl((OhNetHandleInitParams) ptr);
	
	return (jint) searchTime;
}

JNIEXPORT jint JNICALL Java_openhome_net_core_InitParams_OhNetInitParamsNumEventSessionThreads
  (JNIEnv *env, jobject obj, jlong ptr)
{
	int numThreads = OhNetInitParamsNumEventSessionThreads((OhNetHandleInitParams) ptr);
	
	return (jint) numThreads;
}

JNIEXPORT jint JNICALL Java_openhome_net_core_InitParams_OhNetInitParamsNumXmlFetcherThreads
  (JNIEnv *env, jobject obj, jlong ptr)
{
	int numThreads = OhNetInitParamsNumXmlFetcherThreads((OhNetHandleInitParams) ptr);
	
	return (jint) numThreads;
}

JNIEXPORT jint JNICALL Java_openhome_net_core_InitParams_OhNetInitParamsNumActionInvokerThreads
  (JNIEnv *env, jobject obj, jlong ptr)
{
	int numThreads = OhNetInitParamsNumActionInvokerThreads((OhNetHandleInitParams) ptr);
	
	return (jint) numThreads;
}

JNIEXPORT jint JNICALL Java_openhome_net_core_InitParams_OhNetInitParamsNumInvocations
  (JNIEnv *env, jobject obj, jlong ptr)
{
	int numInvocations = OhNetInitParamsNumInvocations((OhNetHandleInitParams) ptr);
	
	return (jint) numInvocations;
}

JNIEXPORT jint JNICALL Java_openhome_net_core_InitParams_OhNetInitParamsNumSubscriberThreads
  (JNIEnv *env, jobject obj, jlong ptr)
{
	int numThreads = OhNetInitParamsNumSubscriberThreads((OhNetHandleInitParams) ptr);
	
	return (jint) numThreads;
}