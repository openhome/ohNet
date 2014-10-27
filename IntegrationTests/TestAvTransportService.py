#!/usr/bin/env python
"""TestAvTransportService - test AvTransport service

Parameters:
    arg#1 - MediaRenderer DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - before state to test from (use ALL for all states)
            
This performs the state-transition tests on a DUT as controlled by the UPnP
AvTransport service (as it relates to audio-digital-source). The state 
transition table including all end-cases is specified as data blocks within this
file.

NOTE/ all data used in this test should be valid for the scenario being tested.
      Invalid, out-of-range and otherwise erroneous data is covered by the
      service's unit testing.
"""
import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.Volkano       as Volkano
import Upnp.ControlPoints.MediaRenderer as MR
import Utils.Network.HttpServer         as HttpServer
import _SoftPlayer                      as SoftPlayer
import os
import random
import sys
import threading
import time
import xml.etree.ElementTree as ET

#### TODO
#### do playing thru end of track - as a special case transition

kStates = \
[
    # Assumptions (based on DS implementation):
    #    - URIs are all single track (no M3Us)
    #    - No support for NextAVTransportURI action
    #    - No support for counter-based indexing (only time-based)
    #    - No support for ANY optional StateVariables
    #
    # Hence only ONE track in 'playlist' at any time, so any 'Seek' actions
    # only move around with in the current track
    #
    # PAUSED states can have 2 precondition states:
    #    - normal (PAUSED_PLAYBACK) where paused on track which has been playing
    #    - PAUSED_UNKNOWN where CurrentURI has been changed whilst paused, hence
    #      the track data (length etc.) which is only found out when playing is
    #      not known

    # Before           Transition            Err    After              Affected SV List
    # ------           ----------            ---    -----              ----------------
    ['STOPPED',        'SetAVTransportURI',  '',    'STOPPED',         ['AVTransportURI','AVTransportURIMetaData','NumberOfTracks','CurrentTrack','CurrentTrackMetaData','CurrentTrackURI','CurrentTrackDuration','CurrentMediaDuration','PlaybackStorageMedium','RelativeTimePosition']],
    ['STOPPED',        'Stop',               '',    'STOPPED',         ['RelativeTimePosition']],
    ['STOPPED',        'Play',               '',    'PLAYING',         ['CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['STOPPED',        'Pause',              '',    'PAUSED_PLAYBACK', []],
    ['STOPPED',        'Seek',               '701', '',                []],
    ['STOPPED',        'Next',               '',    'STOPPED',         ['CurrentTrackURI','AVTransportURI','CurrentTrack','NumberOfTracks','CurrentTrackMetaData','AVTransportURIMetaData','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['STOPPED',        'Previous',           '',    'STOPPED',         ['CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],

    ['PLAYING',        'SetAVTransportURI',  '',    'PLAYING',         ['AVTransportURI','AVTransportURIMetaData','NumberOfTracks','CurrentTrack','CurrentTrackMetaData','CurrentTrackURI','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['PLAYING',        'Stop',               '',    'STOPPED',         ['RelativeTimePosition']],
    ['PLAYING',        'Play',               '',    'PLAYING',         ['RelativeTimePosition']],
    ['PLAYING',        'Pause',              '',    'PAUSED_PLAYBACK', []],
    ['PLAYING',        'Seek',               '',    'PLAYING',         ['RelativeTimePosition']],
    ['PLAYING',        'Next',               '',    'STOPPED',         ['CurrentTrackURI','AVTransportURI','CurrentTrack','NumberOfTracks','CurrentTrackMetaData','AVTransportURIMetaData','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['PLAYING',        'Previous',           '',    'STOPPED',         ['CurrentTrackURI','AVTransportURI','CurrentTrack','NumberOfTracks','CurrentTrackMetaData','AVTransportURIMetaData','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    # ['PLAYING',        '<EndOfTrack>',       '',    'STOPPED',         ['CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],

    ['PAUSED_PLAYBACK', 'SetAVTransportURI', '',    'PAUSED_PLAYBACK', ['AVTransportURI','AVTransportURIMetaData','NumberOfTracks','CurrentTrack','CurrentTrackMetaData','CurrentTrackURI','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['PAUSED_PLAYBACK', 'Stop',              '',    'STOPPED',         ['RelativeTimePosition']],
    ['PAUSED_PLAYBACK', 'Play',              '',    'PLAYING',         ['RelativeTimePosition']],
    ['PAUSED_PLAYBACK', 'Pause',             '',    'PAUSED_PLAYBACK', []],
    ['PAUSED_PLAYBACK', 'Seek',              '701', '',                []],
    ['PAUSED_PLAYBACK', 'Next',              '',    'STOPPED',         ['CurrentTrackURI','AVTransportURI','CurrentTrack','NumberOfTracks','CurrentTrackMetaData','AVTransportURIMetaData','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['PAUSED_PLAYBACK', 'Previous',          '',    'STOPPED', ['CurrentTrackURI','AVTransportURI','CurrentTrack','NumberOfTracks','CurrentTrackMetaData','AVTransportURIMetaData','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],

    ['PAUSED_UNKNOWN', 'SetAVTransportURI',  '',    'PAUSED_PLAYBACK', ['AVTransportURI','AVTransportURIMetaData','NumberOfTracks','CurrentTrack','CurrentTrackMetaData','CurrentTrackURI','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['PAUSED_UNKNOWN', 'Stop',               '',    'STOPPED',         ['RelativeTimePosition']],
    ['PAUSED_UNKNOWN', 'Play',               '',    'PLAYING',         ['RelativeTimePosition']],#['CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['PAUSED_UNKNOWN', 'Pause',              '',    'PAUSED_PLAYBACK', []],
    ['PAUSED_UNKNOWN', 'Seek',               '701', '',                []],
    ['PAUSED_UNKNOWN', 'Next',               '',    'STOPPED',         ['CurrentTrackURI','AVTransportURI','CurrentTrack','NumberOfTracks','CurrentTrackMetaData','AVTransportURIMetaData','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['PAUSED_UNKNOWN', 'Previous',           '',    'STOPPED',         ['CurrentTrackURI','AVTransportURI','CurrentTrack','NumberOfTracks','CurrentTrackMetaData','AVTransportURIMetaData','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
]
kBefore = 0
kAction = 1
kErr    = 2
kAfter  = 3
kAffSvs = 4

kStaticSvs = \
{
    'AbsoluteCounterPosition':      2147483647,
    'AbsoluteTimePosition':         'NOT_IMPLEMENTED',
    'CurrentPlayMode':              'NORMAL',
    'CurrentRecordQualityMode':     'NOT_IMPLEMENTED',
    'CurrentTrackEmbeddedMetaData': '',
    'CurrentTransportActions':      '',
    'NextAVTransportURI':           'NOT_IMPLEMENTED',
    'NextAVTransportURIMetaData':   'NOT_IMPLEMENTED',
    'PossiblePlaybackStorageMedia': 'NETWORK',
    'PossibleRecordQualityModes':   'NOT_IMPLEMENTED',
    'PossibleRecordStorageMedia':   'NOT_IMPLEMENTED',
    'RecordMediumWriteStatus':      'NOT_IMPLEMENTED',
    'RecordStorageMedium':          'NOT_IMPLEMENTED',
    'RelativeCounterPosition':      2147483647,
    'TransportStatus':              'OK',
    'TransportPlaySpeed':           '1'
}

kNonStaticSvs = \
[
    'AVTransportURI',
    'AVTransportURIMetaData',
    'CurrentMediaDuration',
    'CurrentTrackDuration',
    'CurrentTrack',
    'CurrentTrackMetaData',
    'CurrentTrackURI',
    'NumberOfTracks',
    'PlaybackStorageMedium',
    'RelativeTimePosition',
    # 'TransportState'  - ignore in SV checks as state is checked seperately
]

kAudioRoot = os.path.join( _FunctionalTest.audioDir, 'MusicTracks/' )
kAvtNs     = '{urn:schemas-upnp-org:metadata-1-0/AVT/}'
kDidlNs    = '{urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/}'


class Clock():
    """Clock class used to track playback time"""

    def __init__( self ):
        """Initialise class data"""
        self.ticks = 0
        self.timer = None
        self.mutex = threading.Lock()

    def Start( self ):
        """Start counting ticks, don't reset tick count"""
        self.mutex.acquire()
        if self.timer:
            self.timer.cancel()
        self.timer = threading.Timer( 1, self.__TimerCb )
        self.timer.start()
        self.mutex.release()

    def Stop( self ):
        """Stop counting ticks, reset the tick count"""
        self.mutex.acquire()
        if self.timer:
            self.timer.cancel()
            self.timer=None
        self.ticks = 0
        self.mutex.release()

    def Pause( self ):
        """Stop counting ticks, don't reset the tick count"""
        self.mutex.acquire()
        if self.timer:
            self.timer.cancel()
            self.timer=None
        self.mutex.release()

    def Jump( self, aSecs ):
        """Increment count by specified anount"""
        self.mutex.acquire()
        self.ticks += aSecs-1   #(round down as seeks to start-of time)
        self.mutex.release()

    def Reset( self ):
        """Reset the tick count"""
        self.mutex.acquire()
        self.ticks = 0
        self.mutex.release()

    def __TimerCb( self ):
        """Increment tick count, restart 1s timer"""
        self.mutex.acquire()
        self.ticks += 1
        self.timer = threading.Timer( 1, self.__TimerCb )
        self.timer.start()
        self.mutex.release()

    def __GetElapsed( self ):
        """Return the current tick count"""
        self.mutex.acquire()
        t = self.ticks
        self.mutex.release()
        return t

    elapsed = property( __GetElapsed, None, None, 'Elapsed' )


class TestAvTransportService( BASE.BaseTest ):
    """Test DS AvTransport Service"""

    def __init__( self ):
        BASE.BaseTest.__init__( self )
        self.mrName        = None
        self.mrDev         = None
        self.soft          = None
        self.server        = None
        self.upnpMr        = None
        self.avt           = None
        self.setupUri      = None
        self.setupMeta     = None
        self.setupDuration = None
        self.tracks        = []
        self.playingEvt    = threading.Event()
        self.pausedEvt     = threading.Event()
        self.stoppedEvt    = threading.Event()
        self.transportEvt  = threading.Event()
        self.uriEvt        = threading.Event()
        self.clock         = Clock()

    def Test( self, args ):
        """AVTransport state-transition test"""
        stateToTest = 'ALL'
        loopback    = False
        try:
            self.mrName = args[1]
            stateToTest = args[2].upper()
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )
            
        # setup states to test
        allStates = ['STOPPED','PLAYING','PAUSED_PLAYBACK','PAUSED_UNKNOWN']
        statesToTest = None
        if stateToTest == 'ALL':
            statesToTest = allStates
        elif stateToTest in allStates:
            statesToTest = [stateToTest]
        else:
            self.log.Abort( '', 'Invalid state-to-test %s' % stateToTest )

        # start audio server
        self.server = HttpServer.HttpServer( kAudioRoot )
        self.server.Start()        

        # load test track info into track list
        xmlFile = os.path.join( kAudioRoot, 'TrackList.xml' )
        xml = ET.parse( xmlFile )
        trackList = xml.findall( 'Track' )
        for track in trackList:
            uri = self.server.Listener() + track.find( 'Uri' ).text
            meta = track.find( 'Metadata' ).text
            self.tracks.append( {'uri':uri, 'meta':meta} )

        # start local softplayer if required
        if self.mrName.lower() == 'local':
            loopback = True
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestMr', aLoopback=loopback )
            self.mrName = self.soft.name.split( ':' )[0] + ':UPnP AV'
        
        # create UPnP CPs for renderer and server, subscribe to AVT events
        self.mrDev = self.mrName.split( ':' )[0]
        self.upnpMr = MR.MediaRendererDevice( self.mrName, aLoopback=loopback )
        self.avt = self.upnpMr.avt
        self.avt.AddSubscriber( self._AvtEventCb )

        # initialise UPnP AV and check static Svs before start
        self._AvtSetAvtTransportUri( self.tracks[0] )
        self._AvtStop()
        self._CheckStaticSvs()

        # check state transitions and SV changes for all scenarios
        for entry in kStates:
            if entry[kBefore] in statesToTest:
                self.log.Header1( self.mrDev, 'Checking %s invokation from %s state' % (entry[kAction], entry[kBefore]))
                params = None
                if entry[kAction] == 'Seek':
                    params = random.randint( 30, 120 )
                elif entry[kAction] == 'SetAVTransportURI':
                    params = self._SelectTrack()

                self._SetState( entry[kBefore] )
                svsBefore = self._GetNonStaticSvs()
                err = self._InvokeAction( entry[kAction], params )
                if err:
                    msg = 'AVTransport: %s' % entry[kAction]
                    if params: msg += ' with param(s) [%s] ' % params
                    msg += 'gave error <%s>' % err
                    if entry[kErr] in err:
                        self.log.Pass( self.mrDev, '%s as expected' % msg )
                    else:
                        self.log.Fail( self.mrDev, '%s' % msg )
                else:
                    delay = random.randint( 3, 10 )
                    self.log.Info( self.mrDev, 'Waiting %ds after invoke' % delay )
                    time.sleep( delay )

                    # check state
                    if self.avt.transportState == 'TRANSITIONING':
                        self.transportEvt.clear()
                        self.transportEvt.wait( 3 )
                        if self.avt.transportState=='TRANSITIONING':
                            self.log.Fail( self.mrDev, 'TRANSITIONING state failed to clear within 3s' )
                    devState = self.avt.transportState
                    self.log.FailUnless( self.mrDev, devState==entry[kAfter], '%s/%s actual/expected state after %s from %s'
                        % (devState, entry[kAfter], entry[kAction], entry[kBefore]) )

                    # check SVs
                    svsAfter = self._GetNonStaticSvs()
                    self._CheckStaticSvs()
                    self._CheckUnaffectedSvs( svsBefore, svsAfter, entry[kAffSvs] )
                    self._CheckAffectedSvs( svsAfter, entry[kAffSvs] )

        # stop playback before exiting
        self._AvtStop()

    def Cleanup( self ):
        """Perform post-test cleanup"""
        if self.upnpMr:          
            self.upnpMr.Shutdown()
        if self.server:
            self.server.Shutdown()
        if self.soft:
            self.soft.Shutdown()
        BASE.BaseTest.Cleanup( self )

    #
    # Setup preconditions
    #

    def _SetState( self, state ):
        """Force DUT into specified state (only actions if necessary)"""
        self.log.Header2( self.mrDev, 'Setting precondition state to %s' % state )
        self._AvtSetAvtTransportUri( self._SelectTrack() )  # load a random track (different
        self._AvtPlay( aForce=True )                        # from currently loaded) and play
        delay = random.randint( 3, 10 )                     # a short (random) time into it
        self.log.Info( self.mrDev, 'Waiting %ds into playback' % delay )
        time.sleep( delay )

        if state == 'PAUSED_PLAYBACK':
            self._AvtPause( aForce=True )
        elif state == 'PAUSED_UNKNOWN':
            self._AvtPause( aForce=True )
            self._AvtSetAvtTransportUri( self._SelectTrack() )
            state = 'PAUSED_PLAYBACK'   # actual device state
        elif state == 'STOPPED':
            self._AvtStop()

        devState = self.avt.transportState
        self.log.FailUnless( self.mrDev, devState==state, '%s/%s actual/expected precon state' %  (devState, state) )

    def _SelectTrack( self ):
        """Return random track for playback (different from currently loaded)"""
        track = None
        while True:
            track = self.tracks[ random.randint( 0, len( self.tracks )-1 )]
            if track['uri'] != self.avt.avTransportURI:
                break
        return track

    #
    # Invoke actions
    #

    def _InvokeAction( self, aAction, aParams=None ):
        """Invoke specified action with specified parameters"""
        self.log.Header2( self.mrDev, 'Invoking %s (with params %s) ' % (aAction, aParams) )
        if aAction == 'Next':
            err = self._AvtNext()
        elif aAction == 'Pause':
            err = self._AvtPause( aForce=True )
        elif aAction == 'Play':
            err = self._AvtPlay( aForce=True)
        elif aAction == 'Previous':
            err = self._AvtPrevious()
        elif aAction == 'Seek':
            err = self._AvtSeek( aParams )
        elif aAction == 'SetAVTransportURI':
            err = self._AvtSetAvtTransportUri( aParams, aForce=True )
        elif aAction == 'Stop':
            err = self._AvtStop( aForce=True )
        else:
            err = self.log.Fail( self.mrDev, 'Unrecognised invoke: %s' % aAction )
        return err

    #
    # Wrapped invokes which check for status
    #

    def _AvtNext( self ):
        """Invoke AVT next, wait for transport state event( if any)"""
        self.transportEvt.clear()
        err = self.avt.Next( aReturnErr=True )
        self.transportEvt.wait( 3 )
        return err

    def _AvtPause( self, aForce=False ):
        """Pause playback using AVT, wait for event"""
        if self.avt.transportState!='PAUSED_PLAYBACK' or aForce:
            self.pausedEvt.clear()
            err = self.avt.Pause( aReturnErr=True )
            self.pausedEvt.wait( 3 )
            return err

    def _AvtPlay( self, aForce=False ):
        """Start playback using AVT, wait for event"""
        if self.avt.transportState!='PLAYING' or aForce:
            self.playingEvt.clear()
            err = self.avt.Play( aReturnErr=True )
            self.playingEvt.wait( 3 )
            return err

    def _AvtPrevious( self ):
        """Invoke AVT previous, wait for transport state event( if any)"""
        self.transportEvt.clear()
        err = self.avt.Next( aReturnErr=True )
        self.transportEvt.wait( 3 )
        return err

    def _AvtSeek( self, aRelTime ):
        """Invoke AVT seek"""
        self.clock.Jump( aRelTime )
        err = self.avt.Seek( aRelTime, aReturnErr=True )
        return err

    def _AvtSetAvtTransportUri( self, aTrack, aForce=False ):
        """Set AV Transport URI, wait for confirmation event"""
        err = None
        if self.avt.currentTrackURI!=aTrack['uri'] or aForce:
            self.uriEvt.clear()
            err = self.avt.avt.SetAVTransportURI( InstanceID=0, CurrentURI=aTrack['uri'], CurrentURIMetaData=aTrack['meta'], aReturnErr=True )
            self.uriEvt.wait( 3 )
            self.clock.Reset()
        self.setupUri = aTrack['uri']
        self.setupMeta = aTrack['meta']
        didl = ET.XML( aTrack['meta'] )
        res = didl.getiterator( kDidlNs+'res' )[0]
        dur = res.attrib['duration']
        self.setupDuration = int( dur[0:2] )*3600 + int( dur[3:5] )*60 + int( dur[6:] )
        return err

    def _AvtStop( self, aForce=False ):
        """Stop playback using AVT, wait for event"""
        err = None
        if self.avt.transportState!='STOPPED' or aForce:
            self.stoppedEvt.clear()
            err = self.avt.Stop( aReturnErr=True )
            self.stoppedEvt.wait( 3 )
        return err

    # noinspection PyUnusedLocal
    def _AvtEventCb( self, aService, aSvName, aSvVal, aSvSeq ):
        """Callback from AVT service events"""
        xml = ET.XML( aSvVal )
        instance = xml.find( kAvtNs+'InstanceID' )
        if instance is not None:
            elem = instance.find( kAvtNs+'TransportState' )
            if elem is not None:
                self.transportEvt.set()
                state = elem.attrib['val']
                if state == 'PAUSED_PLAYBACK':
                    self.clock.Pause()
                    self.pausedEvt.set()
                elif state == 'PLAYING':
                    self.clock.Start()
                    self.playingEvt.set()
                elif  state == 'STOPPED':
                    self.clock.Stop()
                    self.stoppedEvt.set()
            elem = instance.find( kAvtNs+'CurrentTrackURI' )
            if elem is not None:
                self.uriEvt.set()

    #
    # Checks on SV values
    #

    def _CheckStaticSvs( self ):
        """Verify static SVs are as expected"""
        for sv in kStaticSvs.keys():
            meas = getattr( self.avt, sv[0].lower()+sv[1:] )
            exp = kStaticSvs[sv]
            self.log.FailUnless( self.mrDev, meas==exp,
                '%s/%s actual/expected value for %s (static)' % (meas, exp, sv) )

    def _CheckUnaffectedSvs( self, aBefore, aAfter, aAffSvs ):
        """Verify SVS which should be unaffected have not changed value"""
        for sv in kNonStaticSvs:
            if sv not in aAffSvs:
                self.log.FailUnless( self.mrDev, aAfter[sv]==aBefore[sv],
                    '%s/%s actual/expected value for %s (unaffected)' % (aAfter[sv], aBefore[sv], sv) )

    def _CheckAffectedSvs( self, aAfter, aAffSvs ):
        """Verify SVS which should be affected have changed to expected value"""
        for sv in kNonStaticSvs:
            if sv in aAffSvs:
                expected = eval( 'self._Exp%s()' % sv )
                self.log.FailUnless( self.mrDev, aAfter[sv]==expected,
                    '%s/%s actual/expected value for %s (affected)' % (aAfter[sv], expected, sv) )

    def _GetNonStaticSvs( self ):
        """Read non-static SV values from DUT"""
        val = {}
        for sv in kNonStaticSvs:
            val[sv] = getattr( self.avt, sv[0:2].lower()+sv[2:] )
        return val

    def _ExpAVTransportURI( self, ):
        return self.setupUri

    def _ExpAVTransportURIMetaData( self, ):
        return self.setupMeta

    def _ExpCurrentMediaDuration( self ):
        return self.setupDuration

    def _ExpCurrentTrack( self ):
        return '0' if self.avt.transportState=='NO_MEDIA_PRESENT' else '1'

    def _ExpCurrentTrackDuration( self ):
        return self.setupDuration

    def _ExpCurrentTrackURI( self ):
        return self.setupUri

    def _ExpCurrentTrackMetaData( self ):
        return self.setupMeta

    def _ExpNumberOfTracks( self ):
        return '0' if self.avt.transportState=='NO_MEDIA_PRESENT' else '1'

    def _ExpPlaybackStorageMedium( self ):
        return 'NONE' if self.avt.transportState=='NO_MEDIA_PRESENT' else 'NETWORK'

    def _ExpRelativeTimePosition( self ):
        return self.clock.elapsed


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
