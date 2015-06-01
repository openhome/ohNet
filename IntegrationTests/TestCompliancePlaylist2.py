"""TestCompliancePlaylist2 - test compliance of playlist modes

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check functionality of playback modes (repeat/shuffle)
"""
import TestPlaylistModes  as BASE
import sys


class TestCompliancePlaylist2( BASE.TestPlaylistModes ):
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
        # Where Shuffle is enabled, and seek is Previous, the outcome is
        # implementation specific hence for compliance testing there are
        # no testpoints with shuffle/previous
        #
        # Id   Setup  Track    Rpt   Shfl   Seek
        ( 1, 'before', '@m', 'off', 'off', 'next' ),
        ( 2, 'before', '@m', 'off', 'off', 'previous' ),
        ( 3, 'before', '@m',  'on', 'off', 'next' ),
        ( 4, 'before', '@m',  'on', 'off', 'previous' ),
    ]


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
