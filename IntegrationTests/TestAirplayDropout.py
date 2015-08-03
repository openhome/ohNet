#!/usr/bin/env python
"""TestAirplayDropout - test for audio dropout on Net Aux source using AirPlay

Parameters:
    arg#1 - DUT ['local' for internal SoftPlayer]
    arg#2 - Test duration (secs) or 'forever'
    
Verifies AirPlay audio output by the DUT does not suffer from audio dropout
""" 
import _Paths
import CommonAirplayDropout as BASE
import LogThread
import sys
import threading


class TestAirplayDropout( BASE.CommonAirplayDropout ):

    def __init__( self ):
        """Constructor for Airplay Dropout test"""
        BASE.CommonAirplayDropout.__init__( self )
        self.doc      = __doc__
        self.finished = threading.Event()

    def MonitorDropout( self, aDuration ):
        """monitor dropout - does nothing (other than let playback continue)"""
        if aDuration != 'forever':
            timer = LogThread.Timer( aDuration, self.__DurationCb )
            timer.start()
        self.finished.wait()

    def __DurationCb( self ):
        """Duration timer CB - called to end test after specified time"""
        self.finished.set()

    def _TickCb( self ):
        """Progress monitor"""
        try:
            info = self.dacp.nowPlaying
            self.log.Info( self.dacp.dev, info )
        except:
            # DACP has thrown connection error
            self.dacp = None
        if not self.shuttingDown:
            self.tick = LogThread.Timer( 1, self._TickCb )
            self.tick.start()


if __name__ == '__main__':
    
    BASE.Run( sys.argv )
        