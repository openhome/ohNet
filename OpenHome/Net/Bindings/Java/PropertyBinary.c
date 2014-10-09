#include <jni.h>
#include <stdio.h>
#include "PropertyCallback.h"
#include "PropertyBinary.h"
#include "OpenHome/Net/C/OhNet.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_PropertyBinary
 * Method:    ServicePropertyCreateBinaryCp
 * Signature: (Ljava/lang/String;Lorg/openhome/net/controlpoint/IPropertyChangeListener;)Lorg/openhome/net/core/Property/PropertyInitialised;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_core_PropertyBinary_ServicePropertyCreateBinaryCp
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
	
	property = ServicePropertyCreateBinaryCp(name, callback, ref);
	propertyInit = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, (jlong)(size_t)property, (jlong)(size_t)ref);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return propertyInit;
}

/*
 * Class:     org_openhome_net_core_PropertyBinary
 * Method:    ServicePropertyCreateBinaryDv
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_PropertyBinary_ServicePropertyCreateBinaryDv
  (JNIEnv *aEnv, jclass aClass, jlong aParameter)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	ServiceProperty property = ServicePropertyCreateBinaryDv(param);
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) (size_t)property;
}

/*
 * Class:     org_openhome_net_core_PropertyBinary
 * Method:    ServicePropertyGetValueBinary
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_openhome_net_core_PropertyBinary_ServicePropertyGetValueBinary
  (JNIEnv *aEnv, jclass aClass, jlong aProperty)
{
	ServiceProperty property = (ServiceParameter) (size_t)aProperty;
	const uint8_t* data;
	uint32_t len;
	jbyteArray array;
    jint result;
	aClass = aClass;

	ServicePropertyGetValueBinary(property, &data, &len);
    result = ServicePropertyGetValueBinary(property, &data, &len);

	array = (*aEnv)->NewByteArray(aEnv, len);
	(*aEnv)->SetByteArrayRegion(aEnv, array, 0, len, (jbyte *)data);
    if (result == 0) {
        array = (*aEnv)->NewByteArray(aEnv, len);
        (*aEnv)->SetByteArrayRegion(aEnv, array, 0, len, (jbyte *)data);
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

	return array;
}

/*
 * Class:     org_openhome_net_core_PropertyBinary
 * Method:    ServicePropertySetValueBinary
 * Signature: (J[BI)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_PropertyBinary_ServicePropertySetValueBinary
  (JNIEnv *aEnv, jclass aClass, jlong aProperty, jbyteArray aData, jint aLen)
{
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
	uint8_t *data = (uint8_t*)malloc(sizeof(uint8_t)*aLen);
	jint result;
	aClass = aClass;
	
	(*aEnv)->GetByteArrayRegion(aEnv, aData, 0, aLen, (jbyte *)data);
	
	result = ServicePropertySetValueBinary(property, data, aLen);
	free(data);
	
	return result;
}

#ifdef __cplusplus
}
#endif
