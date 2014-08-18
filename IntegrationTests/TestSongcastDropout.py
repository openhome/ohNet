#!/usr/bin/env python
"""TestSongcastDropout - test for dropout between Songcast receivers

Parameters:
    arg#1 - DUT sender ['local' for internal SoftPlayer on loopback]
    arg#2 - List of DUT receivers ['local' for internal SoftPlayer on loopback] (comma seperated)
    arg#3 - Test duration (secs) or 'forever'
    
This verifies Songcaster audio output by the DUT does not suffer from dropout. 
""" 

# Differences from DS test:
#    - removed songcast sender mode param - set in softplayer at startup
#    - removed scope monitor of actual dropout
#    - removed ability to frig dropout using Diagnostics service

import _FunctionalTest
import BaseTest                   as BASE
import Upnp.ControlPoints.Volkano as Volkano
import Utils.Network.HttpServer   as HttpServer
import Utils.Common               as Common
import _SoftPlayer                as SoftPlayer
import LogThread
import os
import sys
import threading
import time

kAudioRoot = os.path.join( _FunctionalTest.audioDir, 'LongTones/' )
kTrackList = os.path.join( kAudioRoot, 'TrackList.xml' )


class TestSongcastDropout( BASE.BaseTest ):
    """Class to check for dropout in audio output using Songcaster as input"""
    
    def __init__( self ):
        """Constructor for Songcaster Dropout test"""
        BASE.BaseTest.__init__( self )
        self.sender        = None
        self.senderDev     = None
        self.server        = None
        self.rcvrs         = []
        self.softs         = []
        self.rxCount       = 0
        self.senderPlaying = threading.Event()
        self.senderStopped = threading.Event()
        self.rcvrPlaying   = threading.Event()
        self.rcvrUriSet    = threading.Event()
        self.durationEvt   = threading.Event()

    def Test( self, args ):
        """Songcast Dropout test"""
        senderName = None
        rcvrNames  = None
        duration   = None
        loopback   = False

        try:
            senderName = args[1]
            rcvrNames  = args[2]
            duration   = int( args[3] )
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )

        useLocal = False
        if senderName.lower() == 'local':
            useLocal = True
        for name in rcvrNames.split( ',' ):
            if name.lower() == 'local':
                useLocal = True

        if useLocal:
            if senderName.lower() != 'local':
                self.log.Abort( '', 'Local loopback can only apply to ALL or NONE devices (1)' )
            for name in rcvrNames.split( ',' ):
                if name.lower() != 'local':
                    self.log.Abort( '', 'Local loopback can only apply to ALL or NONE devices (2)' )

        # create sender
        if senderName.lower() == 'local':
            loopback = True
            soft = SoftPlayer.SoftPlayer( aRoom='TestSender', aLoopback=loopback )
            self.softs.append( soft )
            senderName = soft.name
        self.senderDev = senderName.split( ':' )[0]
        self.sender = Volkano.VolkanoDevice( senderName, aIsDut=True, aLoopback=loopback )
        self.sender.playlist.AddSubscriber( self._SenderPlaylistCb )

        # create receivers
        for name in rcvrNames.split( ',' ):
            self.rxCount += 1
            if name.lower() == 'local':
                soft = SoftPlayer.SoftPlayer( aRoom='TestRcvr%d' % self.rxCount, aLoopback=loopback )
                self.softs.append( soft )
                name = soft.name
            self.rcvrs.append( Volkano.VolkanoDevice( name, aIsDut=True, aLoopback=loopback ))
            
        # start audio server
        self.server = HttpServer.HttpServer( kAudioRoot )
        self.server.Start()

        # get test tone track
        tracks = Common.GetTracks( kTrackList, self.server )
        testTone = None
        for track in tracks:            
            if '-0dB' in track[0]:
                testTone = [track]
                break
            
        # start playback of tone on sender
        self.senderStopped.clear()
        self.sender.playlist.DeleteAllTracks()
        self.senderStopped.wait( 10 )
        self.sender.playlist.repeat = True
        self.sender.playlist.AddPlaylist( testTone )
        self.senderPlaying.clear()
        self.sender.playlist.SeekIndex( 0 )
        self.senderPlaying.wait( 10 )
        self.sender.playlist.RemoveSubscriber( self._SenderPlaylistCb )
        self.log.FailUnless( self.senderDev, self.sender.playlist.transportState == 'Playing',
            'Expected/Actual sender playback state - Playing/%s' %
            self.sender.playlist.transportState )
        
        # start songcast receipt on receivers
        for rcvr in self.rcvrs:
            rcvr.receiver.AddSubscriber( self._RcvrReceiverCb )
            self.rcvrUriSet.clear()
            rcvr.receiver.SetSender( '', '' )
            self.rcvrUriSet.wait( 5 )

            if rcvr.receiver.uri != self.sender.sender.uri:
                self.rcvrUriSet.clear()
                rcvr.receiver.SetSender( self.sender.sender.uri, self.sender.sender.metadata )
                self.rcvrUriSet.wait( 10 )
            if rcvr.receiver.transportState != 'Playing':
                self.rcvrPlaying.clear()
                rcvr.receiver.Play()
                self.rcvrPlaying.wait( 10 )
            rcvr.receiver.RemoveSubscriber( self._RcvrReceiverCb )
            rcvrDev = rcvr.product.productRoom
            self.log.FailUnless( rcvrDev, rcvr.receiver.uri == self.sender.sender.uri,
                'Expected/Actual receiver URI - %s/%s' %
                (self.sender.sender.uri, rcvr.receiver.uri) )
            self.log.FailUnless( rcvrDev, rcvr.receiver.transportState == 'Playing',
                'Expected/Actual receiver playback state - Playing/%s' %
                rcvr.receiver.transportState )
            
        # Add transport state monitors
        self.sender.playlist.AddSubscriber( self._SenderPlaylistMonitor )
        for rcvr in self.rcvrs:            
            rcvr.receiver.AddSubscriber( self._RcvrReceiverMonitor )
            
        # Run for specified time
        durationTimer = LogThread.Timer( duration, self._DurationCb )
        durationTimer.start()
        self.durationEvt.wait()
            
        # Remove transport state monitors
        self.sender.playlist.RemoveSubscriber( self._SenderPlaylistMonitor )
        for rcvr in self.rcvrs:            
            rcvr.receiver.RemoveSubscriber( self._RcvrReceiverMonitor )

        # stop playback            
        self.sender.playlist.Stop()

    def Cleanup( self ):
        """Perform cleanup on test exit"""
        if self.sender:
            self.sender.Shutdown()
        for rcvr in self.rcvrs:
            rcvr.Shutdown()
        for soft in self.softs:
            soft.Shutdown()
        if self.server:
            self.server.Shutdown()
        BASE.BaseTest.Cleanup( self )

    # noinspection PyUnusedLocal
    def _SenderPlaylistCb( self, service, svName, svVal, svSeq ):
        """Callback from Playlist Service UPnP events on sender device"""
        if svName == 'TransportState':
            if svVal == 'Playing':
                self.senderPlaying.set()
            elif svVal == 'Stopped':
                self.senderStopped.set()
                
    # noinspection PyUnusedLocal
    def _RcvrReceiverCb( self, service, svName, svVal, svSeq ):
        """Callback from Receiver Service UPnP events on receiver device"""
        if svName == 'TransportState':
            if svVal == 'Playing':
                self.rcvrPlaying.set()
        if svName == 'Uri':
            self.rcvrUriSet.set()
            
    # noinspection PyUnusedLocal
    def _SenderPlaylistMonitor( self, service, svName, svVal, svSeq ):
        """Callback from Sender's Playlist service"""
        if svName == 'TransportState':
            if svVal != 'Playing':
                self.log.Fail( self.senderDev, "Sender dropout detected -> state is %s" % svVal )
                
    # noinspection PyUnusedLocal
    def _RcvrReceiverMonitor( self, service, svName, svVal, svSeq ):
        """Callback from Receiver's Receiver service"""
        if svName == 'TransportState':
            if svVal != 'Playing':
                self.log.Fail( '', "Receiver dropout detected -> state is %s" % svVal )

    def _DurationCb( self ):
        """Callback from duration timer expiry"""
        self.durationEvt.set()

        
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
        