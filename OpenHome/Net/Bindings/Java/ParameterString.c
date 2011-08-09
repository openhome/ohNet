#include <jni.h>
#include <malloc.h>
#include <stdlib.h>
#include "ParameterString.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_ParameterString
 * Method:    ServiceParameterCreateString
 * Signature: (Ljava/lang/String;[Ljava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_ParameterString_ServiceParameterCreateString
  (JNIEnv *aEnv, jclass aClass, jstring aName, jobjectArray aAllowedValues, jint aCount)
{
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	char** allowed = (char**) malloc(aCount * sizeof(char *));
	ServiceParameter param;
	int i;
	aClass = aClass;
	
	
	for (i = 0; i < aCount; i++)
	{
		jstring allowedString = (*aEnv)->GetObjectArrayElement(aEnv, aAllowedValues, i);
		const char* nativeAllowedString = (*aEnv)->GetStringUTFChars(aEnv, allowedString, NULL);
		allowed[i] = (char *) nativeAllowedString;
		(*aEnv)->ReleaseStringUTFChars(aEnv, allowedString, allowed[i]);
	}

	param = ServiceParameterCreateString(name, allowed, aCount);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	free(allowed);
	
	return (jlong) (size_t)param;
}

#ifdef __cplusplus
}
#endif
