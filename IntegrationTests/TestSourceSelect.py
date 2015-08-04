#!/usr/bin/env python
"""TestSourceSelect - check Source selection (part of Product service)

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]

Cut-down version of Volkano1 source tests with purely software checks
on only the OpenHome sources (no UPnP AV sources)
"""
import _Paths
import CommonSourceSelect as BASE
import sys


class TestSourceSelect( BASE.CommonSourceSelect ):

    def __init__( self ):
        BASE.CommonSourceSelect.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
