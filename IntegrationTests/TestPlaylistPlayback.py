#!/usr/bin/env python
"""TestPlaylistPlayback - test Playlist service state/transition basic operation

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - test mode 
              - all             for all configs sequentially
              - <num>           for config number <num> 
              - [min:max]       for range of (numbered) configs
              - [<n1>,<n2>...]  list of configs
              - <stim>          for stimulus (Play, Pause, Stop,
                                    SeekSecondsAbsolute, SeekSecondsRelative,
                                    SeekIndex, Next, Previous)
              - <pre-state>     for precon state (Stopped, Playing, Paused)
    arg#3 - random number generator seed (0 for 'random')
            by passing this, test scenarious containing random data can be
            replicated - the seed used is logged at the start of execution
            
Tests state-transition operation of DS service. Each transition is tested as a
standalone operation - no aggregation of actions due to async operation tested.
"""
import _Paths
import CommonPlaylistPlayback as BASE
import sys


class TestPlaylistPlayback( BASE.CommonPlaylistPlayback ):

    def __init__( self ):
        BASE.CommonPlaylistPlayback.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
