"""TestComplianceReceiver - test compliance of receiver service functionality

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check compliance of Receiver service functionality
"""
import _Paths
import CommonComplianceReceiver as BASE
import sys


class TestComplianceReceiver( BASE.CommonComplianceReceiver ):

    def __init__( self ):
        BASE.CommonComplianceReceiver.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
