#!/usr/bin/env python
"""TestPlaylistHandling - test Playlist controls (insert/delete/select mode)

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer on loopback]
    arg#2 - test mode 
              - all          for all configs sequentially
              - <num>        for config number <num>
              - [min:max]    for range of (numbered) configs
              - <stim>       for stimulus (Play, Pause, Stop,
                                    SeekSecondsAbsolute, SeekSecondsRelative,
                                    SeekTrackAbsolute, SeekTrackRelative)
              - <pre-state>  for precon state (Stopped, Playing, Paused)
    arg#3 - random number generator seed (0 for 'random')
            by passing this, test scenarious containing random data can be
            replicated - the seed used is logged at the start of execution
            
Tests operation of Playlist control. Each condition is tested as a standalone
operation - no aggregation of actions due to async operation tested.
"""
import _Paths
import CommonPlaylistHandling as BASE
import sys


class TestPlaylistHandling( BASE.CommonPlaylistHandling ):

    def __init__( self ):
        BASE.CommonPlaylistHandling.__init__( self )
        self.doc          = __doc__
        self.protocolInfo = 'http-get:*:audio/mp4:*,'                       +\
                            'http-get:*:application/vnd.apple.mpegurl:*,'   +\
                            'http-get:*:audio/x-flac:*,'                    +\
                            'http-get:*:audio/wav:*,'                       +\
                            'http-get:*:audio/wave:*,'                      +\
                            'http-get:*:audio/x-wav:*,'                     +\
                            'http-get:*:audio/aiff:*,'                      +\
                            'http-get:*:audio/x-aiff:*,'                    +\
                            'http-get:*:audio/aifc:*,'                      +\
                            'http-get:*:audio/x-aifc:*,'                    +\
                            'http-get:*:audio/aac:*,'                       +\
                            'http-get:*:audio/aacp:*,'                      +\
                            'http-get:*:audio/x-m4a:*,'                     +\
                            'http-get:*:audio/mpeg:*,'                      +\
                            'http-get:*:audio/x-mpeg:*,'                    +\
                            'http-get:*:audio/mp1:*,'                       +\
                            'http-get:*:audio/ogg:*,'                       +\
                            'http-get:*:audio/x-ogg:*,'                     +\
                            'http-get:*:application/ogg:*,'                 +\
                            'http-get:*:audio/x-mpegurl:*,'                 +\
                            'http-get:*:audio/mpegurl:*,'                   +\
                            'http-get:*:audio/x-scpls:*,'                   +\
                            'http-get:*:text/xml:*,'                        +\
                            'tidalhifi.com:*:*:*,'                          +\
                            'qobuz.com:*:*:*'


if __name__ == '__main__':

    BASE.Run( sys.argv )
