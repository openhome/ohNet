#!/usr/bin/env python
"""TestRadioService - test Radio service operations

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - test mode 
              - all       execute all tests
              - fixed     check reporting of fixed data
              - presets   check setup/reporting of preset channels and ID lists
              - manual    check setup/reporting of manually configured channels
              - updated   for update of Radiotime preset list

Suite of tests to check the operation of the Radio service. Checks all aspects
of this service EXCEPT actual playback of the radio channels (which is tested
in the TestRadioPlayback test script)
"""
import _Paths
import CommonRadioService as BASE
import _ProtocolInfo      as ProtocolInfo
import sys


class TestRadioService( BASE.CommonRadioService ):

    def __init__( self ):
        BASE.CommonRadioService.__init__( self )
        self.doc          = __doc__
        self.tuneInBrowse = 'Browse.ashx?c=presets&formats=aac,ogg,hls'
        self.protocolInfo = ProtocolInfo.kProtocolInfo


if __name__ == '__main__':

    BASE.Run( sys.argv )
