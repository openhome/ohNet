#!/usr/bin/env python
"""TestRenderingControlService - test UPnP AV RenderingControl service

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
            
Check UPnP AV RenderingControl (Volume) service
"""
import _Paths
import CommonRenderingControlService as BASE
import sys


class TestRenderingControlService( BASE.CommonRenderingControlService ):

    def __init__( self ):
        BASE.CommonRenderingControlService.__init__( self )
        self.doc = __doc__


if __name__ == '__main__':

    BASE.Run( sys.argv )
