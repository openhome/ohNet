#!/usr/bin/env python
"""TestTransportService - test Transport service attributes and actions

Parameters:
    arg#1 - Device Under Test
"""
import _Paths
import CommonTransportService as BASE
import sys


class TestTransportService( BASE.CommonTransportService ):

    def __init__( self ):
        BASE.CommonTransportService.__init__( self )
        self.doc          = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
