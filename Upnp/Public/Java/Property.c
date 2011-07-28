#include <jni.h>
#include <malloc.h>
#include <stdlib.h>
#include "Property.h"
#include "JniCallbackList.h"
#include "C/Ohnet.h"
#include "C/Service.h"

JniCallbackList *iList = NULL;

static void STDCALL changeCallback(void* aPtr) {

	JniObjRef* ref = (JniObjRef*) aPtr;
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	jint ret;
	
	ret = (*(ref->vm))->AttachCurrentThread(ref->vm, (void **) &env, NULL);
	if (ret < 0)
	{
		printf("PropertyJNI: Unable to attach thread to JVM.\n");
		fflush(stdout);
		return;
	}
	cls = (*env)->GetObjectClass(env, ref->callbackObj);
	mid = (*env)->GetMethodID(env, cls, "changed", "()V");
	if (mid == 0) {
		printf("PropertyJNI: Method ID changed() not found.\n");
		return;
	}
	(*env)->CallVoidMethod(env, ref->callbackObj, mid);
	
	(*(ref->vm))->DetachCurrentThread(ref->vm);
}

static void STDCALL InitialiseReferences(JNIEnv *aEnv, jobject aObject, JniObjRef **aRef)
{
	jint ret;

	*aRef = (JniObjRef*) malloc(sizeof(JniObjRef));
	if (!iList)
	{
		iList = JniCallbackListCreate();
	}

	ret = (*aEnv)->GetJavaVM(aEnv, &(*aRef)->vm);
	if (ret < 0) {
		printf("PropertyJNI: Unable to get reference to the current Java VM.\n");
		fflush(stdout);
	}
	(*aRef)->callbackObj = (*aEnv)->NewWeakGlobalRef(aEnv, aObject);
	if ((*aRef)->callbackObj == NULL) {
		printf("PropertyJNI: Callback object not stored.\n");
		fflush(stdout);
	}
	JniCallbackListAddElement(&iList, *aRef);
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ohnet_Property_ServicePropertyDestroy
  (JNIEnv *env, jobject obj, jlong propertyPtr)
{
	ServiceProperty property = (ServiceProperty) (size_t)propertyPtr;
	obj = obj;
	
	JniCallbackListDestroy(env, &iList);
	iList = NULL;
	ServicePropertyDestroy(property);
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertyCreateIntCp
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_ohnet_Property_ServicePropertyCreateIntCp
  (JNIEnv *env, jobject obj, jstring name)
{
	OhNetCallback callback = (OhNetCallback) &changeCallback;
	const char* nativeName = (*env)->GetStringUTFChars(env, name, NULL);
	ServiceProperty property;
	JniObjRef *ref;

	InitialiseReferences(env, obj, &ref);

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
	ServiceParameter param = (ServiceParameter) (size_t)parameterPtr;
	ServiceProperty property = ServicePropertyCreateIntDv(param);
	env = env;
	obj = obj;
	
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
	OhNetCallback callback = (OhNetCallback) &changeCallback;
	const char* nativeName = (*env)->GetStringUTFChars(env, name, NULL);
	ServiceProperty property;
	JniObjRef *ref;

	InitialiseReferences(env, obj, &ref);

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
	ServiceParameter param = (ServiceParameter) (size_t)parameterPtr;
	ServiceProperty property = ServicePropertyCreateUintDv(param);
	env = env;
	obj = obj;
	
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
	OhNetCallback callback = (OhNetCallback) &changeCallback;
	const char* nativeName = (*env)->GetStringUTFChars(env, name, NULL);
	ServiceProperty property;
	JniObjRef *ref;

	InitialiseReferences(env, obj, &ref);

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
	ServiceParameter param = (ServiceParameter) (size_t)parameterPtr;
	ServiceProperty property = ServicePropertyCreateBoolDv(param);
	env = env;
	obj = obj;
	
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
	OhNetCallback callback = (OhNetCallback) &changeCallback;
	const char* nativeName = (*env)->GetStringUTFChars(env, name, NULL);
	ServiceProperty property;
	JniObjRef *ref;

	InitialiseReferences(env, obj, &ref);

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
	ServiceParameter param = (ServiceParameter) (size_t)parameterPtr;
	ServiceProperty property = ServicePropertyCreateStringDv(param);
	env = env;
	obj = obj;
	
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
	OhNetCallback callback = (OhNetCallback) &changeCallback;
	const char* nativeName = (*env)->GetStringUTFChars(env, name, NULL);
	ServiceProperty property;
	JniObjRef *ref;

	InitialiseReferences(env, obj, &ref);

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
	ServiceParameter param = (ServiceParameter) (size_t)parameterPtr;
	ServiceProperty property = ServicePropertyCreateBinaryDv(param);
	env = env;
	obj = obj;
	
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
	ServiceParameter param = (ServiceParameter) (size_t)parameterPtr;
	env = env;
	obj = obj;
	
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
	ServiceParameter param = (ServiceParameter) (size_t)parameterPtr;
	env = env;
	obj = obj;
	
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
	ServiceParameter param = (ServiceParameter) (size_t)parameterPtr;
	env = env;
	obj = obj;
	
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
	ServiceParameter param = (ServiceParameter) (size_t)parameterPtr;
	const char* value = ServicePropertyValueString(param);
	env = env;
	obj = obj;
	
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
	ServiceParameter param = (ServiceParameter) (size_t)parameterPtr;
	const uint8_t* data;
	uint32_t len;
	jbyteArray array;
	obj = obj;
	
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
	ServiceProperty property = (ServiceProperty) (size_t)propertyPtr;
	env = env;
	obj = obj;
	
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
	ServiceProperty property = (ServiceProperty) (size_t)propertyPtr;
	env = env;
	obj = obj;
	
	return (jint) ServicePropertySetValueUint(property, (uint32_t)value);
}

/*
 * Class:     ohnet_Property
 * Method:    ServicePropertySetValueBool
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_ohnet_Property_ServicePropertySetValueBool
  (JNIEnv *env, jobject obj, jlong propertyPtr, jlong value)
{
	ServiceProperty property = (ServiceProperty) (size_t)propertyPtr;
	env = env;
	obj = obj;
	
	return (jint) ServicePropertySetValueBool(property, (uint32_t)value);
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
	ServiceProperty property = (ServiceProperty) (size_t)propertyPtr;
	jint result;
	obj = obj;
	
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
  (JNIEnv *env, jobject obj, jlong propertyPtr, jbyteArray array, jint len)
{
	ServiceProperty property = (ServiceProperty) (size_t)propertyPtr;
	uint8_t *data;
	jint result;
	obj = obj;
	
	(*env)->GetByteArrayRegion(env, array, 0, len, (jbyte *) &data);
	
	result = ServicePropertySetValueBinary(property, data, len);
	
	return result;
}
