"""TestComplianceProduct - test compliance of Product service functionality

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check compliance of Product service functionality (source manipulation)
"""
import _Paths
import CommonComplianceProduct as BASE
import sys


class TestComplianceProduct( BASE.CommonComplianceProduct ):

    def __init__( self ):
        BASE.CommonComplianceProduct.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
