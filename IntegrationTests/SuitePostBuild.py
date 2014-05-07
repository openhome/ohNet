"""SuitePostBuild - suite of tests for MediaPlayer testing which should be run
                    automatically post-build. Optimised to give maximum covarage
                    in minimum run-time

Parameters:
    arg#1 - [Optional] log directory

This suite of tests verifies ohMediaPlayer functionality using SoftPlayer(s)

 - Network interface to use for testing defined in local Config.xml
 - SoftPlayer instance(s) created/destroyed as required
"""
import _FunctionalTest
import BaseSuite as Suite
import os
import sys
 
logDir     = None

try:
    if len( sys.argv ) > 1:
        logDir = sys.argv[1]
except:
    print '\n', __doc__, '\n'
    print '\n\nInvalid arguments %s' % (str( sys.argv ))
    # noinspection PyProtectedMember
    os._exit( -1 )

    
tests = [
    # # UPnP AV
    # [ 'TestAvTransportPlayTracks',   'local', 'local',    ms,       avtList, 12,    1               ],

    # OH Playlist Service
    [ 'TestPlaylistPlayTracks',      'local', 'local',    ms,       medList, 12,    'off',     'on' ],

    # # OH Radio Service
    # [ 'TestRadioPlayChannels',       'local', 'local',    'klueso', 12,      'on'                   ],
]

Suite.Suite( tests, logDir, ['config','status','info'] )
