#!/usr/bin/env python
"""TestPlaylistDropout - test for audio dropout in playlists

Parameters:
    arg#1 - Device Under Test (Sender)
    arg#2 - Device Under Test (Receiver/Repeater) - optional (None = not present)
    arg#3 - Device Under Test (Receiver/Slave) - optional (None = not present)
    arg#4 - Test duration (secs) or 'forever'
    
This verifies playlist audio output by the DUT does not suffer from audio
dropout.
""" 

# Differences from DS test:
#    - cut-down variant - only monitors events, no monitoring of actual audio
#    - uses different test tone set
#    - removed songcast mode param (as N/A)

import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.Volkano       as Volkano
import Upnp.ControlPoints.MediaServer   as Server
import Utils.Network.HttpServer         as HttpServer
import Utils.Common                     as Common
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
        self.sender       = None
        self.receiver     = None
        self.slave        = None
        self.server       = None
        self.playing      = threading.Event()
        self.durationDone = threading.Event() 
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

        # create sender, clear playlist and subscribe to events
        self.senderDev = senderName.split( ':' )[0]
        self.sender = Volkano.VolkanoDevice( senderName, aIsDut=True )
        if not receiverName and not slaveName:
            if self.sender.volume is not None:
                self.sender.volume.volume = 65
            
        self.sender.playlist.DeleteAllTracks()
        self.sender.playlist.AddSubscriber( self._SenderPlaylistCb )
                
        # create and connect receiver and slave (where specified)
        if receiverName:
            self.rcvrDev = receiverName.split( ':' )[0]
            self.receiver = Volkano.VolkanoDevice( receiverName, aIsDut=True )
            self.receiver.receiver.SetSender( self.sender.sender.uri, self.sender.sender.metadata )
            if not slaveName:
                if self.receiver.volume is not None:
                    self.receiver.volume.volume = 65
            self.receiver.receiver.Play()
            
        if slaveName:
            self.slaveDev = slaveName.split( ':' )[0]
            self.slave = Volkano.VolkanoDevice( slaveName, aIsDut=True )
            self.slave.receiver.SetSender( self.receiver.sender.uri, self.receiver.sender.metadata )
            if self.slave.volume is not None:
                self.slave.volume.volume = 65
            self.slave.receiver.Play()
        
        # Handle 'hub' products
        if slaveName:
            if self.slave.exakt is not None:
                import Utils.Audio.DigitalCrossover as DigitalCrossover
                DigitalCrossover.SetAllFlat( self.slave )
        elif receiverName:
            if self.receiver.exakt is not None:
                import Utils.Audio.DigitalCrossover as DigitalCrossover
                DigitalCrossover.SetAllFlat( self.receiver )
        else:
            if self.sender.exakt is not None:
                import Utils.Audio.DigitalCrossover as DigitalCrossover
                DigitalCrossover.SetAllFlat( self.sender )
                
        # load playlist and start playback
        self.sender.playlist.repeat = 'on';
        self.sender.playlist.shuffle = 'on';
        self.sender.playlist.AddPlaylist( tracks )
        self.playing.clear()
        self.sender.playlist.SeekIndex( 0 )
        self.sender.playlist.Play()
        self.playing.wait( 10 )
        if self.playing.is_set():
            time.sleep( 2 )         # let track info update
    
            # Add transport state monitors
            self.sender.playlist.AddSubscriber( self._SenderPlaylistMonitor )
            if self.receiver:
                self.receiver.receiver.AddSubscriber( self._ReceiverReceiverMonitor )
            if self.slave:
                self.slave.receiver.AddSubscriber( self._SlaveReceiverMonitor )
            
            # Monitor events until timer expired / forever
            self.durationDone.clear()
            if duration != 'forever':
                self.exitTimer = LogThread.Timer( duration, self._DurationCb )
                self.exitTimer.start()
            self.durationDone.wait()
        else:
            self.log.Fail( self.senderDev, 'Playback failed to start' )
        
        # Remove transport state monitor
        self.sender.playlist.RemoveSubscriber( self._SenderPlaylistMonitor )
        if self.receiver:
            self.receiver.receiver.RemoveSubscriber( self._ReceiverReceiverMonitor )
        if self.slave:
            self.slave.receiver.RemoveSubscriber( self._SlaveReceiverMonitor )

    def Cleanup( self ):
        "Perform cleanup on test exit"
        if self.sender:    
            self.sender.playlist.Stop()                 
            self.sender.playlist.RemoveSubscriber( self._SenderPlaylistCb )
            self.sender.Shutdown()
        if self.receiver:
            self.receiver.Shutdown()
        if self.slave:
            self.slave.Shutdown()
        if self.server:
            self.server.Shutdown()
        BASE.BaseTest.Cleanup( self )                
        
    def _SenderPlaylistCb( self, service, svName, svVal, svSeq ):
        "Callback from Playlist service on Sender device"
        if svName == 'TransportState':
            if svVal == 'Playing':
                self.playing.set()
            
    def _SenderPlaylistMonitor( self, service, svName, svVal, svSeq ):
        "Callback from Sender's Playlist service"
        if svName == 'TransportState':
            if svVal != 'Playing':
                self.log.Fail( self.senderDev, "Sender dropout detected -> state is %s" % svVal )
                
    def _ReceiverReceiverMonitor( self, service, svName, svVal, svSeq ):
        "Callback from Receiver's Receiver service"
        if svName == 'TransportState':
            if svVal != 'Playing':
                self.log.Fail( self.rcvrDev, "Receiver dropout detected -> state is %s" % svVal )
            
    def _SlaveReceiverMonitor( self, service, svName, svVal, svSeq ):
        "Callback from Slave's Receiver's service"
        if svName == 'TransportState':
            if svVal != 'Playing':
                self.log.Fail( self.slaveDev, "Slave dropout detected -> state is %s" % svVal )
            
    def _DurationCb( self ):
        "Callback from duration timer"
        self.durationDone.set()

            
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
        