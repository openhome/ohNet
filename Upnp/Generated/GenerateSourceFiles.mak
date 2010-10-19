# Auto-generated file.  DO NOT EDIT DIRECTLY
# Update CpUpnpMakeT4.tt and run 
#    make generate-makefiles
# to apply any updates

GenAll: AllCp AllDv

AllCp: CpApiCppCore CpSrcCppCore CpApiCppStd CpSrcCppStd CpApiC CpSrcC CpCs

AllDv: DvApiCppCore DvSrcCppCore DvApiCppStd DvSrcCppStd DvApiC DvSrcC DvCs


CpApiCppCore:   $(proxyApiCppCore)CpUpnpOrgAVTransport1.h $(proxyApiCppCore)CpUpnpOrgAVTransport2.h $(proxyApiCppCore)CpUpnpOrgConnectionManager1.h $(proxyApiCppCore)CpUpnpOrgConnectionManager2.h $(proxyApiCppCore)CpUpnpOrgContentDirectory1.h $(proxyApiCppCore)CpUpnpOrgContentDirectory2.h $(proxyApiCppCore)CpUpnpOrgContentDirectory3.h $(proxyApiCppCore)CpUpnpOrgRenderingControl1.h $(proxyApiCppCore)CpUpnpOrgRenderingControl2.h $(proxyApiCppCore)CpUpnpOrgScheduledRecording1.h $(proxyApiCppCore)CpUpnpOrgScheduledRecording2.h $(proxyApiCppCore)CpUpnpOrgSwitchPower1.h $(proxyApiCppCore)CpUpnpOrgDimming1.h $(proxyApiCppCore)CpLinnCoUkComponent1.h $(proxyApiCppCore)CpLinnCoUkConfiguration1.h $(proxyApiCppCore)CpLinnCoUkDebug2.h $(proxyApiCppCore)CpLinnCoUkDelay1.h $(proxyApiCppCore)CpLinnCoUkDiagnostics1.h $(proxyApiCppCore)CpLinnCoUkDs1.h $(proxyApiCppCore)CpLinnCoUkInfo1.h $(proxyApiCppCore)CpLinnCoUkJukebox1.h $(proxyApiCppCore)CpLinnCoUkMediaTime1.h $(proxyApiCppCore)CpLinnCoUkPlaylist1.h $(proxyApiCppCore)CpLinnCoUkPreamp4.h $(proxyApiCppCore)CpLinnCoUkProduct1.h $(proxyApiCppCore)CpLinnCoUkProduct2.h $(proxyApiCppCore)CpLinnCoUkProduct3.h $(proxyApiCppCore)CpLinnCoUkProxyManager1.h $(proxyApiCppCore)CpLinnCoUkPtest1.h $(proxyApiCppCore)CpLinnCoUkRadio1.h $(proxyApiCppCore)CpLinnCoUkTime1.h $(proxyApiCppCore)CpLinnCoUkUi2.h $(proxyApiCppCore)CpLinnCoUkVolkano1.h $(proxyApiCppCore)CpZappOrgTestBasic1.h $(proxyApiCppCore)CpZappOrgTestWidget1.h $(proxyApiCppCore)CpZappOrgTestWidgetController1.h $(proxyApiCppCore)CpZappOrgTestLights1.h $(proxyApiCppCore)CpZappOrgTestDimmableLight1.h
$(proxyApiCppCore)CpUpnpOrgAVTransport1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgAVTransport1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1 -a buffer:1
$(proxyApiCppCore)CpUpnpOrgAVTransport2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgAVTransport2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2 -a buffer:1
$(proxyApiCppCore)CpUpnpOrgConnectionManager1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgConnectionManager1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1 -a buffer:1
$(proxyApiCppCore)CpUpnpOrgConnectionManager2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgConnectionManager2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2 -a buffer:1
$(proxyApiCppCore)CpUpnpOrgContentDirectory1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgContentDirectory1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1 -a buffer:1
$(proxyApiCppCore)CpUpnpOrgContentDirectory2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgContentDirectory2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2 -a buffer:1
$(proxyApiCppCore)CpUpnpOrgContentDirectory3.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgContentDirectory3.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3 -a buffer:1
$(proxyApiCppCore)CpUpnpOrgRenderingControl1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgRenderingControl1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1 -a buffer:1
$(proxyApiCppCore)CpUpnpOrgRenderingControl2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgRenderingControl2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2 -a buffer:1
$(proxyApiCppCore)CpUpnpOrgScheduledRecording1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgScheduledRecording1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1 -a buffer:1
$(proxyApiCppCore)CpUpnpOrgScheduledRecording2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgScheduledRecording2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2 -a buffer:1
$(proxyApiCppCore)CpUpnpOrgSwitchPower1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgSwitchPower1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1 -a buffer:1
$(proxyApiCppCore)CpUpnpOrgDimming1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgDimming1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkComponent1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Component1.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkComponent1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkConfiguration1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Configuration1.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkConfiguration1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkDebug2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Debug2.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkDebug2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkDelay1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Delay1.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkDelay1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkDiagnostics1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Diagnostics1.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkDiagnostics1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkDs1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Ds1.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkDs1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkInfo1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Info1.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkInfo1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkJukebox1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Jukebox1.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkJukebox1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkMediaTime1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/MediaTime1.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkMediaTime1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkPlaylist1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Playlist1.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkPlaylist1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkPreamp4.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Preamp4.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkPreamp4.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkProduct1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Product1.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkProduct1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkProduct2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Product2.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkProduct2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkProduct3.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Product3.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkProduct3.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkProxyManager1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/ProxyManager1.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkProxyManager1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkPtest1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Ptest1.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkPtest1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkRadio1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Radio1.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkRadio1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkTime1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Time1.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkTime1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkUi2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Ui2.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkUi2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2 -a buffer:1
$(proxyApiCppCore)CpLinnCoUkVolkano1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Volkano1.xml
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkVolkano1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1 -a buffer:1
$(proxyApiCppCore)CpZappOrgTestBasic1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	$(t4) -o $(proxyApiCppCore)CpZappOrgTestBasic1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1 -a buffer:1
$(proxyApiCppCore)CpZappOrgTestWidget1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestWidget1.xml
	$(t4) -o $(proxyApiCppCore)CpZappOrgTestWidget1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestWidget1.xml" -a domain:zapp.org -a type:TestWidget -a version:1 -a buffer:1
$(proxyApiCppCore)CpZappOrgTestWidgetController1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestWidgetController1.xml
	$(t4) -o $(proxyApiCppCore)CpZappOrgTestWidgetController1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestWidgetController1.xml" -a domain:zapp.org -a type:TestWidgetController -a version:1 -a buffer:1
$(proxyApiCppCore)CpZappOrgTestLights1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	$(t4) -o $(proxyApiCppCore)CpZappOrgTestLights1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1 -a buffer:1
$(proxyApiCppCore)CpZappOrgTestDimmableLight1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	$(t4) -o $(proxyApiCppCore)CpZappOrgTestDimmableLight1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1 -a buffer:1

CpSrcCppCore:   $(proxySrcCppCore)CpUpnpOrgAVTransport1.cpp $(proxySrcCppCore)CpUpnpOrgAVTransport2.cpp $(proxySrcCppCore)CpUpnpOrgConnectionManager1.cpp $(proxySrcCppCore)CpUpnpOrgConnectionManager2.cpp $(proxySrcCppCore)CpUpnpOrgContentDirectory1.cpp $(proxySrcCppCore)CpUpnpOrgContentDirectory2.cpp $(proxySrcCppCore)CpUpnpOrgContentDirectory3.cpp $(proxySrcCppCore)CpUpnpOrgRenderingControl1.cpp $(proxySrcCppCore)CpUpnpOrgRenderingControl2.cpp $(proxySrcCppCore)CpUpnpOrgScheduledRecording1.cpp $(proxySrcCppCore)CpUpnpOrgScheduledRecording2.cpp $(proxySrcCppCore)CpUpnpOrgSwitchPower1.cpp $(proxySrcCppCore)CpUpnpOrgDimming1.cpp $(proxySrcCppCore)CpLinnCoUkComponent1.cpp $(proxySrcCppCore)CpLinnCoUkConfiguration1.cpp $(proxySrcCppCore)CpLinnCoUkDebug2.cpp $(proxySrcCppCore)CpLinnCoUkDelay1.cpp $(proxySrcCppCore)CpLinnCoUkDiagnostics1.cpp $(proxySrcCppCore)CpLinnCoUkDs1.cpp $(proxySrcCppCore)CpLinnCoUkInfo1.cpp $(proxySrcCppCore)CpLinnCoUkJukebox1.cpp $(proxySrcCppCore)CpLinnCoUkMediaTime1.cpp $(proxySrcCppCore)CpLinnCoUkPlaylist1.cpp $(proxySrcCppCore)CpLinnCoUkPreamp4.cpp $(proxySrcCppCore)CpLinnCoUkProduct1.cpp $(proxySrcCppCore)CpLinnCoUkProduct2.cpp $(proxySrcCppCore)CpLinnCoUkProduct3.cpp $(proxySrcCppCore)CpLinnCoUkProxyManager1.cpp $(proxySrcCppCore)CpLinnCoUkPtest1.cpp $(proxySrcCppCore)CpLinnCoUkRadio1.cpp $(proxySrcCppCore)CpLinnCoUkTime1.cpp $(proxySrcCppCore)CpLinnCoUkUi2.cpp $(proxySrcCppCore)CpLinnCoUkVolkano1.cpp $(proxySrcCppCore)CpZappOrgTestBasic1.cpp $(proxySrcCppCore)CpZappOrgTestWidget1.cpp $(proxySrcCppCore)CpZappOrgTestWidgetController1.cpp $(proxySrcCppCore)CpZappOrgTestLights1.cpp $(proxySrcCppCore)CpZappOrgTestDimmableLight1.cpp
$(proxySrcCppCore)CpUpnpOrgAVTransport1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgAVTransport1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
$(proxySrcCppCore)CpUpnpOrgAVTransport2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgAVTransport2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
$(proxySrcCppCore)CpUpnpOrgConnectionManager1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgConnectionManager1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
$(proxySrcCppCore)CpUpnpOrgConnectionManager2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgConnectionManager2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
$(proxySrcCppCore)CpUpnpOrgContentDirectory1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgContentDirectory1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
$(proxySrcCppCore)CpUpnpOrgContentDirectory2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgContentDirectory2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
$(proxySrcCppCore)CpUpnpOrgContentDirectory3.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgContentDirectory3.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
$(proxySrcCppCore)CpUpnpOrgRenderingControl1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgRenderingControl1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
$(proxySrcCppCore)CpUpnpOrgRenderingControl2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgRenderingControl2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
$(proxySrcCppCore)CpUpnpOrgScheduledRecording1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgScheduledRecording1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
$(proxySrcCppCore)CpUpnpOrgScheduledRecording2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgScheduledRecording2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
$(proxySrcCppCore)CpUpnpOrgSwitchPower1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgSwitchPower1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
$(proxySrcCppCore)CpUpnpOrgDimming1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgDimming1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
$(proxySrcCppCore)CpLinnCoUkComponent1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Component1.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkComponent1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
$(proxySrcCppCore)CpLinnCoUkConfiguration1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Configuration1.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkConfiguration1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
$(proxySrcCppCore)CpLinnCoUkDebug2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Debug2.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkDebug2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
$(proxySrcCppCore)CpLinnCoUkDelay1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Delay1.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkDelay1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
$(proxySrcCppCore)CpLinnCoUkDiagnostics1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Diagnostics1.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkDiagnostics1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
$(proxySrcCppCore)CpLinnCoUkDs1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Ds1.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkDs1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
$(proxySrcCppCore)CpLinnCoUkInfo1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Info1.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkInfo1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
$(proxySrcCppCore)CpLinnCoUkJukebox1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Jukebox1.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkJukebox1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
$(proxySrcCppCore)CpLinnCoUkMediaTime1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/MediaTime1.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkMediaTime1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
$(proxySrcCppCore)CpLinnCoUkPlaylist1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Playlist1.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkPlaylist1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
$(proxySrcCppCore)CpLinnCoUkPreamp4.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Preamp4.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkPreamp4.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
$(proxySrcCppCore)CpLinnCoUkProduct1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Product1.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkProduct1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
$(proxySrcCppCore)CpLinnCoUkProduct2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Product2.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkProduct2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
$(proxySrcCppCore)CpLinnCoUkProduct3.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Product3.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkProduct3.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
$(proxySrcCppCore)CpLinnCoUkProxyManager1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/ProxyManager1.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkProxyManager1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
$(proxySrcCppCore)CpLinnCoUkPtest1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Ptest1.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkPtest1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
$(proxySrcCppCore)CpLinnCoUkRadio1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Radio1.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkRadio1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
$(proxySrcCppCore)CpLinnCoUkTime1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Time1.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkTime1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
$(proxySrcCppCore)CpLinnCoUkUi2.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Ui2.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkUi2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
$(proxySrcCppCore)CpLinnCoUkVolkano1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Linn/Volkano1.xml
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkVolkano1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
$(proxySrcCppCore)CpZappOrgTestBasic1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	$(t4) -o $(proxySrcCppCore)CpZappOrgTestBasic1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
$(proxySrcCppCore)CpZappOrgTestWidget1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Zapp/Test/TestWidget1.xml
	$(t4) -o $(proxySrcCppCore)CpZappOrgTestWidget1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Zapp/Test/TestWidget1.xml" -a domain:zapp.org -a type:TestWidget -a version:1
$(proxySrcCppCore)CpZappOrgTestWidgetController1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Zapp/Test/TestWidgetController1.xml
	$(t4) -o $(proxySrcCppCore)CpZappOrgTestWidgetController1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Zapp/Test/TestWidgetController1.xml" -a domain:zapp.org -a type:TestWidgetController -a version:1
$(proxySrcCppCore)CpZappOrgTestLights1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Zapp/Test/TestLights1.xml
	$(t4) -o $(proxySrcCppCore)CpZappOrgTestLights1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
$(proxySrcCppCore)CpZappOrgTestDimmableLight1.cpp : $(tt) T4/Templates/CpUpnpCppBufferSource.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	$(t4) -o $(proxySrcCppCore)CpZappOrgTestDimmableLight1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

CpApiCppStd:   $(proxyApiCppStd)CpUpnpOrgAVTransport1.h $(proxyApiCppStd)CpUpnpOrgAVTransport2.h $(proxyApiCppStd)CpUpnpOrgConnectionManager1.h $(proxyApiCppStd)CpUpnpOrgConnectionManager2.h $(proxyApiCppStd)CpUpnpOrgContentDirectory1.h $(proxyApiCppStd)CpUpnpOrgContentDirectory2.h $(proxyApiCppStd)CpUpnpOrgContentDirectory3.h $(proxyApiCppStd)CpUpnpOrgRenderingControl1.h $(proxyApiCppStd)CpUpnpOrgRenderingControl2.h $(proxyApiCppStd)CpUpnpOrgScheduledRecording1.h $(proxyApiCppStd)CpUpnpOrgScheduledRecording2.h $(proxyApiCppStd)CpUpnpOrgSwitchPower1.h $(proxyApiCppStd)CpUpnpOrgDimming1.h $(proxyApiCppStd)CpLinnCoUkComponent1.h $(proxyApiCppStd)CpLinnCoUkConfiguration1.h $(proxyApiCppStd)CpLinnCoUkDebug2.h $(proxyApiCppStd)CpLinnCoUkDelay1.h $(proxyApiCppStd)CpLinnCoUkDiagnostics1.h $(proxyApiCppStd)CpLinnCoUkDs1.h $(proxyApiCppStd)CpLinnCoUkInfo1.h $(proxyApiCppStd)CpLinnCoUkJukebox1.h $(proxyApiCppStd)CpLinnCoUkMediaTime1.h $(proxyApiCppStd)CpLinnCoUkPlaylist1.h $(proxyApiCppStd)CpLinnCoUkPreamp4.h $(proxyApiCppStd)CpLinnCoUkProduct1.h $(proxyApiCppStd)CpLinnCoUkProduct2.h $(proxyApiCppStd)CpLinnCoUkProduct3.h $(proxyApiCppStd)CpLinnCoUkProxyManager1.h $(proxyApiCppStd)CpLinnCoUkPtest1.h $(proxyApiCppStd)CpLinnCoUkRadio1.h $(proxyApiCppStd)CpLinnCoUkTime1.h $(proxyApiCppStd)CpLinnCoUkUi2.h $(proxyApiCppStd)CpLinnCoUkVolkano1.h $(proxyApiCppStd)CpZappOrgTestBasic1.h $(proxyApiCppStd)CpZappOrgTestWidget1.h $(proxyApiCppStd)CpZappOrgTestWidgetController1.h $(proxyApiCppStd)CpZappOrgTestLights1.h $(proxyApiCppStd)CpZappOrgTestDimmableLight1.h
$(proxyApiCppStd)CpUpnpOrgAVTransport1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgAVTransport1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1 -a buffer:0
$(proxyApiCppStd)CpUpnpOrgAVTransport2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgAVTransport2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2 -a buffer:0
$(proxyApiCppStd)CpUpnpOrgConnectionManager1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgConnectionManager1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1 -a buffer:0
$(proxyApiCppStd)CpUpnpOrgConnectionManager2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgConnectionManager2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2 -a buffer:0
$(proxyApiCppStd)CpUpnpOrgContentDirectory1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgContentDirectory1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1 -a buffer:0
$(proxyApiCppStd)CpUpnpOrgContentDirectory2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgContentDirectory2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2 -a buffer:0
$(proxyApiCppStd)CpUpnpOrgContentDirectory3.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgContentDirectory3.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3 -a buffer:0
$(proxyApiCppStd)CpUpnpOrgRenderingControl1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgRenderingControl1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1 -a buffer:0
$(proxyApiCppStd)CpUpnpOrgRenderingControl2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgRenderingControl2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2 -a buffer:0
$(proxyApiCppStd)CpUpnpOrgScheduledRecording1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgScheduledRecording1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1 -a buffer:0
$(proxyApiCppStd)CpUpnpOrgScheduledRecording2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgScheduledRecording2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2 -a buffer:0
$(proxyApiCppStd)CpUpnpOrgSwitchPower1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgSwitchPower1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1 -a buffer:0
$(proxyApiCppStd)CpUpnpOrgDimming1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgDimming1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkComponent1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Component1.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkComponent1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkConfiguration1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Configuration1.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkConfiguration1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkDebug2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Debug2.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkDebug2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkDelay1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Delay1.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkDelay1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkDiagnostics1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Diagnostics1.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkDiagnostics1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkDs1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Ds1.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkDs1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkInfo1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Info1.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkInfo1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkJukebox1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Jukebox1.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkJukebox1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkMediaTime1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/MediaTime1.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkMediaTime1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkPlaylist1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Playlist1.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkPlaylist1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkPreamp4.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Preamp4.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkPreamp4.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkProduct1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Product1.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkProduct1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkProduct2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Product2.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkProduct2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkProduct3.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Product3.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkProduct3.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkProxyManager1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/ProxyManager1.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkProxyManager1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkPtest1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Ptest1.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkPtest1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkRadio1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Radio1.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkRadio1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkTime1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Time1.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkTime1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkUi2.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Ui2.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkUi2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2 -a buffer:0
$(proxyApiCppStd)CpLinnCoUkVolkano1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Linn/Volkano1.xml
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkVolkano1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1 -a buffer:0
$(proxyApiCppStd)CpZappOrgTestBasic1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	$(t4) -o $(proxyApiCppStd)CpZappOrgTestBasic1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1 -a buffer:0
$(proxyApiCppStd)CpZappOrgTestWidget1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestWidget1.xml
	$(t4) -o $(proxyApiCppStd)CpZappOrgTestWidget1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestWidget1.xml" -a domain:zapp.org -a type:TestWidget -a version:1 -a buffer:0
$(proxyApiCppStd)CpZappOrgTestWidgetController1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestWidgetController1.xml
	$(t4) -o $(proxyApiCppStd)CpZappOrgTestWidgetController1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestWidgetController1.xml" -a domain:zapp.org -a type:TestWidgetController -a version:1 -a buffer:0
$(proxyApiCppStd)CpZappOrgTestLights1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	$(t4) -o $(proxyApiCppStd)CpZappOrgTestLights1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1 -a buffer:0
$(proxyApiCppStd)CpZappOrgTestDimmableLight1.h : $(tt) T4/Templates/CpUpnpCppHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	$(t4) -o $(proxyApiCppStd)CpZappOrgTestDimmableLight1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1 -a buffer:0

CpSrcCppStd:   $(proxySrcCppStd)CpUpnpOrgAVTransport1Std.cpp $(proxySrcCppStd)CpUpnpOrgAVTransport2Std.cpp $(proxySrcCppStd)CpUpnpOrgConnectionManager1Std.cpp $(proxySrcCppStd)CpUpnpOrgConnectionManager2Std.cpp $(proxySrcCppStd)CpUpnpOrgContentDirectory1Std.cpp $(proxySrcCppStd)CpUpnpOrgContentDirectory2Std.cpp $(proxySrcCppStd)CpUpnpOrgContentDirectory3Std.cpp $(proxySrcCppStd)CpUpnpOrgRenderingControl1Std.cpp $(proxySrcCppStd)CpUpnpOrgRenderingControl2Std.cpp $(proxySrcCppStd)CpUpnpOrgScheduledRecording1Std.cpp $(proxySrcCppStd)CpUpnpOrgScheduledRecording2Std.cpp $(proxySrcCppStd)CpUpnpOrgSwitchPower1Std.cpp $(proxySrcCppStd)CpUpnpOrgDimming1Std.cpp $(proxySrcCppStd)CpLinnCoUkComponent1Std.cpp $(proxySrcCppStd)CpLinnCoUkConfiguration1Std.cpp $(proxySrcCppStd)CpLinnCoUkDebug2Std.cpp $(proxySrcCppStd)CpLinnCoUkDelay1Std.cpp $(proxySrcCppStd)CpLinnCoUkDiagnostics1Std.cpp $(proxySrcCppStd)CpLinnCoUkDs1Std.cpp $(proxySrcCppStd)CpLinnCoUkInfo1Std.cpp $(proxySrcCppStd)CpLinnCoUkJukebox1Std.cpp $(proxySrcCppStd)CpLinnCoUkMediaTime1Std.cpp $(proxySrcCppStd)CpLinnCoUkPlaylist1Std.cpp $(proxySrcCppStd)CpLinnCoUkPreamp4Std.cpp $(proxySrcCppStd)CpLinnCoUkProduct1Std.cpp $(proxySrcCppStd)CpLinnCoUkProduct2Std.cpp $(proxySrcCppStd)CpLinnCoUkProduct3Std.cpp $(proxySrcCppStd)CpLinnCoUkProxyManager1Std.cpp $(proxySrcCppStd)CpLinnCoUkPtest1Std.cpp $(proxySrcCppStd)CpLinnCoUkRadio1Std.cpp $(proxySrcCppStd)CpLinnCoUkTime1Std.cpp $(proxySrcCppStd)CpLinnCoUkUi2Std.cpp $(proxySrcCppStd)CpLinnCoUkVolkano1Std.cpp $(proxySrcCppStd)CpZappOrgTestBasic1Std.cpp $(proxySrcCppStd)CpZappOrgTestWidget1Std.cpp $(proxySrcCppStd)CpZappOrgTestWidgetController1Std.cpp $(proxySrcCppStd)CpZappOrgTestLights1Std.cpp $(proxySrcCppStd)CpZappOrgTestDimmableLight1Std.cpp
$(proxySrcCppStd)CpUpnpOrgAVTransport1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgAVTransport1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
$(proxySrcCppStd)CpUpnpOrgAVTransport2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgAVTransport2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
$(proxySrcCppStd)CpUpnpOrgConnectionManager1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgConnectionManager1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
$(proxySrcCppStd)CpUpnpOrgConnectionManager2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgConnectionManager2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
$(proxySrcCppStd)CpUpnpOrgContentDirectory1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgContentDirectory1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
$(proxySrcCppStd)CpUpnpOrgContentDirectory2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgContentDirectory2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
$(proxySrcCppStd)CpUpnpOrgContentDirectory3Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgContentDirectory3Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
$(proxySrcCppStd)CpUpnpOrgRenderingControl1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgRenderingControl1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
$(proxySrcCppStd)CpUpnpOrgRenderingControl2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgRenderingControl2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
$(proxySrcCppStd)CpUpnpOrgScheduledRecording1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgScheduledRecording1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
$(proxySrcCppStd)CpUpnpOrgScheduledRecording2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgScheduledRecording2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
$(proxySrcCppStd)CpUpnpOrgSwitchPower1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgSwitchPower1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
$(proxySrcCppStd)CpUpnpOrgDimming1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgDimming1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
$(proxySrcCppStd)CpLinnCoUkComponent1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Component1.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkComponent1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
$(proxySrcCppStd)CpLinnCoUkConfiguration1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Configuration1.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkConfiguration1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
$(proxySrcCppStd)CpLinnCoUkDebug2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Debug2.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkDebug2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
$(proxySrcCppStd)CpLinnCoUkDelay1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Delay1.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkDelay1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
$(proxySrcCppStd)CpLinnCoUkDiagnostics1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Diagnostics1.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkDiagnostics1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
$(proxySrcCppStd)CpLinnCoUkDs1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Ds1.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkDs1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
$(proxySrcCppStd)CpLinnCoUkInfo1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Info1.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkInfo1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
$(proxySrcCppStd)CpLinnCoUkJukebox1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Jukebox1.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkJukebox1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
$(proxySrcCppStd)CpLinnCoUkMediaTime1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/MediaTime1.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkMediaTime1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
$(proxySrcCppStd)CpLinnCoUkPlaylist1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Playlist1.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkPlaylist1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
$(proxySrcCppStd)CpLinnCoUkPreamp4Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Preamp4.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkPreamp4Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
$(proxySrcCppStd)CpLinnCoUkProduct1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Product1.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkProduct1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
$(proxySrcCppStd)CpLinnCoUkProduct2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Product2.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkProduct2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
$(proxySrcCppStd)CpLinnCoUkProduct3Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Product3.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkProduct3Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
$(proxySrcCppStd)CpLinnCoUkProxyManager1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/ProxyManager1.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkProxyManager1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
$(proxySrcCppStd)CpLinnCoUkPtest1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Ptest1.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkPtest1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
$(proxySrcCppStd)CpLinnCoUkRadio1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Radio1.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkRadio1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
$(proxySrcCppStd)CpLinnCoUkTime1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Time1.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkTime1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
$(proxySrcCppStd)CpLinnCoUkUi2Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Ui2.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkUi2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
$(proxySrcCppStd)CpLinnCoUkVolkano1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Linn/Volkano1.xml
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkVolkano1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
$(proxySrcCppStd)CpZappOrgTestBasic1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	$(t4) -o $(proxySrcCppStd)CpZappOrgTestBasic1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
$(proxySrcCppStd)CpZappOrgTestWidget1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Zapp/Test/TestWidget1.xml
	$(t4) -o $(proxySrcCppStd)CpZappOrgTestWidget1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Zapp/Test/TestWidget1.xml" -a domain:zapp.org -a type:TestWidget -a version:1
$(proxySrcCppStd)CpZappOrgTestWidgetController1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Zapp/Test/TestWidgetController1.xml
	$(t4) -o $(proxySrcCppStd)CpZappOrgTestWidgetController1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Zapp/Test/TestWidgetController1.xml" -a domain:zapp.org -a type:TestWidgetController -a version:1
$(proxySrcCppStd)CpZappOrgTestLights1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Zapp/Test/TestLights1.xml
	$(t4) -o $(proxySrcCppStd)CpZappOrgTestLights1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
$(proxySrcCppStd)CpZappOrgTestDimmableLight1Std.cpp : $(tt) T4/Templates/CpUpnpCppStringSource.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	$(t4) -o $(proxySrcCppStd)CpZappOrgTestDimmableLight1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

CpApiC:   $(proxyApiC)CpUpnpOrgAVTransport1.h $(proxyApiC)CpUpnpOrgAVTransport2.h $(proxyApiC)CpUpnpOrgConnectionManager1.h $(proxyApiC)CpUpnpOrgConnectionManager2.h $(proxyApiC)CpUpnpOrgContentDirectory1.h $(proxyApiC)CpUpnpOrgContentDirectory2.h $(proxyApiC)CpUpnpOrgContentDirectory3.h $(proxyApiC)CpUpnpOrgRenderingControl1.h $(proxyApiC)CpUpnpOrgRenderingControl2.h $(proxyApiC)CpUpnpOrgScheduledRecording1.h $(proxyApiC)CpUpnpOrgScheduledRecording2.h $(proxyApiC)CpUpnpOrgSwitchPower1.h $(proxyApiC)CpUpnpOrgDimming1.h $(proxyApiC)CpLinnCoUkComponent1.h $(proxyApiC)CpLinnCoUkConfiguration1.h $(proxyApiC)CpLinnCoUkDebug2.h $(proxyApiC)CpLinnCoUkDelay1.h $(proxyApiC)CpLinnCoUkDiagnostics1.h $(proxyApiC)CpLinnCoUkDs1.h $(proxyApiC)CpLinnCoUkInfo1.h $(proxyApiC)CpLinnCoUkJukebox1.h $(proxyApiC)CpLinnCoUkMediaTime1.h $(proxyApiC)CpLinnCoUkPlaylist1.h $(proxyApiC)CpLinnCoUkPreamp4.h $(proxyApiC)CpLinnCoUkProduct1.h $(proxyApiC)CpLinnCoUkProduct2.h $(proxyApiC)CpLinnCoUkProduct3.h $(proxyApiC)CpLinnCoUkProxyManager1.h $(proxyApiC)CpLinnCoUkPtest1.h $(proxyApiC)CpLinnCoUkRadio1.h $(proxyApiC)CpLinnCoUkTime1.h $(proxyApiC)CpLinnCoUkUi2.h $(proxyApiC)CpLinnCoUkVolkano1.h $(proxyApiC)CpZappOrgTestBasic1.h $(proxyApiC)CpZappOrgTestWidget1.h $(proxyApiC)CpZappOrgTestWidgetController1.h $(proxyApiC)CpZappOrgTestLights1.h $(proxyApiC)CpZappOrgTestDimmableLight1.h
$(proxyApiC)CpUpnpOrgAVTransport1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	$(t4) -o $(proxyApiC)CpUpnpOrgAVTransport1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
$(proxyApiC)CpUpnpOrgAVTransport2.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	$(t4) -o $(proxyApiC)CpUpnpOrgAVTransport2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
$(proxyApiC)CpUpnpOrgConnectionManager1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	$(t4) -o $(proxyApiC)CpUpnpOrgConnectionManager1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
$(proxyApiC)CpUpnpOrgConnectionManager2.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	$(t4) -o $(proxyApiC)CpUpnpOrgConnectionManager2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
$(proxyApiC)CpUpnpOrgContentDirectory1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	$(t4) -o $(proxyApiC)CpUpnpOrgContentDirectory1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
$(proxyApiC)CpUpnpOrgContentDirectory2.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	$(t4) -o $(proxyApiC)CpUpnpOrgContentDirectory2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
$(proxyApiC)CpUpnpOrgContentDirectory3.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	$(t4) -o $(proxyApiC)CpUpnpOrgContentDirectory3.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
$(proxyApiC)CpUpnpOrgRenderingControl1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	$(t4) -o $(proxyApiC)CpUpnpOrgRenderingControl1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
$(proxyApiC)CpUpnpOrgRenderingControl2.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	$(t4) -o $(proxyApiC)CpUpnpOrgRenderingControl2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
$(proxyApiC)CpUpnpOrgScheduledRecording1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	$(t4) -o $(proxyApiC)CpUpnpOrgScheduledRecording1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
$(proxyApiC)CpUpnpOrgScheduledRecording2.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	$(t4) -o $(proxyApiC)CpUpnpOrgScheduledRecording2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
$(proxyApiC)CpUpnpOrgSwitchPower1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	$(t4) -o $(proxyApiC)CpUpnpOrgSwitchPower1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
$(proxyApiC)CpUpnpOrgDimming1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	$(t4) -o $(proxyApiC)CpUpnpOrgDimming1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
$(proxyApiC)CpLinnCoUkComponent1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Component1.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkComponent1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
$(proxyApiC)CpLinnCoUkConfiguration1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Configuration1.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkConfiguration1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
$(proxyApiC)CpLinnCoUkDebug2.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Debug2.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkDebug2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
$(proxyApiC)CpLinnCoUkDelay1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Delay1.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkDelay1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
$(proxyApiC)CpLinnCoUkDiagnostics1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Diagnostics1.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkDiagnostics1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
$(proxyApiC)CpLinnCoUkDs1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Ds1.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkDs1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
$(proxyApiC)CpLinnCoUkInfo1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Info1.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkInfo1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
$(proxyApiC)CpLinnCoUkJukebox1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Jukebox1.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkJukebox1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
$(proxyApiC)CpLinnCoUkMediaTime1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/MediaTime1.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkMediaTime1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
$(proxyApiC)CpLinnCoUkPlaylist1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Playlist1.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkPlaylist1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
$(proxyApiC)CpLinnCoUkPreamp4.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Preamp4.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkPreamp4.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
$(proxyApiC)CpLinnCoUkProduct1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Product1.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkProduct1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
$(proxyApiC)CpLinnCoUkProduct2.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Product2.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkProduct2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
$(proxyApiC)CpLinnCoUkProduct3.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Product3.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkProduct3.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
$(proxyApiC)CpLinnCoUkProxyManager1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/ProxyManager1.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkProxyManager1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
$(proxyApiC)CpLinnCoUkPtest1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Ptest1.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkPtest1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
$(proxyApiC)CpLinnCoUkRadio1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Radio1.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkRadio1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
$(proxyApiC)CpLinnCoUkTime1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Time1.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkTime1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
$(proxyApiC)CpLinnCoUkUi2.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Ui2.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkUi2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
$(proxyApiC)CpLinnCoUkVolkano1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Linn/Volkano1.xml
	$(t4) -o $(proxyApiC)CpLinnCoUkVolkano1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
$(proxyApiC)CpZappOrgTestBasic1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	$(t4) -o $(proxyApiC)CpZappOrgTestBasic1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
$(proxyApiC)CpZappOrgTestWidget1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Zapp/Test/TestWidget1.xml
	$(t4) -o $(proxyApiC)CpZappOrgTestWidget1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestWidget1.xml" -a domain:zapp.org -a type:TestWidget -a version:1
$(proxyApiC)CpZappOrgTestWidgetController1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Zapp/Test/TestWidgetController1.xml
	$(t4) -o $(proxyApiC)CpZappOrgTestWidgetController1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestWidgetController1.xml" -a domain:zapp.org -a type:TestWidgetController -a version:1
$(proxyApiC)CpZappOrgTestLights1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	$(t4) -o $(proxyApiC)CpZappOrgTestLights1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
$(proxyApiC)CpZappOrgTestDimmableLight1.h : $(tt) T4/Templates/CpUpnpCHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	$(t4) -o $(proxyApiC)CpZappOrgTestDimmableLight1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

CpSrcC:   $(proxySrcC)CpUpnpOrgAVTransport1C.cpp $(proxySrcC)CpUpnpOrgAVTransport2C.cpp $(proxySrcC)CpUpnpOrgConnectionManager1C.cpp $(proxySrcC)CpUpnpOrgConnectionManager2C.cpp $(proxySrcC)CpUpnpOrgContentDirectory1C.cpp $(proxySrcC)CpUpnpOrgContentDirectory2C.cpp $(proxySrcC)CpUpnpOrgContentDirectory3C.cpp $(proxySrcC)CpUpnpOrgRenderingControl1C.cpp $(proxySrcC)CpUpnpOrgRenderingControl2C.cpp $(proxySrcC)CpUpnpOrgScheduledRecording1C.cpp $(proxySrcC)CpUpnpOrgScheduledRecording2C.cpp $(proxySrcC)CpUpnpOrgSwitchPower1C.cpp $(proxySrcC)CpUpnpOrgDimming1C.cpp $(proxySrcC)CpLinnCoUkComponent1C.cpp $(proxySrcC)CpLinnCoUkConfiguration1C.cpp $(proxySrcC)CpLinnCoUkDebug2C.cpp $(proxySrcC)CpLinnCoUkDelay1C.cpp $(proxySrcC)CpLinnCoUkDiagnostics1C.cpp $(proxySrcC)CpLinnCoUkDs1C.cpp $(proxySrcC)CpLinnCoUkInfo1C.cpp $(proxySrcC)CpLinnCoUkJukebox1C.cpp $(proxySrcC)CpLinnCoUkMediaTime1C.cpp $(proxySrcC)CpLinnCoUkPlaylist1C.cpp $(proxySrcC)CpLinnCoUkPreamp4C.cpp $(proxySrcC)CpLinnCoUkProduct1C.cpp $(proxySrcC)CpLinnCoUkProduct2C.cpp $(proxySrcC)CpLinnCoUkProduct3C.cpp $(proxySrcC)CpLinnCoUkProxyManager1C.cpp $(proxySrcC)CpLinnCoUkPtest1C.cpp $(proxySrcC)CpLinnCoUkRadio1C.cpp $(proxySrcC)CpLinnCoUkTime1C.cpp $(proxySrcC)CpLinnCoUkUi2C.cpp $(proxySrcC)CpLinnCoUkVolkano1C.cpp $(proxySrcC)CpZappOrgTestBasic1C.cpp $(proxySrcC)CpZappOrgTestWidget1C.cpp $(proxySrcC)CpZappOrgTestWidgetController1C.cpp $(proxySrcC)CpZappOrgTestLights1C.cpp $(proxySrcC)CpZappOrgTestDimmableLight1C.cpp
$(proxySrcC)CpUpnpOrgAVTransport1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	$(t4) -o $(proxySrcC)CpUpnpOrgAVTransport1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
$(proxySrcC)CpUpnpOrgAVTransport2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	$(t4) -o $(proxySrcC)CpUpnpOrgAVTransport2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
$(proxySrcC)CpUpnpOrgConnectionManager1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	$(t4) -o $(proxySrcC)CpUpnpOrgConnectionManager1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
$(proxySrcC)CpUpnpOrgConnectionManager2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	$(t4) -o $(proxySrcC)CpUpnpOrgConnectionManager2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
$(proxySrcC)CpUpnpOrgContentDirectory1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	$(t4) -o $(proxySrcC)CpUpnpOrgContentDirectory1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
$(proxySrcC)CpUpnpOrgContentDirectory2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	$(t4) -o $(proxySrcC)CpUpnpOrgContentDirectory2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
$(proxySrcC)CpUpnpOrgContentDirectory3C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	$(t4) -o $(proxySrcC)CpUpnpOrgContentDirectory3C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
$(proxySrcC)CpUpnpOrgRenderingControl1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	$(t4) -o $(proxySrcC)CpUpnpOrgRenderingControl1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
$(proxySrcC)CpUpnpOrgRenderingControl2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	$(t4) -o $(proxySrcC)CpUpnpOrgRenderingControl2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
$(proxySrcC)CpUpnpOrgScheduledRecording1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	$(t4) -o $(proxySrcC)CpUpnpOrgScheduledRecording1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
$(proxySrcC)CpUpnpOrgScheduledRecording2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	$(t4) -o $(proxySrcC)CpUpnpOrgScheduledRecording2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
$(proxySrcC)CpUpnpOrgSwitchPower1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	$(t4) -o $(proxySrcC)CpUpnpOrgSwitchPower1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
$(proxySrcC)CpUpnpOrgDimming1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	$(t4) -o $(proxySrcC)CpUpnpOrgDimming1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
$(proxySrcC)CpLinnCoUkComponent1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Component1.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkComponent1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
$(proxySrcC)CpLinnCoUkConfiguration1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Configuration1.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkConfiguration1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
$(proxySrcC)CpLinnCoUkDebug2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Debug2.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkDebug2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
$(proxySrcC)CpLinnCoUkDelay1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Delay1.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkDelay1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
$(proxySrcC)CpLinnCoUkDiagnostics1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Diagnostics1.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkDiagnostics1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
$(proxySrcC)CpLinnCoUkDs1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Ds1.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkDs1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
$(proxySrcC)CpLinnCoUkInfo1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Info1.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkInfo1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
$(proxySrcC)CpLinnCoUkJukebox1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Jukebox1.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkJukebox1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
$(proxySrcC)CpLinnCoUkMediaTime1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/MediaTime1.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkMediaTime1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
$(proxySrcC)CpLinnCoUkPlaylist1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Playlist1.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkPlaylist1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
$(proxySrcC)CpLinnCoUkPreamp4C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Preamp4.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkPreamp4C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
$(proxySrcC)CpLinnCoUkProduct1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Product1.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkProduct1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
$(proxySrcC)CpLinnCoUkProduct2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Product2.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkProduct2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
$(proxySrcC)CpLinnCoUkProduct3C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Product3.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkProduct3C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
$(proxySrcC)CpLinnCoUkProxyManager1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/ProxyManager1.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkProxyManager1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
$(proxySrcC)CpLinnCoUkPtest1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Ptest1.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkPtest1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
$(proxySrcC)CpLinnCoUkRadio1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Radio1.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkRadio1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
$(proxySrcC)CpLinnCoUkTime1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Time1.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkTime1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
$(proxySrcC)CpLinnCoUkUi2C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Ui2.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkUi2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
$(proxySrcC)CpLinnCoUkVolkano1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Linn/Volkano1.xml
	$(t4) -o $(proxySrcC)CpLinnCoUkVolkano1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
$(proxySrcC)CpZappOrgTestBasic1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	$(t4) -o $(proxySrcC)CpZappOrgTestBasic1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
$(proxySrcC)CpZappOrgTestWidget1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Zapp/Test/TestWidget1.xml
	$(t4) -o $(proxySrcC)CpZappOrgTestWidget1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestWidget1.xml" -a domain:zapp.org -a type:TestWidget -a version:1
$(proxySrcC)CpZappOrgTestWidgetController1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Zapp/Test/TestWidgetController1.xml
	$(t4) -o $(proxySrcC)CpZappOrgTestWidgetController1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestWidgetController1.xml" -a domain:zapp.org -a type:TestWidgetController -a version:1
$(proxySrcC)CpZappOrgTestLights1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Zapp/Test/TestLights1.xml
	$(t4) -o $(proxySrcC)CpZappOrgTestLights1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
$(proxySrcC)CpZappOrgTestDimmableLight1C.cpp : $(tt) T4/Templates/CpUpnpCSource.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	$(t4) -o $(proxySrcC)CpZappOrgTestDimmableLight1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

CpCs:   $(proxyCs)CpUpnpOrgAVTransport1.cs $(proxyCs)CpUpnpOrgAVTransport2.cs $(proxyCs)CpUpnpOrgConnectionManager1.cs $(proxyCs)CpUpnpOrgConnectionManager2.cs $(proxyCs)CpUpnpOrgContentDirectory1.cs $(proxyCs)CpUpnpOrgContentDirectory2.cs $(proxyCs)CpUpnpOrgContentDirectory3.cs $(proxyCs)CpUpnpOrgRenderingControl1.cs $(proxyCs)CpUpnpOrgRenderingControl2.cs $(proxyCs)CpUpnpOrgScheduledRecording1.cs $(proxyCs)CpUpnpOrgScheduledRecording2.cs $(proxyCs)CpUpnpOrgSwitchPower1.cs $(proxyCs)CpUpnpOrgDimming1.cs $(proxyCs)CpLinnCoUkComponent1.cs $(proxyCs)CpLinnCoUkConfiguration1.cs $(proxyCs)CpLinnCoUkDebug2.cs $(proxyCs)CpLinnCoUkDelay1.cs $(proxyCs)CpLinnCoUkDiagnostics1.cs $(proxyCs)CpLinnCoUkDs1.cs $(proxyCs)CpLinnCoUkInfo1.cs $(proxyCs)CpLinnCoUkJukebox1.cs $(proxyCs)CpLinnCoUkMediaTime1.cs $(proxyCs)CpLinnCoUkPlaylist1.cs $(proxyCs)CpLinnCoUkPreamp4.cs $(proxyCs)CpLinnCoUkProduct1.cs $(proxyCs)CpLinnCoUkProduct2.cs $(proxyCs)CpLinnCoUkProduct3.cs $(proxyCs)CpLinnCoUkProxyManager1.cs $(proxyCs)CpLinnCoUkPtest1.cs $(proxyCs)CpLinnCoUkRadio1.cs $(proxyCs)CpLinnCoUkTime1.cs $(proxyCs)CpLinnCoUkUi2.cs $(proxyCs)CpLinnCoUkVolkano1.cs $(proxyCs)CpZappOrgTestBasic1.cs $(proxyCs)CpZappOrgTestWidget1.cs $(proxyCs)CpZappOrgTestWidgetController1.cs $(proxyCs)CpZappOrgTestLights1.cs $(proxyCs)CpZappOrgTestDimmableLight1.cs
$(proxyCs)CpUpnpOrgAVTransport1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	$(t4) -o $(proxyCs)CpUpnpOrgAVTransport1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
$(proxyCs)CpUpnpOrgAVTransport2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	$(t4) -o $(proxyCs)CpUpnpOrgAVTransport2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
$(proxyCs)CpUpnpOrgConnectionManager1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	$(t4) -o $(proxyCs)CpUpnpOrgConnectionManager1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
$(proxyCs)CpUpnpOrgConnectionManager2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	$(t4) -o $(proxyCs)CpUpnpOrgConnectionManager2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
$(proxyCs)CpUpnpOrgContentDirectory1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	$(t4) -o $(proxyCs)CpUpnpOrgContentDirectory1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
$(proxyCs)CpUpnpOrgContentDirectory2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	$(t4) -o $(proxyCs)CpUpnpOrgContentDirectory2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
$(proxyCs)CpUpnpOrgContentDirectory3.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	$(t4) -o $(proxyCs)CpUpnpOrgContentDirectory3.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
$(proxyCs)CpUpnpOrgRenderingControl1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	$(t4) -o $(proxyCs)CpUpnpOrgRenderingControl1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
$(proxyCs)CpUpnpOrgRenderingControl2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	$(t4) -o $(proxyCs)CpUpnpOrgRenderingControl2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
$(proxyCs)CpUpnpOrgScheduledRecording1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	$(t4) -o $(proxyCs)CpUpnpOrgScheduledRecording1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
$(proxyCs)CpUpnpOrgScheduledRecording2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	$(t4) -o $(proxyCs)CpUpnpOrgScheduledRecording2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
$(proxyCs)CpUpnpOrgSwitchPower1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	$(t4) -o $(proxyCs)CpUpnpOrgSwitchPower1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
$(proxyCs)CpUpnpOrgDimming1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	$(t4) -o $(proxyCs)CpUpnpOrgDimming1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
$(proxyCs)CpLinnCoUkComponent1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Component1.xml
	$(t4) -o $(proxyCs)CpLinnCoUkComponent1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
$(proxyCs)CpLinnCoUkConfiguration1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Configuration1.xml
	$(t4) -o $(proxyCs)CpLinnCoUkConfiguration1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
$(proxyCs)CpLinnCoUkDebug2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Debug2.xml
	$(t4) -o $(proxyCs)CpLinnCoUkDebug2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
$(proxyCs)CpLinnCoUkDelay1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Delay1.xml
	$(t4) -o $(proxyCs)CpLinnCoUkDelay1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
$(proxyCs)CpLinnCoUkDiagnostics1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Diagnostics1.xml
	$(t4) -o $(proxyCs)CpLinnCoUkDiagnostics1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
$(proxyCs)CpLinnCoUkDs1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Ds1.xml
	$(t4) -o $(proxyCs)CpLinnCoUkDs1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
$(proxyCs)CpLinnCoUkInfo1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Info1.xml
	$(t4) -o $(proxyCs)CpLinnCoUkInfo1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
$(proxyCs)CpLinnCoUkJukebox1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Jukebox1.xml
	$(t4) -o $(proxyCs)CpLinnCoUkJukebox1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
$(proxyCs)CpLinnCoUkMediaTime1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/MediaTime1.xml
	$(t4) -o $(proxyCs)CpLinnCoUkMediaTime1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
$(proxyCs)CpLinnCoUkPlaylist1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Playlist1.xml
	$(t4) -o $(proxyCs)CpLinnCoUkPlaylist1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
$(proxyCs)CpLinnCoUkPreamp4.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Preamp4.xml
	$(t4) -o $(proxyCs)CpLinnCoUkPreamp4.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
$(proxyCs)CpLinnCoUkProduct1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Product1.xml
	$(t4) -o $(proxyCs)CpLinnCoUkProduct1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
$(proxyCs)CpLinnCoUkProduct2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Product2.xml
	$(t4) -o $(proxyCs)CpLinnCoUkProduct2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
$(proxyCs)CpLinnCoUkProduct3.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Product3.xml
	$(t4) -o $(proxyCs)CpLinnCoUkProduct3.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
$(proxyCs)CpLinnCoUkProxyManager1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/ProxyManager1.xml
	$(t4) -o $(proxyCs)CpLinnCoUkProxyManager1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
$(proxyCs)CpLinnCoUkPtest1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Ptest1.xml
	$(t4) -o $(proxyCs)CpLinnCoUkPtest1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
$(proxyCs)CpLinnCoUkRadio1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Radio1.xml
	$(t4) -o $(proxyCs)CpLinnCoUkRadio1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
$(proxyCs)CpLinnCoUkTime1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Time1.xml
	$(t4) -o $(proxyCs)CpLinnCoUkTime1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
$(proxyCs)CpLinnCoUkUi2.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Ui2.xml
	$(t4) -o $(proxyCs)CpLinnCoUkUi2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
$(proxyCs)CpLinnCoUkVolkano1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Linn/Volkano1.xml
	$(t4) -o $(proxyCs)CpLinnCoUkVolkano1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
$(proxyCs)CpZappOrgTestBasic1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	$(t4) -o $(proxyCs)CpZappOrgTestBasic1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
$(proxyCs)CpZappOrgTestWidget1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Zapp/Test/TestWidget1.xml
	$(t4) -o $(proxyCs)CpZappOrgTestWidget1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestWidget1.xml" -a domain:zapp.org -a type:TestWidget -a version:1
$(proxyCs)CpZappOrgTestWidgetController1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Zapp/Test/TestWidgetController1.xml
	$(t4) -o $(proxyCs)CpZappOrgTestWidgetController1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestWidgetController1.xml" -a domain:zapp.org -a type:TestWidgetController -a version:1
$(proxyCs)CpZappOrgTestLights1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Zapp/Test/TestLights1.xml
	$(t4) -o $(proxyCs)CpZappOrgTestLights1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
$(proxyCs)CpZappOrgTestDimmableLight1.cs : $(tt) T4/Templates/CpUpnpCs.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	$(t4) -o $(proxyCs)CpZappOrgTestDimmableLight1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

DvApiCppCore :   $(deviceApiCppCore)DvUpnpOrgAVTransport1.h $(deviceApiCppCore)DvUpnpOrgAVTransport2.h $(deviceApiCppCore)DvUpnpOrgConnectionManager1.h $(deviceApiCppCore)DvUpnpOrgConnectionManager2.h $(deviceApiCppCore)DvUpnpOrgContentDirectory1.h $(deviceApiCppCore)DvUpnpOrgContentDirectory2.h $(deviceApiCppCore)DvUpnpOrgContentDirectory3.h $(deviceApiCppCore)DvUpnpOrgRenderingControl1.h $(deviceApiCppCore)DvUpnpOrgRenderingControl2.h $(deviceApiCppCore)DvUpnpOrgScheduledRecording1.h $(deviceApiCppCore)DvUpnpOrgScheduledRecording2.h $(deviceApiCppCore)DvUpnpOrgSwitchPower1.h $(deviceApiCppCore)DvUpnpOrgDimming1.h $(deviceApiCppCore)DvLinnCoUkComponent1.h $(deviceApiCppCore)DvLinnCoUkConfiguration1.h $(deviceApiCppCore)DvLinnCoUkDebug2.h $(deviceApiCppCore)DvLinnCoUkDelay1.h $(deviceApiCppCore)DvLinnCoUkDiagnostics1.h $(deviceApiCppCore)DvLinnCoUkDs1.h $(deviceApiCppCore)DvLinnCoUkInfo1.h $(deviceApiCppCore)DvLinnCoUkJukebox1.h $(deviceApiCppCore)DvLinnCoUkMediaTime1.h $(deviceApiCppCore)DvLinnCoUkPlaylist1.h $(deviceApiCppCore)DvLinnCoUkPreamp4.h $(deviceApiCppCore)DvLinnCoUkProduct1.h $(deviceApiCppCore)DvLinnCoUkProduct2.h $(deviceApiCppCore)DvLinnCoUkProduct3.h $(deviceApiCppCore)DvLinnCoUkProxyManager1.h $(deviceApiCppCore)DvLinnCoUkPtest1.h $(deviceApiCppCore)DvLinnCoUkRadio1.h $(deviceApiCppCore)DvLinnCoUkTime1.h $(deviceApiCppCore)DvLinnCoUkUi2.h $(deviceApiCppCore)DvLinnCoUkVolkano1.h $(deviceApiCppCore)DvZappOrgTestBasic1.h $(deviceApiCppCore)DvZappOrgTestWidget1.h $(deviceApiCppCore)DvZappOrgTestWidgetController1.h $(deviceApiCppCore)DvZappOrgTestLights1.h $(deviceApiCppCore)DvZappOrgTestDimmableLight1.h
$(deviceApiCppCore)DvUpnpOrgAVTransport1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgAVTransport1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
$(deviceApiCppCore)DvUpnpOrgAVTransport2.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgAVTransport2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
$(deviceApiCppCore)DvUpnpOrgConnectionManager1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgConnectionManager1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
$(deviceApiCppCore)DvUpnpOrgConnectionManager2.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgConnectionManager2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
$(deviceApiCppCore)DvUpnpOrgContentDirectory1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgContentDirectory1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
$(deviceApiCppCore)DvUpnpOrgContentDirectory2.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgContentDirectory2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
$(deviceApiCppCore)DvUpnpOrgContentDirectory3.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgContentDirectory3.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
$(deviceApiCppCore)DvUpnpOrgRenderingControl1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgRenderingControl1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
$(deviceApiCppCore)DvUpnpOrgRenderingControl2.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgRenderingControl2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
$(deviceApiCppCore)DvUpnpOrgScheduledRecording1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgScheduledRecording1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
$(deviceApiCppCore)DvUpnpOrgScheduledRecording2.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgScheduledRecording2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
$(deviceApiCppCore)DvUpnpOrgSwitchPower1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgSwitchPower1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
$(deviceApiCppCore)DvUpnpOrgDimming1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgDimming1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
$(deviceApiCppCore)DvLinnCoUkComponent1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Component1.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkComponent1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
$(deviceApiCppCore)DvLinnCoUkConfiguration1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Configuration1.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkConfiguration1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
$(deviceApiCppCore)DvLinnCoUkDebug2.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Debug2.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkDebug2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
$(deviceApiCppCore)DvLinnCoUkDelay1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Delay1.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkDelay1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
$(deviceApiCppCore)DvLinnCoUkDiagnostics1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Diagnostics1.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkDiagnostics1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
$(deviceApiCppCore)DvLinnCoUkDs1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Ds1.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkDs1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
$(deviceApiCppCore)DvLinnCoUkInfo1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Info1.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkInfo1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
$(deviceApiCppCore)DvLinnCoUkJukebox1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Jukebox1.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkJukebox1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
$(deviceApiCppCore)DvLinnCoUkMediaTime1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/MediaTime1.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkMediaTime1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
$(deviceApiCppCore)DvLinnCoUkPlaylist1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Playlist1.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkPlaylist1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
$(deviceApiCppCore)DvLinnCoUkPreamp4.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Preamp4.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkPreamp4.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
$(deviceApiCppCore)DvLinnCoUkProduct1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Product1.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkProduct1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
$(deviceApiCppCore)DvLinnCoUkProduct2.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Product2.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkProduct2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
$(deviceApiCppCore)DvLinnCoUkProduct3.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Product3.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkProduct3.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
$(deviceApiCppCore)DvLinnCoUkProxyManager1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/ProxyManager1.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkProxyManager1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
$(deviceApiCppCore)DvLinnCoUkPtest1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Ptest1.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkPtest1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
$(deviceApiCppCore)DvLinnCoUkRadio1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Radio1.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkRadio1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
$(deviceApiCppCore)DvLinnCoUkTime1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Time1.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkTime1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
$(deviceApiCppCore)DvLinnCoUkUi2.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Ui2.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkUi2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
$(deviceApiCppCore)DvLinnCoUkVolkano1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Linn/Volkano1.xml
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkVolkano1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
$(deviceApiCppCore)DvZappOrgTestBasic1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	$(t4) -o $(deviceApiCppCore)DvZappOrgTestBasic1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
$(deviceApiCppCore)DvZappOrgTestWidget1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Zapp/Test/TestWidget1.xml
	$(t4) -o $(deviceApiCppCore)DvZappOrgTestWidget1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestWidget1.xml" -a domain:zapp.org -a type:TestWidget -a version:1
$(deviceApiCppCore)DvZappOrgTestWidgetController1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Zapp/Test/TestWidgetController1.xml
	$(t4) -o $(deviceApiCppCore)DvZappOrgTestWidgetController1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestWidgetController1.xml" -a domain:zapp.org -a type:TestWidgetController -a version:1
$(deviceApiCppCore)DvZappOrgTestLights1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	$(t4) -o $(deviceApiCppCore)DvZappOrgTestLights1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
$(deviceApiCppCore)DvZappOrgTestDimmableLight1.h : $(tt) T4/Templates/DvUpnpCppCoreHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	$(t4) -o $(deviceApiCppCore)DvZappOrgTestDimmableLight1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

DvSrcCppCore :   $(deviceSrcCppCore)DvUpnpOrgAVTransport1.cpp $(deviceSrcCppCore)DvUpnpOrgAVTransport2.cpp $(deviceSrcCppCore)DvUpnpOrgConnectionManager1.cpp $(deviceSrcCppCore)DvUpnpOrgConnectionManager2.cpp $(deviceSrcCppCore)DvUpnpOrgContentDirectory1.cpp $(deviceSrcCppCore)DvUpnpOrgContentDirectory2.cpp $(deviceSrcCppCore)DvUpnpOrgContentDirectory3.cpp $(deviceSrcCppCore)DvUpnpOrgRenderingControl1.cpp $(deviceSrcCppCore)DvUpnpOrgRenderingControl2.cpp $(deviceSrcCppCore)DvUpnpOrgScheduledRecording1.cpp $(deviceSrcCppCore)DvUpnpOrgScheduledRecording2.cpp $(deviceSrcCppCore)DvUpnpOrgSwitchPower1.cpp $(deviceSrcCppCore)DvUpnpOrgDimming1.cpp $(deviceSrcCppCore)DvLinnCoUkComponent1.cpp $(deviceSrcCppCore)DvLinnCoUkConfiguration1.cpp $(deviceSrcCppCore)DvLinnCoUkDebug2.cpp $(deviceSrcCppCore)DvLinnCoUkDelay1.cpp $(deviceSrcCppCore)DvLinnCoUkDiagnostics1.cpp $(deviceSrcCppCore)DvLinnCoUkDs1.cpp $(deviceSrcCppCore)DvLinnCoUkInfo1.cpp $(deviceSrcCppCore)DvLinnCoUkJukebox1.cpp $(deviceSrcCppCore)DvLinnCoUkMediaTime1.cpp $(deviceSrcCppCore)DvLinnCoUkPlaylist1.cpp $(deviceSrcCppCore)DvLinnCoUkPreamp4.cpp $(deviceSrcCppCore)DvLinnCoUkProduct1.cpp $(deviceSrcCppCore)DvLinnCoUkProduct2.cpp $(deviceSrcCppCore)DvLinnCoUkProduct3.cpp $(deviceSrcCppCore)DvLinnCoUkProxyManager1.cpp $(deviceSrcCppCore)DvLinnCoUkPtest1.cpp $(deviceSrcCppCore)DvLinnCoUkRadio1.cpp $(deviceSrcCppCore)DvLinnCoUkTime1.cpp $(deviceSrcCppCore)DvLinnCoUkUi2.cpp $(deviceSrcCppCore)DvLinnCoUkVolkano1.cpp $(deviceSrcCppCore)DvZappOrgTestBasic1.cpp $(deviceSrcCppCore)DvZappOrgTestWidget1.cpp $(deviceSrcCppCore)DvZappOrgTestWidgetController1.cpp $(deviceSrcCppCore)DvZappOrgTestLights1.cpp $(deviceSrcCppCore)DvZappOrgTestDimmableLight1.cpp
$(deviceSrcCppCore)DvUpnpOrgAVTransport1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgAVTransport1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
$(deviceSrcCppCore)DvUpnpOrgAVTransport2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgAVTransport2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
$(deviceSrcCppCore)DvUpnpOrgConnectionManager1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgConnectionManager1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
$(deviceSrcCppCore)DvUpnpOrgConnectionManager2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgConnectionManager2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
$(deviceSrcCppCore)DvUpnpOrgContentDirectory1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgContentDirectory1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
$(deviceSrcCppCore)DvUpnpOrgContentDirectory2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgContentDirectory2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
$(deviceSrcCppCore)DvUpnpOrgContentDirectory3.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgContentDirectory3.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
$(deviceSrcCppCore)DvUpnpOrgRenderingControl1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgRenderingControl1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
$(deviceSrcCppCore)DvUpnpOrgRenderingControl2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgRenderingControl2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
$(deviceSrcCppCore)DvUpnpOrgScheduledRecording1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgScheduledRecording1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
$(deviceSrcCppCore)DvUpnpOrgScheduledRecording2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgScheduledRecording2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
$(deviceSrcCppCore)DvUpnpOrgSwitchPower1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgSwitchPower1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
$(deviceSrcCppCore)DvUpnpOrgDimming1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgDimming1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
$(deviceSrcCppCore)DvLinnCoUkComponent1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Component1.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkComponent1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
$(deviceSrcCppCore)DvLinnCoUkConfiguration1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Configuration1.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkConfiguration1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
$(deviceSrcCppCore)DvLinnCoUkDebug2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Debug2.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkDebug2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
$(deviceSrcCppCore)DvLinnCoUkDelay1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Delay1.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkDelay1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
$(deviceSrcCppCore)DvLinnCoUkDiagnostics1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Diagnostics1.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkDiagnostics1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
$(deviceSrcCppCore)DvLinnCoUkDs1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Ds1.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkDs1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
$(deviceSrcCppCore)DvLinnCoUkInfo1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Info1.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkInfo1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
$(deviceSrcCppCore)DvLinnCoUkJukebox1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Jukebox1.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkJukebox1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
$(deviceSrcCppCore)DvLinnCoUkMediaTime1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/MediaTime1.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkMediaTime1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
$(deviceSrcCppCore)DvLinnCoUkPlaylist1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Playlist1.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkPlaylist1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
$(deviceSrcCppCore)DvLinnCoUkPreamp4.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Preamp4.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkPreamp4.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
$(deviceSrcCppCore)DvLinnCoUkProduct1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Product1.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkProduct1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
$(deviceSrcCppCore)DvLinnCoUkProduct2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Product2.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkProduct2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
$(deviceSrcCppCore)DvLinnCoUkProduct3.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Product3.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkProduct3.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
$(deviceSrcCppCore)DvLinnCoUkProxyManager1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/ProxyManager1.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkProxyManager1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
$(deviceSrcCppCore)DvLinnCoUkPtest1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Ptest1.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkPtest1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
$(deviceSrcCppCore)DvLinnCoUkRadio1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Radio1.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkRadio1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
$(deviceSrcCppCore)DvLinnCoUkTime1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Time1.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkTime1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
$(deviceSrcCppCore)DvLinnCoUkUi2.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Ui2.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkUi2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
$(deviceSrcCppCore)DvLinnCoUkVolkano1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Linn/Volkano1.xml
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkVolkano1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
$(deviceSrcCppCore)DvZappOrgTestBasic1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	$(t4) -o $(deviceSrcCppCore)DvZappOrgTestBasic1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
$(deviceSrcCppCore)DvZappOrgTestWidget1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Zapp/Test/TestWidget1.xml
	$(t4) -o $(deviceSrcCppCore)DvZappOrgTestWidget1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Zapp/Test/TestWidget1.xml" -a domain:zapp.org -a type:TestWidget -a version:1
$(deviceSrcCppCore)DvZappOrgTestWidgetController1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Zapp/Test/TestWidgetController1.xml
	$(t4) -o $(deviceSrcCppCore)DvZappOrgTestWidgetController1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Zapp/Test/TestWidgetController1.xml" -a domain:zapp.org -a type:TestWidgetController -a version:1
$(deviceSrcCppCore)DvZappOrgTestLights1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Zapp/Test/TestLights1.xml
	$(t4) -o $(deviceSrcCppCore)DvZappOrgTestLights1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
$(deviceSrcCppCore)DvZappOrgTestDimmableLight1.cpp : $(tt) T4/Templates/DvUpnpCppCoreSource.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	$(t4) -o $(deviceSrcCppCore)DvZappOrgTestDimmableLight1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

DvApiCppStd :   $(deviceApiCppStd)DvUpnpOrgAVTransport1.h $(deviceApiCppStd)DvUpnpOrgAVTransport2.h $(deviceApiCppStd)DvUpnpOrgConnectionManager1.h $(deviceApiCppStd)DvUpnpOrgConnectionManager2.h $(deviceApiCppStd)DvUpnpOrgContentDirectory1.h $(deviceApiCppStd)DvUpnpOrgContentDirectory2.h $(deviceApiCppStd)DvUpnpOrgContentDirectory3.h $(deviceApiCppStd)DvUpnpOrgRenderingControl1.h $(deviceApiCppStd)DvUpnpOrgRenderingControl2.h $(deviceApiCppStd)DvUpnpOrgScheduledRecording1.h $(deviceApiCppStd)DvUpnpOrgScheduledRecording2.h $(deviceApiCppStd)DvUpnpOrgSwitchPower1.h $(deviceApiCppStd)DvUpnpOrgDimming1.h $(deviceApiCppStd)DvLinnCoUkComponent1.h $(deviceApiCppStd)DvLinnCoUkConfiguration1.h $(deviceApiCppStd)DvLinnCoUkDebug2.h $(deviceApiCppStd)DvLinnCoUkDelay1.h $(deviceApiCppStd)DvLinnCoUkDiagnostics1.h $(deviceApiCppStd)DvLinnCoUkDs1.h $(deviceApiCppStd)DvLinnCoUkInfo1.h $(deviceApiCppStd)DvLinnCoUkJukebox1.h $(deviceApiCppStd)DvLinnCoUkMediaTime1.h $(deviceApiCppStd)DvLinnCoUkPlaylist1.h $(deviceApiCppStd)DvLinnCoUkPreamp4.h $(deviceApiCppStd)DvLinnCoUkProduct1.h $(deviceApiCppStd)DvLinnCoUkProduct2.h $(deviceApiCppStd)DvLinnCoUkProduct3.h $(deviceApiCppStd)DvLinnCoUkProxyManager1.h $(deviceApiCppStd)DvLinnCoUkPtest1.h $(deviceApiCppStd)DvLinnCoUkRadio1.h $(deviceApiCppStd)DvLinnCoUkTime1.h $(deviceApiCppStd)DvLinnCoUkUi2.h $(deviceApiCppStd)DvLinnCoUkVolkano1.h $(deviceApiCppStd)DvZappOrgTestBasic1.h $(deviceApiCppStd)DvZappOrgTestWidget1.h $(deviceApiCppStd)DvZappOrgTestWidgetController1.h $(deviceApiCppStd)DvZappOrgTestLights1.h $(deviceApiCppStd)DvZappOrgTestDimmableLight1.h
$(deviceApiCppStd)DvUpnpOrgAVTransport1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgAVTransport1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
$(deviceApiCppStd)DvUpnpOrgAVTransport2.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgAVTransport2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
$(deviceApiCppStd)DvUpnpOrgConnectionManager1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgConnectionManager1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
$(deviceApiCppStd)DvUpnpOrgConnectionManager2.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgConnectionManager2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
$(deviceApiCppStd)DvUpnpOrgContentDirectory1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgContentDirectory1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
$(deviceApiCppStd)DvUpnpOrgContentDirectory2.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgContentDirectory2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
$(deviceApiCppStd)DvUpnpOrgContentDirectory3.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgContentDirectory3.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
$(deviceApiCppStd)DvUpnpOrgRenderingControl1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgRenderingControl1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
$(deviceApiCppStd)DvUpnpOrgRenderingControl2.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgRenderingControl2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
$(deviceApiCppStd)DvUpnpOrgScheduledRecording1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgScheduledRecording1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
$(deviceApiCppStd)DvUpnpOrgScheduledRecording2.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgScheduledRecording2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
$(deviceApiCppStd)DvUpnpOrgSwitchPower1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgSwitchPower1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
$(deviceApiCppStd)DvUpnpOrgDimming1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgDimming1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
$(deviceApiCppStd)DvLinnCoUkComponent1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Component1.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkComponent1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
$(deviceApiCppStd)DvLinnCoUkConfiguration1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Configuration1.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkConfiguration1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
$(deviceApiCppStd)DvLinnCoUkDebug2.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Debug2.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkDebug2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
$(deviceApiCppStd)DvLinnCoUkDelay1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Delay1.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkDelay1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
$(deviceApiCppStd)DvLinnCoUkDiagnostics1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Diagnostics1.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkDiagnostics1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
$(deviceApiCppStd)DvLinnCoUkDs1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Ds1.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkDs1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
$(deviceApiCppStd)DvLinnCoUkInfo1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Info1.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkInfo1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
$(deviceApiCppStd)DvLinnCoUkJukebox1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Jukebox1.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkJukebox1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
$(deviceApiCppStd)DvLinnCoUkMediaTime1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/MediaTime1.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkMediaTime1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
$(deviceApiCppStd)DvLinnCoUkPlaylist1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Playlist1.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkPlaylist1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
$(deviceApiCppStd)DvLinnCoUkPreamp4.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Preamp4.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkPreamp4.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
$(deviceApiCppStd)DvLinnCoUkProduct1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Product1.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkProduct1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
$(deviceApiCppStd)DvLinnCoUkProduct2.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Product2.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkProduct2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
$(deviceApiCppStd)DvLinnCoUkProduct3.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Product3.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkProduct3.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
$(deviceApiCppStd)DvLinnCoUkProxyManager1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/ProxyManager1.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkProxyManager1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
$(deviceApiCppStd)DvLinnCoUkPtest1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Ptest1.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkPtest1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
$(deviceApiCppStd)DvLinnCoUkRadio1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Radio1.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkRadio1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
$(deviceApiCppStd)DvLinnCoUkTime1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Time1.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkTime1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
$(deviceApiCppStd)DvLinnCoUkUi2.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Ui2.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkUi2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
$(deviceApiCppStd)DvLinnCoUkVolkano1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Linn/Volkano1.xml
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkVolkano1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
$(deviceApiCppStd)DvZappOrgTestBasic1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	$(t4) -o $(deviceApiCppStd)DvZappOrgTestBasic1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
$(deviceApiCppStd)DvZappOrgTestWidget1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Zapp/Test/TestWidget1.xml
	$(t4) -o $(deviceApiCppStd)DvZappOrgTestWidget1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestWidget1.xml" -a domain:zapp.org -a type:TestWidget -a version:1
$(deviceApiCppStd)DvZappOrgTestWidgetController1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Zapp/Test/TestWidgetController1.xml
	$(t4) -o $(deviceApiCppStd)DvZappOrgTestWidgetController1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestWidgetController1.xml" -a domain:zapp.org -a type:TestWidgetController -a version:1
$(deviceApiCppStd)DvZappOrgTestLights1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	$(t4) -o $(deviceApiCppStd)DvZappOrgTestLights1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
$(deviceApiCppStd)DvZappOrgTestDimmableLight1.h : $(tt) T4/Templates/DvUpnpCppStdHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	$(t4) -o $(deviceApiCppStd)DvZappOrgTestDimmableLight1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

DvSrcCppStd :   $(deviceSrcCppStd)DvUpnpOrgAVTransport1Std.cpp $(deviceSrcCppStd)DvUpnpOrgAVTransport2Std.cpp $(deviceSrcCppStd)DvUpnpOrgConnectionManager1Std.cpp $(deviceSrcCppStd)DvUpnpOrgConnectionManager2Std.cpp $(deviceSrcCppStd)DvUpnpOrgContentDirectory1Std.cpp $(deviceSrcCppStd)DvUpnpOrgContentDirectory2Std.cpp $(deviceSrcCppStd)DvUpnpOrgContentDirectory3Std.cpp $(deviceSrcCppStd)DvUpnpOrgRenderingControl1Std.cpp $(deviceSrcCppStd)DvUpnpOrgRenderingControl2Std.cpp $(deviceSrcCppStd)DvUpnpOrgScheduledRecording1Std.cpp $(deviceSrcCppStd)DvUpnpOrgScheduledRecording2Std.cpp $(deviceSrcCppStd)DvUpnpOrgSwitchPower1Std.cpp $(deviceSrcCppStd)DvUpnpOrgDimming1Std.cpp $(deviceSrcCppStd)DvLinnCoUkComponent1Std.cpp $(deviceSrcCppStd)DvLinnCoUkConfiguration1Std.cpp $(deviceSrcCppStd)DvLinnCoUkDebug2Std.cpp $(deviceSrcCppStd)DvLinnCoUkDelay1Std.cpp $(deviceSrcCppStd)DvLinnCoUkDiagnostics1Std.cpp $(deviceSrcCppStd)DvLinnCoUkDs1Std.cpp $(deviceSrcCppStd)DvLinnCoUkInfo1Std.cpp $(deviceSrcCppStd)DvLinnCoUkJukebox1Std.cpp $(deviceSrcCppStd)DvLinnCoUkMediaTime1Std.cpp $(deviceSrcCppStd)DvLinnCoUkPlaylist1Std.cpp $(deviceSrcCppStd)DvLinnCoUkPreamp4Std.cpp $(deviceSrcCppStd)DvLinnCoUkProduct1Std.cpp $(deviceSrcCppStd)DvLinnCoUkProduct2Std.cpp $(deviceSrcCppStd)DvLinnCoUkProduct3Std.cpp $(deviceSrcCppStd)DvLinnCoUkProxyManager1Std.cpp $(deviceSrcCppStd)DvLinnCoUkPtest1Std.cpp $(deviceSrcCppStd)DvLinnCoUkRadio1Std.cpp $(deviceSrcCppStd)DvLinnCoUkTime1Std.cpp $(deviceSrcCppStd)DvLinnCoUkUi2Std.cpp $(deviceSrcCppStd)DvLinnCoUkVolkano1Std.cpp $(deviceSrcCppStd)DvZappOrgTestBasic1Std.cpp $(deviceSrcCppStd)DvZappOrgTestWidget1Std.cpp $(deviceSrcCppStd)DvZappOrgTestWidgetController1Std.cpp $(deviceSrcCppStd)DvZappOrgTestLights1Std.cpp $(deviceSrcCppStd)DvZappOrgTestDimmableLight1Std.cpp
$(deviceSrcCppStd)DvUpnpOrgAVTransport1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgAVTransport1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
$(deviceSrcCppStd)DvUpnpOrgAVTransport2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgAVTransport2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
$(deviceSrcCppStd)DvUpnpOrgConnectionManager1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgConnectionManager1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
$(deviceSrcCppStd)DvUpnpOrgConnectionManager2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgConnectionManager2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
$(deviceSrcCppStd)DvUpnpOrgContentDirectory1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgContentDirectory1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
$(deviceSrcCppStd)DvUpnpOrgContentDirectory2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgContentDirectory2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
$(deviceSrcCppStd)DvUpnpOrgContentDirectory3Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgContentDirectory3Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
$(deviceSrcCppStd)DvUpnpOrgRenderingControl1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgRenderingControl1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
$(deviceSrcCppStd)DvUpnpOrgRenderingControl2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgRenderingControl2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
$(deviceSrcCppStd)DvUpnpOrgScheduledRecording1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgScheduledRecording1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
$(deviceSrcCppStd)DvUpnpOrgScheduledRecording2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgScheduledRecording2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
$(deviceSrcCppStd)DvUpnpOrgSwitchPower1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgSwitchPower1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
$(deviceSrcCppStd)DvUpnpOrgDimming1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgDimming1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
$(deviceSrcCppStd)DvLinnCoUkComponent1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Component1.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkComponent1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
$(deviceSrcCppStd)DvLinnCoUkConfiguration1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Configuration1.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkConfiguration1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
$(deviceSrcCppStd)DvLinnCoUkDebug2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Debug2.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkDebug2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
$(deviceSrcCppStd)DvLinnCoUkDelay1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Delay1.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkDelay1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
$(deviceSrcCppStd)DvLinnCoUkDiagnostics1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Diagnostics1.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkDiagnostics1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
$(deviceSrcCppStd)DvLinnCoUkDs1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Ds1.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkDs1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
$(deviceSrcCppStd)DvLinnCoUkInfo1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Info1.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkInfo1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
$(deviceSrcCppStd)DvLinnCoUkJukebox1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Jukebox1.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkJukebox1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
$(deviceSrcCppStd)DvLinnCoUkMediaTime1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/MediaTime1.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkMediaTime1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
$(deviceSrcCppStd)DvLinnCoUkPlaylist1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Playlist1.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkPlaylist1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
$(deviceSrcCppStd)DvLinnCoUkPreamp4Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Preamp4.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkPreamp4Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
$(deviceSrcCppStd)DvLinnCoUkProduct1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Product1.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkProduct1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
$(deviceSrcCppStd)DvLinnCoUkProduct2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Product2.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkProduct2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
$(deviceSrcCppStd)DvLinnCoUkProduct3Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Product3.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkProduct3Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
$(deviceSrcCppStd)DvLinnCoUkProxyManager1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/ProxyManager1.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkProxyManager1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
$(deviceSrcCppStd)DvLinnCoUkPtest1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Ptest1.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkPtest1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
$(deviceSrcCppStd)DvLinnCoUkRadio1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Radio1.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkRadio1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
$(deviceSrcCppStd)DvLinnCoUkTime1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Time1.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkTime1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
$(deviceSrcCppStd)DvLinnCoUkUi2Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Ui2.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkUi2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
$(deviceSrcCppStd)DvLinnCoUkVolkano1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Linn/Volkano1.xml
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkVolkano1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
$(deviceSrcCppStd)DvZappOrgTestBasic1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	$(t4) -o $(deviceSrcCppStd)DvZappOrgTestBasic1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
$(deviceSrcCppStd)DvZappOrgTestWidget1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Zapp/Test/TestWidget1.xml
	$(t4) -o $(deviceSrcCppStd)DvZappOrgTestWidget1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Zapp/Test/TestWidget1.xml" -a domain:zapp.org -a type:TestWidget -a version:1
$(deviceSrcCppStd)DvZappOrgTestWidgetController1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Zapp/Test/TestWidgetController1.xml
	$(t4) -o $(deviceSrcCppStd)DvZappOrgTestWidgetController1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Zapp/Test/TestWidgetController1.xml" -a domain:zapp.org -a type:TestWidgetController -a version:1
$(deviceSrcCppStd)DvZappOrgTestLights1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Zapp/Test/TestLights1.xml
	$(t4) -o $(deviceSrcCppStd)DvZappOrgTestLights1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
$(deviceSrcCppStd)DvZappOrgTestDimmableLight1Std.cpp : $(tt) T4/Templates/DvUpnpCppStdSource.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	$(t4) -o $(deviceSrcCppStd)DvZappOrgTestDimmableLight1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

DvApiC :   $(deviceApiC)DvUpnpOrgAVTransport1.h $(deviceApiC)DvUpnpOrgAVTransport2.h $(deviceApiC)DvUpnpOrgConnectionManager1.h $(deviceApiC)DvUpnpOrgConnectionManager2.h $(deviceApiC)DvUpnpOrgContentDirectory1.h $(deviceApiC)DvUpnpOrgContentDirectory2.h $(deviceApiC)DvUpnpOrgContentDirectory3.h $(deviceApiC)DvUpnpOrgRenderingControl1.h $(deviceApiC)DvUpnpOrgRenderingControl2.h $(deviceApiC)DvUpnpOrgScheduledRecording1.h $(deviceApiC)DvUpnpOrgScheduledRecording2.h $(deviceApiC)DvUpnpOrgSwitchPower1.h $(deviceApiC)DvUpnpOrgDimming1.h $(deviceApiC)DvLinnCoUkComponent1.h $(deviceApiC)DvLinnCoUkConfiguration1.h $(deviceApiC)DvLinnCoUkDebug2.h $(deviceApiC)DvLinnCoUkDelay1.h $(deviceApiC)DvLinnCoUkDiagnostics1.h $(deviceApiC)DvLinnCoUkDs1.h $(deviceApiC)DvLinnCoUkInfo1.h $(deviceApiC)DvLinnCoUkJukebox1.h $(deviceApiC)DvLinnCoUkMediaTime1.h $(deviceApiC)DvLinnCoUkPlaylist1.h $(deviceApiC)DvLinnCoUkPreamp4.h $(deviceApiC)DvLinnCoUkProduct1.h $(deviceApiC)DvLinnCoUkProduct2.h $(deviceApiC)DvLinnCoUkProduct3.h $(deviceApiC)DvLinnCoUkProxyManager1.h $(deviceApiC)DvLinnCoUkPtest1.h $(deviceApiC)DvLinnCoUkRadio1.h $(deviceApiC)DvLinnCoUkTime1.h $(deviceApiC)DvLinnCoUkUi2.h $(deviceApiC)DvLinnCoUkVolkano1.h $(deviceApiC)DvZappOrgTestBasic1.h $(deviceApiC)DvZappOrgTestWidget1.h $(deviceApiC)DvZappOrgTestWidgetController1.h $(deviceApiC)DvZappOrgTestLights1.h $(deviceApiC)DvZappOrgTestDimmableLight1.h
$(deviceApiC)DvUpnpOrgAVTransport1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	$(t4) -o $(deviceApiC)DvUpnpOrgAVTransport1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
$(deviceApiC)DvUpnpOrgAVTransport2.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	$(t4) -o $(deviceApiC)DvUpnpOrgAVTransport2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
$(deviceApiC)DvUpnpOrgConnectionManager1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	$(t4) -o $(deviceApiC)DvUpnpOrgConnectionManager1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
$(deviceApiC)DvUpnpOrgConnectionManager2.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	$(t4) -o $(deviceApiC)DvUpnpOrgConnectionManager2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
$(deviceApiC)DvUpnpOrgContentDirectory1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	$(t4) -o $(deviceApiC)DvUpnpOrgContentDirectory1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
$(deviceApiC)DvUpnpOrgContentDirectory2.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	$(t4) -o $(deviceApiC)DvUpnpOrgContentDirectory2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
$(deviceApiC)DvUpnpOrgContentDirectory3.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	$(t4) -o $(deviceApiC)DvUpnpOrgContentDirectory3.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
$(deviceApiC)DvUpnpOrgRenderingControl1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	$(t4) -o $(deviceApiC)DvUpnpOrgRenderingControl1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
$(deviceApiC)DvUpnpOrgRenderingControl2.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	$(t4) -o $(deviceApiC)DvUpnpOrgRenderingControl2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
$(deviceApiC)DvUpnpOrgScheduledRecording1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	$(t4) -o $(deviceApiC)DvUpnpOrgScheduledRecording1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
$(deviceApiC)DvUpnpOrgScheduledRecording2.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	$(t4) -o $(deviceApiC)DvUpnpOrgScheduledRecording2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
$(deviceApiC)DvUpnpOrgSwitchPower1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	$(t4) -o $(deviceApiC)DvUpnpOrgSwitchPower1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
$(deviceApiC)DvUpnpOrgDimming1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	$(t4) -o $(deviceApiC)DvUpnpOrgDimming1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
$(deviceApiC)DvLinnCoUkComponent1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Component1.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkComponent1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
$(deviceApiC)DvLinnCoUkConfiguration1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Configuration1.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkConfiguration1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
$(deviceApiC)DvLinnCoUkDebug2.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Debug2.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkDebug2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
$(deviceApiC)DvLinnCoUkDelay1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Delay1.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkDelay1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
$(deviceApiC)DvLinnCoUkDiagnostics1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Diagnostics1.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkDiagnostics1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
$(deviceApiC)DvLinnCoUkDs1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Ds1.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkDs1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
$(deviceApiC)DvLinnCoUkInfo1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Info1.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkInfo1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
$(deviceApiC)DvLinnCoUkJukebox1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Jukebox1.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkJukebox1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
$(deviceApiC)DvLinnCoUkMediaTime1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/MediaTime1.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkMediaTime1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
$(deviceApiC)DvLinnCoUkPlaylist1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Playlist1.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkPlaylist1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
$(deviceApiC)DvLinnCoUkPreamp4.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Preamp4.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkPreamp4.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
$(deviceApiC)DvLinnCoUkProduct1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Product1.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkProduct1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
$(deviceApiC)DvLinnCoUkProduct2.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Product2.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkProduct2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
$(deviceApiC)DvLinnCoUkProduct3.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Product3.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkProduct3.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
$(deviceApiC)DvLinnCoUkProxyManager1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/ProxyManager1.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkProxyManager1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
$(deviceApiC)DvLinnCoUkPtest1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Ptest1.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkPtest1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
$(deviceApiC)DvLinnCoUkRadio1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Radio1.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkRadio1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
$(deviceApiC)DvLinnCoUkTime1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Time1.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkTime1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
$(deviceApiC)DvLinnCoUkUi2.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Ui2.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkUi2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
$(deviceApiC)DvLinnCoUkVolkano1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Linn/Volkano1.xml
	$(t4) -o $(deviceApiC)DvLinnCoUkVolkano1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
$(deviceApiC)DvZappOrgTestBasic1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	$(t4) -o $(deviceApiC)DvZappOrgTestBasic1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
$(deviceApiC)DvZappOrgTestWidget1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Zapp/Test/TestWidget1.xml
	$(t4) -o $(deviceApiC)DvZappOrgTestWidget1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestWidget1.xml" -a domain:zapp.org -a type:TestWidget -a version:1
$(deviceApiC)DvZappOrgTestWidgetController1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Zapp/Test/TestWidgetController1.xml
	$(t4) -o $(deviceApiC)DvZappOrgTestWidgetController1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestWidgetController1.xml" -a domain:zapp.org -a type:TestWidgetController -a version:1
$(deviceApiC)DvZappOrgTestLights1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Zapp/Test/TestLights1.xml
	$(t4) -o $(deviceApiC)DvZappOrgTestLights1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
$(deviceApiC)DvZappOrgTestDimmableLight1.h : $(tt) T4/Templates/DvUpnpCHeader.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	$(t4) -o $(deviceApiC)DvZappOrgTestDimmableLight1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

DvSrcC :   $(deviceSrcC)DvUpnpOrgAVTransport1C.cpp $(deviceSrcC)DvUpnpOrgAVTransport2C.cpp $(deviceSrcC)DvUpnpOrgConnectionManager1C.cpp $(deviceSrcC)DvUpnpOrgConnectionManager2C.cpp $(deviceSrcC)DvUpnpOrgContentDirectory1C.cpp $(deviceSrcC)DvUpnpOrgContentDirectory2C.cpp $(deviceSrcC)DvUpnpOrgContentDirectory3C.cpp $(deviceSrcC)DvUpnpOrgRenderingControl1C.cpp $(deviceSrcC)DvUpnpOrgRenderingControl2C.cpp $(deviceSrcC)DvUpnpOrgScheduledRecording1C.cpp $(deviceSrcC)DvUpnpOrgScheduledRecording2C.cpp $(deviceSrcC)DvUpnpOrgSwitchPower1C.cpp $(deviceSrcC)DvUpnpOrgDimming1C.cpp $(deviceSrcC)DvLinnCoUkComponent1C.cpp $(deviceSrcC)DvLinnCoUkConfiguration1C.cpp $(deviceSrcC)DvLinnCoUkDebug2C.cpp $(deviceSrcC)DvLinnCoUkDelay1C.cpp $(deviceSrcC)DvLinnCoUkDiagnostics1C.cpp $(deviceSrcC)DvLinnCoUkDs1C.cpp $(deviceSrcC)DvLinnCoUkInfo1C.cpp $(deviceSrcC)DvLinnCoUkJukebox1C.cpp $(deviceSrcC)DvLinnCoUkMediaTime1C.cpp $(deviceSrcC)DvLinnCoUkPlaylist1C.cpp $(deviceSrcC)DvLinnCoUkPreamp4C.cpp $(deviceSrcC)DvLinnCoUkProduct1C.cpp $(deviceSrcC)DvLinnCoUkProduct2C.cpp $(deviceSrcC)DvLinnCoUkProduct3C.cpp $(deviceSrcC)DvLinnCoUkProxyManager1C.cpp $(deviceSrcC)DvLinnCoUkPtest1C.cpp $(deviceSrcC)DvLinnCoUkRadio1C.cpp $(deviceSrcC)DvLinnCoUkTime1C.cpp $(deviceSrcC)DvLinnCoUkUi2C.cpp $(deviceSrcC)DvLinnCoUkVolkano1C.cpp $(deviceSrcC)DvZappOrgTestBasic1C.cpp $(deviceSrcC)DvZappOrgTestWidget1C.cpp $(deviceSrcC)DvZappOrgTestWidgetController1C.cpp $(deviceSrcC)DvZappOrgTestLights1C.cpp $(deviceSrcC)DvZappOrgTestDimmableLight1C.cpp
$(deviceSrcC)DvUpnpOrgAVTransport1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	$(t4) -o $(deviceSrcC)DvUpnpOrgAVTransport1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
$(deviceSrcC)DvUpnpOrgAVTransport2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	$(t4) -o $(deviceSrcC)DvUpnpOrgAVTransport2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
$(deviceSrcC)DvUpnpOrgConnectionManager1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	$(t4) -o $(deviceSrcC)DvUpnpOrgConnectionManager1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
$(deviceSrcC)DvUpnpOrgConnectionManager2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	$(t4) -o $(deviceSrcC)DvUpnpOrgConnectionManager2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
$(deviceSrcC)DvUpnpOrgContentDirectory1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	$(t4) -o $(deviceSrcC)DvUpnpOrgContentDirectory1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
$(deviceSrcC)DvUpnpOrgContentDirectory2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	$(t4) -o $(deviceSrcC)DvUpnpOrgContentDirectory2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
$(deviceSrcC)DvUpnpOrgContentDirectory3C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	$(t4) -o $(deviceSrcC)DvUpnpOrgContentDirectory3C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
$(deviceSrcC)DvUpnpOrgRenderingControl1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	$(t4) -o $(deviceSrcC)DvUpnpOrgRenderingControl1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
$(deviceSrcC)DvUpnpOrgRenderingControl2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	$(t4) -o $(deviceSrcC)DvUpnpOrgRenderingControl2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
$(deviceSrcC)DvUpnpOrgScheduledRecording1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	$(t4) -o $(deviceSrcC)DvUpnpOrgScheduledRecording1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
$(deviceSrcC)DvUpnpOrgScheduledRecording2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	$(t4) -o $(deviceSrcC)DvUpnpOrgScheduledRecording2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
$(deviceSrcC)DvUpnpOrgSwitchPower1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	$(t4) -o $(deviceSrcC)DvUpnpOrgSwitchPower1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
$(deviceSrcC)DvUpnpOrgDimming1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	$(t4) -o $(deviceSrcC)DvUpnpOrgDimming1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
$(deviceSrcC)DvLinnCoUkComponent1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Component1.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkComponent1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
$(deviceSrcC)DvLinnCoUkConfiguration1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Configuration1.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkConfiguration1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
$(deviceSrcC)DvLinnCoUkDebug2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Debug2.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkDebug2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
$(deviceSrcC)DvLinnCoUkDelay1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Delay1.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkDelay1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
$(deviceSrcC)DvLinnCoUkDiagnostics1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Diagnostics1.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkDiagnostics1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
$(deviceSrcC)DvLinnCoUkDs1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Ds1.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkDs1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
$(deviceSrcC)DvLinnCoUkInfo1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Info1.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkInfo1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
$(deviceSrcC)DvLinnCoUkJukebox1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Jukebox1.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkJukebox1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
$(deviceSrcC)DvLinnCoUkMediaTime1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/MediaTime1.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkMediaTime1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
$(deviceSrcC)DvLinnCoUkPlaylist1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Playlist1.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkPlaylist1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
$(deviceSrcC)DvLinnCoUkPreamp4C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Preamp4.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkPreamp4C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
$(deviceSrcC)DvLinnCoUkProduct1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Product1.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkProduct1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
$(deviceSrcC)DvLinnCoUkProduct2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Product2.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkProduct2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
$(deviceSrcC)DvLinnCoUkProduct3C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Product3.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkProduct3C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
$(deviceSrcC)DvLinnCoUkProxyManager1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/ProxyManager1.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkProxyManager1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
$(deviceSrcC)DvLinnCoUkPtest1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Ptest1.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkPtest1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
$(deviceSrcC)DvLinnCoUkRadio1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Radio1.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkRadio1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
$(deviceSrcC)DvLinnCoUkTime1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Time1.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkTime1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
$(deviceSrcC)DvLinnCoUkUi2C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Ui2.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkUi2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
$(deviceSrcC)DvLinnCoUkVolkano1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Linn/Volkano1.xml
	$(t4) -o $(deviceSrcC)DvLinnCoUkVolkano1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
$(deviceSrcC)DvZappOrgTestBasic1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	$(t4) -o $(deviceSrcC)DvZappOrgTestBasic1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
$(deviceSrcC)DvZappOrgTestWidget1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Zapp/Test/TestWidget1.xml
	$(t4) -o $(deviceSrcC)DvZappOrgTestWidget1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestWidget1.xml" -a domain:zapp.org -a type:TestWidget -a version:1
$(deviceSrcC)DvZappOrgTestWidgetController1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Zapp/Test/TestWidgetController1.xml
	$(t4) -o $(deviceSrcC)DvZappOrgTestWidgetController1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestWidgetController1.xml" -a domain:zapp.org -a type:TestWidgetController -a version:1
$(deviceSrcC)DvZappOrgTestLights1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Zapp/Test/TestLights1.xml
	$(t4) -o $(deviceSrcC)DvZappOrgTestLights1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
$(deviceSrcC)DvZappOrgTestDimmableLight1C.cpp : $(tt) T4/Templates/DvUpnpCSource.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	$(t4) -o $(deviceSrcC)DvZappOrgTestDimmableLight1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

DvCs:   $(deviceCs)DvUpnpOrgAVTransport1.cs $(deviceCs)DvUpnpOrgAVTransport2.cs $(deviceCs)DvUpnpOrgConnectionManager1.cs $(deviceCs)DvUpnpOrgConnectionManager2.cs $(deviceCs)DvUpnpOrgContentDirectory1.cs $(deviceCs)DvUpnpOrgContentDirectory2.cs $(deviceCs)DvUpnpOrgContentDirectory3.cs $(deviceCs)DvUpnpOrgRenderingControl1.cs $(deviceCs)DvUpnpOrgRenderingControl2.cs $(deviceCs)DvUpnpOrgScheduledRecording1.cs $(deviceCs)DvUpnpOrgScheduledRecording2.cs $(deviceCs)DvUpnpOrgSwitchPower1.cs $(deviceCs)DvUpnpOrgDimming1.cs $(deviceCs)DvLinnCoUkComponent1.cs $(deviceCs)DvLinnCoUkConfiguration1.cs $(deviceCs)DvLinnCoUkDebug2.cs $(deviceCs)DvLinnCoUkDelay1.cs $(deviceCs)DvLinnCoUkDiagnostics1.cs $(deviceCs)DvLinnCoUkDs1.cs $(deviceCs)DvLinnCoUkInfo1.cs $(deviceCs)DvLinnCoUkJukebox1.cs $(deviceCs)DvLinnCoUkMediaTime1.cs $(deviceCs)DvLinnCoUkPlaylist1.cs $(deviceCs)DvLinnCoUkPreamp4.cs $(deviceCs)DvLinnCoUkProduct1.cs $(deviceCs)DvLinnCoUkProduct2.cs $(deviceCs)DvLinnCoUkProduct3.cs $(deviceCs)DvLinnCoUkProxyManager1.cs $(deviceCs)DvLinnCoUkPtest1.cs $(deviceCs)DvLinnCoUkRadio1.cs $(deviceCs)DvLinnCoUkTime1.cs $(deviceCs)DvLinnCoUkUi2.cs $(deviceCs)DvLinnCoUkVolkano1.cs $(deviceCs)DvZappOrgTestBasic1.cs $(deviceCs)DvZappOrgTestWidget1.cs $(deviceCs)DvZappOrgTestWidgetController1.cs $(deviceCs)DvZappOrgTestLights1.cs $(deviceCs)DvZappOrgTestDimmableLight1.cs
$(deviceCs)DvUpnpOrgAVTransport1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	$(t4) -o $(deviceCs)DvUpnpOrgAVTransport1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
$(deviceCs)DvUpnpOrgAVTransport2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	$(t4) -o $(deviceCs)DvUpnpOrgAVTransport2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
$(deviceCs)DvUpnpOrgConnectionManager1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	$(t4) -o $(deviceCs)DvUpnpOrgConnectionManager1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
$(deviceCs)DvUpnpOrgConnectionManager2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	$(t4) -o $(deviceCs)DvUpnpOrgConnectionManager2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
$(deviceCs)DvUpnpOrgContentDirectory1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	$(t4) -o $(deviceCs)DvUpnpOrgContentDirectory1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
$(deviceCs)DvUpnpOrgContentDirectory2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	$(t4) -o $(deviceCs)DvUpnpOrgContentDirectory2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
$(deviceCs)DvUpnpOrgContentDirectory3.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	$(t4) -o $(deviceCs)DvUpnpOrgContentDirectory3.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
$(deviceCs)DvUpnpOrgRenderingControl1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	$(t4) -o $(deviceCs)DvUpnpOrgRenderingControl1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
$(deviceCs)DvUpnpOrgRenderingControl2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	$(t4) -o $(deviceCs)DvUpnpOrgRenderingControl2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
$(deviceCs)DvUpnpOrgScheduledRecording1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	$(t4) -o $(deviceCs)DvUpnpOrgScheduledRecording1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
$(deviceCs)DvUpnpOrgScheduledRecording2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	$(t4) -o $(deviceCs)DvUpnpOrgScheduledRecording2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
$(deviceCs)DvUpnpOrgSwitchPower1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	$(t4) -o $(deviceCs)DvUpnpOrgSwitchPower1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
$(deviceCs)DvUpnpOrgDimming1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	$(t4) -o $(deviceCs)DvUpnpOrgDimming1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
$(deviceCs)DvLinnCoUkComponent1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Component1.xml
	$(t4) -o $(deviceCs)DvLinnCoUkComponent1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
$(deviceCs)DvLinnCoUkConfiguration1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Configuration1.xml
	$(t4) -o $(deviceCs)DvLinnCoUkConfiguration1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
$(deviceCs)DvLinnCoUkDebug2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Debug2.xml
	$(t4) -o $(deviceCs)DvLinnCoUkDebug2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
$(deviceCs)DvLinnCoUkDelay1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Delay1.xml
	$(t4) -o $(deviceCs)DvLinnCoUkDelay1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
$(deviceCs)DvLinnCoUkDiagnostics1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Diagnostics1.xml
	$(t4) -o $(deviceCs)DvLinnCoUkDiagnostics1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
$(deviceCs)DvLinnCoUkDs1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Ds1.xml
	$(t4) -o $(deviceCs)DvLinnCoUkDs1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
$(deviceCs)DvLinnCoUkInfo1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Info1.xml
	$(t4) -o $(deviceCs)DvLinnCoUkInfo1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
$(deviceCs)DvLinnCoUkJukebox1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Jukebox1.xml
	$(t4) -o $(deviceCs)DvLinnCoUkJukebox1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
$(deviceCs)DvLinnCoUkMediaTime1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/MediaTime1.xml
	$(t4) -o $(deviceCs)DvLinnCoUkMediaTime1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
$(deviceCs)DvLinnCoUkPlaylist1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Playlist1.xml
	$(t4) -o $(deviceCs)DvLinnCoUkPlaylist1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
$(deviceCs)DvLinnCoUkPreamp4.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Preamp4.xml
	$(t4) -o $(deviceCs)DvLinnCoUkPreamp4.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
$(deviceCs)DvLinnCoUkProduct1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Product1.xml
	$(t4) -o $(deviceCs)DvLinnCoUkProduct1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
$(deviceCs)DvLinnCoUkProduct2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Product2.xml
	$(t4) -o $(deviceCs)DvLinnCoUkProduct2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
$(deviceCs)DvLinnCoUkProduct3.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Product3.xml
	$(t4) -o $(deviceCs)DvLinnCoUkProduct3.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
$(deviceCs)DvLinnCoUkProxyManager1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/ProxyManager1.xml
	$(t4) -o $(deviceCs)DvLinnCoUkProxyManager1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
$(deviceCs)DvLinnCoUkPtest1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Ptest1.xml
	$(t4) -o $(deviceCs)DvLinnCoUkPtest1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
$(deviceCs)DvLinnCoUkRadio1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Radio1.xml
	$(t4) -o $(deviceCs)DvLinnCoUkRadio1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
$(deviceCs)DvLinnCoUkTime1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Time1.xml
	$(t4) -o $(deviceCs)DvLinnCoUkTime1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
$(deviceCs)DvLinnCoUkUi2.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Ui2.xml
	$(t4) -o $(deviceCs)DvLinnCoUkUi2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
$(deviceCs)DvLinnCoUkVolkano1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Linn/Volkano1.xml
	$(t4) -o $(deviceCs)DvLinnCoUkVolkano1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
$(deviceCs)DvZappOrgTestBasic1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Zapp/Test/TestBasic1.xml
	$(t4) -o $(deviceCs)DvZappOrgTestBasic1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
$(deviceCs)DvZappOrgTestWidget1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Zapp/Test/TestWidget1.xml
	$(t4) -o $(deviceCs)DvZappOrgTestWidget1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestWidget1.xml" -a domain:zapp.org -a type:TestWidget -a version:1
$(deviceCs)DvZappOrgTestWidgetController1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Zapp/Test/TestWidgetController1.xml
	$(t4) -o $(deviceCs)DvZappOrgTestWidgetController1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestWidgetController1.xml" -a domain:zapp.org -a type:TestWidgetController -a version:1
$(deviceCs)DvZappOrgTestLights1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Zapp/Test/TestLights1.xml
	$(t4) -o $(deviceCs)DvZappOrgTestLights1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
$(deviceCs)DvZappOrgTestDimmableLight1.cs : $(tt) T4/Templates/DvUpnpCs.tt Service/Upnp/Zapp/Test/TestDimmableLight1.xml
	$(t4) -o $(deviceCs)DvZappOrgTestDimmableLight1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

