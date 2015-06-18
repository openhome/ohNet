"""TestComplianceProduct - test compliance of Product service functionality

Parameters:
    arg#1 - Player to test (UPnP friendly name)

Check compliance of Product service functionality (source manipulation)
"""
import TestSourceSelect as BASE
import sys


class TestComplianceProduct( BASE.TestSourceSelect ):
    """Test Product service functionality compliance"""

    def __init__( self ):
        """Constructor - initialise base class"""
        BASE.TestSourceSelect.__init__( self )
        self.doc = __doc__

    def Test( self, args ):
        """Check product service functionality compliance"""
        if len( args )>1 and args[1].lower() == 'local':
            self.log.Abort( '', 'Require non-local player to test' )
        else:
            BASE.TestSourceSelect.Test( self, args )

    def Cleanup( self ):
        """Perform post-test cleanup"""
        BASE.TestSourceSelect.Cleanup( self )


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
