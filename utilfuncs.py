# FIXME more descriptive name (as valgrind only applicable to native code)
def invoke_test(tsk):
    def print_vg_frame_component(frame, tag, prefix):
        o = frame.find(tag)
        if o != None:
            from xml.sax.saxutils import unescape
            print '    ' + prefix + ': ' + unescape(o.text)
    # invoke_test
    import subprocess
    import os
    os.environ["ABORT_ON_FAILURE"] = "1"
    os.environ["NO_ERROR_DIALOGS"] = "1"
    testfile = tsk.env.cxxprogram_PATTERN % tsk.generator.test
    testargs = tsk.generator.args
    bldpath = tsk.generator.bld.bldnode.abspath()
    testfilepath = os.path.join(bldpath, testfile)
    if not tsk.env.VALGRIND_ENABLE:
        cmdline = []
        cmdline.append(testfile)
        for arg in testargs:
            cmdline.append(arg)
        subprocess.check_call(cmdline, executable=testfilepath, cwd=bldpath)
    else:
        xmlfile = tsk.generator.test + '.xml'
        cmdline = []
        cmdline.append('--leak-check=yes')
        cmdline.append('--suppressions=../ValgrindSuppressions.txt')
        cmdline.append('--xml=yes')
        cmdline.append('--xml-file=' + xmlfile)
        cmdline.append('./' + testfile)
        for arg in testargs:
            cmdline.append(arg)
        subprocess.check_call(cmdline, executable='valgrind', cwd=bldpath)

        import xml.etree.ElementTree as ET
        doc = ET.parse(os.path.join(bldpath, xmlfile))
        errors = doc.findall('//error')
        if len(errors) > 0:
            for error in errors:
                print '---- error start ----'
                frames = error.findall('.//frame')
                for frame in frames:
                    print '  ---- frame start ----'
                    for tag, prefix in [['ip', 'Object'],
                                        ['fn', 'Function'],
                                        ['dir', 'Directory'],
                                        ['file', 'File'],
                                        ['line', 'Line'],
                                       ]:
                        print_vg_frame_component(frame, tag, prefix)
                    print '  ---- frame end ----'
                print '---- error end ----'
            raise Exception("Errors from valgrind")


def guess_dest_platform():
    # literally copied (for consistency) from default_platform.py in ohdevtools
    import platform
    if platform.system() == 'Windows':
        return 'Windows-x86'
    if platform.system() == 'Linux' and platform.architecture()[0] == '32bit':
        return 'Linux-x86'
    if platform.system() == 'Linux' and platform.architecture()[0] == '64bit':
        return 'Linux-x64'
    if platform.system() == 'Darwin':
        # Mac behaves similarly to Windows - a 64-bit machine can support
        # both 32-bit and 64-bit processes. We prefer 32-bit because it's
        # generally more compatible and in particular Mono is 32-bit-only.
        return 'Mac-x86'
    return None


def configure_toolchain(conf):
    import os, sys
    platform_info = get_platform_info(conf.options.dest_platform)
    if platform_info['build_platform'] != sys.platform:
        conf.fatal('Can only build for {0} on {1}, but currently running on {2}.'.format(conf.options.dest_platform, platform_info['build_platform'], sys.platform))
    conf.env.MSVC_TARGETS = ['x86']
    if conf.options.dest_platform in ['Windows-x86', 'Windows-x64']:
        conf.load('msvc')
        conf.env.append_value('CXXFLAGS',['/EHsc', '/DDEFINE_TRACE', '/DDEFINE_'+platform_info['endian']+'_ENDIAN', '/D_CRT_SECURE_NO_WARNINGS'])
        if conf.options.debugmode == 'Debug':
            conf.env.append_value('CXXFLAGS',['/MTd', '/Z7', '/Od', '/RTC1', '/DDEFINE_DEBUG'])
            conf.env.append_value('LINKFLAGS', ['/debug'])
        else:
            conf.env.append_value('CXXFLAGS',['/MT', '/Ox'])
        conf.env.append_value('CFLAGS', conf.env['CXXFLAGS'])
        # Only enable warnings for C++ code as C code si typically third party and often generates many warnings
        conf.env.append_value('CXXFLAGS',['/W4', '/WX'])
    else:
        conf.load('compiler_cxx')
        conf.load('compiler_c')
        conf.env.append_value('CFLAGS', '-g')
        conf.env.append_value('CXXFLAGS', '-g')
        conf.env.append_value('LINKFLAGS', '-g')
        conf.env.append_value('CXXFLAGS', [
                '-pipe', '-D_GNU_SOURCE', '-D_REENTRANT', '-DDEFINE_TRACE',
                '-DDEFINE_'+platform_info['endian']+'_ENDIAN', '-fvisibility=hidden',])
        if conf.options.debugmode == 'Debug':
            conf.env.append_value('CXXFLAGS',['-O0', '-DDEFINE_DEBUG'])
        else:
            conf.env.append_value('CXXFLAGS',['-O2'])
        conf.env.append_value('CFLAGS', conf.env['CXXFLAGS'])
        # Don't enable warnings for C code as its typically third party and written to different standards
        conf.env.append_value('CXXFLAGS', [
                '-fexceptions', '-Wall', '-Werror'])

        if conf.options.dest_platform in ['Linux-x86']:
            conf.env.append_value('LINKFLAGS', ['-pthread'])
            conf.env.append_value('VALGRIND_ENABLE', ['1'])
        if conf.options.dest_platform in ['Linux-x86', 'Linux-x64', 'Linux-ARM']:
            conf.env.append_value('LINKFLAGS', ['-pthread'])
            conf.env.append_value('CXXFLAGS',['-Wno-psabi', '-fPIC'])
        elif conf.options.dest_platform in ['Mac-x86', 'Mac-x64']:
            conf.env.append_value('LINKFLAGS', ['-pthread'])
            if conf.options.dest_platform == 'Mac-x86':
                conf.env.append_value('CXXFLAGS', ['-arch', 'i386'])
                conf.env.append_value('LINKFLAGS', ['-arch', 'i386'])
            if conf.options.dest_platform == 'Mac-x64':
                conf.env.append_value('CXXFLAGS', ['-arch', 'x86_64'])
                conf.env.append_value('LINKFLAGS', ['-arch', 'x86_64'])
            conf.env.append_value('CXXFLAGS',['-fPIC', '-mmacosx-version-min=10.4', '-DPLATFORM_MACOSX_GNU'])
            conf.env.append_value('LINKFLAGS',['-framework', 'CoreFoundation', '-framework', 'SystemConfiguration'])
        # Options for Core-ppc32 and Core-armv6
        if conf.options.dest_platform in ['Core-ppc32', 'Core-armv6']:
            if conf.options.dest_platform == 'Core-ppc32':
                cpu = '403'
            if conf.options.dest_platform == 'Core-armv6':
                cpu = 'arm926ej-s'
                # core2 is arm based - pass no-psabi flag to avoid excessive noise during compilation.
                conf.env.append_value('CXXFLAGS', ['-Wno-psabi'])
                conf.env.append_value('CFLAGS',   ['-Wno-psabi'])

            conf.env.append_value('LINKFLAGS', ['-specs', 'bsp_specs', '-mcpu=' + cpu])
            conf.env.append_value('CXXFLAGS',  ['-mcpu=' + cpu])
            conf.env.append_value('CFLAGS',    ['-mcpu=' + cpu])
            conf.env.append_value('DEFINES',   ['BYTE_ORDER=' + platform_info['endian'] + '_ENDIAN'])

    if conf.options.cross or os.environ.get('CROSS_COMPILE', None):
        cross_compile = conf.options.cross or os.environ['CROSS_COMPILE']
        conf.msg('Cross compiling using compiler prefix:', cross_compile)
        conf.env.CC = cross_compile + 'gcc'
        conf.env.CXX = cross_compile + 'g++'
        conf.env.AR = cross_compile + 'ar'
        conf.env.LINK_CXX = cross_compile + 'g++'
        conf.env.LINK_CC = cross_compile + 'gcc'


def guess_ohnet_location(conf):
    import os.path
    def set_env_verbose(conf, varname, value):
        conf.msg(
            'Setting %s to' % varname,
            'True' if value is True else
            'False' if value is False else
            value)
        setattr(conf.env, varname, value)
        return value
    def match_path(paths, message):
        for p in paths:
            fname = p.format(
                options=conf.options,
                debugmode_lc=conf.options.debugmode.lower(),
                debugmode_tc=conf.options.debugmode.title(),
                platform_info=get_platform_info(conf.options.dest_platform))
            if os.path.exists(fname):
                return os.path.abspath(fname)
        conf.fatal(message)
    # guess_ohnet_location
    set_env_verbose(conf, 'INCLUDES_OHNET', match_path(
        [
            '{options.ohnet_include_dir}',
            '{options.ohnet}/Build/Include',
            'dependencies/{options.dest_platform}/ohNet-{options.dest_platform}-{debugmode_lc}-dev/include/ohnet',
            'dependencies/{options.dest_platform}/ohNet-{options.dest_platform}-{debugmode_tc}/include/ohnet',
        ],
        message='Specify --ohnet-include-dir or --ohnet')
    )
    set_env_verbose(conf, 'STLIBPATH_OHNET', match_path(
        [
            '{options.ohnet_lib_dir}',
            '{options.ohnet}/Build/Obj/{platform_info[ohnet_plat_dir]}/{options.debugmode}',
            'dependencies/{options.dest_platform}/ohNet-{options.dest_platform}-{debugmode_lc}-dev/lib', 
            'dependencies/{options.dest_platform}/ohNet-{options.dest_platform}-{debugmode_tc}/lib',
        ],
        message='Specify --ohnet-lib-dir or --ohnet')
    )

def get_platform_info(dest_platform):
    platforms = {
        'Linux-x86': dict(endian='LITTLE',   build_platform='linux2', ohnet_plat_dir='Posix'),
        'Linux-x64': dict(endian='LITTLE',   build_platform='linux2', ohnet_plat_dir='Posix'),
        'Linux-ARM': dict(endian='LITTLE',   build_platform='linux2', ohnet_plat_dir='Posix'),
        'Windows-x86': dict(endian='LITTLE', build_platform='win32',  ohnet_plat_dir='Windows'),
        'Windows-x64': dict(endian='LITTLE', build_platform='win32',  ohnet_plat_dir='Windows'),
        'Core-ppc32': dict(endian='BIG',     build_platform='linux2', ohnet_plat_dir='Core-ppc32'),
        'Core-armv6': dict(endian='LITTLE',  build_platform='linux2', ohnet_plat_dir='Core-armv6'),
        'Mac-x86': dict(endian='LITTLE',     build_platform='darwin', ohnet_plat_dir='Mac-x86'),
        'Mac-x64': dict(endian='LITTLE',     build_platform='darwin', ohnet_plat_dir='Mac-x64'),
        'iOs-ARM': dict(endian='LITTLE',     build_platform='darwin', ohnet_plat_dir='Mac/arm'),
    }
    return platforms[dest_platform]
