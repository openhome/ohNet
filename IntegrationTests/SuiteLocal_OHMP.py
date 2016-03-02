"""SuiteLocal - suite of all tests for MediaPlayer testing using local (to 
                individual tests)  SoftPlayer(s) as DUT(s)

Parameters:
    arg#1 - clean/nobuild (pull/clean/build vs. use pre-existing source/deps/executable)
    arg#2 - [Optional] log directory

This suite of tests verifies ohMediaPlayer functionality using SoftPlayer(s).
Loopback adapter is used where practical (so all cases except for Airplay and
where external media server is required - ohNet does not allow mix of local
loopback and standard adapter devices within single process space)

 - Network interface to use for testing defined in test configuration XML
 - SoftPlayer instance(s) created/destryed as required
 - iTunes server must be available (for Airplay testing)
 - UPnP media server with reqd. playlists must be available (for playlist soaks) 
"""
import _Paths
import BaseSuite as Suite
import Config
import os
import sys

config = None
logDir = None
mode   = None

try:
    mode = sys.argv[1].lower()
    if len( sys.argv ) > 2:
        logDir = sys.argv[2]
except:
    print( '\n%s\n' % __doc__ )
    print( '\nInvalid arguments %s' % (str( sys.argv )) )
    # noinspection PyProtectedMember
    os._exit( -1 )

if mode not in ['nobuild', 'clean']:
    print( '\n%s\n' % __doc__ )
    print( 'Invalid mode: %s' % mode )
    # noinspection PyProtectedMember
    os._exit( -1 )


try:
    config = Config.Config()
except:
    import time
    time.sleep( 2 )
    # noinspection PyProtectedMember
    os._exit( -1 )
radio2    = config.Get( 'tunein.user.o2' )
radio4    = config.Get( 'tunein.user.o4' )
plEnc     = config.Get( 'playlist.enc-free' )
plMix     = config.Get( 'playlist.mixed-free' )
server    = config.Get( 'mediaserver.name' )
tidalId   = config.Get( 'tidal.id' )
tidalUser = config.Get( 'tidal.user' )
tidalPwd  = config.Get( 'tidal.password' )
qobuzId   = config.Get( 'qobuz.id' ) + ':' + config.Get( 'qobuz.secret' )
qobuzUser = config.Get( 'qobuz.user' )
qobuzPwd  = config.Get( 'qobuz.password' )

tests = [
    # UPnP compliance
    [ 'TestComplianceDevice',         'local'                                                                                        ],

    # OH Playlist Service
    [ 'TestPlaylistHandling',         'local', 'all',   0                                                                            ],
    [ 'TestPlaylistModes',            'local', 'all',   0                                                                            ],
    [ 'TestPlaylistPlayback',         'local', 'all',   0                                                                            ],
    [ 'TestPlaylistAddDelSoak',       'local',  server, plEnc,   100                                                                 ],
    [ 'TestLocalPlayTracks',          'local', 'none',  8,       'off',   'on'                                                       ],
    [ 'TestLocalPlayTracks',          'local', 'none',  'none',  'off',   'on',        'hls'                                         ],
    [ 'TestUpnpMsPlayTracks',         'local', 'none',  8,       'off',   'off',       server,      plEnc                            ],
    [ 'TestLocalDropout',             'local', 'local', 'local', 1800,    'multicast'                                                ],
    [ 'TestLocalDropout',             'local', 'local', 'local', 1800,    'unicast'                                                  ],
    [ 'TestUpnpMsDropout',            'local', 'none',  'none',  1800,    'multicast', server,      plEnc                            ],

    # OH Radio Service
    [ 'TestRadioService',             'local', 'all'                                                                                 ],
    [ 'TestRadioPlayChannels',        'local', 'none',  radio2,  10,      'on',        1                                             ],
    [ 'TestRadioPlayChannels',        'local', 'none',  radio4,  10,      'on',        1                                             ],

    # Tidal
    [ 'TestTidalPlayTracks',          'local', 'none',  8,       'off',   'off',       120,         tidalId,     tidalUser, tidalPwd ],
    [ 'TestTidalDropout',             'local', 'none',  'none',  1800,    'unicast',   20,          tidalId,     tidalUser, tidalPwd ],

    # Qobuz
    [ 'TestQobuzPlayTracks',          'local', 'none',  8,       'off',   'off',       120,         qobuzId,     qobuzUser, qobuzPwd ],
    [ 'TestQobuzDropout',             'local', 'none',  'none',  1800,    'unicast',   20,          qobuzId,     qobuzUser, qobuzPwd ],

    # Airplay
    [ 'TestAirplayFunctions',         'local'                                                                                        ],
    [ 'TestAirplayDropout',           'local', '1800'                                                                                ],

    # UPnP AV
    [ 'TestAvTransportService',       'local', 'ALL'                                                                                 ],
    [ 'TestRenderingControlService',  'local'                                                                                        ],
    [ 'TestConnectionManagerService', 'local'                                                                                        ],
    [ 'TestAvTransportPlayTracks',    'local', 'none',  'none',  'full',  10,          1,           'true'                           ],
    [ 'TestAvTransportPlayTracks',    'local', 'none',  server,  plMix,   8,           1,           'false'                          ],

    # Songcast
    [ 'TestSongcastPlayback',         'local', 'local', 'local', 'all',    0,          'unicast'                                     ],
    [ 'TestSongcastPlayback',         'local', 'local', 'local', 'all',    0,          'multicast'                                   ],
    [ 'TestSongcastConnect',          'local', 'local', 'local', 'local', 'all',       'stop',      'unicast'                        ],
    [ 'TestSongcastConnect',          'local', 'local', 'local', 'local', 'all',       'stop',      'multicast'                      ],
    [ 'TestSongcastConnect',          'local', 'local', 'local', 'local', 'all',       'source',    'unicast'                        ],
    [ 'TestSongcastConnect',          'local', 'local', 'local', 'local', 'all',       'source',    'multicast'                      ],
    [ 'TestSongcastConnect',          'local', 'local', 'local', 'local', 'all',       'sender',    'unicast'                        ],
    [ 'TestSongcastConnect',          'local', 'local', 'local', 'local', 'all',       'sender',    'multicast'                      ],
    [ 'TestSongcastConnect',          'local', 'local', 'local', 'local', 'all',       'standby',   'unicast'                        ],
    [ 'TestSongcastConnect',          'local', 'local', 'local', 'local', 'all',       'standby',   'multicast'                      ],

    # Sources
    [ 'TestSourceSelect',             'local'                                                                                        ],

    # Volume
    [ 'TestVolumeService',            'local'                                                                                        ],

    # Misc
    [ 'TestAudioConx',                'local', 'all'                                                                                 ],
    [ 'TestStandbyCycleSoak',         'local',  100                                                                                  ],

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

if mode == 'clean':
    # Update and build ohMediaPlayer before other tests
    tests.insert(0, [ 'BuildOhmp', 'debug' ])

Suite.Suite( tests, logDir )
