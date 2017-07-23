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

set( SourcesMain
    OpenHome/Ascii.cpp
    OpenHome/Net/Bindings/C/AsyncC.cpp 
    OpenHome/Net/ControlPoint/AsyncPrivate.cpp 
    OpenHome/Net/Device/Bonjour/Bonjour.cpp 
    OpenHome/Buffer.cpp 
    OpenHome/Converter.cpp 
    thirdparty/libb64/cencode.c 
    thirdparty/libb64/cdecode.c 
    OpenHome/Net/Discovery.cpp 
    OpenHome/Debug.cpp 
    OpenHome/Net/ControlPoint/CpDeviceCore.cpp 
    OpenHome/Net/Bindings/C/ControlPoint/CpDeviceC.cpp 
    OpenHome/Net/Bindings/Cpp/ControlPoint/CpDeviceStd.cpp 
    OpenHome/Net/ControlPoint/CpDeviceDvCore.cpp 
    OpenHome/Net/Bindings/Cpp/ControlPoint/CpDeviceDvStd.cpp 
    OpenHome/Net/Bindings/C/ControlPoint/CpDeviceDvC.cpp 
    OpenHome/Net/ControlPoint/CpDeviceUpnpCore.cpp 
    OpenHome/Net/Bindings/C/ControlPoint/CpDeviceUpnpC.cpp 
    OpenHome/Net/Bindings/Cpp/ControlPoint/CpDeviceUpnpStd.cpp 
    OpenHome/Net/ControlPoint/CpiDevice.cpp 
    OpenHome/Net/ControlPoint/Dv/CpiDeviceDv.cpp 
    OpenHome/Net/ControlPoint/Lpec/CpiDeviceLpec.cpp 
    OpenHome/Net/ControlPoint/Upnp/CpiDeviceUpnp.cpp 
    OpenHome/Net/ControlPoint/CpiService.cpp 
    OpenHome/Net/ControlPoint/CpiStack.cpp 
    OpenHome/Net/ControlPoint/CpiSubscription.cpp 
    OpenHome/Net/ControlPoint/CpProxy.cpp 
    OpenHome/Net/Bindings/C/ControlPoint/CpProxyC.cpp 
    OpenHome/Net/Bindings/C/ControlPoint/CpServiceC.cpp 
    OpenHome/Net/Device/DvDevice.cpp 
    OpenHome/Net/Bindings/Cpp/Device/DvDeviceStd.cpp 
    OpenHome/Net/Bindings/C/Device/DvDeviceC.cpp 
    OpenHome/Net/Device/DviDevice.cpp 
    OpenHome/Net/Bindings/C/Device/DvInvocationC.cpp 
    OpenHome/Net/Bindings/Cpp/Device/DvInvocationStd.cpp 
    OpenHome/Net/Device/Upnp/DviProtocolUpnp.cpp 
    OpenHome/Net/Device/DviProviderSubscriptionLongPoll.cpp 
    OpenHome/Net/Device/Providers/DvOpenhomeOrgSubscriptionLongPoll1.cpp 
    OpenHome/Net/Device/DviServer.cpp 
    OpenHome/Net/Device/Upnp/DviServerUpnp.cpp 
    OpenHome/Net/Device/Upnp/DviServerWebSocket.cpp 
    OpenHome/Net/Device/Lpec/DviProtocolLpec.cpp 
    OpenHome/Net/Device/Lpec/DviServerLpec.cpp 
    OpenHome/Net/Device/DviService.cpp 
    OpenHome/Net/Device/Upnp/DviSsdpNotifier.cpp 
    OpenHome/Net/Device/DviStack.cpp 
    OpenHome/Net/Device/DviSubscription.cpp 
    OpenHome/Net/Device/DviPropertyUpdateCollection.cpp 
    OpenHome/Net/Device/DvProvider.cpp 
    OpenHome/Net/Bindings/C/Device/DvProviderC.cpp 
    OpenHome/Net/Device/DvServerUpnp.cpp 
    OpenHome/Net/Bindings/C/Device/DvServerUpnpC.cpp 
    OpenHome/Net/ControlPoint/Upnp/DeviceXml.cpp 
    OpenHome/Net/Error.cpp 
    OpenHome/Net/ControlPoint/Upnp/EventUpnp.cpp 
    OpenHome/Exception.cpp 
    OpenHome/Fifo.cpp 
    OpenHome/FileAnsii.cpp 
    OpenHome/FileBrx.cpp 
    OpenHome/FileStream.cpp 
    OpenHome/Net/Globals.cpp 
    OpenHome/Http.cpp 
    OpenHome/Net/Device/Bonjour/mDNSCore/DNSCommon.c 
    OpenHome/Net/Device/Bonjour/mDNSCore/DNSDigest.c 
    OpenHome/Net/Device/Bonjour/mDNSCore/mDNS.c 
    OpenHome/Net/Device/Bonjour/mDNSCore/uDNS.c 
    OpenHome/Net/Device/Bonjour/MdnsPlatform.cpp 
    OpenHome/Net/Device/Bonjour/MdnsProvider.cpp 
    OpenHome/md5.c 
    OpenHome/NetworkAdapterList.cpp 
    OpenHome/Network.cpp 
    OpenHome/Parser.cpp 
    OpenHome/Printer.cpp 
    OpenHome/Net/ControlPoint/Upnp/ProtocolUpnp.cpp 
    OpenHome/Queue.cpp 
    OpenHome/Net/Service.cpp 
    OpenHome/Net/Bindings/C/ServiceC.cpp 
    OpenHome/sha1.c 
    OpenHome/Net/Ssdp.cpp 
    OpenHome/Net/SsdpDv.cpp
    OpenHome/Env.cpp 
    OpenHome/Stream.cpp 
    OpenHome/Net/Subscription.cpp 
    OpenHome/Terminal.cpp 
    OpenHome/Thread.cpp 
    OpenHome/Timer.cpp 
    OpenHome/Uri.cpp 
    OpenHome/Net/XmlParser.cpp 
    OpenHome/Net/ControlPoint/Upnp/XmlFetcher.cpp 
    OpenHome/Net/OhNet.cpp 
    OpenHome/Net/OhNetCp.cpp 
    OpenHome/Net/OhNetDv.cpp 
    OpenHome/Net/OhNetCombined.cpp 
    OpenHome/Net/Bindings/C/OhNetC.cpp
    OpenHome/Net/Bindings/C/OhNetCCp.cpp 
    OpenHome/Net/Bindings/C/OhNetCDv.cpp 
    OpenHome/Net/Bindings/C/OhNetCCombined.cpp 
    Os/OsWrapper.cpp 
    Os/Posix/File.cpp 
    Os/Posix/TerminalOs.cpp 
    Os/Posix/Os.c 
    Os/Posix/SignalHandlers.cpp 
    OpenHome/Shell/Shell.cpp 
    OpenHome/Shell/InfoProvider.cpp 
    OpenHome/Shell/ShellCommandDebug.cpp 
    OpenHome/Net/Bindings/Android/jni/ifaddrs-android.cpp )


add_library( # Specifies the name of the library.
             ohNet

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${SourcesMain} )


add_custom_target( IncludeCopy )

add_custom_target( IncludeBase )
add_custom_command(TARGET IncludeBase PRE_BUILD
                     COMMAND ${CMAKE_COMMAND} -E
                         make_directory ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Private/ )
add_custom_command(TARGET IncludeBase PRE_BUILD
                     COMMAND ${CMAKE_COMMAND} -E
                         make_directory ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Core/ )
add_custom_command(TARGET IncludeBase PRE_BUILD
                     COMMAND ${CMAKE_COMMAND} -E
                         make_directory ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Private/ )
add_custom_command(TARGET IncludeBase PRE_BUILD
                 COMMAND ${CMAKE_COMMAND} -E
                     make_directory ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Cpp/ )
add_custom_command(TARGET IncludeBase PRE_BUILD
                 COMMAND ${CMAKE_COMMAND} -E
                     make_directory ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/C/ )
add_custom_command(TARGET IncludeBase PRE_BUILD
                 COMMAND ${CMAKE_COMMAND} -E
                     make_directory ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Core/ )
TEST_BIG_ENDIAN( ENDIAN )


###########################################
# macro to split the ninja command line into parts.
# on windows, all the .h files creates 10k bytes of command.
#
# We use parts to build dependencies up.
###########################################
macro( header_copy part base  whole  dir  outdir  list )
    add_custom_target( ${part} )
    foreach(HeaderFile ${list})
      add_custom_command(TARGET ${part} PRE_BUILD
                         COMMAND ${CMAKE_COMMAND} -E
                             copy ${dir}/${HeaderFile} ${outdir} )
    endforeach()
    add_dependencies( ${whole} ${part} )
    add_dependencies( ${part} ${base} )
endmacro( header_copy )

set(PrivateHeaderFiles Arch.h Ascii.h Converter.h Debug.h Env.h Fifo.h File.h Http.h md5.h Network.h sha.h Terminal.h)
set(PrivateHeaderFiles2  NetworkAdapterList.h Parser.h Printer.h Queue.h Stream.h Thread.h Standard.h Uri.h Timer.h )
set(HeaderFiles Buffer.h Buffer.inl Defines.h Exception.h Functor.h FunctorMsg.h FunctorNetworkAdapter.h MimeTypes.h OhNetDefines.h OhNetTypes.h OsTypes.h Types.h )
set(PrivateControlPtHeaders AsyncPrivate.h CpiDevice.h CpiService.h CpiStack.h )
set(ControlPtHeaders CpDevice.h CpDeviceDv.h CpDeviceUpnp.h CpProxy.h FunctorCpDevice.h )
set(NetDeviceBonjourHeaders Bonjour.h MdnsPlatform.h MdnsProvider.h )
set(NetBindingsCppDevice DvDevice.h DvInvocation.h DvStack.h)
set(NetBindingsCppControlPoint CpDevice.h CpDeviceDv.h CpDeviceUpnp.h CpStack.h FunctorCpDevice.h)
set(NetControlPointDv CpiDeviceDv.h)
set(NetBindingsCDevice DvDevice.h DviDeviceC.h DvInvocation.h DvInvocationPrivate.h DvProvider.h DvServerUpnp.h DvStack.h)
set(NetBindingsCControlPoint Async.h CpDevice.h CpDeviceDv.h CpDeviceUpnp.h CpProxy.h CpProxyCPrivate.h CpService.h CpStack.h)
set(NetControlPoint_prv AsyncPrivate.h CpiDevice.h CpiService.h CpiStack.h CpiSubscription.h FunctorCpiDevice.h )
set(NetDevice DviDevice.h DviPropertyUpdateCollection.h DviProviderSubscriptionLongPoll.h DviServer.h DviService.h DviStack.h DviSubscription.h FunctorDviInvocation.h)
set(NetDevice_core DvDevice.h DvInvocationResponse.h DvProvider.h DvResourceWriter.h DvServerUpnp.h)
set(NetDevice_cpp DvResourceWriter.h)
set(NetControlPointUpnp CpiDeviceUpnp.h DeviceXml.h EventUpnp.h ProtocolUpnp.h XmlFetcher.h )
set(Net_prv  Discovery.h Error.h Globals.h Service.h Ssdp.h Subscription.h XmlParser.h )
set(Net_pub OhNet.h FunctorAsync.h)
set(FolderOs Os.h OsWrapper.h OsWrapper.inl)
set(NetBindingsC OhNet.h Service.h)
set(Shell_prv InfoProvider.h Shell.h ShellCommandDebug.h)
set(NetControlPointLpec_prv CpiDeviceLpec.h )
set(NetDeviceLpec_prv DviProtocolLpec.h DviServerLpec.h )
set(NetDeviceUpnp DviServerUpnp.h DviServerWebSocket.h DviSsdpNotifier.h DviProtocolUpnp.h )
set(NetDeviceProviders DvOpenhomeOrgSubscriptionLongPoll1.h )
set(NetDeviceBonjourmDNSCore  mDNSDebug.h mDNSEmbeddedAPI.h MultilineMacro.h )
message( "CMake source dir is " ${CMAKE_SOURCE_DIR} )



header_copy( header1 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Private "${PrivateHeaderFiles}")
header_copy( header2 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome "${HeaderFiles}")
header_copy( header3 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/ControlPoint ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Private "${PrivateControlPtHeaders}")
header_copy( header4 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/ControlPoint ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Core "${ControlPtHeaders}")
header_copy( header5 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/Device/Bonjour ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Private "${NetDeviceBonjourHeaders}")
header_copy( header6 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/Bindings/Cpp/Device ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Cpp "${NetBindingsCppDevice}")
header_copy( header7 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/Bindings/Cpp/ControlPoint ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Cpp "${NetBindingsCppControlPoint}")
header_copy( header8 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/Bindings/C/Device ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/C "${NetBindingsCDevice}")
header_copy( header9 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/Bindings/C/ControlPoint ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/C "${NetBindingsCControlPoint}")
header_copy(header10 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/ControlPoint/Dv ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Private "${NetControlPointDv}")
header_copy(header11 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/ControlPoint ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Private "${NetControlPoint_prv}")
header_copy(header12 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Private "${Net_prv}")
header_copy(header13 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/ControlPoint/Upnp ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Private "${NetControlPointUpnp}")
header_copy( header14 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Private "${PrivateHeaderFiles2}")
header_copy(header15 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Core "${Net_pub}")
header_copy(header16 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/ControlPoint ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Core "${NetControlPoint_pub}")
header_copy(header17 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/Os ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome "${FolderOs}")
header_copy(header18 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/Bindings/C ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/C "${NetBindingsC}")
header_copy(header19 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Shell ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Private "${Shell_prv}")
header_copy(header20 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/Device ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Private "${NetDevice}")
header_copy(header21 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/ControlPoint/Lpec ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Private "${NetControlPointLpec_prv}")
header_copy(header22 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/Device ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Core "${NetDevice_core}")
header_copy(header23 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/Device/Lpec ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Private "${NetDeviceLpec_prv}")
header_copy(header24 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/Device ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Cpp "${NetDevice_cpp}")
header_copy(header25 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/Device/Upnp ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Private "${NetDeviceUpnp}")
header_copy(header26 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/Device/Providers ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Core "${NetDeviceProviders}")
header_copy(header27 IncludeBase IncludeCopy  ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/Device/Bonjour/mDNSCore ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome/Net/Private "${NetDeviceBonjourmDNSCore}")
message( "Creating files in " ${CMAKE_CURRENT_BINARY_DIR}/Temp/OpenHome )
target_include_directories( ohNet SYSTEM PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/Temp )
set( GENERATED_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/Temp PARENT_SCOPE )
target_include_directories( ohNet SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/ohNet/OpenHome/Net/Bindings/Android/jni )
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
    target_compile_definitions( ohNet PUBLIC "-D DEFINE_TRACE" )
endif( DEBUG_LOG )
target_compile_definitions( ohNet PUBLIC ${ENDIANNESS} )
add_dependencies( ohNet IncludeCopy )
target_link_libraries( ohNet android log )
