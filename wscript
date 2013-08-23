#!/usr/bin/python

import sys
import os

from waflib.Node import Node

from wafmodules.filetasks import (
    find_resource_or_fail)

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
    opt.add_option('--testharness-dir', action='store', default=os.path.join('dependencies', 'AnyPlatform', 'testharness'))
    opt.add_option('--ohnet', action='store', default=None)
    opt.add_option('--debug', action='store_const', dest="debugmode", const="Debug", default="Release")
    opt.add_option('--release', action='store_const', dest="debugmode",  const="Release", default="Release")
    opt.add_option('--dest-platform', action='store', default=None)
    opt.add_option('--cross', action='store', default=None)

def configure(conf):

    def set_env(conf, varname, value):
        conf.msg(
                'Setting %s to' % varname,
                "True" if value is True else
                "False" if value is False else
                value)
        setattr(conf.env, varname, value)
        return value

    conf.msg("debugmode:", conf.options.debugmode)
    if conf.options.dest_platform is None:
        try:
            conf.options.dest_platform = guess_dest_platform()
        except KeyError:
            conf.fatal('Specify --dest-platform')

    configure_toolchain(conf)
    guess_ohnet_location(conf)

    conf.env.dest_platform = conf.options.dest_platform
    conf.env.testharness_dir = os.path.abspath(conf.options.testharness_dir)

    if conf.options.dest_platform.startswith('Windows'):
        conf.env.LIB_OHNET=['ws2_32', 'iphlpapi', 'dbghelp']
    conf.env.STLIB_OHNET=['TestFramework', 'ohNetCore']

    if conf.options.dest_platform in ['Core-ppc32', 'Core-armv6']:
        conf.env.append_value('DEFINES', ['DEFINE_TRACE', 'NETWORK_NTOHL_LOCAL', 'NOTERMIOS']) # Tell FLAC to use local ntohl implementation

    conf.env.INCLUDES = [
        '.',
        conf.path.find_node('.').abspath()
        ]

    mono = set_env(conf, 'MONO', [] if conf.options.dest_platform.startswith('Windows') else ["mono", "--debug", "--runtime=v4.0"])

    # Setup FLAC lib options 
    conf.env.DEFINES_FLAC = ['VERSION=\"1.2.1\"', 'FLAC__NO_DLL']
    conf.env.INCLUDES_FLAC = [
        'flac-1.2.1/src/libFLAC/include',
        'flac-1.2.1/include',
        'libogg-1.1.3/include',
        ]

    conf.env.STLIB_SHELL = ['Shell']
    
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

    # OpenSSL
    conf.env.STLIBPATH_OPENSSL = [
        os.path.join(conf.path.find_node('.').abspath(),
        os.path.join('dependencies', conf.options.dest_platform, 'openssl', 'lib')),
    ]
    if conf.options.dest_platform in ['Windows-x86', 'Windows-x64']:
        conf.env.STLIB_OPENSSL = ['eay32']
        conf.env.LIB_OPENSSL = ['advapi32', 'gdi32', 'user32']
    else:
        if conf.options.dest_platform in ['Linux-x86', 'Linux-x64', 'Linux-ppc32']:
            conf.env.LIB_OPENSSL = ['dl']
        conf.env.STLIB_OPENSSL = ['crypto']
    conf.env.INCLUDES_OPENSSL = [
        os.path.join('dependencies', conf.options.dest_platform, 'openssl', 'include'),
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

class GeneratedFile(object):
    def __init__(self, xml, domain, type, version, target):
        self.xml = xml
        self.domain = domain
        self.type = type
        self.version = version
        self.target = target

upnp_services = [
        GeneratedFile('OpenHome/Av/ServiceXml/Upnp/AVTransport1.xml', 'upnp.org', 'AVTransport', '1', 'UpnpOrgAVTransport1'),
        GeneratedFile('OpenHome/Av/ServiceXml/Upnp/ConnectionManager1.xml', 'upnp.org', 'ConnectionManager', '1', 'UpnpOrgConnectionManager1'),
        GeneratedFile('OpenHome/Av/ServiceXml/Upnp/RenderingControl1.xml', 'upnp.org', 'RenderingControl', '1', 'UpnpOrgRenderingControl1'),
        GeneratedFile('OpenHome/Av/ServiceXml/OpenHome/Product1.xml', 'av.openhome.org', 'Product', '1', 'AvOpenhomeOrgProduct1'),
        GeneratedFile('OpenHome/Av/ServiceXml/OpenHome/Radio1.xml', 'av.openhome.org', 'Radio', '1', 'AvOpenhomeOrgRadio1'),
        GeneratedFile('OpenHome/Av/ServiceXml/OpenHome/Sender1.xml', 'av.openhome.org', 'Sender', '1', 'AvOpenhomeOrgSender1'),
        GeneratedFile('OpenHome/Av/ServiceXml/OpenHome/Playlist1.xml', 'av.openhome.org', 'Playlist', '1', 'AvOpenhomeOrgPlaylist1'),
        GeneratedFile('OpenHome/Av/ServiceXml/OpenHome/Time1.xml', 'av.openhome.org', 'Time', '1', 'AvOpenhomeOrgTime1'),
        GeneratedFile('OpenHome/Av/ServiceXml/OpenHome/Info1.xml', 'av.openhome.org', 'Info', '1', 'AvOpenhomeOrgInfo1'),
        GeneratedFile('OpenHome/Av/ServiceXml/OpenHome/Volume1.xml', 'av.openhome.org', 'Volume', '1', 'AvOpenhomeOrgVolume1'),
    ]

def build(bld):

    # Generated provider base classes
    t4templatedir = bld.env['T4_TEMPLATE_PATH']
    text_transform_exe_node = find_resource_or_fail(bld, bld.root, os.path.join(bld.env['TEXT_TRANSFORM_PATH'], 'TextTransform.exe'))
    for service in upnp_services:
        for t4Template, prefix, ext, args in [
                ('DvUpnpCppCoreHeader.tt', 'Dv', '.h', '-a buffer:1'),
                ('DvUpnpCppCoreSource.tt', 'Dv', '.cpp', ''),
                ('CpUpnpCppHeader.tt', 'Cp', '.h', '-a buffer:1'),
                ('CpUpnpCppBufferSource.tt', 'Cp', '.cpp', '')
                ]:
            t4_template_node = find_resource_or_fail(bld, bld.root, os.path.join(t4templatedir, t4Template))
            tgt = bld.path.find_or_declare(os.path.join('Generated', prefix + service.target + ext))
            bld(
                rule="${MONO} " + text_transform_exe_node.abspath() + " -o " + tgt.abspath() + " " + t4_template_node.abspath() + " -a xml:../" + service.xml + " -a domain:" + service.domain + " -a type:" + service.type + " -a version:" + service.version + " " + args,
                source=[text_transform_exe_node, t4_template_node, service.xml],
                target=tgt
                )
    bld.add_group()

    # Library
    bld.stlib(
            source=[
                'OpenHome/Av/FaultCode.cpp',
                'OpenHome/Av/InfoProvider.cpp',
                'OpenHome/Av/KvpStore.cpp',
                'OpenHome/Av/ProviderUtils.cpp',
                'OpenHome/Av/Product.cpp',
                'Generated/DvAvOpenhomeOrgProduct1.cpp',
                'OpenHome/Av/ProviderProduct.cpp',
                'Generated/DvAvOpenhomeOrgTime1.cpp',
                'OpenHome/Av/ProviderTime.cpp',
                'Generated/DvAvOpenhomeOrgInfo1.cpp',
                'OpenHome/Av/ProviderInfo.cpp',
                'Generated/DvAvOpenhomeOrgVolume1.cpp',
                'OpenHome/Av/ProviderVolume.cpp',
                'OpenHome/Av/Source.cpp',
                'Generated/DvAvOpenhomeOrgSender1.cpp',
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
                'OpenHome/Media/Rewinder.cpp',
                'OpenHome/Media/Splitter.cpp',
                'OpenHome/Media/StarvationMonitor.cpp',
                'OpenHome/Media/Stopper.cpp',
                'OpenHome/Media/Supply.cpp',
                'OpenHome/Media/TrackInspector.cpp',
                'OpenHome/Media/VariableDelay.cpp',
                'OpenHome/Media/Pipeline.cpp',
                'OpenHome/Media/IdManager.cpp',
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
                'OpenHome/Media/Protocol/ProtocolTone.cpp',
                'OpenHome/Media/Protocol/RaopHeader.cpp',
                'OpenHome/Media/Protocol/Rtsp.cpp',
                'OpenHome/Media/Protocol/ProtocolRaop.cpp',
                'OpenHome/Media/Protocol/ProtocolRtsp.cpp',
                'OpenHome/Media/Protocol/ContentAudio.cpp',
                'OpenHome/Media/Protocol/ContentPls.cpp',
                'OpenHome/Media/Protocol/ContentM3u.cpp',
                'OpenHome/Media/Protocol/ContentOpml.cpp',
                'OpenHome/Media/Protocol/ContentAsx.cpp',
                'OpenHome/Media/UriProviderSingleTrack.cpp',
                'OpenHome/Media/PipelineManager.cpp',
                'OpenHome/Media/PipelineObserver.cpp',
                'OpenHome/Av/MediaPlayer.cpp',
                'OpenHome/Media/MuteManager.cpp',
                'OpenHome/Media/VolumeManager.cpp',
                'Generated/DvUpnpOrgAVTransport1.cpp',
                'OpenHome/Av/UpnpAv/ProviderAvTransport.cpp',
                'Generated/DvUpnpOrgConnectionManager1.cpp',
                'OpenHome/Av/UpnpAv/ProviderConnectionManager.cpp',
                'Generated/DvUpnpOrgRenderingControl1.cpp',
                'OpenHome/Av/UpnpAv/ProviderRenderingControl.cpp',
                'OpenHome/Av/UpnpAv/UpnpAv.cpp',
                'OpenHome/Av/Radio/SourceRadio.cpp',
                'OpenHome/Av/Radio/PresetDatabase.cpp',
                'OpenHome/Av/Radio/TuneIn.cpp',
                'Generated/DvAvOpenhomeOrgRadio1.cpp',
                'OpenHome/Av/Radio/ProviderRadio.cpp',
                'OpenHome/Av/Raop/Raop.cpp',
                'OpenHome/Av/Raop/SourceRaop.cpp',
                'OpenHome/Media/Tests/AllocatorInfoLogger.cpp', # needed here by MediaPlayer.  Should move back to tests lib
                'Generated/DvAvOpenhomeOrgPlaylist1.cpp',
                'OpenHome/Av/Playlist/ProviderPlaylist.cpp',
                'OpenHome/Av/Playlist/SourcePlaylist.cpp',
                'OpenHome/Av/Playlist/TrackDatabase.cpp',
                'OpenHome/Av/Playlist/UriProviderPlaylist.cpp',
            ],
            use=['OHNET', 'OPENSSL'],
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

    # AlacBase
    bld.stlib(
            source=[
                 'OpenHome/Media/Codec/AlacBase.cpp',
                 'alac_decoder/alac.c',
            ],
            use=['ALAC', 'OHNET', 'ohMediaPlayer'],
            target='CodecAlacBase')
    # Alac
    bld.stlib(
            source=[
                 'OpenHome/Media/Codec/Alac.cpp',
            ],
            use=['CodecAlacBase', 'OHNET'],
            target='CodecAlac')

    # Raop
    bld.stlib(
            source=[ # Does OpenHome/Media/Protocol/RaopHeader need to be used?
                 'OpenHome/Media/Codec/Raop.cpp',
            ],
            use=['CodecAlacBase', 'OHNET', 'OPENSSL'],
            target='CodecRaop')

    # AACBase
    bld.stlib(
            source=[
                'OpenHome/Media/Codec/AacBase.cpp',
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
            use=['AAC', 'OHNET', 'ohMediaPlayer'],
            target='CodecAacBase')

    # AAC
    bld.stlib(
            source=[
                 'OpenHome/Media/Codec/Aac.cpp',
            ],
            use=['CodecAacBase', 'OHNET'],
            target='CodecAac')

    # ADTS
    bld.stlib(
            source=[
                 'OpenHome/Media/Codec/Adts.cpp',
            ],
            use=['CodecAacBase', 'OHNET'],
            target='CodecAdts')

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

    # Tests
    bld.stlib(
            source=[
                'OpenHome/Av/Tests/TestStore.cpp',
                'OpenHome/Av/Tests/RamStore.cpp',
                #'OpenHome/Media/Tests/PipelineUtils.cpp',  #FIXME - to be deleted if no longer used
                'OpenHome/Media/Tests/SongcastingDriver.cpp',
                'OpenHome/Media/Tests/TestMsg.cpp',
                'OpenHome/Media/Tests/TestStarvationMonitor.cpp',
                #'OpenHome/Media/Tests/TestStopper.cpp',
                'OpenHome/Media/Tests/TestSupply.cpp',
                'OpenHome/Media/Tests/TestAudioReservoir.cpp',
                'OpenHome/Media/Tests/TestVariableDelay.cpp',
                'OpenHome/Media/Tests/TestTrackInspector.cpp',
                'OpenHome/Media/Tests/TestReporter.cpp',
                'OpenHome/Media/Tests/TestPreDriver.cpp',
                'OpenHome/Media/Tests/TestContentProcessor.cpp',
                'OpenHome/Media/Tests/TestPipeline.cpp',
                'OpenHome/Media/Tests/TestProtocol.cpp',
                'OpenHome/Media/Tests/TestProtocolHttp.cpp',
                'OpenHome/Media/Tests/TestCodec.cpp',
                'OpenHome/Media/Tests/TestCodecInit.cpp',
                'OpenHome/Media/Tests/TestIdProvider.cpp',
                'OpenHome/Media/Tests/TestFiller.cpp',
                'OpenHome/Media/Tests/TestToneGenerator.cpp',
                'OpenHome/Media/Tests/TestMuteManager.cpp',
                'OpenHome/Media/Tests/TestVolumeManager.cpp',
                'OpenHome/Media/Tests/TestRewinder.cpp',
                'OpenHome/Media/Tests/TestShell.cpp',
                'OpenHome/Av/Tests/TestUpnpErrors.cpp',
                'Generated/CpUpnpOrgAVTransport1.cpp',
                'Generated/CpUpnpOrgConnectionManager1.cpp',
                'Generated/CpUpnpOrgRenderingControl1.cpp',
                'OpenHome/Av/Tests/TestTrackDatabase.cpp',
                'OpenHome/Av/Tests/TestPlaylist.cpp',
                'Generated/CpAvOpenhomeOrgPlaylist1.cpp',
                'OpenHome/Av/Tests/TestMediaPlayer.cpp',
                'OpenHome/Av/Tests/TestMediaPlayerExec.cpp',
                'OpenHome/Av/Tests/TestRadio.cpp',
            ],
            use=['ohMediaPlayer', 'CodecFlac', 'CodecWav', 'CodecAlac', 'CodecAac', 'CodecAdts', 'CodecRaop', 'CodecVorbis'],
            target='ohMediaPlayerTestUtils')

    bld.program(
           source='OpenHome/Media/Tests/TestShellMain.cpp',
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
    #bld.program(
    #        source='OpenHome/Media/Tests/TestStopperMain.cpp',
    #        use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
    #        target='TestStopper')
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
            source='OpenHome/Media/Tests/TestProtocolMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestProtocol')
    #bld.program(
    #        source='OpenHome/Media/Tests/TestProtocolRaop.cpp',
    #        use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils', 'OPENSSL'],
    #        target='TestProtocolRaop')
    bld.program(
            source='OpenHome/Av/Tests/TestStoreMain.cpp',
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
    bld.program(
            source='OpenHome/Media/Tests/TestToneGeneratorMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestToneGenerator')
    bld.program(
            source='OpenHome/Media/Tests/TestMuteManagerMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestMuteManager')
    bld.program(
            source='OpenHome/Media/Tests/TestVolumeManagerMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestVolumeManager')
    bld.program(
            source='OpenHome/Media/Tests/TestRewinderMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestRewinder')
    #bld.program(
    #        source='OpenHome/Av/Tests/TestUpnpAv.cpp',
    #        use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
    #        target='TestUpnpAv')
    bld.program(
            source='OpenHome/Av/Tests/TestUpnpErrorsMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestUpnpErrors')
    bld.program(
            source='OpenHome/Av/Tests/TestTrackDatabaseMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestTrackDatabase')
    bld.program(
            source='OpenHome/Av/Tests/TestPlaylistMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestPlaylist')
    bld.program(
            source='OpenHome/Av/Tests/TestRadioMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestRadio')
    bld.program(
            source='OpenHome/Av/Tests/TestMediaPlayerMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils', 'OPENSSL'],
            target='TestMediaPlayer')

# Bundles
def bundle(ctx):
    print 'bundle binaries'
    header_files = gather_files(ctx, '{top}', ['OpenHome/**/*.h'])
    lib_names = ['ohMediaPlayer', 'ohMediaPlayerTestUtils', 'CodecAac', 'CodecAacBase', 'CodecAdts', 'CodecAlac', 'CodecAlacBase', 'CodecFlac', 'CodecRaop', 'CodecVorbis', 'CodecWav']
    lib_files = gather_files(ctx, '{bld}', (ctx.env.cxxstlib_PATTERN % x for x in lib_names))
    bundle_dev_files = build_tree({
        'ohMediaPlayer/lib' : lib_files,
        'ohMediaPlayer/include' : header_files
        })
    bundle_dev_files.create_tgz_task(ctx, 'ohMediaPlayer.tar.gz')

# == Command for invoking unit tests ==

def test(tst):
    rule = 'python {test} -m {manifest} -p {platform} -b {build_dir} -t {tool_dir}'.format(
        test        = os.path.join(tst.env.testharness_dir, 'Test'),
        manifest    = '${SRC}',
        platform    =  tst.env.dest_platform,
        build_dir   = '.',
        tool_dir    = os.path.join('..', 'dependencies', 'AnyPlatform'))
    tst(rule=rule, source='oncommit.test')

# == Contexts to make 'waf test' work ==

from waflib.Build import BuildContext

class TestContext(BuildContext):
    cmd = 'test'
    fun = 'test'

class BundleContext(BuildContext):
    cmd = 'bundle'
    fun = 'bundle'

# vim: set filetype=python softtabstop=4 expandtab shiftwidth=4 tabstop=4:
