# Auto-generated file.  DO NOT EDIT DIRECTLY
# Update CpUpnpMakeT4.tt and run 
#    make generate-makefiles
# to apply any updates

GenAll: AllCp AllDv

AllCp: CpCppCore CpCppStd CpC CpCs CpJs

AllDv: DvCppCore DvCppStd DvC DvCs


CpCppCore:   $(proxyCppCore)CpUpnpOrgAVTransport1.cpp $(proxyCppCore)CpUpnpOrgAVTransport2.cpp $(proxyCppCore)CpUpnpOrgConnectionManager1.cpp $(proxyCppCore)CpUpnpOrgConnectionManager2.cpp $(proxyCppCore)CpUpnpOrgContentDirectory1.cpp $(proxyCppCore)CpUpnpOrgContentDirectory2.cpp $(proxyCppCore)CpUpnpOrgContentDirectory3.cpp $(proxyCppCore)CpUpnpOrgRenderingControl1.cpp $(proxyCppCore)CpUpnpOrgRenderingControl2.cpp $(proxyCppCore)CpUpnpOrgScheduledRecording1.cpp $(proxyCppCore)CpUpnpOrgScheduledRecording2.cpp $(proxyCppCore)CpUpnpOrgSwitchPower1.cpp $(proxyCppCore)CpUpnpOrgDimming1.cpp $(proxyCppCore)CpAvOpenhomeOrgInfo1.cpp $(proxyCppCore)CpAvOpenhomeOrgTime1.cpp $(proxyCppCore)CpAvOpenhomeOrgPlaylist1.cpp $(proxyCppCore)CpAvOpenhomeOrgVolume1.cpp $(proxyCppCore)CpAvOpenhomeOrgProduct1.cpp $(proxyCppCore)CpAvOpenhomeOrgRadio1.cpp $(proxyCppCore)CpOpenhomeOrgOhNet1.cpp $(proxyCppCore)CpZappOrgTestBasic1.cpp $(proxyCppCore)CpZappOrgTestLights1.cpp $(proxyCppCore)CpZappOrgTestDimmableLight1.cpp
$(proxyCppCore)CpUpnpOrgAVTransport1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo CpUpnpOrgAVTransport1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(proxyCppCore) --domain=upnp.org --type=AVTransport --version=1
$(proxyCppCore)CpUpnpOrgAVTransport2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo CpUpnpOrgAVTransport2.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(proxyCppCore) --domain=upnp.org --type=AVTransport --version=2
$(proxyCppCore)CpUpnpOrgConnectionManager1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo CpUpnpOrgConnectionManager1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(proxyCppCore) --domain=upnp.org --type=ConnectionManager --version=1
$(proxyCppCore)CpUpnpOrgConnectionManager2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo CpUpnpOrgConnectionManager2.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(proxyCppCore) --domain=upnp.org --type=ConnectionManager --version=2
$(proxyCppCore)CpUpnpOrgContentDirectory1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo CpUpnpOrgContentDirectory1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(proxyCppCore) --domain=upnp.org --type=ContentDirectory --version=1
$(proxyCppCore)CpUpnpOrgContentDirectory2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo CpUpnpOrgContentDirectory2.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(proxyCppCore) --domain=upnp.org --type=ContentDirectory --version=2
$(proxyCppCore)CpUpnpOrgContentDirectory3.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo CpUpnpOrgContentDirectory3.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(proxyCppCore) --domain=upnp.org --type=ContentDirectory --version=3
$(proxyCppCore)CpUpnpOrgRenderingControl1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo CpUpnpOrgRenderingControl1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(proxyCppCore) --domain=upnp.org --type=RenderingControl --version=1
$(proxyCppCore)CpUpnpOrgRenderingControl2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo CpUpnpOrgRenderingControl2.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(proxyCppCore) --domain=upnp.org --type=RenderingControl --version=2
$(proxyCppCore)CpUpnpOrgScheduledRecording1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo CpUpnpOrgScheduledRecording1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(proxyCppCore) --domain=upnp.org --type=ScheduledRecording --version=1
$(proxyCppCore)CpUpnpOrgScheduledRecording2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo CpUpnpOrgScheduledRecording2.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(proxyCppCore) --domain=upnp.org --type=ScheduledRecording --version=2
$(proxyCppCore)CpUpnpOrgSwitchPower1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo CpUpnpOrgSwitchPower1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(proxyCppCore) --domain=upnp.org --type=SwitchPower --version=1
$(proxyCppCore)CpUpnpOrgDimming1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo CpUpnpOrgDimming1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(proxyCppCore) --domain=upnp.org --type=Dimming --version=1
$(proxyCppCore)CpAvOpenhomeOrgInfo1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/OpenHome/Info1.xml
	echo CpAvOpenhomeOrgInfo1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/OpenHome/Info1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=Info --version=1
$(proxyCppCore)CpAvOpenhomeOrgTime1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/OpenHome/Time1.xml
	echo CpAvOpenhomeOrgTime1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/OpenHome/Time1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=Time --version=1
$(proxyCppCore)CpAvOpenhomeOrgPlaylist1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/OpenHome/Playlist1.xml
	echo CpAvOpenhomeOrgPlaylist1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/OpenHome/Playlist1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=Playlist --version=1
$(proxyCppCore)CpAvOpenhomeOrgVolume1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/OpenHome/Volume1.xml
	echo CpAvOpenhomeOrgVolume1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/OpenHome/Volume1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=Volume --version=1
$(proxyCppCore)CpAvOpenhomeOrgProduct1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/OpenHome/Product1.xml
	echo CpAvOpenhomeOrgProduct1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/OpenHome/Product1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=Product --version=1
$(proxyCppCore)CpAvOpenhomeOrgRadio1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/OpenHome/Radio1.xml
	echo CpAvOpenhomeOrgRadio1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/OpenHome/Radio1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=Radio --version=1
$(proxyCppCore)CpOpenhomeOrgOhNet1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/OpenHome/OhNet1.xml
	echo CpOpenhomeOrgOhNet1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/OpenHome/OhNet1.xml" --output=$(proxyCppCore) --domain=openhome.org --type=OhNet --version=1
$(proxyCppCore)CpZappOrgTestBasic1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo CpZappOrgTestBasic1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(proxyCppCore) --domain=zapp.org --type=TestBasic --version=1
$(proxyCppCore)CpZappOrgTestLights1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo CpZappOrgTestLights1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(proxyCppCore) --domain=zapp.org --type=TestLights --version=1
$(proxyCppCore)CpZappOrgTestDimmableLight1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo CpZappOrgTestDimmableLight1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(proxyCppCore) --domain=zapp.org --type=TestDimmableLight --version=1

CpCppStd:   $(proxyCppStd)CpUpnpOrgAVTransport1Std.cpp $(proxyCppStd)CpUpnpOrgAVTransport2Std.cpp $(proxyCppStd)CpUpnpOrgConnectionManager1Std.cpp $(proxyCppStd)CpUpnpOrgConnectionManager2Std.cpp $(proxyCppStd)CpUpnpOrgContentDirectory1Std.cpp $(proxyCppStd)CpUpnpOrgContentDirectory2Std.cpp $(proxyCppStd)CpUpnpOrgContentDirectory3Std.cpp $(proxyCppStd)CpUpnpOrgRenderingControl1Std.cpp $(proxyCppStd)CpUpnpOrgRenderingControl2Std.cpp $(proxyCppStd)CpUpnpOrgScheduledRecording1Std.cpp $(proxyCppStd)CpUpnpOrgScheduledRecording2Std.cpp $(proxyCppStd)CpUpnpOrgSwitchPower1Std.cpp $(proxyCppStd)CpUpnpOrgDimming1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgInfo1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgTime1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgPlaylist1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgVolume1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgProduct1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgRadio1Std.cpp $(proxyCppStd)CpOpenhomeOrgOhNet1Std.cpp $(proxyCppStd)CpZappOrgTestBasic1Std.cpp $(proxyCppStd)CpZappOrgTestLights1Std.cpp $(proxyCppStd)CpZappOrgTestDimmableLight1Std.cpp
$(proxyCppStd)CpUpnpOrgAVTransport1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo CpUpnpOrgAVTransport1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(proxyCppStd) --domain=upnp.org --type=AVTransport --version=1
$(proxyCppStd)CpUpnpOrgAVTransport2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo CpUpnpOrgAVTransport2Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(proxyCppStd) --domain=upnp.org --type=AVTransport --version=2
$(proxyCppStd)CpUpnpOrgConnectionManager1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo CpUpnpOrgConnectionManager1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(proxyCppStd) --domain=upnp.org --type=ConnectionManager --version=1
$(proxyCppStd)CpUpnpOrgConnectionManager2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo CpUpnpOrgConnectionManager2Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(proxyCppStd) --domain=upnp.org --type=ConnectionManager --version=2
$(proxyCppStd)CpUpnpOrgContentDirectory1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo CpUpnpOrgContentDirectory1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(proxyCppStd) --domain=upnp.org --type=ContentDirectory --version=1
$(proxyCppStd)CpUpnpOrgContentDirectory2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo CpUpnpOrgContentDirectory2Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(proxyCppStd) --domain=upnp.org --type=ContentDirectory --version=2
$(proxyCppStd)CpUpnpOrgContentDirectory3Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo CpUpnpOrgContentDirectory3Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(proxyCppStd) --domain=upnp.org --type=ContentDirectory --version=3
$(proxyCppStd)CpUpnpOrgRenderingControl1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo CpUpnpOrgRenderingControl1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(proxyCppStd) --domain=upnp.org --type=RenderingControl --version=1
$(proxyCppStd)CpUpnpOrgRenderingControl2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo CpUpnpOrgRenderingControl2Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(proxyCppStd) --domain=upnp.org --type=RenderingControl --version=2
$(proxyCppStd)CpUpnpOrgScheduledRecording1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo CpUpnpOrgScheduledRecording1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(proxyCppStd) --domain=upnp.org --type=ScheduledRecording --version=1
$(proxyCppStd)CpUpnpOrgScheduledRecording2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo CpUpnpOrgScheduledRecording2Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(proxyCppStd) --domain=upnp.org --type=ScheduledRecording --version=2
$(proxyCppStd)CpUpnpOrgSwitchPower1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo CpUpnpOrgSwitchPower1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(proxyCppStd) --domain=upnp.org --type=SwitchPower --version=1
$(proxyCppStd)CpUpnpOrgDimming1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo CpUpnpOrgDimming1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(proxyCppStd) --domain=upnp.org --type=Dimming --version=1
$(proxyCppStd)CpAvOpenhomeOrgInfo1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/OpenHome/Info1.xml
	echo CpAvOpenhomeOrgInfo1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/OpenHome/Info1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=Info --version=1
$(proxyCppStd)CpAvOpenhomeOrgTime1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/OpenHome/Time1.xml
	echo CpAvOpenhomeOrgTime1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/OpenHome/Time1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=Time --version=1
$(proxyCppStd)CpAvOpenhomeOrgPlaylist1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/OpenHome/Playlist1.xml
	echo CpAvOpenhomeOrgPlaylist1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/OpenHome/Playlist1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=Playlist --version=1
$(proxyCppStd)CpAvOpenhomeOrgVolume1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/OpenHome/Volume1.xml
	echo CpAvOpenhomeOrgVolume1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/OpenHome/Volume1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=Volume --version=1
$(proxyCppStd)CpAvOpenhomeOrgProduct1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/OpenHome/Product1.xml
	echo CpAvOpenhomeOrgProduct1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/OpenHome/Product1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=Product --version=1
$(proxyCppStd)CpAvOpenhomeOrgRadio1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/OpenHome/Radio1.xml
	echo CpAvOpenhomeOrgRadio1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/OpenHome/Radio1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=Radio --version=1
$(proxyCppStd)CpOpenhomeOrgOhNet1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/OpenHome/OhNet1.xml
	echo CpOpenhomeOrgOhNet1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/OpenHome/OhNet1.xml" --output=$(proxyCppStd) --domain=openhome.org --type=OhNet --version=1
$(proxyCppStd)CpZappOrgTestBasic1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo CpZappOrgTestBasic1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(proxyCppStd) --domain=zapp.org --type=TestBasic --version=1
$(proxyCppStd)CpZappOrgTestLights1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo CpZappOrgTestLights1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(proxyCppStd) --domain=zapp.org --type=TestLights --version=1
$(proxyCppStd)CpZappOrgTestDimmableLight1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo CpZappOrgTestDimmableLight1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(proxyCppStd) --domain=zapp.org --type=TestDimmableLight --version=1

CpC:   $(proxyC)CpUpnpOrgAVTransport1C.cpp $(proxyC)CpUpnpOrgAVTransport2C.cpp $(proxyC)CpUpnpOrgConnectionManager1C.cpp $(proxyC)CpUpnpOrgConnectionManager2C.cpp $(proxyC)CpUpnpOrgContentDirectory1C.cpp $(proxyC)CpUpnpOrgContentDirectory2C.cpp $(proxyC)CpUpnpOrgContentDirectory3C.cpp $(proxyC)CpUpnpOrgRenderingControl1C.cpp $(proxyC)CpUpnpOrgRenderingControl2C.cpp $(proxyC)CpUpnpOrgScheduledRecording1C.cpp $(proxyC)CpUpnpOrgScheduledRecording2C.cpp $(proxyC)CpUpnpOrgSwitchPower1C.cpp $(proxyC)CpUpnpOrgDimming1C.cpp $(proxyC)CpAvOpenhomeOrgInfo1C.cpp $(proxyC)CpAvOpenhomeOrgTime1C.cpp $(proxyC)CpAvOpenhomeOrgPlaylist1C.cpp $(proxyC)CpAvOpenhomeOrgVolume1C.cpp $(proxyC)CpAvOpenhomeOrgProduct1C.cpp $(proxyC)CpAvOpenhomeOrgRadio1C.cpp $(proxyC)CpOpenhomeOrgOhNet1C.cpp $(proxyC)CpZappOrgTestBasic1C.cpp $(proxyC)CpZappOrgTestLights1C.cpp $(proxyC)CpZappOrgTestDimmableLight1C.cpp
$(proxyC)CpUpnpOrgAVTransport1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo CpUpnpOrgAVTransport1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(proxyC) --domain=upnp.org --type=AVTransport --version=1
$(proxyC)CpUpnpOrgAVTransport2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo CpUpnpOrgAVTransport2C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(proxyC) --domain=upnp.org --type=AVTransport --version=2
$(proxyC)CpUpnpOrgConnectionManager1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo CpUpnpOrgConnectionManager1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(proxyC) --domain=upnp.org --type=ConnectionManager --version=1
$(proxyC)CpUpnpOrgConnectionManager2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo CpUpnpOrgConnectionManager2C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(proxyC) --domain=upnp.org --type=ConnectionManager --version=2
$(proxyC)CpUpnpOrgContentDirectory1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo CpUpnpOrgContentDirectory1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(proxyC) --domain=upnp.org --type=ContentDirectory --version=1
$(proxyC)CpUpnpOrgContentDirectory2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo CpUpnpOrgContentDirectory2C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(proxyC) --domain=upnp.org --type=ContentDirectory --version=2
$(proxyC)CpUpnpOrgContentDirectory3C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo CpUpnpOrgContentDirectory3C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(proxyC) --domain=upnp.org --type=ContentDirectory --version=3
$(proxyC)CpUpnpOrgRenderingControl1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo CpUpnpOrgRenderingControl1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(proxyC) --domain=upnp.org --type=RenderingControl --version=1
$(proxyC)CpUpnpOrgRenderingControl2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo CpUpnpOrgRenderingControl2C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(proxyC) --domain=upnp.org --type=RenderingControl --version=2
$(proxyC)CpUpnpOrgScheduledRecording1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo CpUpnpOrgScheduledRecording1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(proxyC) --domain=upnp.org --type=ScheduledRecording --version=1
$(proxyC)CpUpnpOrgScheduledRecording2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo CpUpnpOrgScheduledRecording2C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(proxyC) --domain=upnp.org --type=ScheduledRecording --version=2
$(proxyC)CpUpnpOrgSwitchPower1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo CpUpnpOrgSwitchPower1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(proxyC) --domain=upnp.org --type=SwitchPower --version=1
$(proxyC)CpUpnpOrgDimming1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo CpUpnpOrgDimming1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(proxyC) --domain=upnp.org --type=Dimming --version=1
$(proxyC)CpAvOpenhomeOrgInfo1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/OpenHome/Info1.xml
	echo CpAvOpenhomeOrgInfo1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/OpenHome/Info1.xml" --output=$(proxyC) --domain=av.openhome.org --type=Info --version=1
$(proxyC)CpAvOpenhomeOrgTime1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/OpenHome/Time1.xml
	echo CpAvOpenhomeOrgTime1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/OpenHome/Time1.xml" --output=$(proxyC) --domain=av.openhome.org --type=Time --version=1
$(proxyC)CpAvOpenhomeOrgPlaylist1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/OpenHome/Playlist1.xml
	echo CpAvOpenhomeOrgPlaylist1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/OpenHome/Playlist1.xml" --output=$(proxyC) --domain=av.openhome.org --type=Playlist --version=1
$(proxyC)CpAvOpenhomeOrgVolume1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/OpenHome/Volume1.xml
	echo CpAvOpenhomeOrgVolume1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/OpenHome/Volume1.xml" --output=$(proxyC) --domain=av.openhome.org --type=Volume --version=1
$(proxyC)CpAvOpenhomeOrgProduct1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/OpenHome/Product1.xml
	echo CpAvOpenhomeOrgProduct1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/OpenHome/Product1.xml" --output=$(proxyC) --domain=av.openhome.org --type=Product --version=1
$(proxyC)CpAvOpenhomeOrgRadio1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/OpenHome/Radio1.xml
	echo CpAvOpenhomeOrgRadio1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/OpenHome/Radio1.xml" --output=$(proxyC) --domain=av.openhome.org --type=Radio --version=1
$(proxyC)CpOpenhomeOrgOhNet1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/OpenHome/OhNet1.xml
	echo CpOpenhomeOrgOhNet1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/OpenHome/OhNet1.xml" --output=$(proxyC) --domain=openhome.org --type=OhNet --version=1
$(proxyC)CpZappOrgTestBasic1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo CpZappOrgTestBasic1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(proxyC) --domain=zapp.org --type=TestBasic --version=1
$(proxyC)CpZappOrgTestLights1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo CpZappOrgTestLights1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(proxyC) --domain=zapp.org --type=TestLights --version=1
$(proxyC)CpZappOrgTestDimmableLight1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo CpZappOrgTestDimmableLight1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(proxyC) --domain=zapp.org --type=TestDimmableLight --version=1

CpCs:   $(proxyCs)CpUpnpOrgAVTransport1.cs $(proxyCs)CpUpnpOrgAVTransport2.cs $(proxyCs)CpUpnpOrgConnectionManager1.cs $(proxyCs)CpUpnpOrgConnectionManager2.cs $(proxyCs)CpUpnpOrgContentDirectory1.cs $(proxyCs)CpUpnpOrgContentDirectory2.cs $(proxyCs)CpUpnpOrgContentDirectory3.cs $(proxyCs)CpUpnpOrgRenderingControl1.cs $(proxyCs)CpUpnpOrgRenderingControl2.cs $(proxyCs)CpUpnpOrgScheduledRecording1.cs $(proxyCs)CpUpnpOrgScheduledRecording2.cs $(proxyCs)CpUpnpOrgSwitchPower1.cs $(proxyCs)CpUpnpOrgDimming1.cs $(proxyCs)CpAvOpenhomeOrgInfo1.cs $(proxyCs)CpAvOpenhomeOrgTime1.cs $(proxyCs)CpAvOpenhomeOrgPlaylist1.cs $(proxyCs)CpAvOpenhomeOrgVolume1.cs $(proxyCs)CpAvOpenhomeOrgProduct1.cs $(proxyCs)CpAvOpenhomeOrgRadio1.cs $(proxyCs)CpOpenhomeOrgOhNet1.cs $(proxyCs)CpZappOrgTestBasic1.cs $(proxyCs)CpZappOrgTestLights1.cs $(proxyCs)CpZappOrgTestDimmableLight1.cs
$(proxyCs)CpUpnpOrgAVTransport1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo CpUpnpOrgAVTransport1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(proxyCs) --domain=upnp.org --type=AVTransport --version=1
$(proxyCs)CpUpnpOrgAVTransport2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo CpUpnpOrgAVTransport2.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(proxyCs) --domain=upnp.org --type=AVTransport --version=2
$(proxyCs)CpUpnpOrgConnectionManager1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo CpUpnpOrgConnectionManager1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(proxyCs) --domain=upnp.org --type=ConnectionManager --version=1
$(proxyCs)CpUpnpOrgConnectionManager2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo CpUpnpOrgConnectionManager2.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(proxyCs) --domain=upnp.org --type=ConnectionManager --version=2
$(proxyCs)CpUpnpOrgContentDirectory1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo CpUpnpOrgContentDirectory1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(proxyCs) --domain=upnp.org --type=ContentDirectory --version=1
$(proxyCs)CpUpnpOrgContentDirectory2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo CpUpnpOrgContentDirectory2.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(proxyCs) --domain=upnp.org --type=ContentDirectory --version=2
$(proxyCs)CpUpnpOrgContentDirectory3.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo CpUpnpOrgContentDirectory3.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(proxyCs) --domain=upnp.org --type=ContentDirectory --version=3
$(proxyCs)CpUpnpOrgRenderingControl1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo CpUpnpOrgRenderingControl1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(proxyCs) --domain=upnp.org --type=RenderingControl --version=1
$(proxyCs)CpUpnpOrgRenderingControl2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo CpUpnpOrgRenderingControl2.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(proxyCs) --domain=upnp.org --type=RenderingControl --version=2
$(proxyCs)CpUpnpOrgScheduledRecording1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo CpUpnpOrgScheduledRecording1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(proxyCs) --domain=upnp.org --type=ScheduledRecording --version=1
$(proxyCs)CpUpnpOrgScheduledRecording2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo CpUpnpOrgScheduledRecording2.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(proxyCs) --domain=upnp.org --type=ScheduledRecording --version=2
$(proxyCs)CpUpnpOrgSwitchPower1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo CpUpnpOrgSwitchPower1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(proxyCs) --domain=upnp.org --type=SwitchPower --version=1
$(proxyCs)CpUpnpOrgDimming1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo CpUpnpOrgDimming1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(proxyCs) --domain=upnp.org --type=Dimming --version=1
$(proxyCs)CpAvOpenhomeOrgInfo1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/OpenHome/Info1.xml
	echo CpAvOpenhomeOrgInfo1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/OpenHome/Info1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=Info --version=1
$(proxyCs)CpAvOpenhomeOrgTime1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/OpenHome/Time1.xml
	echo CpAvOpenhomeOrgTime1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/OpenHome/Time1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=Time --version=1
$(proxyCs)CpAvOpenhomeOrgPlaylist1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/OpenHome/Playlist1.xml
	echo CpAvOpenhomeOrgPlaylist1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/OpenHome/Playlist1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=Playlist --version=1
$(proxyCs)CpAvOpenhomeOrgVolume1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/OpenHome/Volume1.xml
	echo CpAvOpenhomeOrgVolume1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/OpenHome/Volume1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=Volume --version=1
$(proxyCs)CpAvOpenhomeOrgProduct1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/OpenHome/Product1.xml
	echo CpAvOpenhomeOrgProduct1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/OpenHome/Product1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=Product --version=1
$(proxyCs)CpAvOpenhomeOrgRadio1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/OpenHome/Radio1.xml
	echo CpAvOpenhomeOrgRadio1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/OpenHome/Radio1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=Radio --version=1
$(proxyCs)CpOpenhomeOrgOhNet1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/OpenHome/OhNet1.xml
	echo CpOpenhomeOrgOhNet1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/OpenHome/OhNet1.xml" --output=$(proxyCs) --domain=openhome.org --type=OhNet --version=1
$(proxyCs)CpZappOrgTestBasic1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo CpZappOrgTestBasic1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(proxyCs) --domain=zapp.org --type=TestBasic --version=1
$(proxyCs)CpZappOrgTestLights1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo CpZappOrgTestLights1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(proxyCs) --domain=zapp.org --type=TestLights --version=1
$(proxyCs)CpZappOrgTestDimmableLight1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo CpZappOrgTestDimmableLight1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(proxyCs) --domain=zapp.org --type=TestDimmableLight --version=1

CpJs:   $(proxyJs)CpUpnpOrgAVTransport1.js $(proxyJs)CpUpnpOrgAVTransport2.js $(proxyJs)CpUpnpOrgConnectionManager1.js $(proxyJs)CpUpnpOrgConnectionManager2.js $(proxyJs)CpUpnpOrgContentDirectory1.js $(proxyJs)CpUpnpOrgContentDirectory2.js $(proxyJs)CpUpnpOrgContentDirectory3.js $(proxyJs)CpUpnpOrgRenderingControl1.js $(proxyJs)CpUpnpOrgRenderingControl2.js $(proxyJs)CpUpnpOrgScheduledRecording1.js $(proxyJs)CpUpnpOrgScheduledRecording2.js $(proxyJs)CpUpnpOrgSwitchPower1.js $(proxyJs)CpUpnpOrgDimming1.js $(proxyJs)CpAvOpenhomeOrgInfo1.js $(proxyJs)CpAvOpenhomeOrgTime1.js $(proxyJs)CpAvOpenhomeOrgPlaylist1.js $(proxyJs)CpAvOpenhomeOrgVolume1.js $(proxyJs)CpAvOpenhomeOrgProduct1.js $(proxyJs)CpAvOpenhomeOrgRadio1.js $(proxyJs)CpOpenhomeOrgOhNet1.js $(proxyJs)CpZappOrgTestBasic1.js $(proxyJs)CpZappOrgTestLights1.js $(proxyJs)CpZappOrgTestDimmableLight1.js
$(proxyJs)CpUpnpOrgAVTransport1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo CpUpnpOrgAVTransport1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(proxyJs) --domain=upnp.org --type=AVTransport --version=1
$(proxyJs)CpUpnpOrgAVTransport2.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo CpUpnpOrgAVTransport2.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(proxyJs) --domain=upnp.org --type=AVTransport --version=2
$(proxyJs)CpUpnpOrgConnectionManager1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo CpUpnpOrgConnectionManager1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(proxyJs) --domain=upnp.org --type=ConnectionManager --version=1
$(proxyJs)CpUpnpOrgConnectionManager2.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo CpUpnpOrgConnectionManager2.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(proxyJs) --domain=upnp.org --type=ConnectionManager --version=2
$(proxyJs)CpUpnpOrgContentDirectory1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo CpUpnpOrgContentDirectory1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(proxyJs) --domain=upnp.org --type=ContentDirectory --version=1
$(proxyJs)CpUpnpOrgContentDirectory2.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo CpUpnpOrgContentDirectory2.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(proxyJs) --domain=upnp.org --type=ContentDirectory --version=2
$(proxyJs)CpUpnpOrgContentDirectory3.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo CpUpnpOrgContentDirectory3.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(proxyJs) --domain=upnp.org --type=ContentDirectory --version=3
$(proxyJs)CpUpnpOrgRenderingControl1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo CpUpnpOrgRenderingControl1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(proxyJs) --domain=upnp.org --type=RenderingControl --version=1
$(proxyJs)CpUpnpOrgRenderingControl2.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo CpUpnpOrgRenderingControl2.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(proxyJs) --domain=upnp.org --type=RenderingControl --version=2
$(proxyJs)CpUpnpOrgScheduledRecording1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo CpUpnpOrgScheduledRecording1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(proxyJs) --domain=upnp.org --type=ScheduledRecording --version=1
$(proxyJs)CpUpnpOrgScheduledRecording2.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo CpUpnpOrgScheduledRecording2.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(proxyJs) --domain=upnp.org --type=ScheduledRecording --version=2
$(proxyJs)CpUpnpOrgSwitchPower1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo CpUpnpOrgSwitchPower1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(proxyJs) --domain=upnp.org --type=SwitchPower --version=1
$(proxyJs)CpUpnpOrgDimming1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo CpUpnpOrgDimming1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(proxyJs) --domain=upnp.org --type=Dimming --version=1
$(proxyJs)CpAvOpenhomeOrgInfo1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/OpenHome/Info1.xml
	echo CpAvOpenhomeOrgInfo1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/OpenHome/Info1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=Info --version=1
$(proxyJs)CpAvOpenhomeOrgTime1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/OpenHome/Time1.xml
	echo CpAvOpenhomeOrgTime1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/OpenHome/Time1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=Time --version=1
$(proxyJs)CpAvOpenhomeOrgPlaylist1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/OpenHome/Playlist1.xml
	echo CpAvOpenhomeOrgPlaylist1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/OpenHome/Playlist1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=Playlist --version=1
$(proxyJs)CpAvOpenhomeOrgVolume1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/OpenHome/Volume1.xml
	echo CpAvOpenhomeOrgVolume1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/OpenHome/Volume1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=Volume --version=1
$(proxyJs)CpAvOpenhomeOrgProduct1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/OpenHome/Product1.xml
	echo CpAvOpenhomeOrgProduct1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/OpenHome/Product1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=Product --version=1
$(proxyJs)CpAvOpenhomeOrgRadio1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/OpenHome/Radio1.xml
	echo CpAvOpenhomeOrgRadio1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/OpenHome/Radio1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=Radio --version=1
$(proxyJs)CpOpenhomeOrgOhNet1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/OpenHome/OhNet1.xml
	echo CpOpenhomeOrgOhNet1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/OpenHome/OhNet1.xml" --output=$(proxyJs) --domain=openhome.org --type=OhNet --version=1
$(proxyJs)CpZappOrgTestBasic1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo CpZappOrgTestBasic1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(proxyJs) --domain=zapp.org --type=TestBasic --version=1
$(proxyJs)CpZappOrgTestLights1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo CpZappOrgTestLights1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(proxyJs) --domain=zapp.org --type=TestLights --version=1
$(proxyJs)CpZappOrgTestDimmableLight1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo CpZappOrgTestDimmableLight1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(proxyJs) --domain=zapp.org --type=TestDimmableLight --version=1

DvCppCore :   $(deviceCppCore)DvUpnpOrgAVTransport1.cpp $(deviceCppCore)DvUpnpOrgAVTransport2.cpp $(deviceCppCore)DvUpnpOrgConnectionManager1.cpp $(deviceCppCore)DvUpnpOrgConnectionManager2.cpp $(deviceCppCore)DvUpnpOrgContentDirectory1.cpp $(deviceCppCore)DvUpnpOrgContentDirectory2.cpp $(deviceCppCore)DvUpnpOrgContentDirectory3.cpp $(deviceCppCore)DvUpnpOrgRenderingControl1.cpp $(deviceCppCore)DvUpnpOrgRenderingControl2.cpp $(deviceCppCore)DvUpnpOrgScheduledRecording1.cpp $(deviceCppCore)DvUpnpOrgScheduledRecording2.cpp $(deviceCppCore)DvUpnpOrgSwitchPower1.cpp $(deviceCppCore)DvUpnpOrgDimming1.cpp $(deviceCppCore)DvAvOpenhomeOrgInfo1.cpp $(deviceCppCore)DvAvOpenhomeOrgTime1.cpp $(deviceCppCore)DvAvOpenhomeOrgPlaylist1.cpp $(deviceCppCore)DvAvOpenhomeOrgVolume1.cpp $(deviceCppCore)DvAvOpenhomeOrgProduct1.cpp $(deviceCppCore)DvAvOpenhomeOrgRadio1.cpp $(deviceCppCore)DvOpenhomeOrgOhNet1.cpp $(deviceCppCore)DvZappOrgTestBasic1.cpp $(deviceCppCore)DvZappOrgTestLights1.cpp $(deviceCppCore)DvZappOrgTestDimmableLight1.cpp
$(deviceCppCore)DvUpnpOrgAVTransport1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo DvUpnpOrgAVTransport1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(deviceCppCore) --domain=upnp.org --type=AVTransport --version=1
$(deviceCppCore)DvUpnpOrgAVTransport2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo DvUpnpOrgAVTransport2.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(deviceCppCore) --domain=upnp.org --type=AVTransport --version=2
$(deviceCppCore)DvUpnpOrgConnectionManager1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo DvUpnpOrgConnectionManager1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(deviceCppCore) --domain=upnp.org --type=ConnectionManager --version=1
$(deviceCppCore)DvUpnpOrgConnectionManager2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo DvUpnpOrgConnectionManager2.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(deviceCppCore) --domain=upnp.org --type=ConnectionManager --version=2
$(deviceCppCore)DvUpnpOrgContentDirectory1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo DvUpnpOrgContentDirectory1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(deviceCppCore) --domain=upnp.org --type=ContentDirectory --version=1
$(deviceCppCore)DvUpnpOrgContentDirectory2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo DvUpnpOrgContentDirectory2.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(deviceCppCore) --domain=upnp.org --type=ContentDirectory --version=2
$(deviceCppCore)DvUpnpOrgContentDirectory3.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo DvUpnpOrgContentDirectory3.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(deviceCppCore) --domain=upnp.org --type=ContentDirectory --version=3
$(deviceCppCore)DvUpnpOrgRenderingControl1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo DvUpnpOrgRenderingControl1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(deviceCppCore) --domain=upnp.org --type=RenderingControl --version=1
$(deviceCppCore)DvUpnpOrgRenderingControl2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo DvUpnpOrgRenderingControl2.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(deviceCppCore) --domain=upnp.org --type=RenderingControl --version=2
$(deviceCppCore)DvUpnpOrgScheduledRecording1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo DvUpnpOrgScheduledRecording1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(deviceCppCore) --domain=upnp.org --type=ScheduledRecording --version=1
$(deviceCppCore)DvUpnpOrgScheduledRecording2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo DvUpnpOrgScheduledRecording2.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(deviceCppCore) --domain=upnp.org --type=ScheduledRecording --version=2
$(deviceCppCore)DvUpnpOrgSwitchPower1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo DvUpnpOrgSwitchPower1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(deviceCppCore) --domain=upnp.org --type=SwitchPower --version=1
$(deviceCppCore)DvUpnpOrgDimming1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo DvUpnpOrgDimming1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(deviceCppCore) --domain=upnp.org --type=Dimming --version=1
$(deviceCppCore)DvAvOpenhomeOrgInfo1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/OpenHome/Info1.xml
	echo DvAvOpenhomeOrgInfo1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/OpenHome/Info1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=Info --version=1
$(deviceCppCore)DvAvOpenhomeOrgTime1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/OpenHome/Time1.xml
	echo DvAvOpenhomeOrgTime1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/OpenHome/Time1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=Time --version=1
$(deviceCppCore)DvAvOpenhomeOrgPlaylist1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/OpenHome/Playlist1.xml
	echo DvAvOpenhomeOrgPlaylist1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/OpenHome/Playlist1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=Playlist --version=1
$(deviceCppCore)DvAvOpenhomeOrgVolume1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/OpenHome/Volume1.xml
	echo DvAvOpenhomeOrgVolume1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/OpenHome/Volume1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=Volume --version=1
$(deviceCppCore)DvAvOpenhomeOrgProduct1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/OpenHome/Product1.xml
	echo DvAvOpenhomeOrgProduct1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/OpenHome/Product1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=Product --version=1
$(deviceCppCore)DvAvOpenhomeOrgRadio1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/OpenHome/Radio1.xml
	echo DvAvOpenhomeOrgRadio1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/OpenHome/Radio1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=Radio --version=1
$(deviceCppCore)DvOpenhomeOrgOhNet1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/OpenHome/OhNet1.xml
	echo DvOpenhomeOrgOhNet1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/OpenHome/OhNet1.xml" --output=$(deviceCppCore) --domain=openhome.org --type=OhNet --version=1
$(deviceCppCore)DvZappOrgTestBasic1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo DvZappOrgTestBasic1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(deviceCppCore) --domain=zapp.org --type=TestBasic --version=1
$(deviceCppCore)DvZappOrgTestLights1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo DvZappOrgTestLights1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(deviceCppCore) --domain=zapp.org --type=TestLights --version=1
$(deviceCppCore)DvZappOrgTestDimmableLight1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo DvZappOrgTestDimmableLight1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(deviceCppCore) --domain=zapp.org --type=TestDimmableLight --version=1

DvCppStd :   $(deviceCppStd)DvUpnpOrgAVTransport1Std.cpp $(deviceCppStd)DvUpnpOrgAVTransport2Std.cpp $(deviceCppStd)DvUpnpOrgConnectionManager1Std.cpp $(deviceCppStd)DvUpnpOrgConnectionManager2Std.cpp $(deviceCppStd)DvUpnpOrgContentDirectory1Std.cpp $(deviceCppStd)DvUpnpOrgContentDirectory2Std.cpp $(deviceCppStd)DvUpnpOrgContentDirectory3Std.cpp $(deviceCppStd)DvUpnpOrgRenderingControl1Std.cpp $(deviceCppStd)DvUpnpOrgRenderingControl2Std.cpp $(deviceCppStd)DvUpnpOrgScheduledRecording1Std.cpp $(deviceCppStd)DvUpnpOrgScheduledRecording2Std.cpp $(deviceCppStd)DvUpnpOrgSwitchPower1Std.cpp $(deviceCppStd)DvUpnpOrgDimming1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgInfo1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgTime1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgPlaylist1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgVolume1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgProduct1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgRadio1Std.cpp $(deviceCppStd)DvOpenhomeOrgOhNet1Std.cpp $(deviceCppStd)DvZappOrgTestBasic1Std.cpp $(deviceCppStd)DvZappOrgTestLights1Std.cpp $(deviceCppStd)DvZappOrgTestDimmableLight1Std.cpp
$(deviceCppStd)DvUpnpOrgAVTransport1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo DvUpnpOrgAVTransport1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(deviceCppStd) --domain=upnp.org --type=AVTransport --version=1
$(deviceCppStd)DvUpnpOrgAVTransport2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo DvUpnpOrgAVTransport2Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(deviceCppStd) --domain=upnp.org --type=AVTransport --version=2
$(deviceCppStd)DvUpnpOrgConnectionManager1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo DvUpnpOrgConnectionManager1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(deviceCppStd) --domain=upnp.org --type=ConnectionManager --version=1
$(deviceCppStd)DvUpnpOrgConnectionManager2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo DvUpnpOrgConnectionManager2Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(deviceCppStd) --domain=upnp.org --type=ConnectionManager --version=2
$(deviceCppStd)DvUpnpOrgContentDirectory1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo DvUpnpOrgContentDirectory1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(deviceCppStd) --domain=upnp.org --type=ContentDirectory --version=1
$(deviceCppStd)DvUpnpOrgContentDirectory2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo DvUpnpOrgContentDirectory2Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(deviceCppStd) --domain=upnp.org --type=ContentDirectory --version=2
$(deviceCppStd)DvUpnpOrgContentDirectory3Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo DvUpnpOrgContentDirectory3Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(deviceCppStd) --domain=upnp.org --type=ContentDirectory --version=3
$(deviceCppStd)DvUpnpOrgRenderingControl1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo DvUpnpOrgRenderingControl1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(deviceCppStd) --domain=upnp.org --type=RenderingControl --version=1
$(deviceCppStd)DvUpnpOrgRenderingControl2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo DvUpnpOrgRenderingControl2Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(deviceCppStd) --domain=upnp.org --type=RenderingControl --version=2
$(deviceCppStd)DvUpnpOrgScheduledRecording1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo DvUpnpOrgScheduledRecording1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(deviceCppStd) --domain=upnp.org --type=ScheduledRecording --version=1
$(deviceCppStd)DvUpnpOrgScheduledRecording2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo DvUpnpOrgScheduledRecording2Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(deviceCppStd) --domain=upnp.org --type=ScheduledRecording --version=2
$(deviceCppStd)DvUpnpOrgSwitchPower1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo DvUpnpOrgSwitchPower1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(deviceCppStd) --domain=upnp.org --type=SwitchPower --version=1
$(deviceCppStd)DvUpnpOrgDimming1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo DvUpnpOrgDimming1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(deviceCppStd) --domain=upnp.org --type=Dimming --version=1
$(deviceCppStd)DvAvOpenhomeOrgInfo1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/OpenHome/Info1.xml
	echo DvAvOpenhomeOrgInfo1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/OpenHome/Info1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=Info --version=1
$(deviceCppStd)DvAvOpenhomeOrgTime1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/OpenHome/Time1.xml
	echo DvAvOpenhomeOrgTime1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/OpenHome/Time1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=Time --version=1
$(deviceCppStd)DvAvOpenhomeOrgPlaylist1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/OpenHome/Playlist1.xml
	echo DvAvOpenhomeOrgPlaylist1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/OpenHome/Playlist1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=Playlist --version=1
$(deviceCppStd)DvAvOpenhomeOrgVolume1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/OpenHome/Volume1.xml
	echo DvAvOpenhomeOrgVolume1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/OpenHome/Volume1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=Volume --version=1
$(deviceCppStd)DvAvOpenhomeOrgProduct1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/OpenHome/Product1.xml
	echo DvAvOpenhomeOrgProduct1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/OpenHome/Product1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=Product --version=1
$(deviceCppStd)DvAvOpenhomeOrgRadio1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/OpenHome/Radio1.xml
	echo DvAvOpenhomeOrgRadio1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/OpenHome/Radio1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=Radio --version=1
$(deviceCppStd)DvOpenhomeOrgOhNet1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/OpenHome/OhNet1.xml
	echo DvOpenhomeOrgOhNet1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/OpenHome/OhNet1.xml" --output=$(deviceCppStd) --domain=openhome.org --type=OhNet --version=1
$(deviceCppStd)DvZappOrgTestBasic1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo DvZappOrgTestBasic1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(deviceCppStd) --domain=zapp.org --type=TestBasic --version=1
$(deviceCppStd)DvZappOrgTestLights1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo DvZappOrgTestLights1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(deviceCppStd) --domain=zapp.org --type=TestLights --version=1
$(deviceCppStd)DvZappOrgTestDimmableLight1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo DvZappOrgTestDimmableLight1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(deviceCppStd) --domain=zapp.org --type=TestDimmableLight --version=1

DvC :   $(deviceC)DvUpnpOrgAVTransport1C.cpp $(deviceC)DvUpnpOrgAVTransport2C.cpp $(deviceC)DvUpnpOrgConnectionManager1C.cpp $(deviceC)DvUpnpOrgConnectionManager2C.cpp $(deviceC)DvUpnpOrgContentDirectory1C.cpp $(deviceC)DvUpnpOrgContentDirectory2C.cpp $(deviceC)DvUpnpOrgContentDirectory3C.cpp $(deviceC)DvUpnpOrgRenderingControl1C.cpp $(deviceC)DvUpnpOrgRenderingControl2C.cpp $(deviceC)DvUpnpOrgScheduledRecording1C.cpp $(deviceC)DvUpnpOrgScheduledRecording2C.cpp $(deviceC)DvUpnpOrgSwitchPower1C.cpp $(deviceC)DvUpnpOrgDimming1C.cpp $(deviceC)DvAvOpenhomeOrgInfo1C.cpp $(deviceC)DvAvOpenhomeOrgTime1C.cpp $(deviceC)DvAvOpenhomeOrgPlaylist1C.cpp $(deviceC)DvAvOpenhomeOrgVolume1C.cpp $(deviceC)DvAvOpenhomeOrgProduct1C.cpp $(deviceC)DvAvOpenhomeOrgRadio1C.cpp $(deviceC)DvOpenhomeOrgOhNet1C.cpp $(deviceC)DvZappOrgTestBasic1C.cpp $(deviceC)DvZappOrgTestLights1C.cpp $(deviceC)DvZappOrgTestDimmableLight1C.cpp
$(deviceC)DvUpnpOrgAVTransport1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo DvUpnpOrgAVTransport1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(deviceC) --domain=upnp.org --type=AVTransport --version=1
$(deviceC)DvUpnpOrgAVTransport2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo DvUpnpOrgAVTransport2C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(deviceC) --domain=upnp.org --type=AVTransport --version=2
$(deviceC)DvUpnpOrgConnectionManager1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo DvUpnpOrgConnectionManager1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(deviceC) --domain=upnp.org --type=ConnectionManager --version=1
$(deviceC)DvUpnpOrgConnectionManager2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo DvUpnpOrgConnectionManager2C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(deviceC) --domain=upnp.org --type=ConnectionManager --version=2
$(deviceC)DvUpnpOrgContentDirectory1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo DvUpnpOrgContentDirectory1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(deviceC) --domain=upnp.org --type=ContentDirectory --version=1
$(deviceC)DvUpnpOrgContentDirectory2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo DvUpnpOrgContentDirectory2C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(deviceC) --domain=upnp.org --type=ContentDirectory --version=2
$(deviceC)DvUpnpOrgContentDirectory3C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo DvUpnpOrgContentDirectory3C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(deviceC) --domain=upnp.org --type=ContentDirectory --version=3
$(deviceC)DvUpnpOrgRenderingControl1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo DvUpnpOrgRenderingControl1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(deviceC) --domain=upnp.org --type=RenderingControl --version=1
$(deviceC)DvUpnpOrgRenderingControl2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo DvUpnpOrgRenderingControl2C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(deviceC) --domain=upnp.org --type=RenderingControl --version=2
$(deviceC)DvUpnpOrgScheduledRecording1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo DvUpnpOrgScheduledRecording1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(deviceC) --domain=upnp.org --type=ScheduledRecording --version=1
$(deviceC)DvUpnpOrgScheduledRecording2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo DvUpnpOrgScheduledRecording2C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(deviceC) --domain=upnp.org --type=ScheduledRecording --version=2
$(deviceC)DvUpnpOrgSwitchPower1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo DvUpnpOrgSwitchPower1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(deviceC) --domain=upnp.org --type=SwitchPower --version=1
$(deviceC)DvUpnpOrgDimming1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo DvUpnpOrgDimming1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(deviceC) --domain=upnp.org --type=Dimming --version=1
$(deviceC)DvAvOpenhomeOrgInfo1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/OpenHome/Info1.xml
	echo DvAvOpenhomeOrgInfo1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/OpenHome/Info1.xml" --output=$(deviceC) --domain=av.openhome.org --type=Info --version=1
$(deviceC)DvAvOpenhomeOrgTime1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/OpenHome/Time1.xml
	echo DvAvOpenhomeOrgTime1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/OpenHome/Time1.xml" --output=$(deviceC) --domain=av.openhome.org --type=Time --version=1
$(deviceC)DvAvOpenhomeOrgPlaylist1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/OpenHome/Playlist1.xml
	echo DvAvOpenhomeOrgPlaylist1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/OpenHome/Playlist1.xml" --output=$(deviceC) --domain=av.openhome.org --type=Playlist --version=1
$(deviceC)DvAvOpenhomeOrgVolume1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/OpenHome/Volume1.xml
	echo DvAvOpenhomeOrgVolume1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/OpenHome/Volume1.xml" --output=$(deviceC) --domain=av.openhome.org --type=Volume --version=1
$(deviceC)DvAvOpenhomeOrgProduct1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/OpenHome/Product1.xml
	echo DvAvOpenhomeOrgProduct1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/OpenHome/Product1.xml" --output=$(deviceC) --domain=av.openhome.org --type=Product --version=1
$(deviceC)DvAvOpenhomeOrgRadio1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/OpenHome/Radio1.xml
	echo DvAvOpenhomeOrgRadio1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/OpenHome/Radio1.xml" --output=$(deviceC) --domain=av.openhome.org --type=Radio --version=1
$(deviceC)DvOpenhomeOrgOhNet1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/OpenHome/OhNet1.xml
	echo DvOpenhomeOrgOhNet1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/OpenHome/OhNet1.xml" --output=$(deviceC) --domain=openhome.org --type=OhNet --version=1
$(deviceC)DvZappOrgTestBasic1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo DvZappOrgTestBasic1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(deviceC) --domain=zapp.org --type=TestBasic --version=1
$(deviceC)DvZappOrgTestLights1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo DvZappOrgTestLights1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(deviceC) --domain=zapp.org --type=TestLights --version=1
$(deviceC)DvZappOrgTestDimmableLight1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo DvZappOrgTestDimmableLight1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(deviceC) --domain=zapp.org --type=TestDimmableLight --version=1

DvCs:   $(deviceCs)DvUpnpOrgAVTransport1.cs $(deviceCs)DvUpnpOrgAVTransport2.cs $(deviceCs)DvUpnpOrgConnectionManager1.cs $(deviceCs)DvUpnpOrgConnectionManager2.cs $(deviceCs)DvUpnpOrgContentDirectory1.cs $(deviceCs)DvUpnpOrgContentDirectory2.cs $(deviceCs)DvUpnpOrgContentDirectory3.cs $(deviceCs)DvUpnpOrgRenderingControl1.cs $(deviceCs)DvUpnpOrgRenderingControl2.cs $(deviceCs)DvUpnpOrgScheduledRecording1.cs $(deviceCs)DvUpnpOrgScheduledRecording2.cs $(deviceCs)DvUpnpOrgSwitchPower1.cs $(deviceCs)DvUpnpOrgDimming1.cs $(deviceCs)DvAvOpenhomeOrgInfo1.cs $(deviceCs)DvAvOpenhomeOrgTime1.cs $(deviceCs)DvAvOpenhomeOrgPlaylist1.cs $(deviceCs)DvAvOpenhomeOrgVolume1.cs $(deviceCs)DvAvOpenhomeOrgProduct1.cs $(deviceCs)DvAvOpenhomeOrgRadio1.cs $(deviceCs)DvOpenhomeOrgOhNet1.cs $(deviceCs)DvZappOrgTestBasic1.cs $(deviceCs)DvZappOrgTestLights1.cs $(deviceCs)DvZappOrgTestDimmableLight1.cs
$(deviceCs)DvUpnpOrgAVTransport1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo DvUpnpOrgAVTransport1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(deviceCs) --domain=upnp.org --type=AVTransport --version=1
$(deviceCs)DvUpnpOrgAVTransport2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo DvUpnpOrgAVTransport2.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(deviceCs) --domain=upnp.org --type=AVTransport --version=2
$(deviceCs)DvUpnpOrgConnectionManager1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo DvUpnpOrgConnectionManager1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(deviceCs) --domain=upnp.org --type=ConnectionManager --version=1
$(deviceCs)DvUpnpOrgConnectionManager2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo DvUpnpOrgConnectionManager2.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(deviceCs) --domain=upnp.org --type=ConnectionManager --version=2
$(deviceCs)DvUpnpOrgContentDirectory1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo DvUpnpOrgContentDirectory1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(deviceCs) --domain=upnp.org --type=ContentDirectory --version=1
$(deviceCs)DvUpnpOrgContentDirectory2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo DvUpnpOrgContentDirectory2.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(deviceCs) --domain=upnp.org --type=ContentDirectory --version=2
$(deviceCs)DvUpnpOrgContentDirectory3.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo DvUpnpOrgContentDirectory3.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(deviceCs) --domain=upnp.org --type=ContentDirectory --version=3
$(deviceCs)DvUpnpOrgRenderingControl1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo DvUpnpOrgRenderingControl1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(deviceCs) --domain=upnp.org --type=RenderingControl --version=1
$(deviceCs)DvUpnpOrgRenderingControl2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo DvUpnpOrgRenderingControl2.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(deviceCs) --domain=upnp.org --type=RenderingControl --version=2
$(deviceCs)DvUpnpOrgScheduledRecording1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo DvUpnpOrgScheduledRecording1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(deviceCs) --domain=upnp.org --type=ScheduledRecording --version=1
$(deviceCs)DvUpnpOrgScheduledRecording2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo DvUpnpOrgScheduledRecording2.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(deviceCs) --domain=upnp.org --type=ScheduledRecording --version=2
$(deviceCs)DvUpnpOrgSwitchPower1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo DvUpnpOrgSwitchPower1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(deviceCs) --domain=upnp.org --type=SwitchPower --version=1
$(deviceCs)DvUpnpOrgDimming1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo DvUpnpOrgDimming1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(deviceCs) --domain=upnp.org --type=Dimming --version=1
$(deviceCs)DvAvOpenhomeOrgInfo1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/OpenHome/Info1.xml
	echo DvAvOpenhomeOrgInfo1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/OpenHome/Info1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=Info --version=1
$(deviceCs)DvAvOpenhomeOrgTime1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/OpenHome/Time1.xml
	echo DvAvOpenhomeOrgTime1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/OpenHome/Time1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=Time --version=1
$(deviceCs)DvAvOpenhomeOrgPlaylist1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/OpenHome/Playlist1.xml
	echo DvAvOpenhomeOrgPlaylist1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/OpenHome/Playlist1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=Playlist --version=1
$(deviceCs)DvAvOpenhomeOrgVolume1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/OpenHome/Volume1.xml
	echo DvAvOpenhomeOrgVolume1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/OpenHome/Volume1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=Volume --version=1
$(deviceCs)DvAvOpenhomeOrgProduct1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/OpenHome/Product1.xml
	echo DvAvOpenhomeOrgProduct1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/OpenHome/Product1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=Product --version=1
$(deviceCs)DvAvOpenhomeOrgRadio1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/OpenHome/Radio1.xml
	echo DvAvOpenhomeOrgRadio1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/OpenHome/Radio1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=Radio --version=1
$(deviceCs)DvOpenhomeOrgOhNet1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/OpenHome/OhNet1.xml
	echo DvOpenhomeOrgOhNet1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/OpenHome/OhNet1.xml" --output=$(deviceCs) --domain=openhome.org --type=OhNet --version=1
$(deviceCs)DvZappOrgTestBasic1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo DvZappOrgTestBasic1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(deviceCs) --domain=zapp.org --type=TestBasic --version=1
$(deviceCs)DvZappOrgTestLights1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo DvZappOrgTestLights1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(deviceCs) --domain=zapp.org --type=TestLights --version=1
$(deviceCs)DvZappOrgTestDimmableLight1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo DvZappOrgTestDimmableLight1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(deviceCs) --domain=zapp.org --type=TestDimmableLight --version=1

