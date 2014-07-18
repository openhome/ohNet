#include "JniCallbackList.h"
#include "OpenHome/Defines.h"
#include "OpenHome/Net/C/CpDevice.h"

void STDCALL deviceAddedCallback(void* aPtr, CpDeviceC aDevice);
void STDCALL deviceRemovedCallback(void* aPtr, CpDeviceC aDevice);
void InitialiseCpDeviceListReferences(JNIEnv *aEnv, jobject aObject, JniObjRef **aRef);
