#!/usr/bin/python

import sys
import os

from waflib.Node import Node

import os.path, sys
sys.path[0:0] = [os.path.join('dependencies', 'AnyPlatform', 'ohWafHelpers')]

from filetasks import gather_files, build_tree, copy_task
from utilfuncs import invoke_test, guess_dest_platform, configure_toolchain, guess_ohnet_location

def options(opt):
    opt.load('msvc')
    opt.load('compiler_cxx')
    opt.load('compiler_c')
    opt.add_option('--ohnet-include-dir', action='store', default=None)
    opt.add_option('--ohnet-lib-dir', action='store', default=None)
    opt.add_option('--ohnet', action='store', default=None)
    opt.add_option('--debug', action='store_const', dest="debugmode", const="Debug", default="Release")
    opt.add_option('--release', action='store_const', dest="debugmode",  const="Release", default="Release")
    opt.add_option('--dest-platform', action='store', default=None)
    opt.add_option('--cross', action='store', default=None)
    opt.add_option('--nolink', action='store_true', dest="nolink", default=False)

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

    if conf.options.dest_platform in ['Core-ppc32', 'Core-armv6']:
        conf.env.append_value('DEFINES', ['DEFINE_TRACE', 'NETWORK_NTOHL_LOCAL', 'NOTERMIOS']) # Tell FLAC to use local ntohl implementation

    conf.env.nolink = conf.options.nolink

    conf.env.INCLUDES = conf.path.find_node('.').abspath()

    # Setup FLAC lib options 
    conf.env.DEFINES_FLAC = ['VERSION=\"1.2.1\"', 'FLAC__NO_DLL']
    conf.env.INCLUDES_FLAC = [
        'flac-1.2.1/src/libFLAC/include',
        'flac-1.2.1/include',
        'libogg-1.1.3/include',
        ]

    conf.env.STLIB_SHELL = ['Shell']

    # Setup Mad (mp3) lib options
    fixed_point_model = 'FPM_INTEL'
    if conf.options.dest_platform in ['Linux-ARM', 'Core-armv6']:
        fixed_point_model = 'FPM_ARM'
    elif conf.options.dest_platform in ['Core-ppc32']:
        fixed_point_model = 'FPM_PPC'
    conf.env.DEFINES_MAD = [fixed_point_model, 'OPT_ACCURACY']
    if conf.options.dest_platform in ['Windows-x86', 'Windows-x64']:
        conf.env.DEFINES_MAD.append('inline=__inline')
    conf.env.INCLUDES_MAD = ['libmad-0.15.1b']

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
                'OpenHome/Media/Supply.cpp',
                'OpenHome/Media/VariableDelay.cpp',
                'OpenHome/Media/PipelineManager.cpp',
                'OpenHome/Media/DriverSongcastSender.cpp',
                'OpenHome/Media/ProcessorPcmUtils.cpp',
                'OpenHome/Media/Codec/Container.cpp',
                'OpenHome/Media/Codec/Id3v2.cpp',
                'OpenHome/Media/Codec/CodecController.cpp',
                'OpenHome/Media/Protocol/Protocol.cpp',
                'OpenHome/Media/Protocol/ProtocolHttp.cpp',
                'OpenHome/Media/Protocol/ProtocolFile.cpp',
                'OpenHome/Media/Protocol/ContentAudio.cpp',
                'OpenHome/Media/Protocol/ContentPls.cpp',
                'OpenHome/Media/Protocol/ContentM3u.cpp',
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
            use=['FLAC', 'OHNET'],
            target='CodecFlac')

    # MP3
    bld.stlib(
            source=[
                'OpenHome/Media/Codec/Mp3.cpp',
                'libmad-0.15.1b/version.c',
                'libmad-0.15.1b/fixed.c',
                'libmad-0.15.1b/bit.c',
                'libmad-0.15.1b/timer.c',
                'libmad-0.15.1b/stream.c',
                'libmad-0.15.1b/frame.c',
                'libmad-0.15.1b/synth.c',
                'libmad-0.15.1b/decoder.c',
                'libmad-0.15.1b/layer12.c',
                'libmad-0.15.1b/layer3.c',
                'libmad-0.15.1b/huffman.c',
            ],
            use=['MAD', 'OHNET', 'OSA'],
            target='CodecMp3')

    # # Alac
    # bld.stlib(
             # source=[
                 # 'OpenHome/Media/Codec/Alac.cpp',
                 # 'alac_decoder/alac.cpp',
             # ],
             # use=['ALAC', 'OHNET'],
             # target='CodecAlac')

    # Tests
    bld.stlib(
            source=[
                'OpenHome/Av/Tests/RamStore.cpp',
                'OpenHome/Media/Tests/AllocatorInfoLogger.cpp',
                'OpenHome/Media/Tests/TestMsg.cpp',
                'OpenHome/Media/Tests/TestStarvationMonitor.cpp',
                'OpenHome/Media/Tests/TestStopper.cpp',
                'OpenHome/Media/Tests/TestSupply.cpp',
                'OpenHome/Media/Tests/TestAudioReservoir.cpp',
                'OpenHome/Media/Tests/TestVariableDelay.cpp',
                'OpenHome/Media/Tests/TestReporter.cpp',
                'OpenHome/Media/Tests/TestPreDriver.cpp',
                #'OpenHome/Media/Tests/TestContentProcessor.cpp',
                'OpenHome/Media/Tests/TestPipeline.cpp',
                # 'OpenHome/Media/Tests/TestProtocolHttp.cpp',
                'OpenHome/Media/Tests/TestCodec.cpp',
            ],
            use=['ohMediaPlayer', 'FLAC', 'CodecFlac', 'CodecWav'],
            target='ohMediaPlayerTestUtils')

    create_copy_task(
        bld,
        bld.path.ant_glob('dependencies/AnyPlatform/TestTones/*'),
        "")

    if not bld.env.nolink:
        bld.program(
                source='OpenHome/Media/Tests/TestShell.cpp',
                use=['OHNET', 'SHELL', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                target='TestShell')
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
                source='OpenHome/Media/Tests/TestSupplyMain.cpp',
                use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                target='TestSupply')
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
        #bld.program(
        #        source='OpenHome/Media/Tests/TestContentProcessorMain.cpp',
        #        use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
        #        target='TestContentProcessor')
        bld.program(
                source='OpenHome/Media/Tests/TestPipelineMain.cpp',
                use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                target='TestPipeline')
        bld.program(
                source='OpenHome/Media/Tests/TestProtocol.cpp',
                use=['OHNET', 'FLAC', 'ohMediaPlayer', 'CodecFlac', 'CodecWav', 'CodecMp3', 'ohMediaPlayerTestUtils'],
                target='TestProtocol')
        bld.program(
                source='OpenHome/Av/Tests/TestStore.cpp',
                use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                target='TestStore')
        # bld.program(
                # source='OpenHome/Media/Tests/TestProtocolHttpMain.cpp',
                # use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                # target='TestProtocolHttp')
        bld.program(
                source='OpenHome/Media/Tests/TestCodecMain.cpp',
                use=['OHNET', 'ohMediaPlayer', 'CodecWav', 'CodecFlac', 'CodecMp3', 'ohMediaPlayerTestUtils'],
                target='TestCodec')

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
                      ,['TestSupply', [], True]
                      ,['TestAudioReservoir', [], True]
                      ,['TestVariableDelay', [], True]
                      ,['TestStopper', [], True]
                      ,['TestReporter', [], True]
                      ,['TestStarvationMonitor', [], True]
                      ,['TestPreDriver', [], True]
                      #,['TestContentProcessor', [], True]
                      ,['TestPipeline', [], True]
                      ,['TestStore', [], True]
                      #,['TestProtocolHttp', [], True]
                      ,['TestCodec', [], True]
                      ]:
        tst(rule=invoke_test, test=t, args=a, always=when)
        tst.add_group() # Don't start another test until previous has finished.


# == Contexts to make 'waf test' work ==

from waflib.Build import BuildContext

class TestContext(BuildContext):
    cmd = 'test'
    fun = 'test'

# vim: set filetype=python softtabstop=4 expandtab shiftwidth=4 tabstop=4:
