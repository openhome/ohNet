"""SuiteLocal - suite of all tests for MediaPlayer testing using local (to 
                individual tests)  SoftPlayer(s) as DUT(s)

Parameters:
    arg#1 - [Optional] log directory

This suite of tests verifies ohMediaPlayer functionality using SoftPlayer(s).
Loopback adapter is used where practical (so all cases except for Airplay and
where external media server is required - ohNet does not allow mix of local
loopback and standard adapter devices within single process space)

 - Network interface to use for testing defined in test configuration XML
 - SoftPlayer instance(s) created/destryed as required
 - iTunes server must be available (for Airplay testing)
 - UPnP media server with reqd. playlists must be available (for playlist soaks) 
"""
import _FunctionalTest
import BaseSuite as Suite
import Config
import os
import sys
 
config = None
logDir = None

try:
    if len( sys.argv ) > 1:
        logDir = sys.argv[1]
except:
    print '\n', __doc__, '\n'
    print '\n\nInvalid arguments %s' % (str( sys.argv ))
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
plEnc     = config.Get( 'playlist.asset.enc-free' )
plMix     = config.Get( 'playlist.asset.mixed-free' )
server    = config.Get( 'mediaserver.asset' )
tidalId   = config.Get( 'tidal.id' )
tidalUser = config.Get( 'tidal.user' )
tidalPwd  = config.Get( 'tidal.password' )

tests = [
    # Update and build ohMediaPlayer
#    [ 'BuildOhmp',                   'debug'                                                                              ],
    [ 'BuildOhmp'                                                                                                         ],

    # OH Playlist Service
    [ 'TestPlaylistHandling',        'local', 'all',   0                                                                  ],
    [ 'TestPlaylistModes',           'local', 'all',   0                                                                  ],
    [ 'TestPlaylistPlayback',        'local', 'all',   0                                                                  ],
    [ 'TestPlaylistAddDelSoak',      'local',  server, plEnc,   100                                                       ],
    [ 'TestLocalPlayTracks',         'local', 'local', 8,       'off',   'on'                                             ],
    [ 'TestUpnpMsPlayTracks',        'local', 'local', 8,       'off',   'on',   server,   plEnc                          ],
    [ 'TestLocalDropout',            'local', 'local', 'local', 1800                                                      ],
    [ 'TestUpnpMsDropout',           'local', 'local', 'local', 1800,    server, plEnc                                    ],

    # OH Radio Service
    [ 'TestRadioService',            'local', 'all'                                                                       ],
    [ 'TestRadioPlayChannels',       'local', 'local', radio2,  10,      'on',   1                                        ],
    [ 'TestRadioPlayChannels',       'local', 'local', radio4,  10,      'on',   1                                        ],

    # Tidal
    [ 'TestTidalPlayTracks',         'local', 'local', 8,       'off',   'off',  120,      tidalId,   tidalUser, tidalPwd ],
    [ 'TestTidalDropout',            'local', 'local', 'local', 3600,    20,     tidalId,  tidalUser, tidalPwd            ],

    # Airplay
    [ 'TestAirplayFunctions',        'local'                                                                              ],
    [ 'TestAirplayDropout',          'local', '3600'                                                                      ],

    # UPnP AV
    [ 'TestAvTransportService',      'local', 'ALL'                                                                       ],
    [ 'TestRenderingControlService', 'local'                                                                              ],
    [ 'TestAvTransportPlayTracks',   'local', 'local', server,  plMix,   8,      1,        'false'                        ],

    # Songcast
    [ 'TestSongcastPlayback',        'local', 'local', 'local', 'all',   12345                                            ],
    [ 'TestSongcastConnect',         'local', 'local', 'local', 'local', 'all',  'stop'                                   ],
    [ 'TestSongcastConnect',         'local', 'local', 'local', 'local', 'all',  'source'                                 ],
    [ 'TestSongcastConnect',         'local', 'local', 'local', 'local', 'all',  'sender'                                 ],
    [ 'TestSongcastConnect',         'local', 'local', 'local', 'local', 'all',  'standby'                                ],

    # Volume
    [ 'TestVolumeControl',           'local'                                                                              ],

    # Misc
    [ 'TestAudioConx',               'local', 'all'                                                                       ],
    [ 'TestStandbyCycleSoak',        'local',  100                                                                        ]
    
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

Suite.Suite( tests, logDir )
