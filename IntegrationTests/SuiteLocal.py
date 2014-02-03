"""SuiteLocal - suite of all tests for MediaPlayer testing using local (to 
                individual tests)  SoftPlayer(s) as DUT(s)

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
 
logDir     = None
dacpServer = os.environ['COMPUTERNAME']
avtList    = 'Playlists  ~Encodings-FreeCodecs'
medList    = 'Playlists  ~5TrackAlbumsFreeCodecs'
adList     = 'Playlists  ~Mixed-FreeCodecs'


try:
    ms = sys.argv[1]
    if len( sys.argv ) > 2:
        logDir = sys.argv[2]
except:
    print '\n', __doc__, '\n'
    print '\n\nInvalid arguments %s' % (str( sys.argv ))
    os._exit( -1 )

    
tests = [
    # UPnP AV          
    [ 'TestAvTransportService',      'local', 'ALL'                                                                                         ],
    [ 'TestRenderingControlService', 'local'                                                                                                ],
    [ 'TestAvTransportPlayTracks',   'local', 'local',    ms,          avtList,     12,          1                                          ],

    # OH Playlist Service
#    [ 'TestPlaylistHandling',        'local', 'all',      12345                                                                             ],
#    [ 'TestPlaylistModes',           'local', 'all',      12345                                                                             ],
#    [ 'TestPlaylistPlayback',        'local', 'all',      12345                                                                             ],
    [ 'TestPlaylistAddDelSoak',      'local', ms,         adList,      100                                                                  ],
    [ 'TestPlaylistPlayTracks',      'local', 'local',    ms,          medList,     12,          'off',      'on'                           ],       
    [ 'TestPlaylistDropout',         'local', 'local',    'local',     '3600'                                                               ],       

    # OH Radio Service
#    [ 'TestRadioService',            'local', 'all'                                                                                         ],
#    [ 'TestRadioPlayChannels',       'local', 'local',    'klueso',    12,          'on',        'unicast'                                  ],
    
    # Airplay
    [ 'TestAirplayFunctions',        'local', dacpServer                                                                                    ],
#    [ 'TestAirplayDropout',          'local', dacpServer, apTrack,     '3600'                                                               ],       

    # Songcast
#    [ 'TestSongcastPlayback',        'local', 'local',    'local',     'local',     'unicast',   'all',     12345,       1, 'fails', 'file' ],
#    [ 'TestSongcastPlayback',        'local', 'local',    'local',     'local',     'multicast', 'all',     54321,       1, 'fails', 'file' ],
#    [ 'TestSongcastConnect',         'local', 'local',    'local',     'local',     'all',       'stop',    'unicast',   1, 'fails', 'file' ],
#    [ 'TestSongcastConnect',         'local', 'local',    'local',     'local',     'all',       'source',  'multicast', 1, 'fails', 'file' ],
#    [ 'TestSongcastConnect',         'local', 'local',    'local',     'local',     'all',       'sender',  'unicast',   1, 'fails', 'file' ],
#    [ 'TestSongcastConnect',         'local', 'local',    'local',     'local',     'all',       'standby', 'multicast', 1, 'fails', 'file' ],
#    [ 'TestSongcastConnect',         'local', 'local',    'local',     'local',     'all',       'reboot',  'unicast',   1, 'fails', 'file' ],
#    [ 'TestSongcastDelay',           'local', 'None',     'local',     'unicast' ,  'fails',     'file'                                     ],
#    [ 'TestSongcastDelay',           'local', 'None',     'local',     'multicast', 'fails',     'file'                                     ],    
#    [ 'TestSongcastDelay',           'local', 'None',     'local',     'unicast' ,  'fails',     'file'                                     ],
#    [ 'TestSongcastDelay',           'local', 'None',     'local',     'multicast', 'fails',     'file'                                     ],    
#    [ 'TestSongcastDropout',         'local', 'local',    'unicast',   0,           600,                                                    ],    
#    [ 'TestSongcastDropout',         'local', 'local',    'multicast', 0,           600,                                                    ],    

    # Volume
#    [ 'TestVolumeControl',           'local', 'volume',   'fails',     'file'                                                               ],
#    [ 'TestVolumeControl',           'local', 'balance',  'fails',     'file'                                                               ],
#    [ 'TestVolumeControl',           'local', 'startup',  'fails',     'file'                                                               ],
    
    # Misc
#    [ 'TestAudioConx',               'local', 'all'                                                                                         ],
    [ 'TestStandbyCycleSoak',        'local',  100                                                                                          ]
]

Suite.Suite( tests, logDir, ['config','status','info'] )
