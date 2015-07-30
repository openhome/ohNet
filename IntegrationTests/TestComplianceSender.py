"""TestComplianceSender - test compliance of sender service functionality

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check compliance of Sender service functionality
"""
import _Paths
import CommonComplianceSender as BASE
import sys


class TestComplianceSender( BASE.CommonComplianceSender ):

    def __init__( self ):
        BASE.CommonComplianceSender.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
