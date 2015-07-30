"""TestVolumeService - test volume service functionality

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]

Check operations of Volume service functionality
"""
import _Paths
import CommonVolumeService as BASE
import sys


class TestVolumeService( BASE.CommonVolumeService ):

    def __init__( self ):
        BASE.CommonVolumeService.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
