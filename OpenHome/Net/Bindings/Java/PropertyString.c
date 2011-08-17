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
	const char* value = ServicePropertyValueString(property);
	aEnv = aEnv;
	aClass = aClass;
	
	return ((*aEnv)->NewStringUTF(aEnv, value));
}

/*
 * Class:     org_openhome_net_core_PropertyString
 * Method:    ServicePropertySetValueString
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_PropertyString_ServicePropertySetValueString
  (JNIEnv *aEnv, jclass aClass, jlong aProperty, jstring aValue)
{
	const char* value = (*aEnv)->GetStringUTFChars(aEnv, aValue, NULL);
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
	jint result;
	aClass = aClass;
	
	result = ServicePropertySetValueString(property, value);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aValue, value);
	
	return result;
}

#ifdef __cplusplus
}
#endif
