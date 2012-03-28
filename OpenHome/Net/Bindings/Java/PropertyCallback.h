#include "JniCallbackList.h"
#include "OpenHome/OhNetDefines.h"

void STDCALL ChangeCallback(void* aPtr);
void STDCALL InitialiseReferences(JNIEnv *aEnv, jobject aObject, JniObjRef **aRef);
