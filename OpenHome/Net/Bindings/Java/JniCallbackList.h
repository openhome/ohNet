#ifndef HEADER_JNICALLBACKLIST
#define HEADER_JNICALLBACKLIST

#include <jni.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct
{
    JavaVM *vm;
    jweak callbackObj;
}  JniObjRef;

typedef struct callback
{
    JniObjRef *ref;
    struct callback *next;
} JniCallback;

typedef struct
{
    JniCallback *head;
} JniCallbackList;

/**
  * Initialise an empty JNI callback list.
  */
JniCallbackList* JniCallbackListCreate();

/**
  * Destroy a given list.
  */
void JniCallbackListDestroy(JNIEnv *aEnv, JniCallbackList **aList);

/**
  * Add an element to the callback list.
  * List assumes ownership of the callback reference.
  */
void JniCallbackListAddElement(JniCallbackList **aList, JniObjRef *aRef);

#endif // HEADER_JNICALLBACKLIST
