#!/usr/bin/env python
"""TestPlaylistDropout - test for audio dropout in playlists

Parameters:
    arg#1 - Sender ['local' for internal SoftPlayer]
    arg#2 - Receiver/Repeater ['local' for internal SoftPlayer] - optional (None = not present)
    arg#3 - Receiver/Slave ['local' for internal SoftPlayer] - optional (None = not present)
    arg#4 - Test duration (secs) or 'forever'
    
This verifies playlist audio output by the DUT does not suffer from audio dropout.
""" 

# Differences from DS test:
#    - cut-down variant - only monitors events, no monitoring of actual audio
#    - uses different test tone set
#    - removed songcast mode param (as N/A)

import _FunctionalTest
import BaseTest                       as BASE
import Upnp.ControlPoints.Volkano     as Volkano
import Upnp.ControlPoints.MediaServer as Server
import Utils.Network.HttpServer       as HttpServer
import Utils.Common                   as Common
import _SoftPlayer                    as SoftPlayer
import LogThread
import Path
import os
import sys
import threading
import time

kAudioRoot = os.path.join( Path.AudioDir(), 'LRTones/' )
kTrackList = os.path.join( kAudioRoot, 'TrackList.xml' )


class TestPlaylistDropout( BASE.BaseTest ):
    """Class to check for dropout in audio output"""
    
    def __init__( self ):
        "Constructor for AudioDropout test"
        self.sender          = None
        self.receiver        = None
        self.slave           = None
        self.server          = None
        self.soft1           = None
        self.soft2           = None
        self.soft3           = None
        self.monitor         = False
        self.senderPlaying   = threading.Event()
        self.receiverPlaying = threading.Event()
        self.slavePlaying    = threading.Event()
        self.receiverUri     = threading.Event()
        self.slaveUri        = threading.Event()
        self.durationDone    = threading.Event() 
        BASE.BaseTest.__init__( self )

    def Test( self, args ):
        "Audio Dropout test"    
        # parse command line arguments
        try:
            senderName   = args[1]
            receiverName = args[2]
            slaveName    = args[3]
            duration     = args[4].lower()
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )
            
        if receiverName.lower() == 'none':
           receiverName = None
            
        if slaveName.lower() == 'none':
           slaveName = None
            
        if duration != 'forever':
            duration = int( duration )
            
        # start audio server
        self.server = HttpServer.HttpServer( kAudioRoot )
        self.server.Start()        
        tracks = Common.GetTracks( kTrackList, self.server )

        # create and configure sender
        if senderName.lower() == 'local':
            self.soft1 = SoftPlayer.SoftPlayer( aRoom='TestSender' )
            senderName = 'TestSender:SoftPlayer'
        self.senderDev = senderName.split( ':' )[0]
        self.sender = Volkano.VolkanoDevice( senderName, aIsDut=True )
        self.sender.playlist.AddSubscriber( self._SenderPlaylistCb )
                
        # load sender's playlist and start playback
        self.sender.playlist.repeat = 'on';
        self.sender.playlist.shuffle = 'on';
        self.sender.playlist.DeleteAllTracks()
        self.sender.playlist.AddPlaylist( tracks )
        self.sender.playlist.SeekIndex( 0 )
        self.senderPlaying.wait( 10 )
        if self.sender.playlist.transportState != 'Playing':
            self.log.Abort( self.senderDev, 'Sender failed to start playback' )
                
        # create and connect receiver (if specified)
        if receiverName:
            if receiverName.lower() == 'local':
                self.soft2 = SoftPlayer.SoftPlayer( aRoom='TestRcvr' )
                receiverName = 'TestRcvr:SoftPlayer'
            self.rcvrDev = receiverName.split( ':' )[0]
            self.receiver = Volkano.VolkanoDevice( receiverName, aIsDut=True )
            self.receiver.receiver.AddSubscriber( self._ReceiverReceiverCb )
            self.receiver.receiver.SetSender( self.sender.sender.uri, self.sender.sender.metadata )
            self.receiverUri.wait( 5 )
            if self.receiver.receiver.transportState != 'Playing':
                self.receiver.receiver.Play()
                self.receiverPlaying.wait( 5 )
                if self.receiver.receiver.transportState != 'Playing':
                    self.log.Abort( self.rcvrDev, 'Receiver failed to start playback' )
            
        # create and connect slave (if specified)
        if slaveName:
            if slaveName.lower() == 'local':
                self.soft3 = SoftPlayer.SoftPlayer( aRoom='TestSlave' )
                slaveName = 'TestSlave:SoftPlayer'
            self.slaveDev = slaveName.split( ':' )[0]
            self.slave = Volkano.VolkanoDevice( slaveName, aIsDut=True )
            self.slave.receiver.AddSubscriber( self._SlaveReceiverCb )
            self.slave.receiver.SetSender( self.receiver.sender.uri, self.receiver.sender.metadata )
            self.slaveUri.wait( 5 )
            if self.slave.receiver.transportState != 'Playing':
                self.slave.receiver.Play()
                self.slavePlaying.wait( 5 )
                if self.slave.receiver.transportState != 'Playing':
                    self.log.Abort( self.slaveDev, 'Slave failed to start playback' )

        # Monitor events until timer expired / forever
        self.monitor = True
        self.durationDone.clear()
        if duration != 'forever':
            self.exitTimer = LogThread.Timer( duration, self._DurationCb )
            self.exitTimer.start()
        self.durationDone.wait()
        
        # Cleanup
        self.sender.playlist.RemoveSubscriber( self._SenderPlaylistCb )
        self.sender.playlist.Stop()                 
        if self.receiver:
            self.receiver.receiver.RemoveSubscriber( self._ReceiverReceiverCb )
        if self.slave:
            self.slave.receiver.RemoveSubscriber( self._SlaveReceiverCb )        

    def Cleanup( self ):
        "Perform cleanup on test exit"
        if self.sender:    
            self.sender.Shutdown()
        if self.receiver:
            self.receiver.Shutdown()
        if self.slave:
            self.slave.Shutdown()
        if self.server:
            self.server.Shutdown()
        if self.soft1:
            self.soft1.Shutdown()
        if self.soft2:
            self.soft2.Shutdown()
        if self.soft3:
            self.soft3.Shutdown()
        BASE.BaseTest.Cleanup( self )                
        
    def _SenderPlaylistCb( self, service, svName, svVal, svSeq ):
        "Callback from Sender's Playlist service"
        if svName == 'TransportState':
            if svVal == 'Playing':
                self.senderPlaying.set()
            else:
                if self.monitor:
                    self.log.Fail( self.senderDev, "Sender dropout detected -> state is %s" % svVal )
                
    def _ReceiverReceiverCb( self, service, svName, svVal, svSeq ):
        "Callback from Receiver's Receiver service"
        if svName == 'TransportState':
            if svVal == 'Playing':
                self.receiverPlaying.set()
            else:
                if self.monitor:
                    self.log.Fail( self.rcvrDev, "Receiver dropout detected -> state is %s" % svVal )
        elif svName == 'Uri':
            self.receiverUri.set()
            
    def _SlaveReceiverCb( self, service, svName, svVal, svSeq ):
        "Callback from Slave's Receiver's service"
        if svName == 'TransportState':
            if svVal == 'Playing':
                self.slavePlaying.set()
            else:
                if self.monitor:
                    self.log.Fail( self.slaveDev, "Slave dropout detected -> state is %s" % svVal )
        elif svName == 'Uri':
            self.slaveUri.set()
            
    def _DurationCb( self ):
        "Callback from duration timer"
        self.durationDone.set()

            
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
        