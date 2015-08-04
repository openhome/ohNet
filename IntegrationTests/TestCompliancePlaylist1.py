"""TestCompliancePlaylist1 - test compliance of playlist controls

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check functionality of playback handling (insert/delete/seek)
"""
import _Paths
import CommonCompliancePlaylist1 as BASE
import sys


class TestCompliancePlaylist1( BASE.CommonCompliancePlaylist1 ):

    def __init__( self ):
        BASE.CommonCompliancePlaylist1.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
