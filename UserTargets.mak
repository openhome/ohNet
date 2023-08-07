# Targets specifically intended for the user to invoke on the command-line.
#
# (Note that some of these depend on variables defined in the generated
# makefiles, and so cannot be defined in Common.mak.)

all : $(build_targets) bundle-after-build

clean :
	$(rmdir) $(objdir)
	$(rmdir) $(inc_build)
	$(rmdir) $(bundle_build)
	$(rmdir) Build/Docs
	$(rmdir) $(mDNSdir)

	$(rmdir) "OpenHome/Net/Bindings/Cs/bin"
	$(rmdir) "OpenHome/Net/Bindings/Cs/obj"

	$(rmdir) "OpenHome/Net/Bindings/Cs/ControlPoint/Proxies/bin"
	$(rmdir) "OpenHome/Net/Bindings/Cs/ControlPoint/Proxies/obj"

	$(rmdir) "OpenHome/Net/Bindings/Cs/ControlPoint/Tests/bin"
	$(rmdir) "OpenHome/Net/Bindings/Cs/ControlPoint/Tests/obj"

	$(rmdir) "OpenHome/Net/Bindings/Cs/Device/Providers/bin"
	$(rmdir) "OpenHome/Net/Bindings/Cs/Device/Providers/obj"

	$(rmdir) "OpenHome/Net/Bindings/Cs/Device/Tests/bin"
	$(rmdir) "OpenHome/Net/Bindings/Cs/Device/Tests/obj"

mostlyclean : clean clean-t4
	$(rmdir) Generated

maintainer-clean : mostlyclean

generate-makefiles : Generated$(dirsep)GenerateSourceFiles.mak Generated$(dirsep)Proxies.mak Generated$(dirsep)Devices.mak
