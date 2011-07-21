# Makefile for Windows
#

!if "$(csplatform)"=="x64"
csplatform = x64
!else
csplatform = x86
!endif

!if "$(release)"=="1"
link_flag_debug = 
debug_specific_cflags = /MT /Ox
build_dir = Release
!else
link_flag_debug = /debug
debug_specific_cflags = /MTd /Zi /Od /RTC1
build_dir = Debug
!endif

# Macros used by Common.mak
ar = lib /nologo /out:$(objdir)
cflags = $(debug_specific_cflags) /W4 /WX /EHsc /FR$(objdir) -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -D_CRT_SECURE_NO_WARNINGS
objdirbare = Build\Obj\Windows\$(build_dir)
objdir = $(objdirbare)^\
inc_build = Build\Include
includes = -IBuild\Include -IBuild\Include\Cpp
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
csharp = csc /nologo /platform:$(csplatform)
publiccsdir = Public\Cs^\
publicjavadir = Public\Java^\
includes_jni = -I"C:\Program Files (x86)\Java\jdk1.6.0_26\include" -I"C:\Program Files (x86)\Java\jdk1.6.0_26\include\win32"
link_jvm = "C:\Program Files (x86)\Java\jdk1.6.0_26\lib\jvm.lib"
proxyjavadir = $(objdir)openhome\net\controlpoint\proxies^\
javac =  "C:\Program Files (x86)\Java\jdk1.6.0_26\bin\javac.exe"
jar =  "C:\Program Files (x86)\Java\jdk1.6.0_26\bin\jar.exe"
jarflags = cf
javadoc = "C:\Program Files (x86)\Java\jdk1.6.0_26\bin\javadoc.exe"
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
	if not exist $(inc_build)\C mkdir $(inc_build)\C
	if not exist $(inc_build)\Cpp mkdir $(inc_build)\Cpp
	if not exist $(inc_build)\Cpp\Core mkdir $(inc_build)\Cpp\Core
	if not exist $(inc_build)\Cpp\Std mkdir $(inc_build)\Cpp\Std
    if not exist $(inc_build)\Js mkdir $(inc_build)\Js
    if not exist $(inc_build)\Js\Tests mkdir $(inc_build)\Js\Tests
    if not exist $(inc_build)\Js\Tests\css mkdir $(inc_build)\Js\Tests\css
    if not exist $(inc_build)\Js\Tests\Scripts mkdir $(inc_build)\Js\Tests\Scripts
    if not exist $(inc_build)\Js\Tests\extern mkdir $(inc_build)\Js\Tests\extern
    if not exist $(inc_build)\Js\Tests\proxy mkdir $(inc_build)\Js\Tests\proxy
    if not exist $(inc_build)\Js\Tests\test mkdir $(inc_build)\Js\Tests\test
    if not exist $(inc_build)\Js\Tests\test\assets mkdir $(inc_build)\Js\Tests\test\assets
    if not exist $(inc_build)\Js\Tests\test\assets\skins mkdir $(inc_build)\Js\Tests\test\assets\skins
    if not exist $(inc_build)\Js\Tests\test\assets\skins\sam mkdir $(inc_build)\Js\Tests\test\assets\skins\sam
	copy Api\*.h $(inc_build) > nul
	copy Api\C\*.h $(inc_build)\C > nul
	copy Api\Cpp\*.h $(inc_build)\Cpp > nul
	copy Api\Cpp\*.inl $(inc_build)\Cpp > nul
	copy Api\Cpp\Core\*.h $(inc_build)\Cpp\Core > nul
	copy Api\Cpp\Std\*.h $(inc_build)\Cpp\Std > nul
	copy *.h $(inc_build) > nul
	copy Bonjour\*.h $(inc_build) > nul
	copy Bonjour\mDNSCore\*.h $(inc_build) > nul
	copy ControlPoint\*.h $(inc_build) > nul
	copy ControlPoint\Services\Cpp\Core\*.h $(inc_build)\Cpp\Core > nul
	copy ControlPoint\Services\Cpp\Std\*.h $(inc_build)\Cpp\Std > nul
	copy ControlPoint\Services\C\*.h $(inc_build)\C > nul
	copy ControlPoint\Dv\*.h $(inc_build) > nul
	copy ControlPoint\Upnp\*.h $(inc_build) > nul
	copy Device\*.h $(inc_build) > nul
	copy Device\Services\Cpp\Core\*.h $(inc_build)\Cpp\Core > nul
	copy Device\Services\Cpp\Std\*.h $(inc_build)\Cpp\Std > nul
	copy Device\Services\C\*.h $(inc_build)\C > nul
	copy Device\Upnp\*.h $(inc_build) > nul
	copy Network\*.h $(inc_build) > nul
	copy Service\*.h $(inc_build) > nul
	copy Ssdp\*.h $(inc_build) > nul
	copy Os\*.h $(inc_build) > nul
	copy Os\*.inl $(inc_build) > nul
	copy Public\C\*.h $(inc_build)\C > nul
	copy Public\Cpp\Std\*.h $(inc_build)\Cpp\Std > nul
	copy Thread\Thread.h $(inc_build) > nul
	copy Utils\*.h $(inc_build) > nul
	copy TestFramework\*.h $(inc_build) > nul
    copy Public\Js\OhNet.Web.UI.Tests\*.html $(inc_build)\Js\Tests > nul
    copy Public\Js\OhNet.Web.UI.Tests\favicon.ico $(inc_build)\Js\Tests > nul
    copy Public\Js\OhNet.Web.UI.Tests\css\*.css $(inc_build)\Js\Tests\css > nul
    copy Public\Js\OhNet.Web.UI.Tests\Scripts\*.js $(inc_build)\Js\Tests\Scripts > nul
    copy Public\Js\OhNet.Web.UI.Tests\test\assets\skins\sam\*.css $(inc_build)\Js\Tests\test\assets\skins\sam > nul
    copy Public\Js\WebUIsdk\*.js $(inc_build)\Js\Tests\extern > nul
    copy ControlPoint\Services\Js\CpOpenhomeOrgTestBasic1.js $(inc_build)\Js\Tests\proxy > nul
    
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

bundle: tt
	if not exist "$(bundle_build)" mkdir "$(bundle_build)"
	if "$(targetplatform)"=="" echo "Usage: make bundle targetplatform=Windows-x86" && exit /b 1
	python bundle_binaries.py Windows $(targetplatform)

bundle-dev: tt
	if not exist "$(bundle_build)" mkdir "$(bundle_build)"
	if "$(targetplatform)"=="" echo "Usage: make bundle-dev targetplatform=Windows-x86" && exit /b 1
	python bundle_binaries.py --dev Windows $(targetplatform)
