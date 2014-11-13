#!/usr/bin/env python
"""TestTidalDropout - test for audio dropout in tidal playlists

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - Test duration (secs) or 'forever'
    arg#3 - Tidal username
    arg#4 - Tidal password
    
This verifies tidal audio output by the DUT does not suffer from audio dropout.
""" 

# Differences from DS test:
#    - cut-down variant - only monitors events, no monitoring of actual audio

import _FunctionalTest
import BaseTest                       as BASE
import Upnp.ControlPoints.Volkano     as Volkano
import _SoftPlayer                    as SoftPlayer
import LogThread
import os
import sys
import threading
import time

kTidalTracks = [
    ('tidal://track?version=1&trackId=21691876', ''),   # Lonely Are The Brave / Doogie White + La Paz
    ('tidal://track?version=1&trackId=25319855', ''),   # Do It Again / Life On Standby
    ('tidal://track?version=1&trackId=17719348', ''),   # Good Days / Marmozets
    ('tidal://track?version=1&trackId=31924747', ''),   # Black Smoke / Blues Pills
    ('tidal://track?version=1&trackId=25347004', ''),   # Boo Hoo Hoo / No Sinner
    ('tidal://track?version=1&trackId=24392381', ''),   # Fade Into You / Leslie West
    ('tidal://track?version=1&trackId=20751430', ''),   # Mother Mary / Quireboys
    ('tidal://track?version=1&trackId=18233701', ''),   # Just A Ride / Virginmarys
    ('tidal://track?version=1&trackId=18457099', ''),   # Kiss Tried To Kill Me / Black Spiders
    ('tidal://track?version=1&trackId=31214177', ''),   # Bring Down The City / Massive
    ('tidal://track?version=1&trackId=25481067', ''),   # I Bleed Rock n Roll / Treatment
    ('tidal://track?version=1&trackId=33093661', ''),   # Road Less Travelled / Answer
    ('tidal://track?version=1&trackId=30554888', ''),   # Chimpanzee Twist / Tijuana Bibles
    ('tidal://track?version=1&trackId=24155300', ''),   # Valley Of The Dolls / Uncle Acid + The Deadbeats
    ('tidal://track?version=1&trackId=19992548', ''),   # Your Way / Voodoo Six
    ('tidal://track?version=1&trackId=2717446', ''),    # Princess and the Frog / Jim Jones Revue
    ('tidal://track?version=1&trackId=16909477', ''),   # Rough Cut / Bonafide
    ('tidal://track?version=1&trackId=36301141', ''),   # Better Days / Gun
    ('tidal://track?version=1&trackId=9066215', ''),    # One Bullet / Thunder
    ('tidal://track?version=1&trackId=18440593', '')]   # When I Get Down / Logan


class TestTidalDropout( BASE.BaseTest ):
    """Class to check for dropout in audio output"""
    
    def __init__( self ):
        """Constructor for AudioDropout test"""
        self.dut          = None
        self.dutDev       = None
        self.soft         = None
        self.monitor      = False
        self.exitTimer    = None
        self.playing      = threading.Event()
        self.durationDone = threading.Event()
        BASE.BaseTest.__init__( self )

    def Test( self, args ):
        """Audio Dropout test"""
        dutName   = ''
        tidalUser = ''
        tidalPwd  = ''
        duration  = 0
        loopback  = False

        # parse command line arguments
        try:
            dutName   = args[1]
            duration  = args[2].lower()
            tidalUser = args[3]
            tidalPwd  = args[4]
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )

        if duration != 'forever':
            duration = int( duration )

        # create and configure DUT
        if dutName.lower() == 'local':
            loopback = True
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev', aLoopback=loopback, aTidalUser=tidalUser, aTidalPwd=tidalPwd )
            dutName = self.soft.name
        self.dutDev = dutName.split( ':' )[0]
        self.dut = Volkano.VolkanoDevice( dutName, aIsDut=True, aLoopback=loopback )
        self.dut.playlist.AddSubscriber( self._PlaylistCb )

        # load DUT's tidal playlist and start playback
        self.dut.playlist.repeat = 'on'
        self.dut.playlist.shuffle = 'on'
        self.dut.playlist.DeleteAllTracks()
        self.dut.playlist.AddPlaylist( kTidalTracks )
        self.dut.playlist.Play()
        self.playing.wait( 10 )
        if self.dut.playlist.transportState != 'Playing':
            self.log.Abort( self.senderDev, 'Failed to start playback' )

        # Monitor events until timer expired / forever
        self.monitor = True
        self.durationDone.clear()
        if duration != 'forever':
            self.exitTimer = LogThread.Timer( duration, self._DurationCb )
            self.exitTimer.start()
        self.durationDone.wait()

    def Cleanup( self ):
        """Perform cleanup on test exit"""
        if self.dut:
            self.dut.playlist.RemoveSubscriber( self._PlaylistCb )
            self.dut.playlist.Stop()
            self.dut.Shutdown()
        if self.soft:
            self.soft.Shutdown()
        BASE.BaseTest.Cleanup( self )

    # noinspection PyUnusedLocal
    def _PlaylistCb( self, service, svName, svVal, svSeq ):
        """Callback from Playlist service"""
        if svName == 'TransportState':
            if svVal == 'Playing':
                self.playing.set()
            else:
                if self.monitor:
                    self.log.Fail( self.dutDev, "Dropout detected -> state is %s" % svVal )

    def _DurationCb( self ):
        """Callback from duration timer"""
        self.durationDone.set()

            
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
        