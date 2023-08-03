# Auto-generated file.  DO NOT EDIT DIRECTLY
# Update CpUpnpMakeProxies.tt and run
#    make generate-makefiles
# to apply any updates

objects_proxies = \
				  $(objdir)CpUpnpOrgConnectionManager1.$(objext) \
				  $(objdir)CpUpnpOrgConnectionManager1C.$(objext) \
				  $(objdir)CpUpnpOrgConnectionManager1Std.$(objext) \
				  $(objdir)CpAvOpenhomeOrgProduct1.$(objext) \
				  $(objdir)CpAvOpenhomeOrgProduct1C.$(objext) \
				  $(objdir)CpAvOpenhomeOrgProduct1Std.$(objext) \
				  $(objdir)CpAvOpenhomeOrgSender1.$(objext) \
				  $(objdir)CpAvOpenhomeOrgSender1C.$(objext) \
				  $(objdir)CpAvOpenhomeOrgSender1Std.$(objext) \
				  $(objdir)CpOpenhomeOrgTestBasic1.$(objext) \
				  $(objdir)CpOpenhomeOrgTestBasic1C.$(objext) \
				  $(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) \
				  $(objdir)CpOpenhomeOrgSubscriptionLongPoll1.$(objext) \
				  $(objdir)CpOpenhomeOrgSubscriptionLongPoll1C.$(objext) \
				  $(objdir)CpOpenhomeOrgSubscriptionLongPoll1Std.$(objext) \

# Service proxies have well controlled dependencies so we can document a more limited set of headers
headers_proxy = $(inc_build)/OpenHome/Buffer.h \
				$(inc_build)/OpenHome/Buffer.inl \
				$(inc_build)/OpenHome/Exception.h \
				$(inc_build)/OpenHome/Functor.h \
				$(inc_build)/OpenHome/Net/Core/FunctorAsync.h \
				$(inc_build)/OpenHome/Types.h \
				$(inc_build)/OpenHome/Net/Core/CpProxy.h \
				$(inc_build)/OpenHome/Net/Private/CpiService.h \
				$(inc_build)/OpenHome/Net/Private/Service.h \
				$(inc_build)/OpenHome/Private/Thread.h \
				$(inc_build)/OpenHome/Net/Private/AsyncPrivate.h

proxy_dotnet_assemblies = \
		CpUpnpOrgConnectionManager1.net.dll \
		CpAvOpenhomeOrgProduct1.net.dll \
		CpAvOpenhomeOrgSender1.net.dll \
		CpOpenhomeOrgTestBasic1.net.dll \
		CpOpenhomeOrgSubscriptionLongPoll1.net.dll \

proxy_dotnet_assemblies_with_path = \
		$(objdir)CpUpnpOrgConnectionManager1.net.dll \
		$(objdir)CpAvOpenhomeOrgProduct1.net.dll \
		$(objdir)CpAvOpenhomeOrgSender1.net.dll \
		$(objdir)CpOpenhomeOrgTestBasic1.net.dll \
		$(objdir)CpOpenhomeOrgSubscriptionLongPoll1.net.dll \

proxy_java_classes_with_path = \
		$(objdir)org/openhome/net/controlpoint/proxies/CpProxyUpnpOrgConnectionManager1.class \
		$(objdir)org/openhome/net/controlpoint/proxies/CpProxyAvOpenhomeOrgProduct1.class \
		$(objdir)org/openhome/net/controlpoint/proxies/CpProxyAvOpenhomeOrgSender1.class \
		$(objdir)org/openhome/net/controlpoint/proxies/CpProxyOpenhomeOrgTestBasic1.class \
		$(objdir)org/openhome/net/controlpoint/proxies/CpProxyOpenhomeOrgSubscriptionLongPoll1.class \


proxies : ohNetCore $(objects_proxies)
	$(ar)$(libprefix)ohNetProxies.$(libext) $(objects_proxies)
$(objdir)CpUpnpOrgConnectionManager1.$(objext) : $(proxyCppCore)CpUpnpOrgConnectionManager1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpUpnpOrgConnectionManager1.h
	$(compiler)CpUpnpOrgConnectionManager1.$(objext) -c $(cppflags) $(includes) $(proxyCppCore)CpUpnpOrgConnectionManager1.cpp
$(objdir)CpUpnpOrgConnectionManager1C.$(objext) : $(proxyC)CpUpnpOrgConnectionManager1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpUpnpOrgConnectionManager1.h
	$(compiler)CpUpnpOrgConnectionManager1C.$(objext) -c $(cppflags) $(includes) $(proxyC)CpUpnpOrgConnectionManager1C.cpp
$(objdir)CpUpnpOrgConnectionManager1Std.$(objext) : $(proxyCppStd)CpUpnpOrgConnectionManager1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpUpnpOrgConnectionManager1.h
	$(compiler)CpUpnpOrgConnectionManager1Std.$(objext) -c $(cppflags) $(includes) $(proxyCppStd)CpUpnpOrgConnectionManager1Std.cpp
$(objdir)CpAvOpenhomeOrgProduct1.$(objext) : $(proxyCppCore)CpAvOpenhomeOrgProduct1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpAvOpenhomeOrgProduct1.h
	$(compiler)CpAvOpenhomeOrgProduct1.$(objext) -c $(cppflags) $(includes) $(proxyCppCore)CpAvOpenhomeOrgProduct1.cpp
$(objdir)CpAvOpenhomeOrgProduct1C.$(objext) : $(proxyC)CpAvOpenhomeOrgProduct1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpAvOpenhomeOrgProduct1.h
	$(compiler)CpAvOpenhomeOrgProduct1C.$(objext) -c $(cppflags) $(includes) $(proxyC)CpAvOpenhomeOrgProduct1C.cpp
$(objdir)CpAvOpenhomeOrgProduct1Std.$(objext) : $(proxyCppStd)CpAvOpenhomeOrgProduct1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpAvOpenhomeOrgProduct1.h
	$(compiler)CpAvOpenhomeOrgProduct1Std.$(objext) -c $(cppflags) $(includes) $(proxyCppStd)CpAvOpenhomeOrgProduct1Std.cpp
$(objdir)CpAvOpenhomeOrgSender1.$(objext) : $(proxyCppCore)CpAvOpenhomeOrgSender1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpAvOpenhomeOrgSender1.h
	$(compiler)CpAvOpenhomeOrgSender1.$(objext) -c $(cppflags) $(includes) $(proxyCppCore)CpAvOpenhomeOrgSender1.cpp
$(objdir)CpAvOpenhomeOrgSender1C.$(objext) : $(proxyC)CpAvOpenhomeOrgSender1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpAvOpenhomeOrgSender1.h
	$(compiler)CpAvOpenhomeOrgSender1C.$(objext) -c $(cppflags) $(includes) $(proxyC)CpAvOpenhomeOrgSender1C.cpp
$(objdir)CpAvOpenhomeOrgSender1Std.$(objext) : $(proxyCppStd)CpAvOpenhomeOrgSender1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpAvOpenhomeOrgSender1.h
	$(compiler)CpAvOpenhomeOrgSender1Std.$(objext) -c $(cppflags) $(includes) $(proxyCppStd)CpAvOpenhomeOrgSender1Std.cpp
$(objdir)CpOpenhomeOrgTestBasic1.$(objext) : $(proxyCppCore)CpOpenhomeOrgTestBasic1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpOpenhomeOrgTestBasic1.h
	$(compiler)CpOpenhomeOrgTestBasic1.$(objext) -c $(cppflags) $(includes) $(proxyCppCore)CpOpenhomeOrgTestBasic1.cpp
$(objdir)CpOpenhomeOrgTestBasic1C.$(objext) : $(proxyC)CpOpenhomeOrgTestBasic1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpOpenhomeOrgTestBasic1.h
	$(compiler)CpOpenhomeOrgTestBasic1C.$(objext) -c $(cppflags) $(includes) $(proxyC)CpOpenhomeOrgTestBasic1C.cpp
$(objdir)CpOpenhomeOrgTestBasic1Std.$(objext) : $(proxyCppStd)CpOpenhomeOrgTestBasic1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpOpenhomeOrgTestBasic1.h
	$(compiler)CpOpenhomeOrgTestBasic1Std.$(objext) -c $(cppflags) $(includes) $(proxyCppStd)CpOpenhomeOrgTestBasic1Std.cpp
$(objdir)CpOpenhomeOrgSubscriptionLongPoll1.$(objext) : $(proxyCppCore)CpOpenhomeOrgSubscriptionLongPoll1.cpp $(headers_proxy) OpenHome/Net/ControlPoint/Proxies/CpOpenhomeOrgSubscriptionLongPoll1.h
	$(compiler)CpOpenhomeOrgSubscriptionLongPoll1.$(objext) -c $(cppflags) $(includes) $(proxyCppCore)CpOpenhomeOrgSubscriptionLongPoll1.cpp
$(objdir)CpOpenhomeOrgSubscriptionLongPoll1C.$(objext) : $(proxyC)CpOpenhomeOrgSubscriptionLongPoll1C.cpp $(headers_proxy) OpenHome/Net/Bindings/C/ControlPoint/Proxies/CpOpenhomeOrgSubscriptionLongPoll1.h
	$(compiler)CpOpenhomeOrgSubscriptionLongPoll1C.$(objext) -c $(cppflags) $(includes) $(proxyC)CpOpenhomeOrgSubscriptionLongPoll1C.cpp
$(objdir)CpOpenhomeOrgSubscriptionLongPoll1Std.$(objext) : $(proxyCppStd)CpOpenhomeOrgSubscriptionLongPoll1Std.cpp $(headers_proxy) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/CpOpenhomeOrgSubscriptionLongPoll1.h
	$(compiler)CpOpenhomeOrgSubscriptionLongPoll1Std.$(objext) -c $(cppflags) $(includes) $(proxyCppStd)CpOpenhomeOrgSubscriptionLongPoll1Std.cpp

proxy_dlls = \
			 CpUpnpOrgConnectionManager1Dll \
			 CpAvOpenhomeOrgProduct1Dll \
			 CpAvOpenhomeOrgSender1Dll \
			 CpOpenhomeOrgTestBasic1Dll \
			 CpOpenhomeOrgSubscriptionLongPoll1Dll \

CpProxyDlls: $(proxy_dlls)

CpUpnpOrgConnectionManager1Dll: $(objdir)$(dllprefix)CpUpnpOrgConnectionManager1.$(dllext)
$(objdir)$(dllprefix)CpUpnpOrgConnectionManager1.$(dllext) : ZappUpnpDll $(objdir)CpUpnpOrgConnectionManager1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpUpnpOrgConnectionManager1.$(dllext) $(objdir)CpUpnpOrgConnectionManager1.$(objext)
CpAvOpenhomeOrgProduct1Dll: $(objdir)$(dllprefix)CpAvOpenhomeOrgProduct1.$(dllext)
$(objdir)$(dllprefix)CpAvOpenhomeOrgProduct1.$(dllext) : ZappUpnpDll $(objdir)CpAvOpenhomeOrgProduct1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpAvOpenhomeOrgProduct1.$(dllext) $(objdir)CpAvOpenhomeOrgProduct1.$(objext)
CpAvOpenhomeOrgSender1Dll: $(objdir)$(dllprefix)CpAvOpenhomeOrgSender1.$(dllext)
$(objdir)$(dllprefix)CpAvOpenhomeOrgSender1.$(dllext) : ZappUpnpDll $(objdir)CpAvOpenhomeOrgSender1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpAvOpenhomeOrgSender1.$(dllext) $(objdir)CpAvOpenhomeOrgSender1.$(objext)
CpOpenhomeOrgTestBasic1Dll: $(objdir)$(dllprefix)CpOpenhomeOrgTestBasic1.$(dllext)
$(objdir)$(dllprefix)CpOpenhomeOrgTestBasic1.$(dllext) : ZappUpnpDll $(objdir)CpOpenhomeOrgTestBasic1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpOpenhomeOrgTestBasic1.$(dllext) $(objdir)CpOpenhomeOrgTestBasic1.$(objext)
CpOpenhomeOrgSubscriptionLongPoll1Dll: $(objdir)$(dllprefix)CpOpenhomeOrgSubscriptionLongPoll1.$(dllext)
$(objdir)$(dllprefix)CpOpenhomeOrgSubscriptionLongPoll1.$(dllext) : ZappUpnpDll $(objdir)CpOpenhomeOrgSubscriptionLongPoll1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)CpOpenhomeOrgSubscriptionLongPoll1.$(dllext) $(objdir)CpOpenhomeOrgSubscriptionLongPoll1.$(objext)

# Proxy assemblies for .NET:

CpProxyDotNetAssemblies: $(proxy_dotnet_assemblies_with_path)

$(objdir)CpUpnpOrgConnectionManager1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpUpnpOrgConnectionManager1.cs
	$(dotnetsdk) build $(proxyCs)CpUpnpOrgConnectionManager1.csproj --framework $(dotnetFramework) --output $(objdir)
$(objdir)CpAvOpenhomeOrgProduct1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpAvOpenhomeOrgProduct1.cs
	$(dotnetsdk) build $(proxyCs)CpAvOpenhomeOrgProduct1.csproj --framework $(dotnetFramework) --output $(objdir)
$(objdir)CpAvOpenhomeOrgSender1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpAvOpenhomeOrgSender1.cs
	$(dotnetsdk) build $(proxyCs)CpAvOpenhomeOrgSender1.csproj --framework $(dotnetFramework) --output $(objdir)
$(objdir)CpOpenhomeOrgTestBasic1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpOpenhomeOrgTestBasic1.cs
	$(dotnetsdk) build $(proxyCs)CpOpenhomeOrgTestBasic1.csproj --framework $(dotnetFramework) --output $(objdir)
$(objdir)CpOpenhomeOrgSubscriptionLongPoll1.net.dll: $(objdir)ohNet.net.dll $(proxyCs)CpOpenhomeOrgSubscriptionLongPoll1.cs
	$(dotnetsdk) build $(proxyCs)CpOpenhomeOrgSubscriptionLongPoll1.csproj --framework $(dotnetFramework) --output $(objdir)

# Proxy classes for Java:

CpProxyJavaClasses: $(proxy_java_classes_with_path)

$(objdir)org/openhome/net/controlpoint/proxies/CpProxyUpnpOrgConnectionManager1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyUpnpOrgConnectionManager1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyUpnpOrgConnectionManager1.java
$(objdir)org/openhome/net/controlpoint/proxies/CpProxyAvOpenhomeOrgProduct1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyAvOpenhomeOrgProduct1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyAvOpenhomeOrgProduct1.java
$(objdir)org/openhome/net/controlpoint/proxies/CpProxyAvOpenhomeOrgSender1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyAvOpenhomeOrgSender1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyAvOpenhomeOrgSender1.java
$(objdir)org/openhome/net/controlpoint/proxies/CpProxyOpenhomeOrgTestBasic1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyOpenhomeOrgTestBasic1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyOpenhomeOrgTestBasic1.java
$(objdir)org/openhome/net/controlpoint/proxies/CpProxyOpenhomeOrgSubscriptionLongPoll1.class : $(objdir)ohnet.jar $(proxyJava)CpProxyOpenhomeOrgSubscriptionLongPoll1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(proxyJava)CpProxyOpenhomeOrgSubscriptionLongPoll1.java


