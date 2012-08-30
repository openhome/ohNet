#!/usr/bin/python

import sys
import os

from waflib.Node import Node

import os.path, sys
sys.path[0:0] = [os.path.join('dependencies', 'AnyPlatform', 'ohWafHelpers')]

from filetasks import gather_files, build_tree
from utilfuncs import invoke_test, set_env_verbose

def options(opt):
    opt.load('msvc')
    opt.load('compiler_cxx')
    opt.add_option('--ohnet-include-dir', action='store', default=None)
    opt.add_option('--ohnet-lib-dir', action='store', default=None)
    opt.add_option('--ohnet', action='store', default=None)
    opt.add_option('--debug', action='store_const', dest="debugmode", const="Debug", default="Release")
    opt.add_option('--release', action='store_const', dest="debugmode",  const="Release", default="Release")
    opt.add_option('--dest-platform', action='store', default=None)
    opt.add_option('--cross', action='store', default=None)
    #opt.add_option('--big-endian', action='store_const', dest="endian",  const="BIG", default="LITTLE")
    #opt.add_option('--little-endian', action='store_const', dest="endian",  const="LITTLE", default="LITTLE")
    #opt.add_option('--dest', action='store', default=None)

platforms = {
        'Linux-x86': dict(endian='LITTLE',   build_platform='linux2', ohnet_plat_dir='Posix'),
        'Linux-x64': dict(endian='LITTLE',   build_platform='linux2', ohnet_plat_dir='Posix'),
        'Linux-ARM': dict(endian='LITTLE',   build_platform='linux2', ohnet_plat_dir='Posix'),
        'Windows-x86': dict(endian='LITTLE', build_platform='win32',  ohnet_plat_dir='Windows'),
        'Windows-x64': dict(endian='LITTLE', build_platform='win32',  ohnet_plat_dir='Windows'),
        'Core': dict(endian='BIG',           build_platform='linux2', ohnet_plat_dir='Volcano2'),
        'Mac-x86': dict(endian='LITTLE',     build_platform='darwin', ohnet_plat_dir='Mac'),
        'Mac-x64': dict(endian='LITTLE',     build_platform='darwin', ohnet_plat_dir='Mac'),
        'iOs-ARM': dict(endian='LITTLE',     build_platform='darwin', ohnet_plat_dir='Mac/arm'),
        }

def configure(conf):
    def match_path(paths, message):
        for p in paths:
            fname = p.format(options=conf.options, debugmode=debugmode, ohnet_plat_dir=ohnet_plat_dir)
            if os.path.exists(fname):
                return os.path.abspath(fname)
        conf.fatal(message)

    debugmode = conf.options.debugmode
    conf.msg("debugmode:", debugmode)
    dest_platform = conf.options.dest_platform
    if dest_platform is None:
        conf.fatal('Specify --dest-platform')

    platform_info = platforms[dest_platform]
    ohnet_plat_dir = platform_info['ohnet_plat_dir']
    build_platform = platform_info['build_platform']
    endian = platform_info['endian']

    if build_platform != sys.platform:
        conf.fatal('Can only build for {0} on {1}, but currently running on {2}.'.format(dest_platform, build_platform, sys.platform))

    env = conf.env
    append = env.append_value
    env.MSVC_TARGETS = ['x86']
    if dest_platform in ['Windows-x86', 'Windows-x64']:
        conf.load('msvc')
        append('CXXFLAGS',['/W4', '/WX', '/EHsc', '/DDEFINE_TRACE', '/DDEFINE_'+endian+'_ENDIAN'])
        if debugmode == 'Debug':
            append('CXXFLAGS',['/MTd', '/Z7', '/Od', '/RTC1'])
            append('LINKFLAGS', ['/debug'])
        else:
            append('CXXFLAGS',['/MT', '/Ox'])
        env.LIB_OHNET=['ws2_32', 'iphlpapi', 'dbghelp']
    else:
        conf.load('compiler_cxx')
        append('CXXFLAGS', [
                '-fexceptions', '-Wall', '-pipe',
                '-D_GNU_SOURCE', '-D_REENTRANT', '-DDEFINE_'+endian+'_ENDIAN',
                '-DDEFINE_TRACE', '-fvisibility=hidden', '-Werror'])
        if debugmode == 'Debug':
            append('CXXFLAGS',['-g','-O0'])
        else:
            append('CXXFLAGS',['-O2'])
        append('LINKFLAGS', ['-pthread'])
        if dest_platform in ['Linux-x86']:
            append('VALGRIND_ENABLE', ['1'])
        if dest_platform in ['Linux-x86', 'Linux-x64', 'Linux-ARM']:
            append('CXXFLAGS',['-Wno-psabi', '-fPIC'])
        elif dest_platform in ['Mac-x86', 'Mac-x64']:
            if dest_platform == 'Mac-x86':
                append('CXXFLAGS', ['-arch', 'i386'])
                append('LINKFLAGS', ['-arch', 'i386'])
            if dest_platform == 'Max-x64':
                append('CXXFLAGS', ['-arch', 'x86_64'])
                append('LINKFLAGS', ['-arch', 'x86_64'])
            append('CXXFLAGS',['-fPIC', '-mmacosx-version-min=10.4', '-DPLATFORM_MACOSX_GNU'])
            append('LINKFLAGS',['-framework', 'CoreFoundation', '-framework', 'SystemConfiguration'])

    set_env_verbose(conf, 'INCLUDES_OHNET', match_path(
        [
            '{options.ohnet_include_dir}',
            '{options.ohnet}/Build/Include',
        ],
        message='Specify --ohnet-include-dir or --ohnet'))
    set_env_verbose(conf, 'STLIBPATH_OHNET', match_path(
        [
            '{options.ohnet_lib_dir}',
            '{options.ohnet}/Build/Obj/{ohnet_plat_dir}/{debugmode}',
        ],
        message='FAILED.  Was --ohnet-lib-dir or --ohnet specified?  Do the directories they point to (including debug/release) exist?'))
    conf.env.STLIB_OHNET=['ohNetProxies', 'TestFramework', 'ohNetCore']
    conf.env.INCLUDES = conf.path.find_node('.').abspath()

    if conf.options.cross or os.environ.get('CROSS_COMPILE', None):
        cross_compile = conf.options.cross or os.environ['CROSS_COMPILE']
        conf.msg('Cross compiling using compiler prefix:', cross_compile)
        env.CC = cross_compile + 'gcc'
        env.CXX = cross_compile + 'g++'
        env.AR = cross_compile + 'ar'
        env.LINK_CXX = cross_compile + 'g++'
        env.LINK_CC = cross_compile + 'gcc'

def get_node(bld, node_or_filename):
    if isinstance(node_or_filename, Node):
        return node_or_filename
    return bld.path.find_node(node_or_filename)

def create_copy_task(build_context, files, target_dir='', cwd=None, keep_relative_paths=False, name=None):
    source_file_nodes = [get_node(build_context, f) for f in files]
    if keep_relative_paths:
        cwd_node = build_context.path.find_dir(cwd)
        target_filenames = [
                path.join(target_dir, source_node.path_from(cwd_node))
                for source_node in source_file_nodes]
    else:
        target_filenames = [
                os.path.join(target_dir, source_node.name)
                for source_node in source_file_nodes]
        target_filenames = map(build_context.bldnode.make_node, target_filenames)
    return build_context(
            rule=copy_task,
            source=source_file_nodes,
            target=target_filenames,
            name=name)

def build(bld):

    # Library
    bld.stlib(
            source=[
                'OpenHome/Av/FaultCode.cpp',
                'OpenHome/Av/InfoProvider.cpp',
                'OpenHome/Av/KvpStore.cpp',
                'OpenHome/Av/Product.cpp',
                'OpenHome/Av/ProviderProduct.cpp',
                'OpenHome/Av/Source.cpp',
                'OpenHome/Media/Msg.cpp',
                'OpenHome/Media/VariableDelayBuffer.cpp',
            ],
            use=['OHNET'],
            target='ohMediaPlayer')

    # Tests
    bld.stlib(
            source=[
                'OpenHome/Av/Tests/RamStore.cpp',
            ],
            use=['ohMediaPlayer'],
            target='ohMediaPlayerTestUtils')
    bld.program(
            source='OpenHome/Media/Tests/TestMsg.cpp',
            use=['OHNET', 'ohMediaPlayer'],
            target='TestMsg')
    bld.program(
            source='OpenHome/Av/Tests/TestStore.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestStore')

    # Bundles
    #header_files = gather_files(bld, '{top}/src', ['*.h'])
    #lib_files = gather_files(bld, '{bld}', [bld.env.cxxstlib_PATTERN % 'ohTopology'])
    #bundle_dev_files = build_tree({
    #    'ohTopology/lib' : lib_files,
    #    'ohTopology/include' : header_files
    #    })
    #bundle_files = build_tree({
    #    'ohTopology/lib' : lib_files,
    #    })
    #bundle_dev_files.create_tgz_task(bld, 'ohTopology-dev.tar.gz')
    #bundle_files.create_tgz_task(bld, 'ohTopology.tar.gz')

# == Command for invoking unit tests ==

def test(tst):
    for t, a, when in [['TestMsg', [], True]
                      ,['TestStore', [], True]
                      ]:
        tst(rule=invoke_test, test=t, args=a, always=when)
        tst.add_group() # Don't start another test until previous has finished.


# == Contexts to make 'waf test' work ==

from waflib.Build import BuildContext

class TestContext(BuildContext):
    cmd = 'test'
    fun = 'test'

# vim: set filetype=python softtabstop=4 expandtab shiftwidth=4 tabstop=4:
