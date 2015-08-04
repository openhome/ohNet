#!/usr/bin/env python
"""SongcastPlayback - test Songcast functionality (Sender/Receiver/Zpus)

Parameters:
    arg#1 - DUT #1 ['local' for internal SoftPlayer)
    arg#2 - DUT #2 ['local' for internal SoftPlayer)
    arg#3 - DUT #3 ['local' for internal SoftPlayer)
    arg#4 - test mode 
              - all          for all configs sequentially
              - random       for all configs randomly
              - <num>        for config number <num>
              - [min:max]    for range of (numbered) configs
    arg#5 - random number generator seed (0 for 'random')
            by passing this, test scenarious containing random data can be
            replicated - the seed used is logged at the start of execution
    arg#6 - sender mode [unicast/multicast/none] - (optional - default unicast)
            'none' means no change to current DUT(s) sender mode(s)
           
Loopback is used only when ALL DUTs are 'local'
Tests the sender and receiver services, and operation of zpus routing. Ensures
status and actions operate as specified
"""
import _Paths
import CommonSongcastPlayback as BASE
import sys


class TestSongcastPlayback( BASE.CommonSongcastPlayback ):

    def __init__( self ):
        BASE.CommonSongcastPlayback.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
