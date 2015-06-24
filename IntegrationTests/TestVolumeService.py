"""TestVolumeService - test volume service functionality

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]

Check operations of Volume service functionality
"""
import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.OhMediaPlayer as OHMP
import _SoftPlayer                      as SoftPlayer
import os
import sys
import threading


def Run( aArgs ):
    """Pass the Run() call from derived tests up to the base class"""
    BASE.Run( aArgs )


class TestVolumeService( BASE.BaseTest ):

    def __init__( self ):
        """Constructor - initalise base class"""
        BASE.BaseTest.__init__( self )
        self.doc    = __doc__
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
            print '\n', self.doc, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )
            
        # Create and initialise DUT
        if dutName.lower() == 'local':
            loopback = True
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev', aLoopback=loopback )
            dutName = self.soft.name
        self.dutDev = dutName.split( ':' )[0]
        self.dut = OHMP.OhMediaPlayerDevice( dutName, aIsDut=True, aLoopback=loopback )
        if self.dut.volume is None:
            self.log.Skip( self.dutDev, 'No volume service' )
        self.dut.volume.AddSubscriber( self._VolEventCb )

        # Execute the actual tests
        self._TestSetAndMute()
        self._TestVolIncDec()
        self._TestBalSet()
        self._TestBalIncDec()
        self._TestFadeSet()
        self._TestFadeIncDec()

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
        vMax = self.dut.volume.volLimit       # max permitted volume -> volume limit
        for vol in range( vMax/10, vMax+1, vMax/10 ):
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
        vol = int( self.dut.volume.volLimit*0.65 )
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
        """Check balance"""
        bMax = self.dut.volume.balMax
        if bMax:
            for bal in range( -1*bMax, bMax+1 ):
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
        bMax = self.dut.volume.balMax
        if bMax:
            self.log.Info( '' )
            self.log.Info( self.dutDev, 'Checking balance increment/decrement actions' )
            self.log.Info( '' )
            bMax = self.dut.volume.balMax
            bal = -1 * bMax
            self.volEvt.clear()
            self.dut.volume.balance = bal
            self.volEvt.wait( 5 )
            for action in ['BalInc','BalDec']:
                for i in range( bMax*2 ):
                    self.volEvt.clear()
                    getattr( self.dut.volume, action )()
                    self.volEvt.wait( 5 )
                    if action == 'BalInc':
                        bal += 1
                    else:
                        bal -= 1
                    if bal < -1*bMax:
                        bal = -1*bMax
                    elif bal > bMax:
                        bal = bMax
                    self._CheckBalance( bal, 'after %s' % action )
            self.volEvt.clear()
            self.dut.volume.balance = 0
            self.volEvt.wait( 5 )

    def _TestFadeSet( self ):
        """Check fader"""
        fMax = self.dut.volume.fadeMax
        if fMax:
            for fade in range( -1*fMax, fMax+1 ):
                self.log.Info( '' )
                self.log.Info( self.dutDev, 'Checking fader set to %d' % fade )
                self.log.Info( '' )
                self.volEvt.clear()
                self.dut.volume.fade = fade
                self.volEvt.wait( 5 )
                self._CheckFade( fade, 'set to %d' % fade )
            self.volEvt.clear()
            self.dut.volume.fade = 0
            self.volEvt.wait( 5 )

    def _TestFadeIncDec( self ):
        """Check fader increment/decrement functionality"""
        fMax = self.dut.volume.fadeMax
        if fMax:
            self.log.Info( '' )
            self.log.Info( self.dutDev, 'Checking fader increment/decrement actions' )
            self.log.Info( '' )
            fMax = self.dut.volume.fadeMax
            fade = -1 * fMax
            self.volEvt.clear()
            self.dut.volume.fade = fade
            self.volEvt.wait( 5 )
            for action in ['FadeInc','FadeDec']:
                for i in range( fMax*2 ):
                    self.volEvt.clear()
                    getattr( self.dut.volume, action )()
                    self.volEvt.wait( 5 )
                    if action == 'FadeInc':
                        fade += 1
                    else:
                        fade -= 1
                    if fade < -1*fMax:
                        fade = -1*fMax
                    elif fade > fMax:
                        fade = fMax
                    self._CheckFade( fade, 'after %s' % action )
            self.volEvt.clear()
            self.dut.volume.fade = 0
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

    def _CheckFade( self, aFade, aMsg='' ):
        """Check fade (evented and polled) as expected"""
        eventedFade = self.dut.volume.fade
        polledFade  = self.dut.volume.polledFade
        self.log.FailUnless( self.dutDev, eventedFade==aFade,
            '%d/%d  Actual/Expected EVENTED fade %s' % (eventedFade, aFade, aMsg) )
        self.log.FailUnless( self.dutDev, polledFade==aFade,
            '%d/%d  Actual/Expected POLLED fade %s' % (polledFade, aFade, aMsg) )

    # noinspection PyUnusedLocal
    def _VolEventCb( self, aService, aSvName, aSvVal, aSvSeq ):
        self.volEvt.set()
               

if __name__ == '__main__':
    
    BASE.Run( sys.argv )
