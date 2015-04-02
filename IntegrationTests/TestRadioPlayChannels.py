#!/usr/bin/env python
"""TestRadioPlayChannels - test playback of Radio (using Radio service)

Parameters:
    arg#1 - DUT Sender ['local' for internal SoftPlayer on loopback]
    arg#2 - DUT Receiver ['local' for internal SoftPlayer on loopback] - optional (None = not present)
    arg#3 - Radiotime username
    arg#4 - Time to play before skipping to next channel (None = indefinite)
    arg#5 - Shuffle mode [on/off] (optional - default off)
    arg#6 - Test loops (optional - default 1)
"""
import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.OhMediaPlayer as OHMP
import Utils.Common                     as Common
import _SoftPlayer                      as SoftPlayer
import LogThread
import copy
import os
import random
import sys
import threading
import time


class TestRadioPlayChannels( BASE.BaseTest ):
    """Test playback of radio channels"""

    def __init__( self ):
        """Constructor - initialise base class"""
        BASE.BaseTest.__init__( self )
        self.sender           = None
        self.senderDev        = None
        self.receiver         = None
        self.rcvrDev          = None
        self.soft1            = None
        self.soft2            = None
        self.playTimer        = None
        self.stateTimer       = None
        self.checkTimer       = None
        self.startTime        = 0
        self.channels         = []
        self.title            = ""
        self.metatextUpdated  = False
        self.receiverStarted  = False
        self.idUpdated        = threading.Event()
        self.uriUpdated       = threading.Event()
        self.metaUpdated      = threading.Event()
        self.idArrayUpdated   = threading.Event()
        self.isPlaying        = threading.Event()
        self.isStopped        = threading.Event()
        self.playTimerExpired = threading.Event()
        self.lock             = threading.Lock()

    def Test( self, aArgs ):
        """Play radio channels, using Radio service for control"""
        senderName   = None
        receiverName = None
        tuneInUser   = None
        playTime     = None
        loops        = 1
        shuffle      = False
        loopback     = False

        try:
            senderName   = aArgs[1]
            receiverName = aArgs[2]
            tuneInUser   = aArgs[3]
            if aArgs[4] != 'None':
                playTime = int( aArgs[4] )
            if len( aArgs ) > 5:
                if aArgs[5].lower() == 'on':
                    shuffle = True
            if len( aArgs ) > 6:
                loops = int( aArgs[6] )
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( aArgs )) )

        if receiverName.lower() != 'none':
            if receiverName.lower() == 'local' and senderName.lower() != 'local' or \
               senderName.lower() == 'local' and receiverName.lower() != 'local':
                self.log.Abort( '', 'Local loopback can only apply to ALL or NONE devices' )
        if senderName.lower() == 'local':
            loopback = True

        # configure sender and receiver
        self._SetupSender( senderName, tuneInUser, loopback )
        if receiverName.lower() != 'none':
            self._SetupReceiver( receiverName, loopback )

        # repeat test for requested number of loops
        for loop in range( loops ):
            loopMsg      = 'Loop %d of %d' % (loop+1, loops)
            testChannels = self._GetTestChannels( shuffle )
            numChannels  = len( testChannels )
            chanNum      = 0
            self.idArrayUpdated.clear()            
            
            # clear existing channel info
            self.uriUpdated.clear()
            self.sender.radio.SetChannel( 'Empty', 'Empty' )
            self.uriUpdated.wait( 5 )

            # loop thru all the test channels (already randomised if requested)
            for channel in testChannels:
                chanNum += 1
                testMsg = 'Channel %d of %d' % (chanNum, numChannels)

                if self.idArrayUpdated.isSet():
                    self.log.Warn( self.senderDev, 'Presets updated - exiting test loop' )
                    break

                if not channel[1]:
                    self.log.Info( self.senderDev, '%s: No Channel Data -> skipping' % testMsg )
                    continue

                # extract channel info and log test header
                title = Common.GetTitleFromDidl( channel[1] )
                uri = Common.GetUriFromDidl( channel[1] )
                self.log.Header1( '', '%s: %s - %s' % (loopMsg, testMsg, title.decode( 'utf8' )) )

                # select the channel, check selected correctly
                if not self._SelectChannel( uri, channel ):
                    self.log.Warn( self.senderDev, 'Channel select error - skip playback' )
                    continue

                # start playback
                self._StartPlayback( title )
                self.startTime = time.time()

                # log 'now playing' info, set and wait for playback timer
                if self.sender.radio.transportState == 'Playing':
                    self.checkTimer = LogThread.Timer( 4, self._CheckTimerCb )
                    self.checkTimer.start()
                    if playTime:
                        self.playTimerExpired.clear()
                        self.playTimer = LogThread.Timer( playTime, self._PlayTimerCb )
                        self.playTimer.start()
                        self.playTimerExpired.wait()

                        if self.sender.radio.transportState == 'Playing':
                            self.log.Pass( self.senderDev, 'Completed playback of %s' % title )
                            measTime = int( time.time()-self.startTime )
                            evtTime = self.sender.time.seconds
                            self.log.CheckLimits( self.senderDev, 'GELE', evtTime, measTime-1, measTime+1, 'Evented/Measured playback time' )
                            self.log.CheckLimits( self.senderDev, 'GELE', playTime, measTime-1, measTime+1, 'Requested/Measured playback time' )

                        if self.sender.radio.transportState != 'Stopped':
                            self.isStopped.clear()
                            self.sender.radio.Stop()
                            self.isStopped.wait( 5 )
                    else:
                        # wait until radio channel itself disconnects
                        self.isStopped.wait()

                    if self.checkTimer:
                        self.checkTimer.cancel()

    def Cleanup( self ):
        """Perform post-test cleanup"""
        self.log.Info( '', 'Cleaning Up' )
        if self.playTimer:
            self.playTimer.cancel()
        if self.stateTimer:
            self.stateTimer.cancel()
        if self.checkTimer:
            self.checkTimer.cancel()
        if self.sender:
            self.sender.Shutdown()
        if self.receiver:
            self.receiver.Shutdown()
        if self.soft2:
            self.soft2.Shutdown()
        if self.soft1:
            self.soft1.Shutdown()
        BASE.BaseTest.Cleanup( self )

    def _SetupSender( self, aName, aTuneInUser, aLoopback ):
        """Create sender, select radio, setup TuneIn account, subscribe to events"""
        if aName.lower() == 'local':
            tuneInId=self.config.Get( 'tunein.partnerid' )
            self.soft1 = SoftPlayer.SoftPlayer( aRoom='TestSender', aTuneInId=tuneInId, aLoopback=aLoopback )
            aName = self.soft1.name

        self.senderDev = aName.split( ':' )[0]
        self.sender = OHMP.OhMediaPlayerDevice( aName, aIsDut=True, aLoopback=aLoopback )
        self.sender.config.SetValue( 'Radio.TuneInUserName', aTuneInUser )
        self.sender.product.sourceIndexByName = 'Radio'

        self.idArrayUpdated.clear()
        self.sender.radio.AddSubscriber( self._RadioEventCb )
        self.sender.info.AddSubscriber( self._InfoEventCb )
        self.idArrayUpdated.wait( 5 )
        self.channels = self.sender.radio.ChannelsInfo( self.sender.radio.idArray )

    def _SetupReceiver( self, aName, aLoopback ):
        """Create receiver, set as songcast receiver on the sender, subscribe to events"""
        if aName.lower() == 'local':
            self.soft2 = SoftPlayer.SoftPlayer( aRoom='TestRcvr', aLoopback=aLoopback )
            aName = self.soft2.name
        self.rcvrDev = aName.split( ':' )[0]
        self.receiver = OHMP.OhMediaPlayerDevice( aName, aIsDut=True, aLoopback=aLoopback )
        self.receiver.receiver.AddSubscriber( self._ReceiverEventCb )
        time.sleep( 3 )
        self.receiver.receiver.SetSender( self.sender.sender.uri, self.sender.sender.metadata )
        self.receiver.receiver.Play()

    def _GetTestChannels( self, aShuffle ):
        """Return ordered channel list for use in test loop"""
        channels = copy.deepcopy( self.channels )
        testChannels = []
        while len( channels ):
            if aShuffle:
                rand = random.randint( 0, len( channels )-1 )
                channel = channels.pop( rand )
            else:
                channel = channels.pop( 0 )
            if channel != ('',''):
                testChannels.append( channel )
        return testChannels

    def _SelectChannel( self, aUri, aChannel ):
        """Select radio channel, check it selects and updates status"""
        self.idUpdated.clear()
        self.uriUpdated.clear()
        self.metaUpdated.clear()
        self.isStopped.clear()
        self.sender.radio.SetId( aChannel[0], aUri )

        self.uriUpdated.wait( 5 )
        self.metaUpdated.wait( 0.1 )
        self.idUpdated.wait( 0.1 )
        time.sleep( 1 )

        # check evented information after channel updates
        failed = False
        if not self.uriUpdated.isSet():
            self.log.Warn( self.senderDev, 'No Sender URI update after channel change' )
            
        if self.sender.radio.uri != aUri:
            self.log.Fail( self.senderDev, '(%s/%s) Actual/Expected Sender URI' % 
                (self.sender.radio.uri,aUri) )
            failed = True
        else:
            self.log.Pass( self.senderDev, 'Sender URI as expected %s' % aUri )
            
        if not self.metaUpdated.isSet():
            self.log.Fail( self.senderDev, 'No Sender Metadata update after channel change' )
            failed = True 
        elif self.sender.radio.metadata != aChannel[1]:
            self.log.Fail( self.senderDev, '(%s/%s) Actual/Expected Sender Metadata' %
                (self.sender.radio.metadata,aChannel[1]) )
        else:
            self.log.Pass( self.senderDev, 'Sender Metadata as expected %s' % aChannel[1] )
            
        if not self.idUpdated.isSet():
            self.log.Fail( self.senderDev, 'No Sender ID update after channel change' )
            failed = True
        elif int( self.sender.radio.id ) != aChannel[0]:
            self.log.Fail( self.senderDev, '(%s/%s) Actual/Expected Sender ID' % 
                (self.sender.radio.id,aChannel[0]) )
            failed = True
        else:
            self.log.Pass( self.senderDev, 'Sender ID as expected %s' % aChannel[0] )
            
        if self.sender.sender.status != 'Enabled':
            self.log.Fail( self.senderDev, '(%s/Enabled) Actual/Expected Sender status' % self.sender.sender.status )
            failed = True
        else:                 
            self.log.Pass( self.senderDev, 'Sender status as expected %s' % self.sender.sender.status )
            
        return not failed
    
    def _StartPlayback( self, aTitle ):
        """Start playback, wait for playing state (or error)"""
        self.title = aTitle
        self.metatextUpdated = False
        if self.sender.radio.transportState != 'Playing':
            self.isPlaying.clear()
            self.sender.radio.Play()
            self.isPlaying.wait( 10 )

        if 'Not Supported' in aTitle or 'Not Available' in aTitle:
            if not self.isPlaying.isSet():
                self.log.Pass( self.senderDev, 'FAILED playback of %s (as expected)' % aTitle )
            else:
                self.log.Warn( self.senderDev, 'STARTED playback of %s (unexpectedly)' % aTitle )
        else:
            if not self.isPlaying.isSet():
                self.log.Warn( self.senderDev, 'FAILED to start playback of %s' % aTitle )
            else:
                self.log.Pass( self.senderDev, 'STARTED playback of %s' % aTitle )

    # noinspection PyUnusedLocal
    def _RadioEventCb( self, aService, aSvName, aSvVal, aSvSeq ):
        """Callback from Radio Service UPnP events"""
        if aSvName == 'IdArray':
            self.channels = self.sender.radio.ChannelsInfo( self.sender.radio.idArray )
            self.idArrayUpdated.set()
        elif aSvName == 'TransportState':
            if self.stateTimer:
                self._RestartStateTimer()   # Add 2s 'hysteresis' to TransportState check
            if aSvVal == 'Playing':
                self.isStopped.clear()
                self.isPlaying.set()
                self.startTime = time.time()
            elif aSvVal == 'Buffering':
                if self.playTimer:
                    self.playTimer.cancel()
                    self.playTimer = None
                    self.playTimerExpired.set()
                    self.log.Fail( self.senderDev, 'Playback of %s gone buffering' % self.title )
                self.isPlaying.clear()
                self.isStopped.clear()
            elif aSvVal == 'Stopped':
                if self.playTimer:
                    self.playTimer.cancel()
                    self.playTimer = None
                    self.playTimerExpired.set()
                    self.log.Fail( self.senderDev, 'Playback of %s stopped unexpectedly' % self.title )
                self.isPlaying.clear()
                self.isStopped.set()
        elif aSvName == 'Id':
            self.idUpdated.set()
        elif aSvName == 'Uri':
            self.uriUpdated.set()
        elif aSvName == 'Metadata':
            self.metaUpdated.set()
            
    # noinspection PyUnusedLocal
    def _InfoEventCb( self, aService, aSvName, aSvVal, aSvSeq ):
        """Callback from Info service UPnP events"""
        if aSvName == 'Metatext':
            self.metatextUpdated = True
                
    def _PlayTimerCb( self ):
        """Callback from timer"""
        self.playTimerExpired.set()
        self.playTimer = None
        
    def _CheckTimerCb( self ):
        """Callback from timer - perform checks during radio playback"""
        if self.metatextUpdated:
            self.log.Pass( self.senderDev, 'Metatext present:- %s' % self.sender.info.metatext )
        else:
            self.log.Warn( self.senderDev, 'No metatext' )
            
        if self.sender.radio.transportState == 'Playing':
            self.log.FailUnless( self.senderDev, self.sender.sender.audio, 
                'Sender audio flag %s whilst playing' % self.sender.sender.audio )
        else:
            self.log.FailIf( self.senderDev, self.sender.sender.audio, 
                'Sender audio flag %s whilst not playing' % self.sender.sender.audio )
        
        if self.receiver:
            self.log.FailUnless( self.senderDev, self.sender.sender.status == 'Enabled', 
                'Sender status %s' % self.sender.sender.status )
            
            for item in ['bitDepth', 'bitRate', 'codecName', 'lossless',
                         'metadata', 'metatext', 'sampleRate', 'uri']:
                itemTitle = item[0].upper()+item[1:]
                senderVal = eval( 'self.sender.info.%s' % item )
                receiverVal = eval( 'self.receiver.info.%s' % item )
                self.log.FailUnless( self.senderDev, senderVal==receiverVal, 
                    '(%s/%s) EVENTED Sender/Receiver value for %s' % 
                    (senderVal, receiverVal, itemTitle) )

    # noinspection PyUnusedLocal
    def _ReceiverEventCb( self, aService, aSvName, aSvVal, aSvSeq ):
        """Callback from Receiver Service UPnP events"""
        if aSvName == 'TransportState':
            if self.receiverStarted:
                self._RestartStateTimer()   # Add 2s 'hysteresis' to TransportState check
            self.receiverStarted = True
            
    def _ReceiverStateCb( self ):
        """Timer callback from receiver transport state event"""
        senderState = self.sender.radio.transportState
        receiverState = self.receiver.receiver.transportState
        if receiverState == 'Playing':
            self.log .FailUnless( self.rcvrDev, senderState=='Playing',
                '(%s/%s) sender/receiver Transport State' % (senderState, receiverState) )
        elif receiverState == 'Waiting':  
            self.log .FailIf( self.rcvrDev, senderState=='Playing',
                '(%s/%s) sender/receiver Transport State' % (senderState, receiverState) )

    def _RestartStateTimer( self ):
        """Restart timer for checking transport state - ensures that both sender and
           receiver have had stable TransportState for 2s before check is done"""
        self.lock.acquire()
        if self.stateTimer:
            self.stateTimer.cancel()
        self.stateTimer = LogThread.Timer( 2, self._ReceiverStateCb )
        self.stateTimer.start()
        self.lock.release()

if __name__ == '__main__':
    
    BASE.Run( sys.argv )
    