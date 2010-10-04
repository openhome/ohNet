# Auto-generated file.  DO NOT EDIT DIRECTLY
# Update CpUpnpMakeT4.tt and run 
#    [n]make -s -f T4[Linux|Windows].mak UpnpServiceMakeGen
# to apply any updates

GenAll: AllCp AllDv

AllCp: CpApiCppCore CpSrcCppCore CpApiCppStd CpSrcCppStd CpApiC CpSrcC CpCs

AllDv: DvApiCppCore DvSrcCppCore DvApiCppStd DvSrcCppStd DvApiC DvSrcC DvCs


CpApiCppCore: tt
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgAVTransport1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgAVTransport2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgConnectionManager1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgConnectionManager2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgContentDirectory1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgContentDirectory2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgContentDirectory3.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgRenderingControl1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgRenderingControl2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgScheduledRecording1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgScheduledRecording2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgSwitchPower1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpUpnpOrgDimming1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkComponent1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkConfiguration1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkDebug2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkDelay1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkDiagnostics1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkDs1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkInfo1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkJukebox1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkMediaTime1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkPlaylist1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkPreamp4.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkProduct1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkProduct2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkProduct3.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkProxyManager1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkPtest1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkRadio1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkTime1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkUi2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpLinnCoUkVolkano1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpZappOrgTestBasic1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpZappOrgTestLights1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1 -a buffer:1
	$(t4) -o $(proxyApiCppCore)CpZappOrgTestDimmableLight1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1 -a buffer:1

CpSrcCppCore: tt
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgAVTransport1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgAVTransport2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgConnectionManager1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgConnectionManager2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgContentDirectory1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgContentDirectory2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgContentDirectory3.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgRenderingControl1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgRenderingControl2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgScheduledRecording1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgScheduledRecording2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgSwitchPower1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
	$(t4) -o $(proxySrcCppCore)CpUpnpOrgDimming1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkComponent1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkConfiguration1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkDebug2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkDelay1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkDiagnostics1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkDs1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkInfo1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkJukebox1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkMediaTime1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkPlaylist1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkPreamp4.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkProduct1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkProduct2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkProduct3.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkProxyManager1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkPtest1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkRadio1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkTime1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkUi2.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
	$(t4) -o $(proxySrcCppCore)CpLinnCoUkVolkano1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
	$(t4) -o $(proxySrcCppCore)CpZappOrgTestBasic1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
	$(t4) -o $(proxySrcCppCore)CpZappOrgTestLights1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
	$(t4) -o $(proxySrcCppCore)CpZappOrgTestDimmableLight1.cpp T4/Templates/CpUpnpCppBufferSource.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

CpApiCppStd: tt
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgAVTransport1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgAVTransport2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgConnectionManager1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgConnectionManager2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgContentDirectory1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgContentDirectory2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgContentDirectory3.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgRenderingControl1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgRenderingControl2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgScheduledRecording1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgScheduledRecording2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgSwitchPower1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpUpnpOrgDimming1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkComponent1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkConfiguration1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkDebug2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkDelay1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkDiagnostics1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkDs1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkInfo1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkJukebox1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkMediaTime1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkPlaylist1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkPreamp4.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkProduct1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkProduct2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkProduct3.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkProxyManager1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkPtest1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkRadio1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkTime1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkUi2.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpLinnCoUkVolkano1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpZappOrgTestBasic1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpZappOrgTestLights1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1 -a buffer:0
	$(t4) -o $(proxyApiCppStd)CpZappOrgTestDimmableLight1.h T4/Templates/CpUpnpCppHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1 -a buffer:0

CpSrcCppStd: tt
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgAVTransport1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgAVTransport2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgConnectionManager1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgConnectionManager2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgContentDirectory1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgContentDirectory2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgContentDirectory3Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgRenderingControl1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgRenderingControl2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgScheduledRecording1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgScheduledRecording2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgSwitchPower1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
	$(t4) -o $(proxySrcCppStd)CpUpnpOrgDimming1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkComponent1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkConfiguration1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkDebug2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkDelay1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkDiagnostics1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkDs1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkInfo1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkJukebox1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkMediaTime1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkPlaylist1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkPreamp4Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkProduct1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkProduct2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkProduct3Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkProxyManager1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkPtest1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkRadio1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkTime1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkUi2Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
	$(t4) -o $(proxySrcCppStd)CpLinnCoUkVolkano1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
	$(t4) -o $(proxySrcCppStd)CpZappOrgTestBasic1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
	$(t4) -o $(proxySrcCppStd)CpZappOrgTestLights1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
	$(t4) -o $(proxySrcCppStd)CpZappOrgTestDimmableLight1Std.cpp T4/Templates/CpUpnpCppStringSource.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

CpApiC: tt
	$(t4) -o $(proxyApiC)CpUpnpOrgAVTransport1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
	$(t4) -o $(proxyApiC)CpUpnpOrgAVTransport2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
	$(t4) -o $(proxyApiC)CpUpnpOrgConnectionManager1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
	$(t4) -o $(proxyApiC)CpUpnpOrgConnectionManager2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
	$(t4) -o $(proxyApiC)CpUpnpOrgContentDirectory1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
	$(t4) -o $(proxyApiC)CpUpnpOrgContentDirectory2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
	$(t4) -o $(proxyApiC)CpUpnpOrgContentDirectory3.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
	$(t4) -o $(proxyApiC)CpUpnpOrgRenderingControl1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
	$(t4) -o $(proxyApiC)CpUpnpOrgRenderingControl2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
	$(t4) -o $(proxyApiC)CpUpnpOrgScheduledRecording1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
	$(t4) -o $(proxyApiC)CpUpnpOrgScheduledRecording2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
	$(t4) -o $(proxyApiC)CpUpnpOrgSwitchPower1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
	$(t4) -o $(proxyApiC)CpUpnpOrgDimming1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
	$(t4) -o $(proxyApiC)CpLinnCoUkComponent1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
	$(t4) -o $(proxyApiC)CpLinnCoUkConfiguration1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
	$(t4) -o $(proxyApiC)CpLinnCoUkDebug2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
	$(t4) -o $(proxyApiC)CpLinnCoUkDelay1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
	$(t4) -o $(proxyApiC)CpLinnCoUkDiagnostics1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
	$(t4) -o $(proxyApiC)CpLinnCoUkDs1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
	$(t4) -o $(proxyApiC)CpLinnCoUkInfo1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
	$(t4) -o $(proxyApiC)CpLinnCoUkJukebox1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
	$(t4) -o $(proxyApiC)CpLinnCoUkMediaTime1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
	$(t4) -o $(proxyApiC)CpLinnCoUkPlaylist1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
	$(t4) -o $(proxyApiC)CpLinnCoUkPreamp4.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
	$(t4) -o $(proxyApiC)CpLinnCoUkProduct1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
	$(t4) -o $(proxyApiC)CpLinnCoUkProduct2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
	$(t4) -o $(proxyApiC)CpLinnCoUkProduct3.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
	$(t4) -o $(proxyApiC)CpLinnCoUkProxyManager1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
	$(t4) -o $(proxyApiC)CpLinnCoUkPtest1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
	$(t4) -o $(proxyApiC)CpLinnCoUkRadio1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
	$(t4) -o $(proxyApiC)CpLinnCoUkTime1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
	$(t4) -o $(proxyApiC)CpLinnCoUkUi2.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
	$(t4) -o $(proxyApiC)CpLinnCoUkVolkano1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
	$(t4) -o $(proxyApiC)CpZappOrgTestBasic1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
	$(t4) -o $(proxyApiC)CpZappOrgTestLights1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
	$(t4) -o $(proxyApiC)CpZappOrgTestDimmableLight1.h T4/Templates/CpUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

CpSrcC: tt
	$(t4) -o $(proxySrcC)CpUpnpOrgAVTransport1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
	$(t4) -o $(proxySrcC)CpUpnpOrgAVTransport2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
	$(t4) -o $(proxySrcC)CpUpnpOrgConnectionManager1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
	$(t4) -o $(proxySrcC)CpUpnpOrgConnectionManager2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
	$(t4) -o $(proxySrcC)CpUpnpOrgContentDirectory1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
	$(t4) -o $(proxySrcC)CpUpnpOrgContentDirectory2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
	$(t4) -o $(proxySrcC)CpUpnpOrgContentDirectory3C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
	$(t4) -o $(proxySrcC)CpUpnpOrgRenderingControl1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
	$(t4) -o $(proxySrcC)CpUpnpOrgRenderingControl2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
	$(t4) -o $(proxySrcC)CpUpnpOrgScheduledRecording1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
	$(t4) -o $(proxySrcC)CpUpnpOrgScheduledRecording2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
	$(t4) -o $(proxySrcC)CpUpnpOrgSwitchPower1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
	$(t4) -o $(proxySrcC)CpUpnpOrgDimming1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
	$(t4) -o $(proxySrcC)CpLinnCoUkComponent1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
	$(t4) -o $(proxySrcC)CpLinnCoUkConfiguration1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
	$(t4) -o $(proxySrcC)CpLinnCoUkDebug2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
	$(t4) -o $(proxySrcC)CpLinnCoUkDelay1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
	$(t4) -o $(proxySrcC)CpLinnCoUkDiagnostics1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
	$(t4) -o $(proxySrcC)CpLinnCoUkDs1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
	$(t4) -o $(proxySrcC)CpLinnCoUkInfo1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
	$(t4) -o $(proxySrcC)CpLinnCoUkJukebox1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
	$(t4) -o $(proxySrcC)CpLinnCoUkMediaTime1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
	$(t4) -o $(proxySrcC)CpLinnCoUkPlaylist1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
	$(t4) -o $(proxySrcC)CpLinnCoUkPreamp4C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
	$(t4) -o $(proxySrcC)CpLinnCoUkProduct1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
	$(t4) -o $(proxySrcC)CpLinnCoUkProduct2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
	$(t4) -o $(proxySrcC)CpLinnCoUkProduct3C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
	$(t4) -o $(proxySrcC)CpLinnCoUkProxyManager1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
	$(t4) -o $(proxySrcC)CpLinnCoUkPtest1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
	$(t4) -o $(proxySrcC)CpLinnCoUkRadio1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
	$(t4) -o $(proxySrcC)CpLinnCoUkTime1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
	$(t4) -o $(proxySrcC)CpLinnCoUkUi2C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
	$(t4) -o $(proxySrcC)CpLinnCoUkVolkano1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
	$(t4) -o $(proxySrcC)CpZappOrgTestBasic1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
	$(t4) -o $(proxySrcC)CpZappOrgTestLights1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
	$(t4) -o $(proxySrcC)CpZappOrgTestDimmableLight1C.cpp T4/Templates/CpUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

CpCs: tt
	$(t4) -o $(proxyCs)CpUpnpOrgAVTransport1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
	$(t4) -o $(proxyCs)CpUpnpOrgAVTransport2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
	$(t4) -o $(proxyCs)CpUpnpOrgConnectionManager1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
	$(t4) -o $(proxyCs)CpUpnpOrgConnectionManager2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
	$(t4) -o $(proxyCs)CpUpnpOrgContentDirectory1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
	$(t4) -o $(proxyCs)CpUpnpOrgContentDirectory2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
	$(t4) -o $(proxyCs)CpUpnpOrgContentDirectory3.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
	$(t4) -o $(proxyCs)CpUpnpOrgRenderingControl1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
	$(t4) -o $(proxyCs)CpUpnpOrgRenderingControl2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
	$(t4) -o $(proxyCs)CpUpnpOrgScheduledRecording1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
	$(t4) -o $(proxyCs)CpUpnpOrgScheduledRecording2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
	$(t4) -o $(proxyCs)CpUpnpOrgSwitchPower1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
	$(t4) -o $(proxyCs)CpUpnpOrgDimming1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
	$(t4) -o $(proxyCs)CpLinnCoUkComponent1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
	$(t4) -o $(proxyCs)CpLinnCoUkConfiguration1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
	$(t4) -o $(proxyCs)CpLinnCoUkDebug2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
	$(t4) -o $(proxyCs)CpLinnCoUkDelay1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
	$(t4) -o $(proxyCs)CpLinnCoUkDiagnostics1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
	$(t4) -o $(proxyCs)CpLinnCoUkDs1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
	$(t4) -o $(proxyCs)CpLinnCoUkInfo1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
	$(t4) -o $(proxyCs)CpLinnCoUkJukebox1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
	$(t4) -o $(proxyCs)CpLinnCoUkMediaTime1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
	$(t4) -o $(proxyCs)CpLinnCoUkPlaylist1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
	$(t4) -o $(proxyCs)CpLinnCoUkPreamp4.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
	$(t4) -o $(proxyCs)CpLinnCoUkProduct1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
	$(t4) -o $(proxyCs)CpLinnCoUkProduct2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
	$(t4) -o $(proxyCs)CpLinnCoUkProduct3.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
	$(t4) -o $(proxyCs)CpLinnCoUkProxyManager1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
	$(t4) -o $(proxyCs)CpLinnCoUkPtest1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
	$(t4) -o $(proxyCs)CpLinnCoUkRadio1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
	$(t4) -o $(proxyCs)CpLinnCoUkTime1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
	$(t4) -o $(proxyCs)CpLinnCoUkUi2.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
	$(t4) -o $(proxyCs)CpLinnCoUkVolkano1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
	$(t4) -o $(proxyCs)CpZappOrgTestBasic1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
	$(t4) -o $(proxyCs)CpZappOrgTestLights1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
	$(t4) -o $(proxyCs)CpZappOrgTestDimmableLight1.cs T4/Templates/CpUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

DvApiCppCore : tt
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgAVTransport1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgAVTransport2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgConnectionManager1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgConnectionManager2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgContentDirectory1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgContentDirectory2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgContentDirectory3.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgRenderingControl1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgRenderingControl2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgScheduledRecording1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgScheduledRecording2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgSwitchPower1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
	$(t4) -o $(deviceApiCppCore)DvUpnpOrgDimming1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkComponent1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkConfiguration1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkDebug2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkDelay1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkDiagnostics1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkDs1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkInfo1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkJukebox1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkMediaTime1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkPlaylist1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkPreamp4.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkProduct1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkProduct2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkProduct3.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkProxyManager1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkPtest1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkRadio1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkTime1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkUi2.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
	$(t4) -o $(deviceApiCppCore)DvLinnCoUkVolkano1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
	$(t4) -o $(deviceApiCppCore)DvZappOrgTestBasic1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
	$(t4) -o $(deviceApiCppCore)DvZappOrgTestLights1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
	$(t4) -o $(deviceApiCppCore)DvZappOrgTestDimmableLight1.h T4/Templates/DvUpnpCppCoreHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

DvSrcCppCore : tt
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgAVTransport1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgAVTransport2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgConnectionManager1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgConnectionManager2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgContentDirectory1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgContentDirectory2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgContentDirectory3.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgRenderingControl1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgRenderingControl2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgScheduledRecording1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgScheduledRecording2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgSwitchPower1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
	$(t4) -o $(deviceSrcCppCore)DvUpnpOrgDimming1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkComponent1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkConfiguration1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkDebug2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkDelay1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkDiagnostics1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkDs1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkInfo1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkJukebox1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkMediaTime1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkPlaylist1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkPreamp4.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkProduct1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkProduct2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkProduct3.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkProxyManager1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkPtest1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkRadio1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkTime1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkUi2.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
	$(t4) -o $(deviceSrcCppCore)DvLinnCoUkVolkano1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
	$(t4) -o $(deviceSrcCppCore)DvZappOrgTestBasic1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
	$(t4) -o $(deviceSrcCppCore)DvZappOrgTestLights1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
	$(t4) -o $(deviceSrcCppCore)DvZappOrgTestDimmableLight1.cpp T4/Templates/DvUpnpCppCoreSource.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

DvApiCppStd : tt
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgAVTransport1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgAVTransport2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgConnectionManager1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgConnectionManager2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgContentDirectory1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgContentDirectory2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgContentDirectory3.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgRenderingControl1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgRenderingControl2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgScheduledRecording1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgScheduledRecording2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgSwitchPower1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
	$(t4) -o $(deviceApiCppStd)DvUpnpOrgDimming1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkComponent1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkConfiguration1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkDebug2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkDelay1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkDiagnostics1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkDs1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkInfo1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkJukebox1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkMediaTime1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkPlaylist1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkPreamp4.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkProduct1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkProduct2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkProduct3.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkProxyManager1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkPtest1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkRadio1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkTime1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkUi2.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
	$(t4) -o $(deviceApiCppStd)DvLinnCoUkVolkano1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
	$(t4) -o $(deviceApiCppStd)DvZappOrgTestBasic1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
	$(t4) -o $(deviceApiCppStd)DvZappOrgTestLights1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
	$(t4) -o $(deviceApiCppStd)DvZappOrgTestDimmableLight1.h T4/Templates/DvUpnpCppStdHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

DvSrcCppStd : tt
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgAVTransport1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgAVTransport2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgConnectionManager1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgConnectionManager2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgContentDirectory1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgContentDirectory2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgContentDirectory3Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgRenderingControl1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgRenderingControl2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgScheduledRecording1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgScheduledRecording2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgSwitchPower1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
	$(t4) -o $(deviceSrcCppStd)DvUpnpOrgDimming1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkComponent1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkConfiguration1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkDebug2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkDelay1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkDiagnostics1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkDs1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkInfo1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkJukebox1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkMediaTime1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkPlaylist1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkPreamp4Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkProduct1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkProduct2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkProduct3Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkProxyManager1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkPtest1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkRadio1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkTime1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkUi2Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
	$(t4) -o $(deviceSrcCppStd)DvLinnCoUkVolkano1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
	$(t4) -o $(deviceSrcCppStd)DvZappOrgTestBasic1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
	$(t4) -o $(deviceSrcCppStd)DvZappOrgTestLights1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
	$(t4) -o $(deviceSrcCppStd)DvZappOrgTestDimmableLight1Std.cpp T4/Templates/DvUpnpCppStdSource.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

DvApiC : tt
	$(t4) -o $(deviceApiC)DvUpnpOrgAVTransport1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
	$(t4) -o $(deviceApiC)DvUpnpOrgAVTransport2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
	$(t4) -o $(deviceApiC)DvUpnpOrgConnectionManager1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
	$(t4) -o $(deviceApiC)DvUpnpOrgConnectionManager2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
	$(t4) -o $(deviceApiC)DvUpnpOrgContentDirectory1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
	$(t4) -o $(deviceApiC)DvUpnpOrgContentDirectory2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
	$(t4) -o $(deviceApiC)DvUpnpOrgContentDirectory3.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
	$(t4) -o $(deviceApiC)DvUpnpOrgRenderingControl1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
	$(t4) -o $(deviceApiC)DvUpnpOrgRenderingControl2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
	$(t4) -o $(deviceApiC)DvUpnpOrgScheduledRecording1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
	$(t4) -o $(deviceApiC)DvUpnpOrgScheduledRecording2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
	$(t4) -o $(deviceApiC)DvUpnpOrgSwitchPower1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
	$(t4) -o $(deviceApiC)DvUpnpOrgDimming1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
	$(t4) -o $(deviceApiC)DvLinnCoUkComponent1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
	$(t4) -o $(deviceApiC)DvLinnCoUkConfiguration1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
	$(t4) -o $(deviceApiC)DvLinnCoUkDebug2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
	$(t4) -o $(deviceApiC)DvLinnCoUkDelay1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
	$(t4) -o $(deviceApiC)DvLinnCoUkDiagnostics1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
	$(t4) -o $(deviceApiC)DvLinnCoUkDs1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
	$(t4) -o $(deviceApiC)DvLinnCoUkInfo1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
	$(t4) -o $(deviceApiC)DvLinnCoUkJukebox1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
	$(t4) -o $(deviceApiC)DvLinnCoUkMediaTime1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
	$(t4) -o $(deviceApiC)DvLinnCoUkPlaylist1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
	$(t4) -o $(deviceApiC)DvLinnCoUkPreamp4.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
	$(t4) -o $(deviceApiC)DvLinnCoUkProduct1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
	$(t4) -o $(deviceApiC)DvLinnCoUkProduct2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
	$(t4) -o $(deviceApiC)DvLinnCoUkProduct3.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
	$(t4) -o $(deviceApiC)DvLinnCoUkProxyManager1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
	$(t4) -o $(deviceApiC)DvLinnCoUkPtest1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
	$(t4) -o $(deviceApiC)DvLinnCoUkRadio1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
	$(t4) -o $(deviceApiC)DvLinnCoUkTime1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
	$(t4) -o $(deviceApiC)DvLinnCoUkUi2.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
	$(t4) -o $(deviceApiC)DvLinnCoUkVolkano1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
	$(t4) -o $(deviceApiC)DvZappOrgTestBasic1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
	$(t4) -o $(deviceApiC)DvZappOrgTestLights1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
	$(t4) -o $(deviceApiC)DvZappOrgTestDimmableLight1.h T4/Templates/DvUpnpCHeader.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

DvSrcC : tt
	$(t4) -o $(deviceSrcC)DvUpnpOrgAVTransport1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
	$(t4) -o $(deviceSrcC)DvUpnpOrgAVTransport2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
	$(t4) -o $(deviceSrcC)DvUpnpOrgConnectionManager1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
	$(t4) -o $(deviceSrcC)DvUpnpOrgConnectionManager2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
	$(t4) -o $(deviceSrcC)DvUpnpOrgContentDirectory1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
	$(t4) -o $(deviceSrcC)DvUpnpOrgContentDirectory2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
	$(t4) -o $(deviceSrcC)DvUpnpOrgContentDirectory3C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
	$(t4) -o $(deviceSrcC)DvUpnpOrgRenderingControl1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
	$(t4) -o $(deviceSrcC)DvUpnpOrgRenderingControl2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
	$(t4) -o $(deviceSrcC)DvUpnpOrgScheduledRecording1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
	$(t4) -o $(deviceSrcC)DvUpnpOrgScheduledRecording2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
	$(t4) -o $(deviceSrcC)DvUpnpOrgSwitchPower1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
	$(t4) -o $(deviceSrcC)DvUpnpOrgDimming1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
	$(t4) -o $(deviceSrcC)DvLinnCoUkComponent1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
	$(t4) -o $(deviceSrcC)DvLinnCoUkConfiguration1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
	$(t4) -o $(deviceSrcC)DvLinnCoUkDebug2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
	$(t4) -o $(deviceSrcC)DvLinnCoUkDelay1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
	$(t4) -o $(deviceSrcC)DvLinnCoUkDiagnostics1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
	$(t4) -o $(deviceSrcC)DvLinnCoUkDs1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
	$(t4) -o $(deviceSrcC)DvLinnCoUkInfo1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
	$(t4) -o $(deviceSrcC)DvLinnCoUkJukebox1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
	$(t4) -o $(deviceSrcC)DvLinnCoUkMediaTime1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
	$(t4) -o $(deviceSrcC)DvLinnCoUkPlaylist1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
	$(t4) -o $(deviceSrcC)DvLinnCoUkPreamp4C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
	$(t4) -o $(deviceSrcC)DvLinnCoUkProduct1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
	$(t4) -o $(deviceSrcC)DvLinnCoUkProduct2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
	$(t4) -o $(deviceSrcC)DvLinnCoUkProduct3C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
	$(t4) -o $(deviceSrcC)DvLinnCoUkProxyManager1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
	$(t4) -o $(deviceSrcC)DvLinnCoUkPtest1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
	$(t4) -o $(deviceSrcC)DvLinnCoUkRadio1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
	$(t4) -o $(deviceSrcC)DvLinnCoUkTime1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
	$(t4) -o $(deviceSrcC)DvLinnCoUkUi2C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
	$(t4) -o $(deviceSrcC)DvLinnCoUkVolkano1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
	$(t4) -o $(deviceSrcC)DvZappOrgTestBasic1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
	$(t4) -o $(deviceSrcC)DvZappOrgTestLights1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
	$(t4) -o $(deviceSrcC)DvZappOrgTestDimmableLight1C.cpp T4/Templates/DvUpnpCSource.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

DvCs: tt
	$(t4) -o $(deviceCs)DvUpnpOrgAVTransport1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" -a domain:upnp.org -a type:AVTransport -a version:1
	$(t4) -o $(deviceCs)DvUpnpOrgAVTransport2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" -a domain:upnp.org -a type:AVTransport -a version:2
	$(t4) -o $(deviceCs)DvUpnpOrgConnectionManager1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" -a domain:upnp.org -a type:ConnectionManager -a version:1
	$(t4) -o $(deviceCs)DvUpnpOrgConnectionManager2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" -a domain:upnp.org -a type:ConnectionManager -a version:2
	$(t4) -o $(deviceCs)DvUpnpOrgContentDirectory1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" -a domain:upnp.org -a type:ContentDirectory -a version:1
	$(t4) -o $(deviceCs)DvUpnpOrgContentDirectory2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" -a domain:upnp.org -a type:ContentDirectory -a version:2
	$(t4) -o $(deviceCs)DvUpnpOrgContentDirectory3.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" -a domain:upnp.org -a type:ContentDirectory -a version:3
	$(t4) -o $(deviceCs)DvUpnpOrgRenderingControl1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" -a domain:upnp.org -a type:RenderingControl -a version:1
	$(t4) -o $(deviceCs)DvUpnpOrgRenderingControl2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" -a domain:upnp.org -a type:RenderingControl -a version:2
	$(t4) -o $(deviceCs)DvUpnpOrgScheduledRecording1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:1
	$(t4) -o $(deviceCs)DvUpnpOrgScheduledRecording2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" -a domain:upnp.org -a type:ScheduledRecording -a version:2
	$(t4) -o $(deviceCs)DvUpnpOrgSwitchPower1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/SwitchPower1.xml" -a domain:upnp.org -a type:SwitchPower -a version:1
	$(t4) -o $(deviceCs)DvUpnpOrgDimming1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Upnp/Lighting Controls_1/Dimming1.xml" -a domain:upnp.org -a type:Dimming -a version:1
	$(t4) -o $(deviceCs)DvLinnCoUkComponent1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Component1.xml" -a domain:linn.co.uk -a type:Component -a version:1
	$(t4) -o $(deviceCs)DvLinnCoUkConfiguration1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Configuration1.xml" -a domain:linn.co.uk -a type:Configuration -a version:1
	$(t4) -o $(deviceCs)DvLinnCoUkDebug2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Debug2.xml" -a domain:linn.co.uk -a type:Debug -a version:2
	$(t4) -o $(deviceCs)DvLinnCoUkDelay1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Delay1.xml" -a domain:linn.co.uk -a type:Delay -a version:1
	$(t4) -o $(deviceCs)DvLinnCoUkDiagnostics1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Diagnostics1.xml" -a domain:linn.co.uk -a type:Diagnostics -a version:1
	$(t4) -o $(deviceCs)DvLinnCoUkDs1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Ds1.xml" -a domain:linn.co.uk -a type:Ds -a version:1
	$(t4) -o $(deviceCs)DvLinnCoUkInfo1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Info1.xml" -a domain:linn.co.uk -a type:Info -a version:1
	$(t4) -o $(deviceCs)DvLinnCoUkJukebox1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Jukebox1.xml" -a domain:linn.co.uk -a type:Jukebox -a version:1
	$(t4) -o $(deviceCs)DvLinnCoUkMediaTime1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/MediaTime1.xml" -a domain:linn.co.uk -a type:MediaTime -a version:1
	$(t4) -o $(deviceCs)DvLinnCoUkPlaylist1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Playlist1.xml" -a domain:linn.co.uk -a type:Playlist -a version:1
	$(t4) -o $(deviceCs)DvLinnCoUkPreamp4.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Preamp4.xml" -a domain:linn.co.uk -a type:Preamp -a version:4
	$(t4) -o $(deviceCs)DvLinnCoUkProduct1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Product1.xml" -a domain:linn.co.uk -a type:Product -a version:1
	$(t4) -o $(deviceCs)DvLinnCoUkProduct2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Product2.xml" -a domain:linn.co.uk -a type:Product -a version:2
	$(t4) -o $(deviceCs)DvLinnCoUkProduct3.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Product3.xml" -a domain:linn.co.uk -a type:Product -a version:3
	$(t4) -o $(deviceCs)DvLinnCoUkProxyManager1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/ProxyManager1.xml" -a domain:linn.co.uk -a type:ProxyManager -a version:1
	$(t4) -o $(deviceCs)DvLinnCoUkPtest1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Ptest1.xml" -a domain:linn.co.uk -a type:Ptest -a version:1
	$(t4) -o $(deviceCs)DvLinnCoUkRadio1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Radio1.xml" -a domain:linn.co.uk -a type:Radio -a version:1
	$(t4) -o $(deviceCs)DvLinnCoUkTime1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Time1.xml" -a domain:linn.co.uk -a type:Time -a version:1
	$(t4) -o $(deviceCs)DvLinnCoUkUi2.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Ui2.xml" -a domain:linn.co.uk -a type:Ui -a version:2
	$(t4) -o $(deviceCs)DvLinnCoUkVolkano1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Linn/Volkano1.xml" -a domain:linn.co.uk -a type:Volkano -a version:1
	$(t4) -o $(deviceCs)DvZappOrgTestBasic1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestBasic1.xml" -a domain:zapp.org -a type:TestBasic -a version:1
	$(t4) -o $(deviceCs)DvZappOrgTestLights1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestLights1.xml" -a domain:zapp.org -a type:TestLights -a version:1
	$(t4) -o $(deviceCs)DvZappOrgTestDimmableLight1.cs T4/Templates/DvUpnpCs.tt -a "xml:Service/Upnp/Zapp/Test/TestDimmableLight1.xml" -a domain:zapp.org -a type:TestDimmableLight -a version:1

UpnpServiceMakeGen : UpnpServiceMake.dll tt
	$(t4) -o T4.mak T4/Templates/UpnpMakeT4.tt -a xml:Service/Services.xml
	$(t4) -o Proxies.mak T4/Templates/CpUpnpMakeProxies.tt -a xml:Service/Services.xml
	$(t4) -o Devices.mak T4/Templates/DvUpnpMakeDevices.tt -a xml:Service/Services.xml

