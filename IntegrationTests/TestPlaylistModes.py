#!/usr/bin/env python
#!/usr/bin/env python
"""Test PlaylistModes - test different playback mades (repeat/shuffle) combos
                       on playlists, checking playback order etc.
Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - test mode 
              - all          for all configs sequentially
              - <num>        for config number <num>
              - [min:max]    for range of (numbered) configs
    arg#3 - random number generator seed (0 for 'random')
            by passing this, test scenarious containing random data can be
            replicated - the seed used is logged at the start of execution
            
Tests playback order on randomly generated playlists in all the supported play
modes. Ensures play order is as expected.
""" 
import _FunctionalTest
import BaseTest                   as BASE
import Upnp.ControlPoints.Volkano as Volkano
import Utils.Network.HttpServer   as HttpServer
import Utils.Common               as Common
import _SoftPlayer                as SoftPlayer
import LogThread
import random
import os
import sys
import threading
import time

kAudioRoot = os.path.join( _FunctionalTest.audioDir, 'MusicTracks/' )
kTrackList = os.path.join( kAudioRoot, 'TrackList.xml' )


class Config:
    """Test configuration for Playlist service testing"""
    
    class Precon:
        """Configuration subclass for precondition info and setup"""
        
        def __init__( self, aId, aSetup, aTrack, aRepeat, aShuffle, aTracks, aLog, aDev ):
            """Initialise class data"""
            self.id        = aId
            self.setup     = aSetup
            self.plLen     = random.randint( 8, 30 )
            self.track     = self._SubstMacros( aTrack )
            self.repeat    = aRepeat
            self.shuffle   = aShuffle
            self.log       = aLog
            self.playlist  = []
            self.dev       = aDev
            self.startIdx  = 0
            self.listorder = None

            # create random playlist
            self.playlist = []
            numTracks     = len( aTracks )
            for i in range( self.plLen ):
                self.playlist.append( aTracks[random.randint( 0, numTracks-1)] )
                                
        def Setup( self, aDut ):
            """Setup preconditions on the renderer"""
            playingEvent = threading.Event()
            idEvent      = threading.Event()

            # noinspection PyUnusedLocal
            def _EventCb( aService, aSvName, aSvVal, aSvSeq ):
                if aSvName == 'Id':
                    idEvent.set()
                elif aSvName == 'TransportState':
                    if aSvVal == 'Playing':
                        playingEvent.set()

            idEvent.clear()
            aDut.playlist.DeleteAllTracks()
            idEvent.wait( 5 )
            if self.setup == 'before':
                self._SetupPlaylist( aDut )
                self._SetupModes( aDut )
            else:
                self._SetupModes( aDut )
                self._SetupPlaylist( aDut )
            
            aDut.playlist.AddSubscriber( _EventCb )
            idEvent.clear()
            playingEvent.clear()
            # if self.track != '-':
            #     aDut.playlist.SeekIndex( self.track )
            # else:
            #     aDut.playlist.Play()
            if self.track=='-' or self.shuffle=='on': #####comment this #2587
                aDut.playlist.Play()
            else:
                aDut.playlist.SeekIndex( self.track )
            playingEvent.wait( 3 )
            idEvent.wait( 1 )
            aDut.playlist.RemoveSubscriber( _EventCb )

            if self.track=='-' or self.shuffle=='on':           # see #2587 : 1st track is shuffled
                trackId = aDut.playlist.id                      # forces pass when requested unspecified
            else:
                trackId = aDut.playlist.idArray[self.track]     # check selected = requested track
            self.log.FailUnless( self.dev, aDut.playlist.id==trackId,
                '[%d] Selected track %s (got ID %s)' % ( self.id, self.track,aDut.playlist.id) )
            self.startIdx = aDut.playlist.PlaylistIndex( trackId )
            self.listorder = aDut.playlist.idArray

        def _SetupPlaylist( self, aDut ):
            """Setup playlist on DUT"""
            measPlLen = 0
            self.log.Info( self.dev, '[%d] Adding playlist of %d tracks' % (self.id, self.plLen) )
            aDut.playlist.AddPlaylist( self.playlist )
            if self.plLen > 0:
                measPlLen = len( aDut.playlist.idArray )
            self.log.FailUnless( self.dev, self.plLen==measPlLen,
                '[%d] Added %d tracks (requested %d)' % ( self.id, measPlLen, self.plLen) )

        def _SetupModes( self, aDut ):
            """Setup shuffle and repeat modes"""
            aDut.playlist.repeat = self.repeat
            aDut.playlist.shuffle = self.shuffle

        # noinspection PyMethodMayBeStatic
        def _SubstMacros( self, aArg ):
            """Substitute parameter macros with actual values.
               Valid macros are:
                @m - random track within playlist
                @N - last track in playlist
            """
            try:
                aArg = aArg.replace( '@N', 'self.plLen-1' )
                aArg = aArg.replace( '@m', 'random.randint( 2, self.plLen-3 )' )
                subst = eval( aArg )
            except:
                subst = aArg
            return subst


    class Stimulus:
        """Configuration subclass for stimulus info and invokation"""
        
        def __init__( self, aId, aSeek, aPrecon ):
            """Initialise class data"""
            self.id        = aId
            self.timer     = None
            self.seek      = aSeek
            self.precon    = aPrecon
            self.playorder = []
            
        def Invoke( self, aDut ):
            """Skip thru all tracks recording order until Stopped or listlen+2"""
            orderEvt    = threading.Event()
            playing     = threading.Event()
            stim        = 'aDut.playlist.%s()' % self.seek.title()
            self.playorder.append( aDut.playlist.id )

            # noinspection PyUnusedLocal
            def _PlaylistEventCb( aService, aSvName, aSvVal, aSvSeq ):
                if aSvName == 'TransportState':
                    if aSvVal == 'Playing':
                        playing.set()
                    else:
                        playing.clear()
                if aSvName == 'Id':
                    th = LogThread.Thread( target=_UpdatePlayorder, args=[aSvVal] )
                    th.start()

            def _UpdatePlayorder( *args ):
                time.sleep( 2 )     # wait for transport state to 'settle'
                if playing.isSet():
                    self.playorder.append( int( args[0] ))
                orderEvt.set()
                    
            aDut.playlist.AddSubscriber( _PlaylistEventCb )
            if aDut.playlist.transportState == 'Playing':
                playing.set()

            for i in range( self.precon.plLen+2 ):
                orderEvt.clear()
                eval( stim )
                orderEvt.wait( 5 )  # must be longer than total delays in  _UpdatePlayorder
                if aDut.playlist.polledTransportState == 'Stopped':
                    self.precon.log.Pass( self.precon.dev, 'Playlist exhausted after <%s> action' % self.seek )
                    break
                # The only scenario where we can play the same track twice in a row (and hence not
                # get an Id event) is when both shuffle and repeat modes are enabled, and we have
                # moved to the first track in a subsequent loop thru the playlist. There is no
                # reason why the last track in one shuffling cannot be the first track in the
                # subsequent shuffling
                if i==self.precon.plLen-1 and self.precon.shuffle=='on' and self.precon.repeat=='on':
                    self.precon.log.WarnUnless( self.precon.dev, orderEvt.is_set(), '[%d] Executed <%s> action at start of 2nd loop of playlist' % (self.id, self.seek) )
                else:
                    self.precon.log.FailUnless( self.precon.dev, orderEvt.is_set(), '[%d] Executed <%s> action' % (self.id, self.seek) )

            aDut.playlist.RemoveSubscriber( _PlaylistEventCb )


    class Outcome:
        """Configuration subclass for outcome checking"""
        
        def __init__( self, aId, aPrecon, aStim, aLog, aDev ):
            """Initialise class data"""
            self.id      = aId
            self.precon  = aPrecon
            self.stim    = aStim
            self.log     = aLog
            self.dev     = aDev

        def Check( self, aDut ):
            """Check outcome on specified renderer"""
            plLen   = self.precon.plLen
            track   = self.precon.track
            repeat  = self.precon.repeat
            shuffle = self.precon.shuffle
            seek    = self.stim.seek
            meas    = []

            for tId in self.stim.playorder:
                meas.append( aDut.playlist.PlaylistIndex( tId ))

            if track=='-' or shuffle=='on':     # see #2587 : 1st track is shuffled
                start = self.precon.startIdx
            else:
                start = track
                
            self.log.Info( '' )
            self.log.Info( self.dev, '[%d] Tracks: %d,  Start: %s,  Repeat: %s,  Shuffle: %s, Seek: %s' \
                           % (self.id, plLen, str( track ), repeat, shuffle, seek) )
            self.log.Info( '', '[%d] Actual:   %s' % (self.id, meas) )
                
            if shuffle == 'off':
                # check against exact expected playlist
                if seek == 'next':
                    exp = range( start, plLen )
                else:
                    exp = range( start, -1, -1 )
                if repeat == 'on':
                    if seek == 'next':
                        calc = range( 0, start+3 )
                    else:
                        calc = range( plLen-1, start-3, -1 )
                    for entry in calc:
                        if entry < 0:
                            entry = plLen+entry
                        elif entry >= plLen:
                            entry = entry-plLen
                        exp.append( entry )
                self.log.FailUnless( self.dev, meas==exp, '[%d] Playback order meas/expected %s/%s' % (self.id, meas, exp) )
                
            else:
                # check playlist contains expected tracks (any order)
                if repeat=='off' and seek=='previous':
                    missing = [start]  ## whatever was started at
                else:
                    missing = range( 0, plLen )
                invalid = []
                extra   = []
                for entry in meas[:plLen]:
                    try:
                        missing.remove( entry )
                    except:
                        extra.append( entry )
                        
                if repeat == 'on':
                    tracks = range( 0, plLen )
                    for entry in meas[plLen+1:]:
                        try:
                            tracks.remove( entry )
                        except:
                            invalid.append( entry )
                
                self.log.FailIf( self.dev, len( extra ),
                                '[%d] Extra track(s) in list %s' % (self.id, extra) )
                self.log.FailIf( self.dev, len( invalid ),
                                '[%d] Invalid track(s) in list %s' % (self.id, invalid) )
                self.log.FailIf( self.dev, len( missing ),
                                '[%d] Missing track(s) from list %s' % (self.id, missing) )
#                if not (track=='-' and shuffle=='on'):
                if not track!='-' or shuffle!='on':
                    self.log.FailUnless( self.dev, meas[0]==start,
                        '[%d] Actual/Expected 1st track %d/%d' % (self.id, meas[0], start ) )
            self.log.Info( '' )
                        

    def __init__( self, aLog, aDev, aDut, aConf, aTracks ):
        """Initialise class (and sub-class) data"""
        self.log  = aLog
        self.id   = aConf[0]
        self.dut  = aDut
        self.pre  = self.Precon( 
                    self.id, aConf[1], aConf[2], aConf[3], aConf[4], aTracks, self.log, aDev )
        self.stim = self.Stimulus( self.id, aConf[5], self.pre )
        self.out  = self.Outcome( self.id, self.pre, self.stim, self.log, aDev )
        
    def Setup( self ):
        self.pre.Setup( self.dut )
        
    def InvokeStimulus( self ):
        self.stim.Invoke( self.dut )
        
    def CheckOutcome( self ):
        self.out.Check(  self.dut )


class TestPlaylistModes( BASE.BaseTest ):
    """Test playback modes operation (using UPnP as control method)"""

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
            dutName = self.soft.name
        self.dutDev = dutName.split( ':' )[0]
        self.dut = Volkano.VolkanoDevice( dutName, aIsDut=True, aLoopback=loopback )
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
            self.log.Header2( '', 'Testing config ID# %d (%d of %d)' % \
                           (config.id, numConfig, numConfigs) )
            config.Setup()
            config.InvokeStimulus()
            config.CheckOutcome()
            
        # stop playback            
        self.dut.playlist.Stop()

    def Cleanup( self ):
        """Perform post-test cleanup"""
        if self.server:
            self.server.Shutdown()
        if self.dut: 
            self.dut.Shutdown()
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
                configs.append( Config( self.log, self.dutDev, self.dut, entry, tracks ))
            
        return configs


configTable = \
    [
    # 'Setup' is the setup order -> Playlist BEFORE/AFTER modes 
    # 'Track' is the start track for the test
    # 'Seek'  is the seek direction for navgating playback
    #
    # Macros:    @N: last track in list
    #            @m: 1 <= track < last track
    #            -:  don't seek specific track, just Play()
    #  
    # Id    Setup  Track    Rpt   Shfl   Seek 
    ( 10, 'before',  '0', 'off', 'off', 'next' ),
    ( 11, 'before',  '0', 'off', 'off', 'previous' ),
    ( 12, 'before',  '0', 'off',  'on', 'next' ), 
    ( 13, 'before',  '0', 'off',  'on', 'previous' ), 
    ( 14, 'before',  '0',  'on', 'off', 'next' ),
    ( 15, 'before',  '0',  'on', 'off', 'previous' ),
    ( 16, 'before',  '0',  'on',  'on', 'next' ), 
    ( 17, 'before',  '0',  'on',  'on', 'previous' ), 
    
    ( 20, 'before', '@m', 'off', 'off', 'next' ),
    ( 21, 'before', '@m', 'off', 'off', 'previous' ),
    ( 22, 'before', '@m', 'off',  'on', 'next' ), 
    ( 23, 'before', '@m', 'off',  'on', 'previous' ), 
    ( 24, 'before', '@m',  'on', 'off', 'next' ),
    ( 25, 'before', '@m',  'on', 'off', 'previous' ),
    ( 26, 'before', '@m',  'on',  'on', 'next' ), 
    ( 27, 'before', '@m',  'on',  'on', 'previous' ), 
    
    ( 30, 'before', '@N', 'off', 'off', 'next' ),
    ( 31, 'before', '@N', 'off', 'off', 'previous' ),
    ( 32, 'before', '@N', 'off',  'on', 'next' ), 
    ( 33, 'before', '@N', 'off',  'on', 'previous' ), 
    ( 34, 'before', '@N',  'on', 'off', 'next' ),
    ( 35, 'before', '@N',  'on', 'off', 'previous' ),
    ( 36, 'before', '@N',  'on',  'on', 'next' ), 
    ( 37, 'before', '@N',  'on',  'on', 'previous' ),
    
    ( 40, 'before', '-',  'off', 'off', 'next' ),
    ( 41, 'before', '-',  'off', 'off', 'previous' ),
    ( 42, 'before', '-',  'off',  'on', 'next' ), 
    ( 43, 'before', '-',  'off',  'on', 'previous' ), 
    ( 44, 'before', '-',   'on', 'off', 'next' ),
    ( 45, 'before', '-',   'on', 'off', 'previous' ),
    ( 46, 'before', '-',   'on',  'on', 'next' ), 
    ( 47, 'before', '-',   'on',  'on', 'previous' ), 
    
    ( 50,  'after',  '0', 'off', 'off', 'next' ),
    ( 51,  'after',  '0', 'off', 'off', 'previous' ),
    ( 52,  'after',  '0', 'off',  'on', 'next' ),
    ( 53,  'after',  '0', 'off',  'on', 'previous' ),
    ( 54,  'after',  '0',  'on', 'off', 'next' ),
    ( 55,  'after',  '0',  'on', 'off', 'previous' ),
    ( 56,  'after',  '0',  'on',  'on', 'next' ),
    ( 57,  'after',  '0',  'on',  'on', 'previous' ),

    ( 60,  'after', '@m', 'off', 'off', 'next' ),
    ( 61,  'after', '@m', 'off', 'off', 'previous' ),
    ( 62,  'after', '@m', 'off',  'on', 'next' ),
    ( 63,  'after', '@m', 'off',  'on', 'previous' ),
    ( 64,  'after', '@m',  'on', 'off', 'next' ),
    ( 65,  'after', '@m',  'on', 'off', 'previous' ),
    ( 66,  'after', '@m',  'on',  'on', 'next' ),
    ( 67,  'after', '@m',  'on',  'on', 'previous' ),

    ( 70,  'after', '@N', 'off', 'off', 'next' ),
    ( 71,  'after', '@N', 'off', 'off', 'previous' ),
    ( 72,  'after', '@N', 'off',  'on', 'next' ),
    ( 73,  'after', '@N', 'off',  'on', 'previous' ),
    ( 74,  'after', '@N',  'on', 'off', 'next' ),
    ( 75,  'after', '@N',  'on', 'off', 'previous' ),
    ( 76,  'after', '@N',  'on',  'on', 'next' ),
    ( 77,  'after', '@N',  'on',  'on', 'previous' ),

    ( 80, 'after',  '-',  'off', 'off', 'next' ),
    ( 81, 'after',  '-',  'off', 'off', 'previous' ),
    ( 82, 'after',  '-',  'off',  'on', 'next' ),
    ( 83, 'after',  '-',  'off',  'on', 'previous' ),
    ( 84, 'after',  '-',   'on', 'off', 'next' ),
    ( 85, 'after',  '-',   'on', 'off', 'previous' ),
    ( 86, 'after',  '-',   'on',  'on', 'next' ),
    ( 87, 'after',  '-',   'on',  'on', 'previous' )
    ]


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
