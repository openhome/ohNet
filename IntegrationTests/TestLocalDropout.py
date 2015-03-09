#!/usr/bin/env python
"""TestLocalDropout - test for dropout from locally served tracks.

Parameters:
    arg#1 - Sender DUT
    arg#2 - Receiver/Repeater DUT (None = not present)
    arg#3 - Receiver/SlaveDUT  (None = not present)
    arg#4 - Test duration (secs) or 'forever'
    arg#5 - Songcast sender mode (unicast/multicast)
    Use 'local' for internal SoftPlayer on loopback for DUTs

Verifies locally served audio played by the DUT does not suffer from audio dropout.
Additionally checks for dropout on downstream songcast receiver(s)
"""

import _FunctionalTest
import _BaseDropout             as BASE
import Utils.Common             as Common
import Utils.Network.HttpServer as HttpServer
import os
import sys

kAudioRoot = os.path.join( _FunctionalTest.audioDir, 'LRTones/' )
kTrackList = os.path.join( kAudioRoot, 'TrackList.xml' )


class TestLocalDropout( BASE.BaseDropout ):
    """Test dropout on locally served tracks"""

    def __init__( self ):
        """Constructor - initialise base class"""
        BASE.BaseDropout.__init__( self )
        self.doc = __doc__
        self.server = None

    def Test( self, args ):
        """Test dropout on locally served tracks"""
        self.server = HttpServer.HttpServer( kAudioRoot )
        self.server.Start()
        self.tracks = Common.GetTracks( kTrackList, self.server )
        BASE.BaseDropout.Test( self, args )

    def Cleanup( self ):
        """Perform post-test cleanup"""
        BASE.BaseDropout.Cleanup( self )
        if self.server:
            self.server.Shutdown()

            
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
    