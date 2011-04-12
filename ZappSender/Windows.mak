objdir = Build/Obj/Windows
incdir = Build/Include
zappdir = ../Upnp/Build/Obj/Windows
toolsDir = ../Upnp/Build/Windows/Tools
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
link_dll_service = link /nologo /debug  /map $(objdir)ZappUpnp.lib Ws2_32.lib Iphlpapi.lib /dll
csharp = csc /nologo /platform:x86
publiccsdir = Public\Cs^\
dirsep = ^\
installdir = $(PROGRAMFILES)\Zapp
installlibdir = $(installdir)\lib
installincludedir = $(installdir)\include
mkdir = Scripts\mkdir.bat
rmdir = Scripts\rmdir.bat
uset4 = no


all: $(objdir)/WavSender.exe 

$(objdir)/WavSender.exe :
    if not exist $(objdirbare) mkdir $(objdirbare)
	$(compiler)/DvAvOpenhomeOrgSender1.$(objext) -c $(cflags) $(includes) DvAvOpenhomeOrgSender1.cpp
	$(compiler)/Ohm.$(objext) -c $(cflags) $(includes) Ohm.cpp
	$(compiler)/OhmSender.$(objext) -c $(cflags) $(includes) OhmSender.cpp
	$(compiler)/WavSender.$(objext) -c $(cflags) $(includes) WavSender.cpp
	$(link) $(linkoutput)$(objdir)/WavSender.$(exeext) $(objdir)/WavSender.$(objext) $(objdir)/DvAvOpenhomeOrgSender1.$(objext) $(objdir)/Ohm.$(objext) $(objdir)/OhmSender.$(objext) $(zappdir)/$(libprefix)upnp_core.$(libext) $(zappdir)/TestFramework.$(libext)

$(objdir)/Receiver.exe :
    if not exist $(objdirbare) mkdir $(objdirbare)
	$(compiler)/DvAvOpenhomeOrgProduct1.$(objext) -c $(cflags) $(includes) DvAvOpenhomeOrgProduct1.cpp
	$(compiler)/DvAvOpenhomeOrgReceiver1.$(objext) -c $(cflags) $(includes) DvAvOpenhomeOrgReceiver1.cpp
	$(compiler)/Product.$(objext) -c $(cflags) $(includes) Product.cpp
	$(compiler)/Receiver.$(objext) -c $(cflags) $(includes) Receiver.cpp
	$(link) $(linkoutput)$(objdir)/Receiver.$(exeext) $(objdir)/Receiver.$(objext) $(objdir)/Product.$(objext) $(objdir)/DvAvOpenhomeOrgProduct1.$(objext) $(objdir)/DvAvOpenhomeOrgReceiver1.$(objext) $(zappdir)/$(libprefix)upnp_core.$(libext) $(zappdir)/TestFramework.$(libext)

t4 = $(toolsDir)/TextTransform.exe

gen: DvAvOpenhomeOrgSender1.h DvAvOpenhomeOrgSender1.cpp DvAvOpenhomeOrgProduct1.h DvAvOpenhomeOrgProduct1.cpp DvAvOpenhomeOrgReceiver1.h DvAvOpenhomeOrgReceiver1.cpp

DvAvOpenhomeOrgSender1.h : $(templatesDir)/DvUpnpCppCoreHeader.tt Sender1.xml
	$(t4) -o DvAvOpenhomeOrgSender1.h $(templatesDir)/DvUpnpCppCoreHeader.tt -a "xml:Sender1.xml" -a domain:av.openhome.org -a type:Sender -a version:1
DvAvOpenhomeOrgSender1.cpp : ../Upnp/T4/Templates/DvUpnpCppCoreSource.tt Sender1.xml
	$(t4) -o DvAvOpenhomeOrgSender1.cpp $(templatesDir)/DvUpnpCppCoreSource.tt -a "xml:Sender1.xml" -a domain:av.openhome.org -a type:Sender -a version:1

DvAvOpenhomeOrgProduct1.h : $(templatesDir)/DvUpnpCppCoreHeader.tt Product1.xml
	$(t4) -o DvAvOpenhomeOrgProduct1.h $(templatesDir)/DvUpnpCppCoreHeader.tt -a "xml:Product1.xml" -a domain:av.openhome.org -a type:Product -a version:1
DvAvOpenhomeOrgProduct1.cpp : ../Upnp/T4/Templates/DvUpnpCppCoreSource.tt Product1.xml
	$(t4) -o DvAvOpenhomeOrgProduct1.cpp $(templatesDir)/DvUpnpCppCoreSource.tt -a "xml:Product1.xml" -a domain:av.openhome.org -a type:Product -a version:1

DvAvOpenhomeOrgReceiver1.h : $(templatesDir)/DvUpnpCppCoreHeader.tt Receiver1.xml
	$(t4) -o DvAvOpenhomeOrgReceiver1.h $(templatesDir)/DvUpnpCppCoreHeader.tt -a "xml:Receiver1.xml" -a domain:av.openhome.org -a type:Receiver -a version:1
DvAvOpenhomeOrgReceiver1.cpp : ../Upnp/T4/Templates/DvUpnpCppCoreSource.tt Receiver1.xml
	$(t4) -o DvAvOpenhomeOrgReceiver1.cpp $(templatesDir)/DvUpnpCppCoreSource.tt -a "xml:Receiver1.xml" -a domain:av.openhome.org -a type:Receiver -a version:1
