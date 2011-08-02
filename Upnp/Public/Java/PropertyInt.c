#include <jni.h>
#include "PropertyCallback.h"
#include "PropertyInt.h"
#include "OpenHome/Net/C/Ohnet.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_PropertyInt
 * Method:    ServicePropertyCreateIntCp
 * Signature: (Ljava/lang/String;Lorg/openhome/net/controlpoint/IPropertyChangeListener;)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_PropertyInt_ServicePropertyCreateIntCp
  (JNIEnv *aEnv, jclass aClass, jstring aName, jobject aListener)
{
	OhNetCallback callback = &ChangeCallback;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	ServiceProperty property;
	JniObjRef *ref;
	aClass = aClass;

	InitialiseReferences(aEnv, aListener, &ref);

	property = ServicePropertyCreateIntCp(name, callback, ref);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return (jlong) property;
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
	
	return (jlong) property;
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
	aEnv = aEnv;
	aClass = aClass;
	
	return (jint) ServicePropertyValueInt(property);
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
