#!/usr/bin/env python
"""TestAirplayFunctions - test Net Aux source functionality.
 
Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer (NOT on loopback)]

NOTES
    - allow delay after setting DACP speaker (or iTunes (ver >= 11) may hang)
            
This verifies output by the DUT using Net Aux decode is correct, and Net Aux 
source handling operates correctly.
""" 
import _Paths
import CommonAirplayFunctions as BASE
import sys


class TestAirplayFunctions( BASE.CommonAirplayFunctions ):

    def __init__( self ):
        BASE.CommonAirplayFunctions.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
