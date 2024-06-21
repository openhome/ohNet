# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# ----                    README                              ----
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#
# This is an EXPERIMENTAL build solution to allow for building ohNet
# directly under an IDE that supports CMake projects. This is NOT
# the official or recommended solution for building ohNet.
#
# NOTE #1: You MUST run a Makefile build on your system before this
#          project will work to ensure that headers & other supported
#          files are correctly placed into expected directories
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


cmake_minimum_required(VERSION 3.28)
project(ohNet)

set(CMAKE_CXX_STANDARD 11)

include_directories(./Build/Include/)

set(OH_MDNS_DIR "Build/mDNS/")

IF (WIN32)
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   /c /w /EHa /WX -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -D_CRT_SECURE_NO_WARNINGS")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /c /w /EHa /WX -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -D_CRT_SECURE_NO_WARNINGS")
    set(OH_OS_DIR "Os/Windows/")
    set(OS_LINK_LIBS "Ws2_32.lib Iphlpapi.lib Dbghelp.lib")
else()
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -g -O0 -fPIC -fexceptions -Wall -pipe -Wno-int-to-pointer-cast -Wno-psabi -D_GNU_SOURCE -D_REENTRANT -fvisibility=hidden -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -DPOSIX_STACK_TRACE -DSET_PTHREAD_NAMES")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fPIC -fexceptions -Wall -std=c++0x -pipe -Wno-psabi -D_GNU_SOURCE -D_REENTRANT -fvisibility=hidden -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -DPOSIX_STACK_TRACE -DSET_PTHREAD_NAMES")
    set(OH_OS_DIR "Os/Posix/")
    set(OS_LINK_LIBS "pthread")
ENDIF()

# ohNetCore

add_library(ohNetCore STATIC
        OpenHome/Ascii.cpp
        OpenHome/Net/Bindings/C/AsyncC.cpp
        OpenHome/Net/ControlPoint/AsyncPrivate.cpp
        OpenHome/Net/Device/Bonjour/Bonjour.cpp
        OpenHome/Buffer.cpp
        OpenHome/Converter.cpp
        OpenHome/Crc32.cpp
        thirdparty/libb64/cencode.c
        thirdparty/libb64/cdecode.c
        OpenHome/Net/Discovery.cpp
        OpenHome/Debug.cpp
        OpenHome/Net/ControlPoint/CpDeviceCore.cpp
        OpenHome/Net/Bindings/C/ControlPoint/CpDeviceC.cpp
        OpenHome/Net/Bindings/Cpp/ControlPoint/CpDeviceStd.cpp
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
        OpenHome/FileAnsi.cpp
        OpenHome/FileBrx.cpp
        OpenHome/FileStream.cpp
        OpenHome/Net/Globals.cpp
        OpenHome/Http.cpp
        ${OH_MDNS_DIR}DNSCommon.c
        ${OH_MDNS_DIR}DNSDigest.c
        ${OH_MDNS_DIR}mDNS.c
        ${OH_MDNS_DIR}uDNS.c
        ${OH_MDNS_DIR}dnssd_clientshim.c
        ${OH_MDNS_DIR}dnssd_clientlib.c
        OpenHome/Net/Device/Bonjour/MdnsPlatform.cpp
        OpenHome/Net/Device/Bonjour/MdnsProvider.cpp
        OpenHome/md5.c
        OpenHome/NetworkAdapterList.cpp
        OpenHome/DnsChangeNotifier.cpp
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
        OpenHome/Time.cpp
        OpenHome/Timer.cpp
        OpenHome/TIpAddressUtils.cpp
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
        OpenHome/Shell/Shell.cpp
        OpenHome/Shell/InfoProvider.cpp
        OpenHome/Shell/ShellCommandDebug.cpp
        ${OH_OS_DIR}Os.c
        ${OH_OS_DIR}File.cpp
        ${OH_OS_DIR}TerminalOs.cpp
        ${OH_OS_DIR}SignalHandlers.cpp)


target_link_libraries(ohNetCore ${OS_LINK_LIBS})

# TestFramework

add_library(TestFramework
        OpenHome/TestFramework/TestFramework.cpp
        OpenHome/TestFramework/OptionParser.cpp
        OpenHome/TestFramework/SuiteUnitTest.cpp
        OpenHome/TestFramework/TimerFactoryMock.cpp
        OpenHome/Shell/ShellCommandRun.cpp
        OpenHome/Shell/ShellCommandQuit.cpp
        OpenHome/Shell/ShellCommandWatchDog.cpp
        ${OH_OS_DIR}Main.cpp)

target_link_libraries(TestFramework ohNetCore ${OS_LINK_LIBS})

# ----------------
#      TESTS
# ----------------

# TestBuffer
add_executable(TestBuffer
        OpenHome/Tests/TestBuffer.cpp
        OpenHome/Tests/TestBufferMain.cpp)
target_link_libraries(TestBuffer TestFramework ohNetCore ${OS_LINK_LIBS})

# TestPrinter
add_executable(TestPrinter
        OpenHome/Tests/TestPrinter.cpp
        OpenHome/Tests/TestPrinterMain.cpp)
target_link_libraries(TestPrinter TestFramework ohNetCore ${OS_LINK_LIBS})

# TestException
add_executable(TestException
        OpenHome/Tests/TestException.cpp
        OpenHome/Tests/TestExceptionMain.cpp)
target_link_libraries(TestException TestFramework ohNetCore ${OS_LINK_LIBS})

# TestFunctorGeneric
add_executable(TestFunctorGeneric
        OpenHome/Tests/TestFunctorGeneric.cpp
        OpenHome/Tests/TestFunctorGenericMain.cpp)
target_link_libraries(TestFunctorGeneric TestFramework ohNetCore ${OS_LINK_LIBS})

# TestJson
add_executable(TestJson
        OpenHome/Tests/TestJson.cpp
        OpenHome/Tests/TestJsonMain.cpp)
target_link_libraries(TestJson TestFramework ohNetCore ${OS_LINK_LIBS})

# TestFile
add_executable(TestFile
        OpenHome/Tests/TestFile.cpp
        OpenHome/Tests/TestFileMain.cpp)
target_link_libraries(TestFile TestFramework ohNetCore ${OS_LINK_LIBS})

# TestThread
add_executable(TestThread
        OpenHome/Tests/TestThread.cpp
        OpenHome/Tests/TestThreadMain.cpp)
target_link_libraries(TestThread TestFramework ohNetCore ${OS_LINK_LIBS})

# TestQueue
add_executable(TestQueue
        OpenHome/Tests/TestQueue.cpp
        OpenHome/Tests/TestQueueMain.cpp)
target_link_libraries(TestQueue TestFramework ohNetCore ${OS_LINK_LIBS})

# TestFifo
add_executable(TestFifo
        OpenHome/Tests/TestFifo.cpp
        OpenHome/Tests/TestFifoMain.cpp)
target_link_libraries(TestFifo TestFramework ohNetCore ${OS_LINK_LIBS})

# TestStream
add_executable(TestStream
        OpenHome/Tests/TestStream.cpp
        OpenHome/Tests/TestStreamMain.cpp)
target_link_libraries(TestStream TestFramework ohNetCore ${OS_LINK_LIBS})

# TestTextUtils
add_executable(TestTextUtils
        OpenHome/Tests/TestTextUtils.cpp
        OpenHome/Tests/TestTextUtilsMain.cpp)
target_link_libraries(TestTextUtils TestFramework ohNetCore ${OS_LINK_LIBS})

# TestEcho
add_executable(TestEcho
        OpenHome/Tests/TestEcho.cpp)
target_link_libraries(TestEcho TestFramework ohNetCore ${OS_LINK_LIBS})

# TestMulticast
add_executable(TestMulticast
        OpenHome/Tests/TestMulticast.cpp)
target_link_libraries(TestMulticast TestFramework ohNetCore ${OS_LINK_LIBS})

# TestNetwork
add_executable(TestNetwork
        OpenHome/Tests/TestNetwork.cpp
        OpenHome/Tests/TestNetworkMain.cpp)
target_link_libraries(TestNetwork TestFramework ohNetCore ${OS_LINK_LIBS})

# TestTime
add_executable(TestTime
        OpenHome/Tests/TestTime.cpp
        OpenHome/Tests/TestTimeMain.cpp)
target_link_libraries(TestTime TestFramework ohNetCore ${OS_LINK_LIBS})

# TestTimer
add_executable(TestTimer
        OpenHome/Tests/TestTimer.cpp
        OpenHome/Tests/TestTimerMain.cpp)
target_link_libraries(TestTimer TestFramework ohNetCore ${OS_LINK_LIBS})

# TestTimerMock
add_executable(TestTimerMock
        OpenHome/Tests/TestTimerMock.cpp
        OpenHome/Tests/TestTimerMockMain.cpp)
target_link_libraries(TestTimerMock TestFramework ohNetCore ${OS_LINK_LIBS})

# TestSsdpMListen
add_executable(TestSsdpMListen
        OpenHome/Net/Tests/TestSsdpMListen.cpp
        OpenHome/Net/Tests/TestSsdpMListenMain.cpp)
target_link_libraries(TestSsdpMListen TestFramework ohNetCore ${OS_LINK_LIBS})

# TestSsdpUListen
add_executable(TestSsdpUListen
        OpenHome/Net/Tests/TestSsdpUListen.cpp
        OpenHome/Net/Tests/TestSsdpUListenMain.cpp)
target_link_libraries(TestSsdpUListen TestFramework ohNetCore ${OS_LINK_LIBS})

# TestXmlParser
add_executable(TestXmlParser
        OpenHome/Net/Tests/TestXmlParser.cpp
        OpenHome/Net/Tests/TestXmlParserMain.cpp)
target_link_libraries(TestXmlParser TestFramework ohNetCore ${OS_LINK_LIBS})

# TestDeviceList
add_executable(TestDeviceList
        OpenHome/Net/ControlPoint/Tests/TestDeviceList.cpp
        OpenHome/Net/ControlPoint/Tests/TestDeviceListMain.cpp)
target_link_libraries(TestDeviceList TestFramework ohNetCore ${OS_LINK_LIBS})

# TestDviDiscovery
add_executable(TestDviDiscovery
        OpenHome/Net/Device/Tests/TestDviDiscovery.cpp
        OpenHome/Net/Device/Tests/TestDviDiscoveryMain.cpp)
target_link_libraries(TestDviDiscovery TestFramework ohNetCore ${OS_LINK_LIBS})
