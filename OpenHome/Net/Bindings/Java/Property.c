#include <jni.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "Property.h"
#include "PropertyCallback.h"
#include "JniCallbackList.h"
#include "OpenHome/Net/C/OhNet.h"
#include "OpenHome/Net/C/Service.h"

#ifdef __cplusplus
extern "C" {
#endif

void STDCALL ChangeCallback(void* aPtr)
{
    JniObjRef* ref = (JniObjRef*) aPtr;
    JavaVM *vm = ref->vm;
    JNIEnv *env;
    jclass cls;
    jmethodID mid;
    jint ret;
    jint attached;

    attached = (*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_4);
    if (attached < 0)
    {
#ifdef __ANDROID__
        ret = (*vm)->AttachCurrentThreadAsDaemon(vm, &env, NULL);
#else
        ret = (*vm)->AttachCurrentThreadAsDaemon(vm, (void **)&env, NULL);
#endif
        if (ret < 0)
        {
            printf("PropertyJNI: Unable to attach thread to JVM.\n");
            fflush(stdout);
            return;
        }
    }
    cls = (*env)->GetObjectClass(env, ref->callbackObj);
    mid = (*env)->GetMethodID(env, cls, "notifyChange", "()V");
    (*env)->DeleteLocalRef(env, cls);
    if (mid == 0) {
        printf("PropertyJNI: Method ID notifyChange() not found.\n");
        return;
    }
    (*env)->CallVoidMethod(env, ref->callbackObj, mid);
    
    // leave daemon thread attached to the VM
}

void STDCALL InitialiseReferences(JNIEnv *aEnv, jobject aObject, JniObjRef **aRef)
{
    jint ret;

    *aRef = (JniObjRef*) malloc(sizeof(JniObjRef));

    ret = (*aEnv)->GetJavaVM(aEnv, &(*aRef)->vm);
    if (ret < 0) {
        printf("PropertyJNI: Unable to get reference to the current Java VM.\n");
        fflush(stdout);
    }
    (*aRef)->callbackObj = (*aEnv)->NewGlobalRef(aEnv, aObject);
    if ((*aRef)->callbackObj == NULL) {
        printf("PropertyJNI: Callback object not stored.\n");
        fflush(stdout);
    }
}

/*
 * Class:     org_openhome_net_core_Property
 * Method:    ServicePropertyDestroyProperty
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_Property_ServicePropertyDestroyProperty
  (JNIEnv *aEnv, jclass aClass, jlong aProperty)
{
    ServiceProperty property = (ServiceProperty) (size_t)aProperty;
    aEnv = aEnv;
    aClass = aClass;
    
    ServicePropertyDestroy(property);
}

/*
 * Class:     org_openhome_net_core_Property
 * Method:    ServicePropertyDestroyCallback
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_Property_ServicePropertyDestroyCallback
  (JNIEnv *aEnv, jclass aClass, jlong aCallback)
{
    JniObjRef *ref = (JniObjRef*) (size_t)aCallback;
    aClass = aClass;
    
     (*aEnv)->DeleteGlobalRef(aEnv, ref->callbackObj);
     free(ref);
}

#ifdef __cplusplus
}
#endif
