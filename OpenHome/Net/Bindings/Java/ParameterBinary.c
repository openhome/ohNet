#include <jni.h>
#include "ParameterBinary.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_ParameterBinary
 * Method:    ServiceParameterCreateBinary
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_ParameterBinary_ServiceParameterCreateBinary
  (JNIEnv *aEnv, jclass aClass, jstring aName)
{
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	ServiceParameter param = ServiceParameterCreateBinary(name);
	aClass = aClass;
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return (jlong) (size_t)param;
}	

#ifdef __cplusplus
}
#endif
