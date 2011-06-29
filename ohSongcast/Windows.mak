# Makefile for Windows
#

!if "$(release)"=="1"
link_flag_debug = 
debug_specific_cflags = /MT /Ox
build_dir = Release
ohnetdir = ../Upnp/Build/Obj/Windows/Release
!else
link_flag_debug = /debug
debug_specific_cflags = /MTd /Zi /Od /RTC1
build_dir = Debug
ohnetdir = ../Upnp/Build/Obj/Windows/Debug
!endif

# Macros used by Common.mak

ar = lib /nologo /out:$(objdir)
cflags = $(debug_specific_cflags) /W4 /WX /EHsc /FR$(objdir) /Gz -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -D_CRT_SECURE_NO_WARNINGS -DDllExport=__declspec(dllexport) -DDllExportClass=
objdirbare = Build\Obj\Windows\$(build_dir)
objdir = $(objdirbare)^\
inc_build = Build\Include
includes = -I..\Upnp\Build\Include -I..\Upnp\Build\Include\Cpp
bundle_build = Build\Bundles
osdir = Windows
objext = obj
libprefix = lib
libext = lib
exeext = exe
compiler = cl /nologo /Fo$(objdir)
link = link /nologo $(link_flag_debug) /SUBSYSTEM:CONSOLE /map Ws2_32.lib Iphlpapi.lib /incremental:no
linkoutput = /out:
dllprefix =
dllext = dll
link_dll = link /nologo $(link_flag_debug) /map Ws2_32.lib Iphlpapi.lib /dll
link_dll_service = link /nologo $(link_flag_debug)  /map $(objdir)ohNet.lib Ws2_32.lib Iphlpapi.lib /dll
csplatform = x86
csharp = csc /nologo /platform:$(csplatform)
publiccsdir = Public\Cs^\
dirsep = ^\
installdir = $(PROGRAMFILES)\ohNet
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

all: $(objdir)/$(dllprefix)ohSoundcard.$(dllext) $(objdir)/Install32.$(exeext) $(objdir)/TestSoundcard.$(exeext) $(objdir)/TestSoundcardCs.$(exeext) $(objdir)/TestReceiverManager1.$(exeext) $(objdir)/TestReceiverManager2.$(exeext) $(objdir)/TestReceiverManager3.$(exeext) $(objdir)/TestReceiverManager3.$(exeext) $(objdir)/WavSender.$(exeext) $(objdir)/ZoneWatcher.$(exeext)

$(objdir)/$(dllprefix)ohSoundcard.$(dllext) : Services/DvAvOpenhomeOrgSender1.cpp Ohm.cpp OhmSender.cpp ohSoundcard/Windows/Soundcard.cpp
    if not exist $(objdirbare) mkdir $(objdirbare)
	$(compiler)/Ohm.$(objext) -c $(cflags) $(includes) Ohm.cpp
	$(compiler)/OhmSender.$(objext) -c $(cflags) $(includes) OhmSender.cpp
	$(compiler)/ReceiverManager1.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager1.cpp 
	$(compiler)/ReceiverManager2.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager2.cpp 
	$(compiler)/ReceiverManager3.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager3.cpp 
	$(compiler)/Soundcard.$(objext) -c $(cflags) $(includes) ohSoundcard/Windows/Soundcard.cpp
	$(link_dll) $(linkoutput)$(objdir)/$(dllprefix)ohSoundcard.$(dllext) $(ohnetdir)/$(libprefix)ohNetCore.lib $(objects_topology) $(ohnetdir)/DvAvOpenhomeOrgSender1.$(objext) $(ohnetdir)/CpAvOpenhomeOrgReceiver1.$(objext) $(objdir)/Ohm.$(objext) $(objdir)/OhmSender.$(objext) $(objdir)/ReceiverManager1.$(objext) $(objdir)/ReceiverManager2.$(objext) $(objdir)/ReceiverManager3.$(objext) $(objdir)/Soundcard.$(objext) kernel32.lib setupapi.lib shell32.lib

$(objdir)/$(dllprefix)ohSoundcard.net.$(dllext) : $(objdir)/$(dllprefix)ohSoundcard.$(dllext) ohSoundcard\Windows\Soundcard.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)/$(dllprefix)ohSoundcard.net.$(dllext) \
		ohSoundcard\Windows\Soundcard.cs

$(objdir)/Install32.$(exeext) : ohSoundcard/Windows/Install.cpp
	$(compiler)/Install32.$(objext) -c $(cflags) $(includes) ohSoundcard/Windows/Install.cpp
	$(link) $(linkoutput)$(objdir)/Install32.$(exeext) $(objdir)/Install32.$(objext) setupapi.lib

$(objdir)/Install64.$(exeext) : ohSoundcard/Windows/Install.cpp
	$(compiler)/Install64.$(objext) -c $(cflags) $(includes) ohSoundcard/Windows/Install.cpp
	$(link) $(linkoutput)$(objdir)/Install64.$(exeext) $(objdir)/Install64.$(objext) setupapi.lib

$(objdir)/TestSoundcardCs.$(exeext) : $(objdir)/$(dllprefix)ohSoundcard.net.$(dllext) ohSoundcard/Windows/TestSoundcardCs.cs
	$(csharp) /target:exe /debug+ \
		/out:$(objdir)TestSoundcardCs.exe \
		/reference:System.dll \
		/reference:System.Net.dll \
		/reference:$(objdir)/$(dllprefix)ohSoundcard.net.$(dllext)  \
		ohSoundcard\Windows\TestSoundcardCs.cs

$(objdir)/ohSoundcard.$(exeext) : $(objdir)/$(dllprefix)ohSoundcard.net.$(dllext) ohSoundcard/Windows/Wpf/ohSoundcard/ReceiverList.cs ohSoundcard/Windows/Wpf/ohSoundcard/ExtendedNotifyIcon.cs ohSoundcard/Windows/Wpf/ohSoundcard/App.xaml.cs ohSoundcard/Windows/Wpf/ohSoundcard/MainWindow.xaml.cs
	$(csharp) /target:exe /debug+ \
		/out:$(objdir)ohSoundcard.exe \
		/reference:WindowsBase.dll \
		/reference:PresentationCore.dll \
		/reference:PresentationFramework.dll \
		/reference:System.dll \
		/reference:System.Net.dll \
		/reference:System.Core.dll \
		/reference:System.Drawing.dll \
		/reference:System.Windows.Forms.dll \
		/reference:System.Xaml.dll \
		/reference:$(objdir)/$(dllprefix)ohSoundcard.net.$(dllext)  \
		ohSoundcard/Windows/Wpf/ohSoundcard/ReceiverList.cs \
		ohSoundcard/Windows/Wpf/ohSoundcard/ExtendedNotifyIcon.cs \
		ohSoundcard/Windows/Wpf/ohSoundcard/App.xaml.cs \
		ohSoundcard/Windows/Wpf/ohSoundcard/MainWindow.xaml.cs \

$(objdir)/TestReceiverManager1.$(exeext) : ohSoundcard/ReceiverManager1.cpp ohSoundcard/TestReceiverManager1.cpp 
	$(compiler)/ReceiverManager1.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager1.cpp 
    $(compiler)/TestReceiverManager1.$(objext) -c $(cflags) $(includes) ohSoundcard/TestReceiverManager1.cpp 
    $(link) $(linkoutput)$(objdir)/TestReceiverManager1.$(exeext) $(objdir)/ReceiverManager1.$(objext) $(objdir)/TestReceiverManager1.$(objext) $(objects_topology) $(ohnetdir)/$(libprefix)ohNetCore.lib $(ohnetdir)/$(libprefix)TestFramework.$(libext)  
 	
$(objdir)/TestReceiverManager2.$(exeext) : ohSoundcard/ReceiverManager2.cpp ohSoundcard/TestReceiverManager1.cpp ohSoundcard/TestReceiverManager2.cpp
	$(compiler)/ReceiverManager1.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager1.cpp 
	$(compiler)/ReceiverManager2.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager2.cpp 
    $(compiler)/TestReceiverManager2.$(objext) -c $(cflags) $(includes) ohSoundcard/TestReceiverManager2.cpp 
    $(link) $(linkoutput)$(objdir)/TestReceiverManager2.$(exeext) $(objdir)/ReceiverManager2.$(objext) $(objdir)/ReceiverManager1.$(objext) $(objdir)/TestReceiverManager2.$(objext) $(objects_topology) $(ohnetdir)/$(libprefix)ohNetCore.lib $(ohnetdir)/CpAvOpenhomeOrgReceiver1.$(objext) $(ohnetdir)/$(libprefix)TestFramework.$(libext)  
 	
$(objdir)/TestReceiverManager3.$(exeext) : ohSoundcard/ReceiverManager3.cpp ohSoundcard/TestReceiverManager1.cpp ohSoundcard/TestReceiverManager2.cpp ohSoundcard/TestReceiverManager3.cpp
	$(compiler)/ReceiverManager1.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager1.cpp 
	$(compiler)/ReceiverManager2.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager2.cpp 
	$(compiler)/ReceiverManager3.$(objext) -c $(cflags) $(includes) ohSoundcard/ReceiverManager3.cpp 
    $(compiler)/TestReceiverManager3.$(objext) -c $(cflags) $(includes) ohSoundcard/TestReceiverManager3.cpp 
    $(link) $(linkoutput)$(objdir)/TestReceiverManager3.$(exeext) $(objdir)/ReceiverManager3.$(objext) $(objdir)/ReceiverManager2.$(objext) $(objdir)/ReceiverManager1.$(objext) $(objdir)/TestReceiverManager3.$(objext) $(objects_topology) $(ohnetdir)/$(libprefix)ohNetCore.lib $(ohnetdir)/CpAvOpenhomeOrgReceiver1.$(objext) $(ohnetdir)/$(libprefix)TestFramework.$(libext)  
 	
$(objdir)/TestSoundcard.$(exeext) : $(objdir)/$(dllprefix)ohSoundcard.$(dllext) ohSoundcard/Windows/TestSoundcard.cpp
	$(compiler)/TestSoundcard.$(objext) -c $(cflags) $(includes) ohSoundcard/Windows/TestSoundcard.cpp
	$(link) $(linkoutput)$(objdir)/TestSoundcard.$(exeext) $(objdir)/ohSoundcard.$(libext) $(objdir)/TestSoundcard.$(objext) 

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

