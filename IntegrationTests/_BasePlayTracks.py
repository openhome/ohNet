#!/usr/bin/env python
"""BasePlayTracks - base class to test Playing of playlists of tracks.

Derived classes MUST

    - define self.tracks - the list of tracks to test (URI/Meta tuples)
    - define self.doc - docstring to print on parameter parse failure
    - call Test() method with following params
        - Sender DUT ['local' for internal SoftPlayer on loopback]
        - Receiver DUT ['local' for internal SoftPlayer on loop
        - Time to play before skipping to next (None = play all)
        - Repeat mode [on/off]
        - Shuffle mode [on/off]
        - (optional) dict of options to pass to sender SoftPlayer
"""

import _FunctionalTest
import BaseTest                   as BASE
import Upnp.ControlPoints.Volkano as Volkano
import _SoftPlayer                as SoftPlayer
import LogThread
import os
import random
import sys
import threading
import time

kNotPlayedThreshold = 5     # time in secs between ID events below which assume 'failed to play'


def Run( aArgs ):
    """Pass the Run() call up to the base class"""
    BASE.Run( aArgs )


class BasePlayTracks( BASE.BaseTest ):
    """Base class for XxxPlayTracks tests"""

    def __init__( self ):
        """Constructor - initialise base class"""
        BASE.BaseTest.__init__( self )
        self.doc              = 'Define docstring in derived class'
        self.sender           = None
        self.senderDev        = None
        self.softSender       = None
        self.receiver         = None
        self.receiverDev      = None
        self.softRcvr         = None
        self.playTimer        = None
        self.nextTimer        = None
        self.stateTimer       = None
        self.checkInfoTimer   = None
        self.lastIdTime        = time.time()
        self.tracks           = []
        self.repeat           = 'off'
        self.shuffle          = 'off'
        self.numTrack         = 0
        self.startTime        = 0
        self.playTime         = None
        self.senderPlayTime   = 0
        self.receiverPlayTime = 0
        self.expectedPlayTime = 0
        self.senderPlaying    = threading.Event()
        self.senderStarted    = threading.Event()
        self.senderStopped    = threading.Event()
        self.senderDuration   = threading.Event()
        self.idUpdated        = threading.Event()
        self.multiEv1         = threading.Event()
        self.trackChangeMutex = threading.Lock()
        random.seed()

    def Test( self, args ):
        """Play tracks, using Media services for control"""
        senderName   = ''
        receiverName = ''
        softOptions  = None
        loopback     = False

        try:
            senderName   = args[1]
            receiverName = args[2]
            if str( args[3] ).lower() != 'none':
                self.playTime = int( args[3] )
            if len( args ) > 4:
                self.repeat = args[4]
            if len( args ) > 5:
                self.shuffle = args[5]
            if len( args ) > 6:
                softOptions = args[6]
        except:
            print '\n', self.doc, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )

        if receiverName.lower() == 'none':
            receiverName = None

        if receiverName is not None:
            if receiverName.lower() == 'local' and senderName.lower() != 'local' or \
               senderName.lower() == 'local' and receiverName.lower() != 'local':
                self.log.Abort( '', 'Local loopback can only apply to ALL or NONE devices' )
        if senderName.lower() == 'local':
            loopback = True

        if self.repeat.lower() not in ('off', 'on'):
            self.log.Abort( '', 'Invalid repeat mode %s' % self.repeat )

        if self.shuffle.lower() not in ('off', 'on'):
            self.log.Abort( '', 'Invalid shuffle mode %s' % self.shuffle )

        if self.playTime <= kNotPlayedThreshold:
            self.log.Abort( '', 'Minimum value for time-to-play is %ds' % (kNotPlayedThreshold+1) )

        # start local softplayer(s) as required
        if senderName.lower() == 'local':
            options = {'aRoom':'TestSender', 'aLoopback':loopback}
            if softOptions:
                options.update( softOptions )
            self.softSender = SoftPlayer.SoftPlayer( **options )
            senderName = self.softSender.name
        if receiverName is not None and receiverName.lower() == 'local':
            self.softRcvr = SoftPlayer.SoftPlayer( aRoom='TestRcvr', aLoopback=loopback )
            receiverName = self.softRcvr.name

        # create Sender device an put on random source (catch Volkano #2968, Network #894, #1807)
        self.senderDev = senderName.split( ':' )[0]
        self.sender = Volkano.VolkanoDevice( senderName, aIsDut=True, aLoopback=loopback )
        self.sender.product.sourceIndex = random.randint( 1, self.sender.product.sourceCount-1 )
        self.SenderSetup()
        time.sleep( 3 )

        # create Receiver Device, put onto random source and connect to sender
        if receiverName:
            self.receiverDev = receiverName.split( ':' )[0]
            self.receiver = Volkano.VolkanoDevice( receiverName, aIsDut=True, aLoopback=loopback )
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
        time.sleep( 3 )

        # check the playlist ReadList operation
        self._CheckReadList()

        # subscribe to sender and receiver events
        self.sender.playlist.AddSubscriber( self._SenderPlaylistCb )
        self.sender.time.AddSubscriber( self._SenderTimeCb )
        if receiverName:
            self.receiver.time.AddSubscriber( self._ReceiverTimeCb )
            self.receiver.receiver.AddSubscriber( self._ReceiverReceiverCb )

        # start playback
        self.log.Info( self.senderDev, 'Starting on source %s' % self.sender.product.sourceIndex )
        # self.sender.playlist.Play()
        self.sender.playlist.SeekIndex( 0 )         # <<<============ should be Play but doesn't work
        thread = LogThread.Thread( target=self._TrackChanged )
        thread.start()
        self.senderStopped.clear()
        self.senderStopped.wait()

    def Cleanup( self ):
        """Perform post-test cleanup"""
        if self.checkInfoTimer:
            self.checkInfoTimer.cancel()
        if self.playTimer:
             self.playTimer.cancel()
        if self.nextTimer:
            self.nextTimer.cancel()
        if self.stateTimer:
            self.stateTimer.cancel()
        if self.sender:
            self.sender.Shutdown()
            self.sender = None
        if self.receiver:
            self.receiver.Shutdown()
        BASE.BaseTest.Cleanup( self )

    #
    # 'Virtual' methods which can be defined in derived classes
    #

    def SenderSetup( self ):
        """Template to allow additional setup in derived class if required"""
        pass

    #
    # Track change handling
    #

    def _TrackChanged( self ):
        """Track changed - check results and setup timer for next track"""
        self.numTrack += 1
        self.trackChangeMutex.acquire()
        self._CheckPrevPlay()
        if not self.senderStopped.is_set():
            if self.checkInfoTimer:
                self.checkInfoTimer.cancel()
            self._CheckEop()
            if not self.senderStopped.isSet():
                self._LogTrackHeader( self.sender.playlist.id )
                self._SetupPlayTimer()
                self._StartCheckInfoTimer()
        self.trackChangeMutex.release()

    def _SetupPlayTimer( self ):
        """Setup timer to callback after specified play time"""
        self._WaitForSenderPlay()
        if self.sender:
            if self.sender.playlist.transportState == 'Playing':
                self.startTime = time.time()
                self.expectedPlayTime = self._SenderPlayTime()

                if self.playTime is not None and self.playTime < self.expectedPlayTime:
                    self.expectedPlayTime = self.playTime
                    if self.playTime == 0:
                        self._PlayTimerCb()
                    else:
                        self._StartPlayTimer()

    #
    # Checks
    #

    def _CheckEop( self ):
        """Check End-Of-Playlist handled correctly"""
        if self.repeat=='off' and self.numTrack>len( self.tracks ):
            if not self.senderStopped.isSet():
                self.senderStopped.wait( 3 )
                if not self.senderStopped.isSet():
                    self.log.Fail( self.senderDev, 'No stop on end-of-playlist' )
                    self.senderStopped.set()    # force test exit

    def _CheckInfo( self, aId ):
        """Check sender and receiver info"""
        self.checkInfoTimer = None
        self._CheckSenderInfo( aId )
        if self.receiver:
            self._CheckReceiverInfo()

    def _CheckPrevPlay( self ):
        """Check playback/time of track just completed"""
        currIdTime = time.time()
        if currIdTime-self.lastIdTime < kNotPlayedThreshold:
            # less than Ns between ID events - assume previous track skipped
            self.log.Fail( self.senderDev, 'Track %d did NOT play' % self.numTrack )
        elif self.expectedPlayTime:
            loLim = self.expectedPlayTime-1
            hiLim = self.expectedPlayTime+1
            self.log.CheckLimits( self.senderDev, 'GELE', self.senderPlayTime, loLim, hiLim,
                'reported (by Sender) play time')
            if self.receiver:
                self.log.CheckLimits( self.receiverDev, 'GELE', self.receiverPlayTime, loLim, hiLim,
                    'reported (by Receiver) play time')
            self.log.CheckLimits( '', 'GELE', int( round( time.time()-self.startTime, 0 )),
                loLim, hiLim, 'measured (by test) play time')
        self.lastIdTime = currIdTime

    def _CheckSenderInfo( self, aId ):
        """Check sender info is as expected"""
        if self.senderStarted.isSet():
            dsTrack = self.sender.playlist.TrackInfo( aId )
            if dsTrack:
                (uri,meta) = self.tracks[self.sender.playlist.idArray.index( aId )]
                if dsTrack['Uri'] != uri:
                    self.log.Fail( self.senderDev, 'Sender URI mismatch %s / %s'
                                    % (dsTrack['aUri'], uri) )
                else:
                    self.log.Pass( self.senderDev, 'Sender URI as expected' )

                if dsTrack['Metadata'] != meta:
                    self.log.Fail( self.senderDev, 'Sender metadata mismatch %s / %s'
                                    % (dsTrack['Metadata'], meta) )
                else:
                    self.log.Pass( self.senderDev, 'Sender metadata as expected' )

                self.log.FailUnless( self.senderDev, self.sender.sender.audio,
                    'Sender Audio flag is %s' % self.sender.sender.audio )
                self.log.FailUnless( self.senderDev, self.sender.sender.status == 'Enabled',
                    'Sender Status is %s' % self.sender.sender.status )
            else:
                self.log.Fail( self.senderDev, 'No track data returned' )
                self.senderStopped.set()     # force test exit

    def _CheckReceiverInfo( self ):
        """Check receiver Info matches sender"""
        # called 3s after track change to allow events from both sides to be
        # updated to current values - test skipped if track play time < 10s
        for item in ['bitDepth', 'bitRate', 'codecName', 'duration', 'lossless',
                     'metadata', 'metatext', 'sampleRate', 'uri']:
            itemTitle = item[0].upper()+item[1:]
            senderVal = eval( 'self.sender.info.polled%s' % itemTitle )
            receiverVal = eval( 'self.receiver.info.polled%s' % itemTitle )
            self.log.FailUnless( self.receiverDev, senderVal==receiverVal,
                '(%s/%s) POLLED Sender/Receiver value for %s' %
                (str( senderVal ), str( receiverVal ), item[0].upper()+item[1:] ))

            senderVal = eval( 'self.sender.info.%s' % item )
            receiverVal = eval( 'self.receiver.info.%s' % item )
            self.log.FailUnless( self.receiverDev, senderVal==receiverVal,
                '(%s/%s) EVENTED Sender/Receiver value for %s' %
                (str( senderVal ), str( receiverVal ), itemTitle) )

    def _CheckReadList( self ):
        """Check operation of the Playlist ReadList action"""
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
        for tId in readTracks.keys():
            readUri  = readTracks[tId][0]
            readMeta = readTracks[tId][1]
            try:
                (expUri, expMeta)  = self.tracks[self.sender.playlist.idArray.index( tId )]
            except:
                (expUri, expMeta)  = ('', '')
            expMeta = expMeta.decode( 'utf-8' )
            if readUri is None: readUri = ''
            if readMeta is None: readMeta = ''

            if readUri != expUri:
                fail = True
                self.log.Fail( self.senderDev, 'Actual/Expected URI read from DS %s | %s' % (readUri, expUri) )
            if readMeta != expMeta:
                fail = True
                self.log.Fail( self.senderDev, 'Actual/Expected META read from DS %s | %s' % (readMeta, expMeta) )
        if not fail:
            self.log.Pass( self.senderDev, 'All Playlist ReadList tracks OK' )

    #
    # Timer callbacks
    #

    def _PlayTimerCb( self ):
        """Callback from playtime timer - skips to next track"""
        self.playTimer = None
        # The 'next' timer is needed to stimulate track change code when there
        # has been no track change (same track played twice in a row). It will
        # be cancelled before expiry if an Id event (new track) is received
        # from the Playlist service
        if not self.nextTimer:
            self.nextTimer = LogThread.Timer( 1, self._NextTimerCb )
            self.nextTimer.start()
        self.sender.playlist.Next()

    def _NextTimerCb( self ):
        """Next Timer CB - called on expiry of the 'NextTimer'"""
        # Next timer will call into this 1s after a track change has been
        # forced by the 'Next' action (unless the timer has been cancelled due
        # to receipt of an Id event from the Playlist service). This is to
        # handle cases where the same track is played twice in a row, which
        # causes NO id event to be sent.
        self.nextTimer = None
        self.log.Info( self.senderDev, 'Next track timer triggered track change as no Id event Rx' )
        self._TrackChanged()

    #
    # Sender Event callbacks
    #

    # noinspection PyUnusedLocal
    def _SenderTimeCb( self, service, svName, svVal, svSeq ):
        """Callback from Time Service UPnP events on sender device"""
        if svName == 'Seconds':
            if svVal not in [0,'0']:
                # Ignore 0 reading to work around race at track change giving
                # false (=0) results for play time as this event for next track
                # has already occurred
                self.senderPlayTime = int( svVal )
        elif svName == 'Duration':
            if svVal != 0:
                self.senderDuration.set()

    # noinspection PyUnusedLocal
    def _SenderPlaylistCb( self, service, svName, svVal, svSeq ):
        """Callback from Playlist Service UPnP events on sender device"""
        if svName == 'TransportState':
            self.senderPlaying.clear()
            if self.stateTimer:   # add hysteresis to transport state comparison
                self.stateTimer.cancel()
                self.stateTimer = LogThread.Timer( 3, self._ReceiverStateCb )
                self.stateTimer.start()
            if svVal == 'Stopped':
                self.senderStopped.set()
            elif svVal == 'Playing':
                if self.playTimer:
                    self.log.Info( self.senderDev, 'Re-start Play Timer' )
                    self.startTime = time.time()
                    self._StartPlayTimer()
                    self._StartCheckInfoTimer()
                self.senderPlaying.set()
                self.senderStarted.set()
                self.multiEv1.set()
        elif svName == 'Id':
            if self.nextTimer:
                # cancel timer which is required to trigger the TrackChanged
                # code if NO Id event is received (same track plays 2x in a row)
                self.nextTimer.cancel()
                self.nextTimer = None
            # Run on seperate thread so Playback events not blocked
            if svVal != 0:
                thread = LogThread.Thread( target=self._TrackChanged )
                thread.start()
            self.idUpdated.set()
            self.multiEv1.set()

    #
    # Receiver Event callbacks
    #

    # noinspection PyUnusedLocal
    def _ReceiverTimeCb( self, service, svName, svVal, svSeq ):
        """Callback from Time Service UPnP events on receiver device"""
        if svName == 'Seconds':
            if svVal not in [0,'0']:
                # Ignore 0 reading to work around race at track change giving
                # false (=0) results for play time as this event for next track
                # has already occurred
                self.receiverPlayTime = int( svVal )

    # noinspection PyUnusedLocal
    def _ReceiverReceiverCb( self, service, svName, svVal, svSeq ):
        """Callback from Receiver Service UPnP events on receiver device"""
        if svName == 'TransportState':
            # add hysteresis to transport state comparison
            if self.stateTimer:
                self.stateTimer.cancel()
            self.stateTimer = LogThread.Timer( 3, self._ReceiverStateCb )
            self.stateTimer.start()

    def _ReceiverStateCb( self ):
        """Timer callback from receiver transport state event"""
        senderState = self.sender.playlist.transportState
        receiverState = self.receiver.receiver.transportState
        if receiverState == 'Playing':
            self.log.FailUnless( self.receiverDev, senderState=='Playing',
                '(%s/%s) sender/receiver Transport State' % (senderState, receiverState) )
        elif receiverState == 'Waiting':
            self.log.FailIf( self.receiverDev, senderState=='Playing',
                '(%s/%s) sender/receiver Transport State' % (senderState, receiverState) )

    #
    # Utilities
    #

    def _LogTrackHeader( self, aPlId ):
        """Log the header for the next track"""
        if self.repeat=='off' and self.numTrack<=len( self.tracks ):
            if not self.senderStopped.isSet():
                plIndex = self.sender.playlist.PlaylistIndex( aPlId )
                self.log.Header1( '', 'Track %d (Playlist #%d) Rpt->%s Shfl->%s' % \
                    (self.numTrack, plIndex+1, self.repeat, self.shuffle) )


    def _SenderPlayTime( self ):
        """Return track duration reported by sender (with a retry...)"""
        self.senderDuration.clear()
        duration = self.sender.time.duration
        if duration == 0:
            self.senderDuration.wait( 3 )
            if self.senderDuration.is_set():
                duration = self.sender.time.duration
        if duration == 0:
            self.log.Fail( self.senderDev, 'No evented duration for track %d' % self.numTrack )
        return duration

    def _WaitForSenderPlay( self ):
        """Wait for sender playback, warn on slow startup"""
        timeout = False
        start = time.time()
        self.idUpdated.clear()
        self.multiEv1.clear()

        time.sleep( 0.1 )       # allow for delay in buffering event between tracks
        if self.sender.playlist.transportState != 'Playing':
            self.multiEv1.wait( 10 )        # wait for 'Playing', new track ID or timeout
            if not self.multiEv1.is_set():
                timeout = True

        if timeout:
            self.log.Fail( self.senderDev, 'Track %d did NOT play' % (self.numTrack-1) )
            self.sender.playlist.Next()
        elif self.idUpdated.is_set():
            pass
        elif self.sender.playlist.transportState == 'Playing':
            delay = time.time()-start
            if delay > 1:
                self.log.Warn( self.senderDev, 'Slow startup of track playback (%.2fs)' % delay )

    def _StartPlayTimer( self ):
        """Start timer used to control playback time"""
        if self.playTimer:
            self.playTimer.cancel()
            self.playTimer = None
        timed = self.playTime - ( time.time() - self.startTime )
        self.playTimer = LogThread.Timer( timed, self._PlayTimerCb )
        self.playTimer.start()
        self.log.Info( self.senderDev, 'Start Play Timer for %4.2fs' % timed )

    def _StartCheckInfoTimer( self ):
        """Start timer used to delay checking of playback info"""
        if self.checkInfoTimer:
            self.checkInfoTimer.cancel()
        self.checkInfoTimer = LogThread.Timer( 3, self._CheckInfo, args=[self.sender.playlist.id] )
        self.checkInfoTimer.start()
        self.log.Info( self.senderDev, 'Start CheckInfo Timer' )
