"""TestVolumeControl - test volume control functionality

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]

Check operations of Volume control functions
"""

# Severely cut-down variant of DS test.
# Only checks operation of volume service at commands level  

import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.OhMediaPlayer as OHMP
import _SoftPlayer                      as SoftPlayer
import os
import sys
import threading


class TestVolumeControl( BASE.BaseTest ):

    def __init__( self ):
        """Constructor - initalise base class"""
        BASE.BaseTest.__init__( self )
        self.dut    = None
        self.dutDev = None
        self.soft   = None
        self.volEvt = threading.Event()
        
    def Test( self, args ):
        """Tests for volume functionality"""
        dutName  = ''
        loopback = False

        try:
            dutName   = args[1]
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )
            
        # Create and initialise DUT
        if dutName.lower() == 'local':
            loopback = True
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev', aLoopback=loopback )
            dutName = self.soft.name
        self.dutDev = dutName.split( ':' )[0]
        self.dut = OHMP.OhMediaPlayerDevice( dutName, aIsDut=True, aLoopback=loopback )
        self.dut.volume.AddSubscriber( self._VolEventCb )

        # Execute the actual tests
        self._TestSetAndMute()
        self._TestVolIncDec()
        self._TestBalSet()
        self._TestBalIncDec()
        
    def Cleanup( self ):
        """Perform cleanup on test exit"""
        if self.dut:
            self.dut.Shutdown()
        if self.soft:
            self.soft.Shutdown()
        BASE.BaseTest.Cleanup( self )                

    #
    # Actual tests
    #
    
    def _TestSetAndMute( self ):
        """Check setting of spot volumes and mute functionality"""
        for vol in range( 10, 101, 10 ):
            self.log.Info( '' )
            self.log.Info( self.dutDev, 'Checking volume setting -> %d' % vol )
            self.log.Info( '' )
            
            self.volEvt.clear()
            self.dut.volume.volume = vol
            self.volEvt.wait( 5 )
            self._CheckVolume( vol, 'before mute' )
            
            self.volEvt.clear()
            self.dut.volume.mute = True
            self.volEvt.wait( 5 )
            self._CheckMute( True )
            self._CheckVolume( vol, 'whilst muted' )
            
            self.volEvt.clear()
            self.dut.volume.mute = False
            self.volEvt.wait( 5 )
            self._CheckMute( False )
            self._CheckVolume( vol, 'after unmute' )
            
    def _TestVolIncDec( self ):
        """Check volume increment/decrement functionality"""
        vol = 60
        self.volEvt.clear()
        self.dut.volume.volume = vol
        self.volEvt.wait( 5 )
        for action in ['VolInc','VolDec']:
            for i in range( 5 ):
                self.log.Info( '' )
                self.log.Info( self.dutDev, 'Checking %s from %d' % (action, vol) )
                self.log.Info( '' )
                self.volEvt.clear()
                getattr( self.dut.volume, action )()
                self.volEvt.wait( 5 )
                if action == 'VolInc':
                    vol += 1
                else:
                    vol -= 1
                self._CheckVolume( vol, 'after %s' % action )
                
    def _TestBalSet( self ):        
        """Check balance. Balance range is -15(L) -> +15(R)"""
        for bal in range( -15, 16 ):
            self.log.Info( '' )
            self.log.Info( self.dutDev, 'Checking balance set to %d' % bal )
            self.log.Info( '' )
            self.volEvt.clear()
            self.dut.volume.balance = bal
            self.volEvt.wait( 5 )
            self._CheckBalance( bal, 'set to %d' % bal )
        self.volEvt.clear()
        self.dut.volume.balance = 0
        self.volEvt.wait( 5 )
        
    def _TestBalIncDec( self ):
        """Check balance increment/decrement functionality"""
        self.log.Info( '' )
        self.log.Info( self.dutDev, 'Checking balance incremant/decrement actions' )
        self.log.Info( '' )
        bal = -15
        self.volEvt.clear()
        self.dut.volume.balance = bal
        self.volEvt.wait( 5 )
        for action in ['BalInc','BalDec']:
            for i in range( 30 ):
                self.volEvt.clear()
                getattr( self.dut.volume, action )()
                self.volEvt.wait( 5 )
                if action == 'BalInc':
                    bal += 1
                else:
                    bal -= 1
                if bal < -15:
                    bal = -15
                elif bal > 15:
                    bal = 15
                self._CheckBalance( bal, 'after %s' % action )
        self.volEvt.clear()
        self.dut.volume.balance = 0
        self.volEvt.wait( 5 )
            
    #
    # Test utilities
    #
    
    def _CheckVolume( self, aVol, aMsg='' ):
        """Check volume (evented and polled) as expected"""
        eventedVol = self.dut.volume.volume
        polledVol  = self.dut.volume.polledVolume
        self.log.FailUnless( self.dutDev, eventedVol==aVol,
            '%d/%d  Actual/Expected EVENTED volume %s' % (eventedVol, aVol, aMsg) ) 
        self.log.FailUnless( self.dutDev, polledVol==aVol,
            '%d/%d  Actual/Expected POLLED volume %s' % (polledVol, aVol, aMsg) )
        
    def _CheckMute( self, aMute, aMsg='' ):
        """Check mute (evented and polled) as expected"""
        eventedMute = self.dut.volume.mute
        polledMute  = self.dut.volume.polledMute
        self.log.FailUnless( self.dutDev, eventedMute==aMute,
            '%d/%d  Actual/Expected EVENTED mute %s' % (eventedMute, aMute, aMsg) ) 
        self.log.FailUnless( self.dutDev, polledMute==aMute,
            '%d/%d  Actual/Expected POLLED mute %s' % (polledMute, aMute, aMsg) )
    
    def _CheckBalance( self, aBal, aMsg='' ):
        """Check balance (evented and polled) as expected"""
        eventedBal = self.dut.volume.balance
        polledBal  = self.dut.volume.polledBalance
        self.log.FailUnless( self.dutDev, eventedBal==aBal,
            '%d/%d  Actual/Expected EVENTED balance %s' % (eventedBal, aBal, aMsg) ) 
        self.log.FailUnless( self.dutDev, polledBal==aBal,
            '%d/%d  Actual/Expected POLLED balance %s' % (polledBal, aBal, aMsg) )

    # noinspection PyUnusedLocal
    def _VolEventCb( self, aService, aSvName, aSvVal, aSvSeq ):
        self.volEvt.set()
               

if __name__ == '__main__':
    
    BASE.Run( sys.argv )
