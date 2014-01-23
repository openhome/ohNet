#!/usr/bin/env python
"""TestAvTransporttPlayTracks - test Playing of playlists of tracks using AVTransport.

Parameters:
    arg#1 - Device Under Test (AVT Renderer and Sender)
    arg#2 - Device Under Test (Receiver) - optional (None = not present)
    arg#3 - UPnP MediaServer / Web Server to source media
    arg#4 - Playlist name
    arg#5 - Time to play before skipping to next (None = play all)
    arg#6 - Test loops (optional - default 1)    
            
Test test which plays tracks from an M3U playlist sequentially under AVTransport
control (test is acting like an AVT control point). The tracks may be played for
their entirety or any specified length of time
"""

# Differences from DS test:
#    - removed songcast sender mode param - set in softplayer at startup
#    - removed abort threshold param (usage obsolete)
#    - removed ability to use Kinsky as media server
#    - remove .NET XML handling

import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.MediaRenderer as Renderer
import Upnp.ControlPoints.MediaServer   as Server
import Upnp.ControlPoints.Volkano       as Volkano
import Utils.Network.HttpMediaServer    as HttpServer
import Utils.Common                     as Common
import LogThread
import sys
import threading
import time
import xml.etree.ElementTree as ET

kAvtNs = '{urn:schemas-upnp-org:metadata-1-0/AVT/}'


class TestAvTransportPlayTracks( BASE.BaseTest ):
    "Test playing of tracks"

    def __init__( self ):
        " Constructor - initalise base class"
        BASE.BaseTest.__init__( self )

    def Test( self, args ):
        "UPnP device eventing test, with network stressing"
        self.mr               = None
        self.sender           = None
        self.receiver         = None
        self.playlist         = []
        self.trackIndex       = -1
        self.numTracks        = 0
        self.playTime         = None
        self.playTimer        = None
        self.tickTimer        = None
        self.trackPlayTime    = 0
        self.expectedPlayTime = 0
        self.avtState         = None
        self.avtUri           = None
        self.testLoops        = 1
        self.noRelTime        = 0
        self.stuckRelTime     = 0
        self.prevRelTime      = '0:00:00'
        self.abortMsg         = ''
        self.eop              = threading.Event()
        self.playing          = threading.Event()
        self.trackDuration    = threading.Event()
        self.newUri           = threading.Event()
        self.mutex            = threading.Lock()

        try:
            dutName      = args[1]
            receiverName = args[2]
            serverName   = args[3]
            playlistName = args[4]
            if args[5] != 'None':
                self.playTime = int( args[5] )
            if len( args ) > 6:
                self.testLoops = int( args[6] )
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )
            
        if receiverName.lower() == 'none':
           receiverName = None
                   
        if 'MediaRenderer' in dutName:
            senderName = dutName.replace( ':MediaRenderer', '' )
        else:
            senderName = dutName
            dutName += ':MediaRenderer'        

        # get playlist from server
        server = Server.MediaServer( serverName )
        if not server.device:
            self.log.Abort( serverName, 'Not available' )
        self.playlist = server.GetPlaylist( playlistName )
        server.Shutdown()
        self.numTracks = len( self.playlist )

        # create sender
        self.senderDev = senderName.split( ':' )[0]
        self.sender = Volkano.VolkanoDevice( senderName, aIsDut=True )
        
        # create receiver and connect to sender
        if receiverName:
            self.rcvrDev = receiverName.split( ':' )[0]
            self.receiver = Volkano.VolkanoDevice( receiverName, aIsDut=True )
            #time.sleep( 3 )
            self.receiver.receiver.SetSender( self.sender.sender.uri, self.sender.sender.metadata )
            self.receiver.receiver.Play()
                
        # create AVT renderer CP
        self.mr = Renderer.MediaRendererDevice( dutName )
        self.avt = self.mr.avt
        self.avt.Stop()
        self.avt.uri = ''
        self.avt.SetUri( '', '' )
        time.sleep( 5 )
        self.avtState = self.avt.transportState
        for self.testLoop in range( self.testLoops ):
            self.eop.clear()        
            # subscribe to AVT renderer events
            self.avt.AddSubscriber( self._AvtEventCb )
            self._StartNextTrack()
            
            # wait until playback stopped, cleanup and exit
            self.eop.wait()
            self.avt.RemoveSubscriber( self._AvtEventCb )
            if self.tickTimer:
                self.tickTimer.cancel()
                self.tickTimer = None
            if self.playTimer: self.playTimer.cancel()  
            self.trackIndex       = -1
            self.currentPlayTime  = 0
            self.trackPlayTime    = 0
            self.expectedPlayTime = 0
            self.avtState         = None
            self.avtUri           = None
            if self.abortMsg:
                self.log.Abort( self.senderDev, self.abortMsg )
                
    def Cleanup( self ):
        "Perform cleanup on test exit"
        if self.mr: self.mr.Shutdown()
        if self.sender: self.sender.Shutdown()
        if self.receiver: self.receiver.Shutdown()
        BASE.BaseTest.Cleanup( self )
        
    def _AvtEventCb( self, service, svName, svVal, svSeq ):
        "Callback from AVTransport Service UPnP events whilst test is running"
        xml           = ET.fromstring( svVal.encode( 'utf-8' ))[0]  
        evAvtState    = xml.find( kAvtNs+'TransportState' ).attrib['val']
        evTrkDuration = xml.find( kAvtNs+'CurrentTrackDuration' ).attrib['val']
        evAvtUri      = xml.find( kAvtNs+'AVTransportURI' ).attrib['val']
        
        if evAvtState=='PLAYING' and self.avtState != 'PLAYING':
            self.playing.set()
            
        startNext = False
        if evAvtState == 'STOPPED' and self.avtState != 'STOPPED':
            if self.playTimer: self.playTimer.cancel()  
            self._CheckPlayTime()
            startNext = True
            
        self.currentTrackDuration = self.avt.currentMediaDuration
        if self.currentTrackDuration:
            self.trackDuration.set()
            
        if evAvtUri != self.avtUri:
            self.newUri.set()
                
        self.avtUri   = evAvtUri
        self.avtState = evAvtState

        if startNext:
            # chuck onto its own thread to release event handler thread
            t = LogThread.Thread( target=self._StartNextTrack )
            t.start()
                                        
    def _PlayTimerCb( self ):
        "Callback from playtime timer - skips to next track"
        self.mutex.acquire()
        self.avt.Stop()
        self.mutex.release()
        time.sleep(10)
        
    def _StartNextTrack( self ):
        "Start playback of next track - call on a seperate thread"        
        self.trackIndex += 1
        if self.trackIndex >= self.numTracks:
            self.eop.set()
            return
        
        self.log.Info( '' )
        self.log.Info( '', 'Loop %d of %d: Track %d of %d' % 
            (self.testLoop+1, self.testLoops, self.trackIndex+1, self.numTracks))
        self.log.Info( '' )
        self.noRelTime = 0
        self.mutex.acquire()
        
        self.newUri.clear()        
        self.avt.SetUri( self.playlist[self.trackIndex][0], self.playlist[self.trackIndex][1] )
        self.newUri.wait( 3 )
        if not self.newUri.isSet():
            self.mutex.release()
            self._StartNextTrack()
            return
        
        self.trackDuration.clear()
        self.playing.clear()     
        self.avt.Play()
        self.playing.wait( 5 )
        if not self.playing.isSet():
            try:
                title = Common.GetTitleFromDidl( self.playlist[self.trackIndex][1] )
            except:
                title = 'UNKNOWN'
            self.log.Warn( self.senderDev, 'FAILED to Play: %s within 5s' % title ) 
            self.playing.wait( 5 )
            if not self.playing.isSet():
                self.log.Fail( self.senderDev, 'FAILED to Play: %s within 10s' % title ) 
                self.mutex.release()
                self._StartNextTrack()
                return
                
        self.trackDuration.wait( 3 )  # timeout as internet radio has 0 duration
        self.trackPlayTime = 0
        self.expectedPlayTime = self.currentTrackDuration     
            
        if self.playTime != None and self.playTime < self.expectedPlayTime:
            self.expectedPlayTime = self.playTime
            #.... wait for playing (with timeout)
            self.playTimer = LogThread.Timer( self.playTime-0.1, self._PlayTimerCb )
            self.playTimer.start()
            
        self.infoCheckTimer = LogThread.Timer( 7, self._InfoCheckCb )
        self.infoCheckTimer.start()        
                
        if not self.tickTimer:
            # start regular status update (first time thru...)
            self.tickTimer = LogThread.Timer( 0.8, self._TickCb )
            self.tickTimer.start()
            
        self.mutex.release()
        
    def _CheckPlayTime( self ):
        "Verify track played for expected duration (see Trac #1527)"
        if self.expectedPlayTime:
            loLim = self.expectedPlayTime-2 # widened as IPY timer can be 1s short
            hiLim = self.expectedPlayTime+1
            self.log.CheckLimits( self.senderDev, 'GELE', self.trackPlayTime, loLim, hiLim,
                'track play time as expected')
                    
    def _TickCb( self ):
        "One-second tick callback - updates current track elapsed time"
        self.mutex.acquire()
        self.noRelTime += 1
        self.stuckRelTime += 1
        posnInfo = self.avt.avt.GetPositionInfo( InstanceID=0 )
        avtSecs = self._ToSecs( posnInfo['RelTime'] )
        if avtSecs != 0:
            self.noRelTime = 0
            self.log.CheckLimits( self.senderDev, 'GELE', avtSecs,
                 self.sender.time.seconds-1, self.sender.time.seconds+1, 
                '(%d/%d) AVT/Sender seconds' % (avtSecs, self.sender.time.seconds) )
            if self.receiver:
                self.log.CheckLimits( self.senderDev, 'GELE', avtSecs,
                    self.receiver.time.seconds-1, self.receiver.time.seconds+1, 
                    '(%d/%d) AVT/Receiver seconds' % (avtSecs, self.receiver.time.seconds) )
        if avtSecs != self.prevRelTime:
            self.stuckRelTime = 0
                
        if self.noRelTime > 10:
            self.abortMsg = 'No RelTime repeatedly - DUT has died'
        if self.stuckRelTime > 10:
            self.abortMsg = 'RelTime not changing - DUT has died'
        if self.abortMsg:
            # Force exit on main thread (Logger abort problematic on other threads)
            self.mutex.release()
            self.eop.set()
            return
            
        try:
            if avtSecs > self.trackPlayTime:
                self.trackPlayTime = avtSecs
        except:
            pass

        self.prevRelTime = avtSecs
        self.mutex.release()
        self.tickTimer = LogThread.Timer( 0.8, self._TickCb )
        self.tickTimer.start()
                
    def _InfoCheckCb( self ):
        "Called 7s into playback to check Info on Sender and Receiver"
        avtDuration = self.avt.currentMediaDuration
        avtUri      = self.avt.avTransportURI
        avtMetadata = self.avt.avTransportURIMetaData
        
        self.log.FailUnless( self.senderDev, avtDuration==self.sender.info.duration, 
            '(%s/%s) AVT/Sender duration' % (avtDuration, self.sender.info.duration) )
        self.log.FailUnless( self.senderDev, avtUri==self.sender.info.uri, 
            '(%s/%s) AVT/Sender URI' % (avtUri, self.sender.info.uri) )
        self.log.FailUnless( self.senderDev, avtMetadata==self.sender.info.metadata, 
            '(%s/%s) AVT/Sender metadata' % (avtUri, self.sender.info.metadata) )
        
        if self.receiver:
            self.log.FailUnless( self.rcvrDev, avtDuration==self.receiver.info.duration, 
                '(%s/%s) AVT/Receiver duration' % (avtDuration, self.receiver.info.duration) )
            self.log.FailUnless( self.rcvrDev, avtUri==self.receiver.info.uri, 
                '(%s/%s) AVT/Receiver URI' % (avtUri, self.receiver.info.uri) )
            self.log.FailUnless( self.rcvrDev, avtMetadata==self.receiver.info.metadata, 
                '(%s/%s) AVT/Receiver metadata' % (avtMetadata, self.receiver.info.metadata) )
        
    def _ToSecs( self, aTime ):
        "Convert string time passed in (hh:mm:ss) to integer seconds"
        fields = aTime.split( ':' )
        return 3600*int( fields[0] ) + 60*int( fields[1] ) + int( fields[2] )
    
            
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
    