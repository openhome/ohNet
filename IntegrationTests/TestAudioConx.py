#!/usr/bin/env python
"""TestAudioConx - test for low(ish) level functionality on connection to the
               audio server. Uses a 'test' server to force responses.

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - Tests to execute
                - all         -> all tests
                - get         -> standard (non-partial) get response
                - error       -> HTTP error(s) from server
                - accept      -> server accept/not accepting request
                - respond     -> server responding/not responding
                - buff-invoke -> invoke whilst buffering
                - close       -> server close conx
    arg#3 - <optional> param for test
                - errCode for error (blank for all)
                - loops for respond
                - invoke for buff-invoke (blank for all)
               
This is a collection of discrete tests using a 'test' audio server which can
simulate normal and error conditions from the server
"""
import _Paths
import CommonAudioConx as BASE
import sys


class TestAudioConx( BASE.CommonAudioConx ):

    def __init__( self ):
        BASE.CommonAudioConx.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
