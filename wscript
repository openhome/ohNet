#!/usr/bin/python

import sys
import os
import shutil

from waflib.Node import Node

from wafmodules.filetasks import (
    find_resource_or_fail)

import os.path, sys
sys.path[0:0] = [os.path.join('dependencies', 'AnyPlatform', 'ohWafHelpers')]

from filetasks import gather_files, build_tree, copy_task
from utilfuncs import invoke_test, guess_dest_platform, configure_toolchain, guess_ohnet_location, guess_location, guess_libplatform_location, guess_libosa_location, is_core_platform

def options(opt):
    opt.load('msvc')
    opt.load('compiler_cxx')
    opt.load('compiler_c')
    opt.add_option('--ohnet-include-dir', action='store', default=None)
    opt.add_option('--ohnet-lib-dir', action='store', default=None)
    opt.add_option('--ohnetmon-include-dir', action='store', default=None)
    opt.add_option('--ohnetmon-lib-dir', action='store', default=None)
    opt.add_option('--testharness-dir', action='store', default=os.path.join('dependencies', 'AnyPlatform', 'testharness'))
    opt.add_option('--ohnet', action='store', default=None)
    opt.add_option('--ohnetmon', action='store', default=None)
    opt.add_option('--libplatform', action='store', default=None)
    opt.add_option('--libosa', action='store', default=None)
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

    if is_core_platform(conf):
        guess_libosa_location(conf)
        guess_libplatform_location(conf)

    configure_toolchain(conf)
    guess_ohnet_location(conf)
    guess_location(conf, 'ohNetmon')

    conf.env.dest_platform = conf.options.dest_platform
    conf.env.testharness_dir = os.path.abspath(conf.options.testharness_dir)

    if conf.options.dest_platform.startswith('Windows'):
        conf.env.LIB_OHNET=['ws2_32', 'iphlpapi', 'dbghelp']
    conf.env.STLIB_OHNET=['TestFramework', 'ohNetCore']

    if is_core_platform(conf):
        conf.env.prepend_value('STLIB_OHNET', ['target', 'platform'])
        conf.env.append_value('DEFINES', ['DEFINE_TRACE', 'NETWORK_NTOHL_LOCAL', 'NOTERMIOS']) # Tell FLAC to use local ntohl implementation

    conf.env.STLIB_OHNETMON = ['ohNetmon']

    conf.env.INCLUDES = [
        '.',
        conf.path.find_node('.').abspath()
        ]

    mono = set_env(conf, 'MONO', [] if conf.options.dest_platform.startswith('Windows') else ["mono", "--debug", "--runtime=v4.0"])

    # Setup FLAC lib options 
    conf.env.DEFINES_FLAC = ['VERSION=\"1.2.1\"', 'FLAC__NO_DLL', 'FLAC__HAS_OGG']
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
        conf.env.STLIB_OPENSSL = ['libeay32', 'ssleay32']
        conf.env.LIB_OPENSSL = ['advapi32', 'gdi32', 'user32']
    else:
        if conf.options.dest_platform in ['Linux-x86', 'Linux-x64', 'Linux-ppc32']:
            conf.env.LIB_OPENSSL = ['dl']
        conf.env.STLIB_OPENSSL = ['ssl', 'crypto']
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
        GeneratedFile('OpenHome/Av/ServiceXml/OpenHome/Receiver1.xml', 'av.openhome.org', 'Receiver', '1', 'AvOpenhomeOrgReceiver1'),
        GeneratedFile('OpenHome/Av/ServiceXml/OpenHome/Time1.xml', 'av.openhome.org', 'Time', '1', 'AvOpenhomeOrgTime1'),
        GeneratedFile('OpenHome/Av/ServiceXml/OpenHome/Info1.xml', 'av.openhome.org', 'Info', '1', 'AvOpenhomeOrgInfo1'),
        GeneratedFile('OpenHome/Av/ServiceXml/OpenHome/Volume1.xml', 'av.openhome.org', 'Volume', '1', 'AvOpenhomeOrgVolume1'),
        GeneratedFile('OpenHome/Av/ServiceXml/OpenHome/Configuration1.xml', 'av.openhome.org', 'Configuration', '1', 'AvOpenhomeOrgConfiguration1'),
        GeneratedFile('OpenHome/Av/ServiceXml/OpenHome/Credentials1.xml', 'av.openhome.org', 'Credentials', '1', 'AvOpenhomeOrgCredentials1'),
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
                'OpenHome/Media/InfoProvider.cpp',
                'OpenHome/Media/Pipeline/AudioReservoir.cpp',
                'OpenHome/Media/Pipeline/DecodedAudioAggregator.cpp',
                'OpenHome/Media/Pipeline/DecodedAudioReservoir.cpp',
                'OpenHome/Media/Pipeline/EncodedAudioReservoir.cpp',
                'OpenHome/Media/Pipeline/Gorger.cpp',
                'OpenHome/Media/Pipeline/Logger.cpp',
                'OpenHome/Media/Pipeline/Msg.cpp',
                'OpenHome/Media/Pipeline/PreDriver.cpp',
                'OpenHome/Media/Pipeline/Pruner.cpp',
                'OpenHome/Media/Pipeline/Ramper.cpp',
                'OpenHome/Media/Pipeline/Reporter.cpp',
                'OpenHome/Media/Pipeline/SampleReporter.cpp',
                'OpenHome/Media/Pipeline/Rewinder.cpp',
                'OpenHome/Media/Pipeline/Seeker.cpp',
                'OpenHome/Media/Pipeline/Skipper.cpp',
                'OpenHome/Media/Pipeline/Splitter.cpp',
                'OpenHome/Media/Pipeline/StarvationMonitor.cpp',
                'OpenHome/Media/Pipeline/Stopper.cpp',
                'OpenHome/Media/Pipeline/TimestampInspector.cpp',
                'OpenHome/Media/Pipeline/TrackInspector.cpp',
                'OpenHome/Media/Pipeline/VariableDelay.cpp',
                'OpenHome/Media/Pipeline/Waiter.cpp',
                'OpenHome/Media/Pipeline/Pipeline.cpp',
                'OpenHome/Media/IdManager.cpp',
                'OpenHome/Media/Filler.cpp',
                'OpenHome/Media/Supply.cpp',
                'OpenHome/Media/SupplyAggregator.cpp',
                'OpenHome/Media/Utils/DriverBasic.cpp',
                'OpenHome/Media/Utils/ProcessorPcmUtils.cpp',
                'OpenHome/Media/Codec/Mpeg4.cpp',
                'OpenHome/Media/Codec/Container.cpp',
                'OpenHome/Media/Codec/Id3v2.cpp',
                'OpenHome/Media/Codec/CodecController.cpp',
                'OpenHome/Media/Protocol/Protocol.cpp',
                'OpenHome/Media/Protocol/ProtocolHttp.cpp',
                'OpenHome/Media/Protocol/ProtocolHttps.cpp',
                'OpenHome/Media/Protocol/ProtocolFile.cpp',
                'OpenHome/Media/Protocol/ProtocolTone.cpp',
                'OpenHome/Media/Protocol/Rtsp.cpp',
                'OpenHome/Media/Protocol/ProtocolRtsp.cpp',
                'OpenHome/Media/Protocol/ContentAudio.cpp',
                'OpenHome/Media/UriProviderSingleTrack.cpp',
                'OpenHome/Media/PipelineManager.cpp',
                'OpenHome/Media/PipelineObserver.cpp',
                'OpenHome/Media/ClockPullerUtilisation.cpp',
                'OpenHome/Media/MuteManager.cpp',
                'OpenHome/Media/VolumeManager.cpp',
                'OpenHome/Media/Utils/AllocatorInfoLogger.cpp', # needed here by MediaPlayer.  Should move back to tests lib
                'OpenHome/Configuration/BufferPtrCmp.cpp',
                'OpenHome/Configuration/ConfigManager.cpp',
                'OpenHome/Media/Utils/Aggregator.cpp',
                'OpenHome/Media/Utils/Silencer.cpp',
                'OpenHome/Media/Utils/ClockPullerLogging.cpp',
                'OpenHome/SocketSsl.cpp',
            ],
            use=['OHNET', 'OPENSSL', 'OHNETMON'],
            target='ohPipeline')

    # Library
    bld.stlib(
            source=[
                'OpenHome/Av/FaultCode.cpp',
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
                'OpenHome/Av/ConfigInitialiserVolume.cpp',
                'OpenHome/Av/ProviderVolume.cpp',
                'OpenHome/Av/Source.cpp',
                'OpenHome/Av/MediaPlayer.cpp',
                'Generated/DvAvOpenhomeOrgConfiguration1.cpp',
                'OpenHome/Configuration/ProviderConfig.cpp',
                'OpenHome/PowerManager.cpp',
                'OpenHome/Av/Credentials.cpp',
                'Generated/DvAvOpenhomeOrgCredentials1.cpp',
                'OpenHome/Av/ProviderCredentials.cpp',
            ],
            use=['OHNET', 'OPENSSL', 'OHNETMON', 'ohPipeline'],
            target='ohMediaPlayer')

    # Library
    bld.stlib(
            source=[
                'Generated/DvAvOpenhomeOrgPlaylist1.cpp',
                'OpenHome/Av/Playlist/ProviderPlaylist.cpp',
                'OpenHome/Av/Playlist/SourcePlaylist.cpp',
                'OpenHome/Av/Playlist/TrackDatabase.cpp',
                'OpenHome/Av/Playlist/UriProviderPlaylist.cpp',
                'OpenHome/Av/Tidal/Tidal.cpp',
                'OpenHome/Av/Tidal/ProtocolTidal.cpp'
            ],
            use=['OHNET', 'ohMediaPlayer'],
            target='SourcePlaylist')

    # Library
    bld.stlib(
            source=[
                'OpenHome/Av/Radio/SourceRadio.cpp',
                'OpenHome/Av/Radio/PresetDatabase.cpp',
                'OpenHome/Av/Radio/TuneIn.cpp',
                'OpenHome/Av/Radio/ContentAsx.cpp',
                'OpenHome/Av/Radio/ContentM3u.cpp',
                'OpenHome/Av/Radio/ContentOpml.cpp',
                'OpenHome/Av/Radio/ContentPls.cpp',
                'Generated/DvAvOpenhomeOrgRadio1.cpp',
                'OpenHome/Av/Radio/ProviderRadio.cpp',
            ],
            use=['OHNET', 'ohMediaPlayer'],
            target='SourceRadio')

    # Library
    bld.stlib(
            source=[
                'Generated/DvAvOpenhomeOrgSender1.cpp',
                'OpenHome/Av/Songcast/Ohm.cpp',
                'OpenHome/Av/Songcast/OhmMsg.cpp',
                'OpenHome/Av/Songcast/OhmSender.cpp',
                'OpenHome/Av/Songcast/OhmSocket.cpp',
                'OpenHome/Av/Songcast/ProtocolOhBase.cpp',
                'OpenHome/Av/Songcast/ProtocolOhu.cpp',
                'OpenHome/Av/Songcast/ProtocolOhm.cpp',
                'OpenHome/Av/Songcast/CodecOhm.cpp',
                'OpenHome/Av/Songcast/OhmTimestamp.cpp',
                'Generated/DvAvOpenhomeOrgReceiver1.cpp',
                'OpenHome/Av/Songcast/ProviderReceiver.cpp',
                'OpenHome/Av/Songcast/ZoneHandler.cpp',
                'OpenHome/Av/Songcast/SourceReceiver.cpp',
                'OpenHome/Av/Songcast/Sender.cpp',
                'OpenHome/Av/Utils/DriverSongcastSender.cpp',
            ],
            use=['OHNET', 'ohMediaPlayer'],
            target='SourceSongcast')

    # Library
    bld.stlib(
            source=[
                'OpenHome/Av/Raop/Raop.cpp',
                'OpenHome/Av/Raop/SourceRaop.cpp',
                'OpenHome/Av/Raop/RaopHeader.cpp',
                'OpenHome/Av/Raop/ProtocolRaop.cpp',
                'OpenHome/Av/Raop/UdpServer.cpp',
                'OpenHome/Av/Raop/CodecRaop.cpp'
            ],
            use=['OHNET', 'OPENSSL', 'ohMediaPlayer', 'CodecAlacBase'],
            target='SourceRaop')

    # Library
    bld.stlib(
            source=[
                'Generated/DvUpnpOrgAVTransport1.cpp',
                'OpenHome/Av/UpnpAv/ProviderAvTransport.cpp',
                'Generated/DvUpnpOrgConnectionManager1.cpp',
                'OpenHome/Av/UpnpAv/ProviderConnectionManager.cpp',
                'Generated/DvUpnpOrgRenderingControl1.cpp',
                'OpenHome/Av/UpnpAv/ProviderRenderingControl.cpp',
                'OpenHome/Av/UpnpAv/UpnpAv.cpp',
                'OpenHome/Av/UpnpAv/UriProviderRepeater.cpp'
            ],
            use=['OHNET', 'ohMediaPlayer'],
            target='SourceUpnpAv')

    # Wav
    bld.stlib(
            source=['OpenHome/Media/Codec/Wav.cpp'],
            use=['OHNET'],
            target='CodecWav')

    # PCM
    bld.stlib(
            source=['OpenHome/Media/Codec/Pcm.cpp'],
            use=['OHNET'],
            target='CodecPcm')

    # AiffBase
    bld.stlib(
            source=['OpenHome/Media/Codec/AiffBase.cpp'],
            use=['OHNET'],
            target='CodecAiffBase')

    # AIFC
    bld.stlib(
            source=['OpenHome/Media/Codec/Aifc.cpp'],
            use=['CodecAiffBase', 'OHNET'],
            target='CodecAifc')

    # AIFF
    bld.stlib(
            source=['OpenHome/Media/Codec/Aiff.cpp'],
            use=['CodecAiffBase', 'OHNET'],
            target='CodecAiff')

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
            use=['FLAC', 'OHNET', 'libOgg'],
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
                'OpenHome/Media/Tests/VolumeUtils.cpp',
                #'OpenHome/Media/Tests/PipelineUtils.cpp',  #FIXME - to be deleted if no longer used
                'OpenHome/Media/Tests/TestMsg.cpp',
                'OpenHome/Media/Tests/TestStarvationMonitor.cpp',
                'OpenHome/Media/Tests/TestSeeker.cpp',
                'OpenHome/Media/Tests/TestSkipper.cpp',
                'OpenHome/Media/Tests/TestStopper.cpp',
                'OpenHome/Media/Tests/TestWaiter.cpp',
                'OpenHome/Media/Tests/TestSupply.cpp',
                'OpenHome/Media/Tests/TestSupplyAggregator.cpp',
                'OpenHome/Media/Tests/TestAudioReservoir.cpp',
                'OpenHome/Media/Tests/TestVariableDelay.cpp',
                'OpenHome/Media/Tests/TestTrackInspector.cpp',
                'OpenHome/Media/Tests/TestTimestampInspector.cpp',
                'OpenHome/Media/Tests/TestRamper.cpp',
                'OpenHome/Media/Tests/TestReporter.cpp',
                'OpenHome/Media/Tests/TestSampleReporter.cpp',
                'OpenHome/Media/Tests/TestPreDriver.cpp',
                'OpenHome/Media/Tests/TestGorger.cpp',
                'OpenHome/Media/Tests/TestPruner.cpp',
                'OpenHome/Av/Tests/TestContentProcessor.cpp',
                'OpenHome/Media/Tests/TestPipeline.cpp',
                #'OpenHome/Media/Tests/TestProtocol.cpp',
                'OpenHome/Media/Tests/TestProtocolHttp.cpp',
                'OpenHome/Media/Tests/TestCodec.cpp',
                'OpenHome/Media/Tests/TestCodecInit.cpp',
                'OpenHome/Media/Tests/TestCodecController.cpp',
                'OpenHome/Media/Tests/TestDecodedAudioAggregator.cpp',
                'OpenHome/Media/Tests/TestContainer.cpp',
                'OpenHome/Media/Tests/TestAggregator.cpp',
                'OpenHome/Media/Tests/TestSilencer.cpp',
                'OpenHome/Media/Tests/TestIdProvider.cpp',
                'OpenHome/Media/Tests/TestFiller.cpp',
                'OpenHome/Media/Tests/TestToneGenerator.cpp',
                'OpenHome/Media/Tests/TestMuteManager.cpp',
                'OpenHome/Media/Tests/TestVolumeManager.cpp',
                'OpenHome/Media/Tests/TestRewinder.cpp',
                'OpenHome/Media/Tests/TestShell.cpp',
                'OpenHome/Av/Tests/TestUdpServer.cpp',
                'OpenHome/Av/Tests/TestUpnpErrors.cpp',
                'Generated/CpUpnpOrgAVTransport1.cpp',
                'Generated/CpUpnpOrgConnectionManager1.cpp',
                'Generated/CpUpnpOrgRenderingControl1.cpp',
                'OpenHome/Av/Tests/TestTrackDatabase.cpp',
                'OpenHome/Av/Tests/TestPlaylist.cpp',
                'Generated/CpAvOpenhomeOrgPlaylist1.cpp',
                'OpenHome/Av/Tests/TestMediaPlayer.cpp',
                'OpenHome/Av/Tests/TestRadio.cpp',
                'OpenHome/Av/Tests/TestUriProviderRepeater.cpp',
                'OpenHome/Configuration/Tests/ConfigRamStore.cpp',
                'OpenHome/Configuration/Tests/TestConfigManager.cpp',
                'OpenHome/Tests/TestPowerManager.cpp',
                'OpenHome/Tests/TestSsl.cpp',
                'OpenHome/Av/Tests/TestCredentials.cpp',
                'Generated/CpAvOpenhomeOrgCredentials1.cpp',
            ],
            use=['ohMediaPlayer', 'CodecFlac', 'CodecWav', 'CodecPcm', 'CodecAlac', 'CodecAifc', 'CodecAiff', 'CodecAac', 'CodecAdts', 'CodecVorbis'],
            target='ohMediaPlayerTestUtils')

    bld.program(
            source='OpenHome/Media/Tests/TestShellMain.cpp',
            use=['OHNET', 'SHELL', 'ohMediaPlayer', 'ohMediaPlayerTestUtils', 'SourcePlaylist', 'SourceRadio', 'SourceRaop', 'SourceUpnpAv'],
            target='TestShell',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestMsgMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestMsg',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestStarvationMonitorMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestStarvationMonitor',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestSeekerMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestSeeker',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestSkipperMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestSkipper',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestStopperMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestStopper',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestWaiterMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestWaiter',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestSupplyMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestSupply',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestSupplyAggregatorMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestSupplyAggregator',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestAudioReservoirMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestAudioReservoir',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestVariableDelayMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestVariableDelay',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestTrackInspectorMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestTrackInspector',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestTimestampInspectorMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestTimestampInspector',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestRamperMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestRamper',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestReporterMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestReporter',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestSampleReporterMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestSampleReporter',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestPreDriverMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestPreDriver',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestGorgerMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestGorger',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestPrunerMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestPruner',
            install_path=None)
    bld.program(
            source='OpenHome/Av/Tests/TestContentProcessorMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils', 'SourceRadio'],
            target='TestContentProcessor',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestPipelineMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestPipeline',
            install_path=None)
    #bld.program(
    #        source='OpenHome/Media/Tests/TestProtocolMain.cpp',
    #        use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
    #        target='TestProtocol',
    #        install_path=None)
    bld.program(
            source='OpenHome/Av/Tests/TestStoreMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestStore',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestProtocolHttpMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestProtocolHttp',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestCodecMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestCodec',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestCodecControllerMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestCodecController',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestDecodedAudioAggregatorMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestDecodedAudioAggregator',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestContainerMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestContainer',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestAggregatorMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestAggregator',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestSilencerMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestSilencer',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestIdProviderMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestIdProvider',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestFillerMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestFiller',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestToneGeneratorMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestToneGenerator',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestMuteManagerMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestMuteManager',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestVolumeManagerMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestVolumeManager',
            install_path=None)
    bld.program(
            source='OpenHome/Media/Tests/TestRewinderMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestRewinder',
            install_path=None)
    bld.program(
            source='OpenHome/Av/Tests/TestUdpServerMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils', 'SourceRaop'],
            target='TestUdpServer',
            install_path=None)
    #bld.program(
    #        source='OpenHome/Av/Tests/TestUpnpAv.cpp',
    #        use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
    #        target='TestUpnpAv',
    #        install_path=None)
    bld.program(
            source='OpenHome/Av/Tests/TestUpnpErrorsMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils', 'SourceUpnpAv'],
            target='TestUpnpErrors',
            install_path=None)
    bld.program(
            source='OpenHome/Av/Tests/TestTrackDatabaseMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils', 'SourcePlaylist'],
            target='TestTrackDatabase',
            install_path=None)
    bld.program(
            source='OpenHome/Av/Tests/TestPlaylistMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils', 'SourcePlaylist'],
            target='TestPlaylist',
            install_path=None)
    bld.program(
            source='OpenHome/Av/Tests/TestRadioMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils', 'SourceRadio', 'SourceSongcast'],
            target='TestRadio',
            install_path=None)
    bld.program(
            source='OpenHome/Av/Tests/TestUriProviderRepeaterMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils', 'SourceUpnpAv'],
            target='TestUriProviderRepeater',
            install_path=None)
    bld.program(
            source='OpenHome/Av/Tests/TestMediaPlayerMain.cpp',
            use=['OHNET', 'SHELL', 'ohMediaPlayer', 'ohMediaPlayerTestUtils', 'SourcePlaylist', 'SourceRadio', 'SourceSongcast', 'SourceRaop', 'SourceUpnpAv', 'OPENSSL'],
            target='TestMediaPlayer',
            install_path='install/bin')
    bld.program(
            source='OpenHome/Configuration/Tests/TestConfigManagerMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestConfigManager',
            install_path=None)
    bld.program(
            source='OpenHome/Tests/TestPowerManagerMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils'],
            target='TestPowerManager',
            install_path=None)
    bld.program(
            source='OpenHome/Tests/TestSslMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils', 'OPENSSL'],
            target='TestSsl',
            install_path=None)
    bld.program(
            source='OpenHome/Av/Tests/TestCredentialsMain.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils', 'OPENSSL'],
            target='TestCredentials',
            install_path=None)
    bld.program(
            source='OpenHome/Tests/TestHttps.cpp',
            use=['OHNET', 'ohMediaPlayer', 'OPENSSL'],
            target='TestHttps',
            install_path=None)
    #bld.program(
    #        source='OpenHome/Tests/TestHttpsBsd.cpp',
    #        use=['OHNET', 'ohMediaPlayer', 'OPENSSL'],
    #        target='TestHttpsBsd',
    #        install_path=None)
    bld.program(
            source='OpenHome/Av/Tidal/TestTidal.cpp',
            use=['OHNET', 'ohMediaPlayer', 'ohMediaPlayerTestUtils', 'SourcePlaylist'],
            target='TestTidal',
            install_path=None)


# Bundles
def bundle(ctx):
    print 'bundle binaries'
    header_files = gather_files(ctx, '{top}', ['OpenHome/**/*.h'])
    lib_names = ['ohPipeline', 'ohMediaPlayer', 'ohMediaPlayerTestUtils', 'SourcePlaylist', 'SourceRadio', 'SourceSongcast', 'SourceRaop', 'SourceUpnpAv', 'CodecAac', 'CodecAacBase', 'CodecAdts', 'CodecAifc', 'CodecAiff', 'CodecAiffBase', 'CodecAlac', 'CodecAlacBase', 'CodecFlac', 'CodecVorbis', 'CodecWav', 'CodecPcm', 'libOgg']
    lib_files = gather_files(ctx, '{bld}', (ctx.env.cxxstlib_PATTERN % x for x in lib_names))
    bundle_dev_files = build_tree({
        'ohMediaPlayer/lib' : lib_files,
        'ohMediaPlayer/include' : header_files
        })
    bundle_dev_files.create_tgz_task(ctx, 'ohMediaPlayer.tar.gz')

# == Command for invoking unit tests ==

def test(tst):
    if not hasattr(tst, 'test_manifest'):
        tst.test_manifest = 'oncommit.test'
    if tst.env.dest_platform in ['Windows-x86', 'Windows-x64']:
        tst.executable_dep = 'TestShell.exe'
    else:
        tst.executable_dep = 'TestShell'
    print 'Testing using manifest:', tst.test_manifest
    rule = 'python {test} -m {manifest} -p {platform} -b {build_dir} -t {tool_dir}'.format(
        test        = os.path.join(tst.env.testharness_dir, 'Test'),
        manifest    = '${SRC}',
        platform    =  tst.env.dest_platform,
        build_dir   = '.',
        tool_dir    = os.path.join('..', 'dependencies', 'AnyPlatform'))
    tst(rule=rule, source=[tst.test_manifest, os.path.join('projectdata', 'dependencies.json'), tst.executable_dep])

def test_full(tst):
    tst.test_manifest = 'nightly.test'
    test(tst)

# == Contexts to make 'waf test' work ==

from waflib.Build import BuildContext

class TestContext(BuildContext):
    cmd = 'test'
    fun = 'test'

class TestContext(BuildContext):
    cmd = 'test_full'
    fun = 'test_full'

class BundleContext(BuildContext):
    cmd = 'bundle'
    fun = 'bundle'

# vim: set filetype=python softtabstop=4 expandtab shiftwidth=4 tabstop=4:
