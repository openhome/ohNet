import zipfile
import os
import shutil
import tarfile
import sys

_ignorecase = sys.platform == 'win32'

def find_resource_or_fail(bld, root, path):
    node = root.find_resource(path)
    if node is None:
        bld.fatal("Could not find resource '%s' starting from root '%s'." % (path, root))
    return node

def copy_task(task):
    if not (len(task.inputs) == len(task.outputs)):
        raise Exception("copy_task requires the same number of inputs and outputs.")
    for source, target in zip(task.inputs, task.outputs):
        shutil.copy2(source.abspath(), target.abspath())

def simpleziprule(task):
    zf = zipfile.ZipFile(task.outputs[0].abspath(),'w',zipfile.ZIP_DEFLATED)
    for inputnode, arcname in zip(task.inputs, task.generator.arcnames):
        zf.write(inputnode.abspath(), arcname)
    zf.close()

def simpletgzrule(task):
    tarf = tarfile.open(task.outputs[0].abspath(),'w:gz')
    for inputnode, arcname in zip(task.inputs, task.generator.arcnames):
        tarf.add(inputnode.abspath(), arcname)
    tarf.close()

def _strip_prefix(path, prefix):
    result = os.path.relpath(path, prefix)
    if result.startswith('..'):
        raise Exception('Path {0} does not begin with {1}'.format(path, prefix))
    return result

class FileTree(object):
    '''
    Describes a collection of files, possibly in multiple directories.
    The files might all have absolute paths, or might all be relative.
    (There's no mechanism to enforce this, though.)
    Retains the order of the files.
    '''
    def __init__(self, files):
        self.files = list(files)
    def __add__(self, other):
        return FileTree(self.files + other.files)
    def add_prefix(self, prefix):
        return FileTree(os.path.join(prefix, f) for f in self.files)
    def strip_prefix(self, prefix):
        return FileTree(_strip_prefix(f, prefix) for f in self.files)
    def flatten(self):
        return FileTree(os.path.basename(f) for f in self.files)
    def to_nodes(self, bld):
        return [_find_or_declare_node_by_abspath(bld,f) for f in self.files]

def _must_have_at_least_one(sequence):
    if len(sequence) < 1:
        raise ValueError("Expected a non-empty sequence.")

def _find_or_declare_node_by_abspath(bld, abspath):
    '''
    Waf fights us tooth and nail to try to enforce its convoluted view of the file-system,
    and falls to pieces any time it gets confused. This takes an absolute path and works
    around waf's quirks to obtain the corresponding node.
    If the node is in the build tree, it might not exist yet, and waf will do bizarre
    things if we ask it to create the absolute path. If the node is outside of the build
    tree, we require it to exist now, or we will fail immediately.
    '''
    try:
        build_path = os.path.relpath(abspath, bld.bldnode.abspath())
        if not (build_path.startswith('../') or build_path.startswith('..\\')):
            return bld.bldnode.find_or_declare(build_path)
    except ValueError:
        # relpath raises ValueError if abspath is on a different drive from bldnode.
        # Fall through and treat as non-build file.
        pass
    return find_resource_or_fail(bld, bld.root, abspath)

def glob_files_src(bld, *globs):
    '''
    Search for files matching any of the given globs, relative to the source directory. (Note
    that the source directory is the one that contains the wscript, *not* 'src'.) The globs
    should not intersect - no checking is done for duplicate files.
    Returns a FileTree.
    '''
    _must_have_at_least_one(globs)
    return combine_trees(FileTree(node.abspath() for node in bld.srcnode.ant_glob(g,remove=False)) for g in globs)

def glob_files_bld(bld, *globs):
    '''
    Search for files matching any of the given globs, relative to the build directory. The
    globs should not intersect - no checking is done for duplicate files.
    Returns a FileTree.
    '''
    _must_have_at_least_one(globs)
    return combine_trees(FileTree(node.abspath() for node in bld.bldnode.ant_glob(g,remove=False)) for g in globs)

def mk_virtual_tree(bld, rootpath, patterns):
    bldpath = bld.bldnode.abspath()
    toppath = bld.srcnode.abspath()
    all_file_paths = []
    for pattern in patterns:
        full_pattern = os.path.join(rootpath, pattern).format(bld=bldpath, top=toppath)
        if '*' in full_pattern or '?' in full_pattern:
            if full_pattern.startswith('/') or full_pattern.startswith('\\'):
                full_pattern = full_pattern[1:]
            files = _root_glob(bld.root, full_pattern)
        else:
            files = [_find_or_declare_node_by_abspath(bld, full_pattern)]
        all_file_paths.extend(f.abspath() for f in files)
    transfer = FileTransfer(FileTree(all_file_paths))
    result = transfer.targets_stripped(rootpath)
    return result

def _root_glob(root, glob):
    if glob.startswith('/') or glob.startswith('\\'):
        glob = glob[1:]
    return root.ant_glob(glob,ignorecase=_ignorecase, remove=False)

def glob_files_root(bld, *globs):
    '''
    Search for files matching any of the given globs, which should be absolute paths. The
    globs should not intersect - no checking is done for duplicate files.
    Returns a FileTree.
    '''
    _must_have_at_least_one(globs)
    return combine_trees(FileTree(node.abspath() for node in _root_glob(bld.root, g)) for g in globs)

def specify_files_src(bld, *files):
    '''
    Specify a collection of files relative to the source directory. They must exist already.
    Returns a FileTree.
    '''
    return FileTree(find_resource_or_fail(bld, bld.srcnode, f).abspath() for f in files)

def specify_files_bld(bld, *files):
    '''
    Specify a collection of files relative to the build directory. They do not need to exist
    yet.
    Returns a FileTree.
    '''
    _must_have_at_least_one(files)
    return FileTree(bld.bldnode.find_or_declare(f).abspath() for f in files)

def specify_files_root(bld, *files):
    '''
    Specify a collection of files with absolute paths. They must exist already.
    Returns a FileTree.
    '''
    _must_have_at_least_one(files)
    return FileTree(find_resource_or_fail(bld, bld.root, f).abspath() for f in files)

def combine_trees(trees):
    '''
    Combine a sequence of FileTrees into one FileTree, retaining their order.
    '''
    return sum(trees, FileTree([]))

class FileTransfer(object):
    '''
    Describes a transfer of a collection of files from one set of locations to another.
    Source and destination are each FileTrees.
    '''
    def __init__(self, sourcetree, targettree=None):
        self.sourcetree = sourcetree
        self.targettree = targettree if targettree is not None else sourcetree
    def __add__(self, other):
        return FileTransfer(
                self.sourcetree + other.sourcetree,
                self.targettree + other.targettree)
    def targets_prefixed(self, prefix):
        '''
        Return a new FileTransfer that copies files from the same locations as before,
        but with target locations modified by prefixing one or more directories.
        '''
        return FileTransfer(
                self.sourcetree,
                self.targettree.add_prefix(prefix))
    def targets_stripped(self, prefix):
        '''
        Return a new FileTransfer that copies files from the same locations as before,
        but with target locations modified by stripping off the leading directories.
        '''
        return FileTransfer(
                self.sourcetree,
                self.targettree.strip_prefix(prefix))
    def targets_flattened(self):
        '''
        Returns a new FileTransfer that copies files from the same locations as before,
        but that strips off all directories from the targets.
        '''
        return FileTransfer(
                self.sourcetree,
                self.targettree.flatten())
    def create_zip_task(self, bld, target, name=None):
        '''
        Create one task that combines all the source files into a zip-file, using the
        targets as names inside the zip archive.
        '''
        return bld(
                rule=simpleziprule,
                source=list(_find_or_declare_node_by_abspath(bld, f) for f in self.sourcetree.files),
                arcnames=list(self.targettree.files),
                target=target,
                name=name)
    def create_tgz_task(self, bld, target, name=None):
        return bld(
                rule=simpletgzrule,
                source=list(_find_or_declare_node_by_abspath(bld, f) for f in self.sourcetree.files),
                arcnames=list(self.targettree.files),
                target=target,
                name=name)
    def create_copy_tasks(self, bld, name=None):
        '''
        Create one task per file, copying from source locations to target locations.
        Source locations should be absolute paths.
        Target locations should be relative to the build directory.
        '''
        return [
            bld(rule=copy_task, source=_find_or_declare_node_by_abspath(bld, s), target=t)
            for s,t in zip(self.sourcetree.files, self.targettree.files)]
    def install_files(self, bld):
        '''
        Copy the files at install-time.
        '''
        for source, target in zip(self.sourcetree.files, self.targettree.files):
            bld.install_as(target, _find_or_declare_node_by_abspath(bld, source))
    def install_files_preserving_permissions(self, bld):
        '''
        Copy the files at install-time.
        '''
        if not getattr(bld, 'is_install', False):
            return
        for source, target in zip(self.sourcetree.files, self.targettree.files):
            mode = os.stat(source).st_mode & 0o777
            bld.install_as(target, bld.root.find_or_declare(source), chmod=mode)

def combine_transfers(transfers):
    '''
    Combine a sequence of FileTransfers.
    '''
    return sum(transfers, FileTransfer(FileTree([])))
