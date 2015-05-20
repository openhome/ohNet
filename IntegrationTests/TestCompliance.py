#!/usr/bin/env python
"""TestCompliance - ohMediaServer compliance test

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]

Test to ensure device complies with ohMediaPlayer standard. Basically attempts to ensure
that all services, actions and attributes are present and respond as defined by the
ohMediaPlayer 'standard'. Does NOT verify actual functionality (eg. doesn't check Play
causes player to actually Play)
"""
import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.OhMediaPlayer as OHMP
import _SoftPlayer                      as SoftPlayer
import xml.etree.ElementTree            as ET
import LogThread
import base64
import os
import re
import sys
import threading
import time
import types
import urlparse

# The following table defines all attributes (events) and actions for the OpenHome UPnP services.
# Where actions require input (in-args) we have no knowledge of what values would be valid. Hence
# we use some sort of 'sensible' value for each of these cases. If this results in a UPnP error
# from the invocation it will be handled, but type-checking of the expected return(s) cannot occur.

kServices = {
    'Configuration':   {'ObjName': #====================================================================================
                            'config',
                        'Attributes': [
                            # Attribute --------------- Value ------------------------- Allowed Values -----------------
                            ],
                        'Actions': [
                            # Action ------------------ OutArg(s) --------------------- InArg(s) -----------------------
                            ('GetKeys',                 'string',                       None),
                            ('GetValue',                'string',                       'key'),
                            ('SetValue',                None,                           ['key', 'value'])]},

    'Credentials':     {'ObjName': #====================================================================================
                            'credentials',
                        'Attributes': [
                            # Attribute --------------- Value ------------------------- Allowed Values -----------------
                            ('Ids',                     'string'),
                            ('PublicKey',               'string'),
                            ('SequenceNumber',          'uint')],
                        'Actions': [
                            # Action ------------------ OutArg(s) --------------------- InArg(s) -----------------------
                            ('Clear',                   None,                           'id'),
                            ('Get',                     {'UserName':'string',
                                                         'Password':'b64',
                                                         'Enabled': 'bool',
                                                         'Status':  'string',
                                                         'Data':    'string'},          'id'),
                            ('GetIds',                  'string',                       None),
                            ('GetPublicKey',            'string',                       None),
                            ('GetSequenceNumber',       'uint',                         None),
                            ('Login',                   'string',                       'id'),
                            ('ReLogin',                 'string',                       ['id','token']),
                            ('Set',                     None,                           ['id','user','pwd']),
                            ('SetEnabled',              None,                           ['id',True])]},

    'Exakt':           {'ObjName': #====================================================================================
                            'exakt',
                        'Attributes': [
                            # Attribute --------------- Value ------------------------- Allowed Values -----------------
                            ('ConnectionStatus',        'string'),
                            ('DeviceList',              'xml'),
                            ('Version',                 'uint')],
                        'Actions': [
                            # Action ------------------ OutArg(s) --------------------- InArg(s) -----------------------
                            ('ConnectionStatus',        'string',                       None),
                            ('DeviceList',              'xml',                          None),
                            ('DeviceSettings',          'string',                       'id'),
                            ('Reprogram',               None,                           ['id','proto://uri']),
                            ('ReprogramFallback',       None,                           ['id','proto://uri']),
                            ('Set',                     None,                           ['id',0,'proto://uri',True,True]),
                            ('Version',                 'string',                       None)]},

    'Info':            {'ObjName': #====================================================================================
                            'info',
                        'Attributes': [
                            # Attribute --------------- Value ------------------------- Allowed Values -----------------
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
                            # Action ------------------ OutArg(s) --------------------- InArg(s) -----------------------
                            ('Counters',                {'TrackCount':   'uint',
                                                         'DetailsCount': 'uint',
                                                         'MetatextCount':'uint'},       None),
                            ('Details',                 {'Duration':     'uint',
                                                         'BitRate':      'uint',
                                                         'BitDepth':     'uint',
                                                         'SampleRate':   'uint',
                                                         'Lossless':     'bool',
                                                         'CodecName':    'string'},     None),
                            ('Metatext',                'string',                       None),
                            ('Track',                   {'Uri':          'url',
                                                         'Metadata':     'string'},     None)]},

    'NetworkMonitor':  {'ObjName': #====================================================================================
                            'netmon',
                        'Attributes': [
                            # Attribute --------------- Value ------------------------- Allowed Values -----------------
                            ('Name',                    'string'),
                            ('Receiver',                'uint'),
                            ('Results',                 'uint'),
                            ('Sender',                  'uint')],
                        'Actions': [
                            # Action ------------------ OutArg(s) --------------------- InArg(s) -----------------------
                            ('Name',                    'string',                       None),
                            ('Ports',                   {'Sender':  'uint',
                                                         'Receiver':'uint',
                                                         'Results': 'uint'},            None)]},

    'Playlist':        {'ObjName': #====================================================================================
                            'playlist',
                        'Attributes': [
                            # Attribute --------------- Value ------------------------- Allowed Values -----------------
                            ('Id',                      'uint'),
                            ('IdArray',                 'b64'),
                            ('ProtocolInfo',            'string'),
                            ('Repeat',                  'bool'),
                            ('Shuffle',                 'bool'),
                            ('TracksMax',               'uint'),
                            ('TransportState',          'list',                         ['Playing', 'Paused', 'Stopped', 'Buffering'])],
                        'Actions': [
                            # Action ------------------ OutArg(s) --------------------- InArg(s) -----------------------
                            ('DeleteAll',               None,                           None),
                            ('DeleteId',                None,                           1),
                            ('Id',                      'uint',                         None),
                            ('IdArray',                 {'Token':'uint',
                                                         'Array':'b64'},                None),
                            ('IdArrayChanged',          'bool',                         'token'),
                            ('Insert',                  'uint',                         [0,'proto://uri','<meta></meta>']),
                            ('Next',                    None,                           None),
                            ('Pause',                   None,                           None),
                            ('Play',                    None,                           None),
                            ('Previous',                None,                           None),
                            ('ProtocolInfo',            'string',                       None),
                            ('Read',                    {'Uri':     'url',
                                                         'Metadata':'xml'},             1),
                            ('ReadList',                'string',                       '1 2 3'),
                            ('Repeat',                  'bool',                         None),
                            ('SeekId',                  None,                           1),
                            ('SeekIndex',               None,                           1),
                            ('SeekSecondAbsolute',      None,                           10),
                            ('SeekSecondRelative',      None,                           10),
                            ('SetRepeat',               None,                           True),
                            ('SetShuffle',              None,                           True),
                            ('Shuffle',                 'bool',                         None),
                            ('Stop',                    None,                           None),
                            ('TracksMax',               'uint',                         None),
                            ('TransportState',          'string',                       None)]},

    'Product':         {'ObjName': #====================================================================================
                            'product',
                        'Attributes': [
                            # Attribute --------------- Value ------------------------- Allowed Values -----------------
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
                            # Action ------------------ OutArg(s) --------------------- InArg(s) -----------------------
                            ('Attributes',              'string',                       None),
                            ('Manufacturer',            {'Name':      'string',
                                                         'Info':      'string',
                                                         'Url':       'url',
                                                         'ImageUri':  'url'},           None),
                            ('Model',                   {'Name':      'string',
                                                         'Info':      'string',
                                                         'Url':       'url',
                                                         'ImageUri':  'url'},           None),
                            ('Product',                 {'Room':      'string',
                                                         'Name':      'string',
                                                         'Info':      'string',
                                                         'Url':       'url'},           None),
                            ('SetSourceIndex',          None,                           1),
                            ('SetSourceIndexByName',    None,                           'Radio'),
                            ('SetStandby',              None,                           False),
                            ('Source',                  {'SystemName':'string',
                                                         'Type':      'string',
                                                         'Name':      'string',
                                                         'Visible':   'bool'},          1),
                            ('SourceCount',             'uint',                         None),
                            ('SourceIndex',             'uint',                         None),
                            ('SourceXml',               'xml',                          None),
                            ('Standby',                 'bool',                         None)]},

    'Radio':           {'ObjName': #====================================================================================
                            'radio',
                        'Attributes': [
                            # Attribute --------------- Value ------------------------- Allowed Values -----------------
                            ('ChannelsMax',             'uint'),
                            ('Id',                      'uint'),
                            ('IdArray',                 'b64'),
                            ('Metadata',                'xml'),
                            ('ProtocolInfo',            'string'),
                            ('TransportState',          'list',                         ['Playing', 'Paused', 'Stopped', 'Buffering']),
                            ('Uri',                     'url')],
                        'Actions': [
                            # Action ------------------ OutArg(s) --------------------- InArg(s) -----------------------
                            ('Channel',                 {'Uri':     'url',
                                                         'Metadata':'xml'},             None),
                            ('ChannelsMax',             'uint',                         None),
                            ('Id',                      'uint',                         None),
                            ('IdArray',                 {'Token':   'uint',
                                                         'Array':   'b64'},             None),
                            ('IdArrayChanged',          'bool',                         'token'),
                            ('Pause',                   None,                           None),
                            ('Play',                    None,                           None),
                            ('ProtocolInfo',            'string',                       None),
                            ('Read',                    'xml',                          1),
                            ('ReadList',                'string',                       '1 2 3'),
                            ('SeekSecondAbsolute',      None,                           10),
                            ('SeekSecondRelative',      None,                           10),
                            ('SetChannel',              None,                           ['proto://uri','<meta></meta>']),
                            ('SetId',                   None,                           [0,'proto://uri']),
                            ('Stop',                    None,                           None),
                            ('TransportState',          'string',                       None)]},

    'Receiver':        {'ObjName': #====================================================================================
                            'receiver',
                        'Attributes': [
                            # Attribute --------------- Value ------------------------- Allowed Values -----------------
                            ('Metadata',                'xml'),
                            ('ProtocolInfo',            'string'),
                            ('TransportState',          'list',                         ['Playing', 'Waiting', 'Stopped', 'Buffering']),
                            ('Uri',                     'url')],
                        'Actions': [
                            # Action ------------------ OutArg(s) --------------------- InArg(s) -----------------------
                            ('Play',                    None,                           None),
                            ('ProtocolInfo',            'string',                       None),
                            ('Sender',                  {'Uri':     'url',
                                                         'Metadata':'xml'},             None),
                            ('SetSender',               None,                           ['proto://uri','<meta></meta>']),
                            ('Stop',                    None,                           None),
                            ('TransportState',          'string',                       None)]},

    'Sender':          {'ObjName': #====================================================================================
                            'sender',
                        'Attributes': [
                            # Attribute --------------- Value ------------------------- Allowed Values -----------------
                            ('Attributes',              'string'),
                            ('Audio',                   'bool'),
                            ('Metadata',                'xml'),
                            ('PresentationUrl',         'url'),
                            ('Status',                  'list',                         ['Enabled', 'Disabled', 'Blocked'])],
                        'Actions': [
                            # Action ------------------ OutArg(s) --------------------- InArg(s) -----------------------
                            ('Attributes',              'string',                       None),
                            ('Audio',                   'bool',                         None),
                            ('Metadata',                'xml',                          None),
                            ('PresentationUrl',         'url',                          None),
                            ('Status',                  'string',                       None)]},

    'Time':            {'ObjName': #====================================================================================
                            'time',
                        'Attributes': [
                            # Attribute --------------- Value ------------------------- Allowed Values -----------------
                            ('Duration',                'uint'),
                            ('Seconds',                 'uint'),
                            ('TrackCount',              'uint')],
                        'Actions': [
                            # Action ------------------ OutArg(s) --------------------- InArg(s) -----------------------
                            ('Time',                    {'TrackCount':'uint',
                                                         'Duration':  'uint',
                                                         'Seconds':   'uint'},          None)]},

    'Volume':          {'ObjName': #====================================================================================
                            'volume',
                        'Attributes': [
                            # Attribute --------------- Value ------------------------- Allowed Values -----------------
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
                            # Action ------------------ OutArg(s) --------------------- InArg(s) -----------------------
                            ('Balance',                 'int',                          None),
                            ('BalanceDec',              None,                           None),
                            ('BalanceInc',              None,                           None),
                            ('Characteristics',         {'VolumeMax':           'uint',
                                                         'VolumeUnity':         'uint',
                                                         'VolumeSteps':         'uint',
                                                         'VolumeMilliDbPerStep':'uint',
                                                         'BalanceMax':          'uint',
                                                         'FadeMax':             'uint'}, None),
                            ('Fade',                    'int',                           None),
                            ('FadeDec',                 None,                            None),
                            ('FadeInc',                 None,                            None),
                            ('Mute',                    'bool',                          None),
                            ('SetBalance',              None,                            0),
                            ('SetFade',                 None,                            0),
                            ('SetMute',                 None,                            False),
                            ('SetVolume',               None,                            50),
                            ('Volume',                  'uint',                          None),
                            ('VolumeDec',               None,                            None),
                            ('VolumeInc',               None,                            None),
                            ('VolumeLimit',             'uint',                          None)]}
}
kMandatory = ['Product']
kRequested = ['Credentials', 'Exakt', 'Info', 'Sender', 'Time', 'Volume']
kOptional  = ['Configuration', 'NetworkMonitor', 'Playlist', 'Radio', 'Receiver']


class TestCompliance( BASE.BaseTest ):
    
    def __init__( self ):
        """Constructor - initalise base class"""
        BASE.BaseTest.__init__( self )
        self.dut      = None
        self.dutDev   = ''
        self.soft     = None
        self.attr     = None
        self.watchdog = None

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

        loopback = False
        if dutName.lower() == 'local':
            loopback = True
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev', aLoopback=loopback )
            dutName = self.soft.name
        self.dutDev = dutName.split( ':' )[0]
        self.dut = OHMP.OhMediaPlayerDevice( dutName, aLoopback=loopback )
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
        if self.soft:
            self.soft.Shutdown()
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
            self._CheckActions( aSname )

    def _CheckAttributes( self, aSname, aService ):
        """Check required attributes of specified service"""
        evented = {}

        # noinspection PyUnusedLocal
        def _EventCb( aServ, aSvName, aSvVal, aSvSeq ):
            evented[aSvName] = aSvVal

        self.log.Header2( self.dutDev, 'Checking %s service attributes' % aSname )
        aService.proxy.Unsubscribe()
        aService.initEvent.clear()
        aService.AddSubscriber( _EventCb )
        aService.proxy.Subscribe()
        aService.initEvent.wait( 5 )
        if not aService.initEvent.is_set():
            self.log.Fail( self.dutDev, '%s: NO Initial subscription event' % aSname )

        for attribute in kServices[aSname]['Attributes']:
            msg = '%s: <%s> attribute' % (aSname, attribute[0])
            if attribute[0] in evented.keys():
                vals = []
                if len( attribute )> 2:
                    vals = attribute[2]
                self.log.Pass( self.dutDev, '%s present' % msg )
                self._CheckType( msg, evented[attribute[0]], attribute[1], vals )
            else:
                self.log.Fail( self.dutDev, '%s missing' % msg )

    def _CheckActions( self, aSname ):
        """Check required actions of specified service"""
        self.log.Header2( self.dutDev, 'Checking %s service actions' % aSname )
        for entry in kServices[aSname]['Actions']:
            action, outArgs, inArgs = entry
            if inArgs is not None:
                if type( inArgs ) != types.ListType:
                    inArgs = [inArgs]
            self._CheckInvocation( aSname, action, inArgs, outArgs )

    def _CheckInvocation( self, aSname, aAction, aInArgs, aOutArgs ):
        """Invoke action and check types of returned outargs (or valid error)"""
        msg = '%s: <%s> action output' % (aSname, aAction)
        invocation = 'self.dut.%s.%s.%s(' % (kServices[aSname]['ObjName'], kServices[aSname]['ObjName'], aAction )
        if kServices[aSname]['ObjName'] == 'volume':
            # work-around historical naming conflict in volume service
            invocation = 'self.dut.%s.%s.%s(' % (kServices[aSname]['ObjName'], 'vol', aAction )
        if aInArgs is not None:
            invocation += str( aInArgs )[1:-1] + ','
        invocation += 'aReturnErr=True)'

        self._StartWatchdog( 5 )
        result = eval( invocation )
        self._CancelWatchdog()

        err = None
        if type( result ) == types.StringType:
            err = re.match( '^\d{1,3}: ', result )
            if err:
                errCode = int( result.split( ':' )[0] )
                if 800 <= errCode < 900:
                    self.log.Pass( self.dutDev, '%s errored (OK) - %s' % (msg, result))
                else:
                    self.log.Fail( self.dutDev, '%s errored (Unexpected) - %s' % (msg, result))

        if not err:
            if type( aOutArgs ) == types.DictionaryType:
                for key in aOutArgs.keys():
                    try:
                        self._CheckType( msg+' <'+key+'>', result[key], aOutArgs[key] )
                    except:
                        self.log.Fail( self.dutDev, '%s <%s> - NOT returned' % (msg, key) )
            else:
                if result == {}:
                    result = None
                self._CheckType( msg, result, aOutArgs )

    def _CheckType( self, aMsg, aMeas, aExp, aVals=() ):
        """Check returned data type is as expected"""
        ok   = False

        if aExp == 'string':
            if type( aMeas ) == types.StringType:
                ok = True
        elif aExp == 'url':
            if urlparse.urlparse( aMeas ).scheme != '' and urlparse.urlparse( aMeas ).netloc != '':
                ok = True
            elif aMeas == '':    # URLs can be empty
                ok = True
        elif aExp == 'xml':
            if aMeas == '':      # XML can be empty
                ok = True
            else:
                try:
                    ET.XML( aMeas )
                    ok = True
                except:
                    pass
        elif aExp == 'list':
            if aMeas in aVals:
                ok = True
        elif aExp == 'uint':
            try:
                if int( aMeas ) >= 0:
                    ok = True
            except:
                pass
        elif aExp == 'int':
            try:
                int( aMeas )
                ok = True
            except:
                pass
        elif aExp == 'bool':
            if type( aMeas ) == types.BooleanType:
                ok = True
        elif aExp == 'b64':
            try:
                base64.decodestring( aMeas )
                ok = True
            except:
                pass
        elif aExp is None:
            if aMeas is None:
                ok = True
        self.log.FailUnless( self.dutDev, ok, '%s type - expected <%s>' % (aMsg, aExp) )

    def _StartWatchdog( self, aInterval ):
        """Start watchdog timer with specified timeout"""
        if self.watchdog:
            self.watchdog.cancel()
        self.watchdog = LogThread.Timer( aInterval, self._WatchdogCb )
        self.watchdog.start()

    def _CancelWatchdog( self ):
        """Cancel watchdog timer"""
        if self.watchdog:
            self.watchdog.cancel()
            self.watchdog = None

    def _WatchdogCb( self ):
        """Called on watchdog timer expiry - abort test"""
        self.log.Fail( self.dutDev, 'Device failed to respond - exiting' )
        time.sleep( 1 )
        # noinspection PyProtectedMember
        os._exit( -1 )


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
