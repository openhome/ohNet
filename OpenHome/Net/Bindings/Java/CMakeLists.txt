# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.4.1)
include(TestBigEndian)
# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add.library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.

set( SourcesJni
    Action.c
    ArgumentBinary.c
    ArgumentBool.c
    ArgumentInt.c
    ArgumentString.c
    ArgumentUint.c
    CpDevice.c
    CpDeviceDv.c
    CpDeviceList.c
    CpDeviceListUpnpAll.c
    CpDeviceListUpnpDeviceType.c
    CpDeviceListUpnpRoot.c
    CpDeviceListUpnpServiceType.c
    CpDeviceListUpnpUuid.c
    CpProxy.c
    CpService.c
    DvDevice.c
    DvDeviceStandard.c
    DvInvocation.c
    DvProvider.c
    DvServerUpnp.c
    InitParams.c
    Invocation.c
    JniCallbackList.c
    Library.c
    NetworkAdapter.c
    Parameter.c
    ParameterBinary.c
    ParameterBool.c
    ParameterInt.c
    ParameterRelated.c
    ParameterString.c
    ParameterUint.c
    Property.c
    PropertyBinary.c
    PropertyBool.c
    PropertyInt.c
    PropertyString.c
    PropertyUint.c
    ResourceWriter.c
    SubnetList.c
    ../android/jni/ifaddrs-android.cpp
     )


add_library( # Specifies the name of the library.
             ohNetJni

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${SourcesJni} )




if( ANDROID_ENDIAN )
    message( "Android Endian" ${ANDROID_ENDIAN} )
    if( ${ANDROID_ENDIAN} STREQUAL "LITTLE" )
        message( "Android Endian 1" )
        set( ENDIANNESS "-D DEFINE_LITTLE_ENDIAN" )
     else( ${ANDROID_ENDIAN} STREQUAL "LITTLE" )
        message( "Android Endian 2" )
        set( ENDIANNESS "-D DEFINE_BIG_ENDIAN" )
     endif( ${ANDROID_ENDIAN} STREQUAL "LITTLE" )
else( ANDROID_ENDIAN )
    if( ENDIAN EQUAL 0 )
        set( ENDIANNESS "-D DEFINE_LITTLE_ENDIAN" )
    else( ENDIAN EQUAL 0 )
        set( ENDIANNESS "-D DEFINE_BIG_ENDIAN" )
    endif( ENDIAN EQUAL 0 )

endif( ANDROID_ENDIAN )
if( DEBUG_LOG )
    target_compile_definitions( ohNetJni PUBLIC "-D DEFINE_TRACE" )
endif( DEBUG_LOG )
target_compile_definitions( ohNetJni PUBLIC ${ENDIANNESS} )
target_include_directories( ohNetJni SYSTEM PRIVATE ${GENERATED_INCLUDES} )
target_include_directories( ohNetJni SYSTEM PRIVATE ../android/jni/ )
target_link_libraries( ohNetJni ohNet )
add_dependencies( ohNetJni ohNet )