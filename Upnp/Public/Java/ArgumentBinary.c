#include <jni.h>
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
	ServiceParameter param = (ServiceParameter) paramPtr;
	ActionArgument arg;
	uint8_t *data;
	jint result;
	
	(*env)->GetByteArrayRegion(env, array, 0, len, (jbyte *) &data);
	
	arg = ActionArgumentCreateBinaryInput(param, data, len);
	
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
	ServiceParameter param = (ServiceParameter) paramPtr;
	
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
	ServiceParameter param = (ServiceParameter) paramPtr;
	const uint8_t* data;
	uint32_t len;
	jbyteArray array;
	
	ServicePropertyGetValueBinary(param, &data, &len);
	
	array = (*env)->NewByteArray(env, len);
	(*env)->SetByteArrayRegion(env, array, 0, len, (jbyte *) data);
	
	return array;
}

#ifdef __cplusplus
}
#endif
