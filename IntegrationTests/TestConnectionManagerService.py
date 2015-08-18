#!/usr/bin/env python
"""TestConnectionManagerService - test UPnP AV ConnectionManager aervice

Parameters:
    arg#1 - MediaRenderer DUT ['local' for internal SoftPlayer on loopback]

Checks (what little) functionality offered by ConnectionManager service
"""
import _Paths
import CommonConnectionManagerService as BASE
import sys


class TestConnectionManagerService( BASE.CommonConnectionManagerService ):

    def __init__( self ):
        BASE.CommonConnectionManagerService.__init__( self )
        self.doc         = __doc__
        self.sourceProto = ''
        self.sinkProto   = 'http-get:*:audio/mp4:*,'                     +\
                           'http-get:*:application/vnd.apple.mpegurl:*,' +\
                           'http-get:*:audio/x-flac:*,'                  +\
                           'http-get:*:audio/wav:*,'                     +\
                           'http-get:*:audio/wave:*,'                    +\
                           'http-get:*:audio/x-wav:*,'                   +\
                           'http-get:*:audio/aiff:*,'                    +\
                           'http-get:*:audio/x-aiff:*,'                  +\
                           'http-get:*:audio/aifc:*,'                    +\
                           'http-get:*:audio/x-aifc:*,'                  +\
                           'http-get:*:audio/aac:*,'                     +\
                           'http-get:*:audio/aacp:*,'                    +\
                           'http-get:*:audio/x-m4a:*,'                   +\
                           'http-get:*:audio/mpeg:*,'                    +\
                           'http-get:*:audio/x-mpeg:*,'                  +\
                           'http-get:*:audio/mp1:*,'                     +\
                           'http-get:*:audio/ogg:*,'                     +\
                           'http-get:*:audio/x-ogg:*,'                   +\
                           'http-get:*:application/ogg:*,'               +\
                           'http-get:*:audio/x-mpegurl:*,'               +\
                           'http-get:*:audio/mpegurl:*,'                 +\
                           'http-get:*:audio/x-scpls:*,'                 +\
                           'http-get:*:text/xml:*,'                      +\
                           'tidalhifi.com:*:*:*,'                        +\
                           'qobuz.com:*:*:*'


if __name__ == '__main__':

    BASE.Run( sys.argv )
