#include <jni.h>
#include <malloc.h>
#include <stdlib.h>
#include "ArgumentBinary.h"
#include "C/CpService.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     openhome_net_controlpoint_ArgumentBinary
 * Method:    ActionArgumentCreateBinaryInput
 * Signature: (J[B)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_ArgumentBinary_ActionArgumentCreateBinaryInput
  (JNIEnv *env, jobject obj, jlong paramPtr, jbyteArray array, jint len)
{
	ServiceParameter param = (ServiceParameter) (size_t)paramPtr;
	ActionArgument arg;
	uint8_t *data = (uint8_t*)malloc(sizeof(uint8_t)*len);
	obj = obj;

	(*env)->GetByteArrayRegion(env, array, 0, len, (jbyte *)data);
	arg = ActionArgumentCreateBinaryInput(param, data, len);
	free(data); // Do we want to do this or does the stack use this reference?
	
	return (jlong) arg;
}

/*
 * Class:     openhome_net_controlpoint_ArgumentBinary
 * Method:    ActionArgumentCreateBinaryOutput
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_openhome_net_controlpoint_ArgumentBinary_ActionArgumentCreateBinaryOutput
  (JNIEnv *env, jobject obj, jlong paramPtr)
{
	ServiceParameter param = (ServiceParameter) (size_t)paramPtr;
	env = env;
	obj = obj;
	
	return (jlong) ActionArgumentCreateBinaryOutput(param);
}

/*
 * Class:     openhome_net_controlpoint_ArgumentBinary
 * Method:    ActionArgumentGetValueBinary
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_openhome_net_controlpoint_ArgumentBinary_ActionArgumentGetValueBinary
  (JNIEnv *env, jobject obj, jlong paramPtr)
{
	ServiceParameter param = (ServiceParameter) (size_t)paramPtr;
	const uint8_t* data;
	uint32_t len;
	jbyteArray array;
	obj = obj;
	
	ServicePropertyGetValueBinary(param, &data, &len);
	
	array = (*env)->NewByteArray(env, len);
	(*env)->SetByteArrayRegion(env, array, 0, len, (jbyte *) data);
	
	return array;
}

#ifdef __cplusplus
}
#endif
