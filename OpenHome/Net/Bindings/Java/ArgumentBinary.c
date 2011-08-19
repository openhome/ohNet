#include <jni.h>
#include <malloc.h>
#include <stdlib.h>
#include "ArgumentBinary.h"
#include "OpenHome/Net/C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_controlpoint_ArgumentBinary
 * Method:    ActionArgumentCreateBinaryInput
 * Signature: (J[BI)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_ArgumentBinary_ActionArgumentCreateBinaryInput
  (JNIEnv *aEnv, jclass aClass, jlong aParameter, jbyteArray aData, jint aLen)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	ActionArgument arg;
	uint8_t *data = (uint8_t*)malloc(sizeof(uint8_t)*aLen);
	aClass = aClass;

	(*aEnv)->GetByteArrayRegion(aEnv, aData, 0, aLen, (jbyte *)data);
	arg = ActionArgumentCreateBinaryInput(param, data, aLen);
	free(data);
	
	return (jlong) (size_t)arg;
}

/*
 * Class:     org_openhome_net_controlpoint_ArgumentBinary
 * Method:    ActionArgumentCreateBinaryOutput
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_controlpoint_ArgumentBinary_ActionArgumentCreateBinaryOutput
  (JNIEnv *aEnv, jclass aClass, jlong aParameter)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) (size_t)ActionArgumentCreateBinaryOutput(param);
}

/*
 * Class:     org_openhome_net_controlpoint_ArgumentBinary
 * Method:    ActionArgumentGetValueBinary
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_openhome_net_controlpoint_ArgumentBinary_ActionArgumentGetValueBinary
  (JNIEnv *aEnv, jclass aClass, jlong aArgument)
{
	ServiceParameter param = (ServiceParameter) (size_t)aArgument;
	const uint8_t* data;
	uint32_t len;
	jbyteArray array;
	aClass = aClass;
	
	ServicePropertyGetValueBinary(param, &data, &len);
	
	array = (*aEnv)->NewByteArray(aEnv, len);
	(*aEnv)->SetByteArrayRegion(aEnv, array, 0, len, (jbyte *) data);
	
	return array;
}

#ifdef __cplusplus
}
#endif
