#include <jni.h>
#include <malloc.h>
#include <stdlib.h>
#include "ResourceWriter.h"
#include "OpenHome/Net/C/DvDevice.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_device_ResourceWriter
 * Method:    CallbackWriteResourceBegin
 * Signature: (JJILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_ResourceWriter_CallbackWriteResourceBegin
  (JNIEnv *aEnv, jclass aClass, jlong aWriteBegin, jlong aWriterData, jint aTotalBytes, jstring aMimeType)
{
	union
	{
		OhNetCallbackWriteResourceBegin	function;
		void*							data;
	} callback;
	OhNetCallbackWriteResourceBegin writeBegin;
	const char* mimeType = (*aEnv)->GetStringUTFChars(aEnv, aMimeType, NULL);
	aClass = aClass;
	
	callback.data = (void*) (size_t)aWriteBegin;
	writeBegin = callback.function;

	writeBegin((void*)(size_t)aWriterData, aTotalBytes, mimeType);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aMimeType, mimeType);
}

/*
 * Class:     org_openhome_net_device_ResourceWriter
 * Method:    CallbackWriteResource
 * Signature: (JJ[BI)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_ResourceWriter_CallbackWriteResource
  (JNIEnv *aEnv, jclass aClass, jlong aWriteResource, jlong aWriterData, jbyteArray aData, jint aBytes)
{
	union
	{
		OhNetCallbackWriteResource		function;
		void*							data;
	} callback;
	OhNetCallbackWriteResource writeResource;
	uint8_t* data = (uint8_t*)malloc(sizeof(uint8_t)*aBytes);
	aClass = aClass;

	callback.data = (void*) (size_t)aWriteResource;
	writeResource = callback.function;

	(*aEnv)->GetByteArrayRegion(aEnv, aData, 0, aBytes, (jbyte *)data);

	writeResource((void*)(size_t)aWriterData, data, aBytes);
	free(data);
}

/*
 * Class:     org_openhome_net_device_ResourceWriter
 * Method:    CallbackWriteResourceEnd
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_device_ResourceWriter_CallbackWriteResourceEnd
  (JNIEnv *aEnv, jclass aClass, jlong aWriteEnd, jlong aWriterData)
{
	union
	{
		OhNetCallbackWriteResourceEnd	function;
		void*							data;
	} callback;
	OhNetCallbackWriteResourceEnd writeEnd;
	aEnv = aEnv;
	aClass = aClass;
	
	callback.data = (void*) (size_t)aWriteEnd;
	writeEnd = callback.function;
	
	writeEnd((void*)(size_t)aWriterData);
}	

#ifdef __cplusplus
}
#endif
