#!/usr/bin/env python
"""TestPlaylistHandling - test Playlist controls (insert/delete/select mode)

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - test mode 
              - all          for all configs sequentially
              - <num>        for config number <num>
              - [min:max]    for range of (numbered) configs
              - <stim>       for stimulus (Play, Pause, Stop,
                                    SeekSecondsAbsolute, SeekSecondsRelative,
                                    SeekTrackAbsolute, SeekTrackRelative)
              - <pre-state>  for precon state (Stopped, Playing, Paused)
    arg#3 - random number generator seed (0 for 'random')
            by passing this, test scenarious containing random data can be
            replicated - the seed used is logged at the start of execution
            
Tests operation of Playlist control. Each condition is tested as a standalone
operation - no aggregation of actions due to async operation tested.
""" 
import _FunctionalTest
import BaseTest                   as BASE
import Upnp.ControlPoints.Volkano as Volkano
import Utils.Network.HttpServer   as HttpServer
import Utils.Common               as Common
import _SoftPlayer                as SoftPlayer
import os
import random
import sys
import time
import threading

kAudioRoot = os.path.join( _FunctionalTest.audioDir, 'MusicTracks/' )
kTrackList = os.path.join( kAudioRoot, 'TrackList.xml' )


class Config:
    """Test configuration for Playlist service testing"""
    
    class Precon:
        """Configuration subclass for precondition info and setup"""
        
        def __init__( self, aId, aState, aPlLen, aTrack, aSecs,
                      aRepeat, aShuffle, aTracks, aLog, aDev ):
            """Initialise class data"""
            self.id       = aId
            self.state    = aState
            self.plLen    = None
            self.plLen    = self._SubstMacros( aPlLen )
            self.track    = self._SubstMacros( aTrack )
            self.secs     = aSecs
            self.repeat   = self._SubstMacros( aRepeat )
            self.shuffle  = self._SubstMacros( aShuffle )
            self.duration = None
            self.log      = aLog
            self.idArray  = []
            self.dev      = aDev
            
            # create random playlist
            self.playlist = []
            for i in range( self.plLen ):
                self.playlist.append( aTracks[random.randint( 0, len( aTracks )-1)])
                                
        def Setup( self, aDut ):
            """Setup preconditions on the dut"""
            idEvt       = threading.Event()
            durationEvt = threading.Event()
            pausedEvt   = threading.Event()
            playingEvt  = threading.Event()
            stoppedEvt  = threading.Event()
            seekedEvt   = threading.Event()

            # noinspection PyUnusedLocal
            def _PlaylistEventCb( aService, aSvName, aSvVal, aSvSeq ):
                if aSvName == 'Id':
                    idEvt.set()
                elif aSvName == 'TransportState':
                    if aSvVal == 'Playing':
                        playingEvt.set()
                    elif aSvVal == 'Paused':
                        pausedEvt.set()
                    elif aSvVal == 'Stopped':
                        stoppedEvt.set()

            # noinspection PyUnusedLocal
            def _InfoEventCb( aService, aSvName, aSvVal, aSvSeq ):
                if aSvName == 'Duration' and aSvVal not in [0,'0']:
                    durationEvt.set()
            
            # noinspection PyUnusedLocal
            def _TimeEventCb( aService, aSvName, aSvVal, aSvSeq ):
                if aSvName == 'Seconds':
                    if self.secs == int( aSvVal ):
                        seekedEvt.set()

            # Add playlist
            self.log.Info( self.dev, 'Adding playlist of %d tracks' % self.plLen )
            aDut.playlist.DeleteAllTracks()
            aDut.playlist.AddSubscriber( _PlaylistEventCb )
            aDut.info.AddSubscriber( _InfoEventCb )
            aDut.time.AddSubscriber( _TimeEventCb )
            idArrayToken = aDut.playlist.idArrayToken
            aDut.playlist.AddPlaylist( self.playlist )

            # Check playlist add as expected
            if self.plLen > 0:
                self.log.FailUnless( self.dev, aDut.playlist.IdArrayChanged( idArrayToken ),
                    '[%d] ID array updated when playlist changed' % self.id )
                self.idArray = aDut.playlist.idArray
                measPlLen = len(self.idArray)
                self.log.FailUnless( self.dev, self.plLen==measPlLen,
                                     '[%d] Added %d tracks (requested %d)' % (self.id, measPlLen, self.plLen) )

            if self.track != -1:
                # Select specified track
                durationEvt.clear()
                if aDut.playlist.id != aDut.playlist.idArray[self.track]:
                    idEvt.clear()
                    aDut.playlist.SeekIndex( self.track )
                    idEvt.wait( 2 )
                    if aDut.playlist.id != aDut.playlist.idArray[self.track]:
                        # re-check in case of transient ID event on wrong track
                        idEvt.clear()
                        idEvt.wait( 2 )
                self.log.FailUnless( self.dev, aDut.playlist.id == aDut.playlist.idArray[self.track],
                                     '[%d] Selected track %s (got ID %s)' % (self.id, self.track,aDut.playlist.id) )

                # Setup transport state / track secs
                if self.state == 'Stopped':
                    stoppedEvt.clear()
                    aDut.playlist.Stop()
                    stoppedEvt.wait( 2 )
                elif self.state in ['Playing', 'Paused']:
                    if self.secs == '@T':
                        durationEvt.wait( 5 )
                        if not durationEvt.isSet():
                            self.log.Info( self.dev, 'Timeout waiting for duration' )
                            # the same as previous test track - quite likely
                            self.duration = 100
                        else:
                            self.duration = aDut.info.duration
                        self.secs = random.randint( 5, self.duration-5 )
                        playingEvt.clear()
                        seekedEvt.clear()
                        aDut.playlist.SeekSecondAbsolute( self.secs )
                        playingEvt.wait( 2 )
                        seekedEvt.wait( 2 )
                        self.log.FailUnless( self.dev, seekedEvt.is_set(),
                            '[%d] Current track secs %d' % (self.id, aDut.time.seconds) )

                    if self.state == 'Paused':
                        pausedEvt.clear()
                        aDut.playlist.Pause()
                        pausedEvt.wait( 2 )

                self.log.FailUnless( self.dev, aDut.playlist.transportState==self.state,
                                     '[%d] Transport State %s' % (self.id, aDut.playlist.transportState) )

            # Setup shuffle/repeat
            aDut.playlist.repeat = self.repeat
            aDut.playlist.shuffle = self.shuffle

            # clean up local subscriptions
            aDut.playlist.RemoveSubscriber( _PlaylistEventCb )                
            aDut.info.RemoveSubscriber( _InfoEventCb )                
            aDut.time.RemoveSubscriber( _TimeEventCb )

        def _SubstMacros( self, aArg ):
            """Substitute parameter macros with actual values.
               Valid macros are:
                @m - random track within playlist
                @N - playlist length -> random value between 8 and 30
                @R - random (on/off)
            """
            try:
                if not self.plLen:
                    aArg = aArg.replace( '@N', 'random.randint( 8, 30 )' )
                else:
                    aArg = aArg.replace( '@N', 'self.plLen' )
                aArg = aArg.replace( '@m', 'random.randint( 2, self.plLen-3 )' )
                aArg = aArg.replace( '@R', '("true","false")[random.randint( 0 ,1 )]' )
                subst = eval( aArg )
            except:
                subst = aArg
            return subst

        # noinspection PyUnusedLocal
        def _PlaylistEventCb( self, aService, aSvName, aSvVal, aSvSeq ):
            """Callback from Playlist service events"""
            if aSvName == 'TransportState':
                if aSvVal == 'Playing':
                    self.playingEvent.set()
                elif aSvVal == 'Paused':
                    self.pausedEvent.set()


    class Stimulus:
        """Configuration subclass for stimulus info and invokation"""
        
        def __init__( self, aAction, aMinVal, aMaxVal, aTracks, aPrecon ):
            """Initialise class data"""
            self.action = aAction
            self.precon = aPrecon
            self.minVal = aMinVal
            self.maxVal = aMaxVal
            self.val    = 0
            self.insId  = 0
            
            # get a random track (for use in insert)
            self.track = aTracks[random.randint( 0, len( aTracks )-1)]
            
        def Invoke( self, aDut ):
            """Invoke stimulus on specified dut"""
            if self.action in ['DeleteAllTracks']:
                getattr( aDut.playlist, self.action )()
                
            elif self.action in ['repeat','shuffle']:
                exec( 'aDut.playlist.%s="%s"' % (self.action, self.minVal) )
            else:
                mini = self._SubstMacros( self.minVal )
                maxi = self._SubstMacros( self.maxVal )

                if mini == '':
                    self.val = random.randint( maxi-100, maxi )
                elif maxi == '':
                    self.val = random.randint( mini, mini+100 )
                elif mini == maxi:
                    self.val = mini
                else:
                    self.val = random.randint( mini, maxi )
                if self.action in ['Delete']:
                    tId = 0
                    try:
                        tId = self.precon.idArray[self.val]
                    except:
                        self.precon.log.Warn( self.dev, '[D] self.precon.idArray: %s' % self.precon.idArray )
                        self.precon.log.Warn( self.dev, '[D] self.val:            %s' % self.val )
                    getattr( aDut.playlist, self.action )( tId )
                    
                else: # Insert
                    tId = 0
                    if self.val != -1:
                        try:
                            tId = self.precon.idArray[self.val]
                        except:
                            self.precon.log.Warn( self.dev, '[I] self.precon.idArray: %s' % self.precon.idArray )
                            self.precon.log.Warn( self.dev, '[I] self.val:            %s' % self.val )
                    self.insId = aDut.playlist.AddTrack( self.track, tId )

        # noinspection PyMethodMayBeStatic
        def _SubstMacros( self, aArg ):
            """Substitute parameter macros with actual values. Some of these are
               NOT KNOWN at __init__ time, so call the substs at Invoke() time
               Valid macros are:
                @m - current track
                @N - playlist length
            """
            try:
                aArg = aArg.replace( '@m', 'self.precon.track' )
                aArg = aArg.replace( '@N', 'self.precon.plLen' )
                subst = eval( aArg )
            except:
                subst = aArg
            return subst

        
    class Outcome:
        """Configuration subclass for outcome checking"""
        
        def __init__( self, aId, aState, aPlLen, aRepeat, aShuffle, aTrack,
                      aSecs, aPrecon, aStim, aLog, aDev ):
            """Initialise class data"""
            self.id      = aId
            self.state   = aState
            self.plLen   = aPlLen
            self.repeat  = aRepeat
            self.shuffle = aShuffle
            self.track   = aTrack
            self.secs    = aSecs
            self.precon  = aPrecon
            self.stim    = aStim
            self.log     = aLog
            self.dev     = aDev

        def Check( self, aDut ):
            """Check outcome on specified dut"""
            delay1       = 2
            delay2       = 5
            expOrder     = self._CalcOrder()
            expState     = self.state
            expPlLen     = int( self._SubstMacros( self.plLen ))
            expTrack     = int( self._SubstMacros( self.track ))
            expSecs      = int( self._SubstMacros( self.secs ))
            expRepeat    = self.repeat
            expShuffle   = self.shuffle
            
            if expRepeat  == '@R': expRepeat  = self.precon.repeat
            if expShuffle == '@R': expShuffle = self.precon.shuffle
            
            # values may or may not be evented depending on whether they have
            # changed, hence cannot rely on events to inform us that action
            # execution has completed. Just wait a few secs before checking
            time.sleep( delay1 )
            
            # one-off checks of static data for testpoint
            polledIdArray   = aDut.playlist.polledIdArray
            idArrayToken    = aDut.playlist.idArrayToken
            polledTracksMax = aDut.playlist.polledTracksMax

            self.log.FailUnless( self.dev, polledIdArray==aDut.playlist.idArray,
                '[%d] (%s/%s) Polled/Evented IdArray' %
                 (self.id, polledIdArray, aDut.playlist.idArray) )
            self.log.FailUnless( self.dev, polledTracksMax==aDut.playlist.tracksMax,
                '[%d] (%d/%d) Polled/Evented maximum playlist tracks' %
                (self.id, polledTracksMax, aDut.playlist.tracksMax) )
            
            # these are checked after both delay periods
            if expState == 'Playing' and aDut.playlist.transportState == 'Playing':            
                expSecs += delay1
                (expState, expTrack, expSecs) = \
                    self._RecalcExpected( aDut, expState, expTrack, expSecs )
            self._CheckValues( aDut, expOrder, expState, expPlLen, expTrack,
                               expSecs, expRepeat, expShuffle, delay1 )

            # wait a few more secs and check that values are changing correctly
            # (if Playing) or not changing as expected (if Paused, Stopped)
            time.sleep( delay2 )
            if expState == 'Playing' and aDut.playlist.transportState == 'Playing':
                expSecs += delay2
                (expState, expTrack, expSecs) = \
                    self._RecalcExpected( aDut, expState, expTrack, expSecs )
            self._CheckValues( aDut, expOrder, expState, expPlLen, expTrack,
                               expSecs, expRepeat, expShuffle, delay1+delay2 )
            
            # check no ID array update whilst taking results
            self.log.FailUnless( self.dev, aDut.playlist.IdArrayChanged( idArrayToken )==0, 
                '[%d] ID array update when no playlist changed' % self.id )

        def _CheckValues( self, aDut, aOrder, aState, aPlLen, aTrack, aSecs,
                          aRepeat, aShuffle, aAfter ):
            """Check values from DS are as expected"""
            actualOrder   = aDut.playlist.idArray
            actualPlLen   = len( actualOrder )
            actualState   = aDut.playlist.transportState
            actualRepeat  = aDut.playlist.repeat
            actualShuffle = aDut.playlist.shuffle
            actualSecs    = aDut.time.seconds
            
            self.log.Info( '', '' )
            self._DoCheck( actualOrder, aOrder, 'Playlist Order', aAfter )
            self._DoCheck( actualState, aState, 'Transport State', aAfter )
            self._DoCheck( actualPlLen, aPlLen, 'Playlist Length', aAfter )
            self._DoCheck( actualRepeat, aRepeat, 'Repeat Mode', aAfter )
            self._DoCheck( actualShuffle, aShuffle, 'Shuffle Mode', aAfter )
            
            self.log.CheckLimits( self.dev, 'GELE', actualSecs, aSecs-2, aSecs+1,
                '[%d] Expected track seconds %ds after invoke' % (self.id, aAfter) )
            
            if aDut.playlist.id == 0:
                self._DoCheck( aDut.playlist.id, aTrack, 'Eop index', aAfter )
            else:
                try:
                    actualTrack = aDut.playlist.PlaylistIndex( aDut.playlist.id )
                    self._DoCheck( actualTrack, aTrack, 'Track Index', aAfter)
                except:
                    self.log.Fail( self.dev, '[%d] Unknown track ID %d' % (self.id, aDut.playlist.id) )
            self.log.Info( '', '' )
        
        def _DoCheck( self, aActual, aExpected, aTest, aAfter ):
            """Perform comparison, output log message"""
            if aExpected == 'true': aExpected = True
            if aExpected == 'false': aExpected = False
            self.log.FailUnless( self.dev, aActual == aExpected,
                '[%d] (%s/%s) Actual/Expected %s %ds after invoke' % 
                (self.id, aActual, aExpected, aTest, aAfter) )
            
        def _RecalcExpected( self, aDut, aState, aTrack, aSecs ):
            """Recalculate expected values after playback over time"""
            expState = aState
            expTrack = aTrack
            expSecs  = aSecs
            if expSecs > self.precon.duration:
                expSecs = expSecs - self.precon.duration
                expTrack += 1
                if expTrack >= self.precon.plLen:
                    expTrack = 0
                    if self.precon.repeat == 'false':
                        expState = 'Stopped'
            return expState, expTrack, expSecs
        
        def _CalcOrder( self ):
            order = None
            preOrder = self.precon.idArray
            if self.stim.action in ('repeat', 'shuffle'):
                order = preOrder
            elif self.stim.action == 'DeleteAllTracks':                
                order = []
            elif self.stim.action == 'Insert':
                order = preOrder
                order.insert( self.stim.val+1, self.stim.insId )
            elif self.stim.action == 'Delete':
                order = preOrder
                order.pop( self.stim.val )
            return order

        # noinspection PyMethodMayBeStatic
        def _SubstMacros( self, aArg ):
            """Substitute parameter macros with actual values. Some of these are
               NOT KNOWN at __init__ time, so call the substs at Check() time
               Valid macros are:
                @m - precon track
                @N - playlist length
                @T - precon track secs
            """
            try:
                aArg = aArg.replace( '@N', 'self.precon.plLen' )
                aArg = aArg.replace( '@m', 'self.precon.track' )
                aArg = aArg.replace( '@T', 'self.precon.secs' )
                subst = eval( aArg )
            except:
                subst = aArg
            return subst                        

    def __init__( self, aLog, aDut, aDev, aConf, aTracks ):
        """Initialise class (and sub-class) data"""
        self.log  = aLog
        self.id   = aConf[0]
        self.dut  = aDut
        self.pre  = self.Precon( self.id, aConf[1], aConf[2], aConf[3],
                    aConf[4], aConf[5], aConf[6], aTracks, self.log, aDev )
        self.stim = self.Stimulus( aConf[7], aConf[8], aConf[9], aTracks, self.pre )
        self.out  = self.Outcome( self.id, aConf[10], aConf[11], aConf[12],
                    aConf[13], aConf[14], aConf[15], self.pre, self.stim, self.log, aDev )
        
    def Setup( self ):
        self.pre.Setup( self.dut )
        
    def InvokeStimulus( self ):
        self.stim.Invoke( self.dut )
        
    def CheckOutcome( self ):
        self.out.Check(  self.dut )


class TestPlaylistHandling( BASE.BaseTest ):
    """Test Playlist Service operation (using UPnP as control method)"""

    def __init__( self ):
        """Constructor - initalise base class"""
        BASE.BaseTest.__init__( self )
        self.dut    = None
        self.dutDev = None
        self.server = None
        self.soft   = None
                
    def Test( self, aArgs ):
        """Playlist Service state/transition test"""
        dutName  = ''
        mode     = ''
        seed     = 0
        loopback = False

        # parse command line arguments
        try:
            dutName = aArgs[1]
            mode    = aArgs[2]
            seed    = int( aArgs[3] )
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( aArgs )) )

        # create DUT
        if dutName.lower() == 'local':
            loopback = True
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev', aLoopback=loopback )
###            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev', aLoopback=False )
            dutName = self.soft.name
        self.dutDev = dutName.split( ':' )[0]
        self.dut = Volkano.VolkanoDevice( dutName, aIsDut=True, aLoopback=loopback )
###        self.dut = Volkano.VolkanoDevice( dutName, aIsDut=True, aLoopback=False )
        self.dut.product.sourceIndex = 0

        # start audio server
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
            self.log.Header2( '', 'Testing config ID# %d: %s->%s (%d of %d)' %
                (config.id, config.pre.state, config.stim.action, numConfig, numConfigs) )
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
                
            elif aMode in ('DeleteAll','Delete','Insert','SetRepeat','SetShuffle'):
                if entry[7] == aMode:
                    selected = True
                    
            elif aMode in ('Stopped', 'Playing', 'Paused'):
                if entry[1] == aMode:
                    selected = True
                    
            elif aMode[0] == '[':
                # range of numbered configs in format [nn:mm]
                vals = aMode[1:].split( ':' )
                if len( vals ) == 2:
                    try:
                        mini = int( vals[0] )
                        maxi = int( vals[1].strip( ']' ))
                        if mini <= entry[0] <= maxi:
                            selected = True
                    except:
                        pass
            else:
                try:
                    # individual numbered config
                    if entry[0] == int( aMode ):
                        selected = True
                except:
                    pass

            if selected:
                configs.append( Config( self.log, self.dut, self.dutDev, entry, tracks ))
            
        return configs


configTable = \
    [
    #   | Preconditions                                  | Stimulus                         | Outcome
    # Id| State     PlLen  Track   Secs     Rpt   Shfl   | Action             Param1 Param2 | State      PlLen     Rpt     Shfl    Track  Secs
    (200, 'Stopped', '@N',    '0',  '0',    '@R',    '@R', 'DeleteAllTracks',     '',     '', 'Stopped',    '0',    '@R',    '@R',    '0',  '0'),
    (201, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'DeleteAllTracks',     '',     '', 'Stopped',    '0',    '@R',    '@R',    '0',  '0'),
    (202, 'Stopped', '@N', '@N-1',  '0',    '@R',    '@R', 'DeleteAllTracks',     '',     '', 'Stopped',    '0',    '@R',    '@R',    '0',  '0'),
    
    (210, 'Stopped', '@N',    '0',  '0',    '@R', 'false', 'Delete'         ,    '0',    '0', 'Stopped', '@N-1',    '@R',    '@R',    '0',  '0'),
    (211, 'Stopped', '@N',    '0',  '0',    '@R',    '@R', 'Delete'         ,    '1', '@N-2', 'Stopped', '@N-1',    '@R',    '@R',    '0',  '0'),
    (212, 'Stopped', '@N',    '0',  '0',    '@R',    '@R', 'Delete'         , '@N-1', '@N-1', 'Stopped', '@N-1',    '@R',    '@R',    '0',  '0'),
    (213, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'Delete'         ,    '0',    '0', 'Stopped', '@N-1',    '@R',    '@R', '@m-1',  '0'),
    (214, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'Delete'         ,    '1', '@m-1', 'Stopped', '@N-1',    '@R',    '@R', '@m-1',  '0'),
    (215, 'Stopped', '@N',   '@m',  '0',    '@R', 'false', 'Delete'         ,   '@m',   '@m', 'Stopped', '@N-1',    '@R',    '@R',   '@m',  '0'),
    (216, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'Delete'         , '@m+1', '@N-2', 'Stopped', '@N-1',    '@R',    '@R',   '@m',  '0'),
    (217, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'Delete'         , '@N-1', '@N-1', 'Stopped', '@N-1',    '@R',    '@R',   '@m',  '0'),
    (218, 'Stopped', '@N', '@N-1',  '0',    '@R',    '@R', 'Delete'         ,    '0',    '0', 'Stopped', '@N-1',    '@R',    '@R', '@N-2',  '0'),
    (219, 'Stopped', '@N', '@N-1',  '0',    '@R',    '@R', 'Delete'         ,    '1', '@N-2', 'Stopped', '@N-1',    '@R',    '@R', '@N-2',  '0'),
    (220, 'Stopped', '@N', '@N-1',  '0',  'true', 'false', 'Delete'         , '@N-1', '@N-1', 'Stopped', '@N-1',  'true',    '@R',    '0',  '0'),
    (221, 'Stopped', '@N', '@N-1',  '0', 'false', 'false', 'Delete'         , '@N-1', '@N-1', 'Stopped', '@N-1', 'false',    '@R',    '0',  '0'),

    (230, 'Stopped', '@N',    '0',  '0',    '@R',    '@R', 'Insert'         ,   '-1',   '-1', 'Stopped', '@N+1',    '@R',    '@R',    '1',  '0'),
    (231, 'Stopped', '@N',    '0',  '0',    '@R',    '@R', 'Insert'         ,    '0', '@N-2', 'Stopped', '@N+1',    '@R',    '@R',    '0',  '0'),
    (232, 'Stopped', '@N',    '0',  '0',    '@R',    '@R', 'Insert'         , '@N-1', '@N-1', 'Stopped', '@N+1',    '@R',    '@R',    '0',  '0'),
    (233, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'Insert'         ,   '-1',   '-1', 'Stopped', '@N+1',    '@R',    '@R', '@m+1',  '0'),
    (234, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'Insert'         ,    '0', '@m-1', 'Stopped', '@N+1',    '@R',    '@R', '@m+1',  '0'),
    (235, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'Insert'         ,   '@m', '@N-2', 'Stopped', '@N+1',    '@R',    '@R',   '@m',  '0'),
    (236, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'Insert'         , '@N-1', '@N-1', 'Stopped', '@N+1',    '@R',    '@R',   '@m',  '0'),
    (237, 'Stopped', '@N', '@N-1',  '0',    '@R',    '@R', 'Insert'         ,   '-1',   '-1', 'Stopped', '@N+1',    '@R',    '@R',   '@N',  '0'),
    (238, 'Stopped', '@N', '@N-1',  '0',    '@R',    '@R', 'Insert'         ,    '0', '@N-2', 'Stopped', '@N+1',    '@R',    '@R',   '@N',  '0'),
    (239, 'Stopped', '@N', '@N-1',  '0',    '@R',    '@R', 'Insert'         , '@N-1', '@N-1', 'Stopped', '@N+1',    '@R',    '@R', '@N-1',  '0'),
    
    (250, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'repeat'         ,   'on',     '', 'Stopped',   '@N',  'true',    '@R',   '@m',  '0'),
    (251, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'repeat'         ,  'off',     '', 'Stopped',   '@N', 'false',    '@R',   '@m',  '0'),
    (252, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'shuffle'        ,   'on',     '', 'Stopped',   '@N',    '@R',  'true',   '@m',  '0'),
    (253, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'shuffle'        ,  'off',     '', 'Stopped',   '@N',    '@R', 'false',   '@m',  '0'),

    
    #   | Preconditions                                  | Stimulus                         | Outcome
    # Id| State     PlLen  Track   Secs     Rpt   Shfl   | Action             Param1 Param2 | State      PlLen     Rpt     Shfl    Track   Secs
    (300, 'Playing', '@N',    '0', '@T',    '@R',    '@R', 'DeleteAllTracks',     '',     '', 'Stopped',    '0',    '@R',    '@R',    '0',  '0'),
    (301, 'Playing', '@N',   '@m', '@T',    '@R',    '@R', 'DeleteAllTracks',     '',     '', 'Stopped',    '0',    '@R',    '@R',    '0',  '0'),
    (302, 'Playing', '@N', '@N-1', '@T',    '@R',    '@R', 'DeleteAllTracks',     '',     '', 'Stopped',    '0',    '@R',    '@R',    '0',  '0'),
    
    (310, 'Playing', '@N',    '0', '@T',    '@R', 'false', 'Delete'         ,    '0',    '0', 'Playing', '@N-1',    '@R',    '@R',    '0',  '0'),
    (311, 'Playing', '@N',    '0', '@T',    '@R', 'false', 'Delete'         ,    '1', '@N-2', 'Playing', '@N-1',    '@R',    '@R',    '0', '@T'),
    (312, 'Playing', '@N',    '0', '@T',    '@R', 'false', 'Delete'         , '@N-1', '@N-1', 'Playing', '@N-1',    '@R',    '@R',    '0', '@T'),
    (313, 'Playing', '@N',   '@m', '@T',    '@R', 'false', 'Delete'         ,    '0',    '0', 'Playing', '@N-1',    '@R',    '@R', '@m-1', '@T'),
    (314, 'Playing', '@N',   '@m', '@T',    '@R', 'false', 'Delete'         ,    '1', '@m-1', 'Playing', '@N-1',    '@R',    '@R', '@m-1', '@T'),
    (315, 'Playing', '@N',   '@m', '@T',    '@R', 'false', 'Delete'         ,   '@m',   '@m', 'Playing', '@N-1',    '@R',    '@R',   '@m',  '0'),
    (316, 'Playing', '@N',   '@m', '@T',    '@R', 'false', 'Delete'         , '@m+1', '@N-2', 'Playing', '@N-1',    '@R',    '@R',   '@m', '@T'),
    (317, 'Playing', '@N',   '@m', '@T',    '@R', 'false', 'Delete'         , '@N-1', '@N-1', 'Playing', '@N-1',    '@R',    '@R',   '@m', '@T'),
    (318, 'Playing', '@N', '@N-1', '@T',    '@R', 'false', 'Delete'         ,    '0',    '0', 'Playing', '@N-1',    '@R',    '@R', '@N-2', '@T'),
    (319, 'Playing', '@N', '@N-1', '@T',    '@R', 'false', 'Delete'         ,    '1', '@N-2', 'Playing', '@N-1',    '@R',    '@R', '@N-2', '@T'),
    (320, 'Playing', '@N', '@N-1', '@T',  'true', 'false', 'Delete'         , '@N-1', '@N-1', 'Playing', '@N-1',    '@R',    '@R',    '0',  '0'),
    (321, 'Playing', '@N', '@N-1', '@T', 'false', 'false', 'Delete'         , '@N-1', '@N-1', 'Stopped', '@N-1',    '@R',    '@R',    '0',  '0'),
    
    (330, 'Playing', '@N',    '0', '@T',    '@R', 'false', 'Insert'         ,   '-1',   '-1', 'Playing', '@N+1',    '@R',    '@R',    '1', '@T'),
    (331, 'Playing', '@N',    '0', '@T',    '@R', 'false', 'Insert'         ,    '0', '@N-2', 'Playing', '@N+1',    '@R',    '@R',    '0', '@T'),
    (332, 'Playing', '@N',    '0', '@T',    '@R', 'false', 'Insert'         , '@N-1', '@N-1', 'Playing', '@N+1',    '@R',    '@R',    '0', '@T'),
    (333, 'Playing', '@N',   '@m', '@T',    '@R', 'false', 'Insert'         ,   '-1',   '-1', 'Playing', '@N+1',    '@R',    '@R', '@m+1', '@T'),
    (334, 'Playing', '@N',   '@m', '@T',    '@R', 'false', 'Insert'         ,    '0', '@m-1', 'Playing', '@N+1',    '@R',    '@R', '@m+1', '@T'),
    (335, 'Playing', '@N',   '@m', '@T',    '@R', 'false', 'Insert'         ,   '@m', '@N-2', 'Playing', '@N+1',    '@R',    '@R',   '@m', '@T'),
    (336, 'Playing', '@N',   '@m', '@T',    '@R', 'false', 'Insert'         , '@N-1', '@N-1', 'Playing', '@N+1',    '@R',    '@R',   '@m', '@T'),
    (337, 'Playing', '@N', '@N-1', '@T',    '@R', 'false', 'Insert'         ,   '-1',   '-1', 'Playing', '@N+1',    '@R',    '@R',   '@N', '@T'),
    (338, 'Playing', '@N', '@N-1', '@T',    '@R', 'false', 'Insert'         ,    '0', '@N-2', 'Playing', '@N+1',    '@R',    '@R',   '@N', '@T'),
    (339, 'Playing', '@N', '@N-1', '@T',    '@R', 'false', 'Insert'         , '@N-1', '@N-1', 'Playing', '@N+1',    '@R',    '@R', '@N-1', '@T'),
    
    (350, 'Playing', '@N',   '@m', '@T',    '@R',    '@R', 'repeat'         ,   'on',   '-1', 'Playing',   '@N',  'true',    '@R',   '@m', '@T'),
    (351, 'Playing', '@N',   '@m', '@T',    '@R',    '@R', 'repeat'         ,  'off',   '-1', 'Playing',   '@N', 'false',    '@R',   '@m', '@T'),
    (352, 'Playing', '@N',   '@m', '@T',    '@R',    '@R', 'shuffle'        ,   'on',   '-1', 'Playing',   '@N',    '@R',  'true',   '@m', '@T'),
    (353, 'Playing', '@N',   '@m', '@T',    '@R',    '@R', 'shuffle'        ,  'off',   '-1', 'Playing',   '@N',    '@R', 'false',   '@m', '@T'),

    
    # Id| State     PlLen  Track   Secs     Rpt   Shfl   | Action             Param1 Param2 | State      PlLen     Rpt     Shfl    Track   Secs
    (400, 'Paused' , '@N',    '0', '@T',    '@R',    '@R', 'DeleteAllTracks',     '',     '', 'Stopped',    '0',    '@R',    '@R',    '0',  '0'),
    (401, 'Paused' , '@N',   '@m', '@T',    '@R',    '@R', 'DeleteAllTracks',     '',     '', 'Stopped',    '0',    '@R',    '@R',    '0',  '0'),
    (402, 'Paused' , '@N', '@N-1', '@T',    '@R',    '@R', 'DeleteAllTracks',     '',     '', 'Stopped',    '0',    '@R',    '@R',    '0',  '0'),
    
    (410, 'Paused' , '@N',    '0', '@T',    '@R', 'false', 'Delete'         ,    '0',    '0', 'Stopped', '@N-1',    '@R',    '@R',    '0',  '0'),
    (411, 'Paused' , '@N',    '0', '@T',    '@R', 'false', 'Delete'         ,    '1', '@N-2', 'Paused' , '@N-1',    '@R',    '@R',    '0', '@T'),
    (412, 'Paused' , '@N',    '0', '@T',    '@R', 'false', 'Delete'         , '@N-1', '@N-1', 'Paused' , '@N-1',    '@R',    '@R',    '0', '@T'),
    (413, 'Paused' , '@N',   '@m', '@T',    '@R', 'false', 'Delete'         ,    '0',    '0', 'Paused' , '@N-1',    '@R',    '@R', '@m-1', '@T'),
    (414, 'Paused' , '@N',   '@m', '@T',    '@R', 'false', 'Delete'         ,    '1', '@m-1', 'Paused' , '@N-1',    '@R',    '@R', '@m-1', '@T'),
    (415, 'Paused' , '@N',   '@m', '@T',    '@R', 'false', 'Delete'         ,   '@m',   '@m', 'Stopped', '@N-1',    '@R',    '@R',   '@m',  '0'),
    (416, 'Paused' , '@N',   '@m', '@T',    '@R', 'false', 'Delete'         , '@m+1', '@N-2', 'Paused' , '@N-1',    '@R',    '@R',   '@m', '@T'),
    (417, 'Paused' , '@N',   '@m', '@T',    '@R', 'false', 'Delete'         , '@N-1', '@N-1', 'Paused' , '@N-1',    '@R',    '@R',   '@m', '@T'),
    (418, 'Paused' , '@N', '@N-1', '@T',    '@R', 'false', 'Delete'         ,    '0',    '0', 'Paused' , '@N-1',    '@R',    '@R', '@N-2', '@T'),
    (419, 'Paused' , '@N', '@N-1', '@T',    '@R', 'false', 'Delete'         ,    '1', '@N-2', 'Paused' , '@N-1',    '@R',    '@R', '@N-2', '@T'),
    (420, 'Paused' , '@N', '@N-1', '@T',  'true', 'false', 'Delete'         , '@N-1', '@N-1', 'Stopped', '@N-1',    '@R',    '@R',    '0',  '0'),
    (421, 'Paused' , '@N', '@N-1', '@T', 'false', 'false', 'Delete'         , '@N-1', '@N-1', 'Stopped', '@N-1',    '@R',    '@R',    '0',  '0'),
    
    (430, 'Paused' , '@N',    '0', '@T',    '@R', 'false', 'Insert'         ,   '-1',   '-1', 'Paused' , '@N+1',    '@R',    '@R',    '1', '@T'),
    (431, 'Paused' , '@N',    '0', '@T',    '@R', 'false', 'Insert'         ,    '0', '@N-2', 'Paused' , '@N+1',    '@R',    '@R',    '0', '@T'),
    (432, 'Paused' , '@N',    '0', '@T',    '@R', 'false', 'Insert'         , '@N-1', '@N-1', 'Paused' , '@N+1',    '@R',    '@R',    '0', '@T'),
    (433, 'Paused' , '@N',   '@m', '@T',    '@R', 'false', 'Insert'         ,   '-1',   '-1', 'Paused' , '@N+1',    '@R',    '@R', '@m+1', '@T'),
    (434, 'Paused' , '@N',   '@m', '@T',    '@R', 'false', 'Insert'         ,    '0', '@m-1', 'Paused' , '@N+1',    '@R',    '@R', '@m+1', '@T'),
    (435, 'Paused' , '@N',   '@m', '@T',    '@R', 'false', 'Insert'         ,   '@m', '@N-2', 'Paused' , '@N+1',    '@R',    '@R',   '@m', '@T'),
    (436, 'Paused' , '@N',   '@m', '@T',    '@R', 'false', 'Insert'         , '@N-1', '@N-1', 'Paused' , '@N+1',    '@R',    '@R',   '@m', '@T'),
    (437, 'Paused' , '@N', '@N-1', '@T',    '@R', 'false', 'Insert'         ,   '-1',   '-1', 'Paused' , '@N+1',    '@R',    '@R',   '@N', '@T'),
    (438, 'Paused' , '@N', '@N-1', '@T',    '@R', 'false', 'Insert'         ,    '0', '@N-2', 'Paused' , '@N+1',    '@R',    '@R',   '@N', '@T'),
    (439, 'Paused' , '@N', '@N-1', '@T',    '@R', 'false', 'Insert'         , '@N-1', '@N-1', 'Paused' , '@N+1',    '@R',    '@R', '@N-1', '@T'),
    
    (450, 'Paused' , '@N',   '@m', '@T',    '@R',    '@R', 'repeat'         ,   'on',   '-1', 'Paused' ,   '@N',  'true',    '@R',   '@m', '@T'),
    (451, 'Paused' , '@N',   '@m', '@T',    '@R',    '@R', 'repeat'         ,  'off',   '-1', 'Paused' ,   '@N', 'false',    '@R',   '@m', '@T'),
    (452, 'Paused' , '@N',   '@m', '@T',    '@R',    '@R', 'shuffle'        ,   'on',   '-1', 'Paused' ,   '@N',    '@R',  'true',   '@m', '@T'),
    (453, 'Paused' , '@N',   '@m', '@T',    '@R',    '@R', 'shuffle'        ,  'off',   '-1', 'Paused' ,   '@N',    '@R', 'false',   '@m', '@T')
    ]


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
