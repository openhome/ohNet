#include <jni.h>
#include <stdio.h>
#include "ArgumentString.h"
#include "OpenHome/Net/C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_ArgumentString
 * Method:    ActionArgumentCreateStringInput
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_ArgumentString_ActionArgumentCreateStringInput
  (JNIEnv *aEnv, jclass aClass, jlong aParameter, jstring aValue)
{
    ServiceParameter param = (ServiceParameter) (size_t)aParameter;
    ActionArgument arg;
    jclass cls = (*aEnv)->GetObjectClass(aEnv, aValue); // local ref will be deleted when method returns
    jmethodID mid;
    jstring utf8;
    jbyteArray byteArray;
    jsize len;
    jbyte *data;
    aClass = aClass;

    mid = (*aEnv)->GetMethodID(aEnv, cls, "getBytes", "(Ljava/lang/String;)[B");
    if (mid == 0) {
        printf("ArgumentStringJNI: Method ID \"getBytes()\" not found.\n");
        fflush(stdout);
        return (jlong) 0; // error
    }
    utf8 = (*aEnv)->NewStringUTF(aEnv, "UTF-8");
    byteArray = (*aEnv)->CallObjectMethod(aEnv, aValue, mid, utf8);

    len = (*aEnv)->GetArrayLength(aEnv, byteArray);
    data = (*aEnv)->GetByteArrayElements(aEnv, byteArray, NULL);
    arg = ActionArgumentCreateStringInputAsBuffer(param, (char *)data, len);
    (*aEnv)->ReleaseByteArrayElements(aEnv, byteArray, data, JNI_ABORT);

    return (jlong) (size_t)arg;
}

/*
 * Class:     org_openhome_net_controlpoint_ArgumentString
 * Method:    ActionArgumentCreateStringOutput
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_ArgumentString_ActionArgumentCreateStringOutput
  (JNIEnv *aEnv, jclass aClass, jlong aParameter)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) (size_t)ActionArgumentCreateStringOutput(param);
}

/*
 * Class:     org_openhome_net_controlpoint_ArgumentString
 * Method:    ActionArgumentValueString
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_openhome_net_controlpoint_ArgumentString_ActionArgumentValueString
  (JNIEnv *aEnv, jclass aClass, jlong aArgument)
{
	ActionArgument arg = (ActionArgument) (size_t)aArgument;
	const char* val = ActionArgumentValueString(arg);
	aClass = aClass;
	
	return ((*aEnv)->NewStringUTF(aEnv, val));
}

#ifdef __cplusplus
}
#endif
