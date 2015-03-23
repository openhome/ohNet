#!/usr/bin/env python
"""SongcastConnect - test connect/disconnect/following works correctly

Parameters:
    arg#1 - DUT #1 ['local' for internal SoftPlayer on loopback]
    arg#2 - DUT #2 ['local' for internal SoftPlayer on loopback]
    arg#3 - DUT #3 ['local' for internal SoftPlayer on loopback]
    arg#4 - DUT #4 ['local' for internal SoftPlayer on loopback]
    arg#5 - test scenarios [1,2,3,4,5,all]
    arg#6 - disconnect method [stop,source,sender,standby,all]
    arg#7 - sender mode [unicast/multicast] - (optional - default unicast)

Terminology:
    Sender   - device which is the original source of the audio stream
    Repeater - device receiving stream directly from sender and re-sending
               the stream out to the slave device(s)
    Slave(s) - device(s) receiving audio from a receiver

Test configuration:
                                              +-----+
                                              |     |
                    +-------------------------+  C  |
                    |                         |     |
                    |                         +-----+
                    |
                    |
        +-----+     |      +-----+            +-----+
        |     |     |      |     |            |     |
        |  A  +-----+------+  B  +------------+  D  |
        |     |            |     |            |     |
        +-----+            +-----+            +-----+

        A - Sender
        B - Repeater, following A
        C - Slave (on B) following A
        D - Slave (on B) following B

Test Scenarios:

        1) Checking audio on sender
            - Soundcard on A    (A=DS-1, B=DS-2, C=DS-3, D=DS-4)
            - A playing
            - connect B to A    - no dropout on A
            - connect C to A    - no dropout on A
            - connect D to B    - no dropout on A
            - disconnect B      - no dropout on A, D state -> waiting
            - disconnect C      - no dropout on A
            - disconnect D      - no dropout on A
            - A stopped         - A drops out

        2) Checking audio on repeater
            - Soundcard on B    (B=DS-1, A=DS-2, C=DS-3, D=DS-4)
            - A playing
            - connect B to A    - no dropout on B
            - connect C to A    - no dropout on B
            - connect D to B    - no dropout on B
            - disconnect C      - no dropout on B
            - disconnect D      - no dropout on B
            - disconnect A      - B drops out

        3) Checking audio on slave on sender
            - Soundcard on C    (C=DS-1, A=DS-2, B=DS-3, D=DS-4)
            - A playing
            - connect B to A
            - connect C to A
            - connect D to B    - no dropout on C
            - disconnect B      - no dropout on C, D state -> waiting
            - disconnect D      - no dropout on C
            - disconnect A      - C drops out

        4) Checking audio on slave on repeater
            - Soundcard on D    (D=DS-1, A=DS-2, B=DS-3, C=DS-4)
            - A playing
            - connect B to A
            - connect D to B
            - connect C to A    - no dropout on D
            - disconnect C      - no dropout on D
            - disconnect B      - D drops out - state-> waiting
            
        5) Checking audio on slave follows repeater (trac #3165)  
            - Soundcard on D    (D=DS-1, A=DS-2, B=DS-3, C=DS-4)
            - A playing
            - C playing
            - connect B to A    - no dropout on B
            - connect D to B    - audio on D = audio on C
            - connect B to C    - audio on D = audio on C
"""

# Differences from DS test:
#    - removed 'reboot' disconnect method
 
import _FunctionalTest
import BaseTest                   as BASE
import Upnp.ControlPoints.Volkano as Volkano
import Utils.Network.HttpServer   as HttpServer
import Utils.Common               as Common
import _SoftPlayer                as SoftPlayer
import os
import random
import re
import sys
import threading
import time

kAudioRoot = os.path.join( _FunctionalTest.audioDir, 'LRTones/' )
kTrackList = os.path.join( kAudioRoot, 'TrackList.xml' )


class TestSongcastConnect( BASE.BaseTest ):
    """Class to check connect/disconnect of mcast devices"""
    
    def __init__( self ):
        """Constructor"""
        BASE.BaseTest.__init__( self )
        self.dut1    = None
        self.dut2    = None
        self.dut3    = None
        self.dut4    = None
        self.dut1Dev = None
        self.dut2Dev = None
        self.dut3Dev = None
        self.dut4Dev = None
        self.soft1   = None
        self.soft2   = None
        self.soft3   = None
        self.soft4   = None
        self.track1  = None
        self.track2  = None
        self.server  = None
        self.msg     = ''

    def Test( self, args ):
        """Songcast connect/disconnect test"""
        dut1Name   = None
        dut2Name   = None
        dut3Name   = None
        dut4Name   = None
        scenario   = None
        disconnect = None
        loopback   = False
        senderMode = 'unicast'

        # parse command line arguments
        try:
            dut1Name   = args[1]
            dut2Name   = args[2]
            dut3Name   = args[3]
            dut4Name   = args[4]
            scenario   = args[5].lower()
            disconnect = args[6].lower()
            if len( args ) > 7:
                senderMode = args[7].lower()
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )
            
        if scenario not in ['1','2','3','4','5', 'all']:
            self.log.Abort( '', 'Invalid scenario %s' % scenario )
            
        if disconnect not in ['stop','source','sender','standby', 'all']:
            self.log.Abort( '', 'Invalid disconnect method %s' % disconnect )
                            
        if disconnect == 'all':
            disconnect = ['stop','source','sender','standby']
        else:
            disconnect = [disconnect]

        if senderMode not in ('unicast', 'multicast'):
            self.log.Abort( '', 'Invalid sender mode %s' % senderMode )

        if dut1Name.lower()=='local' or dut2Name.lower()=='local' or dut3Name.lower()=='local' or dut4Name.lower()=='local':
            if dut1Name.lower()!='local' or dut2Name.lower()!='local' or dut3Name.lower()!='local' or dut4Name.lower()!='local':
                self.log.Abort( '', 'Local loopback can only apply to ALL or NONE devices' )

        # start audio server
        self.server = HttpServer.HttpServer( kAudioRoot )
        self.server.Start()
        
        # get tracks to use for playlist
        tracks = Common.GetTracks( kTrackList, self.server )
        self.track1 = [tracks[0]]
        self.track2 = [tracks[1]]
        
        # init duts
        if dut1Name.lower() == 'local':
            loopback = True
            self.soft1 = SoftPlayer.SoftPlayer( aRoom='TestDev1', aLoopback=loopback )
            dut1Name = self.soft1.name
        if dut2Name.lower() == 'local':
            self.soft2 = SoftPlayer.SoftPlayer( aRoom='TestDev2', aLoopback=loopback )
            dut2Name = self.soft2.name
        if dut3Name.lower() == 'local':
            self.soft3 = SoftPlayer.SoftPlayer( aRoom='TestDev3', aLoopback=loopback )
            dut3Name = self.soft3.name
        if dut4Name.lower() == 'local':
            self.soft4 = SoftPlayer.SoftPlayer( aRoom='TestDev4', aLoopback=loopback )
            dut4Name = self.soft4.name
        self.dut1Dev = dut1Name.split( ':' )[0]
        self.dut2Dev = dut2Name.split( ':' )[0]
        self.dut3Dev = dut3Name.split( ':' )[0]
        self.dut4Dev = dut4Name.split( ':' )[0]
        self.dut1 = Volkano.VolkanoDevice( dut1Name, aIsDut=True, aLoopback=loopback )
        self.dut2 = Volkano.VolkanoDevice( dut2Name, aIsDut=True, aLoopback=loopback )
        self.dut3 = Volkano.VolkanoDevice( dut3Name, aIsDut=True, aLoopback=loopback )
        self.dut4 = Volkano.VolkanoDevice( dut4Name, aIsDut=True, aLoopback=loopback )

        mode = '1'      # 1->unicast, 0->multicast
        if senderMode == 'multicast': mode = '0'
        for dut in [self.dut1, self.dut2, self.dut3, self.dut4]:
            dut.config.SetValue( 'Sender.Enabled', '1' )
            dut.config.SetValue( 'Sender.Mode', mode )

        if self.dut1.volume is not None:
            self.dut1.volume.volume = 75

        # run the selected test scenarios
        for self.disconx in disconnect:
            if '1' in scenario or 'all' in scenario:
                self.__TestScenario1()
            if '2' in scenario or 'all' in scenario:
                self.__TestScenario2()
            if '3' in scenario or 'all' in scenario:
                self.__TestScenario3()
            if '4' in scenario or 'all' in scenario:
                self.__TestScenario4()
            if '5' in scenario or 'all' in scenario:
                self.__TestScenario5()

        # stop playback            
        self.dut4.playlist.Stop()
        self.dut3.playlist.Stop()
        self.dut2.playlist.Stop()
        self.dut1.playlist.Stop()
                    
    def Cleanup( self ):
        """Perform cleanup on test exit"""
        if self.dut4:
            self.dut4.Shutdown()
        if self.dut3:
            self.dut3.Shutdown()
        if self.dut2:
            self.dut2.Shutdown()
        if self.dut1:
            self.dut1.Shutdown()
        if self.soft4:
            self.soft4.Shutdown()
        if self.soft3:
            self.soft3.Shutdown()
        if self.soft2:
            self.soft2.Shutdown()
        if self.soft1:
            self.soft1.Shutdown()
        if self.server:
            self.server.Shutdown()
        BASE.BaseTest.Cleanup( self )                

    def __TestScenario1( self ):
        """Test scenario (1) checking audio on sender
            - Soundcard on A    (A=DS-1, B=DS-2, C=DS-3, D=DS-4)
            - A playing
            - connect B to A    - no dropout on A
            - connect C to A    - no dropout on A
            - connect D to B    - no dropout on A
            - disconnect B      - no dropout on A, B state-> waiting
            - disconnect C      - no dropout on A
            - disconnect D      - no dropout on A
            - A stopped         - A drops out
        """
        self.msg = '(1) checking audio on sender: '
        self.__LogHeader()
        self.__ClearSources()
        self.__StartPlayback( self.dut1 )
        self.__Follows( self.dut2, self.dut1 )
        self.__Follows( self.dut3, self.dut1 )
        self.__Follows( self.dut4, self.dut2 )
        self.__Disconnect( self.dut2 )
        self.log.FailUnless( self.dut4Dev, self.dut4.receiver.transportState=='Waiting',
            '(1) Actual/Expected receiver state (%s/Waiting) on %s' %
            (self.dut4.receiver.transportState, self.dut4.friendlyName.split( ':' )[0]) )
        self.__Disconnect( self.dut3 )
        self.__Disconnect( self.dut4 )
        self.__StopPlayback( self.dut1 )
        
    def __TestScenario2( self ):
        """Test scenario (2) checking audio on repeater
            - Soundcard on B    (B=DS-1, A=DS-2, C=DS-3, D=DS-4)
            - A playing
            - connect B to A    - B starts with no audio
            - connect C to A    - no dropout on B
            - connect D to B    - no dropout on B
            - disconnect C      - no dropout on B
            - disconnect D      - no dropout on B
            - A stopped         - B drops out
        """
        self.msg = '(2) checking audio on repeater: '
        self.__LogHeader()
        self.__ClearSources()
        self.__StartPlayback( self.dut2 )
        self.__Follows( self.dut1, self.dut2 )
        self.__Follows( self.dut3, self.dut2 )
        self.__Follows( self.dut4, self.dut1 )
        self.__Disconnect( self.dut3 )
        self.__Disconnect( self.dut4 )
        self.__StopPlayback( self.dut2 )

    def __TestScenario3( self ):
        """Test scenario (3) checking audio on slave on sender
            - Soundcard on C    (C=DS-1, A=DS-2, B=DS-3, D=DS-4)
            - A playing
            - connect B to A    - no audio on C
            - connect C to A    - C starts with no audio
            - connect D to B    - no dropout on C
            - disconnect B      - no dropout on C, D state -> waiting
            - disconnect D      - no dropout on C
            - A stopped         -  drops out
        """
        self.msg = '(3) checking audio on slave on sender: '
        self.__LogHeader()
        self.__ClearSources()
        self.__StartPlayback( self.dut2 )
        self.__Follows( self.dut3, self.dut2 )
        self.__Follows( self.dut1, self.dut2 )
        self.__Follows( self.dut4, self.dut3 )
        self.__Disconnect( self.dut3 )
        self.log.FailUnless( self.dut4Dev, self.dut4.receiver.transportState=='Waiting',
            '(3) Actual/Expected receiver state (%s/Waiting) on %s' %
            (self.dut4.receiver.transportState, self.dut4.friendlyName.split( ':' )[0]) )
        self.__Disconnect( self.dut4 )
        self.__StopPlayback( self.dut2 )
            
    def __TestScenario4( self ):
        """Test scenario (4) checking audio on slave on repeater
            - Soundcard on D    (D=DS-1, A=DS-2, B=DS-3, C=DS-4)
            - A playing
            - connect B to A    - no audio on D
            - connect D to B    - D starts with no audio
            - connect C to A    - no dropout on D
            - disconnect C      - no dropout on D
            - disconnect B      - D drops out, B state-> waiting
        """
        self.msg = '(4) checking audio on slave on repeater: '
        self.__LogHeader()
        self.__ClearSources()
        self.__StartPlayback( self.dut2 )
        self.__Follows( self.dut3, self.dut2 )
        self.__Follows( self.dut1, self.dut3 )
        self.__Follows( self.dut4, self.dut2 )
        self.__Disconnect( self.dut4 )
        self.__Disconnect( self.dut3 )
        self.log.FailUnless( self.dut1Dev, self.dut1.receiver.transportState=='Waiting',
            '(4) Actual/Expected receiver state (%s/Waiting) on %s' %
            (self.dut1.receiver.transportState, self.dut1.friendlyName.split( ':' )[0]) )

    def __TestScenario5( self ):
        """Test scenario (5) checking audio on slave on repeater
            - Soundcard on D    (D=DS-1, A=DS-2, B=DS-3, C=DS-4)
            - A playing
            - C playing
            - connect B to A    - no audio on D
            - connect D to B    - audio on D = audio on B
            - connect B to C    - audio on D = audio on C
        """
        self.msg = '(5) checking audio on slave follows repeater (trac 3165)'
        self.__LogHeader()
        self.__ClearSources()
        self.__StartPlayback( self.dut2, aTrack=1 )
        self.__StartPlayback( self.dut4, aTrack=2 )
        self.__Follows( self.dut3, self.dut2 )
        self.__Follows( self.dut1, self.dut3 )
        self.__Follows( self.dut3, self.dut4 )

    def __LogHeader( self ):
        """Log header block for test scenario"""
        self.log.Info( '' )
        self.log.Info( '', '-----------------------------------------------------' )
        self.log.Info( '', 'Test Scenario %s, disconnect method: %s' % (self.msg, self.disconx) )
        self.log.Info( '', '-----------------------------------------------------' )
        self.log.Info( '' )

    def __ClearSources( self ):
        """Clear senders and set source to playlist on all DUTs"""
        # setting all senders to '' was giving obscure lock-ups in the DS. No
        # idea what's going on, but leaving them alone (a more natural use) seems
        # to cure the issues
        self.log.Info( '' )
        self.log.Info( '', 'Clearing sources on ALL DUTs' )
        self.log.Info( '' )
        self.dut1.product.sourceIndex = 0
        self.dut1.playlist.DeleteAllTracks()
        self.dut2.product.sourceIndex = 0
        self.dut2.playlist.DeleteAllTracks()
        self.dut3.product.sourceIndex = 0
        self.dut3.playlist.DeleteAllTracks()
        self.dut4.product.sourceIndex = 0
        self.dut4.playlist.DeleteAllTracks()
        time.sleep( 5 )
        
    def __StartPlayback( self, aDut, aTrack=1 ):
        """Start playback on specified DS"""
        if aTrack == 1:
            track = self.track1
        else:
            track = self.track2
        dutName = aDut.friendlyName.split( ':' )[0]
        event = threading.Event()

        # noinspection PyUnusedLocal
        def __EventCb( aService, aSvName, aSvVal, aSvSeq ):
            if aSvName == 'TransportState':
                if aSvVal == 'Playing':
                    event.set()
                
        self.log.Info( '' )
        self.log.Info( dutName, 'Starting playback' )
        self.log.Info( '' )
        aDut.playlist.DeleteAllTracks()
        aDut.playlist.repeat = True
        aDut.playlist.AddPlaylist( track )
        aDut.playlist.AddSubscriber( __EventCb )
        event.clear()
        aDut.playlist.Play()
        event.wait( 5 )
        aDut.playlist.RemoveSubscriber( __EventCb )
        time.sleep( 5 )     # play a bit into track
        self.log.FailUnless( dutName, aDut.playlist.transportState == 'Playing',
            '%s%s STARTED playback' % (self.msg, dutName) )
            
    def __Follows( self, aReceiver, aSender ):
        """Set receiver to follow sender, check for dropout"""
        receiverName = aReceiver.friendlyName.split( ':' )[0]
        senderName = aSender.friendlyName.split( ':' )[0]
        event = threading.Event()

        # noinspection PyUnusedLocal
        def __EventCb( aService, aSvName, aSvVal, aSvSeq ):
            if aSvName == 'TransportState':
                if aSvVal == 'Playing':
                    event.set()
                    
        self.log.Info( '' )
        self.log.Info( receiverName, 'Setting as receiver on %s' % senderName )
        self.log.Info( '' )
        time.sleep( 1 ) 
        uri = aSender.sender.uri
        meta = aSender.sender.metadata
        aReceiver.receiver.SetSender( uri, meta )
        aReceiver.receiver.AddSubscriber( __EventCb )
        event.clear()
        aReceiver.receiver.Play()
        event.wait( 5 )
        aReceiver.receiver.RemoveSubscriber( __EventCb )
        time.sleep( 1 ) 
        self.log.FailUnless( receiverName, aReceiver.receiver.transportState == 'Playing', 
            '%s%s PLAYING from %s' % (self.msg, receiverName, senderName) )
        
    def __Disconnect( self, aDut ):
        """Disconnect device from the setup, check for dropout"""
        name = aDut.friendlyName
        dutName = name.split( ':' )[0]       
        self.log.Info( '' )
        self.log.Info( dutName, 'Disconnecting using %s method' % self.disconx )
        self.log.Info( '' )                    
        time.sleep( 1 ) 
        if self.disconx == 'stop':
            aDut.receiver.Stop()
        elif self.disconx == 'source':
            aDut.playlist.Play()
        elif self.disconx == 'sender':
            aDut.receiver.SetSender( '', '' )
        elif self.disconx == 'standby':
            aDut.product.CycleStandby()
        time.sleep( 1 ) 
        
    def __StopPlayback( self, aDut ):
        """Stop playback on specified DS, check for audio dropout"""
        dutName = aDut.friendlyName.split( ':' )[0]
        event = threading.Event()

        # noinspection PyUnusedLocal
        def __EventCb( aService, aSvName, aSvVal, aSvSeq ):
            if aSvName == 'TransportState':
                if aSvVal == 'Stopped':
                    event.set()

        self.log.Info( '' )
        self.log.Info( dutName, 'Stopping playback' )
        self.log.Info( '' )                    
        aDut.playlist.AddSubscriber( __EventCb )
        event.clear()
        aDut.playlist.Stop()
        event.wait( 5 )
        aDut.playlist.RemoveSubscriber( __EventCb )
        self.log.FailUnless( dutName, aDut.playlist.transportState == 'Stopped',
            '%s%s STOPPED playback' % (self.msg, dutName) )
        

if __name__ == '__main__':
    
    BASE.Run( sys.argv )
        