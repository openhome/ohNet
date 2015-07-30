#include <jni.h>
#include <OpenHome/Os.h>
#include "Library.h"
#include "OpenHome/Net/C/OhNet.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     openhome_net_core_Library
 * Method:    OhNetLibraryInitialise
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_Library_OhNetLibraryInitialise
  (JNIEnv *aEnv, jclass aClass, jlong aParams)
{
    OhNetHandleInitParams params = (OhNetHandleInitParams) (size_t)aParams;
    aEnv = aEnv;
    aClass = aClass;
    
    return (jlong) OhNetLibraryInitialise(params);
}

/*
 * Class:     org_openhome_net_core_Library
 * Method:    OhNetLibraryInitialiseMinimal
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_Library_OhNetLibraryInitialiseMinimal
  (JNIEnv *aEnv, jclass aClass, jlong aParams)
{
    OhNetHandleInitParams params = (OhNetHandleInitParams) (size_t)aParams;
    aEnv = aEnv;
    aClass = aClass;
    
    return (jlong) OhNetLibraryInitialiseMinimal(params);
}

/*
 * Class:     org_openhome_net_core_Library
 * Method:    OhNetLibraryStartCp
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_Library_OhNetLibraryStartCp
  (JNIEnv *aEnv, jclass aClass, jint aSubnet)
{
#ifdef DEFINE_LITTLE_ENDIAN
    TIpAddress subnet = (TIpAddress) SwapEndian32(aSubnet);
#elif defined DEFINE_BIG_ENDIAN
    TIpAddress subnet = (TIpAddress) aSubnet;
#else
# error Endianness not defined
#endif
    aEnv = aEnv;
    aClass = aClass;
    
    return (jint) OhNetLibraryStartCp(subnet);
}

/*
 * Class:     org_openhome_net_core_Library
 * Method:    OhNetLibraryStartDv
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_Library_OhNetLibraryStartDv
  (JNIEnv *aEnv, jclass aClass)
{
    aEnv = aEnv;
    aClass = aClass;

    return (jint) OhNetLibraryStartDv();
}

/*
 * Class:     org_openhome_net_core_Library
 * Method:    OhNetLibraryStartCombined
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_Library_OhNetLibraryStartCombined
  (JNIEnv *aEnv, jclass aClass, jint aSubnet)
{
#ifdef DEFINE_LITTLE_ENDIAN
    TIpAddress subnet = (TIpAddress) SwapEndian32(aSubnet);
#elif defined DEFINE_BIG_ENDIAN
    TIpAddress subnet = (TIpAddress) aSubnet;
#else
 #error Endianness not defined
#endif
    aEnv = aEnv;
    aClass = aClass;
    
    return (jint) OhNetLibraryStartCombined(subnet);
}

/*
 * Class:     org_openhome_net_core_Library
 * Method:    OhNetLibraryClose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_Library_OhNetLibraryClose
  (JNIEnv *aEnv, jclass aClass)
{
    aEnv = aEnv;
    aClass = aClass;

    OhNetLibraryClose();
}

/*
 * Class:     org_openhome_net_core_Library
 * Method:    OhNetSetCurrentSubnet
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_Library_OhNetSetCurrentSubnet
  (JNIEnv *aEnv, jclass aClass, jlong aSubnet)
{
    OhNetHandleNetworkAdapter subnet = (OhNetHandleNetworkAdapter) (size_t)aSubnet;
    TIpAddress subnetAddress = OhNetNetworkAdapterSubnet(subnet);
    aEnv = aEnv;
    aClass = aClass;

    OhNetSetCurrentSubnet(subnetAddress);
}

/*
 * Class:     org_openhome_net_core_Library
 * Method:    OhNetLibraryNotifySuspended
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_Library_OhNetLibraryNotifySuspended
  (JNIEnv *aEnv, jclass aClass)
{
    aEnv = aEnv;
    aClass = aClass;

    OhNetLibraryNotifySuspended();
}

/*
 * Class:     org_openhome_net_core_Library
 * Method:    OhNetLibraryNotifyResumed
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_Library_OhNetLibraryNotifyResumed
  (JNIEnv *aEnv, jclass aClass)
{
    aEnv = aEnv;
    aClass = aClass;

    OhNetLibraryNotifyResumed();
}

/*
 * Class:     org_openhome_net_core_Library
 * Method:    OhNetDebugSetLevel
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_Library_OhNetDebugSetLevel
  (JNIEnv *aEnv, jclass aClass, jint aLevel)
{
   aEnv = aEnv;
   aClass = aClass;

   OhNetDebugSetLevel((uint32_t)aLevel);
}

/*
 * Class:     org_openhome_net_core_Library
 * Method:    OhNetCurrentSubnetAdapter
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_Library_OhNetCurrentSubnetAdapter
  (JNIEnv *aEnv, jclass aClass)
{
    aEnv = aEnv;
    aClass = aClass;

    return (jlong) (size_t)OhNetCurrentSubnetAdapter("Java client");
}

/*
* Class:     org_openhome_net_core_Library
* Method:    OhNetRefreshNetworkAdapterList
* Signature: ()V
*/
JNIEXPORT void JNICALL Java_org_openhome_net_core_Library_OhNetRefreshNetworkAdapterList
(JNIEnv *aEnv, jclass aClass)
{
    aEnv = aEnv;
    aClass = aClass;

    OhNetRefreshNetworkAdapterList();
}

/*
 * Class:     org_openhome_net_core_Library
 * Method:    OhNetAbortProcess
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_openhome_net_core_Library_OhNetAbortProcess
  (JNIEnv *aEnv, jclass aClass)
{
    aEnv = aEnv;
    aClass = aClass;

    OhNetAbortProcess();
}

#ifdef __cplusplus
}
#endif
