#!/usr/bin/env python
"""TestLocalPlayTracks - test Playing of locally served tracks.

Parameters:
    arg#1 - Sender DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - Receiver DUT ['local' for internal SoftPlayer on loopback] (None->not present)
    arg#3 - Time to play before skipping to next (None = play all)
    arg#4 - Repeat mode [on/off]
    arg#5 - Shuffle mode [on/off]
    arg#6 - [optional] set to 'short' for short track list, 'hls' for HLS track list

Test test which plays locally served tracks from a playlist sequentially. The tracks
may be played for their entirety or any specified length of time. Repeat and shuffle
modes may be selected
"""
import _Paths
import CommonLocalPlayTracks as BASE
import sys


class TestLocalPlayTracks( BASE.CommonLocalPlayTracks ):

    def __init__( self ):
        BASE.CommonLocalPlayTracks.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
