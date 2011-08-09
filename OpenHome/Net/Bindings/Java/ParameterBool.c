#include <jni.h>
#include "ParameterBool.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_ParameterBool
 * Method:    ServiceParameterCreateBool
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_ParameterBool_ServiceParameterCreateBool
  (JNIEnv *aEnv, jclass aClass, jstring aName)
{
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	ServiceParameter param = ServiceParameterCreateBool(name);
	aClass = aClass;
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return (jlong) (size_t)param;
}

#ifdef __cplusplus
}
#endif
