#!/usr/bin/env python
"""TestCompliance - ohMediaServer compliance test

Parameters:
    arg#1 - DUT - UPnP frindly name of device-under-test

Test to ensure device complies with ohMediaServer standard. Basically ensures that
all services, actions and attributes are correctly present and operational as defined
by ohMediaPlayer 'standard'
"""
import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.OhMediaPlayer as OHMP
import xml.etree.ElementTree            as ET
import base64
import os
import sys
import time
import types
import urlparse

kServices = {
    'Configuration':   {'ObjName':
                            'config',
                        'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            ]},
    'Credentials':     {'ObjName':
                            'credentials',
                        'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            ('Ids',                  'string'),
                            ('PublicKey',            'string'),
                            ('SequenceNumber',       'uint')]},
    'Exakt':           {'ObjName':
                            'exakt',
                        'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            ('ConnectionStatus',     'string'),
                            ('DeviceList',           'xml'),
                            ('Version',              'uint')]},
    'Info':            {'ObjName':
                            'info',
                        'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            ('BitDepth',             'uint'),
                            ('BitRate',              'uint'),
                            ('CodecName',            'string'),
                            ('DetailsCount',         'uint'),
                            ('Duration',             'uint'),
                            ('Lossless',             'bool'),
                            ('Metadata',             'xml'),
                            ('Metatext',             'string'),
                            ('MetatextCount',        'uint'),
                            ('TrackCount',           'uint'),
                            ('SampleRate',           'uint'),
                            ('Uri',                  'url')]},
    'NetworkMonitor':  {'ObjName':
                            'netmon',
                        'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            ('Name',                 'string'),
                            ('Receiver',             'uint'),
                            ('Results',              'uint'),
                            ('Sender',               'uint')]},
    'Playlist':        {'ObjName':
                            'playlist',
                        'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            ('Id',                   'uint'),
                            ('IdArray',              'b64'),
                            ('ProtocolInfo',         'string'),
                            ('Repeat',               'bool'),
                            ('Shuffle',              'bool'),
                            ('TracksMax',            'uint'),
                            ('TransportState',       'list',        ['Playing', 'Paused', 'Stopped', 'Buffering'])]},
    'Product':         {'ObjName':
                            'product',
                        'Actions': [
                            'a',
                            'b'],
                        'Attributes': [
                            ('Attributes',           'string'),
                            ('ManufacturerImageUri', 'url'),
                            ('ManufacturerName',     'string'),
                            ('ManufacturerInfo',     'string'),
                            ('ManufacturerUrl',      'url'),
                            ('ModelName',            'string'),
                            ('ModelInfo',            'string'),
                            ('ModelUrl',             'url'),
                            ('ModelImageUri',        'url'),
                            ('ProductRoom',          'string'),
                            ('ProductName',          'string'),
                            ('ProductInfo',          'string'),
                            ('ProductUrl',           'url'),
                            ('ProductImageUri',      'url'),
                            ('Standby',              'bool'),
                            ('SourceIndex',          'uint'),
                            ('SourceCount',          'uint'),
                            ('SourceXml',            'xml')]},
    'Radio':           {'ObjName':
                            'radio',
                        'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            ('ChannelsMax',          'uint'),
                            ('Id',                   'uint'),
                            ('IdArray',              'b64'),
                            ('Metadata',             'xml'),
                            ('ProtocolInfo',         'string'),
                            ('TransportState',       'list',        ['Playing', 'Paused', 'Stopped', 'Buffering']),
                            ('Uri',                  'url')]},
    'Receiver':        {'ObjName':
                            'receiver',
                        'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            ('Metadata',             'xml'),
                            ('ProtocolInfo',         'string'),
                            ('TransportState',       'list',        ['Playing', 'Waiting', 'Stopped', 'Buffering']),
                            ('Uri',                  'url')]},
    'Sender':          {'ObjName':
                            'sender',
                        'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            ('Attributes',           'string'),
                            ('Audio',                'bool'),
                            ('Metadata',             'xml'),
                            ('PresentationUrl',      'url'),
                            ('Status',               'list',        ['Enabled', 'Disabled', 'Blocked'])]},
    'Time':            {'ObjName':
                            'time',
                        'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            ('Duration',              'uint'),
                            ('Seconds',               'uint'),
                            ('TrackCount',            'uint')]},
    'Volume':          {'ObjName':
                            'volume',
                        'Actions': [
                            'x',
                            'y'],
                        'Attributes': [
                            ('Balance',                'int'),
                            ('BalanceMax',             'uint'),
                            ('Fade',                   'int'),
                            ('FadeMax',                'uint'),
                            ('Mute',                   'bool'),
                            ('Volume',                 'uint'),
                            ('VolumeLimit',            'uint'),
                            ('VolumeMax',              'uint'),
                            ('VolumeMilliDbPerStep',   'uint'),
                            ('VolumeUnity',            'uint'),
                            ('VolumeSteps',            'uint')]}
}
kMandatory = ['Product']
kRequested = ['Credentials', 'Exakt', 'Info', 'Sender', 'Time', 'Volume']
kOptional  = ['Configuration', 'NetworkMonitor', 'Playlist', 'Radio', 'Receiver']


class TestCompliance( BASE.BaseTest ):
    
    def __init__( self ):
        """Constructor - initalise base class"""
        BASE.BaseTest.__init__( self )
        self.dut            = None
        self.dutDev         = ''
        self.attr           = None

    def Test( self, aArgs ):
        """Test compliance with ohMediaPlayer 'standard'"""
        if os.environ.has_key( 'PYTHON_STACK' ):
            if os.environ['PYTHON_STACK'] != '':
                self.log.Abort( '', 'Compliance test MUST be executed using PyOhNet UPnP stack' )

        dutName = ''
        try:
            dutName = aArgs[1]
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( aArgs )) )

        self.dutDev = dutName.split( ':' )[0]
        self.dut = OHMP.OhMediaPlayerDevice( dutName )
        self.attr = self.dut.product.attributes

        for sName in kMandatory:
            self._Check( sName, 'mandatory' )
        for sName in kRequested:
            self._Check( sName, 'requested' )
        for sName in kOptional:
            self._Check( sName, 'optional' )

    def Cleanup( self ):
        """Perform cleanup on test exit"""
        if self.dut:
            self.dut.Shutdown()
        BASE.BaseTest.Cleanup( self )

    def _Check( self, aSname, aType ):
        """Check for correct presence of service, and compliance thereof"""
        service = None
        failure = None
        present = False

        if hasattr( self.dut, kServices[aSname]['ObjName'] ):
            service = getattr( self.dut, kServices[aSname]['ObjName'] )
            if service is not None:
                present = True
        requested = aSname in self.attr

        if aType == 'mandatory':
            if not present:
                failure = 'Mandatory service <%s> NOT present' % aSname
        elif aType == 'requested':
            if requested and not present:
                failure = 'Requested service <%s> NOT present' % aSname
            if not requested and present:
                failure = 'Service <%s> NOT listed in product attributes' % aSname

        if failure:
            self.log.Fail( self.dutDev, failure )
        else:
            if present:
                self._CheckCompliance( aSname, service )

    def _CheckCompliance( self, aSname, aService ):
        """Check compliance of specified service"""
        self.log.Header1( self.dutDev, 'Checking compliance of <%s> service' % aSname )
        if len( kServices[aSname]['Attributes'] ):
            self._CheckAttributes( aSname, aService )
        self._CheckActions( aSname, aService )

    def _CheckAttributes( self, aSname, aService ):
        """Check required attributes of specified service"""
        evented = {}

        # noinspection PyUnusedLocal
        def _EventCb( aServ, aSvName, aSvVal, aSvSeq ):
            evented[aSvName] = aSvVal

        aService.proxy.Unsubscribe()
        aService.initEvent.clear()
        aService.AddSubscriber( _EventCb )
        aService.proxy.Subscribe()
        aService.initEvent.wait( 10 )
        if not aService.initEvent.is_set():
            self.log.Fail( self.dutDev, '%s: NO Initial subscription event' % aSname )

        for attribute in kServices[aSname]['Attributes']:
            msg = '%s: <%s> attribute' % (aSname, attribute[0])
            if attribute[0] in evented.keys():
                self.log.Pass( self.dutDev, '%s present' % msg )
                self._CheckType( msg, evented[attribute[0]], attribute )
            else:
                self.log.Fail( self.dutDev, '%s missing' % msg )

    def _CheckActions( self, aSname, aService ):
        """Check required actions of specified service"""
        pass

    def _CheckType( self, aMsg, aMeas, aAttributes ):
        """Check returned data type is as expected"""
        ok   = False
        exp  = aAttributes[1]
        vals = []
        if len( aAttributes )> 2:
            vals = aAttributes[2]

        if exp == 'string':
            if type( aMeas ) == types.StringType:
                ok = True
        elif exp == 'url':
            if urlparse.urlparse( aMeas ).scheme != '' and urlparse.urlparse( aMeas ).netloc != '':
                ok = True
            elif aMeas == '':    # URLs can be empty
                ok = True
        elif exp == 'xml':
            if aMeas == '':      # XML can be empty
                ok = True
            else:
                try:
                    ET.XML( aMeas )
                    ok = True
                except:
                    pass
        elif exp == 'list':
            if aMeas in vals:
                ok = True
        elif exp == 'uint':
            try:
                if int( aMeas ) >= 0:
                    ok = True
            except:
                pass
        elif exp == 'int':
            try:
                int( aMeas )
                ok = True
            except:
                pass
        elif exp == 'bool':
            if type( aMeas ) == types.BooleanType:
                ok = True
        elif exp == 'b64':
            try:
                base64.decodestring( aMeas )
                ok = True
            except:
                pass
        self.log.FailUnless( self.dutDev, ok, '%s type - expected <%s>' % (aMsg, exp) )


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
