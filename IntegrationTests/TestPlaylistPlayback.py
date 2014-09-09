#!/usr/bin/env python
"""TestPlaylistPlayback - test Playlist service state/transition basic operation

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - test mode 
              - all             for all configs sequentially
              - <num>           for config number <num> 
              - [min:max]       for range of (numbered) configs
              - [<n1>,<n2>...]  list of configs
              - <stim>          for stimulus (Play, Pause, Stop,
                                    SeekSecondsAbsolute, SeekSecondsRelative,
                                    SeekIndex, Next, Previous)
              - <pre-state>     for precon state (Stopped, Playing, Paused)
    arg#3 - random number generator seed (0 for 'random')
            by passing this, test scenarious containing random data can be
            replicated - the seed used is logged at the start of execution
            
Tests state-transition operation of DS service. Each transition is tested as a
standalone operation - no aggregation of actions due to async operation tested.
""" 
import _FunctionalTest
import BaseTest                   as BASE
import Upnp.ControlPoints.Volkano as Volkano
import Utils.Network.HttpServer   as HttpServer
import Utils.Common               as Common
import _SoftPlayer                as SoftPlayer
import LogThread
import os
import random
import sys
import time
import threading

kAudioRoot = os.path.join( _FunctionalTest.audioDir, 'MusicTracks/' )
kTrackList = os.path.join( kAudioRoot, 'TrackList.xml' )
kDelay1    = 3
kDelay2    = 8


class Config:
    """Test configuration for Media service testing"""
    
    class Precon:
        """Configuration subclass for precondition info and setup"""
        
        def __init__( self, aId, aState, aPlLen, aTrack, aSecs, aRepeat, aTracks, aLog, aDev ):
            """Initialise class data"""
            self.id            = aId
            self.state         = aState
            self.plLen         = None
            self.plLen         = self._SubstMacros( aPlLen )
            self.track         = self._SubstMacros( aTrack )
            self.secs          = aSecs
            self.repeat        = aRepeat
            self.duration      = None
            self.evtTime       = -1
            self.durationEvent = threading.Event()
            self.idEvent       = threading.Event()
            self.idArrayEvent  = threading.Event()
            self.stoppedEvent  = threading.Event()
            self.pausedEvent   = threading.Event()
            self.playingEvent  = threading.Event()
            self.timeEvent     = threading.Event()
            self.log           = aLog
            self.dev           = aDev

            # create random playlist
            self.playlist = []
            for i in range( self.plLen ):
                self.playlist.append( aTracks[random.randint( 0, len( aTracks )-1)])

        def Setup( self, aDut ):
            """Setup preconditions on the renderer"""
            aDut.playlist.DeleteAllTracks()
            self.log.Info( self.dev, 'Adding playlist of %d tracks' % self.plLen )
            aDut.playlist.AddSubscriber( self._PlaylistEventCb )
            aDut.playlist.AddPlaylist( self.playlist )
            self.idArrayEvent.wait( 5 )
            self.log.Info( self.dev, 'Added playlist of %d tracks' % self.plLen )
            aDut.playlist.repeat = self.repeat
            aDut.info.AddSubscriber( self._InfoEventCb )
            aDut.time.AddSubscriber( self._TimeEventCb )

            if self.track != -1:
                self.durationEvent.clear()
                self.idEvent.clear()
                aDut.playlist.SeekIndex( self.track )
                if aDut.playlist.PlaylistIndex( aDut.playlist.id ) != self.track:
                    self.idEvent.wait( 5 )
                if self.state == 'Stopped':
                    self.stoppedEvent.clear()
                    aDut.playlist.Stop()
                    self.stoppedEvent.wait( 5 )
                    self.duration = None
                elif self.state in ['Playing', 'Paused']:
                    if self.secs == '@T':
                        self.durationEvent.wait( 5 )
                        self.duration = aDut.info.duration
                        if not self.durationEvent.isSet():
                            self.log.Info( self.dev,
                                'Duration event timed-out, assume unchanged (%d)'
                                % self.duration )
                        if self.duration > 12:
                            self.secs = random.randint( 5, self.duration-12 )
                        else:
                            self.log.Warn( self.dev, 'Duration value not updated' )
                            self.secs = random.randint( 5, 95 )
                        self.timeEvent.clear()
                        self.playingEvent.clear()
                        aDut.playlist.SeekSecondAbsolute( self.secs )
                        tries = 0
                        while self.evtTime != self.secs and tries < 5:
                            tries += 1
                            self.timeEvent.wait( 2 )
                            self.timeEvent.clear()
                        if aDut.playlist.transportState != 'Playing':
                            self.playingEvent.wait( 3 )
                    if self.state == 'Paused':
                        self.pausedEvent.clear()
                        aDut.playlist.Pause()
                        self.pausedEvent.wait( 5 )
            aDut.time.RemoveSubscriber( self._TimeEventCb )
            aDut.info.RemoveSubscriber( self._InfoEventCb )
            aDut.playlist.RemoveSubscriber( self._PlaylistEventCb )
            dutState = aDut.playlist.transportState
            if dutState == self.state:
                self.log.Pass( self.dev, '[%d] Preconditions setup' % self.id )
            else:
                self.log.Fail( self.dev, '[%d] Actual/Required precondition state %s/%s' %
                    (self.id, dutState, self.state) )

        def _SubstMacros( self, aArg ):
            """Substitute parameter macros with actual values.
               Valid macros are:
                @m - random track within playlist
                @N - playlist length -> random value between 8 and 30
            """
            try:
                if not self.plLen:
                    aArg = aArg.replace( '@N', 'random.randint( 8, 30 )' )
                else:
                    aArg = aArg.replace( '@N', 'self.plLen' )
                aArg = aArg.replace( '@m', 'random.randint( 2, self.plLen-3 )' )
                subst = eval( aArg )
            except:
                subst = aArg
            return subst

        # noinspection PyUnusedLocal
        def _InfoEventCb( self, aService, aSvName, aSvVal, aSvSeq ):
            """Callback from Info service events"""
            if aSvName == 'Duration' and aSvVal not in [0,'0']:
                self.durationEvent.set()

        # noinspection PyUnusedLocal
        def _TimeEventCb( self, aService, aSvName, aSvVal, aSvSeq ):
            """Callback from Time service events"""
            if aSvName == 'Seconds':
                self.evtTime = int( aSvVal )
                self.timeEvent.set()

        # noinspection PyUnusedLocal
        def _PlaylistEventCb( self, aService, aSvName, aSvVal, aSvSeq ):
            """Callback from Playlist service events"""
            if aSvName == 'TransportState':
                if aSvVal == 'Stopped':
                    self.stoppedEvent.set()
                elif aSvVal == 'Playing':
                    self.playingEvent.set()
                elif aSvVal == 'Paused':
                    self.pausedEvent.set()
            elif aSvName == 'Id':
                self.idEvent.set()
            elif aSvName == 'IdArray' and aSvVal not in [0,'0']:
                self.idArrayEvent.set()


    class Stimulus:
        """Configuration subclass for stimulus info and invokation"""

        def __init__( self, aAction, aMinVal, aMaxVal, aError, aPrecon, aTimer1, aTimer2 ):
            """Initialise class data"""
            self.action = aAction
            self.precon = aPrecon
            self.minVal = aMinVal
            self.maxVal = aMaxVal
            self.err    = aError
            self.timer1 = aTimer1
            self.timer2 = aTimer2
            self.val    = 0
            self.timeEvent= threading.Event()

        def Invoke( self, aDut ):
            """Invoke stimulus on specified renderer"""
            aDut.time.AddSubscriber( self._timeEventCb )
            if self.action in ['Play','Pause','Stop','Next','Previous']:
                getattr( aDut.playlist, self.action )()
            else:
                mini = self._SubstMacros( self.minVal, aDut )
                maxi = self._SubstMacros( self.maxVal, aDut )
                self.precon.log.Info( self.precon.dev, 'MIN %s  MAX %s' % (str(mini), str(maxi)))

                if mini == '':
                    self.val = random.randint( maxi-100, maxi )
                elif maxi == '':
                    self.val = random.randint( mini, mini+100 )
                elif mini == maxi:
                    self.val = mini
                else:
                    self.val = random.randint( mini, maxi )
                err = getattr( aDut.playlist, self.action )( self.val, aReturnErr=True )
                if err:
                    if self.err:
                        devErr = int( err.split( ':' )[0] )
                        self.precon.log.FailUnless( self.precon.dev, devErr==self.err,
                            '[%d] %d/%d Actual/Expected UPnP error code' % (self.precon.id, devErr, self.err) )
                    else:
                        self.precon.log.Fail( self.precon.dev, '[%d] %s' % (self.precon.id, err) )
                else:
                    if self.err:
                        self.precon.log.Fail( self.precon.dev,
                            '[%d] Expected UPnP error code %d, got none' % (self.precon.id, self.err) )
            self.timer1.start()
            self.timer2.start()
            # either DS will start playback in which case need to wait for event
            # before starting outcome timers, or will not be playing in which
            # case wait will timeout without any affect on the result (#2527)
            time.sleep( 0.5 )
            self.timeEvent.clear()
            self.timeEvent.wait( 5 )
            aDut.time.RemoveSubscriber( self._timeEventCb )

        # noinspection PyMethodMayBeStatic, PyUnusedLocal
        def _SubstMacros( self, aArg, aDut ):
            """Substitute parameter macros with actual values. Some of these are
               NOT KNOWN at __init__ time, so call the substs at Invoke() time
               Valid macros are:
                @D - current track duration
                @m - current track
                @N - playlist length
                @T - current track secs
            """
            try:
                aArg = aArg.replace( '@D', 'aDut.info.duration' )
                aArg = aArg.replace( '@m', 'self.precon.track' )
                aArg = aArg.replace( '@N', 'self.precon.plLen' )
                aArg = aArg.replace( '@T', 'self.precon.secs' )
                subst = eval( aArg )
            except:
                subst = aArg
            return subst

        # noinspection PyUnusedLocal
        def _timeEventCb( self, aService, aSvName, aSvVal, aSvSeq ):
            """Callback from Time service events"""
            self.timeEvent.set()


    class Outcome:
        """Configuration subclass for outcome checking"""

        def __init__( self, aId, aState, aTrack, aSecs, aPrecon, aStim, aDelay1, aDelay2 ):
            """Initialise class data"""
            self.id     = aId
            self.state  = aState
            self.track  = aTrack
            self.secs   = aSecs
            self.precon = aPrecon
            self.stim   = aStim
            self.delay1 = aDelay1
            self.delay2 = aDelay2

        def Check( self, aLog, aDut, aDev ):
            """Check outcome on specified renderer"""
            expState = self.state
            expTrack = int( self._SubstMacros( self.track ))
            expSecs  = int( self._SubstMacros( self.secs ))

            # wait a few secs (from time event/timeout) and check values
            self.delay1.wait()
            if expState == 'Playing':
                expSecs += kDelay1
                (expState, expTrack, expSecs) = \
                    self._RecalcExpected( expState, expTrack, expSecs )
            self._CheckValues( aLog, aDut, aDev, expState, expTrack, expSecs, kDelay1 )

            # wait a few more secs and check that values are changing correctly
            # (if Playing) or not changing as expected (if Paused, Stopped)
            self.delay2.wait()
            if expState == 'Playing':
                expSecs += kDelay2-kDelay1
                (expState, expTrack, expSecs) = \
                    self._RecalcExpected( expState, expTrack, expSecs )
            self._CheckValues(
                aLog, aDut, aDev, expState, expTrack, expSecs, kDelay2 )

        def _CheckValues( self, aLog, aDut, aDev, aState, aTrack, aSecs, aAfter ):
            """Check values from DS are as expected"""

            aLog.Info( '' )
            evtTrack = aDut.playlist.PlaylistIndex( aDut.playlist.id )
            aLog.FailUnless( aDev, evtTrack==aTrack,
                '[%d] (%d/%d) Actual/Expected EVENTED track index %ds after invoke' %
                (self.id, evtTrack, aTrack, aAfter) )

            evtState = aDut.playlist.transportState
            aLog.FailUnless( aDev, evtState==aState,
                '[%d] (%s/%s) Actual/Expected EVENTED transport state %ds after invoke' %
                (self.id, evtState, aState, aAfter) )

            pollState = aDut.playlist.polledTransportState
            aLog.FailUnless( aDev, pollState==aState,
                '[%d] (%s/%s) Actual/Expected POLLED transport state %ds after invoke' %
                (self.id, pollState, aState, aAfter) )

            evtSecs = aDut.time.seconds
            aLog.CheckLimits( aDev, 'GELE', evtSecs, aSecs-2, aSecs+1,
                '[%d] Expected EVENTED track seconds %ds after invoke' % (self.id, aAfter) )

            pollSecs = aDut.time.polledSeconds
            aLog.CheckLimits( aDev, 'GELE', pollSecs, aSecs-2, aSecs+1,
                '[%d] Expected POLLED track seconds %ds after invoke' % (self.id, aAfter) )

            pollBitDepth = aDut.info.polledBitDepth
            evtBitDepth = aDut.info.bitDepth
            aLog.FailUnless( aDev, pollBitDepth==evtBitDepth,
                '[%d] (%s/%s) Polled/Evented bit depth %ds after invoke' %
                (self.id, pollBitDepth, evtBitDepth, aAfter) )

            pollBitRate = aDut.info.polledBitRate
            evtBitRate = aDut.info.bitRate
            aLog.FailUnless( aDev, pollBitRate==evtBitRate,
                '[%d] (%s/%s) Polled/Evented bit rate %ds after invoke' %
                (self.id, pollBitRate, evtBitRate, aAfter) )

            pollCodecName = aDut.info.polledCodecName
            evtCodecName = aDut.info.codecName
            aLog.FailUnless( aDev, pollCodecName==evtCodecName,
                '[%d] (%s/%s) Polled/Evented codec name %ds after invoke' %
                (self.id, pollCodecName, evtCodecName, aAfter) )

            pollDetailsCount = aDut.info.polledDetailsCount
            evtDetailsCount = aDut.info.detailsCount
            aLog.FailUnless( aDev, pollDetailsCount==evtDetailsCount,
                '[%d] (%s/%s) Polled/Evented details count %ds after invoke' %
                (self.id, pollDetailsCount, evtDetailsCount, aAfter) )

            pollDuration = aDut.info.polledDuration
            evtDuration = aDut.info.duration
            aLog.FailUnless( aDev, pollDuration==evtDuration,
                '[%d] (%s/%s) Polled/Evented duration %ds after invoke' %
                (self.id, pollDuration, evtDuration, aAfter) )

            pollLossless = aDut.info.polledLossless
            evtLossless = aDut.info.lossless
            aLog.FailUnless( aDev, pollLossless==evtLossless,
                '[%d] (%s/%s) Polled/Evented lossless %ds after invoke' %
                (self.id, pollLossless, evtLossless, aAfter) )

            pollMetadata = aDut.info.polledMetadata
            evtMetadata = aDut.info.metadata
            aLog.FailUnless( aDev, pollMetadata==evtMetadata,
                '[%d] (%s/%s) Polled/Evented metadata %ds after invoke' %
                (self.id, pollMetadata, evtMetadata, aAfter) )

            pollMetatext = aDut.info.polledMetatext
            evtMetatext = aDut.info.metatext
            aLog.FailUnless( aDev, pollMetatext==evtMetatext,
                '[%d] (%s/%s) Polled/Evented metatext %ds after invoke' %
                (self.id, pollMetatext, evtMetatext, aAfter) )

            pollMetatextCount = aDut.info.polledMetatextCount
            evtMetatextCount = aDut.info.metatextCount
            aLog.FailUnless( aDev, pollMetatextCount==evtMetatextCount,
                '[%d] (%s/%s) Polled/Evented metatext count %ds after invoke' %
                (self.id, pollMetatextCount, evtMetatextCount, aAfter) )

            pollSampleRate = aDut.info.polledSampleRate
            evtSampleRate = aDut.info.sampleRate
            aLog.FailUnless( aDev, pollSampleRate==evtSampleRate,
                '[%d] (%s/%s) Polled/Evented sample rate %ds after invoke' %
                (self.id, pollSampleRate, evtSampleRate, aAfter) )

            pollTrackCount = aDut.info.polledTrackCount
            evtTrackCount = aDut.info.trackCount
            aLog.FailUnless( aDev, pollTrackCount==evtTrackCount,
                '[%d] (%s/%s) Polled/Evented track count %ds after invoke' %
                (self.id, pollTrackCount, evtTrackCount, aAfter) )

            pollUri = aDut.info.polledUri
            evtUri = aDut.info.uri
            aLog.FailUnless( aDev, pollUri==evtUri,
                '[%d] (%s/%s) Polled/Evented URI %ds after invoke' %
                (self.id, pollUri, evtUri, aAfter) )
            aLog.Info( '' )

        def _RecalcExpected( self, aState, aTrack, aSecs ):
            """Recalculate expected values after playback over time"""
            expState = aState
            expTrack = aTrack
            expSecs  = aSecs
            if self.precon.duration:
                if expSecs > self.precon.duration:
                    expSecs = expSecs - self.precon.duration
                    expTrack += 1
                    if expTrack >= self.precon.plLen:
                        expTrack = 0
                        if self.precon.repeat == 'off':
                            expState = 'Stopped'
            return expState, expTrack, expSecs

        # noinspection PyMethodMayBeStatic
        def _SubstMacros( self, aArg ):
            """Substitute parameter macros with actual values. Some of these are
               NOT KNOWN at __init__ time, so call the substs at Check() time
               Valid macros are:
                @D - current track duration
                @m - precon track
                @N - playlist length
                @T - precon track secs
                @x - current track
                @y - current track secs
            """
            try:
                aArg = aArg.replace( '@D', 'aDut.info.duration' )
                aArg = aArg.replace( '@N', 'self.precon.plLen' )
                aArg = aArg.replace( '@m', 'self.precon.track' )
                aArg = aArg.replace( '@T', 'self.precon.secs' )
                aArg = aArg.replace( '@x', 'self.stim.val' )
                aArg = aArg.replace( '@y', 'self.stim.val' )
                subst = eval( aArg )
            except:
                subst = aArg
            return subst


    def __init__( self, aLog, aDev, aDut, aConf, aTracks ):
        """Initialise class (and sub-class) data"""
        self.log    = aLog
        self.id     = aConf[0]
        self.dut    = aDut
        self.dev    = aDev
        self.delay1 = threading.Event()
        self.delay2 = threading.Event()
        timer1      = LogThread.Timer( kDelay1, self.__t1Cb )
        timer2      = LogThread.Timer( kDelay2, self.__t2Cb )

        self.pre  = self.Precon( self.id, aConf[1], aConf[2], aConf[3],
                                 aConf[4], aConf[5], aTracks, self.log, aDev )
        self.stim = self.Stimulus( aConf[6], aConf[7], aConf[8], aConf[9], self.pre,
                                   timer1, timer2 )
        self.out  = self.Outcome( self.id, aConf[10], aConf[11], aConf[12],
                                  self.pre, self.stim, self.delay1, self.delay2 )

    def Setup( self ):
        self.pre.Setup( self.dut )

    def InvokeStimulus( self ):
        self.stim.Invoke( self.dut )

    def CheckOutcome( self ):
        self.out.Check( self.log, self.dut, self.dev )

    def __t1Cb( self ):
        self.delay1.set()

    def __t2Cb( self ):
        self.delay2.set()


class TestPlaylistPlayback( BASE.BaseTest ):
    """Test playback control operation (using UPnP is control method)"""

    def __init__( self ):
        """Constructor - initalise base class"""
        BASE.BaseTest.__init__( self )
        self.dut    = None
        self.dutDev = None
        self.server = None
        self.soft   = None

    def Test( self, aArgs ):
        """DS Service state/transition test"""
        dutName  = ''
        mode     = ''
        seed     = 0
        loopback = None

        # parse command line arguments
        try:
            dutName = aArgs[1]
            mode    = aArgs[2]
            seed    = int( aArgs[3] )
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( aArgs )) )

        # create renderer CP and subscribe for DS events
        if dutName.lower() == 'local':
            loopback = True
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev', aLoopback=loopback )
            dutName = self.soft.name
        self.dutDev = dutName.split( ':' )[0]
        self.dut = Volkano.VolkanoDevice( dutName, aIsDut=True, aLoopback=loopback )
        self.dut.playlist.shuffle = False

        # start audio
        self.server = HttpServer.HttpServer( kAudioRoot )
        self.server.Start()

        # seed the random number generator (do AFTER DUT created or gets re-seeded)
        if not seed:
            seed = int( time.time() ) % 1000000
        self.log.Pass( '', 'Seeding random number generator with %d' % seed )
        random.seed( seed )

        # create test confgurations as specified by mode
        testConfigs = self._GetConfigs( mode )

        # test the configurations
        numConfig  = 0
        numConfigs = len( testConfigs )
        for config in testConfigs:
            numConfig += 1
            self.log.Info( '' )
            self.log.Info( '', 'Testing config ID# %d (%d of %d)' % \
                           (config.id, numConfig, numConfigs) )
            self.log.Info( '' )
            config.Setup()
            config.InvokeStimulus()
            config.CheckOutcome()

        # stop playback
        self.dut.playlist.Stop()

    def Cleanup( self ):
        """Perform post-test cleanup"""
        if self.dut:
            self.dut.Shutdown()
        if self.server:
            self.server.Shutdown()
        if self.soft:
            self.soft.Shutdown()
        BASE.BaseTest.Cleanup( self )

    def _GetConfigs( self, aMode ):
        """Create and return list of test configurations (as filtered by aMode)"""
        tracks  = Common.GetTracks( kTrackList, self.server )
        configs = []
        for entry in configTable:
            selected = False
            if aMode in ('all', 'ALL', 'All'):
                selected = True

            elif aMode in ('Play', 'Pause', 'Stop', 'SeekSecondsAbsolute',
                'SeekSecondsRelative', 'SeekIndex', 'SeekId', 'Next', 'Previous' ):
                if entry[6] == aMode:
                    selected = True

            elif aMode in ('Stopped', 'Playing', 'Paused'):
                if entry[1] == aMode:
                    selected = True

            elif aMode[0] == '[':
                vals = aMode[1:].split( ':' )
                if len( vals ) == 2:
                    # range of numbered configs in format [nn:mm]
                    try:
                        mini = int( vals[0] )
                        maxi = int( vals[1].strip( ']' ))
                        if mini <= entry[0] <= maxi:
                            selected = True
                    except:
                        pass
                else:
                    vals = aMode[1:-1].split( ',' )
                    if str( entry[0] ) in vals:
                        selected = True
            else:
                try:
                    # individual numbered config
                    if entry[0] == int( aMode ):
                        selected = True
                except:
                    pass

            if selected:
                configs.append( Config( self.log, self.dutDev, self.dut, entry, tracks ))

        return configs


# Macros for config table:
#   @m - valid random track index (excluding first and last 2 tracks) 1<@m<@N-2
#   @N - playlist length
#   @p - first track's ID
#   @q - valid random track ID (excluding first and last 2 tracks) @p+1<@q<@r-1
#   @r - last track's ID
#   @D - current track duration
#   @T - valid random track secs (excluding first and last 5s) 5<@T<@D-5
#   @x - current track index
#   @y - current track secs
#   @z - current track ID

configTable = \
    [
    #   | Preconditions                       | Stimulus                                       | Outcome
    # Id| State     PlLen  Track   Secs   Rpt | Action                MinVal     MaxVal     Err| State      Track         Secs
    (200, 'Stopped', '@N',    '0',  '0', 'off', 'Play'              ,        '',        '',   0, 'Playing',          '0',     '0'),
    (201, 'Stopped', '@N',   '@m',  '0', 'off', 'Play'              ,        '',        '',   0, 'Playing',         '@m',     '0'),
    (202, 'Stopped', '@N', '@N-1',  '0', 'off', 'Play'              ,        '',        '',   0, 'Playing',       '@N-1',     '0'),

    (210, 'Stopped', '@N',    '0',  '0', 'off', 'Pause'             ,        '',        '',   0, 'Stopped',          '0',     '0'),
    (211, 'Stopped', '@N',   '@m',  '0', 'off', 'Pause'             ,        '',        '',   0, 'Stopped',         '@m',     '0'),
    (212, 'Stopped', '@N', '@N-1',  '0', 'off', 'Pause'             ,        '',        '',   0, 'Stopped',       '@N-1',     '0'),

    (220, 'Stopped', '@N',    '0',  '0', 'off', 'Stop'              ,        '',        '',   0, 'Stopped',          '0',     '0'),
    (221, 'Stopped', '@N',   '@m',  '0', 'off', 'Stop'              ,        '',        '',   0, 'Stopped',         '@m',     '0'),
    (222, 'Stopped', '@N', '@N-1',  '0', 'off', 'Stop'              ,        '',        '',   0, 'Stopped',       '@N-1',     '0'),

    (230, 'Stopped', '@N',    '0',  '0', 'off', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',          '0',     '0'),
    (231, 'Stopped', '@N',    '0',  '0', 'off', 'SeekSecondAbsolute',       '1',        '',   0, 'Playing',          '0',    '@y'),
    (232, 'Stopped', '@N',   '@m',  '0', 'off', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',         '@m',     '0'),
    (233, 'Stopped', '@N',   '@m',  '0', 'off', 'SeekSecondAbsolute',       '1',        '',   0, 'Playing',         '@m',    '@y'),
    (234, 'Stopped', '@N', '@N-1',  '0', 'off', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',       '@N-1',     '0'),
    (235, 'Stopped', '@N', '@N-1',  '0', 'off', 'SeekSecondAbsolute',       '1',        '',   0, 'Playing',       '@N-1',    '@y'),

    (240, 'Stopped', '@N',    '0',  '0', 'off', 'SeekSecondRelative',       '0',       '0',   0, 'Playing',          '0',     '0'),
    (241, 'Stopped', '@N',    '0',  '0', 'off', 'SeekSecondRelative',       '1',        '',   0, 'Playing',          '0',    '@y'),
    (242, 'Stopped', '@N',    '0',  '0', 'off', 'SeekSecondRelative',        '',      '-1',   0, 'Playing',          '0',     '0'),
    (243, 'Stopped', '@N',   '@m',  '0', 'off', 'SeekSecondRelative',       '0',       '0',   0, 'Playing',         '@m',     '0'),
    (244, 'Stopped', '@N',   '@m',  '0', 'off', 'SeekSecondRelative',       '1',        '',   0, 'Playing',         '@m',    '@y'),
    (245, 'Stopped', '@N',   '@m',  '0', 'off', 'SeekSecondRelative',        '',      '-1',   0, 'Playing',         '@m',     '0'),
    (246, 'Stopped', '@N', '@N-1',  '0', 'off', 'SeekSecondRelative',       '0',       '0',   0, 'Playing',       '@N-1',     '0'),
    (247, 'Stopped', '@N', '@N-1',  '0', 'off', 'SeekSecondRelative',       '1',        '',   0, 'Playing',       '@N-1',    '@y'),
    (248, 'Stopped', '@N', '@N-1',  '0', 'off', 'SeekSecondRelative',        '',      '-1',   0, 'Playing',       '@N-1',     '0'),

    (250, 'Stopped', '@N',    '0',  '0', 'off', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (251, 'Stopped', '@N',    '0',  '0', 'off', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (252, 'Stopped', '@N',    '0',  '0', 'off', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (253, 'Stopped', '@N',    '0',  '0', 'off', 'SeekIndex'         ,      '@N',        '', 802, 'Stopped',          '0',     '0'),
    (254, 'Stopped', '@N',   '@m',  '0', 'off', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (255, 'Stopped', '@N',   '@m',  '0', 'off', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (256, 'Stopped', '@N',   '@m',  '0', 'off', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (257, 'Stopped', '@N',   '@m',  '0', 'off', 'SeekIndex'         ,      '@N',        '', 802, 'Stopped',         '@m',     '0'),
    (258, 'Stopped', '@N', '@N-1',  '0', 'off', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (259, 'Stopped', '@N', '@N-1',  '0', 'off', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (260, 'Stopped', '@N', '@N-1',  '0', 'off', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (261, 'Stopped', '@N', '@N-1',  '0', 'off', 'SeekIndex'         ,      '@N',        '', 802, 'Stopped',       '@N-1',     '0'),

    (270, 'Stopped', '@N',    '0',  '0',  'on', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (271, 'Stopped', '@N',    '0',  '0',  'on', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (272, 'Stopped', '@N',    '0',  '0',  'on', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (273, 'Stopped', '@N',    '0',  '0',  'on', 'SeekIndex'         ,      '@N',        '', 802, 'Stopped',          '0',     '0'),
    (274, 'Stopped', '@N',   '@m',  '0',  'on', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (275, 'Stopped', '@N',   '@m',  '0',  'on', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (276, 'Stopped', '@N',   '@m',  '0',  'on', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (277, 'Stopped', '@N',   '@m',  '0',  'on', 'SeekIndex'         ,      '@N',        '', 802, 'Stopped',         '@m',     '0'),
    (278, 'Stopped', '@N', '@N-1',  '0',  'on', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (279, 'Stopped', '@N', '@N-1',  '0',  'on', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (280, 'Stopped', '@N', '@N-1',  '0',  'on', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (281, 'Stopped', '@N', '@N-1',  '0',  'on', 'SeekIndex'         ,      '@N',        '', 802, 'Stopped',       '@N-1',     '0'),

    # (290, 'Stopped', '@N',   '@p',  '0', 'off', 'SeekId'            ,        '',    '@p-1', 802, 'Stopped',         '@p',     '0'),
    # (291, 'Stopped', '@N',   '@p',  '0', 'off', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',         '@p',     '0'),
    # (292, 'Stopped', '@N',   '@p',  '0', 'off', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (293, 'Stopped', '@N',   '@p',  '0', 'off', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',         '@r',     '0'),
    # (294, 'Stopped', '@N',   '@p',  '0', 'off', 'SeekId'            ,    '@r+1',        '', 802, 'Stopped',         '@p',     '0'),
    # (295, 'Stopped', '@N',   '@q',  '0', 'off', 'SeekId'            ,        '',    '@p-1', 802, 'Stopped',         '@q',     '0'),
    # (296, 'Stopped', '@N',   '@q',  '0', 'off', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',         '@p',     '0'),
    # (297, 'Stopped', '@N',   '@q',  '0', 'off', 'SeekId'                 '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (298, 'Stopped', '@N',   '@q',  '0', 'off', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',         '@r',     '0'),
    # (299, 'Stopped', '@N',   '@q',  '0', 'off', 'SeekId'            ,    '@r+1',        '', 802, 'Stopped',         '@m',     '0'),
    # (300, 'Stopped', '@N',   '@r',  '0', 'off', 'SeekId'            ,        '',    '@p-1', 802, 'Stopped',         '@r',     '0'),
    # (301, 'Stopped', '@N',   '@r',  '0', 'off', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',         '@p',     '0'),
    # (302, 'Stopped', '@N',   '@r',  '0', 'off', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (303, 'Stopped', '@N',   '@r',  '0', 'off', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',         '@r',     '0'),
    # (304, 'Stopped', '@N',   '@r',  '0', 'off', 'SeekId'            ,    '@r+1',        '', 802, 'Stopped',         '@r',     '0'),
    #
    # (310, 'Stopped', '@N',   '@p',  '0',  'on', 'SeekId'            ,        '',    '@p-1', 802, 'Stopped',         '@p',     '0'),
    # (311, 'Stopped', '@N',   '@p',  '0',  'on', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),
    # (312, 'Stopped', '@N',   '@p',  '0',  'on', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (313, 'Stopped', '@N',   '@p',  '0',  'on', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',       '@N-1',     '0'),
    # (314, 'Stopped', '@N',   '@p',  '0',  'on', 'SeekId'            ,    '@r+1',        '', 802, 'Stopped',          '0',     '0'),
    # (315, 'Stopped', '@N',   '@q',  '0',  'on', 'SeekId'            ,        '',    '@p-1', 802, 'Stopped',         '@q',     '0'),
    # (316, 'Stopped', '@N',   '@q',  '0',  'on', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),
    # (317, 'Stopped', '@N',   '@q',  '0',  'on', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (318, 'Stopped', '@N',   '@q',  '0',  'on', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',       '@N-1',     '0'),
    # (319, 'Stopped', '@N',   '@q',  '0',  'on', 'SeekId'            ,    '@r+1',        '', 802, 'Stopped',         '@m',     '0'),
    # (320, 'Stopped', '@N',   '@r',  '0',  'on', 'SeekId'            ,        '',    '@p-1', 802, 'Stopped',         '@r',     '0'),
    # (321, 'Stopped', '@N',   '@r',  '0',  'on', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),
    # (322, 'Stopped', '@N',   '@r',  '0',  'on', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (323, 'Stopped', '@N',   '@r',  '0',  'on', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',       '@N-1',     '0'),
    # (324, 'Stopped', '@N',   '@r',  '0',  'on', 'SeekId'            ,    '@r+1',        '', 802, 'Stopped',       '@N-1',     '0'),

    (330, 'Stopped', '@N',    '0',  '0', 'off', 'Next'              ,        '',        '',   0, 'Playing',          '1',     '0'),
    (331, 'Stopped', '@N',    '0',  '0', 'off', 'Previous'          ,        '',        '',   0, 'Stopped',          '0',     '0'),
    (332, 'Stopped', '@N',   '@m',  '0', 'off', 'Next'              ,        '',        '',   0, 'Playing',       '@m+1',     '0'),
    (333, 'Stopped', '@N',   '@m',  '0', 'off', 'Previous'          ,        '',        '',   0, 'Playing',       '@m-1',     '0'),
    (334, 'Stopped', '@N', '@N-1',  '0', 'off', 'Next'              ,        '',        '',   0, 'Stopped',          '0',     '0'),
    (335, 'Stopped', '@N', '@N-1',  '0', 'off', 'Previous'          ,        '',        '',   0, 'Playing',       '@N-2',     '0'),

    (340, 'Stopped', '@N',    '0',  '0',  'on', 'Next'              ,        '',        '',   0, 'Playing',          '1',     '0'),
    (341, 'Stopped', '@N',    '0',  '0',  'on', 'Previous'          ,        '',        '',   0, 'Playing',       '@N-1',     '0'),
    (342, 'Stopped', '@N',   '@m',  '0',  'on', 'Next'              ,        '',        '',   0, 'Playing',       '@m+1',     '0'),
    (343, 'Stopped', '@N',   '@m',  '0',  'on', 'Previous'          ,        '',        '',   0, 'Playing',       '@m-1',     '0'),
    (344, 'Stopped', '@N', '@N-1',  '0',  'on', 'Next'              ,        '',        '',   0, 'Playing',          '0',     '0'),
    (345, 'Stopped', '@N', '@N-1',  '0',  'on', 'Previous'          ,        '',        '',   0, 'Playing',       '@N-2',     '0'),


    #   | Preconditions                       | Stimulus                                       | Outcome
    # Id| State     PlLen  Track   Secs   Rpt | Action                MinVal     MaxVal     Err| State      Track         Secs
    (400, 'Playing', '@N',    '0', '@T', 'off', 'Play'              ,        '',        '',   0, 'Playing',          '0',     '0'),
    (401, 'Playing', '@N',   '@m', '@T', 'off', 'Play'              ,        '',        '',   0, 'Playing',         '@m',     '0'),
    (402, 'Playing', '@N', '@N-1', '@T', 'off', 'Play'              ,        '',        '',   0, 'Playing',       '@N-1',     '0'),

    (410, 'Playing', '@N',    '0', '@T', 'off', 'Pause'             ,        '',        '',   0, 'Paused' ,          '0',    '@T'),
    (411, 'Playing', '@N',   '@m', '@T', 'off', 'Pause'             ,        '',        '',   0, 'Paused' ,         '@m',    '@T'),
    (412, 'Playing', '@N', '@N-1', '@T', 'off', 'Pause'             ,        '',        '',   0, 'Paused' ,       '@N-1',    '@T'),

    (420, 'Playing', '@N',    '0', '@T', 'off', 'Stop'              ,        '',        '',   0, 'Stopped',          '0',     '0'),
    (421, 'Playing', '@N',   '@m', '@T', 'off', 'Stop'              ,        '',        '',   0, 'Stopped',         '@m',     '0'),
    (422, 'Playing', '@N', '@N-1', '@T', 'off', 'Stop'              ,        '',        '',   0, 'Stopped',       '@N-1',     '0'),

    (430, 'Playing', '@N',    '0', '@T', 'off', 'SeekSecondAbsolute',      '@T',   '@D-10',   0, 'Playing',          '0',    '@y'),
    (431, 'Playing', '@N',    '0', '@T', 'off', 'SeekSecondAbsolute',       '0',      '@T',   0, 'Playing',          '0',    '@y'),
    (432, 'Playing', '@N',    '0', '@T', 'off', 'SeekSecondAbsolute',      '@D',      '@D',   0, 'Playing',          '1',     '0'),
    (433, 'Playing', '@N',    '0', '@T', 'off', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',          '0',     '0'),
    (434, 'Playing', '@N',    '0', '@T', 'off', 'SeekSecondAbsolute',    '@D+1',        '',   0, 'Playing',          '1',     '0'),
    (435, 'Playing', '@N',   '@m', '@T', 'off', 'SeekSecondAbsolute',      '@T',   '@D-10',   0, 'Playing',         '@m',    '@y'),
    (436, 'Playing', '@N',   '@m', '@T', 'off', 'SeekSecondAbsolute',       '0',      '@T',   0, 'Playing',         '@m',    '@y'),
    (437, 'Playing', '@N',   '@m', '@T', 'off', 'SeekSecondAbsolute',      '@D',      '@D',   0, 'Playing',       '@m+1',     '0'),
    (438, 'Playing', '@N',   '@m', '@T', 'off', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',         '@m',     '0'),
    (439, 'Playing', '@N',   '@m', '@T', 'off', 'SeekSecondAbsolute',    '@D+1',        '',   0, 'Playing',       '@m+1',     '0'),
    (440, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekSecondAbsolute',      '@T',   '@D-10',   0, 'Playing',       '@N-1',    '@y'),
    (441, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekSecondAbsolute',       '0',      '@T',   0, 'Playing',       '@N-1',    '@y'),
    (442, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekSecondAbsolute',      '@D',      '@D',   0, 'Stopped',          '0',     '0'),
    (443, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',       '@N-1',     '0'),
    (444, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekSecondAbsolute',    '@D+1',        '',   0, 'Stopped',          '0',     '0'),

    (450, 'Playing', '@N',    '0', '@T',  'on', 'SeekSecondAbsolute',      '@T',   '@D-10',   0, 'Playing',          '0',    '@y'),
    (451, 'Playing', '@N',    '0', '@T',  'on', 'SeekSecondAbsolute',       '0',      '@T',   0, 'Playing',          '0',    '@y'),
    (452, 'Playing', '@N',    '0', '@T',  'on', 'SeekSecondAbsolute',      '@D',      '@D',   0, 'Playing',          '1',     '0'),
    (453, 'Playing', '@N',    '0', '@T',  'on', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',          '0',     '0'),
    (454, 'Playing', '@N',    '0', '@T',  'on', 'SeekSecondAbsolute',    '@D+1',        '',   0, 'Playing',          '1',     '0'),
    (455, 'Playing', '@N',   '@m', '@T',  'on', 'SeekSecondAbsolute',      '@T',   '@D-10',   0, 'Playing',         '@m',    '@y'),
    (456, 'Playing', '@N',   '@m', '@T',  'on', 'SeekSecondAbsolute',       '0',      '@T',   0, 'Playing',         '@m',    '@y'),
    (457, 'Playing', '@N',   '@m', '@T',  'on', 'SeekSecondAbsolute',      '@D',      '@D',   0, 'Playing',       '@m+1',     '0'),
    (458, 'Playing', '@N',   '@m', '@T',  'on', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',         '@m',     '0'),
    (459, 'Playing', '@N',   '@m', '@T',  'on', 'SeekSecondAbsolute',    '@D+1',        '',   0, 'Playing',       '@m+1',     '0'),
    (460, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekSecondAbsolute',      '@T',   '@D-10',   0, 'Playing',       '@N-1',    '@y'),
    (461, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekSecondAbsolute',       '0',      '@T',   0, 'Playing',       '@N-1',    '@y'),
    (462, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekSecondAbsolute',      '@D',      '@D',   0, 'Playing',          '0',     '0'),
    (463, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',       '@N-1',     '0'),
    (464, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekSecondAbsolute',    '@D+1',        '',   0, 'Playing',          '0',     '0'),

    (470, 'Playing', '@N',    '0', '@T', 'off', 'SeekSecondRelative',       '0',       '0',   0, 'Playing',          '0',    '@T'),
    (471, 'Playing', '@N',    '0', '@T', 'off', 'SeekSecondRelative',        '','@D-@T-10',   0, 'Playing',          '0', '@T+@y'),
    (472, 'Playing', '@N',    '0', '@T', 'off', 'SeekSecondRelative',   '-@T+1',      '-1',   0, 'Playing',          '0', '@T+@y'),
    (473, 'Playing', '@N',    '0', '@T', 'off', 'SeekSecondRelative',   '@D-@T',   '@D-@T',   0, 'Playing',          '1',     '0'),
    (474, 'Playing', '@N',    '0', '@T', 'off', 'SeekSecondRelative',     '-@T',     '-@T',   0, 'Playing',          '0',     '0'),
    (475, 'Playing', '@N',    '0', '@T', 'off', 'SeekSecondRelative', '@D-@T+1',        '',   0, 'Playing',          '1',     '0'),
    (476, 'Playing', '@N',    '0', '@T', 'off', 'SeekSecondRelative',        '',   '-@T-1',   0, 'Playing',          '0',     '0'),
    (477, 'Playing', '@N',   '@m', '@T', 'off', 'SeekSecondRelative',       '0',       '0',   0, 'Playing',         '@m',    '@T'),
    (478, 'Playing', '@N',   '@m', '@T', 'off', 'SeekSecondRelative',        '','@D-@T-10',   0, 'Playing',         '@m', '@T+@y'),
    (479, 'Playing', '@N',   '@m', '@T', 'off', 'SeekSecondRelative',   '-@T+1',      '-1',   0, 'Playing',         '@m', '@T+@y'),
    (480, 'Playing', '@N',   '@m', '@T', 'off', 'SeekSecondRelative',   '@D-@T',   '@D-@T',   0, 'Playing',       '@m+1',     '0'),
    (481, 'Playing', '@N',   '@m', '@T', 'off', 'SeekSecondRelative',     '-@T',     '-@T',   0, 'Playing',         '@m',     '0'),
    (482, 'Playing', '@N',   '@m', '@T', 'off', 'SeekSecondRelative', '@D-@T+1',        '',   0, 'Playing',       '@m+1',     '0'),
    (483, 'Playing', '@N',   '@m', '@T', 'off', 'SeekSecondRelative',        '',   '-@T-1',   0, 'Playing',         '@m',     '0'),
    (484, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekSecondRelative',       '0',       '0',   0, 'Playing',       '@N-1',    '@T'),
    (485, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekSecondRelative',        '','@D-@T-10',   0, 'Playing',       '@N-1', '@T+@y'),
    (486, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekSecondRelative',   '-@T+1',      '-1',   0, 'Playing',       '@N-1', '@T+@y'),
    (487, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekSecondRelative',   '@D-@T',   '@D-@T',   0, 'Stopped',          '0',     '0'),
    (488, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekSecondRelative',     '-@T',     '-@T',   0, 'Playing',       '@N-1',     '0'),
    (489, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekSecondRelative', '@D-@T+1',        '',   0, 'Stopped',          '0',     '0'),
    (490, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekSecondRelative',        '',   '-@T-1',   0, 'Playing',       '@N-1',     '0'),

    (500, 'Playing', '@N',    '0', '@T',  'on', 'SeekSecondRelative',       '0',       '0',   0, 'Playing',          '0',    '@T'),
    (501, 'Playing', '@N',    '0', '@T',  'on', 'SeekSecondRelative',        '','@D-@T-10',   0, 'Playing',          '0', '@T+@y'),
    (502, 'Playing', '@N',    '0', '@T',  'on', 'SeekSecondRelative',   '-@T+1',      '-1',   0, 'Playing',          '0', '@T+@y'),
    (503, 'Playing', '@N',    '0', '@T',  'on', 'SeekSecondRelative',   '@D-@T',   '@D-@T',   0, 'Playing',          '1',     '0'),
    (504, 'Playing', '@N',    '0', '@T',  'on', 'SeekSecondRelative',     '-@T',     '-@T',   0, 'Playing',          '0',     '0'),
    (505, 'Playing', '@N',    '0', '@T',  'on', 'SeekSecondRelative', '@D-@T+1',        '',   0, 'Playing',          '1',     '0'),
    (506, 'Playing', '@N',    '0', '@T',  'on', 'SeekSecondRelative',        '',   '-@T-1',   0, 'Playing',          '0',     '0'),
    (507, 'Playing', '@N',   '@m', '@T',  'on', 'SeekSecondRelative',       '0',       '0',   0, 'Playing',         '@m',    '@T'),
    (508, 'Playing', '@N',   '@m', '@T',  'on', 'SeekSecondRelative',        '','@D-@T-10',   0, 'Playing',         '@m', '@T+@y'),
    (509, 'Playing', '@N',   '@m', '@T',  'on', 'SeekSecondRelative',   '-@T+1',      '-1',   0, 'Playing',         '@m', '@T+@y'),
    (510, 'Playing', '@N',   '@m', '@T',  'on', 'SeekSecondRelative',   '@D-@T',   '@D-@T',   0, 'Playing',       '@m+1',     '0'),
    (511, 'Playing', '@N',   '@m', '@T',  'on', 'SeekSecondRelative',     '-@T',     '-@T',   0, 'Playing',         '@m',     '0'),
    (512, 'Playing', '@N',   '@m', '@T',  'on', 'SeekSecondRelative', '@D-@T+1',        '',   0, 'Playing',       '@m+1',     '0'),
    (513, 'Playing', '@N',   '@m', '@T',  'on', 'SeekSecondRelative',        '',   '-@T-1',   0, 'Playing',         '@m',     '0'),
    (514, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekSecondRelative',       '0',       '0',   0, 'Playing',       '@N-1',    '@T'),
    (515, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekSecondRelative',        '','@D-@T-10',   0, 'Playing',       '@N-1', '@T+@y'),
    (516, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekSecondRelative',   '-@T+1',      '-1',   0, 'Playing',       '@N-1', '@T+@y'),
    (517, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekSecondRelative',   '@D-@T',   '@D-@T',   0, 'Playing',          '0',     '0'),
    (518, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekSecondRelative',     '-@T',     '-@T',   0, 'Playing',       '@N-1',     '0'),
    (519, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekSecondRelative', '@D-@T+1',        '',   0, 'Playing',          '0',     '0'),
    (520, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekSecondRelative',        '',   '-@T-1',   0, 'Playing',       '@N-1',     '0'),

    (530, 'Playing', '@N',    '0', '@T', 'off', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (531, 'Playing', '@N',    '0', '@T', 'off', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (532, 'Playing', '@N',    '0', '@T', 'off', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (533, 'Playing', '@N',    '0', '@T', 'off', 'SeekIndex'         ,      '@N',        '', 802, 'Playing',          '0',    '@T'),
    (534, 'Playing', '@N',   '@m', '@T', 'off', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (535, 'Playing', '@N',   '@m', '@T', 'off', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (536, 'Playing', '@N',   '@m', '@T', 'off', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (537, 'Playing', '@N',   '@m', '@T', 'off', 'SeekIndex'         ,      '@N',        '', 802, 'Playing',         '@m',    '@T'),
    (538, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (539, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (540, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (541, 'Playing', '@N', '@N-1', '@T', 'off', 'SeekIndex'         ,      '@N',        '', 802, 'Playing',       '@N-1',    '@T'),

    (550, 'Playing', '@N',    '0', '@T',  'on', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (551, 'Playing', '@N',    '0', '@T',  'on', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (552, 'Playing', '@N',    '0', '@T',  'on', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (553, 'Playing', '@N',    '0', '@T',  'on', 'SeekIndex'         ,      '@N',        '', 802, 'Playing',          '0',    '@T'),
    (554, 'Playing', '@N',   '@m', '@T',  'on', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (555, 'Playing', '@N',   '@m', '@T',  'on', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (556, 'Playing', '@N',   '@m', '@T',  'on', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (557, 'Playing', '@N',   '@m', '@T',  'on', 'SeekIndex'         ,      '@N',        '', 802, 'Playing',         '@m',    '@T'),
    (558, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (559, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (560, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (561, 'Playing', '@N', '@N-1', '@T',  'on', 'SeekIndex'         ,      '@N',        '', 802, 'Playing',       '@N-1',    '@T'),

    # (570, 'Playing', '@N',   '@p', '@T', 'off', 'SeekId'            ,        '',    '@p-1', 802, 'Playing',         '@p',    '@T'),
    # (571, 'Playing', '@N',   '@p', '@T', 'off', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),
    # (572, 'Playing', '@N',   '@p', '@T', 'off', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (573, 'Playing', '@N',   '@p', '@T', 'off', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',       '@N-1',     '0'),
    # (574, 'Playing', '@N',   '@p', '@T', 'off', 'SeekId'            ,    '@r+1',        '', 802, 'Playing',         '@p',    '@T'),
    # (575, 'Playing', '@N',   '@q', '@T', 'off', 'SeekId'            ,        '',    '@p-1', 802, 'Playing',         '@q',    '@T'),
    # (576, 'Playing', '@N',   '@q', '@T', 'off', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),
    # (577, 'Playing', '@N',   '@q', '@T', 'off', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (578, 'Playing', '@N',   '@q', '@T', 'off', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',       '@N-1',     '0'),
    # (579, 'Playing', '@N',   '@q', '@T', 'off', 'SeekId'            ,    '@r+1',        '', 802, 'Playing',         '@m',    '@T'),
    # (580, 'Playing', '@N',   '@r', '@T', 'off', 'SeekId'            ,        '',    '@p-1', 802, 'Playing',         '@r',    '@T'),
    # (581, 'Playing', '@N',   '@r', '@T', 'off', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),
    # (582, 'Playing', '@N',   '@r', '@T', 'off', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (583, 'Playing', '@N',   '@r', '@T', 'off', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',       '@N-1',     '0'),
    # (584, 'Playing', '@N',   '@r', '@T', 'off', 'SeekId'            ,    '@r+1',        '', 802, 'Playing',       '@N-1',    '@T'),
    #
    # (590, 'Playing', '@N',   '@p', '@T',  'on', 'SeekId'            ,        '',    '@p-1', 802, 'Playing',         '@p',    '@T'),
    # (591, 'Playing', '@N',   '@p', '@T',  'on', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),
    # (592, 'Playing', '@N',   '@p', '@T',  'on', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (593, 'Playing', '@N',   '@p', '@T',  'on', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',       '@N-1',     '0'),
    # (594, 'Playing', '@N',   '@p', '@T',  'on', 'SeekId'            ,    '@r+1',        '', 802, 'Playing',         '@p',    '@T'),
    # (595, 'Playing', '@N',   '@q', '@T',  'on', 'SeekId'            ,        '',    '@p-1', 802, 'Playing',         '@q',    '@T'),
    # (596, 'Playing', '@N',   '@q', '@T',  'on', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),
    # (597, 'Playing', '@N',   '@q', '@T',  'on', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (598, 'Playing', '@N',   '@q', '@T',  'on', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',       '@N-1',     '0'),
    # (599, 'Playing', '@N',   '@q', '@T',  'on', 'SeekId'            ,    '@r+1',        '', 802, 'Playing',         '@q',    '@T'),
    # (600, 'Playing', '@N',   '@r', '@T',  'on', 'SeekId'            ,        '',    '@p-1', 802, 'Playing',         '@r',    '@T'),
    # (601, 'Playing', '@N',   '@r', '@T',  'on', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),
    # (602, 'Playing', '@N',   '@r', '@T',  'on', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (603, 'Playing', '@N',   '@r', '@T',  'on', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',       '@N-1',     '0'),
    # (604, 'Playing', '@N',   '@r', '@T',  'on', 'SeekId'            ,    '@r+1',        '', 802, 'Playing',         '@r',    '@T'),

    (610, 'Playing', '@N',    '0', '@T', 'off', 'Next'              ,        '',        '',   0, 'Playing',          '1',     '0'),
    (611, 'Playing', '@N',    '0', '@T', 'off', 'Previous'          ,        '',        '',   0, 'Stopped',         '0',      '0'),
    (612, 'Playing', '@N',   '@m', '@T', 'off', 'Next'              ,        '',        '',   0, 'Playing',       '@m+1',     '0'),
    (613, 'Playing', '@N',   '@m', '@T', 'off', 'Previous'          ,        '',        '',   0, 'Playing',       '@m-1',     '0'),
    (614, 'Playing', '@N', '@N-1', '@T', 'off', 'Next'              ,        '',        '',   0, 'Stopped',         '0',      '0'),
    (615, 'Playing', '@N', '@N-1', '@T', 'off', 'Previous'          ,        '',        '',   0, 'Playing',       '@N-2',     '0'),

    (620, 'Playing', '@N',    '0', '@T',  'on', 'Next'              ,        '',        '',   0, 'Playing',          '1',     '0'),
    (621, 'Playing', '@N',    '0', '@T',  'on', 'Previous'          ,        '',        '',   0, 'Playing',       '@N-1',     '0'),
    (622, 'Playing', '@N',   '@m', '@T',  'on', 'Next'              ,        '',        '',   0, 'Playing',       '@m+1',     '0'),
    (623, 'Playing', '@N',   '@m', '@T',  'on', 'Previous'          ,        '',        '',   0, 'Playing',       '@m-1',     '0'),
    (624, 'Playing', '@N', '@N-1', '@T',  'on', 'Next'              ,        '',        '',   0, 'Playing',          '0',     '0'),
    (625, 'Playing', '@N', '@N-1', '@T',  'on', 'Previous'          ,        '',        '',   0, 'Playing',       '@N-2',     '0'),


    #   | Preconditions                       | Stimulus                                       | Outcome
    # Id| State     PlLen  Track   Secs   Rpt | Action                MinVal     MaxVal    Err | State      Track         Secs
    (700, 'Paused' , '@N',    '0', '@T', 'off', 'Play'              ,        '',        '',   0, 'Playing',          '0',    '@T'),
    (701, 'Paused' , '@N',   '@m', '@T', 'off', 'Play'              ,        '',        '',   0, 'Playing',         '@m',    '@T'),
    (702, 'Paused' , '@N', '@N-1', '@T', 'off', 'Play'              ,        '',        '',   0, 'Playing',       '@N-1',    '@T'),

    (710, 'Paused' , '@N',    '0', '@T', 'off', 'Pause'             ,        '',        '',   0, 'Paused' ,          '0',    '@T'),
    (711, 'Paused' , '@N',   '@m', '@T', 'off', 'Pause'             ,        '',        '',   0, 'Paused' ,         '@m',    '@T'),
    (712, 'Paused' , '@N', '@N-1', '@T', 'off', 'Pause'             ,        '',        '',   0, 'Paused' ,       '@N-1',    '@T'),

    (720, 'Paused' , '@N',    '0', '@T', 'off', 'Stop'              ,        '',        '',   0, 'Stopped',          '0',     '0'),
    (721, 'Paused' , '@N',   '@m', '@T', 'off', 'Stop'              ,        '',        '',   0, 'Stopped',         '@m',     '0'),
    (722, 'Paused' , '@N', '@N-1', '@T', 'off', 'Stop'              ,        '',        '',   0, 'Stopped',       '@N-1',     '0'),

    (730, 'Paused' , '@N',    '0', '@T', 'off', 'SeekSecondAbsolute',      '@T',   '@D-10',   0, 'Playing',          '0',    '@y'),
    (731, 'Paused' , '@N',    '0', '@T', 'off', 'SeekSecondAbsolute',       '0',      '@T',   0, 'Playing',          '0',    '@y'),
    (732, 'Paused' , '@N',    '0', '@T', 'off', 'SeekSecondAbsolute',      '@D',      '@D',   0, 'Playing',          '1',     '0'),
    (733, 'Paused' , '@N',    '0', '@T', 'off', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',          '0',     '0'),
    (734, 'Paused' , '@N',    '0', '@T', 'off', 'SeekSecondAbsolute',    '@D+1',        '',   0, 'Playing',          '1',     '0'),
    (735, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekSecondAbsolute',      '@T',   '@D-10',   0, 'Playing',         '@m',    '@y'),
    (736, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekSecondAbsolute',       '0',      '@T',   0, 'Playing',         '@m',    '@y'),
    (737, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekSecondAbsolute',      '@D',      '@D',   0, 'Playing',       '@m+1',     '0'),
    (738, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',         '@m',     '0'),
    (739, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekSecondAbsolute',    '@D+1',        '',   0, 'Playing',       '@m+1',     '0'),
    (740, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekSecondAbsolute',      '@T',   '@D-10',   0, 'Playing',       '@N-1',    '@y'),
    (741, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekSecondAbsolute',       '0',      '@T',   0, 'Playing',       '@N-1',    '@y'),
    (742, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekSecondAbsolute',      '@D',      '@D',   0, 'Stopped',          '0',     '0'),
    (743, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',       '@N-1',     '0'),
    (744, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekSecondAbsolute',    '@D+1',        '',   0, 'Stopped',          '0',     '0'),

    (750, 'Paused' , '@N',    '0', '@T',  'on', 'SeekSecondAbsolute',      '@T',   '@D-10',   0, 'Playing',          '0',    '@y'),
    (751, 'Paused' , '@N',    '0', '@T',  'on', 'SeekSecondAbsolute',       '0',      '@T',   0, 'Playing',          '0',    '@y'),
    (752, 'Paused' , '@N',    '0', '@T',  'on', 'SeekSecondAbsolute',      '@D',      '@D',   0, 'Playing',          '1',     '0'),
    (753, 'Paused' , '@N',    '0', '@T',  'on', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',          '0',     '0'),
    (754, 'Paused' , '@N',    '0', '@T',  'on', 'SeekSecondAbsolute',    '@D+1',        '',   0, 'Playing',          '1',     '0'),
    (755, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekSecondAbsolute',      '@T',   '@D-10',   0, 'Playing',         '@m',    '@y'),
    (756, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekSecondAbsolute',       '0',      '@T',   0, 'Playing',         '@m',    '@y'),
    (757, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekSecondAbsolute',      '@D',      '@D',   0, 'Playing',       '@m+1',     '0'),
    (758, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',         '@m',     '0'),
    (759, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekSecondAbsolute',    '@D+1',        '',   0, 'Playing',       '@m+1',     '0'),
    (760, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekSecondAbsolute',      '@T',   '@D-10',   0, 'Playing',       '@N-1',    '@y'),
    (761, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekSecondAbsolute',       '0',      '@T',   0, 'Playing',       '@N-1',    '@y'),
    (762, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekSecondAbsolute',      '@D',      '@D',   0, 'Playing',          '0',     '0'),
    (763, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',       '@N-1',     '0'),
    (764, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekSecondAbsolute',    '@D+1',        '',   0, 'Playing',          '0',     '0'),

    (770, 'Paused' , '@N',    '0', '@T', 'off', 'SeekSecondRelative',       '0',       '0',   0, 'Playing',          '0',    '@T'),
    (771, 'Paused' , '@N',    '0', '@T', 'off', 'SeekSecondRelative',        '','@D-@T-10',   0, 'Playing',          '0', '@T+@y'),
    (772, 'Paused' , '@N',    '0', '@T', 'off', 'SeekSecondRelative',   '-@T+1',      '-1',   0, 'Playing',          '0', '@T+@y'),
    (773, 'Paused' , '@N',    '0', '@T', 'off', 'SeekSecondRelative',   '@D-@T',   '@D-@T',   0, 'Playing',          '1',     '0'),
    (774, 'Paused' , '@N',    '0', '@T', 'off', 'SeekSecondRelative',     '-@T',     '-@T',   0, 'Playing',          '0',     '0'),
    (775, 'Paused' , '@N',    '0', '@T', 'off', 'SeekSecondRelative', '@D-@T+1',        '',   0, 'Playing',          '1',     '0'),
    (776, 'Paused' , '@N',    '0', '@T', 'off', 'SeekSecondRelative',        '',   '-@T-1',   0, 'Playing',          '0',     '0'),
    (777, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekSecondRelative',       '0',       '0',   0, 'Playing',         '@m',    '@T'),
    (778, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekSecondRelative',        '','@D-@T-10',   0, 'Playing',         '@m', '@T+@y'),
    (779, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekSecondRelative',   '-@T+1',      '-1',   0, 'Playing',         '@m', '@T+@y'),
    (780, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekSecondRelative',   '@D-@T',   '@D-@T',   0, 'Playing',       '@m+1',     '0'),
    (781, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekSecondRelative',     '-@T',     '-@T',   0, 'Playing',         '@m',     '0'),
    (782, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekSecondRelative', '@D-@T+1',        '',   0, 'Playing',       '@m+1',     '0'),
    (783, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekSecondRelative',        '',   '-@T-1',   0, 'Playing',         '@m',     '0'),
    (784, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekSecondRelative',       '0',       '0',   0, 'Playing',       '@N-1',    '@T'),
    (785, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekSecondRelative',        '','@D-@T-10',   0, 'Playing',       '@N-1', '@T+@y'),
    (786, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekSecondRelative',   '-@T+1',      '-1',   0, 'Playing',       '@N-1', '@T+@y'),
    (787, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekSecondRelative',   '@D-@T',   '@D-@T',   0, 'Stopped',          '0',     '0'),
    (788, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekSecondRelative',     '-@T',     '-@T',   0, 'Playing',       '@N-1',     '0'),
    (789, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekSecondRelative', '@D-@T+1',        '',   0, 'Stopped',          '0',     '0'),
    (790, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekSecondRelative',        '',   '-@T-1',   0, 'Playing',       '@N-1',     '0'),

    (800, 'Paused' , '@N',    '0', '@T',  'on', 'SeekSecondRelative',       '0',       '0',   0, 'Playing',          '0',    '@T'),
    (801, 'Paused' , '@N',    '0', '@T',  'on', 'SeekSecondRelative',        '','@D-@T-10',   0, 'Playing',          '0', '@T+@y'),
    (802, 'Paused' , '@N',    '0', '@T',  'on', 'SeekSecondRelative',   '-@T+1',      '-1',   0, 'Playing',          '0', '@T+@y'),
    (803, 'Paused' , '@N',    '0', '@T',  'on', 'SeekSecondRelative',   '@D-@T',   '@D-@T',   0, 'Playing',          '1',     '0'),
    (804, 'Paused' , '@N',    '0', '@T',  'on', 'SeekSecondRelative',     '-@T',     '-@T',   0, 'Playing',          '0',     '0'),
    (805, 'Paused' , '@N',    '0', '@T',  'on', 'SeekSecondRelative', '@D-@T+1',        '',   0, 'Playing',          '1',     '0'),
    (806, 'Paused' , '@N',    '0', '@T',  'on', 'SeekSecondRelative',        '',   '-@T-1',   0, 'Playing',          '0',     '0'),
    (807, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekSecondRelative',       '0',       '0',   0, 'Playing',         '@m',    '@T'),
    (808, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekSecondRelative',        '','@D-@T-10',   0, 'Playing',         '@m', '@T+@y'),
    (809, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekSecondRelative',   '-@T+1',      '-1',   0, 'Playing',         '@m', '@T+@y'),
    (810, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekSecondRelative',   '@D-@T',   '@D-@T',   0, 'Playing',       '@m+1',     '0'),
    (811, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekSecondRelative',     '-@T',     '-@T',   0, 'Playing',         '@m',     '0'),
    (812, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekSecondRelative', '@D-@T+1',        '',   0, 'Playing',       '@m+1',     '0'),
    (813, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekSecondRelative',        '',   '-@T-1',   0, 'Playing',         '@m',     '0'),
    (814, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekSecondRelative',       '0',       '0',   0, 'Playing',       '@N-1',    '@T'),
    (815, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekSecondRelative',        '','@D-@T-10',   0, 'Playing',       '@N-1', '@T+@y'),
    (816, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekSecondRelative',   '-@T+1',      '-1',   0, 'Playing',       '@N-1', '@T+@y'),
    (817, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekSecondRelative',   '@D-@T',   '@D-@T',   0, 'Playing',          '0',     '0'),
    (818, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekSecondRelative',     '-@T',     '-@T',   0, 'Playing',       '@N-1',     '0'),
    (819, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekSecondRelative', '@D-@T+1',        '',   0, 'Playing',          '0',     '0'),
    (820, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekSecondRelative',        '',   '-@T-1',   0, 'Playing',       '@N-1',     '0'),

    (830, 'Paused' , '@N',    '0', '@T', 'off', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (831, 'Paused' , '@N',    '0', '@T', 'off', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (832, 'Paused' , '@N',    '0', '@T', 'off', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (833, 'Paused' , '@N',    '0', '@T', 'off', 'SeekIndex'         ,      '@N',        '', 802, 'Paused',           '0',    '@T'),
    (834, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (835, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (836, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (837, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekIndex'         ,      '@N',        '', 802, 'Paused',          '@m',    '@T'),
    (838, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (839, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (840, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (841, 'Paused' , '@N', '@N-1', '@T', 'off', 'SeekIndex'         ,      '@N',        '', 802, 'Paused',        '@N-1',    '@T'),

    (850, 'Paused' , '@N',    '0', '@T',  'on', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (851, 'Paused' , '@N',    '0', '@T',  'on', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (852, 'Paused' , '@N',    '0', '@T',  'on', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (853, 'Paused' , '@N',    '0', '@T',  'on', 'SeekIndex'         ,      '@N',        '', 802, 'Paused',           '0',    '@T'),
    (854, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (855, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (856, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (857, 'Paused' , '@N',   '@m', '@T',  'on', 'SeekIndex'         ,      '@N',        '', 802, 'Paused',          '@m',    '@T'),
    (858, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekIndex'         ,       '0',       '0',   0, 'Playing',          '0',     '0'),
    (859, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
    (860, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekIndex'         ,    '@N-1',    '@N-1',   0, 'Playing',       '@N-1',     '0'),
    (861, 'Paused' , '@N', '@N-1', '@T',  'on', 'SeekIndex'         ,      '@N',        '', 802, 'Paused',        '@N-1',    '@T'),

    # (870, 'Paused' , '@N',   '@p', '@T', 'off', 'SeekId'            ,        '',    '@p-1', 802, 'Paused',          '@p',    '@T'),
    # (871, 'Paused' , '@N',   '@p', '@T', 'off', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),
    # (872, 'Paused' , '@N',   '@p', '@T', 'off', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (873, 'Paused' , '@N',   '@p', '@T', 'off', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',       '@N-1',     '0'),
    # (874, 'Paused' , '@N',   '@p', '@T', 'off', 'SeekId'            ,    '@r+1',        '', 802, 'Paused',          '@p',    '@T'),
    # (875, 'Paused' , '@N',   '@q', '@T', 'off', 'SeekId'            ,        '',    '@p-1', 802, 'Paused',          '@q',    '@T'),
    # (876, 'Paused' , '@N',   '@q', '@T', 'off', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),
    # (877, 'Paused' , '@N',   '@q', '@T', 'off', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (878, 'Paused' , '@N',   '@q', '@T', 'off', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',       '@N-1',     '0'),
    # (879, 'Paused' , '@N',   '@q', '@T', 'off', 'SeekId'            ,    '@r+1',        '', 802, 'Paused',          '@q',    '@T'),
    # (880, 'Paused' , '@N',   '@r', '@T', 'off', 'SeekId'            ,        '',    '@p-1', 802, 'Paused',          '@r',    '@T'),
    # (881, 'Paused' , '@N',   '@r', '@T', 'off', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),
    # (882, 'Paused' , '@N',   '@r', '@T', 'off', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (883, 'Paused' , '@N',   '@r', '@T', 'off', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',       '@N-1',     '0'),
    # (884, 'Paused' , '@N',   '@r', '@T', 'off', 'SeekId'            ,    '@r+1',        '', 802, 'Paused',          '@r',    '@T'),
    #
    # (890, 'Paused' , '@N',   '@p', '@T',  'on', 'SeekId'            ,        '',    '@p-1', 802, 'Paused',          '@p',    '@T'),
    # (891, 'Paused' , '@N',   '@p', '@T',  'on', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),
    # (892, 'Paused' , '@N',   '@p', '@T',  'on', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (893, 'Paused' , '@N',   '@p', '@T',  'on', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',       '@N-1',     '0'),
    # (894, 'Paused' , '@N',   '@p', '@T',  'on', 'SeekId'            ,    '@r+1',        '', 802, 'Paused',          '@p',    '@T'),
    # (895, 'Paused' , '@N',   '@q', '@T',  'on', 'SeekId'            ,        '',    '@p-1', 802, 'Paused',          '@q',    '@T'),
    # (896, 'Paused' , '@N',   '@q', '@T',  'on', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),
    # (897, 'Paused' , '@N',   '@q', '@T',  'on', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (898, 'Paused' , '@N',   '@q', '@T',  'on', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',       '@N-1',     '0'),
    # (899, 'Paused' , '@N',   '@q', '@T',  'on', 'SeekId'            ,    '@r+1',        '', 802, 'Paused',          '@q',    '@T'),
    # (900, 'Paused' , '@N',   '@r', '@T',  'on', 'SeekId'            ,        '',    '@p-1', 802, 'Paused',          '@r',    '@T'),
    # (901, 'Paused' , '@N',   '@r', '@T',  'on', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),
    # (902, 'Paused' , '@N',   '@r', '@T',  'on', 'SeekId'            ,    '@p+1',    '@r-1',   0, 'Playing',         '@x',     '0'),
    # (903, 'Paused' , '@N',   '@r', '@T',  'on', 'SeekId'            ,      '@r',      '@r',   0, 'Playing',       '@N-1',     '0'),
    # (904, 'Paused' , '@N',   '@r', '@T',  'on', 'SeekId'            ,    '@r+1',        '', 802, 'Paused',          '@r',    '@T'),

    (910, 'Paused' , '@N',    '0', '@T', 'off', 'Next'              ,        '',        '',   0, 'Playing',          '1',     '0'),
    (911, 'Paused' , '@N',    '0', '@T', 'off', 'Previous'          ,        '',        '',   0, 'Stopped',          '0',     '0'),
    (912, 'Paused' , '@N',   '@m', '@T', 'off', 'Next'              ,        '',        '',   0, 'Playing',       '@m+1',     '0'),
    (913, 'Paused' , '@N',   '@m', '@T', 'off', 'Previous'          ,        '',        '',   0, 'Playing',       '@m-1',     '0'),
    (914, 'Paused' , '@N', '@N-1', '@T', 'off', 'Next'              ,        '',        '',   0, 'Stopped',          '0',     '0'),
    (915, 'Paused' , '@N', '@N-1', '@T', 'off', 'Previous'          ,        '',        '',   0, 'Playing',       '@N-2',     '0'),

    (920, 'Paused' , '@N',    '0', '@T',  'on', 'Next'              ,        '',        '',   0, 'Playing',          '1',     '0'),
    (921, 'Paused' , '@N',    '0', '@T',  'on', 'Previous'          ,        '',        '',   0, 'Playing',       '@N-1',     '0'),
    (922, 'Paused' , '@N',   '@m', '@T',  'on', 'Next'              ,        '',        '',   0, 'Playing',       '@m+1',     '0'),
    (923, 'Paused' , '@N',   '@m', '@T',  'on', 'Previous'          ,        '',        '',   0, 'Playing',       '@m-1',     '0'),
    (924, 'Paused' , '@N', '@N-1', '@T',  'on', 'Next'              ,        '',        '',   0, 'Playing',          '0',     '0'),
    (925, 'Paused' , '@N', '@N-1', '@T',  'on', 'Previous'          ,        '',        '',   0, 'Playing',       '@N-2',     '0')
    ]


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
