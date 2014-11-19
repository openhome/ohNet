#!/usr/bin/env python
"""TestLocalPlayTracks - test Playing of locally served tracks.

Parameters:
    arg#1 - Sender DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - Receiver DUT ['local' for internal SoftPlayer on loopback] (None->not present)
    arg#3 - Time to play before skipping to next (None = play all)
    arg#4 - Repeat mode [on/off]
    arg#5 - Shuffle mode [on/off]

Test test which plays locally served tracks from a playlist sequentially. The tracks
may be played for their entirety or any specified length of time. Repeat and shuffle
modes may be selected
"""

import _FunctionalTest
import _BasePlayTracks          as BASE
import Utils.Common             as Common
import Utils.Network.HttpServer as HttpServer
import os
import sys

kAudioRoot = os.path.join( _FunctionalTest.audioDir, 'LRTones/' )
kTrackList = os.path.join( kAudioRoot, 'TrackList.xml' )


class TestLocalPlayTracks( BASE.BasePlayTracks ):
    """Test playing of locally served tracks"""

    def __init__( self ):
        """Constructor - initialise base class"""
        BASE.BasePlayTracks.__init__( self )
        self.doc = __doc__
        self.server = None

    def Test( self, args ):
        """Check playback of locally served tracks"""
        self.server = HttpServer.HttpServer( kAudioRoot )
        self.server.Start()
        self.tracks = Common.GetTracks( kTrackList, self.server )
        BASE.BasePlayTracks.Test( self, args )

    def Cleanup( self ):
        """Perform post-test cleanup"""
        if self.server:
            self.server.Shutdown()
        BASE.BasePlayTracks.Cleanup( self )

            
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
    