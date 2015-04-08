#!/usr/bin/env python
"""TestAvTransporttPlayTracks - test Playing of playlists of tracks using AVTransport.

Parameters:
    arg#1 - AVT Renderer/Sender (UPnP AV Name) ['local' for internal SoftPlayer on loopback]
    arg#2 - Receiver ['local' for internal SoftPlayer on loopback] - optional (None = not present)
    arg#3 - Media server to source media from (None->test served audio)
    arg#4 - Playlist name (None/Full/Short->test served audio [defaults to full])
    arg#5 - Time to play before skipping to next (None = play all)
    arg#6 - Test loops (optional - default 1)
    arg#7 - Set False to prevent use of loopback adapter for local SoftPlayers (optional - default True)

Test test which plays tracks from an M3U playlist sequentially under AVTransport
control (test is acting like an AVT control point). The tracks may be played for
their entirety or any specified length of time
"""

import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.MediaRenderer as Renderer
import Upnp.ControlPoints.MediaServer   as Server
import Upnp.ControlPoints.OhMediaPlayer as OHMP
import Utils.Common                     as Common
import Utils.Network.HttpServer         as HttpServer
import _SoftPlayer                      as SoftPlayer
import LogThread
import os
import sys
import threading
import time
import xml.etree.ElementTree as ET

kAvtNs          = '{urn:schemas-upnp-org:metadata-1-0/AVT/}'
kAudioRoot      = os.path.join( _FunctionalTest.audioDir, 'LRTones/' )
kTrackListFull  = os.path.join( kAudioRoot, 'TrackList.xml' )
kTrackListShort = os.path.join( kAudioRoot, 'TrackListShort.xml' )


class TestAvTransportPlayTracks( BASE.BaseTest ):
    """Test playing of tracks using UPnP AV source"""

    def __init__( self ):
        """Constructor - initialise base class"""
        BASE.BaseTest.__init__( self )
        self.mr           = None
        self.mrDev        = None
        self.sender       = None
        self.senderDev    = None
        self.rcvr         = None
        self.rcvrDev      = None
        self.server       = None
        self.soft1        = None
        self.soft2        = None
        self.playlist     = []
        self.trackIndex   = -1
        self.numTracks    = 0
        self.title        = ''
        self.playTime     = None
        self.playTimer    = None    # expiry -> move to next track
        self.checkTimer   = None    # expiry -> info check
        self.tickTimer    = None    # expiry -> checks PositionInfo incrementing
        self.startTimer   = None    # expiry -> failed to start (log and continue)
        self.avtState     = None
        self.testLoop     = 0
        self.testLoops    = 1
        self.startTime    = 0
        self.stopTime     = 0
        self.prevAvtSecs  = 0
        self.reportedSecs = 0
        self.stuck        = 0
        self.started      = False
        self.eop          = threading.Event()
        self.mutex        = threading.Lock()

    def Test( self, args ):
        """UPnP device eventing test, with network stressing"""
        mrName       = ''
        rcvrName     = ''
        serverName   = ''
        playlistName = ''
        loopback     = False
        useLoopback  = 'True'

        try:
            mrName       = args[1]
            rcvrName     = args[2]
            serverName   = args[3]
            playlistName = args[4]
            if args[5] != 'None':
                self.playTime = int( args[5] )
            if len( args ) > 6:
                self.testLoops = int( args[6] )
            if len( args ) > 7:
                if args[7].lower() == 'false':
                    useLoopback = False
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )

        if rcvrName.lower() != 'none':
            if rcvrName.lower() == 'local' and mrName.lower() != 'local' or \
               mrName.lower() == 'local' and rcvrName.lower() != 'local':
                self.log.Abort( '', 'Local loopback can only apply to ALL or NONE devices' )

        if useLoopback and serverName.lower() != 'none':
            self.log.Abort( '', 'Cannot use external Media Server with local loopback' )

        if mrName.lower() == 'local':
            if useLoopback:
                loopback = True
            self.soft1 = SoftPlayer.SoftPlayer( aRoom='TestSender', aLoopback=loopback )
            mrName = self.soft1.name.split( ':' )[0] + ':UPnP AV'
            mpName = self.soft1.name
        else:
            mrName = mrName.split( ':' )[0] + ':UPnP AV'
            mpName = mrName.split( ':' )[0] + ':SoftPlayer'

        # get playlist from server
        if serverName.lower() != 'none':
            self.server = Server.MediaServer( serverName )
            if not self.server.device:
                self.log.Abort( serverName, 'Not available' )
            self.playlist = self.server.GetPlaylist( playlistName )
            self.server.Shutdown()
            self.server = None
        else:
            if playlistName.lower() == 'short':
                trackList = kTrackListShort
            else:
                trackList = kTrackListFull
            self.server = HttpServer.HttpServer( kAudioRoot )
            self.server.Start()
            self.playlist = Common.GetTracks( trackList, self.server )
        self.numTracks = len( self.playlist )

        # create sender
        self.sender = OHMP.OhMediaPlayerDevice( mpName, aIsDut=True, aLoopback=loopback )
        self.senderDev = mpName.split( ':' )[0]

        # create receiver and connect to renderer
        if rcvrName.lower() != 'none':
            if rcvrName.lower() == 'local':
                self.soft2 = SoftPlayer.SoftPlayer( aRoom='TestRcvr', aLoopback=loopback )
                rcvrName = self.soft2.name
            self.rcvrDev = rcvrName.split( ':' )[0]
            self.rcvr = OHMP.OhMediaPlayerDevice( rcvrName, aIsDut=True, aLoopback=loopback )
            self.rcvr.receiver.SetSender( self.sender.sender.uri, self.sender.sender.metadata )
            self.rcvr.receiver.Play()

        # create AVT renderer
        self.mr = Renderer.MediaRendererDevice( mrName, aLoopback=loopback )
        self.mrDev = mrName.split( ':' )[0]
        self.mr.avt.AddSubscriber( self._AvtEventCb )
        self.avtState = self.mr.avt.transportState

        # Execute the test loops
        for self.testLoop in range( self.testLoops ):
            self.trackIndex = -1
            self.mr.avt.SetUri( '', '' )
            self._HandleStop()
            self.started = True
            self.eop.clear()
            self.eop.wait()
            self.started = False

    def Cleanup( self ):
        """Perform cleanup on test exit"""
        if self.playTimer:
            self.playTimer.cancel()
        if self.tickTimer:
            self.tickTimer.cancel()
        if self.checkTimer:
            self.checkTimer.cancel()
        if self.mr:
            self.mr.Shutdown()
        if self.sender:
            self.sender.Shutdown()
        if self.rcvr:
            self.rcvr.Shutdown()
        if self.server:
            self.server.Shutdown()
        if self.soft1:
            self.soft1.Shutdown()
        if self.soft2:
            self.soft2.Shutdown()
        BASE.BaseTest.Cleanup( self )

    # noinspection PyUnusedLocal
    def _AvtEventCb( self, service, svName, svVal, svSeq ):
        """Callback from AVTransport Service UPnP events whilst test is running"""
        xml        = ET.fromstring( svVal )[0]
        evAvtState = xml.find( kAvtNs+'TransportState' ).attrib['val']
        toDo       = None

        if evAvtState == 'PLAYING' and self.avtState != 'PLAYING':
            if self.startTimer:
                self.startTimer.cancel()
            toDo = self._HandlePlay
            self.startTime = time.time()
        elif evAvtState in ['STOPPED', 'NO_MEDIA_PRESENT'] and self.avtState not in ['STOPPED', 'NO_MEDIA_PRESENT']:
            toDo = self._HandleStop
            self.stopTime = time.time()
        self.avtState = evAvtState
        t = LogThread.Thread( target=toDo )
        t.start()

    def _HandleStop( self ):
        """Handles state transition to STOPPED - clear timers, perform checks, start next track"""
        self.mutex.acquire()
        if self.startTimer:
            self.startTimer.cancel()
        if self.playTimer:
            self.playTimer.cancel()
        if self.tickTimer:
            self.tickTimer.cancel()
        if self.checkTimer:
            self.checkTimer.cancel()

        self._CheckPlayTime()

        self.trackIndex += 1
        if self.trackIndex >= self.numTracks:
            self.eop.set()
        else:
            self.title = Common.GetTitleFromDidl( self.playlist[self.trackIndex][1] )
            self.log.Header1( '', 'Loop %d of %d: Track %d of %d  (%s)' %
                (self.testLoop+1, self.testLoops, self.trackIndex+1, self.numTracks, self.title))

            self.reportedSecs = 0
            self.startTimer = LogThread.Timer( 5, self._StartTimerCb )
            self.startTimer.start()
            self.mr.avt.SetUri( self.playlist[self.trackIndex][0], self.playlist[self.trackIndex][1] )
            self.mr.avt.Play()
        self.mutex.release()

    def _HandlePlay( self ):
        """Handles state transition to PLAYING - sets up all timers"""
        self.mutex.acquire()
        self.playTimer = LogThread.Timer( self.playTime, self._PlayTimerCb )
        self.checkTimer = LogThread.Timer( 5, self._CheckTimerCb )
        self.tickTimer = LogThread.Timer( 1, self._TickTimerCb )
        self.playTimer.start()
        self.checkTimer.start()
        self.tickTimer.start()
        self.mutex.release()

    def _PlayTimerCb( self ):
        """Callback from playtime timer - skips to next track"""
        self.mutex.acquire()
        posn = self.mr.avt.avt.GetPositionInfo( InstanceID=0 )
        self.reportedSecs = self._ToSecs( posn['RelTime'] )
        self.mr.avt.Stop()
        self.mutex.release()

    def _StartTimerCb( self ):
        """Called on start timer expiry - implies PLAYING state has not been reached"""
        if self.mr.avt.transportState != 'PLAYING':
            self.log.Fail( self.mrDev, 'State %s, expected PLAYING (%s)' % (self.mr.avt.transportState, self.title) )
            self._HandleStop()

    def _CheckTimerCb( self ):
        """Called a few secs into playback to check Info on Sender (and Receiver)"""
        self.mutex.acquire()
        avtDuration = self.mr.avt.currentMediaDuration
        avtUri      = self.mr.avt.avTransportURI
        avtMetadata = self.mr.avt.avTransportURIMetaData.encode( 'utf8' )

        self.log.FailUnless( self.senderDev, avtDuration==self.sender.info.duration,
            'AVT/Sender duration (%s/%s)' % (avtDuration, self.sender.info.duration) )
        self.log.FailUnless( self.senderDev, avtUri==self.sender.info.uri,
            'AVT/Sender URI (%s/%s)' % (avtUri, self.sender.info.uri) )
        self.log.FailUnless( self.senderDev, avtMetadata==self.sender.info.metadata,
            'AVT/Sender metadata (%s/%s)' % (avtUri, self.sender.info.metadata) )

        if self.rcvr:
            self.log.FailUnless( self.rcvrDev, avtDuration==self.rcvr.info.duration,
                'AVT/Receiver duration (%s/%s)' % (avtDuration, self.rcvr.info.duration) )
            self.log.FailUnless( self.rcvrDev, avtUri==self.rcvr.info.uri,
                'AVT/Receiver URI (%s/%s)' % (avtUri, self.rcvr.info.uri) )
            self.log.FailUnless( self.rcvrDev, avtMetadata==self.rcvr.info.metadata,
                'AVT/Receiver metadata (%s/%s)' % (avtMetadata, self.rcvr.info.metadata) )
        self.mutex.release()

    def _TickTimerCb( self ):
        """Called every second during playback to check still playing, time incrementing"""
        self.mutex.acquire()
        avtSecs = 0
        posn = self.mr.avt.avt.GetPositionInfo( InstanceID=0 )
        if posn.has_key( 'RelTime' ):
            self.log.Info( self.senderDev, 'Reported play time: %s' % posn['RelTime'] )
            avtSecs = self._ToSecs( posn['RelTime'] )
        if avtSecs==self.prevAvtSecs:
            self.stuck += 1
        else:
            self.stuck = 0

        if self.stuck > 5:
            self.log.Fail( self.mrDev, 'Playback time not incrementing  (%s)' % self.title )
            self.mutex.release()
            self._HandleStop()
        else:
            if avtSecs > self.reportedSecs:
                self.reportedSecs = avtSecs
            self.prevAvtSecs = avtSecs
            self.tickTimer = LogThread.Timer( 1, self._TickTimerCb )
            self.tickTimer.start()
            self.mutex.release()

    def _CheckPlayTime( self ):
        """Check playback time as expected"""
        if self.started:
            meas = int( self.stopTime-self.startTime )
            if self.playTime and self.playTime < self.mr.avt.currentTrackDuration:
                exp = self.playTime
            elif self.mr.avt.currentTrackDuration > 0:
                exp = self.mr.avt.currentTrackDuration
            else:
                exp = self.playTime
            self.log.CheckLimits( self.mrDev, 'GELE', meas, exp-1, exp+1,
                                  'Measured vs expected playback time  (%s)' % self.title )
            self.log.CheckLimits( self.mrDev, 'GELE', self.reportedSecs, exp-1, exp+1,
                                  'Reported vs expected playback time  (%s)' % self.title )

    @staticmethod
    def _ToSecs( aTime ):
        """Convert string time passed in (hh:mm:ss) to integer seconds"""
        fields = aTime.split( ':' )
        return 3600*int( fields[0] ) + 60*int( fields[1] ) + int( fields[2] )


if __name__ == '__main__':

    BASE.Run( sys.argv )
