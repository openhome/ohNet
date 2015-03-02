#!/usr/bin/env python
"""TestRenderingControlService - test UPnP AV RenderingControl service

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
            
Check UPnP AV RenderingControl (Volume) service
""" 
import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.MediaRenderer as MR
import _SoftPlayer                      as SoftPlayer
import random
import sys
import threading
import time
import xml.etree.ElementTree as ET

kMaxVol = 100
kRcsNs  = '{urn:schemas-upnp-org:metadata-1-0/RCS/}'


class TestRenderingControlService( BASE.BaseTest ):
    """Test DS implementation of UPnP AV RenderingControl Service"""

    def __init__( self ):
        BASE.BaseTest.__init__( self )
        self.mr           = None
        self.mrDev        = None
        self.rc           = None
        self.soft         = None
        self.currVolume   = None
        self.currVolumeDb = None
        self.currMute     = None
        self.rcEvent      = threading.Event()
        
    def Test( self, args ):
        dutName  = ''
        loopback = False

        try:
            dutName    = args[1]
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )

        if dutName.lower() == 'local':
            loopback = True
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev', aLoopback=loopback )
            dutName = self.soft.name.split( ':' )[0] + ':UPnP AV'
            
        self.mrDev = dutName.split( ':' )[0]
        self.mr = MR.MediaRendererDevice( dutName, aLoopback=loopback )
        self.rc = self.mr.rc        
        self.rc.AddSubscriber( self._RcEventCb )
        self.currVolume = self.rc.volume
        self.currVolumeDb = self.rc.volumeDb

        # test volume control / monitoring
        targetVol = random.randint( 1, kMaxVol-1 )
        self.VolStepping( kMaxVol )
        self.VolStepping( 0 )
        self.VolStepping( targetVol )
        
        # test volume DB control / monitoring
        volRange = self.rc.volumeDbRange
        if volRange is not None:
            targetVol = random.randint( volRange['MinValue'], volRange['MaxValue'] )
            self.VolDbStepping( targetVol )
        
        # test mute control / monitoring
        self.Mute( 15 )

    def Cleanup( self ):
        """Perform cleanup on test exit"""
        if self.mr:
            self.mr.Shutdown()
        if self.soft:
            self.soft.Shutdown()
        BASE.BaseTest.Cleanup( self )                
                    
    def VolStepping( self, aTarget ):
        """Step volume to aTarget (or range limit)"""
        self.log.Info( self.mrDev, 'Stepping volume to %d' % aTarget )
        polledVolume = -1
        done = False        
        while not done:
            if aTarget > self.currVolume: 
                newVol=self.currVolume+1
            else:
                newVol=self.currVolume-1
            self.rcEvent.clear()
            self.rc.volume = newVol
            self.rcEvent.wait( 5 )
            if not self.rcEvent.isSet():
                if self.currVolume==kMaxVol and aTarget>=self.currVolume \
                or self.currVolume==0       and aTarget<self.currVolume:
                    self.log.Info( self.mrDev, 'Volume range end-point reached' )
                    aTarget = self.currVolume
                done = True
            else:
                polledVolume = self.rc.polledVolume
                self.log.FailUnless( self.mrDev, self.currVolume==newVol, 
                    '%d/%d (actual/expected) EVENTED volume' % (self.currVolume, newVol) )    
                self.log.FailUnless( self.mrDev, polledVolume==newVol, 
                    '%d/%d (actual/expected) POLLED volume' % (polledVolume, newVol) )
            if aTarget > self.currVolume: 
                if self.currVolume>=aTarget:
                    done=True
            else:
                if self.currVolume<=aTarget:
                    done=True
       
        self.log.FailUnless( self.mrDev, self.currVolume == aTarget, 
            'Final EVENTED volume was %d, expected %d' % (self.currVolume, aTarget) )
        self.log.FailUnless( self.mrDev, self.rc.polledVolume == aTarget, 
            'Final POLLED volume was %d, expected %d' % (polledVolume, aTarget) )
                    
    def VolDbStepping( self, aTarget ):
        """Step volume to aTarget (or range limit)"""
        self.log.Info( self.mrDev, 'Stepping volume DB to %d' % aTarget )
        step = (self.rc.volumeDbRange['MaxValue']-self.rc.volumeDbRange['MinValue']) / 100
        done = False        
        while not done:
            if aTarget > self.currVolumeDb: 
                newVol=self.currVolumeDb+step
            else:
                newVol=self.currVolumeDb-step
            self.rcEvent.clear()
            self.rc.volumeDb = newVol
            self.rcEvent.wait( 5 )
            polledVolumeDb = self.rc.polledVolumeDb
            self.log.FailUnless( self.mrDev, self.currVolumeDb==newVol, 
                '%d/%d (actual/expected) EVENTED volume DB' % (self.currVolumeDb, newVol) )    
            self.log.FailUnless( self.mrDev, polledVolumeDb==newVol, 
                '%d/%d (actual/expected) POLLED volume DB' % (polledVolumeDb, newVol) )
            if (aTarget-step) < self.currVolumeDb <= aTarget:
                done=True
        self.log.CheckLimits( self.mrDev, 'GTLE', self.currVolumeDb, aTarget-step, aTarget, 'Final EVENTED volume DB' )
        self.log.CheckLimits( self.mrDev, 'GTLE', self.rc.polledVolumeDb, aTarget-step, aTarget, 'Final EVENTED volume DB' )

    def Mute( self, aLoops ):        
        """Check mute operates correctly"""
        if aLoops/2.0 == aLoops/2:
            expMute = self.currMute
        else:
            if self.currMute == 0:
                expMute = 1
            else:
                expMute = 0

        nextMute = 0
        currMute = self.rc.mute
        for i in range( aLoops ):
            self.rcEvent.clear()
            if currMute == 1:
                nextMute = 0
            else:
                nextMute = 1
            self.rc.mute = nextMute
            currMute = nextMute
            self.rcEvent.wait( 3 )
            if not self.rcEvent.isSet():
                self.log.Fail( self.mrDev, 'Toggling mute timed out' )
            else:
                polledMute = self.rc.polledMute
                self.log.FailUnless( self.mrDev, self.currMute==nextMute, 
                    '%s/%s (actual/expected) EVENTED mute' % (self.currMute, nextMute) )    
                self.log.FailUnless( self.mrDev, polledMute==nextMute, 
                    '%s/%s (actual/expected) POLLED mute' % (polledMute, nextMute) )    
            
        self.log.FailUnless( self.mrDev, self.currMute==expMute,
            'Final EVENTED mute state after %d presses was %s' % (aLoops, self.currMute))
        polledMute = self.rc.polledMute
        if type( polledMute ) == int:
            self.log.FailUnless( self.mrDev, polledMute == nextMute, 
                'Final POLLED mute state after %d presses was %s' % (aLoops, polledMute))

    # noinspection PyUnusedLocal
    def _RcEventCb( self, service, svName, svVal, svSeq ):
        """Callback from UPnP RenderingControl events"""
        tree = ET.XML( svVal.encode( 'utf-8' ))
        self.currVolume = int( tree.getiterator( kRcsNs+'Volume')[0].attrib['val'] )
        self.currVolumeDb = int( tree.getiterator( kRcsNs+'VolumeDB')[0].attrib['val'] )
        self.currMute = int( tree.getiterator( kRcsNs+'Mute')[0].attrib['val'] ) 
        self.rcEvent.set()


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
