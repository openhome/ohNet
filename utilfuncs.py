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


def get_platform_info(dest_platform):
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
    return platforms[dest_platform]


def set_env_verbose(conf, varname, value):
    conf.msg(
        'Setting %s to' % varname,
        'True' if value is True else
        'False' if value is False else
        value)
    setattr(conf.env, varname, value)
    return value
