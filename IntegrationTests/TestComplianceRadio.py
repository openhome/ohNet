"""TestComplianceRadio - test compliance of radio service functionality

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check compliance of Volume service functionality
"""
import _Paths
import CommonComplianceRadio as BASE
import sys


class TestComplianceRadio( BASE.CommonComplianceRadio ):

    def __init__( self ):
        BASE.CommonComplianceRadio.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
