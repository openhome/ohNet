#include <jni.h>
#include "PropertyCallback.h"
#include "PropertyBool.h"
#include "OpenHome/Net/C/Ohnet.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_PropertyBool
 * Method:    ServicePropertyCreateBoolCp
 * Signature: (Ljava/lang/String;Lorg/openhome/net/controlpoint/IPropertyChangeListener;)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_PropertyBool_ServicePropertyCreateBoolCp
  (JNIEnv *aEnv, jclass aClass, jstring aName, jobject aListener)
{
	OhNetCallback callback = &ChangeCallback;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	ServiceProperty property;
	JniObjRef *ref;
	aClass = aClass;

	InitialiseReferences(aEnv, aListener, &ref);

	property = ServicePropertyCreateBoolCp(name, callback, ref);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return (jlong) property;
}

/*
 * Class:     org_openhome_net_core_PropertyBool
 * Method:    ServicePropertyCreateBoolDv
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_PropertyBool_ServicePropertyCreateBoolDv
  (JNIEnv *aEnv, jclass aClass, jlong aParameter)
{
	ServiceParameter param = (ServiceParameter) (size_t)aParameter;
	ServiceProperty property = ServicePropertyCreateBoolDv(param);
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) property;
}

/*
 * Class:     org_openhome_net_core_PropertyBool
 * Method:    ServicePropertyValueBool
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_PropertyBool_ServicePropertyValueBool
  (JNIEnv *aEnv, jclass aClass, jlong aProperty)
{
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jint) ServicePropertyValueBool(property);
}

/*
 * Class:     org_openhome_net_core_PropertyBool
 * Method:    ServicePropertySetValueBool
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_PropertyBool_ServicePropertySetValueBool
  (JNIEnv *aEnv, jclass aClass, jlong aProperty, jint aValue)
{
	ServiceProperty property = (ServiceProperty) (size_t)aProperty;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jint) ServicePropertySetValueBool(property, aValue);
}

#ifdef __cplusplus
}
#endif

