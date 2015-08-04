#!/usr/bin/env python
"""TestRadioPlayChannels - test playback of Radio (using Radio service)

Parameters:
    arg#1 - DUT Sender ['local' for internal SoftPlayer on loopback]
    arg#2 - DUT Receiver ['local' for internal SoftPlayer on loopback] - optional (None = not present)
    arg#3 - Radiotime username
    arg#4 - Time to play before skipping to next channel (None = indefinite)
    arg#5 - Shuffle mode [on/off] (optional - default off)
    arg#6 - Test loops (optional - default 1)
"""
import _Paths
import CommonRadioPlayChannels as BASE
import sys


class TestRadioPlayChannels( BASE.CommonRadioPlayChannels ):

    def __init__( self ):
        BASE.CommonRadioPlayChannels.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
