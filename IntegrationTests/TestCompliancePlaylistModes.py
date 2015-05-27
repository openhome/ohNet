"""TestCompliancePlaylistModes - test compliance of playlist service modes

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check functionality of playback modes (repeat/shuffle)
"""
import TestPlaylistModes  as BASE
import sys


class TestCompliancePlaylistModes( BASE.TestPlaylistModes ):
    """Test Playlist service modes (repeat/shuffle) compliance"""

    def __init__( self ):
        """Constructor - initialise base class"""
        BASE.TestPlaylistModes.__init__( self )
        self.doc = __doc__

    def Test( self, args ):
        """Check playlist repeat/shuffle/next/prev compliance"""
        argList = []
        if len( args )>1:
            if args[1].lower() == 'local':
                self.log.Abort( '', 'Require non-local player to test' )
            else:
                argList = [args[0], args[1], 'all', 12345]
        BASE.TestPlaylistModes.Test( self, argList )

    def Cleanup( self ):
        """Perform post-test cleanup"""
        BASE.TestPlaylistModes.Cleanup( self )

    configTable = \
    [
        # 'Setup' is the setup order -> Playlist BEFORE/AFTER modes
        # 'Track' is the start track for the test
        # 'Seek'  is the seek direction for navgating playback
        #
        # Macros:    @N: last track in list
        #            @m: 1 <= track < last track
        #            -:  don't seek specific track, just Play()
        #
        # Id    Setup  Track    Rpt   Shfl   Seek
        ( 20, 'before', '@m', 'off', 'off', 'next' ),
        ( 23, 'before', '@m', 'off',  'on', 'previous' ),
        ( 24, 'before', '@m',  'on', 'off', 'next' ),
        ( 27, 'before', '@m',  'on',  'on', 'previous' ),
    ]


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
