#!/usr/bin/python

import sys
import os

from waflib.Node import Node

import os.path, sys
sys.path[0:0] = [os.path.join('dependencies', 'AnyPlatform', 'ohWafHelpers')]

from filetasks import gather_files, build_tree
from utilfuncs import invoke_test, guess_dest_platform, configure_toolchain, guess_ohnet_location

def options(opt):
    opt.load('msvc')
    opt.load('compiler_cxx')
    opt.load('compiler_c')
    opt.add_option('--ohnet-include-dir', action='store', default=None)
    opt.add_option('--ohnet-lib-dir', action='store', default=None)
    opt.add_option('--ohnet', action='store', default=None)
    opt.add_option('--libosa', action='store', default=None)
    opt.add_option('--debug', action='store_const', dest="debugmode", const="Debug", default="Release")
    opt.add_option('--release', action='store_const', dest="debugmode",  const="Release", default="Release")
    opt.add_option('--dest-platform', action='store', default=None)
    opt.add_option('--cross', action='store', default=None)
    #opt.add_option('--big-endian', action='store_const', dest="endian",  const="BIG", default="LITTLE")
    #opt.add_option('--little-endian', action='store_const', dest="endian",  const="LITTLE", default="LITTLE")
    #opt.add_option('--dest', action='store', default=None)

def configure(conf):
    conf.msg("debugmode:", conf.options.debugmode)
    if conf.options.dest_platform is None:
        try:
            conf.options.dest_platform = guess_dest_platform()
        except KeyError:
            conf.fatal('Specify --dest-platform')

    configure_toolchain(conf)
    guess_ohnet_location(conf)

    if conf.options.dest_platform in ['Windows-x86', 'Windows-x64']:
        conf.env.LIB_OHNET=['ws2_32', 'iphlpapi', 'dbghelp']
    conf.env.STLIB_OHNET=['ohNetProxies', 'ohNetDevices', 'TestFramework', 'ohNetCore']

    if conf.options.dest_platform in ['Libosa-core1', 'Libosa-core2']:
        osa_include_dir = os.path.join(conf.options.libosa, 'install', 'include')
        conf.env.append_value('INCLUDES_OSA', [os.path.abspath(os.path.join(osa_include_dir, x)) for x in ['', 'lwip']])
        conf.env.append_value('DEFINES', ['NETWORK_LWIP', 'NOTERMIOS']) # Tell FLAC about LWIP, stub out mygetch().
        conf.env.append_value('LINKFLAGS', ['-B' + os.path.abspath(os.path.join(conf.options.libosa, 'install', 'lib'))])

    conf.env.INCLUDES = conf.path.find_node('.').abspath()
    # Setup FLAC lib options 
    conf.env.DEFINES_FLAC = ['VERSION=\"1.2.1\"', 'FLAC__NO_DLL']
    conf.env.INCLUDES_FLAC = [
        'flac-1.2.1/src/libFLAC/include',
        'flac-1.2.1/include',
        'libogg-1.1.3/include',
    ]

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
                'OpenHome/Av/Songcast/Ohm.cpp',
                'OpenHome/Av/Songcast/OhmMsg.cpp',
                'OpenHome/Av/Songcast/OhmProtocolMulticast.cpp',
                'OpenHome/Av/Songcast/OhmProtocolUnicast.cpp',
                'OpenHome/Av/Songcast/OhmReceiver.cpp',
                'OpenHome/Av/Songcast/OhmSender.cpp',
                'OpenHome/Av/Songcast/OhmSocket.cpp',
                'OpenHome/Media/AudioReservoir.cpp',
                'OpenHome/Media/DecodedAudioReservoir.cpp',
                'OpenHome/Media/EncodedAudioReservoir.cpp',
                'OpenHome/Media/Logger.cpp',
                'OpenHome/Media/Msg.cpp',
                'OpenHome/Media/PreDriver.cpp',
                'OpenHome/Media/Reporter.cpp',
                'OpenHome/Media/Splitter.cpp',
                'OpenHome/Media/StarvationMonitor.cpp',
                'OpenHome/Media/Stopper.cpp',
                'OpenHome/Media/VariableDelay.cpp',
                'OpenHome/Media/PipelineManager.cpp',
                'OpenHome/Media/DriverSongcastSender.cpp',
                'OpenHome/Media/ProcessorPcmUtils.cpp',
                'OpenHome/Media/Codec/Container.cpp',
                'OpenHome/Media/Codec/Id3v2.cpp',
                'OpenHome/Media/Codec/CodecController.cpp',
                'OpenHome/Media/Protocol/Protocol.cpp',
                'OpenHome/Media/Protocol/ProtocolHttp.cpp',
            ],
            use=['OHNET'],
            target='ohMediaPlayer')

    # Wav
    bld.stlib(
            source=['OpenHome/Media/Codec/Wav.cpp'],
            use=['OHNET'],
            target='CodecWav')

    # Ogg
    bld.stlib(
            source=[
                'libogg-1.1.3/src/bitwise.c',
                'libogg-1.1.3/src/framing.c'
            ],
            includes = ['libogg-1.1.3/include'],
            target='libOgg')

    # Flac
    bld.stlib(
            source=[
                'OpenHome/Media/Codec/Flac.cpp',
                'flac-1.2.1/src/libFLAC/bitreader.c',
                'flac-1.2.1/src/libFLAC/bitmath.c',
                'flac-1.2.1/src/libFLAC/cpu.c',
                'flac-1.2.1/src/libFLAC/crc.c',
                'flac-1.2.1/src/libFLAC/fixed.c',
                'flac-1.2.1/src/libFLAC/format.c',
                'flac-1.2.1/src/libFLAC/lpc.c',
                'flac-1.2.1/src/libFLAC/md5.c',
                'flac-1.2.1/src/libFLAC/memory.c',
                'flac-1.2.1/src/libFLAC/stream_decoder.c',
                'flac-1.2.1/src/libFLAC/ogg_decoder_aspect.c',
                'flac-1.2.1/src/libFLAC/ogg_mapping.c',
            ],
            use=['FLAC', 'OHNET', 'OSA'],
            target='CodecFlac')

    # Tests
    bld.stlib(
            source=[
                'OpenHome/Av/Tests/RamStore.cpp',
                'OpenHome/Media/Tests/AllocatorInfoLogger.cpp',
                'OpenHome/Media/Tests/TestMsg.cpp',
                'OpenHome/Media/Tests/TestStarvationMonitor.cpp',
                'OpenHome/Media/Tests/TestStopper.cpp',
                'OpenHome/Media/Tests/TestAudioReservoir.cpp',
                'OpenHome/Media/Tests/TestVariableDelay.cpp',
                'OpenHome/Media/Tests/TestReporter.cpp',
                'OpenHome/Media/Tests/TestPreDriver.cpp',
                'OpenHome/Media/Tests/TestPipeline.cpp',
                #'OpenHome/Media/Tests/FileSender.cpp',
            ],
            use=['ohMediaPlayer', 'FLAC', 'CodecFlac', 'CodecWav'],
            target='ohMediaPlayerTestUtils')
    bld.program(
            source='OpenHome/Media/Tests/TestMsgMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestMsg')
    bld.program(
            source='OpenHome/Media/Tests/TestStarvationMonitorMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestStarvationMonitor')
    bld.program(
            source='OpenHome/Media/Tests/TestStopperMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestStopper')
    bld.program(
            source='OpenHome/Media/Tests/TestAudioReservoirMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestAudioReservoir')
    bld.program(
            source='OpenHome/Media/Tests/TestVariableDelayMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestVariableDelay')
    bld.program(
            source='OpenHome/Media/Tests/TestReporterMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestReporter')
    bld.program(
            source='OpenHome/Media/Tests/TestPreDriverMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestPreDriver')
    bld.program(
            source='OpenHome/Media/Tests/TestPipelineMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestPipeline')
    #bld.program(
    #        source='OpenHome/Media/Tests/FileSenderMain.cpp',
    #        use=['OHNET', 'ohMediaPlayer', 'CodecFlac', 'CodecWav', 'ohMediaPlayerTestUtils'],
    #        target='FileSender')
    bld.program(
            source='OpenHome/Media/Tests/TestProtocolHttp.cpp',
            use=['OHNET', 'FLAC', 'ohMediaPlayer', 'CodecFlac', 'CodecWav', 'ohMediaPlayerTestUtils'],
            target='TestProtocolHttp')
    bld.program(
            source='OpenHome/Media/Tests/TestPipeline2.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestPipeline2')
    bld.program(
            source='OpenHome/Media/Tests/TestPipeline3.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestPipeline3')
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
                      ,['TestAudioReservoir', [], True]
                      ,['TestVariableDelay', [], True]
                      ,['TestStopper', [], True]
                      ,['TestReporter', [], True]
                      ,['TestStarvationMonitor', [], True]
                      ,['TestPreDriver', [], True]
                      ,['TestPipeline', [], True]
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
