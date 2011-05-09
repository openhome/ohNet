# Auto-generated file.  DO NOT EDIT DIRECTLY
# Update CpUpnpMakeT4.tt and run 
#    make generate-makefiles
# to apply any updates

GenAll: AllCp AllDv

AllCp: CpCppCore CpCppStd CpC CpCs CpJs

AllDv: DvCppCore DvCppStd DvC DvCs


CpCppCore:   $(proxyCppCore)CpUpnpOrgAVTransport1.cpp $(proxyCppCore)CpUpnpOrgAVTransport2.cpp $(proxyCppCore)CpUpnpOrgConnectionManager1.cpp $(proxyCppCore)CpUpnpOrgConnectionManager2.cpp $(proxyCppCore)CpUpnpOrgContentDirectory1.cpp $(proxyCppCore)CpUpnpOrgContentDirectory2.cpp $(proxyCppCore)CpUpnpOrgContentDirectory3.cpp $(proxyCppCore)CpUpnpOrgRenderingControl1.cpp $(proxyCppCore)CpUpnpOrgRenderingControl2.cpp $(proxyCppCore)CpUpnpOrgScheduledRecording1.cpp $(proxyCppCore)CpUpnpOrgScheduledRecording2.cpp $(proxyCppCore)CpUpnpOrgSwitchPower1.cpp $(proxyCppCore)CpUpnpOrgDimming1.cpp $(proxyCppCore)CpLinnCoUkComponent1.cpp $(proxyCppCore)CpLinnCoUkConfiguration1.cpp $(proxyCppCore)CpLinnCoUkDebug2.cpp $(proxyCppCore)CpLinnCoUkDelay1.cpp $(proxyCppCore)CpLinnCoUkDiagnostics1.cpp $(proxyCppCore)CpLinnCoUkDs1.cpp $(proxyCppCore)CpLinnCoUkInfo1.cpp $(proxyCppCore)CpLinnCoUkJukebox1.cpp $(proxyCppCore)CpLinnCoUkMediaTime1.cpp $(proxyCppCore)CpLinnCoUkPlaylist1.cpp $(proxyCppCore)CpLinnCoUkPreamp4.cpp $(proxyCppCore)CpLinnCoUkProduct1.cpp $(proxyCppCore)CpLinnCoUkProduct2.cpp $(proxyCppCore)CpLinnCoUkProduct3.cpp $(proxyCppCore)CpLinnCoUkProxyManager1.cpp $(proxyCppCore)CpLinnCoUkPtest1.cpp $(proxyCppCore)CpLinnCoUkRadio1.cpp $(proxyCppCore)CpLinnCoUkTime1.cpp $(proxyCppCore)CpLinnCoUkUi2.cpp $(proxyCppCore)CpLinnCoUkVolkano1.cpp $(proxyCppCore)CpZappOrgTestBasic1.cpp $(proxyCppCore)CpZappOrgTestLights1.cpp $(proxyCppCore)CpZappOrgTestDimmableLight1.cpp $(proxyCppCore)CpOpenhomeOrgTestColorLight1.cpp $(proxyCppCore)CpOpenhomeOrgOhNet1.cpp
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
$(proxyCppCore)CpLinnCoUkComponent1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Component1.xml
	echo CpLinnCoUkComponent1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Component1.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Component --version=1
$(proxyCppCore)CpLinnCoUkConfiguration1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Configuration1.xml
	echo CpLinnCoUkConfiguration1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Configuration1.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Configuration --version=1
$(proxyCppCore)CpLinnCoUkDebug2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Debug2.xml
	echo CpLinnCoUkDebug2.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Debug2.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Debug --version=2
$(proxyCppCore)CpLinnCoUkDelay1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Delay1.xml
	echo CpLinnCoUkDelay1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Delay1.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Delay --version=1
$(proxyCppCore)CpLinnCoUkDiagnostics1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Diagnostics1.xml
	echo CpLinnCoUkDiagnostics1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Diagnostics1.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Diagnostics --version=1
$(proxyCppCore)CpLinnCoUkDs1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Ds1.xml
	echo CpLinnCoUkDs1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Ds1.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Ds --version=1
$(proxyCppCore)CpLinnCoUkInfo1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Info1.xml
	echo CpLinnCoUkInfo1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Info1.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Info --version=1
$(proxyCppCore)CpLinnCoUkJukebox1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Jukebox1.xml
	echo CpLinnCoUkJukebox1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Jukebox1.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Jukebox --version=1
$(proxyCppCore)CpLinnCoUkMediaTime1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/MediaTime1.xml
	echo CpLinnCoUkMediaTime1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/MediaTime1.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=MediaTime --version=1
$(proxyCppCore)CpLinnCoUkPlaylist1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Playlist1.xml
	echo CpLinnCoUkPlaylist1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Playlist1.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Playlist --version=1
$(proxyCppCore)CpLinnCoUkPreamp4.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Preamp4.xml
	echo CpLinnCoUkPreamp4.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Preamp4.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Preamp --version=4
$(proxyCppCore)CpLinnCoUkProduct1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Product1.xml
	echo CpLinnCoUkProduct1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Product1.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Product --version=1
$(proxyCppCore)CpLinnCoUkProduct2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Product2.xml
	echo CpLinnCoUkProduct2.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Product2.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Product --version=2
$(proxyCppCore)CpLinnCoUkProduct3.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Product3.xml
	echo CpLinnCoUkProduct3.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Product3.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Product --version=3
$(proxyCppCore)CpLinnCoUkProxyManager1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/ProxyManager1.xml
	echo CpLinnCoUkProxyManager1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/ProxyManager1.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=ProxyManager --version=1
$(proxyCppCore)CpLinnCoUkPtest1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Ptest1.xml
	echo CpLinnCoUkPtest1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Ptest1.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Ptest --version=1
$(proxyCppCore)CpLinnCoUkRadio1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Radio1.xml
	echo CpLinnCoUkRadio1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Radio1.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Radio --version=1
$(proxyCppCore)CpLinnCoUkTime1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Time1.xml
	echo CpLinnCoUkTime1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Time1.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Time --version=1
$(proxyCppCore)CpLinnCoUkUi2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Ui2.xml
	echo CpLinnCoUkUi2.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Ui2.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Ui --version=2
$(proxyCppCore)CpLinnCoUkVolkano1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Volkano1.xml
	echo CpLinnCoUkVolkano1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Linn/Volkano1.xml" --output=$(proxyCppCore) --domain=linn.co.uk --type=Volkano --version=1
$(proxyCppCore)CpZappOrgTestBasic1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo CpZappOrgTestBasic1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(proxyCppCore) --domain=zapp.org --type=TestBasic --version=1
$(proxyCppCore)CpZappOrgTestLights1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo CpZappOrgTestLights1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(proxyCppCore) --domain=zapp.org --type=TestLights --version=1
$(proxyCppCore)CpZappOrgTestDimmableLight1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo CpZappOrgTestDimmableLight1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(proxyCppCore) --domain=zapp.org --type=TestDimmableLight --version=1
$(proxyCppCore)CpOpenhomeOrgTestColorLight1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Openhome/Test/TestColorLight1.xml
	echo CpOpenhomeOrgTestColorLight1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Openhome/Test/TestColorLight1.xml" --output=$(proxyCppCore) --domain=openhome.org --type=TestColorLight --version=1
$(proxyCppCore)CpOpenhomeOrgOhNet1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Openhome/OhNet1.xml
	echo CpOpenhomeOrgOhNet1.cpp
	$(zappgen) --language=cppcore --stack=cp "--xml=Service/Upnp/Openhome/OhNet1.xml" --output=$(proxyCppCore) --domain=openhome.org --type=OhNet --version=1

CpCppStd:   $(proxyCppStd)CpUpnpOrgAVTransport1Std.cpp $(proxyCppStd)CpUpnpOrgAVTransport2Std.cpp $(proxyCppStd)CpUpnpOrgConnectionManager1Std.cpp $(proxyCppStd)CpUpnpOrgConnectionManager2Std.cpp $(proxyCppStd)CpUpnpOrgContentDirectory1Std.cpp $(proxyCppStd)CpUpnpOrgContentDirectory2Std.cpp $(proxyCppStd)CpUpnpOrgContentDirectory3Std.cpp $(proxyCppStd)CpUpnpOrgRenderingControl1Std.cpp $(proxyCppStd)CpUpnpOrgRenderingControl2Std.cpp $(proxyCppStd)CpUpnpOrgScheduledRecording1Std.cpp $(proxyCppStd)CpUpnpOrgScheduledRecording2Std.cpp $(proxyCppStd)CpUpnpOrgSwitchPower1Std.cpp $(proxyCppStd)CpUpnpOrgDimming1Std.cpp $(proxyCppStd)CpLinnCoUkComponent1Std.cpp $(proxyCppStd)CpLinnCoUkConfiguration1Std.cpp $(proxyCppStd)CpLinnCoUkDebug2Std.cpp $(proxyCppStd)CpLinnCoUkDelay1Std.cpp $(proxyCppStd)CpLinnCoUkDiagnostics1Std.cpp $(proxyCppStd)CpLinnCoUkDs1Std.cpp $(proxyCppStd)CpLinnCoUkInfo1Std.cpp $(proxyCppStd)CpLinnCoUkJukebox1Std.cpp $(proxyCppStd)CpLinnCoUkMediaTime1Std.cpp $(proxyCppStd)CpLinnCoUkPlaylist1Std.cpp $(proxyCppStd)CpLinnCoUkPreamp4Std.cpp $(proxyCppStd)CpLinnCoUkProduct1Std.cpp $(proxyCppStd)CpLinnCoUkProduct2Std.cpp $(proxyCppStd)CpLinnCoUkProduct3Std.cpp $(proxyCppStd)CpLinnCoUkProxyManager1Std.cpp $(proxyCppStd)CpLinnCoUkPtest1Std.cpp $(proxyCppStd)CpLinnCoUkRadio1Std.cpp $(proxyCppStd)CpLinnCoUkTime1Std.cpp $(proxyCppStd)CpLinnCoUkUi2Std.cpp $(proxyCppStd)CpLinnCoUkVolkano1Std.cpp $(proxyCppStd)CpZappOrgTestBasic1Std.cpp $(proxyCppStd)CpZappOrgTestLights1Std.cpp $(proxyCppStd)CpZappOrgTestDimmableLight1Std.cpp $(proxyCppStd)CpOpenhomeOrgTestColorLight1Std.cpp $(proxyCppStd)CpOpenhomeOrgOhNet1Std.cpp
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
$(proxyCppStd)CpLinnCoUkComponent1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Component1.xml
	echo CpLinnCoUkComponent1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Component1.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Component --version=1
$(proxyCppStd)CpLinnCoUkConfiguration1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Configuration1.xml
	echo CpLinnCoUkConfiguration1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Configuration1.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Configuration --version=1
$(proxyCppStd)CpLinnCoUkDebug2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Debug2.xml
	echo CpLinnCoUkDebug2Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Debug2.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Debug --version=2
$(proxyCppStd)CpLinnCoUkDelay1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Delay1.xml
	echo CpLinnCoUkDelay1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Delay1.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Delay --version=1
$(proxyCppStd)CpLinnCoUkDiagnostics1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Diagnostics1.xml
	echo CpLinnCoUkDiagnostics1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Diagnostics1.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Diagnostics --version=1
$(proxyCppStd)CpLinnCoUkDs1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Ds1.xml
	echo CpLinnCoUkDs1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Ds1.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Ds --version=1
$(proxyCppStd)CpLinnCoUkInfo1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Info1.xml
	echo CpLinnCoUkInfo1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Info1.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Info --version=1
$(proxyCppStd)CpLinnCoUkJukebox1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Jukebox1.xml
	echo CpLinnCoUkJukebox1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Jukebox1.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Jukebox --version=1
$(proxyCppStd)CpLinnCoUkMediaTime1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/MediaTime1.xml
	echo CpLinnCoUkMediaTime1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/MediaTime1.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=MediaTime --version=1
$(proxyCppStd)CpLinnCoUkPlaylist1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Playlist1.xml
	echo CpLinnCoUkPlaylist1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Playlist1.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Playlist --version=1
$(proxyCppStd)CpLinnCoUkPreamp4Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Preamp4.xml
	echo CpLinnCoUkPreamp4Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Preamp4.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Preamp --version=4
$(proxyCppStd)CpLinnCoUkProduct1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Product1.xml
	echo CpLinnCoUkProduct1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Product1.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Product --version=1
$(proxyCppStd)CpLinnCoUkProduct2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Product2.xml
	echo CpLinnCoUkProduct2Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Product2.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Product --version=2
$(proxyCppStd)CpLinnCoUkProduct3Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Product3.xml
	echo CpLinnCoUkProduct3Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Product3.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Product --version=3
$(proxyCppStd)CpLinnCoUkProxyManager1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/ProxyManager1.xml
	echo CpLinnCoUkProxyManager1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/ProxyManager1.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=ProxyManager --version=1
$(proxyCppStd)CpLinnCoUkPtest1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Ptest1.xml
	echo CpLinnCoUkPtest1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Ptest1.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Ptest --version=1
$(proxyCppStd)CpLinnCoUkRadio1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Radio1.xml
	echo CpLinnCoUkRadio1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Radio1.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Radio --version=1
$(proxyCppStd)CpLinnCoUkTime1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Time1.xml
	echo CpLinnCoUkTime1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Time1.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Time --version=1
$(proxyCppStd)CpLinnCoUkUi2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Ui2.xml
	echo CpLinnCoUkUi2Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Ui2.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Ui --version=2
$(proxyCppStd)CpLinnCoUkVolkano1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Volkano1.xml
	echo CpLinnCoUkVolkano1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Linn/Volkano1.xml" --output=$(proxyCppStd) --domain=linn.co.uk --type=Volkano --version=1
$(proxyCppStd)CpZappOrgTestBasic1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo CpZappOrgTestBasic1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(proxyCppStd) --domain=zapp.org --type=TestBasic --version=1
$(proxyCppStd)CpZappOrgTestLights1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo CpZappOrgTestLights1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(proxyCppStd) --domain=zapp.org --type=TestLights --version=1
$(proxyCppStd)CpZappOrgTestDimmableLight1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo CpZappOrgTestDimmableLight1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(proxyCppStd) --domain=zapp.org --type=TestDimmableLight --version=1
$(proxyCppStd)CpOpenhomeOrgTestColorLight1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Openhome/Test/TestColorLight1.xml
	echo CpOpenhomeOrgTestColorLight1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Openhome/Test/TestColorLight1.xml" --output=$(proxyCppStd) --domain=openhome.org --type=TestColorLight --version=1
$(proxyCppStd)CpOpenhomeOrgOhNet1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Openhome/OhNet1.xml
	echo CpOpenhomeOrgOhNet1Std.cpp
	$(zappgen) --language=cpp --stack=cp "--xml=Service/Upnp/Openhome/OhNet1.xml" --output=$(proxyCppStd) --domain=openhome.org --type=OhNet --version=1

CpC:   $(proxyC)CpUpnpOrgAVTransport1C.cpp $(proxyC)CpUpnpOrgAVTransport2C.cpp $(proxyC)CpUpnpOrgConnectionManager1C.cpp $(proxyC)CpUpnpOrgConnectionManager2C.cpp $(proxyC)CpUpnpOrgContentDirectory1C.cpp $(proxyC)CpUpnpOrgContentDirectory2C.cpp $(proxyC)CpUpnpOrgContentDirectory3C.cpp $(proxyC)CpUpnpOrgRenderingControl1C.cpp $(proxyC)CpUpnpOrgRenderingControl2C.cpp $(proxyC)CpUpnpOrgScheduledRecording1C.cpp $(proxyC)CpUpnpOrgScheduledRecording2C.cpp $(proxyC)CpUpnpOrgSwitchPower1C.cpp $(proxyC)CpUpnpOrgDimming1C.cpp $(proxyC)CpLinnCoUkComponent1C.cpp $(proxyC)CpLinnCoUkConfiguration1C.cpp $(proxyC)CpLinnCoUkDebug2C.cpp $(proxyC)CpLinnCoUkDelay1C.cpp $(proxyC)CpLinnCoUkDiagnostics1C.cpp $(proxyC)CpLinnCoUkDs1C.cpp $(proxyC)CpLinnCoUkInfo1C.cpp $(proxyC)CpLinnCoUkJukebox1C.cpp $(proxyC)CpLinnCoUkMediaTime1C.cpp $(proxyC)CpLinnCoUkPlaylist1C.cpp $(proxyC)CpLinnCoUkPreamp4C.cpp $(proxyC)CpLinnCoUkProduct1C.cpp $(proxyC)CpLinnCoUkProduct2C.cpp $(proxyC)CpLinnCoUkProduct3C.cpp $(proxyC)CpLinnCoUkProxyManager1C.cpp $(proxyC)CpLinnCoUkPtest1C.cpp $(proxyC)CpLinnCoUkRadio1C.cpp $(proxyC)CpLinnCoUkTime1C.cpp $(proxyC)CpLinnCoUkUi2C.cpp $(proxyC)CpLinnCoUkVolkano1C.cpp $(proxyC)CpZappOrgTestBasic1C.cpp $(proxyC)CpZappOrgTestLights1C.cpp $(proxyC)CpZappOrgTestDimmableLight1C.cpp $(proxyC)CpOpenhomeOrgTestColorLight1C.cpp $(proxyC)CpOpenhomeOrgOhNet1C.cpp
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
$(proxyC)CpLinnCoUkComponent1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Component1.xml
	echo CpLinnCoUkComponent1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Component1.xml" --output=$(proxyC) --domain=linn.co.uk --type=Component --version=1
$(proxyC)CpLinnCoUkConfiguration1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Configuration1.xml
	echo CpLinnCoUkConfiguration1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Configuration1.xml" --output=$(proxyC) --domain=linn.co.uk --type=Configuration --version=1
$(proxyC)CpLinnCoUkDebug2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Debug2.xml
	echo CpLinnCoUkDebug2C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Debug2.xml" --output=$(proxyC) --domain=linn.co.uk --type=Debug --version=2
$(proxyC)CpLinnCoUkDelay1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Delay1.xml
	echo CpLinnCoUkDelay1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Delay1.xml" --output=$(proxyC) --domain=linn.co.uk --type=Delay --version=1
$(proxyC)CpLinnCoUkDiagnostics1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Diagnostics1.xml
	echo CpLinnCoUkDiagnostics1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Diagnostics1.xml" --output=$(proxyC) --domain=linn.co.uk --type=Diagnostics --version=1
$(proxyC)CpLinnCoUkDs1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Ds1.xml
	echo CpLinnCoUkDs1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Ds1.xml" --output=$(proxyC) --domain=linn.co.uk --type=Ds --version=1
$(proxyC)CpLinnCoUkInfo1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Info1.xml
	echo CpLinnCoUkInfo1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Info1.xml" --output=$(proxyC) --domain=linn.co.uk --type=Info --version=1
$(proxyC)CpLinnCoUkJukebox1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Jukebox1.xml
	echo CpLinnCoUkJukebox1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Jukebox1.xml" --output=$(proxyC) --domain=linn.co.uk --type=Jukebox --version=1
$(proxyC)CpLinnCoUkMediaTime1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/MediaTime1.xml
	echo CpLinnCoUkMediaTime1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/MediaTime1.xml" --output=$(proxyC) --domain=linn.co.uk --type=MediaTime --version=1
$(proxyC)CpLinnCoUkPlaylist1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Playlist1.xml
	echo CpLinnCoUkPlaylist1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Playlist1.xml" --output=$(proxyC) --domain=linn.co.uk --type=Playlist --version=1
$(proxyC)CpLinnCoUkPreamp4C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Preamp4.xml
	echo CpLinnCoUkPreamp4C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Preamp4.xml" --output=$(proxyC) --domain=linn.co.uk --type=Preamp --version=4
$(proxyC)CpLinnCoUkProduct1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Product1.xml
	echo CpLinnCoUkProduct1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Product1.xml" --output=$(proxyC) --domain=linn.co.uk --type=Product --version=1
$(proxyC)CpLinnCoUkProduct2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Product2.xml
	echo CpLinnCoUkProduct2C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Product2.xml" --output=$(proxyC) --domain=linn.co.uk --type=Product --version=2
$(proxyC)CpLinnCoUkProduct3C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Product3.xml
	echo CpLinnCoUkProduct3C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Product3.xml" --output=$(proxyC) --domain=linn.co.uk --type=Product --version=3
$(proxyC)CpLinnCoUkProxyManager1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/ProxyManager1.xml
	echo CpLinnCoUkProxyManager1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/ProxyManager1.xml" --output=$(proxyC) --domain=linn.co.uk --type=ProxyManager --version=1
$(proxyC)CpLinnCoUkPtest1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Ptest1.xml
	echo CpLinnCoUkPtest1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Ptest1.xml" --output=$(proxyC) --domain=linn.co.uk --type=Ptest --version=1
$(proxyC)CpLinnCoUkRadio1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Radio1.xml
	echo CpLinnCoUkRadio1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Radio1.xml" --output=$(proxyC) --domain=linn.co.uk --type=Radio --version=1
$(proxyC)CpLinnCoUkTime1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Time1.xml
	echo CpLinnCoUkTime1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Time1.xml" --output=$(proxyC) --domain=linn.co.uk --type=Time --version=1
$(proxyC)CpLinnCoUkUi2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Ui2.xml
	echo CpLinnCoUkUi2C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Ui2.xml" --output=$(proxyC) --domain=linn.co.uk --type=Ui --version=2
$(proxyC)CpLinnCoUkVolkano1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Volkano1.xml
	echo CpLinnCoUkVolkano1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Linn/Volkano1.xml" --output=$(proxyC) --domain=linn.co.uk --type=Volkano --version=1
$(proxyC)CpZappOrgTestBasic1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo CpZappOrgTestBasic1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(proxyC) --domain=zapp.org --type=TestBasic --version=1
$(proxyC)CpZappOrgTestLights1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo CpZappOrgTestLights1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(proxyC) --domain=zapp.org --type=TestLights --version=1
$(proxyC)CpZappOrgTestDimmableLight1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo CpZappOrgTestDimmableLight1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(proxyC) --domain=zapp.org --type=TestDimmableLight --version=1
$(proxyC)CpOpenhomeOrgTestColorLight1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Openhome/Test/TestColorLight1.xml
	echo CpOpenhomeOrgTestColorLight1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Openhome/Test/TestColorLight1.xml" --output=$(proxyC) --domain=openhome.org --type=TestColorLight --version=1
$(proxyC)CpOpenhomeOrgOhNet1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt T4/Templates/CpUpnpCHeader.tt Service/Upnp/Openhome/OhNet1.xml
	echo CpOpenhomeOrgOhNet1C.cpp
	$(zappgen) --language=c --stack=cp "--xml=Service/Upnp/Openhome/OhNet1.xml" --output=$(proxyC) --domain=openhome.org --type=OhNet --version=1

CpCs:   $(proxyCs)CpUpnpOrgAVTransport1.cs $(proxyCs)CpUpnpOrgAVTransport2.cs $(proxyCs)CpUpnpOrgConnectionManager1.cs $(proxyCs)CpUpnpOrgConnectionManager2.cs $(proxyCs)CpUpnpOrgContentDirectory1.cs $(proxyCs)CpUpnpOrgContentDirectory2.cs $(proxyCs)CpUpnpOrgContentDirectory3.cs $(proxyCs)CpUpnpOrgRenderingControl1.cs $(proxyCs)CpUpnpOrgRenderingControl2.cs $(proxyCs)CpUpnpOrgScheduledRecording1.cs $(proxyCs)CpUpnpOrgScheduledRecording2.cs $(proxyCs)CpUpnpOrgSwitchPower1.cs $(proxyCs)CpUpnpOrgDimming1.cs $(proxyCs)CpLinnCoUkComponent1.cs $(proxyCs)CpLinnCoUkConfiguration1.cs $(proxyCs)CpLinnCoUkDebug2.cs $(proxyCs)CpLinnCoUkDelay1.cs $(proxyCs)CpLinnCoUkDiagnostics1.cs $(proxyCs)CpLinnCoUkDs1.cs $(proxyCs)CpLinnCoUkInfo1.cs $(proxyCs)CpLinnCoUkJukebox1.cs $(proxyCs)CpLinnCoUkMediaTime1.cs $(proxyCs)CpLinnCoUkPlaylist1.cs $(proxyCs)CpLinnCoUkPreamp4.cs $(proxyCs)CpLinnCoUkProduct1.cs $(proxyCs)CpLinnCoUkProduct2.cs $(proxyCs)CpLinnCoUkProduct3.cs $(proxyCs)CpLinnCoUkProxyManager1.cs $(proxyCs)CpLinnCoUkPtest1.cs $(proxyCs)CpLinnCoUkRadio1.cs $(proxyCs)CpLinnCoUkTime1.cs $(proxyCs)CpLinnCoUkUi2.cs $(proxyCs)CpLinnCoUkVolkano1.cs $(proxyCs)CpZappOrgTestBasic1.cs $(proxyCs)CpZappOrgTestLights1.cs $(proxyCs)CpZappOrgTestDimmableLight1.cs $(proxyCs)CpOpenhomeOrgTestColorLight1.cs $(proxyCs)CpOpenhomeOrgOhNet1.cs
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
$(proxyCs)CpLinnCoUkComponent1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Component1.xml
	echo CpLinnCoUkComponent1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Component1.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Component --version=1
$(proxyCs)CpLinnCoUkConfiguration1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Configuration1.xml
	echo CpLinnCoUkConfiguration1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Configuration1.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Configuration --version=1
$(proxyCs)CpLinnCoUkDebug2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Debug2.xml
	echo CpLinnCoUkDebug2.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Debug2.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Debug --version=2
$(proxyCs)CpLinnCoUkDelay1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Delay1.xml
	echo CpLinnCoUkDelay1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Delay1.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Delay --version=1
$(proxyCs)CpLinnCoUkDiagnostics1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Diagnostics1.xml
	echo CpLinnCoUkDiagnostics1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Diagnostics1.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Diagnostics --version=1
$(proxyCs)CpLinnCoUkDs1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Ds1.xml
	echo CpLinnCoUkDs1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Ds1.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Ds --version=1
$(proxyCs)CpLinnCoUkInfo1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Info1.xml
	echo CpLinnCoUkInfo1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Info1.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Info --version=1
$(proxyCs)CpLinnCoUkJukebox1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Jukebox1.xml
	echo CpLinnCoUkJukebox1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Jukebox1.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Jukebox --version=1
$(proxyCs)CpLinnCoUkMediaTime1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/MediaTime1.xml
	echo CpLinnCoUkMediaTime1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/MediaTime1.xml" --output=$(proxyCs) --domain=linn.co.uk --type=MediaTime --version=1
$(proxyCs)CpLinnCoUkPlaylist1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Playlist1.xml
	echo CpLinnCoUkPlaylist1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Playlist1.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Playlist --version=1
$(proxyCs)CpLinnCoUkPreamp4.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Preamp4.xml
	echo CpLinnCoUkPreamp4.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Preamp4.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Preamp --version=4
$(proxyCs)CpLinnCoUkProduct1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Product1.xml
	echo CpLinnCoUkProduct1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Product1.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Product --version=1
$(proxyCs)CpLinnCoUkProduct2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Product2.xml
	echo CpLinnCoUkProduct2.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Product2.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Product --version=2
$(proxyCs)CpLinnCoUkProduct3.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Product3.xml
	echo CpLinnCoUkProduct3.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Product3.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Product --version=3
$(proxyCs)CpLinnCoUkProxyManager1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/ProxyManager1.xml
	echo CpLinnCoUkProxyManager1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/ProxyManager1.xml" --output=$(proxyCs) --domain=linn.co.uk --type=ProxyManager --version=1
$(proxyCs)CpLinnCoUkPtest1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Ptest1.xml
	echo CpLinnCoUkPtest1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Ptest1.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Ptest --version=1
$(proxyCs)CpLinnCoUkRadio1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Radio1.xml
	echo CpLinnCoUkRadio1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Radio1.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Radio --version=1
$(proxyCs)CpLinnCoUkTime1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Time1.xml
	echo CpLinnCoUkTime1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Time1.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Time --version=1
$(proxyCs)CpLinnCoUkUi2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Ui2.xml
	echo CpLinnCoUkUi2.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Ui2.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Ui --version=2
$(proxyCs)CpLinnCoUkVolkano1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Volkano1.xml
	echo CpLinnCoUkVolkano1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Linn/Volkano1.xml" --output=$(proxyCs) --domain=linn.co.uk --type=Volkano --version=1
$(proxyCs)CpZappOrgTestBasic1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo CpZappOrgTestBasic1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(proxyCs) --domain=zapp.org --type=TestBasic --version=1
$(proxyCs)CpZappOrgTestLights1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo CpZappOrgTestLights1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(proxyCs) --domain=zapp.org --type=TestLights --version=1
$(proxyCs)CpZappOrgTestDimmableLight1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo CpZappOrgTestDimmableLight1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(proxyCs) --domain=zapp.org --type=TestDimmableLight --version=1
$(proxyCs)CpOpenhomeOrgTestColorLight1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Openhome/Test/TestColorLight1.xml
	echo CpOpenhomeOrgTestColorLight1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Openhome/Test/TestColorLight1.xml" --output=$(proxyCs) --domain=openhome.org --type=TestColorLight --version=1
$(proxyCs)CpOpenhomeOrgOhNet1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Openhome/OhNet1.xml
	echo CpOpenhomeOrgOhNet1.cs
	$(zappgen) --language=cs --stack=cp "--xml=Service/Upnp/Openhome/OhNet1.xml" --output=$(proxyCs) --domain=openhome.org --type=OhNet --version=1

CpJs:   $(proxyJs)CpUpnpOrgAVTransport1.js $(proxyJs)CpUpnpOrgAVTransport2.js $(proxyJs)CpUpnpOrgConnectionManager1.js $(proxyJs)CpUpnpOrgConnectionManager2.js $(proxyJs)CpUpnpOrgContentDirectory1.js $(proxyJs)CpUpnpOrgContentDirectory2.js $(proxyJs)CpUpnpOrgContentDirectory3.js $(proxyJs)CpUpnpOrgRenderingControl1.js $(proxyJs)CpUpnpOrgRenderingControl2.js $(proxyJs)CpUpnpOrgScheduledRecording1.js $(proxyJs)CpUpnpOrgScheduledRecording2.js $(proxyJs)CpUpnpOrgSwitchPower1.js $(proxyJs)CpUpnpOrgDimming1.js $(proxyJs)CpLinnCoUkComponent1.js $(proxyJs)CpLinnCoUkConfiguration1.js $(proxyJs)CpLinnCoUkDebug2.js $(proxyJs)CpLinnCoUkDelay1.js $(proxyJs)CpLinnCoUkDiagnostics1.js $(proxyJs)CpLinnCoUkDs1.js $(proxyJs)CpLinnCoUkInfo1.js $(proxyJs)CpLinnCoUkJukebox1.js $(proxyJs)CpLinnCoUkMediaTime1.js $(proxyJs)CpLinnCoUkPlaylist1.js $(proxyJs)CpLinnCoUkPreamp4.js $(proxyJs)CpLinnCoUkProduct1.js $(proxyJs)CpLinnCoUkProduct2.js $(proxyJs)CpLinnCoUkProduct3.js $(proxyJs)CpLinnCoUkProxyManager1.js $(proxyJs)CpLinnCoUkPtest1.js $(proxyJs)CpLinnCoUkRadio1.js $(proxyJs)CpLinnCoUkTime1.js $(proxyJs)CpLinnCoUkUi2.js $(proxyJs)CpLinnCoUkVolkano1.js $(proxyJs)CpZappOrgTestBasic1.js $(proxyJs)CpZappOrgTestLights1.js $(proxyJs)CpZappOrgTestDimmableLight1.js $(proxyJs)CpOpenhomeOrgTestColorLight1.js $(proxyJs)CpOpenhomeOrgOhNet1.js
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
$(proxyJs)CpLinnCoUkComponent1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Component1.xml
	echo CpLinnCoUkComponent1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Component1.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Component --version=1
$(proxyJs)CpLinnCoUkConfiguration1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Configuration1.xml
	echo CpLinnCoUkConfiguration1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Configuration1.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Configuration --version=1
$(proxyJs)CpLinnCoUkDebug2.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Debug2.xml
	echo CpLinnCoUkDebug2.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Debug2.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Debug --version=2
$(proxyJs)CpLinnCoUkDelay1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Delay1.xml
	echo CpLinnCoUkDelay1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Delay1.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Delay --version=1
$(proxyJs)CpLinnCoUkDiagnostics1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Diagnostics1.xml
	echo CpLinnCoUkDiagnostics1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Diagnostics1.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Diagnostics --version=1
$(proxyJs)CpLinnCoUkDs1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Ds1.xml
	echo CpLinnCoUkDs1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Ds1.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Ds --version=1
$(proxyJs)CpLinnCoUkInfo1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Info1.xml
	echo CpLinnCoUkInfo1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Info1.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Info --version=1
$(proxyJs)CpLinnCoUkJukebox1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Jukebox1.xml
	echo CpLinnCoUkJukebox1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Jukebox1.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Jukebox --version=1
$(proxyJs)CpLinnCoUkMediaTime1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/MediaTime1.xml
	echo CpLinnCoUkMediaTime1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/MediaTime1.xml" --output=$(proxyJs) --domain=linn.co.uk --type=MediaTime --version=1
$(proxyJs)CpLinnCoUkPlaylist1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Playlist1.xml
	echo CpLinnCoUkPlaylist1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Playlist1.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Playlist --version=1
$(proxyJs)CpLinnCoUkPreamp4.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Preamp4.xml
	echo CpLinnCoUkPreamp4.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Preamp4.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Preamp --version=4
$(proxyJs)CpLinnCoUkProduct1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Product1.xml
	echo CpLinnCoUkProduct1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Product1.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Product --version=1
$(proxyJs)CpLinnCoUkProduct2.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Product2.xml
	echo CpLinnCoUkProduct2.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Product2.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Product --version=2
$(proxyJs)CpLinnCoUkProduct3.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Product3.xml
	echo CpLinnCoUkProduct3.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Product3.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Product --version=3
$(proxyJs)CpLinnCoUkProxyManager1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/ProxyManager1.xml
	echo CpLinnCoUkProxyManager1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/ProxyManager1.xml" --output=$(proxyJs) --domain=linn.co.uk --type=ProxyManager --version=1
$(proxyJs)CpLinnCoUkPtest1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Ptest1.xml
	echo CpLinnCoUkPtest1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Ptest1.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Ptest --version=1
$(proxyJs)CpLinnCoUkRadio1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Radio1.xml
	echo CpLinnCoUkRadio1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Radio1.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Radio --version=1
$(proxyJs)CpLinnCoUkTime1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Time1.xml
	echo CpLinnCoUkTime1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Time1.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Time --version=1
$(proxyJs)CpLinnCoUkUi2.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Ui2.xml
	echo CpLinnCoUkUi2.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Ui2.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Ui --version=2
$(proxyJs)CpLinnCoUkVolkano1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Linn/Volkano1.xml
	echo CpLinnCoUkVolkano1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Linn/Volkano1.xml" --output=$(proxyJs) --domain=linn.co.uk --type=Volkano --version=1
$(proxyJs)CpZappOrgTestBasic1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo CpZappOrgTestBasic1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(proxyJs) --domain=zapp.org --type=TestBasic --version=1
$(proxyJs)CpZappOrgTestLights1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo CpZappOrgTestLights1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(proxyJs) --domain=zapp.org --type=TestLights --version=1
$(proxyJs)CpZappOrgTestDimmableLight1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo CpZappOrgTestDimmableLight1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(proxyJs) --domain=zapp.org --type=TestDimmableLight --version=1
$(proxyJs)CpOpenhomeOrgTestColorLight1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Openhome/Test/TestColorLight1.xml
	echo CpOpenhomeOrgTestColorLight1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Openhome/Test/TestColorLight1.xml" --output=$(proxyJs) --domain=openhome.org --type=TestColorLight --version=1
$(proxyJs)CpOpenhomeOrgOhNet1.js : $(tt) T4/Templates/CpUpnpJs.tt Service/Upnp/Openhome/OhNet1.xml
	echo CpOpenhomeOrgOhNet1.js
	$(zappgen) --language=js --stack=cp "--xml=Service/Upnp/Openhome/OhNet1.xml" --output=$(proxyJs) --domain=openhome.org --type=OhNet --version=1

DvCppCore :   $(deviceCppCore)DvUpnpOrgAVTransport1.cpp $(deviceCppCore)DvUpnpOrgAVTransport2.cpp $(deviceCppCore)DvUpnpOrgConnectionManager1.cpp $(deviceCppCore)DvUpnpOrgConnectionManager2.cpp $(deviceCppCore)DvUpnpOrgContentDirectory1.cpp $(deviceCppCore)DvUpnpOrgContentDirectory2.cpp $(deviceCppCore)DvUpnpOrgContentDirectory3.cpp $(deviceCppCore)DvUpnpOrgRenderingControl1.cpp $(deviceCppCore)DvUpnpOrgRenderingControl2.cpp $(deviceCppCore)DvUpnpOrgScheduledRecording1.cpp $(deviceCppCore)DvUpnpOrgScheduledRecording2.cpp $(deviceCppCore)DvUpnpOrgSwitchPower1.cpp $(deviceCppCore)DvUpnpOrgDimming1.cpp $(deviceCppCore)DvLinnCoUkComponent1.cpp $(deviceCppCore)DvLinnCoUkConfiguration1.cpp $(deviceCppCore)DvLinnCoUkDebug2.cpp $(deviceCppCore)DvLinnCoUkDelay1.cpp $(deviceCppCore)DvLinnCoUkDiagnostics1.cpp $(deviceCppCore)DvLinnCoUkDs1.cpp $(deviceCppCore)DvLinnCoUkInfo1.cpp $(deviceCppCore)DvLinnCoUkJukebox1.cpp $(deviceCppCore)DvLinnCoUkMediaTime1.cpp $(deviceCppCore)DvLinnCoUkPlaylist1.cpp $(deviceCppCore)DvLinnCoUkPreamp4.cpp $(deviceCppCore)DvLinnCoUkProduct1.cpp $(deviceCppCore)DvLinnCoUkProduct2.cpp $(deviceCppCore)DvLinnCoUkProduct3.cpp $(deviceCppCore)DvLinnCoUkProxyManager1.cpp $(deviceCppCore)DvLinnCoUkPtest1.cpp $(deviceCppCore)DvLinnCoUkRadio1.cpp $(deviceCppCore)DvLinnCoUkTime1.cpp $(deviceCppCore)DvLinnCoUkUi2.cpp $(deviceCppCore)DvLinnCoUkVolkano1.cpp $(deviceCppCore)DvZappOrgTestBasic1.cpp $(deviceCppCore)DvZappOrgTestLights1.cpp $(deviceCppCore)DvZappOrgTestDimmableLight1.cpp $(deviceCppCore)DvOpenhomeOrgTestColorLight1.cpp $(deviceCppCore)DvOpenhomeOrgOhNet1.cpp
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
$(deviceCppCore)DvLinnCoUkComponent1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Component1.xml
	echo DvLinnCoUkComponent1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Component1.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Component --version=1
$(deviceCppCore)DvLinnCoUkConfiguration1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Configuration1.xml
	echo DvLinnCoUkConfiguration1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Configuration1.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Configuration --version=1
$(deviceCppCore)DvLinnCoUkDebug2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Debug2.xml
	echo DvLinnCoUkDebug2.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Debug2.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Debug --version=2
$(deviceCppCore)DvLinnCoUkDelay1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Delay1.xml
	echo DvLinnCoUkDelay1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Delay1.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Delay --version=1
$(deviceCppCore)DvLinnCoUkDiagnostics1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Diagnostics1.xml
	echo DvLinnCoUkDiagnostics1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Diagnostics1.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Diagnostics --version=1
$(deviceCppCore)DvLinnCoUkDs1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Ds1.xml
	echo DvLinnCoUkDs1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Ds1.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Ds --version=1
$(deviceCppCore)DvLinnCoUkInfo1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Info1.xml
	echo DvLinnCoUkInfo1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Info1.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Info --version=1
$(deviceCppCore)DvLinnCoUkJukebox1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Jukebox1.xml
	echo DvLinnCoUkJukebox1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Jukebox1.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Jukebox --version=1
$(deviceCppCore)DvLinnCoUkMediaTime1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/MediaTime1.xml
	echo DvLinnCoUkMediaTime1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/MediaTime1.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=MediaTime --version=1
$(deviceCppCore)DvLinnCoUkPlaylist1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Playlist1.xml
	echo DvLinnCoUkPlaylist1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Playlist1.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Playlist --version=1
$(deviceCppCore)DvLinnCoUkPreamp4.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Preamp4.xml
	echo DvLinnCoUkPreamp4.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Preamp4.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Preamp --version=4
$(deviceCppCore)DvLinnCoUkProduct1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Product1.xml
	echo DvLinnCoUkProduct1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Product1.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Product --version=1
$(deviceCppCore)DvLinnCoUkProduct2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Product2.xml
	echo DvLinnCoUkProduct2.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Product2.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Product --version=2
$(deviceCppCore)DvLinnCoUkProduct3.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Product3.xml
	echo DvLinnCoUkProduct3.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Product3.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Product --version=3
$(deviceCppCore)DvLinnCoUkProxyManager1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/ProxyManager1.xml
	echo DvLinnCoUkProxyManager1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/ProxyManager1.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=ProxyManager --version=1
$(deviceCppCore)DvLinnCoUkPtest1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Ptest1.xml
	echo DvLinnCoUkPtest1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Ptest1.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Ptest --version=1
$(deviceCppCore)DvLinnCoUkRadio1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Radio1.xml
	echo DvLinnCoUkRadio1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Radio1.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Radio --version=1
$(deviceCppCore)DvLinnCoUkTime1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Time1.xml
	echo DvLinnCoUkTime1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Time1.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Time --version=1
$(deviceCppCore)DvLinnCoUkUi2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Ui2.xml
	echo DvLinnCoUkUi2.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Ui2.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Ui --version=2
$(deviceCppCore)DvLinnCoUkVolkano1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Volkano1.xml
	echo DvLinnCoUkVolkano1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Linn/Volkano1.xml" --output=$(deviceCppCore) --domain=linn.co.uk --type=Volkano --version=1
$(deviceCppCore)DvZappOrgTestBasic1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo DvZappOrgTestBasic1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(deviceCppCore) --domain=zapp.org --type=TestBasic --version=1
$(deviceCppCore)DvZappOrgTestLights1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo DvZappOrgTestLights1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(deviceCppCore) --domain=zapp.org --type=TestLights --version=1
$(deviceCppCore)DvZappOrgTestDimmableLight1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo DvZappOrgTestDimmableLight1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(deviceCppCore) --domain=zapp.org --type=TestDimmableLight --version=1
$(deviceCppCore)DvOpenhomeOrgTestColorLight1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Openhome/Test/TestColorLight1.xml
	echo DvOpenhomeOrgTestColorLight1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Openhome/Test/TestColorLight1.xml" --output=$(deviceCppCore) --domain=openhome.org --type=TestColorLight --version=1
$(deviceCppCore)DvOpenhomeOrgOhNet1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Openhome/OhNet1.xml
	echo DvOpenhomeOrgOhNet1.cpp
	$(zappgen) --language=cppcore --stack=dv "--xml=Service/Upnp/Openhome/OhNet1.xml" --output=$(deviceCppCore) --domain=openhome.org --type=OhNet --version=1

DvCppStd :   $(deviceCppStd)DvUpnpOrgAVTransport1Std.cpp $(deviceCppStd)DvUpnpOrgAVTransport2Std.cpp $(deviceCppStd)DvUpnpOrgConnectionManager1Std.cpp $(deviceCppStd)DvUpnpOrgConnectionManager2Std.cpp $(deviceCppStd)DvUpnpOrgContentDirectory1Std.cpp $(deviceCppStd)DvUpnpOrgContentDirectory2Std.cpp $(deviceCppStd)DvUpnpOrgContentDirectory3Std.cpp $(deviceCppStd)DvUpnpOrgRenderingControl1Std.cpp $(deviceCppStd)DvUpnpOrgRenderingControl2Std.cpp $(deviceCppStd)DvUpnpOrgScheduledRecording1Std.cpp $(deviceCppStd)DvUpnpOrgScheduledRecording2Std.cpp $(deviceCppStd)DvUpnpOrgSwitchPower1Std.cpp $(deviceCppStd)DvUpnpOrgDimming1Std.cpp $(deviceCppStd)DvLinnCoUkComponent1Std.cpp $(deviceCppStd)DvLinnCoUkConfiguration1Std.cpp $(deviceCppStd)DvLinnCoUkDebug2Std.cpp $(deviceCppStd)DvLinnCoUkDelay1Std.cpp $(deviceCppStd)DvLinnCoUkDiagnostics1Std.cpp $(deviceCppStd)DvLinnCoUkDs1Std.cpp $(deviceCppStd)DvLinnCoUkInfo1Std.cpp $(deviceCppStd)DvLinnCoUkJukebox1Std.cpp $(deviceCppStd)DvLinnCoUkMediaTime1Std.cpp $(deviceCppStd)DvLinnCoUkPlaylist1Std.cpp $(deviceCppStd)DvLinnCoUkPreamp4Std.cpp $(deviceCppStd)DvLinnCoUkProduct1Std.cpp $(deviceCppStd)DvLinnCoUkProduct2Std.cpp $(deviceCppStd)DvLinnCoUkProduct3Std.cpp $(deviceCppStd)DvLinnCoUkProxyManager1Std.cpp $(deviceCppStd)DvLinnCoUkPtest1Std.cpp $(deviceCppStd)DvLinnCoUkRadio1Std.cpp $(deviceCppStd)DvLinnCoUkTime1Std.cpp $(deviceCppStd)DvLinnCoUkUi2Std.cpp $(deviceCppStd)DvLinnCoUkVolkano1Std.cpp $(deviceCppStd)DvZappOrgTestBasic1Std.cpp $(deviceCppStd)DvZappOrgTestLights1Std.cpp $(deviceCppStd)DvZappOrgTestDimmableLight1Std.cpp $(deviceCppStd)DvOpenhomeOrgTestColorLight1Std.cpp $(deviceCppStd)DvOpenhomeOrgOhNet1Std.cpp
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
$(deviceCppStd)DvLinnCoUkComponent1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Component1.xml
	echo DvLinnCoUkComponent1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Component1.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Component --version=1
$(deviceCppStd)DvLinnCoUkConfiguration1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Configuration1.xml
	echo DvLinnCoUkConfiguration1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Configuration1.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Configuration --version=1
$(deviceCppStd)DvLinnCoUkDebug2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Debug2.xml
	echo DvLinnCoUkDebug2Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Debug2.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Debug --version=2
$(deviceCppStd)DvLinnCoUkDelay1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Delay1.xml
	echo DvLinnCoUkDelay1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Delay1.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Delay --version=1
$(deviceCppStd)DvLinnCoUkDiagnostics1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Diagnostics1.xml
	echo DvLinnCoUkDiagnostics1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Diagnostics1.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Diagnostics --version=1
$(deviceCppStd)DvLinnCoUkDs1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Ds1.xml
	echo DvLinnCoUkDs1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Ds1.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Ds --version=1
$(deviceCppStd)DvLinnCoUkInfo1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Info1.xml
	echo DvLinnCoUkInfo1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Info1.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Info --version=1
$(deviceCppStd)DvLinnCoUkJukebox1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Jukebox1.xml
	echo DvLinnCoUkJukebox1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Jukebox1.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Jukebox --version=1
$(deviceCppStd)DvLinnCoUkMediaTime1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/MediaTime1.xml
	echo DvLinnCoUkMediaTime1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/MediaTime1.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=MediaTime --version=1
$(deviceCppStd)DvLinnCoUkPlaylist1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Playlist1.xml
	echo DvLinnCoUkPlaylist1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Playlist1.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Playlist --version=1
$(deviceCppStd)DvLinnCoUkPreamp4Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Preamp4.xml
	echo DvLinnCoUkPreamp4Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Preamp4.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Preamp --version=4
$(deviceCppStd)DvLinnCoUkProduct1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Product1.xml
	echo DvLinnCoUkProduct1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Product1.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Product --version=1
$(deviceCppStd)DvLinnCoUkProduct2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Product2.xml
	echo DvLinnCoUkProduct2Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Product2.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Product --version=2
$(deviceCppStd)DvLinnCoUkProduct3Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Product3.xml
	echo DvLinnCoUkProduct3Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Product3.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Product --version=3
$(deviceCppStd)DvLinnCoUkProxyManager1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/ProxyManager1.xml
	echo DvLinnCoUkProxyManager1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/ProxyManager1.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=ProxyManager --version=1
$(deviceCppStd)DvLinnCoUkPtest1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Ptest1.xml
	echo DvLinnCoUkPtest1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Ptest1.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Ptest --version=1
$(deviceCppStd)DvLinnCoUkRadio1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Radio1.xml
	echo DvLinnCoUkRadio1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Radio1.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Radio --version=1
$(deviceCppStd)DvLinnCoUkTime1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Time1.xml
	echo DvLinnCoUkTime1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Time1.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Time --version=1
$(deviceCppStd)DvLinnCoUkUi2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Ui2.xml
	echo DvLinnCoUkUi2Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Ui2.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Ui --version=2
$(deviceCppStd)DvLinnCoUkVolkano1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Volkano1.xml
	echo DvLinnCoUkVolkano1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Linn/Volkano1.xml" --output=$(deviceCppStd) --domain=linn.co.uk --type=Volkano --version=1
$(deviceCppStd)DvZappOrgTestBasic1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo DvZappOrgTestBasic1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(deviceCppStd) --domain=zapp.org --type=TestBasic --version=1
$(deviceCppStd)DvZappOrgTestLights1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo DvZappOrgTestLights1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(deviceCppStd) --domain=zapp.org --type=TestLights --version=1
$(deviceCppStd)DvZappOrgTestDimmableLight1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo DvZappOrgTestDimmableLight1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(deviceCppStd) --domain=zapp.org --type=TestDimmableLight --version=1
$(deviceCppStd)DvOpenhomeOrgTestColorLight1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Openhome/Test/TestColorLight1.xml
	echo DvOpenhomeOrgTestColorLight1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Openhome/Test/TestColorLight1.xml" --output=$(deviceCppStd) --domain=openhome.org --type=TestColorLight --version=1
$(deviceCppStd)DvOpenhomeOrgOhNet1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Openhome/OhNet1.xml
	echo DvOpenhomeOrgOhNet1Std.cpp
	$(zappgen) --language=cpp --stack=dv "--xml=Service/Upnp/Openhome/OhNet1.xml" --output=$(deviceCppStd) --domain=openhome.org --type=OhNet --version=1

DvC :   $(deviceC)DvUpnpOrgAVTransport1C.cpp $(deviceC)DvUpnpOrgAVTransport2C.cpp $(deviceC)DvUpnpOrgConnectionManager1C.cpp $(deviceC)DvUpnpOrgConnectionManager2C.cpp $(deviceC)DvUpnpOrgContentDirectory1C.cpp $(deviceC)DvUpnpOrgContentDirectory2C.cpp $(deviceC)DvUpnpOrgContentDirectory3C.cpp $(deviceC)DvUpnpOrgRenderingControl1C.cpp $(deviceC)DvUpnpOrgRenderingControl2C.cpp $(deviceC)DvUpnpOrgScheduledRecording1C.cpp $(deviceC)DvUpnpOrgScheduledRecording2C.cpp $(deviceC)DvUpnpOrgSwitchPower1C.cpp $(deviceC)DvUpnpOrgDimming1C.cpp $(deviceC)DvLinnCoUkComponent1C.cpp $(deviceC)DvLinnCoUkConfiguration1C.cpp $(deviceC)DvLinnCoUkDebug2C.cpp $(deviceC)DvLinnCoUkDelay1C.cpp $(deviceC)DvLinnCoUkDiagnostics1C.cpp $(deviceC)DvLinnCoUkDs1C.cpp $(deviceC)DvLinnCoUkInfo1C.cpp $(deviceC)DvLinnCoUkJukebox1C.cpp $(deviceC)DvLinnCoUkMediaTime1C.cpp $(deviceC)DvLinnCoUkPlaylist1C.cpp $(deviceC)DvLinnCoUkPreamp4C.cpp $(deviceC)DvLinnCoUkProduct1C.cpp $(deviceC)DvLinnCoUkProduct2C.cpp $(deviceC)DvLinnCoUkProduct3C.cpp $(deviceC)DvLinnCoUkProxyManager1C.cpp $(deviceC)DvLinnCoUkPtest1C.cpp $(deviceC)DvLinnCoUkRadio1C.cpp $(deviceC)DvLinnCoUkTime1C.cpp $(deviceC)DvLinnCoUkUi2C.cpp $(deviceC)DvLinnCoUkVolkano1C.cpp $(deviceC)DvZappOrgTestBasic1C.cpp $(deviceC)DvZappOrgTestLights1C.cpp $(deviceC)DvZappOrgTestDimmableLight1C.cpp $(deviceC)DvOpenhomeOrgTestColorLight1C.cpp $(deviceC)DvOpenhomeOrgOhNet1C.cpp
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
$(deviceC)DvLinnCoUkComponent1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Component1.xml
	echo DvLinnCoUkComponent1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Component1.xml" --output=$(deviceC) --domain=linn.co.uk --type=Component --version=1
$(deviceC)DvLinnCoUkConfiguration1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Configuration1.xml
	echo DvLinnCoUkConfiguration1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Configuration1.xml" --output=$(deviceC) --domain=linn.co.uk --type=Configuration --version=1
$(deviceC)DvLinnCoUkDebug2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Debug2.xml
	echo DvLinnCoUkDebug2C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Debug2.xml" --output=$(deviceC) --domain=linn.co.uk --type=Debug --version=2
$(deviceC)DvLinnCoUkDelay1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Delay1.xml
	echo DvLinnCoUkDelay1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Delay1.xml" --output=$(deviceC) --domain=linn.co.uk --type=Delay --version=1
$(deviceC)DvLinnCoUkDiagnostics1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Diagnostics1.xml
	echo DvLinnCoUkDiagnostics1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Diagnostics1.xml" --output=$(deviceC) --domain=linn.co.uk --type=Diagnostics --version=1
$(deviceC)DvLinnCoUkDs1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Ds1.xml
	echo DvLinnCoUkDs1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Ds1.xml" --output=$(deviceC) --domain=linn.co.uk --type=Ds --version=1
$(deviceC)DvLinnCoUkInfo1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Info1.xml
	echo DvLinnCoUkInfo1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Info1.xml" --output=$(deviceC) --domain=linn.co.uk --type=Info --version=1
$(deviceC)DvLinnCoUkJukebox1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Jukebox1.xml
	echo DvLinnCoUkJukebox1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Jukebox1.xml" --output=$(deviceC) --domain=linn.co.uk --type=Jukebox --version=1
$(deviceC)DvLinnCoUkMediaTime1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/MediaTime1.xml
	echo DvLinnCoUkMediaTime1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/MediaTime1.xml" --output=$(deviceC) --domain=linn.co.uk --type=MediaTime --version=1
$(deviceC)DvLinnCoUkPlaylist1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Playlist1.xml
	echo DvLinnCoUkPlaylist1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Playlist1.xml" --output=$(deviceC) --domain=linn.co.uk --type=Playlist --version=1
$(deviceC)DvLinnCoUkPreamp4C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Preamp4.xml
	echo DvLinnCoUkPreamp4C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Preamp4.xml" --output=$(deviceC) --domain=linn.co.uk --type=Preamp --version=4
$(deviceC)DvLinnCoUkProduct1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Product1.xml
	echo DvLinnCoUkProduct1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Product1.xml" --output=$(deviceC) --domain=linn.co.uk --type=Product --version=1
$(deviceC)DvLinnCoUkProduct2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Product2.xml
	echo DvLinnCoUkProduct2C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Product2.xml" --output=$(deviceC) --domain=linn.co.uk --type=Product --version=2
$(deviceC)DvLinnCoUkProduct3C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Product3.xml
	echo DvLinnCoUkProduct3C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Product3.xml" --output=$(deviceC) --domain=linn.co.uk --type=Product --version=3
$(deviceC)DvLinnCoUkProxyManager1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/ProxyManager1.xml
	echo DvLinnCoUkProxyManager1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/ProxyManager1.xml" --output=$(deviceC) --domain=linn.co.uk --type=ProxyManager --version=1
$(deviceC)DvLinnCoUkPtest1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Ptest1.xml
	echo DvLinnCoUkPtest1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Ptest1.xml" --output=$(deviceC) --domain=linn.co.uk --type=Ptest --version=1
$(deviceC)DvLinnCoUkRadio1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Radio1.xml
	echo DvLinnCoUkRadio1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Radio1.xml" --output=$(deviceC) --domain=linn.co.uk --type=Radio --version=1
$(deviceC)DvLinnCoUkTime1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Time1.xml
	echo DvLinnCoUkTime1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Time1.xml" --output=$(deviceC) --domain=linn.co.uk --type=Time --version=1
$(deviceC)DvLinnCoUkUi2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Ui2.xml
	echo DvLinnCoUkUi2C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Ui2.xml" --output=$(deviceC) --domain=linn.co.uk --type=Ui --version=2
$(deviceC)DvLinnCoUkVolkano1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Volkano1.xml
	echo DvLinnCoUkVolkano1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Linn/Volkano1.xml" --output=$(deviceC) --domain=linn.co.uk --type=Volkano --version=1
$(deviceC)DvZappOrgTestBasic1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo DvZappOrgTestBasic1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(deviceC) --domain=zapp.org --type=TestBasic --version=1
$(deviceC)DvZappOrgTestLights1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo DvZappOrgTestLights1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(deviceC) --domain=zapp.org --type=TestLights --version=1
$(deviceC)DvZappOrgTestDimmableLight1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo DvZappOrgTestDimmableLight1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(deviceC) --domain=zapp.org --type=TestDimmableLight --version=1
$(deviceC)DvOpenhomeOrgTestColorLight1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Openhome/Test/TestColorLight1.xml
	echo DvOpenhomeOrgTestColorLight1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Openhome/Test/TestColorLight1.xml" --output=$(deviceC) --domain=openhome.org --type=TestColorLight --version=1
$(deviceC)DvOpenhomeOrgOhNet1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt T4/Templates/DvUpnpCHeader.tt Service/Upnp/Openhome/OhNet1.xml
	echo DvOpenhomeOrgOhNet1C.cpp
	$(zappgen) --language=c --stack=dv "--xml=Service/Upnp/Openhome/OhNet1.xml" --output=$(deviceC) --domain=openhome.org --type=OhNet --version=1

DvCs:   $(deviceCs)DvUpnpOrgAVTransport1.cs $(deviceCs)DvUpnpOrgAVTransport2.cs $(deviceCs)DvUpnpOrgConnectionManager1.cs $(deviceCs)DvUpnpOrgConnectionManager2.cs $(deviceCs)DvUpnpOrgContentDirectory1.cs $(deviceCs)DvUpnpOrgContentDirectory2.cs $(deviceCs)DvUpnpOrgContentDirectory3.cs $(deviceCs)DvUpnpOrgRenderingControl1.cs $(deviceCs)DvUpnpOrgRenderingControl2.cs $(deviceCs)DvUpnpOrgScheduledRecording1.cs $(deviceCs)DvUpnpOrgScheduledRecording2.cs $(deviceCs)DvUpnpOrgSwitchPower1.cs $(deviceCs)DvUpnpOrgDimming1.cs $(deviceCs)DvLinnCoUkComponent1.cs $(deviceCs)DvLinnCoUkConfiguration1.cs $(deviceCs)DvLinnCoUkDebug2.cs $(deviceCs)DvLinnCoUkDelay1.cs $(deviceCs)DvLinnCoUkDiagnostics1.cs $(deviceCs)DvLinnCoUkDs1.cs $(deviceCs)DvLinnCoUkInfo1.cs $(deviceCs)DvLinnCoUkJukebox1.cs $(deviceCs)DvLinnCoUkMediaTime1.cs $(deviceCs)DvLinnCoUkPlaylist1.cs $(deviceCs)DvLinnCoUkPreamp4.cs $(deviceCs)DvLinnCoUkProduct1.cs $(deviceCs)DvLinnCoUkProduct2.cs $(deviceCs)DvLinnCoUkProduct3.cs $(deviceCs)DvLinnCoUkProxyManager1.cs $(deviceCs)DvLinnCoUkPtest1.cs $(deviceCs)DvLinnCoUkRadio1.cs $(deviceCs)DvLinnCoUkTime1.cs $(deviceCs)DvLinnCoUkUi2.cs $(deviceCs)DvLinnCoUkVolkano1.cs $(deviceCs)DvZappOrgTestBasic1.cs $(deviceCs)DvZappOrgTestLights1.cs $(deviceCs)DvZappOrgTestDimmableLight1.cs $(deviceCs)DvOpenhomeOrgTestColorLight1.cs $(deviceCs)DvOpenhomeOrgOhNet1.cs
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
$(deviceCs)DvLinnCoUkComponent1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Component1.xml
	echo DvLinnCoUkComponent1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Component1.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Component --version=1
$(deviceCs)DvLinnCoUkConfiguration1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Configuration1.xml
	echo DvLinnCoUkConfiguration1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Configuration1.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Configuration --version=1
$(deviceCs)DvLinnCoUkDebug2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Debug2.xml
	echo DvLinnCoUkDebug2.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Debug2.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Debug --version=2
$(deviceCs)DvLinnCoUkDelay1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Delay1.xml
	echo DvLinnCoUkDelay1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Delay1.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Delay --version=1
$(deviceCs)DvLinnCoUkDiagnostics1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Diagnostics1.xml
	echo DvLinnCoUkDiagnostics1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Diagnostics1.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Diagnostics --version=1
$(deviceCs)DvLinnCoUkDs1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Ds1.xml
	echo DvLinnCoUkDs1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Ds1.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Ds --version=1
$(deviceCs)DvLinnCoUkInfo1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Info1.xml
	echo DvLinnCoUkInfo1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Info1.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Info --version=1
$(deviceCs)DvLinnCoUkJukebox1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Jukebox1.xml
	echo DvLinnCoUkJukebox1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Jukebox1.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Jukebox --version=1
$(deviceCs)DvLinnCoUkMediaTime1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/MediaTime1.xml
	echo DvLinnCoUkMediaTime1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/MediaTime1.xml" --output=$(deviceCs) --domain=linn.co.uk --type=MediaTime --version=1
$(deviceCs)DvLinnCoUkPlaylist1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Playlist1.xml
	echo DvLinnCoUkPlaylist1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Playlist1.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Playlist --version=1
$(deviceCs)DvLinnCoUkPreamp4.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Preamp4.xml
	echo DvLinnCoUkPreamp4.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Preamp4.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Preamp --version=4
$(deviceCs)DvLinnCoUkProduct1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Product1.xml
	echo DvLinnCoUkProduct1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Product1.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Product --version=1
$(deviceCs)DvLinnCoUkProduct2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Product2.xml
	echo DvLinnCoUkProduct2.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Product2.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Product --version=2
$(deviceCs)DvLinnCoUkProduct3.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Product3.xml
	echo DvLinnCoUkProduct3.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Product3.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Product --version=3
$(deviceCs)DvLinnCoUkProxyManager1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/ProxyManager1.xml
	echo DvLinnCoUkProxyManager1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/ProxyManager1.xml" --output=$(deviceCs) --domain=linn.co.uk --type=ProxyManager --version=1
$(deviceCs)DvLinnCoUkPtest1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Ptest1.xml
	echo DvLinnCoUkPtest1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Ptest1.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Ptest --version=1
$(deviceCs)DvLinnCoUkRadio1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Radio1.xml
	echo DvLinnCoUkRadio1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Radio1.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Radio --version=1
$(deviceCs)DvLinnCoUkTime1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Time1.xml
	echo DvLinnCoUkTime1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Time1.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Time --version=1
$(deviceCs)DvLinnCoUkUi2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Ui2.xml
	echo DvLinnCoUkUi2.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Ui2.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Ui --version=2
$(deviceCs)DvLinnCoUkVolkano1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Volkano1.xml
	echo DvLinnCoUkVolkano1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Linn/Volkano1.xml" --output=$(deviceCs) --domain=linn.co.uk --type=Volkano --version=1
$(deviceCs)DvZappOrgTestBasic1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	echo DvZappOrgTestBasic1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Zapp/Test/TestBasic1.xml" --output=$(deviceCs) --domain=zapp.org --type=TestBasic --version=1
$(deviceCs)DvZappOrgTestLights1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Zapp/Test/TestLights1.xml
	echo DvZappOrgTestLights1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Zapp/Test/TestLights1.xml" --output=$(deviceCs) --domain=zapp.org --type=TestLights --version=1
$(deviceCs)DvZappOrgTestDimmableLight1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	echo DvZappOrgTestDimmableLight1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Zapp/Test/TestDimmableLight1.xml" --output=$(deviceCs) --domain=zapp.org --type=TestDimmableLight --version=1
$(deviceCs)DvOpenhomeOrgTestColorLight1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Openhome/Test/TestColorLight1.xml
	echo DvOpenhomeOrgTestColorLight1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Openhome/Test/TestColorLight1.xml" --output=$(deviceCs) --domain=openhome.org --type=TestColorLight --version=1
$(deviceCs)DvOpenhomeOrgOhNet1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Openhome/OhNet1.xml
	echo DvOpenhomeOrgOhNet1.cs
	$(zappgen) --language=cs --stack=dv "--xml=Service/Upnp/Openhome/OhNet1.xml" --output=$(deviceCs) --domain=openhome.org --type=OhNet --version=1

