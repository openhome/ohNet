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
 
ms         = None
logDir     = None
dacpServer = os.environ['COMPUTERNAME']
avtList    = 'Playlists  ~Encodings-FreeCodecs'
mpList     = 'Playlists  ~Mixed-FreeCodecs'
apTrack    = 'Stereo1kHz-441-16-0dB-72m' 

try:
    ms = sys.argv[1]
    if len( sys.argv ) > 2:
        logDir = sys.argv[2]
except:
    print '\n', __doc__, '\n'
    print '\n\nInvalid arguments %s' % (str( sys.argv ))
    # noinspection PyProtectedMember
    os._exit( -1 )

    
tests = [
    # UPnP AV          
#    [ 'TestAvTransportService',      'local', 'ALL'                                                             ],
#    [ 'TestRenderingControlService', 'local'                                                                    ],
   [ 'TestAvTransportPlayTracks',   'local', 'local',    ms,       avtList,  8,    1,         'false'          ],

    # OH Playlist Service
    [ 'TestPlaylistHandling',        'local', 'all',      12345                                                ],
    [ 'TestPlaylistModes',           'local', 'all',      54321                                                ],
    [ 'TestPlaylistPlayback',        'local', 'all',      12345                                                ],
#    [ 'TestPlaylistAddDelSoak',      'local', ms,         adList,   100                                         ],
    [ 'TestPlaylistPlayTracks',      'local', 'local',    ms,       mpList,   8,    'off',     'on',    'false' ],
#    [ 'TestPlaylistDropout',         'local', 'local',    'local',  '3600'                          ],

    # OH Radio Service
#    [ 'TestRadioService',            'local', 'all'                                                 ],
    [ 'TestRadioPlayChannels',       'local', 'local',    'ohmp2',  20,       'on', 1               ],
    
    # Airplay
#    [ 'TestAirplayFunctions',        'local', dacpServer                                            ],
#    [ 'TestAirplayDropout',          'local', dacpServer, apTrack,  '3600'                          ],

    # Songcast
#    [ 'TestSongcastPlayback',        'local', 'local',    'local',  'all',   12345                  ],
#    [ 'TestSongcastConnect',         'local', 'local',    'local',  'local', 'all', 'stop'          ],
#    [ 'TestSongcastConnect',         'local', 'local',    'local',  'local', 'all', 'source'        ],
#    [ 'TestSongcastConnect',         'local', 'local',    'local',  'local', 'all', 'sender'        ],
#    [ 'TestSongcastConnect',         'local', 'local',    'local',  'local', 'all', 'standby'       ],
#    [ 'TestSongcastDropout',         'local', 'local',    600,                                      ],

    # Volume
#    [ 'TestVolumeControl',           'local'                                                        ],
    
    # Misc
#    [ 'TestAudioConx',               'local', 'all'                                                 ],
#    [ 'TestStandbyCycleSoak',        'local',  100                                                  ]
    
    # N/A to SoftPlayer(s)
    #    - AutoPlay
    #    - CrossoverBitstreamLoad
    #    - CrossoverOperation
    #    - DelayOperation'
    #    - DelayService
    #    - DigitalInDecode
    #    - DigitalOutType
    #    - RebootSoak
    #    - SongcastDelay
    #    - SourceControl
    #    - SourceSelectSoak
    #    - VolumeControl            unity/offset/inputLevel/startup
]

Suite.Suite( tests, logDir, ['config','status','info'] )
