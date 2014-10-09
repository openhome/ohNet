#include <jni.h>
#include <stdio.h>
#include "PropertyCallback.h"
#include "PropertyInt.h"
#include "OpenHome/Net/C/OhNet.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_PropertyInt
 * Method:    ServicePropertyCreateIntCp
 * Signature: (Ljava/lang/String;Lorg/openhome/net/controlpoint/IPropertyChangeListener;)Lorg/openhome/net/core/Property/PropertyInitialised;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_core_PropertyInt_ServicePropertyCreateIntCp
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
	
	property = ServicePropertyCreateIntCp(name, callback, ref);
	propertyInit = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, (jlong)(size_t)property, (jlong)(size_t)ref);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return propertyInit;
}

/*
 * Class:     org_openhome_net_core_PropertyInt
 * Method:    ServicePropertyCreateIntDv
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_PropertyInt_ServicePropertyCreateIntDv
  (JNIEnv *aEnv, jclass aClass, jlong aParameter)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	ServiceProperty property = ServicePropertyCreateIntDv(param);
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) (size_t)property;
}

/*
 * Class:     org_openhome_net_core_PropertyInt
 * Method:    ServicePropertyValueInt
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_PropertyInt_ServicePropertyValueInt
  (JNIEnv *aEnv, jclass aClass, jlong aProperty)
{
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
	int32_t val = 0;
    int32_t result;
    aClass = aClass;

    result = ServicePropertyValueInt(property, &val);
    if (result != 0) {
        jclass errorClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/core/PropertyError");
        if (errorClass == NULL) {
            printf("Unable to find class org/openhome/net/core/PropertyError\n");
        } else {
            (*aEnv)->ThrowNew(aEnv, errorClass, "Value not available");
        }
    }

    return (jint)val;
}	

/*
 * Class:     org_openhome_net_core_PropertyInt
 * Method:    ServicePropertySetValueInt
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_PropertyInt_ServicePropertySetValueInt
  (JNIEnv *aEnv, jclass aClass, jlong aProperty, jint aValue)
{
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jint) ServicePropertySetValueInt(property, aValue);
}

#ifdef __cplusplus
}
#endif
