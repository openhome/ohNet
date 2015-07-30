#!/usr/bin/env python
"""TestLocalDropout - test for dropout from locally served tracks.

Parameters:
    arg#1 - Sender DUT
    arg#2 - Receiver/Repeater DUT (None = not present)
    arg#3 - Receiver/SlaveDUT  (None = not present)
    arg#4 - Test duration (secs) or 'forever'
    arg#5 - Songcast sender mode (unicast/multicast)
    Use 'local' for internal SoftPlayer on loopback for DUTs

Verifies locally served audio played by the DUT does not suffer from audio dropout.
Additionally checks for dropout on downstream songcast receiver(s)
"""
import _Paths
import CommonLocalDropout as BASE
import sys


class TestLocalDropout( BASE.CommonLocalDropout ):

    def __init__( self ):
        BASE.CommonLocalDropout.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
