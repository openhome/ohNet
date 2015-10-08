# Makefile for Windows
#

openhome_system=Windows

!if [cl 2>&1 | find "for x64" > nul] == 0
!message Detected 64-bit compiler.
openhome_architecture=x64
!elseif [cl 2>&1 | find "for 80x86" > nul] == 0
!message Detected 32-bit compiler.
openhome_architecture=x86
!elseif [cl 2>&1 | find "for x86" > nul] == 0
!message Detected 32-bit compiler.
openhome_architecture=x86
!else
!message Cannot tell if compiler is 32-bit or 64-bit. Please specify openhome_architecture=x64 or openhome_architecture=x86.
!endif

!if "$(debug)"=="1"
link_flag_debug = /debug
link_flag_debug_dll = $(link_flag_debug)
debug_specific_cflags = /MTd /Z7 /Od /RTC1
debug_csharp = /define:DEBUG /debug+
build_dir = Debug
openhome_configuration = Debug
android_ndk_debug = 1
!else
link_flag_debug =
link_flag_debug_dll = /debug /opt:ref
debug_specific_cflags = /MT /Ox
debug_csharp = /optimize+ /debug:pdbonly
build_dir = Release
openhome_configuration = Release
android_ndk_debug = 0
!endif

!message Building for system $(openhome_system), architecture $(openhome_architecture), configuration $(openhome_configuration)

# Macros used by Common.mak
ar = lib /nologo /out:$(objdir)
cflags_third_party = $(debug_specific_cflags) /W4 /EHa /FR$(objdir) -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -D_CRT_SECURE_NO_WARNINGS
cflags = $(cflags_third_party) /WX
cppflags = $(cflags)
objdirbare = Build\Obj\Windows\$(build_dir)
objdir = $(objdirbare)^\
inc_build = Build\Include
includes = -IBuild\Include
bundle_build = Build\Bundles
osdir = Windows
objext = obj
libprefix =
libext = lib
sharedlibprefix = 
sharedlibext = lib
exeext = exe
compiler = cl /nologo /Fo$(objdir)
link = link /nologo $(link_flag_debug) /SUBSYSTEM:CONSOLE /map Ws2_32.lib Iphlpapi.lib Dbghelp.lib /incremental:no
linkoutput = /out:
dllprefix =
dllext = dll
linkopts_ohNet =
link_dll = link /nologo $(link_flag_debug_dll) /map Ws2_32.lib Iphlpapi.lib Dbghelp.lib /dll
csharp = csc /nologo /platform:anycpu
csharpdefines = 
publicjavadir = OpenHome\Net\Bindings\Java^\
includes_jni = -I"$(JAVA_HOME)\include" -I"$(JAVA_HOME)\include\win32"
link_jvm = "$(JAVA_HOME)\lib\jvm.lib"
java_cflags = $(cflags)
javac =  "$(JAVA_HOME)\bin\javac.exe"
jar =  "$(JAVA_HOME)\bin\jar.exe"
jarflags = cf
android_build_dir = OpenHome/Net/Bindings/Android/libs/
dirsep = ^\
installdir = $(PROGRAMFILES)\ohNet
installlibdir = $(installdir)\lib
installincludedir = $(installdir)\include
mkdir = Scripts\mkdir.bat
rmdir = Scripts\rmdir.bat
uset4 = no

default : all

include T4Windows.mak
# Actual building of code is shared between platforms
include Common.mak

!if "$(uset4)"=="yes"
build_targets = $(all_targets) tt
!else
build_targets = $(all_targets)
!endif

!if "$(uset4)"=="yes"
!if exist (Generated\GenerateSourceFiles.mak)
!include Generated\GenerateSourceFiles.mak
!else
!message Note: Generated\GenerateSourceFiles.mak does not yet exist. Try "make generate-makefiles".
!endif
!endif

!if exist (Generated\Proxies.mak)
!include Generated\Proxies.mak
!else
!message Note: Generated\Proxies.mak does not yet exist. Try "make generate-makefiles".
!endif

!if exist (Generated\Devices.mak)
!include Generated\Devices.mak
!else
!message Note: Generated\Devices.mak does not yet exist. Try "make generate-makefiles".
!endif

include UserTargets.mak

# Following macros must be provided by each file which wraps Common.mak

make_obj_dir:
	if not exist $(objdirbare) mkdir $(objdirbare)

copy_build_includes:
	if not exist $(inc_build) mkdir $(inc_build)
	if not exist $(inc_build)\OpenHome mkdir $(inc_build)\OpenHome
	if not exist $(inc_build)\OpenHome\Private mkdir $(inc_build)\OpenHome\Private
	if not exist $(inc_build)\OpenHome\Net mkdir $(inc_build)\OpenHome\Net
	if not exist $(inc_build)\OpenHome\Net\Private mkdir $(inc_build)\OpenHome\Net\Private
	if not exist $(inc_build)\OpenHome\Net\Core mkdir $(inc_build)\OpenHome\Net\Core
	if not exist $(inc_build)\OpenHome\Net\C mkdir $(inc_build)\OpenHome\Net\C
	if not exist $(inc_build)\OpenHome\Net\Cpp mkdir $(inc_build)\OpenHome\Net\Cpp
	if not exist $(inc_build)\OpenHome\Net\Private\Js mkdir $(inc_build)\OpenHome\Net\Private\Js
	if not exist $(inc_build)\OpenHome\Net\Private\Js\Tests mkdir $(inc_build)\OpenHome\Net\Private\Js\Tests
	if not exist $(inc_build)\OpenHome\Net\Private\Js\Tests\lib mkdir $(inc_build)\OpenHome\Net\Private\Js\Tests\lib
	if not exist $(inc_build)\OpenHome\Net\Private\Js\Tests\proxies mkdir $(inc_build)\OpenHome\Net\Private\Js\Tests\proxies
	copy OpenHome\*.h $(inc_build)\OpenHome\Private > nul
	copy OpenHome\Buffer.inl $(inc_build)\OpenHome > nul
	move $(inc_build)\OpenHome\Private\Buffer.h $(inc_build)\OpenHome > nul
	move $(inc_build)\OpenHome\Private\Exception.h $(inc_build)\OpenHome > nul
	move $(inc_build)\OpenHome\Private\Functor*.h $(inc_build)\OpenHome > nul
	move $(inc_build)\OpenHome\Private\MimeTypes.h $(inc_build)\OpenHome > nul
	move $(inc_build)\OpenHome\Private\OhNetDefines.h $(inc_build)\OpenHome > nul
	move $(inc_build)\OpenHome\Private\Defines.h $(inc_build)\OpenHome > nul
	move $(inc_build)\OpenHome\Private\OsTypes.h $(inc_build)\OpenHome > nul
	move $(inc_build)\OpenHome\Private\OhNetTypes.h $(inc_build)\OpenHome > nul
	move $(inc_build)\OpenHome\Private\Types.h $(inc_build)\OpenHome > nul
	copy OpenHome\TestFramework\*.h $(inc_build)\OpenHome\Private > nul
	copy OpenHome\Net\*.h $(inc_build)\OpenHome\Net\Private > nul
	move $(inc_build)\OpenHome\Net\Private\FunctorAsync.h $(inc_build)\OpenHome\Net\Core > nul
	copy $(inc_build)\OpenHome\Net\Core\FunctorAsync.h $(inc_build)\OpenHome\Net\Cpp > nul
	move $(inc_build)\OpenHome\Net\Private\OhNet.h $(inc_build)\OpenHome\Net\Core > nul
	copy $(inc_build)\OpenHome\Net\Core\OhNet.h $(inc_build)\OpenHome\Net\Cpp > nul
	copy OpenHome\Net\Shell\*.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\ControlPoint\AsyncPrivate.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\ControlPoint\CpStack.h $(inc_build)\OpenHome\Net\Core > nul
	copy OpenHome\Net\ControlPoint\CpDevice.h $(inc_build)\OpenHome\Net\Core > nul
	copy OpenHome\Net\ControlPoint\CpDeviceDv.h $(inc_build)\OpenHome\Net\Core > nul
	copy OpenHome\Net\ControlPoint\CpDeviceUpnp.h $(inc_build)\OpenHome\Net\Core > nul
	copy OpenHome\Net\ControlPoint\CpProxy.h $(inc_build)\OpenHome\Net\Core > nul
	copy OpenHome\Net\ControlPoint\CpProxy.h $(inc_build)\OpenHome\Net\Cpp > nul
	copy OpenHome\Net\ControlPoint\FunctorCpDevice.h $(inc_build)\OpenHome\Net\Core > nul
	copy OpenHome\Net\ControlPoint\Cpi*.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\ControlPoint\FunctorCpiDevice.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\ControlPoint\Dv\CpiDeviceDv.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\ControlPoint\Lpec\CpiDeviceLpec.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\ControlPoint\Proxies\*.h $(inc_build)\OpenHome\Net\Core > nul
	copy OpenHome\Net\ControlPoint\Upnp\*.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\Device\DvStack.h $(inc_build)\OpenHome\Net\Core > nul
	copy OpenHome\Net\Device\DvDevice.h $(inc_build)\OpenHome\Net\Core > nul
	copy OpenHome\Net\Device\DvInvocationResponse.h $(inc_build)\OpenHome\Net\Core > nul
	copy OpenHome\Net\Device\DvProvider.h $(inc_build)\OpenHome\Net\Core > nul
	copy OpenHome\Net\Device\DvProvider.h $(inc_build)\OpenHome\Net\Cpp > nul
	copy OpenHome\Net\Device\DvResourceWriter.h $(inc_build)\OpenHome\Net\Core > nul
	copy OpenHome\Net\Device\DvResourceWriter.h $(inc_build)\OpenHome\Net\Cpp > nul
	copy OpenHome\Net\Device\DvServerUpnp.h $(inc_build)\OpenHome\Net\Core > nul
	copy OpenHome\Net\Device\DvServerUpnp.h $(inc_build)\OpenHome\Net\Cpp > nul
	copy OpenHome\Net\Device\DviDevice.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\Device\DviServer.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\Device\DviService.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\Device\DviStack.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\Device\DviSubscription.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\Device\DviPropertyUpdateCollection.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\Device\DviProviderSubscriptionLongPoll.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\Device\FunctorDviInvocation.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\Device\Bonjour\*.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\Device\Bonjour\mDNSCore\*.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\Device\Providers\*.h $(inc_build)\OpenHome\Net\Core > nul
	copy OpenHome\Net\Device\Upnp\*.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\Device\Lpec\*.h $(inc_build)\OpenHome\Net\Private > nul
	copy OpenHome\Net\Bindings\C\*.h $(inc_build)\OpenHome\Net\C > nul
	copy OpenHome\Net\Bindings\C\ControlPoint\*.h $(inc_build)\OpenHome\Net\C > nul
	copy OpenHome\Net\Bindings\C\ControlPoint\Proxies\*.h $(inc_build)\OpenHome\Net\C > nul
	copy OpenHome\Net\Bindings\C\Device\*.h $(inc_build)\OpenHome\Net\C > nul
	copy OpenHome\Net\Bindings\C\Device\Providers\*.h $(inc_build)\OpenHome\Net\C > nul
	copy OpenHome\Net\Bindings\Cpp\ControlPoint\*.h $(inc_build)\OpenHome\Net\Cpp > nul
	copy OpenHome\Net\Bindings\Cpp\ControlPoint\Proxies\*.h $(inc_build)\OpenHome\Net\Cpp > nul
	copy OpenHome\Net\Bindings\Cpp\Device\*.h $(inc_build)\OpenHome\Net\Cpp > nul
	copy OpenHome\Net\Bindings\Cpp\Device\Providers\*.h $(inc_build)\OpenHome\Net\Cpp > nul
	xcopy OpenHome\Net\Bindings\Js\ControlPoint\Tests\*.*/s $(inc_build)\OpenHome\Net\Private\Js\Tests /y > nul
	copy OpenHome\Net\Bindings\Js\ControlPoint\lib\*.js $(inc_build)\OpenHome\Net\Private\Js\Tests\lib > nul
	copy OpenHome\Net\Bindings\Js\ControlPoint\Proxies\CpOpenhomeOrgTestBasic1.js $(inc_build)\OpenHome\Net\Private\Js\Tests\proxies > nul
	copy OpenHome\Net\Bindings\Js\ControlPoint\Proxies\CpOpenhomeOrgSubscriptionLongPoll1.js $(inc_build)\OpenHome\Net\Private\Js\Tests\proxies > nul
	copy Os\*.h $(inc_build)\OpenHome > nul
	copy Os\*.inl $(inc_build)\OpenHome > nul

install :
	if not exist "$(installdir)" mkdir "$(installdir)"
	if not exist "$(installlibdir)" mkdir "$(installlibdir)"
	if not exist "$(installincludedir)" mkdir "$(installincludedir)"
	copy "$(objdir)*" "$(installlibdir)" > nul
	xcopy "$(inc_build)" "$(installincludedir)" /Y /S /I > nul

uninstall :
	if not exist "$(installdir)" echo Nothing to uninstall && exit /b 1
	if exist "$(installlibdir)" del /q "$(installlibdir)\*" > nul
	if exist "$(installlibdir)" rmdir "$(installlibdir)"
	if exist "$(installincludedir)" rmdir /s /q "$(installincludedir)"
	rmdir "$(installdir)"

bundle-after-build: $(all_targets)
	if not exist "$(bundle_build)" mkdir "$(bundle_build)"
	python bundle_binaries.py --system $(openhome_system) --architecture $(openhome_architecture) --configuration $(openhome_configuration)
	python bundle_binaries.py --system $(openhome_system) --architecture $(openhome_architecture) --configuration $(openhome_configuration) --managed

bundle:
	if not exist "$(bundle_build)" mkdir "$(bundle_build)"
	python bundle_binaries.py --system $(openhome_system) --architecture $(openhome_architecture) --configuration $(openhome_configuration)
	python bundle_binaries.py --system $(openhome_system) --architecture $(openhome_architecture) --configuration $(openhome_configuration) --managed

ohNet.net.dll :  $(objdir)ohNet.net.dll ohNetDll
ohNetDll : ohNetDllImpl
