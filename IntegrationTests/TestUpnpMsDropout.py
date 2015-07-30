#!/usr/bin/env python
"""TestUpnpMsDropout - test for dropout from UPnP media server served tracks.

Parameters:
    arg#1 - Sender DUT
    arg#2 - Receiver/Repeater DUT (None = not present)
    arg#3 - Receiver/SlaveDUT  (None = not present)
    arg#4 - Test duration (secs) or 'forever'
    arg#5 - songcast sender mode (unicast/multicast)
    arg#6 - Media server to source media from
    arg#7 - Playlist name

    Use 'local' for internal SoftPlayer on loopback for DUTs

Verifies UPnP media server served audio played by the DUT does not suffer from audio dropout.
Additionally checks for dropout on downstream songcast receiver(s)
"""
import _Paths
import CommonUpnpMsDropout as BASE
import sys


class TestUpnpMsDropout( BASE.CommonUpnpMsDropout ):

    def __init__( self ):
        BASE.CommonUpnpMsDropout.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
