"""TestComplianceVolume - test compliance of volume service functionality

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check compliance of Volume service functionality
"""
import TestVolumeService  as BASE
import sys


class TestComplianceVolume( BASE.TestVolumeService ):
    """Test Volume service functionality compliance"""

    def __init__( self ):
        """Constructor - initialise base class"""
        BASE.TestVolumeService.__init__( self )
        self.doc = __doc__

    def Test( self, args ):
        """Check volume service functionality compliance"""
        if len( args )>1 and args[1].lower() == 'local':
            self.log.Abort( '', 'Require non-local player to test' )
        else:
            BASE.TestVolumeService.Test( self, args )

    def Cleanup( self ):
        """Perform post-test cleanup"""
        BASE.TestVolumeService.Cleanup( self )


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
