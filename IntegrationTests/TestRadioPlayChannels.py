#!/usr/bin/env python
"""TestRadioPlayChannels - test playback of Radio (using Radio service)

Parameters:
    arg#1 - DUT Sender ['local' for internal SoftPlayer]
    arg#2 - DUT Receiver ['local' for internal SoftPlayer] - optional (None = not present)
    arg#3 - Radiotime username
    arg#4 - Time to play before skipping to next channel (None = indefinite)
    arg#5 - Shuffle mode [on/off] (optional - default off)
    arg#6 - Test loops (optional - default 1)

Play radio channels sequentially. Channel list provided by Radiotime login or
local ChannelList (CHL) file - see same directory as this test for example.
Repeat/shuffle for radio is controlled by this test, NOT DS.
"""
import _FunctionalTest
import BaseTest                   as BASE
import Upnp.ControlPoints.Volkano as Volkano
import Utils.Common               as Common
import _SoftPlayer                as SoftPlayer
import LogThread
import copy
import os
import random
import sys
import threading
import time

# Predefined TuneIn preset lists (password klueso)
gMixedPresets   = 'linn-test-presets-1'
gNoPresets      = 'linn-test-presets-2'
gMaxPlusPresets = 'linn-test-presets-3'


class TestRadioPlayChannels( BASE.BaseTest ):
    "Test playback of radio channels"

    def __init__( self ):
        "Constructor - initialise base class"
        BASE.BaseTest.__init__( self )
        self.sender           = None
        self.receiver         = None
        self.soft1            = None
        self.soft2            = None
        self.playTimer        = None
        self.stateTimer       = None
        self.checkTimer       = None
        self.channels         = []
        self.title            = ""
        self.stateTimer       = None
        self.receiverStarted  = False
        self.idUpdated        = threading.Event()
        self.uriUpdated       = threading.Event()
        self.metaUpdated      = threading.Event()
        self.idArrayUpdated   = threading.Event()
        self.metatextUpdated  = threading.Event()
        self.isPlaying        = threading.Event()
        self.isStopped        = threading.Event()
        self.newState         = threading.Event()
        self.playTimerExpired = threading.Event()
        self.lock             = threading.Lock()

    def Test( self, aArgs ):
        "Play radio channels, using Radio service for control"
        playTime   = None
        loops      = 1
        shuffle    = False

        try:
            senderName   = aArgs[1]
            receiverName = aArgs[2]
            channelList  = aArgs[3]
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
            
        if receiverName.lower() == 'none':
           receiverName = None 

        # configure radio and load the presets for test
        if senderName.lower() == 'local':
            self.soft1 = SoftPlayer.SoftPlayer( aRoom='TestSender', aTuneIn=channelList )
            senderName = 'TestSender:SoftPlayer'
        self.senderDev = senderName.split( ':' )[0]
        self._initRadio( senderName  )
        
        # create receiver and connect to sender
        if receiverName:
            if receiverName.lower() == 'local':
                self.soft2 = SoftPlayer.SoftPlayer( aRoom='TestRcvr' )
                receiverName = 'TestRcvr:SoftPlayer'
            self.rcvrDev = receiverName.split( ':' )[0]
            self.receiver = Volkano.VolkanoDevice( receiverName, aIsDut=True )
            self.receiver.receiver.AddSubscriber( self._receiverEventCb )
            time.sleep( 3 )
            self.receiver.receiver.SetSender( self.sender.sender.uri, self.sender.sender.metadata )
            self.receiver.receiver.Play()

        # repeat test for requested number of loops
        for loop in range( loops ):
            loopMsg      = 'Loop %d of %d' % (loop+1, loops)
            testChannels = self._getTestChannels( shuffle )          
            numChannels  = len( testChannels )
            testNum      = 0
            self.idArrayUpdated.clear()            
            
            # clear existing channel info
            self.uriUpdated.clear()
            self.sender.radio.SetChannel( 'Empty', 'Empty' )
            self.uriUpdated.wait( 5 )

            # loop thru all the test channels (already randomised if requested)
            for channel in testChannels:
                if self.idArrayUpdated.isSet():
                    self.log.Warn( self.senderDev, 'Presets updated - exiting test loop' )
                    break
                
                testNum += 1
                testMsg = 'Channel %d of %d' % (testNum, numChannels)
                self.log.Info( '' )
                
                if not channel[1]:
                    self.log.Warn( self.senderDev, '%s: No Channel Data -> skipping' % testMsg )
                    continue
                
                # extract channel info and log test header
                title = Common.GetTitleFromDidl( channel[1] )
                uri = Common.GetUriFromDidl( channel[1] )

                self.log.Info( '', '---------------------------------------------' )
                self.log.Info( '', '%s: %s' % (loopMsg, testMsg) )
                self.log.Info( '', '%s' % title )
                self.log.Info( '', '---------------------------------------------' )
                self.log.Info( '' )
            
                # select the channel, check selected correctly
                if not self._selectChannel( uri, channel ):
                    self.log.Warn( self.senderDev, 'Channel select error - skip playback' )
                    continue
                    
                # start playback
                if self.sender.radio.transportState != 'Playing':
                    self._startPlayback( title )
            
                # log 'now playing' info, set and wait for playback timer
                if self.sender.radio.transportState == 'Playing':
                    self.checkTimer = LogThread.Timer( 7, self._checkTimerCb )
                    self.checkTimer.start()
                    if playTime:
                        self.playTimerExpired.clear()
                        self.playTimer = LogThread.Timer( playTime, self._playTimerCb )
                        self.playTimer.start()
                        self.playTimerExpired.wait()
                        self.log.Pass( self.senderDev,  
                            'Completed %ds playback of %s' % (playTime,title) )
                    else:
                        self.isStopped.wait()
                        
                    if self.checkTimer:
                        self.checkTimer.cancel()

        # stop playback, check successful
        if self.sender.radio.transportState != 'Stopped':
            self.isStopped.clear()
            self.sender.radio.Stop()
            self.isStopped.wait( 5 )
            if not self.isStopped.isSet():
                self.log.Fail( self.senderDev, 'Playback failed to STOP' )

    def Cleanup( self ):
        "Perform post-test cleanup" 
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

    def _initRadio( self, aName ):
        "Switch to radio source and clear ony existing presets"
        mode = 'false'
        self.sender = Volkano.VolkanoDevice( aName, aIsDut=True ) 
        self.sender.product.sourceIndexByName = 'Radio'
        
        self.idArrayUpdated.clear()
        self.sender.radio.AddSubscriber( self._radioEventCb )
        self.sender.info.AddSubscriber( self._infoEventCb )
        self.idArrayUpdated.wait( 5 )
        self.channels = self.sender.radio.ChannelsInfo( self.sender.radio.idArray )
        
        
    def _getTestChannels( self, aShuffle ):
        "Return ordered channel list for use in test loop"
        channels = copy.deepcopy( self.channels )
        testChannels = []
        
        while( len( channels )):
            if aShuffle:
                rand = random.randint( 0, len( channels )-1 )
                channel = channels.pop( rand )
            else:
                channel = channels.pop( 0 )
            if channel != ('',''):
                testChannels.append( channel )
        return testChannels

    def _selectChannel( self, aUri, aChannel ):
        "Select radio channel, check it selects and updates status"
        self.idUpdated.clear()
        self.uriUpdated.clear()
        self.metaUpdated.clear()
        self.isStopped.clear()
        self.sender.radio.SetId( aChannel[0], aUri )
                        
        self.uriUpdated.wait( 5 )
        self.metaUpdated.wait( 0.1 )
        self.idUpdated.wait( 0.1 )
            
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
    
    def _startPlayback( self, aTitle ):
        "Start playback, wait for playing state (or error)"
        self.title = aTitle
        self.isPlaying.clear()
        self.newState.clear()
        startPlay = time.time()
        self.sender.radio.Play()
        self.newState.wait( 30 )
        self.metatextUpdated.clear()
        actionTime = time.time()-startPlay
        
        if actionTime > 3:
            self.log.Fail( self.senderDev, 'State change after Play took %ds' % actionTime )
            self.sender.radio.Stop()
             
        self.isPlaying.wait( 10 )
        if not self.isPlaying.isSet():
            self.log.Warn( self.senderDev, 'FAILED playback of %s' % aTitle )
        else:    
            self.log.Pass( self.senderDev, 'Started playback of %s' % aTitle )
            
    def _radioEventCb( self, aService, aSvName, aSvVal, aSvSeq ):
        "Callback from Radio Service UPnP events"
        if aSvName == 'IdArray':
            self.channels = self.sender.radio.ChannelsInfo( self.sender.radio.idArray )
            self.idArrayUpdated.set()
        elif aSvName == 'TransportState':
            self.newState.set()
            if self.stateTimer:   # add hysteresis to transport state comparison
                self.lock.acquire()
                self.stateTimer.cancel()
                self.stateTimer = LogThread.Timer( 5, self._ReceiverStateCb )
                self.stateTimer.start()
                self.lock.release()
            if aSvVal == 'Playing':
                self.isStopped.clear()
                self.isPlaying.set()
            elif aSvVal == 'Stopped':
                if self.playTimer:
                    self.playTimer.cancel()
                    self.playTimer = None
                    self.playTimerExpired.set()
                    self.log.Warn( self.senderDev, 'Playback of %s stopped unexpectedly' % self.title )
                self.isPlaying.clear()
                self.isStopped.set()
        elif aSvName == 'Id':
            self.idUpdated.set()
        elif aSvName == 'Uri':
            self.uriUpdated.set()
        elif aSvName == 'Metadata':
            self.metaUpdated.set()
            
    def _infoEventCb( self, aService, aSvName, aSvVal, aSvSeq ):
        "Callback from Info service UPnP events"
        if aSvName == 'Metatext':
            self.metatextUpdated.set()
                
    def _playTimerCb( self ):
        "Callback from timer"
        self.playTimerExpired.set()
        self.playTimer = None
        
    def _checkTimerCb( self ):
        "Callback from timer - perform checks during radio playback"
        if self.metatextUpdated.isSet():
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
                
    def _receiverEventCb( self, aService, aSvName, aSvVal, aSvSeq ):
        "Callback from Receiver Service UPnP events"
        if aSvName == 'TransportState':
            if self.receiverStarted:
                # add hysteresis to transport state comparison
                self.lock.acquire()
                if self.stateTimer:
                    self.stateTimer.cancel()
                self.stateTimer = LogThread.Timer( 5, self._ReceiverStateCb )
                self.stateTimer.start()
                self.lock.release()
            self.receiverStarted = True
            
    def _ReceiverStateCb( self ):
        "Timer callback from receiver transport state event"
        senderState = self.sender.radio.transportState
        receiverState = self.receiver.receiver.transportState
        if receiverState == 'Playing':
            self.log .FailUnless( self.rcvrDev, senderState=='Playing',
                '(%s/%s) sender/receiver Transport State' % (senderState, receiverState) )
        elif receiverState == 'Waiting':  
            self.log .FailIf( self.rcvrDev, senderState=='Playing',
                '(%s/%s) sender/receiver Transport State' % (senderState, receiverState) )
                
        
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
    