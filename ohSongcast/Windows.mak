objdir = Build/Obj/Windows
incdir = Build/Include
ohnetdir = ../Upnp/Build/Obj/Windows/Debug
templatesDir = ../Upnp/T4/Templates

# Macros used by Common.mak

ar = lib /nologo /out:$(objdir)
cflags = /MDd /W4 /WX /EHsc /RTC1 /Zi /FR$(objdir) /Gz -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -D_CRT_SECURE_NO_WARNINGS /Od -DDllImport=__declspec(dllimport) -DDllExport=__declspec(dllexport) -DDllExportClass=
objdirbare = Build\Obj\Windows
objdir = $(objdirbare)^\
inc_build = Build\Include
includes = -I..\Upnp\Build\Include -I..\Upnp\Build\Include\Cpp
bundle_build = Build\Bundles
osdir = Windows
objext = obj
libprefix = 
libext = lib
exeext = exe
compiler = cl /nologo /Fo$(objdir)
link = link /nologo /debug /SUBSYSTEM:CONSOLE /map Ws2_32.lib Iphlpapi.lib /incremental:no
linkoutput = /out:
dllprefix =
dllext = dll
link_dll = link /nologo /debug /map Ws2_32.lib Iphlpapi.lib /dll
csharp = csc /nologo /platform:x86
publiccsdir = Public\Cs^\
dirsep = ^\
installdir = $(PROGRAMFILES)\Zapp
installlibdir = $(installdir)\lib
installincludedir = $(installdir)\include
mkdir = Scripts\mkdir.bat
rmdir = Scripts\rmdir.bat
uset4 = no

objects_topology = $(ohnetdir)/CpTopology.$(objext) \
    		       $(ohnetdir)/CpTopology1.$(objext) \
    		       $(ohnetdir)/CpTopology2.$(objext) \
    		       $(ohnetdir)/CpTopology3.$(objext) \
			       $(ohnetdir)/CpAvOpenhomeOrgProduct1.$(objext) \
			       $(ohnetdir)/CpAvOpenhomeOrgVolume1.$(objext)

all: $(objdir)/$(dllprefix)ohSoundcard.$(dllext) $(objdir)/TestSoundcard.$(exeext) $(objdir)/TestSoundcardCs.$(exeext) $(objdir)/TestReceiverManager1.$(exeext) $(objdir)/TestReceiverManager2.$(exeext) $(objdir)/TestReceiverManager3.$(exeext) $(objdir)/TestReceiverManager3.$(exeext) $(objdir)/WavSender.$(exeext) $(objdir)/ZoneWatcher.$(exeext)

$(objdir)/$(dllprefix)ohSoundcard.$(dllext) : Services/DvAvOpenhomeOrgSender1.cpp Ohm.cpp OhmSender.cpp ohSoundcard/Windows/Soundcard.cpp
    if not exist $(objdirbare) mkdir $(objdirbare)
	$(compiler)/Ohm.$(objext) -c $(cflags) $(includes) Ohm.cpp
	$(compiler)/OhmSender.$(objext) -c $(cflags) $(includes) OhmSender.cpp
	$(compiler)/ReceiverManager1.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager1.cpp 
	$(compiler)/ReceiverManager2.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager2.cpp 
	$(compiler)/ReceiverManager3.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager3.cpp 
	$(compiler)/Soundcard.$(objext) -c $(cflags) $(includes) ohSoundcard/Windows/Soundcard.cpp
	$(link_dll) $(linkoutput)$(objdir)/$(dllprefix)ohSoundcard.$(dllext) $(ohnetdir)/ohNetCore.lib $(objects_topology) $(ohnetdir)/DvAvOpenhomeOrgSender1.$(objext) $(ohnetdir)/CpAvOpenhomeOrgReceiver1.$(objext) $(objdir)/Ohm.$(objext) $(objdir)/OhmSender.$(objext) $(objdir)/ReceiverManager1.$(objext) $(objdir)/ReceiverManager2.$(objext) $(objdir)/ReceiverManager3.$(objext) $(objdir)/Soundcard.$(objext) kernel32.lib setupapi.lib

$(objdir)/$(dllprefix)ohSoundcard.net.$(dllext) : $(objdir)/$(dllprefix)ohSoundcard.$(dllext) ohSoundcard\Windows\Soundcard.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)/$(dllprefix)ohSoundcard.net.$(dllext) \
		ohSoundcard\Windows\Soundcard.cs

$(objdir)/TestSoundcardCs.$(exeext) : $(objdir)/$(dllprefix)ohSoundcard.net.$(dllext) ohSoundcard/Windows/TestSoundcardCs.cs
	$(csharp) /unsafe /t:exe /debug+ \
		/out:$(objdir)TestSoundcardCs.exe \
		/reference:System.dll \
		/reference:System.Net.dll \
		/reference:$(objdir)/$(dllprefix)ohSoundcard.net.$(dllext)  \
		ohSoundcard\Windows\TestSoundcardCs.cs

$(objdir)/TestReceiverManager1.$(exeext) : ohSoundcard/ReceiverManager1.cpp ohSoundcard/TestReceiverManager1.cpp 
	$(compiler)/ReceiverManager1.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager1.cpp 
    $(compiler)/TestReceiverManager1.$(objext) -c $(cflags) $(includes) ohSoundcard/TestReceiverManager1.cpp 
    $(link) $(linkoutput)$(objdir)/TestReceiverManager1.$(exeext) $(objdir)/ReceiverManager1.$(objext) $(objdir)/TestReceiverManager1.$(objext) $(objects_topology) $(ohnetdir)/ohNetCore.lib $(ohnetdir)/TestFramework.$(libext)  
 	
$(objdir)/TestReceiverManager2.$(exeext) : ohSoundcard/ReceiverManager2.cpp ohSoundcard/TestReceiverManager1.cpp ohSoundcard/TestReceiverManager2.cpp
	$(compiler)/ReceiverManager1.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager1.cpp 
	$(compiler)/ReceiverManager2.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager2.cpp 
    $(compiler)/TestReceiverManager2.$(objext) -c $(cflags) $(includes) ohSoundcard/TestReceiverManager2.cpp 
    $(link) $(linkoutput)$(objdir)/TestReceiverManager2.$(exeext) $(objdir)/ReceiverManager2.$(objext) $(objdir)/ReceiverManager1.$(objext) $(objdir)/TestReceiverManager2.$(objext) $(objects_topology) $(ohnetdir)/ohNetCore.lib $(ohnetdir)/CpAvOpenhomeOrgReceiver1.$(objext) $(ohnetdir)/TestFramework.$(libext)  
 	
$(objdir)/TestReceiverManager3.$(exeext) : ohSoundcard/ReceiverManager3.cpp ohSoundcard/TestReceiverManager1.cpp ohSoundcard/TestReceiverManager2.cpp ohSoundcard/TestReceiverManager3.cpp
	$(compiler)/ReceiverManager1.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager1.cpp 
	$(compiler)/ReceiverManager2.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager2.cpp 
	$(compiler)/ReceiverManager3.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager3.cpp 
    $(compiler)/TestReceiverManager3.$(objext) -c $(cflags) $(includes) ohSoundcard/TestReceiverManager3.cpp 
    $(link) $(linkoutput)$(objdir)/TestReceiverManager3.$(exeext) $(objdir)/ReceiverManager3.$(objext) $(objdir)/ReceiverManager2.$(objext) $(objdir)/ReceiverManager1.$(objext) $(objdir)/TestReceiverManager3.$(objext) $(objects_topology) $(ohnetdir)/ohNetCore.lib $(ohnetdir)/CpAvOpenhomeOrgReceiver1.$(objext) $(ohnetdir)/TestFramework.$(libext)  
 	
$(objdir)/TestSoundcard.$(exeext) : $(objdir)/$(dllprefix)ohSoundcard.$(dllext) ohSoundcard/Windows/TestSoundcard.cpp
	$(compiler)/TestSoundcard.$(objext) -c $(cflags) $(includes) ohSoundcard/Windows/TestSoundcard.cpp
	$(link) $(linkoutput)$(objdir)/TestSoundcard.$(exeext) $(objdir)/$(libprefix)ohSoundcard.$(libext) $(objdir)/TestSoundcard.$(objext) 

$(objdir)/ZoneWatcher.$(exeext) : ZoneWatcher/ZoneWatcher.cpp
    if not exist $(objdirbare) mkdir $(objdirbare)
	$(compiler)/Ohm.$(objext) -c $(cflags) $(includes) Ohm.cpp
	$(compiler)/ZoneWatcher.$(objext) -c $(cflags) $(includes) ZoneWatcher/ZoneWatcher.cpp
	$(link) $(linkoutput)$(objdir)/ZoneWatcher.$(exeext) $(objdir)/ZoneWatcher.$(objext) $(objdir)/Ohm.$(objext) $(ohnetdir)/$(libprefix)ohNetCore.$(libext) $(ohnetdir)/$(libprefix)TestFramework.$(libext)

$(objdir)/WavSender.$(exeext) : Services/DvAvOpenhomeOrgSender1.cpp Ohm.cpp OhmSender.cpp WavSender/WavSender.cpp
    if not exist $(objdirbare) mkdir $(objdirbare)
	$(compiler)/DvAvOpenhomeOrgSender1.$(objext) -c $(cflags) $(includes) Services/DvAvOpenhomeOrgSender1.cpp
	$(compiler)/Ohm.$(objext) -c $(cflags) $(includes) Ohm.cpp
	$(compiler)/OhmSender.$(objext) -c $(cflags) $(includes) OhmSender.cpp
	$(compiler)/WavSender.$(objext) -c $(cflags) $(includes) WavSender/WavSender.cpp
	$(link) $(linkoutput)$(objdir)/WavSender.$(exeext) $(objdir)/WavSender.$(objext) $(ohnetdir)/DvAvOpenhomeOrgSender1.$(objext) $(objdir)/Ohm.$(objext) $(objdir)/OhmSender.$(objext) $(ohnetdir)/$(libprefix)ohNetCore.$(libext) $(ohnetdir)/$(libprefix)TestFramework.$(libext)

#$(objdir)/WavReceiver.$(exeext) : Services/DvAvOpenhomeOrgProduct1.cpp Services/DvAvOpenhomeOrgReceiver1.cpp Product.cpp WavReceiver/WavReceiver.cpp
#    if not exist $(objdirbare) mkdir $(objdirbare)
#	$(compiler)/DvAvOpenhomeOrgProduct1.$(objext) -c $(cflags) $(includes) Services/DvAvOpenhomeOrgProduct1.cpp
#	$(compiler)/DvAvOpenhomeOrgReceiver1.$(objext) -c $(cflags) $(includes) Services/DvAvOpenhomeOrgReceiver1.cpp
#	$(compiler)/Product.$(objext) -c $(cflags) $(includes) Product.cpp
#	$(compiler)/Receiver.$(objext) -c $(cflags) $(includes) WavReceiver/WavReceiver.cpp
#	$(link) $(linkoutput)$(objdir)/WavReceiver.$(exeext) $(objdir)/WavReceiver.$(objext) $(objdir)/Product.$(objext) $(objdir)/DvAvOpenhomeOrgProduct1.$(objext) $(objdir)/DvAvOpenhomeOrgReceiver1.$(objext) $(ohnetdir)/$(libprefix)ohNetCore.$(libext) $(ohnetdir)/$(libprefix)TestFramework.$(libext)

t4 = ..\Upnp\Build\Windows\Tools\TextTransform.exe

gen: DvAvOpenhomeOrgSender1.h DvAvOpenhomeOrgSender1.cpp DvAvOpenhomeOrgProduct1.h DvAvOpenhomeOrgProduct1.cpp DvAvOpenhomeOrgReceiver1.h DvAvOpenhomeOrgReceiver1.cpp

DvAvOpenhomeOrgSender1.h : $(templatesDir)/DvUpnpCppCoreHeader.tt Services/Sender1.xml
	$(t4) -o Services/DvAvOpenhomeOrgSender1.h $(templatesDir)/DvUpnpCppCoreHeader.tt -a "xml:Services/Sender1.xml" -a domain:av.openhome.org -a type:Sender -a version:1
DvAvOpenhomeOrgSender1.cpp : ../Upnp/T4/Templates/DvUpnpCppCoreSource.tt Services/Sender1.xml
	$(t4) -o Services/DvAvOpenhomeOrgSender1.cpp $(templatesDir)/DvUpnpCppCoreSource.tt -a "xml:Services/Sender1.xml" -a domain:av.openhome.org -a type:Sender -a version:1

DvAvOpenhomeOrgProduct1.h : $(templatesDir)/DvUpnpCppCoreHeader.tt Services/Product1.xml
	$(t4) -o Services/DvAvOpenhomeOrgProduct1.h $(templatesDir)/DvUpnpCppCoreHeader.tt -a "xml:Services/Product1.xml" -a domain:av.openhome.org -a type:Product -a version:1
DvAvOpenhomeOrgProduct1.cpp : ../Upnp/T4/Templates/DvUpnpCppCoreSource.tt Services/Product1.xml
	$(t4) -o Services/DvAvOpenhomeOrgProduct1.cpp $(templatesDir)/DvUpnpCppCoreSource.tt -a "xml:Services/Product1.xml" -a domain:av.openhome.org -a type:Product -a version:1

DvAvOpenhomeOrgReceiver1.h : $(templatesDir)/DvUpnpCppCoreHeader.tt Services/Receiver1.xml
	$(t4) -o Services/DvAvOpenhomeOrgReceiver1.h $(templatesDir)/DvUpnpCppCoreHeader.tt -a "xml:Services/Receiver1.xml" -a domain:av.openhome.org -a type:Receiver -a version:1
DvAvOpenhomeOrgReceiver1.cpp : ../Upnp/T4/Templates/DvUpnpCppCoreSource.tt Services/Receiver1.xml
	$(t4) -o Services/DvAvOpenhomeOrgReceiver1.cpp $(templatesDir)/DvUpnpCppCoreSource.tt -a "xml:Services/Receiver1.xml" -a domain:av.openhome.org -a type:Receiver -a version:1
