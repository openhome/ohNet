#include <jni.h>
#include "PropertyCallback.h"
#include "PropertyString.h"
#include "OpenHome/Net/C/Ohnet.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_PropertyString
 * Method:    ServicePropertyCreateStringCp
 * Signature: (Ljava/lang/String;Lorg/openhome/net/controlpoint/IPropertyChangeListener;)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_PropertyString_ServicePropertyCreateStringCp
  (JNIEnv *aEnv, jclass aClass, jstring aName, jobject aListener)
{
	OhNetCallback callback = &ChangeCallback;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	ServiceProperty property;
	JniObjRef *ref;
	aClass = aClass;

	InitialiseReferences(aEnv, aListener, &ref);

	property = ServicePropertyCreateStringCp(name, callback, ref);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return (jlong) property;
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
	
	return (jlong) property;
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
