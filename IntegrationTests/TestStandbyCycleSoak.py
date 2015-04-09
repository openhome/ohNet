#!/usr/bin/env python
"""TestStandbyCycleSoak - repeatedly cycle standby, make sure device starts up
   as expected

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - Number of test loops
    
"""

# Differences from DS test:
#    - removed Autoplay setup (part of Config service)
#    - removed Startup Source setup (part of Config service)
#    - removed Exakt checking (no Exakt in MediaPlayer)
#    - remove on-device crash data monitoring (as N/A)


import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.OhMediaPlayer as OHMP
import _SoftPlayer                      as SoftPlayer
import os
import sys
import time


class TestStandbyCycleSoak( BASE.BaseTest ):
    """Repeatedly cycle standby on device, check that it comes up OK"""
    
    def __init__( self ):
        """Constructor"""
        BASE.BaseTest.__init__( self )
        self.dut  = None
        self.soft = None

    def Test( self, args ):
        """Repeated reboots test"""
        dutName  = ''
        loops    = 1
        loopback = False

        try:
            dutName = args[1]
            loops   = int( args[2] )
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )

        if dutName.lower() == 'local':
            loopback = True
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev', aLoopback=loopback )
            dutName = self.soft.name
            
        self.dut = OHMP.OhMediaPlayerDevice( dutName, aIsDut=True, aLoopback=loopback )
        for loop in range( loops ):
            self.log.Info( '' )
            self.log.Info( '', 'Loop %d of %d' % (loop+1, loops) )
            self.log.Info( '' )
            self.dut.product.CycleStandby()
            time.sleep( 15 )
                    
    def Cleanup( self ):
        """Perform cleanup on test exit"""
        if self.dut:
            self.dut.Shutdown()
        if self.soft:
            self.soft.Shutdown()
        BASE.BaseTest.Cleanup( self )                


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
        
