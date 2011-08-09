#include <jni.h>
#include "ParameterInt.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_ParameterInt
 * Method:    ServiceParameterCreateInt
 * Signature: (Ljava/lang/String;III)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_ParameterInt_ServiceParameterCreateInt
  (JNIEnv *aEnv, jclass aClass, jstring aName, jint aMinValue, jint aMaxValue, jint aStep)
{
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	ServiceParameter param = ServiceParameterCreateInt(name, aMinValue, aMaxValue, aStep);
	aClass = aClass;
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return (jlong) (size_t)param;
}

#ifdef __cplusplus
}
#endif
