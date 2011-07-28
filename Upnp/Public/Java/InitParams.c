#include <jni.h>
#include <stddef.h>
#include "InitParams.h"
#include "C/OhNet.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_InitParams
 * Method:    OhNetInitParamsCreate
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_InitParams_OhNetInitParamsCreate
  (JNIEnv *aEnv, jclass aClass)
{
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) OhNetInitParamsCreate();
}

/*
 * Class:     org_openhome_net_core_InitParams
 * Method:    OhNetInitParamsDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_InitParams_OhNetInitParamsDestroy
  (JNIEnv *aEnv, jclass aClass, jlong aParams)
{
	OhNetHandleInitParams params = (OhNetHandleInitParams) (size_t)aParams;
	aEnv = aEnv;
	aClass = aClass;
	
	OhNetInitParamsDestroy(params);
}

/*
 * Class:     org_openhome_net_core_InitParams
 * Method:    OhNetInitParamsTcpConnectTimeoutMs
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_InitParams_OhNetInitParamsTcpConnectTimeoutMs
  (JNIEnv *aEnv, jclass aClass, jlong aParams)
{
	OhNetHandleInitParams params = (OhNetHandleInitParams) (size_t)aParams;
	aEnv = aEnv;
	aClass = aClass;
	
	return OhNetInitParamsTcpConnectTimeoutMs(params);
}

/*
 * Class:     org_openhome_net_core_InitParams
 * Method:    OhNetInitParamsMsearchTimeSecs
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_InitParams_OhNetInitParamsMsearchTimeSecs
  (JNIEnv *aEnv, jclass aClass, jlong aParams)
{
	OhNetHandleInitParams params = (OhNetHandleInitParams) (size_t)aParams;
	aEnv = aEnv;
	aClass = aClass;
	
	return OhNetInitParamsMsearchTimeSecs(params);
}

/*
 * Class:     org_openhome_net_core_InitParams
 * Method:    OhNetInitParamsMsearchTtl
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_InitParams_OhNetInitParamsMsearchTtl
  (JNIEnv *aEnv, jclass aClass, jlong aParams)
{
	OhNetHandleInitParams params = (OhNetHandleInitParams) (size_t)aParams;
	aEnv = aEnv;
	aClass = aClass;
	
	return OhNetInitParamsMsearchTtl(params);
}

/*
 * Class:     org_openhome_net_core_InitParams
 * Method:    OhNetInitParamsNumEventSessionThreads
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_InitParams_OhNetInitParamsNumEventSessionThreads
  (JNIEnv *aEnv, jclass aClass, jlong aParams)
{
	OhNetHandleInitParams params = (OhNetHandleInitParams) (size_t)aParams;
	aEnv = aEnv;
	aClass = aClass;
	
	return OhNetInitParamsNumEventSessionThreads(params);
}

/*
 * Class:     org_openhome_net_core_InitParams
 * Method:    OhNetInitParamsNumXmlFetcherThreads
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_InitParams_OhNetInitParamsNumXmlFetcherThreads
  (JNIEnv *aEnv, jclass aClass, jlong aParams)
{
	OhNetHandleInitParams params = (OhNetHandleInitParams) (size_t)aParams;
	aEnv = aEnv;
	aClass = aClass;
	
	return OhNetInitParamsNumXmlFetcherThreads(params);
}

/*
 * Class:     org_openhome_net_core_InitParams
 * Method:    OhNetInitParamsNumActionInvokerThreads
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_InitParams_OhNetInitParamsNumActionInvokerThreads
  (JNIEnv *aEnv, jclass aClass, jlong aParams)
{
	OhNetHandleInitParams params = (OhNetHandleInitParams) (size_t)aParams;
	aEnv = aEnv;
	aClass = aClass;
	
	return OhNetInitParamsNumActionInvokerThreads(params);
}

/*
 * Class:     org_openhome_net_core_InitParams
 * Method:    OhNetInitParamsNumInvocations
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_InitParams_OhNetInitParamsNumInvocations
  (JNIEnv *aEnv, jclass aClass, jlong aParams)
{
	OhNetHandleInitParams params = (OhNetHandleInitParams) (size_t)aParams;
	aEnv = aEnv;
	aClass = aClass;
	
	return OhNetInitParamsNumInvocations(params);
}

/*
 * Class:     org_openhome_net_core_InitParams
 * Method:    OhNetInitParamsNumSubscriberThreads
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_InitParams_OhNetInitParamsNumSubscriberThreads
  (JNIEnv *aEnv, jclass aClass, jlong aParams)
{
	OhNetHandleInitParams params = (OhNetHandleInitParams) (size_t)aParams;
	aEnv = aEnv;
	aClass = aClass;
	
	return OhNetInitParamsNumSubscriberThreads(params);
}

/*
 * Class:     org_openhome_net_core_InitParams
 * Method:    OhNetInitParamsSetMsearchTime
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_InitParams_OhNetInitParamsSetMsearchTime
  (JNIEnv *aEnv, jclass aClass, jlong aParams, jint aSecs)
{
	OhNetHandleInitParams params = (OhNetHandleInitParams) (size_t)aParams;
	aEnv = aEnv;
	aClass = aClass;
	
	OhNetInitParamsSetMsearchTime(params, aSecs);
}

/*
 * Class:     org_openhome_net_core_InitParams
 * Method:    OhNetInitParamsSetUseLoopbackNetworkAdapter
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_InitParams_OhNetInitParamsSetUseLoopbackNetworkAdapter
  (JNIEnv *aEnv, jclass aClass, jlong aParams)
{
	OhNetHandleInitParams params = (OhNetHandleInitParams) (size_t)aParams;
	aEnv = aEnv;
	aClass = aClass;
	
	OhNetInitParamsSetUseLoopbackNetworkAdapter(params);
}

#ifdef __cplusplus
}
#endif
