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
import time


class TestAirplayFunctions( BASE.CommonAirplayFunctions ):

    def __init__( self ):
        BASE.CommonAirplayFunctions.__init__( self )
        self.doc = __doc__

    # Dummy the measurement methods for use with SoftPlayers
    # Merely check playback continues error free for a few secs

    # noinspection PyUnusedLocal
    def _DoCheckFreq( self, aTitle ):
        self._MonitorPlayback( 5 )

    # noinspection PyUnusedLocal
    def _DoCheckVolume( self, aVol ):
        self._MonitorPlayback( 5 )

    def _MonitorPlayback( self, aSecs ):
        """Check AirPlay playback over specified period"""
        for i in range( aSecs ):
            time.sleep( 1 )
            info = self.dacp.nowPlaying
            self.log.Info( self.dacp.dev, info )


if __name__ == '__main__':

    BASE.Run( sys.argv )
