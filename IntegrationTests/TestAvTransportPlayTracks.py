#!/usr/bin/env python
"""TestAvTransporttPlayTracks - test Playing of playlists of tracks using AVTransport.

Parameters:
    arg#1 - AVT Renderer/Sender (UPnP AV Name) ['local' for internal SoftPlayer on loopback]
    arg#2 - Receiver ['local' for internal SoftPlayer on loopback] - optional (None = not present)
    arg#3 - Media server to source media from (None->test served audio)
    arg#4 - Playlist name (None/Full/Short->test served audio [defaults to full])
    arg#5 - Time to play before skipping to next (None = play all)
    arg#6 - Test loops (optional - default 1)
    arg#7 - Set False to prevent use of loopback adapter for local SoftPlayers (optional - default True)

Test test which plays tracks from an M3U playlist sequentially under AVTransport
control (test is acting like an AVT control point). The tracks may be played for
their entirety or any specified length of time
"""
import _Paths
import CommonAvTransportPlayTracks as BASE
import sys


class TestAvTransportPlayTracks( BASE.CommonAvTransportPlayTracks ):

    def __init__( self ):
        BASE.CommonAvTransportPlayTracks.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
