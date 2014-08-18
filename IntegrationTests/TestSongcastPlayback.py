#!/usr/bin/env python
"""SongcastPlayback - test Songcast functionality (Sender/Receiver/Zpus)

Parameters:
    arg#1 - DUT #1 ['local' for internal SoftPlayer on loopback]
    arg#1 - DUT #2 ['local' for internal SoftPlayer on loopback]
    arg#1 - DUT #3 ['local' for internal SoftPlayer on loopback]
    arg#4 - test mode 
              - all          for all configs sequentially
              - random       for all configs randomly
              - <num>        for config number <num>
              - [min:max]    for range of (numbered) configs
    arg#5 - random number generator seed (0 for 'random')
            by passing this, test scenarious containing random data can be
            replicated - the seed used is logged at the start of execution
           
Tests the sender and receiver services, and operation of zpus routing. Ensures
status and actions operate as specified
""" 

# Differences from DS test:
#    - removed songcast sender mode param - set in softplayer at startup
#    - removed DS#4 as it was used for external connections to DS#3
#    - removed all tests using external inputs
#    - removed (unused) test loops param
#    - test scenario numbers are unchanged from DS test
#    - removed .NET XML handling
#
# Audio track for playback in a test is selected randomly from the playlist
#
# Order of DUT setup is random 

import _FunctionalTest
import BaseTest                   as BASE
import Upnp.ControlPoints.Volkano as Volkano
import Utils.Network.HttpServer   as HttpServer
import Utils.Common               as Common
import _SoftPlayer                as SoftPlayer
import os
import random
import sys
import threading
import time
import xml.etree.ElementTree as ET

kAudioRoot = os.path.join( _FunctionalTest.audioDir, 'LRTones/' )
kTrackList = os.path.join( kAudioRoot, 'TrackListSpdif.xml' )


class Config:
    """Test configuration for Songcast testing"""

    def __init__( self, aLog, aDut1Dev, aConf ):
        """Initialise class data"""
        self.log     = aLog
        self.dut1Dev = aDut1Dev
        self.conf    = aConf
        self.id      = aConf[0]
        self.duts    = None
        
    def Setup( self, aDuts ):
        """Configure the DUTs. Order of configuration is randomly generated"""
        self.duts = aDuts
        order = [1, 2, 3]
        order.sort( lambda x,y: random.choice( [-1,1] ))
        self.__SetupDut( order[0] )
        self.__SetupDut( order[1] )
        self.__SetupDut( order[2] )
            
    def __SetupDut( self, aNum ):
        """Setup specifed DUT as determined by configuration parameters"""
        source = self.conf[9-2*aNum]
        state  = self.conf[10-2*aNum]
        dut    = self.duts[aNum-1]
        dutDev = dut.product.productRoom
        self.log.Info( '' )
        self.log.Info( dutDev, '[%d] Setting Up DUT #%d: Source %s, State %s' % \
                       (self.id, aNum, source, state) )
        self.log.Info( '' )
        
        if source=='' and state=='':
            self.log.Info( dutDev, 'Nothing to setup - ensure stopped' )
            dut.playlist.Stop()     # switche to playlist source and stops
            return
        
        self.__SetupStandby( dut, state )
        if source == 'Playlist':
            self.__SetupPlaylist( dut, state )                               
        if 'DS' in source:
            self.__SetupReceiver( dut, source, state, self.duts )

    @staticmethod
    def __SetupStandby( aDut, aState ):
        """Set dut to Standby if specified, else ensure DUT out-of-standby"""
        standbyTrue  = threading.Event()
        standbyFalse = threading.Event()

        # noinspection PyUnusedLocal
        def _ProductCb( aService, aSvName, aSvVal, aSvSeq ):
            if aSvName == 'Standby':
                if aSvVal == 'true':
                    standbyTrue.set()
                else:
                    standbyFalse.set()
        
        if aState == 'Standby':
            if not aDut.product.standby:
                aDut.product.AddSubscriber( _ProductCb )
                standbyTrue.clear() 
                aDut.product.standby = True
                standbyTrue.wait( 5 )
                aDut.product.RemoveSubscriber( _ProductCb )
        else:
            if aDut.product.standby:
                aDut.product.AddSubscriber( _ProductCb )
                standbyFalse.clear() 
                aDut.product.standby = False
                standbyFalse.wait( 5 )
                aDut.product.RemoveSubscriber( _ProductCb )

    @staticmethod
    def __SetupPlaylist( aDut, aState ):
        """Select random track in playlist and set specified transport state"""
        transportPlaying = threading.Event()
        transportPaused = threading.Event()
        transportStopped = threading.Event()

        # noinspection PyUnusedLocal
        def _PlaylistCb( aService, aSvName, aSvVal, aSvSeq ):
            if aSvName == 'TransportState':
                if aSvVal == 'Playing':
                    transportPlaying.set()
                elif aSvVal == 'Paused':
                    transportPaused.set()
                elif aSvVal == 'Stopped':
                    transportStopped.set()
        
        aDut.playlist.AddSubscriber( _PlaylistCb )
        transportPlaying.clear()
        aDut.playlist.SeekId( random.choice( aDut.playlist.idArray ))
        transportPlaying.wait( 3 )
        if aState == 'Paused':
            transportPaused.clear()
            aDut.playlist.Pause()
            transportPaused.wait( 3 )
        if aState == 'Stopped':
            transportStopped.clear()
            aDut.playlist.Stop()
            transportStopped.wait( 3 )
        aDut.playlist.RemoveSubscriber( _PlaylistCb )
        
    @staticmethod
    def __SetupReceiver( aDut, aSource, aState, aDuts ):
        """Select receiver source, connect to sender and set transport state"""
        sourceChanged    = threading.Event()
        uriChanged       = threading.Event()
        transportPlaying = threading.Event() 
        transportStopped = threading.Event()

        # noinspection PyUnusedLocal
        def _ProductCb( aService, aSvName, aSvVal, aSvSeq ):
            if aSvName == 'SourceIndex':
                sourceChanged.set()

        # noinspection PyUnusedLocal
        def _ReceiverCb( aService, aSvName, aSvVal, aSvSeq ):
            if aSvName == 'TransportState':
                if aSvVal == 'Playing':
                    transportPlaying.set()
                elif aSvVal == 'Stopped':
                    transportStopped.set()
            elif aSvName == 'Uri':
                uriChanged.set() 
                    
        sender = aDuts[int( aSource[2] ) - 1]
        uri = sender.sender.uri
        meta = sender.sender.metadata
        
        index = aDut.product.SourceIndexFromSystemName( 'Songcast' )
        if aDut.product.sourceIndex != index:        
            aDut.product.AddSubscriber( _ProductCb )
            sourceChanged.clear()
            aDut.product.sourceIndex = index
            sourceChanged.wait( 5 )        
            aDut.product.RemoveSubscriber( _ProductCb )

        aDut.receiver.AddSubscriber( _ReceiverCb )
        uriChanged.clear()
        aDut.receiver.SetSender( uri, meta )    # always set sender to ensure
        if aDut.receiver.uri != uri:            # that sender metadata refreshed
            uriChanged.wait( 3 )
        
        if aState == 'Playing':
            transportPlaying.clear()
            aDut.receiver.Play()
            transportPlaying.wait( 3 )
        if aState == 'Stopped':
            transportStopped.clear()
            aDut.receiver.Stop()
            transportStopped.wait( 3 )
        aDut.receiver.RemoveSubscriber( _ReceiverCb )
        
    def CheckSenders( self, aDuts ):
        """Verify status of senders"""
        self.log.Info( '' )
        self.log.Info( '', '[%d] Checking senders status' % self.id )
        self.log.Info( '' )
        if self.conf[11]:
            dut = aDuts[1]
            expStatus = self.conf[11]
            if self.conf[12] == 'True':
                expAudio = True
            else:
                expAudio = False
            self.__CheckSenderVars( dut, expStatus, expAudio, 'DUT2' )
        if self.conf[9]:
            dut = aDuts[2]
            expStatus = self.conf[9]
            if self.conf[10] == 'True':
                expAudio = True
            else:
                expAudio = False
            self.__CheckSenderVars( dut, expStatus, expAudio, 'DUT3' )
            
    def __CheckSenderVars( self, aDut, aExpStatus, aExpAudio, aName ):
        """Check sender service state vars as expected"""
        dutDev = aDut.product.productRoom
        self.log.FailUnless( dutDev, aDut.sender.status == aExpStatus, 
            '[%d] %s/%s actual/expected sender status for %s' % 
            (self.id, aDut.sender.status, aExpStatus, aName) )
        self.log.FailUnless( dutDev, aDut.sender.audio == aExpAudio, 
            '[%d] %s/%s actual/expected sender audio for %s' % 
            (self.id, aDut.sender.audio, aExpAudio, aName) )
    
    def CheckReceivers( self, aDuts ):
        """Verify status of receivers"""
        self.log.Info( '' )
        self.log.Info( '', '[%d] Checking receivers status' % self.id )
        self.log.Info( '' )
        expUri  = ''
        expMeta = ''

        if self.conf[13]:
            dut = aDuts[1]
            expState = self.conf[13]
            if self.conf[14]=='DS3':
                expUri = aDuts[2].sender.uri
                expMeta = aDuts[2].sender.metadata
            self.__CheckRxVars( dut, expState, expUri, expMeta, 'DUT2' )
        if self.conf[16]:
            dut = aDuts[0]
            expState = self.conf[16]
            if self.conf[17]=='DS3':
                expUri = aDuts[2].sender.uri
                expMeta = aDuts[2].sender.metadata
            elif self.conf[17]=='DS2':
                expUri = aDuts[1].sender.uri
                expMeta = aDuts[1].sender.metadata
            self.__CheckRxVars( dut, expState, expUri, expMeta, 'DUT1' )
                
    def __CheckRxVars( self, aDut, aExpState, aExpUri, aExpMeta, aName ):
        """Check receiver service state vars as expected"""
        dutDev = aDut.product.productRoom
        self.log.FailUnless( dutDev, aDut.receiver.transportState == aExpState, 
            '[%d] %s/%s actual/expected receiver transport state for %s' % 
            (self.id, aDut.receiver.transportState, aExpState, aName) )
        self.log.FailUnless( dutDev, aDut.receiver.uri == aExpUri, 
            '[%d] %s/%s actual/expected receiver URI %s' % 
            (self.id, aDut.receiver.uri, aExpUri, aName) )
        meas = ET.tostring( ET.XML( aDut.receiver.metadata ))   # normalise XML
        exp =  ET.tostring( ET.XML( aExpMeta ))
        self.log.FailUnless( dutDev, meas == exp, 
            '[%d] %s/%s actual/expected receiver Metadata %s' % (self.id, meas, exp, aName) )


class TestSongcastPlayback( BASE.BaseTest ):
    """Test Songcast operations"""

    def __init__( self ):
        """Constructor - initalise base class"""
        BASE.BaseTest.__init__( self )
        self.dut1    = None
        self.dut2    = None
        self.dut3    = None
        self.soft1   = None
        self.soft2   = None
        self.soft3   = None
        self.dut1Dev = None
        self.server  = None
                
    def Test( self, aArgs ):
        """Songcast Playback test"""
        dut1Name = None
        dut2Name = None
        dut3Name = None
        testMode = None
        seed     = None
        loopback = False

        try:
            dut1Name   = aArgs[1]
            dut2Name   = aArgs[2]
            dut3Name   = aArgs[3]
            testMode   = aArgs[4]
            seed       = int( aArgs[5] )
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( aArgs )) )

        if dut1Name.lower()=='local' or dut2Name.lower()=='local' or dut3Name.lower()=='local':
            if dut1Name.lower()!='local' or dut2Name.lower()!='local' or dut3Name.lower()!='local':
                self.log.Abort( '', 'Local loopback can only apply to ALL or NONE devices' )

        # seed the random number generator
        if not seed:
            seed = int( time.time() ) % 1000000
        self.log.Info( '', 'Seeding random number generator with %d' % seed )
        random.seed( seed )
                
        # create DUTs
        self.log.Header2( '', '    ------ Creating DUT #1 (%s) ------' % dut1Name )
        if dut1Name.lower() == 'local':
            loopback = True
            self.soft1 = SoftPlayer.SoftPlayer( aRoom='TestDev1', aLoopback=loopback )
            dut1Name = self.soft1.name
        self.dut1Dev = dut1Name.split( ':' )[0]
        self.dut1 = Volkano.VolkanoDevice( dut1Name, aIsDut=True, aLoopback=loopback )
        self.log.Header2( '', '    ------ Creating DUT #2 (%s) ------' % dut2Name )
        if dut2Name.lower() == 'local':
            self.soft2 = SoftPlayer.SoftPlayer( aRoom='TestDev2', aLoopback=loopback )
            dut2Name = self.soft2.name
        self.dut2 = Volkano.VolkanoDevice( dut2Name, aIsDut=True, aLoopback=loopback )
        self.log.Header2( '', '    ------ Creating DUT #3 (%s) ------' % dut3Name )
        if dut3Name.lower() == 'local':
            self.soft3 = SoftPlayer.SoftPlayer( aRoom='TestDev3', aLoopback=loopback )
            dut3Name = self.soft3.name
        self.dut3 = Volkano.VolkanoDevice( dut3Name, aIsDut=True, aLoopback=loopback )
        duts = [self.dut1, self.dut2, self.dut3]
        
        self.log.Info( '' )
        self.log.Info( '', '    ------ Configuring Test ------' )
        self.log.Info( '' )
    
        # start audio server
        self.server = HttpServer.HttpServer( kAudioRoot )
        self.server.Start()
        
        # get list of tracks to use for playlist
        tracks = Common.GetTracks( kTrackList, self.server )
                
        # setup playlists in DUTs 
        self.dut1.playlist.DeleteAllTracks()
        self.dut2.playlist.DeleteAllTracks()
        self.dut3.playlist.DeleteAllTracks()
        self.dut2.playlist.AddPlaylist( tracks )
        self.dut3.playlist.AddPlaylist( tracks )
                
        # create test confgurations as specified by mode
        testConfigs = self._GetConfigs( testMode )
        
        # test the configurations
        numConfig  = 0
        numConfigs = len( testConfigs )
        for config in testConfigs:
            numConfig += 1
            self.log.Info( '' )
            self.log.Info( '', '----------------------------------------------' )
            self.log.Info( '', 'Testing ID %d (Config %d of %d)' % \
                           (config.id, numConfig, numConfigs) )
            self.log.Info( '', '----------------------------------------------' )
            self.log.Info( '' )
            config.Setup( duts )
            time.sleep( 3 )
            config.CheckSenders( duts )
            config.CheckReceivers( duts )

        # stop playback            
        self.dut3.playlist.Stop()
        self.dut2.playlist.Stop()
        self.dut1.playlist.Stop()

    def Cleanup( self ):
        """Perform cleanup on test exit"""
        self.log.Info( '' )
        self.log.Info( '' )
        self.log.Info( '', 'Shutting Down' )
        self.log.Info( '' )
        if self.dut3:
            self.dut3.Shutdown()
        if self.dut2: 
            self.dut2.Shutdown()
        if self.dut1: 
            self.dut1.Shutdown()
        if self.soft3:
            self.soft3.Shutdown()
        if self.soft2:
            self.soft2.Shutdown()
        if self.soft1:
            self.soft1.Shutdown()
        if self.server:
            self.server.Shutdown()
        BASE.BaseTest.Cleanup( self )                

    def _GetConfigs( self, aMode ):
        """Create and return list of test configurations (as filtered by aMode)"""
        configs = []
        for entry in configTable:
            selected = False
            if aMode.lower() in ('all', 'random'):
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
                configs.append( Config( self.log, self.dut1Dev, entry ))
                
        if aMode.lower() == 'random':
            configs.sort( lambda x,y: random.choice( [-1,1] ))
        return configs


configTable = \
    [
    # Id || Setup                                                                                     || Checks 
    #    || DS4                  | DS3                  | DS2                  | DS1                  || DS3 Sender         | DS2 Sender          | DS2 Receiver           | DS1 Receiver          
    #    || Source    | State    | Source    | State    | Source    | State    | Source    | State    || Status    | Audio  | Status    | Audio  | State    | Uri  | Meta | State    | Uri  | Meta
    ( 100,  ''        , ''       , ''        , ''       , ''        , 'Standby', 'DS2'     , 'Stopped',  ''        , ''     , 'Enabled' , 'False', ''       , ''   , ''   , 'Stopped', 'DS2', 'DS2' ),
    ( 101,  ''        , ''       , ''        , ''       , ''        , 'Standby', 'DS2'     , 'Playing',  ''        , ''     , 'Enabled' , 'False', ''       , ''   , ''   , 'Waiting', 'DS2', 'DS2' ),
    
    ( 102,  ''        , ''       , ''        , ''       , 'Playlist', 'Stopped', 'DS2'     , 'Stopped',  ''        , ''     , 'Enabled' , 'False', ''       , ''   , ''   , 'Stopped', 'DS2', 'DS2' ),
    ( 103,  ''        , ''       , ''        , ''       , 'Playlist', 'Playing', 'DS2'     , 'Stopped',  ''        , ''     , 'Enabled' , 'True' , ''       , ''   , ''   , 'Stopped', 'DS2', 'DS2' ),
    ( 104,  ''        , ''       , ''        , ''       , 'Playlist', 'Paused' , 'DS2'     , 'Stopped',  ''        , ''     , 'Enabled' , 'False', ''       , ''   , ''   , 'Stopped', 'DS2', 'DS2' ),
    ( 105,  ''        , ''       , ''        , ''       , 'Playlist', 'Stopped', 'DS2'     , 'Playing',  ''        , ''     , 'Enabled' , 'False', ''       , ''   , ''   , 'Waiting', 'DS2', 'DS2' ),
    ( 106,  ''        , ''       , ''        , ''       , 'Playlist', 'Playing', 'DS2'     , 'Playing',  ''        , ''     , 'Enabled' , 'True' , ''       , ''   , ''   , 'Playing', 'DS2', 'DS2' ),
    ( 107,  ''        , ''       , ''        , ''       , 'Playlist', 'Paused' , 'DS2'     , 'Playing',  ''        , ''     , 'Enabled' , 'False', ''       , ''   , ''   , 'Waiting', 'DS2', 'DS2' ),
    
    # Id || Setup                                                                                     || Checks 
    #    || DS4                  | DS3                  | DS2                  | DS1                  || DS3 Sender         | DS2 Sender         | DS2 Receiver           | DS1 Receiver          
    #    || Source    | State    | Source    | State    | Source    | State    | Source    | State    || Status    | Audio  | Status    | Audio  | State    | Uri  | Meta | State    | Uri  | Meta
    ( 200,  ''        , ''       , ''        , 'Standby', ''        , ''       , 'DS3'     , 'Stopped',  'Enabled' , 'False', ''        , ''     , ''       , ''   , ''   , 'Stopped', 'DS3', 'DS3' ),
    ( 201,  ''        , ''       , ''        , 'Standby', ''        , ''       , 'DS3'     , 'Playing',  'Enabled' , 'False', ''        , ''     , ''       , ''   , ''   , 'Waiting', 'DS3', 'DS3' ),
    
#    ( 202,  'Playlist', 'Stopped', 'Pure'    , ''       , ''        , ''       , 'DS3'     , 'Stopped',  'Enabled' , 'True' , ''        , ''     , ''       , ''   , ''   , 'Stopped', 'DS3', 'DS3' ),
#    ( 203,  'Playlist', 'Playing', 'Pure'    , ''       , ''        , ''       , 'DS3'     , 'Stopped',  'Enabled' , 'True' , ''        , ''     , ''       , ''   , ''   , 'Stopped', 'DS3', 'DS3' ),
#    ( 204,  'Playlist', 'Stopped', 'Pure'    , ''       , ''        , ''       , 'DS3'     , 'Playing',  'Enabled' , 'True' , ''        , ''     , ''       , ''   , ''   , 'Playing', 'DS3', 'DS3' ),
#    ( 205,  'Playlist', 'Playing', 'Pure'    , ''       , ''        , ''       , 'DS3'     , 'Playing',  'Enabled' , 'True' , ''        , ''     , ''       , ''   , ''   , 'Playing', 'DS3', 'DS3' ),
#    ( 206,  'Playlist', 'Stopped', 'Analog'  , ''       , ''        , ''       , 'DS3'     , 'Stopped',  'Enabled' , 'True' , ''        , ''     , ''       , ''   , ''   , 'Stopped', 'DS3', 'DS3' ),
#    ( 207,  'Playlist', 'Playing', 'Analog'  , ''       , ''        , ''       , 'DS3'     , 'Stopped',  'Enabled' , 'True' , ''        , ''     , ''       , ''   , ''   , 'Stopped', 'DS3', 'DS3' ),
#    ( 208,  'Playlist', 'Stopped', 'Analog'  , ''       , ''        , ''       , 'DS3'     , 'Playing',  'Enabled' , 'True' , ''        , ''     , ''       , ''   , ''   , 'Playing', 'DS3', 'DS3' ),
#    ( 209,  'Playlist', 'Playing', 'Analog'  , ''       , ''        , ''       , 'DS3'     , 'Playing',  'Enabled' , 'True' , ''        , ''     , ''       , ''   , ''   , 'Playing', 'DS3', 'DS3' ),
#    ( 210,  'Playlist', 'Stopped', 'SPDIF'   , ''       , ''        , ''       , 'DS3'     , 'Stopped',  'Enabled' , 'True' , ''        , ''     , ''       , ''   , ''   , 'Stopped', 'DS3', 'DS3' ),
#    ( 211,  'Playlist', 'Playing', 'SPDIF'   , ''       , ''        , ''       , 'DS3'     , 'Stopped',  'Enabled' , 'True' , ''        , ''     , ''       , ''   , ''   , 'Stopped', 'DS3', 'DS3' ),
#    ( 212,  'Playlist', 'Stopped', 'SPDIF'   , ''       , ''        , ''       , 'DS3'     , 'Playing',  'Enabled' , 'True' , ''        , ''     , ''       , ''   , ''   , 'Playing', 'DS3', 'DS3' ),
#    ( 213,  'Playlist', 'Playing', 'SPDIF'   , ''       , ''        , ''       , 'DS3'     , 'Playing',  'Enabled' , 'True' , ''        , ''     , ''       , ''   , ''   , 'Playing', 'DS3', 'DS3' ),
    
    # Id || Setup                                                                                     || Checks 
    #    || DS4                  | DS3                  | DS2                  | DS1                  || DS3 Sender         | DS2 Sender         | DS2 Receiver           | DS1 Receiver          
    #    || Source    | State    | Source    | State    | Source    | State    | Source    | State    || Status    | Audio  | Status    | Audio  | State    | Uri  | Meta | State    | Uri  | Meta
    ( 300,  ''        , ''       , ''        , 'Standby', 'DS3'     , 'Stopped', 'DS2'     , 'Stopped',  'Enabled' , 'False', 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
    ( 301,  ''        , ''       , ''        , 'Standby', 'DS3'     , 'Playing', 'DS2'     , 'Stopped',  'Enabled' , 'False', 'Enabled' , 'False', 'Waiting', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
    ( 302,  ''        , ''       , ''        , 'Standby', 'DS3'     , 'Stopped', 'DS2'     , 'Playing',  'Enabled' , 'False', 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Waiting', 'DS2', 'DS2' ),
    ( 303,  ''        , ''       , ''        , 'Standby', 'DS3'     , 'Playing', 'DS2'     , 'Playing',  'Enabled' , 'False', 'Enabled' , 'False', 'Waiting', 'DS3', 'DS3', 'Waiting', 'DS2', 'DS2' ),
    
    ( 304,  ''        , ''       , 'Playlist', 'Stopped', 'DS3'     , 'Stopped', 'DS2'     , 'Stopped',  'Enabled' , 'False', 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
    ( 305,  ''        , ''       , 'Playlist', 'Playing', 'DS3'     , 'Stopped', 'DS2'     , 'Stopped',  'Enabled' , 'True' , 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
    ( 306,  ''        , ''       , 'Playlist', 'Paused' , 'DS3'     , 'Stopped', 'DS2'     , 'Stopped',  'Enabled' , 'False', 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
    ( 307,  ''        , ''       , 'Playlist', 'Stopped', 'DS3'     , 'Playing', 'DS2'     , 'Stopped',  'Enabled' , 'False', 'Enabled' , 'False', 'Waiting', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
    ( 308,  ''        , ''       , 'Playlist', 'Playing', 'DS3'     , 'Playing', 'DS2'     , 'Stopped',  'Enabled' , 'True' , 'Enabled' , 'True' , 'Playing', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
    ( 309,  ''        , ''       , 'Playlist', 'Paused' , 'DS3'     , 'Playing', 'DS2'     , 'Stopped',  'Enabled' , 'False', 'Enabled' , 'False', 'Waiting', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
    ( 310,  ''        , ''       , 'Playlist', 'Stopped', 'DS3'     , 'Stopped', 'DS2'     , 'Playing',  'Enabled' , 'False', 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Waiting', 'DS2', 'DS2' ),
    ( 311,  ''        , ''       , 'Playlist', 'Playing', 'DS3'     , 'Stopped', 'DS2'     , 'Playing',  'Enabled' , 'True' , 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Waiting', 'DS2', 'DS2' ),
    ( 312,  ''        , ''       , 'Playlist', 'Paused' , 'DS3'     , 'Stopped', 'DS2'     , 'Playing',  'Enabled' , 'False', 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Waiting', 'DS2', 'DS2' ),
    ( 313,  ''        , ''       , 'Playlist', 'Stopped', 'DS3'     , 'Playing', 'DS2'     , 'Playing',  'Enabled' , 'False', 'Enabled' , 'False', 'Waiting', 'DS3', 'DS3', 'Waiting', 'DS2', 'DS2' ),
    ( 314,  ''        , ''       , 'Playlist', 'Playing', 'DS3'     , 'Playing', 'DS2'     , 'Playing',  'Enabled' , 'True' , 'Enabled' , 'True' , 'Playing', 'DS3', 'DS3', 'Playing', 'DS2', 'DS2' ),
    ( 315,  ''        , ''       , 'Playlist', 'Paused' , 'DS3'     , 'Playing', 'DS2'     , 'Playing',  'Enabled' , 'False', 'Enabled' , 'False', 'Waiting', 'DS3', 'DS3', 'Waiting', 'DS2', 'DS2' ),
    
    # Id || Setup                                                                                     || Checks 
    #    || DS4                  | DS3                  | DS2                  | DS1                  || DS3 Sender         | DS2 Sender         | DS2 Receiver           | DS1 Receiver          
    #    || Source    | State    | Source    | State    | Source    | State    | Source    | State    || Status    | Audio  | Status    | Audio  | State    | Uri  | Meta | State    | Uri  | Meta
#    ( 400,  'Playlist', 'Stopped', 'Pure'    , ''       , 'DS3'     , 'Stopped', 'DS2'     , 'Stopped',  'Enabled' , 'True' , 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
#    ( 401,  'Playlist', 'Stopped', 'Pure'    , ''       , 'DS3'     , 'Playing', 'DS2'     , 'Stopped',  'Enabled' , 'True' , 'Enabled' , 'True' , 'Playing', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
#    ( 402,  'Playlist', 'Playing', 'Pure'    , ''       , 'DS3'     , 'Stopped', 'DS2'     , 'Stopped',  'Enabled' , 'True' , 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
#    ( 403,  'Playlist', 'Playing', 'Pure'    , ''       , 'DS3'     , 'Playing', 'DS2'     , 'Stopped',  'Enabled' , 'True' , 'Enabled' , 'True' , 'Playing', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
#    ( 404,  'Playlist', 'Stopped', 'Pure'    , ''       , 'DS3'     , 'Stopped', 'DS2'     , 'Playing',  'Enabled' , 'True' , 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Waiting', 'DS2', 'DS2' ),
#    ( 405,  'Playlist', 'Stopped', 'Pure'    , ''       , 'DS3'     , 'Playing', 'DS2'     , 'Playing',  'Enabled' , 'True' , 'Enabled' , 'True' , 'Playing', 'DS3', 'DS3', 'Playing', 'DS2', 'DS2' ),
#    ( 406,  'Playlist', 'Playing', 'Pure'    , ''       , 'DS3'     , 'Stopped', 'DS2'     , 'Playing',  'Enabled' , 'True' , 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Waiting', 'DS2', 'DS2' ),
#    ( 407,  'Playlist', 'Playing', 'Pure'    , ''       , 'DS3'     , 'Playing', 'DS2'     , 'Playing',  'Enabled' , 'True' , 'Enabled' , 'True' , 'Playing', 'DS3', 'DS3', 'Playing', 'DS2', 'DS2' ),
#    
#    ( 500,  'Playlist', 'Stopped', 'Analog'  , ''       , 'DS3'     , 'Stopped', 'DS2'     , 'Stopped',  'Enabled' , 'True' , 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
#    ( 501,  'Playlist', 'Stopped', 'Analog'  , ''       , 'DS3'     , 'Playing', 'DS2'     , 'Stopped',  'Enabled' , 'True' , 'Enabled' , 'True' , 'Playing', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
#    ( 502,  'Playlist', 'Playing', 'Analog'  , ''       , 'DS3'     , 'Stopped', 'DS2'     , 'Stopped',  'Enabled' , 'True' , 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
#    ( 503,  'Playlist', 'Playing', 'Analog'  , ''       , 'DS3'     , 'Playing', 'DS2'     , 'Stopped',  'Enabled' , 'True' , 'Enabled' , 'True' , 'Playing', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
#    ( 504,  'Playlist', 'Stopped', 'Analog'  , ''       , 'DS3'     , 'Stopped', 'DS2'     , 'Playing',  'Enabled' , 'True' , 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Waiting', 'DS2', 'DS2' ),
#    ( 505,  'Playlist', 'Stopped', 'Analog'  , ''       , 'DS3'     , 'Playing', 'DS2'     , 'Playing',  'Enabled' , 'True' , 'Enabled' , 'True' , 'Playing', 'DS3', 'DS3', 'Playing', 'DS2', 'DS2' ),
#    ( 506,  'Playlist', 'Playing', 'Analog'  , ''       , 'DS3'     , 'Stopped', 'DS2'     , 'Playing',  'Enabled' , 'True' , 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Waiting', 'DS2', 'DS2' ),
#    ( 507,  'Playlist', 'Playing', 'Analog'  , ''       , 'DS3'     , 'Playing', 'DS2'     , 'Playing',  'Enabled' , 'True' , 'Enabled' , 'True' , 'Playing', 'DS3', 'DS3', 'Playing', 'DS2', 'DS2' ),
#    
#    ( 600,  'Playlist', 'Stopped', 'SPDIF'   , ''       , 'DS3'     , 'Stopped', 'DS2'     , 'Stopped',  'Enabled' , 'True' , 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
#    ( 601,  'Playlist', 'Stopped', 'SPDIF'   , ''       , 'DS3'     , 'Playing', 'DS2'     , 'Stopped',  'Enabled' , 'True' , 'Enabled' , 'True' , 'Playing', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
#    ( 602,  'Playlist', 'Playing', 'SPDIF'   , ''       , 'DS3'     , 'Stopped', 'DS2'     , 'Stopped',  'Enabled' , 'True' , 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
#    ( 603,  'Playlist', 'Playing', 'SPDIF'   , ''       , 'DS3'     , 'Playing', 'DS2'     , 'Stopped',  'Enabled' , 'True' , 'Enabled' , 'True' , 'Playing', 'DS3', 'DS3', 'Stopped', 'DS2', 'DS2' ),
#    ( 604,  'Playlist', 'Stopped', 'SPDIF'   , ''       , 'DS3'     , 'Stopped', 'DS2'     , 'Playing',  'Enabled' , 'True' , 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Waiting', 'DS2', 'DS2' ),
#    ( 605,  'Playlist', 'Stopped', 'SPDIF'   , ''       , 'DS3'     , 'Playing', 'DS2'     , 'Playing',  'Enabled' , 'True' , 'Enabled' , 'True' , 'Playing', 'DS3', 'DS3', 'Playing', 'DS2', 'DS2' ),
#    ( 606,  'Playlist', 'Playing', 'SPDIF'   , ''       , 'DS3'     , 'Stopped', 'DS2'     , 'Playing',  'Enabled' , 'True' , 'Enabled' , 'False', 'Stopped', 'DS3', 'DS3', 'Waiting', 'DS2', 'DS2' ),
#    ( 607,  'Playlist', 'Playing', 'SPDIF'   , ''       , 'DS3'     , 'Playing', 'DS2'     , 'Playing',  'Enabled' , 'True' , 'Enabled' , 'True' , 'Playing', 'DS3', 'DS3', 'Playing', 'DS2', 'DS2' )
    ]


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
