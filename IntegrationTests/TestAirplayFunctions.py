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
            self.log.Abort( 'Invalid arguments %s' % (str( args )) )

        # setup self.dacp (iTunes) control
        self.dacp = DacpClient.DacpClient( itunesServer )
        print "\n\n-->", self.dacp.speakers
        if self.dutName not in self.dacp.speakers:
            self.log.Abort( '%s not available as iTunes speaker' % self.dutName )
        self.dacp.speaker = 'My Computer'
        time.sleep( 5 )        
        self.dacp.Pause()
                    
        # setup DUT
        self.dut = Volkano.VolkanoDevice( self.dutName, aIsDut=False )
        self.dut.product.AddSubscriber( self.__ProductEvtCb )
                        
        # get list of available tracks from iTunes
        if self.dacp.library in self.dacp.databases:
            self.dacp.database = self.dacp.library 
            if kItunesCtr in self.dacp.containers:
                self.dacp.container = kItunesCtr
                self.tracks = self.dacp.items
            else:
                self.log.Abort( '%s container not found in iTunes' % kItunesCtr )
        else: 
            self.log.Abort( '%s database not found in iTunes' % self.dacp.library )

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
        self.log.FailUnless( name=='Playlist',
            '%s/Playlist - actual/expected source before Airplay started' % name )
        
        self.srcChanged.clear()
        self.dacp.speaker = self.dutName
        self.srcChanged.wait( 5 )
        name = self.dut.product.SourceSystemName( self.dut.product.sourceIndex )
        self.log.FailUnless( name=='Playlist',
            '%s/Playlist - actual/expected source on Airplay start with Net Aux auto select disabled' % name )
        
        self.dacp.speaker = 'My Computer'
        self.dut.config.Set( 'Net Aux', 'Auto Select', 'true' )
        self.srcChanged.clear()
        self.dut.product.sourceIndexByName = 'Playlist'
        self.srcChanged.wait( 5 )
        name = self.dut.product.SourceSystemName( self.dut.product.sourceIndex )
        self.log.FailUnless( name=='Playlist',
            '%s/Playlist - actual/expected source before Airplay started' % name )
        
        self.srcChanged.clear()
        self.dacp.speaker = self.dutName
        self.srcChanged.wait( 5 )
        name = self.dut.product.SourceSystemName( self.dut.product.sourceIndex )
        self.log.FailUnless( name=='Net Aux',
            '%s/Net Aux - actual/expected source on Airplay start with Net Aux auto select enabled' % name )

        self.srcChanged.clear()
        self.dacp.Pause()
        self.srcChanged.wait( 5 )
        name = self.dut.product.SourceSystemName( self.dut.product.sourceIndex )
        self.log.FailUnless( name=='Net Aux',
            '%s/Net Aux - actual/expected source after Airplay stopped' % name )

        self.srcChanged.clear()
        self.dut.product.sourceIndexByName = 'Playlist'
        self.srcChanged.wait( 5 )
        self.srcChanged.clear
        self.dacp.PlayTrack( kVolTrack )
        self.srcChanged.wait( 5 )
        name = self.dut.product.SourceSystemName( self.dut.product.sourceIndex )
        self.log.FailUnless( name=='Playlist',
            '%s/Playlist - actual/expected source after Airplay restarted' % name )
        
        self.srcChanged.clear()
        self.dacp.speaker = 'My Computer'
        time.sleep( 5 ) 
        self.dacp.speaker = self.dutName 
        time.sleep( 5 )
        self.srcChanged.wait( 5 )
        name = self.dut.product.SourceSystemName( self.dut.product.sourceIndex )
        self.log.FailUnless( name=='Net Aux',
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
            self.log.Fail( '%d required test tones not available on %s' % (len( titles ), self.dacp.server) )
                
        for title in titles:
            msg = 'AirPlay with %s' % title
            self.dacp.PlayTrack( title )
            time.sleep( 5 )
            
            # just wait a few secs and check info ticks and nothing crashes....
            
#            self.scope.chRange = '5V'
#            self.scope.Capture( 1e6, 100 )
#            self.dacp.Pause()
#            
#            expL = int( title.split()[0].strip('Hz'))
#            expR = int( title.split()[2].strip('Hz'))
#                
#            failed = False
#            if self.log.CheckLimits( 'GELE', self.scope.chaFreq,
#                expL*.999, expL*1.001, 'AirPlay LEFT with %s' % title ) == 'fail':
#                failed = True
#            if self.log.CheckLimits( 'GELE', self.scope.chbFreq,
#                expR*.999, expR*1.001, 'AirPlay RIGHT with %s' % title ) == 'fail':
#                failed = True
#            if self.plot == 'all':
#                self.scope.Plot( msg, self.plotter, self._PlotPath() )
#            elif self.plot == 'fails' and failed:
#                self.scope.Plot( msg, self.plotter, self._PlotPath() )
            
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
#        self.scope.chRange = '5V'
#        self.scope.Capture( 1e5, 100 )
#        zeroDbL = self.scope.chaRms
#        zeroDbR = self.scope.chbRms
        
        for (setVol, expVol) in [(10,-42), (20,-28), (30,-21), (40,-16), (50,-12),
                                 (60,-9),  (70,-6),  (80,-4),  (90,-2),  (100,0)]:
            msg = 'AirPlay volume set to %d' % setVol
            self.dacp.volume = setVol
            time.sleep( 5 )
            
            # just wait a few secs and check info ticks and nothing crashes....

            
#            if setVol < 41:
#                self.scope.chRange = '50mV'
#            if setVol < 61:
#                self.scope.chRange = '1V'
#            else:
#                self.scope.chRange = '5V'
#            self.scope.Capture( 1e5, 100 )
#            leftVol = self._ToDb( self.scope.chaRms, zeroDbL )
#            rightVol = self._ToDb( self.scope.chbRms, zeroDbL )
#            
#            failed = False
#            if self.log.CheckLimits( 'GELE', leftVol, expVol-1, expVol+1,
#                ' AirPlay volume LEFT set to %d' % setVol ) == 'fail':
#                failed = True
#            if self.log.CheckLimits( 'GELE', rightVol, expVol-1, expVol+1,
#                ' AirPlay volume RIGHT set to %d' % setVol ) == 'fail':
#                failed = True
#            if self.plot == 'all':
#                self.scope.Plot( msg, self.plotter, self._PlotPath() )
#            elif self.plot == 'fails' and failed:
#                self.scope.Plot( msg, self.plotter, self._PlotPath() )
        
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
                                
#    def _PlotPath( self ):
#        "Generate unique path for scope plot image"
#        self.plotNum += 1
#        fileName = 'AirplayFunctions_%s_Plot_%02d.png' % ( self.uniqueId, self.plotNum )
#        return os.path.join( LogUtils.GetLogfileDir(), fileName )
        
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
        