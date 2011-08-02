#include <jni.h>
#include "PropertyCallback.h"
#include "PropertyUint.h"
#include "OpenHome/Net/C/Ohnet.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_PropertyUint
 * Method:    ServicePropertyCreateUintCp
 * Signature: (Ljava/lang/String;Lorg/openhome/net/controlpoint/IPropertyChangeListener;)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_PropertyUint_ServicePropertyCreateUintCp
  (JNIEnv *aEnv, jclass aClass, jstring aName, jobject aListener)
{
	OhNetCallback callback = &ChangeCallback;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	ServiceProperty property;
	JniObjRef *ref;
	aClass = aClass;

	InitialiseReferences(aEnv, aListener, &ref);

	property = ServicePropertyCreateUintCp(name, callback, ref);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return (jlong) property;
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

	return (jlong) property;
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
	aEnv = aEnv;
	aClass = aClass;
	
	return (jlong) ServicePropertyValueUint(property);
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
