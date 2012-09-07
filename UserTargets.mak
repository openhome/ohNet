# Targets specifically intended for the user to invoke on the command-line.
#
# (Note that some of these depend on variables defined in the generated
# makefiles, and so cannot be defined in Common.mak.)

all : $(build_targets)

clean :
	$(rmdir) $(objdir)
	$(rmdir) $(inc_build)
	$(rmdir) $(bundle_build)
	$(rmdir) Build/Docs


mostlyclean : clean
	$(rmdir) Generated

maintainer-clean : mostlyclean
	$(rmdir) Build/Docs
	$(rmdir) Build

generate-makefiles : Generated$(dirsep)GenerateSourceFiles.mak Generated$(dirsep)Proxies.mak Generated$(dirsep)Devices.mak
