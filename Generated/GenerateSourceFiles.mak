# Auto-generated file.  DO NOT EDIT DIRECTLY
# Update UpnpMakeT4.tt and run 
#    make generate-makefiles
# to apply any updates

GenAll: AllCp AllDv

AllCp: CpCppCore CpCppStd CpC CpCs CpJava CpJs

AllDv: DvCppCore DvCppStd DvC DvCs DvJava


CpCppCore:   $(proxyCppCore)CpUpnpOrgAVTransport1.cpp $(proxyCppCore)CpUpnpOrgAVTransport2.cpp $(proxyCppCore)CpUpnpOrgConnectionManager1.cpp $(proxyCppCore)CpUpnpOrgConnectionManager2.cpp $(proxyCppCore)CpUpnpOrgContentDirectory1.cpp $(proxyCppCore)CpUpnpOrgContentDirectory2.cpp $(proxyCppCore)CpUpnpOrgContentDirectory3.cpp $(proxyCppCore)CpUpnpOrgRenderingControl1.cpp $(proxyCppCore)CpUpnpOrgRenderingControl2.cpp $(proxyCppCore)CpUpnpOrgScheduledRecording1.cpp $(proxyCppCore)CpUpnpOrgScheduledRecording2.cpp $(proxyCppCore)CpUpnpOrgSwitchPower1.cpp $(proxyCppCore)CpUpnpOrgDimming1.cpp $(proxyCppCore)CpAvOpenhomeOrgInfo1.cpp $(proxyCppCore)CpAvOpenhomeOrgTime1.cpp $(proxyCppCore)CpAvOpenhomeOrgPlaylist1.cpp $(proxyCppCore)CpAvOpenhomeOrgVolume1.cpp $(proxyCppCore)CpAvOpenhomeOrgProduct1.cpp $(proxyCppCore)CpAvOpenhomeOrgRadio1.cpp $(proxyCppCore)CpAvOpenhomeOrgReceiver1.cpp $(proxyCppCore)CpAvOpenhomeOrgSender1.cpp $(proxyCppCore)CpAvOpenhomeOrgPlaylistManager1.cpp $(proxyCppCore)CpAvOpenhomeOrgMediaServer1.cpp $(proxyCppCore)CpAvOpenhomeOrgNetworkMonitor1.cpp $(proxyCppCore)CpOpenhomeOrgTestBasic1.cpp $(proxyCppCore)CpOpenhomeOrgTestLights1.cpp $(proxyCppCore)CpOpenhomeOrgSubscriptionLongPoll1.cpp
$(proxyCppCore)CpUpnpOrgAVTransport1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo CpUpnpOrgAVTransport1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(proxyCppCore) --domain=upnp.org --type=AVTransport --version=1
$(proxyCppCore)CpUpnpOrgAVTransport2.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo CpUpnpOrgAVTransport2.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(proxyCppCore) --domain=upnp.org --type=AVTransport --version=2
$(proxyCppCore)CpUpnpOrgConnectionManager1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo CpUpnpOrgConnectionManager1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(proxyCppCore) --domain=upnp.org --type=ConnectionManager --version=1
$(proxyCppCore)CpUpnpOrgConnectionManager2.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo CpUpnpOrgConnectionManager2.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(proxyCppCore) --domain=upnp.org --type=ConnectionManager --version=2
$(proxyCppCore)CpUpnpOrgContentDirectory1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo CpUpnpOrgContentDirectory1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(proxyCppCore) --domain=upnp.org --type=ContentDirectory --version=1
$(proxyCppCore)CpUpnpOrgContentDirectory2.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo CpUpnpOrgContentDirectory2.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(proxyCppCore) --domain=upnp.org --type=ContentDirectory --version=2
$(proxyCppCore)CpUpnpOrgContentDirectory3.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo CpUpnpOrgContentDirectory3.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(proxyCppCore) --domain=upnp.org --type=ContentDirectory --version=3
$(proxyCppCore)CpUpnpOrgRenderingControl1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo CpUpnpOrgRenderingControl1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(proxyCppCore) --domain=upnp.org --type=RenderingControl --version=1
$(proxyCppCore)CpUpnpOrgRenderingControl2.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo CpUpnpOrgRenderingControl2.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(proxyCppCore) --domain=upnp.org --type=RenderingControl --version=2
$(proxyCppCore)CpUpnpOrgScheduledRecording1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo CpUpnpOrgScheduledRecording1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(proxyCppCore) --domain=upnp.org --type=ScheduledRecording --version=1
$(proxyCppCore)CpUpnpOrgScheduledRecording2.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo CpUpnpOrgScheduledRecording2.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(proxyCppCore) --domain=upnp.org --type=ScheduledRecording --version=2
$(proxyCppCore)CpUpnpOrgSwitchPower1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo CpUpnpOrgSwitchPower1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(proxyCppCore) --domain=upnp.org --type=SwitchPower --version=1
$(proxyCppCore)CpUpnpOrgDimming1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo CpUpnpOrgDimming1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(proxyCppCore) --domain=upnp.org --type=Dimming --version=1
$(proxyCppCore)CpAvOpenhomeOrgInfo1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Info1.xml
	echo CpAvOpenhomeOrgInfo1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Info1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=Info --version=1
$(proxyCppCore)CpAvOpenhomeOrgTime1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Time1.xml
	echo CpAvOpenhomeOrgTime1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Time1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=Time --version=1
$(proxyCppCore)CpAvOpenhomeOrgPlaylist1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml
	echo CpAvOpenhomeOrgPlaylist1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=Playlist --version=1
$(proxyCppCore)CpAvOpenhomeOrgVolume1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml
	echo CpAvOpenhomeOrgVolume1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=Volume --version=1
$(proxyCppCore)CpAvOpenhomeOrgProduct1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Product1.xml
	echo CpAvOpenhomeOrgProduct1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Product1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=Product --version=1
$(proxyCppCore)CpAvOpenhomeOrgRadio1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml
	echo CpAvOpenhomeOrgRadio1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=Radio --version=1
$(proxyCppCore)CpAvOpenhomeOrgReceiver1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml
	echo CpAvOpenhomeOrgReceiver1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=Receiver --version=1
$(proxyCppCore)CpAvOpenhomeOrgSender1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml
	echo CpAvOpenhomeOrgSender1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=Sender --version=1
$(proxyCppCore)CpAvOpenhomeOrgPlaylistManager1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml
	echo CpAvOpenhomeOrgPlaylistManager1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=PlaylistManager --version=1
$(proxyCppCore)CpAvOpenhomeOrgMediaServer1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml
	echo CpAvOpenhomeOrgMediaServer1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=MediaServer --version=1
$(proxyCppCore)CpAvOpenhomeOrgNetworkMonitor1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml
	echo CpAvOpenhomeOrgNetworkMonitor1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml" --output=$(proxyCppCore) --domain=av.openhome.org --type=NetworkMonitor --version=1
$(proxyCppCore)CpOpenhomeOrgTestBasic1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml
	echo CpOpenhomeOrgTestBasic1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml" --output=$(proxyCppCore) --domain=openhome.org --type=TestBasic --version=1
$(proxyCppCore)CpOpenhomeOrgTestLights1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml
	echo CpOpenhomeOrgTestLights1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml" --output=$(proxyCppCore) --domain=openhome.org --type=TestLights --version=1
$(proxyCppCore)CpOpenhomeOrgSubscriptionLongPoll1.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppBufferSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml
	echo CpOpenhomeOrgSubscriptionLongPoll1.cpp
	$(ohNetGen) --language=cppcore --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml" --output=$(proxyCppCore) --domain=openhome.org --type=SubscriptionLongPoll --version=1

CpCppStd:   $(proxyCppStd)CpUpnpOrgAVTransport1Std.cpp $(proxyCppStd)CpUpnpOrgAVTransport2Std.cpp $(proxyCppStd)CpUpnpOrgConnectionManager1Std.cpp $(proxyCppStd)CpUpnpOrgConnectionManager2Std.cpp $(proxyCppStd)CpUpnpOrgContentDirectory1Std.cpp $(proxyCppStd)CpUpnpOrgContentDirectory2Std.cpp $(proxyCppStd)CpUpnpOrgContentDirectory3Std.cpp $(proxyCppStd)CpUpnpOrgRenderingControl1Std.cpp $(proxyCppStd)CpUpnpOrgRenderingControl2Std.cpp $(proxyCppStd)CpUpnpOrgScheduledRecording1Std.cpp $(proxyCppStd)CpUpnpOrgScheduledRecording2Std.cpp $(proxyCppStd)CpUpnpOrgSwitchPower1Std.cpp $(proxyCppStd)CpUpnpOrgDimming1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgInfo1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgTime1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgPlaylist1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgVolume1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgProduct1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgRadio1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgReceiver1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgSender1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgPlaylistManager1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgMediaServer1Std.cpp $(proxyCppStd)CpAvOpenhomeOrgNetworkMonitor1Std.cpp $(proxyCppStd)CpOpenhomeOrgTestBasic1Std.cpp $(proxyCppStd)CpOpenhomeOrgTestLights1Std.cpp $(proxyCppStd)CpOpenhomeOrgSubscriptionLongPoll1Std.cpp
$(proxyCppStd)CpUpnpOrgAVTransport1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo CpUpnpOrgAVTransport1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(proxyCppStd) --domain=upnp.org --type=AVTransport --version=1
$(proxyCppStd)CpUpnpOrgAVTransport2Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo CpUpnpOrgAVTransport2Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(proxyCppStd) --domain=upnp.org --type=AVTransport --version=2
$(proxyCppStd)CpUpnpOrgConnectionManager1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo CpUpnpOrgConnectionManager1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(proxyCppStd) --domain=upnp.org --type=ConnectionManager --version=1
$(proxyCppStd)CpUpnpOrgConnectionManager2Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo CpUpnpOrgConnectionManager2Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(proxyCppStd) --domain=upnp.org --type=ConnectionManager --version=2
$(proxyCppStd)CpUpnpOrgContentDirectory1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo CpUpnpOrgContentDirectory1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(proxyCppStd) --domain=upnp.org --type=ContentDirectory --version=1
$(proxyCppStd)CpUpnpOrgContentDirectory2Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo CpUpnpOrgContentDirectory2Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(proxyCppStd) --domain=upnp.org --type=ContentDirectory --version=2
$(proxyCppStd)CpUpnpOrgContentDirectory3Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo CpUpnpOrgContentDirectory3Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(proxyCppStd) --domain=upnp.org --type=ContentDirectory --version=3
$(proxyCppStd)CpUpnpOrgRenderingControl1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo CpUpnpOrgRenderingControl1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(proxyCppStd) --domain=upnp.org --type=RenderingControl --version=1
$(proxyCppStd)CpUpnpOrgRenderingControl2Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo CpUpnpOrgRenderingControl2Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(proxyCppStd) --domain=upnp.org --type=RenderingControl --version=2
$(proxyCppStd)CpUpnpOrgScheduledRecording1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo CpUpnpOrgScheduledRecording1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(proxyCppStd) --domain=upnp.org --type=ScheduledRecording --version=1
$(proxyCppStd)CpUpnpOrgScheduledRecording2Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo CpUpnpOrgScheduledRecording2Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(proxyCppStd) --domain=upnp.org --type=ScheduledRecording --version=2
$(proxyCppStd)CpUpnpOrgSwitchPower1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo CpUpnpOrgSwitchPower1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(proxyCppStd) --domain=upnp.org --type=SwitchPower --version=1
$(proxyCppStd)CpUpnpOrgDimming1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo CpUpnpOrgDimming1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(proxyCppStd) --domain=upnp.org --type=Dimming --version=1
$(proxyCppStd)CpAvOpenhomeOrgInfo1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Info1.xml
	echo CpAvOpenhomeOrgInfo1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Info1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=Info --version=1
$(proxyCppStd)CpAvOpenhomeOrgTime1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Time1.xml
	echo CpAvOpenhomeOrgTime1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Time1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=Time --version=1
$(proxyCppStd)CpAvOpenhomeOrgPlaylist1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml
	echo CpAvOpenhomeOrgPlaylist1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=Playlist --version=1
$(proxyCppStd)CpAvOpenhomeOrgVolume1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml
	echo CpAvOpenhomeOrgVolume1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=Volume --version=1
$(proxyCppStd)CpAvOpenhomeOrgProduct1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Product1.xml
	echo CpAvOpenhomeOrgProduct1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Product1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=Product --version=1
$(proxyCppStd)CpAvOpenhomeOrgRadio1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml
	echo CpAvOpenhomeOrgRadio1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=Radio --version=1
$(proxyCppStd)CpAvOpenhomeOrgReceiver1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml
	echo CpAvOpenhomeOrgReceiver1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=Receiver --version=1
$(proxyCppStd)CpAvOpenhomeOrgSender1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml
	echo CpAvOpenhomeOrgSender1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=Sender --version=1
$(proxyCppStd)CpAvOpenhomeOrgPlaylistManager1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml
	echo CpAvOpenhomeOrgPlaylistManager1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=PlaylistManager --version=1
$(proxyCppStd)CpAvOpenhomeOrgMediaServer1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml
	echo CpAvOpenhomeOrgMediaServer1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=MediaServer --version=1
$(proxyCppStd)CpAvOpenhomeOrgNetworkMonitor1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml
	echo CpAvOpenhomeOrgNetworkMonitor1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml" --output=$(proxyCppStd) --domain=av.openhome.org --type=NetworkMonitor --version=1
$(proxyCppStd)CpOpenhomeOrgTestBasic1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml
	echo CpOpenhomeOrgTestBasic1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml" --output=$(proxyCppStd) --domain=openhome.org --type=TestBasic --version=1
$(proxyCppStd)CpOpenhomeOrgTestLights1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml
	echo CpOpenhomeOrgTestLights1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml" --output=$(proxyCppStd) --domain=openhome.org --type=TestLights --version=1
$(proxyCppStd)CpOpenhomeOrgSubscriptionLongPoll1Std.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCppStringSource.tt OpenHome/Net/T4/Templates/CpUpnpCppHeader.tt OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml
	echo CpOpenhomeOrgSubscriptionLongPoll1Std.cpp
	$(ohNetGen) --language=cpp --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml" --output=$(proxyCppStd) --domain=openhome.org --type=SubscriptionLongPoll --version=1

CpC:   $(proxyC)CpUpnpOrgAVTransport1C.cpp $(proxyC)CpUpnpOrgAVTransport2C.cpp $(proxyC)CpUpnpOrgConnectionManager1C.cpp $(proxyC)CpUpnpOrgConnectionManager2C.cpp $(proxyC)CpUpnpOrgContentDirectory1C.cpp $(proxyC)CpUpnpOrgContentDirectory2C.cpp $(proxyC)CpUpnpOrgContentDirectory3C.cpp $(proxyC)CpUpnpOrgRenderingControl1C.cpp $(proxyC)CpUpnpOrgRenderingControl2C.cpp $(proxyC)CpUpnpOrgScheduledRecording1C.cpp $(proxyC)CpUpnpOrgScheduledRecording2C.cpp $(proxyC)CpUpnpOrgSwitchPower1C.cpp $(proxyC)CpUpnpOrgDimming1C.cpp $(proxyC)CpAvOpenhomeOrgInfo1C.cpp $(proxyC)CpAvOpenhomeOrgTime1C.cpp $(proxyC)CpAvOpenhomeOrgPlaylist1C.cpp $(proxyC)CpAvOpenhomeOrgVolume1C.cpp $(proxyC)CpAvOpenhomeOrgProduct1C.cpp $(proxyC)CpAvOpenhomeOrgRadio1C.cpp $(proxyC)CpAvOpenhomeOrgReceiver1C.cpp $(proxyC)CpAvOpenhomeOrgSender1C.cpp $(proxyC)CpAvOpenhomeOrgPlaylistManager1C.cpp $(proxyC)CpAvOpenhomeOrgMediaServer1C.cpp $(proxyC)CpAvOpenhomeOrgNetworkMonitor1C.cpp $(proxyC)CpOpenhomeOrgTestBasic1C.cpp $(proxyC)CpOpenhomeOrgTestLights1C.cpp $(proxyC)CpOpenhomeOrgSubscriptionLongPoll1C.cpp
$(proxyC)CpUpnpOrgAVTransport1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo CpUpnpOrgAVTransport1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(proxyC) --domain=upnp.org --type=AVTransport --version=1
$(proxyC)CpUpnpOrgAVTransport2C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo CpUpnpOrgAVTransport2C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(proxyC) --domain=upnp.org --type=AVTransport --version=2
$(proxyC)CpUpnpOrgConnectionManager1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo CpUpnpOrgConnectionManager1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(proxyC) --domain=upnp.org --type=ConnectionManager --version=1
$(proxyC)CpUpnpOrgConnectionManager2C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo CpUpnpOrgConnectionManager2C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(proxyC) --domain=upnp.org --type=ConnectionManager --version=2
$(proxyC)CpUpnpOrgContentDirectory1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo CpUpnpOrgContentDirectory1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(proxyC) --domain=upnp.org --type=ContentDirectory --version=1
$(proxyC)CpUpnpOrgContentDirectory2C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo CpUpnpOrgContentDirectory2C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(proxyC) --domain=upnp.org --type=ContentDirectory --version=2
$(proxyC)CpUpnpOrgContentDirectory3C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo CpUpnpOrgContentDirectory3C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(proxyC) --domain=upnp.org --type=ContentDirectory --version=3
$(proxyC)CpUpnpOrgRenderingControl1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo CpUpnpOrgRenderingControl1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(proxyC) --domain=upnp.org --type=RenderingControl --version=1
$(proxyC)CpUpnpOrgRenderingControl2C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo CpUpnpOrgRenderingControl2C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(proxyC) --domain=upnp.org --type=RenderingControl --version=2
$(proxyC)CpUpnpOrgScheduledRecording1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo CpUpnpOrgScheduledRecording1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(proxyC) --domain=upnp.org --type=ScheduledRecording --version=1
$(proxyC)CpUpnpOrgScheduledRecording2C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo CpUpnpOrgScheduledRecording2C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(proxyC) --domain=upnp.org --type=ScheduledRecording --version=2
$(proxyC)CpUpnpOrgSwitchPower1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo CpUpnpOrgSwitchPower1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(proxyC) --domain=upnp.org --type=SwitchPower --version=1
$(proxyC)CpUpnpOrgDimming1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo CpUpnpOrgDimming1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(proxyC) --domain=upnp.org --type=Dimming --version=1
$(proxyC)CpAvOpenhomeOrgInfo1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Info1.xml
	echo CpAvOpenhomeOrgInfo1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Info1.xml" --output=$(proxyC) --domain=av.openhome.org --type=Info --version=1
$(proxyC)CpAvOpenhomeOrgTime1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Time1.xml
	echo CpAvOpenhomeOrgTime1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Time1.xml" --output=$(proxyC) --domain=av.openhome.org --type=Time --version=1
$(proxyC)CpAvOpenhomeOrgPlaylist1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml
	echo CpAvOpenhomeOrgPlaylist1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml" --output=$(proxyC) --domain=av.openhome.org --type=Playlist --version=1
$(proxyC)CpAvOpenhomeOrgVolume1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml
	echo CpAvOpenhomeOrgVolume1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml" --output=$(proxyC) --domain=av.openhome.org --type=Volume --version=1
$(proxyC)CpAvOpenhomeOrgProduct1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Product1.xml
	echo CpAvOpenhomeOrgProduct1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Product1.xml" --output=$(proxyC) --domain=av.openhome.org --type=Product --version=1
$(proxyC)CpAvOpenhomeOrgRadio1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml
	echo CpAvOpenhomeOrgRadio1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml" --output=$(proxyC) --domain=av.openhome.org --type=Radio --version=1
$(proxyC)CpAvOpenhomeOrgReceiver1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml
	echo CpAvOpenhomeOrgReceiver1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml" --output=$(proxyC) --domain=av.openhome.org --type=Receiver --version=1
$(proxyC)CpAvOpenhomeOrgSender1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml
	echo CpAvOpenhomeOrgSender1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml" --output=$(proxyC) --domain=av.openhome.org --type=Sender --version=1
$(proxyC)CpAvOpenhomeOrgPlaylistManager1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml
	echo CpAvOpenhomeOrgPlaylistManager1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml" --output=$(proxyC) --domain=av.openhome.org --type=PlaylistManager --version=1
$(proxyC)CpAvOpenhomeOrgMediaServer1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml
	echo CpAvOpenhomeOrgMediaServer1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml" --output=$(proxyC) --domain=av.openhome.org --type=MediaServer --version=1
$(proxyC)CpAvOpenhomeOrgNetworkMonitor1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml
	echo CpAvOpenhomeOrgNetworkMonitor1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml" --output=$(proxyC) --domain=av.openhome.org --type=NetworkMonitor --version=1
$(proxyC)CpOpenhomeOrgTestBasic1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml
	echo CpOpenhomeOrgTestBasic1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml" --output=$(proxyC) --domain=openhome.org --type=TestBasic --version=1
$(proxyC)CpOpenhomeOrgTestLights1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml
	echo CpOpenhomeOrgTestLights1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml" --output=$(proxyC) --domain=openhome.org --type=TestLights --version=1
$(proxyC)CpOpenhomeOrgSubscriptionLongPoll1C.cpp : $(tt) OpenHome/Net/T4/Templates/CpUpnpCSource.tt OpenHome/Net/T4/Templates/CpUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml
	echo CpOpenhomeOrgSubscriptionLongPoll1C.cpp
	$(ohNetGen) --language=c --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml" --output=$(proxyC) --domain=openhome.org --type=SubscriptionLongPoll --version=1

CpCs:   $(proxyCs)CpUpnpOrgAVTransport1.cs $(proxyCs)CpUpnpOrgAVTransport2.cs $(proxyCs)CpUpnpOrgConnectionManager1.cs $(proxyCs)CpUpnpOrgConnectionManager2.cs $(proxyCs)CpUpnpOrgContentDirectory1.cs $(proxyCs)CpUpnpOrgContentDirectory2.cs $(proxyCs)CpUpnpOrgContentDirectory3.cs $(proxyCs)CpUpnpOrgRenderingControl1.cs $(proxyCs)CpUpnpOrgRenderingControl2.cs $(proxyCs)CpUpnpOrgScheduledRecording1.cs $(proxyCs)CpUpnpOrgScheduledRecording2.cs $(proxyCs)CpUpnpOrgSwitchPower1.cs $(proxyCs)CpUpnpOrgDimming1.cs $(proxyCs)CpAvOpenhomeOrgInfo1.cs $(proxyCs)CpAvOpenhomeOrgTime1.cs $(proxyCs)CpAvOpenhomeOrgPlaylist1.cs $(proxyCs)CpAvOpenhomeOrgVolume1.cs $(proxyCs)CpAvOpenhomeOrgProduct1.cs $(proxyCs)CpAvOpenhomeOrgRadio1.cs $(proxyCs)CpAvOpenhomeOrgReceiver1.cs $(proxyCs)CpAvOpenhomeOrgSender1.cs $(proxyCs)CpAvOpenhomeOrgPlaylistManager1.cs $(proxyCs)CpAvOpenhomeOrgMediaServer1.cs $(proxyCs)CpAvOpenhomeOrgNetworkMonitor1.cs $(proxyCs)CpOpenhomeOrgTestBasic1.cs $(proxyCs)CpOpenhomeOrgTestLights1.cs $(proxyCs)CpOpenhomeOrgSubscriptionLongPoll1.cs
$(proxyCs)CpUpnpOrgAVTransport1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo CpUpnpOrgAVTransport1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(proxyCs) --domain=upnp.org --type=AVTransport --version=1
$(proxyCs)CpUpnpOrgAVTransport2.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo CpUpnpOrgAVTransport2.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(proxyCs) --domain=upnp.org --type=AVTransport --version=2
$(proxyCs)CpUpnpOrgConnectionManager1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo CpUpnpOrgConnectionManager1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(proxyCs) --domain=upnp.org --type=ConnectionManager --version=1
$(proxyCs)CpUpnpOrgConnectionManager2.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo CpUpnpOrgConnectionManager2.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(proxyCs) --domain=upnp.org --type=ConnectionManager --version=2
$(proxyCs)CpUpnpOrgContentDirectory1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo CpUpnpOrgContentDirectory1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(proxyCs) --domain=upnp.org --type=ContentDirectory --version=1
$(proxyCs)CpUpnpOrgContentDirectory2.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo CpUpnpOrgContentDirectory2.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(proxyCs) --domain=upnp.org --type=ContentDirectory --version=2
$(proxyCs)CpUpnpOrgContentDirectory3.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo CpUpnpOrgContentDirectory3.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(proxyCs) --domain=upnp.org --type=ContentDirectory --version=3
$(proxyCs)CpUpnpOrgRenderingControl1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo CpUpnpOrgRenderingControl1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(proxyCs) --domain=upnp.org --type=RenderingControl --version=1
$(proxyCs)CpUpnpOrgRenderingControl2.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo CpUpnpOrgRenderingControl2.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(proxyCs) --domain=upnp.org --type=RenderingControl --version=2
$(proxyCs)CpUpnpOrgScheduledRecording1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo CpUpnpOrgScheduledRecording1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(proxyCs) --domain=upnp.org --type=ScheduledRecording --version=1
$(proxyCs)CpUpnpOrgScheduledRecording2.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo CpUpnpOrgScheduledRecording2.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(proxyCs) --domain=upnp.org --type=ScheduledRecording --version=2
$(proxyCs)CpUpnpOrgSwitchPower1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo CpUpnpOrgSwitchPower1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(proxyCs) --domain=upnp.org --type=SwitchPower --version=1
$(proxyCs)CpUpnpOrgDimming1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo CpUpnpOrgDimming1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(proxyCs) --domain=upnp.org --type=Dimming --version=1
$(proxyCs)CpAvOpenhomeOrgInfo1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Info1.xml
	echo CpAvOpenhomeOrgInfo1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Info1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=Info --version=1
$(proxyCs)CpAvOpenhomeOrgTime1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Time1.xml
	echo CpAvOpenhomeOrgTime1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Time1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=Time --version=1
$(proxyCs)CpAvOpenhomeOrgPlaylist1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml
	echo CpAvOpenhomeOrgPlaylist1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=Playlist --version=1
$(proxyCs)CpAvOpenhomeOrgVolume1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml
	echo CpAvOpenhomeOrgVolume1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=Volume --version=1
$(proxyCs)CpAvOpenhomeOrgProduct1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Product1.xml
	echo CpAvOpenhomeOrgProduct1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Product1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=Product --version=1
$(proxyCs)CpAvOpenhomeOrgRadio1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml
	echo CpAvOpenhomeOrgRadio1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=Radio --version=1
$(proxyCs)CpAvOpenhomeOrgReceiver1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml
	echo CpAvOpenhomeOrgReceiver1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=Receiver --version=1
$(proxyCs)CpAvOpenhomeOrgSender1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml
	echo CpAvOpenhomeOrgSender1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=Sender --version=1
$(proxyCs)CpAvOpenhomeOrgPlaylistManager1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml
	echo CpAvOpenhomeOrgPlaylistManager1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=PlaylistManager --version=1
$(proxyCs)CpAvOpenhomeOrgMediaServer1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml
	echo CpAvOpenhomeOrgMediaServer1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=MediaServer --version=1
$(proxyCs)CpAvOpenhomeOrgNetworkMonitor1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml
	echo CpAvOpenhomeOrgNetworkMonitor1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml" --output=$(proxyCs) --domain=av.openhome.org --type=NetworkMonitor --version=1
$(proxyCs)CpOpenhomeOrgTestBasic1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml
	echo CpOpenhomeOrgTestBasic1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml" --output=$(proxyCs) --domain=openhome.org --type=TestBasic --version=1
$(proxyCs)CpOpenhomeOrgTestLights1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml
	echo CpOpenhomeOrgTestLights1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml" --output=$(proxyCs) --domain=openhome.org --type=TestLights --version=1
$(proxyCs)CpOpenhomeOrgSubscriptionLongPoll1.cs : $(tt) OpenHome/Net/T4/Templates/CpUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml
	echo CpOpenhomeOrgSubscriptionLongPoll1.cs
	$(ohNetGen) --language=cs --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml" --output=$(proxyCs) --domain=openhome.org --type=SubscriptionLongPoll --version=1

CpJava:   $(proxyJava)CpProxyUpnpOrgAVTransport1.java $(proxyJava)CpProxyUpnpOrgAVTransport2.java $(proxyJava)CpProxyUpnpOrgConnectionManager1.java $(proxyJava)CpProxyUpnpOrgConnectionManager2.java $(proxyJava)CpProxyUpnpOrgContentDirectory1.java $(proxyJava)CpProxyUpnpOrgContentDirectory2.java $(proxyJava)CpProxyUpnpOrgContentDirectory3.java $(proxyJava)CpProxyUpnpOrgRenderingControl1.java $(proxyJava)CpProxyUpnpOrgRenderingControl2.java $(proxyJava)CpProxyUpnpOrgScheduledRecording1.java $(proxyJava)CpProxyUpnpOrgScheduledRecording2.java $(proxyJava)CpProxyUpnpOrgSwitchPower1.java $(proxyJava)CpProxyUpnpOrgDimming1.java $(proxyJava)CpProxyAvOpenhomeOrgInfo1.java $(proxyJava)CpProxyAvOpenhomeOrgTime1.java $(proxyJava)CpProxyAvOpenhomeOrgPlaylist1.java $(proxyJava)CpProxyAvOpenhomeOrgVolume1.java $(proxyJava)CpProxyAvOpenhomeOrgProduct1.java $(proxyJava)CpProxyAvOpenhomeOrgRadio1.java $(proxyJava)CpProxyAvOpenhomeOrgReceiver1.java $(proxyJava)CpProxyAvOpenhomeOrgSender1.java $(proxyJava)CpProxyAvOpenhomeOrgPlaylistManager1.java $(proxyJava)CpProxyAvOpenhomeOrgMediaServer1.java $(proxyJava)CpProxyAvOpenhomeOrgNetworkMonitor1.java $(proxyJava)CpProxyOpenhomeOrgTestBasic1.java $(proxyJava)CpProxyOpenhomeOrgTestLights1.java $(proxyJava)CpProxyOpenhomeOrgSubscriptionLongPoll1.java
$(proxyJava)CpProxyUpnpOrgAVTransport1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo CpProxyUpnpOrgAVTransport1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(proxyJava) --domain=upnp.org --type=AVTransport --version=1
$(proxyJava)CpProxyUpnpOrgAVTransport2.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo CpProxyUpnpOrgAVTransport2.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(proxyJava) --domain=upnp.org --type=AVTransport --version=2
$(proxyJava)CpProxyUpnpOrgConnectionManager1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo CpProxyUpnpOrgConnectionManager1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(proxyJava) --domain=upnp.org --type=ConnectionManager --version=1
$(proxyJava)CpProxyUpnpOrgConnectionManager2.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo CpProxyUpnpOrgConnectionManager2.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(proxyJava) --domain=upnp.org --type=ConnectionManager --version=2
$(proxyJava)CpProxyUpnpOrgContentDirectory1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo CpProxyUpnpOrgContentDirectory1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(proxyJava) --domain=upnp.org --type=ContentDirectory --version=1
$(proxyJava)CpProxyUpnpOrgContentDirectory2.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo CpProxyUpnpOrgContentDirectory2.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(proxyJava) --domain=upnp.org --type=ContentDirectory --version=2
$(proxyJava)CpProxyUpnpOrgContentDirectory3.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo CpProxyUpnpOrgContentDirectory3.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(proxyJava) --domain=upnp.org --type=ContentDirectory --version=3
$(proxyJava)CpProxyUpnpOrgRenderingControl1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo CpProxyUpnpOrgRenderingControl1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(proxyJava) --domain=upnp.org --type=RenderingControl --version=1
$(proxyJava)CpProxyUpnpOrgRenderingControl2.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo CpProxyUpnpOrgRenderingControl2.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(proxyJava) --domain=upnp.org --type=RenderingControl --version=2
$(proxyJava)CpProxyUpnpOrgScheduledRecording1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo CpProxyUpnpOrgScheduledRecording1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(proxyJava) --domain=upnp.org --type=ScheduledRecording --version=1
$(proxyJava)CpProxyUpnpOrgScheduledRecording2.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo CpProxyUpnpOrgScheduledRecording2.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(proxyJava) --domain=upnp.org --type=ScheduledRecording --version=2
$(proxyJava)CpProxyUpnpOrgSwitchPower1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo CpProxyUpnpOrgSwitchPower1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(proxyJava) --domain=upnp.org --type=SwitchPower --version=1
$(proxyJava)CpProxyUpnpOrgDimming1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo CpProxyUpnpOrgDimming1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(proxyJava) --domain=upnp.org --type=Dimming --version=1
$(proxyJava)CpProxyAvOpenhomeOrgInfo1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Info1.xml
	echo CpProxyAvOpenhomeOrgInfo1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Info1.xml" --output=$(proxyJava) --domain=av.openhome.org --type=Info --version=1
$(proxyJava)CpProxyAvOpenhomeOrgTime1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Time1.xml
	echo CpProxyAvOpenhomeOrgTime1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Time1.xml" --output=$(proxyJava) --domain=av.openhome.org --type=Time --version=1
$(proxyJava)CpProxyAvOpenhomeOrgPlaylist1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml
	echo CpProxyAvOpenhomeOrgPlaylist1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml" --output=$(proxyJava) --domain=av.openhome.org --type=Playlist --version=1
$(proxyJava)CpProxyAvOpenhomeOrgVolume1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml
	echo CpProxyAvOpenhomeOrgVolume1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml" --output=$(proxyJava) --domain=av.openhome.org --type=Volume --version=1
$(proxyJava)CpProxyAvOpenhomeOrgProduct1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Product1.xml
	echo CpProxyAvOpenhomeOrgProduct1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Product1.xml" --output=$(proxyJava) --domain=av.openhome.org --type=Product --version=1
$(proxyJava)CpProxyAvOpenhomeOrgRadio1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml
	echo CpProxyAvOpenhomeOrgRadio1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml" --output=$(proxyJava) --domain=av.openhome.org --type=Radio --version=1
$(proxyJava)CpProxyAvOpenhomeOrgReceiver1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml
	echo CpProxyAvOpenhomeOrgReceiver1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml" --output=$(proxyJava) --domain=av.openhome.org --type=Receiver --version=1
$(proxyJava)CpProxyAvOpenhomeOrgSender1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml
	echo CpProxyAvOpenhomeOrgSender1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml" --output=$(proxyJava) --domain=av.openhome.org --type=Sender --version=1
$(proxyJava)CpProxyAvOpenhomeOrgPlaylistManager1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml
	echo CpProxyAvOpenhomeOrgPlaylistManager1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml" --output=$(proxyJava) --domain=av.openhome.org --type=PlaylistManager --version=1
$(proxyJava)CpProxyAvOpenhomeOrgMediaServer1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml
	echo CpProxyAvOpenhomeOrgMediaServer1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml" --output=$(proxyJava) --domain=av.openhome.org --type=MediaServer --version=1
$(proxyJava)CpProxyAvOpenhomeOrgNetworkMonitor1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml
	echo CpProxyAvOpenhomeOrgNetworkMonitor1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml" --output=$(proxyJava) --domain=av.openhome.org --type=NetworkMonitor --version=1
$(proxyJava)CpProxyOpenhomeOrgTestBasic1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml
	echo CpProxyOpenhomeOrgTestBasic1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml" --output=$(proxyJava) --domain=openhome.org --type=TestBasic --version=1
$(proxyJava)CpProxyOpenhomeOrgTestLights1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml
	echo CpProxyOpenhomeOrgTestLights1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml" --output=$(proxyJava) --domain=openhome.org --type=TestLights --version=1
$(proxyJava)CpProxyOpenhomeOrgSubscriptionLongPoll1.java : $(tt) OpenHome/Net/T4/Templates/CpUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml
	echo CpProxyOpenhomeOrgSubscriptionLongPoll1.java
	$(ohNetGen) --language=java --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml" --output=$(proxyJava) --domain=openhome.org --type=SubscriptionLongPoll --version=1

CpJs:   $(proxyJs)CpUpnpOrgAVTransport1.js $(proxyJs)CpUpnpOrgAVTransport2.js $(proxyJs)CpUpnpOrgConnectionManager1.js $(proxyJs)CpUpnpOrgConnectionManager2.js $(proxyJs)CpUpnpOrgContentDirectory1.js $(proxyJs)CpUpnpOrgContentDirectory2.js $(proxyJs)CpUpnpOrgContentDirectory3.js $(proxyJs)CpUpnpOrgRenderingControl1.js $(proxyJs)CpUpnpOrgRenderingControl2.js $(proxyJs)CpUpnpOrgScheduledRecording1.js $(proxyJs)CpUpnpOrgScheduledRecording2.js $(proxyJs)CpUpnpOrgSwitchPower1.js $(proxyJs)CpUpnpOrgDimming1.js $(proxyJs)CpAvOpenhomeOrgInfo1.js $(proxyJs)CpAvOpenhomeOrgTime1.js $(proxyJs)CpAvOpenhomeOrgPlaylist1.js $(proxyJs)CpAvOpenhomeOrgVolume1.js $(proxyJs)CpAvOpenhomeOrgProduct1.js $(proxyJs)CpAvOpenhomeOrgRadio1.js $(proxyJs)CpAvOpenhomeOrgReceiver1.js $(proxyJs)CpAvOpenhomeOrgSender1.js $(proxyJs)CpAvOpenhomeOrgPlaylistManager1.js $(proxyJs)CpAvOpenhomeOrgMediaServer1.js $(proxyJs)CpAvOpenhomeOrgNetworkMonitor1.js $(proxyJs)CpOpenhomeOrgTestBasic1.js $(proxyJs)CpOpenhomeOrgTestLights1.js $(proxyJs)CpOpenhomeOrgSubscriptionLongPoll1.js
$(proxyJs)CpUpnpOrgAVTransport1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo CpUpnpOrgAVTransport1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(proxyJs) --domain=upnp.org --type=AVTransport --version=1
$(proxyJs)CpUpnpOrgAVTransport2.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo CpUpnpOrgAVTransport2.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(proxyJs) --domain=upnp.org --type=AVTransport --version=2
$(proxyJs)CpUpnpOrgConnectionManager1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo CpUpnpOrgConnectionManager1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(proxyJs) --domain=upnp.org --type=ConnectionManager --version=1
$(proxyJs)CpUpnpOrgConnectionManager2.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo CpUpnpOrgConnectionManager2.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(proxyJs) --domain=upnp.org --type=ConnectionManager --version=2
$(proxyJs)CpUpnpOrgContentDirectory1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo CpUpnpOrgContentDirectory1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(proxyJs) --domain=upnp.org --type=ContentDirectory --version=1
$(proxyJs)CpUpnpOrgContentDirectory2.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo CpUpnpOrgContentDirectory2.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(proxyJs) --domain=upnp.org --type=ContentDirectory --version=2
$(proxyJs)CpUpnpOrgContentDirectory3.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo CpUpnpOrgContentDirectory3.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(proxyJs) --domain=upnp.org --type=ContentDirectory --version=3
$(proxyJs)CpUpnpOrgRenderingControl1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo CpUpnpOrgRenderingControl1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(proxyJs) --domain=upnp.org --type=RenderingControl --version=1
$(proxyJs)CpUpnpOrgRenderingControl2.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo CpUpnpOrgRenderingControl2.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(proxyJs) --domain=upnp.org --type=RenderingControl --version=2
$(proxyJs)CpUpnpOrgScheduledRecording1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo CpUpnpOrgScheduledRecording1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(proxyJs) --domain=upnp.org --type=ScheduledRecording --version=1
$(proxyJs)CpUpnpOrgScheduledRecording2.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo CpUpnpOrgScheduledRecording2.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(proxyJs) --domain=upnp.org --type=ScheduledRecording --version=2
$(proxyJs)CpUpnpOrgSwitchPower1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo CpUpnpOrgSwitchPower1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(proxyJs) --domain=upnp.org --type=SwitchPower --version=1
$(proxyJs)CpUpnpOrgDimming1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo CpUpnpOrgDimming1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(proxyJs) --domain=upnp.org --type=Dimming --version=1
$(proxyJs)CpAvOpenhomeOrgInfo1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/OpenHome/Info1.xml
	echo CpAvOpenhomeOrgInfo1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Info1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=Info --version=1
$(proxyJs)CpAvOpenhomeOrgTime1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/OpenHome/Time1.xml
	echo CpAvOpenhomeOrgTime1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Time1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=Time --version=1
$(proxyJs)CpAvOpenhomeOrgPlaylist1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml
	echo CpAvOpenhomeOrgPlaylist1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=Playlist --version=1
$(proxyJs)CpAvOpenhomeOrgVolume1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml
	echo CpAvOpenhomeOrgVolume1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=Volume --version=1
$(proxyJs)CpAvOpenhomeOrgProduct1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/OpenHome/Product1.xml
	echo CpAvOpenhomeOrgProduct1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Product1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=Product --version=1
$(proxyJs)CpAvOpenhomeOrgRadio1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml
	echo CpAvOpenhomeOrgRadio1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=Radio --version=1
$(proxyJs)CpAvOpenhomeOrgReceiver1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml
	echo CpAvOpenhomeOrgReceiver1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=Receiver --version=1
$(proxyJs)CpAvOpenhomeOrgSender1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml
	echo CpAvOpenhomeOrgSender1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=Sender --version=1
$(proxyJs)CpAvOpenhomeOrgPlaylistManager1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml
	echo CpAvOpenhomeOrgPlaylistManager1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=PlaylistManager --version=1
$(proxyJs)CpAvOpenhomeOrgMediaServer1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml
	echo CpAvOpenhomeOrgMediaServer1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=MediaServer --version=1
$(proxyJs)CpAvOpenhomeOrgNetworkMonitor1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml
	echo CpAvOpenhomeOrgNetworkMonitor1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml" --output=$(proxyJs) --domain=av.openhome.org --type=NetworkMonitor --version=1
$(proxyJs)CpOpenhomeOrgTestBasic1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml
	echo CpOpenhomeOrgTestBasic1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml" --output=$(proxyJs) --domain=openhome.org --type=TestBasic --version=1
$(proxyJs)CpOpenhomeOrgTestLights1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml
	echo CpOpenhomeOrgTestLights1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml" --output=$(proxyJs) --domain=openhome.org --type=TestLights --version=1
$(proxyJs)CpOpenhomeOrgSubscriptionLongPoll1.js : $(tt) OpenHome/Net/T4/Templates/CpUpnpJs.tt OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml
	echo CpOpenhomeOrgSubscriptionLongPoll1.js
	$(ohNetGen) --language=js --stack=cp "--xml=OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml" --output=$(proxyJs) --domain=openhome.org --type=SubscriptionLongPoll --version=1

DvCppCore :   $(deviceCppCore)DvUpnpOrgAVTransport1.cpp $(deviceCppCore)DvUpnpOrgAVTransport2.cpp $(deviceCppCore)DvUpnpOrgConnectionManager1.cpp $(deviceCppCore)DvUpnpOrgConnectionManager2.cpp $(deviceCppCore)DvUpnpOrgContentDirectory1.cpp $(deviceCppCore)DvUpnpOrgContentDirectory2.cpp $(deviceCppCore)DvUpnpOrgContentDirectory3.cpp $(deviceCppCore)DvUpnpOrgRenderingControl1.cpp $(deviceCppCore)DvUpnpOrgRenderingControl2.cpp $(deviceCppCore)DvUpnpOrgScheduledRecording1.cpp $(deviceCppCore)DvUpnpOrgScheduledRecording2.cpp $(deviceCppCore)DvUpnpOrgSwitchPower1.cpp $(deviceCppCore)DvUpnpOrgDimming1.cpp $(deviceCppCore)DvAvOpenhomeOrgInfo1.cpp $(deviceCppCore)DvAvOpenhomeOrgTime1.cpp $(deviceCppCore)DvAvOpenhomeOrgPlaylist1.cpp $(deviceCppCore)DvAvOpenhomeOrgVolume1.cpp $(deviceCppCore)DvAvOpenhomeOrgProduct1.cpp $(deviceCppCore)DvAvOpenhomeOrgRadio1.cpp $(deviceCppCore)DvAvOpenhomeOrgReceiver1.cpp $(deviceCppCore)DvAvOpenhomeOrgSender1.cpp $(deviceCppCore)DvAvOpenhomeOrgPlaylistManager1.cpp $(deviceCppCore)DvAvOpenhomeOrgMediaServer1.cpp $(deviceCppCore)DvAvOpenhomeOrgNetworkMonitor1.cpp $(deviceCppCore)DvOpenhomeOrgTestBasic1.cpp $(deviceCppCore)DvOpenhomeOrgTestLights1.cpp $(deviceCppCore)DvOpenhomeOrgSubscriptionLongPoll1.cpp
$(deviceCppCore)DvUpnpOrgAVTransport1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo DvUpnpOrgAVTransport1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(deviceCppCore) --domain=upnp.org --type=AVTransport --version=1
$(deviceCppCore)DvUpnpOrgAVTransport2.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo DvUpnpOrgAVTransport2.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(deviceCppCore) --domain=upnp.org --type=AVTransport --version=2
$(deviceCppCore)DvUpnpOrgConnectionManager1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo DvUpnpOrgConnectionManager1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(deviceCppCore) --domain=upnp.org --type=ConnectionManager --version=1
$(deviceCppCore)DvUpnpOrgConnectionManager2.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo DvUpnpOrgConnectionManager2.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(deviceCppCore) --domain=upnp.org --type=ConnectionManager --version=2
$(deviceCppCore)DvUpnpOrgContentDirectory1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo DvUpnpOrgContentDirectory1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(deviceCppCore) --domain=upnp.org --type=ContentDirectory --version=1
$(deviceCppCore)DvUpnpOrgContentDirectory2.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo DvUpnpOrgContentDirectory2.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(deviceCppCore) --domain=upnp.org --type=ContentDirectory --version=2
$(deviceCppCore)DvUpnpOrgContentDirectory3.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo DvUpnpOrgContentDirectory3.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(deviceCppCore) --domain=upnp.org --type=ContentDirectory --version=3
$(deviceCppCore)DvUpnpOrgRenderingControl1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo DvUpnpOrgRenderingControl1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(deviceCppCore) --domain=upnp.org --type=RenderingControl --version=1
$(deviceCppCore)DvUpnpOrgRenderingControl2.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo DvUpnpOrgRenderingControl2.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(deviceCppCore) --domain=upnp.org --type=RenderingControl --version=2
$(deviceCppCore)DvUpnpOrgScheduledRecording1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo DvUpnpOrgScheduledRecording1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(deviceCppCore) --domain=upnp.org --type=ScheduledRecording --version=1
$(deviceCppCore)DvUpnpOrgScheduledRecording2.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo DvUpnpOrgScheduledRecording2.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(deviceCppCore) --domain=upnp.org --type=ScheduledRecording --version=2
$(deviceCppCore)DvUpnpOrgSwitchPower1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo DvUpnpOrgSwitchPower1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(deviceCppCore) --domain=upnp.org --type=SwitchPower --version=1
$(deviceCppCore)DvUpnpOrgDimming1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo DvUpnpOrgDimming1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(deviceCppCore) --domain=upnp.org --type=Dimming --version=1
$(deviceCppCore)DvAvOpenhomeOrgInfo1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Info1.xml
	echo DvAvOpenhomeOrgInfo1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Info1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=Info --version=1
$(deviceCppCore)DvAvOpenhomeOrgTime1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Time1.xml
	echo DvAvOpenhomeOrgTime1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Time1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=Time --version=1
$(deviceCppCore)DvAvOpenhomeOrgPlaylist1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml
	echo DvAvOpenhomeOrgPlaylist1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=Playlist --version=1
$(deviceCppCore)DvAvOpenhomeOrgVolume1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml
	echo DvAvOpenhomeOrgVolume1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=Volume --version=1
$(deviceCppCore)DvAvOpenhomeOrgProduct1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Product1.xml
	echo DvAvOpenhomeOrgProduct1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Product1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=Product --version=1
$(deviceCppCore)DvAvOpenhomeOrgRadio1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml
	echo DvAvOpenhomeOrgRadio1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=Radio --version=1
$(deviceCppCore)DvAvOpenhomeOrgReceiver1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml
	echo DvAvOpenhomeOrgReceiver1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=Receiver --version=1
$(deviceCppCore)DvAvOpenhomeOrgSender1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml
	echo DvAvOpenhomeOrgSender1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=Sender --version=1
$(deviceCppCore)DvAvOpenhomeOrgPlaylistManager1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml
	echo DvAvOpenhomeOrgPlaylistManager1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=PlaylistManager --version=1
$(deviceCppCore)DvAvOpenhomeOrgMediaServer1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml
	echo DvAvOpenhomeOrgMediaServer1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=MediaServer --version=1
$(deviceCppCore)DvAvOpenhomeOrgNetworkMonitor1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml
	echo DvAvOpenhomeOrgNetworkMonitor1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml" --output=$(deviceCppCore) --domain=av.openhome.org --type=NetworkMonitor --version=1
$(deviceCppCore)DvOpenhomeOrgTestBasic1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml
	echo DvOpenhomeOrgTestBasic1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml" --output=$(deviceCppCore) --domain=openhome.org --type=TestBasic --version=1
$(deviceCppCore)DvOpenhomeOrgTestLights1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml
	echo DvOpenhomeOrgTestLights1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml" --output=$(deviceCppCore) --domain=openhome.org --type=TestLights --version=1
$(deviceCppCore)DvOpenhomeOrgSubscriptionLongPoll1.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppCoreSource.tt OpenHome/Net/T4/Templates/DvUpnpCppCoreHeader.tt OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml
	echo DvOpenhomeOrgSubscriptionLongPoll1.cpp
	$(ohNetGen) --language=cppcore --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml" --output=$(deviceCppCore) --domain=openhome.org --type=SubscriptionLongPoll --version=1

DvCppStd :   $(deviceCppStd)DvUpnpOrgAVTransport1Std.cpp $(deviceCppStd)DvUpnpOrgAVTransport2Std.cpp $(deviceCppStd)DvUpnpOrgConnectionManager1Std.cpp $(deviceCppStd)DvUpnpOrgConnectionManager2Std.cpp $(deviceCppStd)DvUpnpOrgContentDirectory1Std.cpp $(deviceCppStd)DvUpnpOrgContentDirectory2Std.cpp $(deviceCppStd)DvUpnpOrgContentDirectory3Std.cpp $(deviceCppStd)DvUpnpOrgRenderingControl1Std.cpp $(deviceCppStd)DvUpnpOrgRenderingControl2Std.cpp $(deviceCppStd)DvUpnpOrgScheduledRecording1Std.cpp $(deviceCppStd)DvUpnpOrgScheduledRecording2Std.cpp $(deviceCppStd)DvUpnpOrgSwitchPower1Std.cpp $(deviceCppStd)DvUpnpOrgDimming1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgInfo1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgTime1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgPlaylist1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgVolume1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgProduct1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgRadio1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgReceiver1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgSender1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgPlaylistManager1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgMediaServer1Std.cpp $(deviceCppStd)DvAvOpenhomeOrgNetworkMonitor1Std.cpp $(deviceCppStd)DvOpenhomeOrgTestBasic1Std.cpp $(deviceCppStd)DvOpenhomeOrgTestLights1Std.cpp $(deviceCppStd)DvOpenhomeOrgSubscriptionLongPoll1Std.cpp
$(deviceCppStd)DvUpnpOrgAVTransport1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo DvUpnpOrgAVTransport1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(deviceCppStd) --domain=upnp.org --type=AVTransport --version=1
$(deviceCppStd)DvUpnpOrgAVTransport2Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo DvUpnpOrgAVTransport2Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(deviceCppStd) --domain=upnp.org --type=AVTransport --version=2
$(deviceCppStd)DvUpnpOrgConnectionManager1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo DvUpnpOrgConnectionManager1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(deviceCppStd) --domain=upnp.org --type=ConnectionManager --version=1
$(deviceCppStd)DvUpnpOrgConnectionManager2Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo DvUpnpOrgConnectionManager2Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(deviceCppStd) --domain=upnp.org --type=ConnectionManager --version=2
$(deviceCppStd)DvUpnpOrgContentDirectory1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo DvUpnpOrgContentDirectory1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(deviceCppStd) --domain=upnp.org --type=ContentDirectory --version=1
$(deviceCppStd)DvUpnpOrgContentDirectory2Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo DvUpnpOrgContentDirectory2Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(deviceCppStd) --domain=upnp.org --type=ContentDirectory --version=2
$(deviceCppStd)DvUpnpOrgContentDirectory3Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo DvUpnpOrgContentDirectory3Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(deviceCppStd) --domain=upnp.org --type=ContentDirectory --version=3
$(deviceCppStd)DvUpnpOrgRenderingControl1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo DvUpnpOrgRenderingControl1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(deviceCppStd) --domain=upnp.org --type=RenderingControl --version=1
$(deviceCppStd)DvUpnpOrgRenderingControl2Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo DvUpnpOrgRenderingControl2Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(deviceCppStd) --domain=upnp.org --type=RenderingControl --version=2
$(deviceCppStd)DvUpnpOrgScheduledRecording1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo DvUpnpOrgScheduledRecording1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(deviceCppStd) --domain=upnp.org --type=ScheduledRecording --version=1
$(deviceCppStd)DvUpnpOrgScheduledRecording2Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo DvUpnpOrgScheduledRecording2Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(deviceCppStd) --domain=upnp.org --type=ScheduledRecording --version=2
$(deviceCppStd)DvUpnpOrgSwitchPower1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo DvUpnpOrgSwitchPower1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(deviceCppStd) --domain=upnp.org --type=SwitchPower --version=1
$(deviceCppStd)DvUpnpOrgDimming1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo DvUpnpOrgDimming1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(deviceCppStd) --domain=upnp.org --type=Dimming --version=1
$(deviceCppStd)DvAvOpenhomeOrgInfo1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Info1.xml
	echo DvAvOpenhomeOrgInfo1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Info1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=Info --version=1
$(deviceCppStd)DvAvOpenhomeOrgTime1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Time1.xml
	echo DvAvOpenhomeOrgTime1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Time1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=Time --version=1
$(deviceCppStd)DvAvOpenhomeOrgPlaylist1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml
	echo DvAvOpenhomeOrgPlaylist1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=Playlist --version=1
$(deviceCppStd)DvAvOpenhomeOrgVolume1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml
	echo DvAvOpenhomeOrgVolume1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=Volume --version=1
$(deviceCppStd)DvAvOpenhomeOrgProduct1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Product1.xml
	echo DvAvOpenhomeOrgProduct1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Product1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=Product --version=1
$(deviceCppStd)DvAvOpenhomeOrgRadio1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml
	echo DvAvOpenhomeOrgRadio1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=Radio --version=1
$(deviceCppStd)DvAvOpenhomeOrgReceiver1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml
	echo DvAvOpenhomeOrgReceiver1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=Receiver --version=1
$(deviceCppStd)DvAvOpenhomeOrgSender1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml
	echo DvAvOpenhomeOrgSender1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=Sender --version=1
$(deviceCppStd)DvAvOpenhomeOrgPlaylistManager1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml
	echo DvAvOpenhomeOrgPlaylistManager1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=PlaylistManager --version=1
$(deviceCppStd)DvAvOpenhomeOrgMediaServer1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml
	echo DvAvOpenhomeOrgMediaServer1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=MediaServer --version=1
$(deviceCppStd)DvAvOpenhomeOrgNetworkMonitor1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml
	echo DvAvOpenhomeOrgNetworkMonitor1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml" --output=$(deviceCppStd) --domain=av.openhome.org --type=NetworkMonitor --version=1
$(deviceCppStd)DvOpenhomeOrgTestBasic1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml
	echo DvOpenhomeOrgTestBasic1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml" --output=$(deviceCppStd) --domain=openhome.org --type=TestBasic --version=1
$(deviceCppStd)DvOpenhomeOrgTestLights1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml
	echo DvOpenhomeOrgTestLights1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml" --output=$(deviceCppStd) --domain=openhome.org --type=TestLights --version=1
$(deviceCppStd)DvOpenhomeOrgSubscriptionLongPoll1Std.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCppStdSource.tt OpenHome/Net/T4/Templates/DvUpnpCppStdHeader.tt OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml
	echo DvOpenhomeOrgSubscriptionLongPoll1Std.cpp
	$(ohNetGen) --language=cpp --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml" --output=$(deviceCppStd) --domain=openhome.org --type=SubscriptionLongPoll --version=1

DvC :   $(deviceC)DvUpnpOrgAVTransport1C.cpp $(deviceC)DvUpnpOrgAVTransport2C.cpp $(deviceC)DvUpnpOrgConnectionManager1C.cpp $(deviceC)DvUpnpOrgConnectionManager2C.cpp $(deviceC)DvUpnpOrgContentDirectory1C.cpp $(deviceC)DvUpnpOrgContentDirectory2C.cpp $(deviceC)DvUpnpOrgContentDirectory3C.cpp $(deviceC)DvUpnpOrgRenderingControl1C.cpp $(deviceC)DvUpnpOrgRenderingControl2C.cpp $(deviceC)DvUpnpOrgScheduledRecording1C.cpp $(deviceC)DvUpnpOrgScheduledRecording2C.cpp $(deviceC)DvUpnpOrgSwitchPower1C.cpp $(deviceC)DvUpnpOrgDimming1C.cpp $(deviceC)DvAvOpenhomeOrgInfo1C.cpp $(deviceC)DvAvOpenhomeOrgTime1C.cpp $(deviceC)DvAvOpenhomeOrgPlaylist1C.cpp $(deviceC)DvAvOpenhomeOrgVolume1C.cpp $(deviceC)DvAvOpenhomeOrgProduct1C.cpp $(deviceC)DvAvOpenhomeOrgRadio1C.cpp $(deviceC)DvAvOpenhomeOrgReceiver1C.cpp $(deviceC)DvAvOpenhomeOrgSender1C.cpp $(deviceC)DvAvOpenhomeOrgPlaylistManager1C.cpp $(deviceC)DvAvOpenhomeOrgMediaServer1C.cpp $(deviceC)DvAvOpenhomeOrgNetworkMonitor1C.cpp $(deviceC)DvOpenhomeOrgTestBasic1C.cpp $(deviceC)DvOpenhomeOrgTestLights1C.cpp $(deviceC)DvOpenhomeOrgSubscriptionLongPoll1C.cpp
$(deviceC)DvUpnpOrgAVTransport1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo DvUpnpOrgAVTransport1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(deviceC) --domain=upnp.org --type=AVTransport --version=1
$(deviceC)DvUpnpOrgAVTransport2C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo DvUpnpOrgAVTransport2C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(deviceC) --domain=upnp.org --type=AVTransport --version=2
$(deviceC)DvUpnpOrgConnectionManager1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo DvUpnpOrgConnectionManager1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(deviceC) --domain=upnp.org --type=ConnectionManager --version=1
$(deviceC)DvUpnpOrgConnectionManager2C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo DvUpnpOrgConnectionManager2C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(deviceC) --domain=upnp.org --type=ConnectionManager --version=2
$(deviceC)DvUpnpOrgContentDirectory1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo DvUpnpOrgContentDirectory1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(deviceC) --domain=upnp.org --type=ContentDirectory --version=1
$(deviceC)DvUpnpOrgContentDirectory2C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo DvUpnpOrgContentDirectory2C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(deviceC) --domain=upnp.org --type=ContentDirectory --version=2
$(deviceC)DvUpnpOrgContentDirectory3C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo DvUpnpOrgContentDirectory3C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(deviceC) --domain=upnp.org --type=ContentDirectory --version=3
$(deviceC)DvUpnpOrgRenderingControl1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo DvUpnpOrgRenderingControl1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(deviceC) --domain=upnp.org --type=RenderingControl --version=1
$(deviceC)DvUpnpOrgRenderingControl2C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo DvUpnpOrgRenderingControl2C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(deviceC) --domain=upnp.org --type=RenderingControl --version=2
$(deviceC)DvUpnpOrgScheduledRecording1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo DvUpnpOrgScheduledRecording1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(deviceC) --domain=upnp.org --type=ScheduledRecording --version=1
$(deviceC)DvUpnpOrgScheduledRecording2C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo DvUpnpOrgScheduledRecording2C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(deviceC) --domain=upnp.org --type=ScheduledRecording --version=2
$(deviceC)DvUpnpOrgSwitchPower1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo DvUpnpOrgSwitchPower1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(deviceC) --domain=upnp.org --type=SwitchPower --version=1
$(deviceC)DvUpnpOrgDimming1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo DvUpnpOrgDimming1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(deviceC) --domain=upnp.org --type=Dimming --version=1
$(deviceC)DvAvOpenhomeOrgInfo1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Info1.xml
	echo DvAvOpenhomeOrgInfo1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Info1.xml" --output=$(deviceC) --domain=av.openhome.org --type=Info --version=1
$(deviceC)DvAvOpenhomeOrgTime1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Time1.xml
	echo DvAvOpenhomeOrgTime1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Time1.xml" --output=$(deviceC) --domain=av.openhome.org --type=Time --version=1
$(deviceC)DvAvOpenhomeOrgPlaylist1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml
	echo DvAvOpenhomeOrgPlaylist1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml" --output=$(deviceC) --domain=av.openhome.org --type=Playlist --version=1
$(deviceC)DvAvOpenhomeOrgVolume1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml
	echo DvAvOpenhomeOrgVolume1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml" --output=$(deviceC) --domain=av.openhome.org --type=Volume --version=1
$(deviceC)DvAvOpenhomeOrgProduct1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Product1.xml
	echo DvAvOpenhomeOrgProduct1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Product1.xml" --output=$(deviceC) --domain=av.openhome.org --type=Product --version=1
$(deviceC)DvAvOpenhomeOrgRadio1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml
	echo DvAvOpenhomeOrgRadio1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml" --output=$(deviceC) --domain=av.openhome.org --type=Radio --version=1
$(deviceC)DvAvOpenhomeOrgReceiver1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml
	echo DvAvOpenhomeOrgReceiver1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml" --output=$(deviceC) --domain=av.openhome.org --type=Receiver --version=1
$(deviceC)DvAvOpenhomeOrgSender1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml
	echo DvAvOpenhomeOrgSender1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml" --output=$(deviceC) --domain=av.openhome.org --type=Sender --version=1
$(deviceC)DvAvOpenhomeOrgPlaylistManager1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml
	echo DvAvOpenhomeOrgPlaylistManager1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml" --output=$(deviceC) --domain=av.openhome.org --type=PlaylistManager --version=1
$(deviceC)DvAvOpenhomeOrgMediaServer1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml
	echo DvAvOpenhomeOrgMediaServer1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml" --output=$(deviceC) --domain=av.openhome.org --type=MediaServer --version=1
$(deviceC)DvAvOpenhomeOrgNetworkMonitor1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml
	echo DvAvOpenhomeOrgNetworkMonitor1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml" --output=$(deviceC) --domain=av.openhome.org --type=NetworkMonitor --version=1
$(deviceC)DvOpenhomeOrgTestBasic1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml
	echo DvOpenhomeOrgTestBasic1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml" --output=$(deviceC) --domain=openhome.org --type=TestBasic --version=1
$(deviceC)DvOpenhomeOrgTestLights1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml
	echo DvOpenhomeOrgTestLights1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml" --output=$(deviceC) --domain=openhome.org --type=TestLights --version=1
$(deviceC)DvOpenhomeOrgSubscriptionLongPoll1C.cpp : $(tt) OpenHome/Net/T4/Templates/DvUpnpCSource.tt OpenHome/Net/T4/Templates/DvUpnpCHeader.tt OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml
	echo DvOpenhomeOrgSubscriptionLongPoll1C.cpp
	$(ohNetGen) --language=c --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml" --output=$(deviceC) --domain=openhome.org --type=SubscriptionLongPoll --version=1

DvCs:   $(deviceCs)DvUpnpOrgAVTransport1.cs $(deviceCs)DvUpnpOrgAVTransport2.cs $(deviceCs)DvUpnpOrgConnectionManager1.cs $(deviceCs)DvUpnpOrgConnectionManager2.cs $(deviceCs)DvUpnpOrgContentDirectory1.cs $(deviceCs)DvUpnpOrgContentDirectory2.cs $(deviceCs)DvUpnpOrgContentDirectory3.cs $(deviceCs)DvUpnpOrgRenderingControl1.cs $(deviceCs)DvUpnpOrgRenderingControl2.cs $(deviceCs)DvUpnpOrgScheduledRecording1.cs $(deviceCs)DvUpnpOrgScheduledRecording2.cs $(deviceCs)DvUpnpOrgSwitchPower1.cs $(deviceCs)DvUpnpOrgDimming1.cs $(deviceCs)DvAvOpenhomeOrgInfo1.cs $(deviceCs)DvAvOpenhomeOrgTime1.cs $(deviceCs)DvAvOpenhomeOrgPlaylist1.cs $(deviceCs)DvAvOpenhomeOrgVolume1.cs $(deviceCs)DvAvOpenhomeOrgProduct1.cs $(deviceCs)DvAvOpenhomeOrgRadio1.cs $(deviceCs)DvAvOpenhomeOrgReceiver1.cs $(deviceCs)DvAvOpenhomeOrgSender1.cs $(deviceCs)DvAvOpenhomeOrgPlaylistManager1.cs $(deviceCs)DvAvOpenhomeOrgMediaServer1.cs $(deviceCs)DvAvOpenhomeOrgNetworkMonitor1.cs $(deviceCs)DvOpenhomeOrgTestBasic1.cs $(deviceCs)DvOpenhomeOrgTestLights1.cs $(deviceCs)DvOpenhomeOrgSubscriptionLongPoll1.cs
$(deviceCs)DvUpnpOrgAVTransport1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo DvUpnpOrgAVTransport1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(deviceCs) --domain=upnp.org --type=AVTransport --version=1
$(deviceCs)DvUpnpOrgAVTransport2.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo DvUpnpOrgAVTransport2.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(deviceCs) --domain=upnp.org --type=AVTransport --version=2
$(deviceCs)DvUpnpOrgConnectionManager1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo DvUpnpOrgConnectionManager1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(deviceCs) --domain=upnp.org --type=ConnectionManager --version=1
$(deviceCs)DvUpnpOrgConnectionManager2.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo DvUpnpOrgConnectionManager2.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(deviceCs) --domain=upnp.org --type=ConnectionManager --version=2
$(deviceCs)DvUpnpOrgContentDirectory1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo DvUpnpOrgContentDirectory1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(deviceCs) --domain=upnp.org --type=ContentDirectory --version=1
$(deviceCs)DvUpnpOrgContentDirectory2.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo DvUpnpOrgContentDirectory2.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(deviceCs) --domain=upnp.org --type=ContentDirectory --version=2
$(deviceCs)DvUpnpOrgContentDirectory3.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo DvUpnpOrgContentDirectory3.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(deviceCs) --domain=upnp.org --type=ContentDirectory --version=3
$(deviceCs)DvUpnpOrgRenderingControl1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo DvUpnpOrgRenderingControl1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(deviceCs) --domain=upnp.org --type=RenderingControl --version=1
$(deviceCs)DvUpnpOrgRenderingControl2.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo DvUpnpOrgRenderingControl2.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(deviceCs) --domain=upnp.org --type=RenderingControl --version=2
$(deviceCs)DvUpnpOrgScheduledRecording1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo DvUpnpOrgScheduledRecording1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(deviceCs) --domain=upnp.org --type=ScheduledRecording --version=1
$(deviceCs)DvUpnpOrgScheduledRecording2.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo DvUpnpOrgScheduledRecording2.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(deviceCs) --domain=upnp.org --type=ScheduledRecording --version=2
$(deviceCs)DvUpnpOrgSwitchPower1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo DvUpnpOrgSwitchPower1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(deviceCs) --domain=upnp.org --type=SwitchPower --version=1
$(deviceCs)DvUpnpOrgDimming1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo DvUpnpOrgDimming1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(deviceCs) --domain=upnp.org --type=Dimming --version=1
$(deviceCs)DvAvOpenhomeOrgInfo1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Info1.xml
	echo DvAvOpenhomeOrgInfo1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Info1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=Info --version=1
$(deviceCs)DvAvOpenhomeOrgTime1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Time1.xml
	echo DvAvOpenhomeOrgTime1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Time1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=Time --version=1
$(deviceCs)DvAvOpenhomeOrgPlaylist1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml
	echo DvAvOpenhomeOrgPlaylist1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=Playlist --version=1
$(deviceCs)DvAvOpenhomeOrgVolume1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml
	echo DvAvOpenhomeOrgVolume1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=Volume --version=1
$(deviceCs)DvAvOpenhomeOrgProduct1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Product1.xml
	echo DvAvOpenhomeOrgProduct1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Product1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=Product --version=1
$(deviceCs)DvAvOpenhomeOrgRadio1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml
	echo DvAvOpenhomeOrgRadio1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=Radio --version=1
$(deviceCs)DvAvOpenhomeOrgReceiver1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml
	echo DvAvOpenhomeOrgReceiver1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=Receiver --version=1
$(deviceCs)DvAvOpenhomeOrgSender1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml
	echo DvAvOpenhomeOrgSender1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=Sender --version=1
$(deviceCs)DvAvOpenhomeOrgPlaylistManager1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml
	echo DvAvOpenhomeOrgPlaylistManager1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=PlaylistManager --version=1
$(deviceCs)DvAvOpenhomeOrgMediaServer1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml
	echo DvAvOpenhomeOrgMediaServer1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=MediaServer --version=1
$(deviceCs)DvAvOpenhomeOrgNetworkMonitor1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml
	echo DvAvOpenhomeOrgNetworkMonitor1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml" --output=$(deviceCs) --domain=av.openhome.org --type=NetworkMonitor --version=1
$(deviceCs)DvOpenhomeOrgTestBasic1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml
	echo DvOpenhomeOrgTestBasic1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml" --output=$(deviceCs) --domain=openhome.org --type=TestBasic --version=1
$(deviceCs)DvOpenhomeOrgTestLights1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml
	echo DvOpenhomeOrgTestLights1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml" --output=$(deviceCs) --domain=openhome.org --type=TestLights --version=1
$(deviceCs)DvOpenhomeOrgSubscriptionLongPoll1.cs : $(tt) OpenHome/Net/T4/Templates/DvUpnpCs.tt OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml
	echo DvOpenhomeOrgSubscriptionLongPoll1.cs
	$(ohNetGen) --language=cs --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml" --output=$(deviceCs) --domain=openhome.org --type=SubscriptionLongPoll --version=1

DvJava:   $(deviceJava)DvProviderUpnpOrgAVTransport1.java $(deviceJava)DvProviderUpnpOrgAVTransport2.java $(deviceJava)DvProviderUpnpOrgConnectionManager1.java $(deviceJava)DvProviderUpnpOrgConnectionManager2.java $(deviceJava)DvProviderUpnpOrgContentDirectory1.java $(deviceJava)DvProviderUpnpOrgContentDirectory2.java $(deviceJava)DvProviderUpnpOrgContentDirectory3.java $(deviceJava)DvProviderUpnpOrgRenderingControl1.java $(deviceJava)DvProviderUpnpOrgRenderingControl2.java $(deviceJava)DvProviderUpnpOrgScheduledRecording1.java $(deviceJava)DvProviderUpnpOrgScheduledRecording2.java $(deviceJava)DvProviderUpnpOrgSwitchPower1.java $(deviceJava)DvProviderUpnpOrgDimming1.java $(deviceJava)DvProviderAvOpenhomeOrgInfo1.java $(deviceJava)DvProviderAvOpenhomeOrgTime1.java $(deviceJava)DvProviderAvOpenhomeOrgPlaylist1.java $(deviceJava)DvProviderAvOpenhomeOrgVolume1.java $(deviceJava)DvProviderAvOpenhomeOrgProduct1.java $(deviceJava)DvProviderAvOpenhomeOrgRadio1.java $(deviceJava)DvProviderAvOpenhomeOrgReceiver1.java $(deviceJava)DvProviderAvOpenhomeOrgSender1.java $(deviceJava)DvProviderAvOpenhomeOrgPlaylistManager1.java $(deviceJava)DvProviderAvOpenhomeOrgMediaServer1.java $(deviceJava)DvProviderAvOpenhomeOrgNetworkMonitor1.java $(deviceJava)DvProviderOpenhomeOrgTestBasic1.java $(deviceJava)DvProviderOpenhomeOrgTestLights1.java $(deviceJava)DvProviderOpenhomeOrgSubscriptionLongPoll1.java
$(deviceJava)DvProviderUpnpOrgAVTransport1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml
	echo DvProviderUpnpOrgAVTransport1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport1.xml" --output=$(deviceJava) --domain=upnp.org --type=AVTransport --version=1
$(deviceJava)DvProviderUpnpOrgAVTransport2.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml
	echo DvProviderUpnpOrgAVTransport2.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/AVTransport2.xml" --output=$(deviceJava) --domain=upnp.org --type=AVTransport --version=2
$(deviceJava)DvProviderUpnpOrgConnectionManager1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml
	echo DvProviderUpnpOrgConnectionManager1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager1.xml" --output=$(deviceJava) --domain=upnp.org --type=ConnectionManager --version=1
$(deviceJava)DvProviderUpnpOrgConnectionManager2.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml
	echo DvProviderUpnpOrgConnectionManager2.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ConnectionManager2.xml" --output=$(deviceJava) --domain=upnp.org --type=ConnectionManager --version=2
$(deviceJava)DvProviderUpnpOrgContentDirectory1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml
	echo DvProviderUpnpOrgContentDirectory1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory1.xml" --output=$(deviceJava) --domain=upnp.org --type=ContentDirectory --version=1
$(deviceJava)DvProviderUpnpOrgContentDirectory2.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml
	echo DvProviderUpnpOrgContentDirectory2.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory2.xml" --output=$(deviceJava) --domain=upnp.org --type=ContentDirectory --version=2
$(deviceJava)DvProviderUpnpOrgContentDirectory3.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml
	echo DvProviderUpnpOrgContentDirectory3.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ContentDirectory3.xml" --output=$(deviceJava) --domain=upnp.org --type=ContentDirectory --version=3
$(deviceJava)DvProviderUpnpOrgRenderingControl1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml
	echo DvProviderUpnpOrgRenderingControl1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl1.xml" --output=$(deviceJava) --domain=upnp.org --type=RenderingControl --version=1
$(deviceJava)DvProviderUpnpOrgRenderingControl2.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml
	echo DvProviderUpnpOrgRenderingControl2.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/RenderingControl2.xml" --output=$(deviceJava) --domain=upnp.org --type=RenderingControl --version=2
$(deviceJava)DvProviderUpnpOrgScheduledRecording1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml
	echo DvProviderUpnpOrgScheduledRecording1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording1.xml" --output=$(deviceJava) --domain=upnp.org --type=ScheduledRecording --version=1
$(deviceJava)DvProviderUpnpOrgScheduledRecording2.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml
	echo DvProviderUpnpOrgScheduledRecording2.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/MediaServer_3/ScheduledRecording2.xml" --output=$(deviceJava) --domain=upnp.org --type=ScheduledRecording --version=2
$(deviceJava)DvProviderUpnpOrgSwitchPower1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml
	echo DvProviderUpnpOrgSwitchPower1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/SwitchPower1.xml" --output=$(deviceJava) --domain=upnp.org --type=SwitchPower --version=1
$(deviceJava)DvProviderUpnpOrgDimming1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml
	echo DvProviderUpnpOrgDimming1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/Upnp/LightingControls_1/Dimming1.xml" --output=$(deviceJava) --domain=upnp.org --type=Dimming --version=1
$(deviceJava)DvProviderAvOpenhomeOrgInfo1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Info1.xml
	echo DvProviderAvOpenhomeOrgInfo1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Info1.xml" --output=$(deviceJava) --domain=av.openhome.org --type=Info --version=1
$(deviceJava)DvProviderAvOpenhomeOrgTime1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Time1.xml
	echo DvProviderAvOpenhomeOrgTime1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Time1.xml" --output=$(deviceJava) --domain=av.openhome.org --type=Time --version=1
$(deviceJava)DvProviderAvOpenhomeOrgPlaylist1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml
	echo DvProviderAvOpenhomeOrgPlaylist1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Playlist1.xml" --output=$(deviceJava) --domain=av.openhome.org --type=Playlist --version=1
$(deviceJava)DvProviderAvOpenhomeOrgVolume1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml
	echo DvProviderAvOpenhomeOrgVolume1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Volume1.xml" --output=$(deviceJava) --domain=av.openhome.org --type=Volume --version=1
$(deviceJava)DvProviderAvOpenhomeOrgProduct1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Product1.xml
	echo DvProviderAvOpenhomeOrgProduct1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Product1.xml" --output=$(deviceJava) --domain=av.openhome.org --type=Product --version=1
$(deviceJava)DvProviderAvOpenhomeOrgRadio1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml
	echo DvProviderAvOpenhomeOrgRadio1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Radio1.xml" --output=$(deviceJava) --domain=av.openhome.org --type=Radio --version=1
$(deviceJava)DvProviderAvOpenhomeOrgReceiver1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml
	echo DvProviderAvOpenhomeOrgReceiver1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Receiver1.xml" --output=$(deviceJava) --domain=av.openhome.org --type=Receiver --version=1
$(deviceJava)DvProviderAvOpenhomeOrgSender1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml
	echo DvProviderAvOpenhomeOrgSender1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Sender1.xml" --output=$(deviceJava) --domain=av.openhome.org --type=Sender --version=1
$(deviceJava)DvProviderAvOpenhomeOrgPlaylistManager1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml
	echo DvProviderAvOpenhomeOrgPlaylistManager1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/PlaylistManager1.xml" --output=$(deviceJava) --domain=av.openhome.org --type=PlaylistManager --version=1
$(deviceJava)DvProviderAvOpenhomeOrgMediaServer1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml
	echo DvProviderAvOpenhomeOrgMediaServer1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/MediaServer1.xml" --output=$(deviceJava) --domain=av.openhome.org --type=MediaServer --version=1
$(deviceJava)DvProviderAvOpenhomeOrgNetworkMonitor1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml
	echo DvProviderAvOpenhomeOrgNetworkMonitor1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/NetworkMonitor1.xml" --output=$(deviceJava) --domain=av.openhome.org --type=NetworkMonitor --version=1
$(deviceJava)DvProviderOpenhomeOrgTestBasic1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml
	echo DvProviderOpenhomeOrgTestBasic1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestBasic1.xml" --output=$(deviceJava) --domain=openhome.org --type=TestBasic --version=1
$(deviceJava)DvProviderOpenhomeOrgTestLights1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml
	echo DvProviderOpenhomeOrgTestLights1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/Test/TestLights1.xml" --output=$(deviceJava) --domain=openhome.org --type=TestLights --version=1
$(deviceJava)DvProviderOpenhomeOrgSubscriptionLongPoll1.java : $(tt) OpenHome/Net/T4/Templates/DvUpnpJava.tt OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml
	echo DvProviderOpenhomeOrgSubscriptionLongPoll1.java
	$(ohNetGen) --language=java --stack=dv "--xml=OpenHome/Net/Service/Upnp/OpenHome/SubscriptionLongPoll1.xml" --output=$(deviceJava) --domain=openhome.org --type=SubscriptionLongPoll --version=1

