#!/usr/bin/env python
"""TestAirplayFunctions - test Net Aux source functionality.
 
Parameters:
    arg#1 - UPnP device to use as DUT
    arg#2 - iTunes server (PC name)
    
NOTES
    - allow delay after setting DACP speaker (or iTunes (ver >= 11) may hang)
            
This verifies output by the DUT using Net Aux decode is correct, and Net Aux 
source handling operates correctly.
""" 

# Differences from DS test:
#    - removed all testing that measured output on scope
#    - removed auto-select mode checking (mode N/A)

import _FunctionalTest
import BaseTest                       as BASE
import Upnp.ControlPoints.Volkano     as Volkano
import Instruments.Network.DacpClient as DacpClient
import math
import sys
import threading
import time

kItunesCtr = 'Music'
kVolTrack  = 'Stereo1kHz-441-16-0dB-72m'


class TestAirplayFunctions( BASE.BaseTest ):
    """Class to verify Net Aux source (Airplay input) functionality"""
    
    def __init__( self ):
        "Constructor for Net Aux test"
        BASE.BaseTest.__init__( self )
        self.dacp       = None
        self.dut        = None
        self.tracks     = None
        self.srcChanged = threading.Event()

    def Test( self, args ):
        "Net Aux test"
        # parse command line arguments
        try:
            self.dutName = args[1]
            itunesServer = args[2]
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )

        # setup self.dacp (iTunes) control
        self.dacp = DacpClient.DacpClient( itunesServer )
        if self.dutName not in self.dacp.speakers:
            self.log.Abort( self.dacp.dev, '%s not available as iTunes speaker' % self.dutName )
        self.dacp.speaker = 'My Computer'
        time.sleep( 5 )        
        self.dacp.Pause()
                    
        # setup DUT
        self.dutDev = self.dutName.split( ':' )[0]
        self.dut = Volkano.VolkanoDevice( self.dutName, aIsDut=False )
        self.dut.product.AddSubscriber( self.__ProductEvtCb )
                        
        # get list of available tracks from iTunes
        if self.dacp.library in self.dacp.databases:
            self.dacp.database = self.dacp.library 
            if kItunesCtr in self.dacp.containers:
                self.dacp.container = kItunesCtr
                self.tracks = self.dacp.items
            else:
                self.log.Abort( self.dacp.dev, '%s container not found in iTunes' % kItunesCtr )
        else: 
            self.log.Abort( self.dacp.dev, '%s database not found in iTunes' % self.dacp.library )

        # run the tests
        self._CheckSelect()
        self._CheckAudioFreq()
        self._CheckVolume()

    def Cleanup( self ):
        "Perform cleanup on test exit"
        if self.dacp:
            try:
                self.dacp.Pause()  
                self.dacp.speaker = 'My Computer'
            except:
                pass
        if self.dut: self.dut.Shutdown()
        BASE.BaseTest.Cleanup( self )

    def _CheckSelect( self ):
        "Check auto-selection of Net Aux source"        
        self.dacp.speaker = 'My Computer'
        self.dacp.PlayTrack( kVolTrack )
        time.sleep( 5 )
         
#        self.dut.config.Set( 'Net Aux', 'Auto Select', 'false' )
        self.srcChanged.clear()
        self.dut.product.sourceIndexByName = 'Playlist'
        self.srcChanged.wait( 5 )
        name = self.dut.product.SourceSystemName( self.dut.product.sourceIndex )
        self.log.FailUnless( self.dutDev, name=='Playlist',
            '%s/Playlist - actual/expected source before Airplay started' % name )
        
        self.srcChanged.clear()
        self.dacp.speaker = self.dutName
        self.srcChanged.wait( 5 )
        name = self.dut.product.SourceSystemName( self.dut.product.sourceIndex )
        self.log.FailUnless( self.dutDev, name=='Playlist',
            '%s/Playlist - actual/expected source on Airplay start with Net Aux auto select disabled' % name )
        
        self.dacp.speaker = 'My Computer'
        self.dut.config.Set( 'Net Aux', 'Auto Select', 'true' )
        self.srcChanged.clear()
        self.dut.product.sourceIndexByName = 'Playlist'
        self.srcChanged.wait( 5 )
        name = self.dut.product.SourceSystemName( self.dut.product.sourceIndex )
        self.log.FailUnless( self.dutDev, name=='Playlist',
            '%s/Playlist - actual/expected source before Airplay started' % name )
        
        self.srcChanged.clear()
        self.dacp.speaker = self.dutName
        self.srcChanged.wait( 5 )
        name = self.dut.product.SourceSystemName( self.dut.product.sourceIndex )
        self.log.FailUnless( self.dutDev, name=='Net Aux',
            '%s/Net Aux - actual/expected source on Airplay start with Net Aux auto select enabled' % name )

        self.srcChanged.clear()
        self.dacp.Pause()
        self.srcChanged.wait( 5 )
        name = self.dut.product.SourceSystemName( self.dut.product.sourceIndex )
        self.log.FailUnless( self.dutDev, name=='Net Aux',
            '%s/Net Aux - actual/expected source after Airplay stopped' % name )

        self.srcChanged.clear()
        self.dut.product.sourceIndexByName = 'Playlist'
        self.srcChanged.wait( 5 )
        self.srcChanged.clear
        self.dacp.PlayTrack( kVolTrack )
        self.srcChanged.wait( 5 )
        name = self.dut.product.SourceSystemName( self.dut.product.sourceIndex )
        self.log.FailUnless( self.dutDev, name=='Playlist',
            '%s/Playlist - actual/expected source after Airplay restarted' % name )
        
        self.srcChanged.clear()
        self.dacp.speaker = 'My Computer'
        time.sleep( 5 ) 
        self.dacp.speaker = self.dutName 
        time.sleep( 5 )
        self.srcChanged.wait( 5 )
        name = self.dut.product.SourceSystemName( self.dut.product.sourceIndex )
        self.log.FailUnless( self.dutDev, name=='Net Aux',
            '%s/Net Aux - actual/expected source after AirPlay speakers reselected' % name )
        
    def _CheckAudioFreq( self ):
        "Check audio frequency of Net Aux tracks"
        if self.dut.volume is not None:
            self.dut.volume.volume = 80
        self.srcChanged.clear()
        self.dacp.speaker = self.dutName
        self.srcChanged.wait( 5 )
        self.dacp.volume = 100
        time.sleep( 5 )

        titles = []
        for track in self.tracks:
            if track['album'] == 'Test Tones':
                if '30s' in track['title']:
                    titles.append( track['title'] )
                    
        if len( titles ) < 14:
            self.log.Fail( self.dacp.dev, '%d required test tones not available on %s' % (len( titles ), self.dacp.server) )
                
        for title in titles:
            msg = 'AirPlay with %s' % title
            self.dacp.PlayTrack( title )
            time.sleep( 5 )
            
            # just wait a few secs and check info ticks and nothing crashes....
                        
    def _CheckVolume( self ):
        "Check volume control on server is reflected in DS output"
        if self.dut.volume is not None:
            self.dut.volume.volume = 80
        self.srcChanged.clear()
        self.dacp.speaker = 'My Computer'
        time.sleep( 5 )
        self.dacp.speaker = self.dutName
        time.sleep( 5 )
        self.dacp.PlayTrack( kVolTrack )
        self.srcChanged.wait( 5 )
        
        self.dacp.volume = 100
        time.sleep( 5 )
        
        for (setVol, expVol) in [(10,-42), (20,-28), (30,-21), (40,-16), (50,-12),
                                 (60,-9),  (70,-6),  (80,-4),  (90,-2),  (100,0)]:
            msg = 'AirPlay volume set to %d' % setVol
            self.dacp.volume = setVol
            time.sleep( 5 )
            
            # just wait a few secs and check info ticks and nothing crashes....
        
    def __ProductEvtCb( self, service, svName, svVal, svSeq ):
        "Callback on events from product service"
        if svName == 'SourceIndex':
            self.srcChanged.set()

    def _ToDb( self, aVmeas, aVzero ):
        "Convert amplitude from Vrms to dB"
        try:
            db = round( 20 * math.log10( aVmeas/aVzero ), 3 )
        except:
            db = -999
        return db
        
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
        