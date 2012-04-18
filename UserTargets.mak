# Targets specifically intended for the user to invoke on the command-line.
#
# (Note that some of these depend on variables defined in the generated
# makefiles, and so cannot be defined in Common.mak.)

ifeq ($(native_only), 1)
all : TestsNative proxies devices
else
all : Tests proxies CpProxyDotNetAssemblies devices DvDeviceDotNetAssemblies
endif

clean :
	$(rmdir) $(objdir)
	$(rmdir) $(inc_build)
	$(rmdir) Build/Bundles

mostlyclean : clean clean-t4
	$(rmdir) Generated

maintainer-clean : mostlyclean

generate-makefiles : Generated$(dirsep)GenerateSourceFiles.mak Generated$(dirsep)Proxies.mak Generated$(dirsep)Devices.mak
