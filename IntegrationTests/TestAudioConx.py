#!/usr/bin/env python
"""TestAudioConx - test for low(ish) level functionality on connection to the
               audio server. Uses a 'test' server to force responses.

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - Tests to execute
                - all         -> all tests
                - get         -> standard (non-partial) get response
                - error       -> HTTP error(s) from server
                - accept      -> server accept/not accepting request
                - respond     -> server responding/not responding
                - buff-invoke -> invoke whilst buffering
                - close       -> server close conx
    arg#3 - <optional> param for test
                - errCode for error (blank for all)
                - loops for respond
                - invoke for buff-invoke (blank for all)
               
This is a collection of discrete tests using a 'test' audio server which can
simulate normal and error conditions from the server
""" 
import _FunctionalTest
import BaseTest                   as BASE
import Upnp.ControlPoints.Volkano as Volkano
import Utils.Network.HttpServer   as HttpServer
import Utils.Common               as Common
import _SoftPlayer                as SoftPlayer
import os
import random
import sys
import time
import threading

kTests     = ['all',
              'get',
              'error',
              'accept',
              'respond',
              'buff-invoke',
               'close']

kErrors    = HttpServer.httpResp.keys()

kInvokes   = ['Pause',
              'Play',
              'SeekSecondAbsolute',
              'SeekSecondRelative',
              'SeekIndex',
              'Stop']

kAudioRoot = os.path.join( _FunctionalTest.audioDir, 'LRTones/' )
kTrackList = os.path.join( kAudioRoot, 'TrackList.xml' )


class TestAudioConx( BASE.BaseTest ):
    """Class to check operation in response to audio server functionality"""
    
    def __init__( self ):
        """Constructor for AudioConx test"""
        self.dut       = None
        self.dutDev    = None
        self.audioSrv  = None
        self.soft      = None
        self.state     = None
        self.tracks    = []
        self.playing   = threading.Event()
        self.paused    = threading.Event()
        self.stopped   = threading.Event()
        self.buffering = threading.Event()
        BASE.BaseTest.__init__( self )

    def Test( self, args ):
        """Audio Conection test"""
        dutName  = None
        test     = None
        loopback = False

        # parse command line arguments
        try:
            dutName = args[1]
            test    = args[2].lower()
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )
            
        param = None
        if len( args ) > 3:
            param = args[3]
            
        if test not in kTests:
            self.log.Abort( '', 'Invalid test type %s' % test )
            
        if param:
            if test == 'error' and int( param ) not in kErrors:
                self.log.Abort( '', 'Invalid error code %s' % param )
            elif test == 'invoke' and param not in kInvokes:
                self.log.Abort( '', 'Invalid invoke %s' % param )
                        
        # create media renderer and subscribe to events
        if dutName.lower() == 'local':
            loopback = True
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestDev', aLoopback=loopback )
            dutName = self.soft.name
        self.dutDev = dutName.split( ':' )[0]
        self.dut = Volkano.VolkanoDevice( dutName, aIsDut=True, aLoopback=loopback )
        self.dut.playlist.AddSubscriber( self._PlaylistEventCb )
        
        # start audio server and load playlist into DS
        self.audioSrv = HttpServer.HttpServer( kAudioRoot )
        self.audioSrv.Start()
        tracks = Common.GetTracks( kTrackList, self.audioSrv )
        self.dut.playlist.DeleteAllTracks()
        self.dut.playlist.AddPlaylist( tracks )

        # sanity check to ensure server is working in 'normal' mode
        self._TestPartialGet()
               
        # run the requested sub-tests
        if test in ['all','get']:
            self._TestGet()
        if test in ['all','error']:
            self._TestError( param )
        if test in ['all','accept']:
            self._TestAccept()
        if test in ['all','respond']:
            self._TestRespond( param )
        if test in ['all','buff-invoke']:
            self._TestBuffInvoke( param )
        if test in ['all','close']:
            self._TestClose()

        # stop playback            
        self.dut.playlist.Stop()
            
    def Cleanup( self ):
        """Perform cleanup on test exit"""
        if self.dut:                     
            self.dut.Shutdown()
        if self.audioSrv:
            self.audioSrv.Shutdown()
        if self.soft:
            self.soft.Shutdown()
        BASE.BaseTest.Cleanup( self )                

    def _TestPartialGet( self ):
        self._LogHeader( 'Testing with Partial-GET request/response pair' )
        
        self.playing.clear()
        index = random.randint( 0, 4 )
        self.dut.playlist.SeekIndex( index )
        self.playing.wait( 5 )
        if not self.playing.isSet():
            # abort as sanity-check test - don't continue if server not serving
            self.log.Abort( self.dutDev, 'No playback on track %d' % index )
        time.sleep( 5 )
        
        self.stopped.clear()
        self.dut.playlist.Stop()
        self.stopped.wait( 5 )
    
    def _TestGet( self ):
        self._LogHeader( 'Testing with GET response (to Partial-GET request)' )
        self.audioSrv.ForceResponse( 200 )
        
        self.playing.clear()
        index = random.randint( 0, 4 )
        self.dut.playlist.SeekIndex( index )
        self.playing.wait( 5 )
        time.sleep( 5 )
        self.log.FailUnless( self.dutDev, self.playing.isSet(),
            '%s/Playing actual/expected state after GET response' % self.state)
        
        self.stopped.clear()
        self.dut.playlist.Stop()
        self.stopped.wait( 5 )
        self.audioSrv.ForceResponse( None )
    
    def _TestError( self, aError=None ):
        # On any error code from server, the DS should seek to the next track
        # and continue to do so until it gets a non-error response (code 200 or
        # 206) at which point it should start playback. If the end of playlist
        # is reached before non-error response then it should stop. If repeat 
        # mode is enabled it will continue to seek forever until non-error
        # response or user intervention
        if aError:
            errList = [int( aError )]
        else:
            errList = kErrors
            
        self.dut.playlist.repeat = 'off'  # ensure repeat disabled
        for err in errList:
            self._LogHeader( 'Testing with %d error response' % err )
            if err in [200,206]:
                self.log.Info( self.dutDev, 'No test with non-error response code %d' % err )
                continue
            
            # Initial state: Playing
            self.playing.clear()
            self.dut.playlist.SeekIndex( 0 )
            self.playing.wait( 3 )
                
            self.audioSrv.ForceResponse( err )
            self.stopped.clear()
            self.dut.playlist.SeekIndex( 1 )
            self.stopped.wait( 10 )
            self.log.FailUnless( self.dutDev, self.stopped.isSet(),
                '%s after HTTP <%d: %s> from Playing' % 
                (self.state, err, HttpServer.httpResp[err] ))
            self.audioSrv.ForceResponse( None )
            self.log.Info( '' )
                
            # Initial state: Paused
            self.playing.clear()
            self.dut.playlist.SeekIndex( 0 )
            self.playing.wait( 3 )
            time.sleep( 5 )
            self.paused.clear()
            self.dut.playlist.Pause()
            self.paused.wait( 3 )
                
            self.audioSrv.ForceResponse( err )
            self.stopped.clear()
            self.dut.playlist.SeekIndex( 1 )
            self.stopped.wait( 10 )
            self.log.FailUnless( self.dutDev, self.stopped.isSet(),
                '%s after HTTP <%d: %s> from Paused' % 
                (self.state, err, HttpServer.httpResp[err] ))
            self.audioSrv.ForceResponse( None )
            self.log.Info( '','' )
                
            # Initial state: Stopped
            self.stopped.clear()
            self.dut.playlist.SeekIndex( 0 )
            self.dut.playlist.Stop()
            self.stopped.wait( 3 )
                
            self.audioSrv.ForceResponse( err )
            self.dut.playlist.SeekIndex( 1 )
            time.sleep( 5 )
            self.log.FailUnless( self.dutDev, self.state == 'Stopped',
                '%s after HTTP <%d: %s> from Stopped' % 
                (self.state, err, HttpServer.httpResp[err] ))
            self.audioSrv.ForceResponse( None )
            self.log.Info( '' )
    
    def _TestAccept( self ):
        # When TCP accept is disabled,  DS should go buffering on next NEW
        # connection (as no response from server). It will remain buffering
        # until TCP accept is re-enabled, at which point it should start playing        
        self._LogHeader( 'Testing with TCP accept disabled' )
        self.playing.clear()
        self.dut.playlist.SeekIndex( 0 )
        self.playing.wait( 3 )
        
        self.audioSrv.DisableAccept()
        self.buffering.clear()
        self.dut.playlist.SeekIndex( 1 )
        self.buffering.wait( 3 )
        time.sleep( 5 )
        self.log.FailUnless( self.dutDev, self.buffering.isSet(),
            'Buffering whilst opening conx. with server TCP accept disabled' )
        
        self.playing.clear()
        self.audioSrv.EnableAccept()
        self.playing.wait( 3 )
        self.log.FailUnless( self.dutDev, self.playing.isSet(),
            'Playing with TCP accept re-enabled' )
        
    def _TestRespond( self, aLoops ):
        # When server is not responding, DS should play out its buffer and then
        # enter Buffering state. On server resuming responding, DS should
        # continue playbac from where it left off
        try:
            loops = int( aLoops )
        except:
            loops = 3
        self._LogHeader( 'Testing with Server responding/not responding' )
        self.playing.clear()
        self.dut.playlist.SeekIndex( 8 )    # hi-res track to reduce time to wait for buffering
        self.playing.wait( 3 )
        time.sleep( 1 )
        
        for loop in range( loops ):
            self.buffering.clear()
            self.audioSrv.StopResponding()
            self.buffering.wait( 60 )
            time.sleep( 5 )
            self.log.FailUnless( self.dutDev, self.buffering.isSet(),
                '%d of %d: Buffering - server not responding' % (loop+1, loops ))
            
            self.playing.clear()
            self.audioSrv.StartResponding()
            self.playing.wait( 10 )
            time.sleep( 5 )
            self.log.FailUnless( self.dutDev, self.playing.isSet(),
                '%d of %d: Playing - server responding' % (loop+1, loops ))
    
    def _TestBuffInvoke( self, aInvoke ):
        # All invokes should operate from Buffering state the same as from any
        # other state. Note that the stimulus forcing buffering state will still
        # be present, which may affect the expected outcome
        if aInvoke:
            invokeList = [aInvoke]
        else:
            invokeList = kInvokes
        for invoke in invokeList:
            self._LogHeader( 'Testing %s invoke whilst DS buffering' % invoke )            
            self.playing.clear()
            self.dut.playlist.SeekIndex( 8 )    # hi-res track to reduce time to wait for buffering
            self.playing.wait( 3 )
            time.sleep( 1 )
            self.buffering.clear()
            self.audioSrv.StopResponding()
            self.buffering.wait( 60 )
            if self.dut.playlist.transportState != 'Buffering':
                self.log.Fail( self.dutDev, 'Failed to enter buffering state on data starvation' )
            else:
                time.sleep( 5 )
                if invoke == 'Pause':
                    self.paused.clear()
                    self.dut.playlist.Pause()
                    self.paused.wait( 5 )
                    self.log.FailUnless( self.dutDev, self.paused.isSet(),
                        '%s/Paused actual/expect state after %s whilst buffering'
                         % (self.state, invoke) )
                else:
                    if invoke == 'Play':
                        self.dut.playlist.Play()
                    elif invoke == 'Stop':
                        # Stop implies 'stop' current playback, and setup to play
                        # first track in playlist. Hence it will attempt to pre-fetch
                        # the first track in list, which fails due to disabled server
                        # so we remain buffering. Not ideal behaviour - see #3088
                        self.dut.playlist.Stop()
                    elif invoke == 'SeekSecondAbsolute':
                        self.dut.playlist.SeekSecondAbsolute( 30 )
                    elif invoke == 'SeekSecondRelative':
                        self.dut.playlist.SeekSecondRelative( 30 )
                    elif invoke == 'SeekTrackAbsolute':
                        self.dut.playlist.SeekTrackAbsolute( 3 )
                    elif invoke == 'SeekTrackRelative':
                        self.dut.playlist.SeekTrackRelative( 3 )
                    time.sleep( 5 )
                    self.log.FailUnless( self.dutDev, self.state == 'Buffering',
                        '%s/Buffering actual/expect state after %s whilst buffering'
                         % (self.state, invoke) )
            self.audioSrv.StartResponding()
    
    def _TestClose( self ):
        # Where server abruptly closes connection, expect DS to play out its
        # buffer and then go buffering. 
        self._LogHeader( 'Testing with Server forcing TCP close' )
        self.playing.clear()
        self.dut.playlist.SeekIndex( 8 )    # hi-res to reduce time to wait for buffering
        self.playing.wait( 3 )
        time.sleep( 1 )
        self.buffering.clear()
        self.audioSrv.CloseConnection()
        self.buffering.wait( 60 )
        if self.dut.playlist.transportState != 'Buffering':
            self.log.Fail( self.dutDev, 'Failed to enter buffering state on data starvation' )
        else:
            time.sleep( 5 )
            self.log.FailUnless( self.dutDev, self.buffering.isSet(),
                'Buffering when server closed TCP conx' )

    def _LogHeader( self, aMsg ):
        """Log a header message"""
        self.log.Info( '' )
        self.log.Info( '', '---- ' + aMsg + ' ----' )
        self.log.Info( '' )

    # noinspection PyUnusedLocal
    def _PlaylistEventCb( self, service, svName, svVal, svSeq ):
        """Callback from Playlist service UPnP events"""
        if svName == 'TransportState':
            self.state = svVal
            if svVal == 'Playing':
                self.playing.set()
            elif svVal == 'Paused':
                self.paused.set()
            elif svVal == 'Stopped':
                self.stopped.set()
            elif svVal == 'Buffering':
                self.buffering.set()

        
if __name__ == '__main__':
    
    BASE.Run( sys.argv )
        