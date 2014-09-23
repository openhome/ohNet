"""SuiteLocal - suite of all tests for MediaPlayer testing using local (to 
                individual tests)  SoftPlayer(s) as DUT(s)

Parameters:
    arg#1 - UPnP Media Server to use for tests
    arg#2 - DACP (iTunes) server PC
    arg#3 - [Optional] log directory

This suite of tests verifies ohMediaPlayer functionality using SoftPlayer(s).
Loopback adapter is used where practical (so all cases except for Airplay and
where external media server is required - ohNet does not allow mix of local
loopback and standard adapter devices within single process space)

 - Network interface to use for testing defined in local Config.xml
 - SoftPlayer instance(s) created/destryed as required
 - iTunes server must be available (for Airplay testing)
 - UPnP media server with reqd. playlists must be available (for playlist soaks) 
"""
import _FunctionalTest
import BaseSuite as Suite
import os
import sys
 
ms      = None
logDir  = None
dacp    = None
avtList = 'Playlists  ~Encodings-FreeCodecs'
mpList  = 'Playlists  ~Mixed-FreeCodecs'
apTrack = 'Stereo1kHz-441-16-0dB-72m'

try:
    ms = sys.argv[1]
    dacp = sys.argv[2]
    if len( sys.argv ) > 3:
        logDir = sys.argv[3]
except:
    print '\n', __doc__, '\n'
    print '\n\nInvalid arguments %s' % (str( sys.argv ))
    # noinspection PyProtectedMember
    os._exit( -1 )

    
tests = [
    # # UPnP AV
    # [ 'TestAvTransportService',      'local', 'ALL'                                                          ],
    # [ 'TestRenderingControlService', 'local'                                                                 ],
    # [ 'TestAvTransportPlayTracks',   'local', 'local', ms,       avtList,  8,    1,         'false'          ],

    # OH Playlist Service
    [ 'TestPlaylistHandling',        'local', 'all',   0                                                     ],
    [ 'TestPlaylistModes',           'local', 'all',   0                                                     ],
    [ 'TestPlaylistPlayback',        'local', 'all',   0                                                     ],
    [ 'TestPlaylistAddDelSoak',      'local', ms,      mpList,   100                                         ],
    [ 'TestPlaylistPlayTracks',      'local', 'local', ms,       mpList,   8,    'off',     'on',    'false' ],
    [ 'TestPlaylistDropout',         'local', 'local', 'local',  '3600'                                      ],

    # OH Radio Service
    [ 'TestRadioService',            'local', 'all'                                                          ],
    [ 'TestRadioPlayChannels',       'local', 'local', 'ohmp2',  20,       'on', 1                           ],

    # Airplay
    [ 'TestAirplayFunctions',        'local', dacp                                                           ],
    [ 'TestAirplayDropout',          'local', dacp,    apTrack,  '3600'                                      ],

    # # Songcast
    # [ 'TestSongcastPlayback',        'local', 'local', 'local',  'all',   12345                              ],
    # [ 'TestSongcastConnect',         'local', 'local', 'local',  'local', 'all', 'stop'                      ],
    # [ 'TestSongcastConnect',         'local', 'local', 'local',  'local', 'all', 'source'                    ],
    # [ 'TestSongcastConnect',         'local', 'local', 'local',  'local', 'all', 'sender'                    ],
    # [ 'TestSongcastConnect',         'local', 'local', 'local',  'local', 'all', 'standby'                   ],
    # [ 'TestSongcastDropout',         'local', 'local', 600,                                                  ],

    # Volume
    [ 'TestVolumeControl',           'local'                                                                 ],

    # # Misc
    # [ 'TestAudioConx',               'local', 'all'                                                          ],
    # [ 'TestStandbyCycleSoak',        'local',  100                                                           ]
    
    # N/A to SoftPlayer(s)
    #    - AutoPlay
    #    - DelayXXX
    #    - DigitalInDecode
    #    - DigitalOutType
    #    - ExaktXXX
    #    - RebootSoak
    #    - SongcastDelay
    #    - SourceXXX
    #    - VolumeXXX   (apart from volume/balance)
]

Suite.Suite( tests, logDir, ['config','status'] )
