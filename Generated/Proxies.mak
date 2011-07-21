# Auto-generated file.  DO NOT EDIT DIRECTLY
# Update CpUpnpMakeProxies.tt and run
#    make generate-makefiles
# to apply any updates

objects_proxies = \
                  $(objdir)CpUpnpOrgAVTransport1.$(objext) \
                  $(objdir)CpUpnpOrgAVTransport1C.$(objext) \
                  $(objdir)CpUpnpOrgAVTransport1Std.$(objext) \
                  $(objdir)CpUpnpOrgAVTransport2.$(objext) \
                  $(objdir)CpUpnpOrgAVTransport2C.$(objext) \
                  $(objdir)CpUpnpOrgAVTransport2Std.$(objext) \
                  $(objdir)CpUpnpOrgConnectionManager1.$(objext) \
                  $(objdir)CpUpnpOrgConnectionManager1C.$(objext) \
                  $(objdir)CpUpnpOrgConnectionManager1Std.$(objext) \
                  $(objdir)CpUpnpOrgConnectionManager2.$(objext) \
                  $(objdir)CpUpnpOrgConnectionManager2C.$(objext) \
                  $(objdir)CpUpnpOrgConnectionManager2Std.$(objext) \
                  $(objdir)CpUpnpOrgContentDirectory1.$(objext) \
                  $(objdir)CpUpnpOrgContentDirectory1C.$(objext) \
                  $(objdir)CpUpnpOrgContentDirectory1Std.$(objext) \
                  $(objdir)CpUpnpOrgContentDirectory2.$(objext) \
                  $(objdir)CpUpnpOrgContentDirectory2C.$(objext) \
                  $(objdir)CpUpnpOrgContentDirectory2Std.$(objext) \
                  $(objdir)CpUpnpOrgContentDirectory3.$(objext) \
                  $(objdir)CpUpnpOrgContentDirectory3C.$(objext) \
                  $(objdir)CpUpnpOrgContentDirectory3Std.$(objext) \
                  $(objdir)CpUpnpOrgRenderingControl1.$(objext) \
                  $(objdir)CpUpnpOrgRenderingControl1C.$(objext) \
                  $(objdir)CpUpnpOrgRenderingControl1Std.$(objext) \
                  $(objdir)CpUpnpOrgRenderingControl2.$(objext) \
                  $(objdir)CpUpnpOrgRenderingControl2C.$(objext) \
                  $(objdir)CpUpnpOrgRenderingControl2Std.$(objext) \
                  $(objdir)CpUpnpOrgScheduledRecording1.$(objext) \
                  $(objdir)CpUpnpOrgScheduledRecording1C.$(objext) \
                  $(objdir)CpUpnpOrgScheduledRecording1Std.$(objext) \
                  $(objdir)CpUpnpOrgScheduledRecording2.$(objext) \
                  $(objdir)CpUpnpOrgScheduledRecording2C.$(objext) \
                  $(objdir)CpUpnpOrgScheduledRecording2Std.$(objext) \
                  $(objdir)CpUpnpOrgSwitchPower1.$(objext) \
                  $(objdir)CpUpnpOrgSwitchPower1C.$(objext) \
                  $(objdir)CpUpnpOrgSwitchPower1Std.$(objext) \
                  $(objdir)CpUpnpOrgDimming1.$(objext) \
                  $(objdir)CpUpnpOrgDimming1C.$(objext) \
                  $(objdir)CpUpnpOrgDimming1Std.$(objext) \
                  $(objdir)CpAvOpenhomeOrgInfo1.$(objext) \
                  $(objdir)CpAvOpenhomeOrgInfo1C.$(objext) \
                  $(objdir)CpAvOpenhomeOrgInfo1Std.$(objext) \
                  $(objdir)CpAvOpenhomeOrgTime1.$(objext) \
                  $(objdir)CpAvOpenhomeOrgTime1C.$(objext) \
                  $(objdir)CpAvOpenhomeOrgTime1Std.$(objext) \
                  $(objdir)CpAvOpenhomeOrgPlaylist1.$(objext) \
                  $(objdir)CpAvOpenhomeOrgPlaylist1C.$(objext) \
                  $(objdir)CpAvOpenhomeOrgPlaylist1Std.$(objext) \
                  $(objdir)CpAvOpenhomeOrgVolume1.$(objext) \
                  $(objdir)CpAvOpenhomeOrgVolume1C.$(objext) \
                  $(objdir)CpAvOpenhomeOrgVolume1Std.$(objext) \
                  $(objdir)CpAvOpenhomeOrgProduct1.$(objext) \
                  $(objdir)CpAvOpenhomeOrgProduct1C.$(objext) \
                  $(objdir)CpAvOpenhomeOrgProduct1Std.$(objext) \
                  $(objdir)CpAvOpenhomeOrgRadio1.$(objext) \
                  $(objdir)CpAvOpenhomeOrgRadio1C.$(objext) \
                  $(objdir)CpAvOpenhomeOrgRadio1Std.$(objext) \
                  $(objdir)CpAvOpenhomeOrgReceiver1.$(objext) \
                  $(objdir)CpAvOpenhomeOrgReceiver1C.$(objext) \
                  $(objdir)CpAvOpenhomeOrgReceiver1Std.$(objext) \
                  $(objdir)CpAvOpenhomeOrgSender1.$(objext) \
                  $(objdir)CpAvOpenhomeOrgSender1C.$(objext) \
                  $(objdir)CpAvOpenhomeOrgSender1Std.$(objext) \
                  $(objdir)CpOpenhomeOrgTestBasic1.$(objext) \
                  $(objdir)CpOpenhomeOrgTestBasic1C.$(objext) \
                  $(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) \
                  $(objdir)CpOpenhomeOrgTestLights1.$(objext) \
                  $(objdir)CpOpenhomeOrgTestLights1C.$(objext) \
                  $(objdir)CpOpenhomeOrgTestLights1Std.$(objext) \

# Service proxies have well controlled dependencies so we can document a more limited set of headers
headers_proxy = $(inc_build)/OpenHome/Buffer.h \
                $(inc_build)/OpenHome/Buffer.inl \
                $(inc_build)/OpenHome/Exception.h \
                $(inc_build)/OpenHome/Functor.h \
                $(inc_build)/OpenHome/Net/Core/FunctorAsync.h \
                $(inc_build)/OpenHome/OhNetTypes.h \
                $(inc_build)/OpenHome/Net/Core/CpProxy.h \
                $(inc_build)/OpenHome/Net/Private/CpiService.h \
                $(inc_build)/OpenHome/Net/Private/Service.h \
                $(inc_build)/OpenHome/Private/Thread.h \
                $(inc_build)/OpenHome/Net/Private/AsyncPrivate.h

proxy_dotnet_assemblies = \
        CpUpnpOrgAVTransport1.net.dll \
        CpUpnpOrgAVTransport2.net.dll \
        CpUpnpOrgConnectionManager1.net.dll \
        CpUpnpOrgConnectionManager2.net.dll \
        CpUpnpOrgContentDirectory1.net.dll \
        CpUpnpOrgContentDirectory2.net.dll \
        CpUpnpOrgContentDirectory3.net.dll \
        CpUpnpOrgRenderingControl1.net.dll \
        CpUpnpOrgRenderingControl2.net.dll \
        CpUpnpOrgScheduledRecording1.net.dll \
        CpUpnpOrgScheduledRecording2.net.dll \
        CpUpnpOrgSwitchPower1.net.dll \
        CpUpnpOrgDimming1.net.dll \
        CpAvOpenhomeOrgInfo1.net.dll \
        CpAvOpenhomeOrgTime1.net.dll \
        CpAvOpenhomeOrgPlaylist1.net.dll \
        CpAvOpenhomeOrgVolume1.net.dll \
        CpAvOpenhomeOrgProduct1.net.dll \
        CpAvOpenhomeOrgRadio1.net.dll \
        CpAvOpenhomeOrgReceiver1.net.dll \
        CpAvOpenhomeOrgSender1.net.dll \
        CpOpenhomeOrgTestBasic1.net.dll \
        CpOpenhomeOrgTestLights1.net.dll \

proxy_dotnet_assemblies_with_path = \
        $(objdir)CpUpnpOrgAVTransport1.net.dll \
        $(objdir)CpUpnpOrgAVTransport2.net.dll \
        $(objdir)CpUpnpOrgConnectionManager1.net.dll \
        $(objdir)CpUpnpOrgConnectionManager2.net.dll \
        $(objdir)CpUpnpOrgContentDirectory1.net.dll \
        $(objdir)CpUpnpOrgContentDirectory2.net.dll \
        $(objdir)CpUpnpOrgContentDirectory3.net.dll \
        $(objdir)CpUpnpOrgRenderingControl1.net.dll \
        $(objdir)CpUpnpOrgRenderingControl2.net.dll \
        $(objdir)CpUpnpOrgScheduledRecording1.net.dll \
        $(objdir)CpUpnpOrgScheduledRecording2.net.dll \
        $(objdir)CpUpnpOrgSwitchPower1.net.dll \
        $(objdir)CpUpnpOrgDimming1.net.dll \
        $(objdir)CpAvOpenhomeOrgInfo1.net.dll \
        $(objdir)CpAvOpenhomeOrgTime1.net.dll \
        $(objdir)CpAvOpenhomeOrgPlaylist1.net.dll \
        $(objdir)CpAvOpenhomeOrgVolume1.net.dll \
        $(objdir)CpAvOpenhomeOrgProduct1.net.dll \
        $(objdir)CpAvOpenhomeOrgRadio1.net.dll \
        $(objdir)CpAvOpenhomeOrgReceiver1.net.dll \
        $(objdir)CpAvOpenhomeOrgSender1.net.dll \
        $(objdir)CpOpenhomeOrgTestBasic1.net.dll \
        $(objdir)CpOpenhomeOrgTestLights1.net.dll \

proxy_java_classes_with_path = \
        $(proxyjavadir)CpProxyUpnpOrgAVTransport1.class \
        $(proxyjavadir)CpProxyUpnpOrgAVTransport2.class \
        $(proxyjavadir)CpProxyUpnpOrgConnectionManager1.class \
        $(proxyjavadir)CpProxyUpnpOrgConnectionManager2.class \
        $(proxyjavadir)CpProxyUpnpOrgContentDirectory1.class \
        $(proxyjavadir)CpProxyUpnpOrgContentDirectory2.class \
        $(proxyjavadir)CpProxyUpnpOrgContentDirectory3.class \
        $(proxyjavadir)CpProxyUpnpOrgRenderingControl1.class \
        $(proxyjavadir)CpProxyUpnpOrgRenderingControl2.class \
        $(proxyjavadir)CpProxyUpnpOrgScheduledRecording1.class \
        $(proxyjavadir)CpProxyUpnpOrgScheduledRecording2.class \
        $(proxyjavadir)CpProxyUpnpOrgSwitchPower1.class \
        $(proxyjavadir)CpProxyUpnpOrgDimming1.class \
        $(proxyjavadir)CpProxyAvOpenhomeOrgInfo1.class \
        $(proxyjavadir)CpProxyAvOpenhomeOrgTime1.class \
        $(proxyjavadir)CpProxyAvOpenhomeOrgPlaylist1.class \
        $(proxyjavadir)CpProxyAvOpenhomeOrgVolume1.class \
        $(proxyjavadir)CpProxyAvOpenhomeOrgProduct1.class \
        $(proxyjavadir)CpProxyAvOpenhomeOrgRadio1.class \
        $(proxyjavadir)CpProxyAvOpenhomeOrgReceiver1.class \
        $(proxyjavadir)CpProxyAvOpenhomeOrgSender1.class \
        $(proxyjavadir)CpProxyOpenhomeOrgTestBasic1.class \
        $(proxyjavadir)CpProxyOpenhomeOrgTestLights1.class \


proxies : ohNetCore $(objects_proxies)
	$(ar)$(libprefix)ohNetProxies.$(libext) $(objects_proxies)
$(objdir)CpUpnpOrgAVTransport1.$(objext) : $(proxyCppCore)CpUpnpOrgAVTransport1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpUpnpOrgAVTransport1.h
	$(compiler)CpUpnpOrgAVTransport1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpUpnpOrgAVTransport1.cpp
$(objdir)CpUpnpOrgAVTransport1C.$(objext) : $(proxyC)CpUpnpOrgAVTransport1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpUpnpOrgAVTransport1.h
	$(compiler)CpUpnpOrgAVTransport1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpUpnpOrgAVTransport1C.cpp
$(objdir)CpUpnpOrgAVTransport1Std.$(objext) : $(proxyCppStd)CpUpnpOrgAVTransport1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpUpnpOrgAVTransport1.h
	$(compiler)CpUpnpOrgAVTransport1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpUpnpOrgAVTransport1Std.cpp
$(objdir)CpUpnpOrgAVTransport2.$(objext) : $(proxyCppCore)CpUpnpOrgAVTransport2.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpUpnpOrgAVTransport2.h
	$(compiler)CpUpnpOrgAVTransport2.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpUpnpOrgAVTransport2.cpp
$(objdir)CpUpnpOrgAVTransport2C.$(objext) : $(proxyC)CpUpnpOrgAVTransport2C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpUpnpOrgAVTransport2.h
	$(compiler)CpUpnpOrgAVTransport2C.$(objext) -c $(cflags) $(includes) $(proxyC)CpUpnpOrgAVTransport2C.cpp
$(objdir)CpUpnpOrgAVTransport2Std.$(objext) : $(proxyCppStd)CpUpnpOrgAVTransport2Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpUpnpOrgAVTransport2.h
	$(compiler)CpUpnpOrgAVTransport2Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpUpnpOrgAVTransport2Std.cpp
$(objdir)CpUpnpOrgConnectionManager1.$(objext) : $(proxyCppCore)CpUpnpOrgConnectionManager1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpUpnpOrgConnectionManager1.h
	$(compiler)CpUpnpOrgConnectionManager1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpUpnpOrgConnectionManager1.cpp
$(objdir)CpUpnpOrgConnectionManager1C.$(objext) : $(proxyC)CpUpnpOrgConnectionManager1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpUpnpOrgConnectionManager1.h
	$(compiler)CpUpnpOrgConnectionManager1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpUpnpOrgConnectionManager1C.cpp
$(objdir)CpUpnpOrgConnectionManager1Std.$(objext) : $(proxyCppStd)CpUpnpOrgConnectionManager1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpUpnpOrgConnectionManager1.h
	$(compiler)CpUpnpOrgConnectionManager1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpUpnpOrgConnectionManager1Std.cpp
$(objdir)CpUpnpOrgConnectionManager2.$(objext) : $(proxyCppCore)CpUpnpOrgConnectionManager2.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpUpnpOrgConnectionManager2.h
	$(compiler)CpUpnpOrgConnectionManager2.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpUpnpOrgConnectionManager2.cpp
$(objdir)CpUpnpOrgConnectionManager2C.$(objext) : $(proxyC)CpUpnpOrgConnectionManager2C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpUpnpOrgConnectionManager2.h
	$(compiler)CpUpnpOrgConnectionManager2C.$(objext) -c $(cflags) $(includes) $(proxyC)CpUpnpOrgConnectionManager2C.cpp
$(objdir)CpUpnpOrgConnectionManager2Std.$(objext) : $(proxyCppStd)CpUpnpOrgConnectionManager2Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpUpnpOrgConnectionManager2.h
	$(compiler)CpUpnpOrgConnectionManager2Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpUpnpOrgConnectionManager2Std.cpp
$(objdir)CpUpnpOrgContentDirectory1.$(objext) : $(proxyCppCore)CpUpnpOrgContentDirectory1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpUpnpOrgContentDirectory1.h
	$(compiler)CpUpnpOrgContentDirectory1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpUpnpOrgContentDirectory1.cpp
$(objdir)CpUpnpOrgContentDirectory1C.$(objext) : $(proxyC)CpUpnpOrgContentDirectory1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpUpnpOrgContentDirectory1.h
	$(compiler)CpUpnpOrgContentDirectory1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpUpnpOrgContentDirectory1C.cpp
$(objdir)CpUpnpOrgContentDirectory1Std.$(objext) : $(proxyCppStd)CpUpnpOrgContentDirectory1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpUpnpOrgContentDirectory1.h
	$(compiler)CpUpnpOrgContentDirectory1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpUpnpOrgContentDirectory1Std.cpp
$(objdir)CpUpnpOrgContentDirectory2.$(objext) : $(proxyCppCore)CpUpnpOrgContentDirectory2.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpUpnpOrgContentDirectory2.h
	$(compiler)CpUpnpOrgContentDirectory2.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpUpnpOrgContentDirectory2.cpp
$(objdir)CpUpnpOrgContentDirectory2C.$(objext) : $(proxyC)CpUpnpOrgContentDirectory2C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpUpnpOrgContentDirectory2.h
	$(compiler)CpUpnpOrgContentDirectory2C.$(objext) -c $(cflags) $(includes) $(proxyC)CpUpnpOrgContentDirectory2C.cpp
$(objdir)CpUpnpOrgContentDirectory2Std.$(objext) : $(proxyCppStd)CpUpnpOrgContentDirectory2Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpUpnpOrgContentDirectory2.h
	$(compiler)CpUpnpOrgContentDirectory2Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpUpnpOrgContentDirectory2Std.cpp
$(objdir)CpUpnpOrgContentDirectory3.$(objext) : $(proxyCppCore)CpUpnpOrgContentDirectory3.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpUpnpOrgContentDirectory3.h
	$(compiler)CpUpnpOrgContentDirectory3.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpUpnpOrgContentDirectory3.cpp
$(objdir)CpUpnpOrgContentDirectory3C.$(objext) : $(proxyC)CpUpnpOrgContentDirectory3C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpUpnpOrgContentDirectory3.h
	$(compiler)CpUpnpOrgContentDirectory3C.$(objext) -c $(cflags) $(includes) $(proxyC)CpUpnpOrgContentDirectory3C.cpp
$(objdir)CpUpnpOrgContentDirectory3Std.$(objext) : $(proxyCppStd)CpUpnpOrgContentDirectory3Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpUpnpOrgContentDirectory3.h
	$(compiler)CpUpnpOrgContentDirectory3Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpUpnpOrgContentDirectory3Std.cpp
$(objdir)CpUpnpOrgRenderingControl1.$(objext) : $(proxyCppCore)CpUpnpOrgRenderingControl1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpUpnpOrgRenderingControl1.h
	$(compiler)CpUpnpOrgRenderingControl1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpUpnpOrgRenderingControl1.cpp
$(objdir)CpUpnpOrgRenderingControl1C.$(objext) : $(proxyC)CpUpnpOrgRenderingControl1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpUpnpOrgRenderingControl1.h
	$(compiler)CpUpnpOrgRenderingControl1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpUpnpOrgRenderingControl1C.cpp
$(objdir)CpUpnpOrgRenderingControl1Std.$(objext) : $(proxyCppStd)CpUpnpOrgRenderingControl1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpUpnpOrgRenderingControl1.h
	$(compiler)CpUpnpOrgRenderingControl1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpUpnpOrgRenderingControl1Std.cpp
$(objdir)CpUpnpOrgRenderingControl2.$(objext) : $(proxyCppCore)CpUpnpOrgRenderingControl2.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpUpnpOrgRenderingControl2.h
	$(compiler)CpUpnpOrgRenderingControl2.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpUpnpOrgRenderingControl2.cpp
$(objdir)CpUpnpOrgRenderingControl2C.$(objext) : $(proxyC)CpUpnpOrgRenderingControl2C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpUpnpOrgRenderingControl2.h
	$(compiler)CpUpnpOrgRenderingControl2C.$(objext) -c $(cflags) $(includes) $(proxyC)CpUpnpOrgRenderingControl2C.cpp
$(objdir)CpUpnpOrgRenderingControl2Std.$(objext) : $(proxyCppStd)CpUpnpOrgRenderingControl2Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpUpnpOrgRenderingControl2.h
	$(compiler)CpUpnpOrgRenderingControl2Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpUpnpOrgRenderingControl2Std.cpp
$(objdir)CpUpnpOrgScheduledRecording1.$(objext) : $(proxyCppCore)CpUpnpOrgScheduledRecording1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpUpnpOrgScheduledRecording1.h
	$(compiler)CpUpnpOrgScheduledRecording1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpUpnpOrgScheduledRecording1.cpp
$(objdir)CpUpnpOrgScheduledRecording1C.$(objext) : $(proxyC)CpUpnpOrgScheduledRecording1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpUpnpOrgScheduledRecording1.h
	$(compiler)CpUpnpOrgScheduledRecording1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpUpnpOrgScheduledRecording1C.cpp
$(objdir)CpUpnpOrgScheduledRecording1Std.$(objext) : $(proxyCppStd)CpUpnpOrgScheduledRecording1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpUpnpOrgScheduledRecording1.h
	$(compiler)CpUpnpOrgScheduledRecording1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpUpnpOrgScheduledRecording1Std.cpp
$(objdir)CpUpnpOrgScheduledRecording2.$(objext) : $(proxyCppCore)CpUpnpOrgScheduledRecording2.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpUpnpOrgScheduledRecording2.h
	$(compiler)CpUpnpOrgScheduledRecording2.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpUpnpOrgScheduledRecording2.cpp
$(objdir)CpUpnpOrgScheduledRecording2C.$(objext) : $(proxyC)CpUpnpOrgScheduledRecording2C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpUpnpOrgScheduledRecording2.h
	$(compiler)CpUpnpOrgScheduledRecording2C.$(objext) -c $(cflags) $(includes) $(proxyC)CpUpnpOrgScheduledRecording2C.cpp
$(objdir)CpUpnpOrgScheduledRecording2Std.$(objext) : $(proxyCppStd)CpUpnpOrgScheduledRecording2Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpUpnpOrgScheduledRecording2.h
	$(compiler)CpUpnpOrgScheduledRecording2Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpUpnpOrgScheduledRecording2Std.cpp
$(objdir)CpUpnpOrgSwitchPower1.$(objext) : $(proxyCppCore)CpUpnpOrgSwitchPower1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpUpnpOrgSwitchPower1.h
	$(compiler)CpUpnpOrgSwitchPower1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpUpnpOrgSwitchPower1.cpp
$(objdir)CpUpnpOrgSwitchPower1C.$(objext) : $(proxyC)CpUpnpOrgSwitchPower1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpUpnpOrgSwitchPower1.h
	$(compiler)CpUpnpOrgSwitchPower1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpUpnpOrgSwitchPower1C.cpp
$(objdir)CpUpnpOrgSwitchPower1Std.$(objext) : $(proxyCppStd)CpUpnpOrgSwitchPower1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpUpnpOrgSwitchPower1.h
	$(compiler)CpUpnpOrgSwitchPower1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpUpnpOrgSwitchPower1Std.cpp
$(objdir)CpUpnpOrgDimming1.$(objext) : $(proxyCppCore)CpUpnpOrgDimming1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpUpnpOrgDimming1.h
	$(compiler)CpUpnpOrgDimming1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpUpnpOrgDimming1.cpp
$(objdir)CpUpnpOrgDimming1C.$(objext) : $(proxyC)CpUpnpOrgDimming1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpUpnpOrgDimming1.h
	$(compiler)CpUpnpOrgDimming1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpUpnpOrgDimming1C.cpp
$(objdir)CpUpnpOrgDimming1Std.$(objext) : $(proxyCppStd)CpUpnpOrgDimming1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpUpnpOrgDimming1.h
	$(compiler)CpUpnpOrgDimming1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpUpnpOrgDimming1Std.cpp
$(objdir)CpAvOpenhomeOrgInfo1.$(objext) : $(proxyCppCore)CpAvOpenhomeOrgInfo1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpAvOpenhomeOrgInfo1.h
	$(compiler)CpAvOpenhomeOrgInfo1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpAvOpenhomeOrgInfo1.cpp
$(objdir)CpAvOpenhomeOrgInfo1C.$(objext) : $(proxyC)CpAvOpenhomeOrgInfo1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpAvOpenhomeOrgInfo1.h
	$(compiler)CpAvOpenhomeOrgInfo1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpAvOpenhomeOrgInfo1C.cpp
$(objdir)CpAvOpenhomeOrgInfo1Std.$(objext) : $(proxyCppStd)CpAvOpenhomeOrgInfo1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpAvOpenhomeOrgInfo1.h
	$(compiler)CpAvOpenhomeOrgInfo1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpAvOpenhomeOrgInfo1Std.cpp
$(objdir)CpAvOpenhomeOrgTime1.$(objext) : $(proxyCppCore)CpAvOpenhomeOrgTime1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpAvOpenhomeOrgTime1.h
	$(compiler)CpAvOpenhomeOrgTime1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpAvOpenhomeOrgTime1.cpp
$(objdir)CpAvOpenhomeOrgTime1C.$(objext) : $(proxyC)CpAvOpenhomeOrgTime1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpAvOpenhomeOrgTime1.h
	$(compiler)CpAvOpenhomeOrgTime1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpAvOpenhomeOrgTime1C.cpp
$(objdir)CpAvOpenhomeOrgTime1Std.$(objext) : $(proxyCppStd)CpAvOpenhomeOrgTime1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpAvOpenhomeOrgTime1.h
	$(compiler)CpAvOpenhomeOrgTime1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpAvOpenhomeOrgTime1Std.cpp
$(objdir)CpAvOpenhomeOrgPlaylist1.$(objext) : $(proxyCppCore)CpAvOpenhomeOrgPlaylist1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpAvOpenhomeOrgPlaylist1.h
	$(compiler)CpAvOpenhomeOrgPlaylist1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpAvOpenhomeOrgPlaylist1.cpp
$(objdir)CpAvOpenhomeOrgPlaylist1C.$(objext) : $(proxyC)CpAvOpenhomeOrgPlaylist1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpAvOpenhomeOrgPlaylist1.h
	$(compiler)CpAvOpenhomeOrgPlaylist1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpAvOpenhomeOrgPlaylist1C.cpp
$(objdir)CpAvOpenhomeOrgPlaylist1Std.$(objext) : $(proxyCppStd)CpAvOpenhomeOrgPlaylist1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpAvOpenhomeOrgPlaylist1.h
	$(compiler)CpAvOpenhomeOrgPlaylist1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpAvOpenhomeOrgPlaylist1Std.cpp
$(objdir)CpAvOpenhomeOrgVolume1.$(objext) : $(proxyCppCore)CpAvOpenhomeOrgVolume1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpAvOpenhomeOrgVolume1.h
	$(compiler)CpAvOpenhomeOrgVolume1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpAvOpenhomeOrgVolume1.cpp
$(objdir)CpAvOpenhomeOrgVolume1C.$(objext) : $(proxyC)CpAvOpenhomeOrgVolume1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpAvOpenhomeOrgVolume1.h
	$(compiler)CpAvOpenhomeOrgVolume1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpAvOpenhomeOrgVolume1C.cpp
$(objdir)CpAvOpenhomeOrgVolume1Std.$(objext) : $(proxyCppStd)CpAvOpenhomeOrgVolume1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpAvOpenhomeOrgVolume1.h
	$(compiler)CpAvOpenhomeOrgVolume1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpAvOpenhomeOrgVolume1Std.cpp
$(objdir)CpAvOpenhomeOrgProduct1.$(objext) : $(proxyCppCore)CpAvOpenhomeOrgProduct1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpAvOpenhomeOrgProduct1.h
	$(compiler)CpAvOpenhomeOrgProduct1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpAvOpenhomeOrgProduct1.cpp
$(objdir)CpAvOpenhomeOrgProduct1C.$(objext) : $(proxyC)CpAvOpenhomeOrgProduct1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpAvOpenhomeOrgProduct1.h
	$(compiler)CpAvOpenhomeOrgProduct1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpAvOpenhomeOrgProduct1C.cpp
$(objdir)CpAvOpenhomeOrgProduct1Std.$(objext) : $(proxyCppStd)CpAvOpenhomeOrgProduct1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpAvOpenhomeOrgProduct1.h
	$(compiler)CpAvOpenhomeOrgProduct1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpAvOpenhomeOrgProduct1Std.cpp
$(objdir)CpAvOpenhomeOrgRadio1.$(objext) : $(proxyCppCore)CpAvOpenhomeOrgRadio1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpAvOpenhomeOrgRadio1.h
	$(compiler)CpAvOpenhomeOrgRadio1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpAvOpenhomeOrgRadio1.cpp
$(objdir)CpAvOpenhomeOrgRadio1C.$(objext) : $(proxyC)CpAvOpenhomeOrgRadio1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpAvOpenhomeOrgRadio1.h
	$(compiler)CpAvOpenhomeOrgRadio1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpAvOpenhomeOrgRadio1C.cpp
$(objdir)CpAvOpenhomeOrgRadio1Std.$(objext) : $(proxyCppStd)CpAvOpenhomeOrgRadio1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpAvOpenhomeOrgRadio1.h
	$(compiler)CpAvOpenhomeOrgRadio1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpAvOpenhomeOrgRadio1Std.cpp
$(objdir)CpAvOpenhomeOrgReceiver1.$(objext) : $(proxyCppCore)CpAvOpenhomeOrgReceiver1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpAvOpenhomeOrgReceiver1.h
	$(compiler)CpAvOpenhomeOrgReceiver1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpAvOpenhomeOrgReceiver1.cpp
$(objdir)CpAvOpenhomeOrgReceiver1C.$(objext) : $(proxyC)CpAvOpenhomeOrgReceiver1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpAvOpenhomeOrgReceiver1.h
	$(compiler)CpAvOpenhomeOrgReceiver1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpAvOpenhomeOrgReceiver1C.cpp
$(objdir)CpAvOpenhomeOrgReceiver1Std.$(objext) : $(proxyCppStd)CpAvOpenhomeOrgReceiver1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpAvOpenhomeOrgReceiver1.h
	$(compiler)CpAvOpenhomeOrgReceiver1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpAvOpenhomeOrgReceiver1Std.cpp
$(objdir)CpAvOpenhomeOrgSender1.$(objext) : $(proxyCppCore)CpAvOpenhomeOrgSender1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpAvOpenhomeOrgSender1.h
	$(compiler)CpAvOpenhomeOrgSender1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpAvOpenhomeOrgSender1.cpp
$(objdir)CpAvOpenhomeOrgSender1C.$(objext) : $(proxyC)CpAvOpenhomeOrgSender1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpAvOpenhomeOrgSender1.h
	$(compiler)CpAvOpenhomeOrgSender1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpAvOpenhomeOrgSender1C.cpp
$(objdir)CpAvOpenhomeOrgSender1Std.$(objext) : $(proxyCppStd)CpAvOpenhomeOrgSender1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpAvOpenhomeOrgSender1.h
	$(compiler)CpAvOpenhomeOrgSender1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpAvOpenhomeOrgSender1Std.cpp
$(objdir)CpOpenhomeOrgTestBasic1.$(objext) : $(proxyCppCore)CpOpenhomeOrgTestBasic1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpOpenhomeOrgTestBasic1.h
	$(compiler)CpOpenhomeOrgTestBasic1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpOpenhomeOrgTestBasic1.cpp
$(objdir)CpOpenhomeOrgTestBasic1C.$(objext) : $(proxyC)CpOpenhomeOrgTestBasic1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpOpenhomeOrgTestBasic1.h
	$(compiler)CpOpenhomeOrgTestBasic1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpOpenhomeOrgTestBasic1C.cpp
$(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) : $(proxyCppStd)CpOpenhomeOrgTestBasic1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpOpenhomeOrgTestBasic1.h
	$(compiler)CpOpenhomeOrgTestBasic1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpOpenhomeOrgTestBasic1Std.cpp
$(objdir)CpOpenhomeOrgTestLights1.$(objext) : $(proxyCppCore)CpOpenhomeOrgTestLights1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpOpenhomeOrgTestLights1.h
	$(compiler)CpOpenhomeOrgTestLights1.$(objext) -c $(cflags) $(includes) $(proxyCppCore)CpOpenhomeOrgTestLights1.cpp
$(objdir)CpOpenhomeOrgTestLights1C.$(objext) : $(proxyC)CpOpenhomeOrgTestLights1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpOpenhomeOrgTestLights1.h
	$(compiler)CpOpenhomeOrgTestLights1C.$(objext) -c $(cflags) $(includes) $(proxyC)CpOpenhomeOrgTestLights1C.cpp
$(objdir)CpOpenhomeOrgTestLights1Std.$(objext) : $(proxyCppStd)CpOpenhomeOrgTestLights1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpOpenhomeOrgTestLights1.h
	$(compiler)CpOpenhomeOrgTestLights1Std.$(objext) -c $(cflags) $(includes) $(proxyCppStd)CpOpenhomeOrgTestLights1Std.cpp

proxy_dlls = \
             CpUpnpOrgAVTransport1Dll \
             CpUpnpOrgAVTransport2Dll \
             CpUpnpOrgConnectionManager1Dll \
             CpUpnpOrgConnectionManager2Dll \
             CpUpnpOrgContentDirectory1Dll \
             CpUpnpOrgContentDirectory2Dll \
             CpUpnpOrgContentDirectory3Dll \
             CpUpnpOrgRenderingControl1Dll \
             CpUpnpOrgRenderingControl2Dll \
             CpUpnpOrgScheduledRecording1Dll \
             CpUpnpOrgScheduledRecording2Dll \
             CpUpnpOrgSwitchPower1Dll \
             CpUpnpOrgDimming1Dll \
             CpAvOpenhomeOrgInfo1Dll \
             CpAvOpenhomeOrgTime1Dll \
             CpAvOpenhomeOrgPlaylist1Dll \
             CpAvOpenhomeOrgVolume1Dll \
             CpAvOpenhomeOrgProduct1Dll \
             CpAvOpenhomeOrgRadio1Dll \
             CpAvOpenhomeOrgReceiver1Dll \
             CpAvOpenhomeOrgSender1Dll \
             CpOpenhomeOrgTestBasic1Dll \
             CpOpenhomeOrgTestLights1Dll \

CpProxyDlls: $(proxy_dlls)

CpUpnpOrgAVTransport1Dll: $(objdir)$(dllprefix)CpUpnpOrgAVTransport1.$(dllext)
$(objdir)$(dllprefix)CpUpnpOrgAVTransport1.$(dllext) : ZappUpnpDll $(objdir)CpUpnpOrgAVTransport1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpUpnpOrgAVTransport1.$(dllext) $(objdir)CpUpnpOrgAVTransport1.$(objext)
CpUpnpOrgAVTransport2Dll: $(objdir)$(dllprefix)CpUpnpOrgAVTransport2.$(dllext)
$(objdir)$(dllprefix)CpUpnpOrgAVTransport2.$(dllext) : ZappUpnpDll $(objdir)CpUpnpOrgAVTransport2.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpUpnpOrgAVTransport2.$(dllext) $(objdir)CpUpnpOrgAVTransport2.$(objext)
CpUpnpOrgConnectionManager1Dll: $(objdir)$(dllprefix)CpUpnpOrgConnectionManager1.$(dllext)
$(objdir)$(dllprefix)CpUpnpOrgConnectionManager1.$(dllext) : ZappUpnpDll $(objdir)CpUpnpOrgConnectionManager1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpUpnpOrgConnectionManager1.$(dllext) $(objdir)CpUpnpOrgConnectionManager1.$(objext)
CpUpnpOrgConnectionManager2Dll: $(objdir)$(dllprefix)CpUpnpOrgConnectionManager2.$(dllext)
$(objdir)$(dllprefix)CpUpnpOrgConnectionManager2.$(dllext) : ZappUpnpDll $(objdir)CpUpnpOrgConnectionManager2.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpUpnpOrgConnectionManager2.$(dllext) $(objdir)CpUpnpOrgConnectionManager2.$(objext)
CpUpnpOrgContentDirectory1Dll: $(objdir)$(dllprefix)CpUpnpOrgContentDirectory1.$(dllext)
$(objdir)$(dllprefix)CpUpnpOrgContentDirectory1.$(dllext) : ZappUpnpDll $(objdir)CpUpnpOrgContentDirectory1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpUpnpOrgContentDirectory1.$(dllext) $(objdir)CpUpnpOrgContentDirectory1.$(objext)
CpUpnpOrgContentDirectory2Dll: $(objdir)$(dllprefix)CpUpnpOrgContentDirectory2.$(dllext)
$(objdir)$(dllprefix)CpUpnpOrgContentDirectory2.$(dllext) : ZappUpnpDll $(objdir)CpUpnpOrgContentDirectory2.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpUpnpOrgContentDirectory2.$(dllext) $(objdir)CpUpnpOrgContentDirectory2.$(objext)
CpUpnpOrgContentDirectory3Dll: $(objdir)$(dllprefix)CpUpnpOrgContentDirectory3.$(dllext)
$(objdir)$(dllprefix)CpUpnpOrgContentDirectory3.$(dllext) : ZappUpnpDll $(objdir)CpUpnpOrgContentDirectory3.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpUpnpOrgContentDirectory3.$(dllext) $(objdir)CpUpnpOrgContentDirectory3.$(objext)
CpUpnpOrgRenderingControl1Dll: $(objdir)$(dllprefix)CpUpnpOrgRenderingControl1.$(dllext)
$(objdir)$(dllprefix)CpUpnpOrgRenderingControl1.$(dllext) : ZappUpnpDll $(objdir)CpUpnpOrgRenderingControl1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpUpnpOrgRenderingControl1.$(dllext) $(objdir)CpUpnpOrgRenderingControl1.$(objext)
CpUpnpOrgRenderingControl2Dll: $(objdir)$(dllprefix)CpUpnpOrgRenderingControl2.$(dllext)
$(objdir)$(dllprefix)CpUpnpOrgRenderingControl2.$(dllext) : ZappUpnpDll $(objdir)CpUpnpOrgRenderingControl2.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpUpnpOrgRenderingControl2.$(dllext) $(objdir)CpUpnpOrgRenderingControl2.$(objext)
CpUpnpOrgScheduledRecording1Dll: $(objdir)$(dllprefix)CpUpnpOrgScheduledRecording1.$(dllext)
$(objdir)$(dllprefix)CpUpnpOrgScheduledRecording1.$(dllext) : ZappUpnpDll $(objdir)CpUpnpOrgScheduledRecording1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpUpnpOrgScheduledRecording1.$(dllext) $(objdir)CpUpnpOrgScheduledRecording1.$(objext)
CpUpnpOrgScheduledRecording2Dll: $(objdir)$(dllprefix)CpUpnpOrgScheduledRecording2.$(dllext)
$(objdir)$(dllprefix)CpUpnpOrgScheduledRecording2.$(dllext) : ZappUpnpDll $(objdir)CpUpnpOrgScheduledRecording2.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpUpnpOrgScheduledRecording2.$(dllext) $(objdir)CpUpnpOrgScheduledRecording2.$(objext)
CpUpnpOrgSwitchPower1Dll: $(objdir)$(dllprefix)CpUpnpOrgSwitchPower1.$(dllext)
$(objdir)$(dllprefix)CpUpnpOrgSwitchPower1.$(dllext) : ZappUpnpDll $(objdir)CpUpnpOrgSwitchPower1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpUpnpOrgSwitchPower1.$(dllext) $(objdir)CpUpnpOrgSwitchPower1.$(objext)
CpUpnpOrgDimming1Dll: $(objdir)$(dllprefix)CpUpnpOrgDimming1.$(dllext)
$(objdir)$(dllprefix)CpUpnpOrgDimming1.$(dllext) : ZappUpnpDll $(objdir)CpUpnpOrgDimming1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpUpnpOrgDimming1.$(dllext) $(objdir)CpUpnpOrgDimming1.$(objext)
CpAvOpenhomeOrgInfo1Dll: $(objdir)$(dllprefix)CpAvOpenhomeOrgInfo1.$(dllext)
$(objdir)$(dllprefix)CpAvOpenhomeOrgInfo1.$(dllext) : ZappUpnpDll $(objdir)CpAvOpenhomeOrgInfo1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpAvOpenhomeOrgInfo1.$(dllext) $(objdir)CpAvOpenhomeOrgInfo1.$(objext)
CpAvOpenhomeOrgTime1Dll: $(objdir)$(dllprefix)CpAvOpenhomeOrgTime1.$(dllext)
$(objdir)$(dllprefix)CpAvOpenhomeOrgTime1.$(dllext) : ZappUpnpDll $(objdir)CpAvOpenhomeOrgTime1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpAvOpenhomeOrgTime1.$(dllext) $(objdir)CpAvOpenhomeOrgTime1.$(objext)
CpAvOpenhomeOrgPlaylist1Dll: $(objdir)$(dllprefix)CpAvOpenhomeOrgPlaylist1.$(dllext)
$(objdir)$(dllprefix)CpAvOpenhomeOrgPlaylist1.$(dllext) : ZappUpnpDll $(objdir)CpAvOpenhomeOrgPlaylist1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpAvOpenhomeOrgPlaylist1.$(dllext) $(objdir)CpAvOpenhomeOrgPlaylist1.$(objext)
CpAvOpenhomeOrgVolume1Dll: $(objdir)$(dllprefix)CpAvOpenhomeOrgVolume1.$(dllext)
$(objdir)$(dllprefix)CpAvOpenhomeOrgVolume1.$(dllext) : ZappUpnpDll $(objdir)CpAvOpenhomeOrgVolume1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpAvOpenhomeOrgVolume1.$(dllext) $(objdir)CpAvOpenhomeOrgVolume1.$(objext)
CpAvOpenhomeOrgProduct1Dll: $(objdir)$(dllprefix)CpAvOpenhomeOrgProduct1.$(dllext)
$(objdir)$(dllprefix)CpAvOpenhomeOrgProduct1.$(dllext) : ZappUpnpDll $(objdir)CpAvOpenhomeOrgProduct1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpAvOpenhomeOrgProduct1.$(dllext) $(objdir)CpAvOpenhomeOrgProduct1.$(objext)
CpAvOpenhomeOrgRadio1Dll: $(objdir)$(dllprefix)CpAvOpenhomeOrgRadio1.$(dllext)
$(objdir)$(dllprefix)CpAvOpenhomeOrgRadio1.$(dllext) : ZappUpnpDll $(objdir)CpAvOpenhomeOrgRadio1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpAvOpenhomeOrgRadio1.$(dllext) $(objdir)CpAvOpenhomeOrgRadio1.$(objext)
CpAvOpenhomeOrgReceiver1Dll: $(objdir)$(dllprefix)CpAvOpenhomeOrgReceiver1.$(dllext)
$(objdir)$(dllprefix)CpAvOpenhomeOrgReceiver1.$(dllext) : ZappUpnpDll $(objdir)CpAvOpenhomeOrgReceiver1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpAvOpenhomeOrgReceiver1.$(dllext) $(objdir)CpAvOpenhomeOrgReceiver1.$(objext)
CpAvOpenhomeOrgSender1Dll: $(objdir)$(dllprefix)CpAvOpenhomeOrgSender1.$(dllext)
$(objdir)$(dllprefix)CpAvOpenhomeOrgSender1.$(dllext) : ZappUpnpDll $(objdir)CpAvOpenhomeOrgSender1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpAvOpenhomeOrgSender1.$(dllext) $(objdir)CpAvOpenhomeOrgSender1.$(objext)
CpOpenhomeOrgTestBasic1Dll: $(objdir)$(dllprefix)CpOpenhomeOrgTestBasic1.$(dllext)
$(objdir)$(dllprefix)CpOpenhomeOrgTestBasic1.$(dllext) : ZappUpnpDll $(objdir)CpOpenhomeOrgTestBasic1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpOpenhomeOrgTestBasic1.$(dllext) $(objdir)CpOpenhomeOrgTestBasic1.$(objext)
CpOpenhomeOrgTestLights1Dll: $(objdir)$(dllprefix)CpOpenhomeOrgTestLights1.$(dllext)
$(objdir)$(dllprefix)CpOpenhomeOrgTestLights1.$(dllext) : ZappUpnpDll $(objdir)CpOpenhomeOrgTestLights1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpOpenhomeOrgTestLights1.$(dllext) $(objdir)CpOpenhomeOrgTestLights1.$(objext)

# Proxy assemblies for .NET:

CpProxyDotNetAssemblies: $(proxy_dotnet_assemblies_with_path)

$(objdir)CpUpnpOrgAVTransport1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpUpnpOrgAVTransport1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpUpnpOrgAVTransport1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpUpnpOrgAVTransport1.cs
$(objdir)CpUpnpOrgAVTransport2.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpUpnpOrgAVTransport2.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpUpnpOrgAVTransport2.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpUpnpOrgAVTransport2.cs
$(objdir)CpUpnpOrgConnectionManager1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpUpnpOrgConnectionManager1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpUpnpOrgConnectionManager1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpUpnpOrgConnectionManager1.cs
$(objdir)CpUpnpOrgConnectionManager2.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpUpnpOrgConnectionManager2.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpUpnpOrgConnectionManager2.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpUpnpOrgConnectionManager2.cs
$(objdir)CpUpnpOrgContentDirectory1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpUpnpOrgContentDirectory1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpUpnpOrgContentDirectory1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpUpnpOrgContentDirectory1.cs
$(objdir)CpUpnpOrgContentDirectory2.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpUpnpOrgContentDirectory2.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpUpnpOrgContentDirectory2.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpUpnpOrgContentDirectory2.cs
$(objdir)CpUpnpOrgContentDirectory3.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpUpnpOrgContentDirectory3.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpUpnpOrgContentDirectory3.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpUpnpOrgContentDirectory3.cs
$(objdir)CpUpnpOrgRenderingControl1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpUpnpOrgRenderingControl1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpUpnpOrgRenderingControl1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpUpnpOrgRenderingControl1.cs
$(objdir)CpUpnpOrgRenderingControl2.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpUpnpOrgRenderingControl2.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpUpnpOrgRenderingControl2.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpUpnpOrgRenderingControl2.cs
$(objdir)CpUpnpOrgScheduledRecording1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpUpnpOrgScheduledRecording1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpUpnpOrgScheduledRecording1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpUpnpOrgScheduledRecording1.cs
$(objdir)CpUpnpOrgScheduledRecording2.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpUpnpOrgScheduledRecording2.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpUpnpOrgScheduledRecording2.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpUpnpOrgScheduledRecording2.cs
$(objdir)CpUpnpOrgSwitchPower1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpUpnpOrgSwitchPower1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpUpnpOrgSwitchPower1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpUpnpOrgSwitchPower1.cs
$(objdir)CpUpnpOrgDimming1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpUpnpOrgDimming1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpUpnpOrgDimming1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpUpnpOrgDimming1.cs
$(objdir)CpAvOpenhomeOrgInfo1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpAvOpenhomeOrgInfo1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpAvOpenhomeOrgInfo1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpAvOpenhomeOrgInfo1.cs
$(objdir)CpAvOpenhomeOrgTime1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpAvOpenhomeOrgTime1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpAvOpenhomeOrgTime1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpAvOpenhomeOrgTime1.cs
$(objdir)CpAvOpenhomeOrgPlaylist1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpAvOpenhomeOrgPlaylist1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpAvOpenhomeOrgPlaylist1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpAvOpenhomeOrgPlaylist1.cs
$(objdir)CpAvOpenhomeOrgVolume1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpAvOpenhomeOrgVolume1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpAvOpenhomeOrgVolume1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpAvOpenhomeOrgVolume1.cs
$(objdir)CpAvOpenhomeOrgProduct1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpAvOpenhomeOrgProduct1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpAvOpenhomeOrgProduct1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpAvOpenhomeOrgProduct1.cs
$(objdir)CpAvOpenhomeOrgRadio1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpAvOpenhomeOrgRadio1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpAvOpenhomeOrgRadio1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpAvOpenhomeOrgRadio1.cs
$(objdir)CpAvOpenhomeOrgReceiver1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpAvOpenhomeOrgReceiver1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpAvOpenhomeOrgReceiver1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpAvOpenhomeOrgReceiver1.cs
$(objdir)CpAvOpenhomeOrgSender1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpAvOpenhomeOrgSender1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpAvOpenhomeOrgSender1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpAvOpenhomeOrgSender1.cs
$(objdir)CpOpenhomeOrgTestBasic1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpOpenhomeOrgTestBasic1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpOpenhomeOrgTestBasic1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpOpenhomeOrgTestBasic1.cs
$(objdir)CpOpenhomeOrgTestLights1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpOpenhomeOrgTestLights1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)CpOpenhomeOrgTestLights1.net.dll \
		/reference:$(objdir)ohNet.net.dll \
		$(proxyCs)CpOpenhomeOrgTestLights1.cs

# Proxy classes for Java:

CpProxyJavaClasses: $(proxy_java_classes_with_path)

$(proxyjavadir)CpProxyUpnpOrgAVTransport1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyUpnpOrgAVTransport1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyUpnpOrgAVTransport1.java
$(proxyjavadir)CpProxyUpnpOrgAVTransport2.class : $(objdir)ohnet.jar $(proxyJava)CpProxyUpnpOrgAVTransport2.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyUpnpOrgAVTransport2.java
$(proxyjavadir)CpProxyUpnpOrgConnectionManager1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyUpnpOrgConnectionManager1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyUpnpOrgConnectionManager1.java
$(proxyjavadir)CpProxyUpnpOrgConnectionManager2.class : $(objdir)ohnet.jar $(proxyJava)CpProxyUpnpOrgConnectionManager2.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyUpnpOrgConnectionManager2.java
$(proxyjavadir)CpProxyUpnpOrgContentDirectory1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyUpnpOrgContentDirectory1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyUpnpOrgContentDirectory1.java
$(proxyjavadir)CpProxyUpnpOrgContentDirectory2.class : $(objdir)ohnet.jar $(proxyJava)CpProxyUpnpOrgContentDirectory2.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyUpnpOrgContentDirectory2.java
$(proxyjavadir)CpProxyUpnpOrgContentDirectory3.class : $(objdir)ohnet.jar $(proxyJava)CpProxyUpnpOrgContentDirectory3.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyUpnpOrgContentDirectory3.java
$(proxyjavadir)CpProxyUpnpOrgRenderingControl1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyUpnpOrgRenderingControl1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyUpnpOrgRenderingControl1.java
$(proxyjavadir)CpProxyUpnpOrgRenderingControl2.class : $(objdir)ohnet.jar $(proxyJava)CpProxyUpnpOrgRenderingControl2.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyUpnpOrgRenderingControl2.java
$(proxyjavadir)CpProxyUpnpOrgScheduledRecording1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyUpnpOrgScheduledRecording1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyUpnpOrgScheduledRecording1.java
$(proxyjavadir)CpProxyUpnpOrgScheduledRecording2.class : $(objdir)ohnet.jar $(proxyJava)CpProxyUpnpOrgScheduledRecording2.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyUpnpOrgScheduledRecording2.java
$(proxyjavadir)CpProxyUpnpOrgSwitchPower1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyUpnpOrgSwitchPower1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyUpnpOrgSwitchPower1.java
$(proxyjavadir)CpProxyUpnpOrgDimming1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyUpnpOrgDimming1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyUpnpOrgDimming1.java
$(proxyjavadir)CpProxyAvOpenhomeOrgInfo1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyAvOpenhomeOrgInfo1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyAvOpenhomeOrgInfo1.java
$(proxyjavadir)CpProxyAvOpenhomeOrgTime1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyAvOpenhomeOrgTime1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyAvOpenhomeOrgTime1.java
$(proxyjavadir)CpProxyAvOpenhomeOrgPlaylist1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyAvOpenhomeOrgPlaylist1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyAvOpenhomeOrgPlaylist1.java
$(proxyjavadir)CpProxyAvOpenhomeOrgVolume1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyAvOpenhomeOrgVolume1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyAvOpenhomeOrgVolume1.java
$(proxyjavadir)CpProxyAvOpenhomeOrgProduct1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyAvOpenhomeOrgProduct1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyAvOpenhomeOrgProduct1.java
$(proxyjavadir)CpProxyAvOpenhomeOrgRadio1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyAvOpenhomeOrgRadio1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyAvOpenhomeOrgRadio1.java
$(proxyjavadir)CpProxyAvOpenhomeOrgReceiver1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyAvOpenhomeOrgReceiver1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyAvOpenhomeOrgReceiver1.java
$(proxyjavadir)CpProxyAvOpenhomeOrgSender1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyAvOpenhomeOrgSender1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyAvOpenhomeOrgSender1.java
$(proxyjavadir)CpProxyOpenhomeOrgTestBasic1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyOpenhomeOrgTestBasic1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyOpenhomeOrgTestBasic1.java
$(proxyjavadir)CpProxyOpenhomeOrgTestLights1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyOpenhomeOrgTestLights1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyOpenhomeOrgTestLights1.java

