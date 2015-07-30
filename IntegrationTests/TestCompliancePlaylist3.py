"""TestCompliancePlaylist3 - test compliance of playlist playback

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check functionality of playback state-transitions
"""
import _Paths
import CommonCompliancePlaylist3 as BASE
import sys


class TestCompliancePlaylist3( BASE.CommonCompliancePlaylist3 ):

    def __init__( self ):
        BASE.CommonCompliancePlaylist3.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
