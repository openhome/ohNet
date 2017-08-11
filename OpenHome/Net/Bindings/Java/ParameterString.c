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
		const char* nativeAllowedString;
		if (allowedString == NULL)
		{
			jclass exc;
			int j;
			for (j = 0; j < i; j++)
			{
				// Free memory before we throw the exception.
				jstring allowedString2 = (*aEnv)->GetObjectArrayElement(aEnv, aAllowedValues, j);
				(*aEnv)->ReleaseStringUTFChars(aEnv, allowedString2, allowed[j]);
			}
            free(allowed);
            exc = (*aEnv)->FindClass(aEnv,
					"java/lang/NullPointerException");
			if (exc == NULL) {
				return 0;
			}
			(*aEnv)->ThrowNew(aEnv, exc, "Allowed values list must not contain null values");
			return 0;
		}
		nativeAllowedString = (*aEnv)->GetStringUTFChars(aEnv, allowedString, NULL);
		allowed[i] = (char *) nativeAllowedString;
	}
    
    param = ServiceParameterCreateString(name, allowed, aCount);

    for (i = 0; i < aCount; i++)
    {
        jstring allowedString = (*aEnv)->GetObjectArrayElement(aEnv, aAllowedValues, i);
        (*aEnv)->ReleaseStringUTFChars(aEnv, allowedString, allowed[i]);
    }

	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	free(allowed);
	
	return (jlong) (size_t)param;
}

#ifdef __cplusplus
}
#endif
