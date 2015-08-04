"""TestCompliancePlaylist2 - test compliance of playlist modes

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check functionality of playback modes (repeat/shuffle)
"""
import _Paths
import CommonCompliancePlaylist2 as BASE
import sys


class TestCompliancePlaylist2( BASE.CommonCompliancePlaylist2 ):

    def __init__( self ):
        BASE.CommonCompliancePlaylist2.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
