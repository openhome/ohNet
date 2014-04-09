#!/usr/bin/env python
"""Test PlaylistModes - test different playback mades (repeat/shuffle) combos
                       on playlists, checking playback order etc.
Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer]
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
import Path
import random
import os
import sys
import threading
import time

kAudioRoot = os.path.join( Path.AudioDir(), 'MusicTracks/' )
kTrackList = os.path.join( kAudioRoot, 'TrackList.xml' )


class Config:
    "Test configuration for Playlist service testing"
    
    class Precon:
        "Configuration subclass for precondition info and setup"
        
        def __init__( self, aSetup, aTrack, aRepeat, aShuffle, aTracks, aLog, aDev ):
            "Initialise class data"
            self.setup         = aSetup
            self.plLen         = random.randint( 8, 30 )
            self.track         = self._SubstMacros( aTrack )
            self.repeat        = aRepeat
            self.shuffle       = aShuffle
            self.log           = aLog            
            self.playlist      = []
            self.dev           = aDev
            
            # create random playlist
            self.playlist = []
            numTracks     = len( aTracks )
            for i in range( self.plLen ):
                self.playlist.append( aTracks[random.randint( 0, numTracks-1)] )
                                
        def Setup( self, aDut ):
            "Setup preconditions on the renderer" 
            playingEvent = threading.Event()
            idEvent      = threading.Event()
            
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
            playingEvent.clear()
            if self.track != '-':
                aDut.playlist.SeekIndex( self.track )
            else:
                aDut.playlist.Play()
            playingEvent.wait( 5 )
            aDut.playlist.RemoveSubscriber( _EventCb )
            self.listorder = aDut.playlist.idArray
            
        def _SetupPlaylist( self, aDut ):
            "Setup playlist on DUT"
            idArrayEvt = threading.Event()
            
            def _EventCb( aService, aSvName, aSvVal, aSvSeq ):
                if aSvName == 'IdArray':
                    idArrayEvt.set()
                    
            self.log.Info( self.dev, 'Adding playlist of %d tracks' % self.plLen )
            aDut.playlist.AddSubscriber( _EventCb )
            idArrayEvt.clear()
            aDut.playlist.AddPlaylist( self.playlist )
            self.log.Info( self.dev, 'Added playlist of %d tracks' % self.plLen )
            if self.plLen > 0:
                idArrayEvt.wait( 5 )
            aDut.playlist.RemoveSubscriber( _EventCb )
            
        def _SetupModes( self, aDut ):
            "Setup shuffle and repeat modes"
            aDut.playlist.repeat = self.repeat
            aDut.playlist.shuffle = self.shuffle
            
        def _SubstMacros( self, aArg ):
            """Substitute parameter macros with actual values.
               Valid macros are:
                @m - random track within playlist
                @N - last reack in playlist
            """
            try:
                aArg = aArg.replace( '@N', 'self.plLen-1' )
                aArg = aArg.replace( '@m', 'random.randint( 2, self.plLen-3 )' )
                subst = eval( aArg )
            except:
                subst = aArg
            return subst

    class Stimulus:
        "Configuration subclass for stimulus info and invokation"
        
        def __init__( self, aSeek, aPrecon ):
            "Initialise class data"
            self.timer     = None
            self.seek      = aSeek
            self.precon    = aPrecon
            self.playorder = []
            
        def Invoke( self, aDut ):
            "Skip thru all tracks recording order until Stopped or listlen+2"
            orderEvt    = threading.Event()
            durationEvt = threading.Event()
            playing     = threading.Event()
            stim        = 'aDut.playlist.%s()' % self.seek.title()
            self.playorder.append( aDut.playlist.id )
            
            def _PlaylistEventCb( aService, aSvName, aSvVal, aSvSeq ):
                if aSvName == 'TransportState':
                    if aSvVal == 'Playing':
                        playing.set()
                    else:
                        playing.clear()
                if aSvName == 'Id':
                    th = LogThread.Thread( target=_UpdatePlayorder, args=[aSvVal] )
                    th.start()
                    
            def _InfoEventCb( aService, aSvName, aSvVal, aSvSeq ):
                if aSvName == 'Duration':
                    if aSvVal > 0:
                        durationEvt.set()
                    
            def _UpdatePlayorder( *args ):
                durationEvt.wait( 5 )
                if not durationEvt.isSet():
                    self.precon.log.Warn( self.precon.dev, 'Timeout on Duration event' )
                playing.wait( 3 )
                if playing.isSet():    
                    self.playorder.append( int( args[0] ))
                durationEvt.clear()
                orderEvt.set()
                    
            aDut.playlist.AddSubscriber( _PlaylistEventCb )
            aDut.info.AddSubscriber( _InfoEventCb )
            if aDut.playlist.transportState == 'Playing':
                playing.set()
            for i in range( self.precon.plLen+2 ):
                orderEvt.clear()
                eval( stim )
                orderEvt.wait( 5 )
                if aDut.playlist.polledTransportState == 'Stopped':
                    break
            aDut.info.RemoveSubscriber( _InfoEventCb )
            aDut.playlist.RemoveSubscriber( _PlaylistEventCb )

        
    class Outcome:
        "Configuration subclass for outcome checking"
        
        def __init__( self, aPrecon, aStim, aLog, aDev ):
            "Initialise class data"
            self.precon  = aPrecon
            self.stim    = aStim
            self.log     = aLog
            self.dev     = aDev

        def Check( self, aDut ):
            "Check outcome on specified renderer"
            plLen   = self.precon.plLen
            track   = self.precon.track
            repeat  = self.precon.repeat
            shuffle = self.precon.shuffle
            seek    = self.stim.seek
            meas    = []
            exp     = []
            
            for id in self.stim.playorder:
                meas.append( aDut.playlist.PlaylistIndex( id ))

            if track == '-':
                start = 0       # started by Play() - use 0 as calculation index
            else:
                start = track
                
            self.log.Info( '' )
            self.log.Info( self.dev, 'Tracks: %d,  Start: %s,  Repeat: %s,  Shuffle: %s, Seek: %s' \
                           % (plLen, str( track ), repeat, shuffle, seek) )
            self.log.Info( '', 'Actual:   %s' % meas )
                
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
                self.log.Info( self.dev, 'Expected: %s' % exp )
                self.log.FailUnless( self.dev, meas==exp, 'Playback order')
                
            else:
                # check playlist contains expected tracks (any order)
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
                                'Extra track(s) in list %s' % extra )
                self.log.FailIf( self.dev, len( invalid ),
                                'Invalid track(s) in list %s' % invalid )
                self.log.FailIf( self.dev, len( missing ),
                                'Missing track(s) from list %s' % missing )
                if not (track=='-' and shuffle=='on'):
                    self.log.FailUnless( self.dev, meas[0]==start,
                        'Actual/Expected 1st track %d/%d' % (meas[0], start ) )
            self.log.Info( '' )
                        

    def __init__( self, aLog, aDev, aDut, aConf, aTracks ):
        "Initialise class (and sub-class) data"
        self.log  = aLog
        self.id   = aConf[0]
        self.dut  = aDut
        self.pre  = self.Precon( 
                    aConf[1], aConf[2], aConf[3], aConf[4], aTracks, self.log, aDev )
        self.stim = self.Stimulus( aConf[5], self.pre )
        self.out  = self.Outcome( self.pre, self.stim, self.log, aDev )
        
    def Setup( self ):
        self.pre.Setup( self.dut )
        
    def InvokeStimulus( self ):
        self.stim.Invoke( self.dut )
        
    def CheckOutcome( self ):
        self.out.Check(  self.dut )


class TestPlaylistModes( BASE.BaseTest ):
    "Test playback modes operation (using UPnP as control method)"

    def __init__( self ):
        "Constructor - initalise base class"
        BASE.BaseTest.__init__( self )
        self.dut    = None
        self.server = None
        self.soft   = None
                
    def Test( self, aArgs ):
        "Playlist Service state/transition test"
        # parse command line arguments
        try:
            dutName    = aArgs[1]
            mode       = aArgs[2]
            seed       = int( aArgs[3] )
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( aArgs )) )
                            
        # seed the random number generator
        if not seed:
            seed = int( time.time() ) % 1000000
        self.log.Info( '', 'Seeding random number generator with %d' % (seed) )
        random.seed( seed )
                
        # create DUT
        if dutName.lower() == 'local':
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev' )
            dutName = 'TestDev:SoftPlayer'
        self.dutDev = dutName.split( ':' )[0]
        self.dut = Volkano.VolkanoDevice( dutName, aIsDut=True )
        
        # start audio server
        self.server = HttpServer.HttpServer( kAudioRoot )
        self.server.Start()        
        
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
        "Perform post-test cleanup" 
        if self.server:
            self.server.Shutdown()
        if self.dut: 
            self.dut.Shutdown()
        if self.soft:
            self.soft.Shutdown()
        BASE.BaseTest.Cleanup( self )               

    def _GetConfigs( self, aMode ):
        "Create and return list of test configurations (as filtered by aMode)"               
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
                        min = int( vals[0] )
                        max = int( vals[1].strip( ']' ))
                        if min <= entry[0] and max >= entry[0]:
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