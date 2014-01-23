"""SuiteAll - suite of all tests for MediaPlayer testing

Parameters:
    arg#1 - UPnP Media Server to use for tests
    arg#2 - [Optional] log directory

This suite of tests verifies ohMediaPlayer functionality using SoftPlayer(s)

 - Network interface to use for testing defined in local Config.xml
 - SoftPlayer instance(s) created/destryed as required
 - iTunes must be running on local machine (for Airplay testing)
 - UPnP media server with reqd. playlists must be available (for playlist soaks) 
"""
import _FunctionalTest
import BaseSuite as Suite
import os
import sys
 
logDir  = None
dut1    = '[' + os.environ['COMPUTERNAME'] + '-1]:SoftPlayer'
dut2    = '[' + os.environ['COMPUTERNAME'] + '-2]:SoftPlayer'
dut3    = '[' + os.environ['COMPUTERNAME'] + '-3]:SoftPlayer'
dut4    = '[' + os.environ['COMPUTERNAME'] + '-4]:SoftPlayer'

dacpServer = os.environ['COMPUTERNAME']
avtList = 'Playlists  ~Encodings-FreeCodecs'
medList = 'Playlists  ~5TrackAlbumsFreeCodecs'
adList  = 'Playlists  ~Mixed-FreeCodecs'


try:
    ms = sys.argv[1]
    if len( sys.argv ) > 2:
        logDir = sys.argv[2]
except:
    print '\n', __doc__, '\n'
    print '\n\nInvalid arguments %s' % (str( sys.argv ))
    os._exit( -1 )

    
# songcast modes, playlists etc will have to be controlled from the StartPlayer
# controls as no Config service on device. Hence these controls have been removed
# from the test parameters and will be setup in some sort of standalone-dut-setup
# prior to running the actual tests    
    
    
tests = [
    # Start the SoftPlayer devices-under-test
#    [ 'TestStartPlayer',             'dut1'                                                                                                             ]
#    [ 'TestStartPlayer',             'dut2'                                                                                                             ],
#    [ 'TestStartPlayer',             'dut3'                                                                                                             ],
#    [ 'TestStartPlayer',             'dut4'                                                                                                             ],
    
    # UPnP AV          
    [ 'TestAvTransportService',      'dut1', 'ALL'                                                                                                      ],
    [ 'TestRenderingControlService', 'dut1'                                                                                                             ],
    [ 'TestAvTransportPlayTracks',   'dut1', 'dut2',       'ms',        avtList,     12,          1                                                     ],

    # OH Playlist Service
#    [ 'TestPlaylistHandling',        'dut1', 'all',        12345                                                                                        ],
#    [ 'TestPlaylistModes',           'dut1', 'all',        12345                                                                                        ],
#    [ 'TestPlaylistPlayback',        'dut1', 'all',        12345                                                                                        ],
    [ 'TestPlaylistAddDelSoak',      'dut1', 'ms',         adList,      100                                                                             ],
    [ 'TestPlaylistPlayTracks',      'dut1', 'dut2',       'ms',        medList,     12,          'off',      'on'                                      ],       
    [ 'TestPlaylistDropout',         'dut1', 'dut2',       'dut3',      '3600'                                                                          ],       

    # OH Radio Service
#    [ 'TestRadioService',            'dut1', 'all'                                                                                                      ],
#    [ 'TestRadioPlayChannels',       'dut1', 'dut2',       'klueso',    12,          'on',        'unicast'                                             ],
    
    # Airplay
    [ 'TestAirplayFunctions',        'dut1', 'dacpServer'                                                                                               ],
#    [ 'TestAirplayDropout',          'dut1', 'dacpServer', apTrack,     '3600'                                                                          ],       

    # Songcast
#    [ 'TestSongcastPlayback',        'dut1', 'dut2',       'dut3',      'dut4',      'unicast',   'all',      12345,       1,           'fails', 'file' ],
#    [ 'TestSongcastPlayback',        'dut1', 'dut2',       'dut3',      'dut4',      'multicast', 'all',      54321,       1,           'fails', 'file' ],
#    [ 'TestSongcastConnect',         'dut1', 'dut2',       'dut3',      'dut4',      'all',       'stop',     'unicast',   1,           'fails', 'file' ],
#    [ 'TestSongcastConnect',         'dut1', 'dut2',       'dut3',      'dut4',      'all',       'source',   'multicast', 1,           'fails', 'file' ],
#    [ 'TestSongcastConnect',         'dut1', 'dut2',       'dut3',      'dut4',      'all',       'sender',   'unicast',   1,           'fails', 'file' ],
#    [ 'TestSongcastConnect',         'dut1', 'dut2',       'dut3',      'dut4',      'all',       'standby',  'multicast', 1,           'fails', 'file' ],
#    [ 'TestSongcastConnect',         'dut1', 'dut2',       'dut3',      'dut4',      'all',       'reboot',   'unicast',   1,           'fails', 'file' ],
#    [ 'TestSongcastDelay',           'dut1', 'None',       'dut2',      'unicast' ,  'fails',     'file'                                                ],
#    [ 'TestSongcastDelay',           'dut1', 'None',       'dut2',      'multicast', 'fails',     'file'                                                ],    
#    [ 'TestSongcastDelay',           'dut2', 'None',       'dut1',      'unicast' ,  'fails',     'file'                                                ],
#    [ 'TestSongcastDelay',           'dut2', 'None',       'dut1',      'multicast', 'fails',     'file'                                                ],    
#    [ 'TestSongcastDropout',         'dut2', 'dut1',       'unicast',   0,           600,                                                               ],    
#    [ 'TestSongcastDropout',         'dut2', 'dut1',       'multicast', 0,           600,                                                               ],    

    # Volume
#    [ 'TestVolumeControl',           'dut1', 'volume',     'fails',     'file'                                                                          ],
#    [ 'TestVolumeControl',           'dut1', 'balance',    'fails',     'file'                                                                          ],
#    [ 'TestVolumeControl',           'dut1', 'unity',      'fails',     'file'                                                                          ],
#    [ 'TestVolumeControl',           'dut1', 'offset',     'fails',     'file'                                                                          ],
#    [ 'TestVolumeControl',           'dut1', 'inputlevel', 'fails',     'file'                                                                          ],
#    [ 'TestVolumeControl',           'dut1', 'startup',    'fails',     'file'                                                                          ],
    
    # Misc
#    [ 'TestAudioConx',               'dut1', 'all'                                                                                                      ],
    [ 'TestStandbyCycleSoak',        'dut1',  100                                                                                                       ],
    
    # Shutdown the SoftPlayers
#    [ 'TestStopPlayer',            'dut1'                                                                                                               ],
#    [ 'TestStopPlayer',            'dut2'                                                                                                               ],    
#    [ 'TestStopPlayer',            'dut3'                                                                                                               ],    
#    [ 'TestStopPlayer',            'dut4'                                                                                                               ]    
]

Suite.Suite( tests, logDir, ['config','status','info'] )
