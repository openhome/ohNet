"""TestComplianceRadio - test compliance of radio service functionality

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check compliance of Volume service functionality
"""
import TestRadioService  as BASE
import sys


class TestComplianceRadio( BASE.TestRadioService ):
    """Test Radio service functionality compliance"""

    def __init__( self ):
        """Constructor - initialise base class"""
        BASE.TestRadioService.__init__( self )
        self.doc   = __doc__
        #self.users = ['linn-test-presets-1', 'linn-test-presets-2', 'linn-test-presets-3']
        self.users = ['linn-test-presets-1', 'klueso', 'linn-test-presets-3']

    def Test( self, args ):
        """Check radio service functionality compliance"""
        argList = []
        if len( args )>1:
            if args[1].lower() == 'local':
                self.log.Abort( '', 'Require non-local player to test' )
            else:
                argList = [args[0], args[1], 'all']
        BASE.TestRadioService.Test( self, argList )

    def Cleanup( self ):
        """Perform post-test cleanup"""
        BASE.TestRadioService.Cleanup( self )

    def TestFixedParams( self ):
        # impementation dependant -> disabled for compliance testing
        pass

    def TestUpdated( self ):
        # impementation dependant -> disabled for compliance testing
        pass


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
