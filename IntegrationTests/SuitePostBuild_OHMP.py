"""SuitePostBuild - suite of tests for MediaPlayer testing which should be run
                    automatically post-build. Optimised to give maximum covarage
                    in minimum run-time

Parameters:
    arg#1 - [Optional] log directory

This suite of tests verifies ohMediaPlayer functionality using SoftPlayer(s)

 - Network interface to use for testing defined in test configuration XML
 - SoftPlayer instance(s) created/destroyed as required
"""
import _Paths
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
    print( '\n%s\n' % __doc__ )
    print( '\n\nInvalid arguments %s' % (str( sys.argv )) )
    # noinspection PyProtectedMember
    os._exit( -1 )

try:
    config = Config.Config()
except:
    import time
    time.sleep( 2 )
    # noinspection PyProtectedMember
    os._exit( -1 )
tunein = config.Get( 'tunein.user.o4' )

tests = [
    # # UPnP AV
    # [ 'TestAvTransportPlayTracks', 'local', 'None',  'None',  'short', 6,    1                   ],

    # OH Playlist Service
    [ 'TestLocalPlayTracks',       'local', 'None',  6,       'off',   'on', 'short'             ],

    # OH Radio Service (all locally served channels)
    [ 'TestRadioPlayChannels',     'local', 'None',  tunein,  6,       'on'                      ],

    # Songcast (OHU/OHZ protocol)
    [ 'TestSongcastConnect',       'local', 'local', 'local', 'local', '4',   'stop',  'unicast' ],

    # Sources selection (Product service)
    [ 'TestSourceSelect',          'local'                                                       ],

    # Volume operation
    [ 'TestVolumeService',         'local'                                                       ]
]

Suite.Suite( tests, logDir )
