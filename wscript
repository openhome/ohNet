#!/usr/bin/python

import sys
import os

from waflib.Node import Node

import os.path, sys
sys.path[0:0] = [os.path.join('dependencies', 'AnyPlatform', 'ohWafHelpers')]

from filetasks import gather_files, build_tree, copy_task
from utilfuncs import invoke_test, guess_dest_platform, configure_toolchain, guess_ohnet_location
from fileserver import invoke_test_fileserver

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
    
    # Setup ALAC lib options
    conf.env.INCLUDES_ALAC = [
        'alac_decoder',
        ]

    # Setup AAC lib options
    if conf.options.dest_platform in ['Windows-x86', 'Windows-x64']:
        conf.env.DEFINES_AAC = ['WIN32', 'MONO_ONLY', 'LP_SBR_ONLY']
    else:
        conf.env.DEFINES_AAC = ['linux', 'i386', 'MONO_ONLY', 'LP_SBR_ONLY']
    conf.env.INCLUDES_AAC = [
        'ETSI_aacPlusdec/src',
        'ETSI_aacPlusdec/etsiop_aacdec',
        'ETSI_aacPlusdec/etsiop_aacdec/src',
        'ETSI_aacPlusdec/etsiop_bitbuf',
        'ETSI_aacPlusdec/etsiop_ffrlib',
        'ETSI_aacPlusdec/etsiop_sbrdec',
        'ETSI_aacPlusdec/etsiop_sbrdec/src',
        'ETSI_aacPlusdec/etsioplib',
        ]

    # Setup Vorbis lib options
    conf.env.INCLUDES_VORBIS = [
        'Tremor',
        ]

    # Setup WMA lib options
    conf.env.DEFINES_WMA = [
        'WMAAPI_NO_DRM',
        'WMAAPI_NO_DRM_STREAM',
        'INCLUDE_BASEPLUS',
        'BUILD_WMASTD',
        'BUILD_WMAPRO',
        'BUILD_WMAPRO_PLLM',
        'BUILD_WMALSL',
        'ENABLE_ALL_ENCOPT',
        'ENABLE_LPC',
        'BUILD_INTEGER',
        'DISABLE_UES',
        'WMA_DECPK_BUILD',
        ]
    if conf.options.dest_platform not in ['Windows-x86', 'Windows-x64']:
        conf.env.DEFINES_WMA.append('__stdcall')
        conf.env.DEFINES_WMA.append('OPENHOME')
        if conf.options.debugmode == 'Debug':
            conf.env.CFLAGS_WMA = ['-O1', '-finline-functions']
    if conf.options.dest_platform in ['Core-ppc32']:
        conf.env.DEFINES_WMA.append('__powerpc__')
    conf.env.INCLUDES_WMA = [
        'WMA10Dec/audio/wmaudio/v10/decoder',
        'WMA10Dec/audio/wmaudio/v10/include',
        'WMA10Dec/audio/wmaudio/v10/common',
        'WMA10Dec/audio/wmaudio/v10/asfparse_s',
        'WMA10Dec/audio/wmaudio/v10/win32',
        'WMA10Dec/audio/common/include',
        'WMA10Dec/common/include',
        'WMA10Dec/common/cpudetect',
        'WMA10Dec/common/logging',
        ]
    if conf.options.dest_platform in ['Windows-x86', 'Windows-x64']:
        conf.env.LIB_WMA=['advapi32', 'user32']

def get_node(bld, node_or_filename):
    if isinstance(node_or_filename, Node):
        return node_or_filename
    return bld.path.find_node(node_or_filename)

def create_copy_task(build_context, files, target_dir='', cwd=None, keep_relative_paths=False, name=None):
    source_file_nodes = [get_node(build_context, f) for f in files]
    if keep_relative_paths:
        cwd_node = build_context.path.find_dir(cwd)
        target_filenames = [
                os.path.join(target_dir, source_node.path_from(cwd_node))
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
                'OpenHome/Media/TrackInspector.cpp',
                'OpenHome/Media/VariableDelay.cpp',
                'OpenHome/Media/Pipeline.cpp',
                'OpenHome/Media/IdProvider.cpp',
                'OpenHome/Media/Filler.cpp',
                'OpenHome/Media/DriverSongcastSender.cpp',
                'OpenHome/Media/ProcessorPcmUtils.cpp',
                'OpenHome/Media/Codec/Mpeg4.cpp',
                'OpenHome/Media/Codec/Container.cpp',
                'OpenHome/Media/Codec/Id3v2.cpp',
                'OpenHome/Media/Codec/CodecController.cpp',
                'OpenHome/Media/Protocol/Protocol.cpp',
                'OpenHome/Media/Protocol/ProtocolHttp.cpp',
                'OpenHome/Media/Protocol/ProtocolFile.cpp',
                'OpenHome/Media/Protocol/ContentAudio.cpp',
                'OpenHome/Media/Protocol/ContentPls.cpp',
                'OpenHome/Media/Protocol/ContentM3u.cpp',
                'OpenHome/Media/UriProviderSingleTrack.cpp',
                'OpenHome/Media/PipelineManager.cpp',
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

    # Alac
    bld.stlib(
            source=[
                 'OpenHome/Media/Codec/Alac.cpp',
                 'alac_decoder/alac.cpp',
            ],
            use=['ALAC', 'OHNET'],
            target='CodecAlac')

    # AAC
    bld.stlib(
            source=[
                'OpenHome/Media/Codec/Aac.cpp',
                'ETSI_aacPlusdec/etsiop_aacdec/src/aacdecoder.c',
                'ETSI_aacPlusdec/etsiop_aacdec/src/shortblock.c',
                'ETSI_aacPlusdec/etsiop_aacdec/src/longblock.c',

                'ETSI_aacPlusdec/etsiop_aacdec/src/aac_ram.c',
                'ETSI_aacPlusdec/etsiop_aacdec/src/aac_rom.c',
                'ETSI_aacPlusdec/etsiop_aacdec/src/bitstream.c',
                'ETSI_aacPlusdec/etsiop_aacdec/src/block.c',
                'ETSI_aacPlusdec/etsiop_aacdec/src/channel.c',
                'ETSI_aacPlusdec/etsiop_aacdec/src/channelinfo.c',
                'ETSI_aacPlusdec/etsiop_aacdec/src/conceal.c',
                'ETSI_aacPlusdec/etsiop_aacdec/src/datastream.c',
                'ETSI_aacPlusdec/etsiop_aacdec/src/imdct.c',
                'ETSI_aacPlusdec/etsiop_aacdec/src/pns.c',
                'ETSI_aacPlusdec/etsiop_aacdec/src/pulsedata.c',
                'ETSI_aacPlusdec/etsiop_aacdec/src/stereo.c',
                'ETSI_aacPlusdec/etsiop_aacdec/src/streaminfo.c',
                'ETSI_aacPlusdec/etsiop_aacdec/src/tns.c',

                'ETSI_aacPlusdec/etsiop_bitbuf/src/bitbuffer.c',

                'ETSI_aacPlusdec/etsiop_ffrlib/src/dsp_fft32x32s.c',
                'ETSI_aacPlusdec/etsiop_ffrlib/src/intrinsics-native.c',
                'ETSI_aacPlusdec/etsiop_ffrlib/src/transcendent.c',
                'ETSI_aacPlusdec/etsiop_ffrlib/src/transcendent_enc.c',
                'ETSI_aacPlusdec/etsiop_ffrlib/src/vector.c',

                'ETSI_aacPlusdec/etsiop_sbrdec/src/aacpluscheck.c',
                'ETSI_aacPlusdec/etsiop_sbrdec/src/env_calc.c',
                'ETSI_aacPlusdec/etsiop_sbrdec/src/env_dec.c',
                'ETSI_aacPlusdec/etsiop_sbrdec/src/env_extr.c',
                'ETSI_aacPlusdec/etsiop_sbrdec/src/freq_sca.c',
                'ETSI_aacPlusdec/etsiop_sbrdec/src/hybrid.c',
                'ETSI_aacPlusdec/etsiop_sbrdec/src/lpp_tran.c',
                'ETSI_aacPlusdec/etsiop_sbrdec/src/ps_bitdec.c',
                'ETSI_aacPlusdec/etsiop_sbrdec/src/ps_dec.c',
                'ETSI_aacPlusdec/etsiop_sbrdec/src/qmf_dec.c',
                'ETSI_aacPlusdec/etsiop_sbrdec/src/sbr_crc.c',
                'ETSI_aacPlusdec/etsiop_sbrdec/src/sbr_dec.c',
                'ETSI_aacPlusdec/etsiop_sbrdec/src/sbr_ram.c',
                'ETSI_aacPlusdec/etsiop_sbrdec/src/sbr_rom.c',
                'ETSI_aacPlusdec/etsiop_sbrdec/src/sbrdecoder.c',

                'ETSI_aacPlusdec/etsioplib/basicop2.c',
                'ETSI_aacPlusdec/etsioplib/count.c',
                'ETSI_aacPlusdec/etsioplib/oper_32b.c',

                'ETSI_aacPlusdec/src/spline_resampler.c',
            ],
            use=['AAC', 'OHNET'],
            target='CodecAac')

    # Vorbis
    bld.stlib(
            source=[
                'OpenHome/Media/Codec/Vorbis.cpp',
                'Tremor/mdct.c',
                'Tremor/block.c',
                'Tremor/window.c',
                'Tremor/synthesis.c',
                'Tremor/info.c',
                'Tremor/floor1.c',
                'Tremor/floor0.c',
                'Tremor/vorbisfile.c',
                'Tremor/res012.c',
                'Tremor/mapping0.c',
                'Tremor/registry.c',
                'Tremor/codebook.c',
                'Tremor/sharedbook.c',
                'Tremor/framing.c',
                'Tremor/bitwise.c',
            ],
            use=['VORBIS', 'OHNET'],
            target='CodecVorbis')

        # WMA
    bld.stlib(
             source=[
                 'OpenHome/Media/Codec/Wma.cpp',
                 'WMA10Dec/audio/wmaudio/v10/asfparse_s/wmaudio.c',
                 'WMA10Dec/audio/wmaudio/v10/asfparse_s/wmaudio_parse.c',
                 'WMA10Dec/audio/wmaudio/v10/asfparse_s/wmaudio_audec.c',
                 'WMA10Dec/audio/common/primitive/wmapcmacc.c',
                 'WMA10Dec/audio/common/primitive/wmamalloc.c',
                 'WMA10Dec/audio/wmaudio/v10/common/chexpro.c',
                 'WMA10Dec/audio/wmaudio/v10/common/msaudio.c',
                 'WMA10Dec/audio/wmaudio/v10/common/fex.c',
                 'WMA10Dec/audio/wmaudio/v10/common/fft.c',
                 'WMA10Dec/audio/wmaudio/v10/common/dectablespro.c',
                 'WMA10Dec/audio/wmaudio/v10/common/dectablesstdpro.c',
                 'WMA10Dec/audio/wmaudio/v10/common/lpcprolsl.c',
                 'WMA10Dec/audio/wmaudio/v10/common/lowrate_commonstd.c',
                 'WMA10Dec/audio/wmaudio/v10/common/msaudiopro.c',
                 'WMA10Dec/audio/wmaudio/v10/common/drccommonpro.c',
                 'WMA10Dec/audio/wmaudio/v10/common/AutoProfile.c',
                 'WMA10Dec/audio/wmaudio/v10/common/lpcstd.c',
                 'WMA10Dec/audio/wmaudio/v10/common/dectables.c',
                 'WMA10Dec/audio/wmaudio/v10/common/lowrate_common.c',
                 'WMA10Dec/audio/wmaudio/v10/common/msaudioprotemplate.c',
                 'WMA10Dec/audio/wmaudio/v10/common/configcommon.c',
                 'WMA10Dec/audio/wmaudio/v10/common/msaudiostd.c',
                 'WMA10Dec/audio/wmaudio/v10/common/dectablesstd.c',
                 'WMA10Dec/audio/wmaudio/v10/common/msaudiostdpro.c',
                 'WMA10Dec/audio/wmaudio/v10/common/msaudiotemplate.c',
                 'WMA10Dec/audio/wmaudio/v10/common/downmix.c',
                 'WMA10Dec/audio/wmaudio/v10/common/lpclsl.c',
                 'WMA10Dec/audio/wmaudio/v10/common/lpc.c',
                 'WMA10Dec/audio/wmaudio/v10/common/msaudiolsl.c',
                 'WMA10Dec/audio/wmaudio/v10/common/float.c',

                 'WMA10Dec/audio/common/chanmtx/wmaltrt.c',
                 'WMA10Dec/audio/common/chanmtx/wmachmtx.c',
                 'WMA10Dec/audio/common/chanmtx/wmabuffilt.c',
                 'WMA10Dec/audio/common/pcmfmt/pcmfmt.c',
                 'WMA10Dec/audio/common/primitive/wmaerror.c',

                 'WMA10Dec/audio/wmaudio/v10/fmthlpr/wmafmt.c',

                 'WMA10Dec/audio/wmaudio/v10/decoder/wmaprodecS_api.c',
                 'WMA10Dec/audio/wmaudio/v10/decoder/losslessdecpro.c',
                 'WMA10Dec/audio/wmaudio/v10/decoder/entropydecpro.c',
                 'WMA10Dec/audio/wmaudio/v10/decoder/entropydecprolsl.c',
                 'WMA10Dec/audio/wmaudio/v10/decoder/entropydecstd.c',
                 'WMA10Dec/audio/wmaudio/v10/decoder/fexdec.c',
                 'WMA10Dec/audio/wmaudio/v10/decoder/huffdec.c',
                 'WMA10Dec/audio/wmaudio/v10/decoder/losslessdeclsl.c',
                 'WMA10Dec/audio/wmaudio/v10/decoder/losslessdecprolsl.c',
                 'WMA10Dec/audio/wmaudio/v10/decoder/msaudiodec.c',
                 'WMA10Dec/audio/wmaudio/v10/decoder/strmdec_wma.c',
                 'WMA10Dec/audio/wmaudio/v10/decoder/baseplusdecpro.c',
                 'WMA10Dec/audio/wmaudio/v10/decoder/chexdecpro.c',
                 'WMA10Dec/audio/wmaudio/v10/decoder/entropydec.c',

                 'WMA10Dec/audio/wmaudio/v10/win32/decoder/win32.c',
                 'WMA10Dec/common/cpudetect/cpudetect.c',
           ],
           use=['WMA', 'OHNET', 'advapi32.lib'],
           target='CodecWma',
           )

    # Tests
    bld.stlib(
            source=[
                'OpenHome/Av/Tests/RamStore.cpp',
                'OpenHome/Media/Tests/AllocatorInfoLogger.cpp',
                'OpenHome/Media/Tests/PipelineUtils.cpp',
                'OpenHome/Media/Tests/SuiteUnitTest.cpp',
                'OpenHome/Media/Tests/TestMsg.cpp',
                'OpenHome/Media/Tests/TestStarvationMonitor.cpp',
                'OpenHome/Media/Tests/TestStopper.cpp',
                'OpenHome/Media/Tests/TestSupply.cpp',
                'OpenHome/Media/Tests/TestAudioReservoir.cpp',
                'OpenHome/Media/Tests/TestVariableDelay.cpp',
                'OpenHome/Media/Tests/TestTrackInspector.cpp',
                'OpenHome/Media/Tests/TestReporter.cpp',
                'OpenHome/Media/Tests/TestPreDriver.cpp',
                'OpenHome/Media/Tests/TestContentProcessor.cpp',
                'OpenHome/Media/Tests/TestPipeline.cpp',
                'OpenHome/Media/Tests/TestProtocolHttp.cpp',
                'OpenHome/Media/Tests/TestCodec.cpp',
                'OpenHome/Media/Tests/TestIdProvider.cpp',
                'OpenHome/Media/Tests/TestFiller.cpp',
            ],
            use=['ohMediaPlayer', 'CodecFlac', 'CodecWav', 'CodecMp3', 'CodecAlac', 'CodecAac', 'CodecVorbis', 'CodecWma'],
            target='ohMediaPlayerTestUtils')

    # Copy CherryPy to build dir
    create_copy_task(
        bld,
        bld.path.ant_glob('dependencies/AnyPlatform/CherryPy/cherrypy/**/*'),
        'cherrypy',
        cwd='dependencies/AnyPlatform/CherryPy/cherrypy',
        keep_relative_paths=True,
        name=None)
    create_copy_task(
        bld,
        bld.path.ant_glob('fileserver.py'),
        '')
    
    # Copy files for codec tests.
    create_copy_task(
        bld,
        bld.path.ant_glob('dependencies/AnyPlatform/TestTones/*'),
        '')

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
                source='OpenHome/Media/Tests/TestTrackInspectorMain.cpp',
                use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                target='TestTrackInspector')
        bld.program(
                source='OpenHome/Media/Tests/TestReporterMain.cpp',
                use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                target='TestReporter')
        bld.program(
                source='OpenHome/Media/Tests/TestPreDriverMain.cpp',
                use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                target='TestPreDriver')
        bld.program(
                source='OpenHome/Media/Tests/TestContentProcessorMain.cpp',
                use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                target='TestContentProcessor')
        bld.program(
                source='OpenHome/Media/Tests/TestPipelineMain.cpp',
                use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                target='TestPipeline')
        bld.program(
                source='OpenHome/Media/Tests/TestProtocol.cpp',
                use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                target='TestProtocol')
        bld.program(
                source='OpenHome/Av/Tests/TestStore.cpp',
                use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                target='TestStore')
        bld.program(
                source='OpenHome/Media/Tests/TestProtocolHttpMain.cpp',
                use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                target='TestProtocolHttp')
        bld.program(
                source='OpenHome/Media/Tests/TestCodecMain.cpp',
                use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                target='TestCodec')
        bld.program(
                source='OpenHome/Media/Tests/TestIdProviderMain.cpp',
                use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                target='TestIdProvider')
        bld.program(
                source='OpenHome/Media/Tests/TestFillerMain.cpp',
                use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
                target='TestFiller')

# Bundles
def bundle(ctx):
    print 'bundle binaries'
    header_files = gather_files(ctx, '{top}', ['OpenHome/**/*.h'])
    lib_names = ['ohMediaPlayer', 'ohMediaPlayerTestUtils', 'CodecAac', 'CodecAlac', 'CodecFlac', 'CodecMp3', 'CodecVorbis', 'CodecWav', 'CodecWma']
    lib_files = gather_files(ctx, '{bld}', (ctx.env.cxxstlib_PATTERN % x for x in lib_names))
    bundle_dev_files = build_tree({
        'ohMediaPlayer/lib' : lib_files,
        'ohMediaPlayer/include' : header_files
        })
    bundle_dev_files.create_tgz_task(ctx, 'ohMediaPlayer.tar.gz')

# == Command for invoking unit tests ==

def test(tst):
    for t, a, when in [['TestStore', [], True]
                      ,['TestMsg', [], True]
                      ,['TestSupply', [], True]
                      ,['TestAudioReservoir', [], True]
                      ,['TestVariableDelay', [], True]
                      ,['TestStopper', [], True]
                      ,['TestTrackInspector', [], True]
                      ,['TestReporter', [], True]
                      ,['TestStarvationMonitor', [], True]
                      ,['TestPreDriver', [], True]
                      ,['TestContentProcessor', [], True]
                      ,['TestPipeline', [], True]
                      ,['TestProtocolHttp', [], True]
                      #,['TestCodec', [], True]
                      ,['TestIdProvider', [], True]
                      ,['TestFiller', [], True]
                      ]:
        tst(rule=invoke_test, test=t, args=a, always=when)
        tst.add_group() # Don't start another test until previous has finished.
    tst(rule=invoke_test_fileserver, test='TestCodec', args=['127.0.0.1', '8080'], always=True)
    tst.add_group()

# == Contexts to make 'waf test' work ==

from waflib.Build import BuildContext

class TestContext(BuildContext):
    cmd = 'test'
    fun = 'test'

class BundleContext(BuildContext):
    cmd = 'bundle'
    fun = 'bundle'

# vim: set filetype=python softtabstop=4 expandtab shiftwidth=4 tabstop=4:
