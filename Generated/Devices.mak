# Auto-generated file.  DO NOT EDIT DIRECTLY
# Update DvUpnpMakeDevices.tt and run
#    make generate-makefiles
# to apply any updates

objects_devices = \
				  $(objdir)DvUpnpOrgConnectionManager1.$(objext) \
				  $(objdir)DvUpnpOrgConnectionManager1Std.$(objext) \
				  $(objdir)DvUpnpOrgConnectionManager1C.$(objext) \
				  $(objdir)DvAvOpenhomeOrgProduct1.$(objext) \
				  $(objdir)DvAvOpenhomeOrgProduct1Std.$(objext) \
				  $(objdir)DvAvOpenhomeOrgProduct1C.$(objext) \
				  $(objdir)DvAvOpenhomeOrgSender1.$(objext) \
				  $(objdir)DvAvOpenhomeOrgSender1Std.$(objext) \
				  $(objdir)DvAvOpenhomeOrgSender1C.$(objext) \
				  $(objdir)DvOpenhomeOrgTestBasic1.$(objext) \
				  $(objdir)DvOpenhomeOrgTestBasic1Std.$(objext) \
				  $(objdir)DvOpenhomeOrgTestBasic1C.$(objext) \
				  $(objdir)DvOpenhomeOrgSubscriptionLongPoll1.$(objext) \
				  $(objdir)DvOpenhomeOrgSubscriptionLongPoll1Std.$(objext) \
				  $(objdir)DvOpenhomeOrgSubscriptionLongPoll1C.$(objext) \

# Devices have well controlled dependencies so we can document a more limited set of headers
headers_device = $(inc_build)/OpenHome/Types.h \
				 $(inc_build)/OpenHome/Net/Private/DviService.h \
				 $(inc_build)/OpenHome/Functor.h \
				 $(inc_build)/OpenHome/Net/Private/Service.h \
				 $(inc_build)/OpenHome/Net/Private/FunctorDviInvocation.h

device_dotnet_assemblies = \
		DvUpnpOrgConnectionManager1.net.dll \
		DvAvOpenhomeOrgProduct1.net.dll \
		DvAvOpenhomeOrgSender1.net.dll \
		DvOpenhomeOrgTestBasic1.net.dll \
		DvOpenhomeOrgSubscriptionLongPoll1.net.dll \

device_dotnet_assemblies_with_path = \
		$(objdir)DvUpnpOrgConnectionManager1.net.dll \
		$(objdir)DvAvOpenhomeOrgProduct1.net.dll \
		$(objdir)DvAvOpenhomeOrgSender1.net.dll \
		$(objdir)DvOpenhomeOrgTestBasic1.net.dll \
		$(objdir)DvOpenhomeOrgSubscriptionLongPoll1.net.dll \

device_java_classes_with_path = \
		$(objdir)org/openhome/net/device/providers/DvProviderUpnpOrgConnectionManager1.class \
		$(objdir)org/openhome/net/device/providers/DvProviderAvOpenhomeOrgProduct1.class \
		$(objdir)org/openhome/net/device/providers/DvProviderAvOpenhomeOrgSender1.class \
		$(objdir)org/openhome/net/device/providers/DvProviderOpenhomeOrgTestBasic1.class \
		$(objdir)org/openhome/net/device/providers/DvProviderOpenhomeOrgSubscriptionLongPoll1.class \

devices : ohNetCore $(objects_devices)
	$(ar)$(libprefix)ohNetDevices.$(libext) $(objects_devices)
$(objdir)DvUpnpOrgConnectionManager1.$(objext) : $(deviceCppCore)DvUpnpOrgConnectionManager1.cpp $(headers_device) OpenHome/Net/Device/Providers/DvUpnpOrgConnectionManager1.h
	$(compiler)DvUpnpOrgConnectionManager1.$(objext) -c $(cppflags) $(includes) $(deviceCppCore)DvUpnpOrgConnectionManager1.cpp
$(objdir)DvUpnpOrgConnectionManager1Std.$(objext) : $(deviceCppStd)DvUpnpOrgConnectionManager1Std.cpp $(headers_device) OpenHome/Net/Bindings/Cpp/Device/Providers/DvUpnpOrgConnectionManager1.h
	$(compiler)DvUpnpOrgConnectionManager1Std.$(objext) -c $(cppflags) $(includes) $(deviceCppStd)DvUpnpOrgConnectionManager1Std.cpp
$(objdir)DvUpnpOrgConnectionManager1C.$(objext) : $(deviceC)DvUpnpOrgConnectionManager1C.cpp $(headers_device) OpenHome/Net/Bindings/C/Device/Providers/DvUpnpOrgConnectionManager1.h
	$(compiler)DvUpnpOrgConnectionManager1C.$(objext) -c $(cppflags) $(includes) $(deviceC)DvUpnpOrgConnectionManager1C.cpp
$(objdir)DvAvOpenhomeOrgProduct1.$(objext) : $(deviceCppCore)DvAvOpenhomeOrgProduct1.cpp $(headers_device) OpenHome/Net/Device/Providers/DvAvOpenhomeOrgProduct1.h
	$(compiler)DvAvOpenhomeOrgProduct1.$(objext) -c $(cppflags) $(includes) $(deviceCppCore)DvAvOpenhomeOrgProduct1.cpp
$(objdir)DvAvOpenhomeOrgProduct1Std.$(objext) : $(deviceCppStd)DvAvOpenhomeOrgProduct1Std.cpp $(headers_device) OpenHome/Net/Bindings/Cpp/Device/Providers/DvAvOpenhomeOrgProduct1.h
	$(compiler)DvAvOpenhomeOrgProduct1Std.$(objext) -c $(cppflags) $(includes) $(deviceCppStd)DvAvOpenhomeOrgProduct1Std.cpp
$(objdir)DvAvOpenhomeOrgProduct1C.$(objext) : $(deviceC)DvAvOpenhomeOrgProduct1C.cpp $(headers_device) OpenHome/Net/Bindings/C/Device/Providers/DvAvOpenhomeOrgProduct1.h
	$(compiler)DvAvOpenhomeOrgProduct1C.$(objext) -c $(cppflags) $(includes) $(deviceC)DvAvOpenhomeOrgProduct1C.cpp
$(objdir)DvAvOpenhomeOrgSender1.$(objext) : $(deviceCppCore)DvAvOpenhomeOrgSender1.cpp $(headers_device) OpenHome/Net/Device/Providers/DvAvOpenhomeOrgSender1.h
	$(compiler)DvAvOpenhomeOrgSender1.$(objext) -c $(cppflags) $(includes) $(deviceCppCore)DvAvOpenhomeOrgSender1.cpp
$(objdir)DvAvOpenhomeOrgSender1Std.$(objext) : $(deviceCppStd)DvAvOpenhomeOrgSender1Std.cpp $(headers_device) OpenHome/Net/Bindings/Cpp/Device/Providers/DvAvOpenhomeOrgSender1.h
	$(compiler)DvAvOpenhomeOrgSender1Std.$(objext) -c $(cppflags) $(includes) $(deviceCppStd)DvAvOpenhomeOrgSender1Std.cpp
$(objdir)DvAvOpenhomeOrgSender1C.$(objext) : $(deviceC)DvAvOpenhomeOrgSender1C.cpp $(headers_device) OpenHome/Net/Bindings/C/Device/Providers/DvAvOpenhomeOrgSender1.h
	$(compiler)DvAvOpenhomeOrgSender1C.$(objext) -c $(cppflags) $(includes) $(deviceC)DvAvOpenhomeOrgSender1C.cpp
$(objdir)DvOpenhomeOrgTestBasic1.$(objext) : $(deviceCppCore)DvOpenhomeOrgTestBasic1.cpp $(headers_device) OpenHome/Net/Device/Providers/DvOpenhomeOrgTestBasic1.h
	$(compiler)DvOpenhomeOrgTestBasic1.$(objext) -c $(cppflags) $(includes) $(deviceCppCore)DvOpenhomeOrgTestBasic1.cpp
$(objdir)DvOpenhomeOrgTestBasic1Std.$(objext) : $(deviceCppStd)DvOpenhomeOrgTestBasic1Std.cpp $(headers_device) OpenHome/Net/Bindings/Cpp/Device/Providers/DvOpenhomeOrgTestBasic1.h
	$(compiler)DvOpenhomeOrgTestBasic1Std.$(objext) -c $(cppflags) $(includes) $(deviceCppStd)DvOpenhomeOrgTestBasic1Std.cpp
$(objdir)DvOpenhomeOrgTestBasic1C.$(objext) : $(deviceC)DvOpenhomeOrgTestBasic1C.cpp $(headers_device) OpenHome/Net/Bindings/C/Device/Providers/DvOpenhomeOrgTestBasic1.h
	$(compiler)DvOpenhomeOrgTestBasic1C.$(objext) -c $(cppflags) $(includes) $(deviceC)DvOpenhomeOrgTestBasic1C.cpp
$(objdir)DvOpenhomeOrgSubscriptionLongPoll1.$(objext) : $(deviceCppCore)DvOpenhomeOrgSubscriptionLongPoll1.cpp $(headers_device) OpenHome/Net/Device/Providers/DvOpenhomeOrgSubscriptionLongPoll1.h
	$(compiler)DvOpenhomeOrgSubscriptionLongPoll1.$(objext) -c $(cppflags) $(includes) $(deviceCppCore)DvOpenhomeOrgSubscriptionLongPoll1.cpp
$(objdir)DvOpenhomeOrgSubscriptionLongPoll1Std.$(objext) : $(deviceCppStd)DvOpenhomeOrgSubscriptionLongPoll1Std.cpp $(headers_device) OpenHome/Net/Bindings/Cpp/Device/Providers/DvOpenhomeOrgSubscriptionLongPoll1.h
	$(compiler)DvOpenhomeOrgSubscriptionLongPoll1Std.$(objext) -c $(cppflags) $(includes) $(deviceCppStd)DvOpenhomeOrgSubscriptionLongPoll1Std.cpp
$(objdir)DvOpenhomeOrgSubscriptionLongPoll1C.$(objext) : $(deviceC)DvOpenhomeOrgSubscriptionLongPoll1C.cpp $(headers_device) OpenHome/Net/Bindings/C/Device/Providers/DvOpenhomeOrgSubscriptionLongPoll1.h
	$(compiler)DvOpenhomeOrgSubscriptionLongPoll1C.$(objext) -c $(cppflags) $(includes) $(deviceC)DvOpenhomeOrgSubscriptionLongPoll1C.cpp

device_dlls = \
			 DvUpnpOrgConnectionManager1Dll \
			 DvAvOpenhomeOrgProduct1Dll \
			 DvAvOpenhomeOrgSender1Dll \
			 DvOpenhomeOrgTestBasic1Dll \
			 DvOpenhomeOrgSubscriptionLongPoll1Dll \

DvDeviceDlls: $(device_dlls)
DvUpnpOrgConnectionManager1Dll: $(objdir)$(dllprefix)DvUpnpOrgConnectionManager1.$(dllext) 
$(objdir)$(dllprefix)DvUpnpOrgConnectionManager1.$(dllext) : ZappUpnpDll $(objdir)DvUpnpOrgConnectionManager1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvUpnpOrgConnectionManager1.$(dllext) $(objdir)DvUpnpOrgConnectionManager1.$(objext)
DvAvOpenhomeOrgProduct1Dll: $(objdir)$(dllprefix)DvAvOpenhomeOrgProduct1.$(dllext) 
$(objdir)$(dllprefix)DvAvOpenhomeOrgProduct1.$(dllext) : ZappUpnpDll $(objdir)DvAvOpenhomeOrgProduct1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvAvOpenhomeOrgProduct1.$(dllext) $(objdir)DvAvOpenhomeOrgProduct1.$(objext)
DvAvOpenhomeOrgSender1Dll: $(objdir)$(dllprefix)DvAvOpenhomeOrgSender1.$(dllext) 
$(objdir)$(dllprefix)DvAvOpenhomeOrgSender1.$(dllext) : ZappUpnpDll $(objdir)DvAvOpenhomeOrgSender1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvAvOpenhomeOrgSender1.$(dllext) $(objdir)DvAvOpenhomeOrgSender1.$(objext)
DvOpenhomeOrgTestBasic1Dll: $(objdir)$(dllprefix)DvOpenhomeOrgTestBasic1.$(dllext) 
$(objdir)$(dllprefix)DvOpenhomeOrgTestBasic1.$(dllext) : ZappUpnpDll $(objdir)DvOpenhomeOrgTestBasic1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvOpenhomeOrgTestBasic1.$(dllext) $(objdir)DvOpenhomeOrgTestBasic1.$(objext)
DvOpenhomeOrgSubscriptionLongPoll1Dll: $(objdir)$(dllprefix)DvOpenhomeOrgSubscriptionLongPoll1.$(dllext) 
$(objdir)$(dllprefix)DvOpenhomeOrgSubscriptionLongPoll1.$(dllext) : ZappUpnpDll $(objdir)DvOpenhomeOrgSubscriptionLongPoll1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvOpenhomeOrgSubscriptionLongPoll1.$(dllext) $(objdir)DvOpenhomeOrgSubscriptionLongPoll1.$(objext)


# Device assemblies for .NET:

DvDeviceDotNetAssemblies: $(device_dotnet_assemblies_with_path)

$(objdir)DvUpnpOrgConnectionManager1.net.dll: $(objdir)ohNet.net.dll $(deviceCs)DvUpnpOrgConnectionManager1.cs
	$(dotnetsdk) build $(proxyCs)CpUpnpOrgConnectionManager1.csproj --framework $(dotnetFramework) --output $(objdir)
$(objdir)DvAvOpenhomeOrgProduct1.net.dll: $(objdir)ohNet.net.dll $(deviceCs)DvAvOpenhomeOrgProduct1.cs
	$(dotnetsdk) build $(proxyCs)CpAvOpenhomeOrgProduct1.csproj --framework $(dotnetFramework) --output $(objdir)
$(objdir)DvAvOpenhomeOrgSender1.net.dll: $(objdir)ohNet.net.dll $(deviceCs)DvAvOpenhomeOrgSender1.cs
	$(dotnetsdk) build $(proxyCs)CpAvOpenhomeOrgSender1.csproj --framework $(dotnetFramework) --output $(objdir)
$(objdir)DvOpenhomeOrgTestBasic1.net.dll: $(objdir)ohNet.net.dll $(deviceCs)DvOpenhomeOrgTestBasic1.cs
	$(dotnetsdk) build $(proxyCs)CpOpenhomeOrgTestBasic1.csproj --framework $(dotnetFramework) --output $(objdir)
$(objdir)DvOpenhomeOrgSubscriptionLongPoll1.net.dll: $(objdir)ohNet.net.dll $(deviceCs)DvOpenhomeOrgSubscriptionLongPoll1.cs
	$(dotnetsdk) build $(proxyCs)CpOpenhomeOrgSubscriptionLongPoll1.csproj --framework $(dotnetFramework) --output $(objdir)

# Device classes for Java:

DvDeviceJavaClasses: $(device_java_classes_with_path)

$(objdir)org/openhome/net/device/providers/DvProviderUpnpOrgConnectionManager1.class : $(objdir)ohnet.jar $(deviceJava)DvProviderUpnpOrgConnectionManager1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(deviceJava)DvProviderUpnpOrgConnectionManager1.java
$(objdir)org/openhome/net/device/providers/DvProviderAvOpenhomeOrgProduct1.class : $(objdir)ohnet.jar $(deviceJava)DvProviderAvOpenhomeOrgProduct1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(deviceJava)DvProviderAvOpenhomeOrgProduct1.java
$(objdir)org/openhome/net/device/providers/DvProviderAvOpenhomeOrgSender1.class : $(objdir)ohnet.jar $(deviceJava)DvProviderAvOpenhomeOrgSender1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(deviceJava)DvProviderAvOpenhomeOrgSender1.java
$(objdir)org/openhome/net/device/providers/DvProviderOpenhomeOrgTestBasic1.class : $(objdir)ohnet.jar $(deviceJava)DvProviderOpenhomeOrgTestBasic1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(deviceJava)DvProviderOpenhomeOrgTestBasic1.java
$(objdir)org/openhome/net/device/providers/DvProviderOpenhomeOrgSubscriptionLongPoll1.class : $(objdir)ohnet.jar $(deviceJava)DvProviderOpenhomeOrgSubscriptionLongPoll1.java
	$(javac) -classpath $(objdir)ohnet.jar -d $(objdir) $(deviceJava)DvProviderOpenhomeOrgSubscriptionLongPoll1.java


