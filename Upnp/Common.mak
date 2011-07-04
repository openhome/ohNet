
proxyCppCore = ControlPoint$(dirsep)Services$(dirsep)Cpp$(dirsep)Core$(dirsep)
proxyC = ControlPoint$(dirsep)Services$(dirsep)C$(dirsep)
proxyCppStd = ControlPoint$(dirsep)Services$(dirsep)Cpp$(dirsep)Std$(dirsep)
proxyCs = ControlPoint$(dirsep)Services$(dirsep)Cs$(dirsep)
proxyJs = ControlPoint$(dirsep)Services$(dirsep)Js$(dirsep)
deviceCppCore = Device$(dirsep)Services$(dirsep)Cpp$(dirsep)Core$(dirsep)
deviceCppStd = Device$(dirsep)Services$(dirsep)Cpp$(dirsep)Std$(dirsep)
deviceC = Device$(dirsep)Services$(dirsep)C$(dirsep)
deviceCs = Device$(dirsep)Services$(dirsep)Cs$(dirsep)

objects_core = $(objdir)Ascii.$(objext) \
               $(objdir)AsyncC.$(objext) \
               $(objdir)AsyncPrivate.$(objext) \
               $(objdir)Bonjour.$(objext) \
               $(objdir)Buffer.$(objext) \
      		   $(objdir)Discovery.$(objext) \
     		   $(objdir)Debug.$(objext) \
    		   $(objdir)Converter.$(objext) \
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
    		   $(objdir)CpiDeviceUpnp.$(objext) \
    		   $(objdir)CpiService.$(objext) \
    		   $(objdir)CpiStack.$(objext) \
    		   $(objdir)CpiSubscription.$(objext) \
    		   $(objdir)CpProxy.$(objext) \
    		   $(objdir)CpProxyC.$(objext) \
    		   $(objdir)CpServiceC.$(objext) \
    		   $(objdir)DvDevice.$(objext) \
    		   $(objdir)DvDeviceStd.$(objext) \
    		   $(objdir)DvDeviceC.$(objext) \
    		   $(objdir)DviDevice.$(objext) \
    		   $(objdir)DviDeviceUpnp.$(objext) \
    		   $(objdir)DviServer.$(objext) \
    		   $(objdir)DviServerUpnp.$(objext) \
    		   $(objdir)DviServerWebSocket.$(objext) \
    		   $(objdir)DviService.$(objext) \
    		   $(objdir)DviStack.$(objext) \
    		   $(objdir)DviSubscription.$(objext) \
    		   $(objdir)DvProvider.$(objext) \
    		   $(objdir)DvProviderC.$(objext) \
    		   $(objdir)DvServerUpnp.$(objext) \
    		   $(objdir)DvServerUpnpC.$(objext) \
    		   $(objdir)DeviceXml.$(objext) \
    		   $(objdir)Error.$(objext) \
    		   $(objdir)EventUpnp.$(objext) \
    		   $(objdir)Exception.$(objext) \
    		   $(objdir)Fifo.$(objext) \
    		   $(objdir)Http.$(objext) \
    		   $(objdir)DNSCommon.$(objext) \
    		   $(objdir)DNSDigest.$(objext) \
    		   $(objdir)mDNS.$(objext) \
    		   $(objdir)uDNS.$(objext) \
    		   $(objdir)MdnsPlatform.$(objext) \
    		   $(objdir)MdnsProvider.$(objext) \
    		   $(objdir)Maths.$(objext) \
    		   $(objdir)Md5.$(objext) \
    		   $(objdir)NetworkInterfaceList.$(objext) \
    		   $(objdir)Network.$(objext) \
    		   $(objdir)Parser.$(objext) \
    		   $(objdir)Printer.$(objext) \
    		   $(objdir)ProtocolUpnp.$(objext) \
    		   $(objdir)Queue.$(objext) \
    		   $(objdir)RefCounter.$(objext) \
    		   $(objdir)Service.$(objext) \
    		   $(objdir)ServiceC.$(objext) \
    		   $(objdir)Ssdp.$(objext) \
    		   $(objdir)SsdpDv.$(objext) \
    		   $(objdir)Stack.$(objext) \
    		   $(objdir)Stream.$(objext) \
    		   $(objdir)Subscription.$(objext) \
    		   $(objdir)Thread.$(objext) \
    		   $(objdir)Timer.$(objext) \
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

# For simplicity, we make a list of all headers in the project and have all (core) source files depend on them
headers = $(inc_build)/Ascii.h \
          $(inc_build)/Arch.h \
          $(inc_build)/C/Async.h \
          $(inc_build)/AsyncPrivate.h \
          $(inc_build)/Bonjour.h \
          $(inc_build)/Cpp/Buffer.h \
          $(inc_build)/Cpp/Buffer.inl \
          $(inc_build)/Converter.h \
          $(inc_build)/Cpp/Core/CpDevice.h \
          $(inc_build)/C/CpDevice.h \
          $(inc_build)/Cpp/Std/CpDevice.h \
          $(inc_build)/Cpp/Core/CpDeviceDv.h \
          $(inc_build)/Cpp/Std/CpDeviceDv.h \
          $(inc_build)/C/CpDeviceDv.h \
          $(inc_build)/Cpp/Core/CpDeviceUpnp.h \
          $(inc_build)/C/CpDeviceUpnp.h \
          $(inc_build)/Cpp/Std/CpDeviceUpnp.h \
          $(inc_build)/Debug.h \
          $(inc_build)/CpiDevice.h \
          $(inc_build)/CpiDeviceDv.h \
          $(inc_build)/CpiDeviceUpnp.h \
          $(inc_build)/CpiService.h \
          $(inc_build)/CpiStack.h \
          $(inc_build)/CpiSubscription.h \
          $(inc_build)/Discovery.h \
          $(inc_build)/Cpp/DvResourceWriter.h \
          $(inc_build)/Cpp/Core/DvDevice.h \
          $(inc_build)/Cpp/Std/DvDevice.h \
          $(inc_build)/C/DvDevice.h \
          $(inc_build)/C/DviDeviceC.h \
          $(inc_build)/DviDevice.h \
          $(inc_build)/DviDeviceUpnp.h \
          $(inc_build)/DviServer.h \
          $(inc_build)/DviServerUpnp.h \
          $(inc_build)/DviServerWebSocket.h \
          $(inc_build)/DviService.h \
          $(inc_build)/DviStack.h \
          $(inc_build)/DviSubscription.h \
          $(inc_build)/Cpp/DvProvider.h \
          $(inc_build)/C/DvProvider.h \
          $(inc_build)/FunctorDviInvocation.h \
          $(inc_build)/DeviceXml.h \
          $(inc_build)/Error.h \
          $(inc_build)/EventUpnp.h \
          $(inc_build)/Cpp/Exception.h \
          $(inc_build)/Fifo.h \
          $(inc_build)/Cpp/Functor.h \
          $(inc_build)/Cpp/FunctorAsync.h \
          $(inc_build)/Cpp/Core/FunctorCpDevice.h \
          $(inc_build)/Cpp/Std/FunctorCpDevice.h \
          $(inc_build)/FunctorCpiDevice.h \
          $(inc_build)/Cpp/FunctorMsg.h \
          $(inc_build)/Http.h \
          $(inc_build)/Maths.h \
          $(inc_build)/MdnsPlatform.h \
          $(inc_build)/MdnsProvider.h \
          $(inc_build)/Network.h \
          $(inc_build)/NetworkInterfaceList.h \
          $(inc_build)/OsWrapper.h \
          $(inc_build)/OsWrapper.inl \
          $(inc_build)/OsTypes.h \
          $(inc_build)/Os.h \
          $(inc_build)/Parser.h \
          $(inc_build)/Printer.h \
          $(inc_build)/ProtocolUpnp.h \
          $(inc_build)/Cpp/CpProxy.h \
          $(inc_build)/C/CpProxy.h \
          $(inc_build)/C/CpProxyCPrivate.h \
          $(inc_build)/Queue.h \
          $(inc_build)/RefCounter.h \
          $(inc_build)/Service.h \
          $(inc_build)/Ssdp.h \
          $(inc_build)/Stack.h \
          $(inc_build)/Standard.h \
          $(inc_build)/Stream.h \
          $(inc_build)/Subscription.h \
          $(inc_build)/Thread.h \
          $(inc_build)/Timer.h \
          $(inc_build)/Uri.h \
          $(inc_build)/XmlParser.h \
          $(inc_build)/XmlFetcher.h \
          $(inc_build)/Cpp/OhNet.h \
          $(inc_build)/C/OhNet.h \
          $(inc_build)/Cpp/OhNetTypes.h

ohNetCore : make_obj_dir copy_build_includes $(objects_core) $(objdir)$(libprefix)ohNetCore.$(libext) 
$(objdir)$(libprefix)ohNetCore.$(libext) : $(objects_core)
	$(ar)$(libprefix)ohNetCore.$(libext) $(objects_core)
$(objdir)Ascii.$(objext) : Utils/Ascii.cpp $(headers)
	$(compiler)Ascii.$(objext) -c $(cflags) $(includes) Utils/Ascii.cpp
$(objdir)AsyncC.$(objext) : Public/C/AsyncC.cpp $(headers)
	$(compiler)AsyncC.$(objext) -c $(cflags) $(includes) Public/C/AsyncC.cpp
$(objdir)AsyncPrivate.$(objext) : ControlPoint/AsyncPrivate.cpp $(headers)
	$(compiler)AsyncPrivate.$(objext) -c $(cflags) $(includes) ControlPoint/AsyncPrivate.cpp
$(objdir)Bonjour.$(objext) : Bonjour/Bonjour.cpp $(headers)
	$(compiler)Bonjour.$(objext) -c $(cflags) $(includes) Bonjour/Bonjour.cpp
$(objdir)Buffer.$(objext) : Public/Cpp/Core/Buffer.cpp $(headers)
	$(compiler)Buffer.$(objext) -c $(cflags) $(includes) Public/Cpp/Core/Buffer.cpp
$(objdir)Converter.$(objext) : Utils/Converter.cpp $(headers)
	$(compiler)Converter.$(objext) -c $(cflags) $(includes) Utils/Converter.cpp
$(objdir)Discovery.$(objext) : Ssdp/Discovery.cpp $(headers)
	$(compiler)Discovery.$(objext) -c $(cflags) $(includes) Ssdp/Discovery.cpp
$(objdir)Debug.$(objext) : Utils/Debug.cpp $(headers)
	$(compiler)Debug.$(objext) -c $(cflags) $(includes) Utils/Debug.cpp
$(objdir)CpDeviceCore.$(objext) : Public/Cpp/Core/CpDeviceCore.cpp $(headers)
	$(compiler)CpDeviceCore.$(objext) -c $(cflags) $(includes) Public/Cpp/Core/CpDeviceCore.cpp
$(objdir)CpDeviceC.$(objext) : Public/C/CpDeviceC.cpp $(headers)
	$(compiler)CpDeviceC.$(objext) -c $(cflags) $(includes) Public/C/CpDeviceC.cpp
$(objdir)CpDeviceStd.$(objext) : Public/Cpp/Std/CpDeviceStd.cpp $(headers)
	$(compiler)CpDeviceStd.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/CpDeviceStd.cpp
$(objdir)CpDeviceDvCore.$(objext) : Public/Cpp/Core/CpDeviceDvCore.cpp $(headers)
	$(compiler)CpDeviceDvCore.$(objext) -c $(cflags) $(includes) Public/Cpp/Core/CpDeviceDvCore.cpp
$(objdir)CpDeviceDvStd.$(objext) : Public/Cpp/Std/CpDeviceDvStd.cpp $(headers)
	$(compiler)CpDeviceDvStd.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/CpDeviceDvStd.cpp
$(objdir)CpDeviceDvC.$(objext) : Public/C/CpDeviceDvC.cpp $(headers)
	$(compiler)CpDeviceDvC.$(objext) -c $(cflags) $(includes) Public/C/CpDeviceDvC.cpp
$(objdir)CpDeviceUpnpCore.$(objext) : Public/Cpp/Core/CpDeviceUpnpCore.cpp $(headers)
	$(compiler)CpDeviceUpnpCore.$(objext) -c $(cflags) $(includes) Public/Cpp/Core/CpDeviceUpnpCore.cpp
$(objdir)CpDeviceUpnpC.$(objext) : Public/C/CpDeviceUpnpC.cpp $(headers)
	$(compiler)CpDeviceUpnpC.$(objext) -c $(cflags) $(includes) Public/C/CpDeviceUpnpC.cpp
$(objdir)CpDeviceUpnpStd.$(objext) : Public/Cpp/Std/CpDeviceUpnpStd.cpp $(headers)
	$(compiler)CpDeviceUpnpStd.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/CpDeviceUpnpStd.cpp
$(objdir)CpiDevice.$(objext) : ControlPoint/CpiDevice.cpp $(headers)
	$(compiler)CpiDevice.$(objext) -c $(cflags) $(includes) ControlPoint/CpiDevice.cpp
$(objdir)CpiDeviceDv.$(objext) : ControlPoint/Dv/CpiDeviceDv.cpp $(headers)
	$(compiler)CpiDeviceDv.$(objext) -c $(cflags) $(includes) ControlPoint/Dv/CpiDeviceDv.cpp
$(objdir)CpiDeviceUpnp.$(objext) : ControlPoint/Upnp/CpiDeviceUpnp.cpp $(headers)
	$(compiler)CpiDeviceUpnp.$(objext) -c $(cflags) $(includes) ControlPoint/Upnp/CpiDeviceUpnp.cpp
$(objdir)CpiService.$(objext) : ControlPoint/CpiService.cpp $(headers)
	$(compiler)CpiService.$(objext) -c $(cflags) $(includes) ControlPoint/CpiService.cpp
$(objdir)CpiStack.$(objext) : ControlPoint/CpiStack.cpp $(headers)
	$(compiler)CpiStack.$(objext) -c $(cflags) $(includes) ControlPoint/CpiStack.cpp
$(objdir)CpiSubscription.$(objext) : ControlPoint/CpiSubscription.cpp $(headers)
	$(compiler)CpiSubscription.$(objext) -c $(cflags) $(includes) ControlPoint/CpiSubscription.cpp
$(objdir)CpProxy.$(objext) : Public/Cpp/CpProxy.cpp $(headers)
	$(compiler)CpProxy.$(objext) -c $(cflags) $(includes) Public/Cpp/CpProxy.cpp
$(objdir)CpProxyC.$(objext) : Public/C/CpProxyC.cpp $(headers)
	$(compiler)CpProxyC.$(objext) -c $(cflags) $(includes) Public/C/CpProxyC.cpp
$(objdir)CpServiceC.$(objext) : Public/C/CpServiceC.cpp $(headers)
	$(compiler)CpServiceC.$(objext) -c $(cflags) $(includes) Public/C/CpServiceC.cpp
$(objdir)DvDevice.$(objext) : Public/Cpp/Core/DvDevice.cpp $(headers)
	$(compiler)DvDevice.$(objext) -c $(cflags) $(includes) Public/Cpp/Core/DvDevice.cpp
$(objdir)DvDeviceStd.$(objext) : Public/Cpp/Std/DvDeviceStd.cpp $(headers)
	$(compiler)DvDeviceStd.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/DvDeviceStd.cpp
$(objdir)DvDeviceC.$(objext) : Public/C/DvDeviceC.cpp $(headers)
	$(compiler)DvDeviceC.$(objext) -c $(cflags) $(includes) Public/C/DvDeviceC.cpp
$(objdir)DviDevice.$(objext) : Device/DviDevice.cpp $(headers)
	$(compiler)DviDevice.$(objext) -c $(cflags) $(includes) Device/DviDevice.cpp
$(objdir)DviDeviceUpnp.$(objext) : Device/Upnp/DviDeviceUpnp.cpp $(headers)
	$(compiler)DviDeviceUpnp.$(objext) -c $(cflags) $(includes) Device/Upnp/DviDeviceUpnp.cpp
$(objdir)DviServer.$(objext) : Device/DviServer.cpp $(headers)
	$(compiler)DviServer.$(objext) -c $(cflags) $(includes) Device/DviServer.cpp
$(objdir)DviServerUpnp.$(objext) : Device/Upnp/DviServerUpnp.cpp $(headers)
	$(compiler)DviServerUpnp.$(objext) -c $(cflags) $(includes) Device/Upnp/DviServerUpnp.cpp
$(objdir)DviServerWebSocket.$(objext) : Device/Upnp/DviServerWebSocket.cpp $(headers)
	$(compiler)DviServerWebSocket.$(objext) -c $(cflags) $(includes) Device/Upnp/DviServerWebSocket.cpp
$(objdir)DviService.$(objext) : Device/DviService.cpp $(headers)
	$(compiler)DviService.$(objext) -c $(cflags) $(includes) Device/DviService.cpp
$(objdir)DviStack.$(objext) : Device/DviStack.cpp $(headers)
	$(compiler)DviStack.$(objext) -c $(cflags) $(includes) Device/DviStack.cpp
$(objdir)DviSubscription.$(objext) : Device/DviSubscription.cpp $(headers)
	$(compiler)DviSubscription.$(objext) -c $(cflags) $(includes) Device/DviSubscription.cpp
$(objdir)DvProvider.$(objext) : Public/Cpp/DvProvider.cpp $(headers)
	$(compiler)DvProvider.$(objext) -c $(cflags) $(includes) Public/Cpp/DvProvider.cpp
$(objdir)DvProviderC.$(objext) : Public/C/DvProviderC.cpp $(headers)
	$(compiler)DvProviderC.$(objext) -c $(cflags) $(includes) Public/C/DvProviderC.cpp
$(objdir)DvServerUpnp.$(objext) : Public/Cpp/DvServerUpnp.cpp $(headers)
	$(compiler)DvServerUpnp.$(objext) -c $(cflags) $(includes) Public/Cpp/DvServerUpnp.cpp
$(objdir)DvServerUpnpC.$(objext) : Public/C/DvServerUpnpC.cpp $(headers)
	$(compiler)DvServerUpnpC.$(objext) -c $(cflags) $(includes) Public/C/DvServerUpnpC.cpp
$(objdir)DeviceXml.$(objext) : ControlPoint/Upnp/DeviceXml.cpp $(headers)
	$(compiler)DeviceXml.$(objext) -c $(cflags) $(includes) ControlPoint/Upnp/DeviceXml.cpp
$(objdir)Error.$(objext) : Utils/Error.cpp $(headers)
	$(compiler)Error.$(objext) -c $(cflags) $(includes) Utils/Error.cpp
$(objdir)EventUpnp.$(objext) : ControlPoint/Upnp/EventUpnp.cpp $(headers)
	$(compiler)EventUpnp.$(objext) -c $(cflags) $(includes) ControlPoint/Upnp/EventUpnp.cpp
$(objdir)Exception.$(objext) : Public/Cpp/Exception.cpp $(headers)
	$(compiler)Exception.$(objext) -c $(cflags) $(includes) Public/Cpp/Exception.cpp
$(objdir)Fifo.$(objext) : Utils/Fifo.cpp $(headers)
	$(compiler)Fifo.$(objext) -c $(cflags) $(includes) Utils/Fifo.cpp
$(objdir)Http.$(objext) : Network/Http.cpp $(headers)
	$(compiler)Http.$(objext) -c $(cflags) $(includes) Network/Http.cpp
$(objdir)DNSCommon.$(objext) : Bonjour/mDNSCore/DNSCommon.c $(headers)
	$(compiler)DNSCommon.$(objext) -c $(cflags) $(includes) Bonjour/mDNSCore/DNSCommon.c
$(objdir)DNSDigest.$(objext) : Bonjour/mDNSCore/DNSDigest.c $(headers)
	$(compiler)DNSDigest.$(objext) -c $(cflags) $(includes) Bonjour/mDNSCore/DNSDigest.c
$(objdir)mDNS.$(objext) : Bonjour/mDNSCore/mDNS.c $(headers)
	$(compiler)mDNS.$(objext) -c $(cflags) $(includes) Bonjour/mDNSCore/mDNS.c
$(objdir)uDNS.$(objext) : Bonjour/mDNSCore/uDNS.c $(headers)
	$(compiler)uDNS.$(objext) -c $(cflags) $(includes) Bonjour/mDNSCore/uDNS.c
$(objdir)MdnsPlatform.$(objext) : Bonjour/MdnsPlatform.cpp $(headers)
	$(compiler)MdnsPlatform.$(objext) -c $(cflags) $(includes) Bonjour/MdnsPlatform.cpp
$(objdir)MdnsProvider.$(objext) : Bonjour/MdnsProvider.cpp $(headers)
	$(compiler)MdnsProvider.$(objext) -c $(cflags) $(includes) Bonjour/MdnsProvider.cpp
$(objdir)Maths.$(objext) : Utils/Maths.cpp $(headers)
	$(compiler)Maths.$(objext) -c $(cflags) $(includes) Utils/Maths.cpp
$(objdir)Md5.$(objext) : Utils/md5.c $(headers)
	$(compiler)Md5.$(objext) -c $(cflags) $(includes) Utils/md5.c
$(objdir)NetworkInterfaceList.$(objext) : Network/NetworkInterfaceList.cpp $(headers)
	$(compiler)NetworkInterfaceList.$(objext) -c $(cflags) $(includes) Network/NetworkInterfaceList.cpp
$(objdir)Network.$(objext) : Network/Network.cpp $(headers)
	$(compiler)Network.$(objext) -c $(cflags) $(includes) Network/Network.cpp
$(objdir)Parser.$(objext) : Utils/Parser.cpp $(headers)
	$(compiler)Parser.$(objext) -c $(cflags) $(includes) Utils/Parser.cpp
$(objdir)Printer.$(objext) : Utils/Printer.cpp $(headers)
	$(compiler)Printer.$(objext) -c $(cflags) $(includes) Utils/Printer.cpp
$(objdir)ProtocolUpnp.$(objext) : ControlPoint/Upnp/ProtocolUpnp.cpp $(headers)
	$(compiler)ProtocolUpnp.$(objext) -c $(cflags) $(includes) ControlPoint/Upnp/ProtocolUpnp.cpp
$(objdir)Queue.$(objext) : Utils/Queue.cpp $(headers)
	$(compiler)Queue.$(objext) -c $(cflags) $(includes) Utils/Queue.cpp
$(objdir)RefCounter.$(objext) : Utils/RefCounter.cpp $(headers)
	$(compiler)RefCounter.$(objext) -c $(cflags) $(includes) Utils/RefCounter.cpp
$(objdir)Service.$(objext) : Service/Service.cpp $(headers)
	$(compiler)Service.$(objext) -c $(cflags) $(includes) Service/Service.cpp
$(objdir)ServiceC.$(objext) : Public/C/ServiceC.cpp $(headers)
	$(compiler)ServiceC.$(objext) -c $(cflags) $(includes) Public/C/ServiceC.cpp
$(objdir)Ssdp.$(objext) : Ssdp/Ssdp.cpp $(headers)
	$(compiler)Ssdp.$(objext) -c $(cflags) $(includes) Ssdp/Ssdp.cpp
$(objdir)SsdpDv.$(objext) : Ssdp/SsdpDv.cpp $(headers)
	$(compiler)SsdpDv.$(objext) -c $(cflags) $(includes) Ssdp/SsdpDv.cpp
$(objdir)Stack.$(objext) : Stack.cpp $(headers)
	$(compiler)Stack.$(objext) -c $(cflags) $(includes) Stack.cpp
$(objdir)Stream.$(objext) : Utils/Stream.cpp $(headers)
	$(compiler)Stream.$(objext) -c $(cflags) $(includes) Utils/Stream.cpp
$(objdir)Subscription.$(objext) : Network/Subscription.cpp $(headers)
	$(compiler)Subscription.$(objext) -c $(cflags) $(includes) Network/Subscription.cpp
$(objdir)Thread.$(objext) : Thread/Thread.cpp $(headers)
	$(compiler)Thread.$(objext) -c $(cflags) $(includes) Thread/Thread.cpp
$(objdir)Timer.$(objext) : Utils/Timer.cpp $(headers)
	$(compiler)Timer.$(objext) -c $(cflags) $(includes) Utils/Timer.cpp
$(objdir)Uri.$(objext) : Utils/Uri.cpp $(headers)
	$(compiler)Uri.$(objext) -c $(cflags) $(includes) Utils/Uri.cpp
$(objdir)XmlParser.$(objext) : Utils/XmlParser.cpp $(headers)
	$(compiler)XmlParser.$(objext) -c $(cflags) $(includes) Utils/XmlParser.cpp
$(objdir)XmlFetcher.$(objext) : ControlPoint/Upnp/XmlFetcher.cpp $(headers)
	$(compiler)XmlFetcher.$(objext) -c $(cflags) $(includes) ControlPoint/Upnp/XmlFetcher.cpp
$(objdir)OhNet.$(objext) : Public/Cpp/OhNet.cpp $(headers)
	$(compiler)OhNet.$(objext) -c $(cflags) $(includes) Public/Cpp/OhNet.cpp
$(objdir)OhNetCp.$(objext) : Public/Cpp/OhNetCp.cpp $(headers)
	$(compiler)OhNetCp.$(objext) -c $(cflags) $(includes) Public/Cpp/OhNetCp.cpp
$(objdir)OhNetDv.$(objext) : Public/Cpp/OhNetDv.cpp $(headers)
	$(compiler)OhNetDv.$(objext) -c $(cflags) $(includes) Public/Cpp/OhNetDv.cpp
$(objdir)OhNetCombined.$(objext) : Public/Cpp/OhNetCombined.cpp $(headers)
	$(compiler)OhNetCombined.$(objext) -c $(cflags) $(includes) Public/Cpp/OhNetCombined.cpp
$(objdir)OhNetC.$(objext) : Public/C/OhNetC.cpp $(headers)
	$(compiler)OhNetC.$(objext) -c $(cflags) $(includes) Public/C/OhNetC.cpp
$(objdir)OhNetCCp.$(objext) : Public/C/OhNetCCp.cpp $(headers)
	$(compiler)OhNetCCp.$(objext) -c $(cflags) $(includes) Public/C/OhNetCCp.cpp
$(objdir)OhNetCDv.$(objext) : Public/C/OhNetCDv.cpp $(headers)
	$(compiler)OhNetCDv.$(objext) -c $(cflags) $(includes) Public/C/OhNetCDv.cpp
$(objdir)OhNetCCombined.$(objext) : Public/C/OhNetCCombined.cpp $(headers)
	$(compiler)OhNetCCombined.$(objext) -c $(cflags) $(includes) Public/C/OhNetCCombined.cpp
$(objdir)OsWrapper.$(objext) : Os/OsWrapper.cpp $(headers)
	$(compiler)OsWrapper.$(objext) -c $(cflags) $(includes) Os/OsWrapper.cpp
$(objdir)Os.$(objext) : Os/$(osdir)/Os.c $(headers)
	$(compiler)Os.$(objext) -c $(cflags) $(includes) Os/$(osdir)/Os.c


ohNetDll: ohNetCore
	$(link_dll) $(linkoutput)$(objdir)$(dllprefix)ohNet.$(dllext) $(objects_core)



ohNet: proxies devices
	$(ar)$(libprefix)ohNet.$(libext) $(objects_core) $(objects_proxies) $(objects_devices)

TestFramework: $(libprefix)TestFramework.$(libext)

$(libprefix)TestFramework.$(libext): $(objdir)TestFramework.$(objext) $(objdir)Main.$(objext) $(objdir)OptionParser.$(objext)
	$(ar)$(libprefix)TestFramework.$(libext) $(objdir)TestFramework.$(objext) $(objdir)Main.$(objext) $(objdir)OptionParser.$(objext)
$(objdir)TestFramework.$(objext) : TestFramework/TestFramework.cpp $(headers)
	$(compiler)TestFramework.$(objext) -c $(cflags) $(includes) TestFramework/TestFramework.cpp
$(objdir)Main.$(objext) : Os/$(osdir)/Main.cpp $(headers)
	$(compiler)Main.$(objext) -c $(cflags) $(includes) Os/$(osdir)/Main.cpp
$(objdir)OptionParser.$(objext) : TestFramework/OptionParser.cpp $(headers)
	$(compiler)OptionParser.$(objext) -c $(cflags) $(includes) TestFramework/OptionParser.cpp


TestBuffer: $(objdir)TestBuffer.$(exeext) 
$(objdir)TestBuffer.$(exeext) :  ohNetCore $(objdir)TestBuffer.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestBuffer.$(exeext) $(objdir)TestBuffer.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestBuffer.$(objext) : Public/Cpp/Core/TestBuffer.cpp $(headers)
	$(compiler)TestBuffer.$(objext) -c $(cflags) $(includes) Public/Cpp/Core/TestBuffer.cpp

TestThread: $(objdir)TestThread.$(exeext) 
$(objdir)TestThread.$(exeext) :  ohNetCore $(objdir)TestThread.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestThread.$(exeext) $(objdir)TestThread.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestThread.$(objext) : Thread/TestThread.cpp $(headers)
	$(compiler)TestThread.$(objext) -c $(cflags) $(includes) Thread/TestThread.cpp

TestQueue: $(objdir)TestQueue.$(exeext) 
$(objdir)TestQueue.$(exeext) :  ohNetCore $(objdir)TestQueue.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestQueue.$(exeext) $(objdir)TestQueue.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestQueue.$(objext) : Utils/TestQueue.cpp $(headers)
	$(compiler)TestQueue.$(objext) -c $(cflags) $(includes) Utils/TestQueue.cpp

TestFifo: $(objdir)TestFifo.$(exeext) 
$(objdir)TestFifo.$(exeext) :  ohNetCore $(objdir)TestFifo.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestFifo.$(exeext) $(objdir)TestFifo.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestFifo.$(objext) : Utils/TestFifo.cpp $(headers)
	$(compiler)TestFifo.$(objext) -c $(cflags) $(includes) Utils/TestFifo.cpp

TestEcho: $(objdir)TestEcho.$(exeext) 
$(objdir)TestEcho.$(exeext) :  ohNetCore $(objdir)TestEcho.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestEcho.$(exeext) $(objdir)TestEcho.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestEcho.$(objext) : Network/TestEcho.cpp $(headers)
	$(compiler)TestEcho.$(objext) -c $(cflags) $(includes) Network/TestEcho.cpp

TestMulticast: $(objdir)TestMulticast.$(exeext) 
$(objdir)TestMulticast.$(exeext) :  ohNetCore $(objdir)TestMulticast.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestMulticast.$(exeext) $(objdir)TestMulticast.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestMulticast.$(objext) : Network/TestMulticast.cpp $(headers)
	$(compiler)TestMulticast.$(objext) -c $(cflags) $(includes) Network/TestMulticast.cpp

TestNetwork: $(objdir)TestNetwork.$(exeext) 
$(objdir)TestNetwork.$(exeext) :  ohNetCore $(objdir)TestNetwork.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestNetwork.$(exeext) $(objdir)TestNetwork.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestNetwork.$(objext) : Network/TestNetwork.cpp $(headers)
	$(compiler)TestNetwork.$(objext) -c $(cflags) $(includes) Network/TestNetwork.cpp

TestTimer: $(objdir)TestTimer.$(exeext) 
$(objdir)TestTimer.$(exeext) :  ohNetCore $(objdir)TestTimer.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestTimer.$(exeext) $(objdir)TestTimer.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestTimer.$(objext) : Utils/TestTimer.cpp $(headers)
	$(compiler)TestTimer.$(objext) -c $(cflags) $(includes) Utils/TestTimer.cpp

TestSsdpMListen: $(objdir)TestSsdpMListen.$(exeext) 
$(objdir)TestSsdpMListen.$(exeext) :  ohNetCore $(objdir)TestSsdpMListen.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestSsdpMListen.$(exeext) $(objdir)TestSsdpMListen.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestSsdpMListen.$(objext) : Ssdp/TestSsdpMListen.cpp $(headers)
	$(compiler)TestSsdpMListen.$(objext) -c $(cflags) $(includes) Ssdp/TestSsdpMListen.cpp

TestSsdpUListen: $(objdir)TestSsdpUListen.$(exeext) 
$(objdir)TestSsdpUListen.$(exeext) :  ohNetCore $(objdir)TestSsdpUListen.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestSsdpUListen.$(exeext) $(objdir)TestSsdpUListen.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestSsdpUListen.$(objext) : Ssdp/TestSsdpUListen.cpp $(headers)
	$(compiler)TestSsdpUListen.$(objext) -c $(cflags) $(includes) Ssdp/TestSsdpUListen.cpp

TestDeviceList: $(objdir)TestDeviceList.$(exeext) 
$(objdir)TestDeviceList.$(exeext) :  ohNetCore $(objdir)TestDeviceList.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDeviceList.$(exeext) $(objdir)TestDeviceList.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDeviceList.$(objext) : ControlPoint/TestDeviceList.cpp $(headers)
	$(compiler)TestDeviceList.$(objext) -c $(cflags) $(includes) ControlPoint/TestDeviceList.cpp

TestDeviceListC: $(objdir)TestDeviceListC.$(exeext) 
$(objdir)TestDeviceListC.$(exeext) :  ohNetCore $(objdir)TestDeviceListC.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDeviceListC.$(exeext) $(objdir)TestDeviceListC.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDeviceListC.$(objext) : Public/C/TestDeviceListC.cpp $(headers)
	$(compiler)TestDeviceListC.$(objext) -c $(cflags) $(includes) Public/C/TestDeviceListC.cpp

TestDeviceListStd: $(objdir)TestDeviceListStd.$(exeext) 
$(objdir)TestDeviceListStd.$(exeext) :  ohNetCore $(objdir)TestDeviceListStd.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDeviceListStd.$(exeext) $(objdir)TestDeviceListStd.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDeviceListStd.$(objext) : Public/Cpp/Std/TestDeviceListStd.cpp $(headers)
	$(compiler)TestDeviceListStd.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/TestDeviceListStd.cpp

TestDimmableLights: $(objdir)TestDimmableLights.$(exeext) 
$(objdir)TestDimmableLights.$(exeext) :  ohNetCore $(objdir)TestDimmableLights.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDimmableLights.$(exeext) $(objdir)TestDimmableLights.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDimmableLights.$(objext) : ControlPoint/TestDimmableLights.cpp $(headers)
	$(compiler)TestDimmableLights.$(objext) -c $(cflags) $(includes) ControlPoint/TestDimmableLights.cpp

TestInvocation: $(objdir)TestInvocation.$(exeext) 
$(objdir)TestInvocation.$(exeext) :  ohNetCore $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestInvocation.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestInvocation.$(exeext) $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestInvocation.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestInvocation.$(objext) : ControlPoint/TestInvocation.cpp $(headers)
	$(compiler)TestInvocation.$(objext) -c $(cflags) $(includes) ControlPoint/TestInvocation.cpp

TestInvocationStd: $(objdir)TestInvocationStd.$(exeext) 
$(objdir)TestInvocationStd.$(exeext) :  ohNetCore $(objdir)CpUpnpOrgConnectionManager1Std.$(objext) $(objdir)TestInvocationStd.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestInvocationStd.$(exeext) $(objdir)CpUpnpOrgConnectionManager1Std.$(objext) $(objdir)TestInvocationStd.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestInvocationStd.$(objext) : Public/Cpp/Std/TestInvocationStd.cpp $(headers)
	$(compiler)TestInvocationStd.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/TestInvocationStd.cpp

TestSubscription: $(objdir)TestSubscription.$(exeext) 
$(objdir)TestSubscription.$(exeext) :  ohNetCore $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestSubscription.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestSubscription.$(exeext) $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestSubscription.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestSubscription.$(objext) : ControlPoint/TestSubscription.cpp $(headers)
	$(compiler)TestSubscription.$(objext) -c $(cflags) $(includes) ControlPoint/TestSubscription.cpp

TestNetworkInterfaceChange: $(objdir)TestNetworkInterfaceChange.$(exeext) 
$(objdir)TestNetworkInterfaceChange.$(exeext) :  ohNetCore $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)LinnCoUkPlaylist1.$(objext) $(objdir)TestNetworkInterfaceChange.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestNetworkInterfaceChange.$(exeext) $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)LinnCoUkPlaylist1.$(objext) $(objdir)TestNetworkInterfaceChange.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestNetworkInterfaceChange.$(objext) : ControlPoint/TestNetworkInterfaceChange.cpp $(headers)
	$(compiler)TestNetworkInterfaceChange.$(objext) -c $(cflags) $(includes) ControlPoint/TestNetworkInterfaceChange.cpp

TestProxyC: $(objdir)TestProxyC.$(exeext) 
$(objdir)TestProxyC.$(exeext) :  ohNetCore $(objdir)CpUpnpOrgConnectionManager1C.$(objext) $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestProxyC.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext)
	$(link) $(linkoutput)$(objdir)TestProxyC.$(exeext) $(objdir)CpUpnpOrgConnectionManager1C.$(objext) $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestProxyC.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestProxyC.$(objext) : Public/C/TestProxyC.cpp $(headers)
	$(compiler)TestProxyC.$(objext) -c $(cflags) $(includes) Public/C/TestProxyC.cpp
$(objdir)MainC.$(objext) : Os/$(osdir)/MainC.c $(headers)
	$(compiler)MainC.$(objext) -c $(cflags) $(includes) Os/$(osdir)/MainC.c

objects_topology = $(objdir)CpTopology.$(objext) \
    		       $(objdir)CpTopology1.$(objext) \
    		       $(objdir)CpTopology2.$(objext) \
    		       $(objdir)CpTopology3.$(objext) \
			       $(objdir)CpAvOpenhomeOrgProduct1.$(objext) \
			       $(objdir)CpAvOpenhomeOrgVolume1.$(objext)

upnp_topology : ohNetCore $(objects_topology)

$(objdir)CpTopology1.$(objext) : ControlPoint/Topology/CpTopology1.cpp $(headers)
	$(compiler)CpTopology1.$(objext) -c $(cflags) $(includes) ControlPoint/Topology/CpTopology1.cpp 
$(objdir)CpTopology2.$(objext) : ControlPoint/Topology/CpTopology2.cpp $(headers)
	$(compiler)CpTopology2.$(objext) -c $(cflags) $(includes) ControlPoint/Topology/CpTopology2.cpp 
$(objdir)CpTopology3.$(objext) : ControlPoint/Topology/CpTopology3.cpp $(headers)
	$(compiler)CpTopology3.$(objext) -c $(cflags) $(includes) ControlPoint/Topology/CpTopology3.cpp 
$(objdir)CpTopology.$(objext) : ControlPoint/Topology/CpTopology.cpp $(headers)
	$(compiler)CpTopology.$(objext) -c $(cflags) $(includes) ControlPoint/Topology/CpTopology.cpp 

TestTopology1: $(objdir)TestTopology1.$(exeext)  
$(objdir)TestTopology1.$(exeext) :  ohNetCore $(objects_topology) $(objdir)TestTopology1.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestTopology1.$(exeext) $(objdir)TestTopology1.$(objext) $(objects_topology) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestTopology1.$(objext) : ControlPoint/Topology/TestTopology1.cpp $(headers)
	$(compiler)TestTopology1.$(objext) -c $(cflags) $(includes) ControlPoint/Topology/TestTopology1.cpp

TestTopology2: $(objdir)TestTopology2.$(exeext) 
$(objdir)TestTopology2.$(exeext) :  ohNetCore $(objects_topology) $(objdir)TestTopology2.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestTopology2.$(exeext) $(objdir)TestTopology2.$(objext) $(objects_topology) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestTopology2.$(objext) : ControlPoint/Topology/TestTopology2.cpp $(headers)
	$(compiler)TestTopology2.$(objext) -c $(cflags) $(includes) ControlPoint/Topology/TestTopology2.cpp

TestTopology3: $(objdir)TestTopology3.$(exeext) 
$(objdir)TestTopology3.$(exeext) :  ohNetCore $(objects_topology) $(objdir)TestTopology3.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestTopology3.$(exeext) $(objdir)TestTopology3.$(objext) $(objects_topology) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestTopology3.$(objext) : ControlPoint/Topology/TestTopology3.cpp $(headers)
	$(compiler)TestTopology3.$(objext) -c $(cflags) $(includes) ControlPoint/Topology/TestTopology3.cpp

TestTopology: $(objdir)TestTopology.$(exeext) 
$(objdir)TestTopology.$(exeext) :  ohNetCore $(objects_topology) $(objdir)TestTopology.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestTopology.$(exeext) $(objdir)TestTopology.$(objext) $(objects_topology) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestTopology.$(objext) : ControlPoint/Topology/TestTopology.cpp $(headers)
	$(compiler)TestTopology.$(objext) -c $(cflags) $(includes) ControlPoint/Topology/TestTopology.cpp

TestDviDiscovery: $(objdir)TestDviDiscovery.$(exeext) 
$(objdir)TestDviDiscovery.$(exeext) :  ohNetCore $(objdir)TestDviDiscovery.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDviDiscovery.$(exeext) $(objdir)TestDviDiscovery.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDviDiscovery.$(objext) : Device/Upnp/TestDviDiscovery.cpp $(headers)
	$(compiler)TestDviDiscovery.$(objext) -c $(cflags) $(includes) Device/Upnp/TestDviDiscovery.cpp

TestDviDeviceList: $(objdir)TestDviDeviceList.$(exeext) 
$(objdir)TestDviDeviceList.$(exeext) :  ohNetCore $(objdir)TestDviDeviceList.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDviDeviceList.$(exeext) $(objdir)TestDviDeviceList.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDviDeviceList.$(objext) : Device/Upnp/TestDviDeviceList.cpp $(headers)
	$(compiler)TestDviDeviceList.$(objext) -c $(cflags) $(includes) Device/Upnp/TestDviDeviceList.cpp

TestDvInvocation: $(objdir)TestDvInvocation.$(exeext) 
$(objdir)TestDvInvocation.$(exeext) :  ohNetCore $(objdir)TestDvInvocation.$(objext) $(objdir)DvOpenhomeOrgTestBasic1.$(objext) $(objdir)CpOpenhomeOrgTestBasic1.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDvInvocation.$(exeext) $(objdir)TestDvInvocation.$(objext) $(objdir)DvOpenhomeOrgTestBasic1.$(objext) $(objdir)CpOpenhomeOrgTestBasic1.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDvInvocation.$(objext) : Device/Upnp/TestDvInvocation.cpp $(headers)
	$(compiler)TestDvInvocation.$(objext) -c $(cflags) $(includes) Device/Upnp/TestDvInvocation.cpp

TestDvSubscription: $(objdir)TestDvSubscription.$(exeext) 
$(objdir)TestDvSubscription.$(exeext) :  ohNetCore $(objdir)TestDvSubscription.$(objext) $(objdir)DvOpenhomeOrgTestBasic1.$(objext) $(objdir)CpOpenhomeOrgTestBasic1.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDvSubscription.$(exeext) $(objdir)TestDvSubscription.$(objext) $(objdir)DvOpenhomeOrgTestBasic1.$(objext) $(objdir)CpOpenhomeOrgTestBasic1.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDvSubscription.$(objext) : Device/Upnp/TestDvSubscription.cpp $(headers)
	$(compiler)TestDvSubscription.$(objext) -c $(cflags) $(includes) Device/Upnp/TestDvSubscription.cpp

TestDvLights: $(objdir)TestDvLights.$(exeext) 
$(objdir)TestDvLights.$(exeext) :  ohNetCore $(objdir)TestDvLights.$(objext) $(objdir)DvOpenhomeOrgTestLights1.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDvLights.$(exeext) $(objdir)TestDvLights.$(objext) $(objdir)DvOpenhomeOrgTestLights1.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDvLights.$(objext) : Device/Upnp/TestDvLights.cpp $(headers)
	$(compiler)TestDvLights.$(objext) -c $(cflags) $(includes) Device/Upnp/TestDvLights.cpp

TestDvTestBasic: $(objdir)TestDvTestBasic.$(exeext) 
$(objdir)TestDvTestBasic.$(exeext) :  ohNetCore $(objdir)TestDvTestBasic.$(objext) $(objdir)DvOpenhomeOrgTestBasic1.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDvTestBasic.$(exeext) $(objdir)TestDvTestBasic.$(objext) $(objdir)DvOpenhomeOrgTestBasic1.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDvTestBasic.$(objext) : Device/Upnp/TestDvTestBasic.cpp $(headers)
	$(compiler)TestDvTestBasic.$(objext) -c $(cflags) $(includes) Device/Upnp/TestDvTestBasic.cpp

TestDeviceFinder: $(objdir)TestDeviceFinder.$(exeext) 
$(objdir)TestDeviceFinder.$(exeext) :  ohNetCore $(objdir)TestDeviceFinder.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDeviceFinder.$(exeext) $(objdir)TestDeviceFinder.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDeviceFinder.$(objext) : ControlPoint/TestDeviceFinder.cpp $(headers)
	$(compiler)TestDeviceFinder.$(objext) -c $(cflags) $(includes) ControlPoint/TestDeviceFinder.cpp

TestDvDeviceStd: $(objdir)TestDvDeviceStd.$(exeext) 
$(objdir)TestDvDeviceStd.$(exeext) :  ohNetCore $(objdir)TestDvDeviceStd.$(objext) $(objdir)TestBasicCpStd.$(objext) $(objdir)TestBasicDvStd.$(objext) $(objdir)DvOpenhomeOrgTestBasic1Std.$(objext) $(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestDvDeviceStd.$(exeext) $(objdir)TestDvDeviceStd.$(objext) $(objdir)TestBasicCpStd.$(objext) $(objdir)TestBasicDvStd.$(objext) $(objdir)DvOpenhomeOrgTestBasic1Std.$(objext) $(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDvDeviceStd.$(objext) : Public/Cpp/Std/TestDvDeviceStd.cpp $(headers)
	$(compiler)TestDvDeviceStd.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/TestDvDeviceStd.cpp
$(objdir)TestBasicCpStd.$(objext) : Public/Cpp/Std/TestBasicCp.cpp $(headers)
	$(compiler)TestBasicCpStd.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/TestBasicCp.cpp
$(objdir)TestBasicDvStd.$(objext) : Public/Cpp/Std/TestBasicDv.cpp $(headers)
	$(compiler)TestBasicDvStd.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/TestBasicDv.cpp

TestDvDeviceC: $(objdir)TestDvDeviceC.$(exeext) 
$(objdir)TestDvDeviceC.$(exeext) :  ohNetCore $(objdir)TestDvDeviceC.$(objext) $(objdir)TestBasicCpC.$(objext) $(objdir)TestBasicDvC.$(objext) $(objdir)DvOpenhomeOrgTestBasic1C.$(objext) $(objdir)CpOpenhomeOrgTestBasic1C.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext)
	$(link) $(linkoutput)$(objdir)TestDvDeviceC.$(exeext) $(objdir)TestDvDeviceC.$(objext) $(objdir)TestBasicCpC.$(objext) $(objdir)TestBasicDvC.$(objext) $(objdir)DvOpenhomeOrgTestBasic1C.$(objext) $(objdir)CpOpenhomeOrgTestBasic1C.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestDvDeviceC.$(objext) : Public/C/TestDvDeviceC.cpp $(headers)
	$(compiler)TestDvDeviceC.$(objext) -c $(cflags) $(includes) Public/C/TestDvDeviceC.cpp
$(objdir)TestBasicCpC.$(objext) : Public/C/TestBasicCpC.cpp $(headers)
	$(compiler)TestBasicCpC.$(objext) -c $(cflags) $(includes) Public/C/TestBasicCpC.cpp
$(objdir)TestBasicDvC.$(objext) : Public/C/TestBasicDvC.cpp $(headers)
	$(compiler)TestBasicDvC.$(objext) -c $(cflags) $(includes) Public/C/TestBasicDvC.cpp

TestCpDeviceDv: $(objdir)TestCpDeviceDv.$(exeext) 
$(objdir)TestCpDeviceDv.$(exeext) :  ohNetCore $(objdir)TestCpDeviceDv.$(objext) $(objdir)DvOpenhomeOrgTestBasic1.$(objext) $(objdir)CpOpenhomeOrgTestBasic1.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestCpDeviceDv.$(exeext) $(objdir)TestCpDeviceDv.$(objext) $(objdir)DvOpenhomeOrgTestBasic1.$(objext) $(objdir)CpOpenhomeOrgTestBasic1.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestCpDeviceDv.$(objext) : ControlPoint/Dv/TestCpDeviceDv.cpp $(headers)
	$(compiler)TestCpDeviceDv.$(objext) -c $(cflags) $(includes) ControlPoint/Dv/TestCpDeviceDv.cpp

TestCpDeviceDvStd: $(objdir)TestCpDeviceDvStd.$(exeext) 
$(objdir)TestCpDeviceDvStd.$(exeext) :  ohNetCore $(objdir)TestCpDeviceDvStd.$(objext) $(objdir)TestBasicCpStd.$(objext) $(objdir)TestBasicDvStd.$(objext) $(objdir)DvOpenhomeOrgTestBasic1Std.$(objext) $(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestCpDeviceDvStd.$(exeext) $(objdir)TestCpDeviceDvStd.$(objext) $(objdir)TestBasicCpStd.$(objext) $(objdir)TestBasicDvStd.$(objext) $(objdir)DvOpenhomeOrgTestBasic1Std.$(objext) $(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestCpDeviceDvStd.$(objext) : Public/Cpp/Std/TestCpDeviceDvStd.cpp $(headers)
	$(compiler)TestCpDeviceDvStd.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/TestCpDeviceDvStd.cpp

TestCpDeviceDvC: $(objdir)TestCpDeviceDvC.$(exeext) 
$(objdir)TestCpDeviceDvC.$(exeext) :  ohNetCore $(objdir)TestCpDeviceDvC.$(objext) $(objdir)TestBasicCpC.$(objext) $(objdir)TestBasicDvC.$(objext) $(objdir)DvOpenhomeOrgTestBasic1C.$(objext) $(objdir)CpOpenhomeOrgTestBasic1C.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext)
	$(link) $(linkoutput)$(objdir)TestCpDeviceDvC.$(exeext) $(objdir)TestCpDeviceDvC.$(objext) $(objdir)TestBasicCpC.$(objext) $(objdir)TestBasicDvC.$(objext) $(objdir)DvOpenhomeOrgTestBasic1C.$(objext) $(objdir)CpOpenhomeOrgTestBasic1C.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestCpDeviceDvC.$(objext) : Public/C/TestCpDeviceDvC.cpp $(headers)
	$(compiler)TestCpDeviceDvC.$(objext) -c $(cflags) $(includes) Public/C/TestCpDeviceDvC.cpp

TestPerformanceDv: $(objdir)TestPerformanceDv.$(exeext) 
$(objdir)TestPerformanceDv.$(exeext) :  ohNetCore $(objdir)TestPerformanceDv.$(objext) $(objdir)TestBasicDvStd.$(objext) $(objdir)DvOpenhomeOrgTestBasic1Std.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestPerformanceDv.$(exeext) $(objdir)TestPerformanceDv.$(objext) $(objdir)TestBasicDvStd.$(objext) $(objdir)DvOpenhomeOrgTestBasic1Std.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestPerformanceDv.$(objext) : Public/Cpp/Std/TestPerformanceDv.cpp $(headers)
	$(compiler)TestPerformanceDv.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/TestPerformanceDv.cpp

TestPerformanceCp: $(objdir)TestPerformanceCp.$(exeext) 
$(objdir)TestPerformanceCp.$(exeext) :  ohNetCore $(objdir)TestPerformanceCp.$(objext) $(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) $(libprefix)TestFramework.$(libext)
	$(link) $(linkoutput)$(objdir)TestPerformanceCp.$(exeext) $(objdir)TestPerformanceCp.$(objext) $(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) $(objdir)$(libprefix)TestFramework.$(libext) $(objdir)$(libprefix)ohNetCore.$(libext)
$(objdir)TestPerformanceCp.$(objext) : Public/Cpp/Std/TestPerformanceCp.cpp $(headers)
	$(compiler)TestPerformanceCp.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/TestPerformanceCp.cpp

Tests: TestBuffer TestThread TestFifo TestQueue TestMulticast TestNetwork TestEcho TestTimer TestSsdpMListen TestSsdpUListen TestDeviceList TestDeviceListStd TestDeviceListC TestInvocation TestInvocationStd TestSubscription TestProxyC TestTopology1 TestTopology2 TestTopology3 TestTopology TestDviDiscovery TestDviDeviceList TestDvInvocation TestDvSubscription TestDvLights TestDvTestBasic TestDeviceFinder TestDvDeviceStd TestDvDeviceC TestCpDeviceDv TestCpDeviceDvStd TestCpDeviceDvC TestProxyCs TestDvDeviceCs TestDvLightsCs TestCpDeviceDvCs TestPerformanceDv TestPerformanceCp TestPerformanceDvCs TestPerformanceCpCs

ohNet.net.dll : ohNetDll $(objdir)ohNet.net.dll

$(objdir)ohNet.net.dll: \
	$(publiccsdir)CpDevice.cs \
	$(publiccsdir)CpDeviceUpnp.cs \
	$(publiccsdir)CpProxy.cs \
	$(publiccsdir)CpService.cs \
	$(publiccsdir)Service.cs \
	$(publiccsdir)DvDevice.cs \
	$(publiccsdir)DvProvider.cs \
	$(publiccsdir)DvProviderErrors.cs \
	$(publiccsdir)DvServerUpnp.cs \
	$(publiccsdir)OhNet.cs \
	$(publiccsdir)CpDeviceDv.cs
	$(csharp) /unsafe /t:library /debug+ /warnaserror+\
		/out:$(objdir)ohNet.net.dll \
		$(publiccsdir)CpDevice.cs \
		$(publiccsdir)CpDeviceUpnp.cs \
		$(publiccsdir)CpProxy.cs \
		$(publiccsdir)CpService.cs \
		$(publiccsdir)DvDevice.cs \
		$(publiccsdir)DvProvider.cs \
		$(publiccsdir)DvProviderErrors.cs \
		$(publiccsdir)DvServerUpnp.cs \
		$(publiccsdir)Service.cs \
		$(publiccsdir)OhNet.cs \
		$(publiccsdir)CpDeviceDv.cs

TestProxyCs: $(objdir)TestProxyCs.exe

$(objdir)TestProxyCs.exe: \
	ohNetDll \
	$(objdir)ohNet.net.dll \
	$(publiccsdir)TestProxy.cs \
	$(objdir)CpUpnpOrgConnectionManager1.net.dll \
	
	$(csharp) /unsafe /t:exe /debug+ /warnaserror+\
		/out:$(objdir)TestProxyCs.exe \
		/reference:$(objdir)ohNet.net.dll \
		/reference:$(objdir)CpUpnpOrgConnectionManager1.net.dll \
		$(publiccsdir)TestProxy.cs \

TestDvDeviceCs: $(objdir)TestDvDeviceCs.exe

$(objdir)TestDvDeviceCs.exe: \
	ohNetDll \
	$(objdir)ohNet.net.dll \
	$(objdir)DvOpenhomeOrgTestBasic1.net.dll \
	$(objdir)CpOpenhomeOrgTestBasic1.net.dll \
	$(publiccsdir)TestBasicDv.cs \
	$(publiccsdir)TestBasicCp.cs \
	$(publiccsdir)TestDvDevice.cs
	$(csharp) \
		/d:DEBUG /debug /unsafe /warnaserror+ /t:exe \
		/out:$(objdir)TestDvDeviceCs.exe \
		/reference:$(objdir)ohNet.net.dll \
		/reference:$(objdir)DvOpenhomeOrgTestBasic1.net.dll \
		/reference:$(objdir)CpOpenhomeOrgTestBasic1.net.dll \
		$(publiccsdir)TestBasicDv.cs \
		$(publiccsdir)TestBasicCp.cs \
		$(publiccsdir)TestDvDevice.cs
		
TestDvLightsCs: $(objdir)TestDvLightsCs.exe

$(objdir)TestDvLightsCs.exe: \
	ohNetDll \
	$(objdir)ohNet.net.dll \
	$(objdir)DvOpenhomeOrgTestLights1.net.dll \
	$(objdir)CpOpenhomeOrgTestLights1.net.dll \
	$(publiccsdir)TestDvLights.cs
	$(csharp) \
		/d:DEBUG /debug /unsafe /warnaserror+ /t:exe \
		/out:$(objdir)TestDvLightsCs.exe \
		/reference:$(objdir)ohNet.net.dll \
		/reference:$(objdir)DvOpenhomeOrgTestLights1.net.dll \
		/reference:$(objdir)CpOpenhomeOrgTestLights1.net.dll \
		$(publiccsdir)TestDvLights.cs

TestCpDeviceDvCs: $(objdir)TestCpDeviceDvCs.exe

$(objdir)TestCpDeviceDvCs.exe: \
	ohNetDll \
	$(objdir)ohNet.net.dll \
	$(objdir)DvOpenhomeOrgTestBasic1.net.dll \
	$(objdir)CpOpenhomeOrgTestBasic1.net.dll \
	$(publiccsdir)TestBasicDv.cs \
	$(publiccsdir)TestBasicCp.cs \
	$(publiccsdir)TestDvDevice.cs
	$(csharp) \
		/d:DEBUG /debug /unsafe /warnaserror+ /t:exe \
		/out:$(objdir)TestCpDeviceDvCs.exe \
		/reference:$(objdir)ohNet.net.dll \
		/reference:$(objdir)DvOpenhomeOrgTestBasic1.net.dll \
		/reference:$(objdir)CpOpenhomeOrgTestBasic1.net.dll \
		$(publiccsdir)TestBasicDv.cs \
		$(publiccsdir)TestBasicCp.cs \
		$(publiccsdir)TestCpDeviceDv.cs

TestPerformanceDvCs: $(objdir)TestPerformanceDvCs.exe

$(objdir)TestPerformanceDvCs.exe: \
	ohNetDll \
	$(objdir)ohNet.net.dll \
	$(objdir)DvOpenhomeOrgTestBasic1.net.dll \
	$(publiccsdir)TestBasicDv.cs \
	$(publiccsdir)TestPerformanceDv.cs
	$(csharp) \
		/unsafe /warnaserror+ /t:exe \
		/out:$(objdir)TestPerformanceDvCs.exe \
		/reference:$(objdir)ohNet.net.dll \
		/reference:$(objdir)DvOpenhomeOrgTestBasic1.net.dll \
		$(publiccsdir)TestBasicDv.cs \
		$(publiccsdir)TestPerformanceDv.cs

TestPerformanceCpCs: $(objdir)TestPerformanceCpCs.exe

$(objdir)TestPerformanceCpCs.exe: \
	ohNetDll \
	$(objdir)ohNet.net.dll \
	$(objdir)CpOpenhomeOrgTestBasic1.net.dll \
	$(publiccsdir)TestPerformanceCp.cs
	$(csharp) \
		/unsafe /warnaserror+ /t:exe \
		/out:$(objdir)TestPerformanceCpCs.exe \
		/reference:$(objdir)ohNet.net.dll \
		/reference:$(objdir)CpOpenhomeOrgTestBasic1.net.dll \
		$(publiccsdir)TestPerformanceCp.cs


Generated$(dirsep)GenerateSourceFiles.mak : $(tt) Service$(dirsep)Services.xml T4/Templates/UpnpMakeT4.tt
	$(mkdir) Generated
	$(t4) -o Generated$(dirsep)GenerateSourceFiles.mak T4/Templates/UpnpMakeT4.tt -a xml:Service/Services.xml
	@echo Attention: a makefile has been re-generated.

Generated$(dirsep)Proxies.mak : $(tt) Service$(dirsep)Services.xml T4/Templates/CpUpnpMakeProxies.tt
	$(mkdir) Generated
	$(t4) -o Generated$(dirsep)Proxies.mak T4/Templates/CpUpnpMakeProxies.tt -a xml:Service/Services.xml
	@echo Attention: a makefile has been re-generated.

Generated$(dirsep)Devices.mak : $(tt) Service$(dirsep)Services.xml T4/Templates/DvUpnpMakeDevices.tt
	$(mkdir) Generated
	$(t4) -o Generated$(dirsep)Devices.mak T4/Templates/DvUpnpMakeDevices.tt -a xml:Service/Services.xml
	@echo Attention: a makefile has been re-generated.
