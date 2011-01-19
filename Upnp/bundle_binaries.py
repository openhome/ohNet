import sys
import tarfile
import optparse
from os import path
import os

def exclude_non_binary(filename):
    if filename.lower().startswith("test"):
        return True
    return not (filename.endswith(".dll") or filename.endswith(".so") or filename.endswith(".elf") or ("." not in filename))

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

    builddir = "Build/Obj/" + osname
    includedir = "Build/Include"
    outputdir = "Build/Bundles"
    t4dir = "Build/" + osname + "/Tools"
    templateDir = "T4/Templates"

    bundle_fileprefix = "zapp-%s%s" % (targetname, "-dev" if options.dev else "")
    bundle_filename = bundle_fileprefix + ".tar.gz"
    bundle_path = path.join(outputdir, bundle_filename)

    tf = tarfile.open(bundle_path, 'w:gz')

    recursively_add_directory(tf, builddir, bundle_fileprefix + "/lib", exclude=exclude_non_binary)
    #tf.add(builddir, bundle_fileprefix + "/lib", exclude=exclude_non_binary)
    if options.dev:
        recursively_add_directory(tf, includedir, bundle_fileprefix + "/include/zapp")
        #tf.add(includedir, bundle_fileprefix + "/include/zapp")
        recursively_add_directory(tf, t4dir, bundle_fileprefix + "/lib/t4")
        recursively_add_directory(tf, templateDir, bundle_fileprefix + "/lib/t4")

if __name__ == "__main__":
    main()
