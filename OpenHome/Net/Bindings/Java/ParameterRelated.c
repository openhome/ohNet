#include <jni.h>
#include "ParameterRelated.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_ParameterRelated
 * Method:    ServiceParameterCreateRelated
 * Signature: (Ljava/lang/String;J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_ParameterRelated_ServiceParameterCreateRelated
  (JNIEnv *aEnv, jclass aClass, jstring aName, jlong aProperty)
{
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
	ServiceParameter param = ServiceParameterCreateRelated(name, property);
	aClass = aClass;
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return (jlong) (size_t)param;
}

#ifdef __cplusplus
}
#endif
