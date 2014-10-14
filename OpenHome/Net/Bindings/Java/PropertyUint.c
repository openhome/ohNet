#include <jni.h>
#include <stdio.h>
#include "PropertyCallback.h"
#include "PropertyUint.h"
#include "OpenHome/Net/C/OhNet.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_PropertyUint
 * Method:    ServicePropertyCreateUintCp
 * Signature: (Ljava/lang/String;Lorg/openhome/net/controlpoint/IPropertyChangeListener;)Lorg/openhome/net/core/Property/PropertyInitialised;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_core_PropertyUint_ServicePropertyCreateUintCp
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
	
	property = ServicePropertyCreateUintCp(name, callback, ref);
	propertyInit = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, (jlong)(size_t)property, (jlong)(size_t)ref);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return propertyInit;
}

/*
 * Class:     org_openhome_net_core_PropertyUint
 * Method:    ServicePropertyCreateUintDv
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_PropertyUint_ServicePropertyCreateUintDv
  (JNIEnv *aEnv, jclass aClass, jlong aParameter)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	ServiceProperty property = ServicePropertyCreateUintDv(param);
	aEnv = aEnv;
	aClass = aClass;

	return (jlong) (size_t)property;
}

/*
 * Class:     org_openhome_net_core_PropertyUint
 * Method:    ServicePropertyValueUint
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_PropertyUint_ServicePropertyValueUint
  (JNIEnv *aEnv, jclass aClass, jlong aProperty)
{
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
    uint32_t val = 0;
    int32_t result;
    aClass = aClass;

    result = ServicePropertyValueUint(property, &val);
    if (result != 0) {
        jclass errorClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/core/PropertyError");
        if (errorClass == NULL) {
            printf("Unable to find class org/openhome/net/core/PropertyError\n");
        } else {
            (*aEnv)->ThrowNew(aEnv, errorClass, "Value not available");
        }
    }

    return (jlong)val;
}

/*
 * Class:     org_openhome_net_core_PropertyUint
 * Method:    ServicePropertySetValueUint
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_PropertyUint_ServicePropertySetValueUint
  (JNIEnv *aEnv, jclass aClass, jlong aProperty, jlong aValue)
{
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jint) ServicePropertySetValueUint(property, (uint32_t)aValue);
}

#ifdef __cplusplus
}
#endif
