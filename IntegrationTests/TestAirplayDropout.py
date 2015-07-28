#!/usr/bin/env python
"""TestAirplayDropout - test for audio dropout on Net Aux source using AirPlay

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer]
    arg#2 - Test duration (secs) or 'forever'
    
Verifies AirPlay audio output by the DUT does not suffer from audio dropout
""" 
import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.OhMediaPlayer as OHMP
import Instruments.Network.DacpClient   as DacpClient
import _SoftPlayer                      as SoftPlayer
import LogThread 
import os       
import sys
import threading
import time

kItunesCtr = 'Music'


class TestAirplayDropout( BASE.BaseTest ):
    """Class to check for dropout in audio output using Airplay input"""
    
    def __init__( self, aSongcaster=None ):
        """Constructor for Airplay Dropout test"""
        BASE.BaseTest.__init__( self )
        self.dacp         = None
        self.dut          = None
        self.dutDev       = None
        self.soft         = None        
        self.shuttingDown = False
        self.tick         = None
        self.timer        = None
        self.songcaster   = aSongcaster
        self.finished     = threading.Event()

    def Test( self, args ):
        """Net Aux Audio Dropout test"""
        dutName      = ''
        duration     = '0'
        loopback     = False
        itunesGuid   = self.config.Get( 'itunes.guid' )
        itunesLib    = self.config.Get( 'itunes.library' )
        itunesAddr   = self.config.Get( 'itunes.address' )
        itunesTrack  = self.config.Get( 'itunes.track1k' )

        try:
            dutName      = args[1]
            duration     = args[2].lower()
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )
            
        if duration != 'forever':
            duration = int( duration )
            
        # setup DUT
        if dutName.lower() == 'local':
            loopback = True
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev' )
            dutName = self.soft.name
            time.sleep( 10 )     # allow time for iTunes to discover device
        self.dutDev = dutName.split( ':' )[0]
        self.dut = OHMP.OhMediaPlayerDevice( dutName, aIsDut=True )
        if self.dut.volume is not None:
            self.dut.volume.volume = 65

        # setup dacp (iTunes) control
        self.dacp = DacpClient.DacpClient( itunesGuid, itunesLib, itunesAddr )
        if dutName not in self.dacp.speakers:
            self.log.Abort( self.dacp.dev, '%s not available as iTunes speaker' % dutName )
        
        # setup iTunes to use local Music container
        if self.dacp.library in self.dacp.databases:
            self.dacp.database = self.dacp.library 
            if kItunesCtr in self.dacp.containers:
                self.dacp.container = kItunesCtr
            else:
                self.log.Abort( self.dacp.dev, '%s container not found in iTunes' % kItunesCtr )
        else: 
            self.log.Abort( self.dacp.dev, '%s database not found in iTunes' % self.dacp.library )
            
        self.dacp.volume  = 100
        if self.songcaster:
            self.dacp.speaker = 'My Computer'
        else:
            self.dacp.speaker = dutName
        self.dacp.PlayTrack( itunesTrack )
        self.dacp.repeat  = True
        time.sleep( 5 )
                    
        # setup playback and boundary condition monitor
        self.tick = LogThread.Timer( 1, self.__TickCb )
        self.tick.start()
        
        # start duration timer and wait for expiry
        if duration != 'forever':
            self.timer = LogThread.Timer( duration, self.__DurationCb )
            self.timer.start()
        self.finished.wait()
                            
    def Cleanup( self ):
        """Perform cleanup on test exit"""
        self.shuttingDown = True
        if self.tick: self.tick.cancel()
        if self.dut:  self.dut.Shutdown()
        if self.dacp:
            try:
                self.dacp.Pause()            
                self.dacp.speaker = 'My Computer'        
            except:
                pass
        if self.soft:
            self.soft.Shutdown()
        BASE.BaseTest.Cleanup( self )
        
    def __TickCb( self ):
        """Tick timer CB - monitor playback, detect boundary conditions"""
        try:
            info = self.dacp.nowPlaying
            self.log.Info( self.dacp.dev, info )        
        except:
            # DACP has thrown connection error
            self.dacp = None
        if not self.shuttingDown:        
            self.tick = LogThread.Timer( 1, self.__TickCb )
            self.tick.start()
        
    def __DurationCb( self ):
        """Duration timer CB - called to end test after specified time"""
        self.finished.set()
            
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
        