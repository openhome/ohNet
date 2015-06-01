#!/usr/bin/env python
"""TestSourceSelect - check Source selection (part of Product service)

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]

Cut-down version of Volkano1 source tests with purely software checks
on only the OpenHome sources (no UPnP AV sources)
"""
import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.OhMediaPlayer as OHMP
import _SoftPlayer                      as SoftPlayer
import sys
import time
import threading
import xml.etree.ElementTree            as ET


def Run( aArgs ):
    """Pass the Run() call from derived tests up to the base class"""
    BASE.Run( aArgs )


class TestSourceSelect( BASE.BaseTest ):

    def __init__( self ):
        """Constructor - initalise base class"""
        BASE.BaseTest.__init__( self )
        self.doc     = __doc__
        self.dut     = None
        self.dutDev  = None
        self.soft    = None
        self.sources = []

    def Test( self, args ):
        """Product Service tests for preamp functionality"""
        dutName  = ''
        loopback = False

        try:
            dutName = args[1]
        except:
            print '\n', self.doc, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )

        if dutName.lower() == 'local':
            loopback = True
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev', aLoopback=loopback )
            dutName = self.soft.name

        self.dutDev = dutName.split( ':' )[0]
        self.dut = OHMP.OhMediaPlayerDevice( dutName, aIsDut=True, aLoopback=loopback )
        self.sources = self._GetSources()

        self._CheckCount()
        self._CheckConfig( self.sources )

        for src in self.sources:
            self._CheckSourceSelect( src, 'index' )
        for src in self.sources:
            self._CheckSourceSelect( src, 'name' )
        for src in self.sources:
            self._CheckSourceSelect( src, 'auto' )

    def Cleanup( self ):
        """Perform cleanup on test exit"""
        if self.dut:
            self.dut.Shutdown()
        if self.soft:
            self.soft.Shutdown()
        BASE.BaseTest.Cleanup( self )

    def _CheckCount( self ):
        """Check evented vs. polled source count"""
        self.log.Header2( self.dutDev, 'Checking source count' )
        evented = self.dut.product.sourceCount
        polled  = self.dut.product.polledSourceCount
        self.log.FailUnless( self.dutDev, evented==polled,
            '%s/%s Evented/Polled Source Count' % (evented, polled) )

    def _CheckConfig( self, aSources ):
        """Check reported config against expected"""
        self.log.Header2( self.dutDev, 'Checking source configuration' )
        time.sleep( 2 )    # Let XML update
        xmlConfig = []
        sourceList = ET.fromstring( self.dut.product.sourceXml )
        sources = sourceList.getiterator( 'Source' )
        for source in sources:
            xmlConfig.append(
                {'name': source.getiterator( 'Name' )[0].text,
                 'type': source.getiterator( 'Type' )[0].text,
                 'visible': source.getiterator( 'Visible' )[0].text} )

        for i in range( len( aSources )):
            evt = aSources[i]
            xml = xmlConfig[i]
            strEvtVisible = 'false'
            if evt['visible']: strEvtVisible = 'true'
            self.log.FailUnless( self.dutDev, evt['name'] == xml['name'],
                '%d: %s/%s Evented/XML source Name' % (i, evt['name'], xml['name']) )
            self.log.FailUnless( self.dutDev, evt['type'] == xml['type'],
                '%d: %s/%s Evented/XML source Type' % (i, evt['type'], xml['type']) )
            self.log.FailUnless( self.dutDev, strEvtVisible == xml['visible'],
                '%d: %s/%s Evented/XML source Visibility' % (i, strEvtVisible, xml['visible']) )
            self.log.Info( self.dutDev, '%s Evented source System Name' % aSources[i]['sysName'])

    def _CheckSourceSelect( self, aSrc, aMode ):
        """Check source select action and event"""
        srcIndexEv = threading.Event()

        # noinspection PyUnusedLocal
        def ProductEventCb( service, svName, svVal, svSeq ):
            """Callback on events from product service"""
            if svName == 'SourceIndex':
                srcIndexEv.set()

        self.log.Header2( self.dutDev, 'Checking select of %s by %s' % (aSrc['name'], aMode) )
        self.dut.product.AddSubscriber( ProductEventCb )
        srcIndexEv.clear()
        if aMode == 'index':
            self.dut.product.sourceIndex = aSrc['index']
        elif aMode =='name':
            self.dut.product.sourceIndexByName = aSrc['name']
        else:   # auto
            if 'Playlist' in aSrc['type']:
                self.dut.playlist.SeekIndex( 0, aReturnErr=True )
            elif 'Radio' in aSrc['type']:
                self.dut.radio.Play()
            elif 'Receiver' in aSrc['type']:
                self.dut.receiver.Play()
            else:
                self.log.Info( self.dutDev, 'No test for auto-select of %s' % aSrc['type'] )
                return
        srcIndexEv.wait( 10 )
        self.dut.product.RemoveSubscriber( ProductEventCb )

        # check source selection (and event) as expected
        eventedIndex = self.dut.product.sourceIndex
        self.log.FailUnless( self.dutDev, aSrc['index'] == eventedIndex,
            '(%s/%s) set/evented source index' % ( str( aSrc['index'] ), str( eventedIndex )) )
        polledIndex = self.dut.product.polledSourceIndex
        self.log.FailUnless( self.dutDev, polledIndex==aSrc['index'],
            '(%s/%s) set/polled source index' % (str( aSrc['index'] ), str( polledIndex )) )
        name = self.dut.product.SourceName( aSrc['index'] )
        self.log.FailUnless( self.dutDev, name==aSrc['name'],
            '(%s/%s) set/polled source name' % (aSrc['name'], name) )

    def _GetSources( self ):
        """Return current sources read from DUT"""
        config = []
        for i in range( self.dut.product.sourceCount ):
            name =    self.dut.product.SourceName( i )
            sType =   self.dut.product.SourceType( i )
            visible = self.dut.product.SourceVisible( i )
            sysName = self.dut.product.SourceSystemName( i )
            # level = False
            # if sType in ['Analog']:
            #     if self.model in ProductData.kInputLevelAvail: level = True
            config.append( {'index':i, 'name':name, 'type':sType,
                           'visible':visible, 'sysName':sysName} ) #, 'level':level} )
        return config


if __name__ == '__main__':

    BASE.Run( sys.argv )
