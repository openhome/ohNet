#!/usr/bin/env python
"""TestComplianceDevice - ohMediaServer device compliance test

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Test to ensure device complies with ohMediaPlayer standard. Basically attempts to ensure
that all services, actions and attributes are present and respond as defined by the
ohMediaPlayer 'standard'. Does NOT verify actual functionality - this is checked (in a
basic form) in the service compliance tests.
"""
import _Paths
import CommonComplianceDevice as BASE
import sys


class TestComplianceDevice( BASE.CommonComplianceDevice ):

    def __init__( self ):
        BASE.CommonComplianceDevice.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
