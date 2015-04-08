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
                        'Attributes': [
                            ],
                        'Actions': [
                            # Action                    OutArg(s)                                       InArg(s)
                            ('GetKeys',                 'string',                                       None),
                            ('GetValue',                'string',                                       'key'),
                            ('SetValue',                None,                                           ['key', 'value'])]},
    'Credentials':     {'ObjName':
                            'credentials',
                        'Attributes': [
                            # Attribute                 Value
                            ('Ids',                     'string'),
                            ('PublicKey',               'string'),
                            ('SequenceNumber',          'uint')],
                        'Actions': [
                            # Action                    OutArg(s)                                       InArg(s)
                            ('Clear',                   None,                                           'id'),
                            ('Get',                     ['string','b64','bool','string','string'],      'id'),
                            ('GetIds',                  'string',                                       None),
                            ('GetPublicKey',            'string',                                       None),
                            ('GetSequenceNumber',       'uint',                                         None),
                            ('Login',                   'string',                                       'id'),
                            ('ReLogin',                 'string',                                       ['id','token']),
                            ('Set',                     None,                                           ['id','user','pwd']),
                            ('SetEnabled',              None,                                           ['id','enabled'])]},
    'Exakt':           {'ObjName':
                            'exakt',
                        'Attributes': [
                            # Attribute                 Value
                            ('ConnectionStatus',        'string'),
                            ('DeviceList',              'xml'),
                            ('Version',                 'uint')],
                        'Actions': [
                            # Action                    OutArg(s)                                       InArg(s)
                            ('ConnectionStatus',        'string',                                       None),
                            ('DeviceList',              'xml',                                          None),
                            ('DeviceSettings',          'string',                                       'id'),
                            ('Reprogram',               None,                                           ['id','uri']),
                            ('ReprogramFallback',       None,                                           ['id','uri']),
                            ('Set',                     None,                                           ['id','bank','uri','mute','present']),
                            ('Version',                 'string',                                       None)]},
    'Info':            {'ObjName':
                            'info',
                        'Attributes': [
                            # Attribute                 Value
                            ('BitDepth',                'uint'),
                            ('BitRate',                 'uint'),
                            ('CodecName',               'string'),
                            ('DetailsCount',            'uint'),
                            ('Duration',                'uint'),
                            ('Lossless',                'bool'),
                            ('Metadata',                'xml'),
                            ('Metatext',                'string'),
                            ('MetatextCount',           'uint'),
                            ('TrackCount',              'uint'),
                            ('SampleRate',              'uint'),
                            ('Uri',                     'url')],
                        'Actions': [
                            # Action                    OutArg(s)                                       InArg(s)
                            ('Counters',                ['uint','uint','uint'],                         None),
                            ('Details',                 ['uint','uint','uint','uint','bool','string'],  None),
                            ('Metatext',                'string',                                       None),
                            ('Track',                   ['uri','string'],                               None)]},
    'NetworkMonitor':  {'ObjName':
                            'netmon',
                        'Attributes': [
                            # Attribute                 Value
                            ('Name',                    'string'),
                            ('Receiver',                'uint'),
                            ('Results',                 'uint'),
                            ('Sender',                  'uint')],
                        'Actions': [
                            # Action                    OutArg(s)                                       InArg(s)
                            ('Name',                    'string',                                       None),
                            ('Ports',                   ['uint','uint','uint'],                         None)]},
    'Playlist':        {'ObjName':
                            'playlist',
                        'Attributes': [
                            # Attribute                 Value                                           Allowed Values
                            ('Id',                      'uint'),
                            ('IdArray',                 'b64'),
                            ('ProtocolInfo',            'string'),
                            ('Repeat',                  'bool'),
                            ('Shuffle',                 'bool'),
                            ('TracksMax',               'uint'),
                            ('TransportState',          'list',                                         ['Playing', 'Paused', 'Stopped', 'Buffering'])],
                        'Actions': [
                            # Action                    OutArg(s)                                       InArg(s)
                            ('DeleteAll',               None,                                           None),
                            ('DeleteId',                None,                                           'id'),
                            ('Id',                      'uint',                                         None),
                            ('IdArray',                 ['uint','b64'],                                 None),
                            ('IdArrayChanged',          'bool',                                         'token'),
                            ('Insert',                  'uint',                                         ['after','uri','meta']),
                            ('Next',                    None,                                           None),
                            ('Pause',                   None,                                           None),
                            ('Play',                    None,                                           None),
                            ('Previous',                None,                                           None),
                            ('ProtocolInfo',            'string',                                       None),
                            ('Read',                    ['url','xml'],                                  'id'),
                            ('ReadList',                'string',                                       'idlist'),
                            ('Repeat',                  'bool',                                         None),
                            ('SeekId',                  None,                                           'id'),
                            ('SeekIndex',               None,                                           'index'),
                            ('SeekSecondAbsolute',      None,                                           'secs'),
                            ('SeekSecondRelative',      None,                                           'secs'),
                            ('SetRepeat',               None,                                           'val'),
                            ('SetShuffle',              None,                                           'val'),
                            ('Shuffle',                 'bool',                                         None),
                            ('Stop',                    None,                                           None),
                            ('TracksMax',               'uint',                                         None),
                            ('TransportState',          'string',                                       None)]},
    'Product':         {'ObjName':
                            'product',
                        'Attributes': [
                            # Attribute                 Value
                            ('Attributes',              'string'),
                            ('ManufacturerImageUri',    'url'),
                            ('ManufacturerName',        'string'),
                            ('ManufacturerInfo',        'string'),
                            ('ManufacturerUrl',         'url'),
                            ('ModelName',               'string'),
                            ('ModelInfo',               'string'),
                            ('ModelUrl',                'url'),
                            ('ModelImageUri',           'url'),
                            ('ProductRoom',             'string'),
                            ('ProductName',             'string'),
                            ('ProductInfo',             'string'),
                            ('ProductUrl',              'url'),
                            ('ProductImageUri',         'url'),
                            ('Standby',                 'bool'),
                            ('SourceIndex',             'uint'),
                            ('SourceCount',             'uint'),
                            ('SourceXml',               'xml')],
                        'Actions': [
                            # Action                    OutArg(s)                                       InArg(s)
                            ('Attributes',              'string',                                       None),
                            ('Manufacturer',            ['string', 'string', 'string', 'string'],       None),
                            ('Model',                   ['string', 'string', 'url', 'url'],             None),
                            ('Product',                 ['string', 'string', 'string', 'url'],          None),
                            ('SetSourceIndex',          None,                                           0),
                            ('SetSourceIndexByName',    None,                                           'name'),
                            ('SetStandby',              None,                                           False),
                            ('Source',                  ['string', 'string', 'string', 'bool'],         0),
                            ('SourceCount',             'uint',                                         None),
                            ('SourceIndex',             'uint',                                         None),
                            ('SourceXml',               'xml',                                          None),
                            ('Standby',                 'bool',                                         None)]},
    'Radio':           {'ObjName':
                            'radio',
                        'Attributes': [
                            # Attribute                 Value                                           Allowed Values
                            ('ChannelsMax',             'uint'),
                            ('Id',                      'uint'),
                            ('IdArray',                 'b64'),
                            ('Metadata',                'xml'),
                            ('ProtocolInfo',            'string'),
                            ('TransportState',          'list',                                         ['Playing', 'Paused', 'Stopped', 'Buffering']),
                            ('Uri',                     'url')],
                        'Actions': [
                            # Action                    OutArg(s)                                       InArg(s)
                            ('Channel',                 ['url','xml'],                                  None),
                            ('ChannelsMax',             'uint',                                         None),
                            ('Id',                      'uint',                                         None),
                            ('IdArray',                 'b64',                                          'token'),
                            ('IdArrayChanged',          'bool',                                         'token'),
                            ('Pause',                   None,                                           None),
                            ('Play',                    None,                                           None),
                            ('ProtocolInfo',            'string',                                       None),
                            ('Read',                    'xml',                                          'id'),
                            ('ReadList',                'string',                                       'idlist'),
                            ('SeekSecondAbsolute',      None,                                           'secs'),
                            ('SeekSecondRelative',      None,                                           'secs'),
                            ('SetChannel',              None,                                           ['channel','meta']),
                            ('SetId',                   None,                                           ['id','uri']),
                            ('Stop',                    None,                                           None),
                            ('TransportState',          'string',                                       None)]},
    'Receiver':        {'ObjName':
                            'receiver',
                        'Attributes': [
                            # Attribute                 Value                                           Allowed Values
                            ('Metadata',                'xml'),
                            ('ProtocolInfo',            'string'),
                            ('TransportState',          'list',                                         ['Playing', 'Waiting', 'Stopped', 'Buffering']),
                            ('Uri',                     'url')],
                        'Actions': [
                            # Action                    OutArg(s)                                       InArg(s)
                            ('Play',                    None,                                           None),
                            ('ProtocolInfo',            'string',                                       None),
                            ('Sender',                  ['url','xml'],                                  None),
                            ('SetSender',               None,                                           ['url','meta']),
                            ('Stop',                    None,                                           None),
                            ('TransportState',          'string',                                       None)]},
    'Sender':          {'ObjName':
                            'sender',
                        'Attributes': [
                            # Attribute                 Value                                           Allowed Values
                            ('Attributes',              'string'),
                            ('Audio',                   'bool'),
                            ('Metadata',                'xml'),
                            ('PresentationUrl',         'url'),
                            ('Status',                  'list',                                         ['Enabled', 'Disabled', 'Blocked'])],
                        'Actions': [
                            # Action                    OutArg(s)                                       InArg(s)
                            ('Attributes',              'string',                                       None),
                            ('Audio',                   'string',                                       None),
                            ('Metadata',                'xml',                                          None),
                            ('PresentationUrl',         'url',                                          None),
                            ('Status',                  'string',                                       None)]},
    'Time':            {'ObjName':
                            'time',
                        'Attributes': [
                            # Attribute                 Value
                            ('Duration',                'uint'),
                            ('Seconds',                 'uint'),
                            ('TrackCount',              'uint')],
                        'Actions': [
                            # Action                    OutArg(s)                                       InArg(s)
                            ('Time',                    ['uint','uint','uint'],                         None)]},
    'Volume':          {'ObjName':
                            'volume',
                        'Attributes': [
                            # Attribute                 Value
                            ('Balance',                 'int'),
                            ('BalanceMax',              'uint'),
                            ('Fade',                    'int'),
                            ('FadeMax',                 'uint'),
                            ('Mute',                    'bool'),
                            ('Volume',                  'uint'),
                            ('VolumeLimit',             'uint'),
                            ('VolumeMax',               'uint'),
                            ('VolumeMilliDbPerStep',    'uint'),
                            ('VolumeUnity',             'uint'),
                            ('VolumeSteps',             'uint')],
                        'Actions': [
                            # Action                    OutArg(s)                                       InArg(s)
                            ('Balance',                 'int',                                          None),
                            ('BalanceDec',              None,                                           None),
                            ('BalanceInc',              None,                                           None),
                            ('Characteristics',         ['uint','uint','uint','uint','uint','uint'],    None),
                            ('Fade',                    'int',                                          None),
                            ('FadeDec',                 None,                                           None),
                            ('FadeInc',                 None,                                           None),
                            ('Mute',                    'bool',                                         None),
                            ('SetBalance',              None,                                           'bal'),
                            ('SetFade',                 None,                                           'fade'),
                            ('SetMute',                 None,                                           'mute'),
                            ('SetVolume',               None,                                           'vol'),
                            ('Volume',                  'uint',                                         None),
                            ('VolumeDec',               None,                                           None),
                            ('VolumeInc',               None,                                           None),
                            ('VolumeLimit',             'uint',                                         None)]}
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
        if len( kServices[aSname]['Actions'] ):
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
