#!/usr/bin/env python
"""BaseDropout - base class fro testing for audio dropout

Derived classes MUST

    - define self.tracks - the list of tracks to test (URI/Meta tuples)
    - define self.doc - docstring to print on parameter parse failure
    - call Test() method with following params
        - Sender
        - Receiver #1 (repeater) - 'None' if not present
        - Receiver #2 (slave) - 'None' if not present
        - Test duration (secs) or 'forever'

    For all players can use 'local' for internal SoftPlayer on loopback
"""

import _FunctionalTest
import BaseTest                       as BASE
import Upnp.ControlPoints.Volkano     as Volkano
import _SoftPlayer                    as SoftPlayer
import LogThread
import os
import sys
import threading
import time


def Run( aArgs ):
    """Pass the Run() call up to the base class"""
    BASE.Run( aArgs )


class BaseDropout( BASE.BaseTest ):
    """Base class for XxxDropout tests"""

    def __init__( self ):
        """Constructor for AudioDropout test"""
        self.doc             = 'Define docstring in derived class'
        self.tracks          = []
        self.sender          = None
        self.senderDev       = None
        self.receiver        = None
        self.receiverDev     = None
        self.slave           = None
        self.slaveDev        = None
        self.soft1           = None
        self.soft2           = None
        self.soft3           = None
        self.monitor         = False
        self.exitTimer       = None
        self.senderPlaying   = threading.Event()
        self.receiverPlaying = threading.Event()
        self.slavePlaying    = threading.Event()
        self.receiverUri     = threading.Event()
        self.slaveUri        = threading.Event()
        self.durationDone    = threading.Event() 
        BASE.BaseTest.__init__( self )

    def Test( self, args ):
        """Audio Dropout test"""
        senderName   = ''
        receiverName = ''
        slaveName    = ''
        duration     = 0
        loopback     = False
        softOptions  = None

        # parse command line arguments
        try:
            senderName   = args[1]
            receiverName = args[2]
            slaveName    = args[3]
            duration     = args[4].lower()
            if len( args ) > 5:
                softOptions = args[5]
        except:
            print '\n', self.doc, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )

        if senderName.lower() == 'local':
            loopback = True
            if receiverName.lower() not in ['local','none'] or slaveName.lower() not in ['local','none']:
                self.log.Abort( '', 'Local loopback can only apply to ALL or NONE devices' )
        if receiverName.lower() == 'local':
            if senderName.lower() != 'local' or slaveName.lower() not in ['local','none']:
                self.log.Abort( '', 'Local loopback can only apply to ALL or NONE devices' )
        if slaveName.lower() == 'local':
            if senderName.lower() != 'local' or receiverName.lower() != 'local':
                self.log.Abort( '', 'Local loopback can only apply to ALL or NONE devices' )

        if receiverName.lower() == 'none':
           receiverName = None
            
        if slaveName.lower() == 'none':
           slaveName = None
            
        if duration != 'forever':
            duration = int( duration )

        # create and configure sender
        if senderName.lower() == 'local':
            options = {'aRoom':'TestSender', 'aLoopback':loopback}
            if softOptions:
                options.update( softOptions )
            self.soft1 = SoftPlayer.SoftPlayer( **options )
            senderName = self.soft1.name
        self.senderDev = senderName.split( ':' )[0]
        self.sender = Volkano.VolkanoDevice( senderName, aIsDut=True, aLoopback=loopback )
        self.sender.playlist.AddSubscriber( self._SenderPlaylistCb )
                
        # load sender's playlist and start playback
        self.sender.playlist.repeat = 'on'
        self.sender.playlist.shuffle = 'on'
        self.sender.playlist.DeleteAllTracks()
        self.sender.playlist.AddPlaylist( self.tracks )
        self.sender.playlist.SeekIndex( 0 )
        self.senderPlaying.wait( 10 )
        if self.sender.playlist.transportState != 'Playing':
            self.log.Abort( self.senderDev, 'Sender failed to start playback' )
                
        # create and connect receiver (if specified)
        if receiverName:
            if receiverName.lower() == 'local':
                self.soft2 = SoftPlayer.SoftPlayer( aRoom='TestRcvr', aLoopback=loopback )
                receiverName = self.soft2.name
            self.receiverDev = receiverName.split( ':' )[0]
            self.receiver = Volkano.VolkanoDevice( receiverName, aIsDut=True, aLoopback=loopback )
            self.receiver.receiver.AddSubscriber( self._ReceiverReceiverCb )
            self.receiver.receiver.SetSender( self.sender.sender.uri, self.sender.sender.metadata )
            self.receiverUri.wait( 5 )
            if self.receiver.receiver.transportState != 'Playing':
                self.receiver.receiver.Play()
                self.receiverPlaying.wait( 5 )
                if self.receiver.receiver.transportState != 'Playing':
                    self.log.Abort( self.receiverDev, 'Receiver failed to start playback' )
            
        # create and connect slave (if specified)
        if slaveName:
            if slaveName.lower() == 'local':
                self.soft3 = SoftPlayer.SoftPlayer( aRoom='TestSlave', aLoopback=loopback )
                slaveName = self.soft3.name
            self.slaveDev = slaveName.split( ':' )[0]
            self.slave = Volkano.VolkanoDevice( slaveName, aIsDut=True, aLoopback=loopback )
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
        self.monitor = False

    def Cleanup( self ):
        """Perform cleanup on test exit"""
        if self.sender:
            self.sender.playlist.Stop()
            self.sender.Shutdown()
        if self.receiver:
            self.receiver.Shutdown()
        if self.slave:
            self.slave.Shutdown()
        if self.soft1:
            self.soft1.Shutdown()
        if self.soft2:
            self.soft2.Shutdown()
        if self.soft3:
            self.soft3.Shutdown()
        BASE.BaseTest.Cleanup( self )

    # noinspection PyUnusedLocal
    def _SenderPlaylistCb( self, service, svName, svVal, svSeq ):
        """Callback from Sender's Playlist service"""
        if svName == 'TransportState':
            if svVal == 'Playing':
                self.senderPlaying.set()
            else:
                if self.monitor:
                    self.log.Fail( self.senderDev, "Sender dropout detected -> state is %s" % svVal )
                
    # noinspection PyUnusedLocal
    def _ReceiverReceiverCb( self, service, svName, svVal, svSeq ):
        """Callback from Receiver's Receiver service"""
        if svName == 'TransportState':
            if svVal == 'Playing':
                self.receiverPlaying.set()
            else:
                if self.monitor:
                    self.log.Fail( self.receiverDev, "Receiver dropout detected -> state is %s" % svVal )
        elif svName == 'Uri':
            self.receiverUri.set()
            
    # noinspection PyUnusedLocal
    def _SlaveReceiverCb( self, service, svName, svVal, svSeq ):
        """Callback from Slave's Receiver's service"""
        if svName == 'TransportState':
            if svVal == 'Playing':
                self.slavePlaying.set()
            else:
                if self.monitor:
                    self.log.Fail( self.slaveDev, "Slave dropout detected -> state is %s" % svVal )
        elif svName == 'Uri':
            self.slaveUri.set()
            
    def _DurationCb( self ):
        """Callback from duration timer"""
        self.durationDone.set()
