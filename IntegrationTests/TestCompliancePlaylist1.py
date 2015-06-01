"""TestCompliancePlaylist1 - test compliance of playlist controls

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check functionality of playback handling (insert/delete/seek)
"""
import TestPlaylistHandling  as BASE
import sys


class TestCompliancePlaylist1( BASE.TestPlaylistHandling ):
    """Test Playlist service handling (insert/delete/seek) compliance"""

    def __init__( self ):
        """Constructor - initialise base class"""
        BASE.TestPlaylistHandling.__init__( self )
        self.doc = __doc__

    def Test( self, args ):
        """Check playlist service insert/delete/seek compliance"""
        argList = []
        if len( args )>1:
            if args[1].lower() == 'local':
                self.log.Abort( '', 'Require non-local player to test' )
            else:
                argList = [args[0], args[1], 'all', 12345]
        BASE.TestPlaylistHandling.Test( self, argList )

    def Cleanup( self ):
        """Perform post-test cleanup"""
        BASE.TestPlaylistHandling.Cleanup( self )

    def _CheckStaticData( self ):
        """Check playlist 'static' info - N/A for compliance testing"""
        pass

    configTable = \
    [
        #   | Preconditions                                  | Stimulus                         | Outcome
        # Id| State     PlLen  Track   Secs     Rpt   Shfl   | Action             Param1 Param2 | State      PlLen     Rpt     Shfl    Track  Secs
        (201, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'DeleteAllTracks',     '',     '', 'Stopped',    '0',    '@R',    '@R',    '0',  '0'),
        (216, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'Delete'         , '@m+1', '@N-2', 'Stopped', '@N-1',    '@R',    '@R',   '@m',  '0'),
        (234, 'Stopped', '@N',   '@m',  '0',    '@R',    '@R', 'Insert'         ,    '0', '@m-1', 'Stopped', '@N+1',    '@R',    '@R', '@m+1',  '0'),

        (301, 'Playing', '@N',   '@m', '@T',    '@R',    '@R', 'DeleteAllTracks',     '',     '', 'Stopped',    '0',    '@R',    '@R',    '0',  '0'),
        (315, 'Playing', '@N',   '@m', '@T',    '@R', 'false', 'Delete'         ,   '@m',   '@m', 'Playing', '@N-1',    '@R',    '@R',   '@m',  '0'),
        (334, 'Playing', '@N',   '@m', '@T',    '@R', 'false', 'Insert'         ,    '0', '@m-1', 'Playing', '@N+1',    '@R',    '@R', '@m+1', '@T'),

        (401, 'Paused' , '@N',   '@m', '@T',    '@R',    '@R', 'DeleteAllTracks',     '',     '', 'Stopped',    '0',    '@R',    '@R',    '0',  '0'),
        (414, 'Paused' , '@N',   '@m', '@T',    '@R', 'false', 'Delete'         ,    '1', '@m-1', 'Paused' , '@N-1',    '@R',    '@R', '@m-1', '@T'),
        (436, 'Paused' , '@N',   '@m', '@T',    '@R', 'false', 'Insert'         , '@N-1', '@N-1', 'Paused' , '@N+1',    '@R',    '@R',   '@m', '@T'),
    ]


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
