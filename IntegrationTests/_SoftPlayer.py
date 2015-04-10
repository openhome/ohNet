"""Wrapper for TestMediaPlayer executable

Wraps the TestmediaPlayer executable to permit simple start/stop/configuration 
from integration tests, and to capture SoftPlayer output to test logs
"""

import _FunctionalTest
import Component as BASE
import Config
import LogThread
import os
import platform
import random
import subprocess
import threading
import time
import xml.etree.ElementTree as ET

_platform = platform.system()
if _platform in ['Windows', 'cli']:
    kExe = os.path.join( 'install', 'bin', 'TestMediaPlayer.exe' )
elif _platform in ['Linux', 'Darwin']:
    kExe = os.path.join( 'install', 'bin', 'TestMediaPlayer' )

class SoftPlayer( BASE.Component ):
    """Class to wrap SoftPlayer executable (TestMediaPlayer.exe)"""
    
    def __init__( self, 
                  aRoom          = None,     # defaults to 'SoftPlayer'
                  aModel         = None,     # defaults to 'SoftPlayer'
                  aTuneInId      = None,     # defaults to ''
                  aLoopback      = False,    # defaults to False
                  aTidalId       = None,     # defaults to Tidal disabled
                  aQobuzId       = None,     # defaults to qobuz disabled (format id:secret)
                  aSenderChannel = None ):   # defaults to a random value
        """Start the SoftPlayer - all parameters are optional and will default
        as described above. These 'configuration' options cannot be changed on
        a running SoftPlayer, so have to be initialised at creation"""
        BASE.Component.__init__( self )
        self.testConfig = Config.Config()
        self.shutdown   = False
        self.room       = None
        self.model      = None

        hostId = self.testConfig.Get( 'softplayer.adapter' )
        if hostId is not None:
            hostId = int( hostId )

        random.seed()
        uniqueId = '%06d' % random.randint( 0, 999999 )

        if aRoom is None:
            self.room = 'SoftPlayer-' + uniqueId
        else:
            self.room = aRoom + '-' + uniqueId
        self.dev = '[' + self.room + ']'

        if aModel is None:
            self.model = 'SoftPlayer'
        else:
            self.model = aModel

        exePath = ''        
        path1 = os.path.abspath( os.path.join( '.', kExe ))
        path2 = os.path.abspath( os.path.join( '..', kExe ))
        if os.path.isfile( path1 ):
            exePath = path1
        elif os.path.isfile( path2 ):
            exePath = path2
        else:
            self.log.Abort( '', 'No SoftPlayer executable found' )
        self.log.Info( '', 'Using SoftPlayer executable at %s' % exePath )

        cmd  = [exePath, '-r', self.room, '-n', self.model]
        if aLoopback:
            cmd.extend( ['-l'] )
        elif hostId:
            cmd.extend( ['-a', '%d' % hostId] )
        if aTuneInId:
            cmd.extend( ['-t', aTuneInId] )
        if aSenderChannel:
            cmd.extend( ['-c', '%d' % aSenderChannel] )
        if aTidalId:
            cmd.extend( ['--tidal', '%s' % aTidalId] )
        if aQobuzId:
            cmd.extend( ['--qobuz', '%s' % aQobuzId] )
        self.log.Info( '', 'SoftPlayer command: %s' % cmd )
            
        self.proc = subprocess.Popen( cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT )
        self.logThread = LogThread.Thread( target=self.__Log )
        self.logThread.start()
        time.sleep( 1 )             # Let it start up 
        
    def Shutdown( self ):
        self.log.Info( self.dev, 'Shutting down......')
        self.shutdown = True
        t = LogThread.Timer( 15, self.__KillSoftPlayer )
        t.start()
        try:
            self.proc.stdin.write( 'q\n' )
            self.proc.stdin.close()
            self.proc.wait()
        except:
            self.log.Info( self.dev, 'Problem shutting down' )
        t.cancel()
        self.logThread.join()
        time.sleep( 1 )             # Let it shut down

    def __KillSoftPlayer( self ):
        """Timer CB - kills SoftPlayer process (unblocks Shutdown)"""
        self.log.Fail( self.dev, 'Did NOT shut down -> killing process' )
        self.proc.kill()
        
    def __Log( self ):
        """Log data received from stdout on SoftPlayer"""
        exception = False
        
        # running - handle log messages until shutdown called
        while not self.shutdown:
            msg = self.proc.stdout.readline()
            if 'AssertionFailed' in msg:
                exception = True

            stat = self.proc.poll()
            if stat:
                self.log.Fail( self.dev, 'Unexpected exit [code %d]' % stat )
                exception = True

            if not exception:
                lower = msg.lower()
                if 'failed' in lower or 'warning' in lower:
                    self.log.Warn( self.dev, '%s' % msg )
                else:
                    self.log.Info( self.dev, '%s' % msg )
            else:
                self.log.Fail( self.dev, '%s' % msg )
                self.shutdown = True        # force loop exit        
            
        # shutting down - clear out remaining messages and exit logging
        msg = self.proc.stdout.readline()        
        while msg:
            if not exception: 
                self.log.Info( self.dev, '%s' % msg )
            else:
                self.log.Fail( self.dev, '%s' % msg )
            msg = self.proc.stdout.readline()
        self.log.Info( self.dev, 'SoftPlayer logger shut down' )

    def __GetName( self ):
        return self.room + ':' + self.model

    name = property( __GetName, None, None, 'name' )
    
if __name__ == '__main__':

    # start softplayer, wait for exit
    tuneinId = Config.Config().Get( 'tunein.partnerid' )
    tidalId  = Config.Config().Get( 'tidal.id' )
    qobuzId  = Config.Config().Get( 'qobuz.id' ) + ':' + Config.Config().Get( 'qobuz.secret' )
    s = SoftPlayer( aRoom='TestDev', aTuneInId=tuneinId, aTidalId=tidalId, aQobuzId=qobuzId )
    if _platform in ['Windows', 'cli']:
        import msvcrt
        print '\nPress ANY KEY to EXIT'
        msvcrt.getch()
    else:
        import sys
        print '\nPress ENTER to EXIT'
        sys.stdin.readline()
    s.Shutdown()
    s.log.Cleanup()
