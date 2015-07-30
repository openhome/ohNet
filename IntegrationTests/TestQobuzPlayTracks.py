#!/usr/bin/env python
"""TestQobuzPlayTracks - test Playing of Qobuz served tracks.

Parameters:
    arg#1 - Sender DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - Receiver DUT ['local' for internal SoftPlayer on loopback] (None->not present)
    arg#3 - Time to play before skipping to next (None = play all)
    arg#4 - Repeat mode [on/off]
    arg#5 - Shuffle mode [on/off]
    arg#6 - Number of tracks to test with (use 0 for fixed list of 20 hard-coded tracks)
    arg#7 - Qobuz ID:Secret
    arg#8 - Qobuz username
    arg#9 - Qobuz password

Test test which plays Qobuz served tracks from a playlist sequentially. The tracks
may be played for their entirety or any specified length of time. Repeat and shuffle
modes may be selected
"""
import _Paths
import CommonQobuzPlayTracks as BASE
import sys


class TestQobuzPlayTracks( BASE.CommonQobuzPlayTracks ):

    def __init__( self ):
        BASE.CommonQobuzPlayTracks.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
