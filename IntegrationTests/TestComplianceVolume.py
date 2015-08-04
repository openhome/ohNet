"""TestComplianceVolume - test compliance of volume service functionality

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check compliance of Volume service functionality
"""
import _Paths
import CommonComplianceVolume as BASE
import sys


class TestComplianceVolume( BASE.CommonComplianceVolume ):

    def __init__( self ):
        BASE.CommonComplianceVolume.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
