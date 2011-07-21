#include <jni.h>
#include <malloc.h>
#include <stdlib.h>
#include "Property.h"
#include "C/Ohnet.h"
#include "C/Service.h"

typedef struct{
	JavaVM *vm;
	jweak callbackObj;
} jniObjRef;

//jniObjRef *ref = NULL; // If not using this must destroy local references somewhere!

//typedef jlong (*PropertyCreate)(const char* aName, OhNetCallback aCallback, void* aPtr);

void changeCallback(void* aPtr) {

	jniObjRef* ref = (jniObjRef*) aPtr;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	jint ret;
	
	ret = (*(ref->vm))->AttachCurrentThread(ref->vm, (void **) &env, NULL);
	if (ret < 0)
		printf("Unable to attach thread to JVM.\n");
	
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "changed", "()V");
	if (mid == 0) {
		printf("Method ID changed() not found.\n");
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackObj, mid);
	
	(*(ref->vm))->DetachCurrentThread(ref->vm);
}

void initialiseReferences(JNIEnv *env, jobject obj, jniObjRef **ref)
{
	jint vmCount;
	jint ret;

	/*ret = (*env)->GetJavaVM(env, &(ref->vm));
	if (ret < 0) {
		printf("Unable to get reference to the current Java VM.\n");
	}*/
	*ref = (jniObjRef*) malloc(sizeof(jniObjRef));

	ret = JNI_GetCreatedJavaVMs(&((*ref)->vm), 1, &vmCount);
//	printf("Number of virtual machines found: %d\n", vmCount);
	(*ref)->callbackObj = (*env)->NewWeakGlobalRef(env, obj);
	/*if (callbackObj == NULL) {
		printf("Callback object not stored.\n");
	} else {
		printf("Callback object successfully stored.\n");
	}*/
}

/*jlong ServicePropertyCreateCp(JNIEnv *env, jobject obj, jstring name, PropertyCreate funcPtr)
{
	OhNetCallback callback = &changeCallback;
	const char* nativeName = (*env)->GetStringUTFChars(env, name, NULL);
	ServiceProperty property;

	initialiseReferences(env, obj);

	property = funcPtr(nativeName, callback, ref);
	
	(*env)->ReleaseStringUTFChars(env, name, nativeName);
	
	return (jlong) property;
}*/

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ohnet_Property_ServicePropertyDestroy
  (JNIEnv *env, jobject obj, jlong propertyPtr)
{
	ServiceProperty property = (ServiceProperty) propertyPtr;
	
	ServicePropertyDestroy(property);
//	free(ref);
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyCreateIntCp
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_ohnet_Property_ServicePropertyCreateIntCp
  (JNIEnv *env, jobject obj, jstring name)
{
	OhNetCallback callback = &changeCallback;
	const char* nativeName = (*env)->GetStringUTFChars(env, name, NULL);
	ServiceProperty property;
	jniObjRef *ref;

	initialiseReferences(env, obj, &ref);

	property = ServicePropertyCreateIntCp(nativeName, callback, ref);
	
	(*env)->ReleaseStringUTFChars(env, name, nativeName);
	
	return (jlong) property;
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyCreateIntDv
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_ohnet_Property_ServicePropertyCreateIntDv
  (JNIEnv *env, jobject obj, jlong parameterPtr)
{
	ServiceParameter param = (ServiceParameter) parameterPtr;
	
	ServiceProperty property = ServicePropertyCreateIntDv(param);
	
	return (jlong) property;
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyCreateUintCp
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_ohnet_Property_ServicePropertyCreateUintCp
  (JNIEnv *env, jobject obj, jstring name)
{
	OhNetCallback callback = &changeCallback;
	const char* nativeName = (*env)->GetStringUTFChars(env, name, NULL);
	ServiceProperty property;
	jniObjRef *ref;

	initialiseReferences(env, obj, &ref);

	property = ServicePropertyCreateUintCp(nativeName, callback, ref);
	
	(*env)->ReleaseStringUTFChars(env, name, nativeName);
	
	return (jlong) property;
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyCreateUintDv
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_ohnet_Property_ServicePropertyCreateUintDv
  (JNIEnv *env, jobject obj, jlong parameterPtr)
{
	ServiceParameter param = (ServiceParameter) parameterPtr;
	
	ServiceProperty property = ServicePropertyCreateUintDv(param);
	
	return (jlong) property;
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyCreateBoolCp
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_ohnet_Property_ServicePropertyCreateBoolCp
  (JNIEnv *env, jobject obj, jstring name)
{
	OhNetCallback callback = &changeCallback;
	const char* nativeName = (*env)->GetStringUTFChars(env, name, NULL);
	ServiceProperty property;
	jniObjRef *ref;

	initialiseReferences(env, obj, &ref);

	property = ServicePropertyCreateBoolCp(nativeName, callback, ref);
	
	(*env)->ReleaseStringUTFChars(env, name, nativeName);
	
	return (jlong) property;
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyCreateBoolDv
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_ohnet_Property_ServicePropertyCreateBoolDv
  (JNIEnv *env, jobject obj, jlong parameterPtr)
{
	ServiceParameter param = (ServiceParameter) parameterPtr;
	
	ServiceProperty property = ServicePropertyCreateBoolDv(param);
	
	return (jlong) property;
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyCreateStringCp
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_ohnet_Property_ServicePropertyCreateStringCp
  (JNIEnv *env, jobject obj, jstring name)
{
	OhNetCallback callback = &changeCallback;
	const char* nativeName = (*env)->GetStringUTFChars(env, name, NULL);
	ServiceProperty property;
	jniObjRef *ref;

	initialiseReferences(env, obj, &ref);

	property = ServicePropertyCreateStringCp(nativeName, callback, ref);
	
	(*env)->ReleaseStringUTFChars(env, name, nativeName);
	
	return (jlong) property;
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyCreateStringDv
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_ohnet_Property_ServicePropertyCreateStringDv
  (JNIEnv *env, jobject obj, jlong parameterPtr)
{
	ServiceParameter param = (ServiceParameter) parameterPtr;
	
	ServiceProperty property = ServicePropertyCreateStringDv(param);
	
	return (jlong) property;
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyCreateBinaryCp
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_ohnet_Property_ServicePropertyCreateBinaryCp
  (JNIEnv *env, jobject obj, jstring name)
{
	OhNetCallback callback = &changeCallback;
	const char* nativeName = (*env)->GetStringUTFChars(env, name, NULL);
	ServiceProperty property;
	jniObjRef *ref;

	initialiseReferences(env, obj, &ref);

	property = ServicePropertyCreateBinaryCp(nativeName, callback, ref);
	
	(*env)->ReleaseStringUTFChars(env, name, nativeName);
	
	return (jlong) property;
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyCreateBinaryDv
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_ohnet_Property_ServicePropertyCreateBinaryDv
  (JNIEnv *env, jobject obj, jlong parameterPtr)
{
	ServiceParameter param = (ServiceParameter) parameterPtr;
	
	ServiceProperty property = ServicePropertyCreateBinaryDv(param);
	
	return (jlong) property;
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyValueInt
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_ohnet_Property_ServicePropertyValueInt
  (JNIEnv *env, jobject obj, jlong parameterPtr)
{
	ServiceParameter param = (ServiceParameter) parameterPtr;
	
	return (jint) ServicePropertyValueInt(param);
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyValueUint
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_ohnet_Property_ServicePropertyValueUint
  (JNIEnv *env, jobject obj, jlong parameterPtr)
{
	ServiceParameter param = (ServiceParameter) parameterPtr;
	
	return (jlong) ServicePropertyValueUint(param);
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyValueBool
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_ohnet_Property_ServicePropertyValueBool
  (JNIEnv *env, jobject obj, jlong parameterPtr)
{
	ServiceParameter param = (ServiceParameter) parameterPtr;
	
	return (jint) ServicePropertyValueBool(param);
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyValueString
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ohnet_Property_ServicePropertyValueString
  (JNIEnv *env, jobject obj, jlong parameterPtr)
{
	ServiceParameter param = (ServiceParameter) parameterPtr;
	
	const char* value = ServicePropertyValueString(param);
	
	return ((*env)->NewStringUTF(env, value));
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyGetValueBinary
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_ohnet_Property_ServicePropertyGetValueBinary
  (JNIEnv *env, jobject obj, jlong parameterPtr)
{
	ServiceParameter param = (ServiceParameter) parameterPtr;
	const uint8_t* data;
	uint32_t len;
	jbyteArray array;
	
	ServicePropertyGetValueBinary(param, &data, &len);
	
	array = (*env)->NewByteArray(env, len);
	(*env)->SetByteArrayRegion(env, array, 0, len, (jbyte *) data);
	
	return array;
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertySetValueInt
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_ohnet_Property_ServicePropertySetValueInt
  (JNIEnv *env, jobject obj, jlong propertyPtr, jint value)
{
	ServiceProperty property = (ServiceProperty) propertyPtr;
	
	return (jint) ServicePropertySetValueInt(property, value);
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertySetValueUint
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_ohnet_Property_ServicePropertySetValueUint
  (JNIEnv *env, jobject obj, jlong propertyPtr, jlong value)
{
	ServiceProperty property = (ServiceProperty) propertyPtr;
	
	return (jint) ServicePropertySetValueUint(property, value);
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertySetValueBool
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_ohnet_Property_ServicePropertySetValueBool
  (JNIEnv *env, jobject obj, jlong propertyPtr, jlong value)
{
	ServiceProperty property = (ServiceProperty) propertyPtr;
	
	return (jint) ServicePropertySetValueBool(property, value);
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertySetValueString
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_ohnet_Property_ServicePropertySetValueString
  (JNIEnv *env, jobject obj, jlong propertyPtr, jstring value)
{
	const char* nativeValue = (*env)->GetStringUTFChars(env, value, NULL);
	ServiceProperty property = (ServiceProperty) propertyPtr;
	jint result;
	
	result = ServicePropertySetValueString(property, nativeValue);
	
	(*env)->ReleaseStringUTFChars(env, value, nativeValue);
	
	return result;
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertySetValueBinary
 * Signature: (JBJ)I
 */
JNIEXPORT jint JNICALL Java_ohnet_Property_ServicePropertySetValueBinary
  (JNIEnv *env, jobject obj, jlong propertyPtr, jbyteArray array, jlong len)
{
	ServiceProperty property = (ServiceProperty) propertyPtr;
	uint8_t *data;
	jint result;
	
	(*env)->GetByteArrayRegion(env, array, 0, len, (jbyte *) &data);
	
	result = ServicePropertySetValueBinary(property, data, len);
	
	return result;
}
