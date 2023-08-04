proxyCppCore = OpenHome$(dirsep)Net$(dirsep)ControlPoint$(dirsep)Proxies$(dirsep)
proxyC = OpenHome$(dirsep)Net$(dirsep)Bindings$(dirsep)C$(dirsep)ControlPoint$(dirsep)Proxies$(dirsep)
proxyCppStd = OpenHome$(dirsep)Net$(dirsep)Bindings$(dirsep)Cpp$(dirsep)ControlPoint$(dirsep)Proxies$(dirsep)
proxyCs = OpenHome$(dirsep)Net$(dirsep)Bindings$(dirsep)Cs$(dirsep)ControlPoint$(dirsep)Proxies$(dirsep)
proxyJava = OpenHome$(dirsep)Net$(dirsep)Bindings$(dirsep)Java$(dirsep)org$(dirsep)openhome$(dirsep)net$(dirsep)controlpoint$(dirsep)proxies$(dirsep)
proxyJs = OpenHome$(dirsep)Net$(dirsep)Bindings$(dirsep)Js$(dirsep)ControlPoint$(dirsep)Proxies$(dirsep)
deviceCppCore = OpenHome$(dirsep)Net$(dirsep)Device$(dirsep)Providers$(dirsep)
deviceCppStd = OpenHome$(dirsep)Net$(dirsep)Bindings$(dirsep)Cpp$(dirsep)Device$(dirsep)Providers$(dirsep)
deviceC = OpenHome$(dirsep)Net$(dirsep)Bindings$(dirsep)C$(dirsep)Device$(dirsep)Providers$(dirsep)
deviceCs = OpenHome$(dirsep)Net$(dirsep)Bindings$(dirsep)Cs$(dirsep)Device$(dirsep)Providers$(dirsep)
deviceJava = OpenHome$(dirsep)Net$(dirsep)Bindings$(dirsep)Java$(dirsep)org$(dirsep)openhome$(dirsep)net$(dirsep)device$(dirsep)providers$(dirsep)

csShared = OpenHome$(dirsep)Net$(dirsep)Bindings$(dirsep)Cs$(dirsep)
csCp = OpenHome$(dirsep)Net$(dirsep)Bindings$(dirsep)Cs$(dirsep)ControlPoint$(dirsep)
csCpTests = OpenHome$(dirsep)Net$(dirsep)Bindings$(dirsep)Cs$(dirsep)ControlPoint$(dirsep)Tests$(dirsep)
csDv = OpenHome$(dirsep)Net$(dirsep)Bindings$(dirsep)Cs$(dirsep)Device$(dirsep)
csDvTests = OpenHome$(dirsep)Net$(dirsep)Bindings$(dirsep)Cs$(dirsep)Device$(dirsep)Tests$(dirsep)

objects_core = \
	$(objdir)Ascii.$(objext) \
	$(objdir)AsyncC.$(objext) \
	$(objdir)AsyncPrivate.$(objext) \
	$(objdir)Bonjour.$(objext) \
	$(objdir)Buffer.$(objext) \
	$(objdir)Converter.$(objext) \
	$(objdir)cencode.$(objext) \
	$(objdir)cdecode.$(objext) \
	$(objdir)Discovery.$(objext) \
	$(objdir)Debug.$(objext) \
	$(objdir)CpDeviceCore.$(objext) \
	$(objdir)CpDeviceC.$(objext) \
	$(objdir)CpDeviceStd.$(objext) \
	$(objdir)CpDeviceDvCore.$(objext) \
	$(objdir)CpDeviceDvStd.$(objext) \
	$(objdir)CpDeviceDvC.$(objext) \
	$(objdir)CpDeviceUpnpCore.$(objext) \
	$(objdir)CpDeviceUpnpC.$(objext) \
	$(objdir)CpDeviceUpnpStd.$(objext) \
	$(objdir)CpiDevice.$(objext) \
	$(objdir)CpiDeviceDv.$(objext) \
	$(objdir)CpiDeviceLpec.$(objext) \
	$(objdir)CpiDeviceUpnp.$(objext) \
	$(objdir)CpiService.$(objext) \
	$(objdir)CpiStack.$(objext) \
	$(objdir)CpiSubscription.$(objext) \
	$(objdir)CpProxy.$(objext) \
	$(objdir)CpProxyC.$(objext) \
	$(objdir)CpServiceC.$(objext) \
	$(objdir)Crc32.$(objext) \
	$(objdir)DvDevice.$(objext) \
	$(objdir)DvDeviceStd.$(objext) \
	$(objdir)DvDeviceC.$(objext) \
	$(objdir)DviDevice.$(objext) \
	$(objdir)DvInvocationC.$(objext) \
	$(objdir)DvInvocationStd.$(objext) \
	$(objdir)DviProtocolUpnp.$(objext) \
	$(objdir)DviProviderSubscriptionLongPoll.$(objext) \
	$(objdir)DvOpenhomeOrgSubscriptionLongPoll1.$(objext) \
	$(objdir)DviServer.$(objext) \
	$(objdir)DviServerUpnp.$(objext) \
	$(objdir)DviServerWebSocket.$(objext) \
	$(objdir)DviProtocolLpec.$(objext) \
	$(objdir)DviServerLpec.$(objext) \
	$(objdir)DviService.$(objext) \
	$(objdir)DviSsdpNotifier.$(objext) \
	$(objdir)DviStack.$(objext) \
	$(objdir)DviSubscription.$(objext) \
	$(objdir)DviPropertyUpdateCollection.$(objext) \
	$(objdir)DvProvider.$(objext) \
	$(objdir)DvProviderC.$(objext) \
	$(objdir)DvServerUpnp.$(objext) \
	$(objdir)DvServerUpnpC.$(objext) \
	$(objdir)DeviceXml.$(objext) \
	$(objdir)Error.$(objext) \
	$(objdir)EventUpnp.$(objext) \
	$(objdir)Exception.$(objext) \
	$(objdir)Fifo.$(objext) \
	$(objdir)File.$(objext) \
	$(objdir)FileAnsi.$(objext) \
	$(objdir)FileBrx.$(objext) \
	$(objdir)FileStream.$(objext) \
	$(objdir)Globals.$(objext) \
	$(objdir)Http.$(objext) \
	$(objdir)DNSCommon.$(objext) \
	$(objdir)DNSDigest.$(objext) \
	$(objdir)mDNS.$(objext) \
	$(objdir)uDNS.$(objext) \
	$(objdir)dnssd_clientshim.$(objext) \
	$(objdir)dnssd_clientlib.$(objext) \
	$(objdir)MdnsPlatform.$(objext) \
	$(objdir)MdnsProvider.$(objext) \
	$(objdir)Md5.$(objext) \
	$(objdir)NetworkAdapterList.$(objext) \
	$(objdir)DnsChangeNotifier.$(objext) \
	$(objdir)Network.$(objext) \
	$(objdir)Parser.$(objext) \
	$(objdir)Printer.$(objext) \
	$(objdir)ProtocolUpnp.$(objext) \
	$(objdir)Queue.$(objext) \
	$(objdir)Service.$(objext) \
	$(objdir)ServiceC.$(objext) \
	$(objdir)sha1.$(objext) \
	$(objdir)Ssdp.$(objext) \
	$(objdir)SsdpDv.$(objext) \
	$(objdir)Env.$(objext) \
	$(objdir)Stream.$(objext) \
	$(objdir)Subscription.$(objext) \
	$(objdir)Terminal.$(objext) \
	$(objdir)TerminalOs.$(objext) \
	$(objdir)Thread.$(objext) \
	$(objdir)Timer.$(objext) \
	$(objdir)TIpAddressUtils.$(objext) \
	$(objdir)Uri.$(objext) \
	$(objdir)XmlParser.$(objext) \
	$(objdir)XmlFetcher.$(objext) \
	$(objdir)OhNet.$(objext) \
	$(objdir)OhNetCp.$(objext) \
	$(objdir)OhNetDv.$(objext) \
	$(objdir)OhNetCombined.$(objext) \
	$(objdir)OhNetC.$(objext) \
	$(objdir)OhNetCCp.$(objext) \
	$(objdir)OhNetCDv.$(objext) \
	$(objdir)OhNetCCombined.$(objext) \
	$(objdir)OsWrapper.$(objext) \
	$(objdir)Os.$(objext) \
	$(objdir)SignalHandlers.$(objext) \
	$(objdir)Shell.$(objext) \
	$(objdir)InfoProvider.$(objext) \
	$(objdir)ShellCommandDebug.$(objext)


# For simplicity, we make a list of all headers in the project and have all (core) source files depend on them
headers = \
	$(inc_build)/OpenHome/Buffer.h \
	$(inc_build)/OpenHome/Exception.h \
	$(inc_build)/OpenHome/Functor.h \
	$(inc_build)/OpenHome/FunctorMsg.h \
	$(inc_build)/OpenHome/FunctorNetworkAdapter.h \
	$(inc_build)/OpenHome/MimeTypes.h \
	$(inc_build)/OpenHome/Defines.h \
	$(inc_build)/OpenHome/OhNetDefines.h \
	$(inc_build)/OpenHome/Types.h \
	$(inc_build)/OpenHome/OhNetTypes.h \
	$(inc_build)/OpenHome/Os.h \
	$(inc_build)/OpenHome/OsTypes.h \
	$(inc_build)/OpenHome/OsWrapper.h \
	$(inc_build)/OpenHome/OsWrapper.inl \
	$(inc_build)/OpenHome/Private/Arch.h \
	$(inc_build)/OpenHome/Private/Ascii.h \
	$(inc_build)/OpenHome/Private/Converter.h \
	$(inc_build)/OpenHome/Private/Crc32.h \
	$(inc_build)/OpenHome/Private/Debug.h \
	$(inc_build)/OpenHome/Private/Fifo.h \
	$(inc_build)/OpenHome/Private/File.h \
	$(inc_build)/OpenHome/Private/Http.h \
	$(inc_build)/OpenHome/Private/md5.h \
	$(inc_build)/OpenHome/Private/Network.h \
	$(inc_build)/OpenHome/Private/NetworkAdapterList.h \
	$(inc_build)/OpenHome/Private/DnsChangeNotifier.h \
	$(inc_build)/OpenHome/Private/Parser.h \
	$(inc_build)/OpenHome/Private/Printer.h \
	$(inc_build)/OpenHome/Private/Queue.h \
	$(inc_build)/OpenHome/Private/Standard.h \
	$(inc_build)/OpenHome/Private/Stream.h \
	$(inc_build)/OpenHome/Private/Terminal.h \
	$(inc_build)/OpenHome/Private/Thread.h \
	$(inc_build)/OpenHome/Private/Timer.h \
	$(inc_build)/OpenHome/Private/TIpAddressUtils.h \
	$(inc_build)/OpenHome/Private/Uri.h \
	$(inc_build)/OpenHome/Net/Private/CpiDevice.h \
	$(inc_build)/OpenHome/Net/Private/CpiDeviceDv.h \
	$(inc_build)/OpenHome/Net/Private/CpiDeviceLpec.h \
	$(inc_build)/OpenHome/Net/Private/CpiDeviceUpnp.h \
	$(inc_build)/OpenHome/Net/Private/CpiService.h \
	$(inc_build)/OpenHome/Net/Private/CpiStack.h \
	$(inc_build)/OpenHome/Net/Private/CpiSubscription.h \
	$(inc_build)/OpenHome/Net/Private/DeviceXml.h \
	$(inc_build)/OpenHome/Net/Private/Discovery.h \
	$(inc_build)/OpenHome/Net/Private/DviDevice.h \
	$(inc_build)/OpenHome/Net/Private/DviProtocolUpnp.h \
	$(inc_build)/OpenHome/Net/Private/DviServer.h \
	$(inc_build)/OpenHome/Net/Private/DviServerUpnp.h \
	$(inc_build)/OpenHome/Net/Private/DviServerWebSocket.h \
	$(inc_build)/OpenHome/Net/Private/DviProtocolLpec.h \
	$(inc_build)/OpenHome/Net/Private/DviServerLpec.h \
	$(inc_build)/OpenHome/Net/Private/DviService.h \
	$(inc_build)/OpenHome/Net/Private/DviSsdpNotifier.h \
	$(inc_build)/OpenHome/Net/Private/DviStack.h \
	$(inc_build)/OpenHome/Net/Private/DviSubscription.h \
	$(inc_build)/OpenHome/Net/Private/DviPropertyUpdateCollection.h \
	$(inc_build)/OpenHome/Net/Private/DviProviderSubscriptionLongPoll.h \
	$(inc_build)/OpenHome/Net/Private/Error.h \
	$(inc_build)/OpenHome/Net/Private/EventUpnp.h \
	$(inc_build)/OpenHome/Net/Private/FunctorCpiDevice.h \
	$(inc_build)/OpenHome/Net/Private/FunctorDviInvocation.h \
	$(inc_build)/OpenHome/Net/Private/MdnsPlatform.h \
	$(inc_build)/OpenHome/Net/Private/MdnsProvider.h \
	$(inc_build)/OpenHome/Net/Private/ProtocolUpnp.h \
	$(inc_build)/OpenHome/Net/Private/Service.h \
	$(inc_build)/OpenHome/Net/Private/Ssdp.h \
	$(inc_build)/OpenHome/Private/Env.h \
	$(inc_build)/OpenHome/Net/Private/Subscription.h \
	$(inc_build)/OpenHome/Net/Private/XmlFetcher.h \
	$(inc_build)/OpenHome/Net/Private/XmlParser.h \
	$(inc_build)/OpenHome/Net/C/Async.h \
	$(inc_build)/OpenHome/Net/C/CpDevice.h \
	$(inc_build)/OpenHome/Net/C/CpDeviceDv.h \
	$(inc_build)/OpenHome/Net/C/CpDeviceUpnp.h \
	$(inc_build)/OpenHome/Net/C/CpProxy.h \
	$(inc_build)/OpenHome/Net/C/CpService.h \
	$(inc_build)/OpenHome/Net/C/DvDevice.h \
	$(inc_build)/OpenHome/Net/C/DvProvider.h \
	$(inc_build)/OpenHome/Net/C/DvServerUpnp.h \
	$(inc_build)/OpenHome/Net/C/OhNet.h \
	$(inc_build)/OpenHome/Net/C/Service.h \
	$(inc_build)/OpenHome/Net/Cpp/FunctorAsync.h \
	$(inc_build)/OpenHome/Net/Cpp/OhNet.h \
	$(inc_build)/OpenHome/Net/Cpp/CpDevice.h \
	$(inc_build)/OpenHome/Net/Cpp/CpDeviceDv.h \
	$(inc_build)/OpenHome/Net/Cpp/CpDeviceUpnp.h \
	$(inc_build)/OpenHome/Net/Cpp/CpProxy.h \
	$(inc_build)/OpenHome/Net/Cpp/DvDevice.h \
	$(inc_build)/OpenHome/Net/Cpp/DvProvider.h \
	$(inc_build)/OpenHome/Net/Cpp/DvResourceWriter.h \
	$(inc_build)/OpenHome/Net/Cpp/DvServerUpnp.h \
	$(inc_build)/OpenHome/Net/Cpp/FunctorCpDevice.h \
	$(inc_build)/OpenHome/Net/Core/FunctorAsync.h \
	$(inc_build)/OpenHome/Net/Core/OhNet.h \
	$(inc_build)/OpenHome/Net/Core/CpDevice.h \
	$(inc_build)/OpenHome/Net/Core/CpDeviceDv.h \
	$(inc_build)/OpenHome/Net/Core/CpDeviceUpnp.h \
	$(inc_build)/OpenHome/Net/Core/CpProxy.h \
	$(inc_build)/OpenHome/Net/Core/DvDevice.h \
	$(inc_build)/OpenHome/Net/Core/DvInvocationResponse.h \
	$(inc_build)/OpenHome/Net/Core/DvProvider.h \
	$(inc_build)/OpenHome/Net/Core/DvResourceWriter.h \
	$(inc_build)/OpenHome/Net/Core/DvServerUpnp.h \
	$(inc_build)/OpenHome/Net/Core/FunctorCpDevice.h


ohNetCore : make_obj_dir copy_build_includes patch_thirdparty_sources $(objects_core) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)$(libprefix)ohNetCore.$(libext) : $(objects_core)
	$(ar)$(libprefix)ohNetCore.$(libext) $(objects_core)
$(objdir)Ascii.$(objext) : OpenHome/Ascii.cpp $(headers)
	$(compiler)Ascii.$(objext) -c $(cppflags) $(includes) OpenHome/Ascii.cpp
$(objdir)AsyncC.$(objext) : OpenHome/Net/Bindings/C/AsyncC.cpp $(headers)
	$(compiler)AsyncC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/AsyncC.cpp
$(objdir)AsyncPrivate.$(objext) : OpenHome/Net/ControlPoint/AsyncPrivate.cpp $(headers)
	$(compiler)AsyncPrivate.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/AsyncPrivate.cpp
$(objdir)Bonjour.$(objext) : OpenHome/Net/Device/Bonjour/Bonjour.cpp $(headers)
	$(compiler)Bonjour.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Bonjour/Bonjour.cpp
$(objdir)Buffer.$(objext) : OpenHome/Buffer.cpp $(headers)
	$(compiler)Buffer.$(objext) -c $(cppflags) $(includes) OpenHome/Buffer.cpp
$(objdir)Converter.$(objext) : OpenHome/Converter.cpp $(headers)
	$(compiler)Converter.$(objext) -c $(cppflags) $(includes) OpenHome/Converter.cpp
$(objdir)Crc32.$(objext) : OpenHome/Crc32.cpp $(headers)
	$(compiler)Crc32.$(objext) -c $(cppflags) $(includes) OpenHome/Crc32.cpp
$(objdir)cencode.$(objext) : thirdparty/libb64/cencode.c $(headers)
	$(compiler)cencode.$(objext) -c $(cflags_third_party) $(includes) thirdparty/libb64/cencode.c
$(objdir)cdecode.$(objext) : thirdparty/libb64/cdecode.c $(headers)
	$(compiler)cdecode.$(objext) -c $(cflags_third_party) $(includes) thirdparty/libb64/cdecode.c
$(objdir)Discovery.$(objext) : OpenHome/Net/Discovery.cpp $(headers)
	$(compiler)Discovery.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Discovery.cpp
$(objdir)Debug.$(objext) : OpenHome/Debug.cpp $(headers)
	$(compiler)Debug.$(objext) -c $(cppflags) $(includes) OpenHome/Debug.cpp
$(objdir)CpDeviceCore.$(objext) : OpenHome/Net/ControlPoint/CpDeviceCore.cpp $(headers)
	$(compiler)CpDeviceCore.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/CpDeviceCore.cpp
$(objdir)CpDeviceC.$(objext) : OpenHome/Net/Bindings/C/ControlPoint/CpDeviceC.cpp $(headers)
	$(compiler)CpDeviceC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/ControlPoint/CpDeviceC.cpp
$(objdir)CpDeviceStd.$(objext) : OpenHome/Net/Bindings/Cpp/ControlPoint/CpDeviceStd.cpp $(headers)
	$(compiler)CpDeviceStd.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/Cpp/ControlPoint/CpDeviceStd.cpp
$(objdir)CpDeviceDvCore.$(objext) : OpenHome/Net/ControlPoint/CpDeviceDvCore.cpp $(headers)
	$(compiler)CpDeviceDvCore.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/CpDeviceDvCore.cpp
$(objdir)CpDeviceDvStd.$(objext) : OpenHome/Net/Bindings/Cpp/ControlPoint/CpDeviceDvStd.cpp $(headers)
	$(compiler)CpDeviceDvStd.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/Cpp/ControlPoint/CpDeviceDvStd.cpp
$(objdir)CpDeviceDvC.$(objext) : OpenHome/Net/Bindings/C/ControlPoint/CpDeviceDvC.cpp $(headers)
	$(compiler)CpDeviceDvC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/ControlPoint/CpDeviceDvC.cpp
$(objdir)CpDeviceUpnpCore.$(objext) : OpenHome/Net/ControlPoint/CpDeviceUpnpCore.cpp $(headers)
	$(compiler)CpDeviceUpnpCore.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/CpDeviceUpnpCore.cpp
$(objdir)CpDeviceUpnpC.$(objext) : OpenHome/Net/Bindings/C/ControlPoint/CpDeviceUpnpC.cpp $(headers)
	$(compiler)CpDeviceUpnpC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/ControlPoint/CpDeviceUpnpC.cpp
$(objdir)CpDeviceUpnpStd.$(objext) : OpenHome/Net/Bindings/Cpp/ControlPoint/CpDeviceUpnpStd.cpp $(headers)
	$(compiler)CpDeviceUpnpStd.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/Cpp/ControlPoint/CpDeviceUpnpStd.cpp
$(objdir)CpiDevice.$(objext) : OpenHome/Net/ControlPoint/CpiDevice.cpp $(headers)
	$(compiler)CpiDevice.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/CpiDevice.cpp
$(objdir)CpiDeviceDv.$(objext) : OpenHome/Net/ControlPoint/Dv/CpiDeviceDv.cpp $(headers)
	$(compiler)CpiDeviceDv.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Dv/CpiDeviceDv.cpp
$(objdir)CpiDeviceLpec.$(objext) : OpenHome/Net/ControlPoint/Lpec/CpiDeviceLpec.cpp $(headers)
	$(compiler)CpiDeviceLpec.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Lpec/CpiDeviceLpec.cpp
$(objdir)CpiDeviceUpnp.$(objext) : OpenHome/Net/ControlPoint/Upnp/CpiDeviceUpnp.cpp $(headers)
	$(compiler)CpiDeviceUpnp.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Upnp/CpiDeviceUpnp.cpp
$(objdir)CpiService.$(objext) : OpenHome/Net/ControlPoint/CpiService.cpp $(headers)
	$(compiler)CpiService.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/CpiService.cpp
$(objdir)CpiStack.$(objext) : OpenHome/Net/ControlPoint/CpiStack.cpp $(headers)
	$(compiler)CpiStack.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/CpiStack.cpp
$(objdir)CpiSubscription.$(objext) : OpenHome/Net/ControlPoint/CpiSubscription.cpp $(headers)
	$(compiler)CpiSubscription.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/CpiSubscription.cpp
$(objdir)CpProxy.$(objext) : OpenHome/Net/ControlPoint/CpProxy.cpp $(headers)
	$(compiler)CpProxy.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/CpProxy.cpp
$(objdir)CpProxyC.$(objext) : OpenHome/Net/Bindings/C/ControlPoint/CpProxyC.cpp $(headers)
	$(compiler)CpProxyC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/ControlPoint/CpProxyC.cpp
$(objdir)CpServiceC.$(objext) : OpenHome/Net/Bindings/C/ControlPoint/CpServiceC.cpp $(headers)
	$(compiler)CpServiceC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/ControlPoint/CpServiceC.cpp
$(objdir)DvDevice.$(objext) : OpenHome/Net/Device/DvDevice.cpp $(headers)
	$(compiler)DvDevice.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/DvDevice.cpp
$(objdir)DvDeviceStd.$(objext) : OpenHome/Net/Bindings/Cpp/Device/DvDeviceStd.cpp $(headers)
	$(compiler)DvDeviceStd.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/Cpp/Device/DvDeviceStd.cpp
$(objdir)DvDeviceC.$(objext) : OpenHome/Net/Bindings/C/Device/DvDeviceC.cpp $(headers)
	$(compiler)DvDeviceC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/Device/DvDeviceC.cpp
$(objdir)DviDevice.$(objext) : OpenHome/Net/Device/DviDevice.cpp $(headers)
	$(compiler)DviDevice.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/DviDevice.cpp
$(objdir)DvInvocationC.$(objext) : OpenHome/Net/Bindings/C/Device/DvInvocationC.cpp $(headers)
	$(compiler)DvInvocationC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/Device/DvInvocationC.cpp
$(objdir)DvInvocationStd.$(objext) : OpenHome/Net/Bindings/Cpp/Device/DvInvocationStd.cpp $(headers)
	$(compiler)DvInvocationStd.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/Cpp/Device/DvInvocationStd.cpp
$(objdir)DviProtocolUpnp.$(objext) : OpenHome/Net/Device/Upnp/DviProtocolUpnp.cpp $(headers)
	$(compiler)DviProtocolUpnp.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Upnp/DviProtocolUpnp.cpp
$(objdir)DviProviderSubscriptionLongPoll.$(objext) : OpenHome/Net/Device/DviProviderSubscriptionLongPoll.cpp $(objdir)DvOpenhomeOrgSubscriptionLongPoll1.$(objext)  $(headers)
	$(compiler)DviProviderSubscriptionLongPoll.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/DviProviderSubscriptionLongPoll.cpp
$(objdir)DviServer.$(objext) : OpenHome/Net/Device/DviServer.cpp $(headers)
	$(compiler)DviServer.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/DviServer.cpp
$(objdir)DviServerUpnp.$(objext) : OpenHome/Net/Device/Upnp/DviServerUpnp.cpp $(headers)
	$(compiler)DviServerUpnp.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Upnp/DviServerUpnp.cpp
$(objdir)DviServerWebSocket.$(objext) : OpenHome/Net/Device/Upnp/DviServerWebSocket.cpp $(headers)
	$(compiler)DviServerWebSocket.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Upnp/DviServerWebSocket.cpp
$(objdir)DviProtocolLpec.$(objext) : OpenHome/Net/Device/Lpec/DviProtocolLpec.cpp $(headers)
	$(compiler)DviProtocolLpec.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Lpec/DviProtocolLpec.cpp
$(objdir)DviServerLpec.$(objext) : OpenHome/Net/Device/Lpec/DviServerLpec.cpp $(headers)
	$(compiler)DviServerLpec.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Lpec/DviServerLpec.cpp
$(objdir)DviService.$(objext) : OpenHome/Net/Device/DviService.cpp $(headers)
	$(compiler)DviService.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/DviService.cpp
$(objdir)DviSsdpNotifier.$(objext) : OpenHome/Net/Device/Upnp/DviSsdpNotifier.cpp $(headers)
	$(compiler)DviSsdpNotifier.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Upnp/DviSsdpNotifier.cpp
$(objdir)DviStack.$(objext) : OpenHome/Net/Device/DviStack.cpp $(headers)
	$(compiler)DviStack.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/DviStack.cpp
$(objdir)DviSubscription.$(objext) : OpenHome/Net/Device/DviSubscription.cpp $(headers)
	$(compiler)DviSubscription.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/DviSubscription.cpp
$(objdir)DviPropertyUpdateCollection.$(objext) : OpenHome/Net/Device/DviPropertyUpdateCollection.cpp $(headers)
	$(compiler)DviPropertyUpdateCollection.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/DviPropertyUpdateCollection.cpp
$(objdir)DvProvider.$(objext) : OpenHome/Net/Device/DvProvider.cpp $(headers)
	$(compiler)DvProvider.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/DvProvider.cpp
$(objdir)DvProviderC.$(objext) : OpenHome/Net/Bindings/C/Device/DvProviderC.cpp $(headers)
	$(compiler)DvProviderC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/Device/DvProviderC.cpp
$(objdir)DvServerUpnp.$(objext) : OpenHome/Net/Device/DvServerUpnp.cpp $(headers)
	$(compiler)DvServerUpnp.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/DvServerUpnp.cpp
$(objdir)DvServerUpnpC.$(objext) : OpenHome/Net/Bindings/C/Device/DvServerUpnpC.cpp $(headers)
	$(compiler)DvServerUpnpC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/Device/DvServerUpnpC.cpp
$(objdir)DeviceXml.$(objext) : OpenHome/Net/ControlPoint/Upnp/DeviceXml.cpp $(headers)
	$(compiler)DeviceXml.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Upnp/DeviceXml.cpp
$(objdir)Error.$(objext) : OpenHome/Net/Error.cpp $(headers)
	$(compiler)Error.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Error.cpp
$(objdir)EventUpnp.$(objext) : OpenHome/Net/ControlPoint/Upnp/EventUpnp.cpp $(headers)
	$(compiler)EventUpnp.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Upnp/EventUpnp.cpp
$(objdir)Exception.$(objext) : OpenHome/Exception.cpp $(headers)
	$(compiler)Exception.$(objext) -c $(cppflags) $(includes) OpenHome/Exception.cpp
$(objdir)Fifo.$(objext) : OpenHome/Fifo.cpp $(headers)
	$(compiler)Fifo.$(objext) -c $(cppflags) $(includes) OpenHome/Fifo.cpp
$(objdir)FileAnsi.$(objext) : OpenHome/FileAnsi.cpp $(headers)
	$(compiler)FileAnsi.$(objext) -c $(cppflags) $(includes) OpenHome/FileAnsi.cpp
$(objdir)FileBrx.$(objext) : OpenHome/FileBrx.cpp $(headers)
	$(compiler)FileBrx.$(objext) -c $(cppflags) $(includes) OpenHome/FileBrx.cpp
$(objdir)FileStream.$(objext) : OpenHome/FileStream.cpp $(headers)
	$(compiler)FileStream.$(objext) -c $(cppflags) $(includes) OpenHome/FileStream.cpp
$(objdir)Globals.$(objext) : OpenHome/Net/Globals.cpp $(headers)
	$(compiler)Globals.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Globals.cpp
$(objdir)Http.$(objext) : OpenHome/Http.cpp $(headers)
	$(compiler)Http.$(objext) -c $(cppflags) $(includes) OpenHome/Http.cpp
$(objdir)anonymous.$(objext) : $(mDNSdir)/anonymous.c $(headers)
	$(compiler)anonymous.$(objext) -c $(cflags_third_party) $(includes) $(mDNSdir)/anonymous.c
$(objdir)CryptoAlg.$(objext) : $(mDNSdir)/CryptoAlg.c $(headers)
	$(compiler)CryptoAlg.$(objext) -c $(cflags_third_party) $(includes) $(mDNSdir)/CryptoAlg.c
$(objdir)DNSCommon.$(objext) : $(mDNSdir)/DNSCommon.c $(headers)
	$(compiler)DNSCommon.$(objext) -c $(cflags_third_party) $(includes) $(mDNSdir)/DNSCommon.c
$(objdir)DNSDigest.$(objext) : $(mDNSdir)/DNSDigest.c $(headers)
	$(compiler)DNSDigest.$(objext) -c $(cflags_third_party) $(includes) $(mDNSdir)/DNSDigest.c
$(objdir)mDNS.$(objext) : $(mDNSdir)/mDNS.c $(headers)
	$(compiler)mDNS.$(objext) -c $(cflags_third_party) $(includes) $(mDNSdir)/mDNS.c
$(objdir)nsec.$(objext) : $(mDNSdir)/nsec.c $(headers)
	$(compiler)nsec.$(objext) -c $(cflags_third_party) $(includes) $(mDNSdir)/nsec.c
$(objdir)nsec3.$(objext) : $(mDNSdir)/nsec3.c $(headers)
	$(compiler)nsec3.$(objext) -c $(cflags_third_party) $(includes) $(mDNSdir)/nsec3.c
$(objdir)uDNS.$(objext) : $(mDNSdir)/uDNS.c $(headers)
	$(compiler)uDNS.$(objext) -c $(cflags_third_party) $(includes) $(mDNSdir)/uDNS.c
$(objdir)dnssd_clientshim.$(objext) : $(mDNSdir)/dnssd_clientshim.c $(headers)
	$(compiler)dnssd_clientshim.$(objext) -c $(cflags_third_party) $(includes) $(mDNSdir)/dnssd_clientshim.c
$(objdir)dnssd_clientlib.$(objext) : $(mDNSdir)/dnssd_clientlib.c $(headers)
	$(compiler)dnssd_clientlib.$(objext) -c $(cflags_third_party) $(includes) $(mDNSdir)/dnssd_clientlib.c
$(objdir)MdnsPlatform.$(objext) : OpenHome/Net/Device/Bonjour/MdnsPlatform.cpp $(headers)
	$(compiler)MdnsPlatform.$(objext) -c $(cflags_third_party) $(includes) OpenHome/Net/Device/Bonjour/MdnsPlatform.cpp
$(objdir)MdnsProvider.$(objext) : OpenHome/Net/Device/Bonjour/MdnsProvider.cpp $(headers)
	$(compiler)MdnsProvider.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Bonjour/MdnsProvider.cpp
$(objdir)Md5.$(objext) : OpenHome/md5.c $(headers)
	$(compiler)Md5.$(objext) -c $(cflags_third_party) $(includes) OpenHome/md5.c
$(objdir)NetworkAdapterList.$(objext) : OpenHome/NetworkAdapterList.cpp $(headers)
	$(compiler)NetworkAdapterList.$(objext) -c $(cppflags) $(includes) OpenHome/NetworkAdapterList.cpp
$(objdir)DnsChangeNotifier.$(objext) : OpenHome/DnsChangeNotifier.cpp $(headers)
	$(compiler)DnsChangeNotifier.$(objext) -c $(cppflags) $(includes) OpenHome/DnsChangeNotifier.cpp
$(objdir)Network.$(objext) : OpenHome/Network.cpp $(headers)
	$(compiler)Network.$(objext) -c $(cppflags) $(includes) OpenHome/Network.cpp
$(objdir)Parser.$(objext) : OpenHome/Parser.cpp $(headers)
	$(compiler)Parser.$(objext) -c $(cppflags) $(includes) OpenHome/Parser.cpp
$(objdir)Printer.$(objext) : OpenHome/Printer.cpp $(headers)
	$(compiler)Printer.$(objext) -c $(cppflags) $(includes) OpenHome/Printer.cpp
$(objdir)ProtocolUpnp.$(objext) : OpenHome/Net/ControlPoint/Upnp/ProtocolUpnp.cpp $(headers)
	$(compiler)ProtocolUpnp.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Upnp/ProtocolUpnp.cpp
$(objdir)Queue.$(objext) : OpenHome/Queue.cpp $(headers)
	$(compiler)Queue.$(objext) -c $(cppflags) $(includes) OpenHome/Queue.cpp
$(objdir)Service.$(objext) : OpenHome/Net/Service.cpp $(headers)
	$(compiler)Service.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Service.cpp
$(objdir)ServiceC.$(objext) : OpenHome/Net/Bindings/C/ServiceC.cpp $(headers)
	$(compiler)ServiceC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/ServiceC.cpp
$(objdir)sha1.$(objext) : OpenHome/sha1.c $(headers)
	$(compiler)sha1.$(objext) -c $(cflags_third_party) $(includes) OpenHome/sha1.c
$(objdir)Ssdp.$(objext) : OpenHome/Net/Ssdp.cpp $(headers)
	$(compiler)Ssdp.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Ssdp.cpp
$(objdir)SsdpDv.$(objext) : OpenHome/Net/SsdpDv.cpp $(headers)
	$(compiler)SsdpDv.$(objext) -c $(cppflags) $(includes) OpenHome/Net/SsdpDv.cpp
$(objdir)Env.$(objext) : OpenHome/Env.cpp $(headers)
	$(compiler)Env.$(objext) -c $(cppflags) $(includes) OpenHome/Env.cpp
$(objdir)Stream.$(objext) : OpenHome/Stream.cpp $(headers)
	$(compiler)Stream.$(objext) -c $(cppflags) $(includes) OpenHome/Stream.cpp
$(objdir)Subscription.$(objext) : OpenHome/Net/Subscription.cpp $(headers)
	$(compiler)Subscription.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Subscription.cpp
$(objdir)Terminal.$(objext) : OpenHome/Terminal.cpp $(headers)
	$(compiler)Terminal.$(objext) -c $(cppflags) $(includes) OpenHome/Terminal.cpp
$(objdir)Thread.$(objext) : OpenHome/Thread.cpp $(headers)
	$(compiler)Thread.$(objext) -c $(cppflags) $(includes) OpenHome/Thread.cpp
$(objdir)Timer.$(objext) : OpenHome/Timer.cpp $(headers)
	$(compiler)Timer.$(objext) -c $(cppflags) $(includes) OpenHome/Timer.cpp
$(objdir)TIpAddressUtils.$(objext) : OpenHome/TIpAddressUtils.cpp $(headers)
	$(compiler)TIpAddressUtils.$(objext) -c $(cppflags) $(includes) OpenHome/TIpAddressUtils.cpp
$(objdir)Uri.$(objext) : OpenHome/Uri.cpp $(headers)
	$(compiler)Uri.$(objext) -c $(cppflags) $(includes) OpenHome/Uri.cpp
$(objdir)XmlParser.$(objext) : OpenHome/Net/XmlParser.cpp $(headers)
	$(compiler)XmlParser.$(objext) -c $(cppflags) $(includes) OpenHome/Net/XmlParser.cpp
$(objdir)XmlFetcher.$(objext) : OpenHome/Net/ControlPoint/Upnp/XmlFetcher.cpp $(headers)
	$(compiler)XmlFetcher.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Upnp/XmlFetcher.cpp
$(objdir)OhNet.$(objext) : OpenHome/Net/OhNet.cpp $(headers)
	$(compiler)OhNet.$(objext) -c $(cppflags) $(includes) OpenHome/Net/OhNet.cpp
$(objdir)OhNetCp.$(objext) : OpenHome/Net/OhNetCp.cpp $(headers)
	$(compiler)OhNetCp.$(objext) -c $(cppflags) $(includes) OpenHome/Net/OhNetCp.cpp
$(objdir)OhNetDv.$(objext) : OpenHome/Net/OhNetDv.cpp $(headers)
	$(compiler)OhNetDv.$(objext) -c $(cppflags) $(includes) OpenHome/Net/OhNetDv.cpp
$(objdir)OhNetCombined.$(objext) : OpenHome/Net/OhNetCombined.cpp $(headers)
	$(compiler)OhNetCombined.$(objext) -c $(cppflags) $(includes) OpenHome/Net/OhNetCombined.cpp
$(objdir)OhNetC.$(objext) : OpenHome/Net/Bindings/C/OhNetC.cpp $(headers)
	$(compiler)OhNetC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/OhNetC.cpp
$(objdir)OhNetCCp.$(objext) : OpenHome/Net/Bindings/C/OhNetCCp.cpp $(headers)
	$(compiler)OhNetCCp.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/OhNetCCp.cpp
$(objdir)OhNetCDv.$(objext) : OpenHome/Net/Bindings/C/OhNetCDv.cpp $(headers)
	$(compiler)OhNetCDv.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/OhNetCDv.cpp
$(objdir)OhNetCCombined.$(objext) : OpenHome/Net/Bindings/C/OhNetCCombined.cpp $(headers)
	$(compiler)OhNetCCombined.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/OhNetCCombined.cpp
$(objdir)OsWrapper.$(objext) : Os/OsWrapper.cpp $(headers)
	$(compiler)OsWrapper.$(objext) -c $(cppflags) $(includes) Os/OsWrapper.cpp
$(objdir)Os.$(objext) : Os/$(osdir)/Os.c $(headers)
	$(compiler)Os.$(objext) -c $(cflags_third_party) $(includes) Os/$(osdir)/Os.c
$(objdir)File.$(objext) : Os/$(osdir)/File.cpp $(headers)
	$(compiler)File.$(objext) -c $(cppflags) $(includes) Os/$(osdir)/File.cpp
$(objdir)TerminalOs.$(objext) : Os/$(osdir)/TerminalOs.cpp $(headers)
	$(compiler)TerminalOs.$(objext) -c $(cppflags) $(includes) Os/$(osdir)/TerminalOs.cpp
$(objdir)SignalHandlers.$(objext) : Os/$(osdir)/SignalHandlers.cpp $(headers)
	$(compiler)SignalHandlers.$(objext) -c $(cppflags) $(includes) Os/$(osdir)/SignalHandlers.cpp
$(objdir)Shell.$(objext) : OpenHome/Shell/Shell.cpp $(headers)
	$(compiler)Shell.$(objext) -c $(cppflags) $(includes) OpenHome/Shell/Shell.cpp
$(objdir)InfoProvider.$(objext) : OpenHome/Shell/InfoProvider.cpp $(headers)
	$(compiler)InfoProvider.$(objext) -c $(cppflags) $(includes) OpenHome/Shell/InfoProvider.cpp
$(objdir)ShellCommandDebug.$(objext) : OpenHome/Shell/ShellCommandDebug.cpp $(headers)
	$(compiler)ShellCommandDebug.$(objext) -c $(cppflags) $(includes) OpenHome/Shell/ShellCommandDebug.cpp

ohNetDllImpl: ohNetCore
	$(link_dll) $(linkopts_ohNet) $(linkoutput)$(objdir)$(dllprefix)ohNet.$(dllext) $(objects_core)



ohNet: proxies devices
	$(ar)$(libprefix)ohNet.$(libext) $(objects_core) $(objects_proxies) $(objects_devices)

TestFramework: $(libprefix)TestFramework.$(libext)

objects_test_framework =                        \
    $(objdir)TestFramework.$(objext)            \
    $(objdir)Main.$(objext)                     \
    $(objdir)OptionParser.$(objext)             \
    $(objdir)SuiteUnitTest.$(objext)            \
    $(objdir)TimerFactoryMock.$(objext)         \
    $(objdir)ShellCommandRun.$(objext)          \
    $(objdir)ShellCommandQuit.$(objext)         \
    $(objdir)ShellCommandWatchDog.$(objext)     \
    $(objdir)TestBasicDvCore.$(objext)          \
    $(objdir)DvOpenhomeOrgTestBasic1.$(objext)  \
    $(objdir)CpOpenhomeOrgTestBasic1.$(objext) 

$(libprefix)TestFramework.$(libext): $(objects_test_framework)
	$(ar)$(libprefix)TestFramework.$(libext) $(objects_test_framework)
$(objdir)TestFramework.$(objext) : OpenHome/TestFramework/TestFramework.cpp $(headers)
	$(compiler)TestFramework.$(objext) -c $(cppflags) $(includes) OpenHome/TestFramework/TestFramework.cpp
$(objdir)Main.$(objext) : Os/$(osdir)/Main.cpp $(headers)
	$(compiler)Main.$(objext) -c $(cppflags) $(includes) Os/$(osdir)/Main.cpp
$(objdir)OptionParser.$(objext) : OpenHome/TestFramework/OptionParser.cpp $(headers)
	$(compiler)OptionParser.$(objext) -c $(cppflags) $(includes) OpenHome/TestFramework/OptionParser.cpp
$(objdir)SuiteUnitTest.$(objext) : OpenHome/TestFramework/SuiteUnitTest.cpp $(headers)
	$(compiler)SuiteUnitTest.$(objext) -c $(cppflags) $(includes) OpenHome/TestFramework/SuiteUnitTest.cpp
$(objdir)TimerFactoryMock.$(objext) : OpenHome/TestFramework/TimerFactoryMock.cpp $(headers)
	$(compiler)TimerFactoryMock.$(objext) -c $(cppflags) $(includes) OpenHome/TestFramework/TimerFactoryMock.cpp
$(objdir)ShellCommandRun.$(objext) : OpenHome/Shell/ShellCommandRun.cpp $(headers)
	$(compiler)ShellCommandRun.$(objext) -c $(cppflags) $(includes) OpenHome/Shell/ShellCommandRun.cpp
$(objdir)ShellCommandQuit.$(objext) : OpenHome/Shell/ShellCommandQuit.cpp $(headers)
	$(compiler)ShellCommandQuit.$(objext) -c $(cppflags) $(includes) OpenHome/Shell/ShellCommandQuit.cpp
$(objdir)ShellCommandWatchDog.$(objext) : OpenHome/Shell/ShellCommandWatchDog.cpp $(headers)
	$(compiler)ShellCommandWatchDog.$(objext) -c $(cppflags) $(includes) OpenHome/Shell/ShellCommandWatchDog.cpp

TestBuffer: $(objdir)TestBuffer.$(exeext)
$(objdir)TestBuffer.$(exeext) :  ohNetCore $(objdir)TestBuffer.$(objext) $(objdir)TestBufferMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestBuffer.$(exeext) $(objdir)TestBufferMain.$(objext) $(objdir)TestBuffer.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestBuffer.$(objext) : OpenHome/Tests/TestBuffer.cpp $(headers)
	$(compiler)TestBuffer.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestBuffer.cpp
$(objdir)TestBufferMain.$(objext) : OpenHome/Tests/TestBufferMain.cpp $(headers)
	$(compiler)TestBufferMain.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestBufferMain.cpp

TestPrinter: $(objdir)TestPrinter.$(exeext)
$(objdir)TestPrinter.$(exeext) :  ohNetCore $(objdir)TestPrinter.$(objext) $(objdir)TestPrinterMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestPrinter.$(exeext) $(objdir)TestPrinterMain.$(objext) $(objdir)TestPrinter.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestPrinter.$(objext) : OpenHome/Tests/TestPrinter.cpp $(headers)
	$(compiler)TestPrinter.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestPrinter.cpp
$(objdir)TestPrinterMain.$(objext) : OpenHome/Tests/TestPrinterMain.cpp $(headers)
	$(compiler)TestPrinterMain.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestPrinterMain.cpp

TestException: $(objdir)TestException.$(exeext)
$(objdir)TestException.$(exeext) :  ohNetCore $(objdir)TestException.$(objext) $(objdir)TestExceptionMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestException.$(exeext) $(objdir)TestExceptionMain.$(objext) $(objdir)TestException.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestException.$(objext) : OpenHome/Tests/TestException.cpp $(headers)
	$(compiler)TestException.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestException.cpp
$(objdir)TestExceptionMain.$(objext) : OpenHome/Tests/TestExceptionMain.cpp $(headers)
	$(compiler)TestExceptionMain.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestExceptionMain.cpp

TestFunctorGeneric: $(objdir)TestFunctorGeneric.$(exeext)
$(objdir)TestFunctorGeneric.$(exeext) :  ohNetCore $(objdir)TestFunctorGeneric.$(objext) $(objdir)TestFunctorGenericMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestFunctorGeneric.$(exeext) $(objdir)TestFunctorGenericMain.$(objext) $(objdir)TestFunctorGeneric.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestFunctorGeneric.$(objext) : OpenHome/Tests/TestFunctorGeneric.cpp $(headers)
	$(compiler)TestFunctorGeneric.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestFunctorGeneric.cpp
$(objdir)TestFunctorGenericMain.$(objext) : OpenHome/Tests/TestFunctorGenericMain.cpp $(headers)
	$(compiler)TestFunctorGenericMain.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestFunctorGenericMain.cpp

TestFile: $(objdir)TestFile.$(exeext)
$(objdir)TestFile.$(exeext) :  ohNetCore $(objdir)TestFile.$(objext) $(objdir)TestFileMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestFile.$(exeext) $(objdir)TestFileMain.$(objext) $(objdir)TestFile.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestFile.$(objext) : OpenHome/Tests/TestFile.cpp $(headers)
	$(compiler)TestFile.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestFile.cpp
$(objdir)TestFileMain.$(objext) : OpenHome/Tests/TestFileMain.cpp $(headers)
	$(compiler)TestFileMain.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestFileMain.cpp

TestThread: $(objdir)TestThread.$(exeext)
$(objdir)TestThread.$(exeext) :  ohNetCore $(objdir)TestThread.$(objext) $(objdir)TestThreadMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestThread.$(exeext) $(objdir)TestThreadMain.$(objext) $(objdir)TestThread.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestThread.$(objext) : OpenHome/Tests/TestThread.cpp $(headers)
	$(compiler)TestThread.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestThread.cpp
$(objdir)TestThreadMain.$(objext) : OpenHome/Tests/TestThreadMain.cpp $(headers)
	$(compiler)TestThreadMain.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestThreadMain.cpp

TestQueue: $(objdir)TestQueue.$(exeext)
$(objdir)TestQueue.$(exeext) :  ohNetCore $(objdir)TestQueue.$(objext) $(objdir)TestQueueMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestQueue.$(exeext) $(objdir)TestQueueMain.$(objext) $(objdir)TestQueue.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestQueue.$(objext) : OpenHome/Tests/TestQueue.cpp $(headers)
	$(compiler)TestQueue.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestQueue.cpp
$(objdir)TestQueueMain.$(objext) : OpenHome/Tests/TestQueueMain.cpp $(headers)
	$(compiler)TestQueueMain.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestQueueMain.cpp

TestFifo: $(objdir)TestFifo.$(exeext)
$(objdir)TestFifo.$(exeext) :  ohNetCore $(objdir)TestFifo.$(objext) $(objdir)TestFifoMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestFifo.$(exeext) $(objdir)TestFifoMain.$(objext) $(objdir)TestFifo.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestFifo.$(objext) : OpenHome/Tests/TestFifo.cpp $(headers)
	$(compiler)TestFifo.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestFifo.cpp
$(objdir)TestFifoMain.$(objext) : OpenHome/Tests/TestFifoMain.cpp $(headers)
	$(compiler)TestFifoMain.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestFifoMain.cpp

TestStream: $(objdir)TestStream.$(exeext)
$(objdir)TestStream.$(exeext) :  ohNetCore $(objdir)TestStream.$(objext) $(objdir)TestStreamMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestStream.$(exeext) $(objdir)TestStreamMain.$(objext) $(objdir)TestStream.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestStream.$(objext) : OpenHome/Tests/TestStream.cpp $(headers)
	$(compiler)TestStream.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestStream.cpp
$(objdir)TestStreamMain.$(objext) : OpenHome/Tests/TestStreamMain.cpp $(headers)
	$(compiler)TestStreamMain.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestStreamMain.cpp

TestTextUtils: $(objdir)TestTextUtils.$(exeext)
$(objdir)TestTextUtils.$(exeext) :  ohNetCore $(objdir)TestTextUtils.$(objext) $(objdir)TestTextUtilsMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestTextUtils.$(exeext) $(objdir)TestTextUtilsMain.$(objext) $(objdir)TestTextUtils.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestTextUtils.$(objext) : OpenHome/Tests/TestTextUtils.cpp $(headers)
	$(compiler)TestTextUtils.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestTextUtils.cpp
$(objdir)TestTextUtilsMain.$(objext) : OpenHome/Tests/TestTextUtilsMain.cpp $(headers)
	$(compiler)TestTextUtilsMain.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestTextUtilsMain.cpp

TestEcho: $(objdir)TestEcho.$(exeext)
$(objdir)TestEcho.$(exeext) :  ohNetCore $(objdir)TestEcho.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestEcho.$(exeext) $(objdir)TestEcho.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestEcho.$(objext) : OpenHome/Tests/TestEcho.cpp $(headers)
	$(compiler)TestEcho.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestEcho.cpp

TestMulticast: $(objdir)TestMulticast.$(exeext)
$(objdir)TestMulticast.$(exeext) :  ohNetCore $(objdir)TestMulticast.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestMulticast.$(exeext) $(objdir)TestMulticast.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestMulticast.$(objext) : OpenHome/Tests/TestMulticast.cpp $(headers)
	$(compiler)TestMulticast.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestMulticast.cpp

TestNetwork: $(objdir)TestNetwork.$(exeext)
$(objdir)TestNetwork.$(exeext) :  ohNetCore $(objdir)TestNetwork.$(objext) $(objdir)TestNetworkMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestNetwork.$(exeext) $(objdir)TestNetworkMain.$(objext) $(objdir)TestNetwork.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestNetwork.$(objext) : OpenHome/Tests/TestNetwork.cpp $(headers)
	$(compiler)TestNetwork.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestNetwork.cpp
$(objdir)TestNetworkMain.$(objext) : OpenHome/Tests/TestNetworkMain.cpp $(headers)
	$(compiler)TestNetworkMain.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestNetworkMain.cpp

TestTimer: $(objdir)TestTimer.$(exeext)
$(objdir)TestTimer.$(exeext) :  ohNetCore $(objdir)TestTimer.$(objext) $(objdir)TestTimerMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestTimer.$(exeext) $(objdir)TestTimerMain.$(objext) $(objdir)TestTimer.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestTimer.$(objext) : OpenHome/Tests/TestTimer.cpp $(headers)
	$(compiler)TestTimer.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestTimer.cpp
$(objdir)TestTimerMain.$(objext) : OpenHome/Tests/TestTimerMain.cpp $(headers)
	$(compiler)TestTimerMain.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestTimerMain.cpp

TestTimerMock: $(objdir)TestTimerMock.$(exeext)
$(objdir)TestTimerMock.$(exeext) :  ohNetCore $(objdir)TestTimerMock.$(objext) $(objdir)TestTimerMockMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestTimerMock.$(exeext) $(objdir)TestTimerMockMain.$(objext) $(objdir)TestTimerMock.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestTimerMock.$(objext) : OpenHome/Tests/TestTimerMock.cpp $(headers)
	$(compiler)TestTimerMock.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestTimerMock.cpp
$(objdir)TestTimerMockMain.$(objext) : OpenHome/Tests/TestTimerMockMain.cpp $(headers)
	$(compiler)TestTimerMockMain.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestTimerMockMain.cpp

TestSsdpMListen: $(objdir)TestSsdpMListen.$(exeext)
$(objdir)TestSsdpMListen.$(exeext) :  ohNetCore $(objdir)TestSsdpMListen.$(objext) $(objdir)TestSsdpMListenMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestSsdpMListen.$(exeext) $(objdir)TestSsdpMListenMain.$(objext) $(objdir)TestSsdpMListen.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestSsdpMListen.$(objext) : OpenHome/Net/Tests/TestSsdpMListen.cpp $(headers)
	$(compiler)TestSsdpMListen.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Tests/TestSsdpMListen.cpp
$(objdir)TestSsdpMListenMain.$(objext) : OpenHome/Net/Tests/TestSsdpMListenMain.cpp $(headers)
	$(compiler)TestSsdpMListenMain.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Tests/TestSsdpMListenMain.cpp

TestSsdpUListen: $(objdir)TestSsdpUListen.$(exeext)
$(objdir)TestSsdpUListen.$(exeext) :  ohNetCore $(objdir)TestSsdpUListen.$(objext) $(objdir)TestSsdpUListenMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestSsdpUListen.$(exeext) $(objdir)TestSsdpUListenMain.$(objext) $(objdir)TestSsdpUListen.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestSsdpUListen.$(objext) : OpenHome/Net/Tests/TestSsdpUListen.cpp $(headers)
	$(compiler)TestSsdpUListen.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Tests/TestSsdpUListen.cpp
$(objdir)TestSsdpUListenMain.$(objext) : OpenHome/Net/Tests/TestSsdpUListenMain.cpp $(headers)
	$(compiler)TestSsdpUListenMain.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Tests/TestSsdpUListenMain.cpp

TestXmlParser: $(objdir)TestXmlParser.$(exeext)
$(objdir)TestXmlParser.$(exeext) :  ohNetCore $(objdir)TestXmlParser.$(objext) $(objdir)TestXmlParserMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestXmlParser.$(exeext) $(objdir)TestXmlParserMain.$(objext) $(objdir)TestXmlParser.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestXmlParser.$(objext) : OpenHome/Net/Tests/TestXmlParser.cpp $(headers)
	$(compiler)TestXmlParser.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Tests/TestXmlParser.cpp
$(objdir)TestXmlParserMain.$(objext) : OpenHome/Net/Tests/TestXmlParserMain.cpp $(headers)
	$(compiler)TestXmlParserMain.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Tests/TestXmlParserMain.cpp

TestDeviceList: $(objdir)TestDeviceList.$(exeext)
$(objdir)TestDeviceList.$(exeext) :  ohNetCore $(objdir)TestDeviceList.$(objext) $(objdir)TestDeviceListMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDeviceList.$(exeext) $(objdir)TestDeviceListMain.$(objext) $(objdir)TestDeviceList.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDeviceList.$(objext) : OpenHome/Net/ControlPoint/Tests/TestDeviceList.cpp $(headers)
	$(compiler)TestDeviceList.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Tests/TestDeviceList.cpp
$(objdir)TestDeviceListMain.$(objext) : OpenHome/Net/ControlPoint/Tests/TestDeviceListMain.cpp $(headers)
	$(compiler)TestDeviceListMain.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Tests/TestDeviceListMain.cpp

TestDeviceListC: $(objdir)TestDeviceListC.$(exeext)
$(objdir)TestDeviceListC.$(exeext) :  ohNetCore $(objdir)TestDeviceListC.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDeviceListC.$(exeext) $(objdir)TestDeviceListC.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDeviceListC.$(objext) : OpenHome/Net/Bindings/C/ControlPoint/Tests/TestDeviceListC.cpp $(headers)
	$(compiler)TestDeviceListC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/ControlPoint/Tests/TestDeviceListC.cpp

TestDeviceListStd: $(objdir)TestDeviceListStd.$(exeext)
$(objdir)TestDeviceListStd.$(exeext) :  ohNetCore $(objdir)TestDeviceListStd.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDeviceListStd.$(exeext) $(objdir)TestDeviceListStd.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDeviceListStd.$(objext) : OpenHome/Net/Bindings/Cpp/ControlPoint/Tests/TestDeviceListStd.cpp $(headers)
	$(compiler)TestDeviceListStd.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/Cpp/ControlPoint/Tests/TestDeviceListStd.cpp

TestDimmableLights: $(objdir)TestDimmableLights.$(exeext)
$(objdir)TestDimmableLights.$(exeext) :  ohNetCore $(objdir)TestDimmableLights.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDimmableLights.$(exeext) $(objdir)TestDimmableLights.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDimmableLights.$(objext) : OpenHome/Net/ControlPoint/Tests/TestDimmableLights.cpp $(headers)
	$(compiler)TestDimmableLights.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Tests/TestDimmableLights.cpp

TestInvocation: $(objdir)TestInvocation.$(exeext)
$(objdir)TestInvocation.$(exeext) :  ohNetCore $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestInvocation.$(objext) $(objdir)TestInvocationMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestInvocation.$(exeext) $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestInvocationMain.$(objext) $(objdir)TestInvocation.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestInvocation.$(objext) : OpenHome/Net/ControlPoint/Tests/TestInvocation.cpp $(headers)
	$(compiler)TestInvocation.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Tests/TestInvocation.cpp
$(objdir)TestInvocationMain.$(objext) : OpenHome/Net/ControlPoint/Tests/TestInvocationMain.cpp $(headers)
	$(compiler)TestInvocationMain.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Tests/TestInvocationMain.cpp

$(objdir)TestBasicDvCore.$(objext) : OpenHome/Net/Device/Tests/TestBasicDv.cpp $(headers)
	$(compiler)TestBasicDvCore.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Tests/TestBasicDv.cpp

TestInvocationStd: $(objdir)TestInvocationStd.$(exeext)
$(objdir)TestInvocationStd.$(exeext) :  ohNetCore $(objdir)CpUpnpOrgConnectionManager1Std.$(objext) $(objdir)TestInvocationStd.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestInvocationStd.$(exeext) $(objdir)CpUpnpOrgConnectionManager1Std.$(objext) $(objdir)TestInvocationStd.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestInvocationStd.$(objext) : OpenHome/Net/Bindings/Cpp/ControlPoint/Tests/TestInvocationStd.cpp $(headers)
	$(compiler)TestInvocationStd.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/Cpp/ControlPoint/Tests/TestInvocationStd.cpp

TestSubscription: $(objdir)TestSubscription.$(exeext)
$(objdir)TestSubscription.$(exeext) :  ohNetCore $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestSubscription.$(objext) $(objdir)TestSubscriptionMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestSubscription.$(exeext) $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestSubscriptionMain.$(objext) $(objdir)TestSubscription.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestSubscription.$(objext) : OpenHome/Net/ControlPoint/Tests/TestSubscription.cpp $(headers)
	$(compiler)TestSubscription.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Tests/TestSubscription.cpp
$(objdir)TestSubscriptionMain.$(objext) : OpenHome/Net/ControlPoint/Tests/TestSubscriptionMain.cpp $(headers)
	$(compiler)TestSubscriptionMain.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Tests/TestSubscriptionMain.cpp

TestNetworkInterfaceChange: $(objdir)TestNetworkInterfaceChange.$(exeext)
$(objdir)TestNetworkInterfaceChange.$(exeext) :  ohNetCore $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)CpAvOpenHomeOrgPlaylist1.$(objext) $(objdir)TestNetworkInterfaceChange.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestNetworkInterfaceChange.$(exeext) $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)CpAvOpenHomeOrgPlaylist1.$(objext) $(objdir)TestNetworkInterfaceChange.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestNetworkInterfaceChange.$(objext) : OpenHome/Net/ControlPoint/Tests/TestNetworkInterfaceChange.cpp $(headers)
	$(compiler)TestNetworkInterfaceChange.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Tests/TestNetworkInterfaceChange.cpp

TestSuspendResume: $(objdir)TestSuspendResume.$(exeext)
$(objdir)TestSuspendResume.$(exeext) :  ohNetCore $(objdir)TestSuspendResume.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestSuspendResume.$(exeext) $(objdir)CpAvOpenhomeOrgProduct1.$(objext) $(objdir)CpAvOpenhomeOrgSender1.$(objext) $(objdir)TestSuspendResume.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestSuspendResume.$(objext) : OpenHome/Net/ControlPoint/Tests/TestSuspendResume.cpp $(headers)
	$(compiler)TestSuspendResume.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Tests/TestSuspendResume.cpp

TestProxyC: $(objdir)TestProxyC.$(exeext)
$(objdir)TestProxyC.$(exeext) :  ohNetCore $(objdir)CpUpnpOrgConnectionManager1C.$(objext) $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestProxyC.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext)
	$(link) $(linkoutput)$(objdir)TestProxyC.$(exeext) $(objdir)CpUpnpOrgConnectionManager1C.$(objext) $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestProxyC.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestProxyC.$(objext) : OpenHome/Net/Bindings/C/ControlPoint/Tests/TestProxyC.cpp $(headers)
	$(compiler)TestProxyC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/ControlPoint/Tests/TestProxyC.cpp
$(objdir)MainC.$(objext) : Os/$(osdir)/MainC.c $(headers)
	$(compiler)MainC.$(objext) -c $(cflags) $(includes) Os/$(osdir)/MainC.c

TestCpDeviceListMdns: $(objdir)TestCpDeviceListMdns.$(exeext)
$(objdir)TestCpDeviceListMdns.$(exeext) :  ohNetCore $(objdir)TestCpDeviceListMdns.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestCpDeviceListMdns.$(exeext) $(objdir)$(libprefix)ohNetCore.$(libext) $(objdir)TestCpDeviceListMdns.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestCpDeviceListMdns.$(objext) : OpenHome/Net/Device/Bonjour/Tests/TestCpDeviceListMdns.cpp $(headers)
	$(compiler)TestCpDeviceListMdns.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Bonjour/Tests/TestCpDeviceListMdns.cpp

TestDviDiscovery: $(objdir)TestDviDiscovery.$(exeext)
$(objdir)TestDviDiscovery.$(exeext) :  ohNetCore $(objdir)TestDviDiscovery.$(objext) $(objdir)TestDviDiscoveryMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDviDiscovery.$(exeext) $(objdir)TestDviDiscoveryMain.$(objext) $(objdir)TestDviDiscovery.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDviDiscovery.$(objext) : OpenHome/Net/Device/Tests/TestDviDiscovery.cpp $(headers)
	$(compiler)TestDviDiscovery.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Tests/TestDviDiscovery.cpp
$(objdir)TestDviDiscoveryMain.$(objext) : OpenHome/Net/Device/Tests/TestDviDiscoveryMain.cpp $(headers)
	$(compiler)TestDviDiscoveryMain.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Tests/TestDviDiscoveryMain.cpp

TestDviDeviceList: $(objdir)TestDviDeviceList.$(exeext)
$(objdir)TestDviDeviceList.$(exeext) :  ohNetCore $(objdir)TestDviDeviceList.$(objext) $(objdir)TestDviDeviceListMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDviDeviceList.$(exeext) $(objdir)TestDviDeviceListMain.$(objext) $(objdir)TestDviDeviceList.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDviDeviceList.$(objext) : OpenHome/Net/Device/Tests/TestDviDeviceList.cpp $(headers)
	$(compiler)TestDviDeviceList.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Tests/TestDviDeviceList.cpp
$(objdir)TestDviDeviceListMain.$(objext) : OpenHome/Net/Device/Tests/TestDviDeviceListMain.cpp $(headers)
	$(compiler)TestDviDeviceListMain.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Tests/TestDviDeviceListMain.cpp

TestDvInvocation: $(objdir)TestDvInvocation.$(exeext)
$(objdir)TestDvInvocation.$(exeext) :  ohNetCore $(objdir)TestDvInvocation.$(objext) $(objdir)TestDvInvocationMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDvInvocation.$(exeext) $(objdir)TestDvInvocationMain.$(objext) $(objdir)TestDvInvocation.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDvInvocation.$(objext) : OpenHome/Net/Device/Tests/TestDvInvocation.cpp $(headers)
	$(compiler)TestDvInvocation.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Tests/TestDvInvocation.cpp
$(objdir)TestDvInvocationMain.$(objext) : OpenHome/Net/Device/Tests/TestDvInvocationMain.cpp $(headers)
	$(compiler)TestDvInvocationMain.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Tests/TestDvInvocationMain.cpp

TestDvSubscription: $(objdir)TestDvSubscription.$(exeext)
$(objdir)TestDvSubscription.$(exeext) :  ohNetCore $(objdir)TestDvSubscription.$(objext) $(objdir)TestDvSubscriptionMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDvSubscription.$(exeext) $(objdir)TestDvSubscriptionMain.$(objext) $(objdir)TestDvSubscription.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDvSubscription.$(objext) : OpenHome/Net/Device/Tests/TestDvSubscription.cpp $(headers)
	$(compiler)TestDvSubscription.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Tests/TestDvSubscription.cpp
$(objdir)TestDvSubscriptionMain.$(objext) : OpenHome/Net/Device/Tests/TestDvSubscriptionMain.cpp $(headers)
	$(compiler)TestDvSubscriptionMain.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Tests/TestDvSubscriptionMain.cpp

TestDvLpec: $(objdir)TestDvLpec.$(exeext)
$(objdir)TestDvLpec.$(exeext) :  ohNetCore $(objdir)TestDvLpec.$(objext) $(objdir)TestDvLpecMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDvLpec.$(exeext) $(objdir)TestDvLpecMain.$(objext) $(objdir)TestDvLpec.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDvLpec.$(objext) : OpenHome/Net/Device/Tests/TestDvLpec.cpp $(headers)
	$(compiler)TestDvLpec.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Tests/TestDvLpec.cpp
$(objdir)TestDvLpecMain.$(objext) : OpenHome/Net/Device/Tests/TestDvLpecMain.cpp $(headers)
	$(compiler)TestDvLpecMain.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Tests/TestDvLpecMain.cpp

TestDvTestBasic: $(objdir)TestDvTestBasic.$(exeext)
$(objdir)TestDvTestBasic.$(exeext) :  ohNetCore $(objdir)TestDvTestBasic.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDvTestBasic.$(exeext) $(objdir)TestDvTestBasic.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDvTestBasic.$(objext) : OpenHome/Net/Device/Tests/TestDvTestBasic.cpp $(headers)
	$(compiler)TestDvTestBasic.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Tests/TestDvTestBasic.cpp

TestAdapterChange: $(objdir)TestAdapterChange.$(exeext)
$(objdir)TestAdapterChange.$(exeext) :  ohNetCore $(objdir)TestAdapterChange.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestAdapterChange.$(exeext) $(objdir)TestAdapterChange.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestAdapterChange.$(objext) : OpenHome/Net/Device/Tests/TestAdapterChange.cpp $(headers)
	$(compiler)TestAdapterChange.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Device/Tests/TestAdapterChange.cpp

TestDeviceFinder: $(objdir)TestDeviceFinder.$(exeext)
$(objdir)TestDeviceFinder.$(exeext) :  ohNetCore $(objdir)TestDeviceFinder.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDeviceFinder.$(exeext) $(objdir)TestDeviceFinder.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDeviceFinder.$(objext) : OpenHome/Net/ControlPoint/Tests/TestDeviceFinder.cpp $(headers)
	$(compiler)TestDeviceFinder.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Tests/TestDeviceFinder.cpp

TestDvDeviceStd: $(objdir)TestDvDeviceStd.$(exeext)
$(objdir)TestDvDeviceStd.$(exeext) :  ohNetCore $(objdir)TestDvDeviceStd.$(objext) $(objdir)TestBasicCpStd.$(objext) $(objdir)TestBasicDvStd.$(objext) $(objdir)DvOpenhomeOrgTestBasic1Std.$(objext) $(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDvDeviceStd.$(exeext) $(objdir)TestDvDeviceStd.$(objext) $(objdir)TestBasicCpStd.$(objext) $(objdir)TestBasicDvStd.$(objext) $(objdir)DvOpenhomeOrgTestBasic1Std.$(objext) $(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDvDeviceStd.$(objext) : OpenHome/Net/Bindings/Cpp/Device/Tests/TestDvDeviceStd.cpp $(headers)
	$(compiler)TestDvDeviceStd.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/Cpp/Device/Tests/TestDvDeviceStd.cpp
$(objdir)TestBasicCpStd.$(objext) : OpenHome/Net/Bindings/Cpp/ControlPoint/Tests/TestBasicCp.cpp $(headers)
	$(compiler)TestBasicCpStd.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/Cpp/ControlPoint/Tests/TestBasicCp.cpp
$(objdir)TestBasicDvStd.$(objext) : OpenHome/Net/Bindings/Cpp/Device/Tests/TestBasicDv.cpp $(headers)
	$(compiler)TestBasicDvStd.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/Cpp/Device/Tests/TestBasicDv.cpp

TestDvDeviceC: $(objdir)TestDvDeviceC.$(exeext)
$(objdir)TestDvDeviceC.$(exeext) :  ohNetCore $(objdir)TestDvDeviceC.$(objext) $(objdir)TestBasicCpC.$(objext) $(objdir)TestBasicDvC.$(objext) $(objdir)DvOpenhomeOrgTestBasic1C.$(objext) $(objdir)CpOpenhomeOrgTestBasic1C.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext)
	$(link) $(linkoutput)$(objdir)TestDvDeviceC.$(exeext) $(objdir)TestDvDeviceC.$(objext) $(objdir)TestBasicCpC.$(objext) $(objdir)TestBasicDvC.$(objext) $(objdir)DvOpenhomeOrgTestBasic1C.$(objext) $(objdir)CpOpenhomeOrgTestBasic1C.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDvDeviceC.$(objext) : OpenHome/Net/Bindings/C/Device/Tests/TestDvDeviceC.cpp $(headers)
	$(compiler)TestDvDeviceC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/Device/Tests/TestDvDeviceC.cpp
$(objdir)TestBasicCpC.$(objext) : OpenHome/Net/Bindings/C/ControlPoint/Tests/TestBasicCpC.cpp $(headers)
	$(compiler)TestBasicCpC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/ControlPoint/Tests/TestBasicCpC.cpp
$(objdir)TestBasicDvC.$(objext) : OpenHome/Net/Bindings/C/Device/Tests/TestBasicDvC.cpp $(headers)
	$(compiler)TestBasicDvC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/Device/Tests/TestBasicDvC.cpp

TestCpDeviceDv: $(objdir)TestCpDeviceDv.$(exeext)
$(objdir)TestCpDeviceDv.$(exeext) :  ohNetCore $(objdir)TestCpDeviceDv.$(objext) $(objdir)TestCpDeviceDvMain.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestCpDeviceDv.$(exeext) $(objdir)TestCpDeviceDvMain.$(objext) $(objdir)TestCpDeviceDv.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestCpDeviceDv.$(objext) : OpenHome/Net/ControlPoint/Tests/TestCpDeviceDv.cpp $(headers)
	$(compiler)TestCpDeviceDv.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Tests/TestCpDeviceDv.cpp
$(objdir)TestCpDeviceDvMain.$(objext) : OpenHome/Net/ControlPoint/Tests/TestCpDeviceDvMain.cpp $(headers)
	$(compiler)TestCpDeviceDvMain.$(objext) -c $(cppflags) $(includes) OpenHome/Net/ControlPoint/Tests/TestCpDeviceDvMain.cpp

TestCpDeviceDvStd: $(objdir)TestCpDeviceDvStd.$(exeext)
$(objdir)TestCpDeviceDvStd.$(exeext) :  ohNetCore $(objdir)TestCpDeviceDvStd.$(objext) $(objdir)TestBasicCpStd.$(objext) $(objdir)TestBasicDvStd.$(objext) $(objdir)DvOpenhomeOrgTestBasic1Std.$(objext) $(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestCpDeviceDvStd.$(exeext) $(objdir)TestCpDeviceDvStd.$(objext) $(objdir)TestBasicCpStd.$(objext) $(objdir)TestBasicDvStd.$(objext) $(objdir)DvOpenhomeOrgTestBasic1Std.$(objext) $(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestCpDeviceDvStd.$(objext) : OpenHome/Net/Bindings/Cpp/ControlPoint/Tests/TestCpDeviceDvStd.cpp $(headers)
	$(compiler)TestCpDeviceDvStd.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/Cpp/ControlPoint/Tests/TestCpDeviceDvStd.cpp

TestCpDeviceDvC: $(objdir)TestCpDeviceDvC.$(exeext)
$(objdir)TestCpDeviceDvC.$(exeext) :  ohNetCore $(objdir)TestCpDeviceDvC.$(objext) $(objdir)TestBasicCpC.$(objext) $(objdir)TestBasicDvC.$(objext) $(objdir)DvOpenhomeOrgTestBasic1C.$(objext) $(objdir)CpOpenhomeOrgTestBasic1C.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext)
	$(link) $(linkoutput)$(objdir)TestCpDeviceDvC.$(exeext) $(objdir)TestCpDeviceDvC.$(objext) $(objdir)TestBasicCpC.$(objext) $(objdir)TestBasicDvC.$(objext) $(objdir)DvOpenhomeOrgTestBasic1C.$(objext) $(objdir)CpOpenhomeOrgTestBasic1C.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestCpDeviceDvC.$(objext) : OpenHome/Net/Bindings/C/ControlPoint/Tests/TestCpDeviceDvC.cpp $(headers)
	$(compiler)TestCpDeviceDvC.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/C/ControlPoint/Tests/TestCpDeviceDvC.cpp

TestPerformanceDv: $(objdir)TestPerformanceDv.$(exeext)
$(objdir)TestPerformanceDv.$(exeext) :  ohNetCore $(objdir)TestPerformanceDv.$(objext) $(objdir)TestBasicDvStd.$(objext) $(objdir)DvOpenhomeOrgTestBasic1Std.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestPerformanceDv.$(exeext) $(objdir)TestPerformanceDv.$(objext) $(objdir)TestBasicDvStd.$(objext) $(objdir)DvOpenhomeOrgTestBasic1Std.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestPerformanceDv.$(objext) : OpenHome/Net/Bindings/Cpp/Device/Tests/TestPerformanceDv.cpp $(headers)
	$(compiler)TestPerformanceDv.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/Cpp/Device/Tests/TestPerformanceDv.cpp

TestPerformanceCp: $(objdir)TestPerformanceCp.$(exeext)
$(objdir)TestPerformanceCp.$(exeext) :  ohNetCore $(objdir)TestPerformanceCp.$(objext) $(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestPerformanceCp.$(exeext) $(objdir)TestPerformanceCp.$(objext) $(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestPerformanceCp.$(objext) : OpenHome/Net/Bindings/Cpp/ControlPoint/Tests/TestPerformanceCp.cpp $(headers)
	$(compiler)TestPerformanceCp.$(objext) -c $(cppflags) $(includes) OpenHome/Net/Bindings/Cpp/ControlPoint/Tests/TestPerformanceCp.cpp

TestKazooServer: $(objdir)TestKazooServer.$(exeext)
$(objdir)TestKazooServer.$(exeext) :  ohNetCore $(objdir)TestKazooServer.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestKazooServer.$(exeext) $(objdir)TestKazooServer.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestKazooServer.$(objext) : OpenHome/Tests/TestKazooServer.cpp $(headers)
	$(compiler)TestKazooServer.$(objext) -c $(cppflags) $(includes) OpenHome/Tests/TestKazooServer.cpp

TestShell: $(objdir)TestShell.$(exeext)
$(objdir)TestShell.$(exeext) :  ohNetCore $(objdir)ShellCommandRun.$(objext) $(objdir)TestShell.$(objext) $(libprefix)TestFramework.$(libext) TestsCore
	$(link) $(linkoutput)$(objdir)TestShell.$(exeext) $(objdir)TestShell.$(objext) $(objdir)ohNetTestsCore.$(libext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestShell.$(objext) : OpenHome/Shell/TestShell.cpp $(headers)
	$(compiler)TestShell.$(objext) -c $(cppflags) $(includes) OpenHome/Shell/TestShell.cpp


tests_core = \
	$(objdir)TestBuffer.$(objext) \
	$(objdir)TestPrinter.$(objext) \
	$(objdir)TestThread.$(objext) \
	$(objdir)TestFunctorGeneric.$(objext) \
	$(objdir)TestFifo.$(objext) \
	$(objdir)TestStream.$(objext) \
	$(objdir)TestFile.$(objext) \
	$(objdir)TestQueue.$(objext) \
	$(objdir)TestTextUtils.$(objext) \
	$(objdir)TestNetwork.$(objext) \
	$(objdir)TestTimer.$(objext) \
	$(objdir)TestTimerMock.$(objext) \
	$(objdir)TestSsdpMListen.$(objext) \
	$(objdir)TestSsdpUListen.$(objext) \
	$(objdir)TestXmlParser.$(objext) \
	$(objdir)TestDeviceList.$(objext) \
	$(objdir)TestInvocation.$(objext) \
	$(objdir)CpUpnpOrgConnectionManager1.$(objext) \
	$(objdir)TestSubscription.$(objext) \
	$(objdir)TestCpDeviceDv.$(objext) \
	$(objdir)TestDviDiscovery.$(objext) \
	$(objdir)TestDviDeviceList.$(objext) \
	$(objdir)TestDvInvocation.$(objext) \
	$(objdir)TestDvSubscription.$(objext) \
	$(objdir)TestDvLpec.$(objext) \
	$(objdir)TestException.$(objext) \
	$(objdir)TestCpDeviceListMdns.$(objext)

TestsCore: $(tests_core)
	$(ar)ohNetTestsCore.$(libext) $(tests_core)

TestsNative: TestBuffer TestPrinter TestThread TestFunctorGeneric TestFifo TestStream TestFile TestQueue TestTextUtils TestMulticast TestNetwork TestEcho TestTimer TestTimerMock TestSsdpMListen TestSsdpUListen TestXmlParser TestDeviceList TestDeviceListStd TestDeviceListC TestInvocation TestInvocationStd TestSubscription TestProxyC TestDviDiscovery TestDviDeviceList TestDvInvocation TestDvSubscription TestDvLpec TestDvTestBasic TestAdapterChange TestDeviceFinder TestDvDeviceStd TestDvDeviceC TestCpDeviceDv TestCpDeviceDvStd TestCpDeviceDvC TestShell

TestsCs: TestProxyCs TestDvDeviceCs TestCpDeviceDvCs TestPerformanceDv TestPerformanceCp TestPerformanceDvCs TestPerformanceCpCs

Tests: TestsNative TestsCs

$(objdir)ohNet.net.dll: make_obj_dir
	$(dotnetsdk) build $(csShared)ohNet.net.csproj --framework $(dotnetFramework) --output $(objdir)

TestProxyCs: $(objdir)TestProxyCs.exe

# iOS currently doesn't build the test projects as these will require their own csprojs which bring in the iOS SDKs
# now that ohNet.Net is built that way....
$(objdir)TestProxyCs.exe: \
	ohNetDll \
	$(objdir)ohNet.net.dll \
	$(csCpTests)TestProxy.cs \
	$(objdir)CpUpnpOrgConnectionManager1.net.dll \

	$(dotnetsdk) build $(csCpTests)TestProxy.csproj --framework $(dotnetFramework) --output $(objdir) --self-contained --runtime $(dotnetRuntime)

TestDvDeviceCs: $(objdir)TestDvDeviceCs.exe

$(objdir)TestDvDeviceCs.exe: \
	ohNetDll \
	$(objdir)ohNet.net.dll \
	$(objdir)DvOpenhomeOrgTestBasic1.net.dll \
	$(objdir)CpOpenhomeOrgTestBasic1.net.dll \
	$(csDvTests)TestBasicDv.cs \
	$(csCpTests)TestBasicCp.cs \
	$(csDvTests)TestDvDevice.cs
	$(dotnetsdk) build $(csShared)TestDvDeviceCs.csproj --framework $(dotnetFramework) --output $(objdir) --self-contained --runtime $(dotnetRuntime)

TestDvLightsCs: $(objdir)TestDvLightsCs.exe

TestCpDeviceDvCs: $(objdir)TestCpDeviceDvCs.exe

$(objdir)TestCpDeviceDvCs.exe: \
	ohNetDll \
	$(objdir)ohNet.net.dll \
	$(objdir)DvOpenhomeOrgTestBasic1.net.dll \
	$(objdir)CpOpenhomeOrgTestBasic1.net.dll \
	$(csDvTests)TestBasicDv.cs \
	$(csCpTests)TestBasicCp.cs \
	$(csCpTests)TestCpDeviceDv.cs
	$(dotnetsdk) build $(csShared)TestCpDeviceDvCs.csproj --framework $(dotnetFramework) --output $(objdir) --self-contained --runtime $(dotnetRuntime)


TestPerformanceDvCs: $(objdir)TestPerformanceDvCs.exe

$(objdir)TestPerformanceDvCs.exe: \
	ohNetDll \
	$(objdir)ohNet.net.dll \
	$(objdir)DvOpenhomeOrgTestBasic1.net.dll \
	$(csDvTests)TestBasicDv.cs \
	$(csDvTests)TestPerformanceDv.cs
	$(dotnetsdk) build $(csDvTests)TestPerformanceDvCs.csproj --framework $(dotnetFramework) --output $(objdir) --self-contained --runtime $(dotnetRuntime)


TestPerformanceCpCs: $(objdir)TestPerformanceCpCs.exe

$(objdir)TestPerformanceCpCs.exe: \
	ohNetDll \
	$(objdir)ohNet.net.dll \
	$(objdir)CpOpenhomeOrgTestBasic1.net.dll \
	$(csCpTests)TestPerformanceCp.cs
	$(dotnetsdk) build $(csCpTests)TestPerformanceCpCs.csproj --framework $(dotnetFramework) --output $(objdir) --self-contained --runtime $(dotnetRuntime)


ohNetJavaAll : ohNetJni ohNetJava CpProxyJavaClasses DvDeviceJavaClasses ohNetJavaSrc

objects_jni = \
	$(objdir)JniAction.$(objext) \
	$(objdir)JniArgumentBinary.$(objext) \
	$(objdir)JniArgumentBool.$(objext) \
	$(objdir)JniArgumentInt.$(objext) \
	$(objdir)JniArgumentString.$(objext) \
	$(objdir)JniArgumentUint.$(objext) \
	$(objdir)JniCallbackList.$(objext) \
	$(objdir)JniCpDevice.$(objext) \
	$(objdir)JniCpDeviceDv.$(objext) \
	$(objdir)JniCpDeviceListUpnpAll.$(objext) \
	$(objdir)JniCpDeviceListUpnpDeviceType.$(objext) \
	$(objdir)JniCpDeviceListUpnpRoot.$(objext) \
	$(objdir)JniCpDeviceListUpnpServiceType.$(objext) \
	$(objdir)JniCpDeviceListUpnpUuid.$(objext) \
	$(objdir)JniCpDeviceList.$(objext) \
	$(objdir)JniCpProxy.$(objext) \
	$(objdir)JniCpService.$(objext) \
	$(objdir)JniDvDevice.$(objext) \
	$(objdir)JniDvDeviceStandard.$(objext) \
	$(objdir)JniDvInvocation.$(objext) \
	$(objdir)JniDvProvider.$(objext) \
	$(objdir)JniDvServerUpnp.$(objext) \
	$(objdir)JniInitParams.$(objext) \
	$(objdir)JniInvocation.$(objext) \
	$(objdir)JniLibrary.$(objext) \
	$(objdir)JniNetworkAdapter.$(objext) \
	$(objdir)JniParameterBinary.$(objext) \
	$(objdir)JniParameterBool.$(objext) \
	$(objdir)JniParameterInt.$(objext) \
	$(objdir)JniParameterRelated.$(objext) \
	$(objdir)JniParameterString.$(objext) \
	$(objdir)JniParameterUint.$(objext) \
	$(objdir)JniProperty.$(objext) \
	$(objdir)JniPropertyBinary.$(objext) \
	$(objdir)JniPropertyBool.$(objext) \
	$(objdir)JniPropertyInt.$(objext) \
	$(objdir)JniPropertyString.$(objext) \
	$(objdir)JniPropertyUint.$(objext) \
	$(objdir)JniResourceWriter.$(objext) \
	$(objdir)JniSubnetList.$(objext) \

ohNetJni : $(objdir)$(dllprefix)ohNetJni.$(dllext)
$(objdir)$(dllprefix)ohNetJni.$(dllext) : ohNetDll $(objects_jni)
	$(link_dll) $(linkoutput)$(objdir)$(dllprefix)ohNetJni.$(dllext) $(objects_jni) $(objdir)$(sharedlibprefix)ohNet.$(sharedlibext) $(link_jvm)
$(objdir)JniAction.$(objext) : $(publicjavadir)Action.c $(headers)
	$(compiler)JniAction.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)Action.c
$(objdir)JniArgumentBinary.$(objext) : $(publicjavadir)ArgumentBinary.c $(headers)
	$(compiler)JniArgumentBinary.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)ArgumentBinary.c
$(objdir)JniArgumentBool.$(objext) : $(publicjavadir)ArgumentBool.c $(headers)
	$(compiler)JniArgumentBool.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)ArgumentBool.c
$(objdir)JniArgumentInt.$(objext) : $(publicjavadir)ArgumentInt.c $(headers)
	$(compiler)JniArgumentInt.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)ArgumentInt.c
$(objdir)JniArgumentString.$(objext) : $(publicjavadir)ArgumentString.c $(headers)
	$(compiler)JniArgumentString.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)ArgumentString.c
$(objdir)JniArgumentUint.$(objext) : $(publicjavadir)ArgumentUint.c $(headers)
	$(compiler)JniArgumentUint.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)ArgumentUint.c
$(objdir)JniCallbackList.$(objext) : $(publicjavadir)JniCallbackList.c $(headers)
	$(compiler)JniCallbackList.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)JniCallbackList.c
$(objdir)JniCpDevice.$(objext) : $(publicjavadir)CpDevice.c $(headers)
	$(compiler)JniCpDevice.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)CpDevice.c
$(objdir)JniCpDeviceDv.$(objext) : $(publicjavadir)CpDeviceDv.c $(headers)
	$(compiler)JniCpDeviceDv.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)CpDeviceDv.c
$(objdir)JniCpDeviceList.$(objext) : $(publicjavadir)CpDeviceList.c $(headers)
	$(compiler)JniCpDeviceList.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)CpDeviceList.c
$(objdir)JniCpDeviceListUpnpAll.$(objext) : $(publicjavadir)CpDeviceListUpnpAll.c $(headers)
	$(compiler)JniCpDeviceListUpnpAll.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)CpDeviceListUpnpAll.c
$(objdir)JniCpDeviceListUpnpDeviceType.$(objext) : $(publicjavadir)CpDeviceListUpnpDeviceType.c $(headers)
	$(compiler)JniCpDeviceListUpnpDeviceType.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)CpDeviceListUpnpDeviceType.c
$(objdir)JniCpDeviceListUpnpRoot.$(objext) : $(publicjavadir)CpDeviceListUpnpRoot.c $(headers)
	$(compiler)JniCpDeviceListUpnpRoot.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)CpDeviceListUpnpRoot.c
$(objdir)JniCpDeviceListUpnpServiceType.$(objext) : $(publicjavadir)CpDeviceListUpnpServiceType.c $(headers)
	$(compiler)JniCpDeviceListUpnpServiceType.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)CpDeviceListUpnpServiceType.c
$(objdir)JniCpDeviceListUpnpUuid.$(objext) : $(publicjavadir)CpDeviceListUpnpUuid.c $(headers)
	$(compiler)JniCpDeviceListUpnpUuid.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)CpDeviceListUpnpUuid.c
$(objdir)JniCpProxy.$(objext) : $(publicjavadir)CpProxy.c $(headers)
	$(compiler)JniCpProxy.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)CpProxy.c
$(objdir)JniCpService.$(objext) : $(publicjavadir)CpService.c $(headers)
	$(compiler)JniCpService.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)CpService.c
$(objdir)JniDvDevice.$(objext) : $(publicjavadir)DvDevice.c $(headers)
	$(compiler)JniDvDevice.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)DvDevice.c
$(objdir)JniDvDeviceStandard.$(objext) : $(publicjavadir)DvDeviceStandard.c $(headers)
	$(compiler)JniDvDeviceStandard.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)DvDeviceStandard.c
$(objdir)JniDvInvocation.$(objext) : $(publicjavadir)DvInvocation.c $(headers)
	$(compiler)JniDvInvocation.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)DvInvocation.c
$(objdir)JniDvProvider.$(objext) : $(publicjavadir)DvProvider.c $(headers)
	$(compiler)JniDvProvider.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)DvProvider.c
$(objdir)JniDvServerUpnp.$(objext) : $(publicjavadir)DvServerUpnp.c $(headers)
	$(compiler)JniDvServerUpnp.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)DvServerUpnp.c
$(objdir)JniInitParams.$(objext) : $(publicjavadir)InitParams.c $(headers)
	$(compiler)JniInitParams.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)InitParams.c
$(objdir)JniInvocation.$(objext) : $(publicjavadir)Invocation.c $(headers)
	$(compiler)JniInvocation.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)Invocation.c
$(objdir)JniLibrary.$(objext) : $(publicjavadir)Library.c $(headers)
	$(compiler)JniLibrary.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)Library.c
$(objdir)JniNetworkAdapter.$(objext) : $(publicjavadir)NetworkAdapter.c $(headers)
	$(compiler)JniNetworkAdapter.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)NetworkAdapter.c
$(objdir)JniParameterBinary.$(objext) : $(publicjavadir)ParameterBinary.c $(headers)
	$(compiler)JniParameterBinary.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)ParameterBinary.c
$(objdir)JniParameterBool.$(objext) : $(publicjavadir)ParameterBool.c $(headers)
	$(compiler)JniParameterBool.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)ParameterBool.c
$(objdir)JniParameterInt.$(objext) : $(publicjavadir)ParameterInt.c $(headers)
	$(compiler)JniParameterInt.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)ParameterInt.c
$(objdir)JniParameterRelated.$(objext) : $(publicjavadir)ParameterRelated.c $(headers)
	$(compiler)JniParameterRelated.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)ParameterRelated.c
$(objdir)JniParameterString.$(objext) : $(publicjavadir)ParameterString.c $(headers)
	$(compiler)JniParameterString.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)ParameterString.c
$(objdir)JniParameterUint.$(objext) : $(publicjavadir)ParameterUint.c $(headers)
	$(compiler)JniParameterUint.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)ParameterUint.c
$(objdir)JniProperty.$(objext) : $(publicjavadir)Property.c $(headers)
	$(compiler)JniProperty.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)Property.c
$(objdir)JniPropertyBinary.$(objext) : $(publicjavadir)PropertyBinary.c $(headers)
	$(compiler)JniPropertyBinary.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)PropertyBinary.c
$(objdir)JniPropertyBool.$(objext) : $(publicjavadir)PropertyBool.c $(headers)
	$(compiler)JniPropertyBool.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)PropertyBool.c
$(objdir)JniPropertyInt.$(objext) : $(publicjavadir)PropertyInt.c $(headers)
	$(compiler)JniPropertyInt.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)PropertyInt.c
$(objdir)JniPropertyString.$(objext) : $(publicjavadir)PropertyString.c $(headers)
	$(compiler)JniPropertyString.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)PropertyString.c
$(objdir)JniPropertyUint.$(objext) : $(publicjavadir)PropertyUint.c $(headers)
	$(compiler)JniPropertyUint.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)PropertyUint.c
$(objdir)JniResourceWriter.$(objext) : $(publicjavadir)ResourceWriter.c $(headers)
	$(compiler)JniResourceWriter.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)ResourceWriter.c
$(objdir)JniSubnetList.$(objext) : $(publicjavadir)SubnetList.c $(headers)
	$(compiler)JniSubnetList.$(objext) -c $(java_cflags) $(includes) $(includes_jni) $(publicjavadir)SubnetList.c

java_classes = \
	$(objdir)org/openhome/net/controlpoint/Argument.class \
	$(objdir)org/openhome/net/controlpoint/ArgumentBinary.class \
	$(objdir)org/openhome/net/controlpoint/ArgumentBool.class \
	$(objdir)org/openhome/net/controlpoint/ArgumentInt.class \
	$(objdir)org/openhome/net/controlpoint/ArgumentString.class \
	$(objdir)org/openhome/net/controlpoint/ArgumentUint.class \
	$(objdir)org/openhome/net/controlpoint/CpAttribute.class \
	$(objdir)org/openhome/net/controlpoint/CpDevice.class \
	$(objdir)org/openhome/net/controlpoint/CpDeviceDv.class \
	$(objdir)org/openhome/net/controlpoint/CpDeviceList.class \
	$(objdir)org/openhome/net/controlpoint/CpDeviceListListener.class \
	$(objdir)org/openhome/net/controlpoint/CpDeviceListUpnpAll.class \
	$(objdir)org/openhome/net/controlpoint/CpDeviceListUpnpDeviceType.class \
	$(objdir)org/openhome/net/controlpoint/CpDeviceListUpnpRoot.class \
	$(objdir)org/openhome/net/controlpoint/CpDeviceListUpnpServiceType.class \
	$(objdir)org/openhome/net/controlpoint/CpDeviceListUpnpUuid.class \
	$(objdir)org/openhome/net/controlpoint/CpProxy.class \
	$(objdir)org/openhome/net/controlpoint/CpService.class \
	$(objdir)org/openhome/net/controlpoint/CpUpnpDeviceListFactory.class \
	$(objdir)org/openhome/net/controlpoint/ICpDeviceList.class \
	$(objdir)org/openhome/net/controlpoint/ICpDeviceListListener.class \
	$(objdir)org/openhome/net/controlpoint/ICpProxy.class \
	$(objdir)org/openhome/net/controlpoint/ICpProxyListener.class \
	$(objdir)org/openhome/net/controlpoint/ICpUpnpDeviceListFactory.class \
	$(objdir)org/openhome/net/controlpoint/Invocation.class \
	$(objdir)org/openhome/net/controlpoint/IPropertyChangeListener.class \
	$(objdir)org/openhome/net/controlpoint/PropertyChangeListener.class \
	$(objdir)org/openhome/net/controlpoint/ProxyError.class \
	$(objdir)org/openhome/net/controlpoint/SyncProxyAction.class \
	$(objdir)org/openhome/net/controlpoint/tests/TestBasicCp.class \
	$(objdir)org/openhome/net/controlpoint/tests/TestCpDeviceDv.class \
	$(objdir)org/openhome/net/controlpoint/tests/TestPerformanceCp.class \
	$(objdir)org/openhome/net/controlpoint/tests/TestProxy.class \
	$(objdir)org/openhome/net/core/Action.class \
	$(objdir)org/openhome/net/core/CombinedStack.class \
	$(objdir)org/openhome/net/core/ControlPointStack.class \
    $(objdir)org/openhome/net/core/DebugLevel.class \
	$(objdir)org/openhome/net/core/DeviceStack.class \
	$(objdir)org/openhome/net/core/ErrorGeneral.class \
	$(objdir)org/openhome/net/core/ErrorNetworkAddressInUse.class \
	$(objdir)org/openhome/net/core/ErrorNoMemory.class \
    $(objdir)org/openhome/net/core/IMessageListener.class \
	$(objdir)org/openhome/net/core/InitParams.class \
	$(objdir)org/openhome/net/core/Library.class \
	$(objdir)org/openhome/net/core/LibraryException.class \
	$(objdir)org/openhome/net/core/NetworkAdapter.class \
	$(objdir)org/openhome/net/core/Parameter.class \
	$(objdir)org/openhome/net/core/ParameterBinary.class \
	$(objdir)org/openhome/net/core/ParameterBool.class \
	$(objdir)org/openhome/net/core/ParameterInt.class \
	$(objdir)org/openhome/net/core/ParameterRelated.class \
	$(objdir)org/openhome/net/core/ParameterString.class \
	$(objdir)org/openhome/net/core/ParameterUint.class \
	$(objdir)org/openhome/net/core/Property.class \
	$(objdir)org/openhome/net/core/PropertyBinary.class \
	$(objdir)org/openhome/net/core/PropertyBool.class \
	$(objdir)org/openhome/net/core/PropertyError.class \
	$(objdir)org/openhome/net/core/PropertyInt.class \
	$(objdir)org/openhome/net/core/PropertyString.class \
	$(objdir)org/openhome/net/core/PropertyUint.class \
	$(objdir)org/openhome/net/core/SubnetList.class \
	$(objdir)org/openhome/net/device/ActionDisabledError.class \
	$(objdir)org/openhome/net/device/ActionError.class \
	$(objdir)org/openhome/net/device/DvDevice.class \
	$(objdir)org/openhome/net/device/DvDeviceFactory.class \
	$(objdir)org/openhome/net/device/DvDeviceStandard.class \
	$(objdir)org/openhome/net/device/DvInvocation.class \
	$(objdir)org/openhome/net/device/DvProvider.class \
	$(objdir)org/openhome/net/device/DvServerUpnp.class \
	$(objdir)org/openhome/net/device/IDvDeviceFactory.class \
	$(objdir)org/openhome/net/device/IDvDeviceListener.class \
	$(objdir)org/openhome/net/device/IDvInvocationListener.class \
	$(objdir)org/openhome/net/device/IResourceManager.class \
	$(objdir)org/openhome/net/device/IResourceWriter.class \
	$(objdir)org/openhome/net/device/PropertyUpdateError.class \
	$(objdir)org/openhome/net/device/ResourceWriter.class \
	$(objdir)org/openhome/net/device/tests/DeviceBasic.class \
	$(objdir)org/openhome/net/device/tests/TestBasicDv.class \
	$(objdir)org/openhome/net/device/tests/TestDvDevice.class \
	$(objdir)org/openhome/net/device/tests/TestPerformanceDv.class \

ohNetJava : make_obj_dir $(objdir)ohnet.jar
$(objdir)ohnet.jar : $(java_classes)
	$(jar) $(jarflags) $(objdir)ohnet.jar -C $(objdir) org
$(objdir)org/openhome/net/controlpoint/Argument.class : $(publicjavadir)org/openhome/net/controlpoint/Argument.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/Argument.java
$(objdir)org/openhome/net/controlpoint/ArgumentBinary.class : $(publicjavadir)org/openhome/net/controlpoint/ArgumentBinary.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/ArgumentBinary.java
$(objdir)org/openhome/net/controlpoint/ArgumentBool.class : $(publicjavadir)org/openhome/net/controlpoint/ArgumentBool.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/ArgumentBool.java
$(objdir)org/openhome/net/controlpoint/ArgumentInt.class : $(publicjavadir)org/openhome/net/controlpoint/ArgumentInt.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/ArgumentInt.java
$(objdir)org/openhome/net/controlpoint/ArgumentString.class : $(publicjavadir)org/openhome/net/controlpoint/ArgumentString.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/ArgumentString.java
$(objdir)org/openhome/net/controlpoint/ArgumentUint.class : $(publicjavadir)org/openhome/net/controlpoint/ArgumentUint.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/ArgumentUint.java
$(objdir)org/openhome/net/controlpoint/CpAttribute.class : $(publicjavadir)org/openhome/net/controlpoint/CpAttribute.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/CpAttribute.java
$(objdir)org/openhome/net/controlpoint/CpDevice.class : $(publicjavadir)org/openhome/net/controlpoint/CpDevice.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/CpDevice.java
$(objdir)org/openhome/net/controlpoint/CpDeviceDv.class : $(publicjavadir)org/openhome/net/controlpoint/CpDeviceDv.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/CpDeviceDv.java
$(objdir)org/openhome/net/controlpoint/CpDeviceList.class : $(publicjavadir)org/openhome/net/controlpoint/CpDeviceList.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/CpDeviceList.java
$(objdir)org/openhome/net/controlpoint/CpDeviceListListener.class : $(publicjavadir)org/openhome/net/controlpoint/CpDeviceListListener.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/CpDeviceListListener.java
$(objdir)org/openhome/net/controlpoint/CpDeviceListUpnpAll.class : $(publicjavadir)org/openhome/net/controlpoint/CpDeviceListUpnpAll.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/CpDeviceListUpnpAll.java
$(objdir)org/openhome/net/controlpoint/CpDeviceListUpnpDeviceType.class : $(publicjavadir)org/openhome/net/controlpoint/CpDeviceListUpnpDeviceType.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/CpDeviceListUpnpDeviceType.java
$(objdir)org/openhome/net/controlpoint/CpDeviceListUpnpRoot.class : $(publicjavadir)org/openhome/net/controlpoint/CpDeviceListUpnpRoot.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/CpDeviceListUpnpRoot.java
$(objdir)org/openhome/net/controlpoint/CpDeviceListUpnpServiceType.class : $(publicjavadir)org/openhome/net/controlpoint/CpDeviceListUpnpServiceType.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/CpDeviceListUpnpServiceType.java
$(objdir)org/openhome/net/controlpoint/CpDeviceListUpnpUuid.class : $(publicjavadir)org/openhome/net/controlpoint/CpDeviceListUpnpUuid.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/CpDeviceListUpnpUuid.java
$(objdir)org/openhome/net/controlpoint/CpProxy.class : $(publicjavadir)org/openhome/net/controlpoint/CpProxy.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/CpProxy.java
$(objdir)org/openhome/net/controlpoint/CpService.class : $(publicjavadir)org/openhome/net/controlpoint/CpService.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/CpService.java
$(objdir)org/openhome/net/controlpoint/CpUpnpDeviceListFactory.class : $(publicjavadir)org/openhome/net/controlpoint/CpUpnpDeviceListFactory.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/CpUpnpDeviceListFactory.java
$(objdir)org/openhome/net/controlpoint/ICpDeviceList.class : $(publicjavadir)org/openhome/net/controlpoint/ICpDeviceList.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/ICpDeviceList.java
$(objdir)org/openhome/net/controlpoint/ICpDeviceListListener.class : $(publicjavadir)org/openhome/net/controlpoint/ICpDeviceListListener.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/ICpDeviceListListener.java
$(objdir)org/openhome/net/controlpoint/ICpProxy.class : $(publicjavadir)org/openhome/net/controlpoint/ICpProxy.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/ICpProxy.java
$(objdir)org/openhome/net/controlpoint/ICpProxyListener.class : $(publicjavadir)org/openhome/net/controlpoint/ICpProxyListener.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/ICpProxyListener.java
$(objdir)org/openhome/net/controlpoint/ICpUpnpDeviceListFactory.class : $(publicjavadir)org/openhome/net/controlpoint/ICpUpnpDeviceListFactory.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/ICpUpnpDeviceListFactory.java
$(objdir)org/openhome/net/controlpoint/Invocation.class : $(publicjavadir)org/openhome/net/controlpoint/Invocation.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/Invocation.java
$(objdir)org/openhome/net/controlpoint/IPropertyChangeListener.class : $(publicjavadir)org/openhome/net/controlpoint/IPropertyChangeListener.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/IPropertyChangeListener.java
$(objdir)org/openhome/net/controlpoint/PropertyChangeListener.class : $(publicjavadir)org/openhome/net/controlpoint/PropertyChangeListener.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/PropertyChangeListener.java
$(objdir)org/openhome/net/controlpoint/ProxyError.class : $(publicjavadir)org/openhome/net/controlpoint/ProxyError.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/ProxyError.java
$(objdir)org/openhome/net/controlpoint/SyncProxyAction.class : $(publicjavadir)org/openhome/net/controlpoint/SyncProxyAction.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/SyncProxyAction.java
$(objdir)org/openhome/net/controlpoint/tests/TestBasicCp.class : $(publicjavadir)org/openhome/net/controlpoint/tests/TestBasicCp.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/tests/TestBasicCp.java
$(objdir)org/openhome/net/controlpoint/tests/TestCpDeviceDv.class : $(publicjavadir)org/openhome/net/controlpoint/tests/TestCpDeviceDv.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/tests/TestCpDeviceDv.java
$(objdir)org/openhome/net/controlpoint/tests/TestPerformanceCp.class : $(publicjavadir)org/openhome/net/controlpoint/tests/TestPerformanceCp.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/tests/TestPerformanceCp.java
$(objdir)org/openhome/net/controlpoint/tests/TestProxy.class : $(publicjavadir)org/openhome/net/controlpoint/tests/TestProxy.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/controlpoint/tests/TestProxy.java
$(objdir)org/openhome/net/core/Action.class : $(publicjavadir)org/openhome/net/core/Action.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/Action.java
$(objdir)org/openhome/net/core/DebugLevel.class : $(publicjavadir)org/openhome/net/core/DebugLevel.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/DebugLevel.java
$(objdir)org/openhome/net/core/CombinedStack.class : $(publicjavadir)org/openhome/net/core/CombinedStack.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/CombinedStack.java
$(objdir)org/openhome/net/core/ControlPointStack.class : $(publicjavadir)org/openhome/net/core/ControlPointStack.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/ControlPointStack.java
$(objdir)org/openhome/net/core/DeviceStack.class : $(publicjavadir)org/openhome/net/core/DeviceStack.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/DeviceStack.java
$(objdir)org/openhome/net/core/ErrorGeneral.class : $(publicjavadir)org/openhome/net/core/ErrorGeneral.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/ErrorGeneral.java
$(objdir)org/openhome/net/core/ErrorNetworkAddressInUse.class : $(publicjavadir)org/openhome/net/core/ErrorNetworkAddressInUse.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/ErrorNetworkAddressInUse.java
$(objdir)org/openhome/net/core/ErrorNoMemory.class : $(publicjavadir)org/openhome/net/core/ErrorNoMemory.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/ErrorNoMemory.java
$(objdir)org/openhome/net/core/IMessageListener.class : $(publicjavadir)org/openhome/net/core/IMessageListener.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/IMessageListener.java
$(objdir)org/openhome/net/core/InitParams.class : $(publicjavadir)org/openhome/net/core/InitParams.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/InitParams.java
$(objdir)org/openhome/net/core/Library.class : $(publicjavadir)org/openhome/net/core/Library.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/Library.java
$(objdir)org/openhome/net/core/LibraryException.class : $(publicjavadir)org/openhome/net/core/LibraryException.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/LibraryException.java
$(objdir)org/openhome/net/core/NetworkAdapter.class : $(publicjavadir)org/openhome/net/core/NetworkAdapter.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/NetworkAdapter.java
$(objdir)org/openhome/net/core/Parameter.class : $(publicjavadir)org/openhome/net/core/Parameter.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/Parameter.java
$(objdir)org/openhome/net/core/ParameterBinary.class : $(publicjavadir)org/openhome/net/core/ParameterBinary.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/ParameterBinary.java
$(objdir)org/openhome/net/core/ParameterBool.class : $(publicjavadir)org/openhome/net/core/ParameterBool.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/ParameterBool.java
$(objdir)org/openhome/net/core/ParameterInt.class : $(publicjavadir)org/openhome/net/core/ParameterInt.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/ParameterInt.java
$(objdir)org/openhome/net/core/ParameterRelated.class : $(publicjavadir)org/openhome/net/core/ParameterRelated.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/ParameterRelated.java
$(objdir)org/openhome/net/core/ParameterString.class : $(publicjavadir)org/openhome/net/core/ParameterString.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/ParameterString.java
$(objdir)org/openhome/net/core/ParameterUint.class : $(publicjavadir)org/openhome/net/core/ParameterUint.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/ParameterUint.java
$(objdir)org/openhome/net/core/Property.class : $(publicjavadir)org/openhome/net/core/Property.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/Property.java
$(objdir)org/openhome/net/core/PropertyBinary.class : $(publicjavadir)org/openhome/net/core/PropertyBinary.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/PropertyBinary.java
$(objdir)org/openhome/net/core/PropertyBool.class : $(publicjavadir)org/openhome/net/core/PropertyBool.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/PropertyBool.java
$(objdir)org/openhome/net/core/PropertyError.class : $(publicjavadir)org/openhome/net/core/PropertyError.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/PropertyError.java
$(objdir)org/openhome/net/core/PropertyInt.class : $(publicjavadir)org/openhome/net/core/PropertyInt.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/PropertyInt.java
$(objdir)org/openhome/net/core/PropertyString.class : $(publicjavadir)org/openhome/net/core/PropertyString.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/PropertyString.java
$(objdir)org/openhome/net/core/PropertyUint.class : $(publicjavadir)org/openhome/net/core/PropertyUint.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/PropertyUint.java
$(objdir)org/openhome/net/core/SubnetList.class : $(publicjavadir)org/openhome/net/core/SubnetList.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/core/SubnetList.java
$(objdir)org/openhome/net/device/ActionDisabledError.class : $(publicjavadir)org/openhome/net/device/ActionDisabledError.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/ActionDisabledError.java
$(objdir)org/openhome/net/device/ActionError.class : $(publicjavadir)org/openhome/net/device/ActionError.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/ActionError.java
$(objdir)org/openhome/net/device/DvDevice.class : $(publicjavadir)org/openhome/net/device/DvDevice.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/DvDevice.java
$(objdir)org/openhome/net/device/DvDeviceFactory.class : $(publicjavadir)org/openhome/net/device/DvDeviceFactory.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/DvDeviceFactory.java
$(objdir)org/openhome/net/device/DvDeviceStandard.class : $(publicjavadir)org/openhome/net/device/DvDeviceStandard.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/DvDeviceStandard.java
$(objdir)org/openhome/net/device/DvInvocation.class : $(publicjavadir)org/openhome/net/device/DvInvocation.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/DvInvocation.java
$(objdir)org/openhome/net/device/DvProvider.class : $(publicjavadir)org/openhome/net/device/DvProvider.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/DvProvider.java
$(objdir)org/openhome/net/device/DvServerUpnp.class : $(publicjavadir)org/openhome/net/device/DvServerUpnp.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/DvServerUpnp.java
$(objdir)org/openhome/net/device/IDvDeviceFactory.class : $(publicjavadir)org/openhome/net/device/IDvDeviceFactory.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/IDvDeviceFactory.java
$(objdir)org/openhome/net/device/IDvDeviceListener.class : $(publicjavadir)org/openhome/net/device/IDvDeviceListener.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/IDvDeviceListener.java
$(objdir)org/openhome/net/device/IDvInvocationListener.class : $(publicjavadir)org/openhome/net/device/IDvInvocationListener.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/IDvInvocationListener.java
$(objdir)org/openhome/net/device/IResourceManager.class : $(publicjavadir)org/openhome/net/device/IResourceManager.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/IResourceManager.java
$(objdir)org/openhome/net/device/IResourceWriter.class : $(publicjavadir)org/openhome/net/device/IResourceWriter.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/IResourceWriter.java
$(objdir)org/openhome/net/device/PropertyUpdateError.class : $(publicjavadir)org/openhome/net/device/PropertyUpdateError.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/PropertyUpdateError.java
$(objdir)org/openhome/net/device/ResourceWriter.class : $(publicjavadir)org/openhome/net/device/ResourceWriter.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/ResourceWriter.java
$(objdir)org/openhome/net/device/tests/DeviceBasic.class : $(publicjavadir)org/openhome/net/device/tests/DeviceBasic.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/tests/DeviceBasic.java
$(objdir)org/openhome/net/device/tests/TestBasicDv.class : $(publicjavadir)org/openhome/net/device/tests/TestBasicDv.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/tests/TestBasicDv.java
$(objdir)org/openhome/net/device/tests/TestDvDevice.class : $(publicjavadir)org/openhome/net/device/tests/TestDvDevice.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/tests/TestDvDevice.java
$(objdir)org/openhome/net/device/tests/TestPerformanceDv.class : $(publicjavadir)org/openhome/net/device/tests/TestPerformanceDv.java
	$(javac) -classpath $(publicjavadir) -d $(objdir) -Xbootclasspath:"$(JAVA_HOME)/jre/lib/rt.jar" -target 1.6 -source 1.6 $(publicjavadir)org/openhome/net/device/tests/TestPerformanceDv.java

ohNetJavaSrc : $(objdir)ohnet-src.jar
$(objdir)ohnet-src.jar :
	$(jar) $(jarflags) $(objdir)ohnet-src.jar -C $(publicjavadir) .


ohNetAndroidNative : make_obj_dir copy_build_includes patch_thirdparty_sources ohNetJava
	$(ANDROID_NDK_ROOT)/ndk-build NDK_DEBUG=$(android_ndk_debug) -C OpenHome/Net/Bindings/Android/jni
	$(mkdir) $(objdir)
	$(mkdir) $(objdir)arm64-v8a
	$(mkdir) $(objdir)armeabi-v7a
	$(mkdir) $(objdir)x86
	$(mkdir) $(objdir)x86_64
	cp $(android_build_dir)/arm64-v8a/libohNet.so $(objdir)arm64-v8a
	cp $(android_build_dir)/arm64-v8a/libohNetJni.so $(objdir)arm64-v8a
	cp $(android_build_dir)/armeabi-v7a/libohNet.so $(objdir)armeabi-v7a
	cp $(android_build_dir)/armeabi-v7a/libohNetJni.so $(objdir)armeabi-v7a
	cp $(android_build_dir)/x86/libohNet.so $(objdir)/x86
	cp $(android_build_dir)/x86/libohNetJni.so $(objdir)/x86
	cp $(android_build_dir)/x86_64/libohNet.so $(objdir)/x86_64
	cp $(android_build_dir)/x86_64/libohNetJni.so $(objdir)/x86_64

ohNetAndroidClean:
	$(ANDROID_NDK_ROOT)/ndk-build -C OpenHome/Net/Bindings/Android/jni clean
	if [ -d OpenHome/Net/Bindings/Android/libs ]; then rm -rf OpenHome/Net/Bindings/Android/libs; fi
	if [ -d OpenHome/Net/Bindings/Android/obj ]; then rm -rf OpenHome/Net/Bindings/Android/obj; fi
	if [ -d OpenHome/Net/Bindings/Android/OpenHome ]; then rm -rf OpenHome/Net/Bindings/Android/OpenHome; fi
	if [ -d OpenHome/Net/Bindings/Android/Os ]; then rm -rf OpenHome/Net/Bindings/Android/Os; fi

Generated$(dirsep)GenerateSourceFiles.mak : $(tt) OpenHome$(dirsep)Net$(dirsep)Service$(dirsep)Services.xml OpenHome/Net/T4/Templates/UpnpMakeT4.tt
	$(mkdir) Generated
	$(t4) -o Generated$(dirsep)GenerateSourceFiles.mak OpenHome/Net/T4/Templates/UpnpMakeT4.tt -a xml:OpenHome/Net/Service/Services.xml
	@echo Attention: a makefile has been re-generated.

Generated$(dirsep)Proxies.mak : $(tt) OpenHome$(dirsep)Net$(dirsep)Service$(dirsep)Services.xml OpenHome/Net/T4/Templates/CpUpnpMakeProxies.tt
	$(mkdir) Generated
	$(t4) -o Generated$(dirsep)Proxies.mak OpenHome/Net/T4/Templates/CpUpnpMakeProxies.tt -a xml:OpenHome/Net/Service/Services.xml
	@echo Attention: a makefile has been re-generated.

Generated$(dirsep)Devices.mak : $(tt) OpenHome$(dirsep)Net$(dirsep)Service$(dirsep)Services.xml OpenHome/Net/T4/Templates/DvUpnpMakeDevices.tt
	$(mkdir) Generated
	$(t4) -o Generated$(dirsep)Devices.mak OpenHome/Net/T4/Templates/DvUpnpMakeDevices.tt -a xml:OpenHome/Net/Service/Services.xml
	@echo Attention: a makefile has been re-generated.

native_targets = ohNetDll TestsNative proxies devices

all_targets = $(native_targets) TestsCs CpProxyDotNetAssemblies DvDeviceDotNetAssemblies
