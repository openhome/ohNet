#include <jni.h>
#include "PropertyCallback.h"
#include "PropertyBinary.h"
#include "OpenHome/Net/C/Ohnet.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_PropertyBinary
 * Method:    ServicePropertyCreateBinaryCp
 * Signature: (Ljava/lang/String;Lorg/openhome/net/controlpoint/IPropertyChangeListener;)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_PropertyBinary_ServicePropertyCreateBinaryCp
  (JNIEnv *aEnv, jclass aClass, jstring aName, jobject aListener)
{
	OhNetCallback callback = &ChangeCallback;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	ServiceProperty property;
	JniObjRef *ref;
	aClass = aClass;

	InitialiseReferences(aEnv, aListener, &ref);

	property = ServicePropertyCreateBinaryCp(name, callback, ref);
	
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return (jlong) property;
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
	
	return (jlong) property;
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
	aClass = aClass;
	
	ServicePropertyGetValueBinary(property, &data, &len);
	
	array = (*aEnv)->NewByteArray(aEnv, len);
	(*aEnv)->SetByteArrayRegion(aEnv, array, 0, len, (jbyte *) data);
	
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
	uint8_t *data;
	jint result;
	aClass = aClass;
	
	(*aEnv)->GetByteArrayRegion(aEnv, aData, 0, aLen, (jbyte *) &data);
	
	result = ServicePropertySetValueBinary(property, data, aLen);
	
	return result;
}

#ifdef __cplusplus
}
#endif
