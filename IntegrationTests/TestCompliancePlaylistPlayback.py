"""TestCompliancePlaylistPlayback - test compliance of playlist playback

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check functionality of playback state-transitions
"""
import TestPlaylistPlayback as BASE
import sys


class TestCompliancePlaylistPlayback( BASE.TestPlaylistPlayback ):
    """Test Playlist service stete-transitions"""

    def __init__( self ):
        """Constructor - initialise base class"""
        BASE.TestPlaylistPlayback.__init__( self )
        self.doc = __doc__

    def Test( self, args ):
        """Check Playlist service stete-transitions"""
        argList = []
        if len( args )>1:
            if args[1].lower() == 'local':
                self.log.Abort( '', 'Require non-local player to test' )
            else:
                argList = [args[0], args[1], 'all', 12345]
        BASE.TestPlaylistPlayback.Test( self, argList )

    def Cleanup( self ):
        """Perform post-test cleanup"""
        BASE.TestPlaylistPlayback.Cleanup( self )

    configTable = \
    [
        #   | Preconditions                       | Stimulus                                       | Outcome
        # Id| State     PlLen  Track   Secs   Rpt | Action                MinVal     MaxVal     Err| State      Track         Secs
        (201, 'Stopped', '@N',   '@m',  '0', 'off', 'Play'              ,        '',        '',   0, 'Playing',         '@m',     '0'),
        (211, 'Stopped', '@N',   '@m',  '0', 'off', 'Pause'             ,        '',        '',   0, 'Stopped',         '@m',     '0'),
        (221, 'Stopped', '@N',   '@m',  '0', 'off', 'Stop'              ,        '',        '',   0, 'Stopped',         '@m',     '0'),
        (232, 'Stopped', '@N',   '@m',  '0', 'off', 'SeekSecondAbsolute',       '0',       '0',   0, 'Playing',         '@m',     '0'),
        (244, 'Stopped', '@N',   '@m',  '0', 'off', 'SeekSecondRelative',       '1',        '',   0, 'Playing',         '@m',    '@y'),
        (255, 'Stopped', '@N',   '@m',  '0', 'off', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
        (296, 'Stopped', '@N',   '@m',  '0', 'off', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),

        (401, 'Playing', '@N',   '@m', '@T', 'off', 'Play'              ,        '',        '',   0, 'Playing',         '@m',     '0'),
        (411, 'Playing', '@N',   '@m', '@T', 'off', 'Pause'             ,        '',        '',   0, 'Paused' ,         '@m',    '@T'),
        (421, 'Playing', '@N',   '@m', '@T', 'off', 'Stop'              ,        '',        '',   0, 'Stopped',         '@m',     '0'),
        (436, 'Playing', '@N',   '@m', '@T', 'off', 'SeekSecondAbsolute',       '0',      '@T',   0, 'Playing',         '@m',    '@y'),
        (478, 'Playing', '@N',   '@m', '@T', 'off', 'SeekSecondRelative',        '','@D-@T-10',   0, 'Playing',         '@m', '@T+@y'),
        (535, 'Playing', '@N',   '@m', '@T', 'off', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
        (576, 'Playing', '@N',   '@m', '@T', 'off', 'SeekId'            ,      '@p',      '@p',   0, 'Playing',          '0',     '0'),

        (701, 'Paused' , '@N',   '@m', '@T', 'off', 'Play'              ,        '',        '',   0, 'Playing',         '@m',    '@T'),
        (711, 'Paused' , '@N',   '@m', '@T', 'off', 'Pause'             ,        '',        '',   0, 'Paused' ,         '@m',    '@T'),
        (721, 'Paused' , '@N',   '@m', '@T', 'off', 'Stop'              ,        '',        '',   0, 'Stopped',         '@m',     '0'),
        (736, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekSecondAbsolute',       '0',      '@T',   0, 'Playing',         '@m',    '@y'),
        (778, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekSecondRelative',        '','@D-@T-10',   0, 'Playing',         '@m', '@T+@y'),
        (835, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekIndex'         ,       '1',    '@N-2',   0, 'Playing',         '@x',     '0'),
        (875, 'Paused' , '@N',   '@m', '@T', 'off', 'SeekId'            ,       '1',    '@p-1', 800, 'Paused',          '@m',    '@T'),
    ]


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
