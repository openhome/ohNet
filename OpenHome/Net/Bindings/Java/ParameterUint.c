#include <jni.h>
#include "ParameterUint.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     org_openhome_net_core_ParameterUint
 * Method:    ServiceParameterCreateUint
 * Signature: (Ljava/lang/String;JJJ)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_ParameterUint_ServiceParameterCreateUint
  (JNIEnv *aEnv, jclass aClass, jstring aName, jlong aMinValue, jlong aMaxValue, jlong aStep)
{
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	ServiceParameter param = ServiceParameterCreateUint(name, (uint32_t)aMinValue, (uint32_t)aMaxValue, (uint32_t)aStep);
	aClass = aClass;
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return (jlong) (size_t)param;
}

#ifdef __cplusplus
}
#endif
