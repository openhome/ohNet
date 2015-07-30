#!/usr/bin/env python
"""TestAvTransportService - test AvTransport service

Parameters:
    arg#1 - MediaRenderer DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - before state to test from (use ALL for all states)
            
This performs the state-transition tests on a DUT as controlled by the UPnP
AvTransport service (as it relates to audio-digital-source). The state 
transition table including all end-cases is specified as data blocks within this
file.

NOTE/ all data used in this test should be valid for the scenario being tested.
      Invalid, out-of-range and otherwise erroneous data is covered by the
      service's unit testing.
"""
import _Paths
import CommonAvTransportService as BASE
import sys


class TestAvTransportService( BASE.CommonAvTransportService ):

    def __init__( self ):
        BASE.CommonAvTransportService.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
