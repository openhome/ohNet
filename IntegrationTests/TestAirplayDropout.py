#!/usr/bin/env python
"""TestAirplayDropout - test for audio dropout on Net Aux source using AirPlay

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer]
    arg#2 - Test duration (secs) or 'forever'
    
Verifies AirPlay audio output by the DUT does not suffer from audio dropout
""" 
import _Paths
import CommonAirplayDropout as BASE
import sys


class TestAirplayDropout( BASE.CommonAirplayDropout ):

    def __init__( self ):
        """Constructor for Airplay Dropout test"""
        BASE.CommonAirplayDropout.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
        