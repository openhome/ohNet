#!/usr/bin/env python
"""TestConnectionManagerService - test UPnP AV ConnectionManager aervice

Parameters:
    arg#1 - MediaRenderer DUT ['local' for internal SoftPlayer on loopback]

Checks (what little) functionality offered by ConnectionManager service
"""
import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.MediaRenderer as MR
import _SoftPlayer                      as SoftPlayer
import sys

kConnectionIds = '0'
kSourceProto   = ''
kSinkProto     = 'http-get:*:audio/x-flac:*,'    +\
                 'http-get:*:audio/wav:*,'       +\
                 'http-get:*:audio/wave:*,'      +\
                 'http-get:*:audio/x-wav:*,'     +\
                 'http-get:*:audio/aiff:*,'      +\
                 'http-get:*:audio/x-aiff:*,'    +\
                 'http-get:*:audio/x-m4a:*,'     +\
                 'http-get:*:audio/x-scpls:*,'   +\
                 'http-get:*:text/xml:*,'        +\
                 'http-get:*:audio/aac:*,'       +\
                 'http-get:*:audio/aacp:*,'      +\
                 'http-get:*:audio/mp4:*,'       +\
                 'http-get:*:audio/ogg:*,'       +\
                 'http-get:*:audio/x-ogg:*,'     +\
                 'http-get:*:application/ogg:*,' +\
                 'tidalhifi.com:*:*:*,'          +\
                 'qobuz.com:*:*:*'
kRcsId         = 0
kAvTransportId = 0
kPeerCm        = ''
kPeerId        = -1
kDirection     = 'Input'
kStatus        = 'Unknown'


class TestConnectionManagerService( BASE.BaseTest ):
    """Test UPnP AV ConnectionManager Service"""

    def __init__( self ):
        BASE.BaseTest.__init__( self )
        self.mrName = None
        self.mrDev  = None
        self.upnpMr = None
        self.cm     = None

    def Test( self, args ):
        """ConnectionManager service test"""
        loopback    = False
        try:
            self.mrName = args[1]
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )

        # start local softplayer if required
        if self.mrName.lower() == 'local':
            loopback = True
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestMr', aLoopback=loopback )
            self.mrName = self.soft.name.split( ':' )[0] + ':UPnP AV'
        else:
            self.mrName = self.mrName.split( ':' )[0] + ':UPnP AV'

        # create UPnP CPs for renderer and server, subscribe to AVT events
        self.mrDev = self.mrName.split( ':' )[0]
        self.upnpMr = MR.MediaRendererDevice( self.mrName, aLoopback=loopback )
        self.cm = self.upnpMr.cm

        # check CurrentConnectionIds
        connectionIds = self.cm.currentConnectionIDs
        self.log.FailUnless( self.mrDev, connectionIds==kConnectionIds,
            'Actual|Expected CurrentConnectionIds %s|%s' % (connectionIds, kConnectionIds) )

        # check ProtocolInfo
        source = self.cm.sourceProtocolInfo
        sink = self.cm.sinkProtocolInfo
        self.log.FailUnless( self.mrDev, source==kSourceProto,
            'Actual|Expected Source ProtocolInfo %s|%s' % (source, kSourceProto) )
        self.log.FailUnless( self.mrDev, sink==kSinkProto,
            'Actual|Expected Sink ProtocolInfo %s|%s' % (sink, kSinkProto) )

        # check CurrentConnectionInfo
        info = self.cm.GetCurrentConnectionInfo( ConnectionID=0 )
        self.log.FailUnless( self.mrDev, info['RcsID']==kRcsId,
            'Actual|Expected current RcsID %s|%s' % (info['RcsID'], kRcsId) )
        self.log.FailUnless( self.mrDev, info['AVTransportID']==kAvTransportId,
            'Actual|Expected current AVTransportID %s|%s' % (info['AVTransportID'], kAvTransportId) )
        self.log.FailUnless( self.mrDev, info['ProtocolInfo']==kSinkProto,
            'Actual|Expected current ProtocolInfo %s|%s' % (info['ProtocolInfo'], kSinkProto) )
        self.log.FailUnless( self.mrDev, info['PeerConnectionManager']==kPeerCm,
            'Actual|Expected current PeerConnectionManager %s|%s' % (info['PeerConnectionManager'], kPeerCm) )
        self.log.FailUnless( self.mrDev, info['PeerConnectionID']==kPeerId,
            'Actual|Expected current PeerConnectionID %s|%s' % (info['PeerConnectionID'], kPeerId) )
        self.log.FailUnless( self.mrDev, info['Direction']==kDirection,
            'Actual|Expected current Direction %s|%s' % (info['Direction'], kDirection) )
        self.log.FailUnless( self.mrDev, info['Status']==kStatus,
            'Actual|Expected current Status %s|%s' % (info['Status'], kStatus) )

    def Cleanup( self ):
        """Perform post-test cleanup"""
        if self.upnpMr:
            self.upnpMr.Shutdown()
        BASE.BaseTest.Cleanup( self )


if __name__ == '__main__':

    BASE.Run( sys.argv )
