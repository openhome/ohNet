#!/usr/bin/env python
"""TestUpnpMsPlayTracks - test Playing of UPnP Media Server served tracks.

Parameters:
    arg#1 - Sender DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - Receiver DUT ['local' for internal SoftPlayer on loopback] (None->not present)
    arg#3 - Time to play before skipping to next (None = play all)
    arg#4 - Repeat mode [on/off]
    arg#5 - Shuffle mode [on/off]
    arg#6 - Media server to source media from
    arg#7 - Playlist name

Test test which plays UPnP Media Server served tracks from a playlist sequentially. The
tracks may be played for their entirety or any specified length of time. Repeat and shuffle
modes may be selected
"""

import _FunctionalTest
import _BasePlayTracks                as BASE
import Upnp.ControlPoints.MediaServer as Server
import sys


class TestUpnpMsPlayTracks( BASE.BasePlayTracks ):
    """Test playing of UPnP Media Server served tracks"""

    def __init__( self ):
        """Constructor - initialise base class"""
        BASE.BasePlayTracks.__init__( self )
        self.doc = __doc__

    def Test( self, args ):
        """Check playback of locally served tracks"""
        serverName   = ''
        playlistName = ''
        try:
            serverName   = args[6]
            playlistName = args[7]
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )

        server = Server.MediaServer( serverName )
        if not server.device:
            log.Abort( serverName, 'Not available' )
        self.tracks = server.GetPlaylist( playlistName )
        server.Shutdown()

        BASE.BasePlayTracks.Test( self, args[:6] )

    def Cleanup( self ):
        """Perform post-test cleanup"""
        self.trackChangeMutex.acquire()     # prevent races during shutdown
        BASE.BasePlayTracks.Cleanup( self )

            
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
    