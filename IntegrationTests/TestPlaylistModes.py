#!/usr/bin/env python
"""Test PlaylistModes - test different playback mades (repeat/shuffle) combos
                       on playlists, checking playback order etc.
Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - test mode 
              - all          for all configs sequentially
              - <num>        for config number <num>
              - [min:max]    for range of (numbered) configs
    arg#3 - random number generator seed (0 for 'random')
            by passing this, test scenarious containing random data can be
            replicated - the seed used is logged at the start of execution
            
Tests playback order on randomly generated playlists in all the supported play
modes. Ensures play order is as expected.
"""
import _Paths
import CommonPlaylistModes as BASE
import sys


class TestPlaylistModes( BASE.CommonPlaylistModes ):

    def __init__( self ):
        BASE.CommonPlaylistModes.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
