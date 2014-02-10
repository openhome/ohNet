"""TestVolumeControl - test volume control functionality

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer]

Check operations of Volume control functions
"""

# Severely cut-down variant of DS test.
# Only checks operation of volume service at commands level  

import _FunctionalTest
import BaseTest                        as BASE
import Upnp.ControlPoints.Volkano      as Volkano
import _SoftPlayer                as SoftPlayer
import os
import sys


class TestVolumeControl( BASE.BaseTest ):

    def __init__( self ):
        "Constructor - initalise base class"
        BASE.BaseTest.__init__( self )
        self.dut  = None
        self.soft = None
        
    def Test( self, args ):
        "Tests for volume functionality"
        try:
            dutName   = args[1]
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )
            
        # Create and initialise DUT
        if dutName.lower() == 'local':
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev' )
            dutName = 'TestDev:SoftPlayer'
        self.dutDev = dutName.split( ':' )[0]
        self.dut = Volkano.VolkanoDevice( dutName, aIsDut=True )

        # Execute the actual tests
        self._TestSetAndMute()
        self._TestVolIncDec()
        self._TestBalSet()
        self._TestBalIncDec()
        
    def Cleanup( self ):
        "Perform cleanup on test exit"
        if self.dut:
            self.dut.Shutdown()
        if self.soft:
            self.soft.Shutdown()
        BASE.BaseTest.Cleanup( self )                

    #
    # Actual tests
    #
    
    def _TestSetAndMute( self ):
        "Check setting of spot volumes and mute functionality"
        for i in range( 10, 101, 10 ):
            self.log.Info( '' )
            self.log.Info( self.dutDev, 'Checking volume setting -> %d' % i )
            self.log.Info( '' )
            self.dut.volume.volume = i
            
            # these just need to check evented/polled values
            # self._CheckVolume( expVol, expVol, 'on %s (set to %d)' % (aSource['name'], i) )
            # self._CheckMute( aSource['name'] )
            
    def _TestVolIncDec( self ):
        "Check volume increment/decrement functionality"
        vol = 60
        self.dut.volume.volume = vol
        for action in ['VolInc','VolDec']:
            for i in range( 5 ):
                self.log.Info( '' )
                self.log.Info( self.dutDev, 'Checking %s from %d on %s' % (action, vol, aSource['name']) )
                self.log.Info( '' )
                getattr( self.dut.volume, action )()
                if action == 'VolInc':
                    vol += 1
                else:
                    vol -= 1
                expVol = vol-kVolumeUnityGain
                # just check evented / polled values
                #self._CheckVolume( expVol, expVol, 'on %s (%s to %d)' % (aSource['name'], action, vol) )
                
    def _TestBalSet( self ):        
        "Check balance. Balance range is -15(L) -> +15(R)"
        for i in range( -15, 16 ):
            self.log.Info( '' )
            self.log.Info( self.dutDev, 'Checking balance on %s -> %d  (vol=%d)' % (aSource['name'], i, vol) )
            self.log.Info( '' )
            self.dut.volume.balance = i
            ## self._CheckVolume( left, right, 'on %s (balance at %d)' % (aSource['name'], i) )
        self.dut.volume.balance = 0
        
    def _TestBalIncDec( self ):
        "Check balance increment/decrement functionality"
        self.log.Info( '' )
        self.log.Info( self.dutDev, 'Checking balance incremant/decrement actions' )
        self.log.Info( '' )
        bal = -15
        self.dut.volume.balance = bal
        for action in ['BalInc','BalDec']:
            for i in range( 31 ):
                getattr( self.dut.volume, action )()
                measBal = self.dut.volume.polledBalance
                if action == 'BalInc':
                    bal += 1
                else:
                    bal -= 1
                if bal < -15:
                    bal = -15
                elif bal > 15:
                    bal = 15
                self.log.FailUnless( self.dutDev, measBal==bal,
                    '%d/%d Actual/Expected balance on %s after %s' % 
                    (measBal, bal, aSource['name'], action) )
        self.dut.volume.balance = 0
            
    #
    # Test utilities
    #
        
    def _CheckMute( self ):
        "Checks mute functionality"
        self.dut.volume.mute = True
#        self._CheckVolume( -85, -85, 'on %s muted' % aSource )
        self.dut.volume.mute = False
               

if __name__ == '__main__':
    
    BASE.Run( sys.argv )
