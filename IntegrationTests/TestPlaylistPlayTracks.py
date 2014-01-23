#!/usr/bin/env python
"""TestPlaylistPlayTracks - test Playing of playlists of tracks.

Parameters:
    arg#1 - Device Under Test (Sender)
    arg#2 - Device Under Test (Receiver) - optional (None = not present)
    arg#3 - Media server to source media from
    arg#4 - Playlist name
    arg#5 - Time to play before skipping to next (None = play all)
    arg#6 - Repeat mode [on/off] (optional - default off)
    arg#7 - Shuffle mode [on/off] - (optional - default off)
            
Test test which plays tracks from a playlist sequentially. The tracks may be
played for their entirety or any specified length of time. Repeat and shuffle
modes may be selected
"""

# Differences from DS test:
#    - removed songcast sender mode param - set in softplayer at startup
#    - removed abort threshold param (usage obsolete)

import _FunctionalTest
import BaseTest                       as BASE
import Upnp.ControlPoints.Volkano     as Volkano
import Upnp.ControlPoints.MediaServer as Server
import Utils.Common                   as Common
import LogThread
import os
import random
import sys
import threading
import time


class TestPlaylistPlayTracks( BASE.BaseTest ):
    "Test playing of tracks"

    def __init__( self ):
        " Constructor - initalise base class"
        BASE.BaseTest.__init__( self )
        self.sender           = None
        self.receiver         = None
        self.server           = None
        self.playTimer        = None
        self.nextTimer        = None

    def Test( self, args ):
        "Play tracks, using Media services for control"
        self.meta             = ''
        self.tracks           = []
        self.repeat           = 'off'
        self.shuffle          = 'off'
        self.numTrack         = 0
        self.startTime        = 0
        self.playTime         = None
        self.senderPlayTime   = 0
        self.receiverPlayTime = 0
        self.expectedPlayTime = 0
        self.playTimer        = None
        self.playActioned     = False
        self.senderPlayed     = False
        self.stateTimer       = None
        self.senderPlaying    = threading.Event()
        self.senderStarted    = threading.Event()
        self.senderStopped    = threading.Event()
        self.senderDuration   = threading.Event()
        self.playTimerMutex   = threading.Lock()

        try:
            senderName   = args[1]
            receiverName = args[2]
            serverName   = args[3]
            playlistName = args[4]
            if args[5] != 'None':
                self.playTime = int( args[5] )
            if len( args ) > 6:
                self.repeat = args[6]
            if len( args ) > 7:
                self.shuffle = args[7]
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )
            
        if receiverName.lower() == 'none':
           receiverName = None 
            
        if self.repeat.lower() not in ('off', 'on'):
            self.log.Abort( '', 'Invalid repeat mode %s' % self.repeat )
            
        if self.shuffle.lower() not in ('off', 'on'):
            self.log.Abort( '', 'Invalid shuffle mode %s' % self.shuffle )
            
        # get playlist from server
        self.server = Server.MediaServer( serverName )
        if not self.server.device:
            self.log.Abort( serverName, 'Not available' )
        self.tracks = self.server.GetPlaylist( playlistName )
        self.server.Shutdown()
        self.server = None

        # create Sender device add subscribe to events
        self.senderDev = senderName.split( ':' )[0]
        self.sender = Volkano.VolkanoDevice( senderName, aIsDut=True )
        self.sender.playlist.AddSubscriber( self._SenderPlaylistCb )
        self.sender.time.AddSubscriber( self._SenderTimeCb )
        self.sender.info.AddSubscriber( self._SenderInfoCb )
                
        # Put sender onto random source before starting playback (catch #2968) 
        self.sender.product.sourceIndex = random.randint( 0, self.sender.product.sourceCount-1 )
        time.sleep( 3 )
        
        # create Receiver Device, put onto random source and connect to sender
        if receiverName:
            self.rcvrDev = receiverName.split( ':' )[0]
            self.receiver = Volkano.VolkanoDevice( receiverName, aIsDut=True )
            self.receiver.time.AddSubscriber( self._ReceiverTimeCb )
            self.receiver.receiver.AddSubscriber( self._ReceiverReceiverCb )
            self.receiver.product.sourceIndex = random.randint( 0, self.receiver.product.sourceCount-1 )
            time.sleep( 3 )
            self.receiver.receiver.SetSender( self.sender.sender.uri, self.sender.sender.metadata )
            self.receiver.receiver.Play()
        
        # add and verify playlist and set playback mode
        self.senderStopped.clear()        
        self.sender.playlist.DeleteAllTracks()
        self.sender.playlist.repeat = self.repeat
        self.sender.playlist.shuffle = self.shuffle
        self.sender.playlist.AddPlaylist( self.tracks )
        
        # check the playlist ReadList operation
        self._CheckReadList()
            
        # start playback
        self.senderPlaying.clear()
        self.sender.playlist.SeekIndex( 0 )
        self.sender.playlist.Play()
        self.playActioned = True
        
        # wait until playback stopped
        self.senderStopped.clear()        
        self.senderStopped.wait()
        
    def Cleanup( self ):
        "Perform post-test cleanup" 
        if self.playTimer:
             self.playTimer.cancel()
        if self.server:
            self.server.Shutdown()
        if self.sender: 
            self.sender.time.RemoveSubscriber( self._SenderTimeCb )
            self.sender.playlist.RemoveSubscriber( self._SenderPlaylistCb )
            time.sleep( 1 )
            self.sender.Shutdown()
        if self.receiver: 
            self.receiver.time.RemoveSubscriber( self._ReceiverTimeCb )
            self.receiver.receiver.RemoveSubscriber( self._ReceiverReceiverCb )
            self.receiver.Shutdown() 
        BASE.BaseTest.Cleanup( self )               
        
    def _SenderTimeCb( self, service, svName, svVal, svSeq ):
        "Callback from Time Service UPnP events on sender device"
        if svName == 'Seconds':
            if svVal not in [0,'0']:
                # Ignore 0 reading to work around race at track change giving
                # false (=0) results for play time as this event for next track
                # has already occurred
                self.senderPlayTime = int( svVal )
                                
    def _SenderInfoCb( self, service, svName, svVal, svSeq ):
        "Callback from Time Service UPnP events on sender device"
        if svName == 'Duration':
            if svVal != 0:
                self.senderDuration.set()
                
    def _SenderPlaylistCb( self, service, svName, svVal, svSeq ):
        "Callback from Playlist Service UPnP events on sender device"
        if svName == 'TransportState':
            self.senderPlaying.clear()
            if self.stateTimer:   # add hysteresis to transport state comparison
                self.stateTimer.cancel()
                self.stateTimer = LogThread.Timer( 3, self._ReceiverStateCb )
                self.stateTimer.start()
            if svVal == 'Stopped':
                if self.playActioned:
                    self.senderStopped.set()
            elif svVal == 'Playing':
                self.senderPlaying.set()
                if self.playActioned:
                    self.senderStarted.set()
                    self.senderPlayed = True
        elif svName == 'Id':
            if self.nextTimer:
                # cancel timer which is required to trigger the TrackChanged
                # code if NO Id event is received (same track plays 2x in a row)
                self.nextTimer.cancel()
                self.nextTimer = None
            self._TrackChanged( int( svVal) )
            
    def _TrackChanged( self, aId ):
        "Track changed - check results and setup timer for next track"            
        if aId>0:
            if self.senderPlayed:
                self._CheckPlayTime()
            else:
                if self.senderStarted.isSet():
                    if self.meta:
                        title = Common.GetTitleFromDidl( aTrack[1] )
                        self.log.Fail( self.senderDev, 'FAILED to play track %s' % title )
                    else:
                        self.log.Fail( self.senderDev, 'FAILED to play track' )
                
            if self.senderStarted.isSet():
                dsTrack = self.sender.playlist.TrackInfo( aId )
                (uri,self.meta) = self.tracks[self.sender.playlist.idArray.index( aId )]
                if dsTrack['Uri'] != uri:
                    self.log.Fail( self.senderDev, 'Sender URI mismatch %s / %s'
                                    % (dsTrack['aUri'], uri) )
                else:
                    self.log.Pass( self.senderDev, 'Sender URI as expected' )
                
                if os.name == 'posix':
                    # clean up 'screwed up' unicode escaping in Linux
                    dsTrack['Metadata'] = dsTrack['Metadata'].replace( '\\', '' )
                    self.meta = self.meta.replace( '\\', '' )
                if dsTrack['Metadata'] != self.meta:
                    self.log.Fail( self.senderDev, 'Sender metadata mismatch %s / %s'
                                    % (dsTrack['Metadata'], self.meta) )
                else:
                    self.log.Pass( self.senderDev, 'Sender metadata as expected' )
                    
                self.log.FailUnless( self.senderDev, self.sender.sender.audio, 
                    'Sender Audio flag is %s' % self.sender.sender.audio )
                self.log.FailUnless( self.senderDev, self.sender.sender.status == 'Enabled', 
                    'Sender Status is %s' % self.sender.sender.status )                         
                    
            if not self.senderStopped.isSet():
                self.numTrack += 1
                if self.sender.playlist.transportState != 'Playing':
                    self.senderPlayed = False
                th = LogThread.Thread( target=self._SetupPlayTimer )
                th.start() # on its own thread as depends on DS events

    def _ReceiverTimeCb( self, service, svName, svVal, svSeq ):
        "Callback from Time Service UPnP events on receiver device"
        if svName == 'Seconds':
            if svVal not in [0,'0']:
                # Ignore 0 reading to work around race at track change giving
                # false (=0) results for play time as this event for next track
                # has already occurred
                self.receiverPlayTime = int( svVal )
                
    def _ReceiverReceiverCb( self, service, svName, svVal, svSeq ):
        "Callback from Receiver Service UPnP events on receiver device"
        if self.playActioned:
            if svName == 'TransportState':
                # add hysteresis to transport state comparison
                if self.stateTimer:
                    self.stateTimer.cancel()
                self.stateTimer = LogThread.Timer( 3, self._ReceiverStateCb )
                self.stateTimer.start()
            
    def _ReceiverStateCb( self ):
        "Timer callback from receiver transport state event"
        senderState = self.sender.playlist.transportState
        receiverState = self.receiver.receiver.transportState
        if receiverState == 'Playing':
            self.log .FailUnless( senderState=='Playing',
                '(%s/%s) sender/receiver Transport State' % (senderState, receiverState) )
        elif receiverState == 'Waiting':  
            self.log .FailIf( senderState=='Playing',
                '(%s/%s) sender/receiver Transport State' % (senderState, receiverState) )
                
    def _SetupPlayTimer( self ):
        "Setup timer to callback after specified play time"
        plIndex = self.sender.playlist.PlaylistIndex( self.sender.playlist.id )
        self.log.Info( '' )
        self.log.Info( '', '----------------------------------------' )
        self.log.Info( '', 'Track %d (Playlist #%d) Rpt->%s Shfl->%s' % \
            (self.numTrack, plIndex+1, self.repeat, self.shuffle) )
        self.log.Info( '', '----------------------------------------' )
        self.log.Info( '' )
        self.senderStarted.wait()
        self.senderPlaying.wait()
        self.startTime = time.time()
        self.senderDuration.clear()
        self.expectedPlayTime = self.sender.info.duration
        if self.expectedPlayTime == 0:
            self.senderDuration.wait( 2 )
            if self.senderDuration.is_set():
                self.expectedPlayTime = self.sender.info.duration
            else:
                self.log.Fail( self.senderDev, 'No evented duration for track %d' % self.numTrack )
        if self.playTime != None and self.playTime < self.expectedPlayTime:
            self.expectedPlayTime = self.playTime
            if self.playTime == 0:
                self._PlayTimerCb()
            else:
                self.playTimerMutex.acquire()
                if self.playTimer:
                    self.playTimer.cancel()
                self.playTimer = LogThread.Timer(
                    self.playTime-(time.time()-self.startTime), self._PlayTimerCb )
                self.playTimer.start()
                self.playTimerMutex.release()
        if self.receiver:
            if self.expectedPlayTime > 9:
                self.checkInfoTimer = LogThread.Timer( 3, self._CheckReceiverInfo )
                self.checkInfoTimer.start()
        else:
            # The 'next' timer is needed to stimulate track change code when there
            # has been no track change (same track played twice in a row). This
            # be cancelled before expiry if an Id event (new track) is received
            # from the Playlist service. This case is where same track played 
            # twice in a row, and no PlayTimer set 
            self.nextTimer = LogThread.Timer( self.sender.info.duration+1, self._NextTimerCb )
            self.nextTimer.start()
        
    def _PlayTimerCb( self ):
        "Callback from playtime timer - skips to next track"
        self.sender.playlist.Next()
        # The 'next' timer is needed to stimulate track change code when there
        # has been no track change (same track played twice in a row). It will
        # be cancelled before expiry if an Id event (new track) is received
        # from the Playlist service 
        self.nextTimer = LogThread.Timer( 1, self._NextTimerCb )
        self.nextTimer.start()
        
    def _NextTimerCb( self ):
        "Next Timer CB - called on expiry of th e 'NextTimer'"
        # Next timer will call into this 1s after a track change has been
        # forced by the 'Next' action (unless the timer has been cancelled due
        # to receipt of an Id event from the Playlist service). This is to 
        # handle cases where the same track is played twice in a row, which
        # causes NO id event to be sent.
        self.log.Info( self.senderDev, 'Next track timer triggered track change as no Id event Rx' ) 
        self._TrackChanged( self.sender.playlist.id )

    def _CheckPlayTime( self ):
        "Verify track played for expected duration (see Trac #1527)"
        if self.expectedPlayTime:
            loLim = self.expectedPlayTime-1
            hiLim = self.expectedPlayTime+1
            self.log.CheckLimits( self.senderDev, 'GELE', self.senderPlayTime, loLim, hiLim,
                'reported (by Sender) play time')
            if self.receiver:
                self.log.CheckLimits( self.rcvrDev, 'GELE', self.receiverPlayTime, loLim, hiLim,
                    'reported (by Receiver) play time')
            self.log.CheckLimits( '', 'GELE', int( round( time.time()-self.startTime, 0 )),
                loLim, hiLim, 'measured (by test) play time')
            
    def _CheckReadList( self ):
        "Check operation of the (Cara) Playlist ReadList action"
        # Test ReadList using a random population sample from the entire current
        # IDArray, and randomly append a (probably) invalid ID to this test list
        fail        = False
        totalTracks = len( self.sender.playlist.idArray )
        numTracks   = random.randint( 0, totalTracks )
        ids         = random.sample( self.sender.playlist.idArray, numTracks )       
        if random.randint( 0, 1 ):
            numTracks += 1
            totalTracks += 1
            ids.append( 9876543 )
            
        self.log.Info( self.senderDev, 'Checking ReadList on %d random tracks from %d' % 
            (numTracks, totalTracks) )
        
        readTracks = self.sender.playlist.TracksInfo( ids )
        for id in readTracks.keys():
            readUri  = readTracks[id][0]
            readMeta = readTracks[id][1]
            try:
                (expUri, expMeta)  = self.tracks[self.sender.playlist.idArray.index( id )]
            except:
                (expUri, expMeta)  = ('', '')
            if os.name == 'posix':
                # clean up 'screwed up' unicode escaping in Linux
                readMeta = readMeta.replace( '\\', '' )
                expMeta  = expMeta.replace( '\\', '' )
                
            if( readUri != expUri ):
                fail = True
                self.log.Fail( self.senderDev, 'Actual/Expected URI read from DS %s | %s' % 
                               (readUri, expUri) )
            if( readMeta != expMeta ):
                fail = True
                self.log.Fail( self.senderDev, 'Actual/Expected META read from DS %s | %s' % 
                               (readMeta, expMeta) )
        if not fail:
            self.log.Pass( self.senderDev, 'All Playlist ReadList tracks OK' )

    def _CheckReceiverInfo( self ):
        "Check receiver Info matches sender"
        # called 3s after track change to allow events from both sides to be
        # updated to current values - test skipped if track play time < 10s
        for item in ['bitDepth', 'bitRate', 'codecName', 'duration', 'lossless',
                     'metadata', 'metatext', 'sampleRate', 'uri']:
            itemTitle = item[0].upper()+item[1:]
            senderVal = eval( 'self.sender.info.polled%s' % itemTitle )
            receiverVal = eval( 'self.receiver.info.polled%s' % itemTitle )
            self.log.FailUnless( self.rcvrDev, senderVal==receiverVal, 
                '(%s/%s) POLLED Sender/Receiver value for %s' % 
                (str( senderVal ), str( receiverVal ), item[0].upper()+item[1:] ))
            
            senderVal = eval( 'self.sender.info.%s' % item )
            receiverVal = eval( 'self.receiver.info.%s' % item )
            self.log.FailUnless( self.rcvrDev, senderVal==receiverVal, 
                '(%s/%s) EVENTED Sender/Receiver value for %s' % 
                (str( senderVal ), str( receiverVal ), itemTitle) )
        
            
            
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
    