#include <jni.h>
#include <stdio.h>
#include "PropertyCallback.h"
#include "PropertyString.h"
#include "OpenHome/Net/C/OhNet.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_PropertyString
 * Method:    ServicePropertyCreateStringCp
 * Signature: (Ljava/lang/String;Lorg/openhome/net/controlpoint/IPropertyChangeListener;)Lorg/openhome/net/core/Property/PropertyInitialised;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_core_PropertyString_ServicePropertyCreateStringCp
  (JNIEnv *aEnv, jobject aObject, jstring aName, jobject aListener)
{
	OhNetCallback callback = &ChangeCallback;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	ServiceProperty property;
	JniObjRef *ref;
	jclass statusClass;
	jmethodID cid;
	jobject propertyInit;

	InitialiseReferences(aEnv, aListener, &ref);

	statusClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/core/Property$PropertyInitialised");
	if (statusClass == NULL)
	{
		printf("Unable to find class org/openhome/net/core/Property$PropertyInitialised\n");
		return NULL;
	}
	cid = (*aEnv)->GetMethodID(aEnv, statusClass, "<init>", "(Lorg/openhome/net/core/Property;JJ)V");
	if (cid == NULL) {
		printf("Unable to find constructor for class org/openhome/net/core/Property$PropertyInitialised\n");
        return NULL;
	}
	
	property = ServicePropertyCreateStringCp(name, callback, ref);
	propertyInit = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, (jlong)(size_t)property, (jlong)(size_t)ref);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return propertyInit;
}

/*
 * Class:     org_openhome_net_core_PropertyString
 * Method:    ServicePropertyCreateStringDv
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_PropertyString_ServicePropertyCreateStringDv
  (JNIEnv *aEnv, jclass aClass, jlong aParameter)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	ServiceProperty property = ServicePropertyCreateStringDv(param);
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) (size_t)property;
}

/*
 * Class:     org_openhome_net_core_PropertyString
 * Method:    ServicePropertyValueString
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_openhome_net_core_PropertyString_ServicePropertyValueString
  (JNIEnv *aEnv, jclass aClass, jlong aProperty)
{
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
    jclass stringClass;
    jmethodID cidString;
    const char* value;
    uint32_t len;
    jbyteArray byteArray;
    jstring utf8;
    jstring valueJava;
    int result;
    aClass = aClass;

    result = ServicePropertyGetValueString(property, &value, &len);
    if (result == 0) {
        stringClass = (*aEnv)->FindClass(aEnv, "java/lang/String");
        if (stringClass == NULL) {
            printf("Unable to find class java/lang/String\n");
            return NULL;
        }
        cidString = (*aEnv)->GetMethodID(aEnv, stringClass, "<init>", "([BLjava/lang/String;)V");
        if (cidString == NULL) {
            printf("Unable to find constructor for class java/lang/String\n");
            return NULL;
        }
        byteArray = (*aEnv)->NewByteArray(aEnv, len);
        (*aEnv)->SetByteArrayRegion(aEnv, byteArray, 0, len, (jbyte *) value);
        utf8 = (*aEnv)->NewStringUTF(aEnv, "UTF-8");
        valueJava = (*aEnv)->NewObject(aEnv, stringClass, cidString, byteArray, utf8);
    }
    else {
        jclass errorClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/core/PropertyError");
        if (errorClass == NULL) {
            printf("Unable to find class org/openhome/net/core/PropertyError\n");
        }
        else {
            (*aEnv)->ThrowNew(aEnv, errorClass, "Value not available");
        }
        return NULL;
    }

    return valueJava;
}

/*
 * Class:     org_openhome_net_core_PropertyString
 * Method:    ServicePropertySetValueString
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_PropertyString_ServicePropertySetValueString
  (JNIEnv *aEnv, jclass aClass, jlong aProperty, jstring aValue)
{
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
	jint result;
    jclass cls = (*aEnv)->GetObjectClass(aEnv, aValue); // local ref will be deleted when method returns
    jmethodID mid;
    jstring utf8;
    jbyteArray byteArray;
    jbyte *data;
    jsize len;
    aClass = aClass;

    mid = (*aEnv)->GetMethodID(aEnv, cls, "getBytes", "(Ljava/lang/String;)[B");
    if (mid == 0) {
        printf("PropertyStringJNI: Method ID \"getBytes()\" not found.\n");
        fflush(stdout);
        return 1; // error
    }
    utf8 = (*aEnv)->NewStringUTF(aEnv, "UTF-8");
    byteArray = (*aEnv)->CallObjectMethod(aEnv, aValue, mid, utf8);
    len = (*aEnv)->GetArrayLength(aEnv, byteArray);
    data = (*aEnv)->GetByteArrayElements(aEnv, byteArray, NULL);
    result = ServicePropertySetValueStringAsBuffer(property, (char *)data, len);
    (*aEnv)->ReleaseByteArrayElements(aEnv, byteArray, data, JNI_ABORT);

    return result;
}

#ifdef __cplusplus
}
#endif
