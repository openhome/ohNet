#!/usr/bin/env python
"""TestAvTransportService - test AvTransport service

Parameters:
    arg#1 - MediaRenderer DUT ['local' for internal SoftPlayer]
    arg#2 - before state to test from (use ALL for all states)
            
This performs the state-transition tests on a DUT as controlled by the UPnP
AvTransport service (as it relates to audio-digital-source). The state 
transition table including all end-cases is specified as data blocks within this
file.

NOTE/ all data used in this test should be valid for the scenario being tested.
      Invalid, out-of-range and otherwise erroneous data is covered by the
      service's unit testing.
"""
 
# Differences from DS test:
#    - remove .NET XML handling

import _FunctionalTest
import BaseTest                         as BASE
import Upnp.ControlPoints.Volkano       as Volkano
import Upnp.ControlPoints.MediaRenderer as MR
import Utils.Network.HttpServer         as HttpServer
import _SoftPlayer                      as SoftPlayer
import Path
import copy
import os
import sys
import tempfile
import time
import xml.etree.ElementTree as ET

#### TODO
#### do playing thru end of track - as a special case transition

gStates = \
[
    # Assumptions (based on DS implementation):
    #    - URIs are all single track (no M3Us)
    #    - No support for NextAVTransportURI action
    #    - No support for counter-based indexing (only time-based)
    #    - No support for ANY optional StateVariables
    #
    # Hence only ONE track in 'playlist' at any time, so any 'Seek' actions
    # only move around with in the current track
    #
    # PAUSED states can have 2 precondition states:
    #    - normal (PAUSED_PLAYBACK) where paused on track which has been playing
    #    - PAUSED_UNKNOWN where CurrentURI has been changed whilst paused, hence
    #      the track data (length etc.) which is only found out when playing is
    #      not known
    #
    # SetAVTransportURI always changes transport state to STOPPED

    #  Before             Transition               After               Affected SV List
    #  ------             ----------               -----               ----------------
#    ['STOPPED',          'SetAVTransportURI',     'STOPPED',         ['AVTransportURI','AVTransportURIMetaData','NumberOfTracks','CurrentTrack','CurrentTrackMetaData','CurrentTrackURI','CurrentTrackDuration','CurrentMediaDuration','CurrentMediaCategory','PlaybackStorageMedium']],
    ['STOPPED',          'SetAVTransportURI',     'STOPPED',         ['AVTransportURI','AVTransportURIMetaData','NumberOfTracks','CurrentTrack','CurrentTrackMetaData','CurrentTrackURI','CurrentTrackDuration','CurrentMediaDuration','PlaybackStorageMedium']],
    ['STOPPED',          'Stop',                  'STOPPED',         ['RelativeTimePosition']],
    ['STOPPED',          'Play',                  'PLAYING',         ['CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['STOPPED',          'Pause',                 'STOPPED',         []],        
    ['STOPPED',          'Seek',                  'STOPPED',         ['CurrentTrackURI','AVTransportURI','CurrentTrack','NumberOfTracks','CurrentTrackMetaData','AVTransportURIMetaData','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['STOPPED',          'Next',                  'STOPPED',         ['CurrentTrackURI','AVTransportURI','CurrentTrack','NumberOfTracks','CurrentTrackMetaData','AVTransportURIMetaData','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['STOPPED',          'Previous',              'STOPPED',         ['CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],

    ['PLAYING',          'SetAVTransportURI',     'STOPPED',         ['AVTransportURI','AVTransportURIMetaData','NumberOfTracks','CurrentTrack','CurrentTrackMetaData','CurrentTrackURI','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['PLAYING',          'Stop',                  'STOPPED',         ['RelativeTimePosition']],
    ['PLAYING',          'Play',                  'PLAYING',         ['RelativeTimePosition']],
    ['PLAYING',          'Pause',                 'PAUSED_PLAYBACK', []],
    ['PLAYING',          'Seek',                  'PLAYING',         ['RelativeTimePosition']],
    ['PLAYING',          'Next',                  'STOPPED',         ['CurrentTrackURI','AVTransportURI','CurrentTrack','NumberOfTracks','CurrentTrackMetaData','AVTransportURIMetaData','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['PLAYING',          'Previous',              'STOPPED',         ['CurrentTrackURI','AVTransportURI','CurrentTrack','NumberOfTracks','CurrentTrackMetaData','AVTransportURIMetaData','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    #['PLAYING',          '<EndOfTrack>',          'STOPPED',         ['CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    
    ['PAUSED_PLAYBACK',  'SetAVTransportURI',     'STOPPED',         ['AVTransportURI','AVTransportURIMetaData','NumberOfTracks','CurrentTrack','CurrentTrackMetaData','CurrentTrackURI','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['PAUSED_PLAYBACK',  'Stop',                  'STOPPED',         ['RelativeTimePosition']],
    ['PAUSED_PLAYBACK',  'Play',                  'PLAYING',         ['RelativeTimePosition']],
    ['PAUSED_PLAYBACK',  'Pause',                 'PAUSED_PLAYBACK', []],
    ['PAUSED_PLAYBACK',  'Seek',                  'PAUSED_PLAYBACK', []],
    ['PAUSED_PLAYBACK',  'Next',                  'STOPPED',         ['CurrentTrackURI','AVTransportURI','CurrentTrack','NumberOfTracks','CurrentTrackMetaData','AVTransportURIMetaData','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['PAUSED_PLAYBACK',  'Previous',              'STOPPED',         ['CurrentTrackURI','AVTransportURI','CurrentTrack','NumberOfTracks','CurrentTrackMetaData','AVTransportURIMetaData','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],

    ['PAUSED_UNKNOWN',    'SetAVTransportURI',    'STOPPED',         ['AVTransportURI','AVTransportURIMetaData','NumberOfTracks','CurrentTrack','CurrentTrackMetaData','CurrentTrackURI','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['PAUSED_UNKNOWN',    'Stop',                 'STOPPED',         ['RelativeTimePosition']],
    ['PAUSED_UNKNOWN',    'Play',                 'PLAYING',         ['CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['PAUSED_UNKNOWN',    'Pause',                'STOPPED',         []],
    ['PAUSED_UNKNOWN',    'Seek',                 'STOPPED',         ['RelativeTimePosition']],
    ['PAUSED_UNKNOWN',    'Next',                 'STOPPED',         ['CurrentTrackURI','AVTransportURI','CurrentTrack','NumberOfTracks','CurrentTrackMetaData','AVTransportURIMetaData','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
    ['PAUSED_UNKNOWN',    'Previous',             'STOPPED',         ['CurrentTrackURI','AVTransportURI','CurrentTrack','NumberOfTracks','CurrentTrackMetaData','AVTransportURIMetaData','CurrentTrackDuration','CurrentMediaDuration','RelativeTimePosition']],
]
gBefore = 0
gTrans  = 1
gAfter  = 2
gAffSvs = 3

gParams = \
{ 
    'SetAVTransportURI':     [ # built up in test from media server query
                             ],    
    'Stop':                  [ {'InstanceID':0 }
                             ],
    'Play':                  [ {'InstanceID':0, 'Speed':'1' }
                             ],
    'Pause':                 [ {'InstanceID':0 }
                             ],
    'Seek':                  [ # built up in test, specific to  track
                             ],
    'Next':                  [ {'InstanceID':0 }
                             ],
    'Previous':              [ {'InstanceID':0 }
                             ]
}

gStaticSvs = \
{
    'AbsoluteCounterPosition':      2147483647,
    'AbsoluteTimePosition':         'NOT_IMPLEMENTED',
    'CurrentPlayMode':              'NORMAL',
    'CurrentRecordQualityMode':     'NOT_IMPLEMENTED',
    'NextAVTransportURI':           'NOT_IMPLEMENTED',
    'NextAVTransportURIMetaData':   'NOT_IMPLEMENTED',
    'PossiblePlaybackStorageMedia': 'NETWORK',
    'PossibleRecordQualityModes':   'NOT_IMPLEMENTED',
    'PossibleRecordStorageMedia':   'NOT_IMPLEMENTED',
    'RecordMediumWriteStatus':      'NOT_IMPLEMENTED',
    'RecordStorageMedium':          'NOT_IMPLEMENTED',
    'RelativeCounterPosition':      2147483647,
    'TransportStatus':              'OK',
    'TransportPlaySpeed':           '1'
}

kDelay     = 2
kPlayTime  = 10
kAudioRoot = os.path.join( Path.AudioDir(), 'MusicTracks/' )
kAvtNs     = '{urn:schemas-upnp-org:metadata-1-0/AVT/}'
kDidlNs    = '{urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/}'


class TestAvTransportService( BASE.BaseTest ):
    "Test DS AvTransport Service"

    def __init__( self ):
        BASE.BaseTest.__init__( self )
        self.soft      = None
        self.server    = None
        self.volkano   = None
        self.upnpMr    = None
        self.avt       = None
        self.prevSv    = {}
        self.currSv    = {}
        self.trackLen  = {}        
        self.trackMeta = {}
        self.playTime  = kPlayTime 
        
    def Test( self, args ):
        "AVTransport state-transition test"
        # parse command line arguments
        try:
            self.mrName = args[1]
            stateToTest = args[2].upper()
        except:
            print '\n', __doc__, '\n'
            self.log.Abort( '', 'Invalid arguments %s' % (str( args )) )
            
        # setup states to test
        allStates = ['STOPPED','PLAYING','PAUSED_PLAYBACK','PAUSED_UNKNOWN']
        if stateToTest == 'ALL':
            statesToTest = allStates
        elif stateToTest in allStates:
            statesToTest = [stateToTest]
        else:
            self.log.Abort( '', 'Invalid state-to-test %s' % (stateToTest) )

        if 'MediaRenderer' not in self.mrName:
            self.mrName += ':MediaRenderer'
            
        # start audio server
        self.server = HttpServer.HttpServer( kAudioRoot )
        self.server.Start()        
        
        # start local softplayer if required
        if self.mrName.lower() == 'local:mediarenderer':
            self.soft = SoftPlayer.SoftPlayer( aRoom='TestMr' )
            self.mrName = 'TestMr:SoftPlayer:MediaRenderer'
        
        # create UPnP CPs for renderer and server, and subscribe to AVT events
        self.mrDev = self.mrName.split( ':' )[0]
        self.upnpMr = MR.MediaRendererDevice( self.mrName )
        self.avt = self.upnpMr.avt
        
        # check value of 'static' SVs (rechecked for unchanged hereafter)
        self._RefreshCurrentSvs()
        for sv in gStaticSvs.keys():
            msg = '%s initialised to %s, expected %s' % \
                      (sv, self.currSv[sv], gStaticSvs[sv])
            self.log.FailIf( self.mrDev, gStaticSvs[sv]!=self.currSv[sv], msg )
        
        # load test track info from media server into transition parameters
        xmlFile = os.path.join( kAudioRoot, 'TrackList.xml' )
        xml = ET.parse( xmlFile )
        trackList = xml.findall( 'Track' );
        for track in trackList:
            if len( gParams['SetAVTransportURI'] ) < 4:
                uri = self.server.Listener() + track.find( 'Uri' ).text
                meta = track.find( 'Metadata' ).text
                didl = ET.XML( meta )
                res = didl.getiterator( kDidlNs+'res' )[0]
                gParams['SetAVTransportURI'].append( {'InstanceID':0, 'CurrentURI':uri, 'CurrentURIMetaData':meta})
                self.trackLen[uri] = res.attrib['duration'][1:]           
                self.trackMeta[uri] = meta
            
        # ensure not in NO_MEDIA_PRESENT state (occurs ONLY after reboot)
        self.avt.SetUri( uri, meta )
        time.sleep(10)

        # ensure source switched and settled (to avoid autoplay issues) 
        self.avt.Stop()
        time.sleep( 3 )
            
        # check state transitions and SV changes for all scenarios
        for entry in gStates:    
            if entry[gBefore] in statesToTest:
            
                self.trans = entry[gTrans]
                action = getattr( self.avt.avt, self.trans )
                gParams['Seek'] = self._SeekParams()
                params = gParams[self.trans]
                
                for param in params:
                    self.startState = entry[gBefore]
                    prefix = '%s->%s' % (entry[gBefore], self.trans)
                    self.log.Info( '' )
                    self.log.Info( self.mrDev, 'Invoking %s (with %s params)' %
                        (prefix, str( param )) )
                    self.log.Info( '' )
                    
                    # force 'before' state, invoke action, read 'after' state
                    # as cannot wait for specific event (don't know which one(s)
                    # or if they are working), just add delay for event catchup
                    self._SetState( entry[gBefore] )
                    time.sleep( kDelay )    # delay to let UPnP events catch up
                    self._RefreshCurrentSvs()           
                    self.prevSv = copy.deepcopy( self.currSv )
                    if entry[gBefore] != 'PAUSED_UNKNOWN':
                        self.log.FailIf( self.mrDev,
                            self.currSv['TransportState'] != entry[gBefore], 
                            '%s: BEFORE state %s, expected %s' %
                            (prefix, self.currSv['TransportState'], entry[gBefore]))
                    
                    if entry[gBefore] == 'PLAYING':
                        self.playTime = kPlayTime
                        self.log.Info( self.mrDev, 'Waiting %ds into playback' % self.playTime )
                        time.sleep( self.playTime )
                    else:
                        self.playTime = 0
                   
                    action( **param )
                    time.sleep( kDelay )  # delay to let UPnP events catch up
                    self._RefreshCurrentSvs()
                    remainingSvs = self.currSv.keys()
                    
                    # check new state after action is as expected
                    self.log.FailIf( self.mrDev, 
                        self.currSv['TransportState'] != entry[gAfter],
                        '%s: AFTER state %s, expected %s' %
                        (prefix, self.currSv['TransportState'], entry[gAfter]))
                    remainingSvs.remove( 'TransportState' )
                    
                    # check all affected SVs as expected
                    for sv in entry[gAffSvs]:
                        remainingSvs.remove( sv )
                        check = getattr( self, '_' + sv + 'Check' )
                        (ok, msg) = check( **param )
                        self.log.FailIf( self.mrDev, not ok, '%s: %s' % (prefix, msg) )
                        
                    # check all unaffected SVs are unchanged
                    for sv in remainingSvs:
                        if sv == 'RelativeTimePosition':
                            # allow 1 sec slippage for execution/delay times
                            expValues = self._GetPositions( self.currSv[sv] )
                            self.log.FailIf( self.mrDev, self.currSv[sv] not in expValues,
                                '%s: %s expected in %s was %s' %
                                (prefix, sv, expValues, self.currSv[sv]) )                            
                        else:
                            self.log.FailIf( self.mrDev, self.prevSv[sv] != self.currSv[sv],
                                '%s: %s changed from %s to %s' %
                                (prefix, sv, self.prevSv[sv], self.currSv[sv]) )

    def Cleanup( self ):
        "Perform post-test cleanup" 
        if self.upnpMr:          
            self.avt.Stop()
            self.upnpMr.Shutdown()
        if self.volkano:
            self.volkano.config.Set( 'Device', 'Handset Commands Accepted', 'None' )
            self.volkano.Shutdown()
        if self.server:
            self.server.Shutdown()
        if self.soft:
            self.soft.Shutdown()
        BASE.BaseTest.Cleanup( self )

    def _RefreshCurrentSvs( self ):
        "Refresh SV dict with current values"
        self.currSv = {'AbsoluteCounterPosition':      self.avt.absoluteCounterPosition,        
                       'AbsoluteTimePosition':         self.avt.absoluteTimePosition,
                       'AVTransportURI':               self.avt.avTransportURI,
                       'AVTransportURIMetaData':       self.avt.avTransportURIMetaData,
                       'CurrentMediaDuration':         self.avt.currentMediaDuration,
                       'CurrentPlayMode':              self.avt.currentPlayMode,    
                       'CurrentRecordQualityMode':     self.avt.currentRecordQualityMode,
                       'CurrentTrackDuration':         self.avt.currentTrackDuration,
                       'CurrentTrack':                 self.avt.currentTrack,
                       'CurrentTrackEmbeddedMetaData': self.avt.currentTrackEmbeddedMetaData,
                       'CurrentTrackMetaData':         self.avt.currentTrackMetaData,
                       'CurrentTrackURI':              self.avt.currentTrackURI,
                       'CurrentTransportActions':      self.avt.currentTransportActions,
                       'NumberOfTracks':               self.avt.numberOfTracks,
                       'NextAVTransportURI':           self.avt.nextAVTransportURI,
                       'NextAVTransportURIMetaData':   self.avt.nextAVTransportURIMetaData,
                       'PlaybackStorageMedium':        self.avt.playbackStorageMedium,
                       'PossiblePlaybackStorageMedia': self.avt.possiblePlaybackStorageMedia,
                       'PossibleRecordQualityModes':   self.avt.possibleRecordQualityModes,
                       'PossibleRecordStorageMedia':   self.avt.possibleRecordStorageMedia,
                       'RecordMediumWriteStatus':      self.avt.recordMediumWriteStatus,
                       'RecordStorageMedium':          self.avt.recordStorageMedium,
                       'RelativeTimePosition':         self.avt.relativeTimePosition,
                       'RelativeCounterPosition':      self.avt.relativeCounterPosition,
                       'TransportPlaySpeed':           self.avt.transportPlaySpeed,
                       'TransportState':               self.avt.transportState,
                       'TransportStatus':              self.avt.transportStatus }
        posnInfo = self.avt.avt.GetPositionInfo( InstanceID=0 )
        self.currSv['RelativeTimePosition'] = posnInfo['RelTime']
        self.currSv['AbsoluteTimePosition'] = posnInfo['AbsTime']
        self.currSv['RelativeCounterPosition'] = posnInfo['RelCount']
        self.currSv['AbsoluteCounterPosition'] = posnInfo['AbsCount']
                
    def _SetState( self, state ):
        "Force DUT into specified state (only actions if necessary)"
        self.avt.Stop()
        if state == 'PAUSED_PLAYBACK':            
            if int( self.currSv['NumberOfTracks'] ) < 1:
                self.avt.avt.SetAVTransportURI(  **gParams['SetAVTransportURI'][0] )
            self.avt.Play()
            time.sleep( kDelay )  # play a few secs into track
            self.avt.Pause()

        elif state == 'PAUSED_UNKNOWN':            
            # URI has changed whilst paused
            if int( self.currSv['NumberOfTracks'] ) < 1:
                self.avt.avt.SetAVTransportURI(  **gParams['SetAVTransportURI'][0] )
            self.avt.Play()
            self.avt.Pause()
            time.sleep( 1 )
            self.avt.avt.SetAVTransportURI(  **gParams['SetAVTransportURI'][0] )
        
        elif state == 'STOPPED':
            self.avt.avt.SetAVTransportURI(  **gParams['SetAVTransportURI'][0] )
            self.avt.Stop()
            
        elif state == 'PLAYING':
            if int( self.currSv['NumberOfTracks'] ) < 1:
                self.avt.avt.SetAVTransportURI(  **gParams['SetAVTransportURI'][0] )
            self.avt.Play()
            time.sleep( self.playTime )

    def _SeekParams( self ):
        "Build seek parameters"
        seek = [{'InstanceID':0, 'Unit':'REL_TIME',  'Target': '0:01:45'},
                {'InstanceID':0, 'Unit':'REL_TIME',  'Target': '0:00:10'}]
        return seek

    #
    # define a 'check' method for every non-static SV 
    #
        
    def _AVTransportURICheck( self, **kw ):
        actual = self.currSv['AVTransportURI']
        if self.trans == 'SetAVTransportURI':
            expected = kw.get( 'CurrentURI', None )   
        else:
            expected = self.prevSv['AVTransportURI']
        msg = 'AVTransportURI was %s expected %s' % (actual, expected)
        return( actual==expected, msg )
    
    def _AVTransportURIMetaDataCheck( self, **kw ):
        actual   = self.currSv['AVTransportURIMetaData']
        expected = self.trackMeta[self.currSv['AVTransportURI']]
        msg = 'AVTransportURIMetaData was %s expected %s' % (actual, expected)
        return( actual==expected, msg )        
    
    def _CurrentMediaDurationCheck( self, **kw ):
        d = self.currSv['CurrentMediaDuration']
        actual = '%01d:%02d:%02d' % (d/3600, d/60, d%60) 
        if self.currSv['TransportState'] == 'PLAYING':
            expected = self.trackLen[self.currSv['AVTransportURI']]
        elif self.currSv['TransportState'] in ['STOPPED','PAUSED_PLAYBACK']:
            if actual == '0:00:00':
                expected = '0:00:00'
            else:
                expected = self.trackLen[self.currSv['AVTransportURI']]            
        else:    
            expected = '0:00:00'
        msg = 'CurrentMediaDuration was %s expected %s' % (actual, expected)
        return( actual==expected, msg )
                
    def _CurrentTrackCheck( self, **kw ):
        actual   = int( self.currSv['CurrentTrack'] )
        expected = 0
        if self.currSv['AVTransportURI']:
            expected = 1
        msg = 'CurrentTrack was %s expected %s' % (actual, expected)
        return( actual==expected, msg )

    def _CurrentTrackDurationCheck( self, **kw ):
        # CurrentTrackDuration will either be zero or the actual duration.
        # Actual duration is deduced only once track is playing, hence for
        # STOPPED and PAUSED_PLAYBACK states the value may be either zero or the
        # actual duration dependent on history, so we will allow either value to
        # pass
        d = self.currSv['CurrentTrackDuration']
        actual = '%01d:%02d:%02d' % (d/3600, d/60, d%60) 
        if self.currSv['TransportState'] == 'PLAYING':
            expected = self.trackLen[self.currSv['AVTransportURI']]
        elif self.currSv['TransportState'] in ['STOPPED','PAUSED_PLAYBACK']:
            if actual == '0:00:00':
                expected = '0:00:00'
            else:
                expected = self.trackLen[self.currSv['AVTransportURI']]            
        else:    
            expected = '0:00:00'
        msg = 'CurrentTrackDuration was %s expected %s' % (actual, expected)
        return( actual==expected, msg )
    
    def _CurrentTrackMetaDataCheck( self, **kw ):
        actual   = self.currSv['CurrentTrackMetaData']
        expected = self.trackMeta[self.currSv['CurrentTrackURI']]
        msg = 'CurrentTrackMetaData was %s expected %s' % (actual, expected)
        return( actual==expected, msg )        
    
    def _CurrentTrackURICheck( self, **kw ):
        actual   = self.currSv['CurrentTrackURI']        
        expected = self.currSv['AVTransportURI']
        msg = 'CurrentTrack was %s expected %s' % (actual, expected)
        return( actual==expected, msg )
    
    def _NumberOfTracksCheck( self, **kw ):
        actual   = int( self.currSv['NumberOfTracks'] )
        expected = 0
        if self.currSv['AVTransportURI']:
            expected = 1
        msg = 'NumberOfTracks was %s expected %s' % (actual, expected)
        return( actual==expected, msg )
     
    def _PlaybackStorageMediumCheck( self, **kw ):
        actual   = self.currSv['PlaybackStorageMedium']
        expected = 'NETWORK'
        if self.currSv['AVTransportURI'] == '':
            expected = 'NONE'
        msg = 'PlaybackStorageMedium was %s expected %s' % (actual, expected)
        return (actual==expected, msg)    
    
    def _RelativeCounterPositionCheck( self, **kw ):
        actual     = self.currSv['RelativeCounterPosition']
        expected   = self._ExpectedRelativePosition( mode='count', **kw )
        msg        = 'RelativeCounterPosition was %d expected %d -> %d' \
                       % (actual, expected[0], expected[1])        
        return( expected[0] <= actual <= expected[1], msg )    
    
    def _RelativeTimePositionCheck( self, **kw ):
        actual   = self.currSv['RelativeTimePosition']
        expected = self._ExpectedRelativePosition( mode='time', **kw )
        msg      = 'RelativeTimePosition was %s expected one of %s' \
                       % (actual, expected)        
        return( actual in expected, msg )
    
    #
    # helper methods for SV 'checks'
    #  

    def _ExpectedRelativePosition( self, mode, **kw ):
        "Calculate the expected value for relative position SVs"
        expected = []
        
        if self.startState == 'PAUSED_UNKNOWN':
            if self.trans in ['Play']:
                expected = ['0:00:0%d' % (kDelay-1), '0:00:0%d' % (kDelay),'0:00:0%d' % (kDelay+1)]
            elif self.trans in ['Seek']:
                expected = self._SeekPosition( playing=True, mode=mode, **kw )
            else:
                if self.currSv['TransportState']=='PLAYING':
                    expected = ['0:00:0%d' % (kDelay-1), '0:00:0%d' % (kDelay),'0:00:0%d' % (kDelay+1)]
                else:
                    expected = ['0:00:00']
        
        elif self.prevSv['TransportState'] == 'PLAYING':
            if self.trans == 'Seek':
                expected = self._SeekPosition( playing=True, mode=mode, **kw )
            else:
                #if self.currSv['TransportState'] == 'PLAYING':
                #    expected = ['0:00:0%d' % (kDelay*2-1), '0:00:0%d' % (kDelay*2),'0:00:0%d' % (kDelay*2+1)]
                if self.currSv['TransportState'] in ['PLAYING','PAUSED_PLAYBACK']:
                    expected = ['0:00:0%d' % (kDelay-1), '0:00:0%d' % (kDelay),'0:00:0%d' % (kDelay+1)]
                else:
                    expected = ['0:00:00']
                
        elif self.prevSv['TransportState'] == 'STOPPED':
            if self.trans == 'Seek':
                expected = self._SeekPosition( playing=True, mode=mode, **kw )
            else:
                if self.currSv['TransportState']=='PLAYING':
                    expected = ['0:00:0%d' % (kDelay-1), '0:00:0%d' % (kDelay),'0:00:0%d' % (kDelay+1)]
                else:
                    expected = ['0:00:00']

        elif self.prevSv['TransportState'] == 'PAUSED_PLAYBACK':
            if self.trans == 'Seek':
                expected = self._SeekPosition( playing=True, mode=mode, **kw )
            elif self.trans in ['Next','Previous','SetAVTransportURI']:
                expected = self._StartOfTrack( playing=False, mode=mode, **kw )
            elif self.trans in ['Stop']:
                expected = self._StartOfTrack( playing=False, mode=mode, **kw )
            else:
                expected = self._PrevPosition( playing=True, mode=mode, **kw )
                
        return expected            

    def _StartOfTrack( self, playing, mode, **kw ):
        expected = {'time' : [['0:00:00'], ['0:00:0%d' % (kDelay*2-1),
                                            '0:00:0%d' % (kDelay*2),
                                            '0:00:0%d' % (kDelay*2+1)]],
                    'count': [[0,5000],    [0, 100000]]}
        if not playing:
            index = 0
        else:
            index = 1
        return expected[mode][index]

    def _SeekPosition( self, playing, mode, **kw ):
        "Calculate the position SV values after a Seek() action"
        target = kw.get( 'Target', None )
        unit   = kw.get( 'Unit',   None )
        
        if mode == 'time':
            if not playing:
                expected = [target]
            else:
                t = target.split( ':' )
                s = int(t[0])*3600 + int(t[1])*60 + int(t[2])
                if unit == 'REL_TIME':
                    s += self.playTime
                expected = [
                    '%d:%02d:%02d' % (s/3600,(s%3600)/60,s%60),
                    '%d:%02d:%02d' % ((s+1)/3600,((s+1)%3600)/60,(s+1)%60),
                    '%d:%02d:%02d' % ((s+2)/3600,((s+2)%3600)/60,(s+2)%60)]
        elif mode == 'count' and unit == 'REL_COUNT':
            target =  int( target )
            if not playing:
                expected = [target,target]
            else:
                expected = [target,target+100000]            
        else:
            # using time units in count seek or vv - no simple way of working
            # this out (or guaranteeing repeatability - so just force pass
            if mode == 'time':
                expected = [self.currSv['RelativeTimePosition']]
            else:
                expected = [int( self.currSv['RelativeCounterPosition'] ),
                            int( self.currSv['RelativeCounterPosition'] )]            
        return expected
    
    def _PrevPosition( self, playing, mode, **kw ):
        "Calculate the expected 'no-change' position SV values"
        if mode == 'time':
            prev = self.prevSv['RelativeTimePosition']
            if not playing:
                expected = [prev]
            else:
                t = prev.split( ':' )
                s = int(t[0])*3600 + int(t[1])*60 + int(t[2])
                expected = [
                    '%d:%02d:%02d' % (s/3600,(s%3600)/60,s%60),
                    '%d:%02d:%02d' % ((s+1)/3600,((s+1)%3600)/60,(s+1)%60),
                    '%d:%02d:%02d' % ((s+2)/3600,((s+2)%3600)/60,(s+2)%60)]            
        else:
            prev = self.prevSv['RelativeCounterPosition']
            if not playing:
                expected = [prev,prev]
            else:
                expected = [prev,prev+100000]
        return expected

    def _GetPositions( self, pos ):
        "Return passed in position, and same incremented by 1 sec"
        s = pos.split( ':' )
        exp  = int(s[0])*3600 + int(s[1])*60 + int(s[2])
        exp1 = exp + 1
        return ['%d:%02d:%02d' % (exp/3600,(exp%3600)/60,exp%60),
                '%d:%02d:%02d' % (exp1/3600,(exp1%3600)/60,exp1%60)]
        

if __name__ == '__main__':
    
    BASE.Run( sys.argv )
