objects_core = $(objdir)Ascii.$(objext) \
               $(objdir)AsyncC.$(objext) \
               $(objdir)AsyncPrivate.$(objext) \
               $(objdir)Buffer.$(objext) \
      		   $(objdir)Discovery.$(objext) \
     		   $(objdir)Debug.$(objext) \
    		   $(objdir)Converter.$(objext) \
    		   $(objdir)CpDeviceCore.$(objext) \
    		   $(objdir)CpDeviceC.$(objext) \
    		   $(objdir)CpDeviceStd.$(objext) \
    		   $(objdir)CpDeviceUpnpCore.$(objext) \
    		   $(objdir)CpDeviceUpnpC.$(objext) \
    		   $(objdir)CpDeviceUpnpStd.$(objext) \
    		   $(objdir)CpiDevice.$(objext) \
    		   $(objdir)CpiDeviceUpnp.$(objext) \
    		   $(objdir)CpiService.$(objext) \
    		   $(objdir)CpiStack.$(objext) \
    		   $(objdir)CpiSubscription.$(objext) \
    		   $(objdir)CpProxy.$(objext) \
    		   $(objdir)CpProxyC.$(objext) \
    		   $(objdir)DvDevice.$(objext) \
    		   $(objdir)DvDeviceStd.$(objext) \
    		   $(objdir)DvDeviceC.$(objext) \
    		   $(objdir)DviDevice.$(objext) \
    		   $(objdir)DviDeviceUpnp.$(objext) \
    		   $(objdir)DviServerUpnp.$(objext) \
    		   $(objdir)DviService.$(objext) \
    		   $(objdir)DviStack.$(objext) \
    		   $(objdir)DviSubscription.$(objext) \
    		   $(objdir)DvService.$(objext) \
    		   $(objdir)DeviceXml.$(objext) \
    		   $(objdir)Error.$(objext) \
    		   $(objdir)EventUpnp.$(objext) \
    		   $(objdir)Exception.$(objext) \
    		   $(objdir)Fifo.$(objext) \
    		   $(objdir)Http.$(objext) \
    		   $(objdir)Maths.$(objext) \
    		   $(objdir)NetworkInterfaceList.$(objext) \
    		   $(objdir)NetworkSockets.$(objext) \
    		   $(objdir)Parser.$(objext) \
    		   $(objdir)Printer.$(objext) \
    		   $(objdir)ProtocolUpnp.$(objext) \
    		   $(objdir)Queue.$(objext) \
    		   $(objdir)Service.$(objext) \
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
    		   $(objdir)Zapp.$(objext) \
    		   $(objdir)ZappCp.$(objext) \
    		   $(objdir)ZappDv.$(objext) \
    		   $(objdir)ZappCombined.$(objext) \
    		   $(objdir)ZappC.$(objext) \
    		   $(objdir)ZappCCp.$(objext) \
    		   $(objdir)ZappCDv.$(objext) \
    		   $(objdir)ZappCCombined.$(objext) \
    		   $(objdir)OsWrapper.$(objext) \
    		   $(objdir)Os.$(objext)

# For simplicity, we make a list of all headers in the project and have all (core) source files depend on them
headers = $(inc_build)/Ascii.h \
          $(inc_build)/Arch.h \
          $(inc_build)/ArchSpecific.h \
          $(inc_build)/C/Async.h \
          $(inc_build)/AsyncPrivate.h \
          $(inc_build)/Cpp/Buffer.h \
          $(inc_build)/Cpp/Buffer.inl \
          $(inc_build)/Converter.h \
          $(inc_build)/Cpp/Core/CpDevice.h \
          $(inc_build)/C/CpDevice.h \
          $(inc_build)/Cpp/Std/CpDevice.h \
          $(inc_build)/Cpp/Core/CpDeviceUpnp.h \
          $(inc_build)/C/CpDeviceUpnp.h \
          $(inc_build)/Cpp/Std/CpDeviceUpnp.h \
          $(inc_build)/Debug.h \
          $(inc_build)/CpiDevice.h \
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
          $(inc_build)/DviServerUpnp.h \
          $(inc_build)/DviService.h \
          $(inc_build)/DviStack.h \
          $(inc_build)/DviSubscription.h \
          $(inc_build)/Cpp/DvService.h \
          $(inc_build)/FunctorDvInvocation.h \
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
          $(inc_build)/Network.h \
          $(inc_build)/NetworkInterfaceList.h \
          $(inc_build)/Os.h \
          $(inc_build)/Os.inl \
          $(inc_build)/OsTypes.h \
          $(inc_build)/C/Os.h \
          $(inc_build)/Parser.h \
          $(inc_build)/Printer.h \
          $(inc_build)/ProtocolUpnp.h \
          $(inc_build)/Cpp/CpProxy.h \
          $(inc_build)/C/CpProxy.h \
          $(inc_build)/C/CpProxyCPrivate.h \
          $(inc_build)/Queue.h \
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
          $(inc_build)/Cpp/Zapp.h \
          $(inc_build)/C/Zapp.h \
          $(inc_build)/Cpp/ZappTypes.h

upnp_core : make_obj_dir copy_build_includes $(objects_core)
	$(ar)$(libprefix)upnp_core.$(libext) $(objects_core)
$(objdir)Ascii.$(objext) : Utils/Ascii.cpp $(headers)
	$(compiler)Ascii.$(objext) -c $(cflags) $(includes) Utils/Ascii.cpp
$(objdir)AsyncC.$(objext) : Public/C/AsyncC.cpp $(headers)
	$(compiler)AsyncC.$(objext) -c $(cflags) $(includes) Public/C/AsyncC.cpp
$(objdir)AsyncPrivate.$(objext) : ControlPoint/AsyncPrivate.cpp $(headers)
	$(compiler)AsyncPrivate.$(objext) -c $(cflags) $(includes) ControlPoint/AsyncPrivate.cpp
$(objdir)Buffer.$(objext) : Buffer/Buffer.cpp $(headers)
	$(compiler)Buffer.$(objext) -c $(cflags) $(includes) Buffer/Buffer.cpp
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
$(objdir)CpDeviceUpnpCore.$(objext) : Public/Cpp/Core/CpDeviceUpnpCore.cpp $(headers)
	$(compiler)CpDeviceUpnpCore.$(objext) -c $(cflags) $(includes) Public/Cpp/Core/CpDeviceUpnpCore.cpp
$(objdir)CpDeviceUpnpC.$(objext) : Public/C/CpDeviceUpnpC.cpp $(headers)
	$(compiler)CpDeviceUpnpC.$(objext) -c $(cflags) $(includes) Public/C/CpDeviceUpnpC.cpp
$(objdir)CpDeviceUpnpStd.$(objext) : Public/Cpp/Std/CpDeviceUpnpStd.cpp $(headers)
	$(compiler)CpDeviceUpnpStd.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/CpDeviceUpnpStd.cpp
$(objdir)CpiDevice.$(objext) : ControlPoint/CpiDevice.cpp $(headers)
	$(compiler)CpiDevice.$(objext) -c $(cflags) $(includes) ControlPoint/CpiDevice.cpp
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
$(objdir)DviServerUpnp.$(objext) : Device/Upnp/DviServerUpnp.cpp $(headers)
	$(compiler)DviServerUpnp.$(objext) -c $(cflags) $(includes) Device/Upnp/DviServerUpnp.cpp
$(objdir)DviService.$(objext) : Device/DviService.cpp $(headers)
	$(compiler)DviService.$(objext) -c $(cflags) $(includes) Device/DviService.cpp
$(objdir)DviStack.$(objext) : Device/DviStack.cpp $(headers)
	$(compiler)DviStack.$(objext) -c $(cflags) $(includes) Device/DviStack.cpp
$(objdir)DviSubscription.$(objext) : Device/DviSubscription.cpp $(headers)
	$(compiler)DviSubscription.$(objext) -c $(cflags) $(includes) Device/DviSubscription.cpp
$(objdir)DvService.$(objext) : Public/Cpp/DvService.cpp $(headers)
	$(compiler)DvService.$(objext) -c $(cflags) $(includes) Public/Cpp/DvService.cpp
$(objdir)DeviceXml.$(objext) : ControlPoint/Upnp/DeviceXml.cpp $(headers)
	$(compiler)DeviceXml.$(objext) -c $(cflags) $(includes) ControlPoint/Upnp/DeviceXml.cpp
$(objdir)Error.$(objext) : Utils/Error.cpp $(headers)
	$(compiler)Error.$(objext) -c $(cflags) $(includes) Utils/Error.cpp
$(objdir)EventUpnp.$(objext) : ControlPoint/Upnp/EventUpnp.cpp $(headers)
	$(compiler)EventUpnp.$(objext) -c $(cflags) $(includes) ControlPoint/Upnp/EventUpnp.cpp
$(objdir)Exception.$(objext) : Exception/Exception.cpp $(headers)
	$(compiler)Exception.$(objext) -c $(cflags) $(includes) Exception/Exception.cpp
$(objdir)Fifo.$(objext) : Utils/Fifo.cpp $(headers)
	$(compiler)Fifo.$(objext) -c $(cflags) $(includes) Utils/Fifo.cpp
$(objdir)Http.$(objext) : Network/Http.cpp $(headers)
	$(compiler)Http.$(objext) -c $(cflags) $(includes) Network/Http.cpp
$(objdir)Maths.$(objext) : Utils/Maths.cpp $(headers)
	$(compiler)Maths.$(objext) -c $(cflags) $(includes) Utils/Maths.cpp
$(objdir)NetworkInterfaceList.$(objext) : Network/NetworkInterfaceList.cpp $(headers)
	$(compiler)NetworkInterfaceList.$(objext) -c $(cflags) $(includes) Network/NetworkInterfaceList.cpp
$(objdir)NetworkSockets.$(objext) : Network/NetworkSockets.cpp $(headers)
	$(compiler)NetworkSockets.$(objext) -c $(cflags) $(includes) Network/NetworkSockets.cpp
$(objdir)Parser.$(objext) : Utils/Parser.cpp $(headers)
	$(compiler)Parser.$(objext) -c $(cflags) $(includes) Utils/Parser.cpp
$(objdir)Printer.$(objext) : Utils/Printer.cpp $(headers)
	$(compiler)Printer.$(objext) -c $(cflags) $(includes) Utils/Printer.cpp
$(objdir)ProtocolUpnp.$(objext) : ControlPoint/Upnp/ProtocolUpnp.cpp $(headers)
	$(compiler)ProtocolUpnp.$(objext) -c $(cflags) $(includes) ControlPoint/Upnp/ProtocolUpnp.cpp
$(objdir)Queue.$(objext) : Utils/Queue.cpp $(headers)
	$(compiler)Queue.$(objext) -c $(cflags) $(includes) Utils/Queue.cpp
$(objdir)Service.$(objext) : Service/Service.cpp $(headers)
	$(compiler)Service.$(objext) -c $(cflags) $(includes) Service/Service.cpp
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
$(objdir)Timer.$(objext) : Timer/Timer.cpp $(headers)
	$(compiler)Timer.$(objext) -c $(cflags) $(includes) Timer/Timer.cpp
$(objdir)Uri.$(objext) : Utils/Uri.cpp $(headers)
	$(compiler)Uri.$(objext) -c $(cflags) $(includes) Utils/Uri.cpp
$(objdir)XmlParser.$(objext) : Utils/XmlParser.cpp $(headers)
	$(compiler)XmlParser.$(objext) -c $(cflags) $(includes) Utils/XmlParser.cpp
$(objdir)XmlFetcher.$(objext) : ControlPoint/Upnp/XmlFetcher.cpp $(headers)
	$(compiler)XmlFetcher.$(objext) -c $(cflags) $(includes) ControlPoint/Upnp/XmlFetcher.cpp
$(objdir)Zapp.$(objext) : Public/Cpp/Zapp.cpp $(headers)
	$(compiler)Zapp.$(objext) -c $(cflags) $(includes) Public/Cpp/Zapp.cpp
$(objdir)ZappCp.$(objext) : Public/Cpp/ZappCp.cpp $(headers)
	$(compiler)ZappCp.$(objext) -c $(cflags) $(includes) Public/Cpp/ZappCp.cpp
$(objdir)ZappDv.$(objext) : Public/Cpp/ZappDv.cpp $(headers)
	$(compiler)ZappDv.$(objext) -c $(cflags) $(includes) Public/Cpp/ZappDv.cpp
$(objdir)ZappCombined.$(objext) : Public/Cpp/ZappCombined.cpp $(headers)
	$(compiler)ZappCombined.$(objext) -c $(cflags) $(includes) Public/Cpp/ZappCombined.cpp
$(objdir)ZappC.$(objext) : Public/C/ZappC.cpp $(headers)
	$(compiler)ZappC.$(objext) -c $(cflags) $(includes) Public/C/ZappC.cpp
$(objdir)ZappCCp.$(objext) : Public/C/ZappCCp.cpp $(headers)
	$(compiler)ZappCCp.$(objext) -c $(cflags) $(includes) Public/C/ZappCCp.cpp
$(objdir)ZappCDv.$(objext) : Public/C/ZappCDv.cpp $(headers)
	$(compiler)ZappCDv.$(objext) -c $(cflags) $(includes) Public/C/ZappCDv.cpp
$(objdir)ZappCCombined.$(objext) : Public/C/ZappCCombined.cpp $(headers)
	$(compiler)ZappCCombined.$(objext) -c $(cflags) $(includes) Public/C/ZappCCombined.cpp
$(objdir)OsWrapper.$(objext) : Os/OsWrapper.cpp $(headers)
	$(compiler)OsWrapper.$(objext) -c $(cflags) $(includes) Os/OsWrapper.cpp
$(objdir)Os.$(objext) : Os/$(osdir)/Os.c $(headers)
	$(compiler)Os.$(objext) -c $(cflags) $(includes) Os/$(osdir)/Os.c


ZappUpnpDll: upnp_core
	$(linker_dll)$(dllprefix)ZappUpnp.$(dllext) $(objects_core)


include Proxies.mak
include Devices.mak

Zapp: proxies devices
	$(ar)$(libprefix)Zapp.$(libext) $(objects_core) $(objects_proxies) $(objects_devices)


TestFramework.$(libext): $(objdir)TestFramework.$(objext) $(objdir)Main.$(objext) $(objdir)OptionParser.$(objext)
	$(ar)TestFramework.$(libext) $(objdir)TestFramework.$(objext) $(objdir)Main.$(objext) $(objdir)OptionParser.$(objext)
$(objdir)TestFramework.$(objext) : TestFramework/TestFramework.cpp $(headers)
	$(compiler)TestFramework.$(objext) -c $(cflags) $(includes) TestFramework/TestFramework.cpp
$(objdir)Main.$(objext) : Os/$(osdir)/Main.cpp $(headers)
	$(compiler)Main.$(objext) -c $(cflags) $(includes) Os/$(osdir)/Main.cpp
$(objdir)OptionParser.$(objext) : TestFramework/OptionParser.cpp $(headers)
	$(compiler)OptionParser.$(objext) -c $(cflags) $(includes) TestFramework/OptionParser.cpp


TestBuffer: upnp_core $(objdir)TestBuffer.$(objext) TestFramework.$(libext)
	$(linker)TestBuffer.$(exeext) $(objdir)TestBuffer.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestBuffer.$(objext) : Buffer/TestBuffer.cpp $(headers)
	$(compiler)TestBuffer.$(objext) -c $(cflags) $(includes) Buffer/TestBuffer.cpp

TestThread: upnp_core $(objdir)TestThread.$(objext) TestFramework.$(libext)
	$(linker)TestThread.$(exeext) $(objdir)TestThread.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestThread.$(objext) : Thread/TestThread.cpp $(headers)
	$(compiler)TestThread.$(objext) -c $(cflags) $(includes) Thread/TestThread.cpp

TestQueue: upnp_core $(objdir)TestQueue.$(objext) TestFramework.$(libext)
	$(linker)TestQueue.$(exeext) $(objdir)TestQueue.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestQueue.$(objext) : Utils/TestQueue.cpp $(headers)
	$(compiler)TestQueue.$(objext) -c $(cflags) $(includes) Utils/TestQueue.cpp

TestFifo: upnp_core $(objdir)TestFifo.$(objext) TestFramework.$(libext)
	$(linker)TestFifo.$(exeext) $(objdir)TestFifo.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestFifo.$(objext) : Utils/TestFifo.cpp $(headers)
	$(compiler)TestFifo.$(objext) -c $(cflags) $(includes) Utils/TestFifo.cpp

TestEcho: upnp_core $(objdir)TestEcho.$(objext) TestFramework.$(libext)
	$(linker)TestEcho.$(exeext) $(objdir)TestEcho.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestEcho.$(objext) : Network/TestEcho.cpp $(headers)
	$(compiler)TestEcho.$(objext) -c $(cflags) $(includes) Network/TestEcho.cpp

TestNetwork: upnp_core $(objdir)TestNetwork.$(objext) TestFramework.$(libext)
	$(linker)TestNetwork.$(exeext) $(objdir)TestNetwork.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestNetwork.$(objext) : Network/TestNetwork.cpp $(headers)
	$(compiler)TestNetwork.$(objext) -c $(cflags) $(includes) Network/TestNetwork.cpp

TestTimer: upnp_core $(objdir)TestTimer.$(objext) TestFramework.$(libext)
	$(linker)TestTimer.$(exeext) $(objdir)TestTimer.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestTimer.$(objext) : Timer/TestTimer.cpp $(headers)
	$(compiler)TestTimer.$(objext) -c $(cflags) $(includes) Timer/TestTimer.cpp

TestSsdpMListen: upnp_core $(objdir)TestSsdpMListen.$(objext) TestFramework.$(libext)
	$(linker)TestSsdpMListen.$(exeext) $(objdir)TestSsdpMListen.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestSsdpMListen.$(objext) : Ssdp/TestSsdpMListen.cpp $(headers)
	$(compiler)TestSsdpMListen.$(objext) -c $(cflags) $(includes) Ssdp/TestSsdpMListen.cpp

TestSsdpUListen: upnp_core $(objdir)TestSsdpUListen.$(objext) TestFramework.$(libext)
	$(linker)TestSsdpUListen.$(exeext) $(objdir)TestSsdpUListen.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestSsdpUListen.$(objext) : Ssdp/TestSsdpUListen.cpp $(headers)
	$(compiler)TestSsdpUListen.$(objext) -c $(cflags) $(includes) Ssdp/TestSsdpUListen.cpp

TestDeviceList: upnp_core $(objdir)TestDeviceList.$(objext) TestFramework.$(libext)
	$(linker)TestDeviceList.$(exeext) $(objdir)TestDeviceList.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestDeviceList.$(objext) : ControlPoint/TestDeviceList.cpp $(headers)
	$(compiler)TestDeviceList.$(objext) -c $(cflags) $(includes) ControlPoint/TestDeviceList.cpp

TestDeviceListC: upnp_core $(objdir)TestDeviceListC.$(objext) TestFramework.$(libext)
	$(linker)TestDeviceListC.$(exeext) $(objdir)TestDeviceListC.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestDeviceListC.$(objext) : Public/C/TestDeviceListC.cpp $(headers)
	$(compiler)TestDeviceListC.$(objext) -c $(cflags) $(includes) Public/C/TestDeviceListC.cpp

TestDeviceListStd: upnp_core $(objdir)TestDeviceListStd.$(objext) TestFramework.$(libext)
	$(linker)TestDeviceListStd.$(exeext) $(objdir)TestDeviceListStd.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestDeviceListStd.$(objext) : Public/Cpp/Std/TestDeviceListStd.cpp $(headers)
	$(compiler)TestDeviceListStd.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/TestDeviceListStd.cpp

TestDimmableLights: zapp $(objdir)TestDimmableLights.$(objext) TestFramework.$(libext)
	$(linker)TestDimmableLights.$(exeext) $(objdir)TestDimmableLights.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)Zapp.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestDimmableLights.$(objext) : ControlPoint/TestDimmableLights.cpp $(headers)
	$(compiler)TestDimmableLights.$(objext) -c $(cflags) $(includes) ControlPoint/TestDimmableLights.cpp

TestInvocation: upnp_core $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestInvocation.$(objext) TestFramework.$(libext)
	$(linker)TestInvocation.$(exeext) $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestInvocation.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestInvocation.$(objext) : ControlPoint/TestInvocation.cpp $(headers)
	$(compiler)TestInvocation.$(objext) -c $(cflags) $(includes) ControlPoint/TestInvocation.cpp

TestInvocationStd: upnp_core $(objdir)CpUpnpOrgConnectionManager1Std.$(objext) $(objdir)TestInvocationStd.$(objext) TestFramework.$(libext)
	$(linker)TestInvocationStd.$(exeext) $(objdir)CpUpnpOrgConnectionManager1Std.$(objext) $(objdir)TestInvocationStd.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestInvocationStd.$(objext) : Public/Cpp/Std/TestInvocationStd.cpp $(headers)
	$(compiler)TestInvocationStd.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/TestInvocationStd.cpp

TestSubscription: upnp_core $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestSubscription.$(objext) TestFramework.$(libext)
	$(linker)TestSubscription.$(exeext) $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestSubscription.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestSubscription.$(objext) : ControlPoint/TestSubscription.cpp $(headers)
	$(compiler)TestSubscription.$(objext) -c $(cflags) $(includes) ControlPoint/TestSubscription.cpp

TestNetworkInterfaceChange: upnp_core $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)LinnCoUkPlaylist1.$(objext) $(objdir)TestNetworkInterfaceChange.$(objext) TestFramework.$(libext)
	$(linker)TestNetworkInterfaceChange.$(exeext) $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)LinnCoUkPlaylist1.$(objext) $(objdir)TestNetworkInterfaceChange.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestNetworkInterfaceChange.$(objext) : ControlPoint/TestNetworkInterfaceChange.cpp $(headers)
	$(compiler)TestNetworkInterfaceChange.$(objext) -c $(cflags) $(includes) ControlPoint/TestNetworkInterfaceChange.cpp

TestProxyC: upnp_core $(objdir)CpUpnpOrgConnectionManager1C.$(objext) $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestProxyC.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext)
	$(linker)TestProxyC.$(exeext) $(objdir)CpUpnpOrgConnectionManager1C.$(objext) $(objdir)CpUpnpOrgConnectionManager1.$(objext) $(objdir)TestProxyC.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestProxyC.$(objext) : Public/C/TestProxyC.cpp $(headers)
	$(compiler)TestProxyC.$(objext) -c $(cflags) $(includes) Public/C/TestProxyC.cpp
$(objdir)MainC.$(objext) : Os/$(osdir)/MainC.c $(headers)
	$(compiler)MainC.$(objext) -c $(cflags) $(includes) Os/$(osdir)/MainC.c

TestTopology1: upnp_core $(objdir)CpTopology1.$(objext) $(objdir)TestTopology1.$(objext) TestFramework.$(libext)
	$(linker)TestTopology1.$(exeext) $(objdir)CpTopology1.$(objext) $(objdir)TestTopology1.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)CpTopology1.$(objext) : ControlPoint/Topology/CpTopology1.cpp $(headers)
	$(compiler)CpTopology1.$(objext) -c $(cflags) $(includes) ControlPoint/Topology/CpTopology1.cpp 
$(objdir)TestTopology1.$(objext) : ControlPoint/Topology/TestTopology1.cpp $(headers)
	$(compiler)TestTopology1.$(objext) -c $(cflags) $(includes) ControlPoint/Topology/TestTopology1.cpp

TestTopology2: upnp_core $(objdir)CpTopology1.$(objext) $(objdir)CpTopology2.$(objext) $(objdir)TestTopology2.$(objext) $(objdir)CpLinnCoUkProduct3.$(objext) $(objdir)CpLinnCoUkPreamp4.$(objext) $(objdir)CpUpnpOrgRenderingControl1.$(objext) TestFramework.$(libext)
	$(linker)TestTopology2.$(exeext) $(objdir)CpTopology1.$(objext) $(objdir)CpTopology2.$(objext) $(objdir)TestTopology2.$(objext) $(objdir)CpLinnCoUkProduct3.$(objext) $(objdir)CpLinnCoUkPreamp4.$(objext) $(objdir)CpUpnpOrgRenderingControl1.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)CpTopology2.$(objext) : ControlPoint/Topology/CpTopology2.cpp $(headers)
	$(compiler)CpTopology2.$(objext) -c $(cflags) $(includes) ControlPoint/Topology/CpTopology2.cpp 
$(objdir)TestTopology2.$(objext) : ControlPoint/Topology/TestTopology2.cpp $(headers)
	$(compiler)TestTopology2.$(objext) -c $(cflags) $(includes) ControlPoint/Topology/TestTopology2.cpp

TestTopology3: upnp_core $(objdir)CpTopology1.$(objext) $(objdir)CpTopology2.$(objext) $(objdir)CpTopology3.$(objext) $(objdir)TestTopology3.$(objext) $(objdir)CpLinnCoUkProduct3.$(objext) $(objdir)CpLinnCoUkPreamp4.$(objext) $(objdir)CpUpnpOrgRenderingControl1.$(objext) TestFramework.$(libext)
	$(linker)TestTopology3.$(exeext) $(objdir)CpTopology1.$(objext) $(objdir)CpTopology2.$(objext) $(objdir)CpTopology3.$(objext) $(objdir)TestTopology3.$(objext) $(objdir)CpLinnCoUkProduct3.$(objext) $(objdir)CpLinnCoUkPreamp4.$(objext) $(objdir)CpUpnpOrgRenderingControl1.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)CpTopology3.$(objext) : ControlPoint/Topology/CpTopology3.cpp $(headers)
	$(compiler)CpTopology3.$(objext) -c $(cflags) $(includes) ControlPoint/Topology/CpTopology3.cpp 
$(objdir)TestTopology3.$(objext) : ControlPoint/Topology/TestTopology3.cpp $(headers)
	$(compiler)TestTopology3.$(objext) -c $(cflags) $(includes) ControlPoint/Topology/TestTopology3.cpp

TestDviDiscovery: upnp_core $(objdir)TestDviDiscovery.$(objext) TestFramework.$(libext)
	$(linker)TestDviDiscovery.$(exeext) $(objdir)TestDviDiscovery.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestDviDiscovery.$(objext) : Device/Upnp/TestDviDiscovery.cpp $(headers)
	$(compiler)TestDviDiscovery.$(objext) -c $(cflags) $(includes) Device/Upnp/TestDviDiscovery.cpp

TestDviDeviceList: upnp_core $(objdir)TestDviDeviceList.$(objext) TestFramework.$(libext)
	$(linker)TestDviDeviceList.$(exeext) $(objdir)TestDviDeviceList.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestDviDeviceList.$(objext) : Device/Upnp/TestDviDeviceList.cpp $(headers)
	$(compiler)TestDviDeviceList.$(objext) -c $(cflags) $(includes) Device/Upnp/TestDviDeviceList.cpp

TestDvInvocation: upnp_core $(objdir)TestDvInvocation.$(objext) $(objdir)DvZappOrgTestBasic1.$(objext) $(objdir)CpZappOrgTestBasic1.$(objext) TestFramework.$(libext)
	$(linker)TestDvInvocation.$(exeext) $(objdir)TestDvInvocation.$(objext) $(objdir)DvZappOrgTestBasic1.$(objext) $(objdir)CpZappOrgTestBasic1.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestDvInvocation.$(objext) : Device/Upnp/TestDvInvocation.cpp $(headers)
	$(compiler)TestDvInvocation.$(objext) -c $(cflags) $(includes) Device/Upnp/TestDvInvocation.cpp

TestDvSubscription: upnp_core $(objdir)TestDvSubscription.$(objext) $(objdir)DvZappOrgTestBasic1.$(objext) $(objdir)CpZappOrgTestBasic1.$(objext) TestFramework.$(libext)
	$(linker)TestDvSubscription.$(exeext) $(objdir)TestDvSubscription.$(objext) $(objdir)DvZappOrgTestBasic1.$(objext) $(objdir)CpZappOrgTestBasic1.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestDvSubscription.$(objext) : Device/Upnp/TestDvSubscription.cpp $(headers)
	$(compiler)TestDvSubscription.$(objext) -c $(cflags) $(includes) Device/Upnp/TestDvSubscription.cpp

TestDvLights: upnp_core $(objdir)TestDvLights.$(objext) $(objdir)DvZappOrgTestLights1.$(objext) TestFramework.$(libext)
	$(linker)TestDvLights.$(exeext) $(objdir)TestDvLights.$(objext) $(objdir)DvZappOrgTestLights1.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestDvLights.$(objext) : Device/Upnp/TestDvLights.cpp $(headers)
	$(compiler)TestDvLights.$(objext) -c $(cflags) $(includes) Device/Upnp/TestDvLights.cpp

TestDvDeviceStd: upnp_core $(objdir)TestDvDeviceStd.$(objext) $(objdir)DvZappOrgTestBasic1Std.$(objext) $(objdir)CpZappOrgTestBasic1Std.$(objext) TestFramework.$(libext)
	$(linker)TestDvDeviceStd.$(exeext) $(objdir)TestDvDeviceStd.$(objext) $(objdir)DvZappOrgTestBasic1Std.$(objext) $(objdir)CpZappOrgTestBasic1Std.$(objext) $(objdir)TestFramework.$(libext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestDvDeviceStd.$(objext) : Public/Cpp/Std/TestDvDeviceStd.cpp $(headers)
	$(compiler)TestDvDeviceStd.$(objext) -c $(cflags) $(includes) Public/Cpp/Std/TestDvDeviceStd.cpp

TestDvDeviceC: upnp_core $(objdir)TestDvDeviceC.$(objext) $(objdir)DvZappOrgTestBasic1C.$(objext) $(objdir)DvZappOrgTestBasic1.$(objext) $(objdir)CpZappOrgTestBasic1C.$(objext) $(objdir)CpZappOrgTestBasic1.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext)
	$(linker)TestDvDeviceC.$(exeext) $(objdir)TestDvDeviceC.$(objext) $(objdir)DvZappOrgTestBasic1C.$(objext) $(objdir)DvZappOrgTestBasic1.$(objext) $(objdir)CpZappOrgTestBasic1C.$(objext) $(objdir)CpZappOrgTestBasic1.$(objext) $(objdir)TestFramework.$(objext) $(objdir)MainC.$(objext) $(objdir)$(libprefix)upnp_core.$(libext)
$(objdir)TestDvDeviceC.$(objext) : Public/C/TestDvDeviceC.cpp $(headers)
	$(compiler)TestDvDeviceC.$(objext) -c $(cflags) $(includes) Public/C/TestDvDeviceC.cpp

Tests: TestBuffer TestThread TestFifo TestQueue TestNetwork TestEcho TestTimer TestSsdpMListen TestSsdpUListen TestDeviceList TestDeviceListStd TestDeviceListC TestInvocation TestInvocationStd TestSubscription TestProxyC TestTopology1 TestTopology2 TestTopology3 TestDviDiscovery TestDviDeviceList TestDvInvocation TestDvSubscription TestDvLights TestDvDeviceStd TestDvDeviceC
