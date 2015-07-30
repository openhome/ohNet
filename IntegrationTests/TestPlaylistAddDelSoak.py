#!/usr/bin/env python
"""TestPlaylistAddDel - test Add/Del of playlist.

Parameters:
    arg#1 - UPnP DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - UPnP media server to source media from
    arg#3 - Playlist name
    arg#4 - Loops of add/del
    
This is a stress test for the pipeline    
"""
import _Paths
import CommonPlaylistAddDelSoak as BASE
import sys


class TestPlaylistAddDelSoak( BASE.CommonPlaylistAddDelSoak ):

    def __init__( self ):
        BASE.CommonPlaylistAddDelSoak.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
