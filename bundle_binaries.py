import sys
import tarfile
import optparse
from os import path
import os

def exclude_non_binary(filename):
    if filename.lower().startswith("test"):
        return True
    executable_extensions = [".dll", ".so", ".elf", ".lib", ".map", ".pdb", ".dylib"]
    has_executable_extension = any(filename.endswith(ex) for ex in executable_extensions)
    has_no_extension = "." not in filename
    is_binary = has_executable_extension or has_no_extension
    return not is_binary

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


def main():
    parser = optparse.OptionParser()
    parser.add_option("-d", "--dev", dest="dev", action="store_true", default=False, help="Include development files (e.g. headers)")
    options, args = parser.parse_args()
    osname = args[0]      # E.g. "Windows", "Posix"
    targetname = args[1]  # E.g. "Windows-x86", "Linux-ARM", "Linux-x64"
    release_type = args[2] # e.g. debug release

    builddir = "Build/Obj/" + osname
    includedir = "Build/Include"
    outputdir = "Build/Bundles"
    t4dir = "Build/" + osname + "/Tools"
    templateDir = "OpenHome/Net/T4/Templates"
    uisdkDir = "OpenHome/Net/Bindings/Js/ControlPoint"

    if release_type == 'debug':
        builddir = os.path.join(builddir, 'Debug')
    if release_type == 'release':
        builddir = os.path.join(builddir, 'Release')

    bundle_fileprefix = "ohNet-%s-%s%s" % (targetname, release_type, "-dev" if options.dev else "")
    bundle_filename = bundle_fileprefix + ".tar.gz"
    bundle_path = path.join(outputdir, bundle_filename)
    if os.path.exists(bundle_path):
        os.remove(bundle_path)

    tf = tarfile.open(bundle_path, 'w:gz')

    recursively_add_directory(tf, builddir, bundle_fileprefix + "/lib", exclude=exclude_non_binary)
    #tf.add(builddir, bundle_fileprefix + "/lib", exclude=exclude_non_binary)
    if options.dev:
        recursively_add_directory(tf, includedir, bundle_fileprefix + "/include/ohnet")
        #tf.add(includedir, bundle_fileprefix + "/include/ohnet")
        recursively_add_directory(tf, t4dir, bundle_fileprefix + "/lib/t4")
        recursively_add_directory(tf, templateDir, bundle_fileprefix + "/lib/t4")
        recursively_add_directory(tf, uisdkDir, bundle_fileprefix + "/lib/ui")

if __name__ == "__main__":
    main()
