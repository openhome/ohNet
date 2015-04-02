#!/usr/bin/env python
"""TestPlaylistAddDel - test Add/Del of playlist.

Parameters:
    arg#1 - UPnP DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - UPnP media server to source media from
    arg#3 - Playlist name
    arg#4 - Loops of add/del
    
This is a stress test for the pipeline    
"""
import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.OhMediaPlayer as OHMP
import Upnp.ControlPoints.MediaServer   as Server
import _SoftPlayer                      as SoftPlayer
import sys
import threading
import time


class TestPlaylistAddDelSoak( BASE.BaseTest ):
    """Test playlist add/delete"""

    def __init__( self ):
        """ Constructor - initialise base class"""
        BASE.BaseTest.__init__( self )
        self.dut            = None
        self.server         = None
        self.soft           = None
        self.codecEvt       = threading.Event()

    def Test( self, args ):
        dutName      = None
        serverName   = None
        playlistName = None
        loops        = 0
        loopback     = False

        try:
            dutName      = args[1]
            serverName   = args[2]
            playlistName = args[3]
            loops        = int( args[4] )
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )

        # get playlist from server
        self.server = Server.MediaServer( serverName )
        if not self.server.device:
            self.log.Abort( serverName, 'Not available' )
        playlist = self.server.GetPlaylist( playlistName )
        self.server.Shutdown()
        self.server = None
        
        # start local softplayer(s) as required
        if dutName.lower() == 'local':
            loopback = True
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev', aLoopback=loopback )
            dutName = self.soft.name
        
        # create renderer add subscribe to events
        self.dut = OHMP.OhMediaPlayerDevice( dutName, aIsDut=True, aLoopback=loopback )
        self.dut.info.AddSubscriber( self._InfoEventCb )

        # Repeatedly Add / Remove playlist
        for i in range( loops ):
            self.log.Info( '' )
            self.log.Info( '', 'Loop %d of %d' % (i+1, loops) )
            self.log.Info( '' )
            
            self.codecEvt.clear()
            self.dut.playlist.DeleteAllTracks()
            if i>0:
                self.codecEvt.wait( 3 )
            
            self.codecEvt.clear()
            self.dut.playlist.AddPlaylist( playlist )
            self.dut.playlist.SeekIndex( 0 )
            if i>0:
                self.codecEvt.wait( 3 )

    def Cleanup( self ):
        """Perform post-test cleanup"""
        if self.server:
            self.server.Shutdown()
        if self.dut: 
            self.dut.Shutdown()
        if self.soft:
            self.soft.Shutdown()
        BASE.BaseTest.Cleanup( self )

    # noinspection PyUnusedLocal
    def _InfoEventCb( self, service, svName, svVal, svSeq ):
        """Callback from Info Service UPnP events"""
        if svName == 'CodecName':
            self.codecEvt.set()
                
        
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
    