"""TestComplianceSender - test compliance of sender service functionality

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check compliance of Sender service functionality
"""
import TestSongcastPlayback  as BASE
import sys


class TestComplianceSender( BASE.TestSongcastPlayback ):
    """Test Sender service functionality compliance"""

    def __init__( self ):
        """Constructor - initialise base class"""
        BASE.TestSongcastPlayback.__init__( self )
        self.doc = __doc__

    def Test( self, args ):
        """Check sender service functionality compliance"""

        argList = []
        if len( args )>1:
            if args[1].lower() == 'local':
                self.log.Abort( '', 'Require non-local player to test' )
            else:
                argList = [args[0], 'local', args[1], 'none', 'all', 12345, 'none']
        BASE.TestSongcastPlayback.Test( self, argList )

    def Cleanup( self ):
        """Perform post-test cleanup"""
        BASE.TestSongcastPlayback.Cleanup( self )

    # DS2 is sender (DUT) , DS1 is SoftPlayer

    configTable = \
    [
        # Id || Setup                                                                                     || Checks
        #    || DS4                  | DS3                  | DS2                  | DS1                  || DS3 Sender         | DS2 Sender          | DS2 Receiver           | DS1 Receiver
        #    || Source    | State    | Source    | State    | Source    | State    | Source    | State    || Status    | Audio  | Status    | Audio  | State    | Uri  | Meta | State    | Uri  | Meta
        ( 100,  ''        , ''       , ''        , ''       , ''        , 'Standby', 'DS2'     , 'Stopped',  ''        , ''     , 'Enabled' , 'False', ''       , ''   , ''   , 'Stopped', 'DS2', 'DS2' ),
        ( 101,  ''        , ''       , ''        , ''       , ''        , 'Standby', 'DS2'     , 'Playing',  ''        , ''     , 'Enabled' , 'False', ''       , ''   , ''   , 'Waiting', 'DS2', 'DS2' ),
        ( 102,  ''        , ''       , ''        , ''       , 'Playlist', 'Stopped', 'DS2'     , 'Stopped',  ''        , ''     , 'Enabled' , 'False', ''       , ''   , ''   , 'Stopped', 'DS2', 'DS2' ),
        ( 103,  ''        , ''       , ''        , ''       , 'Playlist', 'Playing', 'DS2'     , 'Stopped',  ''        , ''     , 'Enabled' , 'True' , ''       , ''   , ''   , 'Stopped', 'DS2', 'DS2' ),
        ( 104,  ''        , ''       , ''        , ''       , 'Playlist', 'Paused' , 'DS2'     , 'Stopped',  ''        , ''     , 'Enabled' , 'False', ''       , ''   , ''   , 'Stopped', 'DS2', 'DS2' ),
        ( 105,  ''        , ''       , ''        , ''       , 'Playlist', 'Stopped', 'DS2'     , 'Playing',  ''        , ''     , 'Enabled' , 'False', ''       , ''   , ''   , 'Waiting', 'DS2', 'DS2' ),
        ( 106,  ''        , ''       , ''        , ''       , 'Playlist', 'Playing', 'DS2'     , 'Playing',  ''        , ''     , 'Enabled' , 'True' , ''       , ''   , ''   , 'Playing', 'DS2', 'DS2' ),
        ( 107,  ''        , ''       , ''        , ''       , 'Playlist', 'Paused' , 'DS2'     , 'Playing',  ''        , ''     , 'Enabled' , 'False', ''       , ''   , ''   , 'Waiting', 'DS2', 'DS2' ),
    ]


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
