#!/usr/bin/env python
"""TestRadioService - test Radio service operations

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - test mode 
              - all       execute all tests
              - fixed     check reporting of fixed data
              - presets   check setup/reporting of preset channels and ID lists
              - manual    check setup/reporting of manually configured channels
              - updated   for update of Radiotime preset list

Suite of tests to check the operation of the Radio service. Checks all aspects
of this service EXCEPT actual playback of the radio channels (which is tested
in the TestRadioPlayback test script)
"""
import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.OhMediaPlayer as OHMP
import Utils.Common                     as Common
import _SoftPlayer                      as SoftPlayer
import sys
import time
import threading
import urllib
import xml.etree.ElementTree as ET

kTuneInCreds      = 'tunein.com'
kTuneInUrl        = 'http://opml.radiotime.com/'
kTuneInBrowseAll  = 'Browse.ashx?c=presets&formats=mp3,wma,aac,wmvideo,ogg,hls'
kTuneInBrowseFree = 'Browse.ashx?c=presets&formats=aac,ogg,hls'
kProtocolInfoAll  = 'http-get:*:audio/x-flac:*,'         +\
                    'http-get:*:audio/wav:*,'            +\
                    'http-get:*:audio/wave:*,'           +\
                    'http-get:*:audio/x-wav:*,'          +\
                    'http-get:*:audio/mpeg:*,'           +\
                    'http-get:*:audio/x-mpeg:*,'         +\
                    'http-get:*:audio/mp1:*,'            +\
                    'http-get:*:audio/aiff:*,'           +\
                    'http-get:*:audio/x-aiff:*,'         +\
                    'http-get:*:audio/x-m4a:*,'          +\
                    'http-get:*:audio/x-ms-wma:*,'       +\
                    'rtsp-rtp-udp:*:audio/x-ms-wma:*,'   +\
                    'http-get:*:audio/x-scpls:*,'        +\
                    'http-get:*:audio/x-mpegurl:*,'      +\
                    'http-get:*:audio/x-ms-asf:*,'       +\
                    'http-get:*:audio/x-ms-wax:*,'       +\
                    'http-get:*:audio/x-ms-wvx:*,'       +\
                    'http-get:*:video/x-ms-asf:*,'       +\
                    'http-get:*:video/x-ms-wax:*,'       +\
                    'http-get:*:video/x-ms-wvx:*,'       +\
                    'http-get:*:text/xml:*,'             +\
                    'http-get:*:audio/aac:*,'            +\
                    'http-get:*:audio/aacp:*,'           +\
                    'http-get:*:audio/mp4:*,'            +\
                    'http-get:*:audio/ogg:*,'            +\
                    'http-get:*:audio/x-ogg:*,'          +\
                    'http-get:*:application/ogg:*,'      +\
                    'tidalhifi.com:*:*:*,'               +\
                    'qobuz.com:*:*:*'
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
                    'tidalhifi.com:*:*:*,'               +\
                    'qobuz.com:*:*:*'
kChannelsMax      = 100
kManualChannels   = [ # For the purposes of this test it doesn't matter if these work or not
                     {'uri' : 'http://192.168.10.201:8000/mp3-128k-stereo',
                      'meta': '<DIDL-Lite xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/" xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title>MP3 128k Stereo</dc:title><res>http://10.2.8.201:8000/mp3-128k-stereo</res><upnp:class>object.item.audioItem</upnp:class></item></DIDL-Lite>'},
                     {'uri' : 'http://192.168.10.201:8000/mp3-32k-mono',
                      'meta': '<DIDL-Lite xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/" xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"><item><dc:title>MP3 32k Mono</dc:title><res>http://10.2.8.201:8000/mp3-32k-mono</res><upnp:class>object.item.audioItem</upnp:class></item></DIDL-Lite>'}]


def Run( aArgs ):
    """Pass the Run() call from derived tests up to the base class"""
    BASE.Run( aArgs )


class TestRadioService( BASE.BaseTest ):
    
    def __init__( self ):
        """Constructor - initalise base class"""
        BASE.BaseTest.__init__( self )
        self.doc    = __doc__
        self.dut    = None
        self.soft   = None
        self.dutDev = ''

    def Test( self, aArgs ):
        """Test functionality of Radio service"""
        radioName = ''
        mode      = ''
        loopback  = False

        try:
            radioName = aArgs[1]
            mode      = aArgs[2].lower() 
        except:
            print '\n', self.doc, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( aArgs )) )

        if mode not in ['all', 'fixed', 'presets', 'manual', 'updated']:
            self.log.Abort( '', 'Invalid test mode:- %s' % mode )

        if radioName.lower() == 'local':
            loopback = True
            tuneinId = self.config.Get( 'tunein.partnerid' )
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev', aLoopback=loopback )
            radioName = self.soft.name
        self.dutDev = radioName.split( ':' )[0]
        self.dut = OHMP.OhMediaPlayerDevice( radioName, aIsDut=True, aLoopback=loopback )
        time.sleep( 3 )

        if mode in ['all','fixed']:
            self.TestFixedParams()
        if mode in ['all','presets']:
            self.TestPresets()
        if mode in ['all','manual']:
            self.TestManual()
        if mode in ['all','updated']:
            self.TestUpdated()
        time.sleep( 3 )     # needed to ensure clean shutdown of SoftPlayer
            
    def Cleanup( self ):
        """Perform cleanup on test exit"""
        if self.dut:
            self.dut.Shutdown()
        if self.soft:
            self.soft.Shutdown()
        BASE.BaseTest.Cleanup( self )

    #
    # Fixed parameter testing
    #
        
    def TestFixedParams( self ):
        """Verify the 'fixed' parameter values are returned correctly"""
        if self.soft:
            expProtocolInfo = kProtocolInfoFree
        else:
            expProtocolInfo = kProtocolInfoAll
            
        self.log.Header2( self.dutDev, 'Testing fixed parameters' )
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

    #
    # Preset testing
    #

    def TestPresets( self ):
        """Verify preset lists from TuneIn are handled correctly"""
        presetsUpdate = threading.Event()

        # noinspection PyUnusedLocal
        def _PresetsEvtCb( aService, aSvName, aSvVal, aSvSeq ):
            if aSvName == 'IdArray':
                presetsUpdate.set()

        self.log.Header2( self.dutDev, 'Testing setup and reporting of TuneIn presets' )
        self._SetTuneInUser( 'no-one' )
        time.sleep( 2 )
        self.dut.radio.AddSubscriber( _PresetsEvtCb )
        for user in (self.config.Get( 'tunein.user.l1' ),       # 0 < channels < 100
                     self.config.Get( 'tunein.user.l2' ),       # 0 channels
                     self.config.Get( 'tunein.user.l3' )):      # > 100 channels
            self.log.Header2( self.dutDev, 'Testing with %s' % user )
            presetsUpdate.clear()
            self._SetTuneInUser( user )
            presetsUpdate.wait( 45 )
            self.log.FailUnless( self.dutDev, presetsUpdate.isSet(),
                'Presets updated after switching user to %s' % user )

            dsPresets = self.dut.radio.AllChannels()
            rtPresets = self._GetTuneInPresets( user )

            for i in range( len( dsPresets )):
                if dsPresets[i][0]:
                    dsUri = Common.GetUriFromDidl( dsPresets[i][1] )
                    dsTitle = Common.GetTitleFromDidl( dsPresets[i][1] )
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
                            '[%d] DS/TuneIn Title: %s/%s' % (i,dsTitle,rtTitle) )
                else:
                    self.log.FailUnless( self.dutDev, rtPresets[i][0]=='',
                        '[%d] TuneIn URI for empty entry: %s' % (i,rtPresets[i][0]) )
                    self.log.FailUnless( self.dutDev, rtPresets[i][1]=='',
                        '[%d] TuneIn Title for empty entry: %s' % (i,rtPresets[i][1]) )
        self.dut.radio.RemoveSubscriber( _PresetsEvtCb )

    def _SetTuneInUser( self, aUser ):
        """Set TuneIn user"""
        seqNum = threading.Event()

        # noinspection PyUnusedLocal
        def CredentialsEventCb( service, svName, svVal, svSeq ):
            """Callback on events from credentials service"""
            if svName == 'SequenceNumber':
                seqNum.set()

        if kTuneInCreds in self.dut.credentials.idList:
            self.dut.credentials.AddSubscriber( CredentialsEventCb )
            seqNum.clear()
            self.dut.credentials.Set( kTuneInCreds, aUser )
            seqNum.wait( 10 )
            self.dut.credentials.RemoveSubscriber( CredentialsEventCb )
            time.sleep( 1 )
            err = self.dut.credentials.Status( kTuneInCreds )
            self.log.FailIf( self.dutDev, err, 'Setting TuneIn user to <%s> %s' % (aUser, err ))
        else:
            self.log.Abort( self.dutDev, 'Unable to set TuneIn account' )

    def _GetTuneInPresets( self, aUser ):
        """Read preset channel info directly from TuneIn"""
        if self.soft:
            browse = kTuneInBrowseFree
        else:
            browse = kTuneInBrowseAll

        partner = self.config.Get( 'tunein.partnerid' )
        tiId = '&username=%s&partnerId=%s' % (aUser, partner)
        resp = self._UrlQuery( kTuneInUrl + 'Preset.ashx?c=listFolders' + tiId )
        dflt = self._GetFromOpmlDefault( resp )
        resp = self._UrlQuery( kTuneInUrl + browse + tiId )
        uri  = self._GetFromOpmlUri( resp, dflt )
        if uri:
            resp = self._UrlQuery( uri )
        return self._GetPresetsFromOpml( resp )

    #
    # Manual radio channel select testing
    #

    def TestManual( self ):
        """Verify manually inserted radio channels"""
        uriUpdated  = threading.Event()
        metaUpdated = threading.Event()

        # noinspection PyUnusedLocal
        def _RadioEvtCb( aService, aSvName, aSvVal, aSvSeq ):
            if aSvName == 'Uri':
                uriUpdated.set()
            elif aSvName == 'Metadata':
                metaUpdated.set()

        self.log.Header2( self.dutDev, 'Testing setup and reporting of manual channels' )
        self.dut.radio.AddSubscriber( _RadioEvtCb )
        uriUpdated.clear()
        self.dut.radio.SetChannel( 'uri', 'meta' )
        uriUpdated.wait( 5 )
        
        for channel in kManualChannels:
            self.log.Header2( self.dutDev, 'Checking with %s' % channel['uri'] )
            uriUpdated.clear()
            metaUpdated.clear()
            self.dut.radio.SetChannel( channel['uri'], channel['meta'] )
            uriUpdated.wait( 3 )
            metaUpdated.wait( 1 )
            
            if not uriUpdated.isSet():
                self.log.Fail( self.dutDev, 'No URI event after channel manually updated' )
            if not metaUpdated.isSet():
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

    #
    # TuneIn list update testing
    #

    def TestUpdated( self ):
        """Verify TuneIn updates are detected by DS"""
        username = self.config.Get( 'tunein.user.new' )
        idArrayUpdated = threading.Event()

        # noinspection PyUnusedLocal
        def _IdArrayEvtCb( aService, aSvName, aSvVal, aSvSeq ):
            if aSvName == 'IdArray':
                idArrayUpdated.set()

        self.log.Header2( self.dutDev, 'Testing detection of TuneIn updates' )
        self.dut.radio.AddSubscriber( _IdArrayEvtCb )
        idArrayUpdated.clear()
        self.dut.config.SetValue( 'Radio.TuneInUserName', username )
        time.sleep( 1 )
        self.dut.product.sourceIndexByName = 'Playlist'
        time.sleep( 1 )
        self.dut.product.sourceIndexByName = 'Radio'
        idArrayUpdated.wait( 30 )

        idArrayUpdated.clear()
        partner = self.config.Get( 'tunein.partnerid' )
        hdr     = kTuneInUrl
        user    = '&partnerId=%s&username=%s&password=%s' % (partner, username, username)
        self._UrlQuery( hdr + 'Preset.ashx?c=add&id=s32500' + user )
        self.log.Info( self.dutDev, 'Updated preset list' )

        for i in range( 36 ):
            if not idArrayUpdated.isSet():
                self.log.Info( self.dutDev, 'Waiting for IdArray update....%d' % (360-(10*i)) )
                time.sleep( 10 )
            else:
                break

        if idArrayUpdated.isSet():
            self.log.Pass( self.dutDev, 'ID updated OK after change to TuneIn presets' )
        else:
            self.log.Fail( self.dutDev, 'NO ID update after change to TuneIn presets' )

        self._UrlQuery( hdr + 'Preset.ashx?c=remove&id=s32500' + user )
        self.dut.radio.RemoveSubscriber( _IdArrayEvtCb )

    #
    # TuneIn comms / OPML decoding
    #

    def _UrlQuery( self, aUrl ):
        """Perform query on specified URL, return response"""
        resp = '<xml/>'
        self.log.Comms( '', 'tunein', 'GET -->> %s' % aUrl )
        try:
            handle = urllib.urlopen( aUrl )
            resp = handle.read( 65535 )
            handle.close()
        except IOError, err:
            self.log.Fail( self.dutDev, 'TuneIn: %s' % err )
        self.log.Comms( self.dutDev, 'tunein', '<<-- %s' % str( resp ))
        return resp

    @staticmethod
    def _GetFromOpmlDefault( aOpml ):
        default = ''
        opml = ET.fromstring( aOpml )
        outlines = opml.getiterator( 'outline' )
        for outline in outlines:
            if outline.get( 'is_default' ):
                default = outline.get( 'text' ).encode( 'utf8' )
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
                title = outline.get( 'text' ).encode( 'utf8' )
                num = int( outline.get( 'preset_number' ))
                if num <= entries:
                    preset[num-1] = (uri, title)
        return preset


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
