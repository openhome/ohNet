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
import _Paths
import CommonUpnpMsPlayTracks as BASE
import sys


class TestUpnpMsPlayTracks( BASE.CommonUpnpMsPlayTracks ):

    def __init__( self ):
        BASE.CommonUpnpMsPlayTracks.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
