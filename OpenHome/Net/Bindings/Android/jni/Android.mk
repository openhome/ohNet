LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ohroot := ../../../../../

LOCAL_C_INCLUDES := $(ohroot)Build/Include
LOCAL_CFLAGS := -fexceptions -Wall -Werror -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -fvisibility=hidden -Wno-unused
LOCAL_LDLIBS := -llog
LOCAL_MODULE    := ohNet
LOCAL_SRC_FILES := $(ohroot)OpenHome/Ascii.cpp \
                   $(ohroot)OpenHome/Net/Bindings/C/AsyncC.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/AsyncPrivate.cpp \
                   $(ohroot)OpenHome/Net/Device/Bonjour/Bonjour.cpp \
                   $(ohroot)OpenHome/Buffer.cpp \
                   $(ohroot)OpenHome/Converter.cpp \
                   $(ohroot)thirdparty/libb64/cencode.c \
                   $(ohroot)thirdparty/libb64/cdecode.c \
                   $(ohroot)OpenHome/Net/Discovery.cpp \
                   $(ohroot)OpenHome/Debug.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/CpDeviceCore.cpp \
                   $(ohroot)OpenHome/Net/Bindings/C/ControlPoint/CpDeviceC.cpp \
                   $(ohroot)OpenHome/Net/Bindings/Cpp/ControlPoint/CpDeviceStd.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/CpDeviceDvCore.cpp \
                   $(ohroot)OpenHome/Net/Bindings/Cpp/ControlPoint/CpDeviceDvStd.cpp \
                   $(ohroot)OpenHome/Net/Bindings/C/ControlPoint/CpDeviceDvC.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/CpDeviceUpnpCore.cpp \
                   $(ohroot)OpenHome/Net/Bindings/C/ControlPoint/CpDeviceUpnpC.cpp \
                   $(ohroot)OpenHome/Net/Bindings/Cpp/ControlPoint/CpDeviceUpnpStd.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/CpiDevice.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/Dv/CpiDeviceDv.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/Lpec/CpiDeviceLpec.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/Upnp/CpiDeviceUpnp.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/CpiService.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/CpiStack.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/CpiSubscription.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/CpProxy.cpp \
                   $(ohroot)OpenHome/Net/Bindings/C/ControlPoint/CpProxyC.cpp \
                   $(ohroot)OpenHome/Net/Bindings/C/ControlPoint/CpServiceC.cpp \
                   $(ohroot)OpenHome/Net/Device/DvDevice.cpp \
                   $(ohroot)OpenHome/Net/Bindings/Cpp/Device/DvDeviceStd.cpp \
                   $(ohroot)OpenHome/Net/Bindings/C/Device/DvDeviceC.cpp \
                   $(ohroot)OpenHome/Net/Device/DviDevice.cpp \
                   $(ohroot)OpenHome/Net/Bindings/C/Device/DvInvocationC.cpp \
                   $(ohroot)OpenHome/Net/Bindings/Cpp/Device/DvInvocationStd.cpp \
                   $(ohroot)OpenHome/Net/Device/Upnp/DviProtocolUpnp.cpp \
                   $(ohroot)OpenHome/Net/Device/DviProviderSubscriptionLongPoll.cpp \
                   $(ohroot)OpenHome/Net/Device/Providers/DvOpenhomeOrgSubscriptionLongPoll1.cpp \
                   $(ohroot)OpenHome/Net/Device/DviServer.cpp \
                   $(ohroot)OpenHome/Net/Device/Upnp/DviServerUpnp.cpp \
                   $(ohroot)OpenHome/Net/Device/Upnp/DviServerWebSocket.cpp \
                   $(ohroot)OpenHome/Net/Device/Lpec/DviProtocolLpec.cpp \
                   $(ohroot)OpenHome/Net/Device/Lpec/DviServerLpec.cpp \
                   $(ohroot)OpenHome/Net/Device/DviService.cpp \
                   $(ohroot)OpenHome/Net/Device/Upnp/DviSsdpNotifier.cpp \
                   $(ohroot)OpenHome/Net/Device/DviStack.cpp \
                   $(ohroot)OpenHome/Net/Device/DviSubscription.cpp \
                   $(ohroot)OpenHome/Net/Device/DviPropertyUpdateCollection.cpp \
                   $(ohroot)OpenHome/Net/Device/DvProvider.cpp \
                   $(ohroot)OpenHome/Net/Bindings/C/Device/DvProviderC.cpp \
                   $(ohroot)OpenHome/Net/Device/DvServerUpnp.cpp \
                   $(ohroot)OpenHome/Net/Bindings/C/Device/DvServerUpnpC.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/Upnp/DeviceXml.cpp \
                   $(ohroot)OpenHome/Net/Error.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/Upnp/EventUpnp.cpp \
                   $(ohroot)OpenHome/Exception.cpp \
                   $(ohroot)OpenHome/Fifo.cpp \
                   $(ohroot)OpenHome/FileAnsi.cpp \
                   $(ohroot)OpenHome/FileBrx.cpp \
                   $(ohroot)OpenHome/FileStream.cpp \
                   $(ohroot)OpenHome/Net/Globals.cpp \
                   $(ohroot)OpenHome/Http.cpp \
                   $(ohroot)OpenHome/Net/Device/Bonjour/mDNSCore/DNSCommon.c \
                   $(ohroot)OpenHome/Net/Device/Bonjour/mDNSCore/DNSDigest.c \
                   $(ohroot)OpenHome/Net/Device/Bonjour/mDNSCore/mDNS.c \
                   $(ohroot)OpenHome/Net/Device/Bonjour/mDNSCore/uDNS.c \
                   $(ohroot)OpenHome/Net/Device/Bonjour/mDNSShared/dnssd_clientshim.c \
                   $(ohroot)OpenHome/Net/Device/Bonjour/MdnsPlatform.cpp \
                   $(ohroot)OpenHome/Net/Device/Bonjour/MdnsProvider.cpp \
                   $(ohroot)OpenHome/md5.c \
                   $(ohroot)OpenHome/NetworkAdapterList.cpp \
                   $(ohroot)OpenHome/Network.cpp \
                   $(ohroot)OpenHome/Parser.cpp \
                   $(ohroot)OpenHome/Printer.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/Upnp/ProtocolUpnp.cpp \
                   $(ohroot)OpenHome/Queue.cpp \
                   $(ohroot)OpenHome/Net/Service.cpp \
                   $(ohroot)OpenHome/Net/Bindings/C/ServiceC.cpp \
                   $(ohroot)OpenHome/sha1.c \
                   $(ohroot)OpenHome/Net/Ssdp.cpp \
                   $(ohroot)OpenHome/Net/SsdpDv.cpp \
                   $(ohroot)OpenHome/Env.cpp \
                   $(ohroot)OpenHome/Stream.cpp \
                   $(ohroot)OpenHome/Net/Subscription.cpp \
                   $(ohroot)OpenHome/Terminal.cpp \
                   $(ohroot)OpenHome/Thread.cpp \
                   $(ohroot)OpenHome/Timer.cpp \
                   $(ohroot)OpenHome/Uri.cpp \
                   $(ohroot)OpenHome/Net/XmlParser.cpp \
                   $(ohroot)OpenHome/Net/ControlPoint/Upnp/XmlFetcher.cpp \
                   $(ohroot)OpenHome/Net/OhNet.cpp \
                   $(ohroot)OpenHome/Net/OhNetCp.cpp \
                   $(ohroot)OpenHome/Net/OhNetDv.cpp \
                   $(ohroot)OpenHome/Net/OhNetCombined.cpp \
                   $(ohroot)OpenHome/Net/Bindings/C/OhNetC.cpp \
                   $(ohroot)OpenHome/Net/Bindings/C/OhNetCCp.cpp \
                   $(ohroot)OpenHome/Net/Bindings/C/OhNetCDv.cpp \
                   $(ohroot)OpenHome/Net/Bindings/C/OhNetCCombined.cpp \
                   $(ohroot)Os/OsWrapper.cpp \
                   $(ohroot)Os/Posix/File.cpp \
                   $(ohroot)Os/Posix/TerminalOs.cpp \
                   $(ohroot)Os/Posix/Os.c \
                   $(ohroot)Os/Posix/SignalHandlers.cpp \
                   $(ohroot)OpenHome/Shell/Shell.cpp \
                   $(ohroot)OpenHome/Shell/InfoProvider.cpp \
                   $(ohroot)OpenHome/Shell/ShellCommandDebug.cpp \
                   ifaddrs-android.cpp

include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_C_INCLUDES := $(ohroot)Build/Include
LOCAL_CFLAGS := -fexceptions -Wall -Werror -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -Wno-psabi
LOCAL_LDLIBS := -llog
LOCAL_MODULE := ohNetJni
LOCAL_SHARED_LIBRARIES := ohNet
LOCAL_SRC_FILES := $(ohroot)OpenHome/Net/Bindings/Java/Action.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/ArgumentBinary.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/ArgumentBool.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/ArgumentInt.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/ArgumentString.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/ArgumentUint.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/CpDevice.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/CpDeviceDv.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/CpDeviceListUpnpAll.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/CpDeviceListUpnpDeviceType.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/CpDeviceListUpnpRoot.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/CpDeviceListUpnpServiceType.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/CpDeviceListUpnpUuid.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/CpDeviceList.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/CpProxy.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/CpService.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/DvDevice.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/DvDeviceStandard.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/DvInvocation.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/DvProvider.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/DvServerUpnp.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/InitParams.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/Invocation.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/JniCallbackList.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/Library.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/NetworkAdapter.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/ParameterBinary.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/ParameterBool.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/ParameterInt.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/ParameterRelated.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/ParameterString.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/ParameterUint.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/Property.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/PropertyBinary.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/PropertyBool.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/PropertyInt.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/PropertyString.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/PropertyUint.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/ResourceWriter.c \
                   $(ohroot)OpenHome/Net/Bindings/Java/SubnetList.c

include $(BUILD_SHARED_LIBRARY)
