#!/usr/bin/env python
"""TestRadioService - test Radio service operations

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - test mode 
              - all       execute all tests
              - fixed     check reporting of fixed data
              - presets   check setup/reporting of preset channels and ID lists
              - manual    check setup/reporting of manually configured channels
              
Suite of tests to check the operation of the Radio service. Checks all aspects
of this service EXCEPT actual playback of the radio channels (which is tested
in the TestRadioPlayback test script)

Relies on LinnEngRadio Icecast radio server at 10.2.8.201
""" 

# Uses the following TuneIn account for sourciing radio information. The presets
# contained have been selected to test all aspects of the radio functionality
# whilst working on the basis of only free codec support (so ohMediaPlayer can
# be tested 
#     - linn-test-presets-1 / password:klueso

import _FunctionalTest
import BaseTest                   as BASE
import Upnp.ControlPoints.Volkano as Volkano
import Utils.Common               as Common
import _SoftPlayer                as SoftPlayer
import sys
import time
import threading
import urllib
import xml.etree.ElementTree as ET

kTuneInUser       = 'linn-test-presets-1'
kTuneInUrl        = 'http://opml.radiotime.com/'
kTuneInPartner    = 'ah2rjr68'
kTuneInBrowseAll  = 'Browse.ashx?c=presets&formats=mp3,wma,aac,wmvideo,ogg'
kTuneInBrowseFree = 'Browse.ashx?c=presets&formats=aac,ogg'
kProtocolInfoAll  = 'http-get:*:audio/x-flac:*,'       +\
                    'http-get:*:audio/wav:*,'          +\
                    'http-get:*:audio/wave:*,'         +\
                    'http-get:*:audio/x-wav:*,'        +\
                    'http-get:*:audio/mpeg:*,'         +\
                    'http-get:*:audio/x-mpeg:*,'       +\
                    'http-get:*:audio/mp1:*,'          +\
                    'http-get:*:audio/aiff:*,'         +\
                    'http-get:*:audio/x-aiff:*,'       +\
                    'http-get:*:audio/x-m4a:*,'        +\
                    'http-get:*:audio/x-ms-wma:*,'     +\
                    'rtsp-rtp-udp:*:audio/x-ms-wma:*,' +\
                    'http-get:*:audio/x-scpls:*,'      +\
                    'http-get:*:audio/x-mpegurl:*,'    +\
                    'http-get:*:audio/x-ms-asf:*,'     +\
                    'http-get:*:audio/x-ms-wax:*,'     +\
                    'http-get:*:audio/x-ms-wvx:*,'     +\
                    'http-get:*:video/x-ms-asf:*,'     +\
                    'http-get:*:video/x-ms-wax:*,'     +\
                    'http-get:*:video/x-ms-wvx:*,'     +\
                    'http-get:*:text/xml:*,'           +\
                    'http-get:*:audio/aac:*,'          +\
                    'http-get:*:audio/aacp:*,'         +\
                    'http-get:*:audio/mp4:*,'          +\
                    'http-get:*:audio/ogg:*,'          +\
                    'http-get:*:audio/x-ogg:*,'        +\
                    'http-get:*:application/ogg:*'     +\
                    'tidalhifi.com:*:*:*'
kProtocolInfoFree = 'http-get:*:audio/x-flac:*,'       +\
                    'http-get:*:audio/wav:*,'          +\
                    'http-get:*:audio/wave:*,'         +\
                    'http-get:*:audio/x-wav:*,'        +\
                    'http-get:*:audio/aiff:*,'         +\
                    'http-get:*:audio/x-aiff:*,'       +\
                    'http-get:*:audio/x-m4a:*,'        +\
                    'http-get:*:audio/x-scpls:*,'      +\
                    'http-get:*:text/xml:*,'           +\
                    'http-get:*:audio/aac:*,'          +\
                    'http-get:*:audio/aacp:*,'         +\
                    'http-get:*:audio/mp4:*,'          +\
                    'http-get:*:audio/ogg:*,'          +\
                    'http-get:*:audio/x-ogg:*,'        +\
                    'http-get:*:application/ogg:*,'    +\
                    'tidalhifi.com:*:*:*,'

kChannelsMax      = 100
kLocalChannels    = [ # For the purposes of this test it doesn't matter if these work or not
                     {'uri' : 'http://10.2.8.201:8000/mp3-128k-stereo',
                      'meta': '<DIDL-Lite xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/" xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title>MP3 128k Stereo</dc:title><res>http://10.2.8.201:8000/mp3-128k-stereo</res><upnp:class>object.item.audioItem</upnp:class></item></DIDL-Lite>'},
                     {'uri' : 'http://10.2.8.201:8000/mp3-32k-mono',
                      'meta': '<DIDL-Lite xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/" xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title>MP3 32k Mono</dc:title><res>http://10.2.8.201:8000/mp3-32k-mono</res><upnp:class>object.item.audioItem</upnp:class></item></DIDL-Lite>'}]


# noinspection PyUnusedLocal
class TestRadioService( BASE.BaseTest ):
    
    def __init__( self ):
        """Constructor - initalise base class"""
        BASE.BaseTest.__init__( self )
        self.dut            = None
        self.soft           = None
        self.dutDev         = ''
        self.configUpdate   = threading.Event()
        self.presetsUpdate  = threading.Event()
        self.uriUpdated     = threading.Event()
        self.metaUpdated    = threading.Event()
        self.idArrayUpdated = threading.Event()
        
    def Test( self, aArgs ):
        """Test functionality of Radio service"""
        radioName = ''
        mode      = ''
        loopback  = False

        try:
            radioName = aArgs[1]
            mode      = aArgs[2].lower() 
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( aArgs )) )

        if mode not in ['all', 'fixed', 'presets', 'manual']:
            self.log.Abort( '', 'Invalid test mode:- %s' % mode )

        if radioName.lower() == 'local':
            loopback = True
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev', aTuneIn=kTuneInUser, aLoopback=loopback )
            radioName = self.soft.name
        self.dutDev = radioName.split( ':' )[0]
        self.dut = Volkano.VolkanoDevice( radioName, aIsDut=True, aLoopback=loopback )
        time.sleep( 3 )

        if mode in ['all','fixed']:
            self.TestFixedParams()
        if mode in ['all','presets']:
            self.TestPresets()
        if mode in ['all','manual']:
            self.TestManual()
        time.sleep( 3 )     # needed to ensure clean shutdown of SoftPlayer
            
    def Cleanup( self ):
        """Perform cleanup on test exit"""
        if self.dut:
            self.dut.Shutdown()
        if self.soft:
            self.soft.Shutdown()
        BASE.BaseTest.Cleanup( self )
        
    def TestFixedParams( self ):
        """Verify the 'fixed' parameter values are returned correctly"""
        self.log.Info( '' )
        self.log.Info( self.dutDev, 'Testing fixed parameters' )
        self.log.Info( '' )
        
        if self.soft:
            expProtocolInfo = kProtocolInfoFree
        else:
            expProtocolInfo = kProtocolInfoAll
            
        self.log.FailUnless( self.dutDev, self.dut.radio.polledProtocolInfo==expProtocolInfo,
            'Actual/Expected POLLED ProtocolInfo %s/%s' %
            (self.dut.radio.polledProtocolInfo,expProtocolInfo) )
        self.log.FailUnless( self.dutDev, self.dut.radio.protocolInfo==expProtocolInfo,
            'Actual/Expected EVENTED ProtocolInfo %s/%s' %
            (self.dut.radio.protocolInfo,expProtocolInfo) )
        self.log.FailUnless( self.dutDev, self.dut.radio.polledChannelsMax==kChannelsMax,
            'Actual/Expected POLLED ChannelsMax %s/%s' %
            (self.dut.radio.polledChannelsMax,kChannelsMax) )
        self.log.FailUnless( self.dutDev, self.dut.radio.channelsMax==kChannelsMax,
            'Actual/Expected EVENTED ChannelsMax %s/%s' %
            (self.dut.radio.channelsMax,kChannelsMax) )
    
    def TestPresets( self ):
        """Verify preset lists from TuneIn are handled correctly"""
        self.log.Info( '' )
        self.log.Info( self.dutDev, 'Testing handling of presets supplied by TuneIn' )
        self.log.Info( '' )
        
        dsPresets = self.dut.radio.AllChannels()
        rtPresets = self._GetTuneInPresets()

        for i in range( len( dsPresets )):
            if i >= len( rtPresets ):
                self.log.Fail( self.dutDev, '[%d] No TuneIn preset' % i )
            else:
                if dsPresets[i][0]:
                    dsUri = Common.GetUriFromDidl( dsPresets[i][1] )
                    dsTitle = Common.GetTitleFromDidl( dsPresets[i][1] ).decode( 'utf8 ' )
                    rtTitle = rtPresets[i][1]
                    
                    if 'notcompatible' not in rtPresets[i][0]:
                        # check URI only, not CGI params
                        self.log.FailUnless( self.dutDev, dsUri.split('&')[0]==rtPresets[i][0].split('&')[0],
                            '[%d] DS/TuneIn URI: %s %s' % (i,dsUri,rtPresets[i][0]) ) 
                        # titles can vary in genre, as stations with multiple genres seem to
                        # return one of the available genres, randomly selected, so subsequent
                        # identical queries MAY contain different genres in the station title.
                        # Hence ignore title string after '(' to ignore genre
                        self.log.FailUnless( self.dutDev, dsTitle.split('(')[0]==rtTitle.split('(')[0],
                            '[%d] DS/TuneIn Title:%s/%s' % (i,dsTitle,rtTitle) )
                else:
                    self.log.FailUnless( self.dutDev, rtPresets[i][0]=='',
                        '[%d] TuneIn URI for empty entry: %s' % (i,rtPresets[i][0]) ) 
                    self.log.FailUnless( self.dutDev, rtPresets[i][1]=='',
                        '[%d] TuneIn Title for empty entry: %s' % (i,rtPresets[i][1]) ) 
            
    def _GetTuneInPresets( self ):
        """Read preset channel info directly from TuneIn"""
        if self.soft:
            browse = kTuneInBrowseFree
        else:
            browse = kTuneInBrowseAll
        tiId   = '&username=%s&partnerId=%s' % (kTuneInUser, kTuneInPartner)
        resp = self._UrlQuery( kTuneInUrl + 'Preset.ashx?c=listFolders' + tiId )
        dflt = self._GetFromOpmlDefault( resp )
        resp = self._UrlQuery( kTuneInUrl + browse + tiId )
        uri  = self._GetFromOpmlUri( resp, dflt )
        if uri:
            resp = self._UrlQuery( uri )
        return self._GetPresetsFromOpml( resp )
        
    @staticmethod
    def _UrlQuery( aUrl ):
        """Perform query on specified URL, return response"""
        handle = urllib.urlopen( aUrl )
        resp = handle.read( 65535 )
        handle.close()
        return resp
    
    @staticmethod
    def _GetFromOpmlDefault( aOpml ):
        default = ''
        opml = ET.fromstring( aOpml )
        outlines = opml.getiterator( 'outline' )
        for outline in outlines:
            if outline.get( 'is_default' ):
                default = outline.get( 'text' )
                break
        return default
    
    @staticmethod
    def _GetFromOpmlUri( aOpml, aUri ):
        uri = ''
        opml = ET.fromstring( aOpml )
        outlines = opml.getiterator( 'outline' )
        for outline in outlines:
            if outline.get( 'text' ) == aUri:
                uri = outline.get( 'URL' )
                break
        return uri
    
    def _GetPresetsFromOpml( self, aOpml ):
        """Extract presets from RT OPML response to Browse"""
        preset  = []
        entries = self.dut.radio.channelsMax
        for i in range( entries ):
            preset.append( ('','') )
        opml = ET.fromstring( aOpml )
        outlines = opml.getiterator( 'outline' )
        for outline in outlines:
            if outline.get( 'is_preset' ):
                uri = outline.get( 'URL' )
                title = outline.get( 'text' )
                num = int( outline.get( 'preset_number' ))
                if num <= entries:
                    preset[num-1] = (uri, title)
        return preset
    
    def TestManual( self ):
        """Verify manually inserted radio channels"""
        
        def _RadioEvtCb( aService, aSvName, aSvVal, aSvSeq ):
            if aSvName == 'Uri':
                self.uriUpdated.set()
            elif aSvName == 'Metadata':
                self.metaUpdated.set()
            
        self.log.Info( '' )
        self.log.Info( self.dutDev, 'Testing setup and reporting of manual channels' )
        self.log.Info( '' )
        self.dut.radio.AddSubscriber( _RadioEvtCb )
        self.uriUpdated.clear()
        self.dut.radio.SetChannel( 'uri', 'meta' )
        self.uriUpdated.wait( 5 )
        
        for channel in kLocalChannels:
            self.uriUpdated.clear()
            self.metaUpdated.clear()
            self.dut.radio.SetChannel( channel['uri'], channel['meta'] )
            self.uriUpdated.wait( 3 )
            self.metaUpdated.wait( 1 )
            
            if not self.uriUpdated.isSet():
                self.log.Fail( self.dutDev, 'No URI event after channel manually updated' )
            if not self.metaUpdated.isSet():
                self.log.Fail( self.dutDev, 'No Metadata event after channel manually updated' )
            
            self.log.FailUnless( self.dutDev, self.dut.radio.uri==channel['uri'],
                'Actual/Expected EVENTED channel URI %s/%s' %
                (self.dut.radio.uri, channel['uri']) )
            self.log.FailUnless( self.dutDev, self.dut.radio.polledUri==channel['uri'],
                'Actual/Expected POLLED channel URI %s/%s' %
                (self.dut.radio.polledUri, channel['uri']) )
            self.log.FailUnless( self.dutDev, self.dut.radio.metadata==channel['meta'],
                'Actual/Expected EVENTED channel Metadata %s/%s' %
                (self.dut.radio.metadata, channel['meta']) )
            self.log.FailUnless( self.dutDev, self.dut.radio.polledMetadata==channel['meta'],
                'Actual/Expected POLLED channel Metadata %s/%s' %
                (self.dut.radio.polledMetadata, channel['meta']) )
            self.log.FailUnless( self.dutDev, self.dut.radio.id==0,
                'Actual/Expected EVENTED channel ID %d/0' % self.dut.radio.id )
            self.log.FailUnless( self.dutDev, self.dut.radio.polledId==0,
                'Actual/Expected POLLED channel ID %d/0' % self.dut.radio.polledId )
        self.dut.radio.RemoveSubscriber( _RadioEvtCb )
    

if __name__ == '__main__':
    
    BASE.Run( sys.argv )
