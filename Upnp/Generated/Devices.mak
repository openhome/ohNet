# Auto-generated file.  DO NOT EDIT DIRECTLY
# Update DvUpnpMakeDevices.tt and run
#    make generate-makefiles
# to apply any updates

objects_devices = \
                  $(objdir)DvUpnpOrgAVTransport1.$(objext) \
                  $(objdir)DvUpnpOrgAVTransport1Std.$(objext) \
                  $(objdir)DvUpnpOrgAVTransport1C.$(objext) \
                  $(objdir)DvUpnpOrgAVTransport2.$(objext) \
                  $(objdir)DvUpnpOrgAVTransport2Std.$(objext) \
                  $(objdir)DvUpnpOrgAVTransport2C.$(objext) \
                  $(objdir)DvUpnpOrgConnectionManager1.$(objext) \
                  $(objdir)DvUpnpOrgConnectionManager1Std.$(objext) \
                  $(objdir)DvUpnpOrgConnectionManager1C.$(objext) \
                  $(objdir)DvUpnpOrgConnectionManager2.$(objext) \
                  $(objdir)DvUpnpOrgConnectionManager2Std.$(objext) \
                  $(objdir)DvUpnpOrgConnectionManager2C.$(objext) \
                  $(objdir)DvUpnpOrgContentDirectory1.$(objext) \
                  $(objdir)DvUpnpOrgContentDirectory1Std.$(objext) \
                  $(objdir)DvUpnpOrgContentDirectory1C.$(objext) \
                  $(objdir)DvUpnpOrgContentDirectory2.$(objext) \
                  $(objdir)DvUpnpOrgContentDirectory2Std.$(objext) \
                  $(objdir)DvUpnpOrgContentDirectory2C.$(objext) \
                  $(objdir)DvUpnpOrgContentDirectory3.$(objext) \
                  $(objdir)DvUpnpOrgContentDirectory3Std.$(objext) \
                  $(objdir)DvUpnpOrgContentDirectory3C.$(objext) \
                  $(objdir)DvUpnpOrgRenderingControl1.$(objext) \
                  $(objdir)DvUpnpOrgRenderingControl1Std.$(objext) \
                  $(objdir)DvUpnpOrgRenderingControl1C.$(objext) \
                  $(objdir)DvUpnpOrgRenderingControl2.$(objext) \
                  $(objdir)DvUpnpOrgRenderingControl2Std.$(objext) \
                  $(objdir)DvUpnpOrgRenderingControl2C.$(objext) \
                  $(objdir)DvUpnpOrgScheduledRecording1.$(objext) \
                  $(objdir)DvUpnpOrgScheduledRecording1Std.$(objext) \
                  $(objdir)DvUpnpOrgScheduledRecording1C.$(objext) \
                  $(objdir)DvUpnpOrgScheduledRecording2.$(objext) \
                  $(objdir)DvUpnpOrgScheduledRecording2Std.$(objext) \
                  $(objdir)DvUpnpOrgScheduledRecording2C.$(objext) \
                  $(objdir)DvUpnpOrgSwitchPower1.$(objext) \
                  $(objdir)DvUpnpOrgSwitchPower1Std.$(objext) \
                  $(objdir)DvUpnpOrgSwitchPower1C.$(objext) \
                  $(objdir)DvUpnpOrgDimming1.$(objext) \
                  $(objdir)DvUpnpOrgDimming1Std.$(objext) \
                  $(objdir)DvUpnpOrgDimming1C.$(objext) \
                  $(objdir)DvAvOpenhomeOrgInfo1.$(objext) \
                  $(objdir)DvAvOpenhomeOrgInfo1Std.$(objext) \
                  $(objdir)DvAvOpenhomeOrgInfo1C.$(objext) \
                  $(objdir)DvAvOpenhomeOrgTime1.$(objext) \
                  $(objdir)DvAvOpenhomeOrgTime1Std.$(objext) \
                  $(objdir)DvAvOpenhomeOrgTime1C.$(objext) \
                  $(objdir)DvAvOpenhomeOrgPlaylist1.$(objext) \
                  $(objdir)DvAvOpenhomeOrgPlaylist1Std.$(objext) \
                  $(objdir)DvAvOpenhomeOrgPlaylist1C.$(objext) \
                  $(objdir)DvAvOpenhomeOrgVolume1.$(objext) \
                  $(objdir)DvAvOpenhomeOrgVolume1Std.$(objext) \
                  $(objdir)DvAvOpenhomeOrgVolume1C.$(objext) \
                  $(objdir)DvAvOpenhomeOrgProduct1.$(objext) \
                  $(objdir)DvAvOpenhomeOrgProduct1Std.$(objext) \
                  $(objdir)DvAvOpenhomeOrgProduct1C.$(objext) \
                  $(objdir)DvAvOpenhomeOrgRadio1.$(objext) \
                  $(objdir)DvAvOpenhomeOrgRadio1Std.$(objext) \
                  $(objdir)DvAvOpenhomeOrgRadio1C.$(objext) \
                  $(objdir)DvZappOrgTestBasic1.$(objext) \
                  $(objdir)DvZappOrgTestBasic1Std.$(objext) \
                  $(objdir)DvZappOrgTestBasic1C.$(objext) \
                  $(objdir)DvZappOrgTestLights1.$(objext) \
                  $(objdir)DvZappOrgTestLights1Std.$(objext) \
                  $(objdir)DvZappOrgTestLights1C.$(objext) \
                  $(objdir)DvZappOrgTestDimmableLight1.$(objext) \
                  $(objdir)DvZappOrgTestDimmableLight1Std.$(objext) \
                  $(objdir)DvZappOrgTestDimmableLight1C.$(objext) \
                  $(objdir)DvOpenhomeOrgTestColorLight1.$(objext) \
                  $(objdir)DvOpenhomeOrgTestColorLight1Std.$(objext) \
                  $(objdir)DvOpenhomeOrgTestColorLight1C.$(objext) \
                  $(objdir)DvOpenhomeOrgOhNet1.$(objext) \
                  $(objdir)DvOpenhomeOrgOhNet1Std.$(objext) \
                  $(objdir)DvOpenhomeOrgOhNet1C.$(objext) \

# Devices have well controlled dependencies so we can document a more limited set of headers
headers_device = $(inc_build)/Cpp/ZappTypes.h \
                 $(inc_build)/DviService.h \
                 $(inc_build)/Cpp/Functor.h \
                 $(inc_build)/Service.h \
                 $(inc_build)/FunctorDviInvocation.h

device_dotnet_assemblies = \
        DvUpnpOrgAVTransport1.net.dll \
        DvUpnpOrgAVTransport2.net.dll \
        DvUpnpOrgConnectionManager1.net.dll \
        DvUpnpOrgConnectionManager2.net.dll \
        DvUpnpOrgContentDirectory1.net.dll \
        DvUpnpOrgContentDirectory2.net.dll \
        DvUpnpOrgContentDirectory3.net.dll \
        DvUpnpOrgRenderingControl1.net.dll \
        DvUpnpOrgRenderingControl2.net.dll \
        DvUpnpOrgScheduledRecording1.net.dll \
        DvUpnpOrgScheduledRecording2.net.dll \
        DvUpnpOrgSwitchPower1.net.dll \
        DvUpnpOrgDimming1.net.dll \
        DvAvOpenhomeOrgInfo1.net.dll \
        DvAvOpenhomeOrgTime1.net.dll \
        DvAvOpenhomeOrgPlaylist1.net.dll \
        DvAvOpenhomeOrgVolume1.net.dll \
        DvAvOpenhomeOrgProduct1.net.dll \
        DvAvOpenhomeOrgRadio1.net.dll \
        DvZappOrgTestBasic1.net.dll \
        DvZappOrgTestLights1.net.dll \
        DvZappOrgTestDimmableLight1.net.dll \
        DvOpenhomeOrgTestColorLight1.net.dll \
        DvOpenhomeOrgOhNet1.net.dll \

device_dotnet_assemblies_with_path = \
        $(objdir)DvUpnpOrgAVTransport1.net.dll \
        $(objdir)DvUpnpOrgAVTransport2.net.dll \
        $(objdir)DvUpnpOrgConnectionManager1.net.dll \
        $(objdir)DvUpnpOrgConnectionManager2.net.dll \
        $(objdir)DvUpnpOrgContentDirectory1.net.dll \
        $(objdir)DvUpnpOrgContentDirectory2.net.dll \
        $(objdir)DvUpnpOrgContentDirectory3.net.dll \
        $(objdir)DvUpnpOrgRenderingControl1.net.dll \
        $(objdir)DvUpnpOrgRenderingControl2.net.dll \
        $(objdir)DvUpnpOrgScheduledRecording1.net.dll \
        $(objdir)DvUpnpOrgScheduledRecording2.net.dll \
        $(objdir)DvUpnpOrgSwitchPower1.net.dll \
        $(objdir)DvUpnpOrgDimming1.net.dll \
        $(objdir)DvAvOpenhomeOrgInfo1.net.dll \
        $(objdir)DvAvOpenhomeOrgTime1.net.dll \
        $(objdir)DvAvOpenhomeOrgPlaylist1.net.dll \
        $(objdir)DvAvOpenhomeOrgVolume1.net.dll \
        $(objdir)DvAvOpenhomeOrgProduct1.net.dll \
        $(objdir)DvAvOpenhomeOrgRadio1.net.dll \
        $(objdir)DvZappOrgTestBasic1.net.dll \
        $(objdir)DvZappOrgTestLights1.net.dll \
        $(objdir)DvZappOrgTestDimmableLight1.net.dll \
        $(objdir)DvOpenhomeOrgTestColorLight1.net.dll \
        $(objdir)DvOpenhomeOrgOhNet1.net.dll \

devices : upnp_core $(objects_devices)
	$(ar)ZappDevices.$(libext) $(objects_devices)
$(objdir)DvUpnpOrgAVTransport1.$(objext) : $(deviceCppCore)DvUpnpOrgAVTransport1.cpp $(headers_device) Device/Services/Cpp/Core/DvUpnpOrgAVTransport1.h
	$(compiler)DvUpnpOrgAVTransport1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvUpnpOrgAVTransport1.cpp
$(objdir)DvUpnpOrgAVTransport1Std.$(objext) : $(deviceCppStd)DvUpnpOrgAVTransport1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvUpnpOrgAVTransport1.h
	$(compiler)DvUpnpOrgAVTransport1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvUpnpOrgAVTransport1Std.cpp
$(objdir)DvUpnpOrgAVTransport1C.$(objext) : $(deviceC)DvUpnpOrgAVTransport1C.cpp $(headers_device) Device/Services/C/DvUpnpOrgAVTransport1.h
	$(compiler)DvUpnpOrgAVTransport1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvUpnpOrgAVTransport1C.cpp
$(objdir)DvUpnpOrgAVTransport2.$(objext) : $(deviceCppCore)DvUpnpOrgAVTransport2.cpp $(headers_device) Device/Services/Cpp/Core/DvUpnpOrgAVTransport2.h
	$(compiler)DvUpnpOrgAVTransport2.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvUpnpOrgAVTransport2.cpp
$(objdir)DvUpnpOrgAVTransport2Std.$(objext) : $(deviceCppStd)DvUpnpOrgAVTransport2Std.cpp $(headers_device) Device/Services/Cpp/Std/DvUpnpOrgAVTransport2.h
	$(compiler)DvUpnpOrgAVTransport2Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvUpnpOrgAVTransport2Std.cpp
$(objdir)DvUpnpOrgAVTransport2C.$(objext) : $(deviceC)DvUpnpOrgAVTransport2C.cpp $(headers_device) Device/Services/C/DvUpnpOrgAVTransport2.h
	$(compiler)DvUpnpOrgAVTransport2C.$(objext) -c $(cflags) $(includes) $(deviceC)DvUpnpOrgAVTransport2C.cpp
$(objdir)DvUpnpOrgConnectionManager1.$(objext) : $(deviceCppCore)DvUpnpOrgConnectionManager1.cpp $(headers_device) Device/Services/Cpp/Core/DvUpnpOrgConnectionManager1.h
	$(compiler)DvUpnpOrgConnectionManager1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvUpnpOrgConnectionManager1.cpp
$(objdir)DvUpnpOrgConnectionManager1Std.$(objext) : $(deviceCppStd)DvUpnpOrgConnectionManager1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvUpnpOrgConnectionManager1.h
	$(compiler)DvUpnpOrgConnectionManager1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvUpnpOrgConnectionManager1Std.cpp
$(objdir)DvUpnpOrgConnectionManager1C.$(objext) : $(deviceC)DvUpnpOrgConnectionManager1C.cpp $(headers_device) Device/Services/C/DvUpnpOrgConnectionManager1.h
	$(compiler)DvUpnpOrgConnectionManager1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvUpnpOrgConnectionManager1C.cpp
$(objdir)DvUpnpOrgConnectionManager2.$(objext) : $(deviceCppCore)DvUpnpOrgConnectionManager2.cpp $(headers_device) Device/Services/Cpp/Core/DvUpnpOrgConnectionManager2.h
	$(compiler)DvUpnpOrgConnectionManager2.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvUpnpOrgConnectionManager2.cpp
$(objdir)DvUpnpOrgConnectionManager2Std.$(objext) : $(deviceCppStd)DvUpnpOrgConnectionManager2Std.cpp $(headers_device) Device/Services/Cpp/Std/DvUpnpOrgConnectionManager2.h
	$(compiler)DvUpnpOrgConnectionManager2Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvUpnpOrgConnectionManager2Std.cpp
$(objdir)DvUpnpOrgConnectionManager2C.$(objext) : $(deviceC)DvUpnpOrgConnectionManager2C.cpp $(headers_device) Device/Services/C/DvUpnpOrgConnectionManager2.h
	$(compiler)DvUpnpOrgConnectionManager2C.$(objext) -c $(cflags) $(includes) $(deviceC)DvUpnpOrgConnectionManager2C.cpp
$(objdir)DvUpnpOrgContentDirectory1.$(objext) : $(deviceCppCore)DvUpnpOrgContentDirectory1.cpp $(headers_device) Device/Services/Cpp/Core/DvUpnpOrgContentDirectory1.h
	$(compiler)DvUpnpOrgContentDirectory1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvUpnpOrgContentDirectory1.cpp
$(objdir)DvUpnpOrgContentDirectory1Std.$(objext) : $(deviceCppStd)DvUpnpOrgContentDirectory1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvUpnpOrgContentDirectory1.h
	$(compiler)DvUpnpOrgContentDirectory1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvUpnpOrgContentDirectory1Std.cpp
$(objdir)DvUpnpOrgContentDirectory1C.$(objext) : $(deviceC)DvUpnpOrgContentDirectory1C.cpp $(headers_device) Device/Services/C/DvUpnpOrgContentDirectory1.h
	$(compiler)DvUpnpOrgContentDirectory1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvUpnpOrgContentDirectory1C.cpp
$(objdir)DvUpnpOrgContentDirectory2.$(objext) : $(deviceCppCore)DvUpnpOrgContentDirectory2.cpp $(headers_device) Device/Services/Cpp/Core/DvUpnpOrgContentDirectory2.h
	$(compiler)DvUpnpOrgContentDirectory2.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvUpnpOrgContentDirectory2.cpp
$(objdir)DvUpnpOrgContentDirectory2Std.$(objext) : $(deviceCppStd)DvUpnpOrgContentDirectory2Std.cpp $(headers_device) Device/Services/Cpp/Std/DvUpnpOrgContentDirectory2.h
	$(compiler)DvUpnpOrgContentDirectory2Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvUpnpOrgContentDirectory2Std.cpp
$(objdir)DvUpnpOrgContentDirectory2C.$(objext) : $(deviceC)DvUpnpOrgContentDirectory2C.cpp $(headers_device) Device/Services/C/DvUpnpOrgContentDirectory2.h
	$(compiler)DvUpnpOrgContentDirectory2C.$(objext) -c $(cflags) $(includes) $(deviceC)DvUpnpOrgContentDirectory2C.cpp
$(objdir)DvUpnpOrgContentDirectory3.$(objext) : $(deviceCppCore)DvUpnpOrgContentDirectory3.cpp $(headers_device) Device/Services/Cpp/Core/DvUpnpOrgContentDirectory3.h
	$(compiler)DvUpnpOrgContentDirectory3.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvUpnpOrgContentDirectory3.cpp
$(objdir)DvUpnpOrgContentDirectory3Std.$(objext) : $(deviceCppStd)DvUpnpOrgContentDirectory3Std.cpp $(headers_device) Device/Services/Cpp/Std/DvUpnpOrgContentDirectory3.h
	$(compiler)DvUpnpOrgContentDirectory3Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvUpnpOrgContentDirectory3Std.cpp
$(objdir)DvUpnpOrgContentDirectory3C.$(objext) : $(deviceC)DvUpnpOrgContentDirectory3C.cpp $(headers_device) Device/Services/C/DvUpnpOrgContentDirectory3.h
	$(compiler)DvUpnpOrgContentDirectory3C.$(objext) -c $(cflags) $(includes) $(deviceC)DvUpnpOrgContentDirectory3C.cpp
$(objdir)DvUpnpOrgRenderingControl1.$(objext) : $(deviceCppCore)DvUpnpOrgRenderingControl1.cpp $(headers_device) Device/Services/Cpp/Core/DvUpnpOrgRenderingControl1.h
	$(compiler)DvUpnpOrgRenderingControl1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvUpnpOrgRenderingControl1.cpp
$(objdir)DvUpnpOrgRenderingControl1Std.$(objext) : $(deviceCppStd)DvUpnpOrgRenderingControl1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvUpnpOrgRenderingControl1.h
	$(compiler)DvUpnpOrgRenderingControl1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvUpnpOrgRenderingControl1Std.cpp
$(objdir)DvUpnpOrgRenderingControl1C.$(objext) : $(deviceC)DvUpnpOrgRenderingControl1C.cpp $(headers_device) Device/Services/C/DvUpnpOrgRenderingControl1.h
	$(compiler)DvUpnpOrgRenderingControl1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvUpnpOrgRenderingControl1C.cpp
$(objdir)DvUpnpOrgRenderingControl2.$(objext) : $(deviceCppCore)DvUpnpOrgRenderingControl2.cpp $(headers_device) Device/Services/Cpp/Core/DvUpnpOrgRenderingControl2.h
	$(compiler)DvUpnpOrgRenderingControl2.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvUpnpOrgRenderingControl2.cpp
$(objdir)DvUpnpOrgRenderingControl2Std.$(objext) : $(deviceCppStd)DvUpnpOrgRenderingControl2Std.cpp $(headers_device) Device/Services/Cpp/Std/DvUpnpOrgRenderingControl2.h
	$(compiler)DvUpnpOrgRenderingControl2Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvUpnpOrgRenderingControl2Std.cpp
$(objdir)DvUpnpOrgRenderingControl2C.$(objext) : $(deviceC)DvUpnpOrgRenderingControl2C.cpp $(headers_device) Device/Services/C/DvUpnpOrgRenderingControl2.h
	$(compiler)DvUpnpOrgRenderingControl2C.$(objext) -c $(cflags) $(includes) $(deviceC)DvUpnpOrgRenderingControl2C.cpp
$(objdir)DvUpnpOrgScheduledRecording1.$(objext) : $(deviceCppCore)DvUpnpOrgScheduledRecording1.cpp $(headers_device) Device/Services/Cpp/Core/DvUpnpOrgScheduledRecording1.h
	$(compiler)DvUpnpOrgScheduledRecording1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvUpnpOrgScheduledRecording1.cpp
$(objdir)DvUpnpOrgScheduledRecording1Std.$(objext) : $(deviceCppStd)DvUpnpOrgScheduledRecording1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvUpnpOrgScheduledRecording1.h
	$(compiler)DvUpnpOrgScheduledRecording1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvUpnpOrgScheduledRecording1Std.cpp
$(objdir)DvUpnpOrgScheduledRecording1C.$(objext) : $(deviceC)DvUpnpOrgScheduledRecording1C.cpp $(headers_device) Device/Services/C/DvUpnpOrgScheduledRecording1.h
	$(compiler)DvUpnpOrgScheduledRecording1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvUpnpOrgScheduledRecording1C.cpp
$(objdir)DvUpnpOrgScheduledRecording2.$(objext) : $(deviceCppCore)DvUpnpOrgScheduledRecording2.cpp $(headers_device) Device/Services/Cpp/Core/DvUpnpOrgScheduledRecording2.h
	$(compiler)DvUpnpOrgScheduledRecording2.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvUpnpOrgScheduledRecording2.cpp
$(objdir)DvUpnpOrgScheduledRecording2Std.$(objext) : $(deviceCppStd)DvUpnpOrgScheduledRecording2Std.cpp $(headers_device) Device/Services/Cpp/Std/DvUpnpOrgScheduledRecording2.h
	$(compiler)DvUpnpOrgScheduledRecording2Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvUpnpOrgScheduledRecording2Std.cpp
$(objdir)DvUpnpOrgScheduledRecording2C.$(objext) : $(deviceC)DvUpnpOrgScheduledRecording2C.cpp $(headers_device) Device/Services/C/DvUpnpOrgScheduledRecording2.h
	$(compiler)DvUpnpOrgScheduledRecording2C.$(objext) -c $(cflags) $(includes) $(deviceC)DvUpnpOrgScheduledRecording2C.cpp
$(objdir)DvUpnpOrgSwitchPower1.$(objext) : $(deviceCppCore)DvUpnpOrgSwitchPower1.cpp $(headers_device) Device/Services/Cpp/Core/DvUpnpOrgSwitchPower1.h
	$(compiler)DvUpnpOrgSwitchPower1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvUpnpOrgSwitchPower1.cpp
$(objdir)DvUpnpOrgSwitchPower1Std.$(objext) : $(deviceCppStd)DvUpnpOrgSwitchPower1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvUpnpOrgSwitchPower1.h
	$(compiler)DvUpnpOrgSwitchPower1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvUpnpOrgSwitchPower1Std.cpp
$(objdir)DvUpnpOrgSwitchPower1C.$(objext) : $(deviceC)DvUpnpOrgSwitchPower1C.cpp $(headers_device) Device/Services/C/DvUpnpOrgSwitchPower1.h
	$(compiler)DvUpnpOrgSwitchPower1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvUpnpOrgSwitchPower1C.cpp
$(objdir)DvUpnpOrgDimming1.$(objext) : $(deviceCppCore)DvUpnpOrgDimming1.cpp $(headers_device) Device/Services/Cpp/Core/DvUpnpOrgDimming1.h
	$(compiler)DvUpnpOrgDimming1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvUpnpOrgDimming1.cpp
$(objdir)DvUpnpOrgDimming1Std.$(objext) : $(deviceCppStd)DvUpnpOrgDimming1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvUpnpOrgDimming1.h
	$(compiler)DvUpnpOrgDimming1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvUpnpOrgDimming1Std.cpp
$(objdir)DvUpnpOrgDimming1C.$(objext) : $(deviceC)DvUpnpOrgDimming1C.cpp $(headers_device) Device/Services/C/DvUpnpOrgDimming1.h
	$(compiler)DvUpnpOrgDimming1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvUpnpOrgDimming1C.cpp
$(objdir)DvAvOpenhomeOrgInfo1.$(objext) : $(deviceCppCore)DvAvOpenhomeOrgInfo1.cpp $(headers_device) Device/Services/Cpp/Core/DvAvOpenhomeOrgInfo1.h
	$(compiler)DvAvOpenhomeOrgInfo1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvAvOpenhomeOrgInfo1.cpp
$(objdir)DvAvOpenhomeOrgInfo1Std.$(objext) : $(deviceCppStd)DvAvOpenhomeOrgInfo1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvAvOpenhomeOrgInfo1.h
	$(compiler)DvAvOpenhomeOrgInfo1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvAvOpenhomeOrgInfo1Std.cpp
$(objdir)DvAvOpenhomeOrgInfo1C.$(objext) : $(deviceC)DvAvOpenhomeOrgInfo1C.cpp $(headers_device) Device/Services/C/DvAvOpenhomeOrgInfo1.h
	$(compiler)DvAvOpenhomeOrgInfo1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvAvOpenhomeOrgInfo1C.cpp
$(objdir)DvAvOpenhomeOrgTime1.$(objext) : $(deviceCppCore)DvAvOpenhomeOrgTime1.cpp $(headers_device) Device/Services/Cpp/Core/DvAvOpenhomeOrgTime1.h
	$(compiler)DvAvOpenhomeOrgTime1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvAvOpenhomeOrgTime1.cpp
$(objdir)DvAvOpenhomeOrgTime1Std.$(objext) : $(deviceCppStd)DvAvOpenhomeOrgTime1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvAvOpenhomeOrgTime1.h
	$(compiler)DvAvOpenhomeOrgTime1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvAvOpenhomeOrgTime1Std.cpp
$(objdir)DvAvOpenhomeOrgTime1C.$(objext) : $(deviceC)DvAvOpenhomeOrgTime1C.cpp $(headers_device) Device/Services/C/DvAvOpenhomeOrgTime1.h
	$(compiler)DvAvOpenhomeOrgTime1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvAvOpenhomeOrgTime1C.cpp
$(objdir)DvAvOpenhomeOrgPlaylist1.$(objext) : $(deviceCppCore)DvAvOpenhomeOrgPlaylist1.cpp $(headers_device) Device/Services/Cpp/Core/DvAvOpenhomeOrgPlaylist1.h
	$(compiler)DvAvOpenhomeOrgPlaylist1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvAvOpenhomeOrgPlaylist1.cpp
$(objdir)DvAvOpenhomeOrgPlaylist1Std.$(objext) : $(deviceCppStd)DvAvOpenhomeOrgPlaylist1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvAvOpenhomeOrgPlaylist1.h
	$(compiler)DvAvOpenhomeOrgPlaylist1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvAvOpenhomeOrgPlaylist1Std.cpp
$(objdir)DvAvOpenhomeOrgPlaylist1C.$(objext) : $(deviceC)DvAvOpenhomeOrgPlaylist1C.cpp $(headers_device) Device/Services/C/DvAvOpenhomeOrgPlaylist1.h
	$(compiler)DvAvOpenhomeOrgPlaylist1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvAvOpenhomeOrgPlaylist1C.cpp
$(objdir)DvAvOpenhomeOrgVolume1.$(objext) : $(deviceCppCore)DvAvOpenhomeOrgVolume1.cpp $(headers_device) Device/Services/Cpp/Core/DvAvOpenhomeOrgVolume1.h
	$(compiler)DvAvOpenhomeOrgVolume1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvAvOpenhomeOrgVolume1.cpp
$(objdir)DvAvOpenhomeOrgVolume1Std.$(objext) : $(deviceCppStd)DvAvOpenhomeOrgVolume1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvAvOpenhomeOrgVolume1.h
	$(compiler)DvAvOpenhomeOrgVolume1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvAvOpenhomeOrgVolume1Std.cpp
$(objdir)DvAvOpenhomeOrgVolume1C.$(objext) : $(deviceC)DvAvOpenhomeOrgVolume1C.cpp $(headers_device) Device/Services/C/DvAvOpenhomeOrgVolume1.h
	$(compiler)DvAvOpenhomeOrgVolume1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvAvOpenhomeOrgVolume1C.cpp
$(objdir)DvAvOpenhomeOrgProduct1.$(objext) : $(deviceCppCore)DvAvOpenhomeOrgProduct1.cpp $(headers_device) Device/Services/Cpp/Core/DvAvOpenhomeOrgProduct1.h
	$(compiler)DvAvOpenhomeOrgProduct1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvAvOpenhomeOrgProduct1.cpp
$(objdir)DvAvOpenhomeOrgProduct1Std.$(objext) : $(deviceCppStd)DvAvOpenhomeOrgProduct1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvAvOpenhomeOrgProduct1.h
	$(compiler)DvAvOpenhomeOrgProduct1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvAvOpenhomeOrgProduct1Std.cpp
$(objdir)DvAvOpenhomeOrgProduct1C.$(objext) : $(deviceC)DvAvOpenhomeOrgProduct1C.cpp $(headers_device) Device/Services/C/DvAvOpenhomeOrgProduct1.h
	$(compiler)DvAvOpenhomeOrgProduct1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvAvOpenhomeOrgProduct1C.cpp
$(objdir)DvAvOpenhomeOrgRadio1.$(objext) : $(deviceCppCore)DvAvOpenhomeOrgRadio1.cpp $(headers_device) Device/Services/Cpp/Core/DvAvOpenhomeOrgRadio1.h
	$(compiler)DvAvOpenhomeOrgRadio1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvAvOpenhomeOrgRadio1.cpp
$(objdir)DvAvOpenhomeOrgRadio1Std.$(objext) : $(deviceCppStd)DvAvOpenhomeOrgRadio1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvAvOpenhomeOrgRadio1.h
	$(compiler)DvAvOpenhomeOrgRadio1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvAvOpenhomeOrgRadio1Std.cpp
$(objdir)DvAvOpenhomeOrgRadio1C.$(objext) : $(deviceC)DvAvOpenhomeOrgRadio1C.cpp $(headers_device) Device/Services/C/DvAvOpenhomeOrgRadio1.h
	$(compiler)DvAvOpenhomeOrgRadio1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvAvOpenhomeOrgRadio1C.cpp
$(objdir)DvZappOrgTestBasic1.$(objext) : $(deviceCppCore)DvZappOrgTestBasic1.cpp $(headers_device) Device/Services/Cpp/Core/DvZappOrgTestBasic1.h
	$(compiler)DvZappOrgTestBasic1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvZappOrgTestBasic1.cpp
$(objdir)DvZappOrgTestBasic1Std.$(objext) : $(deviceCppStd)DvZappOrgTestBasic1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvZappOrgTestBasic1.h
	$(compiler)DvZappOrgTestBasic1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvZappOrgTestBasic1Std.cpp
$(objdir)DvZappOrgTestBasic1C.$(objext) : $(deviceC)DvZappOrgTestBasic1C.cpp $(headers_device) Device/Services/C/DvZappOrgTestBasic1.h
	$(compiler)DvZappOrgTestBasic1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvZappOrgTestBasic1C.cpp
$(objdir)DvZappOrgTestLights1.$(objext) : $(deviceCppCore)DvZappOrgTestLights1.cpp $(headers_device) Device/Services/Cpp/Core/DvZappOrgTestLights1.h
	$(compiler)DvZappOrgTestLights1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvZappOrgTestLights1.cpp
$(objdir)DvZappOrgTestLights1Std.$(objext) : $(deviceCppStd)DvZappOrgTestLights1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvZappOrgTestLights1.h
	$(compiler)DvZappOrgTestLights1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvZappOrgTestLights1Std.cpp
$(objdir)DvZappOrgTestLights1C.$(objext) : $(deviceC)DvZappOrgTestLights1C.cpp $(headers_device) Device/Services/C/DvZappOrgTestLights1.h
	$(compiler)DvZappOrgTestLights1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvZappOrgTestLights1C.cpp
$(objdir)DvZappOrgTestDimmableLight1.$(objext) : $(deviceCppCore)DvZappOrgTestDimmableLight1.cpp $(headers_device) Device/Services/Cpp/Core/DvZappOrgTestDimmableLight1.h
	$(compiler)DvZappOrgTestDimmableLight1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvZappOrgTestDimmableLight1.cpp
$(objdir)DvZappOrgTestDimmableLight1Std.$(objext) : $(deviceCppStd)DvZappOrgTestDimmableLight1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvZappOrgTestDimmableLight1.h
	$(compiler)DvZappOrgTestDimmableLight1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvZappOrgTestDimmableLight1Std.cpp
$(objdir)DvZappOrgTestDimmableLight1C.$(objext) : $(deviceC)DvZappOrgTestDimmableLight1C.cpp $(headers_device) Device/Services/C/DvZappOrgTestDimmableLight1.h
	$(compiler)DvZappOrgTestDimmableLight1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvZappOrgTestDimmableLight1C.cpp
$(objdir)DvOpenhomeOrgTestColorLight1.$(objext) : $(deviceCppCore)DvOpenhomeOrgTestColorLight1.cpp $(headers_device) Device/Services/Cpp/Core/DvOpenhomeOrgTestColorLight1.h
	$(compiler)DvOpenhomeOrgTestColorLight1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvOpenhomeOrgTestColorLight1.cpp
$(objdir)DvOpenhomeOrgTestColorLight1Std.$(objext) : $(deviceCppStd)DvOpenhomeOrgTestColorLight1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvOpenhomeOrgTestColorLight1.h
	$(compiler)DvOpenhomeOrgTestColorLight1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvOpenhomeOrgTestColorLight1Std.cpp
$(objdir)DvOpenhomeOrgTestColorLight1C.$(objext) : $(deviceC)DvOpenhomeOrgTestColorLight1C.cpp $(headers_device) Device/Services/C/DvOpenhomeOrgTestColorLight1.h
	$(compiler)DvOpenhomeOrgTestColorLight1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvOpenhomeOrgTestColorLight1C.cpp
$(objdir)DvOpenhomeOrgOhNet1.$(objext) : $(deviceCppCore)DvOpenhomeOrgOhNet1.cpp $(headers_device) Device/Services/Cpp/Core/DvOpenhomeOrgOhNet1.h
	$(compiler)DvOpenhomeOrgOhNet1.$(objext) -c $(cflags) $(includes) $(deviceCppCore)DvOpenhomeOrgOhNet1.cpp
$(objdir)DvOpenhomeOrgOhNet1Std.$(objext) : $(deviceCppStd)DvOpenhomeOrgOhNet1Std.cpp $(headers_device) Device/Services/Cpp/Std/DvOpenhomeOrgOhNet1.h
	$(compiler)DvOpenhomeOrgOhNet1Std.$(objext) -c $(cflags) $(includes) $(deviceCppStd)DvOpenhomeOrgOhNet1Std.cpp
$(objdir)DvOpenhomeOrgOhNet1C.$(objext) : $(deviceC)DvOpenhomeOrgOhNet1C.cpp $(headers_device) Device/Services/C/DvOpenhomeOrgOhNet1.h
	$(compiler)DvOpenhomeOrgOhNet1C.$(objext) -c $(cflags) $(includes) $(deviceC)DvOpenhomeOrgOhNet1C.cpp

device_dlls = \
             DvUpnpOrgAVTransport1Dll \
             DvUpnpOrgAVTransport2Dll \
             DvUpnpOrgConnectionManager1Dll \
             DvUpnpOrgConnectionManager2Dll \
             DvUpnpOrgContentDirectory1Dll \
             DvUpnpOrgContentDirectory2Dll \
             DvUpnpOrgContentDirectory3Dll \
             DvUpnpOrgRenderingControl1Dll \
             DvUpnpOrgRenderingControl2Dll \
             DvUpnpOrgScheduledRecording1Dll \
             DvUpnpOrgScheduledRecording2Dll \
             DvUpnpOrgSwitchPower1Dll \
             DvUpnpOrgDimming1Dll \
             DvAvOpenhomeOrgInfo1Dll \
             DvAvOpenhomeOrgTime1Dll \
             DvAvOpenhomeOrgPlaylist1Dll \
             DvAvOpenhomeOrgVolume1Dll \
             DvAvOpenhomeOrgProduct1Dll \
             DvAvOpenhomeOrgRadio1Dll \
             DvZappOrgTestBasic1Dll \
             DvZappOrgTestLights1Dll \
             DvZappOrgTestDimmableLight1Dll \
             DvOpenhomeOrgTestColorLight1Dll \
             DvOpenhomeOrgOhNet1Dll \

DvDeviceDlls: $(device_dlls)
DvUpnpOrgAVTransport1Dll: $(objdir)$(dllprefix)DvUpnpOrgAVTransport1.$(dllext) 
$(objdir)$(dllprefix)DvUpnpOrgAVTransport1.$(dllext) : ZappUpnpDll $(objdir)DvUpnpOrgAVTransport1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvUpnpOrgAVTransport1.$(dllext) $(objdir)DvUpnpOrgAVTransport1.$(objext)
DvUpnpOrgAVTransport2Dll: $(objdir)$(dllprefix)DvUpnpOrgAVTransport2.$(dllext) 
$(objdir)$(dllprefix)DvUpnpOrgAVTransport2.$(dllext) : ZappUpnpDll $(objdir)DvUpnpOrgAVTransport2.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvUpnpOrgAVTransport2.$(dllext) $(objdir)DvUpnpOrgAVTransport2.$(objext)
DvUpnpOrgConnectionManager1Dll: $(objdir)$(dllprefix)DvUpnpOrgConnectionManager1.$(dllext) 
$(objdir)$(dllprefix)DvUpnpOrgConnectionManager1.$(dllext) : ZappUpnpDll $(objdir)DvUpnpOrgConnectionManager1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvUpnpOrgConnectionManager1.$(dllext) $(objdir)DvUpnpOrgConnectionManager1.$(objext)
DvUpnpOrgConnectionManager2Dll: $(objdir)$(dllprefix)DvUpnpOrgConnectionManager2.$(dllext) 
$(objdir)$(dllprefix)DvUpnpOrgConnectionManager2.$(dllext) : ZappUpnpDll $(objdir)DvUpnpOrgConnectionManager2.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvUpnpOrgConnectionManager2.$(dllext) $(objdir)DvUpnpOrgConnectionManager2.$(objext)
DvUpnpOrgContentDirectory1Dll: $(objdir)$(dllprefix)DvUpnpOrgContentDirectory1.$(dllext) 
$(objdir)$(dllprefix)DvUpnpOrgContentDirectory1.$(dllext) : ZappUpnpDll $(objdir)DvUpnpOrgContentDirectory1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvUpnpOrgContentDirectory1.$(dllext) $(objdir)DvUpnpOrgContentDirectory1.$(objext)
DvUpnpOrgContentDirectory2Dll: $(objdir)$(dllprefix)DvUpnpOrgContentDirectory2.$(dllext) 
$(objdir)$(dllprefix)DvUpnpOrgContentDirectory2.$(dllext) : ZappUpnpDll $(objdir)DvUpnpOrgContentDirectory2.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvUpnpOrgContentDirectory2.$(dllext) $(objdir)DvUpnpOrgContentDirectory2.$(objext)
DvUpnpOrgContentDirectory3Dll: $(objdir)$(dllprefix)DvUpnpOrgContentDirectory3.$(dllext) 
$(objdir)$(dllprefix)DvUpnpOrgContentDirectory3.$(dllext) : ZappUpnpDll $(objdir)DvUpnpOrgContentDirectory3.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvUpnpOrgContentDirectory3.$(dllext) $(objdir)DvUpnpOrgContentDirectory3.$(objext)
DvUpnpOrgRenderingControl1Dll: $(objdir)$(dllprefix)DvUpnpOrgRenderingControl1.$(dllext) 
$(objdir)$(dllprefix)DvUpnpOrgRenderingControl1.$(dllext) : ZappUpnpDll $(objdir)DvUpnpOrgRenderingControl1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvUpnpOrgRenderingControl1.$(dllext) $(objdir)DvUpnpOrgRenderingControl1.$(objext)
DvUpnpOrgRenderingControl2Dll: $(objdir)$(dllprefix)DvUpnpOrgRenderingControl2.$(dllext) 
$(objdir)$(dllprefix)DvUpnpOrgRenderingControl2.$(dllext) : ZappUpnpDll $(objdir)DvUpnpOrgRenderingControl2.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvUpnpOrgRenderingControl2.$(dllext) $(objdir)DvUpnpOrgRenderingControl2.$(objext)
DvUpnpOrgScheduledRecording1Dll: $(objdir)$(dllprefix)DvUpnpOrgScheduledRecording1.$(dllext) 
$(objdir)$(dllprefix)DvUpnpOrgScheduledRecording1.$(dllext) : ZappUpnpDll $(objdir)DvUpnpOrgScheduledRecording1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvUpnpOrgScheduledRecording1.$(dllext) $(objdir)DvUpnpOrgScheduledRecording1.$(objext)
DvUpnpOrgScheduledRecording2Dll: $(objdir)$(dllprefix)DvUpnpOrgScheduledRecording2.$(dllext) 
$(objdir)$(dllprefix)DvUpnpOrgScheduledRecording2.$(dllext) : ZappUpnpDll $(objdir)DvUpnpOrgScheduledRecording2.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvUpnpOrgScheduledRecording2.$(dllext) $(objdir)DvUpnpOrgScheduledRecording2.$(objext)
DvUpnpOrgSwitchPower1Dll: $(objdir)$(dllprefix)DvUpnpOrgSwitchPower1.$(dllext) 
$(objdir)$(dllprefix)DvUpnpOrgSwitchPower1.$(dllext) : ZappUpnpDll $(objdir)DvUpnpOrgSwitchPower1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvUpnpOrgSwitchPower1.$(dllext) $(objdir)DvUpnpOrgSwitchPower1.$(objext)
DvUpnpOrgDimming1Dll: $(objdir)$(dllprefix)DvUpnpOrgDimming1.$(dllext) 
$(objdir)$(dllprefix)DvUpnpOrgDimming1.$(dllext) : ZappUpnpDll $(objdir)DvUpnpOrgDimming1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvUpnpOrgDimming1.$(dllext) $(objdir)DvUpnpOrgDimming1.$(objext)
DvAvOpenhomeOrgInfo1Dll: $(objdir)$(dllprefix)DvAvOpenhomeOrgInfo1.$(dllext) 
$(objdir)$(dllprefix)DvAvOpenhomeOrgInfo1.$(dllext) : ZappUpnpDll $(objdir)DvAvOpenhomeOrgInfo1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvAvOpenhomeOrgInfo1.$(dllext) $(objdir)DvAvOpenhomeOrgInfo1.$(objext)
DvAvOpenhomeOrgTime1Dll: $(objdir)$(dllprefix)DvAvOpenhomeOrgTime1.$(dllext) 
$(objdir)$(dllprefix)DvAvOpenhomeOrgTime1.$(dllext) : ZappUpnpDll $(objdir)DvAvOpenhomeOrgTime1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvAvOpenhomeOrgTime1.$(dllext) $(objdir)DvAvOpenhomeOrgTime1.$(objext)
DvAvOpenhomeOrgPlaylist1Dll: $(objdir)$(dllprefix)DvAvOpenhomeOrgPlaylist1.$(dllext) 
$(objdir)$(dllprefix)DvAvOpenhomeOrgPlaylist1.$(dllext) : ZappUpnpDll $(objdir)DvAvOpenhomeOrgPlaylist1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvAvOpenhomeOrgPlaylist1.$(dllext) $(objdir)DvAvOpenhomeOrgPlaylist1.$(objext)
DvAvOpenhomeOrgVolume1Dll: $(objdir)$(dllprefix)DvAvOpenhomeOrgVolume1.$(dllext) 
$(objdir)$(dllprefix)DvAvOpenhomeOrgVolume1.$(dllext) : ZappUpnpDll $(objdir)DvAvOpenhomeOrgVolume1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvAvOpenhomeOrgVolume1.$(dllext) $(objdir)DvAvOpenhomeOrgVolume1.$(objext)
DvAvOpenhomeOrgProduct1Dll: $(objdir)$(dllprefix)DvAvOpenhomeOrgProduct1.$(dllext) 
$(objdir)$(dllprefix)DvAvOpenhomeOrgProduct1.$(dllext) : ZappUpnpDll $(objdir)DvAvOpenhomeOrgProduct1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvAvOpenhomeOrgProduct1.$(dllext) $(objdir)DvAvOpenhomeOrgProduct1.$(objext)
DvAvOpenhomeOrgRadio1Dll: $(objdir)$(dllprefix)DvAvOpenhomeOrgRadio1.$(dllext) 
$(objdir)$(dllprefix)DvAvOpenhomeOrgRadio1.$(dllext) : ZappUpnpDll $(objdir)DvAvOpenhomeOrgRadio1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvAvOpenhomeOrgRadio1.$(dllext) $(objdir)DvAvOpenhomeOrgRadio1.$(objext)
DvZappOrgTestBasic1Dll: $(objdir)$(dllprefix)DvZappOrgTestBasic1.$(dllext) 
$(objdir)$(dllprefix)DvZappOrgTestBasic1.$(dllext) : ZappUpnpDll $(objdir)DvZappOrgTestBasic1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvZappOrgTestBasic1.$(dllext) $(objdir)DvZappOrgTestBasic1.$(objext)
DvZappOrgTestLights1Dll: $(objdir)$(dllprefix)DvZappOrgTestLights1.$(dllext) 
$(objdir)$(dllprefix)DvZappOrgTestLights1.$(dllext) : ZappUpnpDll $(objdir)DvZappOrgTestLights1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvZappOrgTestLights1.$(dllext) $(objdir)DvZappOrgTestLights1.$(objext)
DvZappOrgTestDimmableLight1Dll: $(objdir)$(dllprefix)DvZappOrgTestDimmableLight1.$(dllext) 
$(objdir)$(dllprefix)DvZappOrgTestDimmableLight1.$(dllext) : ZappUpnpDll $(objdir)DvZappOrgTestDimmableLight1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvZappOrgTestDimmableLight1.$(dllext) $(objdir)DvZappOrgTestDimmableLight1.$(objext)
DvOpenhomeOrgTestColorLight1Dll: $(objdir)$(dllprefix)DvOpenhomeOrgTestColorLight1.$(dllext) 
$(objdir)$(dllprefix)DvOpenhomeOrgTestColorLight1.$(dllext) : ZappUpnpDll $(objdir)DvOpenhomeOrgTestColorLight1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvOpenhomeOrgTestColorLight1.$(dllext) $(objdir)DvOpenhomeOrgTestColorLight1.$(objext)
DvOpenhomeOrgOhNet1Dll: $(objdir)$(dllprefix)DvOpenhomeOrgOhNet1.$(dllext) 
$(objdir)$(dllprefix)DvOpenhomeOrgOhNet1.$(dllext) : ZappUpnpDll $(objdir)DvOpenhomeOrgOhNet1.$(objext)
	$(link_dll_service) $(linkoutput)$(objdir)$(dllprefix)DvOpenhomeOrgOhNet1.$(dllext) $(objdir)DvOpenhomeOrgOhNet1.$(objext)


# Device assemblies for .NET:

DvDeviceDotNetAssemblies: $(device_dotnet_assemblies_with_path)

$(objdir)DvUpnpOrgAVTransport1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvUpnpOrgAVTransport1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvUpnpOrgAVTransport1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvUpnpOrgAVTransport1.cs
$(objdir)DvUpnpOrgAVTransport2.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvUpnpOrgAVTransport2.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvUpnpOrgAVTransport2.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvUpnpOrgAVTransport2.cs
$(objdir)DvUpnpOrgConnectionManager1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvUpnpOrgConnectionManager1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvUpnpOrgConnectionManager1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvUpnpOrgConnectionManager1.cs
$(objdir)DvUpnpOrgConnectionManager2.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvUpnpOrgConnectionManager2.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvUpnpOrgConnectionManager2.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvUpnpOrgConnectionManager2.cs
$(objdir)DvUpnpOrgContentDirectory1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvUpnpOrgContentDirectory1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvUpnpOrgContentDirectory1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvUpnpOrgContentDirectory1.cs
$(objdir)DvUpnpOrgContentDirectory2.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvUpnpOrgContentDirectory2.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvUpnpOrgContentDirectory2.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvUpnpOrgContentDirectory2.cs
$(objdir)DvUpnpOrgContentDirectory3.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvUpnpOrgContentDirectory3.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvUpnpOrgContentDirectory3.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvUpnpOrgContentDirectory3.cs
$(objdir)DvUpnpOrgRenderingControl1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvUpnpOrgRenderingControl1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvUpnpOrgRenderingControl1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvUpnpOrgRenderingControl1.cs
$(objdir)DvUpnpOrgRenderingControl2.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvUpnpOrgRenderingControl2.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvUpnpOrgRenderingControl2.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvUpnpOrgRenderingControl2.cs
$(objdir)DvUpnpOrgScheduledRecording1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvUpnpOrgScheduledRecording1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvUpnpOrgScheduledRecording1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvUpnpOrgScheduledRecording1.cs
$(objdir)DvUpnpOrgScheduledRecording2.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvUpnpOrgScheduledRecording2.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvUpnpOrgScheduledRecording2.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvUpnpOrgScheduledRecording2.cs
$(objdir)DvUpnpOrgSwitchPower1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvUpnpOrgSwitchPower1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvUpnpOrgSwitchPower1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvUpnpOrgSwitchPower1.cs
$(objdir)DvUpnpOrgDimming1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvUpnpOrgDimming1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvUpnpOrgDimming1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvUpnpOrgDimming1.cs
$(objdir)DvAvOpenhomeOrgInfo1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvAvOpenhomeOrgInfo1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvAvOpenhomeOrgInfo1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvAvOpenhomeOrgInfo1.cs
$(objdir)DvAvOpenhomeOrgTime1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvAvOpenhomeOrgTime1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvAvOpenhomeOrgTime1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvAvOpenhomeOrgTime1.cs
$(objdir)DvAvOpenhomeOrgPlaylist1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvAvOpenhomeOrgPlaylist1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvAvOpenhomeOrgPlaylist1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvAvOpenhomeOrgPlaylist1.cs
$(objdir)DvAvOpenhomeOrgVolume1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvAvOpenhomeOrgVolume1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvAvOpenhomeOrgVolume1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvAvOpenhomeOrgVolume1.cs
$(objdir)DvAvOpenhomeOrgProduct1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvAvOpenhomeOrgProduct1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvAvOpenhomeOrgProduct1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvAvOpenhomeOrgProduct1.cs
$(objdir)DvAvOpenhomeOrgRadio1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvAvOpenhomeOrgRadio1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvAvOpenhomeOrgRadio1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvAvOpenhomeOrgRadio1.cs
$(objdir)DvZappOrgTestBasic1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvZappOrgTestBasic1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvZappOrgTestBasic1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvZappOrgTestBasic1.cs
$(objdir)DvZappOrgTestLights1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvZappOrgTestLights1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvZappOrgTestLights1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvZappOrgTestLights1.cs
$(objdir)DvZappOrgTestDimmableLight1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvZappOrgTestDimmableLight1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvZappOrgTestDimmableLight1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvZappOrgTestDimmableLight1.cs
$(objdir)DvOpenhomeOrgTestColorLight1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvOpenhomeOrgTestColorLight1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvOpenhomeOrgTestColorLight1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvOpenhomeOrgTestColorLight1.cs
$(objdir)DvOpenhomeOrgOhNet1.net.dll: $(objdir)Zapp.net.dll $(deviceCs)DvOpenhomeOrgOhNet1.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)DvOpenhomeOrgOhNet1.net.dll \
		/reference:$(objdir)Zapp.net.dll \
		$(deviceCs)DvOpenhomeOrgOhNet1.cs


