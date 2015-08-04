#!/usr/bin/env python
"""TestStandbyCycleSoak - repeatedly cycle standby, make sure device starts up
   as expected

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - Number of test loops
    
"""
import _Paths
import CommonStandbyCycleSoak as BASE
import sys


class TestStandbyCycleSoak( BASE.CommonStandbyCycleSoak ):

    def __init__( self ):
        BASE.CommonStandbyCycleSoak.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
