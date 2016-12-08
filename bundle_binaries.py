import sys
import tarfile
import optparse
from os import path
import os
from collections import namedtuple

def exclude_non_binary(filename):
    if filename.lower().startswith("test") and not filename.lower().startswith("testframework"):
        return True
    executable_extensions = [".dll", ".so", ".elf", ".lib", ".map", ".pdb", ".dylib", ".a", ".jar"]
    has_executable_extension = any(filename.endswith(ex) for ex in executable_extensions)
    has_no_extension = "." not in filename
    is_binary = has_executable_extension or has_no_extension
    return not is_binary

def exclude_non_managed(filename):
    managed_extensions = [".net.dll", ".net.pdb", ".net.dll.mdb", ".jar"]
    has_managed_extension = any(filename.endswith(ex) for ex in managed_extensions)
    return not has_managed_extension

# Prior to Python 2.6, tarfile's add method doesn't have any filtering
# mechanism, so we have to replicate that functionality.
def recursively_add_directory(tarfile, directory_path, path_in_archive, exclude=None):
    for sub_path, dirs, files in os.walk(directory_path):
        assert sub_path[:len(directory_path)]==directory_path
        relative_dir = sub_path[len(directory_path):]
        if len(relative_dir)>0 and relative_dir[0] in [os.path.sep, os.path.altsep]:
            relative_dir = relative_dir[1:]
        for fname in files:
            if exclude is None or not exclude(fname):
                tarfile.add(path.join(sub_path, fname), path.join(path_in_archive, relative_dir, fname))

BuildTarget = namedtuple("BuildTarget", "system architecture configuration")
BuildInfo = namedtuple("BuildInfo", "builddir")
ALL_TARGETS = {
        BuildTarget("Windows", "x86",   "Debug"):   BuildInfo(builddir="Build/Obj/Windows/Debug"),
        BuildTarget("Windows", "x64",   "Debug"):   BuildInfo(builddir="Build/Obj/Windows/Debug"),
        BuildTarget("Windows", "x86",   "Release"): BuildInfo(builddir="Build/Obj/Windows/Release"),
        BuildTarget("Windows", "x64",   "Release"): BuildInfo(builddir="Build/Obj/Windows/Release"),

        BuildTarget("Windows81", "x86",   "Debug"):   BuildInfo(builddir="Build/Obj/Windows/Debug"),
        BuildTarget("Windows81", "x64",   "Debug"):   BuildInfo(builddir="Build/Obj/Windows/Debug"),
        BuildTarget("Windows81", "arm",   "Debug"):   BuildInfo(builddir="Build/Obj/Windows/Debug"),
        BuildTarget("Windows81", "x86",   "Release"): BuildInfo(builddir="Build/Obj/Windows/Release"),
        BuildTarget("Windows81", "x64",   "Release"): BuildInfo(builddir="Build/Obj/Windows/Release"),
        BuildTarget("Windows81", "arm",   "Release"): BuildInfo(builddir="Build/Obj/Windows/Release"),

        BuildTarget("Windows10", "x86",   "Debug"):   BuildInfo(builddir="Build/Obj/Windows/Debug"),
        BuildTarget("Windows10", "x64",   "Debug"):   BuildInfo(builddir="Build/Obj/Windows/Debug"),
        BuildTarget("Windows10", "arm",   "Debug"):   BuildInfo(builddir="Build/Obj/Windows/Debug"),
        BuildTarget("Windows10", "x86",   "Release"): BuildInfo(builddir="Build/Obj/Windows/Release"),
        BuildTarget("Windows10", "x64",   "Release"): BuildInfo(builddir="Build/Obj/Windows/Release"),
        BuildTarget("Windows10", "arm",   "Release"): BuildInfo(builddir="Build/Obj/Windows/Release"),

        BuildTarget("Linux",   "x86",   "Debug"):   BuildInfo(builddir="Build/Obj/Posix/Debug"),
        BuildTarget("Linux",   "x64",   "Debug"):   BuildInfo(builddir="Build/Obj/Posix/Debug"),
        BuildTarget("Linux",   "armel", "Debug"):   BuildInfo(builddir="Build/Obj/Posix/Debug"),
        BuildTarget("Linux",   "armhf", "Debug"):   BuildInfo(builddir="Build/Obj/Posix/Debug"),
        BuildTarget("Linux",   "ppc32", "Debug"):   BuildInfo(builddir="Build/Obj/Posix/Debug"),
        BuildTarget("Linux",   "mipsel","Debug"):   BuildInfo(builddir="Build/Obj/Posix/Debug"),
        BuildTarget("Linux",   "x86",   "Release"): BuildInfo(builddir="Build/Obj/Posix/Release"),
        BuildTarget("Linux",   "x64",   "Release"): BuildInfo(builddir="Build/Obj/Posix/Release"),
        BuildTarget("Linux",   "armel", "Release"): BuildInfo(builddir="Build/Obj/Posix/Release"),
        BuildTarget("Linux",   "armhf", "Release"): BuildInfo(builddir="Build/Obj/Posix/Release"),
        BuildTarget("Linux",   "ppc32", "Release"): BuildInfo(builddir="Build/Obj/Posix/Release"),
        BuildTarget("Linux",   "mipsel","Release"): BuildInfo(builddir="Build/Obj/Posix/Release"),

        BuildTarget("Qnap",    "x86",   "Debug"):   BuildInfo(builddir="Build/Obj/Posix/Debug"),
        BuildTarget("Qnap",    "x86",   "Release"): BuildInfo(builddir="Build/Obj/Posix/Release"),
        BuildTarget("Qnap",    "x19",   "Debug"):   BuildInfo(builddir="Build/Obj/Posix/Debug"),
        BuildTarget("Qnap",    "x19",   "Release"): BuildInfo(builddir="Build/Obj/Posix/Release"),

        BuildTarget("Mac",     "x86",   "Debug"):   BuildInfo(builddir="Build/Obj/Mac-x86/Debug"),
        BuildTarget("Mac",     "x64",   "Debug"):   BuildInfo(builddir="Build/Obj/Mac-x64/Debug"),
        BuildTarget("Mac",     "x86",   "Release"): BuildInfo(builddir="Build/Obj/Mac-x86/Release"),
        BuildTarget("Mac",     "x64",   "Release"): BuildInfo(builddir="Build/Obj/Mac-x64/Release"),

        BuildTarget("FreeBSD", "x86",   "Debug"):   BuildInfo(builddir="Build/Obj/Posix/Debug"),
        BuildTarget("FreeBSD", "x86",   "Release"): BuildInfo(builddir="Build/Obj/Posix/Release"),

        BuildTarget("iOs",     "x86",   "Debug"):   BuildInfo(builddir="Build/Obj/iOs-x86/Debug"),
        BuildTarget("iOs",     "armv6", "Debug"):   BuildInfo(builddir="Build/Obj/iOs-armv6/Debug"),
        BuildTarget("iOs",     "armv7", "Debug"):   BuildInfo(builddir="Build/Obj/iOs-armv7/Debug"),
        BuildTarget("iOs",     "arm64", "Debug"):   BuildInfo(builddir="Build/Obj/iOs-arm64/Debug"),
        BuildTarget("iOs",     "x86",   "Release"): BuildInfo(builddir="Build/Obj/iOs-x86/Release"),
        BuildTarget("iOs",     "armv6", "Release"): BuildInfo(builddir="Build/Obj/iOs-armv6/Release"),
        BuildTarget("iOs",     "armv7", "Release"): BuildInfo(builddir="Build/Obj/iOs-armv7/Release"),
        BuildTarget("iOs",     "arm64", "Release"): BuildInfo(builddir="Build/Obj/iOs-arm64/Release"),

        BuildTarget("Core",    "armv5", "Debug"):   BuildInfo(builddir="Build/Obj/Core-armv5/Debug"),
        BuildTarget("Core",    "armv5", "Release"): BuildInfo(builddir="Build/Obj/Core-armv5/Release"),
        BuildTarget("Core",    "armv6", "Debug"):   BuildInfo(builddir="Build/Obj/Core-armv6/Debug"),
        BuildTarget("Core",    "armv6", "Release"): BuildInfo(builddir="Build/Obj/Core-armv6/Release"),
        BuildTarget("Core",    "ppc32", "Debug"):   BuildInfo(builddir="Build/Obj/Core-ppc32/Debug"),
        BuildTarget("Core",    "ppc32", "Release"): BuildInfo(builddir="Build/Obj/Core-ppc32/Release"),

        BuildTarget("Android",    "anycpu", "Debug"):   BuildInfo(builddir="Build/Obj/Android-anycpu/Debug"),
        BuildTarget("Android",    "anycpu", "Release"): BuildInfo(builddir="Build/Obj/Android-anycpu/Release"),
    }

ALL_SYSTEMS = set(tgt.system for tgt in ALL_TARGETS.keys())
ALL_ARCHITECTURES = set(tgt.architecture for tgt in ALL_TARGETS.keys())
ALL_CONFIGURATIONS = set(tgt.configuration for tgt in ALL_TARGETS.keys())

def get_target_as_option_string(target):
    return "--system {0} --architecture {1} --configuration {2}".format(target.system, target.architecture, target.configuration)

def main():
    parser = optparse.OptionParser()
    #parser.add_option("-d", "--dev", dest="dev", action="store_true", default=False, help="Include development files (e.g. headers)")
    parser.add_option("-s", "--system", default=None, help="Target operating system. (One of: {0})".format(", ".join(sorted(ALL_SYSTEMS))))
    parser.add_option("-a", "--architecture", default=None, help="Target architecture. (One of: {0})".format(", ".join(sorted(ALL_ARCHITECTURES))))
    parser.add_option("-c", "--configuration", default=None, help="Target configuration. (One of: {0})".format(", ".join(sorted(ALL_CONFIGURATIONS))))
    parser.add_option("-m", "--managed-only", default=False, action="store_true", help="Package only the managed assembly.")
    options, args = parser.parse_args()
    if len(args)>0:
        print "Too many arguments."
        sys.exit(1)
    if options.system not in ALL_SYSTEMS:
        print "Please specify --system from one of {0}.".format(", ".join(sorted(ALL_SYSTEMS)))
        sys.exit(1)
    if options.architecture not in ALL_ARCHITECTURES:
        print "Please specify --architecture from one of {0}.".format(", ".join(sorted(set(tgt.architecture for tgt in ALL_TARGETS.keys() if tgt.system == options.system))))
        sys.exit(1)
    if options.configuration not in ALL_CONFIGURATIONS:
        print "Please specify --configuration from one of {0}.".format(", ".join(sorted(ALL_CONFIGURATIONS)))
        sys.exit(1)
    target = BuildTarget(options.system, options.architecture, options.configuration)
    if target not in ALL_TARGETS:
        print "Unrecognized target combination. Valid combinations are:"
        for valid_target in sorted(ALL_TARGETS.keys()):
            print "    " + get_target_as_option_string(valid_target)
        sys.exit(1)

    buildinfo = ALL_TARGETS[target]

    #osname = args[0]      # E.g. "Windows", "Posix"
    #targetname = args[1]  # E.g. "Windows-x86", "Linux-ARM", "Linux-x64"
    #release_type = args[2] # e.g. debug release

    builddir = buildinfo.builddir
    includedir = "Build/Include"
    outputdir = "Build/Bundles"
    t4dir = "Build/Tools"
    templateDir = "OpenHome/Net/T4/Templates"
    uisdkDir = "OpenHome/Net/Bindings/Js/ControlPoint"
    pyDir = "OpenHome/Net/Bindings/Python/PyOhNet"

    #if release_type == 'debug':
    #    builddir = os.path.join(builddir, 'Debug')
    #if release_type == 'release':
    #    builddir = os.path.join(builddir, 'Release')

    if options.managed_only:
        bundle_fileprefix = "ohNet.net-AnyPlatform-{target.configuration}".format(target=target)
    else:
        bundle_fileprefix = "ohNet-{target.system}-{target.architecture}-{target.configuration}".format(target=target)
    bundle_filename = bundle_fileprefix + ".tar.gz"
    bundle_path = path.join(outputdir, bundle_filename)
    if os.path.exists(bundle_path):
        os.remove(bundle_path)

    tf = tarfile.open(bundle_path, 'w:gz')

    if options.managed_only:
        recursively_add_directory(tf, builddir, bundle_fileprefix + "/lib", exclude=exclude_non_managed)
    else:
        recursively_add_directory(tf, builddir, bundle_fileprefix + "/lib", exclude=exclude_non_binary)
        #tf.add(builddir, bundle_fileprefix + "/lib", exclude=exclude_non_binary)
        recursively_add_directory(tf, includedir, bundle_fileprefix + "/include/ohnet")
        #tf.add(includedir, bundle_fileprefix + "/include/ohnet")
        recursively_add_directory(tf, t4dir, bundle_fileprefix + "/lib/t4")
        recursively_add_directory(tf, templateDir, bundle_fileprefix + "/lib/t4")
        recursively_add_directory(tf, uisdkDir, bundle_fileprefix + "/lib/ui")
        recursively_add_directory(tf, pyDir, bundle_fileprefix + "/lib/PyOhNet")

if __name__ == "__main__":
    main()
