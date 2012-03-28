#include <malloc.h>
#include <stdlib.h>
#include "JniCallbackList.h"

/**
  * Initialise an empty JNI callback list.
  */
JniCallbackList* JniCallbackListCreate()
{
	JniCallbackList *list = (JniCallbackList *)malloc(sizeof(JniCallbackList));
	list->head = NULL;
	
	return list;
}

/**
  * Destroy a given list.
  */
void JniCallbackListDestroy(JNIEnv *aEnv, JniCallbackList **aList)
{
	if(!(*aList))
	{
		return;
	}
	
	while((*aList)->head)
	{
		JniCallback *curr = (*aList)->head;
		(*aList)->head = (*aList)->head->next;
		(*aEnv)->DeleteGlobalRef(aEnv, curr->ref->callbackObj);
		free(curr->ref);
		free(curr);
	}
	free(*aList);
}

/**
  * Add an element to the callback list.
  * List assumes ownership of the callback reference.
  */
void JniCallbackListAddElement(JniCallbackList **aList, JniObjRef *aRef)
{
	JniCallback *callback = (JniCallback *)malloc(sizeof(JniCallback));
	callback->ref = aRef;
	callback->next = (*aList)->head;
	(*aList)->head = callback;
}
